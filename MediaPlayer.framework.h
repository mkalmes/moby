// ==========  MediaPlayer.framework/Headers/MPNowPlayingInfoLanguageOption.h
//
//  MPNowPlayingInfoLanguageOption.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
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
MP_EXTERN NSString * const MPLanguageOptionCharacteristicIsMainProgramContent MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicIsAuxiliaryContent MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicContainsOnlyForcedSubtitles MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicTranscribesSpokenDialog MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicDescribesMusicAndSound MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicEasyToRead MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicDescribesVideo MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicLanguageTranslation MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicDubbedTranslation MP_API(ios(9.0), macos(10.12.2), watchos(5.0));
MP_EXTERN NSString * const MPLanguageOptionCharacteristicVoiceOverTranslation MP_API(ios(9.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSUInteger, MPNowPlayingInfoLanguageOptionType) {
    MPNowPlayingInfoLanguageOptionTypeAudible,
    MPNowPlayingInfoLanguageOptionTypeLegible,
} MP_API(ios(9.0), macos(10.12.2), watchos(5.0));

// -----------------------------------------------------------------------------

/// Represents a single language option option.
MP_API(ios(9.0), tvos(9.0), macos(10.12.2), watchos(5.0))
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

/// Represents a special case that is used to
/// represent the best audible language option based on system preferences.
/// See AVPlayerItem-selectMediaOptionAutomaticallyInMediaSelectionGroup
- (BOOL)isAutomaticAudibleLanguageOption;

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
MP_API(ios(9.0), tvos(9.0), macos(10.12.2), watchos(5.0))
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
// ==========  MediaPlayer.framework/Headers/NSUserActivity+MediaPlayerAdditions.h
//
//  NSUserActivity+MediaPlayerAdditions.h
//  MediaPlayer
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (MediaPlayerAdditions)

/// A unique identifier relative to the app's media content catalog for the displayed media item.
@property (nonatomic, copy, nullable) NSString *externalMediaContentIdentifier MP_API(ios(10.1), tvos(10.0.1)) MP_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPContentItem.h
//
//  MPContentItem.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItemArtwork;

/// MPContentItem represents high-level metadata for a particular media item for
/// representation outside the client application. Examples of media items that a
/// developer might want to represent include song files, streaming audio URLs,
/// or radio stations.
MP_API(ios(7.1), tvos(7.1), macos(10.12.2))
MP_PROHIBITED(watchos)
@interface MPContentItem : NSObject

/// Designated initializer. A unique identifier is required to identify the item
/// for later use.
- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

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

/// Represents the current playback progress of the item.
/// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
/// Default is -1.0 (no progress indicator shown)
@property (nonatomic, assign) float playbackProgress;

/// Represents whether this content item is streaming content, i.e. from the cloud
/// where the content is not stored locally.
@property (nonatomic, assign, getter = isStreamingContent) BOOL streamingContent MP_API(ios(10.0), tvos(10.0), macos(10.12.2));

/// Represents whether this content item is explicit content
@property (nonatomic, assign, getter = isExplicitContent) BOOL explicitContent MP_API(ios(10.0), tvos(10.0), macos(10.12.2));

/// Represents whether the content item is a container that may contain other
/// content items, e.g. an album or a playlist.
@property (nonatomic, assign, getter = isContainer) BOOL container;

/// Represents whether the content item is actionable from a playback
/// perspective. Albums are playable, for example, because selecting an album
/// for playback means the app should play each song in the album in order. An
/// example of a content item that may not be playable is a genre, since an app
/// experience typically doesn't involve selecting an entire genre for playback.
@property (nonatomic, assign, getter = isPlayable) BOOL playable;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPPlayableContentManager.h
//
//  MPPlayableContentManager.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/// MPPlayableContentManager is a class that manages the interactions between a
/// media application and an external media player interface. The application
/// provides the content manager with a data source, which allows the media player
/// to browse the media content offered by the application, as well as a delegate,
/// which allows the media player to relay non-media remote playback commands to the application.
MP_API(ios(7.1))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPPlayableContentManager : NSObject

@property (nonatomic, weak, nullable) id<MPPlayableContentDataSource> dataSource;
@property (nonatomic, weak, nullable) id<MPPlayableContentDelegate>   delegate;
@property (nonatomic, readonly) MPPlayableContentManagerContext *context MP_API(ios(8.4));

/// Tells the content manager which MPContentItems are currently playing based on their identifiers.
@property (nonatomic, copy) NSArray<NSString *> *nowPlayingIdentifiers MP_API(ios(10.0));

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
//  Copyright 2008-2019 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define _MP_EXTERN extern "C"
#else
#define _MP_EXTERN extern
#endif

#define MP_EXTERN _MP_EXTERN __attribute__((visibility("default")))

#define MP_API(...) __API_AVAILABLE(__VA_ARGS__)
#define MP_DEPRECATED(...) __API_DEPRECATED(__VA_ARGS__)
#define MP_UNAVAILABLE(...) __API_UNAVAILABLE(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT(...) __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)

#pragma mark - Prohibited

#define __MP_PROHIBITED_PLATFORM_macos macos,unavailable
#define __MP_PROHIBITED_PLATFORM_macosx macosx,unavailable
#define __MP_PROHIBITED_PLATFORM_ios ios,unavailable
#define __MP_PROHIBITED_PLATFORM_watchos watchos,unavailable
#define __MP_PROHIBITED_PLATFORM_tvos tvos,unavailable


#if __has_include(<AvailabilityProhibitedInternal.h>)
#define __MP_P(x)
#else
#define __MP_P(x) __attribute__((availability(__MP_PROHIBITED_PLATFORM_##x)))
#endif

#define __MP_PROHIBITED1(x) __MP_P(x)
#define __MP_PROHIBITED2(x,y) __MP_P(x) __MP_P(y)
#define __MP_PROHIBITED3(x,y,z) __MP_PROHIBITED2(x,y) __MP_P(z)
#define __MP_PROHIBITED4(x,y,z,t) __MP_PROHIBITED3(x,y) __MP_P(b)
#define __MP_PROHIBITED_GET_MACRO(_1,_2,_3,_4,NAME,...) NAME

#define MP_PROHIBITED(...) __MP_PROHIBITED_GET_MACRO(__VA_ARGS__,__MP_PROHIBITED4,__MP_PROHIBITED3,__MP_PROHIBITED2,__MP_PROHIBITED1)(__VA_ARGS__)

#define MP_HAS_UIVIEW               __has_include(<UIKit/UIView.h>)
#define MP_HAS_AVMEDIASELECTION     __has_include(<AVFoundation/AVMediaSelection.h>)
// ==========  MediaPlayer.framework/Headers/MPPlayableContentDelegate.h
//
//  MPPlayableContentDelegate.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPPlayableContentManager, MPContentItem, MPPlayableContentManagerContext;

/// The MPPlayableContentDelegate is a protocol that allows for external media
/// players to send playback commands to an application. For instance,
/// the user could browse the application's media content (provided by the
/// MPPlayableContentDataSource) and selects a content item to play. If the media
/// player decides that it wants to play the item, it will ask the application's
/// content delegate to initiate playback.
MP_API(ios(7.1))
MP_PROHIBITED(tvos, macos, watchos)
@protocol MPPlayableContentDelegate <NSObject>
@optional

/// This method is called when a media player interface wants to play a requested
/// content item. The application should call the completion handler with an
/// appropriate error if there was an error beginning playback for the item.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initiatePlaybackOfContentItemAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_API(ios(7.1))
    MP_PROHIBITED(tvos, macos, watchos);


/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue but not start playback until a Play command is
/// received or if the playable content manager requests to play something else.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithCompletionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_DEPRECATED("Use Intents framework for initiating playback queues.", ios(9.0, 9.3))
    MP_PROHIBITED(tvos, macos, watchos);

/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue based on the provided content items and
/// prepare it for playback, but not start playback until a Play command is
/// received or if the playable content manager requests to play something else.
/// A nil contentItems array means that the app should prepare its queue with
/// anything it deems appropriate.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithContentItems:(nullable NSArray *)contentItems completionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_DEPRECATED("Use Intents framework for initiating playback queues.", ios(9.3, 12.0))
    MP_PROHIBITED(tvos, macos, watchos);

/// This method is called when the content server notifies the manager that the current context has changed.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager didUpdateContext:(MPPlayableContentManagerContext *)context
    MP_API(ios(8.4))
    MP_PROHIBITED(tvos, macos, watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MediaPlayer.h
//
//  MediaPlayer.h
//  MediaPlayer
//
//  Copyright 2008-2019 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <TargetConditionals.h>

#if !TARGET_OS_OSX
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaLibrary.h>
#import <MediaPlayer/MPMediaPickerController.h>
#import <MediaPlayer/MPMediaPlaylist.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaQuerySection.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import <MediaPlayer/MPMoviePlayerViewController.h>
#import <MediaPlayer/MPMusicPlayerApplicationController.h>
#import <MediaPlayer/MPMusicPlayerController.h>
#import <MediaPlayer/MPMusicPlayerQueueDescriptor.h>
#import <MediaPlayer/MPVolumeSettings.h>
#import <MediaPlayer/MPVolumeView.h>
#import <MediaPlayer/NSUserActivity+MediaPlayerAdditions.h>
#endif

#import <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>
#import <MediaPlayer/MPContentItem.h>
#import <MediaPlayer/MPError.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPNowPlayingInfoCenter.h>
#import <MediaPlayer/MPNowPlayingInfoLanguageOption.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>
#import <MediaPlayer/MPPlayableContentManager.h>
#import <MediaPlayer/MPPlayableContentManagerContext.h>
#import <MediaPlayer/MPRemoteCommand.h>
#import <MediaPlayer/MPRemoteCommandCenter.h>
#import <MediaPlayer/MPRemoteCommandEvent.h>
#import <MediaPlayer/MPRemoteControlTypes.h>
// ==========  MediaPlayer.framework/Headers/MPPlayableContentDataSource.h
//
//  MPPlayableContentDataSource.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPContentItem;

/// MPPlayableContentDataSource is a protocol that application objects conform to
/// if they want to support external media players, such as vehicle head units.
/// Data sources are responsible for providing metadata about your media to these
/// systems in a meaningful way, so that features like user interfaces and play
/// queues can be setup automatically.
MP_API(ios(7.1))
MP_PROHIBITED(tvos, macos, watchos)
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

/// Provides a content item for the provided identifier.
/// Provide nil if there is no content item corresponding to the identifier.
/// Provide an error if there is an error that will not allow content items
/// to be retrieved.
/// Client applications should always call the completion handler after loading
/// has finished, if this method is implemented.
- (void)contentItemForIdentifier:(NSString *)identifier completionHandler:(void(^)(MPContentItem *__nullable, NSError * __nullable))completionHandler MP_API(ios(10.0)) MP_PROHIBITED(tvos, macos, watchos);

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
// ==========  MediaPlayer.framework/Headers/MPError.h
//
//  MPError.h
//  MediaPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

MP_EXTERN NSString * const MPErrorDomain MP_API(ios(9.3), macos(10.12.2)) MP_PROHIBITED(watchos);

// error codes for the MPErrorDomain
typedef NS_ENUM(NSInteger, MPErrorCode) {
    MPErrorUnknown,
    MPErrorPermissionDenied,                        // the user has not granted permission for this request.
    MPErrorCloudServiceCapabilityMissing,           // the user has not enabled this capability
    MPErrorNetworkConnectionFailed,                 // the device could not connect to the network
    MPErrorNotFound,                                // the id could not be found in the current storefront
    MPErrorNotSupported,                            // the request is not supported (ex: trying to add items to a smart playlist)
    MPErrorCancelled MP_API(ios(10.1)),             // the request was cancelled before it could complete
    MPErrorRequestTimedOut MP_API(ios(10.3)),
} MP_API(ios(9.3), macos(10.14.2)) MP_PROHIBITED(watchos);

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMusicPlayerQueueDescriptor.h
//
//  MPMusicPlayerQueueDescriptor.h
//  MediaPlayerFramework
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem, MPMediaItemCollection, MPMediaQuery;

MP_API(ios(10.1))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerQueueDescriptor : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
@end

MP_API(ios(10.1))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerMediaItemQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithQuery:(MPMediaQuery *)query;
- (instancetype)initWithItemCollection:(MPMediaItemCollection *)itemCollection;

@property (nonatomic, readonly, copy) MPMediaQuery *query;
@property (nonatomic, readonly, strong) MPMediaItemCollection *itemCollection;
@property (nonatomic, nullable, strong) MPMediaItem *startItem;

- (void)setStartTime:(NSTimeInterval)startTime forItem:(MPMediaItem *)mediaItem;
- (void)setEndTime:(NSTimeInterval)endTime forItem:(MPMediaItem *)mediaItem;

@end

MP_API(ios(10.1))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerStoreQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithStoreIDs:(NSArray<NSString *> *)storeIDs;

@property (nonatomic, nullable, copy) NSArray<NSString *> *storeIDs;
@property (nonatomic, nullable, copy) NSString *startItemID;

- (void)setStartTime:(NSTimeInterval)startTime forItemWithStoreID:(NSString *)storeID;
- (void)setEndTime:(NSTimeInterval)endTime forItemWithStoreID:(NSString *)storeID;

@end

MP_API(ios(11.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerPlayParameters : NSObject

- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *dictionary;

@end

MP_API(ios(11.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerPlayParametersQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithPlayParametersQueue:(NSArray<MPMusicPlayerPlayParameters *> *)playParametersQueue;

@property (nonatomic, copy) NSArray<MPMusicPlayerPlayParameters *> *playParametersQueue;
@property (nonatomic, nullable, strong) MPMusicPlayerPlayParameters *startItemPlayParameters;

- (void)setStartTime:(NSTimeInterval)startTime forItemWithPlayParameters:(MPMusicPlayerPlayParameters *)playParameters;
- (void)setEndTime:(NSTimeInterval)endTime forItemWithPlayParameters:(MPMusicPlayerPlayParameters *)playParameters;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPRemoteCommand.h
//
//  MPRemoteCommand.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPRemoteControlTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommandEvent;

typedef NS_ENUM(NSInteger, MPRemoteCommandHandlerStatus) {
    /// There was no error executing the requested command.
    MPRemoteCommandHandlerStatusSuccess = 0,
    
    /// The command could not be executed because the requested content does not
    /// exist in the current application state.
    MPRemoteCommandHandlerStatusNoSuchContent = 100,
    
    /// The command could not be executed because there is no now playing item
    /// available that is required for this command. As an example, an
    /// application would return this error code if an "enable language option"
    /// command is received, but nothing is currently playing.
    MPRemoteCommandHandlerStatusNoActionableNowPlayingItem MP_API(ios(9.1), macos(10.12.2)) = 110,
    
    /// The command could not be executed because a device required
    /// is not available. For instance, if headphones are required, or if a watch
    /// app realizes that it needs the companion to fulfull a request.
    MPRemoteCommandHandlerStatusDeviceNotFound MP_API(ios(11.0), macos(10.13)) = 120,
    
    /// The command could not be executed for another reason.
    MPRemoteCommandHandlerStatusCommandFailed = 200
} MP_API(ios(7.1), macos(10.12.2), watchos(5.0));

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
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

/// Private constructor.
- (instancetype)init NS_UNAVAILABLE;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPSkipIntervalCommand : MPRemoteCommand

/// An array of NSNumbers (NSTimeIntervals) that contain preferred skip intervals.
@property (nonatomic, copy) NSArray<NSNumber *> *preferredIntervals;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
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
@property (nonatomic, copy) NSString *localizedShortTitle MP_API(ios(8.0));

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRatingCommand : MPRemoteCommand

/// Minimum rating for the command.
@property (nonatomic, assign) float minimumRating;

/// Maximum rating for the command.
@property (nonatomic, assign) float maximumRating;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackRateCommand : MPRemoteCommand

/// An array of NSNumbers (floats) that contain supported playback rates that
/// the command can send.
@property (nonatomic, copy) NSArray<NSNumber *> *supportedPlaybackRates;

@end

/// Command for changing the current playback position in a now playing item.
/// Sends out MPChangePlaybackPositionCommandEvents.
MP_API(ios(9.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackPositionCommand : MPRemoteCommand

@end

/// Command for changing the current shuffle mode to use during playback. To
/// update the system's current representation of your app's shuffle mode, set
/// the currentShuffleType property on this command to the proper shuffle type
/// value.
MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeShuffleModeCommand : MPRemoteCommand

/// The app's current shuffle type.
@property (nonatomic, assign) MPShuffleType currentShuffleType;

@end

/// Command for changing the current repeat mode to use during playback. To
/// update the system's current representation of your app's repeat mode, set
/// the currentRepeatType property on this command to the proper repeat type
/// value.
MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeRepeatModeCommand : MPRemoteCommand

/// The app's current repeat mode.
@property (nonatomic, assign) MPRepeatType currentRepeatType;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMoviePlayerController.h
//
//  MPMoviePlayerController.h
//  MediaPlayer
//
//  Copyright 2008-2015 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#if MP_HAS_UIVIEW
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
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(2.0, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMoviePlaybackState) {
    MPMoviePlaybackStateStopped,
    MPMoviePlaybackStatePlaying,
    MPMoviePlaybackStatePaused,
    MPMoviePlaybackStateInterrupted,
    MPMoviePlaybackStateSeekingForward,
    MPMoviePlaybackStateSeekingBackward
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_OPTIONS(NSUInteger, MPMovieLoadState) {
    MPMovieLoadStateUnknown        = 0,
    MPMovieLoadStatePlayable       = 1 << 0,
    MPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    MPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMovieRepeatMode) {
    MPMovieRepeatModeNone,
    MPMovieRepeatModeOne
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMovieControlStyle) {
    MPMovieControlStyleNone,       // No controls
    MPMovieControlStyleEmbedded,   // Controls for an embedded view
    MPMovieControlStyleFullscreen, // Controls for fullscreen playback
    
    MPMovieControlStyleDefault = MPMovieControlStyleEmbedded
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMovieFinishReason) {
    MPMovieFinishReasonPlaybackEnded,
    MPMovieFinishReasonPlaybackError,
    MPMovieFinishReasonUserExited
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// -----------------------------------------------------------------------------
// Movie Property Types

typedef NS_OPTIONS(NSUInteger, MPMovieMediaTypeMask) {
    MPMovieMediaTypeMaskNone  = 0,
    MPMovieMediaTypeMaskVideo = 1 << 0,
    MPMovieMediaTypeMaskAudio = 1 << 1
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMovieSourceType) {
    MPMovieSourceTypeUnknown,
    MPMovieSourceTypeFile,     // Local or progressively downloaded network content
    MPMovieSourceTypeStreaming // Live or on-demand streaming content
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// -----------------------------------------------------------------------------
// Movie Player
// 
// See MPMediaPlayback.h for the playback methods.

MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(2.0, 9.0))
MP_PROHIBITED(tvos, watchos)
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
@property (nonatomic, readonly) BOOL readyForDisplay MP_API(ios(6.0));

// The types of media in the movie, or MPMovieMediaTypeNone if not known.
@property (nonatomic, readonly) MPMovieMediaTypeMask movieMediaTypes;

// The playback type of the movie. Defaults to MPMovieSourceTypeUnknown.
// Specifying a playback type before playing the movie can result in faster load times.
@property (nonatomic) MPMovieSourceType movieSourceType;

// The duration of the movie, or 0.0 if not known.
@property (nonatomic, readonly) NSTimeInterval duration;

// The currently playable duration of the movie, for progressively downloaded network content.
@property (nonatomic, readonly) NSTimeInterval playableDuration;

// The natural size of the movie, or CGSizeZero if not known/applicable.
@property (nonatomic, readonly) CGSize naturalSize;

// The start time of movie playback. Defaults to NaN, indicating the natural start time of the movie.
@property (nonatomic) NSTimeInterval initialPlaybackTime;

// The end time of movie playback. Defaults to NaN, which indicates natural end time of the movie.
@property (nonatomic) NSTimeInterval endPlaybackTime;

// Indicates whether the movie player allows AirPlay video playback. Defaults to YES on iOS 5.0 and later.
@property (nonatomic) BOOL allowsAirPlay;

// Indicates whether the movie player is currently playing video via AirPlay.
@property (nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive;

@end

// -----------------------------------------------------------------------------
// Movie Player Notifications

// Posted when the scaling mode changes.
MP_EXTERN NSString * const MPMoviePlayerScalingModeDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(2.0, 9.0)) MP_PROHIBITED(tvos, watchos);

// Posted when movie playback ends or a user exits playback.
MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(2.0, 9.0)) MP_PROHIBITED(tvos, watchos);

MP_EXTERN NSString * const MPMoviePlayerPlaybackDidFinishReasonUserInfoKey MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // NSNumber (MPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSString * const MPMoviePlayerPlaybackStateDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// Posted when the network load state changes.
MP_EXTERN NSString * const MPMoviePlayerLoadStateDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// Posted when the currently playing movie changes.
MP_EXTERN NSString * const MPMoviePlayerNowPlayingMovieDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// Posted when the movie player enters or exits fullscreen mode.
MP_EXTERN NSString * const MPMoviePlayerWillEnterFullscreenNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerDidEnterFullscreenNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerWillExitFullscreenNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerDidExitFullscreenNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationDurationUserInfoKey MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // NSNumber of double (NSTimeInterval)
MP_EXTERN NSString * const MPMoviePlayerFullscreenAnimationCurveUserInfoKey MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);     // NSNumber of NSUInteger (UIViewAnimationCurve)

// Posted when the movie player begins or ends playing video via AirPlay.
MP_EXTERN NSString * const MPMoviePlayerIsAirPlayVideoActiveDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(5.0, 9.0)) MP_PROHIBITED(tvos, watchos);

// Posted when the ready for display state changes.
MP_EXTERN NSString * const MPMoviePlayerReadyForDisplayDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(6.0, 9.0)) MP_PROHIBITED(tvos, watchos);

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
MP_EXTERN NSString * const MPMovieMediaTypesAvailableNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMovieSourceTypeAvailableNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // Posted if the movieSourceType is MPMovieSourceTypeUnknown when preparing for playback.
MP_EXTERN NSString * const MPMovieDurationAvailableNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMovieNaturalSizeAvailableNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, MPMovieTimeOption) {
    MPMovieTimeOptionNearestKeyFrame,
    MPMovieTimeOptionExact
} MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

@interface MPMoviePlayerController (MPMoviePlayerThumbnailGeneration)

// Returns a thumbnail at the given time.
// Deprecated.  Use -requestThumbnailImagesAtTimes:timeOption: / MPMoviePlayerThumbnailImageRequestDidFinishNotification instead.
- (UIImage *)thumbnailImageAtTime:(NSTimeInterval)playbackTime timeOption:(MPMovieTimeOption)option MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// Asynchronously request thumbnails for one or more times, provided as an array of NSNumbers (double).
// Posts MPMoviePlayerThumbnailImageRequestDidFinishNotification on completion.
- (void)requestThumbnailImagesAtTimes:(NSArray *)playbackTimes timeOption:(MPMovieTimeOption)option MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

// Cancels all pending asynchronous thumbnail requests.
- (void)cancelAllThumbnailImageRequests MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

@end

// Posted when each thumbnail image request is completed.
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageRequestDidFinishNotification MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerThumbnailImageKey MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // UIImage, may be nil if an error occurred.
MP_EXTERN NSString * const MPMoviePlayerThumbnailTimeKey MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // NSNumber (double)
MP_EXTERN NSString * const MPMoviePlayerThumbnailErrorKey MP_DEPRECATED("Use AVFoundation.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos); // NSError

// -----------------------------------------------------------------------------
// Timed Metadata

@interface MPMoviePlayerController (MPMoviePlayerTimedMetadataAdditions)

// Returns an array of the most recent MPTimedMetadata objects provided by the media stream.
@property (nonatomic, readonly) NSArray *timedMetadata MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);

@end

MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0))
MP_PROHIBITED(tvos, watchos)
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
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUpdatedNotification MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataUserInfoKey MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);       // NSDictionary of the most recent MPTimedMetadata objects.

// Additional dictionary keys for use with the 'allMetadata' property. All keys are optional.
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyName MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyInfo MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);           // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyMIMEType MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyDataType MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);       // NSString
MP_EXTERN NSString * const MPMoviePlayerTimedMetadataKeyLanguageCode MP_DEPRECATED("Use AVFoundation.", ios(4.0, 9.0)) MP_PROHIBITED(tvos, watchos);   // NSString (ISO 639-2)

// -----------------------------------------------------------------------------

@interface MPMoviePlayerController (MPMovieLogging)

// Returns an object that represents a snapshot of the network access log. Can be nil.
@property (nonatomic, readonly) MPMovieAccessLog *accessLog MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0)) MP_PROHIBITED(tvos, watchos);

