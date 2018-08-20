// ==========  MediaPlayer.framework/Headers/MPNowPlayingInfoLanguageOption.h
//
//  MPNowPlayingInfoLanguageOption.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>

NS_ASSUME_NONNULL_BEGIN

// MPNowPlayingInfoLanguageOption and MPNowPlayingInfoLanguageOptionGroup provide
// interfaces for setting information about language options (ie audio and subtitles)
// in the current now playing information.
//
// When using AVFoundation the categories in
// <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>
// can automatically create these classes from various AVFoundation types.

// Common values used to to populate MPNowPlayingInfoLanguageOption's
// characteristics property.
// See the AVMediaSelectionOption documentation about Media Characteristics for more details.
MP_EXTERN NSString *const MPLanguageOptionCharacteristicIsMainProgramContent NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicIsAuxiliaryContent NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicContainsOnlyForcedSubtitles NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicTranscribesSpokenDialog NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDescribesMusicAndSound NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicEasyToRead NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDescribesVideo NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicLanguageTranslation NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDubbedTranslation NS_AVAILABLE_IOS(9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicVoiceOverTranslation NS_AVAILABLE_IOS(9_0);

typedef NS_ENUM(NSUInteger, MPNowPlayingInfoLanguageOptionType) {
    MPNowPlayingInfoLanguageOptionTypeAudible,
    MPNowPlayingInfoLanguageOptionTypeLegible,
} NS_ENUM_AVAILABLE_IOS(9_0);

// -----------------------------------------------------------------------------

/// Represents a single language option option.
MP_EXTERN_CLASS_AVAILABLE(9_0)
@interface MPNowPlayingInfoLanguageOption : NSObject

- (instancetype)initWithType:(MPNowPlayingInfoLanguageOptionType)languageOptionType
                 languageTag:(NSString *)languageTag
             characteristics:(nullable NSArray<NSString *> *)languageOptionCharacteristics
                 displayName:(NSString *)displayName
                  identifier:(NSString *)identifier;

/// Represents a special case that is used to
/// represent the best legible language option based on system preferences.
/// See AVPlayerItem-selectMediaOptionAutomaticallyInMediaSelectionGroup
- (BOOL)isAutomaticLegibleLanguageOption;

/// The type of language option.
@property (nonatomic, readonly) MPNowPlayingInfoLanguageOptionType languageOptionType;

/// The IETF BCP 47 language tag.
/// A nil languageTag reprsents that this option should be disabled.
/// A languageTag with the value of MPLangaugeOptionAutoLangaugeTag represents
/// that the best langauge based on the system preferences should be used.
@property (nonatomic, readonly, nullable) NSString *languageTag;

/// Characteristics describing the content of the language options.
/// See the LanguageOptionCharacteristics for the most commonly used values.
@property (nonatomic, readonly, nullable) NSArray<NSString *> *languageOptionCharacteristics;

/// A user presentable display name for this option.
@property (nonatomic, readonly, nullable) NSString *displayName;

/// A unique identifier representing this option.
@property (nonatomic, readonly, nullable) NSString *identifier;


@end

// -----------------------------------------------------------------------------

// Represents a mutually exclusive group of language options.
// Only one language option within a given group may be active at a time.
MP_EXTERN_CLASS_AVAILABLE(9_0)
@interface MPNowPlayingInfoLanguageOptionGroup : NSObject

- (instancetype)initWithLanguageOptions:(NSArray<MPNowPlayingInfoLanguageOption *> *)languageOptions
                  defaultLanguageOption:(nullable MPNowPlayingInfoLanguageOption *)defaultLanguageOption
                    allowEmptySelection:(BOOL)allowEmptySelection;

/// The available language options within this group.
@property (nonatomic, readonly) NSArray<MPNowPlayingInfoLanguageOption *> *languageOptions;

/// The default language option, if any, within this group.
@property (nonatomic, readonly, nullable) MPNowPlayingInfoLanguageOption *defaultLanguageOption;

/// Indicates whether a selection in this group is required at all times.
@property (nonatomic, readonly) BOOL allowEmptySelection;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPContentItem.h
//
//  MPContentItem.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItemArtwork;

/// MPContentItem represents high-level metadata for a particular media item for
/// representation outside the client application. Examples of media items that a
/// developer might want to represent include song files, streaming audio URLs,
/// or radio stations.
MP_EXTERN_CLASS_AVAILABLE(7_1)

@interface MPContentItem : NSObject

/// A unique identifier for this content item. (Required)
@property (nonatomic, copy, readonly) NSString *identifier;

/// A title for this item. Usually this would be the track name, if representing
/// a song, the episode name of a podcast, etc.
@property (nonatomic, copy, nullable) NSString *title;

/// A subtitle for this item. If this were representing a song, this would
/// usually be the artist or composer.
@property (nonatomic, copy, nullable) NSString *subtitle;

/// Artwork for this item. Examples of artwork for a content item are the album
/// cover for a song, or a movie poster for a movie.
@property (nonatomic, strong, nullable) MPMediaItemArtwork *artwork;

/// Represents whether the content item is a container of other content items.
/// An example of a container content item might be an album, which contains
/// multiple songs.
@property (nonatomic, assign, getter = isContainer) BOOL container;

/// Represents whether this content item is playable or not. A content item can
/// be both a container, and playable. For example, a container item like a
/// playlist might be set as playable if the app would like to provide the
/// option of playing the playlist's tracks in order when selected.
@property (nonatomic, assign, getter = isPlayable) BOOL playable;

/// Represents the current playback progress of the item.
/// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
/// Default is -1.0 (no progress indicator shown)
@property (nonatomic, assign) float playbackProgress;

/// Designated initializer. A unique identifier is required to identify the item
/// for later use.
- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPPlayableContentManager.h
//
//  MPPlayableContentManager.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// MPPlayableContentManager is a class that manages the interactions between a
/// media application and an external media player interface. The application
/// provides the content manager with a data source, which allows the media player
/// to browse the media content offered by the application, as well as a delegate,
/// which allows the media player to relay non-media remote playback commands to the application.
MP_EXTERN_CLASS_AVAILABLE(7_1)

@interface MPPlayableContentManager : NSObject

@property (nonatomic, weak, nullable) id<MPPlayableContentDataSource> dataSource;
@property (nonatomic, weak, nullable) id<MPPlayableContentDelegate>   delegate;
@property (nonatomic, readonly) MPPlayableContentManagerContext *context;

/// Returns the application's instance of the content manager.
+ (instancetype)sharedContentManager;

/// Tells the content manager that the data source has changed and that we need to
/// reload data from the data source.
- (void)reloadData;

/// Used to begin a synchronized update to multiple MPContentItems at once.
- (void)beginUpdates;

/// Ends a synchronized update.
- (void)endUpdates;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MediaPlayerDefines.h
//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#ifdef __cplusplus
#define MP_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define MP_EXTERN     extern __attribute__((visibility ("default")))
#endif

#define MP_EXTERN_CLASS                    __attribute__((visibility("default")))
#define MP_EXTERN_CLASS_AVAILABLE(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, version)
// ==========  MediaPlayer.framework/Headers/MPPlayableContentDelegate.h
//
//  MPPlayableContentDelegate.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPPlayableContentManager, MPContentItem, MPPlayableContentManagerContext;

/// The MPPlayableContentDelegate is a protocol that allows for external media
/// players to send playback commands to an application. For instance,
/// the user could browse the application's media content (provided by the
/// MPPlayableContentDataSource) and selects a content item to play. If the media
/// player decides that it wants to play the item, it will ask the application's
/// content delegate to initiate playback.

@protocol MPPlayableContentDelegate <NSObject>
@optional

/// This method is called when a media player interface wants to play a requested
/// content item. The application should call the completion handler with an
/// appropriate error if there was an error beginning playback for the item.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initiatePlaybackOfContentItemAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void(^)(NSError * __nullable))completionHandler NS_AVAILABLE_IOS(7_1);

/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue and prepare it for playback, but not start
/// playback until a Play command is received or if the playable content manager
/// requests to play something else.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithCompletionHandler:(void(^)(NSError * __nullable))completionHandler NS_AVAILABLE_IOS(9_0);

/// This method is called when the content server notifies the manager that the current context has changed.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager didUpdateContext:(MPPlayableContentManagerContext *)context NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MediaPlayer.h
//
//  MediaPlayer.h
//  MediaPlayer
//
//  Copyright 2008-2011 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPContentItem.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaLibrary.h>
#import <MediaPlayer/MPMediaPickerController.h>
#import <MediaPlayer/MPMediaPlaylist.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaQuerySection.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import <MediaPlayer/MPMoviePlayerViewController.h>
#import <MediaPlayer/MPMusicPlayerController.h>
#import <MediaPlayer/MPNowPlayingInfoCenter.h>
#import <MediaPlayer/MPNowPlayingInfoLanguageOption.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>
#import <MediaPlayer/MPPlayableContentManager.h>
#import <MediaPlayer/MPPlayableContentManagerContext.h>
#import <MediaPlayer/MPRemoteCommand.h>
#import <MediaPlayer/MPRemoteCommandCenter.h>
#import <MediaPlayer/MPRemoteCommandEvent.h>
#import <MediaPlayer/MPVolumeSettings.h>
#import <MediaPlayer/MPVolumeView.h>
// ==========  MediaPlayer.framework/Headers/MPPlayableContentDataSource.h
//
//  MPPlayableContentDataSource.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPContentItem;

/// MPPlayableContentDataSource is a protocol that application objects conform to
/// if they want to support external media players, such as vehicle head units.
/// Data sources are responsible for providing metadata about your media to these
/// systems in a meaningful way, so that features like user interfaces and play
/// queues can be setup automatically.

@protocol MPPlayableContentDataSource <NSObject>
@optional

/// Tells the data source to begin loading content items that are children of the
/// item specified by indexPath. This is provided so that applications can begin
/// asynchronous batched loading of content before MediaPlayer begins asking for
/// content items to display.
/// Client applications should always call the completion handler after loading
/// has finished, if this method is implemented.
- (void)beginLoadingChildItemsAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void(^)(NSError * __nullable))completionHandler;

