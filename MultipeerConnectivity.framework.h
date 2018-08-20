// ==========  MultipeerConnectivity.framework/Headers/MCNearbyServiceBrowser.h
//
// MCNearbyServiceBrowser.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import "MCPeerID.h"
#import "MCSession.h"

@protocol MCNearbyServiceBrowserDelegate;

/*!
   @class MCNearbyServiceBrowser
   @abstract
   MCNearbyServiceBrowser looks for nearby peers, and connects them to
   sessions.

   @discussion
   To create the MCNearbyServiceBrowser object and start browsing for
   nearby peers, a new MCPeerID should be created to represent the local
   peer, and a service type needs to be specified.

   The serviceType parameter is a short text string used to describe the
   app's networking protocol.  It should be in the same format as a
   Bonjour service type: up to 15 characters long and valid characters
   include ASCII lowercase letters, numbers, and the hyphen.  A short name
   that distinguishes itself from unrelated services is recommended; for
   example, a text chat app made by ABC company could use the service type
   "abc-txtchat". For more detailed information about service type
   restrictions, see RFC 6335, Section 5.1.

   A delegate that conforms to the MCNearbyServiceBrowserDelegate
   protocol must also be provided.  The delegate is notified when nearby
   peers are found and lost. No assumption should be made as to which queue
   the callbacks are called on.

   MCNearbyAdvertiser must be initialized with an MCPeerID object and a
   valid service type.

   See Bonjour APIs https://developer.apple.com/bonjour/ for more
   information about service types.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCNearbyServiceBrowser : NSObject
- (instancetype)initWithPeer:(MCPeerID *)myPeerID serviceType:(NSString *)serviceType NS_DESIGNATED_INITIALIZER;

// The methods -startBrowsingForPeers and -stopBrowsingForPeers are used to
// start and stop looking for nearby advertising peers.
- (void)startBrowsingForPeers;
- (void)stopBrowsingForPeers;

/*
   The method -invitePeer:toSession:withContext:timeout: sends an
   invitation to a peer, and when the peer accepts the invitation, adds
   the peer to the specified session.

   The invited peer will receive a -advertiser:
   didReceiveInvitationFromPeer:withContext:invitationHandler: callback.
   The context is passed through to the invited peer. It can be used to
   describe the session or pass some additional identification
   information to the invitee.

   The timeout parameter is seconds and should be a positive value.  If a
   timeout of <=0 is specified, a default value of 30 seconds will be
   used instead.
 */
- (void)invitePeer:(MCPeerID *)peerID
         toSession:(MCSession *)session
       withContext:(nullable NSData *)context
           timeout:(NSTimeInterval)timeout;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCNearbyServiceBrowserDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCNearbyServiceBrowserDelegate <NSObject>
// Found a nearby advertising peer.
- (void)        browser:(MCNearbyServiceBrowser *)browser
              foundPeer:(MCPeerID *)peerID
      withDiscoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info;

// A nearby peer has stopped advertising.
- (void)browser:(MCNearbyServiceBrowser *)browser lostPeer:(MCPeerID *)peerID;

@optional
// Browsing did not start due to an error.
- (void)browser:(MCNearbyServiceBrowser *)browser didNotStartBrowsingForPeers:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
// ==========  MultipeerConnectivity.framework/Headers/MCSession.h
//
// MCSession.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MCPeerID.h"
#import "MCError.h"

// MCSession send modes for the -sendData:toPeers:withMode:error: method.
typedef NS_ENUM (NSInteger, MCSessionSendDataMode) {
    MCSessionSendDataReliable,      // guaranteed reliable and in-order delivery
    MCSessionSendDataUnreliable     // sent immediately without queuing, no guaranteed delivery
} NS_ENUM_AVAILABLE (10_10, 7_0);

