// ==========  CallKit.framework/Headers/CXCallObserver.h
//
//  CXCallObserver.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCall;
@class CXCallObserver;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@protocol CXCallObserverDelegate <NSObject>

- (void)callObserver:(CXCallObserver *)callObserver callChanged:(CXCall *)call;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallObserver : NSObject

/// Retrieve the current call list, blocking on initial state retrieval if necessary
@property (nonatomic, readonly, copy) NSArray<CXCall *> *calls;

/// Set delegate and optional queue for delegate callbacks to be performed on.
/// A nil queue implies that delegate callbacks should happen on the main queue. The delegate is stored weakly
- (void)setDelegate:(nullable id<CXCallObserverDelegate>)delegate queue:(nullable dispatch_queue_t)queue;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CallKit.h
//
//  CallKit.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CallKit/CXBase.h>

#import <CallKit/CXError.h>

#import <CallKit/CXAction.h>
#import <CallKit/CXTransaction.h>

#import <CallKit/CXCallUpdate.h>
#import <CallKit/CXHandle.h>

#import <CallKit/CXCallAction.h>
#import <CallKit/CXStartCallAction.h>
#import <CallKit/CXAnswerCallAction.h>
#import <CallKit/CXEndCallAction.h>
#import <CallKit/CXSetHeldCallAction.h>
#import <CallKit/CXSetMutedCallAction.h>
#import <CallKit/CXSetGroupCallAction.h>
#import <CallKit/CXPlayDTMFCallAction.h>

#import <CallKit/CXProvider.h>
#import <CallKit/CXProviderConfiguration.h>

#import <CallKit/CXCall.h>
#import <CallKit/CXCallObserver.h>
#import <CallKit/CXCallController.h>

#import <CallKit/CXCallDirectory.h>
#import <CallKit/CXCallDirectoryManager.h>
#import <CallKit/CXCallDirectoryProvider.h>
#import <CallKit/CXCallDirectoryExtensionContext.h>
// ==========  CallKit.framework/Headers/CXProvider.h
//
//  CXProvider.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;
@class CXCallAction;
@class CXCallUpdate;
@class CXProvider;
@class CXProviderConfiguration;
@class CXTransaction;
@class CXAction;
@class CXCallAction;
@class CXStartCallAction;
@class CXAnswerCallAction;
@class CXEndCallAction;
@class CXSetHeldCallAction;
@class CXSetMutedCallAction;
@class CXSetGroupCallAction;
@class CXPlayDTMFCallAction;

@class AVAudioSession;