/// Tells MediaPlayer whether the content provided by the data source supports
/// playback progress as a property of its metadata.
/// If this method is not implemented, MediaPlayer will assume that progress is
/// not supported for any content items.
- (BOOL)childItemsDisplayPlaybackProgressAtIndexPath:(NSIndexPath *)indexPath;

@required
/// Returns the number of child nodes at the specified index path. In a virtual
/// filesystem, this would be the number of files in a specific folder. An empty
/// index path represents the root node.
- (NSInteger)numberOfChildItemsAtIndexPath:(NSIndexPath *)indexPath;

/// Returns the content item at the specified index path. If the content item is
/// mutated after returning, its updated contents will be sent to MediaPlayer.
- (nullable MPContentItem *)contentItemAtIndexPath:(NSIndexPath *)indexPath;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPRemoteCommand.h
//
//  MPRemoteCommand.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommandEvent;

typedef NS_ENUM(NSInteger, MPRemoteCommandHandlerStatus) {
    /// There was no error executing the requested command.
    MPRemoteCommandHandlerStatusSuccess        = 0,
    
    /// The command could not be executed because the requested content does not
    /// exist in the current application state.
    MPRemoteCommandHandlerStatusNoSuchContent  = 100,
    
    /// The command could not be executed for another reason.
    MPRemoteCommandHandlerStatusCommandFailed  = 200
} NS_ENUM_AVAILABLE_IOS(7_1);

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRemoteCommand : NSObject

/// Whether a button (for example) should be enabled and tappable for this
/// particular command.
@property (nonatomic, assign, getter = isEnabled) BOOL enabled;

// Target-action style for adding handlers to commands.
// Actions receive an MPRemoteCommandEvent as the first parameter.
// Targets are not retained by addTarget:action:, and should be removed from the
// command when the target is deallocated.
//
// Your selector should return a MPRemoteCommandHandlerStatus value when
// possible. This allows the system to respond appropriately to commands that
// may not have been able to be executed in accordance with the application's
// current state.
- (void)addTarget:(id)target action:(SEL)action;
- (void)removeTarget:(id)target action:(nullable SEL)action;
- (void)removeTarget:(nullable id)target;

/// Returns an opaque object to act as the target.
- (id)addTargetWithHandler:(MPRemoteCommandHandlerStatus(^)(MPRemoteCommandEvent *event))handler;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPSkipIntervalCommand : MPRemoteCommand

/// An array of NSNumbers (NSTimeIntervals) that contain preferred skip intervals.
@property (nonatomic, copy) NSArray *preferredIntervals;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPFeedbackCommand : MPRemoteCommand

/// Whether the feedback command is in an "active" state. An example of when a
/// feedback command would be active is if the user already "liked" a particular
/// content item.
@property (nonatomic, assign, getter = isActive) BOOL active;

/// A localized string briefly describing the context of the command.
@property (nonatomic, copy) NSString *localizedTitle;

/// An optional shorter version of the localized title for this feedback
/// command. MediaPlayer uses this property to display this command's title on
/// remote control interfaces with little screen space.
@property (nonatomic, copy) NSString *localizedShortTitle NS_AVAILABLE_IOS(8_0);

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRatingCommand : MPRemoteCommand

/// Minimum rating for the command.
@property (nonatomic, assign) float minimumRating;

/// Maximum rating for the command.
@property (nonatomic, assign) float maximumRating;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPChangePlaybackRateCommand : MPRemoteCommand

/// An array of NSNumbers (floats) that contain supported playback rates that
/// the command can send.
@property (nonatomic, copy) NSArray<NSNumber *> *supportedPlaybackRates;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMoviePlayerController.h
//
//  MPMoviePlayerController.h
//  MediaPlayer
//
//  Copyright 2008-2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaPlayback.h>
#import <UIKit/UIKit.h>

@class MPMovieAccessLog, MPMovieErrorLog;

// -----------------------------------------------------------------------------
// Types

typedef NS_ENUM(NSInteger, MPMovieScalingMode) {
    MPMovieScalingModeNone,       // No scaling
    MPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    MPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
} NS_DEPRECATED_IOS(2_0, 9_0);

typedef NS_ENUM(NSInteger, MPMoviePlaybackState) {
    MPMoviePlaybackStateStopped,
    MPMoviePlaybackStatePlaying,
    MPMoviePlaybackStatePaused,
    MPMoviePlaybackStateInterrupted,
    MPMoviePlaybackStateSeekingForward,
    MPMoviePlaybackStateSeekingBackward
} NS_DEPRECATED_IOS(3_2, 9_0);

typedef NS_OPTIONS(NSUInteger, MPMovieLoadState) {
    MPMovieLoadStateUnknown        = 0,
    MPMovieLoadStatePlayable       = 1 << 0,
    MPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    MPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
} NS_DEPRECATED_IOS(3_2, 9_0);

typedef NS_ENUM(NSInteger, MPMovieRepeatMode) {
    MPMovieRepeatModeNone,
    MPMovieRepeatModeOne
} NS_DEPRECATED_IOS(3_2, 9_0);

typedef NS_ENUM(NSInteger, MPMovieControlStyle) {
    MPMovieControlStyleNone,       // No controls
    MPMovieControlStyleEmbedded,   // Controls for an embedded view
    MPMovieControlStyleFullscreen, // Controls for fullscreen playback
    
    MPMovieControlStyleDefault = MPMovieControlStyleEmbedded
} NS_DEPRECATED_IOS(3_2, 9_0);

typedef NS_ENUM(NSInteger, MPMovieFinishReason) {
    MPMovieFinishReasonPlaybackEnded,
    MPMovieFinishReasonPlaybackError,
    MPMovieFinishReasonUserExited
} NS_DEPRECATED_IOS(3_2, 9_0);

// -----------------------------------------------------------------------------
// Movie Property Types

typedef NS_OPTIONS(NSUInteger, MPMovieMediaTypeMask) {
    MPMovieMediaTypeMaskNone  = 0,
    MPMovieMediaTypeMaskVideo = 1 << 0,
    MPMovieMediaTypeMaskAudio = 1 << 1
} NS_DEPRECATED_IOS(3_2, 9_0);

typedef NS_ENUM(NSInteger, MPMovieSourceType) {
    MPMovieSourceTypeUnknown,
    MPMovieSourceTypeFile,     // Local or progressively downloaded network content
    MPMovieSourceTypeStreaming // Live or on-demand streaming content
} NS_DEPRECATED_IOS(3_2, 9_0);