// Returns an object that represents a snapshot of the error log. Can be nil.
@property (nonatomic, readonly) MPMovieErrorLog *errorLog MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0)) MP_PROHIBITED(tvos, watchos);

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLog accumulates key metrics about network playback and presents them as a collection of MPMovieAccessLogEvent instances.
// Each MPMovieAccessLogEvent instance collates the data that relates to each uninterrupted period of playback.

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_PROHIBITED(tvos, watchos)
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

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_PROHIBITED(tvos, watchos)
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

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_PROHIBITED(tvos, watchos)
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

MP_DEPRECATED("Use AVFoundation.", ios(4.3, 9.0))
MP_PROHIBITED(tvos, watchos)
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
@property (nonatomic) BOOL useApplicationAudioSession MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(6.0, 9.0)) MP_PROHIBITED(tvos, watchos);

@end
#endif
// ==========  MediaPlayer.framework/Headers/MPMusicPlayerApplicationController.h
//
//  MPMusicPlayerApplicationController.h
//  MediaPlayer
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMusicPlayerController.h>

NS_ASSUME_NONNULL_BEGIN

MP_API(ios(10.3))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerControllerQueue : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, copy, readonly) NSArray<MPMediaItem *> *items;

@end

MP_API(ios(10.3))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerControllerMutableQueue : MPMusicPlayerControllerQueue