typedef NS_ENUM(NSInteger, CXCallEndedReason) {
    CXCallEndedReasonFailed = 1, // An error occurred while trying to service the call
    CXCallEndedReasonRemoteEnded = 2, // The remote party explicitly ended the call
    CXCallEndedReasonUnanswered = 3, // The call never started connecting and was never explicitly ended (e.g. outgoing/incoming call timeout)
    CXCallEndedReasonAnsweredElsewhere = 4, // The call was answered on another device
    CXCallEndedReasonDeclinedElsewhere = 5, // The call was declined on another device
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@protocol CXProviderDelegate <NSObject>

/// Called when the provider has been reset. Delegates must respond to this callback by cleaning up all internal call state (disconnecting communication channels, releasing network resources, etc.). This callback can be treated as a request to end all calls without the need to respond to any actions
- (void)providerDidReset:(CXProvider *)provider;

@optional

/// Called when the provider has been fully created and is ready to send actions and receive updates
- (void)providerDidBegin:(CXProvider *)provider;

/// Called whenever a new transaction should be executed. Return whether or not the transaction was handled:
///
/// - NO: the transaction was not handled indicating that the perform*CallAction methods should be called sequentially for each action in the transaction
/// - YES: the transaction was handled and the perform*CallAction methods should not be called sequentially
///
/// If the method is not implemented, NO is assumed.
- (BOOL)provider:(CXProvider *)provider executeTransaction:(CXTransaction *)transaction;

// If provider:executeTransaction:error: returned NO, each perform*CallAction method is called sequentially for each action in the transaction
- (void)provider:(CXProvider *)provider performStartCallAction:(CXStartCallAction *)action;
- (void)provider:(CXProvider *)provider performAnswerCallAction:(CXAnswerCallAction *)action;
- (void)provider:(CXProvider *)provider performEndCallAction:(CXEndCallAction *)action;
- (void)provider:(CXProvider *)provider performSetHeldCallAction:(CXSetHeldCallAction *)action;
- (void)provider:(CXProvider *)provider performSetMutedCallAction:(CXSetMutedCallAction *)action;
- (void)provider:(CXProvider *)provider performSetGroupCallAction:(CXSetGroupCallAction *)action;
- (void)provider:(CXProvider *)provider performPlayDTMFCallAction:(CXPlayDTMFCallAction *)action;

/// Called when an action was not performed in time and has been inherently failed. Depending on the action, this timeout may also force the call to end. An action that has already timed out should not be fulfilled or failed by the provider delegate
- (void)provider:(CXProvider *)provider timedOutPerformingAction:(CXAction *)action;

/// Called when the provider's audio session activation state changes.
- (void)provider:(CXProvider *)provider didActivateAudioSession:(AVAudioSession *)audioSession;
- (void)provider:(CXProvider *)provider didDeactivateAudioSession:(AVAudioSession *)audioSession;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXProvider : NSObject

/// In some regions, this functionality may not be supported. Query this value to determine whether your application is allowed to use CXProvider or not.
@property (class, readonly, getter=isSupported) BOOL supported API_AVAILABLE(ios(13.0));

/// Initialize a new provider instance with the supplied configuration
- (instancetype)initWithConfiguration:(CXProviderConfiguration *)configuration NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/// Set delegate and optional queue for delegate callbacks to be performed on.
/// A nil queue implies that delegate callbacks should happen on the main queue. The delegate is stored weakly
- (void)setDelegate:(nullable id<CXProviderDelegate>)delegate queue:(nullable dispatch_queue_t)queue;

/// Report a new incoming call to the system.
///
/// If completion is invoked with a non-nil `error`, the incoming call has been disallowed by the system and will not be displayed, so the provider should not proceed with the call.
///
/// Completion block will be called on delegate queue, if specified, otherwise on a private serial queue.
- (void)reportNewIncomingCallWithUUID:(NSUUID *)UUID update:(CXCallUpdate *)update completion:(void (^)(NSError *_Nullable error))completion;

/// Report an update to call information.
- (void)reportCallWithUUID:(NSUUID *)UUID updated:(CXCallUpdate *)update;

/// Report that a call ended. A nil value for `dateEnded` results in the ended date being set to now.
- (void)reportCallWithUUID:(NSUUID *)UUID endedAtDate:(nullable NSDate *)dateEnded reason:(CXCallEndedReason)endedReason;

/// Report that an outgoing call started connecting. A nil value for `dateStartedConnecting` results in the started connecting date being set to now.
- (void)reportOutgoingCallWithUUID:(NSUUID *)UUID startedConnectingAtDate:(nullable NSDate *)dateStartedConnecting;

/// Report that an outgoing call connected. A nil value for `dateConnected` results in the connected date being set to now.
- (void)reportOutgoingCallWithUUID:(NSUUID *)UUID connectedAtDate:(nullable NSDate *)dateConnected;

/// The receiver's current configuration.
@property (nonatomic, readwrite, copy) CXProviderConfiguration *configuration;

/// Invalidate the receiver. All existing calls will be marked as ended in failure. The provider must be invalidated before it is deallocated.
- (void)invalidate;

/// List of all transactions that are incomplete.
@property (nonatomic, readonly, copy) NSArray<CXTransaction *> *pendingTransactions;

/// Returns subset of call actions contained in any transaction in -pendingTransactions of the specified class and with the specified call UUID.
- (NSArray<__kindof CXCallAction *> *)pendingCallActionsOfClass:(Class)callActionClass withCallUUID:(NSUUID *)callUUID;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCall.h
//
//  CXCall.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCall : NSObject

@property (nonatomic, readonly, copy) NSUUID *UUID;

@property (nonatomic, readonly, assign, getter=isOutgoing) BOOL outgoing;
@property (nonatomic, readonly, assign, getter=isOnHold) BOOL onHold;
@property (nonatomic, readonly, assign) BOOL hasConnected;
@property (nonatomic, readonly, assign) BOOL hasEnded;

- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToCall:(CXCall *)call;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallController.h
//
//  CXCallController.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;
@class CXCallObserver;
@class CXTransaction;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallController : NSObject

/// Initialize call controller with a private, serial queue.
- (instancetype)init;

/// Initialize call controller with specified queue, which is used for calling completion blocks.
- (instancetype)initWithQueue:(dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) CXCallObserver *callObserver;

/// Request a transaction to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransaction:(CXTransaction *)transaction completion:(void (^)(NSError *_Nullable error))completion;

/// Request a transaction containing the specified actions to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransactionWithActions:(NSArray<CXAction *> *)actions completion:(void (^)(NSError *_Nullable error))completion API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

/// Request a transaction containing the specified action to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed to the CXProvider's -provider:executeTransaction: delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransactionWithAction:(CXAction *)action completion:(void (^)(NSError *_Nullable error))completion API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXEndCallAction.h
//
//  CXEndCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXEndCallAction : CXCallAction

/// Normally, providers can just call -[CXAction fulfill] to indicate action fulfillment. Use this method to note a specific date that the call ended.
- (void)fulfillWithDateEnded:(NSDate *)dateEnded;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallDirectory.h
//
//  CXCallDirectory.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef int64_t CXCallDirectoryPhoneNumber;

static const CXCallDirectoryPhoneNumber CXCallDirectoryPhoneNumberMax = (INT64_MAX - 1);

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallDirectoryExtensionContext.h
//
//  CXCallDirectoryExtensionContext.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>
#import <CallKit/CXCallDirectory.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallDirectoryExtensionContext;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@protocol CXCallDirectoryExtensionContextDelegate <NSObject>

- (void)requestFailedForExtensionContext:(CXCallDirectoryExtensionContext *)extensionContext withError:(NSError *)error;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallDirectoryExtensionContext : NSExtensionContext

@property (nonatomic, weak, nullable) id<CXCallDirectoryExtensionContextDelegate> delegate;

/**
 Whether the request should provide incremental data.

 If this is called at the beginning of the request (before any entries have been added or removed) and the result is YES,
 then the request must only provide an "incremental" set of entries, i.e. only add or remove entries relative to the last time data
 was loaded for the extension. Otherwise, if this method is not called OR is called and returns NO, then the request must provide
 a "complete" set of entries, adding the full list of entries from scratch (and removing none), regardless of whether data has ever been
 successfully loaded in the past.
 */
@property (nonatomic, readonly, getter=isIncremental) BOOL incremental API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)addBlockingEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber;