// -----------------------------------------------------------------------------
// Movie Player
// 
// See MPMediaPlayback.h for the playback methods.

MP_EXTERN_CLASS_AVAILABLE(2_0)
NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")

@interface MPMoviePlayerController : NSObject <MPMediaPlayback>

- (instancetype)initWithContentURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSURL *contentURL;

// The view in which the media and playback controls are displayed.
@property (nonatomic, readonly) UIView *view;

// A view for customization which is always displayed behind movie content.
@property (nonatomic, readonly) UIView *backgroundView;

// Returns the current playback state of the movie player.
@property (nonatomic, readonly) MPMoviePlaybackState playbackState;

// Returns the network load state of the movie player.
@property (nonatomic, readonly) MPMovieLoadState loadState;

// The style of the playback controls. Defaults to MPMovieControlStyleDefault.
@property (nonatomic) MPMovieControlStyle controlStyle;

// Determines how the movie player repeats when reaching the end of playback. Defaults to MPMovieRepeatModeNone.
@property (nonatomic) MPMovieRepeatMode repeatMode;

// Indicates if a movie should automatically start playback when it is likely to finish uninterrupted based on e.g. network conditions. Defaults to YES.
@property (nonatomic) BOOL shouldAutoplay;

// Determines if the movie is presented in the entire screen (obscuring all other application content). Default is NO.
// Setting this property to YES before the movie player's view is visible will have no effect.
@property (nonatomic, getter=isFullscreen) BOOL fullscreen;
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

// Determines how the content scales to fit the view. Defaults to MPMovieScalingModeAspectFit.
@property (nonatomic) MPMovieScalingMode scalingMode;

// Returns YES if the first video frame has been made ready for display for the current item.
// Will remain NO for items that do not have video tracks associated.
@property (nonatomic, readonly) BOOL readyForDisplay NS_AVAILABLE_IOS(6_0);

@end

// -----------------------------------------------------------------------------
// Movie properties of the current movie prepared for playback.

@interface MPMoviePlayerController (MPMovieProperties)

// The types of media in the movie, or MPMovieMediaTypeNone if not known.
@property (nonatomic, readonly) MPMovieMediaTypeMask movieMediaTypes NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.");

// The playback type of the movie. Defaults to MPMovieSourceTypeUnknown.
// Specifying a playback type before playing the movie can result in faster load times.
@property (nonatomic) MPMovieSourceType movieSourceType NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// The duration of the movie, or 0.0 if not known.
@property (nonatomic, readonly) NSTimeInterval duration NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// The currently playable duration of the movie, for progressively downloaded network content.
@property (nonatomic, readonly) NSTimeInterval playableDuration NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// The natural size of the movie, or CGSizeZero if not known/applicable.
@property (nonatomic, readonly) CGSize naturalSize NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// The start time of movie playback. Defaults to NaN, indicating the natural start time of the movie.
@property (nonatomic) NSTimeInterval initialPlaybackTime NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// The end time of movie playback. Defaults to NaN, which indicates natural end time of the movie.
@property (nonatomic) NSTimeInterval endPlaybackTime NS_DEPRECATED_IOS(2_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

// Indicates whether the movie player allows AirPlay video playback. Defaults to YES on iOS 5.0 and later.
@property (nonatomic) BOOL allowsAirPlay NS_DEPRECATED_IOS(4_3, 9_0, "Use AVPlayerViewController in AVKit.")
;

// Indicates whether the movie player is currently playing video via AirPlay.
@property (nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive NS_DEPRECATED_IOS(5_0, 9_0, "Use AVPlayerViewController in AVKit.")
;

@end

// -----------------------------------------------------------------------------
// Movie Player Notifications

// Posted when the scaling mode changes.
MP_EXTERN NSString * const MPMoviePlayerScalingModeDidChangeNotification NS_DEPRECATED_IOS(2_0, 9_0);

// Posted when movie playback ends or a user exits playback.
MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishNotification NS_DEPRECATED_IOS(2_0, 9_0);

MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishReasonUserInfoKey NS_DEPRECATED_IOS(3_2, 9_0); // NSNumber (MPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSString * const MPMoviePlayerPlaybackStateDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);

// Posted when the network load state changes.
MP_EXTERN NSString * const MPMoviePlayerLoadStateDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);

// Posted when the currently playing movie changes.
MP_EXTERN NSString * const MPMoviePlayerNowPlayingMovieDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);

// Posted when the movie player enters or exits fullscreen mode.
MP_EXTERN NSString * const MPMoviePlayerWillEnterFullscreenNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMoviePlayerDidEnterFullscreenNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMoviePlayerWillExitFullscreenNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMoviePlayerDidExitFullscreenNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationDurationUserInfoKey NS_DEPRECATED_IOS(3_2, 9_0); // NSNumber of double (NSTimeInterval)
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationCurveUserInfoKey NS_DEPRECATED_IOS(3_2, 9_0);     // NSNumber of NSUInteger (UIViewAnimationCurve)

// Posted when the movie player begins or ends playing video via AirPlay.
MP_EXTERN NSString * const MPMoviePlayerIsAirPlayVideoActiveDidChangeNotification NS_DEPRECATED_IOS(5_0, 9_0);

// Posted when the ready for display state changes.
MP_EXTERN NSString * const MPMoviePlayerReadyForDisplayDidChangeNotification NS_DEPRECATED_IOS(6_0, 9_0);

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
MP_EXTERN NSString * const MPMovieMediaTypesAvailableNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMovieSourceTypeAvailableNotification NS_DEPRECATED_IOS(3_2, 9_0); // Posted if the movieSourceType is MPMovieSourceTypeUnknown when preparing for playback.
MP_EXTERN NSString * const MPMovieDurationAvailableNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMovieNaturalSizeAvailableNotification NS_DEPRECATED_IOS(3_2, 9_0);

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, MPMovieTimeOption) {
    MPMovieTimeOptionNearestKeyFrame,
    MPMovieTimeOptionExact
} NS_DEPRECATED_IOS(3_2, 9_0);

@interface MPMoviePlayerController (MPMoviePlayerThumbnailGeneration)

// Returns a thumbnail at the given time.
// Deprecated.  Use -requestThumbnailImagesAtTimes:timeOption: / MPMoviePlayerThumbnailImageRequestDidFinishNotification instead.
- (UIImage *)thumbnailImageAtTime:(NSTimeInterval)playbackTime timeOption:(MPMovieTimeOption)option NS_DEPRECATED_IOS(3_2, 7_0);

// Asynchronously request thumbnails for one or more times, provided as an array of NSNumbers (double).
// Posts MPMoviePlayerThumbnailImageRequestDidFinishNotification on completion.
- (void)requestThumbnailImagesAtTimes:(NSArray *)playbackTimes timeOption:(MPMovieTimeOption)option NS_DEPRECATED_IOS(3_2, 9_0);

// Cancels all pending asynchronous thumbnail requests.
- (void)cancelAllThumbnailImageRequests NS_DEPRECATED_IOS(3_2, 9_0);

@end

// Posted when each thumbnail image request is completed.
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageRequestDidFinishNotification NS_DEPRECATED_IOS(3_2, 9_0);
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageKey NS_DEPRECATED_IOS(3_2, 9_0); // UIImage, may be nil if an error occurred.
MP_EXTERN NSString * const MPMoviePlayerThumbnailTimeKey NS_DEPRECATED_IOS(3_2, 9_0);  // NSNumber (double)
MP_EXTERN NSString * const MPMoviePlayerThumbnailErrorKey NS_DEPRECATED_IOS(3_2, 9_0); // NSError

// -----------------------------------------------------------------------------
// Timed Metadata

@interface MPMoviePlayerController (MPMoviePlayerTimedMetadataAdditions)

// Returns an array of the most recent MPTimedMetadata objects provided by the media stream.
@property (nonatomic, readonly) NSArray *timedMetadata NS_DEPRECATED_IOS(4_0, 9_0);

@end

MP_EXTERN_CLASS_AVAILABLE(4_0)
NS_DEPRECATED_IOS(4_0, 9_0)

@interface MPTimedMetadata : NSObject

// A key which identifies a piece of timed metadata.
@property (nonatomic, readonly) NSString *key;