- (void)insertQueueDescriptor:(MPMusicPlayerQueueDescriptor *)queueDescriptor afterItem:(nullable MPMediaItem *)afterItem;
- (void)removeItem:(MPMediaItem *)item;

@end

MP_API(ios(10.3))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerApplicationController : MPMusicPlayerController

- (void)performQueueTransaction:(void (^)(MPMusicPlayerControllerMutableQueue *queue))queueTransaction completionHandler:(void (^)(MPMusicPlayerControllerQueue *queue, NSError *_Nullable error))completionHandler;

@end

// Posted when the queue changes
MP_EXTERN NSString * const MPMusicPlayerControllerQueueDidChangeNotification MP_PROHIBITED(tvos, watchos);

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPRemoteControlTypes.h
//
//  MPRemoteControlTypes.h
//  MediaPlayerFramework
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MPShuffleType) {
    MPShuffleTypeOff,           /// Nothing is shuffled during playback.
    MPShuffleTypeItems,         /// Individual items are shuffled during playback.
    MPShuffleTypeCollections,   /// Collections (e.g. albums) are shuffled during playback.
} MP_API(ios(3.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSInteger, MPRepeatType) {
    MPRepeatTypeOff,    /// Nothing is repeated during playback.
    MPRepeatTypeOne,    /// Repeat a single item indefinitely.
    MPRepeatTypeAll,    /// Repeat the current container or playlist indefinitely.
} MP_API(ios(3.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSInteger, MPChangeLanguageOptionSetting) {
    MPChangeLanguageOptionSettingNone, /// No Language Option Change
    MPChangeLanguageOptionSettingNowPlayingItemOnly, /// The Language Option change applies only the the now playing item
    MPChangeLanguageOptionSettingPermanent /// The Language Option change should apply to all future playback
} MP_API(ios(9.3), macos(10.12.2), watchos(5.0));
// ==========  MediaPlayer.framework/Headers/MPMusicPlayerController.h
//
//  MPMusicPlayerController.h
//  MediaPlayer
//
//  Copyright © 2008-2017 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaPlayback.h>
#import <MediaPlayer/MPMusicPlayerQueueDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMusicPlayerApplicationController;

typedef NS_ENUM(NSInteger, MPMusicPlaybackState) {
    MPMusicPlaybackStateStopped,
    MPMusicPlaybackStatePlaying,
    MPMusicPlaybackStatePaused,
    MPMusicPlaybackStateInterrupted,
    MPMusicPlaybackStateSeekingForward,
    MPMusicPlaybackStateSeekingBackward
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMusicRepeatMode) {
    MPMusicRepeatModeDefault, // the user's preference for repeat mode
    MPMusicRepeatModeNone,
    MPMusicRepeatModeOne,
    MPMusicRepeatModeAll
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, watchos);

typedef NS_ENUM(NSInteger, MPMusicShuffleMode) {
    MPMusicShuffleModeDefault, // the user's preference for shuffle mode
    MPMusicShuffleModeOff,
    MPMusicShuffleModeSongs,
    MPMusicShuffleModeAlbums
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, watchos);

@protocol MPSystemMusicPlayerController <NSObject>
/// Switches to Music to play the content provided by the queue descriptor.
- (void)openToPlayQueueDescriptor:(MPMusicPlayerQueueDescriptor *)queueDescriptor MP_API(ios(11.0)) MP_PROHIBITED(tvos, watchos) NS_SWIFT_NAME(openToPlay(_:));
@end

// MPMusicPlayerController allows playback of MPMediaItems through the Music application.
// See MPMediaPlayback.h for basic playback control.
MP_API(ios(3.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMusicPlayerController : NSObject <MPMediaPlayback>

/// Playing items with applicationMusicPlayer does not affect Music's playback state.
@property (class, readonly) MPMusicPlayerController *applicationMusicPlayer;

/// Similar to applicationMusicPlayer, but allows direct manipulation of the queue.
@property (class, readonly) MPMusicPlayerApplicationController *applicationQueuePlayer MP_API(ios(10.3));

/// Playing media items with the systemMusicPlayer will replace the user's current Music state.
@property (class, readonly) MPMusicPlayerController<MPSystemMusicPlayerController> *systemMusicPlayer;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// Returns the current playback state of the music player
@property (nonatomic, readonly) MPMusicPlaybackState playbackState;

// Determines how music repeats after playback completes. Defaults to MPMusicRepeatModeDefault.
@property (nonatomic) MPMusicRepeatMode repeatMode;

// Determines how music is shuffled when playing. Defaults to MPMusicShuffleModeDefault.
@property (nonatomic) MPMusicShuffleMode shuffleMode;

// The current volume of playing music, in the range of 0.0 to 1.0.
// This property is deprecated -- use MPVolumeView for volume control instead.
@property (nonatomic) float volume MP_DEPRECATED("Use MPVolumeView for volume control.", ios(3.0, 7.0));

// Returns the currently playing media item, or nil if none is playing.
// Setting the nowPlayingItem to an item in the current queue will begin playback at that item.
@property (nonatomic, copy, nullable) MPMediaItem *nowPlayingItem;

// Returns the index of the now playing item in the current playback queue.
// May return NSNotFound if the index is not valid (e.g. an empty queue or an infinite playlist).
@property (nonatomic, readonly) NSUInteger indexOfNowPlayingItem MP_API(ios(5.0));

// Call -play to begin playback after setting an item queue source. Setting a query will implicitly use MPMediaGroupingTitle.
- (void)setQueueWithQuery:(MPMediaQuery *)query;
- (void)setQueueWithItemCollection:(MPMediaItemCollection *)itemCollection;
- (void)setQueueWithStoreIDs:(NSArray<NSString *> *)storeIDs MP_API(ios(9.3));
- (void)setQueueWithDescriptor:(MPMusicPlayerQueueDescriptor *)descriptor MP_API(ios(10.1));

// Inserts the contents of the queue descriptor after the now playing item
- (void)prependQueueDescriptor:(MPMusicPlayerQueueDescriptor *)descriptor MP_API(ios(10.3));

// Adds the contents of the queue descriptor to the end of the queue
- (void)appendQueueDescriptor:(MPMusicPlayerQueueDescriptor *)descriptor MP_API(ios(10.3));

// The completion handler will be called when the first item from the queue is buffered and ready to play.
// If a first item has been specified using MPMusicPlayerQueueDescriptor, the error will be non-nil if the specified item cannot be prepared for playback.
// If a first item is not specified, the error will be non-nil if an item cannot be prepared for playback.
// Errors will be in MPErrorDomain.
- (void)prepareToPlayWithCompletionHandler:(void (^)(NSError *_Nullable error))completionHandler MP_API(ios(10.1));

// Skips to the next item in the queue.
// If already at the last item, this resets the queue to the first item in a paused playback state.
- (void)skipToNextItem;

// Restarts playback at the beginning of the currently playing media item.
- (void)skipToBeginning;

// Skips to the previous item in the queue. If already at the first item, this will end playback.
- (void)skipToPreviousItem;

// These methods determine whether playback notifications will be generated.
// Calls to begin/endGeneratingPlaybackNotifications are nestable.
- (void)beginGeneratingPlaybackNotifications;
- (void)endGeneratingPlaybackNotifications;

@property (class, readonly) MPMusicPlayerController *iPodMusicPlayer MP_DEPRECATED_WITH_REPLACEMENT("systemMusicPlayer", ios(3.0, 8.0));

@end

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSNotificationName const MPMusicPlayerControllerPlaybackStateDidChangeNotification MP_PROHIBITED(tvos, watchos);

// Posted when the currently playing media item changes.
MP_EXTERN NSNotificationName const MPMusicPlayerControllerNowPlayingItemDidChangeNotification MP_PROHIBITED(tvos, watchos);

// Posted when the current volume changes.
MP_EXTERN NSNotificationName const MPMusicPlayerControllerVolumeDidChangeNotification MP_PROHIBITED(tvos, watchos);

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPlayback.h
//
//  MPMediaPlayback.h
//  MediaPlayer
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

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
MP_EXTERN NSString * const MPMediaPlaybackIsPreparedToPlayDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos);
// ==========  MediaPlayer.framework/Headers/MPMediaEntity.h
//
//  MPMediaEntity.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaLibrary;

typedef uint64_t MPMediaEntityPersistentID;

// An MPMediaEntity represents an abstract member of an MPMediaLibrary.
// Concrete subclasses are MPMediaItem and MPMediaItemCollection.

MP_API(ios(4.2))
MP_PROHIBITED(tvos, macos)
@interface MPMediaEntity : NSObject <NSSecureCoding>

// Returns YES for properties which can be used to construct MPMediaPropertyPredicates.
+ (BOOL)canFilterByProperty:(NSString *)property;

// Executes a provided block with the fetched values for the given item properties, or nil if no value is available for a property.
// In some cases, enumerating the values for multiple properties can be more efficient than fetching each individual property with -valueForProperty:.
- (void)enumerateValuesForProperties:(NSSet<NSString *> *)properties usingBlock:(void (^)(NSString *property, id value, BOOL *stop))block MP_API(ios(4.0));

// Read-only support for Objective-C subscripting syntax with MPMediaEntity property constants.
- (nullable id)objectForKeyedSubscript:(id)key MP_API(ios(8.0));

// Returns the value for the given entity property.
// MPMediaItem and MPMediaPlaylist have their own properties
- (nullable id)valueForProperty:(NSString *)property;

#pragma mark - Properties

MP_EXTERN NSString * const MPMediaEntityPropertyPersistentID MP_API(ios(4.2));        // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(7.0));

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPlaylist.h
//
//  MPMediaPlaylist.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem;

// A playlist may have any number of MPMediaPlaylistAttributes associated.
typedef NS_OPTIONS(NSUInteger, MPMediaPlaylistAttribute) {
    MPMediaPlaylistAttributeNone    = 0,
    MPMediaPlaylistAttributeOnTheGo = (1 << 0), // if set, the playlist was created on a device rather than synced from iTunes
    MPMediaPlaylistAttributeSmart   = (1 << 1),
    MPMediaPlaylistAttributeGenius  = (1 << 2)
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, macos, watchos);

// An MPMediaPlaylist is a collection of related MPMediaItems in an MPMediaLibrary.
// Playlists have a unique identifier which persists across application launches.
MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaPlaylist : MPMediaItemCollection

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaPlaylistPropertyPersistentID;                             // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyName;                                     // filterable
@property (nonatomic, readonly, nullable) NSString *name MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyPlaylistAttributes;                       // filterable
@property (nonatomic, readonly) MPMediaPlaylistAttribute playlistAttributes MP_API(ios(7.0));

// For playlists with attribute MPMediaPlaylistAttributeGenius, the seedItems are the MPMediaItems which were used to the generate the playlist.
// Returns nil for playlists without MPMediaPlaylistAttributeGenius set.
MP_EXTERN NSString * const MPMediaPlaylistPropertySeedItems;
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *seedItems MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyDescriptionText MP_API(ios(9.3));
@property (nonatomic, readonly, nullable) NSString *descriptionText MP_API(ios(9.3));

MP_EXTERN NSString * const MPMediaPlaylistPropertyAuthorDisplayName MP_API(ios(9.3));
@property (nonatomic, readonly, nullable) NSString *authorDisplayName MP_API(ios(9.3));

- (void)addItemWithProductID:(NSString *)productID completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler MP_API(ios(9.3));
- (void)addMediaItems:(NSArray<MPMediaItem *> *)mediaItems completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler MP_API(ios(9.3));

@end

MP_API(ios(9.3))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaPlaylistCreationMetadata : NSObject

- (id)init NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name NS_DESIGNATED_INITIALIZER;

/// The display name of the playlist.
@property (nonatomic, readonly, copy) NSString *name;
/// Defaults to the requesting app's display name.
@property (null_resettable, nonatomic, copy) NSString *authorDisplayName;
@property (nonatomic, copy) NSString *descriptionText;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaQuerySection.h
//
//  MPMediaQuerySection.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// An MPMediaQuerySection object represents a single section grouping for a query.
MP_API(ios(4.2))
MP_PROHIBITED(tvos, macos, watchos)
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

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPChangePlaybackPositionCommand;
@class MPChangePlaybackRateCommand;
@class MPChangeRepeatModeCommand;
@class MPChangeShuffleModeCommand;
@class MPFeedbackCommand;
@class MPRatingCommand;
@class MPRemoteCommand;
@class MPSkipIntervalCommand;

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRemoteCommandCenter : NSObject

// Playback Commands
@property (nonatomic, readonly) MPRemoteCommand *pauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *playCommand;
@property (nonatomic, readonly) MPRemoteCommand *stopCommand;
@property (nonatomic, readonly) MPRemoteCommand *togglePlayPauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *enableLanguageOptionCommand MP_API(ios(9.0), macos(10.12.2));
@property (nonatomic, readonly) MPRemoteCommand *disableLanguageOptionCommand MP_API(ios(9.0), macos(10.12.2));
@property (nonatomic, readonly) MPChangePlaybackRateCommand *changePlaybackRateCommand;
@property (nonatomic, readonly) MPChangeRepeatModeCommand *changeRepeatModeCommand;
@property (nonatomic, readonly) MPChangeShuffleModeCommand *changeShuffleModeCommand;

// Previous/Next Track Commands
@property (nonatomic, readonly) MPRemoteCommand *nextTrackCommand;
@property (nonatomic, readonly) MPRemoteCommand *previousTrackCommand;

// Skip Interval Commands
@property (nonatomic, readonly) MPSkipIntervalCommand *skipForwardCommand;
@property (nonatomic, readonly) MPSkipIntervalCommand *skipBackwardCommand;

// Seek Commands
@property (nonatomic, readonly) MPRemoteCommand *seekForwardCommand;
@property (nonatomic, readonly) MPRemoteCommand *seekBackwardCommand;
@property (nonatomic, readonly) MPChangePlaybackPositionCommand *changePlaybackPositionCommand MP_API(ios(9.1), macos(10.12.2));

// Rating Command
@property (nonatomic, readonly) MPRatingCommand *ratingCommand;

// Feedback Commands
// These are generalized to three distinct actions. Your application can provide
// additional context about these actions with the localizedTitle property in
// MPFeedbackCommand.
@property (nonatomic, readonly) MPFeedbackCommand *likeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *dislikeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *bookmarkCommand;

+ (MPRemoteCommandCenter *)sharedCommandCenter;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPVolumeSettings.h
//
//  MPVolumeSettings.h
//  MediaPlayer
//
//  Copyright 2008-2019 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

MP_EXTERN void MPVolumeSettingsAlertShow(void) MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN void MPVolumeSettingsAlertHide(void) MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3)) MP_PROHIBITED(tvos, watchos);
MP_EXTERN BOOL MPVolumeSettingsAlertIsVisible(void) MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3)) MP_PROHIBITED(tvos, watchos);
// ==========  MediaPlayer.framework/Headers/MPPlayableContentManagerContext.h
//
//  MPPlayableContentManagerContext.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

