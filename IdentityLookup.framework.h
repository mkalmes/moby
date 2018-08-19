// ==========  IdentityLookup.framework/Headers/ILMessageFilterError.h
//
//  ILMessageFilterError.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

IL_EXTERN NSErrorDomain const ILMessageFilterErrorDomain API_AVAILABLE(ios(11.0));

typedef NS_ERROR_ENUM(ILMessageFilterErrorDomain, ILMessageFilterError) {
    /// An unspecified system error occurred.
    ILMessageFilterErrorSystem = 1,

    /// The network request URL included in the extension's Info.plist was either missing or invalid. See documentation for network request URL requirements.
    ILMessageFilterErrorInvalidNetworkURL = 2,

    /// Extension's containing app is not authorized to allow extension to defer network requests to the host specified in the URL of the extension's Info.plist.
    ILMessageFilterErrorNetworkURLUnauthorized = 3,

    /// Network request was attempted but failed. See `NSUnderlyingErrorKey` in `userInfo` dictionary for details.
    ILMessageFilterErrorNetworkRequestFailed = 4,

    /// Extension requested to defer a request to its network service more than once. Requests may be deferred to the network at most once.
    ILMessageFilterErrorRedundantNetworkDeferral = 5,
} API_AVAILABLE(ios(11.0));

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterQueryHandling.h
//
//  ILMessageFilterQueryHandling.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

@class ILMessageFilterQueryRequest;
@class ILMessageFilterExtensionContext;
@class ILMessageFilterQueryResponse;

/**
 Functionality related to MessageFilter extension query requests.

 Subclasses of ILMessageFilterExtension which support querying must conform to this protocol.
 */
IL_EXTERN API_AVAILABLE(ios(11.0))
@protocol ILMessageFilterQueryHandling <NSObject>

/**
 Evaluate a query request and provide a response describing how the system should handle the message it represents.

 May include either (or both) of the following:

 - Using offline/stored information to form a response about the message described by the query request.

 - Deferring the query request to a network service associated with the app extension, allowing the network service to
   return data back to extension in order to form a response about the message. The `context` parameter provides an API which
   allows deferring a request to the network and receiving the response to that network request.

 Block specified in `completion` parameter must be invoked with a response describing how to handle the message, and may be
 invoked asynchronously.

 @param queryRequest A query request to be handled which describes a received message.
 @param context Extension context which offers API to defer request to network if necessary.
 @param completion Completion block for returning a response.
 */
- (void)handleQueryRequest:(ILMessageFilterQueryRequest *)queryRequest context:(ILMessageFilterExtensionContext *)context completion:(void (^)(ILMessageFilterQueryResponse *))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterQueryResponse.h
//
//  ILMessageFilterQueryResponse.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>
#import <IdentityLookup/ILMessageFilterAction.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an ILMessageFilterQueryRequest.
IL_EXTERN API_AVAILABLE(ios(11.0))
@interface ILMessageFilterQueryResponse : NSObject <NSSecureCoding>

/// Action to take for the received message.
@property (nonatomic) ILMessageFilterAction action;

@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILBase.h
//
//  ILBase.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
#define IL_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define IL_EXTERN extern __attribute__((visibility("default")))
#endif

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/IdentityLookup.h
//
//  IdentityLookup.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <IdentityLookup/ILBase.h>

#import <IdentityLookup/ILMessageFilterAction.h>

#import <IdentityLookup/ILMessageFilterError.h>

#import <IdentityLookup/ILNetworkResponse.h>

#import <IdentityLookup/ILMessageFilterExtension.h>
#import <IdentityLookup/ILMessageFilterExtensionContext.h>

#import <IdentityLookup/ILMessageFilterQueryHandling.h>
#import <IdentityLookup/ILMessageFilterQueryRequest.h>
#import <IdentityLookup/ILMessageFilterQueryResponse.h>
// ==========  IdentityLookup.framework/Headers/ILNetworkResponse.h
//
//  ILNetworkResponse.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an HTTPS network request.
IL_EXTERN API_AVAILABLE(ios(11.0))
@interface ILNetworkResponse : NSObject <NSSecureCoding>

/// Represents the URL response itself. See documentation for NSHTTPURLResponse.
@property (nonatomic, readonly) NSHTTPURLResponse *urlResponse;

/// Data returned in the HTTPS response.
@property (nonatomic, readonly) NSData *data;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterQueryRequest.h
//
//  ILMessageFilterQueryRequest.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A request to query a MessageFilter extension about how to interpret a received message.
IL_EXTERN API_AVAILABLE(ios(11.0))
@interface ILMessageFilterQueryRequest : NSObject <NSSecureCoding>

/// The sender of the message the receiver relates to.
@property (nonatomic, readonly, nullable) NSString *sender;

/// The body of the message the receiver relates to.
@property (nonatomic, readonly, nullable) NSString *messageBody;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterExtension.h
//
//  ILMessageFilterExtension.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// Parent class for a MessageFilter extension's principal class.
IL_EXTERN API_AVAILABLE(ios(11.0))
@interface ILMessageFilterExtension : NSObject
@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterExtensionContext.h
//
//  ILMessageFilterExtensionContext.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

@class ILNetworkResponse;

/// Represents a MessageFilter extension request's context.
IL_EXTERN API_AVAILABLE(ios(11.0))
@interface ILMessageFilterExtensionContext : NSExtensionContext

/**
 Defer the current query request to the app extension's associated network service and receive a network response asynchronously.

 This causes the system to perform an HTTPS network request to a URL specified in the app extension's Info.plist, and the response
 to that HTTPS request (or an error) is returned asynchronously. See documentation for details regarding how this HTTPS request
 is formatted, restrictions on the URL, etc.

 @param completion Completion block containing either the network response to the HTTPS request or an error.
 */
- (void)deferQueryRequestToNetworkWithCompletion:(void (^)(ILNetworkResponse *_Nullable response, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  IdentityLookup.framework/Headers/ILMessageFilterAction.h
//
//  ILMessageFilterAction.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Describes an action to take in response to a received message.
typedef NS_ENUM(NSInteger, ILMessageFilterAction) {
    /// Insufficient information to determine an action to take. In a query response, has the effect of allowing the message to be shown normally.
    ILMessageFilterActionNone = 0,

    /// Allow the message to be shown normally.
    ILMessageFilterActionAllow = 1,

    /// Prevent the message from being shown normally.
    ILMessageFilterActionFilter = 2,
} API_AVAILABLE(ios(11.0));

NS_ASSUME_NONNULL_END