// The namespace of the identifying key.
@property (nonatomic, readonly) NSString *keyspace;

// The object value of the metadata.
@property (nonatomic, readonly) id value;

// The timestamp of the metadata, in the timebase of the media stream.
@property (nonatomic, readonly) NSTimeInterval timestamp;

// A dictionary containing all metadata information associated with this object, which may hold additional key-specific data (see below).
@property (nonatomic, readonly) NSDictionary *allMetadata;

@end

// Posted when new timed metadata arrives.
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUpdatedNotification NS_DEPRECATED_IOS(4_0, 9_0);
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUserInfoKey NS_DEPRECATED_IOS(4_0, 9_0);       // NSDictionary of the most recent MPTimedMetadata objects.

// Additional dictionary keys for use with the 'allMetadata' property. All keys are optional.
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyName NS_DEPRECATED_IOS(4_0, 9_0);           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyInfo NS_DEPRECATED_IOS(4_0, 9_0);           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyMIMEType NS_DEPRECATED_IOS(4_0, 9_0);       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyDataType NS_DEPRECATED_IOS(4_0, 9_0);       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyLanguageCode NS_DEPRECATED_IOS(4_0, 9_0);   // NSString (ISO 639-2)

// -----------------------------------------------------------------------------

@interface MPMoviePlayerController (MPMovieLogging)

// Returns an object that represents a snapshot of the network access log. Can be nil.
@property (nonatomic, readonly) MPMovieAccessLog *accessLog NS_DEPRECATED_IOS(4_3, 9_0);

// Returns an object that represents a snapshot of the error log. Can be nil.
@property (nonatomic, readonly) MPMovieErrorLog *errorLog NS_DEPRECATED_IOS(4_3, 9_0);

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLog accumulates key metrics about network playback and presents them as a collection of MPMovieAccessLogEvent instances.
// Each MPMovieAccessLogEvent instance collates the data that relates to each uninterrupted period of playback.

MP_EXTERN_CLASS_AVAILABLE(4_3)
NS_DEPRECATED_IOS(4_3, 9_0)

@interface MPMovieAccessLog : NSObject <NSCopying>

// Returns the webserver access log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieAccessLogEvent instances that represent the chronological sequence of events contained in the access log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLog provides data to identify if, and when, network resource playback failures occured.

MP_EXTERN_CLASS_AVAILABLE(4_3)
NS_DEPRECATED_IOS(4_3, 9_0)

@interface MPMovieErrorLog : NSObject <NSCopying>

// Returns the webserver error log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieErrorLogEvent instances that represent the chronological sequence of events contained in the error log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLogEvent repesents a single access log entry.

MP_EXTERN_CLASS_AVAILABLE(4_3)
NS_DEPRECATED_IOS(4_3, 9_0)

@interface MPMovieAccessLogEvent : NSObject <NSCopying>

// A count of media segments downloaded from the server to this client.
@property (nonatomic, readonly) NSUInteger numberOfSegmentsDownloaded;

// The date/time at which playback began for this event.
@property (nonatomic, readonly) NSDate *playbackStartDate;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the last delivered media segment. Can be either an IPv4 or IPv6 address.
@property (nonatomic, readonly) NSString *serverAddress;

// A count of changes to the serverAddress property over the last uninterrupted period of playback.
@property (nonatomic, readonly) NSUInteger numberOfServerAddressChanges;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// An offset into the playlist where the last uninterrupted period of playback began, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval playbackStartOffset;

// The accumulated duration of the media downloaded, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval segmentsDownloadedDuration;

// The accumulated duration of the media played, in seconds.
@property (nonatomic, readonly) NSTimeInterval durationWatched;

// The total number of playback stalls encountered. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger numberOfStalls;

// The accumulated number of bytes transferred. The value is negative if unknown.
@property (nonatomic, readonly) int64_t numberOfBytesTransferred;

// The empirical throughput across all media downloaded, in bits per second.
@property (nonatomic, readonly) double observedBitrate;

// The throughput required to play the stream, as advertised by the server, in bits per second.
@property (nonatomic, readonly) double indicatedBitrate;

// The total number of dropped video frames.
@property (nonatomic, readonly) NSInteger numberOfDroppedVideoFrames;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLogEvent repesents a single error log entry.

MP_EXTERN_CLASS_AVAILABLE(4_3)
NS_DEPRECATED_IOS(4_3, 9_0)

@interface MPMovieErrorLogEvent : NSObject <NSCopying>

// The date and time when the error occured.
@property (nonatomic, readonly) NSDate *date;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the error.
@property (nonatomic, readonly) NSString *serverAddress;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// A unique error code identifier. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger errorStatusCode;

// The domain of the error.
@property (nonatomic, readonly) NSString *errorDomain;

// A description of the error encountered.
@property (nonatomic, readonly) NSString *errorComment;

@end

// -----------------------------------------------------------------------------
// Deprecated methods and properties
// These will be removed in a future release of iOS

@interface MPMoviePlayerController (MPMoviePlayerDeprecated)

// Indicates if the movie player should inherit the application's audio session instead of creating a new session (which would interrupt the application's session).
// Defaults to YES. Setting this property during playback will not take effect until playback is stopped and started again.
@property (nonatomic) BOOL useApplicationAudioSession NS_DEPRECATED_IOS(3_2, 6_0);

@end
// ==========  MediaPlayer.framework/Headers/MPMusicPlayerController.h
//
//  MPMusicPlayerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaPlayback.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem, MPMediaQuery, MPMusicPlayerControllerInternal;

typedef NS_ENUM(NSInteger, MPMusicPlaybackState) {
    MPMusicPlaybackStateStopped,
    MPMusicPlaybackStatePlaying,
    MPMusicPlaybackStatePaused,
    MPMusicPlaybackStateInterrupted,
    MPMusicPlaybackStateSeekingForward,
    MPMusicPlaybackStateSeekingBackward
};

typedef NS_ENUM(NSInteger, MPMusicRepeatMode) {
    MPMusicRepeatModeDefault, // the user's preference for repeat mode
    MPMusicRepeatModeNone,
    MPMusicRepeatModeOne,
    MPMusicRepeatModeAll
};

typedef NS_ENUM(NSInteger, MPMusicShuffleMode) {
    MPMusicShuffleModeDefault, // the user's preference for shuffle mode
    MPMusicShuffleModeOff,
    MPMusicShuffleModeSongs,
    MPMusicShuffleModeAlbums
};

// MPMusicPlayerController allows playback of MPMediaItems through the Music application.
MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMusicPlayerController : NSObject <MPMediaPlayback>

/// Playing media items with the applicationMusicPlayer will restore the user's Music state after the application quits.
+ (MPMusicPlayerController *)applicationMusicPlayer;

/// Playing media items with the systemMusicPlayer will replace the user's current Music state.
+ (MPMusicPlayerController *)systemMusicPlayer;

+ (MPMusicPlayerController *)iPodMusicPlayer NS_DEPRECATED_IOS(3_0, 8_0, "Use +systemMusicPlayer instead.");

@end

@interface MPMusicPlayerController (MPPlaybackControl)

// See MPMediaPlayback.h for basic playback control.

// Returns the current playback state of the music player
@property (nonatomic, readonly) MPMusicPlaybackState playbackState;

// Determines how music repeats after playback completes. Defaults to MPMusicRepeatModeDefault.
@property (nonatomic) MPMusicRepeatMode repeatMode;

// Determines how music is shuffled when playing. Defaults to MPMusicShuffleModeDefault.
@property (nonatomic) MPMusicShuffleMode shuffleMode;

// The current volume of playing music, in the range of 0.0 to 1.0.
// This property is deprecated -- use MPVolumeView for volume control instead.
@property (nonatomic) float volume NS_DEPRECATED_IOS(3_0, 7_0);

// Returns the currently playing media item, or nil if none is playing.
// Setting the nowPlayingItem to an item in the current queue will begin playback at that item.
@property (nonatomic, copy, nullable) MPMediaItem *nowPlayingItem;

// Returns the index of the now playing item in the current playback queue.
// May return NSNotFound if the index is not valid (e.g. an empty queue or an infinite playlist).
@property (nonatomic, readonly) NSUInteger indexOfNowPlayingItem NS_AVAILABLE_IOS(5_0);