/**
 Remove blocking entry with the specified phone number.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove a previously-added blocking entry.

 @param phoneNumber The blocking entry phone number to remove.
 */
- (void)removeBlockingEntryWithPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

/**
 Remove all currently-stored blocking entries.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove all previously-added blocking entries.
 */
- (void)removeAllBlockingEntries API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)addIdentificationEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber label:(NSString *)label;

/**
 Remove identification entry with the specified phone number.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove a previously-added identification entry. Removes all identification entries with the specified phone number, even if
 multiple identification entries with different labels are present for a single phone number.

 @param phoneNumber The identification entry phone number to remove.
 */
- (void)removeIdentificationEntryWithPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

/**
 Remove all currently-stored identification entries.

 May only be used when `-isIncremental` returns YES, indicating that the request should provide incremental entries and thus may use this
 API to remove all previously-added identification entries.
 */
- (void)removeAllIdentificationEntries API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

- (void)completeRequestWithCompletionHandler:(nullable void (^)(BOOL expired))completion;

// Use -completeRequestWithCompletionHandler: instead
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^__nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXAction.h
//
//  CXAction.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXAction : NSObject <NSCopying, NSSecureCoding>

/// Unique ID
@property (nonatomic, readonly, copy) NSUUID *UUID;

/// Whether all actions are either fulfilled or failed
@property (nonatomic, readonly, assign, getter=isComplete) BOOL complete;

