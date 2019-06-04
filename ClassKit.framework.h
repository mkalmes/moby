// ==========  ClassKit.framework/Headers/CLSScoreItem.h
//
//  CLSScoreItem.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSScoreItem represents user generated score information.
 */

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSScoreItem : CLSActivityItem

/*!
 @abstract      Score out of @c maxScore.
 @discussion    Should be between zero and @c maxScore [0.0,maxScore].
 */
@property (nonatomic, assign) double score;

/*!
 @abstract      Total score possible.
 @discussion    Must be greater than zero.
 */
@property (nonatomic, assign) double maxScore;

/*!
 @abstract      Create a score item with identifiers, title, score and maximum score.
 @param         identifier      An identifier that is unique within activity.
 @param         title           Title of score. Ex @em Biology- Cellular Division Quiz @em
 @param         score           The score the user received.
 @param         maxScore        The maximum score possible.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title
                             score:(double)score
                          maxScore:(double)maxScore NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSObject.h
//
//  CLSObject.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      An object managed by ClassKit.
 @discussion    See @c CLSContext for more details.
 */

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSObject : NSObject <NSSecureCoding>

/*!
 @abstract      The date this object was created.
 */
@property (nonatomic, strong, readonly) NSDate *dateCreated;

/*!
 @abstract      The date this object was last modified.
 */
@property (nonatomic, strong, readonly) NSDate *dateLastModified;

- (instancetype)init NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSContext.h
//
//  CLSContext.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSDefines.h>
#import <ClassKit/CLSObject.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CLSContextType) {
    CLSContextTypeNone = 0,

    CLSContextTypeApp,       // Reserved for the main app context

    CLSContextTypeChapter,
    CLSContextTypeSection,
    CLSContextTypeLevel,
    CLSContextTypePage,

    CLSContextTypeTask,
    CLSContextTypeChallenge,
    CLSContextTypeQuiz,
    CLSContextTypeExercise,
    CLSContextTypeLesson,

    CLSContextTypeBook,
    CLSContextTypeGame,

    CLSContextTypeDocument,
    CLSContextTypeAudio,
    CLSContextTypeVideo,

} API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSContextTopic NS_STRING_ENUM API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

CLS_EXTERN CLSContextTopic const CLSContextTopicMath API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicScience API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicLiteracyAndWriting API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicWorldLanguage API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicSocialScience API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicComputerScienceAndEngineering API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicArtsAndMusic API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicHealthAndFitness API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);


/*!
 @abstract      Contexts represent activities, documents, and areas within your app.
 @discussion    Contexts have two major components.

                (1) Child contexts, used to model your app hierarchy.
                (2) Activity, holds user generated data that pertains to this context.

 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSContext : CLSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract      App-assigned identifier. This identifier should work across users and devices and be unique with regards to its siblings within its parent.
 @discussion    The identifier could be used to embed information later used for deep linking. For example: @em hydrogen-element, or @em chapter-1.
 */
@property (nonatomic, copy, readonly) NSString *identifier;


/*!
 @abstract      Alternative deep link URL using universal links.
 @discussion    If your app supports universal links, you can supply them here to link the content this context represents.
 */
