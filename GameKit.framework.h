// ==========  GameKit.framework/Headers/GKChallenge.h
//
//  GKChallenge.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKScore.h>
#import <GameKit/GKAchievement.h>

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IPHONE
@class UIViewController;
typedef void (^GKChallengeComposeCompletionBlock)(UIViewController *composeController, BOOL didIssueChallenge, NSArray<NSString *> * __nullable sentPlayerIDs);
#else
@class NSViewController;
typedef void (^GKChallengeComposeCompletionBlock)(NSViewController *composeController, BOOL didIssueChallenge, NSArray<NSString *> * __nullable sentPlayerIDs);
#endif

@class GKPlayer;


typedef NS_ENUM(NSInteger, GKChallengeState) {
    GKChallengeStateInvalid = 0,
    GKChallengeStatePending = 1, // The challenge has been issued, but neither completed nor declined
    GKChallengeStateCompleted = 2, // The challenge has been completed by the receiving player
    GKChallengeStateDeclined = 3, // The challenge has been declined by the receiving player
};


NS_CLASS_AVAILABLE(10_8, 6_0) __WATCHOS_PROHIBITED
@interface GKChallenge : NSObject <NSCoding, NSSecureCoding>

// Query challenges for the current game issued to the local player -- equivalent GKChallenge objects are not guaranteed to be pointer equivalent across calls, but equal GKChallenge objects will have equal hashes
+ (void)loadReceivedChallengesWithCompletionHandler:(void(^ __nullable)(NSArray<GKChallenge *> * __nullable challenges, NSError * __nullable error))completionHandler;

// Any GKChallenge object to be declined must be in a state of GKChallengeStatePending in order to be successfully cancelled
- (void)decline;

@property (nonatomic, readonly, nullable, copy) NSString *issuingPlayerID NS_DEPRECATED(10_8, 10_10, 6_0, 8_0, "Use issuingPlayer instead") ;
@property (nonatomic, readonly, nullable, copy) NSString *receivingPlayerID NS_DEPRECATED(10_8, 10_10, 6_0, 8_0, "Use receivingPlayer instead") ;
@property (nonatomic, readonly, nullable, copy) GKPlayer *issuingPlayer NS_AVAILABLE(10_10, 8_0); // The GKPlayer who issued the challenge
@property (nonatomic, readonly, nullable, copy) GKPlayer *receivingPlayer NS_AVAILABLE(10_10, 8_0); // The GKPlayer who has received the challenge
@property (nonatomic, readonly, assign) GKChallengeState state; // Current state of the challenge
@property (nonatomic, readonly, retain) NSDate *issueDate; // Date the challenge was issued
@property (nonatomic, readonly, nullable, retain) NSDate *completionDate; // Date the challenge was completed or aborted
@property (nonatomic, readonly, nullable, copy) NSString *message; // The message sent to receivers of this challenge


@end

NS_CLASS_AVAILABLE(10_8, 6_0) __WATCHOS_PROHIBITED
@interface GKScoreChallenge : GKChallenge

@property (nonatomic, readonly, nullable, retain) GKScore *score; // The score to meet to satisfy this challenge
@end

NS_CLASS_AVAILABLE(10_8, 6_0) __WATCHOS_PROHIBITED
@interface GKAchievementChallenge : GKChallenge

@property (nonatomic, readonly, nullable, retain) GKAchievement *achievement; // The achievement to achieve to satisfy this challenge
@end


// Use the following category methods to issue GKScoreChallenges and GKAchievementChallenges to an array of playerIDs. Players may not issue challenges to themselves nor to non-friends. Please see the GameKit reference documentation for further details on these methods.
#if !TARGET_OS_WATCH
@interface GKScore (GKChallenge)

// Return a challenge compose view controller with pre-selected GKPlayers and a preformatted, player-editable message. Once this view controller is displayed, and the player sends or cancels sending the challenge, the completion handler will be called. This block contains the view controller, the reason why the handler was called, as well as which (if any) GKPlayers the challenge was sent to. Present modally from the top view controller. The completion handler should dismiss the view controller.
#if TARGET_OS_IPHONE
- (UIViewController *)challengeComposeControllerWithMessage:(nullable NSString *)message players:(nullable NSArray<GKPlayer *> *)players completionHandler:(nullable GKChallengeComposeCompletionBlock)completionHandler NS_AVAILABLE_IOS(8_0);
#else
- (NSViewController *)challengeComposeControllerWithMessage:(nullable NSString *)message players:(nullable NSArray<GKPlayer *> *)players completionHandler:(nullable GKChallengeComposeCompletionBlock)completionHandler NS_AVAILABLE_MAC(10_10);
#endif

// As of iOS 7.0, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:completionHandler: and present the view controller instead") ;