@property (nonatomic, readonly, strong) NSDate *timeoutDate;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// Report successful execution of the receiver.
- (void)fulfill;

/// Report failed execution of the receiver.
- (void)fail;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXSetMutedCallAction.h
//
//  CXSetMutedCallAction.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXSetMutedCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID muted:(BOOL)muted NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

@property (nonatomic, getter=isMuted) BOOL muted;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXPlayDTMFCallAction.h
//
//  CXPlayDTMFCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

typedef NS_ENUM(NSInteger, CXPlayDTMFCallActionType) {
    CXPlayDTMFCallActionTypeSingleTone = 1, // The user tapped a digit on the in-call keypad
    CXPlayDTMFCallActionTypeSoftPause = 2, // The user included digits after a soft pause in their dial string
    CXPlayDTMFCallActionTypeHardPause = 3, // The user included digits after a hard pause in their dial string
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXPlayDTMFCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID digits:(NSString *)digits type:(CXPlayDTMFCallActionType)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

// The string representation of the digits that should be played as DTMF tones
@property (nonatomic, copy) NSString *digits;

// Whether or not the string of digits represents tones following a hard or soft pause
@property (nonatomic) CXPlayDTMFCallActionType type;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXAnswerCallAction.h
//
//  CXAnswerCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXAnswerCallAction : CXCallAction

/// Normally, providers can just call -[CXAction fulfill] to indicate action fulfillment. Use this method to note a specific date that the call connected. A call is considered connected when both caller and callee can start communicating.
- (void)fulfillWithDateConnected:(NSDate *)dateConnected;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallAction.h
//
//  CXCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallAction : CXAction

@property (nonatomic, readonly, copy) NSUUID *callUUID;

- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXSetHeldCallAction.h
//
//  CXSetHeldCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXSetHeldCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID onHold:(BOOL)onHold NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

@property (nonatomic, getter=isOnHold) BOOL onHold;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXSetGroupCallAction.h
//
//  CXSetGroupCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXSetGroupCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID callUUIDToGroupWith:(nullable NSUUID *)callUUIDToGroupWith NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

/// The UUID of another call to group with.
///
/// - If the call for this action's UUID is already in a group, it should leave that group if necessary.
/// - If nil, leave any group the call is currently in.
@property (nonatomic, copy, nullable) NSUUID *callUUIDToGroupWith;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXHandle.h
//
//  CXHandle.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CXHandleType) {
    CXHandleTypeGeneric = 1,
    CXHandleTypePhoneNumber = 2,
    CXHandleTypeEmailAddress = 3,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXHandle : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly) CXHandleType type;
@property (nonatomic, readonly, copy) NSString *value;

- (instancetype)initWithType:(CXHandleType)type value:(NSString *)value NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToHandle:(CXHandle *)handle;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXTransaction.h
//
//  CXTransaction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXTransaction : NSObject <NSCopying, NSSecureCoding>

/// Unique ID
@property (nonatomic, readonly, copy) NSUUID *UUID;

/// Whether all actions have been completed
@property (nonatomic, readonly, assign, getter=isComplete) BOOL complete;