/// MPPlayableContentManagerContext represents the current state of
/// the playable content endpoint. A context is retrievable from an instance
/// of MPPlayableContentManager.
MP_API(ios(8.4))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPPlayableContentManagerContext : NSObject

/// The number of items the content server will display when content limiting is enforced.
/// Returns NSIntegerMax if the content server will never limit the number of items.
@property (nonatomic, readonly) NSInteger enforcedContentItemsCount;

/// The depth of the navigation hierarchy the content server will allow. Exceeding this limit will result in a crash.
@property (nonatomic, readonly) NSInteger enforcedContentTreeDepth;

/// Represents whether content limits are being enforced by the content server or not.
@property (nonatomic, readonly) BOOL contentLimitsEnforced;
@property (nonatomic, readonly) BOOL contentLimitsEnabled MP_DEPRECATED_WITH_REPLACEMENT("contentLimitsEnforced", ios(8.4, 9.0));

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

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaEntity;
@class MPMediaQuery;
@class MPMediaPlaylist;
@class MPMediaPlaylistCreationMetadata;

// MPMediaLibrary represents a collection of media on a device, and can be used 
// to fetch items and playlists from the user's synced iTunes library.
// 
// See MPMediaQuery.h for a list of common queries or to build a custom query 
// from a chain of filter predicates.