// Peer states.
typedef NS_ENUM (NSInteger, MCSessionState) {
    MCSessionStateNotConnected,     // not in the session
    MCSessionStateConnecting,       // connecting to this peer
    MCSessionStateConnected         // connected to the session
} NS_ENUM_AVAILABLE (10_10, 7_0);

// Encryption preference.
typedef NS_ENUM (NSInteger, MCEncryptionPreference) {
    MCEncryptionOptional = 0,                   // session preferred encryption but will accept unencrypted connections
    MCEncryptionRequired = 1,                   // session requires encryption
    MCEncryptionNone = 2,                       // session should not be encrypted
} NS_ENUM_AVAILABLE (10_10, 7_0);

// Minimum number of peers in a session.
MC_EXTERN NSUInteger const kMCSessionMinimumNumberOfPeers NS_AVAILABLE(10_10, 7_0);

// Maximum number of peers in a session.
MC_EXTERN NSUInteger const kMCSessionMaximumNumberOfPeers NS_AVAILABLE(10_10, 7_0);

@class NSProgress;
@protocol MCSessionDelegate;

/*!
   @class MCSession
   @abstract
   A MCSession facilitates communication among all peers in a multipeer
   session.

   @discussion
   To start a multipeer session with remote peers, a MCPeerID that
   represents the local peer needs to be supplied to the init method.

   Once a peer is added to the session on both sides, the delegate
   callback -session:peer:didChangeState: will be called with
   MCSessionStateConnected state for the remote peer.

   Data messages can be sent to a connected peer with the -sendData:
   toPeers:withMode:error: method.

   The receiver of data messages will receive a delegate callback
   -session:didReceiveData:fromPeer:.

   Resources referenced by NSURL (e.g. a file) can be sent to a connected
   peer with the -sendResourceAtURL:toPeer:withTimeout:completionHandler:
   method. The completionHandler will be called when the resource is fully
   received by the remote peer, or if an error occurred during
   transmission. The receiver of data messages will receive a delegate
   callbacks -session:didStartReceivingResourceWithName:fromPeer:
   withProgress: when it starts receiving the resource and -session:
   didFinishReceivingResourceWithName:fromPeer:atURL:withError:
   when the resource has been fully received.

   A byte stream can be sent to a connected peer with the
   -startStreamWithName:toPeer:error: method. On success, an
   NSOutputStream  object is returned, and can be used to send bytes to
   the remote peer once the stream is properly set up. The receiver of the
   byte stream will receive a delegate callback -session:didReceiveStream:
   withName:fromPeer:

   Delegate calls occur on a private serial queue. If your app needs to
   perform an action on a particular run loop or operation queue, its
   delegate method should explicitly dispatch or schedule that work.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCSession : NSObject

// Create a session with an MCPeerID for the local peer.
- (instancetype)initWithPeer:(MCPeerID *)myPeerID;

// Create a session with a security configuration.
// The securityIdentity argument is an array of
// [ SecIdentityRef, [ zero or more additional certs ] ].
- (instancetype)initWithPeer:(MCPeerID *)myPeerID
            securityIdentity:(nullable NSArray *)identity
        encryptionPreference:(MCEncryptionPreference)encryptionPreference NS_DESIGNATED_INITIALIZER;

// Send a data message to a list of destination peers.
- (BOOL)sendData:(NSData *)data
         toPeers:(NSArray<MCPeerID *> *)peerIDs
        withMode:(MCSessionSendDataMode)mode
           error:(NSError * __nullable * __nullable)error;

// Disconnect from the session.
- (void)disconnect;

/*
   Send a resource referenced by an NSURL to a remote peer. The resource
   can be a file or an HTTP document. The completionHandler is called when
   the resource is received by the remote peer or if an error occurred.
   The remote peer will get a -session:didStartReceivingResourceWithName:
   fromPeer:withProgress callback when it starts receiving the resource and
   a -session:didFinishReceivingResourceWithName:fromPeer:atURL:withError:
   when the resource has been fully received.

   The primary mechanism for observing progress of the send should be to
   create an NSProgress using +progressWithTotalUnitCount,
   -becomeCurrentWithPendingUnitCount:, invoking this method, then calling
   -resignCurrent. This is described in the NSProgress documentation.
   Alternatively, if you wish to observe the progress directly instead
   of incorporating it into a larger operation, you may observe the
   NSProgress returned from this method.
 */