/// The list of actions contained by the receiver
@property (nonatomic, readonly, copy) NSArray<__kindof CXAction *> *actions;

- (instancetype)initWithActions:(NSArray<CXAction *> *)actions NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAction:(CXAction *)action;

/// Add the provided action to the receiver's list of actions
- (void)addAction:(CXAction *)action;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXBase.h
//
//  CXBase.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
#define CX_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define CX_EXTERN extern __attribute__((visibility("default")))
#endif

#define CX_CLASS_AVAILABLE(...) CX_EXTERN API_AVAILABLE(__VA_ARGS__)

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallDirectoryManager.h
//
//  CXCallDirectoryManager.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CXCallDirectoryEnabledStatus) {
    CXCallDirectoryEnabledStatusUnknown = 0,
    CXCallDirectoryEnabledStatusDisabled = 1,
    CXCallDirectoryEnabledStatusEnabled = 2,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallDirectoryManager : NSObject

@property (readonly, class) CXCallDirectoryManager *sharedInstance;

- (void)reloadExtensionWithIdentifier:(NSString *)identifier completionHandler:(nullable void (^)(NSError *_Nullable error))completion;
- (void)getEnabledStatusForExtensionWithIdentifier:(NSString *)identifier completionHandler:(void (^)(CXCallDirectoryEnabledStatus enabledStatus, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallDirectoryProvider.h
//
//  CXCallDirectoryProvider.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallDirectoryExtensionContext;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallDirectoryProvider : NSObject <NSExtensionRequestHandling>

- (void)beginRequestWithExtensionContext:(CXCallDirectoryExtensionContext *)context;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXStartCallAction.h
//
//  CXStartCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

NS_ASSUME_NONNULL_BEGIN

@class CXHandle;

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXStartCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID handle:(CXHandle *)handle NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

/// Handle for the party to call
@property (nonatomic, copy) CXHandle *handle;

@property (nonatomic, copy, nullable) NSString *contactIdentifier;

@property (nonatomic, getter=isVideo) BOOL video;

/// Normally, providers can just call -[CXAction fulfill] to indicate action fulfillment. Use this method to note a specific date that the call started if it is different from [NSDate date]. A call is considered started when its invitation has been sent to the remote callee.
- (void)fulfillWithDateStarted:(NSDate *)dateStarted;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXError.h
//
//  CXError.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN NSErrorDomain const CXErrorDomain API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);
CX_EXTERN NSErrorDomain const CXErrorDomainIncomingCall API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);
CX_EXTERN NSErrorDomain const CXErrorDomainRequestTransaction API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);
CX_EXTERN NSErrorDomain const CXErrorDomainCallDirectoryManager API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