// Call -play to begin playback after setting an item queue source. Setting a query will implicitly use MPMediaGroupingTitle.
- (void)setQueueWithQuery:(MPMediaQuery *)query;
- (void)setQueueWithItemCollection:(MPMediaItemCollection *)itemCollection;

// Skips to the next item in the queue. If already at the last item, this will end playback.
- (void)skipToNextItem;

// Restarts playback at the beginning of the currently playing media item.
- (void)skipToBeginning;

// Skips to the previous item in the queue. If already at the first item, this will end playback.
- (void)skipToPreviousItem;

// These methods determine whether playback notifications will be generated.
// Calls to begin/endGeneratingPlaybackNotifications are nestable.
- (void)beginGeneratingPlaybackNotifications;
- (void)endGeneratingPlaybackNotifications;

@end

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSString * const MPMusicPlayerControllerPlaybackStateDidChangeNotification;

// Posted when the currently playing media item changes.
MP_EXTERN NSString * const MPMusicPlayerControllerNowPlayingItemDidChangeNotification;

// Posted when the current volume changes.
MP_EXTERN NSString * const MPMusicPlayerControllerVolumeDidChangeNotification;

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPlayback.h
//
//  MPMediaPlayback.h
//  MediaPlayer
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

@protocol MPMediaPlayback

// Prepares the current queue for playback, interrupting any active (non-mixible) audio sessions.
// Automatically invoked when -play is called if the player is not already prepared.
- (void)prepareToPlay;

// Returns YES if prepared for playback.
@property(nonatomic, readonly) BOOL isPreparedToPlay;

// Plays items from the current queue, resuming paused playback if possible.
- (void)play;

// Pauses playback if playing.
- (void)pause;

// Ends playback. Calling -play again will start from the beginnning of the queue.
- (void)stop;

// The current playback time of the now playing item in seconds.
@property(nonatomic) NSTimeInterval currentPlaybackTime;

// The current playback rate of the now playing item. Default is 1.0 (normal speed).
// Pausing will set the rate to 0.0. Setting the rate to non-zero implies playing.
@property(nonatomic) float currentPlaybackRate;

// The seeking rate will increase the longer scanning is active.
- (void)beginSeekingForward;
- (void)beginSeekingBackward;
- (void)endSeeking;

@end

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
MP_EXTERN NSString *const MPMediaPlaybackIsPreparedToPlayDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);
// ==========  MediaPlayer.framework/Headers/MPMediaEntity.h
//
//  MPMediaEntity.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaLibrary;

typedef uint64_t MPMediaEntityPersistentID;

// An MPMediaEntity represents an abstract member of an MPMediaLibrary.
// Concrete subclasses are MPMediaItem and MPMediaItemCollection.

MP_EXTERN_CLASS_AVAILABLE(4_2)

@interface MPMediaEntity : NSObject <NSSecureCoding>

// Returns YES for properties which can be used to construct MPMediaPropertyPredicates.
+ (BOOL)canFilterByProperty:(NSString *)property;

// Executes a provided block with the fetched values for the given item properties, or nil if no value is available for a property.
// In some cases, enumerating the values for multiple properties can be more efficient than fetching each individual property with -valueForProperty:.
- (void)enumerateValuesForProperties:(NSSet<NSString *> *)properties usingBlock:(void (^)(NSString *property, id value, BOOL *stop))block NS_AVAILABLE_IOS(4_0);

// Read-only support for Objective-C subscripting syntax with MPMediaEntity property constants.
- (nullable id)objectForKeyedSubscript:(id)key NS_AVAILABLE_IOS(8_0);

// Returns the value for the given entity property.
// MPMediaItem and MPMediaPlaylist have their own properties
- (nullable id)valueForProperty:(NSString *)property;

#pragma mark - Properties

MP_EXTERN NSString * const MPMediaEntityPropertyPersistentID NS_AVAILABLE_IOS(4_2);         // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID NS_AVAILABLE_IOS(7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPlaylist.h
//
//  MPMediaPlaylist.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem;

// A playlist may have any number of MPMediaPlaylistAttributes associated.
typedef NS_OPTIONS(NSUInteger, MPMediaPlaylistAttribute) {
    MPMediaPlaylistAttributeNone    = 0,
    MPMediaPlaylistAttributeOnTheGo = (1 << 0), // if set, the playlist was created on a device rather than synced from iTunes
    MPMediaPlaylistAttributeSmart   = (1 << 1),
    MPMediaPlaylistAttributeGenius  = (1 << 2)
} NS_ENUM_AVAILABLE_IOS(3_0);

// An MPMediaPlaylist is a collection of related MPMediaItems in an MPMediaLibrary.
// Playlists have a unique identifier which persists across application launches.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaPlaylist : MPMediaItemCollection

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaPlaylistPropertyPersistentID;                             // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaPlaylistPropertyName;                                     // filterable
@property (nonatomic, readonly, nullable) NSString *name NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaPlaylistPropertyPlaylistAttributes;                       // filterable
@property (nonatomic, readonly) MPMediaPlaylistAttribute playlistAttributes NS_AVAILABLE_IOS(7_0);