- (nullable NSProgress *)sendResourceAtURL:(NSURL *)resourceURL
                                  withName:(NSString *)resourceName
                                    toPeer:(MCPeerID *)peerID
                     withCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler;

// Start a named byte stream with the remote peer.
- (nullable NSOutputStream *)startStreamWithName:(NSString *)streamName
                                          toPeer:(MCPeerID *)peerID
                                           error:(NSError * __nullable * __nullable)error;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCSessionDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;

@property (readonly, NS_NONATOMIC_IOSONLY, nullable) NSArray *securityIdentity;

@property (readonly, NS_NONATOMIC_IOSONLY) MCEncryptionPreference encryptionPreference;

@property (readonly, NS_NONATOMIC_IOSONLY) NSArray<MCPeerID *> *connectedPeers;

@end

// Delegate methods for MCSession.
@protocol MCSessionDelegate <NSObject>

// Remote peer changed state.
- (void)session:(MCSession *)session peer:(MCPeerID *)peerID didChangeState:(MCSessionState)state;

// Received data from remote peer.
- (void)session:(MCSession *)session didReceiveData:(NSData *)data fromPeer:(MCPeerID *)peerID;

// Received a byte stream from remote peer.
- (void)    session:(MCSession *)session
   didReceiveStream:(NSInputStream *)stream
           withName:(NSString *)streamName
           fromPeer:(MCPeerID *)peerID;

// Start receiving a resource from remote peer.
- (void)                    session:(MCSession *)session
  didStartReceivingResourceWithName:(NSString *)resourceName
                           fromPeer:(MCPeerID *)peerID
                       withProgress:(NSProgress *)progress;

// Finished receiving a resource from remote peer and saved the content
// in a temporary location - the app is responsible for moving the file
// to a permanent location within its sandbox.
- (void)                    session:(MCSession *)session
 didFinishReceivingResourceWithName:(NSString *)resourceName
                           fromPeer:(MCPeerID *)peerID
                              atURL:(NSURL *)localURL
                          withError:(nullable NSError *)error;

@optional

// Made first contact with peer and have identity information about the
// remote peer (certificate may be nil).
- (void)        session:(MCSession *)session
  didReceiveCertificate:(nullable NSArray *)certificate
               fromPeer:(MCPeerID *)peerID
     certificateHandler:(void (^)(BOOL accept))certificateHandler;

@end

/*
   If the developer chooses to write their own discovery code (with
   NetServices, or the Bonjour C API directly), instead of using
   MCNearbyServiceAdvertiser/Browser or MCBrowserViewController, one can
   add a remote peer to a MCSession by following these steps:

   1. Exchange MCPeerID with the remote peer.  Start by serializing the
    MCPeerID object with NSKeyedArchiver, exchange the data with
    the remote peer, and then reconstruct the remote MCPeerID object
    with NSKeyedUnarchiver.
   2. Exchange connection data with the remote peer.  Start by calling the
    session's -nearbyConnectionDataForPeer:completionHandler: and send
    the connection data to the remote peer, once the completionHandler
    is called.
   3. When the remote peer's connection data is received, call the
    session's -connectPeer:withNearbyConnectionData: method to add the
    remote peer to the session.
 */

@interface MCSession (MCSessionCustomDiscovery)

// Gets the connection data for a remote peer.
- (void)nearbyConnectionDataForPeer:(MCPeerID *)peerID
              withCompletionHandler:(void (^)(NSData *connectionData, NSError * __nullable error))completionHandler;