@property (nullable, nonatomic, strong) NSURL *universalLinkURL API_AVAILABLE(ios(11.4)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Type of this context
 @discussion    The type that best describes this context.
 */
@property (nonatomic, assign, readonly) CLSContextType type;

/*!
 @abstract      Title of this context.
 @discussion    For example: @em Level 1 @em.
 */
@property (nonatomic, copy) NSString *title;

/*!
 @abstract      The displayOrder is by default sorted ascending.
 @discussion    Set the displayOrder if you want your contexts to be displayed in a particular order. The
                sort key is used as a way to sort sibling contexts in a particular order.
 */
@property (nonatomic, assign) NSInteger displayOrder;

/*!
 @abstract      Topic associated with this context.
 @discussion    See above for valid, predefined topics.
 */
@property (nullable, nonatomic, copy) CLSContextTopic topic;

/*!
@abstract      Initialize and configure the type of content this context represents.
 @param         identifier     App-assigned identifier for this context. 256 characters max length.
 @param         type           The type of content this context represents.
 @param         title          Title for what this context represents. 256 characters max length.
*/
- (instancetype)initWithType:(CLSContextType)type
                  identifier:(NSString *)identifier
                       title:(NSString *)title NS_DESIGNATED_INITIALIZER;

/*!
 @discussion    Returns true if self is the active context.
 */
@property (nonatomic, assign, readonly, getter=isActive) BOOL active;

/*!
 @abstract      Marks contexts as active.
 @discussion    If a context is already active, it will remain active. If another context is active, the other will resign active before this one becomes active.
 */
- (void)becomeActive;

/*!
 @abstract      Resign being active.
 @discussion    This method does nothing if the reciever of the message is not active.
 */
- (void)resignActive;

@end

@interface CLSContext (Hierarchy)

/*!
 @abstract      Returns the parent of this context.
 */
@property (nullable, nonatomic, weak, readonly) CLSContext *parent;

/*!
 @abstract      Removes this child context from its parent.
 @discussion    If you remove a context from its parent and do not add it as a child of another
                context, it will be deleted when you call -save on the dataStore.
 */
- (void)removeFromParent;

/*!
 @abstract      Adds a child context.
 @discussion    A context can only have a single parent.
 @note          objectID of child context may change after it's been added.
 */
- (void)addChildContext:(CLSContext *)child;

/*!
 @abstract      Returns a descendant of this context matching the context path you provide.
                Context path must start with an identifier of a child context of the context to which this message is sent.
 @discussion    If there are any missing contexts, they will be filled in by calling the following method on the context's data store's delegate:
                @code -[CLSDataStoreDelegate createContextForIdentifier:parentContext:parentIdentifierPath:] @endcode
                If the dataStore does not have a delegate and there are missing contexts then an incomplete list of contexts will be passed to the completion handler.
 				Completion block is called on a background thread.
 */
- (void)descendantMatchingIdentifierPath:(NSArray<NSString *> *)identifierPath
                              completion:(void(^)(CLSContext * _Nullable context, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSDataStore.h
//
//  CLSDataStore.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSDefines.h>
#import <ClassKit/CLSContext.h>
#import <ClassKit/CLSActivity.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@protocol CLSDataStoreDelegate <NSObject>

@required

/*!
 @abstract      Implement to return a new context with the supplied identifier as a child of the parent context.
 @discussion    This method is invoked for missing contexts in: @code -[CLSDataStore contextsMatchingIdentifierPath:completion:] @endcode and @code -[CLSContext descendantMatchingIdentifierPath:completion:] @endcode
                It will be called successively for each identifier in the path that is not found. This helps centralize context creation in one place.
 @note          New contexts returned in this method are automatically saved.

 @param         identifier              Identifier for the new context.
 @param         parentContext           Parent of the new context.
 @param         parentIdentifierPath    Ordered list of identifiers leading to the parent context.

 @return        The new context for the supplied identifier. The new context is automatically saved.
 */
- (nullable __kindof CLSContext *)createContextForIdentifier:(NSString *)identifier
                                               parentContext:(__kindof CLSContext *)parentContext
                                        parentIdentifierPath:(NSArray<NSString *> *)parentIdentifierPath;

@end


/*!
 @abstract      The data store maintains and syncs your app's contexts.
 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSDataStore : NSObject

/*!
 @abstract      The data store provides read/write access to your app's ClassKit data.
 @discussion    Data written to the data store is automatically synced via iCloud across the user's devices.
 */
@property (class, nonatomic, strong, readonly) CLSDataStore *shared;

/*!
 @abstract      Fetch the top level context for the current app.
 @discussion    The main context is automatically created. Add child contexts to this context to persist them in the data store.
 */
@property (nonatomic, strong, readonly) CLSContext *mainAppContext;

/*!
 @abstract      Returns the context that is currently active. If no context is active, this will return nil.
 */
@property (nullable, nonatomic, strong, readonly) CLSContext *activeContext;

/*!
 @abstract      Returns the most recently started activity that is running.
 */
@property (nullable, nonatomic, strong, readonly) CLSActivity *runningActivity;

/*!
 @abstract      The data store delegate allows for easy population of the app's context hierarchy.
 */
@property (nullable, nonatomic, weak) id<CLSDataStoreDelegate> delegate;


- (instancetype)init NS_UNAVAILABLE;

 /*!
  @abstract      Save changes made in the data store.
  @discussion    Save new/modified/removed contexts, activities, etc. to the local store. In case of an error -[NSError userInfo] will contain the object that caused the error under the CLSErrorObjectKey..
  */
- (void)saveWithCompletion:(nullable void(^)(NSError * _Nullable error))completion;

/*!
 @abstract      Complete all assigned actvities.
 @discussion    Marks all of the currently active assigned activities for this contextPath as complete.
 */
- (void)completeAllAssignedActivitiesMatching:(NSArray<NSString *> *)contextPath API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSDataStore (Contexts)


 /*!
  @abstract      Fetch contexts matching a predicate.
  @discussion    For example: NSPredicate<topic == kCLSContextTopicPhysics AND parent == someContext>.  Completion block may be called on a background thread.
  */
- (void)contextsMatchingPredicate:(NSPredicate *)predicate
                       completion:(void(^)(NSArray<CLSContext *> *contexts, NSError * _Nullable error))completion;

 /*!
  @abstract      Returns contexts matching a set of identifiers where each identifier is the parent of the following identifier.
  @discussion    For example: @c@["math-game", @c"level1"] returns two contexts where @em math-game is the parent of @em level1.
                 If there are any missing contexts, they will be filled in by calling the following method on the data store's delegate:
                 @code -[CLSDataStoreDelegate createContextForIdentifier:parentContext:parentIdentifierPath:] @endcode
                 If the dataStore does not have a delegate and there are missing contexts then an incomplete list of contexts will be passed to the completion handler.  Completion block may be called on a background thread.
  */
- (void)contextsMatchingIdentifierPath:(NSArray<NSString *> *)identifierPath
                            completion:(void(^)(NSArray<CLSContext *> *contexts, NSError * _Nullable error))completion;

/*!
 @abstract      Mark a context for removal.
 @discussion    Save to commit removal. Removal cascades and deletes all descendants.
 */
- (void)removeContext:(CLSContext *)context;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSActivityItem.h
//
//  CLSActivityItem.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSObject.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSActivityItem is used to gather information about the activity generated by a user.
 */

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSActivityItem : CLSObject

/*!
 @abstract      Title of what this ActivityItem respresents.
 @discussion    This will be the title associated with the activity item in the generated progress report.
 */
@property (nonatomic, copy) NSString *title;

/*!
 @abstract      An identifier that is unique within its owning activity
 @discussion    The identifier can be used to look up existing activityItems in a given activity.
 */
@property (nonatomic, copy, readonly) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSBinaryItem.h
//
//  CLSBinaryItem.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSActivityItem.h>
#import <ClassKit/CLSDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CLSBinaryValueType) {
    CLSBinaryValueTypeTrueFalse = 0,
    CLSBinaryValueTypePassFail,
    CLSBinaryValueTypeYesNo,
    CLSBinaryValueTypeCorrectIncorrect API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      CLSBinaryItem represents user generated information that is true or false, pass or fail, yes or no.
 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSBinaryItem : CLSActivityItem

/*!
 @abstract      True or false value.
 */
@property (nonatomic, assign) BOOL value;

/*!
 @abstract      Value type of this CLSBinaryItem.
 @discussion    The type that best describes this CLSBinaryItem value.
 */
@property (nonatomic, assign, readonly) CLSBinaryValueType valueType;

/*!
 @abstract      Create an item that represents a binary value
 @param         title           Title of the CLSBinaryItem.
 @param         identifier      An identifier that is unique within its owning activity.
 @param         valueType       The type of binary value. Ex. pass or fail.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title
                              type:(CLSBinaryValueType)valueType NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSDefines.h
//
//  CLSDefines.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#ifndef CLSDEFINES_H
#define CLSDEFINES_H

#import <Foundation/Foundation.h>

#if !defined(__cplusplus)
#define CLS_EXTERN extern __attribute__((visibility("default")))
#else
#define CLS_EXTERN extern "C" __attribute__((visibility("default")))
#endif

#if !defined(__cplusplus)
#define CLS_EXTERN_HIDDEN extern __attribute__((visibility("hidden")))
#else
#define CLS_EXTERN_HIDDEN extern "C" __attribute__((visibility("hidden")))
#endif


CLS_EXTERN NSString * const CLSErrorCodeDomain API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @enum      CLSErrorCode

 @constant  CLSErrorCodeNone                         No error.
 @constant  CLSErrorCodeClassKitUnavailable       	 ClassKit is not available on this device.
 @constant  CLSErrorCodeInvalidArgument              An invalid argument was provided to the API.
 @constant  CLSErrorCodeInvalidModification          Attempted to modify a readonly object.
 @constant  CLSErrorCodeAuthorizationDenied          The application is not authorized to perform the requested operation.
 @constant  CLSErrorCodeDatabaseInaccessible         Protected ClassKit is inaccessible because the device is locked.
 @constant  CLSErrorCodeLimits                       Limits exceeded.
 @constant  CLSErrorCodeInvalidCreate                Attempted to save new object that already exists in the data store.
 @constant  CLSErrorCodeInvalidUpdate                Failed to save updated object in the data store.
 @constant  CLSErrorCodePartialFailure               Returned if an operation resulted in a mix of successes and failures.
 */
typedef NS_ERROR_ENUM(CLSErrorCodeDomain, CLSErrorCode) {
    CLSErrorCodeNone = 0,
    CLSErrorCodeClassKitUnavailable,
    CLSErrorCodeInvalidArgument,
    CLSErrorCodeInvalidModification,
    CLSErrorCodeAuthorizationDenied,
    CLSErrorCodeDatabaseInaccessible,
    CLSErrorCodeLimits,
    CLSErrorCodeInvalidCreate,
    CLSErrorCodeInvalidUpdate,
    CLSErrorCodePartialFailure
} API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSErrorUserInfoKey NS_EXTENSIBLE_STRING_ENUM API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract   Any object that caused a failure will be available in - [NSError userInfo]; under this key.
 */
CLS_EXTERN CLSErrorUserInfoKey const CLSErrorObjectKey API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract   If multiple objects cause errors we return an error with code `CLSErrorCodePartialFailure` which will contain an array of errors in - [NSError userInfo]; under this key.
 */
CLS_EXTERN CLSErrorUserInfoKey const CLSErrorUnderlyingErrorsKey API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSPredicateKeyPath NS_EXTENSIBLE_STRING_ENUM API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathDateCreated API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathIdentifier API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathTitle API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathUniversalLinkURL API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathTopic API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathParent API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

#endif // CLSDEFINES_H
// ==========  ClassKit.framework/Headers/NSUserActivity+CLSDeepLinks.h
//
//  NSUserActivity+CLSDeepLinks.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSDefines.h>
#import <Foundation/NSUserActivity.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (CLSDeepLinks)

/*!
 @abstract      Returns whether the user activity is a ClassKit deep link.
 */
@property (nonatomic, assign, readonly) BOOL isClassKitDeepLink API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Returns the context identifier path you should deep link to.
 @discussion    For example for the context identifier path @c @["swift-programming-book", @c "chapter1"],
                your app should direct the user to @em chapter1 in @em swift-programming-book.
 */
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *contextIdentifierPath API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSActivity.h
//
//  CLSActivity.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSObject.h>
#import <ClassKit/CLSContext.h>
#import <ClassKit/CLSActivityItem.h>

@class CLSActivityItem;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSActivity represents user generated activity data for a given context.
 @discussion    CLSActivity has three major components.

             (1) Progress, used to measure the amount of activity a user generates as a percentage.
             (2) Duration, used to measure the length of time a user spent on this activity. Use @c -start and @c -stop methods.
             (3) Activity Items, used to gather information about the activity generated by a user.
 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSActivity : CLSObject

/*!
 @abstract      Current progress as a decimal representation of a percentage.
 @discussion    Should be [0.0, 1.0].
 */
@property (nonatomic, assign) double progress;

/*!
 @abstract      Returns the total time tracked in this activity (excluding any previous activities).
 @discussion    The time between calling @c -start and @c -stop.
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;

/*!
 @abstract      The primary activityItem to be reported on.
 @discussion    This can be nil indicating @c progress property is the primary data instead of any activityItems.
 */
@property (nullable, nonatomic, strong) __kindof CLSActivityItem *primaryActivityItem;

/*!
 @abstract      Adds progress to this activity.
 @discussion    The progress should be a decimal representation of the start and ending percentage [0.0, 1.0].
 @param         start      Starting percentage.
 @param         end        Ending percentage.
 */
- (void)addProgressRangeFromStart:(double)start
                            toEnd:(double)end;

/*!
 @abstract      Add an activity item to this CLSActivity.
 */
- (void)addAdditionalActivityItem:(CLSActivityItem *)activityItem;

/*!
 @abstract      Array of all additional activity items on this CLSActivity.
 */
@property (nonatomic, strong, readonly) NSArray<__kindof CLSActivityItem *> *additionalActivityItems;

@end

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSActivity (Activation)

/*!
 @abstract      Returns whether this Activity has been started or not.
 */
@property (nonatomic, assign, readonly, getter=isStarted) BOOL started;

/*!
 @abstract      Start Activity.
 @discussion    Starts the activity (or resumes if previously stopped).
 */
- (void)start;

/*!
 @abstract      Stop Activity.
 @discussion    Stops or pauses the activity and ends the time being tracked on it.
 */
- (void)stop;

@end

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSContext (Activity)

/*!
 @abstract      Returns the current activity.
 @discussion    Activity associated with a context.  If no activity was ever created this is nil. See: @c -[CLSContext createNewActivity]; for more details.
 */
@property (nullable, nonatomic, strong, readonly) CLSActivity *currentActivity;

/*!
 @abstract      Creates a new activity
 @discussion    Creates a new activity and sets it as the current activity.
 */
- (CLSActivity *)createNewActivity;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/CLSContextProvider.h
//
//  CLSContextProvider.h
//  ClassKit
//
//  Created by Baskaran Subramaniam on 10/02/18.
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSDefines.h>


@class CLSContext;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      The CLSContext provider protocol.
 @discussion    The app extension that provides CLSContexts should adopt this protocol.
 */
API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@protocol CLSContextProvider

@required

/*!
 @abstract      This method asks the app extension to update CLSContexts that are descendants of a given context.
 @param         context     A CLSContext whose descendants are to be updated
 @param         completion  A completion block the extension should call with an optional error to indicate success or failure.
 @discussion    The extension may choose to modify, delete, or create some or all descendants of the given context. The host app may call this method as the user selects a context.
 */
- (void)updateDescendantsOfContext:(CLSContext *)context completion:(void(^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  ClassKit.framework/Headers/ClassKit.h
//
//  ClassKit.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSDefines.h>
#import <ClassKit/CLSObject.h>
#import <ClassKit/CLSContext.h>
#import <ClassKit/CLSActivity.h>
#import <ClassKit/CLSActivityItem.h>
#import <ClassKit/CLSScoreItem.h>
#import <ClassKit/CLSBinaryItem.h>
#import <ClassKit/CLSQuantityItem.h>
#import <ClassKit/CLSDataStore.h>
#import <ClassKit/NSUserActivity+CLSDeepLinks.h>
#import <ClassKit/CLSContextProvider.h>
// ==========  ClassKit.framework/Headers/CLSQuantityItem.h
//
//  CLSQuantityItem.h
//  ClassKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ClassKit/CLSActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSQuantityItem represents user generated quantity information.
 */

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface CLSQuantityItem : CLSActivityItem

/*!
 @abstract      Quantity awarded.
 */
@property (nonatomic, assign) double quantity;

/*!
 @abstract      Create a quantity item with an identifier and title.
 @param         identifier      An identifier that is unique within activity.
 @param         title           Title of the quantity. Ex @em Hints @em
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