typedef NS_ERROR_ENUM(CXErrorDomain, CXErrorCode) {
    CXErrorCodeUnknownError = 0,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

typedef NS_ERROR_ENUM(CXErrorDomainIncomingCall, CXErrorCodeIncomingCallError) {
    CXErrorCodeIncomingCallErrorUnknown = 0,
    CXErrorCodeIncomingCallErrorUnentitled = 1,
    CXErrorCodeIncomingCallErrorCallUUIDAlreadyExists = 2,
    CXErrorCodeIncomingCallErrorFilteredByDoNotDisturb = 3,
    CXErrorCodeIncomingCallErrorFilteredByBlockList = 4,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

typedef NS_ERROR_ENUM(CXErrorDomainRequestTransaction, CXErrorCodeRequestTransactionError) {
    CXErrorCodeRequestTransactionErrorUnknown = 0,
    CXErrorCodeRequestTransactionErrorUnentitled = 1,
    CXErrorCodeRequestTransactionErrorUnknownCallProvider = 2,
    CXErrorCodeRequestTransactionErrorEmptyTransaction = 3,
    CXErrorCodeRequestTransactionErrorUnknownCallUUID = 4,
    CXErrorCodeRequestTransactionErrorCallUUIDAlreadyExists = 5,
    CXErrorCodeRequestTransactionErrorInvalidAction = 6,
    CXErrorCodeRequestTransactionErrorMaximumCallGroupsReached = 7,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

typedef NS_ERROR_ENUM(CXErrorDomainCallDirectoryManager, CXErrorCodeCallDirectoryManagerError) {
    CXErrorCodeCallDirectoryManagerErrorUnknown = 0,
    CXErrorCodeCallDirectoryManagerErrorNoExtensionFound = 1,
    CXErrorCodeCallDirectoryManagerErrorLoadingInterrupted = 2,
    CXErrorCodeCallDirectoryManagerErrorEntriesOutOfOrder = 3,
    CXErrorCodeCallDirectoryManagerErrorDuplicateEntries = 4,
    CXErrorCodeCallDirectoryManagerErrorMaximumEntriesExceeded = 5,
    CXErrorCodeCallDirectoryManagerErrorExtensionDisabled = 6,
    CXErrorCodeCallDirectoryManagerErrorCurrentlyLoading API_AVAILABLE(ios(10.3), uikitformac(13.0)) = 7,
    CXErrorCodeCallDirectoryManagerErrorUnexpectedIncrementalRemoval API_AVAILABLE(ios(11.0), uikitformac(13.0)) = 8,
} API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXProviderConfiguration.h
//
//  CXProviderConfiguration.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXProviderConfiguration : NSObject <NSCopying>

/// Localized name of the provider
@property (nonatomic, readonly, copy) NSString *localizedName;

/// Name of resource in app's bundle to play as ringtone for incoming call
@property (nonatomic, strong, nullable) NSString *ringtoneSound;

@property (nonatomic, copy, nullable) NSData *iconTemplateImageData; // Image should be a square with side length of 40 points
@property (nonatomic) NSUInteger maximumCallGroups; // Default 2
@property (nonatomic) NSUInteger maximumCallsPerCallGroup; // Default 5

/// Whether this provider's calls should be included in the system's Recents list at the end of each call.
/// Default: YES
@property (nonatomic) BOOL includesCallsInRecents API_AVAILABLE(ios(11.0), uikitformac(13.0)) API_UNAVAILABLE(macos, watchos);

@property (nonatomic) BOOL supportsVideo; // Default NO

// Numbers are of type CXHandleType
@property (nonatomic, copy) NSSet<NSNumber *> *supportedHandleTypes;

- (instancetype)initWithLocalizedName:(NSString *)localizedName NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  CallKit.framework/Headers/CXCallUpdate.h
//
//  CXCallUpdate.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXHandle;

// Any property that is not set will be ignored

CX_EXTERN API_AVAILABLE(ios(10.0), uikitformac(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface CXCallUpdate : NSObject <NSCopying>

/// Handle for the remote party (for an incoming call, the caller; for an outgoing call, the callee)
@property (nonatomic, copy, nullable) CXHandle *remoteHandle;

/// Override the computed caller name to a provider-defined value.
/// Normally the system will determine the appropriate caller name to display (e.g. using the user's contacts) based on the supplied caller identifier. Set this property to customize.
@property (nonatomic, copy, nullable) NSString *localizedCallerName;

/// Whether the call can be held on its own or swapped with another call
@property (nonatomic) BOOL supportsHolding;

/// Whether the call can be grouped (merged) with other calls when it is ungrouped
@property (nonatomic) BOOL supportsGrouping;

/// The call can be ungrouped (taken private) when it is grouped
@property (nonatomic) BOOL supportsUngrouping;

/// The call can send DTMF tones via hard pause digits or in-call keypad entries
@property (nonatomic) BOOL supportsDTMF;

/// The call includes video in addition to audio.
@property (nonatomic) BOOL hasVideo;

@end

NS_ASSUME_NONNULL_END