// Use this alternative to reportScores:withCompletionHandler: to allow only certain specific challenges to be completed. Pass nil to avoid completing any challenges.
+ (void)reportScores:(NSArray<GKScore *> *)scores withEligibleChallenges:(NSArray<GKChallenge *> *)challenges withCompletionHandler:(void(^ __nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

@end

@interface GKAchievement (GKChallenge)

// If an achievement has already been earned by the receiving player, and that achievement is not marked as replayable in iTunes connect, then the challenge will not be issued to the player. If an achievement is hidden, then it will not be issued.

// Return a challenge compose view controller with pre-selected GKPlayers and a preformatted, player-editable message. Once this view controller is displayed, and the player sends or cancels sending the challenge, the completion handler will be called. This block contains the view controller, the reason why the handler was called, as well as which (if any) GKPlayers the challenge was sent to. Present modally from the top view controller. The completion handler should dismiss the view controller.
#if TARGET_OS_IPHONE
- (UIViewController *)challengeComposeControllerWithMessage:(nullable NSString *)message players:(NSArray<GKPlayer *> *)players completionHandler:(__nullable GKChallengeComposeCompletionBlock)completionHandler NS_AVAILABLE_IOS(8_0);
#else
- (NSViewController *)challengeComposeControllerWithMessage:(nullable NSString *)message players:(NSArray<GKPlayer *> *)players completionHandler:(__nullable GKChallengeComposeCompletionBlock)completionHandler NS_AVAILABLE_MAC(10_10);
#endif

// As of iOS 7.0 and Mac OS X 10.10, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:completionHandler: and present the view controller instead") ;

// Given a list of players, return a subset of that list containing only players that are eligible to receive a challenge for the achievement.
- (void)selectChallengeablePlayers:(NSArray<GKPlayer *> *)players withCompletionHandler:(void(^ __nullable)(NSArray<GKPlayer *> * __nullable challengeablePlayers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

// Use this alternative to reportAchievements:withCompletionHandler: to allow only certain specific challenges to be completed. Pass nil to avoid completing any challenges.
+ (void)reportAchievements:(NSArray<GKAchievement *> *)achievements withEligibleChallenges:(NSArray<GKChallenge *> *)challenges withCompletionHandler:(void(^ __nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

@end

@interface GKScore (GKChallengeDeprecated)

#if TARGET_OS_IPHONE
- (nullable UIViewController *)challengeComposeControllerWithPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message completionHandler:(__nullable GKChallengeComposeCompletionBlock)completionHandler NS_DEPRECATED_IOS(7_0, 8_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:") ;
#endif

// As of iOS 7.0, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:completionHandler: and present the view controller instead") ;
@end

@interface GKAchievement (GKChallengeDeprecated)

- (void)selectChallengeablePlayerIDs:(nullable NSArray<NSString *> *)playerIDs withCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable challengeablePlayerIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 6_0, 8_0, "pass GKPlayers to selectChallengeablePlayers:") ;

// As of iOS 7.0 and Mac OS X 10.10, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:completionHandler: and present the view controller instead") ;

#if TARGET_OS_IPHONE
- (nullable UIViewController *)challengeComposeControllerWithPlayers:(nullable NSArray<NSString *> *)playerIDs message:(nullable NSString *)message completionHandler:(nullable GKChallengeComposeCompletionBlock)completionHandler NS_DEPRECATED_IOS(7_0, 8_0, "pass GKPlayers to challengeComposeControllerWithMessage:players:") ;
#endif

@end
#endif
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKBasePlayer.h
//
//  GKBasePlayer.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_AVAILABLE(3_0)
@interface GKBasePlayer : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) NSString *playerID;

// This player's full name as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

@end
// ==========  GameKit.framework/Headers/GKGameSessionError.h
//
//  GKGameSessionError.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * __nonnull GKGameSessionErrorDomain API_DEPRECATED("GKGameSession is deprecated, use real-time and turn-based matchmaking APIs instead.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);

typedef  NS_ENUM(NSInteger, GKGameSessionErrorCode) {
    GKGameSessionErrorUnknown = 1,
    GKGameSessionErrorNotAuthenticated = 2,
    GKGameSessionErrorSessionConflict = 3,
    GKGameSessionErrorSessionNotShared = 4,
    GKGameSessionErrorConnectionCancelledByUser = 5,
    GKGameSessionErrorConnectionFailed = 6,
    GKGameSessionErrorSessionHasMaxConnectedPlayers = 7,
    GKGameSessionErrorSendDataNotConnected = 8,
    GKGameSessionErrorSendDataNoRecipients = 9,
    GKGameSessionErrorSendDataNotReachable = 10,
    GKGameSessionErrorSendRateLimitReached = 11,
    GKGameSessionErrorBadContainer = 12,
    GKGameSessionErrorCloudQuotaExceeded = 13,
    GKGameSessionErrorNetworkFailure = 14,
    GKGameSessionErrorCloudDriveDisabled = 15,
    GKGameSessionErrorInvalidSession = 16,
} API_DEPRECATED("GKGameSession is deprecated, use real-time and turn-based matchmaking APIs instead.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);
// ==========  GameKit.framework/Headers/GKAchievementViewController.h
//
//  GKAchievementViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif
#import <GameKit/GKGameCenterViewController.h>

@protocol GKAchievementViewControllerDelegate;

// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
NS_CLASS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@interface GKAchievementViewController : GKGameCenterViewController
#if !TARGET_OS_IPHONE
{
    id<GKAchievementViewControllerDelegate> _achievementDelegate;
}
#endif
@end

@interface GKAchievementViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) id<GKAchievementViewControllerDelegate> achievementDelegate;
@end

// Optional delegate
NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@protocol GKAchievementViewControllerDelegate <NSObject>
@required
// The achievement view has finished
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;
@end


// ==========  GameKit.framework/Headers/GKGameCenterViewController.h
//
//  GKGameCenterViewController.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>

@protocol GKGameCenterControllerDelegate;

typedef NS_ENUM(NSInteger, GKGameCenterViewControllerState) {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges,
};

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#import <GameCenterUICore/GKDialogController.h>
#endif

NS_ASSUME_NONNULL_BEGIN
// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : UINavigationController
@end
#else
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : NSViewController  <GKViewController> {
	id _internal1, __weak _internal2, _internal3;
    GKGameCenterViewControllerState _viewState;
    NSString *_leaderboardIdentifier;
    NSString *_leaderboardCategory;
    GKLeaderboardTimeScope _leaderboardTimeScope;
    BOOL _internalFlag;
}
@end
#endif

@interface GKGameCenterViewController ()
@property (weak, nullable, NS_NONATOMIC_IOSONLY) id<GKGameCenterControllerDelegate> gameCenterDelegate;
@property (assign, NS_NONATOMIC_IOSONLY) GKGameCenterViewControllerState viewState ;

@end

@interface GKGameCenterViewController (Leaderboards)

@property (nonatomic, assign) GKLeaderboardTimeScope leaderboardTimeScope NS_AVAILABLE(10_8, 4_1) ;
@property (nonatomic, nullable, strong) NSString *leaderboardIdentifier NS_AVAILABLE(10_10, 7_0) ;

@property (nonatomic, nullable, strong) NSString *leaderboardCategory    NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "GKGameCenterViewController's leaderboardCategory property is deprecated. Use leaderboardIdentifier instead.") ;

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController NS_AVAILABLE(10_9, 6_0);

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKGameSession.h
//
//  GKGameSession.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

@class GKCloudPlayer;

typedef NS_ENUM(NSInteger, GKConnectionState) {
    GKConnectionStateNotConnected,
    GKConnectionStateConnected
};

typedef NS_ENUM(NSInteger, GKTransportType) {
    GKTransportTypeUnreliable,
    GKTransportTypeReliable
};

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("For real-time matches, use GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewController.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos)
@interface GKGameSession : NSObject
#if !__OBJC2__
{
    NSString *_identifier;
    NSString *_title;
    GKCloudPlayer *_owner;
    NSArray<GKCloudPlayer *> *_players;
    NSDate *_lastModifiedDate;
    GKCloudPlayer *_lastModifiedPlayer;
    NSString *_serverChangeTag;
    NSInteger _maxNumberOfConnectedPlayers;
    NSMutableDictionary<NSString*, NSArray<NSNumber*> *> *_playerStates;
}
#endif

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) GKCloudPlayer *owner;
@property (nonatomic, readonly) NSArray<GKCloudPlayer *> *players;
@property (nonatomic, readonly) NSDate *lastModifiedDate;
@property (nonatomic, readonly) GKCloudPlayer *lastModifiedPlayer;
@property (nonatomic, readonly) NSInteger maxNumberOfConnectedPlayers;
@property (nonatomic, readonly) NSArray<GKCloudPlayer *> *badgedPlayers;

// Create a new session with the given title and maximum number of connected players. (You may pass 0 to use the system limit of 16 players.)
+ (void)createSessionInContainer:(NSString * __nullable)containerName withTitle:(NSString *)title maxConnectedPlayers:(NSInteger)maxPlayers completionHandler:(void(^)(GKGameSession * __nullable session, NSError * __nullable error))completionHandler;

// Load all sessions involving the current user.
+ (void)loadSessionsInContainer:(NSString * __nullable)containerName completionHandler:(void(^)(NSArray<GKGameSession *> * __nullable sessions, NSError * __nullable error))completionHandler;

// Load a specific session.
+ (void)loadSessionWithIdentifier:(NSString *)identifier completionHandler:(void(^)(GKGameSession * __nullable session, NSError * __nullable error))completionHandler;

// Remove a session. If called by the owner this deletes the session from the server.
+ (void)removeSessionWithIdentifier:(NSString *)identifier completionHandler:(void(^)(NSError * __nullable error))completionHandler;


// Get the URL needed to share this session.
- (void)getShareURLWithCompletionHandler:(void(^)(NSURL * __nullable url, NSError * __nullable error))completionHandler;

// Load associated persistent data.
- (void)loadDataWithCompletionHandler:(void(^)(NSData * __nullable data, NSError * __nullable error))completionHandler;

// Save new/updated persistent data. Data size is limited to 512K. The session's lastModifiedDate and lastModifiedPlayer will be updated upon completion.
// If a version conflict is detected the handler will include the version currently on the server and an error. In this case the data has not been saved. To resolve the conflict a client would call this method again, presumably after merging data or giving the user a choice on how to resolve the conflict. (Note that when calling again it is possible to get a new conflict, if another device has since written a new version.)
- (void)saveData:(NSData *)data completionHandler:(void(^)(NSData * __nullable conflictingData, NSError * __nullable error))completionHandler;


// Set your connection state. May fail if you attempt to connect but the connected player limit has already been reached or there are network problems. The session's lastModifiedDate and lastModifiedPlayer will be updated upon completion.
- (void)setConnectionState:(GKConnectionState)state completionHandler:(void(^)(NSError * __nullable error))completionHandler;

// Get the players with the given connection state.
- (NSArray<GKCloudPlayer *> *)playersWithConnectionState:(GKConnectionState)state;

// Send data to all connected players.
- (void)sendData:(NSData *)data withTransportType:(GKTransportType)transport completionHandler:(void(^)(NSError * __nullable error))completionHandler;


// Send a message to any players in the session. This uses an unreliable push mechanism. Message/data delivery is not guaranteed and may take some time to arrive. Receiving players may optionally have their application badged for this session.
- (void)sendMessageWithLocalizedFormatKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments data:(NSData * __nullable)data toPlayers:(NSArray<GKCloudPlayer *> *)players badgePlayers:(BOOL)badgePlayers completionHandler:(void(^)(NSError * __nullable error))completionHandler;

// Clear application badge state for players for this session.
- (void)clearBadgeForPlayers:(NSArray<GKCloudPlayer *> *)players completionHandler:(void(^)(NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKPlayer.h
//
//  GKPlayer.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKBasePlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKError.h>

@class GKPlayerInternal;
@class GKGame;
@class GKLocalPlayer;
@class UIImage;

NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKPlayer : GKBasePlayer

// Load the Game Center players for the playerIDs provided. Error will be nil on success.
// Possible reasons for error:
// 1. Unauthenticated local player
// 2. Communications failure
// 3. Invalid player identifier
+ (void)loadPlayersForIdentifiers:(nonnull NSArray<NSString *> *)identifiers withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler;

//  This is the local player's unique and persistent ID that is scoped to this application. For non-local players, this ID is unique for this instantiation of this app.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *gamePlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

//  This is the local player's unique and persistent ID that is scoped to the Apple Store Connect Team identifier of this application. For non-local players, this ID is unique for this instantiation of this app.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *teamPlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

// This is player's alias to be displayed. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nonnull, NS_NONATOMIC_IOSONLY)          NSString    *displayName NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// The alias property contains the player's nickname. When you need to display the name to the user, consider using displayName instead. The nickname is unique but not invariant: the player may change their nickname. The nickname may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, copy, nonnull, NS_NONATOMIC_IOSONLY)    NSString    *alias;

+ (nonnull instancetype)anonymousGuestPlayerWithIdentifier:(nonnull NSString *)guestIdentifier NS_AVAILABLE(10_11, 9_0) __WATCHOS_PROHIBITED;
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *guestIdentifier NS_AVAILABLE(10_11, 9_0) __WATCHOS_PROHIBITED;

@end

#import <GameKit/GKPlayer.h>

@interface GKPlayer (UI)

// Available photo sizes.  Actual pixel dimensions will vary on different devices.
typedef NS_ENUM(NSInteger, GKPhotoSize) {
    GKPhotoSizeSmall = 0,
    GKPhotoSizeNormal,
};

// Asynchronously load the player's photo. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
#if TARGET_OS_IPHONE
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(UIImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#else
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(NSImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#endif

@end


// Notification will be posted whenever the player details changes. The object of the notification will be the player.
GK_EXTERN_WEAK NSNotificationName __nonnull GKPlayerDidChangeNotificationName;

@interface GKPlayer (Deprecated)

@property(readonly, NS_NONATOMIC_IOSONLY)          BOOL         isFriend NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use -[GKLocalPlayer loadFriendPlayers...]") ;    // True if this player is a friend of the local player
@property(readonly, nonnull, retain, NS_NONATOMIC_IOSONLY)  NSString *playerID GK_API_DEPRECATED( "use the teamPlayerID property to identify a player",ios(4.1,13.0),tvos(9.0,13.0),macosx(10.8,10.15));
@end
// ==========  GameKit.framework/Headers/GKDefines.h
//
//  GKDefines.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#ifndef GK_EXTERN
#ifdef __cplusplus
#define GK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#ifndef GK_EXTERN_WEAK
#define GK_EXTERN_WEAK  GK_EXTERN __attribute__((weak_import))
#endif

#if !defined(__GK_HAS_COMPILER_ATTRIBUTE)
# if defined(__has_attribute)
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) __has_attribute(attribute)
# elif defined(__GNUC__) && __GNUC__ >= 4
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) (1)
# else
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) (0)
# endif
#endif

#if !defined(GK_API_DEPRECATED)
# if __GK_HAS_COMPILER_ATTRIBUTE(deprecated) && !defined(GK_BUILDING_GK)
#  define GK_API_DEPRECATED(...) API_DEPRECATED(__VA_ARGS__)
# else
#  define GK_API_DEPRECATED(...)
# endif
#endif
// ==========  GameKit.framework/Headers/GKCloudPlayer.h
//
//  GKCloudPlayer.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <GameKit/GKBasePlayer.h>
NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("GKGameSession is deprecated. Use GKPlayer for both real-time and turn-based matchmaking APIs.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos)
@interface GKCloudPlayer : GKBasePlayer
#if !__OBJC2__
{
    NSString *_identifier;
    NSString *_name;
}
#endif

// Retrieve a player instance representing the active iCloud account for a given iCloud container. Returns nil and an error if the user is not signed in to iCloud or the container is invalid.
+ (void)getCurrentSignedInPlayerForContainer:(NSString * __nullable)containerName completionHandler:(void(^)(GKCloudPlayer *__nullable player, NSError * __nullable error))handler;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GameKit.h
//
//  GameKit.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>
#import <simd/simd.h>

#import <UIKit/UIKit.h>

#if !TARGET_OS_SIMULATOR
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#endif

#import <SpriteKit/SpriteKit.h>
#import <SceneKit/SceneKit.h>
#import <GameplayKit/GameplayKit.h>
#import <GameController/GameController.h>
#import <ModelIO/ModelIO.h>
#import <ReplayKit/ReplayKit.h>

#import <GameKit/GKDefines.h>
#import <GameKit/GKAchievement.h>
#import <GameKit/GKAchievementDescription.h>
#import <GameKit/GKAchievementViewController.h>
#import <GameKit/GKBasePlayer.h>
#import <GameKit/GKChallenge.h>
#import <GameKit/GKChallengeEventHandler.h>
#import <GameKit/GKCloudPlayer.h>
#import <GameKit/GKError.h>
#import <GameKit/GKEventListener.h>
#import <GameKit/GKFriendRequestComposeViewController.h>
#import <GameKit/GKGameCenterViewController.h>
#import <GameKit/GKGameSession.h>
#import <GameKit/GKGameSessionError.h>
#import <GameKit/GKGameSessionEventListener.h>
#import <GameKit/GKGameSessionSharingViewController.h>
#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKLeaderboardSet.h>
#import <GameKit/GKLeaderboardViewController.h>
#import <GameKit/GKLocalPlayer.h>
#import <GameKit/GKMatch.h>
#import <GameKit/GKMatchmaker.h>
#import <GameKit/GKMatchmakerViewController.h>
#import <GameKit/GKNotificationBanner.h>
#import <GameKit/GKPeerPickerController.h>
#import <GameKit/GKPlayer.h>
#import <GameKit/GKPublicConstants.h>
#import <GameKit/GKPublicProtocols.h>
#import <GameKit/GKRemoteUIController.h>
#import <GameKit/GKSavedGame.h>
#import <GameKit/GKSavedGameListener.h>
#import <GameKit/GKScore.h>
#import <GameKit/GKSession.h>
#import <GameKit/GKSessionError.h>
#import <GameKit/GKTurnBasedMatch.h>
#import <GameKit/GKTurnBasedMatchmakerViewController.h>
#import <GameKit/GKVoiceChat.h>
#import <GameKit/GKVoiceChatService.h>
// ==========  GameKit.framework/Headers/GKMatch.h
//
//  GKMatch.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GKVoiceChat;
@class GKPlayer;
@class GKLocalPlayer;
@class GKThreadsafeDictionary;

@protocol GKMatchDelegate;

typedef NS_ENUM(NSInteger, GKMatchSendDataMode) {
    GKMatchSendDataReliable,         // a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKMatchSendDataUnreliable        // Preferred method. Best effort and immediate, but no guarantees of delivery or order; will not stall.
};

typedef NS_ENUM(NSInteger, GKPlayerConnectionState) {
    GKPlayerStateUnknown,       // initial player state
    GKPlayerStateConnected,     // connected to the match
    GKPlayerStateDisconnected   // disconnected from the match
};


NS_ASSUME_NONNULL_BEGIN
// GKMatch represents an active networking sessions between players. It handles network communications and can report player connection status. All matches are created by a GKMatchmaker.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKMatch : NSObject

@property(nonatomic, readonly) NSArray<GKPlayer *> *players NS_AVAILABLE(10_10, 8_0);    // GKPlayers in the match
@property(nonatomic, nullable, assign) id<GKMatchDelegate> delegate;
@property(nonatomic, readonly) NSUInteger expectedPlayerCount;

// Asynchronously send data to one or more GKPlayers. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<GKPlayer *> *)players dataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error NS_AVAILABLE(10_10, 8_0);

// Asynchronously broadcasts data to all players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendDataToAllPlayers:(NSData *)data withDataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error;

// Disconnect the match. This will show all other players in the match that the local player has disconnected. This should be called before releasing the match instance.
- (void)disconnect;

// Join a named voice chat channel
// Will return nil if parental controls are turned on
- (nullable GKVoiceChat *)voiceChatWithName:(NSString *)name;

// Choose the best host from among the connected players using gathered estimates for bandwidth and packet loss. This is intended for applications that wish to implement a client-server model on top of the match. The returned player ID will be nil if the best host cannot currently be determined (e.g. players are still connecting).
- (void)chooseBestHostingPlayerWithCompletionHandler:(void(^)(GKPlayer * __nullable player))completionHandler NS_AVAILABLE(10_10, 8_0);

// Auto-matching to recreate a previous peer-to-peer match that became disconnected. A new match with the same set of players will be returned by the completion handler. All players should perform this when the match has ended for auto-matching to succeed. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)rematchWithCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0);

@end

__WATCHOS_PROHIBITED
@protocol GKMatchDelegate <NSObject>
@optional

// The match received data sent from the player.
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromRemotePlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data forRecipient:(GKPlayer *)recipient fromRemotePlayer:(GKPlayer *)player NS_AVAILABLE(10_11, 9_0);
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use match:didReceiveData:fromRemotePlayer:") ;

// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)match player:(GKPlayer *)player didChangeConnectionState:(GKPlayerConnectionState)state NS_AVAILABLE(10_8, 4_1);
- (void)match:(GKMatch *)match player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state NS_DEPRECATED(10_8, 10_8, 4_1, 8_0, "use match:player:didChangeConnectionState:") ;

// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)match didFailWithError:(nullable NSError *)error NS_AVAILABLE(10_8, 4_1);

// This method is called when the match is interrupted; if it returns YES, a new invite will be sent to attempt reconnection. This is supported only for 1v1 games
- (BOOL)match:(GKMatch *)match shouldReinviteDisconnectedPlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (BOOL)match:(GKMatch *)match shouldReinvitePlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use shouldReinviteDisconnectedPlayer:") ;

@end

@interface GKMatch (Deprecated)

- (void)chooseBestHostPlayerWithCompletionHandler:(void(^)(NSString * __nullable playerID))completionHandler NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use chooseBestHostingPlayerWithCompletionHandler:") ;
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<NSString *> *)playerIDs withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use sendData:toPlayers:dataMode:error:") ;
@property(nonatomic, readonly) NSArray<NSString *> *playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use players") ;   // NSStrings of player identifiers in the match

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKTurnBasedMatch.h
//
//  GKTurnBasedMatch.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <GameKit/GKPlayer.h>

@class GKMatchRequest, GKTurnBasedMatch, GKTurnBasedExchange, GKTurnBasedExchangeReply, GKScore, GKAchievement;

// Constants that describe the state of the overall match
typedef NS_ENUM(NSInteger, GKTurnBasedMatchStatus) {
    GKTurnBasedMatchStatusUnknown   = 0,
    GKTurnBasedMatchStatusOpen      = 1,
    GKTurnBasedMatchStatusEnded     = 2,
    GKTurnBasedMatchStatusMatching  = 3
};

// Constants that describe the state of individual participants in the match
typedef NS_ENUM(NSInteger, GKTurnBasedParticipantStatus) {
    // Statuses that are set by GameKit
    GKTurnBasedParticipantStatusUnknown     = 0,
    GKTurnBasedParticipantStatusInvited     = 1,    // a participant has been invited but not yet responded
    GKTurnBasedParticipantStatusDeclined    = 2,    // a participant that has declined an invite to this match
    GKTurnBasedParticipantStatusMatching    = 3,    // a participant that is waiting to be matched
    GKTurnBasedParticipantStatusActive      = 4,    // a participant that is active in this match
    GKTurnBasedParticipantStatusDone        = 5,    // a participant is done with this session
};

// Constants that describe the game result for a given participant who has reached the done state.  The developer is free to use these constants or add additional ones
typedef NS_ENUM(NSInteger, GKTurnBasedMatchOutcome) {
    GKTurnBasedMatchOutcomeNone         = 0,        // Participants who are not done with a match have this state
    GKTurnBasedMatchOutcomeQuit         = 1,        // Participant quit
    GKTurnBasedMatchOutcomeWon          = 2,        // Participant won
    GKTurnBasedMatchOutcomeLost         = 3,        // Participant lost
    GKTurnBasedMatchOutcomeTied         = 4,        // Participant tied
    GKTurnBasedMatchOutcomeTimeExpired  = 5,        // Game ended due to time running out
    GKTurnBasedMatchOutcomeFirst        = 6,
    GKTurnBasedMatchOutcomeSecond       = 7,
    GKTurnBasedMatchOutcomeThird        = 8,
    GKTurnBasedMatchOutcomeFourth       = 9,
    
    GKTurnBasedMatchOutcomeCustomRange = 0x00FF0000    // game result range available for custom app use
    
};

// GKTurnBasedMatch represents an ongoing turn-based game among the matched group of participants
// Existing matches can be shown and new matches created using GKTurnBasedMatchmakerViewController
// A list of existing matches can be retrieved using +loadMatchesWithCompletionHandler:
//
// By default turn based events will badge your app.  To opt out of this add GKGameCenterBadgingDisabled  with a boolean value of YES to your info plist


NS_CLASS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedParticipant : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) GKPlayer            *player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSDate                *lastTurnDate;
@property(readonly, NS_NONATOMIC_IOSONLY)       GKTurnBasedParticipantStatus    status;
@property(assign, NS_NONATOMIC_IOSONLY)         GKTurnBasedMatchOutcome         matchOutcome;
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSDate                *timeoutDate NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// Deprecated
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSString              *playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use player") ;

@end

NS_ASSUME_NONNULL_BEGIN
@protocol GKTurnBasedEventListener
@optional

// If Game Center initiates a match the developer should create a GKTurnBasedMatch from playersToInvite and present a GKTurnbasedMatchmakerViewController.
- (void)player:(GKPlayer *)player didRequestMatchWithOtherPlayers:(NSArray<GKPlayer *> *)playersToInvite NS_AVAILABLE(10_10, 8_0) API_UNAVAILABLE(watchos);

// called when it becomes this player's turn.  It also gets called under the following conditions:
//      the player's turn has a timeout and it is about to expire.
//      the player accepts an invite from another player.
// when the game is running it will additionally recieve turn events for the following:
//      turn was passed to another player
//      another player saved the match data
// Because of this the app needs to be prepared to handle this even while the player is taking a turn in an existing match.  The boolean indicates whether this event launched or brought to forground the app.
- (void)player:(GKPlayer *)player receivedTurnEventForMatch:(GKTurnBasedMatch *)match didBecomeActive:(BOOL)didBecomeActive NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// called when the match has ended.
- (void)player:(GKPlayer *)player matchEnded:(GKTurnBasedMatch *)match;

// this is called when a player receives an exchange request from another player.
- (void)player:(GKPlayer *)player receivedExchangeRequest:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// this is called when an exchange is canceled by the sender.
- (void)player:(GKPlayer *)player receivedExchangeCancellation:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// called when all players either respond or timeout responding to this request.  This is sent to both the turn holder and the initiator of the exchange
- (void)player:(GKPlayer *)player receivedExchangeReplies:(NSArray<GKTurnBasedExchangeReply *> *)replies forCompletedExchange:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Called when a player chooses to quit a match and that player has the current turn.  The developer should call participantQuitInTurnWithOutcome:nextParticipants:turnTimeout:matchData:completionHandler: on the match passing in appropriate values.  They can also update matchOutcome for other players as appropriate.
- (void)player:(GKPlayer *)player wantsToQuitMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_11, 9_0) __WATCHOS_AVAILABLE(3_0);

// Deprecated
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray<NSString *> *)playerIDsToInvite NS_DEPRECATED_IOS(7_0, 8_0, "use didRequestMatchWithOtherPlayers") ;

@end

// Turn timeout constants

extern NSTimeInterval        GKTurnTimeoutDefault NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);    // use a default timeout of one week
extern NSTimeInterval        GKTurnTimeoutNone NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);