// -----------------------------------------------------------------------------

typedef NS_ENUM(NSInteger, MPMediaLibraryAuthorizationStatus) {
    MPMediaLibraryAuthorizationStatusNotDetermined = 0,
    MPMediaLibraryAuthorizationStatusDenied,
    MPMediaLibraryAuthorizationStatusRestricted,
    MPMediaLibraryAuthorizationStatusAuthorized,
} MP_API(ios(9.3)) MP_PROHIBITED(tvos, macos, watchos);

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaLibrary : NSObject <NSSecureCoding>

+ (MPMediaLibrary *)defaultMediaLibrary;

// Returns the date at which the media library was last modified.
@property (nonatomic, readonly) NSDate *lastModifiedDate;

// MPMediaLibraryDidChangeNotification will be posted when a sync happens.
- (void)beginGeneratingLibraryChangeNotifications;
- (void)endGeneratingLibraryChangeNotifications;

+ (MPMediaLibraryAuthorizationStatus)authorizationStatus MP_API(ios(9.3));
+ (void)requestAuthorization:(void (^)(MPMediaLibraryAuthorizationStatus status))handler MP_API(ios(9.3));

- (void)addItemWithProductID:(NSString *)productID completionHandler:(nullable void (^)(NSArray <__kindof MPMediaEntity *> *entities, NSError * __nullable error))completionHandler MP_API(ios(9.3));