// For playlists with attribute MPMediaPlaylistAttributeGenius, the seedItems are the MPMediaItems which were used to the generate the playlist.
// Returns nil for playlists without MPMediaPlaylistAttributeGenius set.
MP_EXTERN NSString * const MPMediaPlaylistPropertySeedItems;
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *seedItems NS_AVAILABLE_IOS(8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaQuerySection.h
//
//  MPMediaQuerySection.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

// An MPMediaQuerySection object represents a single section grouping for a query.

MP_EXTERN_CLASS_AVAILABLE(4_2)

@interface MPMediaQuerySection : NSObject <NSSecureCoding, NSCopying>

// The localized title of the section grouping.
@property (nonatomic, copy, readonly) NSString *title;

// The range in the query's corresponding collections or items array represented by this section.
@property (nonatomic, assign, readonly) NSRange range;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPRemoteCommandCenter.h
//
//  MPRemoteCommandCenter.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommand, MPSkipIntervalCommand, MPRatingCommand, MPChangePlaybackRateCommand, MPFeedbackCommand;

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRemoteCommandCenter : NSObject

// Playback Commands
@property (nonatomic, readonly) MPRemoteCommand *pauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *playCommand;
@property (nonatomic, readonly) MPRemoteCommand *stopCommand;
@property (nonatomic, readonly) MPRemoteCommand *togglePlayPauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *enableLanguageOptionCommand;
@property (nonatomic, readonly) MPRemoteCommand *disableLanguageOptionCommand;

// Previous/Next Track Commands
@property (nonatomic, readonly) MPRemoteCommand *nextTrackCommand;
@property (nonatomic, readonly) MPRemoteCommand *previousTrackCommand;

// Skip Interval Commands
@property (nonatomic, readonly) MPSkipIntervalCommand *skipForwardCommand;
@property (nonatomic, readonly) MPSkipIntervalCommand *skipBackwardCommand;

// Seek Commands
@property (nonatomic, readonly) MPRemoteCommand *seekForwardCommand;
@property (nonatomic, readonly) MPRemoteCommand *seekBackwardCommand;

// Rating Command
@property (nonatomic, readonly) MPRatingCommand *ratingCommand;

// Playback Commands
@property (nonatomic, readonly) MPChangePlaybackRateCommand *changePlaybackRateCommand;

// Feedback Commands
// These are generalized to three distinct actions. Your application can provide
// additional context about these actions with the localizedTitle property in
// MPFeedbackCommand.
@property (nonatomic, readonly) MPFeedbackCommand *likeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *dislikeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *bookmarkCommand;

+ (MPRemoteCommandCenter *)sharedCommandCenter;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPVolumeSettings.h
//
//  MPVolumeSettings.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>

MP_EXTERN void MPVolumeSettingsAlertShow();
MP_EXTERN void MPVolumeSettingsAlertHide();
MP_EXTERN BOOL MPVolumeSettingsAlertIsVisible();
// ==========  MediaPlayer.framework/Headers/MPPlayableContentManagerContext.h
//
//  MPPlayableContentManagerContext.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>


/// MPPlayableContentManagerContext represents the current state of
/// the playable content endpoint. A context is retrievable from an instance
/// of MPPlayableContentManager.
MP_EXTERN_CLASS_AVAILABLE(8_4)

@interface MPPlayableContentManagerContext : NSObject

/// The number of items the content server will display when content limiting is enforced.
/// Returns NSIntegerMax if the content server will never limit the number of items.
@property (nonatomic, readonly) NSInteger enforcedContentItemsCount;

/// The depth of the navigation hierarchy the content server will allow. Exceeding this limit will result in a crash.
@property (nonatomic, readonly) NSInteger enforcedContentTreeDepth;

/// Represents whether content limits are being enforced by the content server or not.
@property (nonatomic, readonly) BOOL contentLimitsEnforced;
@property (nonatomic, readonly) BOOL contentLimitsEnabled NS_DEPRECATED_IOS(8_4, 9_0, "Use contentLimitsEnforced");

/// Represents whether the content server is available or not.
@property (nonatomic, readonly) BOOL endpointAvailable;

@end
// ==========  MediaPlayer.framework/Headers/MPMediaLibrary.h
//
//  MPMediaLibrary.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaQuery;

// MPMediaLibrary represents a collection of media on a device, and can be used 
// to fetch items and playlists from the user's synced iTunes library.
// 
// See MPMediaQuery.h for a list of common queries or to build a custom query 
// from a chain of filter predicates.

// -----------------------------------------------------------------------------


MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaLibrary : NSObject <NSSecureCoding>

+ (MPMediaLibrary *)defaultMediaLibrary;

// Returns the date at which the media library was last modified.
@property(nonatomic, readonly) NSDate *lastModifiedDate;

// MPMediaLibraryDidChangeNotification will be posted when a sync happens.
- (void)beginGeneratingLibraryChangeNotifications;
- (void)endGeneratingLibraryChangeNotifications;

@end


// -----------------------------------------------------------------------------
// Notifications

// Any items or playlists which were previously cached should be re-evaluated from queries when MPMediaLibraryDidChangeNotification is posted.
MP_EXTERN NSString * const MPMediaLibraryDidChangeNotification;

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h
//
//  AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVMediaFormat.h>

NS_ASSUME_NONNULL_BEGIN

@class MPNowPlayingInfoLanguageOption, MPNowPlayingInfoLanguageOptionGroup;

/// Category for creating language options from AV types
@interface AVMediaSelectionOption (MPNowPlayingInfoLanguageOptionAdditions)

/// Will create a language option from the AVMediaSelectionOption
/// Returns nil if the AVMediaSelectionOption does not represent an Audible or Legible selection option.
- (nullable MPNowPlayingInfoLanguageOption *)makeNowPlayingInfoLanguageOption;

@end

// -----------------------------------------------------------------------------

@interface AVMediaSelectionGroup (MPNowPlayingInfoLanguageOptionAdditions)

/// Will create a language option group from the AVMediaSelectionGroup
/// Any AVMediaSelectionOptions in the AVMediaSelectionGroup not representing
/// Audible or Legible selection options will be ignored.
- (MPNowPlayingInfoLanguageOptionGroup *)makeNowPlayingInfoLanguageOptionGroup;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPRemoteCommandEvent.h
//
//  MPRemoteCommandEvent.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPNowPlayingInfoLanguageOption.h>


NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommand;

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRemoteCommandEvent : NSObject

/// The command that sent the event.
@property (nonatomic, readonly) MPRemoteCommand *command;

/// The time when the event occurred.
@property (nonatomic, readonly) NSTimeInterval timestamp;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPSkipIntervalCommandEvent : MPRemoteCommandEvent

/// The chosen interval for this skip command event.
@property (nonatomic, readonly) NSTimeInterval interval;

@end

typedef NS_ENUM(NSUInteger, MPSeekCommandEventType) {
    MPSeekCommandEventTypeBeginSeeking,
    MPSeekCommandEventTypeEndSeeking
} NS_ENUM_AVAILABLE_IOS(7_1);

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPSeekCommandEvent : MPRemoteCommandEvent

/// The type of seek command event, which specifies whether an external player
/// began or ended seeking.
@property (nonatomic, readonly) MPSeekCommandEventType type;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRatingCommandEvent : MPRemoteCommandEvent

/// The chosen rating for this command event. This value will be within the
/// minimumRating and maximumRating values set for the MPRatingCommand object.
@property (nonatomic, readonly) float rating;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPChangePlaybackRateCommandEvent : MPRemoteCommandEvent

/// The chosen playback rate for this command event. This value will be equal
/// to one of the values specified in the supportedPlaybackRates array for the
/// MPChangePlaybackRateCommand object.
@property (nonatomic, readonly) float playbackRate;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPFeedbackCommandEvent : MPRemoteCommandEvent

/// Whether the command event is a negative operation. For example, the command
/// might ask that the app remove a bookmark for a particular track, rather than
/// add it. In this case, the handler for the bookmark command should check this
/// flag and remove the bookmark if it is set to YES.
///
/// For like/dislike, a "negative like" might be treated differently from a
/// dislike command. The app might want to remove the "like" flag from the
/// current track, but not blacklist and skip to the next track as it would for
/// a dislike command.
@property (nonatomic, readonly, getter = isNegative) BOOL negative;

@end

MP_EXTERN_CLASS_AVAILABLE(9_0)
@interface MPChangeLanguageOptionCommandEvent : MPRemoteCommandEvent

/// The requested language option to change.
/// The supplied language option may be the Automatic Legible Language Option
/// which would mean that best legible language option based on user preferences
/// is being requested. See MPNowPlayingInfoLanguageOption isAutomaticLegibleLanguageOption
@property (nonatomic, readonly) MPNowPlayingInfoLanguageOption *languageOption;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPickerController.h
//
//  MPMediaPickerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPMediaPickerControllerDelegate;

// MPMediaPickerController is a UIViewController for visually selecting media items.
// To display it, present it modally on an existing view controller.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaPickerController : UIViewController

- (instancetype)initWithMediaTypes:(MPMediaType)mediaTypes NS_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly) MPMediaType mediaTypes;

@property (nonatomic, weak, nullable) id<MPMediaPickerControllerDelegate> delegate;

@property (nonatomic) BOOL allowsPickingMultipleItems; // default is NO

@property (nonatomic) BOOL showsCloudItems NS_AVAILABLE_IOS(6_0); // default is YES

@property (nonatomic, copy, nullable) NSString *prompt; // displays a prompt for the user above the navigation bar buttons

@end


@protocol MPMediaPickerControllerDelegate<NSObject>
@optional

// It is the delegate's responsibility to dismiss the modal view controller on the parent view controller.

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection;
- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPVolumeView.h
//
//  MPVolumeView.h
//  MediaPlayer
//
//  Copyright 2008-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

MP_EXTERN_CLASS_AVAILABLE(2_0)

@interface MPVolumeView : UIView <NSCoding>

@property (nonatomic) BOOL showsVolumeSlider NS_AVAILABLE_IOS(4_2); // Default is YES.
@property (nonatomic) BOOL showsRouteButton NS_AVAILABLE_IOS(4_2);  // Default is YES.

// Returns YES if wireless routes (AirPlay, Bluetooth, etc) are available for user selection.
// Note that the view must be in present in a window hierarchy in order to discover some types of wireless routes.
@property (nonatomic, readonly, getter=areWirelessRoutesAvailable) BOOL wirelessRoutesAvailable NS_AVAILABLE_IOS(7_0);

// Returns YES if a wireless route is active.
@property (nonatomic, readonly, getter=isWirelessRouteActive) BOOL wirelessRouteActive NS_AVAILABLE_IOS(7_0);

// Volume slider customization