NS_CLASS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedMatch : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSString                           *matchID;
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSDate                             *creationDate;
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedParticipant *>  *participants;          // array of GKTurnBasedParticipant objects
@property(readonly, NS_NONATOMIC_IOSONLY)                    GKTurnBasedMatchStatus             status;

// This indicates the participant who has the current turn.  This is set by passing the next participant into endTurnWithNextParticipant:matchData:completionHandler:
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  GKTurnBasedParticipant  *currentParticipant;

// Developer-defined data representing the current state of the game. This property is nil until loaded by loadMatchDataWithCompletionHandler:
// The developer can submit updated matchData by passing it into endTurnWithNextParticipant:matchData:completionHandler: or endMatchInTurnWithMatchData:completionHandler:
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSData                  *matchData;

// If the developer wishes to display a message in GKTurnBasedMatchmakerViewController at the end of a turn or end of the match.  Only the current participant can set this.
// Sets a localizable mesage that will be localized on the receiver side if the game is installed and on the sender side as a fallback.
// The key and arguments offer a subset of formated strings as follows
//    key is a string in a Localizable.strings file for the current localization (which is set by the user’s language preference).  key string can be formatted with %@ and %n$@ specifiers to take the variables specified in loc-args
//    arguments is an array of strings that will be substituted using the format string.
// Notes: The localized message will be evaluated locally from these keys and sent across as well so that devices that do not have the game installed will see the message in the sender's localization
//        The developer can access resulting string using the message property
//        This is a similar concept to the way we handle localization for Push Notifications. See the "Local and Push Notification Programming Guide" for more details.
- (void)setLocalizableMessageWithKey:(NSString*)key arguments:(nullable NSArray<NSString *> *)arguments NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the localizable message in the current locale. Setting this is equivalent to calling [self setLocalizableMessageWithKey:message arguments:nil]
@property(readwrite, nullable, copy, NS_NONATOMIC_IOSONLY)   NSString                *message;


// Returns the maximum size for the match data.
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              matchDataMaximumSize NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// exchanges that are in progress on this match.  Once an exchange has completed and has been resolved by merging it into the match data by the current turn holder then it will be removed from this list
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *exchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the exchanges that currently await a reply from the local player
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *activeExchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the exchanges that have been completed and need to be merged by the local participant.  This will be nil unless the local participant is the current turn holder for this match
@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *completedExchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// maximum data allowed for exchange data
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              exchangeDataMaximumSize NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// limit of the number of exchanges that this player can have initiated at a given time
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              exchangeMaxInitiatedExchangesPerPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Attempt to find a turn-based match for the specified request. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
+ (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler;

// This method retrieves the list of GKTurnBasedMatches that the current player is or has participated in. The callback’s array contains GKTurnBasedMatches
+ (void)loadMatchesWithCompletionHandler:(void(^__nullable)(NSArray<GKTurnBasedMatch *> * __nullable matches, NSError * __nullable error))completionHandler;

// load a match based on a previously known match ID
+ (void)loadMatchWithID:(NSString *)matchID withCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Recreate a previously existing turn based match that ended. A new match with the same set of players will be returned by the completion handler. If multiple players do this then multiple new matches will be created. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
- (void)rematchWithCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);

// If the local participant has status invited then accept the invite, otherwise returns an error
- (void)acceptInviteWithCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// If the local participant has status invited then decline the invite, otherwise returns an error
- (void)declineInviteWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Remove a declined or completed match (one with a matchOutcome set) from the player's list of matches. If using the GKTurnBasedMatchmakerViewController UI, this will remove it from the finished sessions.  The developer should not do this without user input.
- (void)removeWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This method fetches the match data and exchanges for this match.  This data is the state of the game at this point in time.  This may update the status and/or participant properties if they have changed.
- (void)loadMatchDataWithCompletionHandler:(void(^__nullable)(NSData * __nullable matchData, NSError * __nullable error))completionHandler;


// Ends the current player's turn. You may update the matchOutcome for any GKTurnBasedPlayerInfos that you wish to before ending the turn.
// This will asynchronously report error in these cases:
// 1. Communications problem
// 2. Is not current player's turn
// 3. Session is closed
- (void)endTurnWithNextParticipants:(NSArray<GKTurnBasedParticipant *> *)nextParticipants
                        turnTimeout:(NSTimeInterval)timeout
                          matchData:(NSData*)matchData
                 completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);


// Ends the current player's turn by quitting the match.  The caller must indicate the next player and pass in updated matchData (if used).  All completed exchanges must be resolved or canceled before calling this.
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome
                        nextParticipants:(NSArray<GKTurnBasedParticipant *> *)nextParticipants
                             turnTimeout:(NSTimeInterval)timeout
                               matchData:(NSData*)matchData
                       completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);

// Abandon the match when it is not the current participant's turn.  In this there is no update to matchData and no need to set nextParticipant.
- (void)participantQuitOutOfTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This will end the match for all participants. You must set each participant’s matchOutcome before calling this method.  All completed exchanges must be resolved or canceled before calling this.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This will end the match and submit scores and achievements for all participants. Scores should be submitted for all involved players, and multiple scores may be submitted for each to different leaderboards. Earned achievements may also be submitted for any participants. You must set each participant’s matchOutcome before calling this method. All completed exchanges must be resolved or canceled before calling this.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData scores:(nullable NSArray<GKScore *> *)scores achievements:(nullable NSArray<GKAchievement *> *)achievements completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// saves the matchData for the current turn without ending the turn.  If other players have the game running they will receive a handleTurnEventForMatch to indicate that the matchData has changed.  This is useful to initialize the game state for the first player when they take their turn or for updating the turn data due to the user taking an irreversible action within their turn.  All completed exchanges must be resolved or canceled before calling this. If you are using exchanges use saveMergedMatchData instead.  
- (void)saveCurrentTurnWithMatchData:(NSData *)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// saves the merged matchData for the current turn without ending the turn and mark the supplied exchanges as resolved meaning that the data has been merged into the match data. If other players have the game running they will receive a handleTurnEventForMatch to indicate that the matchData has changed.  It is required that all completed exchanges are resolved before ending a turn.  Otherwise calling endTurn, participantQuitInTurnWithOutCome or endMatchInTurn will return an error
- (void)saveMergedMatchData:(NSData *)matchData
      withResolvedExchanges:(NSArray<GKTurnBasedExchange *> *)exchanges
          completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Send an exchange request to one or more participants.  Each recipient will receive a push notification using supplied localizable message.  If any of the participants have an inactive status (GKTurnBasedParticipantStatusDone) then this will return an error.  completionHandler gets passed the updated exchange with identifier, sender and recipients set
- (void)sendExchangeToParticipants:(NSArray<GKTurnBasedParticipant *> *)participants
                              data:(NSData *)data
             localizableMessageKey:(NSString *)key
                         arguments:(NSArray<NSString *> *)arguments
                           timeout:(NSTimeInterval)timeout
                 completionHandler:(void(^__nullable)(GKTurnBasedExchange * __nullable exchange, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0)  __WATCHOS_AVAILABLE(3_0);

// Send a reminder to one or more participants.  Each recipient will receive a push notification using supplied localizable message.  This allows a game to send reminders that a turn or exchange request needs action.  On the receiver side this will generate a turn event for the match.
- (void)sendReminderToParticipants:(NSArray<GKTurnBasedParticipant *> *)participants
             localizableMessageKey:(NSString *)key
                         arguments:(NSArray<NSString *> *)arguments
                 completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);
                 
// deprecated methods
- (void)endTurnWithNextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 5_0, 6_0, "Use endTurnWithNextParticipants:... instead") ;
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome nextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 5_0, 6_0, "Use participantQuitInTurnWithOutcome:nextParticipants:turnTimeout:... instead") ;

@end

// Turn Based Exchanges

// Constants that describe the status of exchanges and their replies

typedef NS_ENUM(int8_t, GKTurnBasedExchangeStatus) {
    GKTurnBasedExchangeStatusUnknown = 0,
    GKTurnBasedExchangeStatusActive = 1,
    GKTurnBasedExchangeStatusComplete = 2,
    GKTurnBasedExchangeStatusResolved = 3,
    GKTurnBasedExchangeStatusCanceled = 4
}  NS_ENUM_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Exchange timeout constants

extern NSTimeInterval        GKExchangeTimeoutDefault NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);    // use a default timeout of one day
extern NSTimeInterval        GKExchangeTimeoutNone NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


NS_CLASS_AVAILABLE(10_10,7_0) __WATCHOS_AVAILABLE(3_0)
@interface  GKTurnBasedExchange : NSObject

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSString                            *exchangeID;         // persistent identifier used to refer to this exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     GKTurnBasedParticipant              *sender;             // participant who sent the exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSArray<GKTurnBasedParticipant *>   *recipients;         // participants who are the recipients of the exchange
@property (assign, readonly, NS_NONATOMIC_IOSONLY)       GKTurnBasedExchangeStatus           status;              // status of the exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSString                            *message;            // localized message for the push notification sent to all recipients of this exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSData                              *data;               // data to send with the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *sendDate;           // send date for the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *timeoutDate;        // timeout date for the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *completionDate;     // date when this exchange completed

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSArray<GKTurnBasedExchangeReply *> *replies;            // Array of GKTurnBasedExchangeReply.

// cancel an exchange. It is possible to cancel an exchange that is active or complete. Each recipient will receive a push notification using supplied localizable message. Returns an error if the exchange has already been canceled.
- (void)cancelWithLocalizableMessageKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// reply to an exchange. The sender will receive a push notification using supplied localizable message. Returns an error if the exchange has already been canceled.
- (void)replyWithLocalizableMessageKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments data:(NSData *)data completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

@end

    
NS_CLASS_AVAILABLE(10_10,7_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedExchangeReply  : NSObject

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          GKTurnBasedParticipant         *recipient;          // the recipient who this reply is from
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSString                       *message;            // localized message for the push notification generated by the reply of this exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSData                         *data;               // data sent by the replying recipient
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSDate                         *replyDate NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0); // send date for the exchange.
@end

// deprecated

// see documentation for GKTurnBasedEventListener for the equivalent methods
NS_DEPRECATED(10_8, 10_10, 5_0, 7_0, "Use registerListener on GKLocalPlayer with an object that implements the GKTurnBasedEventListener protocol") 
@protocol  GKTurnBasedEventHandlerDelegate

- (void)handleInviteFromGameCenter:(NSArray<NSString *> *)playersToInvite NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match didBecomeActive:(BOOL)didBecomeActive NS_DEPRECATED(10_9, 10_10, 6_0, 7_0);

@optional
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_9, 5_0, 7_0);
- (void)handleMatchEnded:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_10, 6_0, 7_0);

@end

NS_CLASS_DEPRECATED(10_8, 10_10, 5_0, 7_0, "Use registerListener on GKLocalPlayer with an object that implements the GKTurnBasedEventListener protocol") 
@interface GKTurnBasedEventHandler : NSObject

+ (GKTurnBasedEventHandler *)sharedTurnBasedEventHandler NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);

@property (assign, NS_NONATOMIC_IOSONLY)         NSObject<GKTurnBasedEventHandlerDelegate>    *delegate NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKLeaderboard.h
//
//  GKLeaderboard.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <os/lock.h>

typedef NS_ENUM(NSInteger, GKLeaderboardTimeScope) {
    GKLeaderboardTimeScopeToday = 0,
    GKLeaderboardTimeScopeWeek,
    GKLeaderboardTimeScopeAllTime
};

typedef NS_ENUM(NSInteger, GKLeaderboardPlayerScope) {
    GKLeaderboardPlayerScopeGlobal = 0,
    GKLeaderboardPlayerScopeFriendsOnly
};

@class GKPlayer;
@class GKScore;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN

// GKLeaderboard represents the set of high scores for the current game, always including the local player's best score.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKLeaderboard : NSObject

@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardTimeScope      timeScope;
@property(assign, NS_NONATOMIC_IOSONLY)            GKLeaderboardPlayerScope    playerScope;        // Filter on friends. Does not apply to leaderboard initialized with players.