/*!
 * Finds the playlist associated with the UUID.
 * If the playlist exists, the creation metadata is ignored.
 * If no such playlist exists and creation metadata is valid, a playlist associated the UUID will be created.
 *
 * @discussion The UUID should typically be pre-generated to avoid creating a new playlist with every call.
 */

- (void)getPlaylistWithUUID:(NSUUID *)uuid creationMetadata:(nullable MPMediaPlaylistCreationMetadata *)creationMetadata completionHandler:(void (^)(MPMediaPlaylist * __nullable playlist, NSError * __nullable error))completionHandler MP_API(ios(9.3));

@end


// -----------------------------------------------------------------------------
// Notifications

// Any items or playlists which were previously cached should be re-evaluated from queries when MPMediaLibraryDidChangeNotification is posted.
MP_EXTERN NSString * const MPMediaLibraryDidChangeNotification MP_PROHIBITED(tvos, watchos);

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h
//
//  AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#if MP_HAS_AVMEDIASELECTION
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
#endif
// ==========  MediaPlayer.framework/Headers/MPRemoteCommandEvent.h
//
//  MPRemoteCommandEvent.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPNowPlayingInfoLanguageOption.h>
#import <MediaPlayer/MPRemoteControlTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommand;

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRemoteCommandEvent : NSObject

/// The command that sent the event.
@property (nonatomic, readonly) MPRemoteCommand *command;

/// The time when the event occurred.
@property (nonatomic, readonly) NSTimeInterval timestamp;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPSkipIntervalCommandEvent : MPRemoteCommandEvent

/// The chosen interval for this skip command event.
@property (nonatomic, readonly) NSTimeInterval interval;

@end

typedef NS_ENUM(NSUInteger, MPSeekCommandEventType) {
    MPSeekCommandEventTypeBeginSeeking,
    MPSeekCommandEventTypeEndSeeking
} MP_API(ios(7.1), macos(10.12.2), watchos(5.0));

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPSeekCommandEvent : MPRemoteCommandEvent

/// The type of seek command event, which specifies whether an external player
/// began or ended seeking.
@property (nonatomic, readonly) MPSeekCommandEventType type;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPRatingCommandEvent : MPRemoteCommandEvent

/// The chosen rating for this command event. This value will be within the
/// minimumRating and maximumRating values set for the MPRatingCommand object.
@property (nonatomic, readonly) float rating;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackRateCommandEvent : MPRemoteCommandEvent

/// The chosen playback rate for this command event. This value will be equal
/// to one of the values specified in the supportedPlaybackRates array for the
/// MPChangePlaybackRateCommand object.
@property (nonatomic, readonly) float playbackRate;

@end

MP_API(ios(7.1), tvos(7.1), macos(10.12.2), watchos(5.0))
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