// Connect a peer to the session once connection data is received.
- (void)connectPeer:(MCPeerID *)peerID withNearbyConnectionData:(NSData *)data;

// Cancel connection attempt with a peer.
- (void)cancelConnectPeer:(MCPeerID *)peerID;

@end
NS_ASSUME_NONNULL_END
// ==========  MultipeerConnectivity.framework/Headers/MCBrowserViewController.h
//
// MCBrowserViewController.h
// MultipeerConnectivity
//
// Copyright (c) 2013 Apple Inc. All rights reserved.
//
// This API provides a system-supplied user interface for selecting and
// connecting to another device for a multiplayer session.
//
// The API introduces MCBrowserViewController for this purpose, and
// should be used in conjunction with the MCSession API.
//

#import <UIKit/UIKit.h>
#import "MCNearbyServiceBrowser.h"

@protocol MCBrowserViewControllerDelegate;

/*!
   @class MCBrowserViewController
   @abstract The
   MCBrowserViewController class manages the system-supplied user
   interface for choosing peers to connect with for multipeer sessions.

   @discussion
   MCBrowserViewController manages presentation of nearby peers and the
   invite process for you. The invite process is driven by the user
   and handled by the peer picker and the MCNearbyServiceBrowser object
   it holds.

   MCBrowserViewController must be initialized with a
   MCNearbyServiceBrowser object and a MCSession object at init time.
   If the browser object's delegate is nil, the browser view controller
   will set itself as the browser's delegate. The session object will be
   used by the browser view controller during the invite process.
   A delegate that conforms to the MCBrowserViewControllerDelegate
   protocol must also be provided. The delegate is notified to decide
   whether to present a peer, when the user taps the done button, or when
   the users taps the cancel button. No assumption should be made as to
   which queue the callbacks are called on.

   When presented, the browser view controller looks for nearby peers,
   and allows the user to connect up to the specified maximum number of
   peers.  When the user taps on a nearby peer, the browser view
   controller will send an invitation to it.

   When the browser view controller is dismissed, it will stop looking
   for nearby peers.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCBrowserViewController : UIViewController <MCNearbyServiceBrowserDelegate>
// Create a browser view controller with a service type and a session.
- (instancetype)initWithServiceType:(NSString *)serviceType session:(MCSession *)session;
// Create a browser view controller with a programmatic browser
// and a session.
- (instancetype)initWithBrowser:(MCNearbyServiceBrowser *)browser session:(MCSession *)session NS_DESIGNATED_INITIALIZER;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCBrowserViewControllerDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY, nullable) MCNearbyServiceBrowser *browser;
@property (readonly, NS_NONATOMIC_IOSONLY) MCSession *session;
// The minimum number of peers the session should expect.
@property (assign, NS_NONATOMIC_IOSONLY) NSUInteger minimumNumberOfPeers;
// The maximum number of peers the session should expect.
@property (assign, NS_NONATOMIC_IOSONLY) NSUInteger maximumNumberOfPeers;

@end

@protocol MCBrowserViewControllerDelegate <NSObject>
// Notifies the delegate, when the user taps the done button.
- (void)browserViewControllerDidFinish:(MCBrowserViewController *)browserViewController;

// Notifies delegate that the user taps the cancel button.
- (void)browserViewControllerWasCancelled:(MCBrowserViewController *)browserViewController;

@optional
// Notifies delegate that a peer was found; discoveryInfo can be used to
// determine whether the peer should be presented to the user, and the
// delegate should return a YES if the peer should be presented; this method
// is optional, if not implemented every nearby peer will be presented to
// the user.
- (BOOL)browserViewController:(MCBrowserViewController *)browserViewController
      shouldPresentNearbyPeer:(MCPeerID *)peerID
            withDiscoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info;

@end
NS_ASSUME_NONNULL_END
// ==========  MultipeerConnectivity.framework/Headers/MCNearbyServiceAdvertiser.h
//
// MCNearbyServiceAdvertiser.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import "MCPeerID.h"
#import "MCSession.h"

@protocol MCNearbyServiceAdvertiserDelegate;

/*!
   @class MCNearbyServiceAdvertiser
   @abstract
   MCNearbyServiceAdvertiser advertises availability of the local peer,
   and handles invitations from nearby peers.

   @discussion
   To create the MCNearbyServiceAdvertiser object and start advertising
   to nearby peers, a new MCPeerID should be created to
   represent the local peer, and a service type needs to be specified.

   The serviceType parameter is a short text string used to describe the
   app's networking protocol.  It should be in the same format as a
   Bonjour service type: up to 15 characters long and valid characters
   include ASCII lowercase letters, numbers, and the hyphen.  A short
   name that distinguishes itself from unrelated services is recommended;
   for example, a text chat app made by ABC company could use the service
   type "abc-txtchat". For more detailed information about service type
   restrictions, see RFC 6335, Section 5.1.

   The discoveryInfo parameter is a dictionary of string key/value pairs
   that will be advertised for browsers to see. Both keys and values must
   be NSString objects. The content of discoveryInfo will be advertised
   within Bonjour TXT records, and keeping the dictionary small is good
   for keeping network traffic low.

   MCNearbyServiceAdvertiser must be initialized with an MCPeerID object
   and a valid service type. The discoveryInfo parameter is optional and
   may be nil.

   A delegate that conforms to the MCNearbyServiceAdvertiserDelegate protocol
   must be provided. No assumption should be made as to which queue the
   callbacks are called on.

   See Bonjour APIs https://developer.apple.com/bonjour/ for more
   information about service types.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCNearbyServiceAdvertiser : NSObject
- (instancetype)initWithPeer:(MCPeerID *)myPeerID
               discoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info
                 serviceType:(NSString *)serviceType NS_DESIGNATED_INITIALIZER;

// The methods -startAdvertisingPeer and -stopAdvertisingPeer are used to
// start and stop announcing presence to nearby browsing peers.
- (void)startAdvertisingPeer;
- (void)stopAdvertisingPeer;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCNearbyServiceAdvertiserDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;
@property (readonly, NS_NONATOMIC_IOSONLY, nullable) NSDictionary<NSString *, NSString *> *discoveryInfo;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCNearbyServiceAdvertiserDelegate <NSObject>
// Incoming invitation request.  Call the invitationHandler block with YES
// and a valid session to connect the inviting peer to the session.
- (void)            advertiser:(MCNearbyServiceAdvertiser *)advertiser
  didReceiveInvitationFromPeer:(MCPeerID *)peerID
                   withContext:(nullable NSData *)context
             invitationHandler:(void (^)(BOOL accept, MCSession *session))invitationHandler;

@optional
// Advertising did not start due to an error.
- (void)advertiser:(MCNearbyServiceAdvertiser *)advertiser didNotStartAdvertisingPeer:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
// ==========  MultipeerConnectivity.framework/Headers/MCPeerID.h
//
// MCPeerID.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
   @class MCPeerID
   @abstract
   MCPeerID represents a peer in a multipeer session.

   @discussion
    MCPeerID is used to reference a peer in a multipeer session.

    Use the init method -initWithDisplayName: to create a new ID for the
    local app, and associate a display name with the ID.

    Note that the displayName is intended for a UI element, and should
    be short and descriptive of the local peer.  The hard limit of
    displayName is 63 bytes in UTF8 encoding.  The displayName parameter
    may not be nil or an empty string.

    MCPeerID conforms to NSCopying and can be used as a key in a
    NSDictionary.
 */

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCPeerID : NSObject <NSCopying, NSSecureCoding>
- (instancetype)initWithDisplayName:(NSString *)myDisplayName NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *displayName;
@end
NS_ASSUME_NONNULL_END
// ==========  MultipeerConnectivity.framework/Headers/MultipeerConnectivity.h
//
// MultipeerConnectivity.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