@property(copy, nullable, NS_NONATOMIC_IOSONLY)              NSString          *identifier NS_AVAILABLE(10_10, 7_0);         // leaderboardID. If nil, fetch the aggregate leaderboard.
 
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)    NSString          *title;             // Localized category title. Defaults to nil until loaded.
@property(assign, NS_NONATOMIC_IOSONLY)            NSRange                     range;              // Leaderboards start at index 1 and the length should be less than 100. Does not apply to leaderboards initialized with players.  Exception will be thrown if developer tries to set an invalid range

@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)  NSArray<GKScore *> *scores;            // Scores are not valid until loadScores: has completed.
@property(readonly, assign, NS_NONATOMIC_IOSONLY)  NSUInteger                  maxRange;           // The maxRange which represents the size of the leaderboard is not valid until loadScores: has completed.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)  GKScore           *localPlayerScore;  // The local player's score
@property(readonly, getter=isLoading)              BOOL                        loading;            // true if the leaderboard is currently loading

@property(nonatomic, readonly, nullable, retain)   NSString                    *groupIdentifier    NS_AVAILABLE(10_9, 6_0);       // set when leaderboards have been designated a game group; set when loadLeaderboardsWithCompletionHandler has been called for leaderboards that support game groups

// Default is the range 1-10 with Global/AllTime scopes
// if you want to change the scopes or range, set the properites before loading the scores.
- (instancetype)init;

// Specify an array of GKPlayers. For example, the players who are in a match together
// Defaults to AllTime score, if you want to change the timeScope, set the property before loading the scores. Range and playerScope are not applicable. players may not be nil.
- (instancetype)initWithPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);

// Load the scores for this leader board asynchronously.  Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadScoresWithCompletionHandler:(void(^__nullable)(NSArray<GKScore *> * __nullable scores, NSError * __nullable error))completionHandler;

// Loads the array of GKLeaderboard for your app
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
+ (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0);

@end

@interface GKLeaderboard (Deprecated)

@property(copy, nullable, NS_NONATOMIC_IOSONLY)              NSString                    *category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use identifier instead") ;         // Deprecated. Use identifier instead.

- (nullable instancetype)initWithPlayerIDs:(nullable NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "Use initWithPlayers: instead") ;

+ (void)loadCategoriesWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable categories, NSArray<NSString *> * __nullable titles, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 4_1, 6_0, "Use loadLeaderboardsWithCompletionHandler: instead") ;

+ (void)setDefaultLeaderboard:(nullable NSString *)leaderboardIdentifier withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 5_0, 7_0,"Use setDefaultLeaderboardIdentifier:completionHandler: on GKLocalPlayer instead") ;

@end
NS_ASSUME_NONNULL_END


@interface GKLeaderboard (UI)
 
 // Asynchronously load the image. Error will be nil on success.
#if TARGET_OS_IPHONE
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 7_0) __TVOS_UNAVAILABLE;
#else
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 7_0);
#endif

@end
 

// ==========  GameKit.framework/Headers/GKRemoteUIController.h
//
//  GKViewController.h
//  GameCenterSettings
//
//  Created by Jeff Watkins on 2/6/13.
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GKRemoteUIController;

typedef void (^GKRemoteUIControllerCompletionHandler)(GKRemoteUIController *controller, NSError *error);

extern NSString * const GKRemoteUIApplyThemeKey;
extern NSString * const GKRemoteUILayoutStyleKey;
extern NSString * const GKRemoteUIErrorDomain;

extern NSString * const GKRemoteUIAuthTitle;
extern NSString * const GKRemoteUIAuthOKURL;
extern NSString * const GKRemoteUIAuthCancelURL;
extern NSString * const GKRemoteUIAuthUserName;
extern NSString * const GKRemoteUIAuthPassword;
extern NSString * const GKRemoteUIAuthErrorMessage;

typedef enum {
    GKRemoteUILayoutStylePhone,
    GKRemoteUILayoutStyleModalPad,
    GKRemoteUILayoutStyleFullscreenPad
} GKRemoteUILayoutStyle;

typedef enum {
    GKRemoteUIErrorTypeCancelledByServer = 0,
    GKRemoteUIErrorTypeNoServerImplementation = 1,
    GKRemoteUIErrorTypeNoData = 2,
    GKRemoteUIErrorTypeNeedsAuth = 3,
    GKRemoteUIErrorTypeCanceledByUser = 4
} GKRemoteUIErrorType;

@protocol GKRemoteUIAuxiliaryViewDelegate <NSObject>
@optional
- (void)auxiliaryView:(UIView *)auxiliaryView pressedButton:(NSString *)buttonName attributes:(NSDictionary *)attributes;
- (void)auxiliaryView:(UIView *)auxiliaryView pressedLink:(NSString *)linkURLString attributes:(NSDictionary *)attributes;
@end

@interface GKRemoteUIController : NSObject <GKRemoteUIAuxiliaryViewDelegate>

@property (nonatomic, copy) GKRemoteUIControllerCompletionHandler completionHandler;
@property (nonatomic, readonly, strong) NSError *error;
@property (nonatomic, readonly) BOOL loading;
@property (nonatomic, assign) BOOL shouldApplyGameCenterTheme; /// Default is YES

+ (instancetype)remoteUIController;

- (void)presentInParentNavigationController:(UINavigationController *)navigationController animated:(BOOL)animated;

@end
// ==========  GameKit.framework/Headers/GKLeaderboardSet.h
//
//  GKLeaderboardSet.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>


@class GKLeaderboard;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN
// GKLeaderboardSet represents the sets that leaderboards can be broken out into. 
NS_CLASS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0)
@interface GKLeaderboardSet : NSObject <NSCoding, NSSecureCoding>

@property(readonly, copy, NS_NONATOMIC_IOSONLY)    NSString                    *title;               // Localized set title.

@property(nonatomic, readonly, nullable, retain)            NSString                    *groupIdentifier;       // set when leaderboardSets have been designated a game group; set when loadLeaderboardSetsWithCompletionHandler has been called for leaderboards that support game groups
@property(copy, nullable, NS_NONATOMIC_IOSONLY)             NSString                    *identifier;          // leaderboard set.

// Loads array with all sets for game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Set not present
+ (void)loadLeaderboardSetsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboardSet *> * __nullable leaderboardSets, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

// Loads array with all leaderboards for the leaderboardSet
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0);

@end
NS_ASSUME_NONNULL_END

#import <GameKit/GKLeaderboardSet.h>

@interface GKLeaderboardSet (UI)

// Asynchronously load the image. Error will be nil on success.
#if TARGET_OS_IPHONE
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler __TVOS_UNAVAILABLE;
#else
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler;
#endif

@end



// ==========  GameKit.framework/Headers/GKNotificationBanner.h
//
//  GKNotificationBanner.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

// Asynchronously shows a notification banner like the one used for Game Center’s “Welcome Back” message. 
// If a banner is already being displayed, additional banners will be shown in sequence. Use this to notify the user of game events, high scores, completed achievements, etc.

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKNotificationBanner : NSObject

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message completionHandler:(void(^__nullable)(void))completionHandler NS_AVAILABLE(10_8, 5_0);

+ (void)showBannerWithTitle:(nullable NSString *)title message:(nullable NSString *)message duration:(NSTimeInterval)duration completionHandler:(void(^__nullable)(void))completionHandler NS_AVAILABLE(10_8, 6_0);

@end
// ==========  GameKit.framework/Headers/GKSessionError.h
/*
 *  GKSessionError.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

// domain
GK_EXTERN_WEAK NSString * __nonnull const GKSessionErrorDomain;

// code
typedef NS_ENUM(int, GKSessionError)
{
    GKSessionInvalidParameterError = 30500,
    GKSessionPeerNotFoundError = 30501,
    GKSessionDeclinedError = 30502,
    GKSessionTimedOutError = 30503,
    GKSessionCancelledError = 30504,
    GKSessionConnectionFailedError = 30505,
    GKSessionConnectionClosedError = 30506,
    GKSessionDataTooBigError = 30507,
    GKSessionNotConnectedError = 30508,
    GKSessionCannotEnableError = 30509,
    GKSessionInProgressError = 30510,

    GKSessionConnectivityError = 30201,
    GKSessionTransportError = 30202,
    GKSessionInternalError = 30203,
    GKSessionUnknownError = 30204,
    GKSessionSystemError = 30205
}  NS_ENUM_DEPRECATED_IOS(3_0, 7_0);

// ==========  GameKit.framework/Headers/GKChallengeEventHandler.h
//
//  GKChallengeEventHandler.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKChallenge.h>

// GKChallengeEventHandler's delegate must implement the following protocol to be notified of challenge-related events. All of these methods are called on the main thread.
NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.") __WATCHOS_PROHIBITED 
@protocol GKChallengeEventHandlerDelegate <NSObject>

@optional

// Called when the user taps a challenge notification banner or the "Play Now" button for a challenge inside Game Center, causing the game to launch. Also called when the user taps a challenge banner inside the game.
- (void)localPlayerDidSelectChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed when a challenge is received in-game for the local player. If NO, then no banner is displayed, and localPlayerDidSelectChallenge: will not be called for that challenge. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyReceivedChallenge:(GKChallenge *)challenge;

// Called when the local player has received a challenge, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidReceiveChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyCompletedChallenge:(GKChallenge *)challenge;

// Called when the local player has completed one of their challenges, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidCompleteChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForRemotelyCompletedChallenge:(GKChallenge *)challenge;

// Called when a non-local player has completed a challenge issued by the local player. Triggered by a push notification from the server. Received when a challenge notification banner is tapped, or while the game is running. 
- (void)remotePlayerDidCompleteChallenge:(GKChallenge *)challenge;

@end

#if !TARGET_OS_WATCH

NS_CLASS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.") 
// A singleton object responsible for dispatching challenge-related events to its delegate
@interface GKChallengeEventHandler : NSObject

+ (GKChallengeEventHandler *) challengeEventHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0);

@property (nonatomic, assign) id<GKChallengeEventHandlerDelegate> delegate NS_DEPRECATED(10_8, 10_10, 6_0, 7_0); // It is not safe to read or write this property on anything other than the main thread
@end
#endif
// ==========  GameKit.framework/Headers/GKPublicProtocols.h
/*
 GKPublicProtocols.h
 GameKit
 
 Copyright 2010 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <GameKit/GKPublicConstants.h>

@class GKSession;
@protocol GKSessionDelegate;

NS_ASSUME_NONNULL_BEGIN

/* Callbacks to the GKSession delegate.
*/
NS_DEPRECATED(10_8, 10_10, 3_0, 7_0, "Use MCSession in association with MCSessionDelegate from the MultipeerConnectivity framework instead") 
@protocol GKSessionDelegate <NSObject>

@optional

/* Indicates a state change for the given peer.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)session:(GKSession *)session peer:(NSString *)peerID didChangeState:(GKPeerConnectionState)state;
#pragma clang diagnostic pop

/* Indicates a connection request was received from another peer. 
 
Accept by calling -acceptConnectionFromPeer:
Deny by calling -denyConnectionFromPeer:
*/
- (void)session:(GKSession *)session didReceiveConnectionRequestFromPeer:(NSString *)peerID;

/* Indicates a connection error occurred with a peer, which includes connection request failures, or disconnects due to timeouts.
*/
- (void)session:(GKSession *)session connectionWithPeerFailed:(NSString *)peerID withError:(NSError *)error;

/* Indicates an error occurred with the session such as failing to make available.
*/
- (void)session:(GKSession *)session didFailWithError:(NSError *)error;

@end


@class GKVoiceChatService;

//All clients will need to implement this protocol
NS_DEPRECATED_IOS(3_0, 7_0, "Use GKVoiceChat instead") 
@protocol GKVoiceChatClient <NSObject>

@required

//this channel will only be used to setup voice chat, and not to send audio data. The only requirement is that messages are sent and received within a few (1-2) seconds time.
- (void)voiceChatService:(GKVoiceChatService *)voiceChatService sendData:(NSData *)data toParticipantID:(NSString *)participantID; //must be sent within some reasonble period of time and should accept at least 512 bytes.

- (NSString *)participantID; // voice chat client's participant ID

@optional

//should be sent immediately with no delay on a UDP peer-to-peer connection.  
// If this method is implemented, then the Voice Chat Service will not attempt to set up a peer-to-peer connection. And will rely on this one.  To transmit audio.
- (void)voiceChatService:(GKVoiceChatService *)voiceChatService sendRealTimeData:(NSData *)data toParticipantID:(NSString *)participantID;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didStartWithParticipantID:(NSString *)participantID;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didNotStartWithParticipantID:(NSString *)participantID error:(nullable NSError *)error;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didStopWithParticipantID:(NSString *)participantID error:(nullable NSError *)error;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didReceiveInvitationFromParticipantID:(NSString *)participantID callID:(NSInteger)callID;

@end

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKEventListener.h
//
//  GKEventListener.h
//  Game Center
//
//  Copyright 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GKPlayer, GKChallenge;

NS_ASSUME_NONNULL_BEGIN
@protocol GKChallengeListener <NSObject>
@optional

// Called when a player starts the game with the intent of playing a challenge, or intends to play a challenge after selecting it within the in-game Game Center UI.
// player: The player who selected the challenge
// challenge: The challenge which was selected
- (void)player:(GKPlayer *)player wantsToPlayChallenge:(GKChallenge *)challenge NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

// Called when a player has received a challenge, triggered by a push notification from the server. Received only while the game is running.
// player: The player who received the challenge
// challenge: The challenge which was received
- (void)player:(GKPlayer *)player didReceiveChallenge:(GKChallenge *)challenge NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

// Called when a player has completed a challenge, triggered while the game is running, or when the user has tapped a challenge notification banner while outside of the game.
// player: The player who completed the challenge
// challenge: The challenge which the player completed
// friendPlayer: The friend who sent the challenge originally
- (void)player:(GKPlayer *)player didCompleteChallenge:(GKChallenge *)challenge issuedByFriend:(GKPlayer *)friendPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

// Called when a player's friend has completed a challenge which the player sent to that friend. Triggered while the game is running, or when the user has tapped a challenge notification banner while outside of the game.
// player: The player who sent the challenge originally
// challenge: The challenge which the player created and sent
// friendPlayer: The friend who completed the challenge
- (void)player:(GKPlayer *)player issuedChallengeWasCompleted:(GKChallenge *)challenge byFriend:(GKPlayer *)friendPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKFriendRequestComposeViewController.h
//
//  GKFriendRequestComposeViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKFriendRequestComposeViewControllerDelegate;
@class GKPlayer;


// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0) 
@interface GKFriendRequestComposeViewController : UINavigationController
@end
#else
#import <GameCenterUICore/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0)
@interface GKFriendRequestComposeViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKFriendRequestComposeViewControllerDelegate> _composeViewDelegateWeak;
    id _initialState;
    BOOL _internalFlag;
}
@end
#endif