- (void)setMinimumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (void)setMaximumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (void)setVolumeThumbImage:(nullable UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

- (nullable UIImage *)minimumVolumeSliderImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (nullable UIImage *)maximumVolumeSliderImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (nullable UIImage *)volumeThumbImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

// Sets the image for the EU volume limit. When appropriate, this image will be displayed on top of the
// maximumVolumeSliderImage. It must be visually distinct from the maximumVolumeSliderImage, and use
// a color similar to the default, to convey a sense of warning to the user. The same image is used for
// all control states. For debugging purposes, switch on the "EU Volume Limit" setting in the Developer
// menu of the Settings application to always enable the volume limit.
@property (nonatomic, strong, nullable) UIImage *volumeWarningSliderImage NS_AVAILABLE_IOS(7_0);

- (CGRect)volumeSliderRectForBounds:(CGRect)bounds NS_AVAILABLE_IOS(6_0);
- (CGRect)volumeThumbRectForBounds:(CGRect)bounds volumeSliderRect:(CGRect)rect value:(float)value NS_AVAILABLE_IOS(6_0);

// Route button customization

- (void)setRouteButtonImage:(nullable UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (nullable UIImage *)routeButtonImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

- (CGRect)routeButtonRectForBounds:(CGRect)bounds NS_AVAILABLE_IOS(6_0);

@end

// Posted when the wirelessRoutesAvailable property changes.
MP_EXTERN NSString *const MPVolumeViewWirelessRoutesAvailableDidChangeNotification NS_AVAILABLE_IOS(7_0);

// Posted when the wirelessRouteActive property changes.
MP_EXTERN NSString *const MPVolumeViewWirelessRouteActiveDidChangeNotification NS_AVAILABLE_IOS(7_0);

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaItemCollection.h
//
//  MPMediaItemCollection.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItem.h>

NS_ASSUME_NONNULL_BEGIN

// An MPMediaItemCollection is a collection of related MPMediaItems in a media library.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaItemCollection : MPMediaEntity

// Creates a media item collection by copying an array of MPMediaItems.
+ (MPMediaItemCollection *)collectionWithItems:(NSArray<MPMediaItem *> *)items;

- (instancetype)initWithItems:(NSArray<MPMediaItem *> *)items NS_DESIGNATED_INITIALIZER;

// Returns the MPMediaItems in the collection.
@property (nonatomic, readonly) NSArray<MPMediaItem *> *items;

// Returns an item representative of other items in the collection.
// This item can be used for common item properties in the collection, often more efficiently than fetching an item out of the items array.
@property (nonatomic, readonly, nullable) MPMediaItem *representativeItem;

// Returns the number of items in the collection.
// In some cases, this is more efficient than fetching the items array and asking for the count.
@property (nonatomic, readonly) NSUInteger count;

// Returns the types of media which the collection holds.
@property (nonatomic, readonly) MPMediaType mediaTypes;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPNowPlayingInfoCenter.h
//
//  MPNowPlayingInfoCenter.h
//  MediaPlayer
//
//  Copyright 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

// -----------------------------------------------------------------------------
// MPNowPlayingInfoCenter provides an interface for setting the current now 
// playing information for the application. This information will be displayed 
// wherever now playing information typically appears, such as the lock screen
// and app switcher. The now playing info dictionary contains a group of 
// metadata properties for a now playing item. The list of property constants
// is available in <MediaPlayer/MPMediaItem.h>. The properties which are 
// currently supported include:
// 
// MPMediaItemPropertyAlbumTitle
// MPMediaItemPropertyAlbumTrackCount
// MPMediaItemPropertyAlbumTrackNumber
// MPMediaItemPropertyArtist
// MPMediaItemPropertyArtwork
// MPMediaItemPropertyComposer
// MPMediaItemPropertyDiscCount
// MPMediaItemPropertyDiscNumber
// MPMediaItemPropertyGenre
// MPMediaItemPropertyPersistentID
// MPMediaItemPropertyPlaybackDuration
// MPMediaItemPropertyTitle
//
// In addition, metadata properties specific to the current playback session
// may also be specified -- see "Additional metadata properties" below.

MP_EXTERN_CLASS_AVAILABLE(5_0)
@interface MPNowPlayingInfoCenter : NSObject

// Returns the default now playing info center.
// The default center holds now playing info about the current application.
+ (MPNowPlayingInfoCenter *)defaultCenter;

// The current now playing info for the center.
// Setting the info to nil will clear it.
@property (copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo;

@end

// -----------------------------------------------------------------------------
// Additional metadata properties

// The elapsed time of the now playing item, in seconds.
// Note the elapsed time will be automatically extrapolated from the previously 
// provided elapsed time and playback rate, so updating this property frequently
// is not required (or recommended.)
MP_EXTERN NSString *const MPNowPlayingInfoPropertyElapsedPlaybackTime NS_AVAILABLE_IOS(5_0); // NSNumber (double)

// The playback rate of the now playing item, with 1.0 representing normal 
// playback. For example, 2.0 would represent playback at twice the normal rate.
// If not specified, assumed to be 1.0.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackRate NS_AVAILABLE_IOS(5_0); // NSNumber (double)

// The "default" playback rate of the now playing item. You should set this
// property if your app is playing a media item at a rate other than 1.0 in a
// default playback state. e.g., if you are playing back content at a rate of
// 2.0 and your playback state is not fast-forwarding, then the default
// playback rate should also be 2.0. Conversely, if you are playing back content
// at a normal rate (1.0) but the user is fast-forwarding your content at a rate
// greater than 1.0, then the default playback rate should be set to 1.0.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyDefaultPlaybackRate NS_AVAILABLE_IOS(8_0); // NSNumber (double)

// The index of the now playing item in the application's playback queue.
// Note that the queue uses zero-based indexing, so the index of the first item 
// would be 0 if the item should be displayed as "item 1 of 10".
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackQueueIndex NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The total number of items in the application's playback queue.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackQueueCount NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The chapter currently being played. Note that this is zero-based.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyChapterNumber NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The total number of chapters in the now playing item.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyChapterCount NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// A list of available language option groups in the now playing item
// Only one language option in a given group can be played at once.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyAvailableLanguageOptions NS_AVAILABLE_IOS(9_0); // NSArrayRef of MPNowPlayingInfoLanguageOptionGroup

// A list of currently active language options in the now playing item.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyCurrentLanguageOptions NS_AVAILABLE_IOS(9_0); // NSArray of MPNowPlayingInfoLanguageOption


NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaItem.h
//
//  MPMediaItem.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaEntity.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, MPMediaItemArtwork;

typedef NS_OPTIONS(NSUInteger, MPMediaType) {
    // audio
    MPMediaTypeMusic                                   = 1 << 0,
    MPMediaTypePodcast                                 = 1 << 1,
    MPMediaTypeAudioBook                               = 1 << 2,
    MPMediaTypeAudioITunesU NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 3,
    MPMediaTypeAnyAudio                                = 0x00ff,
    
    // video (available in iOS 5.0)
    MPMediaTypeMovie        NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 8,
    MPMediaTypeTVShow       NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 9,
    MPMediaTypeVideoPodcast NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 10,
    MPMediaTypeMusicVideo   NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 11,
    MPMediaTypeVideoITunesU NS_ENUM_AVAILABLE_IOS(5_0) = 1 << 12,
    MPMediaTypeHomeVideo    NS_ENUM_AVAILABLE_IOS(7_0) = 1 << 13,
    MPMediaTypeAnyVideo     NS_ENUM_AVAILABLE_IOS(5_0) = 0xff00,
    
    MPMediaTypeAny                                     = ~0UL
} NS_ENUM_AVAILABLE_IOS(3_0);

// An MPMediaItem represents a single piece of media in an MPMediaLibrary.
// Media items have a unique identifier which persists across application launches.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaItem : MPMediaEntity

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaItemPropertyPersistentID NS_AVAILABLE_IOS(4_2);               // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID NS_AVAILABLE_IOS(5_0);

MP_EXTERN NSString * const MPMediaItemPropertyMediaType;                                        // filterable
@property (nonatomic, readonly) MPMediaType mediaType NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyTitle;                                            // filterable
@property (nonatomic, readonly, nullable) NSString *title NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTitle;                                       // filterable
@property (nonatomic, readonly, nullable) NSString *albumTitle NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumPersistentID NS_AVAILABLE_IOS(4_2);          // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtist;                                           // filterable
@property (nonatomic, readonly, nullable) NSString *artist NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtistPersistentID NS_AVAILABLE_IOS(4_2);         // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID artistPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtist;                                      // filterable
@property (nonatomic, readonly, nullable) NSString *albumArtist NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtistPersistentID NS_AVAILABLE_IOS(4_2);    // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumArtistPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyGenre;                                            // filterable
@property (nonatomic, readonly, nullable) NSString *genre NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyGenrePersistentID NS_AVAILABLE_IOS(4_2);          // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID genrePersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyComposer;                                         // filterable
@property (nonatomic, readonly, nullable) NSString *composer NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyComposerPersistentID NS_AVAILABLE_IOS(4_2);       // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID composerPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyPlaybackDuration;
@property (nonatomic, readonly) NSTimeInterval playbackDuration NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackNumber;
@property (nonatomic, readonly) NSUInteger albumTrackNumber NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackCount;
@property (nonatomic, readonly) NSUInteger albumTrackCount NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyDiscNumber;
@property (nonatomic, readonly) NSUInteger discNumber NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyDiscCount;
@property (nonatomic, readonly) NSUInteger discCount NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtwork;
@property (nonatomic, readonly, nullable) MPMediaItemArtwork *artwork NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyLyrics;
@property (nonatomic, readonly, nullable) NSString *lyrics NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyIsCompilation;                                    // filterable
@property (nonatomic, readonly, getter = isCompilation) BOOL compilation NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyReleaseDate NS_AVAILABLE_IOS(4_0);
@property (nonatomic, readonly, nullable) NSDate *releaseDate NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyBeatsPerMinute NS_AVAILABLE_IOS(4_0);
@property (nonatomic, readonly) NSUInteger beatsPerMinute NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyComments NS_AVAILABLE_IOS(4_0);
@property (nonatomic, readonly, nullable) NSString *comments NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyAssetURL NS_AVAILABLE_IOS(4_0);
@property (nonatomic, readonly, nullable) NSURL *assetURL NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyIsCloudItem NS_AVAILABLE_IOS(6_0);                // filterable
@property (nonatomic, readonly, getter = isCloudItem) BOOL cloudItem NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyPodcastTitle;                                     // filterable
@property (nonatomic, readonly, nullable) NSString *podcastTitle NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyPodcastPersistentID NS_AVAILABLE_IOS(4_2);        // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID podcastPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyPlayCount;                                        // filterable
@property (nonatomic, readonly) NSUInteger playCount NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertySkipCount;
@property (nonatomic, readonly) NSUInteger skipCount NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyRating;
@property (nonatomic, readonly) NSUInteger rating NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyLastPlayedDate;
@property (nonatomic, readonly, nullable) NSDate *lastPlayedDate NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyUserGrouping NS_AVAILABLE_IOS(4_0);
@property (nonatomic, readonly, nullable) NSString *userGrouping NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyBookmarkTime NS_AVAILABLE_IOS(6_0);
@property (nonatomic, readonly) NSTimeInterval bookmarkTime NS_AVAILABLE_IOS(7_0);

@end

//-----------------------------------------------------

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaItemArtwork : NSObject

// Initializes an MPMediaItemArtwork instance with the given full-size image.
// The crop rect of the image is assumed to be equal to the bounds of the 
// image as defined by the image's size in points, i.e. tightly cropped.
- (instancetype)initWithImage:(UIImage *)image NS_DESIGNATED_INITIALIZER NS_AVAILABLE_IOS(5_0);

// Returns the artwork image for an item at a given size (in points).
- (nullable UIImage *)imageWithSize:(CGSize)size;

@property (nonatomic, readonly) CGRect bounds; // The bounds of the full size image (in points).
@property (nonatomic, readonly) CGRect imageCropRect; // The actual content area of the artwork, in the bounds of the full size image (in points).

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaQuery.h
//
//  MPMediaQuery.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaPredicate;
@class MPMediaQuerySection;

typedef NS_ENUM(NSInteger, MPMediaGrouping) {
    MPMediaGroupingTitle,
    MPMediaGroupingAlbum,
    MPMediaGroupingArtist,
    MPMediaGroupingAlbumArtist,
    MPMediaGroupingComposer,
    MPMediaGroupingGenre,
    MPMediaGroupingPlaylist,
    MPMediaGroupingPodcastTitle
} NS_ENUM_AVAILABLE_IOS(3_0);

// MPMediaQuery represents a collection of items or playlists determined by a chain of MPMediaPredicate objects.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaQuery : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithFilterPredicates:(nullable NSSet<MPMediaPredicate *> *)filterPredicates NS_DESIGNATED_INITIALIZER;
@property (nonatomic, strong, nullable) NSSet<MPMediaPredicate *> *filterPredicates;

- (void)addFilterPredicate:(MPMediaPredicate *)predicate;
- (void)removeFilterPredicate:(MPMediaPredicate *)predicate;

// Returns an array of MPMediaItems matching the query filter predicates.
// If no items match this method returns an empty array, otherwise returns nil if an error prevents the items from being fetched.
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *items;

// Returns an array of MPMediaItemCollections matching the query filter predicates. The collections are grouped by the groupingType.
@property (nonatomic, readonly, nullable) NSArray<MPMediaItemCollection *> *collections;

// The property used to group collections, defaults to MPMediaGroupingTitle.
@property (nonatomic) MPMediaGrouping groupingType;

// Returns an array of MPMediaQuerySection instances representing the section grouping of the query's items or collections.
// May be nil in cases where no section grouping of the items or collections is appropriate.
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *itemSections NS_AVAILABLE_IOS(4_2);
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *collectionSections NS_AVAILABLE_IOS(4_2);

// Base queries which can be used directly or as the basis for custom queries.
// The groupingType for these queries is preset to the appropriate type for the query.
+ (MPMediaQuery *)albumsQuery;
+ (MPMediaQuery *)artistsQuery;
+ (MPMediaQuery *)songsQuery;
+ (MPMediaQuery *)playlistsQuery;
+ (MPMediaQuery *)podcastsQuery;
+ (MPMediaQuery *)audiobooksQuery;
+ (MPMediaQuery *)compilationsQuery;
+ (MPMediaQuery *)composersQuery;
+ (MPMediaQuery *)genresQuery;

@end

// ------------------------------------------------------------------------
// MPMediaPredicate is an abstract class that allows filtering media in an MPMediaQuery.
// See the concrete subclass MPMediaPropertyPredicate for filtering options.

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaPredicate : NSObject <NSSecureCoding> {}
@end

// ------------------------------------------------------------------------
// MPMediaPropertyPredicate allows filtering based on a specific property value of an item or collection.
// See MPMediaItem.h and MPMediaPlaylist.h for a list of properties.

typedef NS_ENUM(NSInteger, MPMediaPredicateComparison) {
    MPMediaPredicateComparisonEqualTo,
    MPMediaPredicateComparisonContains
} NS_ENUM_AVAILABLE_IOS(3_0);

MP_EXTERN_CLASS_AVAILABLE(3_0)

@interface MPMediaPropertyPredicate : MPMediaPredicate

+ (MPMediaPropertyPredicate *)predicateWithValue:(nullable id)value forProperty:(NSString *)property; // comparisonType is MPMediaPredicateComparisonEqualTo
+ (MPMediaPropertyPredicate *)predicateWithValue:(nullable id)value forProperty:(NSString *)property comparisonType:(MPMediaPredicateComparison)comparisonType;

@property (nonatomic, readonly, copy) NSString *property;
@property (nonatomic, readonly, copy, nullable) id value;
@property (nonatomic, readonly) MPMediaPredicateComparison comparisonType;

@end

// ------------------------------------------------------------------------
// Convenience methods to determine item properties corresponding to a given grouping type.

@interface MPMediaItem (MPMediaQueryAdditions)

// Returns the item property for a given grouping type.
// For example, [MPMediaItem persistentIDPropertyForGroupingType:MPMediaGroupingAlbum] returns MPMediaItemPropertyAlbumPersistentID.
+ (NSString *)persistentIDPropertyForGroupingType:(MPMediaGrouping)groupingType NS_AVAILABLE_IOS(4_2);

// Returns the item property to determine a title for a given grouping type.
// For example, [MPMediaItem titlePropertyForGroupingType:MPMediaGroupingAlbum] returns MPMediaItemPropertyAlbumTitle.
// Note that distinct collections will not necessarily have unique titles, e.g. an album may exist with the title "Greatest Hits" for multiple artists.
+ (NSString *)titlePropertyForGroupingType:(MPMediaGrouping)groupingType NS_AVAILABLE_IOS(4_2);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMoviePlayerViewController.h
//
//  MPMoviePlayerViewController.h
//  MediaPlayer
//
//  Copyright 2009-2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <UIKit/UIViewController.h>

@class MPMoviePlayerController;

MP_EXTERN_CLASS_AVAILABLE(3_2)
NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.")

@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.");
- (void)dismissMoviePlayerViewControllerAnimated NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.");

@end