// MultipeerConnectivity headers
#import <MultipeerConnectivity/MCError.h>
#import <MultipeerConnectivity/MCPeerID.h>
#import <MultipeerConnectivity/MCNearbyServiceAdvertiser.h>
#import <MultipeerConnectivity/MCNearbyServiceBrowser.h>
#import <MultipeerConnectivity/MCSession.h>
#import <MultipeerConnectivity/MCBrowserViewController.h>
#import <MultipeerConnectivity/MCAdvertiserAssistant.h>
// ==========  MultipeerConnectivity.framework/Headers/MCAdvertiserAssistant.h
//
// MCAdvertiserAssistant.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import "MCPeerID.h"
#import "MCSession.h"

@protocol MCAdvertiserAssistantDelegate;

/*!
   @class MCAdvertiserAssistant
   @abstract
   MCAdvertiserAssistant is a convenience class that handles advertising,
   presents incoming invitations to the user and handles user's responses.

   @discussion
   To create the MCAdvertiserAssistant object a new MCPeerID should be
   created to represent the local peer, and a service type needs to be
   specified.

   The serviceType parameter is a short text string used to describe the
   app's networking protocol.  It should be in the same format as a
   Bonjour service type: up to 15 characters long and valid characters
   include ASCII lowercase letters, numbers, and the hyphen. A short name
   that distinguishes itself from unrelated services is recommended;
   for example, a text chat app made by ABC company could use the service
   type "abc-txtchat".

   The discoveryInfo parameter is a dictionary of string key/value pairs
   that will be advertised for browsers to see. Both keys and values must
   be NSString objects. The content of discoveryInfo will be advertised
   within Bonjour TXT records, and keeping the dictionary small is good
   for keeping network traffic low.

   A delegate that conforms to the MCAdvertiserAssistantDelegate protocol
   must be provided. No assumption should be made as to which queue the
   callbacks are called on.

   See Bonjour APIs https://developer.apple.com/bonjour/ for more
   information about service types.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCAdvertiserAssistant : NSObject
- (instancetype)initWithServiceType:(NSString *)serviceType
                      discoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info
                            session:(MCSession *)session NS_DESIGNATED_INITIALIZER;

// The methods -start and -stop are used to start and stop the assistant.
- (void)start;
- (void)stop;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCAdvertiserAssistantDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCSession *session;
@property (readonly, NS_NONATOMIC_IOSONLY, nullable) NSDictionary<NSString *, NSString *> *discoveryInfo;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCAdvertiserAssistantDelegate <NSObject>
@optional

// An invitation will be presented to the user.
- (void)advertiserAssistantWillPresentInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

// An invitation was dismissed from screen.
- (void)advertiserAssistantDidDismissInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

@end
NS_ASSUME_NONNULL_END

// ==========  MultipeerConnectivity.framework/Headers/MCError.h
//
// MCError.h
// MultipeerConnectivity
//
// Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef MC_EXTERN
#ifdef __cplusplus
#define MC_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define MC_EXTERN extern __attribute__((visibility("default")))
#endif
#endif

#define MC_EXTERN_CLASS __attribute__((visibility("default")))

#ifndef MC_EXTERN_WEAK
#define MC_EXTERN_WEAK MC_EXTERN __attribute__((weak_import))
#endif

MC_EXTERN_WEAK NSString *const MCErrorDomain;

typedef NS_ENUM (NSInteger, MCErrorCode) {
    MCErrorUnknown = 0,
    MCErrorNotConnected = 1,
    MCErrorInvalidParameter = 2,
    MCErrorUnsupported = 3,
    MCErrorTimedOut  = 4,
    MCErrorCancelled = 5,
    MCErrorUnavailable = 6,
} NS_ENUM_AVAILABLE (10_10, 7_0);