@interface GKFriendRequestComposeViewController ()
// Get the maximum number of recipients permitted
+ (NSUInteger)maxNumberOfRecipients;

// Specify the message sent to the invitee. A default message will be used if you don't specify one.
- (void)setMessage:(nullable NSString *)message;

// Add recipients to the request.
// If you don't specify at least one recipient before presenting the view, the recipients field will be made firstResponder, to encourage the user to add some.
// If you add more than maxNumberOfRecipients recipients, these methods will throw an exception.
- (void)addRecipientPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);
- (void)addRecipientsWithPlayerIDs:(NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_2, 8_0, "use addRecipientPlayers:") ;
- (void)addRecipientsWithEmailAddresses:(NSArray<NSString *> *)emailAddresses;

@property (nonatomic, assign, nullable) id<GKFriendRequestComposeViewControllerDelegate> composeViewDelegate NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) ;
@end

// Optional delegate
NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) 
@protocol GKFriendRequestComposeViewControllerDelegate
// The compose view has finished
- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController *)viewController NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) ;
@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKPeerPickerController.h
/*
 GKPeerPickerController.h
 Game Kit
 
 Copyright 2010 Apple Inc. All rights reserved.
 
 This API provides a system-supplied user interface for selecting and connecting to another device for a multiplayer game.  The API introduces GKPeerPickerController for this purpose, and should be used in conjunction with the GKSession API.
 
 This a not a Game Center feature. To support Game Center and online play, see GKMatchMatchmakerViewController.
 */

#import <GameKit/GKSession.h>

// This a not a Game Center feature. To support Game Center and online play, see GKMatchMatchmakerViewController.
@class GKPeerPickerController;

/* Connection types
 */
typedef NS_ENUM(NSUInteger, GKPeerPickerConnectionType)
{
	GKPeerPickerConnectionTypeOnline = 1 << 0,		// Online (Internet) based multiplayer connection
	GKPeerPickerConnectionTypeNearby = 1 << 1		// Nearby (Bluetooth) based multiplayer connection
} NS_ENUM_DEPRECATED_IOS(3_0, 7_0);

NS_ASSUME_NONNULL_BEGIN

/* callbacks to the GKPeerPickerController delegate
 */
NS_DEPRECATED_IOS(3_0, 7_0, "Use MCBrowserViewController along with MCBrowserViewControllerDelegate from the MultipeerConnectivity framework") 
@protocol GKPeerPickerControllerDelegate <NSObject>

@optional

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
/* Notifies delegate that a connection type was chosen by the user.
 */
- (void)peerPickerController:(GKPeerPickerController *)picker didSelectConnectionType:(GKPeerPickerConnectionType)type ;

/* Notifies delegate that the connection type is requesting a GKSession object.
 
 You should return a valid GKSession object for use by the picker. If this method is not implemented or returns 'nil', a default GKSession is created on the delegate's behalf.
 */

- (GKSession *)peerPickerController:(GKPeerPickerController *)picker sessionForConnectionType:(GKPeerPickerConnectionType)type ;

/* Notifies delegate that the peer was connected to a GKSession.
 */
- (void)peerPickerController:(GKPeerPickerController *)picker didConnectPeer:(NSString *)peerID toSession:(GKSession *)session ;
#pragma clang diagnostic pop

/* Notifies delegate that the user cancelled the picker.
 */
- (void)peerPickerControllerDidCancel:(GKPeerPickerController *)picker ;

@end


/* The GKPeerPickerController class manages the system-supplied user interface for choosing peers to connect with for multiplayer games. The class manages the actual user interactions with the views and reports the results of those interactions to your delegate object.
 
 Because the GKPeerPickerController class handles all of the user interactions, all you have to do is tell it which GKSession selected peers should be connected to, tell it to start, and then wait to receive a delegate callback when the picker finished connecting peers or cancels.
 
 You must provide a delegate that conforms to the GKPeerPickerControllerDelegate protocol in order to use this class. After the user interface starts, this class notifies your delegate of the user’s actions.
 */
NS_CLASS_DEPRECATED_IOS(3_0, 7_0, "Use MCBrowserViewController from the MultipeerConnectivity framework") 
@interface GKPeerPickerController : NSObject {
@private
	id _picker;
}

/* An integer bit mask that determines what connection types are supported by the application, and displays system-supplied UI as appropriate. 
 
 This mask can be specified by combining, using the C bitwise OR operator, any of the options described in GKPickerConnectionType. If not set, the default supported type is GKPickerConnectionTypeNearby.  If multiple connection types are supported, system-supplied UI will be presented to allow the user to select a connection type. The delegate receives a -peerPickerController:didSelectConnectionType: callback when the user selects a connection type.  If desired, this property should be set prior to calling -show, and should not be set while the picker is visible.
 */
@property(nonatomic, assign) GKPeerPickerConnectionType connectionTypesMask;

/* The delegate receives notifications when the user interacts with the picker interface. If this property is nil, the picker is dismissed immediately if you try to show it.
 */
@property(nonatomic, nullable, assign) id<GKPeerPickerControllerDelegate> delegate NS_DEPRECATED_IOS(3_0, 7_0) ;

/* Show the picker.
 */
- (void)show;

/* Dismiss the picker.
 */
- (void)dismiss;

@property(nonatomic,readonly,getter=isVisible) BOOL visible;

@end

NS_ASSUME_NONNULL_END// ==========  GameKit.framework/Headers/GKSavedGame.h
//
//  GKSavedGame.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <GameKit/GKLocalPlayer.h>
#import <GameKit/GKSavedGameListener.h>

// Class representing a saved game for the local player, or a version of a saved game when in conflict
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED 
@interface GKSavedGame : NSObject <NSCopying>

NS_ASSUME_NONNULL_BEGIN

@property (atomic, nullable, readonly) NSString *name NS_AVAILABLE(10_10, 8_0);
@property (atomic, nullable, readonly) NSString *deviceName NS_AVAILABLE(10_10, 8_0);
@property (atomic, nullable, readonly) NSDate *modificationDate NS_AVAILABLE(10_10, 8_0);

// Asynchronously load the data for this saved game. The completion handler is called with loaded data or an error.
- (void)loadDataWithCompletionHandler:(void(^__nullable)(NSData * __nullable data, NSError * __nullable error))handler NS_AVAILABLE(10_10, 8_0);

@end

#if !TARGET_OS_WATCH && !TARGET_OS_TV
@interface GKLocalPlayer (GKSavedGame) <GKSavedGameListener>

// Asynchronously fetch saved games. The handler is called with an array of GKSavedGame objects or an error.
// If there is more than one saved game with the same name then a conflict exists. The application should determine the correct data to use and call resolveConflictingSavedGames:withData:completionHandler:. This may require data merging or asking the user.
- (void)fetchSavedGamesWithCompletionHandler:(void(^__nullable)(NSArray<GKSavedGame *> * __nullable savedGames, NSError * __nullable error))handler NS_AVAILABLE(10_10, 8_0)  ;

// Asynchronously save game data. If a saved game with that name already exists it is overwritten, otherwise a new one is created. The completion handler is called with the new / modified GKSavedGame or an error.
// If the saved game was in conflict then the overwritten version will be the one with the same deviceName if present, otherwise the most recent overall.
- (void)saveGameData:(NSData *)data withName:(NSString *)name completionHandler:(void(^__nullable)(GKSavedGame * __nullable savedGame, NSError * __nullable error))handler NS_AVAILABLE(10_10, 8_0) ;

// Asynchronously delete saved games with the given name. The completion handler will indicate whether or not the deletion was successful.
- (void)deleteSavedGamesWithName:(NSString *)name completionHandler:(void(^__nullable)(NSError * __nullable error))handler NS_AVAILABLE(10_10, 8_0) ;

// Asynchronously resolve a saved game conflict. This deletes all versions included in conflictingSavedGames and creates a new version with the given data. The completion handler is called with the newly created save and all other remaining versions or an error.
- (void)resolveConflictingSavedGames:(NSArray<GKSavedGame *> *)conflictingSavedGames withData:(NSData *)data completionHandler:(void(^__nullable)(NSArray<GKSavedGame *> * __nullable savedGames, NSError * __nullable error))handler NS_AVAILABLE(10_10, 8_0) ;

@end
#endif

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKVoiceChatService.h
/*
  GKVoiceChatService.h

  Copyright 2010 Apple Inc. All rights reserved.
 
 This service is useful for setting up a voice chat in two cases.
 1) You have a server that connects two clients, but you have no way of establishing a peer-to-peer channel.
    An example of this case is if you had an xmpp (jabber) client, and wanted to add voice chat.

 2) Or, you already have a peer-to-peer application that you want to add voice chat to.  
    For instance, most networked games are peer-to-peer.  You could add voice chat to your game using this class.
 
 This a not a Game Center feature. To support voice chat as part of Game Center online play, see GKVoiceChat.
 
 Implementation example for an application that has a peer-to-peer channel established already.
 
 PeerToPeerHockeyClient<VoiceChatClient, VoiceChatPeerToPeerChannel> hockeyClientA;
 
 vcService = [GKVoiceChatService defaultVoiceChatService];
 vcService.client = hockeyClientA;
 
 *** During the init, the GKVoiceChatService will check to see if the -sendRealTimeData:toParticipantID: method is implemented by the client.
     The Voice Chat Service will first attempt to negotiate its own connection, and then use the hockeyClient tunnel if it fails.
 
 *** some time later the hockeyClient with participantID A connects p2p with hockeyClient with participantID B.
 

 *** A wants to set up a voice chat with @"B"
 [vcService startVoiceChatWithParticipantID: @"B" error: nil];

 *** The vcService will then sendData using the VoiceChatClient protocol method.
 [client sendData:inviteData toParticipantID:@"B"]
 
 *** When B receives the data it passes it down to B's vcService 
 [hockeyClientB.vcService receivedData:data fromParticipantID:@"A"]
 
 *** vcService will inform its VoiceChatClient (hockeyClientB) that it recevied the invite
 [client voiceChatService:self receivedVoiceChatInvitationFromParticipantID:@"A" callID: 123]

 *** B accepts the connection and calls:
 
 [hockeyClientB.vcService acceptCallID: (NSInteger) 123 error:NULL];

 *** The GKVoiceChatService establishes a voice chat and informs the hockey client of a successful voice chat session***
 [clientA voiceChatService:self didStartWithParticipantID:@"B"];
 [clientB voiceChatService:self didStartWithParticipantID:@"A"];

 As the voice chat service generates audio it will call
 
 [clientA sendRealTimeData:audio toParticipant:@"B"];
 [clientB sendRealTimeData:audio toParticipant:@"A"];
 


 Implementation examples for an application that has uses a server to establish connections between clients and wants to add peer-to-peer voice chat.  We'll use an XMPP chat client as an example.
 
 XMPPClient<VoiceChatClient, VoiceChatPeerToPeerChannel> xmppClientA;
 
 vcService = [GKVoiceChatService defaultVoiceChatService];
 vcService.client = xmppClientA;
 
 *** During the init, the GKVoiceChatService will check to see if @selector(sendRealTimeData:toParticipant:) method is implemented by the client.
 The Voice Chat Service will know to negotiate its own Peer To Peer channel since our xmpp client does not implement this method.
 
 *** Assume the xmppClient has a jabber id of clientA@jabber.foo.org and wants to start a voice chat with clientB@jabber.foo.org ***
 
 [xmppClientA.vcService startVoiceChatWithParticipantID: @"clientB@jabber.foo.org"];
 
 *** The Voice Chat Service will then try to send necessary connection info to clientB@jabber.foo.org using the server channel that the XMPP client implements.
 
 [client voiceChatService:self sendData:(NSData *) data toParticipantID: clientB@jabber.foo.org ];
 
 *** xmppClientA will implement the sendConnectionData like this
 
 [xmppClientA wrapAndSendData:(NSData *) data toJid: clientB@jabber.foo.org]
 
 *** On the remote side the xmppClient for clientB@jabber.foo.org should 
 
 NSData *serviceData [xmppClientB unwrapData:(NSData *) data fromJid: clientB@jabber.foo.org]
 [xmppClientB.vcService receivedData: serviceData fromParticipantID:participant];
 
 *** Upon receiving this connection data.  vcServiceForXMPPClientB will do the following:
 [client voiceChatService:self receivedVoiceChatInvitationFromParticipant: clientA@jabber.foo.org callID: 1]
 
 *** Client B will then pop up a dialog.  The user will choose to accept.  So B will notifiy the voice chat service.
 [xmppClientB.vcService acceptConnection: (callid)];
 
 *** The voice chat service on both sides will attempt to establish a peer-to-peer connection.  If they are successful then both voice chat services will call
 [client voiceChatService: self didStartWithParticipantID:@"clientB(orA)@jabber.foo.org]
 
 The sending and receiving of audio is then done transparently by the GKVoiceChatService.
 
*/

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKPublicProtocols.h>

// This a not a Game Center feature. To support voice chat as part of Game Center online play, see GKVoiceChat.
@class GKVoiceChatService;

// GKVoiceChatService provides voice chat capabilities depending on your networking situation.
NS_CLASS_DEPRECATED_IOS(3_0, 7_0, "Use GKVoiceChat instead") 
@interface GKVoiceChatService : NSObject {
    @private
    id _voiceChatService;
}

+ (GKVoiceChatService *)defaultVoiceChatService;

+ (BOOL)isVoIPAllowed;

@property(assign) id<GKVoiceChatClient> client NS_DEPRECATED_IOS(3_0, 7_0) ;

// May fail if you already in a chat, or if there is no peer-to-peer channel that can be made to the participant.
- (BOOL)startVoiceChatWithParticipantID:(NSString *)participantID error:(NSError **)error;

- (void)stopVoiceChatWithParticipantID:(NSString *)participantID;

//callID is returned by didReceiveInvitationFromParticipantID call. An error may occur if there can be no viable connection made to the remote participant.
- (BOOL)acceptCallID:(NSInteger)callID error:(NSError **)error;

//callID is returned by didReceiveInvitationFromParticipantID call.
- (void)denyCallID:(NSInteger)callID;

// will only be called by the client if the client has a pre-established peer-to-peer UDP connection.  Used to receive audio.
- (void)receivedRealTimeData:(NSData *)audio fromParticipantID:(NSString *)participantID;

// will be called by the client otherwise.
- (void)receivedData:(NSData *)arbitraryData fromParticipantID:(NSString *)participantID;

@property(nonatomic, getter=isMicrophoneMuted) BOOL microphoneMuted;  // default is NO

// Applies a value to raise or lower the voice of the remote peer.
@property(nonatomic) float remoteParticipantVolume; //default 1.0 (max is 1.0, min is 0.0)

// set to YES if you want to use the outputMeterLevel to implement a meter for the output signal.
@property(nonatomic, getter=isOutputMeteringEnabled) BOOL outputMeteringEnabled; //default NO