MP_API(ios(9.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPChangeLanguageOptionCommandEvent : MPRemoteCommandEvent

/// The requested language option to change.
/// The supplied language option may be the Automatic Legible Language Option
/// which would mean that best legible language option based on user preferences
/// is being requested. See MPNowPlayingInfoLanguageOption isAutomaticLegibleLanguageOption
@property (nonatomic, readonly) MPNowPlayingInfoLanguageOption *languageOption;

/// Describes the extent of the changed language option
@property (nonatomic, readonly) MPChangeLanguageOptionSetting setting;

@end

MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangePlaybackPositionCommandEvent : MPRemoteCommandEvent

/// The desired playback position to use when setting the current time of the player.
@property (nonatomic, readonly) NSTimeInterval positionTime;

@end

MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeShuffleModeCommandEvent : MPRemoteCommandEvent

/// The desired shuffle type to use when fulfilling the request.
@property (nonatomic, readonly) MPShuffleType shuffleType;

/// Whether or not the selection should be preserved between playback sessions
@property (nonatomic, readonly) BOOL preservesShuffleMode;

@end

MP_API(ios(8.0), tvos(8.0), macos(10.12.2), watchos(5.0))
@interface MPChangeRepeatModeCommandEvent : MPRemoteCommandEvent

/// The desired repeat type to use when fulfilling the request.
@property (nonatomic, readonly) MPRepeatType repeatType;

/// Whether or not the selection should be preserved between playback sessions
@property (nonatomic, readonly) BOOL preservesRepeatMode;

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaPickerController.h
//
//  MPMediaPickerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#if MP_HAS_UIVIEW
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPMediaPickerControllerDelegate;

// MPMediaPickerController is a UIViewController for visually selecting media items.
// To display it, present it modally on an existing view controller.
MP_API(ios(3.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMediaPickerController : UIViewController

- (instancetype)initWithMediaTypes:(MPMediaType)mediaTypes NS_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly) MPMediaType mediaTypes;

@property (nonatomic, weak, nullable) id<MPMediaPickerControllerDelegate> delegate;

@property (nonatomic) BOOL allowsPickingMultipleItems; // default is NO

@property (nonatomic) BOOL showsCloudItems MP_API(ios(6.0)); // default is YES

@property (nonatomic) BOOL showsItemsWithProtectedAssets MP_API(ios(9.2)); // default is YES

@property (nonatomic, copy, nullable) NSString *prompt; // displays a prompt for the user above the navigation bar buttons

@end

MP_PROHIBITED(tvos, watchos)
@protocol MPMediaPickerControllerDelegate<NSObject>
@optional

// It is the delegate's responsibility to dismiss the modal view controller on the parent view controller.

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection;
- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker;

@end
NS_ASSUME_NONNULL_END
#endif
// ==========  MediaPlayer.framework/Headers/MPVolumeView.h
//
//  MPVolumeView.h
//  MediaPlayer
//
//  Copyright 2008-2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#if MP_HAS_UIVIEW
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

MP_API(ios(2.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPVolumeView : UIView <NSCoding>

@property (nonatomic) BOOL showsVolumeSlider MP_API(ios(4.2)); // Default is YES.
@property (nonatomic) BOOL showsRouteButton MP_DEPRECATED("Use AVRoutePickerView instead.", ios(4.2, 13.0));

// Returns YES if wireless routes (AirPlay, Bluetooth, etc) are available for user selection.
// Note that the view must be in present in a window hierarchy in order to discover some types of wireless routes.
@property (nonatomic, readonly, getter=areWirelessRoutesAvailable) BOOL wirelessRoutesAvailable MP_DEPRECATED("Use AVRouteDetector.multipleRoutesDetected instead.", ios(7.0, 13.0));

// Returns YES if a wireless route is active.
@property (nonatomic, readonly, getter=isWirelessRouteActive) BOOL wirelessRouteActive MP_DEPRECATED("Use AVPlayer.externalPlaybackActive instead.", ios(7.0, 13.0));

// Volume slider customization

- (void)setMinimumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));
- (void)setMaximumVolumeSliderImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));
- (void)setVolumeThumbImage:(nullable UIImage *)image forState:(UIControlState)state MP_API(ios(6.0));

- (nullable UIImage *)minimumVolumeSliderImageForState:(UIControlState)state MP_API(ios(6.0));
- (nullable UIImage *)maximumVolumeSliderImageForState:(UIControlState)state MP_API(ios(6.0));
- (nullable UIImage *)volumeThumbImageForState:(UIControlState)state MP_API(ios(6.0));

// Sets the image for the EU volume limit. When appropriate, this image will be displayed on top of the
// maximumVolumeSliderImage. It must be visually distinct from the maximumVolumeSliderImage, and use
// a color similar to the default, to convey a sense of warning to the user. The same image is used for
// all control states. For debugging purposes, switch on the "EU Volume Limit" setting in the Developer
// menu of the Settings application to always enable the volume limit.
@property (nonatomic, strong, nullable) UIImage *volumeWarningSliderImage MP_API(ios(7.0));

- (CGRect)volumeSliderRectForBounds:(CGRect)bounds MP_API(ios(6.0));
- (CGRect)volumeThumbRectForBounds:(CGRect)bounds volumeSliderRect:(CGRect)rect value:(float)value MP_API(ios(6.0));

// Route button customization

- (void)setRouteButtonImage:(nullable UIImage *)image forState:(UIControlState)state MP_DEPRECATED("Use AVRoutePickerView.routePickerButtonStyle instead.", ios(6.0, 13.0));
- (nullable UIImage *)routeButtonImageForState:(UIControlState)state MP_DEPRECATED("See AVRoutePickerView for possible replacements.", ios(6.0, 13.0));

- (CGRect)routeButtonRectForBounds:(CGRect)bounds MP_DEPRECATED("See AVRoutePickerView for possible replacements.", ios(6.0, 13.0));

@end

// Posted when the wirelessRoutesAvailable property changes.
MP_EXTERN NSString * const MPVolumeViewWirelessRoutesAvailableDidChangeNotification MP_DEPRECATED("Use AVRouteDetectorMultipleRoutesDetectedDidChangeNotification instead.", ios(7.0, 13.0)) MP_PROHIBITED(tvos, watchos);

// Posted when the wirelessRouteActive property changes.
MP_EXTERN NSString * const MPVolumeViewWirelessRouteActiveDidChangeNotification MP_DEPRECATED("Use AVPlayer.externalPlaybackActive KVO instead.", ios(7.0, 13.0)) MP_PROHIBITED(tvos, watchos);

NS_ASSUME_NONNULL_END
#endif
// ==========  MediaPlayer.framework/Headers/MPMediaItemCollection.h
//
//  MPMediaItemCollection.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaEntity.h>
#import <MediaPlayer/MPMediaItem.h>

NS_ASSUME_NONNULL_BEGIN

// An MPMediaItemCollection is a collection of related MPMediaItems in a media library.

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
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

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

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

typedef NS_ENUM(NSUInteger, MPNowPlayingInfoMediaType) {
    MPNowPlayingInfoMediaTypeNone = 0,
    MPNowPlayingInfoMediaTypeAudio,
    MPNowPlayingInfoMediaTypeVideo,
} MP_API(ios(10.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSUInteger, MPNowPlayingPlaybackState) {
    MPNowPlayingPlaybackStateUnknown = 0,
    MPNowPlayingPlaybackStatePlaying,
    MPNowPlayingPlaybackStatePaused,
    MPNowPlayingPlaybackStateStopped,
    MPNowPlayingPlaybackStateInterrupted
} MP_API(ios(11.0), tvos(11.0), macos(10.12.2), watchos(5.0));

MP_API(ios(5.0), tvos(5.0), macos(10.12.2), watchos(5.0))
@interface MPNowPlayingInfoCenter : NSObject

/// Returns the default now playing info center.
/// The default center holds now playing info about the current application.
+ (MPNowPlayingInfoCenter *)defaultCenter;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The current now playing info for the center.
/// Setting the info to nil will clear it.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo;

/// The current playback state of the app.
/// This only applies on macOS, where playback state cannot be determined by
/// the application's audio session. This property must be set every time
/// the app begins or halts playback, otherwise remote control functionality may
/// not work as expected.
@property (nonatomic) MPNowPlayingPlaybackState playbackState MP_API(macos(10.12.2), ios(13.0), uikitformac(13.0));

@end

// -----------------------------------------------------------------------------
// Additional metadata properties

// The elapsed time of the now playing item, in seconds.
// Note the elapsed time will be automatically extrapolated from the previously 
// provided elapsed time and playback rate, so updating this property frequently
// is not required (or recommended.)
MP_EXTERN NSString * const MPNowPlayingInfoPropertyElapsedPlaybackTime MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The playback rate of the now playing item, with 1.0 representing normal 
// playback. For example, 2.0 would represent playback at twice the normal rate.
// If not specified, assumed to be 1.0.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackRate MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The "default" playback rate of the now playing item. You should set this
// property if your app is playing a media item at a rate other than 1.0 in a
// default playback state. e.g., if you are playing back content at a rate of
// 2.0 and your playback state is not fast-forwarding, then the default
// playback rate should also be 2.0. Conversely, if you are playing back content
// at a normal rate (1.0) but the user is fast-forwarding your content at a rate
// greater than 1.0, then the default playback rate should be set to 1.0.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyDefaultPlaybackRate MP_API(ios(8.0), macos(10.12.2), watchos(5.0)); // NSNumber (double)

// The index of the now playing item in the application's playback queue.
// Note that the queue uses zero-based indexing, so the index of the first item 
// would be 0 if the item should be displayed as "item 1 of 10".
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackQueueIndex MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The total number of items in the application's playback queue.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackQueueCount MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The chapter currently being played. Note that this is zero-based.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyChapterNumber MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// The total number of chapters in the now playing item.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyChapterCount MP_API(ios(5.0), macos(10.12.2), watchos(5.0)); // NSNumber (NSUInteger)

// A boolean denoting whether the now playing item is a live stream.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyIsLiveStream MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (BOOL)

// A list of available language option groups in the now playing item
// Only one language option in a given group can be played at once.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyAvailableLanguageOptions MP_API(ios(9.0), macos(10.12.2), watchos(5.0)); // NSArrayRef of MPNowPlayingInfoLanguageOptionGroup

// A list of currently active language options in the now playing item.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyCurrentLanguageOptions MP_API(ios(9.0), macos(10.12.2), watchos(5.0)); // NSArray of MPNowPlayingInfoLanguageOption

// An identifier that represents the collection to which the now playing item belongs.
// This can refer to an artist, album, playlist, etc.
// This can be used to ask the now playing app to resume playback of the collection.
MP_EXTERN NSString * const MPNowPlayingInfoCollectionIdentifier MP_API(ios(9.3), macos(10.12.2), watchos(5.0)); // NSString

// An opaque identifier that uniquely represents the now playing item,
// even across app relaunches. This can be in any format and is only used to
// reference this item back to the now playing app.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyExternalContentIdentifier MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSString

// An optional opaque identifier that uniquely represents the profile that the
// now playing item is being played from, even across app relauches.
// This can be in any format and is only used to reference this profile back to
// the now playing app.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyExternalUserProfileIdentifier MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSString

// A unique string that identifies a service provider. If the now playing item
// belongs to a channel or subscription service, this key can be used to
// coordinate various types of now playing content from a particular service
// provider.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyServiceIdentifier MP_API(ios(11.0), macos(10.13), watchos(5.0)); // NSString

// Represents the current playback progress of the now playing item.
// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
// This value is different that ElapsedPlaybackTime and does not need to be exact
// as it is used as a high level indicator as to how far along the user is.
// For example, a movie may wish to set the now playing item as fully watched
// when the credits begin to roll.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyPlaybackProgress MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (float)

// Indicates the media type of the now playing item
// This can be used to determine what kind of user interface the system displays.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyMediaType MP_API(ios(10.0), macos(10.12.2), watchos(5.0)); // NSNumber (MPNowPlayingInfoMediaType)

// A URL pointing to the now playing item's underlying audio/video asset. This
// property is used by system UI when video thumbnails or audio waveform
// visualizations are applicable.
MP_EXTERN NSString * const MPNowPlayingInfoPropertyAssetURL MP_API(ios(10.3), macos(10.12.3), watchos(5.0)); // NSURL

// Represents the real-time date associated with the current elapsed playback time.
// The value of an AVPlayerItem’s currentDate property can be used to populate this property (see AVFoundation framework.)
// Note the current playback date will be automatically extrapolated from the previously
// provided current playback date, so updating this property frequently is not required (nor recommended.)
// For example, a sports broadcast can map an elapsed playback time (i.e 12 minutes and 30 seconds) to a real-time date (i.e "10:30:00 9/14/2017")
MP_EXTERN NSString * const MPNowPlayingInfoPropertyCurrentPlaybackDate MP_API(ios(11.1), macos(10.13.1), watchos(5.0)); // NSDate

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMediaItem.h
//
//  MPMediaItem.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaEntity.h>

NS_ASSUME_NONNULL_BEGIN

@class NSImage, UIImage, MPMediaItemArtwork;

typedef NS_OPTIONS(NSUInteger, MPMediaType) {
    // audio
    MPMediaTypeMusic                                            = 1 << 0,
    MPMediaTypePodcast                                          = 1 << 1,
    MPMediaTypeAudioBook                                        = 1 << 2,
    MPMediaTypeAudioITunesU MP_API(ios(5.0), macos(10.12.2))    = 1 << 3,
    MPMediaTypeAnyAudio                                         = 0x00ff,
    
    // video
    MPMediaTypeMovie        MP_API(ios(5.0), macos(10.12.2))    = 1 << 8,
    MPMediaTypeTVShow       MP_API(ios(5.0), macos(10.12.2))    = 1 << 9,
    MPMediaTypeVideoPodcast MP_API(ios(5.0), macos(10.12.2))    = 1 << 10,
    MPMediaTypeMusicVideo   MP_API(ios(5.0), macos(10.12.2))    = 1 << 11,
    MPMediaTypeVideoITunesU MP_API(ios(5.0), macos(10.12.2))    = 1 << 12,
    MPMediaTypeHomeVideo    MP_API(ios(7.0), macos(10.12.2))    = 1 << 13,
    MPMediaTypeAnyVideo     MP_API(ios(5.0), macos(10.12.2))    = 0xff00,
    
    MPMediaTypeAny                                     = ~0UL
} MP_API(ios(3.0), tvos(9.0), macos(10.12.2)) MP_PROHIBITED(watchos);

// An MPMediaItem represents a single piece of media in an MPMediaLibrary.
// Media items have a unique identifier which persists across application launches.

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaItem : MPMediaEntity

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaItemPropertyPersistentID MP_API(ios(4.2), macos(10.12.2));                            // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(5.0));

MP_EXTERN NSString * const MPMediaItemPropertyMediaType;                                                                // filterable
@property (nonatomic, readonly) MPMediaType mediaType MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyTitle;                                                                    // filterable
@property (nonatomic, readonly, nullable) NSString *title MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTitle;                                                               // filterable
@property (nonatomic, readonly, nullable) NSString *albumTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumPersistentID MP_API(ios(4.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtist;                                                                   // filterable
@property (nonatomic, readonly, nullable) NSString *artist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtistPersistentID MP_API(ios(4.2), macos(10.12.2));                      // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID artistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtist;                                                              // filterable
@property (nonatomic, readonly, nullable) NSString *albumArtist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtistPersistentID MP_API(ios(4.2), macos(10.12.2));                 // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumArtistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenre;                                                                    // filterable
@property (nonatomic, readonly, nullable) NSString *genre MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenrePersistentID MP_API(ios(4.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID genrePersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposer;                                                                 // filterable
@property (nonatomic, readonly, nullable) NSString *composer MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposerPersistentID MP_API(ios(4.2), macos(10.12.2));                    // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID composerPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlaybackDuration;
@property (nonatomic, readonly) NSTimeInterval playbackDuration MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackNumber;
@property (nonatomic, readonly) NSUInteger albumTrackNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackCount;
@property (nonatomic, readonly) NSUInteger albumTrackCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscNumber;
@property (nonatomic, readonly) NSUInteger discNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscCount;
@property (nonatomic, readonly) NSUInteger discCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtwork MP_API(ios(3.0), macos(10.13.2));
@property (nonatomic, readonly, nullable) MPMediaItemArtwork *artwork MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsExplicit MP_API(ios(7.0), macos(10.12.2));
@property (nonatomic, readonly, getter = isExplicitItem) BOOL explicitItem MP_API(ios(10.0));

MP_EXTERN NSString * const MPMediaItemPropertyLyrics;
@property (nonatomic, readonly, nullable) NSString *lyrics MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCompilation;                                                            // filterable
@property (nonatomic, readonly, getter = isCompilation) BOOL compilation MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyReleaseDate MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSDate *releaseDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyBeatsPerMinute MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger beatsPerMinute MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComments MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *comments MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAssetURL MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSURL *assetURL MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCloudItem MP_API(ios(6.0), macos(10.12.2));                             // filterable
@property (nonatomic, readonly, getter = isCloudItem) BOOL cloudItem MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyHasProtectedAsset MP_API(ios(9.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly, getter = hasProtectedAsset) BOOL protectedAsset MP_API(ios(9.2));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastTitle;                                                             // filterable
@property (nonatomic, readonly, nullable) NSString *podcastTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastPersistentID MP_API(ios(4.2), macos(10.12.2));                     // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID podcastPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlayCount;                                                                // filterable
@property (nonatomic, readonly) NSUInteger playCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertySkipCount;
@property (nonatomic, readonly) NSUInteger skipCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyRating;
@property (nonatomic, readonly) NSUInteger rating MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyLastPlayedDate;
@property (nonatomic, readonly, nullable) NSDate *lastPlayedDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyUserGrouping MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *userGrouping MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyBookmarkTime MP_API(ios(6.0), macos(10.12.2));
@property (nonatomic, readonly) NSTimeInterval bookmarkTime MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDateAdded MP_API(ios(10.0), macos(10.12.2));
@property (nonatomic, readonly) NSDate *dateAdded MP_API(ios(10.0));

// Matches the id used by MPMusicPlayerController to enqueue store tracks
MP_EXTERN NSString * const MPMediaItemPropertyPlaybackStoreID MP_API(ios(10.3));
@property (nonatomic, readonly) NSString *playbackStoreID MP_API(ios(10.3));

@end

//-----------------------------------------------------

MP_API(ios(3.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPMediaItemArtwork : NSObject

#if TARGET_OS_IPHONE

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(UIImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER MP_API(ios(10.0), tvos(10.0));

// Returns the artwork image for an item at a given size (in points).
- (nullable UIImage *)imageWithSize:(CGSize)size;

#else

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(NSImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER MP_API(ios(10.12.2));

// Returns the artwork image for an item at a given size (in points).
- (nullable NSImage *)imageWithSize:(CGSize)size MP_API(ios(10.12.2));

#endif

@property (nonatomic, readonly) CGRect bounds; // The bounds of the full size image (in points).
@property (nonatomic, readonly) CGRect imageCropRect MP_DEPRECATED("cropRect is no longer used", ios(3.0, 10.0));

#if TARGET_OS_IPHONE
- (instancetype)initWithImage:(UIImage *)image MP_DEPRECATED("Use -initWithBoundsSize:requestHandler:", ios(5.0, 10.0));
#endif

- (id)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

// ==========  MediaPlayer.framework/Headers/MPMediaQuery.h
//
//  MPMediaQuery.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
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
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, macos, watchos);

// MPMediaQuery represents a collection of items or playlists determined by a chain of MPMediaPredicate objects.
MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
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
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *itemSections MP_API(ios(4.2));
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *collectionSections MP_API(ios(4.2));

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

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaPredicate : NSObject <NSSecureCoding> {}
@end

// ------------------------------------------------------------------------
// MPMediaPropertyPredicate allows filtering based on a specific property value of an item or collection.
// See MPMediaItem.h and MPMediaPlaylist.h for a list of properties.

typedef NS_ENUM(NSInteger, MPMediaPredicateComparison) {
    MPMediaPredicateComparisonEqualTo,
    MPMediaPredicateComparisonContains
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, macos, watchos);

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
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
+ (NSString *)persistentIDPropertyForGroupingType:(MPMediaGrouping)groupingType MP_API(ios(4.2));

// Returns the item property to determine a title for a given grouping type.
// For example, [MPMediaItem titlePropertyForGroupingType:MPMediaGroupingAlbum] returns MPMediaItemPropertyAlbumTitle.
// Note that distinct collections will not necessarily have unique titles, e.g. an album may exist with the title "Greatest Hits" for multiple artists.
+ (NSString *)titlePropertyForGroupingType:(MPMediaGrouping)groupingType MP_API(ios(4.2));

@end

NS_ASSUME_NONNULL_END
// ==========  MediaPlayer.framework/Headers/MPMoviePlayerViewController.h
//
//  MPMoviePlayerViewController.h
//  MediaPlayer
//
//  Copyright 2009-2015 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#if MP_HAS_UIVIEW
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>

@class MPMoviePlayerController;

MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0))
MP_PROHIBITED(tvos, watchos)
@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);
- (void)dismissMoviePlayerViewControllerAnimated MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0)) MP_PROHIBITED(tvos, watchos);

@end
#endif