// set to YES if you want to use the inputMeterLevel to implement a meter for the input (microphone) signal.
@property(nonatomic, getter=isInputMeteringEnabled) BOOL inputMeteringEnabled;  //default NO

// A value in dB to indicate how loud the other participants are at this moment in time.
@property(readonly) float outputMeterLevel;  //changes frequently as the far-end participant speaks

// A value in dB to indicate how loud the the near-end participant is speaking
@property(readonly) float inputMeterLevel;  //changes frequently as the near-end participant speaks

@end

GK_EXTERN_WEAK    NSString *  const GKVoiceChatServiceErrorDomain;

// ==========  GameKit.framework/Headers/GKAchievement.h
//
//  GKAchievement.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

@class GKPlayer;


NS_ASSUME_NONNULL_BEGIN
// GKAchievement represents a game achievement that the player has started or completely achieved.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)

@interface GKAchievement : NSObject <NSCoding, NSSecureCoding>

// Asynchronously load all achievements for the local player
+ (void)loadAchievementsWithCompletionHandler:(void (^ __nullable)(NSArray<GKAchievement *> * __nullable achievements, NSError * __nullable error))completionHandler;

// Reset the achievements progress for the local player. All the entries for the local player are removed from the server. Error will be nil on success.
//Possible reasons for error:
// 1. Local player not authenticated
// 2. Communications failure
+ (void)resetAchievementsWithCompletionHandler:(void(^ __nullable)(NSError * __nullable error))completionHandler;

// Designated initializer
- (instancetype)initWithIdentifier:(nullable NSString *)identifier;

// Initialize the achievement for a specific player. Use to submit participant achievements when ending a turn-based match.
- (instancetype)initWithIdentifier:(nullable NSString *)identifier player:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);


// Report an array of achievements to the server. Percent complete is required. Points, completed state are set based on percentComplete. isHidden is set to NO anytime this method is invoked. Date is optional. Error will be nil on success.
// Possible reasons for error:
// 1. Local player not authenticated
// 2. Communications failure
// 3. Reported Achievement does not exist
+ (void)reportAchievements:(NSArray<GKAchievement *> *)achievements withCompletionHandler:(void(^ __nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0);


@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;                     // Achievement identifier
@property(assign, NS_NONATOMIC_IOSONLY) double percentComplete;                 // Required, Percentage of achievement complete.
@property(readonly, getter=isCompleted, NS_NONATOMIC_IOSONLY) BOOL completed;   // Set to NO until percentComplete = 100.
@property(copy, readonly, NS_NONATOMIC_IOSONLY) NSDate *lastReportedDate;       // Date the achievement was last reported. Read-only. Created at initialization

@property(assign, NS_NONATOMIC_IOSONLY) BOOL showsCompletionBanner NS_AVAILABLE(10_8, 5_0);             // A banner will be momentarily displayed after reporting a completed achievement

// The identifier of the player that earned the achievement.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY) GKPlayer *player NS_AVAILABLE(10_10, 8_0);

@end

@interface GKAchievement (Deprecated)

- (void)reportAchievementWithCompletionHandler:(void(^ __nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use +reportAchievements:withCompletionHandler:") ;
- (instancetype)initWithIdentifier:(nullable NSString *)identifier forPlayer:(NSString *)playerID NS_DEPRECATED_IOS(7_0, 8_0, "use initWithIdentifier:player:") ;
@property(assign, getter=isHidden, readonly, NS_NONATOMIC_IOSONLY) BOOL hidden NS_DEPRECATED(10_8, 10_10, 4_1, 6_0, "Use isHidden on the GKAchievementDescription class instead") ;
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *playerID NS_DEPRECATED_IOS(7_0, 8_0, "use player") ;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKTurnBasedMatchmakerViewController.h
//
//  GKTurnBasedMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

@class GKMatchmakerViewController, GKTurnBasedMatch, GKMatchRequest;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

// View controller to manage turn-based matches, invite friends and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h> // NS_ASSUME_NONNULL_BEGIN
#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameCenterUICore/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKTurnBasedMatchmakerViewControllerDelegate> __weak _turnBasedMatchmakerDelegate;
    GKMatchRequest *_matchRequest;
    BOOL _showExistingMatches;
    BOOL _internalFlag;
}
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (nonatomic, nullable, readwrite, weak) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; // defaults to YES

- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 5_0);

// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 5_0);


@optional

// Deprecated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_11, 5_0, 9_0, "use GKTurnBasedEventListener player:receivedTurnEventForMatch:didBecomeActive:") ;

// Deprectated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_11, 5_0, 9_0, "use GKTurnBasedEventListener player:wantsToQuitMatch:") ;

@end

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKVoiceChat.h
//
//  GKVoiceChat.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, GKVoiceChatPlayerState) {
    GKVoiceChatPlayerConnected,
    GKVoiceChatPlayerDisconnected,
    GKVoiceChatPlayerSpeaking,
    GKVoiceChatPlayerSilent,
    GKVoiceChatPlayerConnecting
};

@class GKPlayer;


NS_ASSUME_NONNULL_BEGIN
// GKVoiceChat represents an instance of a named voice communications channel
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKVoiceChat : NSObject

- (void)start;  // start receiving audio from the chat
- (void)stop;   // stop receiving audio from the chat

- (void)setPlayer:(GKPlayer *)player muted:(BOOL)isMuted NS_AVAILABLE(10_10, 8_0);

@property(copy, NS_NONATOMIC_IOSONLY) void(^playerVoiceChatStateDidChangeHandler)(GKPlayer *player, GKVoiceChatPlayerState state) NS_AVAILABLE(10_10, 8_0);

@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;  // name the chat was created with
@property(assign, getter=isActive, NS_NONATOMIC_IOSONLY)    BOOL active; // make this session active and route the microphone
@property(assign, NS_NONATOMIC_IOSONLY) float volume; // default 1.0 (max is 1.0, min is 0.0)

@property(readonly, NS_NONATOMIC_IOSONLY) NSArray<GKPlayer *> *players NS_AVAILABLE(10_10, 8_0); // array of GKPlayer *

+ (BOOL)isVoIPAllowed;

@end

@interface GKVoiceChat (Deprecated)

@property(readonly, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *playerIDs NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use players") ;
@property(copy, NS_NONATOMIC_IOSONLY) void(^playerStateUpdateHandler)(NSString *playerID, GKVoiceChatPlayerState state) NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use setPlayerVoiceChatStateDidChangeHandler:") ;

- (void)setMute:(BOOL)isMuted forPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use setPlayer:muted:") ;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKSession.h
/*
 GKSession.h
 GameKit
 
 Copyright 2010 Apple Inc. All rights reserved.
 
 The Game Connectivity Kit (GCK) is a framework for handling connectivity and data transport in multiplayer network games.  
 
 With the GCK API, a developer can setup a game network, which consists of players connected to each other for a game.  The API supports setting up and connecting a client/server game, or a peer-to-peer game (any peer can be the game server).
 
 This a not a Game Center feature. To support Game Center and online play, see GKMatch.
*/

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKPublicProtocols.h>

/* The GKSession handles networking between peers for a game, which includes establishing and maintaining connections over a game network, and network data transport.
 
 This a not a Game Center feature. To support Game Center and online play, see GKMatch.
*/
NS_CLASS_DEPRECATED(10_8, 10_10, 3_0, 7_0, "Use MCSession from the MultipeerConnectivity framework instead") 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@interface GKSession : NSObject {
#pragma clang diagnostic pop
@private
    id _session;
}

/* Creating a GKSession requires a unique identifier, sessionID, and mode.  All instances of the application must have the same sessionID in order to be able to join a game network.  Additionally, the GKSession requires a name, which is used to identify the specific instances of the application.

If sessionID = nil then the GKSession will use the app bundle identifier.
If name = nil then GKSession will use the device name.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (id)initWithSessionID:(NSString *)sessionID displayName:(NSString *)name sessionMode:(GKSessionMode)mode NS_DEPRECATED(10_8, 10_10, 3_0, 7_0);
#pragma clang diagnostic pop

@property(assign) id<GKSessionDelegate> delegate NS_DEPRECATED(10_8, 10_10, 3_0, 7_0) ;

@property(readonly) NSString *sessionID;
@property(readonly) NSString *displayName;
@property(readonly) GKSessionMode sessionMode NS_DEPRECATED(10_8, 10_10, 3_0, 7_0);
@property(readonly) NSString *peerID;            // session's peerID

/* Toggle availability on the network based on session mode and search criteria.  Delegate will get a callback -session:didReceiveConnectionRequestFromPeer: when a peer attempts a connection.
*/
@property(getter=isAvailable) BOOL available;

/* The timeout for disconnecting a peer if it appears that the peer has lost connection to the game network 
*/
@property(assign) NSTimeInterval disconnectTimeout; // default is 20 seconds

/* Return the application chosen name of a specific peer
*/
- (NSString *)displayNameForPeer:(NSString *)peerID;

/* Asynchronous delivery of data to one or more peers.  Returns YES if delivery started, NO if unable to start sending, and error will be set.  Delivery will be reliable or unreliable as set by mode.
*/
- (BOOL)sendData:(NSData *) data toPeers:(NSArray *)peers withDataMode:(GKSendDataMode)mode error:(NSError **)error NS_DEPRECATED(10_8, 10_10, 3_0, 7_0);

/* Asynchronous delivery to all peers.  Returns YES if delivery started, NO if unable to start sending, and error will be set.  Delivery will be reliable or unreliable as set by mode.
*/
- (BOOL)sendDataToAllPeers:(NSData *) data withDataMode:(GKSendDataMode)mode error:(NSError **)error NS_DEPRECATED(10_8, 10_10, 3_0, 7_0);    // errors: buffer full, data too big

/* Set the handler to receive data sent from remote peers.
*/
- (void)setDataReceiveHandler:(id)handler withContext:(void *)context;  // SEL = -receiveData:fromPeer:inSession:context:

/* Attempt connection to a remote peer.  Remote peer gets a callback to -session:didReceiveConnectionRequestFromPeer:.  

Success results in a call to delegate -session:peer:didChangeState: GKPeerStateConnected
Failure results in a call to delegate -session:connectionWithPeerFailed:withError:
*/
- (void)connectToPeer:(NSString *)peerID withTimeout:(NSTimeInterval)timeout;
- (void)cancelConnectToPeer:(NSString *)peerID;

/* Methods to accept or deny a prior connection request from -session:didReceiveConnectionRequestFromPeer:
*/
- (BOOL)acceptConnectionFromPeer:(NSString *)peerID error:(NSError **)error;    // errors: cancelled, or timeout
- (void)denyConnectionFromPeer:(NSString *)peerID;

/* Disconnect a peer from the session (the peer gets disconnected from all connected peers).
*/
- (void)disconnectPeerFromAllPeers:(NSString *)peerID;

/* Disconnect local peer
*/
- (void)disconnectFromAllPeers;

/* Returns peers according to connection state
*/ 
- (NSArray *)peersWithConnectionState:(GKPeerConnectionState)state NS_DEPRECATED(10_8, 10_10, 3_0, 7_0);
@end
// ==========  GameKit.framework/Headers/GKGameSessionEventListener.h
//
//  GKGameSessionEventListener.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import "GKGameSession.h"
NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("Use GKLocalPlayerListener for multiplayer event notifications.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos)
@protocol GKGameSessionEventListener <NSObject>
@optional
- (void)session:(GKGameSession *)session didAddPlayer:(GKCloudPlayer *)player;
- (void)session:(GKGameSession *)session didRemovePlayer:(GKCloudPlayer *)player;
- (void)session:(GKGameSession *)session player:(GKCloudPlayer *)player didChangeConnectionState:(GKConnectionState)newState;
- (void)session:(GKGameSession *)session player:(GKCloudPlayer *)player didSaveData:(NSData *)data;
- (void)session:(GKGameSession *)session didReceiveData:(NSData *)data fromPlayer:(GKCloudPlayer *)player;
- (void)session:(GKGameSession *)session didReceiveMessage:(NSString *)message withData:(NSData *)data fromPlayer:(GKCloudPlayer *)player;

@end

@interface GKGameSession (GKGameSessionEventListener)
+ (void)addEventListener:(NSObject<GKGameSessionEventListener> *)listener NS_SWIFT_NAME(add(listener:)) API_DEPRECATED("Use GKLocalPlayer's registerListener: to register for GKLocalPlayerListener event notifications.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);
+ (void)removeEventListener:(NSObject<GKGameSessionEventListener> *)listener NS_SWIFT_NAME(remove(listener:)) API_DEPRECATED("Use GKLocalPlayer's unregisterListener: or unregisterAllListeners to unregister from GKLocalPlayerListener event notifications.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);
@end

NS_ASSUME_NONNULL_END

// ==========  GameKit.framework/Headers/GKSavedGameListener.h
//
//  GKSavedGameListener.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/NSObjCRuntime.h> // NS_ASSUME_NONNULL_BEGIN
#import <objc/NSObject.h> // NSObject

@class NSArray;
@class GKPlayer;
@class GKSavedGame;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED 
@protocol GKSavedGameListener <NSObject>
@optional

// Called when a player’s saved game data has been modified.
- (void)player:(GKPlayer *)player didModifySavedGame:(GKSavedGame *)savedGame NS_AVAILABLE(10_10, 8_0) ;

// Called when a conflict has arisen between different versions of the same saved game. This can happen when multiple devices write to the same saved game while one or more is offline. The application should determine the correct data to use, then call resolveConflictingSavedGames:withData:completionHandler:. This may require data merging or asking the user.
- (void)player:(GKPlayer *)player hasConflictingSavedGames:(NSArray<GKSavedGame *> *)savedGames NS_AVAILABLE(10_10, 8_0) ;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKAchievementDescription.h
//
//  GKAchievementDescription.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>


NS_ASSUME_NONNULL_BEGIN
// GKAchievementDescription is a full description of the achievement as defined before app submission in iTunes Connect.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKAchievementDescription : NSObject <NSCoding, NSSecureCoding>

// Asynchronously load all achievement descriptions
+ (void)loadAchievementDescriptionsWithCompletionHandler:(void(^ __nullable)(NSArray<GKAchievementDescription *> * __nullable descriptions,NSError * __nullable error))completionHandler;

@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;
@property(nonatomic, retain, nullable, readonly) NSString *groupIdentifier NS_AVAILABLE(10_8, 6_0);       // The group identifier for the achievement, if one exists.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *title;                 // The title of the achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *achievedDescription;   // The description for an unachieved achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *unachievedDescription; // The description for an achieved achievement.
@property(assign, readonly, NS_NONATOMIC_IOSONLY) NSInteger maximumPoints;         // Maximum points available for completing this achievement.
@property(getter = isHidden, assign, readonly, NS_NONATOMIC_IOSONLY) BOOL hidden;  // Whether or not the achievement should be listed or displayed if not yet unhidden by the game.
@property(nonatomic, getter = isReplayable, assign, readonly) BOOL replayable  NS_AVAILABLE(10_8, 6_0);  // Whether or not the achievement will be reported by the game when the user earns it again. This allows the achievement to be used for challenges when the recipient has previously earned it.
@end
NS_ASSUME_NONNULL_END

#if TARGET_OS_IPHONE
@class UIImage;
#else
@class NSImage;
#endif

#import <GameKit/GKAchievementDescription.h>

@interface GKAchievementDescription (UI)

#if TARGET_OS_IPHONE

// Image for completed achievement. Not valid until loadImage: has completed. Deprecated -- use loadImageWithCompletionHandler: instead.
@property(nonatomic, retain, readonly, nullable) UIImage *image NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use loadImageWithCompletionHandler: instead");

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler;
#else

// Image for completed achievement. Not valid until loadImage: has completed. Deprecated -- use loadImageWithCompletionHandler: instead.
@property(atomic, retain, readonly, nullable) NSImage *image __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_NA, __IPHONE_4_1, __IPHONE_7_0);

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler;
#endif

#if TARGET_OS_IPHONE

// The default image for any incomplete achievement
+ (nonnull UIImage *)incompleteAchievementImage;

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull UIImage *)placeholderCompletedAchievementImage;

#else

// The default image for any incomplete achievement
+ (nonnull NSImage *)incompleteAchievementImage;

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull NSImage *)placeholderCompletedAchievementImage;

#endif

@end


// ==========  GameKit.framework/Headers/GKLocalPlayer.h
//
//  GKLocalPlayer.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKPlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKEventListener.h>
#import <GameKit/GKTurnBasedMatch.h>
#import <GameKit/GKMatchmaker.h>
#import <GameKit/GKSavedGameListener.h>

#if TARGET_OS_IPHONE
@class UIViewController;
#else
@class NSViewController;
#endif

typedef NS_ENUM(NSUInteger, GKAuthenticationType) {
    GKAuthenticatingWithoutUI                = 0,
    GKAuthenticatingWithGreenBuddyUI         = 1,    // need to accept T&C
    GKAuthenticatingWithAuthKitInvocation    = 2,    // no account
};


NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKLocalPlayer : GKPlayer

// Obtain the primary GKLocalPlayer object.
// The player is only available for offline play until logged in.
// A temporary player is created if no account is set up.
@property (class, readonly, nonnull) GKLocalPlayer *local;

// TODO: deprecate this <rdar://problem/42128153> Swiftification: Should update objective C APIs to match our changes in swift (GKLocalPlayere.localPlayer -> local, nullability, lightweight generics)
@property (class, readonly, nonnull) GKLocalPlayer *localPlayer;

@property(readonly, getter=isAuthenticated, NS_NONATOMIC_IOSONLY)  BOOL authenticated; // Authentication state
@property(readonly, getter=isUnderage, NS_NONATOMIC_IOSONLY)       BOOL underage;      // Underage state

// A Boolean value that declares whether or not multiplayer gaming is restricted on this device.
@property(readonly, getter=isMultiplayerGamingRestricted, nonatomic) BOOL multiplayerGamingRestricted API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

// The authenticate handler will be called whenever the authentication process finishes or needs to show UI. The handler may be called multiple times. Authentication will happen automatically when the handler is first set and whenever the app returns to the foreground.
// If the authentication process needs to display UI the viewController property will be non-nil. Your application should present this view controller and continue to wait for another call of the authenticateHandler.  The view controller will be dismissed automatically.
// Possible reasons for error:
// 1. Communications problem
// 2. User credentials invalid
// 3. User cancelled
#if TARGET_OS_WATCH
@property(atomic, nullable, copy) void(^authenticateHandler)(NSError * __nullable error) __WATCHOS_AVAILABLE(3_0);
#elif TARGET_OS_IPHONE
@property(nonatomic, nullable, copy) void(^authenticateHandler)(UIViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_IOS(6_0);
#else
@property(atomic, nullable, copy) void(^authenticateHandler)(NSViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_MAC(10_9);
#endif

// Asynchronously load the recent players list as an array of GKPlayer.  A recent player is someone that you have played a game with or is a legacy game center friend.  Calls completionHandler when finished. Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadRecentPlayersWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable recentPlayers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 10_0) __WATCHOS_AVAILABLE(3_0);
;

// Asynchronously load the challengable friends list as an array of GKPlayer.  A challengable player is a friend player with friend level FL1 and FL2.  Calls completionHandler when finished. Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadChallengableFriendsWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable challengableFriends, NSError * __nullable error))completionHandler;


// Set the default leaderboard for the current game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
- (void)setDefaultLeaderboardIdentifier:(NSString *)leaderboardIdentifier completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


// Load the default leaderboard identifier for the local player
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
- (void)loadDefaultLeaderboardIdentifierWithCompletionHandler:(void(^__nullable)(NSString * __nullable leaderboardIdentifier, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


// Generates a signature allowing 3rd party server to authenticate the GKLocalPlayer
//Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)generateIdentityVerificationSignatureWithCompletionHandler:(void (^__nullable)(NSURL * __nullable publicKeyUrl, NSData * __nullable signature, NSData * __nullable salt, uint64_t timestamp, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

@end

#if TARGET_OS_WATCH
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener>
@end
#elif TARGET_OS_TV
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener>
@end
#else
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener, GKSavedGameListener>
@end
#endif

@interface GKLocalPlayer (GKLocalPlayerEvents)

// A single listener may be registered once. Registering multiple times results in undefined behavior. The registered listener will receive callbacks for any selector it responds to.
- (void)registerListener:(id<GKLocalPlayerListener>)listener NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

- (void)unregisterListener:(id<GKLocalPlayerListener>)listener NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

- (void)unregisterAllListeners NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

@end

// Notification will be posted whenever authentication status changes.
GK_EXTERN NSNotificationName GKPlayerAuthenticationDidChangeNotificationName NS_AVAILABLE(10_8, 4_1);

@interface GKLocalPlayer (Deprecated)

- (void)setDefaultLeaderboardCategoryID:(nullable NSString *)categoryID completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0,"Use setDefaultLeaderboardIdentifier:completionHandler: instead") ;
- (void)loadDefaultLeaderboardCategoryIDWithCompletionHandler:(void(^__nullable)(NSString * __nullable categoryID, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0,"Use loadDefaultLeaderboardIdentifierWithCompletionHandler: instead") ;
- (void)loadFriendsWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable friendIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use loadRecentPlayersWithCompletionHandler: instead") ;
- (void)authenticateWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_8, 4_1, 6_0, "Set the authenticateHandler instead") ;

@property(nonatomic, readonly, nullable, retain) NSArray<NSString *> *friends NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use loadFriendPlayersWithCompletionHandler: instead") ; // Array of player identifiers of friends for the local player. Not valid until loadFriendsWithCompletionHandler: has completed.

- (void)loadFriendPlayersWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable friendPlayers, NSError * __nullable error))completionHandler NS_DEPRECATED(10_10, 10_11, 8_0, 10_0);

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKError.h
//
//  GKError.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

GK_EXTERN_WEAK NSString * __nonnull GKErrorDomain;

typedef NS_ENUM(NSInteger, GKErrorCode) {
    GKErrorUnknown                              = 1,
    GKErrorCancelled                            = 2,
    GKErrorCommunicationsFailure                = 3,
    GKErrorUserDenied                           = 4,
    GKErrorInvalidCredentials                   = 5,
    GKErrorNotAuthenticated                     = 6,
    GKErrorAuthenticationInProgress             = 7,
    GKErrorInvalidPlayer                        = 8,
    GKErrorScoreNotSet                          = 9,
    GKErrorParentalControlsBlocked              = 10,
    GKErrorPlayerStatusExceedsMaximumLength     = 11,
    GKErrorPlayerStatusInvalid                  = 12,
    GKErrorMatchRequestInvalid                  = 13,
    GKErrorUnderage                             = 14,
    GKErrorGameUnrecognized                     = 15,
    GKErrorNotSupported                         = 16,
    GKErrorInvalidParameter                     = 17,
    GKErrorUnexpectedConnection                 = 18,
    GKErrorChallengeInvalid                     = 19,
    GKErrorTurnBasedMatchDataTooLarge           = 20,
    GKErrorTurnBasedTooManySessions             = 21,
    GKErrorTurnBasedInvalidParticipant          = 22,
    GKErrorTurnBasedInvalidTurn                 = 23,
    GKErrorTurnBasedInvalidState                = 24,
    GKErrorInvitationsDisabled                  = 25,
    GKErrorPlayerPhotoFailure                   = 26,
    GKErrorUbiquityContainerUnavailable         = 27,
    GKErrorMatchNotConnected                    = 28,
    GKErrorGameSessionRequestInvalid            = 29,
    GKErrorRestrictedToAutomatch                = 30
};

// FIXME: do we need to merge this into GKError?

GK_EXTERN_WEAK NSString *__nonnull GKTournamentErrorDomain;

typedef NS_ENUM(NSInteger, GKTournamentErrorCode) {
    GKTournamentErrorUnknown                            = 1,
    GKTournamentErrorInvalidTournament                  = 2,
    GKTournamentErrorRegistrationNotOpen                = 3,
    GKTournamentErrorPlayerNotRegistered                = 4,
    GKTournamentErrorInvalidTournamentState             = 5,
    GKTournamentErrorInvalidParticipantState            = 6,
    GKTournamentErrorAlreadyRegistered                  = 7,
    GKTournamentErrorDeviceConflict                     = 8,
    GKTournamentErrorLocalPlayerCustomTournamentLimit   = 9,
    GKTournamentErrorNotEnoughPlayers                   = 10,      // Tournament could not start because there aren't enough players
    GKTournamentErrorCheatingDetected                   = 11,      // Cheating was detected in this tournament instance
    GKTournamentErrorInvalidTryToken                    = 12,
    GKTournamentErrorNetworkError                       = 13,      // Network error

    // Below are temporary for the CloudKit prototype.
    GKTournamentErrorNotSignedIntoICloud,
    GKTournamentErrorCKServerRecordChanged,
};
// ==========  GameKit.framework/Headers/GKMatchmakerViewController.h
//
//  GKMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

@class GKMatchRequest, GKInvite, GKMatch, GKPlayer;

@protocol GKMatchmakerViewControllerDelegate;

// View controller to invite friends, respond to invites, and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h> // NS_ASSUME_NONNULL_BEGIN
#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : UINavigationController

#else
#import <GameCenterUICore/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKMatchmakerViewControllerDelegate> _matchmakerDelegateWeak;
    GKMatchRequest *_matchRequest;
    GKInvite *_acceptedInvite;
    GKMatch *_match;
    BOOL _hosted;
    BOOL _finished;
    BOOL _internalFlag;
    NSMutableArray *_hostedPlayers;
}

#endif
@property(nonatomic, nullable, assign) id<GKMatchmakerViewControllerDelegate>     matchmakerDelegate;
@property(nonatomic, readonly, strong) GKMatchRequest                   *matchRequest;
@property(nonatomic, assign, getter=isHosted) BOOL                      hosted;  // set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.

// Initialize with a matchmaking request, allowing the user to send invites and/or start matchmaking
- (nullable id)initWithMatchRequest:(GKMatchRequest *)request;

// Initialize with an accepted invite, allowing the user to see the status of other invited players and get notified when the game starts
- (nullable id)initWithInvite:(GKInvite *)invite;

// Add additional players (not currently connected) to an existing peer-to-peer match.  
// Apps should elect a single device to do this, otherwise conflicts could arise resulting in unexpected connection errors.
- (void)addPlayersToMatch:(GKMatch *)match NS_AVAILABLE(10_8, 5_0);

// Update the displayed connection status for a remote server-hosted player
- (void)setHostedPlayer:(NSString *)playerID connected:(BOOL)connected NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use setHostedPlayer:didConnect:") ;
- (void)setHostedPlayer:(GKPlayer *)player didConnect:(BOOL)connected NS_AVAILABLE(10_10, 8_0);

#if TARGET_OS_IPHONE
// Deprecated, use setHostedPlayer:connected: instead.
- (void)setHostedPlayerReady:(NSString *)playerID NS_DEPRECATED(NA, NA, 4_1, 5_0) ;
#endif

// deprecated, set the message on the match request instead
@property(nonatomic, nullable, copy) NSString *defaultInvitationMessage NS_DEPRECATED(10_8, 10_10, 5_0, 7_0) ; // default message to use when inviting friends. Can be edited by the user.

@end

@protocol GKMatchmakerViewControllerDelegate <NSObject>
@required
// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 4_1);

// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 4_1);

@optional
// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)match NS_AVAILABLE(10_8, 4_1);

// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindHostedPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use matchmakerViewController:didFindHostedPlayers:") ;

// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController hostedPlayerDidAccept:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use matchmakerViewController:hostedPlayerDidAccept:") ;
@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKGameSessionSharingViewController.h
//
//  GKGameSessionSharingViewController.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_TV

#import <UIKit/UIViewController.h> // UIViewController

@class GKGameSession;
@protocol GKGameSessionSharingViewControllerDelegate;


NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("For real-time matches, use GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewController.", tvos(10.0, 12.0))
@interface GKGameSessionSharingViewController : UIViewController
@property (nonatomic, readonly, strong) GKGameSession *session;
@property (nonatomic, weak, nullable) id<GKGameSessionSharingViewControllerDelegate> delegate;

- (instancetype)initWithSession:(GKGameSession *)session;

@end

API_DEPRECATED("For real-time matches, use GKMatchmakerViewControllerDelegate to receive notifications from the GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewControllerDelegate and GKLocalPlayerListener to receive notifications from the GKTurnBasedMatchmakerViewController.", tvos(10.0, 12.0))
@protocol GKGameSessionSharingViewControllerDelegate <NSObject>
- (void)sharingViewController:(GKGameSessionSharingViewController *)viewController didFinishWithError:(NSError * __nullable)error;
@end

NS_ASSUME_NONNULL_END


#endif
// ==========  GameKit.framework/Headers/GKLeaderboardViewController.h
//
//  GKLeaderboardViewController.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKLeaderboardViewControllerDelegate;

// View controller that provides the standard user interface for leaderboards.  Present modally from the top view controller.
NS_CLASS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@interface GKLeaderboardViewController : GKGameCenterViewController
#if !TARGET_OS_IPHONE
{
    id<GKLeaderboardViewControllerDelegate> _leaderboardDelegate;
    NSString *_category;
    GKLeaderboardTimeScope _timeScope;
}
#endif
@end

@interface GKLeaderboardViewController ()
@property (assign, NS_NONATOMIC_IOSONLY) GKLeaderboardTimeScope timeScope;
@property (copy, NS_NONATOMIC_IOSONLY)   NSString *category;
@property (assign, NS_NONATOMIC_IOSONLY) id <GKLeaderboardViewControllerDelegate> leaderboardDelegate;

@end

NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use GKGameCenterViewController instead") 
@protocol GKLeaderboardViewControllerDelegate <NSObject>
@required
// The leaderboard view has finished
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
@end
// ==========  GameKit.framework/Headers/GKScore.h
//
//  GKScore.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameKit/GKLeaderboard.h>


@class GKPlayer;

NS_ASSUME_NONNULL_BEGIN

// GKScore represents a score in the leaderboards.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKScore : NSObject <NSCoding, NSSecureCoding>

// Initialize the score with the local player and current date.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier;

// Initialize the achievement for a specific player. Use to submit participant scores when ending a turn-based match.
- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier player:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);

@property(assign, NS_NONATOMIC_IOSONLY)                     int64_t     value;              // The score value as a 64bit integer.
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)   NSString    *formattedValue;    // The score formatted as a string, localized with a label

// leaderboard identifier (required)
@property(copy, NS_NONATOMIC_IOSONLY)               NSString    *leaderboardIdentifier NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// optional additional context that allows a game to store and retrieve additional data associated with the store.  Default value of zero is returned if no value is set.
@property(assign, NS_NONATOMIC_IOSONLY)                        uint64_t    context NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

@property(readonly, retain, NS_NONATOMIC_IOSONLY)   NSDate      *date;              // The date this score was recorded. A newly initialized, unsubmitted GKScore records the current date at init time.
@property(readonly, retain, nullable, NS_NONATOMIC_IOSONLY)   GKPlayer    *player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);          // The player that recorded the score.
@property(readonly, assign, NS_NONATOMIC_IOSONLY)   NSInteger   rank;               // The rank of the player within the leaderboard, only valid when returned from GKLeaderboard

// Convenience property to make the leaderboard associated with this GKScore, the default leaderboard for this player. Default value is false.
// If true, reporting that score will make the category this score belongs to, the default leaderboard for this user
@property(nonatomic, assign)                        BOOL        shouldSetDefaultLeaderboard     NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Report scores to the server. The value must be set, and date may be changed.
// Possible reasons for error:
// 1. Value not set
// 2. Local player not authenticated
// 3. Communications problem
+ (void)reportScores:(NSArray<GKScore *> *)scores withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

@end

@interface GKScore (Deprecated)

- (instancetype)initWithLeaderboardIdentifier:(NSString *)identifier forPlayer:(NSString *)playerID NS_DEPRECATED_IOS(7_0, 8_0, "use initWithLeaderboardIdentifier:player:") ;
- (void)reportScoreWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use +reportScores:withCompletionhandler: instead") ;
- (instancetype)initWithCategory:(nullable NSString *)category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use initWithLeaderboardIdentifier: instead") ;

@property(readonly, retain, NS_NONATOMIC_IOSONLY)   NSString    *playerID NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use player") ;          // The identifier of the player that recorded the score.
@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *category NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use leaderboardIdentifier instead") ;

@end

NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKMatchmaker.h
//
//  GKMatchmaker.h
//  Game Center
//
//  Copyright 2010-2019 Apple Inc. All rights reserved.
//

#include <Foundation/Foundation.h>

@class GKPlayer;
@class GKMatch;
@class GKTournament;


// Possible invitee responses
typedef NS_ENUM(NSInteger, GKInviteRecipientResponse) {
    GKInviteRecipientResponseAccepted           = 0,
    GKInviteRecipientResponseDeclined           = 1,
    GKInviteRecipientResponseFailed             = 2,
    GKInviteRecipientResponseIncompatible       = 3,
    GKInviteRecipientResponseUnableToConnect    = 4,
    GKInviteRecipientResponseNoAnswer           = 5,
    
    // Old names
    GKInviteeResponseAccepted           = GKInviteRecipientResponseAccepted,
    GKInviteeResponseDeclined           = GKInviteRecipientResponseDeclined,
    GKInviteeResponseFailed             = GKInviteRecipientResponseFailed,
    GKInviteeResponseIncompatible       = GKInviteRecipientResponseIncompatible,
    GKInviteeResponseUnableToConnect    = GKInviteRecipientResponseUnableToConnect,
    GKInviteeResponseNoAnswer           = GKInviteRecipientResponseNoAnswer,
};

typedef GKInviteRecipientResponse GKInviteeResponse;

NS_ASSUME_NONNULL_BEGIN
// GKMatchRequest represents the parameters needed to create the match.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKMatchRequest : NSObject

@property(assign) NSUInteger minPlayers;     // Minimum number of players for the match
@property(assign) NSUInteger maxPlayers;     // Maximum number of players for the match
@property(assign) NSUInteger playerGroup;    // The player group identifier. Matchmaking will only take place between players in the same group.
@property(assign) uint32_t playerAttributes; // optional mask that specifies the role that the local player would like to play in the game.  If this value is 0 (the default), this property is ignored. If the value is nonzero, then automatching uses the value as a mask that restricts the role the player can play in the group. Automatching with player attributes matches new players into the game so that the bitwise OR of the masks of all the players in the resulting match equals 0xFFFFFFFF.
@property(retain, nullable) NSArray<GKPlayer *> *recipients NS_AVAILABLE(10_10, 8_0);  // Array of GKPlayers to invite, or nil if none. This array can also include local guest players.
@property(retain, nullable) NSArray<NSString *> *playersToInvite NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use recipients") ; // Array of player IDs to invite, or nil if none

// Message sent to invited players, may be modified if using GKMatchmakerViewController
@property(copy, nullable)   NSString *inviteMessage NS_AVAILABLE(10_8, 6_0);

// Default number of players to use during matchmaking.  If not set we default to maxPlayers
@property(assign) NSUInteger defaultNumberOfPlayers NS_AVAILABLE(10_8, 6_0);

// Whether or not a match will be created only using auto-match.  If YES, then a player will not be able to
// invite anyone (including contacts, friends, and nearby players) to the match, but rely on auto-matching to
// find players for the match.  Default is NO.
@property(assign) BOOL restrictToAutomatch API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

// If supplied, then the match created from this request may only include players that are registered in this tournament.
// If nil, then all players available for matchmaking will be considered for both tournament matches and non-tournament matches.
@property (retain, nullable) GKTournament *tournamentForInvitePool API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

// An recipientResponseHandler can be set in order to receive responses from programmatically invited players.
@property(copy, nullable) void(^recipientResponseHandler)(GKPlayer *player, GKInviteRecipientResponse response) NS_AVAILABLE(10_10, 8_0);
@property(copy, nullable) void(^inviteeResponseHandler)(NSString *playerID, GKInviteeResponse response) NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use recipientResponseHandler") ;

typedef NS_ENUM(NSUInteger, GKMatchType) {
    GKMatchTypePeerToPeer,
    GKMatchTypeHosted,
    GKMatchTypeTurnBased
};

// To determine the maximum allowed players for each type of match supported.
+ (NSUInteger)maxPlayersAllowedForMatchOfType:(GKMatchType)matchType NS_AVAILABLE(10_9, 6_0);

@end


// GKInvite represents an accepted game invite, it is used to create a GKMatchmakerViewController
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKInvite : NSObject

@property(readonly, retain, NS_NONATOMIC_IOSONLY) GKPlayer *sender NS_AVAILABLE(10_10, 8_0);
@property(readonly, retain, NS_NONATOMIC_IOSONLY) NSString *inviter NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use sender") ;
@property(readonly, getter=isHosted, NS_NONATOMIC_IOSONLY) BOOL hosted;
@property(readonly, NS_NONATOMIC_IOSONLY) NSUInteger playerGroup NS_AVAILABLE(10_9, 6_0);      // player group from inviter's match request
@property(readonly, NS_NONATOMIC_IOSONLY) uint32_t playerAttributes NS_AVAILABLE(10_9, 6_0);   // player attributes from inviter's match request

@end

// GKInviteEventListener uses the GKLocalPlayerListener mechanism on GKLocalPlayer to listen to the two kinds of invite events that a game must respond to
@protocol GKInviteEventListener

@optional

// player:didAcceptInvite: gets called when another player accepts the invite from the local player
- (void)player:(GKPlayer *)player didAcceptInvite:(GKInvite *)invite NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

// didRequestMatchWithRecipients: gets called when the player chooses to play with another player from Game Center and it launches the game to start matchmaking
- (void)player:(GKPlayer *)player didRequestMatchWithRecipients:(NSArray<GKPlayer *> *)recipientPlayers NS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED;
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray<NSString *> *)playerIDsToInvite NS_DEPRECATED_IOS(7_0, 8_0, "use player:didRequestMatchWithRecipients:") ;

@end


// GKMatchmaker is a singleton object to manage match creation from invites and auto-matching.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKMatchmaker : NSObject

// The shared matchmaker
+ (GKMatchmaker *)sharedMatchmaker;

// Get a match for an accepted invite
// Possible reasons for error:
// 1. Communications failure
// 2. Invite cancelled
- (void)matchForInvite:(GKInvite *)invite completionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0);

// Auto-matching or invites to find a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
// Note that the players property on the returned GKMatch instance will only contain connected players. It will initially be empty as players are connecting. Implement the GKMatchDelegate method match:player:didChangeConnectionState: to listen for updates to the GKMatch instance's players property.

- (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler;

// Auto-matching or invites for host-client match request. This returns a list of player identifiers to be included in the match. Determination and communication with the host is not part of this API.
// When inviting, no player identifiers will be returned. Player responses will be reported via the inviteeResponseHandler.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
- (void)findPlayersForHostedRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

// Auto-matching or invites to add additional players to a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)addPlayersToMatch:(GKMatch *)match matchRequest:(GKMatchRequest *)matchRequest completionHandler:(void (^__nullable)(NSError * __nullable error))completionHandler;

// Cancel matchmaking and any pending invites
- (void)cancel;

// Cancel a pending invitation to a player
- (void)cancelPendingInviteToPlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);

// Call this when finished with all programmatic P2P invites/matchmaking, for compatability with connected players using GKMatchmakerViewController.
- (void)finishMatchmakingForMatch:(GKMatch *)match NS_AVAILABLE(10_9, 6_0);

// Query the server for recent activity in the specified player group. A larger value indicates that a given group has seen more recent activity. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryPlayerGroupActivity:(NSUInteger)playerGroup withCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;

// Query the server for recent activity for all the player groups of that game. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryActivityWithCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;


// Start browsing for nearby players that can be invited to a match. The reachableHandler will be called for each player found with a compatible game. It may be called more than once for the same player if that player ever becomes unreachable (e.g. moves out of range). You should call stopBrowsingForNearbyPlayers when finished browsing.
- (void)startBrowsingForNearbyPlayersWithHandler:(void(^__nullable)(GKPlayer *player, BOOL reachable))reachableHandler NS_AVAILABLE(10_10, 8_0);

// Stop browsing for nearby players.
- (void)stopBrowsingForNearbyPlayers  NS_AVAILABLE(10_9, 6_0);

@end

@interface GKMatchmaker (GKDeprecated)

@property(nonatomic, nullable, copy) void(^inviteHandler)(GKInvite *acceptedInvite, NSArray * __nullable playerIDsToInvite) NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use registerListener on GKLocalPlayer to register an object that implements the GKInviteEventListenerProtocol instead") ;

- (void)startBrowsingForNearbyPlayersWithReachableHandler:(void(^__nullable)(NSString *playerID, BOOL reachable))reachableHandler NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "Use startBrowsingForNearbyPlayersWithHandler: instead") ;
- (void)cancelInviteToPlayer:(NSString *)playerID NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use cancelPendingInviteToPlayer:") ;
- (void)findPlayersForHostedMatchRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable playerIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use findPlayersForHostedRequest:") ;

@end
NS_ASSUME_NONNULL_END
// ==========  GameKit.framework/Headers/GKPublicConstants.h
/*
 GKPublicConstants.h
 GameKit
 
 Copyright 2010 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* Delivery options for GKSession's -(BOOL)sendData... methods.
*/
typedef NS_ENUM(int, GKSendDataMode)
{
    GKSendDataReliable,        // a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKSendDataUnreliable,    // best effort and immediate, but no guarantees of delivery or order; will not stall.
} NS_ENUM_DEPRECATED(10_8, 10_10, 3_0, 7_0);

/* Specifies how GKSession behaves when it is made available.
*/
typedef NS_ENUM(int, GKSessionMode)
{
    GKSessionModeServer,    // delegate will get -didReceiveConnectionRequestFromPeer callback when a client wants to connect
    GKSessionModeClient,    // delegate will get -session:peer:didChangeState: callback with GKPeerStateAvailable, or GKPeerStateUnavailable for discovered servers
    GKSessionModePeer,      // delegate will get -didReceiveConnectionRequestFromPeer when a peer wants to connect, and -session:peer:didChangeState: callback with GKPeerStateAvailable, or GKPeerStateUnavailable for discovered servers
} NS_ENUM_DEPRECATED(10_8, 10_10, 3_0, 7_0);

/* Specifies the type of peers to return in method -peersWithConnectionState:
*/
typedef NS_ENUM(int, GKPeerConnectionState)
{
    GKPeerStateAvailable,    // not connected to session, but available for connectToPeer:withTimeout:
    GKPeerStateUnavailable,  // no longer available
    GKPeerStateConnected,    // connected to the session
    GKPeerStateDisconnected, // disconnected from the session
    GKPeerStateConnecting,   // waiting for accept, or deny response
} NS_ENUM_DEPRECATED(10_8, 10_10, 3_0, 7_0);


typedef NS_ENUM(int, GKVoiceChatServiceError)
{

    GKVoiceChatServiceInternalError = 32000,
    GKVoiceChatServiceNoRemotePacketsError = 32001,
    GKVoiceChatServiceUnableToConnectError = 32002,
    GKVoiceChatServiceRemoteParticipantHangupError = 32003,
    GKVoiceChatServiceInvalidCallIDError = 32004,
    GKVoiceChatServiceAudioUnavailableError = 32005,
    GKVoiceChatServiceUninitializedClientError = 32006,
    GKVoiceChatServiceClientMissingRequiredMethodsError = 32007,
    GKVoiceChatServiceRemoteParticipantBusyError = 32008,
    GKVoiceChatServiceRemoteParticipantCancelledError = 32009,
    GKVoiceChatServiceRemoteParticipantResponseInvalidError = 32010,
    GKVoiceChatServiceRemoteParticipantDeclinedInviteError = 32011,
    GKVoiceChatServiceMethodCurrentlyInvalidError = 32012,
    GKVoiceChatServiceNetworkConfigurationError = 32013,
    GKVoiceChatServiceUnsupportedRemoteVersionError = 32014,
    GKVoiceChatServiceOutOfMemoryError = 32015,
    GKVoiceChatServiceInvalidParameterError = 32016

} NS_ENUM_DEPRECATED_IOS(3_0, 7_0);
