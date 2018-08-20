// ==========  NetworkExtension.framework/Headers/NWEndpoint.h
//
//  NWEndpoint
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWEndpoint
 * @discussion NWEndpoint is a generic class to represent network endpoints, such as a port on a remote server.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWEndpoint : NSObject

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEVPNProtocolIPSec.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NEVPNIKEAuthenticationMethod
 * @abstract Internet Key Exchange (IKE) authentication methods used to authenticate with the IPSec server.
 */
typedef NS_ENUM(NSInteger, NEVPNIKEAuthenticationMethod) {
	/*! @const NEVPNIKEAuthenticationMethodNone Do not authenticate with the IPSec server */
	NEVPNIKEAuthenticationMethodNone = 0,
	/*! @const NEVPNIKEAuthenticationMethodCertificate Use a certificate and private key as the authentication credential */
	NEVPNIKEAuthenticationMethodCertificate = 1,
	/*! @const NEVPNIKEAuthenticationMethodSharedSecret Use a shared secret as the authentication credential */
	NEVPNIKEAuthenticationMethodSharedSecret = 2,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEVPNProtocolIPSec
 * @discussion The NEVPNProtocolIPSec class declares the programmatic interface of an object that manages the IPSec-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 1 for key negotiation.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNProtocolIPSec : NEVPNProtocol

/*!
 * @property authenticationMethod
 * @discussion The method used to authenticate with the IPSec server. Note that if this property is set to NEVPNIKEAuthenticationMethodNone, extended authentication will still be negotiated if useExtendedAuthentication is set to YES.
 */
@property NEVPNIKEAuthenticationMethod authenticationMethod NS_AVAILABLE(10_10, 8_0);

/*!
 * @property useExtendedAuthentication
 * @discussion A flag indicating if extended authentication will be negotiated. This authentication is in addition to the IKE authentication used to authenticate the endpoints of the IKE session.
 *   For IKE version 1, when this flag is set X-Auth authentication will be negotiated as part of the IKE session, using the username and password properties as the credential.
 *   For IKE version 2, when this flag is set EAP authentication will be negotiated as part of the IKE session, using the username, password, and/or identity properties as the credential depending on which EAP method the server requires.
 */
@property BOOL useExtendedAuthentication NS_AVAILABLE(10_10, 8_0);

/*!
 * @property sharedSecretReference
 * @discussion A persistent reference to a keychain item of class kSecClassGenericPassword containing the IKE shared secret.
 */
@property (copy, nullable) NSData *sharedSecretReference NS_AVAILABLE(10_10, 8_0);

/*!
 * @property localIdentifier
 * @discussion A string identifying the local IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *localIdentifier NS_AVAILABLE(10_10, 8_0);

/*!
 * @property remoteIdentifier
 * @discussion A string identifying the remote IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *remoteIdentifier NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NETunnelProviderSession.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNConnection.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETunnelProviderSession.h
 * @discussion This file declares the NETunnelProviderSession API. The NETunnelProviderSession API is used to control network tunnel services provided by NETunnelProvider implementations.
 *
 * This API is part of NetworkExtension.framework.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NETunnelProviderSession : NEVPNConnection

/*!
 * @method startTunnelWithOptions:andReturnError:
 * @discussion This function is used to start the tunnel using the configuration associated with this connection object. The tunnel connection process is started and this function returns immediately.
 * @param options A dictionary that will be passed as-is to the tunnel provider during the process of starting the tunnel.
 * @param error If the tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startTunnelWithOptions:(nullable NSDictionary<NSString *,id> *)options andReturnError:(NSError **)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method stopTunnel
 * @discussion This function is used to stop the tunnel. The tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopTunnel NS_AVAILABLE(10_11, 9_0);

/*!
 * @method sendProviderMessage:responseHandler:
 * @discussion This function sends a message to the NETunnelProvider and provides a way to receive a response.
 * @param messageData An NSData object containing the message to be sent.
 * @param error If the message was sent successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @param responseHandler A block that handles the response. Can be set to nil if no response is expected.
 * @return YES if the message was sent successfully, NO if an error occurred.
 */
- (BOOL)sendProviderMessage:(NSData *)messageData returnError:(NSError **)error responseHandler:(nullable void (^)( NSData * __nullable responseData))responseHandler NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END// ==========  NetworkExtension.framework/Headers/NEVPNManager.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

/*!
 * @file NEVPNManager.h
 * @discussion This file declares the NEVPNManager API. The NEVPNManager API is used to configure and control Virtual Private Network (VPN) tunnels.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create VPN configurations. The VPN tunnel can be started manually, or On Demand rules can be created that will start the VPN tunnel automatically when specific network events occur.
 */

#if !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
#import <Security/Security.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEVPN_EXPORT extern "C"
#else
#define NEVPN_EXPORT extern
#endif

@class NEVPNConnection;
@class NEVPNProtocol;
@class NEOnDemandRule;

/*!
 * @typedef NEVPNError
 * @abstract VPN error codes
 */
typedef NS_ENUM(NSInteger, NEVPNError) {
    /*! @const NEVPNErrorConfigurationInvalid The VPN configuration is invalid */
    NEVPNErrorConfigurationInvalid = 1,
    /*! @const NEVPNErrorConfigurationDisabled The VPN configuration is not enabled. */
    NEVPNErrorConfigurationDisabled = 2,
    /*! @const NEVPNErrorConnectionFailed The connection to the VPN server failed. */
    NEVPNErrorConnectionFailed = 3,
    /*! @const NEVPNErrorConfigurationStale The VPN configuration is stale and needs to be loaded. */
    NEVPNErrorConfigurationStale = 4,
    /*! @const NEVPNErrorConfigurationReadWriteFailed The VPN configuration cannot be read from or written to disk. */
    NEVPNErrorConfigurationReadWriteFailed = 5,
    /*! @const NEVPNErrorConfigurationUnknown An unknown configuration error occurred. */
    NEVPNErrorConfigurationUnknown = 6,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @const NEVPNErrorDomain The VPN error domain */
NEVPN_EXPORT NSString * const NEVPNErrorDomain NS_AVAILABLE(10_10, 8_0);

/*! @const NEVPNConfigurationChangeNotification Name of the NSNotification that is posted when the VPN configuration changes. */
NEVPN_EXPORT NSString * const NEVPNConfigurationChangeNotification NS_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEVPNManager
 * @discussion The NEVPNManager class declares the programmatic interface for an object that manages Virtual Private Network (VPN) configurations.
 *
 * NEVPNManager declares methods and properties for configuring and controlling a VPN.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEVPNManager object for the calling process.
 */
+ (NEVPNManager *)sharedManager NS_AVAILABLE(10_10, 8_0);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current VPN configuration from the caller's VPN preferences.
 * @param completionHandler A block that will be called on the main thread when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the VPN configuration from the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN is disabled and the VPN On Demand rules are de-activated.
 * @param completionHandler A block that will be called on the main thread when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the VPN configuration in the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN On Demand rules are activated.
 *
 * @param completionHandler A block that will be called on the main thread when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

#if !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
/*!
 * @method setAuthorization:
 * @discussion This function sets an authorization object that can be used to obtain the authorization rights necessary to modify the system VPN configuration.
 * @param authorization The AuthorizationRef to use to obtain rights.
 */
- (void)setAuthorization:(AuthorizationRef)authorization NS_AVAILABLE(10_10, NA);
#endif

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules NS_AVAILABLE(10_10, 8_0);

/*!
 * @property onDemandEnabled
 * @discussion Toggles VPN On Demand.
 */
@property (getter=isOnDemandEnabled) BOOL onDemandEnabled NS_AVAILABLE(10_10, 8_0);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the VPN.
 */
@property (copy, nullable) NSString *localizedDescription NS_AVAILABLE(10_10, 8_0);

/*!
 * @property protocol
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocol NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use protocolConfiguration instead");

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocolConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property connection
 * @discussion The NEVPNConnection object used for controlling the VPN tunnel.
 */
@property (readonly) NEVPNConnection *connection NS_AVAILABLE(10_10, 8_0);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the VPN. Setting this property will disable VPN configurations of other apps. This property will be set to NO  when other VPN configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterDataProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterProvider.h>

@class NEFilterVerdict;
@class NEFilterNewFlowVerdict;
@class NEFilterDataVerdict;
@class NEFilterRemediationVerdict;
@class NEFilterFlow;
@class NEFilterBrowserFlow;
@class NEFilterSocketFlow;

NS_ASSUME_NONNULL_BEGIN

#define NEFILTER_DATA_PROVIDER_EXTERN extern

/*!
 * @file NEFilterDataProvider.h
 * @discussion This file declares the NEFilterDataProvider. The NEFilterDataProvider API is used to implement the portion of a content filtering solution that is responsible for making filtering decisions about network data flows.
 */

/*!
 * @interface NEFilterDataProvider
 * @discussion The NEFilterDataProvider class declares the programmatic interface for an object that evaluates network data flows based on a set of locally-available rules and makes decisions about whether to block or allow the flows.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterDataProvider : NEFilterProvider

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework when a filtering decision needs to be made about a new network data flow. Subclasses must override this method to implement the steps necessary to match the flow against some locally stored rules and return an appropriate verdict.
 * @param flow An NEFilterFlow object containing details about the new flow.
 * @return An NEFilterNewFlowVerdict object containing the veridct for the new flow.
 */
- (NEFilterNewFlowVerdict *)handleNewFlow:(NEFilterFlow *)flow NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleInboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some inbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's data of readBytes.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleOutboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some outbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param readBytesStartOffset The offset in bytes from the start of the flow's data of readBytes.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleInboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the inbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataCompleteForFlow:(NEFilterFlow *)flow NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleOutboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the outbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataCompleteForFlow:(NEFilterFlow *)flow NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleRemediationForFlow:
 * @discussion This function is called by the framework after the user requests remediation for a blocked flow. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterRemediationVerdict verdict for the flow.
 */
- (NEFilterRemediationVerdict *)handleRemediationForFlow:(NEFilterFlow *)flow NS_AVAILABLE(NA, 9_0);


/*!
 * @meethod handleRulesChanged
 * @discussion This function is called by the framework when -[NEFilterControlProvider notifyRulesChanged] is called. Subclasses should override this method to reload new rules from disk.
 */
- (void)handleRulesChanged NS_AVAILABLE(NA, 9_0);

@end

/*!
 * @interface NEFilterDataVerdict
 * @discussion The NEFilterDataVerdict class declares the programmatic interface of an object that is the verdict for a flow of network data after some of the data has been seen by the filter.
 *
 * NEFilterDataVerdict is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterDataVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *) allowVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *) dropVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url. Passing nil will result into data provider being notified with the callback handleRemediationForFlow:
 * @param remediationButtonTextMapKey Remediation button map key used by the data plugin to get the remediation button text. Passing nil will set the button text to "Request Access"
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)remediateVerdictWithRemediationURLMapKey:(nullable NSString *)remediationURLMapKey remediationButtonTextMapKey:(nullable NSString *)remediationButtonTextMapKey NS_AVAILABLE(NA, 9_0);

/*!
 * @method dataVerdictWithPassBytes:peekBytes:
 * @discussion This class method returns a data verdict indicating that the filter is passing a given number of bytes through the filter and needs to see a given number of bytes after the bytes that are passed.
 * @param passBytes The number of bytes to pass through the filter. Note that the framework does not pass the bytes to the destination until a "final" allow/drop/remediate verdict is returned.
 * @param peekBytes The number of bytes after the end of the bytes passed that the filter wants to see in the next call to -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:] or -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The data flow verdict.
 */
+ (NEFilterDataVerdict *)dataVerdictWithPassBytes:(NSUInteger)passBytes peekBytes:(NSUInteger)peekBytes NS_AVAILABLE(NA, 9_0);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the data flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)needRulesVerdict NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @interface NEFilterRemediationVerdict
 * @discussion The NEFilterRemediationVerdict class declares the programmatic interface of an object that is the verdict for a flow which has been blocked by the filter, but the user has made a request for remediation.
 *
 * NEFilterRemediationVerdict is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterRemediationVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) allowVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) dropVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the remediation. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) needRulesVerdict NS_AVAILABLE(NA, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEDNSSettings.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSSettings.h
 * @discussion This file declares the NEDNSSettings API. The NEDNSSettings API is used to specify DNS settings for Network Extensions.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEDNSSettings
 * @discussion The NEDNSSettings class declares the programmatic interface for an object that contains DNS settings.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEDNSSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithServers:
 * @discussion Initialize a newly-allocated NEDNSSettings object.
 * @param servers An array of DNS server IP address strings.
 */
- (instancetype)initWithServers:(NSArray<NSString *> *)servers NS_AVAILABLE(10_11, 9_0);

/*!
 * @property servers
 * @discussion An array of DNS server address strings.
 */
@property (readonly) NSArray<NSString *> *servers NS_AVAILABLE(10_11, 9_0);

/*! 
 * @property searchDomains
 * @discussion An array of DNS server search domain strings.
 */
@property (copy, nullable) NSArray<NSString *> *searchDomains NS_AVAILABLE(10_11, 9_0);

/*!
 * @property domainName
 * @discussion A string containing the DNS domain.
 */
@property (copy, nullable) NSString *domainName NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain strings. If this property is non-nil, the DNS settings will only be used to resolve host names within the specified domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomainsNoSearch
 * @discussion A boolean indicating if the match domains should be appended to the search domain list.  Default is NO (match domains will be appended to the search domain list).
 */
@property BOOL matchDomainsNoSearch NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWTCPConnection.h
//
//  NWTCPConnection.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Security/Security.h>

NS_ASSUME_NONNULL_BEGIN

@class NWEndpoint;
@class NWPath;
@class NWTCPConnection;

/*!
 * @typedef NWTCPConnectionState
 * @abstract Defined connection states. New types may be defined in the future.
 */
typedef NS_ENUM(NSInteger, NWTCPConnectionState) {
	/*! @constant NWTCPConnectionStateInvalid The connection is in an invalid or uninitialized state */
	NWTCPConnectionStateInvalid			= 0,

	/*! @constant NWTCPConnectionStateConnecting The connection is attempting */
	NWTCPConnectionStateConnecting		= 1,

	/*! @constant NWTCPConnectionStateWaiting The connection has attempted but failed. It is now
	 *		waiting for better condition(s) before trying again.
	 */
	NWTCPConnectionStateWaiting			= 2,

	/*! @constant NWTCPConnectionStateConnected The connection is established. It is now possible
	 *		to transfer data. If TLS is in use, the TLS handshake would have finished when the connection
	 *		is in this state.
	 */
	NWTCPConnectionStateConnected		= 3,

	/*! @constant NWTCPConnectionStateDisconnected The connection is disconnected. It is no longer
	 *		possible to transfer data. The application should call cancellation method to clean up resources
	 *		when the connection is in this state.
	 */
	NWTCPConnectionStateDisconnected	= 4,

	/*! @constant NWTCPConnectionStateCancelled The connection is cancelled. This is triggered by
	 *		the cancellation method.
	 */
	NWTCPConnectionStateCancelled		= 5,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NWTCPConnection
 * @discussion Establish TCP connections to an endpoint, and send and receive data on the TCP connection.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWTCPConnection : NSObject

/*!
 * @method initWithUpgradeForConnection:
 * @discussion This convenience initializer can be used to create a new connection that would only
 * 		be connected if there exists a better path (as determined by the system) to the destination
 * 		endpoint of the original connection. It will be initialized using the same destination endpoint
 * 		and set of parameters from the original connection.
 *
 * 		If the original connection becomes disconnected or cancelled, the new "upgrade" connection
 * 		would automatically be considered better.
 *
 *		The caller should create an NWTCPConnection and watch for the hasBetterPath property.
 *		When this property is YES, the caller should attempt to create a new upgrade
 *		connection, with the goal to start transferring data on the new better path as soon as
 *		possible to reduce power and potentially monetary cost. When the new upgrade connection
 *		becomes connected and when the caller wraps up the previous caller session on
 *		the original connection, the caller can start using the new upgrade connection and
 *		tear down the original one.
 *
 * @param connection The original connection from which the caller will upgrade
 * @return An initialized NWTCPConnection
 */
- (instancetype)initWithUpgradeForConnection:(NWTCPConnection *)connection NS_AVAILABLE(10_11, 9_0);

/*!
 * @property state
 * @discussion The status of the connection. Use KVO to watch this property to get updates.
 */
@property (readonly) NWTCPConnectionState state NS_AVAILABLE(10_11, 9_0);

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise. Use KVO to watch this property.
 */
@property (readonly, getter=isViable) BOOL viable NS_AVAILABLE(10_11, 9_0);

/*!
 * @property hasBetterPath
 * @discussion YES if the system determines there is a better path the destination can be reached if
 *		the caller creates a new connection using the same endpoint and parameters. This can
 *		be done using the convenience upgrade initializer method.
 *		Use KVO to watch this property to get updates.
 */
@property (readonly) BOOL hasBetterPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @property endpoint
 * @discussion The destination endpoint with which this connection was created.
 */
@property (readonly) NWEndpoint *endpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property connectedPath
 * @discussion The network path over which the connection was established. The caller can query
 *		additional properties from the NWPath object for more information.
 *
 * 		Note that this contains a snapshot of information at the time of connection establishment
 * 		for this connection only. As a result, some underlying properties might change in time and
 * 		might not reflect the path for other connections that might be established at different times.
 */
@property (readonly, nullable) NWPath *connectedPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @property localAddress
 * @discussion The IP address endpoint from which the connection was connected.
 */
@property (readonly, nullable) NWEndpoint *localAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property remoteAddress
 * @discussion The IP address endpoint to which the connection was connected.
 */
@property (readonly, nullable) NWEndpoint *remoteAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property txtRecord
 * @discussion When the connection is connected to a Bonjour service endpoint, the TXT record associated
 * 		with the Bonjour service is available via this property. Beware that the value comes from
 * 		the network. Care must be taken when parsing this potentially malicious value.
 */
@property (readonly, nullable) NSData *txtRecord NS_AVAILABLE(10_11, 9_0);

/*!
 * @property error
 * @discussion The connection-wide error property indicates any fatal error that occurred while
 * 		processing the connection or performing data reading or writing.
 */
@property (readonly, nullable) NSError *error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method cancel:
 * @discussion Cancel the connection. This will clean up the resources associated with this object
 * 		and transition this object to NWTCPConnectionStateCancelled state.
 */
- (void)cancel NS_AVAILABLE(10_11, 9_0);

/*!
 * @method readLength:completionHandler:
 * @discussion Read "length" number of bytes. See readMinimumLength:maximumLength:completionHandler:
 * 		for a complete discussion of the callback behavior.
 * @param length The exact number of bytes the application wants to read
 *		for a complete discussion of the callback behavior.
 * @param length The exact number of bytes the caller wants to read
 * @param completion The completion handler to be invoked when there is data to read or an error occurred
 */
- (void)readLength:(NSUInteger)length completionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completion NS_AVAILABLE(10_11, 9_0);

/*!
 * @method readMinimumLength:maximumLength:completionHandler:
 *
 * @discussion Read the requested range of bytes. The completion handler will be invoked when:
 * 		- Exactly "length" number of bytes have been read. 'data' will be non-nil.
 *
 * 		- Fewer than "length" number of bytes, including 0 bytes, have been read, and the connection's
 * 		read side has been closed. 'data' might be nil, depending on whether there was any data to be
 * 		read when the connection's read side was closed.
 *
 * 		- Some fatal error has occurred, and 'data' will be nil.
 *
 * 		To know when to schedule a read again, check for the condition whether an error has occurred.
 *
 *		For better performance, the caller should pick the effective minimum and maximum lengths.
 *		For example, if the caller absolutely needs a specific number of bytes before it can
 *		make any progress, use that value as the minimum. The maximum bytes can be the upperbound
 *		that the caller wants to read. Typically, the minimum length can be the caller
 *		protocol fixed-size header and the maximum length can be the maximum size of the payload or
 *		the size of the current read buffer.
 *
 * @param minimum The minimum number of bytes the caller wants to read
 * @param maximum The maximum number of bytes the caller wants to read
 * @param completion The completion handler to be invoked when there is data to read or an error occurred
 */
- (void)readMinimumLength:(NSUInteger)minimum maximumLength:(NSUInteger)maximum completionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completion NS_AVAILABLE(10_11, 9_0);

/*!
 * @method write:completionHandler:
 * @discussion Write the given data object content. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param data The data object whose content will be written
 * @param completion The completion handler to be invoked when the data content has been written or an error has occurred.
 * 		If the error is nil, the write succeeded and the caller can write more data.
 */
- (void)write:(NSData *)data completionHandler:(void (^)(NSError * __nullable error))completion NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeClose:
 * @discussion Close this connection's write side such that further write requests won't succeed.
 * 		Note that this has the effect of closing the read side of the peer connection.
 * 		When the connection's read side and write side are closed, the connection is considered
 * 		disconnected and will transition to the appropriate state.
 */
- (void)writeClose NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @protocol NWTCPConnectionAuthenticationDelegate
 * @discussion Allows the caller to take custom actions on some connection events.
 */
@protocol NWTCPConnectionAuthenticationDelegate <NSObject>
@optional

/*!
 * @method shouldProvideIdentityForConnection:
 * @discussion The caller can implement this optional protocol method to decide whether it
 *		wants to provide the identity for this connection for authentication. If this delegate
 *		method is not implemented, the return value will default to YES if
 *		provideIdentityForConnection:completionHandler: is implemented.
 * @param connection The connection sending this message
 * @return YES to provide the identity for this connection, in which case, the delegate method
 *		provideIdentityForConnection:completionHandler: will be called.
 */
- (BOOL)shouldProvideIdentityForConnection:(NWTCPConnection *)connection;

/*!
 * @method provideIdentityForConnection:completionHandler:
 * @discussion The caller can implement this optional protocol method to provide the identity
 *		and an optional certificate chain to be used for authentication.
 * @param connection The connection sending this message
 * @param completion The completion handler for passing identity and certificate chain to the connection.
 *		The "identity" argument is required and must not be nil. The "certificateChain" argument is optional,
 *		and is an array of one or more SecCertificateRef objects. The certificate chain must contain objects
 *		of type SecCertificateRef only. If the certificate chain is set, it will be used. Otherwise, the leaf
 *		certificate will be extracted from the SecIdentityRef object and will be used for authentication.
 *
 *		The caller is responsible for keeping the argument object(s) alive for the duration of the
 *		completion handler invocation.
 */
- (void)provideIdentityForConnection:(NWTCPConnection *)connection
				   completionHandler:(void (^)(SecIdentityRef identity, NSArray<id> *certificateChain))completion;

/*!
 * @method shouldEvaluateTrustForConnection:
 * @discussion The caller can implement this optional protocol method to decide whether it
 *		wants to take over the default trust evaluation for this connection. If this delegate method
 *		is not implemented, the return value will default to YES if
 *		provideIdentityForConnection:completionHandler: is implemented.
 * @param connection The connection sending this message
 * @return YES to take over the default trust evaluation, in which case, the delegate method
 *		evaluateTrustForConnection:peerCertificateChain:completionHandler: will be called.
 */
- (BOOL)shouldEvaluateTrustForConnection:(NWTCPConnection *)connection;

/*!
 * @method evaluateTrustForConnection:peerCertificateChain:completionHandler:
 * @discussion The caller can implement this optional protocol method to set up custom policies
 *		for peer certificate trust evaluation. If the delegate method is implemented, the caller
 *		is responsible for creating and setting up the SecTrustRef object and passing it to the
 *		completion handler. Otherwise, the default trust evaluation policy is used for the connection.
 * @param connection The connection sending this message
 * @param peerCertificateChain The peer certificate chain
 * @param completion The completion handler for passing the SecTrustRef object to the connection.
 *		The SecTrustRef object "trust" is required and must not be nil. It will be evaluated using
 *		SecTrustEvaluate() if necessary. The caller is responsible for keeping the argument object
 *		alive for the duration of the completion handler invocation.
 */
- (void)evaluateTrustForConnection:(NWTCPConnection *)connection
			  peerCertificateChain:(NSArray<id> *)peerCertificateChain
				 completionHandler:(void (^)(SecTrustRef trust))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEAppRule.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppRule.h
 * @discussion This file declares the NEAppRule API. The NEAppRule API is used to create rules that match network traffic by the source application of the traffic.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEAppRule
 * @discussion The NEAppRule class declares the programmatic interface for an object that contains the match conditions for a rule that is used to match network traffic originated by applications.
 *
 * NEAppRule is used in the context of a Network Extension configuration to specify what traffic should be made available to the Network Extension.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithSigningIdentifier:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier NS_AVAILABLE(NA, 9_0);

/*!
 * @method initWithSigningIdentifier:designatedRequirement:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 * @param designatedRequirement The designated requirement of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier designatedRequirement:(NSString *)designatedRequirement NS_AVAILABLE(10_11, NA);

/*!
 * @property matchSigningIdentifier
 * @discussion A string containing a signing identifier. If the code signature of the executable being evaluated has a signing identifier equal to this string and all other conditions of the rule match, then the rule matches.
 */
@property (readonly) NSString *matchSigningIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDesignatedRequirement
 * @discussion A string containing a designated requirement. If the code signature of the exectuable being evaluated has a designated requirement equal to this string and all other conditions of the rule match, then the rule matches. This property is required on Mac OS X.
 */
@property (readonly) NSString *matchDesignatedRequirement NS_AVAILABLE(10_11, NA);

/*!
 * @property matchPath
 * @discussion A string containing a file system path. If the file system path of the executable being evaluated is equal to this string and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSString *matchPath NS_AVAILABLE(10_11, NA);

/*!
 * @property matchDomains
 * @discussion An array of strings. If the destination host of the network traffic being evaluated has a suffix equal to one of the strings in this array and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSArray *matchDomains NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NWTLSParameters.h
//
//  NWUDPSession.h
//  Network
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NWTLSParameters : NSObject

/*!
 * @property TLSSessionID
 * @discussion The session ID for the associated connection, used for TLS session resumption.
 *		This property is optional when using TLS.
 */
@property (nullable, copy) NSData *TLSSessionID NS_AVAILABLE(10_11, 9_0);

/*!
 * @property SSLCipherSuites
 * @discussion The set of allowed cipher suites, as defined in <Security/CipherSuite.h>.
 *		If set to nil, the default cipher suites will be used.
 */
@property (nullable, copy) NSSet<NSNumber *> *SSLCipherSuites NS_AVAILABLE(10_11, 9_0);

/*!
 * @property minimumSSLProtocolVersion
 * @discussion The minimum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version older than the minimum.
 */
@property (assign) NSUInteger minimumSSLProtocolVersion NS_AVAILABLE(10_11, 9_0);

/*!
 * @property maximumSSLProtocolVersion
 * @discussion The maximum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version newer than the maximum.
 *		This property should be used with caution, since it may limit the use of preferred
 *		SSL protocols.
 */
@property (assign) NSUInteger maximumSSLProtocolVersion NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEFilterProviderConfiguration.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFilterProviderConfiguration
 * @discussion The NEFilterProviderConfiguration class declares the programmatic interface of an object that configures a plugin-based content filter.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEFilterProviderConfiguration : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property filterBrowsers
 * @discussion If YES, the filter plugin will be allowed to filter browser traffic. If NO, the filter plugin will not see any browser flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterBrowsers NS_AVAILABLE(10_11, 9_0);

/*!
 * @property filterSockets
 * @discussion If YES, the filter plugin will be allowed to filter socket traffic. If NO, the filter plugin will not see any socket flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterSockets NS_AVAILABLE(10_11, 9_0);

/*!
 * @property vendorConfiguration
 * @discussion An optional dictionary of plugin-specific keys to be passed to the plugin.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *vendorConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property serverAddress
 * @discussion The optional address of the server used to support the filter.
 */
@property (copy, nullable) NSString *serverAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property username
 * @discussion The optional username associated with the filter.
 */
@property (copy, nullable) NSString *username NS_AVAILABLE(10_11, 9_0);

/*!
 * @property organization
 * @discussion The optional organization associated with the filter.
 */
@property (copy, nullable) NSString *organization NS_AVAILABLE(10_11, 9_0);

/*!
 * @property passwordReference
 * @discussion The optional password keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *passwordReference NS_AVAILABLE(10_11, 9_0);

/*!
 * @property identityReference
 * @discussion The optional certificate identity keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *identityReference NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEIPv4Settings.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEIPv4Settings.h
 * @discussion This file declares the NEIPv4Settings API. The NEIPv4Settings API is used to specify IPv4 settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEIPv4Route;

/*!
 * @interface NEIPv4Settings
 * @discussion The NEIPv4Settings class declares the programmatic interface for an object that contains IPv4 settings.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv4Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:subnetMasks:
 * @discussion Initialize a newly-allocated NEIPv4Settings object.
 * @param addresses An array of IPv4 addresses represented as dotted decimal strings.
 * @param subnetMasks An array of IPv4 subnet masks represented as dotted decimal strings.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses subnetMasks:(NSArray<NSString *> *)subnetMasks NS_AVAILABLE(10_11, 9_0);

/*!
 * @property addresses
 * @discussion An array of IPv4 addresses represented as dotted decimal strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses NS_AVAILABLE(10_11, 9_0);

/*!
 * @property subnetMasks
 * @discussion An array of IPv4 subnet masks represented as dotted decimal strings. These subnet masks will be set along with their corresponding addresses from the addresses array on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *subnetMasks NS_AVAILABLE(10_11, 9_0);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *includedRoutes NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *excludedRoutes NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEIPv4Route
 * @discussion The NEIPv4Route class declares the programmatic interface for an object that contains settings for an IPv4 route.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv4Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:subnetMask:
 * @discussion Initialize a newly-allocated NEIPv4Route.
 * @param address The IPv4 address of the destination network.
 * @param subnetMask The subnet mask of the destination network.
 * @return The initialized NEIPv4Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address subnetMask:(NSString *)subnetMask NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationAddress
 * @discussion An IPv4 address represented as a dotted decimal string. 
 */
@property (readonly) NSString *destinationAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationSubnetMask
 * @discussion An IPv4 subnet mask represented as a dotted decimal string. This mask in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSString *destinationSubnetMask NS_AVAILABLE(10_11, 9_0);

/*!
 * @property gatewayAddress
 * @discussion The IPv4 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv4 default route.
 */
+ (NEIPv4Route * const)defaultRoute NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWPath.h
//
//  NWPath.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NWPathStatus
 * @abstract Path status values
 */
typedef NS_ENUM(NSInteger, NWPathStatus) {
	/*! @const NWPathStatusInvalid The path cannot be evaluated. */
	NWPathStatusInvalid = 0,
	/*! @const NWPathStatusSatisfied The path is ready to be used for traffic. */
	NWPathStatusSatisfied = 1,
	/*! @const NWPathStatusUnsatisfied The network for this connection is not available. */
	NWPathStatusUnsatisfied = 2,
	/*! @const NWPathStatusSatisfiable The path may become satisfied upon
	 *		a connection attempt. */
	NWPathStatusSatisfiable = 3,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NWPath
 * @discussion A network path, represented with NWPath, expresses the viability status and 
 *		properties of the path that a networking connection will take on the device. For example, 
 *		if the path status is NWPathStatusSatisfied, then a connection could use that path.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWPath : NSObject

/*!
 * @property status
 * @discussion The evaluated NWPathStatus of the NWPath.
 */
@property (readonly) NWPathStatus status NS_AVAILABLE(10_11, 9_0);

/*!
 * @property expensive
 * @discussion Returns YES is the path is considered expensive, as when using a cellular data plan.
 */
@property (readonly, getter=isExpensive) BOOL expensive NS_AVAILABLE(10_11, 9_0);

/*!
 * @method isEqualToPath:
 * @param path An NWPath object to compare.
 * @return YES if the two path objects have the same content, NO otherwise.
 */
- (BOOL)isEqualToPath:(NWPath *)path NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEVPNProtocolIKEv2.h
/*
 * Copyright (c) 2014-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocolIPSec.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NEVPNIKEv2EncryptionAlgorithm
 * @abstract IKEv2 Encryption Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2EncryptionAlgorithm) {
	/*! @const NEVPNIKEv2EncryptionAlgorithmDES Data Encryption Standard (DES) */
	NEVPNIKEv2EncryptionAlgorithmDES = 1,
	/*! @const NEVPNIKEv2EncryptionAlgorithm3DES Triple Data Encryption Algorithm (aka 3DES) */
	NEVPNIKEv2EncryptionAlgorithm3DES = 2,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128 Advanced Encryption Standard 128 bit (AES128) */
	NEVPNIKEv2EncryptionAlgorithmAES128 = 3,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256 Advanced Encryption Standard 256 bit (AES256) */
	NEVPNIKEv2EncryptionAlgorithmAES256 = 4,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128GCM Advanced Encryption Standard 128 bit (AES128GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES128GCM NS_ENUM_AVAILABLE(10_11, 8_3) = 5,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256GCM Advanced Encryption Standard 256 bit (AES256GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES256GCM NS_ENUM_AVAILABLE(10_11, 8_3) = 6,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2IntegrityAlgorithm
 * @abstract IKEv2 Integrity Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2IntegrityAlgorithm) {
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA96 SHA-1 96 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA96 = 1,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA160 SHA-1 160 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA160 = 2,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA256 SHA-2 256 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA256 = 3,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA384 SHA-2 384 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA384 = 4,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA512 SHA-2 512 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA512 = 5,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2DeadPeerDetectionRate
 * @abstract IKEv2 Dead Peer Detection Rates
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DeadPeerDetectionRate) {
	/*! @const NEVPNIKEv2DeadPeerDetectionRateNone Do not perform dead peer detection */
	NEVPNIKEv2DeadPeerDetectionRateNone = 0,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateLow Run dead peer detection once every 30 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateLow = 1,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateMedium Run dead peer detection once every 10 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateMedium = 2,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateHigh Run dead peer detection once every 1 minute. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateHigh = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2DiffieHellmanGroup
 * @abstract IKEv2 Diffie Hellman groups
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DiffieHellmanGroup) {
	/*! @const NEVPNIKEv2DiffieHellmanGroup0 Diffie Hellman group 0 */
	NEVPNIKEv2DiffieHellmanGroup0 = 0,
	/*! @const NEVPNIKEv2DiffieHellmanGroup1 Diffie Hellman group 1 */
	NEVPNIKEv2DiffieHellmanGroup1 = 1,
	/*! @const NEVPNIKEv2DiffieHellmanGroup2 Diffie Hellman group 2 */
	NEVPNIKEv2DiffieHellmanGroup2 = 2,
	/*! @const NEVPNIKEv2DiffieHellmanGroup5 Diffie Hellman group 5 */
	NEVPNIKEv2DiffieHellmanGroup5 = 5,
	/*! @const NEVPNIKEv2DiffieHellmanGroup14 Diffie Hellman group 14 */
	NEVPNIKEv2DiffieHellmanGroup14 = 14,
	/*! @const NEVPNIKEv2DiffieHellmanGroup15 Diffie Hellman group 15 */
	NEVPNIKEv2DiffieHellmanGroup15 = 15,
	/*! @const NEVPNIKEv2DiffieHellmanGroup16 Diffie Hellman group 16 */
	NEVPNIKEv2DiffieHellmanGroup16 = 16,
	/*! @const NEVPNIKEv2DiffieHellmanGroup17 Diffie Hellman group 17 */
	NEVPNIKEv2DiffieHellmanGroup17 = 17,
	/*! @const NEVPNIKEv2DiffieHellmanGroup18 Diffie Hellman group 18 */
	NEVPNIKEv2DiffieHellmanGroup18 = 18,
	/*! @const NEVPNIKEv2DiffieHellmanGroup19 Diffie Hellman group 19 */
	NEVPNIKEv2DiffieHellmanGroup19 = 19,
	/*! @const NEVPNIKEv2DiffieHellmanGroup20 Diffie Hellman group 20 */
	NEVPNIKEv2DiffieHellmanGroup20 = 20,
	/*! @const NEVPNIKEv2DiffieHellmanGroup21 Diffie Hellman group 21 */
	NEVPNIKEv2DiffieHellmanGroup21 = 21,
	
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2CertificateType
 * @abstract IKEv2 Certificate types
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2CertificateType) {
    /*! @const NEVPNIKEv2CertificateType RSA */
    NEVPNIKEv2CertificateTypeRSA = 1,
    /*! @const NEVPNIKEv2CertificateTypeECDSA256 ECDSA with p-256 curve */
    NEVPNIKEv2CertificateTypeECDSA256 = 2,
    /*! @const NEVPNIKEv2CertificateTypeECDSA384 ECDSA with p-384 curve */
    NEVPNIKEv2CertificateTypeECDSA384 = 3,
    /*! @const NEVPNIKEv2CertificateTypeECDSA521 ECDSA with p-521 curve */
    NEVPNIKEv2CertificateTypeECDSA521 = 4,
} NS_ENUM_AVAILABLE(10_11, 8_3);

/*!
 * @class NEVPNIKEv2SecurityAssociationParameters
 * @discussion The NEVPNIKEv2SecurityAssociationParameters class declares the programmatic interface of an object that manages parameters for an IPSec Security Association
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNIKEv2SecurityAssociationParameters : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property encryptionAlgorithm
 * @discussion The algorithm used by the Security Association to encrypt and decrypt data. Default is NEVPNIKEv2EncryptionAlgorithm3DES.
 */
@property NEVPNIKEv2EncryptionAlgorithm encryptionAlgorithm NS_AVAILABLE(10_10, 8_0);

/*!
 * @property integrityAlgorithm
 * @discussion The algorithm used by the Security Association to verify the integrity of data. Default is NEVPNIKEv2IntegrityAlgorithmSHA96. The IKE psedo-random function algorithm will be inferred based on the integrity algorithm.
 */
@property NEVPNIKEv2IntegrityAlgorithm integrityAlgorithm NS_AVAILABLE(10_10, 8_0);

/*!
 * @property diffieHellmanGroup
 * @discussion The Diffie Hellman group used by the Security Association. Default is NEVPNIKEv2DiffieHellmanGroup2.
 */
@property NEVPNIKEv2DiffieHellmanGroup diffieHellmanGroup NS_AVAILABLE(10_10, 8_0);

/*!
 * @property lifetimeMinutes
 * @discussion The life time of the Security Association, in minutes. Default is 60 for IKE Security Associations, and 30 for Child Security Associations. Before the lifetime is reached, IKEv2 will attempt to rekey the Security Association to maintain the connection.
 */
@property int32_t lifetimeMinutes NS_AVAILABLE(10_10, 8_0);

@end

/*!
 * @interface NEVPNProtocolIKEv2
 * @discussion The NEVPNProtocolIKEv2 class declares the programmatic interface of an object that manages the IKEv2-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 2 for key negotiation.
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNProtocolIKEv2 : NEVPNProtocolIPSec

/*!
 * @property deadPeerDetectionRate
 * @discussion How frequently the IKEv2 client will run the dead peer detection algorithm.  Default is NEVPNIKEv2DeadPeerDetectionRateMedium.
 */
@property NEVPNIKEv2DeadPeerDetectionRate deadPeerDetectionRate NS_AVAILABLE(10_10, 8_0);

/*!
 * @property serverCertificateIssuerCommonName
 * @discussion A string containing the Subject Common Name field of the Certificate Authority certificate that issued the IKEv2 server's certificate.
 */
@property (copy, nullable) NSString *serverCertificateIssuerCommonName NS_AVAILABLE(10_10, 8_0);

/*!
 * @property serverCertificateCommonName
 * @discussion A string containing the value to verify in the IKEv2 server certificate's Subject Common Name field.
 */
@property (copy, nullable) NSString *serverCertificateCommonName NS_AVAILABLE(10_10, 8_0);

/*!
 * @property certificateType
 * @discussion contains the type of certificate if an certificate is configured.  Default is RSA.
 */
@property NEVPNIKEv2CertificateType certificateType NS_AVAILABLE(10_11, 8_3);

/*!
 * @property useConfigurationAttributeInternalIPSubnet
 * @discussion Boolean indicating if client should use INTERNAL_IP4_SUBNET / INTERNAL_IP6_SUBNET attributes.  Default is False.
 */
@property BOOL useConfigurationAttributeInternalIPSubnet NS_AVAILABLE(10_11, 9_0);

/*!
 * @property IKESecurityAssociationParameters
 * @discussion Parameters for the IKE SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *IKESecurityAssociationParameters NS_AVAILABLE(10_10, 8_0);

/*!
 * @property childSecurityAssociationParameters
 * @discussion Parameters for the child SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *childSecurityAssociationParameters NS_AVAILABLE(10_10, 8_0);

/*!
 * @property disableMOBIKE
 * @discussion Disable MOBIKE negotiation. Default is NO.
 */
@property BOOL disableMOBIKE NS_AVAILABLE(10_11, 9_0);

/*!
 * @property disableRedirect
 * @discussion Disable Server Redirect. Default is NO.
 */
@property BOOL disableRedirect NS_AVAILABLE(10_11, 9_0);

/*!
 * @property enablePFS
 * @discussion Enable Perfect Forward Secrecy. Default is NO.
 */
@property BOOL enablePFS NS_AVAILABLE(10_11, 9_0);

/*!
 * @property enableRevocationCheck
 * @discussion Enable certificate revocation check. Default is NO.
 */
@property BOOL enableRevocationCheck NS_AVAILABLE(10_11, 9_0);

/*!
 * @property strictRevocationCheck
 * @discussion Require positive certificate revocation check response for peer certificate validation to pass. Default is NO.
 */
@property BOOL strictRevocationCheck NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEOnDemandRule.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEOnDemandRule.h
 * @discussion This file declares the family of NEOnDemandRule classes. NEOnDemandRule objects are used to create VPN configurations that are started "On Demand", or automatically when certain conditions specified by the rules are satisfied.
 *
 * This API is part of NetworkExtension.framework.
 *
 * When the network state of the system changes, the active On Demand rules are evaluated. The matching rule's action is saved by the system as the "current" action. When applications running on the system open network connections, the current On Demand action is checked to determine if the network connection should cause the associated NetworkExtension session to be started (or stopped). If the On Demand action is "evaluate connection", then further evaluation of the network connection's properties is performed before making the decision about whether or not the NetworkExtension session should be started.
 */

@class NEEvaluateConnectionRule;

/*!
 * @typedef NEOnDemandRuleAction
 * @abstract On Demand rule actions
 */
typedef NS_ENUM(NSInteger, NEOnDemandRuleAction) {
	/*! @const NEOnDemandRuleActionConnect Start the VPN connection */
	NEOnDemandRuleActionConnect = 1,
	/*! @const NEOnDemandRuleActionDisconnect Do not start the VPN connection, and disconnect the VPN connection if it is not currently disconnected */
	NEOnDemandRuleActionDisconnect = 2,
	/*! @const NEOnDemandRuleActionEvaluateConnection Start the VPN after evaluating the destination host being accessed against the rule's connection rules */
	NEOnDemandRuleActionEvaluateConnection = 3,
	/*! @const NEOnDemandRuleActionIgnore Do not start the VPN connection, and leave the VPN connection in its current state */
	NEOnDemandRuleActionIgnore = 4,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEOnDemandRuleInterfaceType
 * @abstract On Demand rule network interface types
 */
typedef NS_ENUM(NSInteger, NEOnDemandRuleInterfaceType) {
	/*! @const NEOnDemandRuleInterfaceTypeAny */
	NEOnDemandRuleInterfaceTypeAny NS_ENUM_AVAILABLE(10_11, 9_0) = 0,
	/*! @const NEOnDemandRuleInterfaceTypeEthernet Wired Ethernet */
	NEOnDemandRuleInterfaceTypeEthernet NS_ENUM_AVAILABLE(10_10, NA) = 1,
	/*! @const NEOnDemandRuleInterfaceTypeWiFi WiFi */
	NEOnDemandRuleInterfaceTypeWiFi NS_ENUM_AVAILABLE(10_10, 8_0) = 2,
	/*! @const NEOnDemandRuleInterfaceTypeCellular Cellular */
	NEOnDemandRuleInterfaceTypeCellular NS_ENUM_AVAILABLE(NA, 8_0) = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEOnDemandRule
 * @discussion The NEOnDemandRule class declares the programmatic interface for an object that defines an On Demand rule. 
 *
 * NEOnDemandRule is an abstract base class from which other action-specific rule classes are derived.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEOnDemandRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property action
 * @discussion The rule's action
 */
@property (readonly) NEOnDemandRuleAction action NS_AVAILABLE(10_10, 8_0);

/*!
 * @property DNSSearchDomainMatch
 * @discussion An array of NSString objects. If the current default search domain is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current default search domain does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSSearchDomainMatch NS_AVAILABLE(10_10, 8_0);

/*!
 * @property DNSServerAddressMatch
 * @discussion An array of DNS server IP addresses represented as NSString objects. If each of the current default DNS servers is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the default DNS servers do not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSServerAddressMatch NS_AVAILABLE(10_10, 8_0);

/*!
 * @property interfaceTypeMatch
 * @discussion The type of interface that this rule matches. If the current primary network interface is of this type and all of the other conditions in the rule match, then the rule matches. If this property is 0 (the default), then the current primary interface type does not factor into the rule match.
 */
@property NEOnDemandRuleInterfaceType interfaceTypeMatch NS_AVAILABLE(10_10, 8_0);

/*!
 * @property SSIDMatch
 * @discussion An array of NSString objects. If the Service Set Identifier (SSID) of the current primary connected network matches one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current primary connected network SSID does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *SSIDMatch NS_AVAILABLE(10_10, 8_0);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If a request sent to this URL results in a HTTP 200 OK response and all of the other conditions in the rule match, then then rule matches. If this property is nil (the default), then an HTTP request does not factor into the rule match.
 */
@property (copy, nullable) NSURL *probeURL NS_AVAILABLE(10_10, 8_0);

@end

/*!
 * @interface NEOnDemandRuleConnect
 * @discussion The NEOnDemandRuleConnect class declares the programmatic interface for an object that defines an On Demand rule with the "Connect" action.
 *
 * When rules of this class match, the VPN connection is started whenever an application running on the system opens a network connection.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEOnDemandRuleConnect : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleDisconnect
 * @discussion The NEOnDemandRuleDisconnect class declares the programmatic interface for an object that defines an On Demand rule with the "Disconnect" action.
 *
 * When rules of this class match, the VPN connection is not started, and the VPN connection is disconnected if it is not currently disconnected.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEOnDemandRuleDisconnect : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleIgnore
 * @discussion The NEOnDemandRuleIgnore class declares the programmatic interface for an object that defines an On Demand rule with the "Ignore" action.
 *
 * When rules of this class match, the VPN connection is not started, and the current status of the VPN connection is left unchanged.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEOnDemandRuleIgnore : NEOnDemandRule
@end

/*!
 * @interface NEOnDemandRuleEvaluateConnection
 * @discussion The NEOnDemandRuleEvaluateConnection class declares the programmatic interface for an object that defines an On Demand rule with the "Evaluate Connection" action.
 *
 * When rules of this class match, the properties of the network connection being established are matched against a set of connection rules. The action of the matched rule (if any) is used to determine whether or not the VPN will be started.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEOnDemandRuleEvaluateConnection : NEOnDemandRule

/*!
 * @property connectionRules
 * @discussion An array of NEEvaluateConnectionRule objects. Each NEEvaluateConnectionRule object is evaluated in order against the properties of the network connection being established.
 */
@property (copy, nullable) NSArray<NEEvaluateConnectionRule *> *connectionRules NS_AVAILABLE(10_10, 8_0);

@end

/*!
 * @typedef NEEvaluateConnectionRuleAction
 * @abstract Evaluate Connection rule actions
 */
typedef NS_ENUM(NSInteger, NEEvaluateConnectionRuleAction) {
	/*! @const NEEvaluateConnectionRuleActionConnectIfNeeded Start the VPN connection if the destination host is not accessible directly */
	NEEvaluateConnectionRuleActionConnectIfNeeded = 1,
	/*! @const NEEvaluateConnectionRuleActionNeverConnect Do not start the VPN connection */
	NEEvaluateConnectionRuleActionNeverConnect = 2,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEEvaluateConnectionRule
 * @discussion The NEEvaluateConnectionRule class declares the programmatic interface for an object that associates properties of network connections with an action.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEEvaluateConnectionRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithMatchDomains:andAction
 * @discussion Initialize an NEEvaluateConnectionRule instance with a list of destination host domains and an action
 */
- (instancetype)initWithMatchDomains:(NSArray<NSString *> *)domains andAction:(NEEvaluateConnectionRuleAction)action NS_AVAILABLE(10_10, 8_0);

/*!
 * @property action
 * @discussion The action to take if the properties of the network connection being established match the rule.
 */
@property (readonly) NEEvaluateConnectionRuleAction action NS_AVAILABLE(10_10, 8_0);

/*!
 * @property matchDomains
 * @discussion An array of NSString objects. If the host name of the destination of the network connection being established shares a suffix with one of the strings in this array, then the rule matches.
 */
@property (readonly) NSArray<NSString *> *matchDomains NS_AVAILABLE(10_10, 8_0);

/*!
 * @property useDNSServers
 * @discussion An array of NSString objects. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded, the DNS servers specified in this array are used to resolve the host name of the destination while evaluating connectivity to the destination. If the resolution fails for any reason, the VPN is started.
 */
@property (copy, nullable) NSArray<NSString *> *useDNSServers NS_AVAILABLE(10_10, 8_0);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded and a request sent to this URL results in a response with an HTTP response code other than 200, then the VPN is started.
 */
@property (copy, nullable) NSURL *probeURL NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacketTunnelNetworkSettings.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

@class NEIPv4Settings;
@class NEIPv6Settings;

/*!
 * @file NEPacketTunnelNetworkSettings
 * @discussion This file declares the NEPacketTunnelNetworkSettings API. The NEPacketTunnelNetworkSettings API is used to specify IP network settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEPacketTunnelNetworkSettings
 * @discussion The NEPacketTunnelNetworkSettings class declares the programmatic interface for an object that contains IP network settings.
 *
 * NEPacketTunnelNetworkSettings is used by NEPacketTunnelProviders to communicate the desired IP network settings for the packet tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEPacketTunnelNetworkSettings : NETunnelNetworkSettings

/*!
 * @property IPv4Settings
 * @discussion An NEIPv4Settings object that contains the desired tunnel IPv4 settings.
 */
@property (copy, nullable) NEIPv4Settings *IPv4Settings NS_AVAILABLE(10_11, 9_0);

/*!
 * @property IPv6Settings
 * @discussion An NEIPv6Settings object that contains the desired tunnel IPv6 settings.
 */
@property (copy, nullable) NEIPv6Settings *IPv6Settings NS_AVAILABLE(10_11, 9_0);

/*!
 * @property tunnelOverheadBytes
 * @discussion An NSNumber object containing the number of bytes of overhead appended to each outbound packet through the tunnel. The MTU for the TUN interface is computed by subtracting this value from the MTU of the primary physical interface.
 */
@property (copy, nullable) NSNumber *tunnelOverheadBytes NS_AVAILABLE(10_11, 9_0);

/*!
 * @property MTU
 * @discussion An NSNumber object containing the Maximum Transmission Unit (MTU) size in bytes to assign to the TUN interface. If this property is set, the tunnelOverheadBytes property is ignored.
 */
@property (copy, nullable) NSNumber *MTU NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEHotspotHelper.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

/*!
 * @file NEHotspotHelper.h
 *
 * @discussion
 *   The NEHotspotHelper interface allows an application to
 *   participate in the process of joining Wi-Fi/hotspot networks. Such an
 *   application is referred to as a HotspotHelper. A HotspotHelper receives
 *   commands to be processed in the background that allow it to participate
 *   in the Hotspot Network state machine.
 *
 *   When a network is joined initially, the state machine enters
 *   the Evaluating state. In that state, each HotspotHelper receives a
 *   command of type Evaluate. If one or more helpers indicates that it
 *   is able to handle the network, the one with the highest confidence
 *   level is chosen before entering the Authenticating state. As an
 *   optimization, the first helper to assert a high confidence wins and
 *   the state machine ignores the other helpers.
 *
 *   If no helpers claim the network, the state machine enters the
 *   Authenticated state.
 *
 *   In the Authenticating state, the chosen helper is given a command of type
 *   Authenticate. The helper is expected to perform whatever network
 *   processing is required to make the network available for general
 *   network traffic. If the authentication is successful, the helper
 *   indicates that with a Success result. The state machine enters the
 *   Authenticated state.
 *
 *   On a network that has been authenticated by a helper, the state machine
 *   enters the Maintaining state when the network is joined again, and also
 *   periodically while the system remains associated with the network. In the
 *   Maintaining state, the helper is expected to perform whatever network
 *   operations are required to determine if the network is still able to
 *   carry general network traffic. If that is the case, the helper returns
 *   Success. If not, and authentication is again required, it returns
 *   AuthenticationRequired to cause the state machine to re-enter the
 *   Authenticating state.
 *
 *   In the Authenticating state, if the helper determines that it requires
 *   user interaction to proceed, the helper first arranges to alert
 *   the user via a UserLocalNotification, then returns a result of
 *   UIRequired. The state machine enters the PresentingUI state.
 *
 *   In the PresentingUI state, the helper is given a command of type
 *   PresentUI. The application is not kept running in the background
 *   in this state: PresentingUI relies on the user bringing the application
 *   to the foreground manually or via the UILocalNotification. Once the
 *   application has the required information, it returns Success to
 *   enter the Authenticated state.
 *
 *   The HotspotHelper may also receive a FilterScanList command at any time,
 *   in addition to a state machine command as described above. In its response,
 *   the helper indicates which of the networks in the scan list it can
 *   confidently handle.
 *
 * @ignorefuncmacro NS_OPTIONS
 * @ignorefuncmacro NS_ENUM
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEHS_EXPORT extern "C"
#else
#define NEHS_EXPORT extern
#endif

/*!
 * @typedef NEHotspotHelperCommandType
 * @abstract The type of the NEHotspotHelperCommand object.
 * @const kNEHotspotHelperCommandTypeNone Placeholder for the null command.
 * @const kNEHotspotHelperCommandTypeFilterScanList Filter the Wi-Fi scan list.
 * @const kNEHotspotHelperCommandTypeEvaluate Evaluate the network.
 * @const kNEHotspotHelperCommandTypeAuthenticate Authenticate to the network.
 * @const kNEHotspotHelperCommandTypePresentUI Present user interface.
 * @const kNEHotspotHelperCommandTypeMaintain Maintain the network.
 * @const kNEHotspotHelperCommandTypeLogoff Logoff the network.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperCommandType) {
	kNEHotspotHelperCommandTypeNone				= 0,
	kNEHotspotHelperCommandTypeFilterScanList	= 1,
	kNEHotspotHelperCommandTypeEvaluate			= 2,
	kNEHotspotHelperCommandTypeAuthenticate		= 3,
	kNEHotspotHelperCommandTypePresentUI		= 4,
	kNEHotspotHelperCommandTypeMaintain			= 5,
	kNEHotspotHelperCommandTypeLogoff			= 6,
} NS_AVAILABLE(NA, 9_0);

/*!
 * @typedef NEHotspotHelperResult
 * @abstract The result of processing the NEHotspotHelperCommand.
 * @discussion The HotspotHelper provides the result of
 *   processing the NEHotspotHelperCommand when it instantiates
 *   its NEHotspotHelperResponse.
 * @const kNEHotspotHelperResultSuccess The operation was successful.
 * @const kNEHotspotHelperResultFailure The operation failed.
 * @const kNEHotspotHelperResultUIRequired The operation requires user
 *   interaction. This result is only valid in response to a command with type
 *   kNEHotspotHelperCommandTypeAuthenticate.
 * @const kNEHotspotHelperResultCommandNotRecognized The helper did not
 *   recognize the command type.
 * @const kNEHotspotHelperResultAuthenticationRequired The network requires
 *   authentication again. This result is only valid in response to a
 *   command with type kNEHotspotHelperCommandTypeMaintain.
 * @const kNEHotspotHelperResultUnsupportedNetwork After attempting to
 *   authenticate, the helper determined that it can't perform the
 *   authentication. This result is only valid in response to commands of type
 *   kNEHotspotHelperCommandTypeAuthenticate and
 *   kNEHotspotHelperCommandTypePresentUI.
 * @const kNEHotspotHelperResultTemporaryFailure The helper determined that
 *   it is temporarily unable to perform the authentication.
 *   This result is only valid in response to commands of type
 *   kNEHotspotHelperCommandTypeAuthenticate and
 *   kNEHotspotHelperCommandTypePresentUI.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperResult) {
	kNEHotspotHelperResultSuccess				= 0,
	kNEHotspotHelperResultFailure				= 1,
	kNEHotspotHelperResultUIRequired			= 2,
	kNEHotspotHelperResultCommandNotRecognized	= 3,
	kNEHotspotHelperResultAuthenticationRequired= 4,
	kNEHotspotHelperResultUnsupportedNetwork	= 5,
	kNEHotspotHelperResultTemporaryFailure		= 6,
} NS_AVAILABLE(NA, 9_0);

/*!
 * @typedef NEHotspotHelperConfidence
 * @abstract
 *   The HotspotHelper's confidence in its ability to handle the network.
 * @discussion
 *   The HotspotHelper indicates its confidence in being able to handle the
 *   given hotspot network.
 * @const kNEHotspotHelperConfidenceNone The helper is unable to handle
 *   the network.
 * @const kNEHotspotHelperConfidenceLow The helper has some confidence
 *   in being able to handle the network.
 * @const kNEHotspotHelperConfidenceHigh The helper has high confidence
 *   in being able to handle the network.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperConfidence) {
	kNEHotspotHelperConfidenceNone		= 0,
	kNEHotspotHelperConfidenceLow		= 1,
	kNEHotspotHelperConfidenceHigh		= 2,
} NS_AVAILABLE(NA, 9_0);

/*!
 * @interface NEHotspotNetwork
 * @discussion
 *   The NEHotspotNetwork class conveys information about the
 *   network to the HotspotHelper. When the HotspotHelper is asked
 *   to evaluate the current network or filter the Wi-Fi scan list, it
 *   annotates the NEHotspotNetwork via the setConfidence method.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEHotspotNetwork : NSObject

/*!
 * @property SSID
 * @discussion The SSID for the Wi-Fi network.
 */
@property (readonly) NSString * SSID
NS_AVAILABLE(NA, 9_0);

/*!
 * @property BSSID
 * @discussion The BSSID for the Wi-Fi network.
 */
@property (readonly) NSString * BSSID
NS_AVAILABLE(NA, 9_0);

/*!
 * @property signalStrength
 * @discussion
 *   The signal strength for the Wi-Fi network. The value lies within
 *   the range 0.0 (weak/no signal) to 1.0 (strong signal).
 */
@property (readonly) double signalStrength
NS_AVAILABLE(NA, 9_0);

/*!
 * @property secure
 * @discussion Indicates whether the network is secure
 */
@property (readonly, getter=isSecure) BOOL secure
NS_AVAILABLE(NA, 9_0);

/*!
 * @property autoJoined
 * @discussion
 *   Indicates whether the network was joined automatically
 *   (YES) or joined by the user (NO).
 */
@property (readonly, getter=didAutoJoin) BOOL autoJoined
NS_AVAILABLE(NA, 9_0);

/*!
 * @property justJoined
 * @discussion
 *   Indicates whether the network was just joined. Useful in the
 *   Maintaining state to differentiate whether the Maintain command
 *   is for the initial join, or the subsequent periodic callback.
 */
@property (readonly, getter=didJustJoin) BOOL justJoined
NS_AVAILABLE(NA, 9_0);

/*!
 * @property chosenHelper
 * @discussion
 *   Indicates whether the HotspotHelper is the chosen helper for
 *   the network. The NEHotspotNetwork must have been instantiated via a
 *   call to the +[NEHotspotHelper supportedNetworkInterfaces] method. This
 *   is useful to restore state after the HotspotHelper application is quit
 *   and restarted.
 */
@property (readonly, getter=isChosenHelper) BOOL chosenHelper
NS_AVAILABLE(NA, 9_0);

/*!
 * @method setConfidence
 * @abstract
 *   Indicate the confidence in being able to handle the network.
 * @discussion
 *   Use this method to indicate the confidence in being able to
 *   successfully authenticate to the given network. Used in the response
 *   to the kNEHotspotHelperCommandTypeEvaluate and
 *   kNEHotspotHelperCommandTypeFilterScanList commands.
 */
- (void)setConfidence:(NEHotspotHelperConfidence)confidence
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method setPassword
 * @abstract
 *   Provide the password for a secure network
 * @discussion
 *   The HotspotHelper may set a password for a secure network. The format
 *   password string must adhere to IEEE 802.11 guidelines appropriate for
 *   the particular security scheme.
 *
 *   Used only in the response to the kNEHotspotHelperCommandTypeFilterScanList
 *   command.
 */
- (void)setPassword:(NSString *)password
	NS_AVAILABLE(NA, 9_0);

@end

@class NEHotspotHelperResponse;
@class NWTCPConnection;
@class NWUDPSession;
@class NWEndpoint;

/*!
 * @interface NEHotspotHelperCommand
 * @discussion
 *   An NEHotspotHelperCommand object is provided to the helper's
 *   command handler block. The HotspotHelper processes the command
 *   instantiates an NEHotspotHelperResponse object, sets the annotated
 *   network or networkList (Evaluate/FilterScanList only),
 *   then delivers it.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEHotspotHelperCommand : NSObject

/*!
 * @property commandType
 * @discussion
 *   The type of the command.
 */
@property (readonly) NEHotspotHelperCommandType commandType
NS_AVAILABLE(NA, 9_0);

/*!
 * @property network
 * @discussion
 *   The network associated with the command. May be nil.
 */
@property (readonly, nullable) NEHotspotNetwork * network
NS_AVAILABLE(NA, 9_0);

/*!
 * @property networkList
 * @discussion
 *   The list of networks associated with a command. Will be nil unless
 *   the command type is kNEHotspotHelperCommandTypeFilterScanList.
 *   This property returns an NSArray of NEHotspotNetwork.
 */
@property (readonly, nullable) NSArray<NEHotspotNetwork *> * networkList
NS_AVAILABLE(NA, 9_0);

/*!
 * @method createResponse:
 * @abstract
 *   Create a response to the command.
 * @discussion
 *   Instantiate an NEHotspotHelperResponse for the command.
 * @return
 *   NEHotspotHelperResponse with the specified result.
 */
- (NEHotspotHelperResponse *)createResponse:(NEHotspotHelperResult)result
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method createTCPConnection
 * @abstract
 *   Create a new TCP connection over the interface associated with the command.
 * @discussion
 *   Instantiate an NWTCPConnection to the specified endpoint
 *   bound to the network interface associated with the command.
 * @return
 *   non-nil NWTCPConnection object if successful, nil otherwise
 */
- (NWTCPConnection *)createTCPConnection:(NWEndpoint *)endpoint
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method createUDPSession
 * @abstract
 *   Create a new UDP session over the interface associated with the command.
 * @discussion
 *   Instantiate an NWUDPSession to the specified endpoint
 *   bound to the network interface associated with the command.
 * @return
 *   non-nil NWUDPSession object if successful, nil otherwise
 */
- (NWUDPSession *)createUDPSession:(NWEndpoint *)endpoint
	NS_AVAILABLE(NA, 9_0);

@end

/*!
 * @interface NEHotspotHelperResponse
 * @discussion
 *   The HotspotHelper creates an NEHotspotHelperResponse object to provide
 *   the results of running the corresponding NEHotspotHelperCommand.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEHotspotHelperResponse : NSObject

/*!
 * @method setNetwork
 * @abstract
 *   Set the network that conveys the confidence level.
 * @discussion
 *   Provide the annotated NEHotspotNetwork object in the response to the
 *   kNEHotspotHelperCommandTypeEvaluate command. The helper sets the
 *   confidence in the network object to indicate its ability to handle
 *   the current network.
 */
- (void)setNetwork:(NEHotspotNetwork *)network
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method setNetworkList
 * @abstract
 *   Set the list of handled networks.
 * @discussion
 *   Provide an NSArray of annotated NEHotspotNetwork objects in response
 *   to the kNEHotspotHelperCommandTypeFilterScanList command.
 *   The helper provides the list of network objects that it is capable of
 *   handling with at least low confidence. Networks that it has no
 *   confidence in handling should not be specified.
 */
- (void)setNetworkList:(NSArray<NEHotspotNetwork *> *)networkList
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method deliver
 * @abstract
 *   Delivers the response to the command.
 * @discussion
 *   Deliver the NEHotspotHelperResponse to the HotspotHelper infrastructure.
 */
- (void)deliver
	NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @typedef NEHotspotHelperHandler
 * @abstract
 *   The type definition for the HotspotHelper's command handler block.
 * @discussion
 *   The application provides a block of this type when it
 *   invokes the +[NEHotspotHelper registerWithOptions:queue:handler] method.
 *   The block is invoked every time there is a command to be processed.
 */
typedef void (^NEHotspotHelperHandler)(NEHotspotHelperCommand * cmd)
NS_AVAILABLE(NA, 9_0);

NEHS_EXPORT
/*!
 * @const kNEHotspotHelperOptionDisplayName
 * @abstract
 *   The string displayed in Wi-Fi Settings for a network handled by
 *   the application.
 * @discussion
 *   This key specifies the display name for the application, if an alternate
 *   name is desired.  If this property is not specified, the application's
 *   name is used.
 *
 *   This name appears in Settings -> Wi-Fi underneath the Wi-Fi network
 *   name if the helper indicated that it was able to handle the network.
 */
const NSString * kNEHotspotHelperOptionDisplayName
NS_AVAILABLE(NA, 9_0);

/*!
 * @interface NEHotspotHelper
 * @discussion
 *   The NEHotspotHelper class allows an application to register itself as a
 *   HotspotHelper.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEHotspotHelper : NSObject

/*!
 * @method registerWithOptions:queue:handler
 * @abstract
 *   Register the application as a HotspotHelper.
 * @discussion
 *   Once this API is invoked successfully, the application becomes
 *   eligible to be launched in the background and participate in
 *   various hotspot related functions.
 *
 *   This function should be called once when the application starts up.
 *   Invoking it again will have no effect and result in FALSE being returned.
 *
 *   The 'options' dictionary may be nil, or contain the single property
 *   kNEHotspotHelperOptionDisplayName.
 *
 * @param options If not nil, 'options' is an NSDictionary containing
 *   kNEHotspotHelperOption* keys (currently just
 *   kNEHotspotHelperOptionDisplayName).
 * @param queue The dispatch_queue_t to invoke the handle block on.
 * @param handler The NEHotspotHelperHandler block to execute to process
 *   helper commands.
 * @return
 *   YES if the registration was successful, NO otherwise.
 * @note Notes
 * @note 1
 *   The application's Info.plist MUST include a UIBackgroundModes array
 *   containing 'network-authentication'.
 * @note 2
 *   The application MUST set 'com.apple.developer.networking.HotspotHelper'
 *   as one of its entitlements. The value of the entitlement is a boolean
 *   value true.
 */
+ (BOOL)registerWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options
					  queue:(dispatch_queue_t)queue
					handler:(NEHotspotHelperHandler)handler
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method logoff:
 * @abstract
 *   Terminate the authentication session.
 * @discussion
 *   The application invokes this method when it wants to logoff from the
 *   current network. Invoking this method causes an NEHotspotHelperCommand
 *   of type kNEHotspotHelperCommandTypeLogoff to be issued to the application's
 *   'handler' block (see +[NEHotspotHelper registerWithOptions:queue:handler]).
 *
 *   'network' must correspond to the currently associated Wi-Fi network
 *   i.e. it must have come from the NEHotspotHelperCommand's 'network' property
 *   or from the +[NEHotspotHelper supportedInterfaces] method.
 * @return
 *   YES if the logoff command was successfully queued, NO otherwise.
 * @note Notes
 * @note 1
 *   The application MUST NOT actually logoff from the network until it
 *   receives the command to logoff.
 * @note 2
 *   After the application invokes -[NEHotspotHelperResponse deliver] indicating
 *   kNEHotspotHelperResultSuccess, the Wi-Fi network is disassociated.
 */
+ (BOOL)logoff:(NEHotspotNetwork *)network
	NS_AVAILABLE(NA, 9_0);

/*!
 * @method supportedNetworkInterfaces
 * @abstract
 *   Return the list of network interfaces managed by the
 *   HotspotHelper infrastructure.
 * @discussion
 *   Each network interface is represented by an NEHotspotNetwork object.
 *   Currently, the returned array contains exactly one NEHotspotNetwork
 *   object representing the Wi-Fi interface.
 *
 *   The main purpose of this method is to allow a HotspotHelper to provide
 *   accurate status in its UI at times when it has not been given a command
 *   to process. This method coupled with -[NEHotspotNetwork isChosenHelper]
 *   allows the application to know whether it is the one that is handling
 *   the current network.
 * @return
 *   nil if no network interfaces are being managed,
 *   non-nil NSArray of NEHotspotNetwork objects otherwise.
 */
+ (NSArray *)supportedNetworkInterfaces /* of NEHotspotNetwork */
	NS_AVAILABLE(NA, 9_0);

@end

/*!
 * @category NSMutableURLRequest(NEHotspotHelper)
 * @discussion
 *   Extend NSMutableURLRequest to include a method to bind the
 *   request to the network interface associated with the specified
 *   NEHotspotHelperCommand object.
 */
@interface NSMutableURLRequest (NEHotspotHelper)
/*!
 * @method bindToHotspotHelperCommand:
 * @discussion
 *   Binds the NSMutableURLRequest to the network interface associated with
 *   the NEHotspotHelperCommand object.
 */
- (void)bindToHotspotHelperCommand:(NEHotspotHelperCommand *)command
	NS_AVAILABLE(NA, 9_0);
@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NETunnelProviderProtocol.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETunnelProviderProtocol.h
 * @discussion This file declares the NETunnelProviderProtocol API. The NETunnelProviderProtocol API is used to specify configuration settings that are specific to Network Extensions provided by NETunnelProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelProviderProtocol
 * @discussion The NETunnelProviderProtocol class declares the programmatic interface for an object that contains NETunnelProvider-specific configuration settings.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NETunnelProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NETunnelProvider vendor-specific configuration parameters. This dictionary is passed as-is to NETunnelProviders when a tunnel is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NETunnelProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacketTunnelProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEPacketFlow;
@class NEPacketTunnelNetworkSettings;
@class NEPacketTunnelFlow;
@class NWTCPConnection;
@class NWTLSParameters;
@class NWUDPSession;
@class NWEndpoint;
@class NWHostEndpoint;

/*!
 * @file NEPacketTunnelProvider.h
 * @discussion This file declares the NEPacketTunnelProvider API. The NEPacketTunnelProvider API is used to implement custom IP packet tunneling solutions.
 */

/*!
 * @interface NEPacketTunnelProvider
 * @discussion The NEPacketTunnelProvider class declares the programmatic interface of an object that implements the client side of a custom IP packet tunneling protocol.
 *
 * NEPacketTunnelProvider is part of NetworkExtension.framework.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEPacketTunnelProvider : NETunnelProvider

/*!
 * @method startTunnelWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new tunnel is being created. Subclasses must override this method to perform whatever steps are necessary to establish the tunnel.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the tunnel then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of startingt the tunnel is complete. If the tunnel cannot be established then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the tunnel was successfully established.
 */
- (void)startTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method stopTunnelWithReason:completionHandler:
 * @discussion This function is called by the framework when the tunnel is being destroyed. Subclasses must override this method to perform whatever steps are necessary to tear down the tunnel.
 * @param reason An NEProviderStopReason indicating why the tunnel is being stopped.
 * @param completionHandler A block that must be called when the tunnel is completely torn down.
 */
- (void)stopTunnelWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method cancelTunnelWithError:
 * @discussion This function is called by tunnel provider implementations to initiate tunnel destruction when a network error is encountered that renders the tunnel no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the tunnel provider implementation encountered.
 */
- (void)cancelTunnelWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @property packetFlow
 * @discussion An NEPacketFlow object that the tunnel provider implementation should use to receive packets from the network stack and inject packets into the network stack. Every time the tunnel is started the packet flow object is in an initialized state and must be explicitly opened before any packets can be received or injected.
 */
@property (readonly) NEPacketTunnelFlow *packetFlow NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createTCPConnectionThroughTunnelToEndpoint:enableTLS:TLSParameters:delegate:
 * @discussion This function can be called by subclass implementations to create a TCP connection to a given network endpoint, through the tunnel established by the provider. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote network endpoint to connect to.
 * @param routeThroughTunnel A flag indicating if the connection should be established through the tunnel provided by this NETunnelProvider.
 * @param enableTLS A flag indicating if a TLS session should be negotiated on the connection.
 * @param TLSParameters A set of optional TLS parameters. Only valid if enableTLS is YES. If TLSParameters is nil, the default system parameters will be used for TLS negotiation.
 * @param delegate An object to use as the connection delegate. This object should conform to the NWTCPConnectionAuthenticationDelegate protocol.
 * @return An NWTCPConnection object.
 */
- (NWTCPConnection *)createTCPConnectionThroughTunnelToEndpoint:(NWEndpoint *)remoteEndpoint enableTLS:(BOOL)enableTLS TLSParameters:(nullable NWTLSParameters *)TLSParameters delegate:(nullable id)delegate NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createUDPSessionThroughTunnelToEndpoint:fromEndpoint:
 * @discussion This function can be called by subclass implementations to create a UDP session between a local network endpoint and a remote network endpoint, through the tunnel established by the provider. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote endpoint to which UDP datagrams will be sent by the UDP session.
 * @param localEndpoint An NWHostEndpoint object that specifies the local IP address endpoint to use as the source endpoint of the UDP session.
 * @return An NWUDPSession object.
 */
- (NWUDPSession *)createUDPSessionThroughTunnelToEndpoint:(NWEndpoint *)remoteEndpoint fromEndpoint:(nullable NWHostEndpoint *)localEndpoint NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NetworkExtension.h
/*
 * Copyright (c) 2014, 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#define __NE_INDIRECT__
#endif

#import <Foundation/Foundation.h>

#import <NetworkExtension/NEAppProxyFlow.h>
#import <NetworkExtension/NEAppProxyProvider.h>
#import <NetworkExtension/NEAppProxyProviderManager.h>
#import <NetworkExtension/NEAppProxyTCPFlow.h>
#import <NetworkExtension/NEAppProxyUDPFlow.h>
#import <NetworkExtension/NEAppRule.h>
#import <NetworkExtension/NEDNSSettings.h>
#import <NetworkExtension/NEFilterControlProvider.h>
#import <NetworkExtension/NEFilterDataProvider.h>
#import <NetworkExtension/NEFilterFlow.h>
#import <NetworkExtension/NEFilterManager.h>
#import <NetworkExtension/NEFilterProvider.h>
#import <NetworkExtension/NEFilterProviderConfiguration.h>
#if TARGET_OS_IPHONE
#import <NetworkExtension/NEHotspotHelper.h>
#endif
#import <NetworkExtension/NEIPv4Settings.h>
#import <NetworkExtension/NEIPv6Settings.h>
#import <NetworkExtension/NEOnDemandRule.h>
#import <NetworkExtension/NEPacketTunnelFlow.h>
#import <NetworkExtension/NEPacketTunnelNetworkSettings.h>
#import <NetworkExtension/NEPacketTunnelProvider.h>
#import <NetworkExtension/NEProvider.h>
#import <NetworkExtension/NEProxySettings.h>
#import <NetworkExtension/NETunnelProvider.h>
#import <NetworkExtension/NETunnelProviderManager.h>
#import <NetworkExtension/NETunnelProviderSession.h>
#import <NetworkExtension/NETunnelProviderProtocol.h>
#import <NetworkExtension/NEVPNConnection.h>
#import <NetworkExtension/NEVPNManager.h>
#import <NetworkExtension/NEVPNProtocol.h>
#import <NetworkExtension/NEVPNProtocolIKEv2.h>
#import <NetworkExtension/NEVPNProtocolIPSec.h>

#import <NetworkExtension/NWEndpoint.h>
#import <NetworkExtension/NWHostEndpoint.h>
#import <NetworkExtension/NWBonjourServiceEndpoint.h>
#import <NetworkExtension/NWPath.h>
#import <NetworkExtension/NWTCPConnection.h>
#import <NetworkExtension/NWUDPSession.h>
#import <NetworkExtension/NWTLSParameters.h>

#undef __NE_INDIRECT__
// ==========  NetworkExtension.framework/Headers/NEAppProxyProviderManager.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyProviderManager
 * @discussion This file declares the NEAppProxyProviderManager API. The NEAppProxyProviderManager API is used to configure and control network tunnels provided by NEAppProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEAppProxyProviderManager
 * @discussion The NEAppProxyProviderManager class declares the programmatic interface for an object that is used to configure and control network tunnels provided by NEAppProxyProviders.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyProviderManager : NETunnelProviderManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NEAppProxy configurations associated with the calling app that have previously been saved to disk and returns them as NEAppProxyProviderManager objects.
 * @param completionHandler A block that takes an array NEAppProxyProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NEAppProxyProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEVPNProtocol.h
/*
 * NEVPNProtocol.h
 *
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProxySettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEVPNProtocol
 * @discussion The NEVPNProtocol class declares the programmatic interface of an object that manages the protocol-specific portion of a VPN configuration.
 *
 * NEVPNProtocol is an abstract base class from which other protocol-specific classes are derived.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNProtocol : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property serverAddress
 * @discussion The VPN server. Depending on the protocol, may be an IP address, host name, or URL.
 */
@property (copy, nullable) NSString *serverAddress NS_AVAILABLE(10_10, 8_0);

/*!
 * @property username
 * @discussion The username component of the VPN authentication credential.
 */
@property (copy, nullable) NSString *username NS_AVAILABLE(10_10, 8_0);

/*!
 * @property passwordReference
 * @discussion The password component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassGenericPassword class.
 */
@property (copy, nullable) NSData *passwordReference NS_AVAILABLE(10_10, 8_0);

/*!
 * @property identityReference
 * @discussion The certificate and private key component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassIdentity class.
 */
@property (copy, nullable) NSData *identityReference NS_AVAILABLE(10_10, 9_0);

/*!
 * @property identityData
 * @discussion The PKCS12 data for the VPN authentication identity. The value is a NSData in PKCS12 format.
 */
@property (copy, nullable) NSData *identityData NS_AVAILABLE(10_11, 8_0);

/*!
 * @property identityDataPassword 
 * @discussion The password to be used to decrypt the PKCS12 identity data.
 */
@property (copy, nullable) NSString *identityDataPassword NS_AVAILABLE(10_11, 8_0);

/*!
 * @property disconnectOnSleep
 * @discussion If YES, the VPN connection will be disconnected when the device goes to sleep. The default is NO.
 */
@property BOOL disconnectOnSleep NS_AVAILABLE(10_10, 8_0);

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object containing the proxy settings to use for connections routed through the tunnel.
 */
@property (copy, nullable) NEProxySettings *proxySettings NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyTCPFlow.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEAppProxyFlow.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyTCPFlow
 * @discussion This file declares the NEAppProxyTCPFlow API. The NEAppProxyTCPFlow API is used by NEAppProxyProvider implementations to proxy the payload of TCP connections.
 */

@class NWEndpoint;

/*!
 * @interface NEAppProxyTCPFlow
 * @discussion The NEAppProxyTCPFlow class declares the programmatic interface of an object that is used by NEAppProxyProvider implementations to proxy the payload of TCP connections.
 *
 * NEAppProxyTCPFlow is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyTCPFlow : NEAppProxyFlow

/*!
 * @method readDataWithCompletionHandler:
 * @discussion Read data from the flow.
 * @param completionHandler A block that will be executed when some data is read from the flow. The block is passed either the data that was read or a non-nil error if an error occurred. If data has a length of 0 then no data can be subsequently read from the flow. The completion handler is only called for the single read operation that was initiated by calling this method. If the caller wants to read more data then it should call this method again to schedule another read operation and another execution of the completion handler block.
 */
- (void)readDataWithCompletionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeData:completionHandler
 * @discussion Write data to the flow.
 * @param data The data to write.
 * @param completionHandler A block that will be executed when the data is written into the associated socket's receive buffer. The caller should use this callback as an indication that it is possible to write more data to the flow without using up excessive buffer memory. If an error occurs while writing the data then a non-nil NSError object is passed to the block.
 */
- (void)writeData:(NSData *)data withCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @property remoteEndpoint
 * @discussion An NWEndpoint object containing information about the intended remote endpoint of the flow.
 */
@property (readonly) NWEndpoint *remoteEndpoint NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEProxySettings.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEProxySettings.h
 * @discussion This file declares the NEProxySettings API. The NEProxySettings API is used to specify proxy settings to be used when a Network Extension is active.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEProxyServer
 * @discussion The NEProxyServer class declares the programmatic interface for an object that contains settings for a proxy server.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProxyServer : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddress:port:
 * @discussion This function initializes a newly-allocated NEProxyServer object
 * @param address The string representation of the proxy server IP address.
 * @param port The TCP port of the proxy server.
 */
- (instancetype)initWithAddress:(NSString *)address port:(NSInteger)port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property address
 * @discussion The string representation of the proxy server IP address.
 */
@property (readonly) NSString *address NS_AVAILABLE(10_11, 9_0);

/*!
 * @property port
 * @discussion The TCP port of the proxy server.
 */
@property (readonly) NSInteger port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property authenticationRequired
 * @discussion A flag indicating if the server requires authentication credentials.
 */
@property BOOL authenticationRequired NS_AVAILABLE(10_11, 9_0);

/*!
 * @property username
 * @discussion The username portion of the authentication credential to use when communicating with the proxy server.
 */
@property (copy, nullable) NSString *username NS_AVAILABLE(10_11, 9_0);

/*!
 * @property password
 * @discussion The password portion of the authentication credential to use when communicating with the proxy server. This property is only saved persistently if the username property is non-nil and non-empty and if the authenticationRequired flag is set.
 */
@property (copy, nullable) NSString *password NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEProxySettings
 * @discussion The NEProxySettings class declares the programmatic interface for an object that contains proxy settings.
 *
 * NEProxySettings is used in the context of a Network Extension configuration to specify the proxy that should be used for network traffic when the Network Extension is active.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProxySettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property autoProxyConfigurationEnabled
 * @discussion A boolean indicating if proxy auto-configuration is enabled.
 */
@property BOOL autoProxyConfigurationEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property proxyAutoConfigurationURL
 * @discussion A URL specifying where the PAC script is located.
 */
@property (copy, nullable) NSURL *proxyAutoConfigurationURL NS_AVAILABLE(10_11, 9_0);

/*!
 * @property proxyAutoConfigurationJavaScript
 * @discussion A string containing the PAC JavaScript source code.
 */
@property (copy, nullable) NSString *proxyAutoConfigurationJavaScript NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPEnabled
 * @discussion A boolean indicating if the static HTTP proxy is enabled.
 */
@property BOOL HTTPEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPServer
 * @discussion A NEProxyServer object containing the HTTP proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPServer NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPSEnabled
 * @discussion A boolean indicating if the static HTTPS proxy is enabled.
 */
@property BOOL HTTPSEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPSServer
 * @discussion A NEProxyServer object containing the HTTPS proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPSServer NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludeSimpleHostnames
 * @discussion A flag indicating if the proxy settings should not be used for network destinations specified using single-label host names.
 */
@property BOOL excludeSimpleHostnames NS_AVAILABLE(10_11, 9_0);

/*!
 * @property exceptionList
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will not be used for the connection.
 */
@property (copy, nullable) NSArray<NSString *> *exceptionList NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomains
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will be used for the connection. Otherwise the proxy settings will not be used. If this property is nil then all connections to which the Network Extension applies will use the proxy settings.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyFlow.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyFlow.h
 * @discussion This file declares the NEAppProxyFlow API. The NEAppProxyFlow API is used to interact with various streams of network data in the context of NEProvider implementations.
 */

@class NWHostEndpoint;
@class NEFlowMetaData;

#if defined(__cplusplus)
#define NEAPPPROXYFLOW_EXPORT extern "C"
#else
#define NEAPPPROXYFLOW_EXPORT extern
#endif

/*!
 * @typedef NEAppProxyFlowError
 * @abstract Flow error codes
 */
typedef NS_ENUM(NSInteger, NEAppProxyFlowError) {
	/*! @const NEAppProxyFlowErrorNotOpen The flow is not fully open. */
	NEAppProxyFlowErrorNotConnected = 1,
	/*! @const NEAppProxyFlowErrorPeerReset The remote peer reset the flow. */
	NEAppProxyFlowErrorPeerReset = 2,
	/*! @const NEAppProxyFlowErrorHostUnreachable The remote peer is unreachable. */
	NEAppProxyFlowErrorHostUnreachable = 3,
	/*! @const NEAppProxyFlowErrorInvalidArgument An invalid argument was passed to one of the NEAppProxyFlow methods. */
	NEAppProxyFlowErrorInvalidArgument = 4,
	/*! @const NEAppProxyFlowErrorAborted The flow was aborted. */
	NEAppProxyFlowErrorAborted = 5,
	/*! @const NEAppProxyFlowErrorRefused The flow was disallowed. */
	NEAppProxyFlowErrorRefused = 6,
	/*! @const NEAppProxyFlowErrorTimedOut The flow timed out. */
	NEAppProxyFlowErrorTimedOut = 7,
	/*! @const NEAppProxyFlowErrorInternal An internal error occurred. */
	NEAppProxyFlowErrorInternal = 8,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*! @const NEAppProxyErrorDomain The NEAppProxyFlow error domain */
NEAPPPROXYFLOW_EXPORT NSString * const NEAppProxyErrorDomain NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NEAppProxyFlow
 * @discussion The NEAppProxyFlow class is an abstract base class that declares the programmatic interface for a flow of network data.
 *
 * NEAppProxyFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyFlow : NSObject

/*!
 * @method openWithLocalAddress:completionHandler:
 * @discussion This function is used by an NEProvider implementation to indicate that it is ready to handle flow data.
 * @param localEndpoint The address and port that should be used as the local endpoint of the socket associated with this flow. If the source application already specifed a local endpoint by binding the socket then this parameter is ignored.
 * @param completionHandler A block that is called when the process of opening flow is complete. A nil value passed to this block indicates that the flow was opened successfully. A non-nil NSError value indicates that the flow failed to open successfully.
 */
- (void)openWithLocalEndpoint:(nullable NWHostEndpoint *)localEndpoint completionHandler:(void (^)(NSError *__nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method closeReadWithError:
 * @discussion This function is used by an NEProvider implementation to indicate that it does not want to receive any more data from the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeReadWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method closeWriteWithError:
 * @discussion This functions is used by an NEProvider implementation to indicate that it does not have any more data to write to the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeWriteWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @property metaData
 * @discussion An NEFlowMetaData object containing meta data for the flow.
 */
@property (readonly) NEFlowMetaData *metaData NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEFlowMetaData
 * @discussion The NEFlowMetaData class declares the programmatic interface for an object that contains extra information about a flow.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEFlowMetaData : NSObject

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A blob of bytes that uniquely identifies the source app binary of the flow. This value is unique across multiple versions of the same app.
 */
@property (readonly) NSData *sourceAppUniqueIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
 * @property sourceAppSigningIdentifier
 * @discussion A string containing the signing identifier (almost always equivalent to the bundle identifier) of the source app of the flow.
 */
@property (readonly) NSString *sourceAppSigningIdentifier NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyUDPFlow.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEAppProxyFlow.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyUDPFlow.h
 * @discussion This file declares the NEAppProxyUDPFlow API. The NEAppProxyUDPFlow API is used by NEAppProxyProvider implementations to proxy the payload of UDP datagrams.
 */

@class NWEndpoint;

/*!
 * @interface NEAppProxyUDPFlow
 * @discussion The NEAppProxyUDPFlow class declares the programmatic interface of an object that is used by NEAppProxyProvider implementations to proxy the payload of UDP datagrams.
 *
 * NEAppProxyUDPFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyUDPFlow : NEAppProxyFlow

/*!
 * @method readDatagramWithCompletionHandler:
 * @discussion Read a datagram from the flow.
 * @param completionHandler A block that will be executed when datagrams have been read from the flow. The block takes the datagrams that were read, the destination endpoints of the datagrams, and an NSError. If an error occurred while reading then the error parameter will be non-nil. If the datagrams and remoteEndpoints arrays are non-nill but 
 */
- (void)readDatagramsWithCompletionHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSArray<NWEndpoint *> * __nullable remoteEndpoints,  NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeDatagram:sentByEndpoint:completionHandler:
 * @discussion Write a datagram to the flow.
 * @param datagrams An array of NSData objects containing the data to be written.
 * @param remoteEndpoints The source endpoints of the datagrams.
 * @param completionHandler A block that will be executed when the datagrams have been written to the corresponding socket's receive buffer.
 */
- (void)writeDatagrams:(NSArray<NSData *> *)datagrams sentByEndpoints:(NSArray<NWEndpoint *> *)remoteEndpoints completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @property localEndpoint
 * @discussion An NWEndpoint object containing the local endpoint of the flow's corresponding socket.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NETunnelNetworkSettings.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

NS_ASSUME_NONNULL_BEGIN

@class NEDNSSettings;
@class NEProxySettings;

/*!
 * @file NETunnelNetworkSettings
 * @discussion This file declares the NETunnelNetworkSettings API. The NETunnelNetworkSettings API is used to specify network settings for tunnel provider by NetworkExtension providers.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelNetworkSettings
 * @discussion The NETunnelNetworkSettings class declares the programmatic interface for an object that contains network settings.
 *
 * NETunnelNetworkSettings is used by NETunnelProviders to communicate the desired network settings for tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NETunnelNetworkSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithTunnelRemoteAddress:
 * @discussion This function initializes a newly-allocated NETunnelNetworkSettings object with a given tunnel remote address.
 * @param address The address of the remote endpoint that is providing the tunnel service.
 */
- (instancetype)initWithTunnelRemoteAddress:(NSString *)address NS_AVAILABLE(10_11, 9_0);

/*!
 * @property tunnelRemoteAddress
 * @discussion A string containing the IP address of the remote endpoint that is providing the tunnel service.
 */
@property (readonly) NSString *tunnelRemoteAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property DNSSettings
 * @discussion An NEDNSSettings object that contains the desired tunnel DNS settings.
 */
@property (copy, nullable) NEDNSSettings *DNSSettings NS_AVAILABLE(10_11, 9_0);

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object that contains the desired tunnel proxy settings.
 */
@property (copy, nullable) NEProxySettings *proxySettings NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppProxyFlow;

/*!
 * @file NEAppProxyProvider
 * @discussion This file declares the NEAppProxyProvider API. The NEAppProxyProvider is used to implement custom network proxy solutions.
 */

/*!
 * @interface NEAppProxyProvider
 * @discussion The NEAppProxyProvider class declares the programmatic interface for an object that implements the client side of a custom network proxy solution.
 *
 * NEAppProxyProvider is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyProvider : NETunnelProvider

/*!
 * @method startProxyWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new proxy instance is being created. Subclasses must override this method to perform whatever steps are necessary to ready the proxy for handling flows of network data.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the proxy then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of starting the proxy complete. If the proxy cannot be started then the subclass' implementation of this method must pass a non-nill NSError object to this block. A value of nil passed to the completion handler indicates that the proxy was successfully started.
 */
- (void)startProxyWithOptions:(nullable NSDictionary<NSString *,id> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method stopProxyWithReason:completionHandler:
 * @discussion This function is called by the framework when the proxy is being stopped. Subclasses must override this method to perform whatever steps are necessary to stop the proxy.
 * @param reason An NEProviderStopReason indicating why the proxy is being stopped.
 * @param completionHandler A block that must be called when the proxy is completely stopped.
 */
- (void)stopProxyWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method cancelProxyWithError:
 * @discussion This function is called by proxy provider implementations to stop the proxy when a network error is encountered that renders the proxy no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the prxoy provider implementation encountered.
 */
- (void)cancelProxyWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework to deliver a new network data flow to the proxy provider implementation. Subclasses must override this method to perform whatever steps are necessary to ready the proxy to receive data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEFlow openWithCompletionHandler:] on the flow. If the proxy implementation decides to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES. In this case the proxy implementation is responsible for retaining the NEFlow object.
 * @param flow The new flow
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewFlow:(NEAppProxyFlow *)flow NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEFilterProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

@class NEFilterProviderConfiguration;

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEFILTER_EXPORT extern "C"
#else
#define NEFILTER_EXPORT extern
#endif

/*!
 *	Key to specify in the NSDictionary which is returned as a value in remediationMap.
 *	This key is used to indicate the Remediation URL. The URL should follow the scheme
 *	http or https to be used by the content filter.
 */
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationURLs NS_AVAILABLE(NA, 9_0);			// Key for RemediationURL
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationButtonTexts NS_AVAILABLE(NA, 9_0);	// Key for Remediation button text

/*!
 *	Strings which can be appended or inserted into the remediation URL
 */
#define	NEFilterProviderRemediationURLFlowURLHostname			@"NE_FLOW_HOSTNAME"	// Browser flow URL Hostname
#define NEFilterProviderRemediationURLFlowURL					@"NE_FLOW_URL"		// Browser flow URL
#define NEFilterProviderRemediationURLOrganization				@"NE_ORGANIZATION"	// Organization in filter provider configuration
#define NEFilterProviderRemediationURLUsername					@"NE_USERNAME"		// Username in the filter provider configuration

/*!
 * @file NEFilterProvider.h
 * @discussion This file declares the NEFilterProvider API. The NEFilterProvider API is used to implement custom content filtering solutions.
 */

/*!
 * @interface NEFilterProvider
 * @discussion The NEFilterProvider class is an abstract base class that declares the programmatic interface of an object that implements a socket filter.
 *
 * NEFilterProvider is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterProvider : NEProvider

/*!
 * @method startFilterWithCompletionHandler:
 * @discussion This function is called by the framework when the content filter is being started. Subclasses must override this method and perform whatever steps are necessary to start the filter.
 * @param completionHandler A block that must be called when the process of starting the filter is complete. If the filter was started successfully, subclass implementations must pass the nil value to this block. If an error occurred while starting the filter, sublcass implementations must pass a non-nil NSError containing more details about the error.
 */
- (void)startFilterWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(NA, 9_0);

/*!
 * @method stopFilterWithReason:completionHandler:
 * @discussion This function is called by the framework when the content filter is being stopped. Subclasses must override this method and perform whatever steps are necessary to stop the filter.
 * @param reason An NEProviderStopReason indicating why the filter is being stopped.
 * @param completionHandler A block that must be called when the process of stopping the filter is complete.
 */
- (void)stopFilterWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler NS_AVAILABLE(NA, 9_0);

/*!
 * @property filterConfiguration
 * @discussion An NEContentFilterConfiguration object containing the current filter configuration. The value of this property can change during the lifetime of a filter. Filter implementations can use KVO to be notified when the configuration changes.
 */
@property (readonly) NEFilterProviderConfiguration *filterConfiguration NS_AVAILABLE(NA, 9_0);

@end

/*!
 * @interface NEFilterVerdict
 * @discussion The NEFilterVerdict class declares the programmatic interface for an object that is the verdict for a flow of network data.
 *
 * NEFilterVerdict is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterVerdict : NSObject <NSSecureCoding,NSCopying>
@end

/*!
 * @interface NEFilterNewFlowVerdict
 * @discussion The NEFilterNewFlowVerdict declares the programmatic interface of an object that is the verdict for a new flow of network data before any of the flow's data has been seen by the filter.
 *
 * NEFilterNewFlowVerdict is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterNewFlowVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the new flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the new flow again.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) needRulesVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) allowVerdict NS_AVAILABLE(NA, 9_0);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) dropVerdict NS_AVAILABLE(NA, 9_0);
/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)remediateVerdictWithRemediationURLMapKey:(NSString *)remediationURLMapKey remediationButtonTextMapKey:(NSString *)remediationButtonTextMapKey NS_AVAILABLE(NA, 9_0);

/*!
 * @method URLAppendStringVerdictWithMapKey
 * @discussion This class method returns a verdict indicating that safe search URL for the new should be specified
 * @param urlAppendMapKey URL Append map key to be used by the data plugin to notify what the url should be appended with
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)URLAppendStringVerdictWithMapKey:(NSString *)urlAppendMapKey NS_AVAILABLE(NA, 9_0);

/*!
 * @method filterDataVerdictWithFilterInbound:peekInboundBytes:filterOutbound:peekOutboundBytes:
 * @discussion This class method returns a new flow verdict indicating that the filter needs to make a decision about a new flow after seeing a portion of the flow's data.
 * @param filterInbound A boolean indicating if the filter needs to see inbound data
 * @param peekInboundBytes The number of inbound bytes that the filter needs to see in the subsequent call to -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @param filterOutbound  boolean indicating if the filter needs to see outbound data
 * @param peekOutboundBytes The number of outbound bytes that the filter needs to see in the subsequent call to -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The new flow verdict.
 */
+ (NEFilterNewFlowVerdict *)filterDataVerdictWithFilterInbound:(BOOL)filterInbound peekInboundBytes:(NSUInteger)peekInboundBytes filterOutbound:(BOOL)filterOutbound peekOutboundBytes:(NSUInteger)peekOutboundBytes NS_AVAILABLE(NA, 9_0);

@end

/*!
 * @interface NEFilterControlVerdict
 * @discussion The NEFilterControlVerdict declares the programmatic interface of an object that is the verdict for a new flow of network data by the control provider.
 *
 * NEFilterControlVerdict is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterControlVerdict : NEFilterNewFlowVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be allowed to go through, and also tell the data provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)allowVerdictWithUpdateRules:(BOOL)updateRules NS_AVAILABLE(NA, 9_0);

/*!
 * @method dropVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be dropped, and also tell the data provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)dropVerdictWithUpdateRules:(BOOL)updateRules NS_AVAILABLE(NA, 9_0);

/*!
 * @method updateRules
 * @discussion This class method returns a verdict indicating that the flow should be handled by the data provider, and the rules needed by the data provider have been set.
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)updateRules NS_AVAILABLE(NA, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacketTunnelFlow.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEPacketTunnelFlow.h
 * @discussion This file declares the NEPacketTunnelFlow API. The NEPacketTunnelFlow is used by NEPacketTunnelProvider implementations to tunnel IP packets.
 */

/*!
 * @interface NEPacketTunnelFlow
 * @discussion The NEPacketTunnelFlow class declares the programmatic interface of an object that is used by NEPacketTunnelProvider implementations to tunnel IP packets.
 *
 * NEPacketTunnelFlow is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEPacketTunnelFlow : NSObject

/*!
 * @method readPacketsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NSData objects and an array of NSNumber objects. The NSData and NSNumber in corresponding indicies in the array represent one packet. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketsWithCompletionHandler:(void (^)(NSArray<NSData *> *packets, NSArray<NSNumber *> *protocols))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writePackets:completionHandler:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NSData objects, each containing packet data to be written.
 * @param protocols An array of NSNumber objects. Each number contains the protocol of the packet in the corresponding index in the packets array.
 */
- (BOOL)writePackets:(NSArray<NSData *> *)packets withProtocols:(NSArray<NSNumber *> *)protocols NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterManager.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterManager.h
 * @discussion This file declares the NEFilterManager API. The NEFilterManager API is used to configure and control content filtering services.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create filter configurations.
 */

#if defined(__cplusplus)
#define NEFILTER_EXPORT extern "C"
#else
#define NEFILTER_EXPORT extern
#endif

@class NEFilterProviderConfiguration;

/*!
 * @typedef NEFilterError
 * @abstract Filter error codes
 */
typedef NS_ENUM(NSInteger, NEFilterManagerError) {
	/*! @const NEFilterManagerErrorConfigurationInvalid The filter configuration is invalid */
	NEFilterManagerErrorConfigurationInvalid = 1,
	/*! @const NEFilterManagerErrorConfigurationDisabled The filter configuration is not enabled. */
	NEFilterManagerErrorConfigurationDisabled = 2,
	/*! @const NEFilterManagerErrorConfigurationStale The filter configuration needs to be loaded. */
	NEFilterManagerErrorConfigurationStale = 3,
	/*! @const NEFilterManagerErrorConfigurationCannotBeRemoved The filter configuration cannot be removed. */
	NEFilterManagerErrorConfigurationCannotBeRemoved = 4,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @const NEFilterErrorDomain The filter error domain */
NEFILTER_EXPORT NSString * const NEFilterErrorDomain NS_AVAILABLE(10_10, 8_0);

/*! @const NEFilterConfigurationDidChangeNotification Name of the NSNotification that is posted when the filter configuration changes. */
NEFILTER_EXPORT NSString * const NEFilterConfigurationDidChangeNotification NS_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEFilterManager
 * @discussion The NEFilterManager class declares the programmatic interface for an object that manages content filtering configurations.
 *
 * NEFilterManager declares methods and properties for configuring and controlling a filter.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEFilterManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEFilterManager object for the calling process.
 */
+ (NEFilterManager *)sharedManager NS_AVAILABLE(10_10, 8_0);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current filter configuration from the caller's filter preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the filter configuration from the caller's filter preferences. If the filter is enabled, the filter becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the filter configuration in the caller's filter preferences. If the filter is enabled, it will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the filter.
 */
@property (copy, nullable) NSString *localizedDescription NS_AVAILABLE(10_10, 8_0);

/*!
 * @property providerConfiguration
 * @discussion An NEFilterProviderConfiguration object containing the provider-specific portion of the filter configuration.
 */
@property (strong, nullable) NEFilterProviderConfiguration *providerConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the filter. Setting this property will disable filter configurations of other apps. This property will be set to NO when other filter configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEVPNConnection.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

#if !defined(NEVPN_EXPORT)
#define NEVPN_EXPORT extern
#endif

/*!
 * @typedef NEVPNStatus
 * @abstract VPN status codes
 */
typedef NS_ENUM(NSInteger, NEVPNStatus) {
    /*! @const NEVPNStatusInvalid The VPN is not configured. */
    NEVPNStatusInvalid = 0,
    /*! @const NEVPNStatusDisconnected The VPN is disconnected. */
    NEVPNStatusDisconnected = 1,
    /*! @const NEVPNStatusConnecting The VPN is connecting. */
    NEVPNStatusConnecting = 2,
    /*! @const NEVPNStatusConnected The VPN is connected. */
    NEVPNStatusConnected = 3,
    /*! @const NEVPNStatusReasserting The VPN is reconnecting following loss of underlying network connectivity. */
    NEVPNStatusReasserting = 4,
    /*! @const NEVPNStatusDisconnecting The VPN is disconnecting. */
    NEVPNStatusDisconnecting = 5,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @const NEVPNStatusDidChangeNotification Name of the NSNotification that is posted when the VPN status changes. */
NEVPN_EXPORT NSString * const NEVPNStatusDidChangeNotification NS_AVAILABLE(10_10, 8_0);

/*! @const NEVPNConnectionStartOptionUsername Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the username saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionUsername NS_AVAILABLE(10_11, 9_0);

/*! @const kNEVPNConnectioNEVPNConnectionStartOptionPasswordnOptionAuthPassword Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the password saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionPassword NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NEVPNConnection
 * @discussion The NEVPNConnection class declares the programmatic interface for an object that manages VPN connections.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNConnection : NSObject

/*!
 * @method startVPNTunnelAndReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelAndReturnError:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/*!
 * @method startVPNTunnelWithOptions:andReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param options A dictionary that will be passed to the tunnel provider during the process of starting the tunnel.
 *    If not nil, 'options' is an NSDictionary may contain the following keys
 *        NEVPNConnectionStartOptionUsername
 *        NEVPNConnectionStartOptionPassword
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options andReturnError:(NSError **)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method stopVPNTunnel:
 * @discussion This function is used to stop the VPN tunnel. The VPN tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopVPNTunnel NS_AVAILABLE(10_10, 8_0);

/*!
 * @property status
 * @discussion The current status of the VPN.
 */
@property (readonly) NEVPNStatus status NS_AVAILABLE(10_10, 8_0);

/*!
 * @property connectedDate
 * @discussion The date and time when the connection status changed to NEVPNStatusConnected. This property is nil if the connection is not fully established.
 */
@property (readonly, nullable) NSDate *connectedDate NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterControlProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterProvider.h>

@class NEFilterFlow;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterControlProvider.h
 * @discussion This file declares the NEFilterControlProvider API. The NEFilterControlProvider API is used to implement the portion of a custom content filter that is responsible for installing the filtering rules on the device.
 */

/*!
 * @interface NEFilterControlProvider
 * @discussion The NEFilterControlProvider class declares the programmatic interface for an object that is responsible for installing filtering rules on the device.
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterControlProvider : NEFilterProvider

/*!
 * @property remediationMap
 * @discussion A dictionary containing custom strings to be inserted into the "content blocked" page displayed in WebKit. Each key in this dictionary corresponds to a string in the "content blocked" page. The value of each key is a dictionary that maps keys to the custom strings to be inserted into the "content blocked" page. The keys for the sub-dictionaries are defined by the control provider. When the data provider creates a "remediate" verdict using [NEFilterDataVerdict remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:], it passes the key corresponding to the custom string to be inserted into the "content blocked" page.

	Here is a sample remediationMap dictionary:

	remediationMap = @{ NEFilterProviderRemediationMapRemediationURLs :
							@{
								@"RemediateKey1" : @"http://www.remediation_url_1.com",
								@"RemediateKey2" : @"http://www.remediation_url_2.com"
							 },
						NEFilterProviderRemediationMapRemediationButtonTexts :
							@{
								@"RemediationButtonText1" : @"Remediate URL"
							 }
					  };

 */
@property (copy, nullable) NSDictionary<NSString *, NSDictionary<NSString *, NSObject *> *> *remediationMap NS_AVAILABLE(NA, 9_0);

/*!
 * @property URLAppendStringMap
 * @discussion A dictionary containing strings to be appended to URLs.
 */
@property (copy, nullable) NSDictionary<NSString *, NSString *> *URLAppendStringMap NS_AVAILABLE(NA, 9_0);

/*!
 * @method handleRemediationForFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterRemediateVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to remediate the given flow.
 * @param flow An NEFilterFlow object containing details about the flow that requires remediation.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleRemediationForFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler NS_AVAILABLE(NA, 9_0);


/*!
 * @method handleNewFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterNewFlowVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to fetch new rules pertaining to the given flow and place them on disk in a location accessible by the NEFilterDataProvider.
 * @param flow An NEFilterFlow object containing details about the flow that requires a rules update.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleNewFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler NS_AVAILABLE(NA, 9_0);

/*!
 * @method notifyRulesChanged
 * @discussion This function is called by filter control implementations to notify the data provider "out of band" that the rules changed.
 */
- (void)notifyRulesChanged NS_AVAILABLE(NA, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEIPv6Settings.h
/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEIPv6Settings
 * @discussion This file declares the NEIPv6Settings API. The NEIPv6Settings API is used to specify the IPv6 settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEIPv6Route;

/*!
 * @interface NEIPv6Settings
 * @discussion The NEIPv6Settings class declares the programmatic interface for an object that contains IPv6 settings.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv6Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:networkPrefixLengths:
 * @discussion Initialize a newly-allocated NEIPv6Settings object.
 * @param addresses An array of IPv6 addresses represented as dotted decimal strings.
 * @param networkPrefixLengths An array of NSNumber objects each containing the length in bits of the network prefix of the corresponding address in the addresses parameter.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses networkPrefixLengths:(NSArray<NSNumber *> *)networkPrefixLengths NS_AVAILABLE(10_11, 9_0);

/*!
 * @property addresses
 * @discussion An array of IPv6 addresses represented strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses NS_AVAILABLE(10_11, 9_0);

/*!
 * @property networkPrefixLengths
 * @discussion An array of NSNumber objects each representing the length in bits of the network prefix of the corresponding address in the addresses property.
 */
@property (readonly) NSArray<NSNumber *> *networkPrefixLengths NS_AVAILABLE(10_11, 9_0);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *includedRoutes NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *excludedRoutes NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEIPv6Route
 * @discussion The NEIPv6Route class declares the programmatic interface for an object that contains settings for an IPv6 route.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv6Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:networkPrefixLength:
 * @discussion Initialize a newly-allocated NEIPv6Route.
 * @param address The IPv6 address of the destination network.
 * @param networkPrefixLength A number containing the length in bits of the network prefix of the destination network.
 * @return The initialized NEIPv6Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address networkPrefixLength:(NSNumber *)networkPrefixLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationAddress
 * @discussion An IPv6 address represented as a string.
 */
@property (readonly) NSString *destinationAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationNetworkPrefixLength
 * @discussion A number containing the length in bits of the network prefix of the destination network. This prefix in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSNumber *destinationNetworkPrefixLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @property gatewayAddress
 * @discussion The IPv6 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv6 default route.
 */
+ (NEIPv6Route * const)defaultRoute NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NETunnelProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NETUNNELPROVIDER_EXPORT extern "C"
#else
#define NETUNNELPROVIDER_EXPORT extern
#endif

/*!
 * @file NETunnelProvider.h
 * @discussion This file declares the NETunnelProvider API. The NETunnelProvider API is used to implement Network Extension providers that provide network tunneling services.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEVPNProtocol;
@class NETunnelNetworkSettings;
@class NEAppRule;

/*!
 * @typedef NETunnelProviderError
 * @abstract Tunnel Provider error codes
 */
typedef NS_ENUM(NSInteger, NETunnelProviderError) {
	/*! @const NETunnelProviderErrorNetworkSettingsInvalid The provided tunnel network settings are invalid. */
	NETunnelProviderErrorNetworkSettingsInvalid = 1,
	/*! @const NETunnelProviderErrorNetworkSettingsCanceled The request to set/clear the tunnel network settings was canceled. */
	NETunnelProviderErrorNetworkSettingsCanceled = 2,
	/*! @const NETunnelProviderErrorNetworkSettingsFailed The request to set/clear the tunnel network settings failed. */
	NETunnelProviderErrorNetworkSettingsFailed = 3,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @typedef NETunnelProviderRoutingMethod
 * @abstract Network traffic routing methods.
 */
typedef NS_ENUM(NSInteger, NETunnelProviderRoutingMethod) {
	/*! @const NETunnelProviderRoutingMethodDestinationIP Route network traffic to the tunnel based on destination IP */
	NETunnelProviderRoutingMethodDestinationIP = 1,
	/*! @const NETunnelProviderRoutingMethodSourceApplication Route network traffic to the tunnel based on source application */
	NETunnelProviderRoutingMethodSourceApplication = 2,
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*! @const NETunnelProviderErrorDomain The tunnel provider error domain */
NETUNNELPROVIDER_EXPORT NSString * const NETunnelProviderErrorDomain NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NETunnelProvider
 * @discussion The NETunnelProvider class declares the programmatic interface for an object that provides a network tunnel service.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NETunnelProvider : NEProvider

/*!
 * @method handleAppMessage:completionHandler:
 * @discussion This function is called by the framework when the container app sends a message to the provider. Subclasses should override this method to handle the message and optionally send a response.
 * @param messageData An NSData object containing the message sent by the container app.
 * @param completionHandler A block that the method can execute to send a response to the container app. If this parameter is non-nil then the method implementation should always execute the block. If this parameter is nil then the method implementation should treat this as an indication that the container app is not expecting a response.
 */
- (void)handleAppMessage:(NSData *)messageData completionHandler:(nullable void (^)(NSData * __nullable responseData))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method setTunnelNetworkSettings:completionHandler:
 * @discussion This function is called by tunnel provider implementations to set the network settings of the tunnel, including IP routes, DNS servers, and virtual interface addresses depending on the tunnel type. Subclasses should not override this method. This method can be called multiple times during the lifetime of a particular tunnel. It is not necessary to call this function with nil to clear out the existing settings before calling this function with a non-nil configuration.
 * @param tunnelNetworkSettings An NETunnelNetworkSettings object containing all of the desired network settings for the tunnel. Pass nil to clear out the current network settings.
 * @param completionHandler A block that will be called by the framework when the process of setting or clearing the network settings is complete. If an error occurred during the process of setting or clearing the IP network settings then a non-nill NSError object will be passed to this block containing error details.
 */
- (void)setTunnelNetworkSettings:(nullable NETunnelNetworkSettings *)tunnelNetworkSettings completionHandler:(nullable void (^)( NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the provider's current configuration. The value of this property may change during the lifetime of the tunnel provided by this NETunnelProvider, KVO can be used to detect when changes occur.  For different protocol types, this property will contain the corresponding subclass.   For NEVPNProtocolTypePlugin protocol type, this property will contain the NETunnelProviderProtocol subclass.  For NEVPNProtocolTypeIKEv2 protocol type, this property will contain the NEVPNProtocolIKEv2 subclass.
 */
@property (readonly) NEVPNProtocol *protocolConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property appRules
 * @discussion An array of NEAppRule objects specifying which applications are currently being routed through the tunnel provided by this NETunnelProvider. If application-based routing is not enabled for the tunnel, then this property is set to nil. 
 */
@property (readonly, nullable) NSArray<NEAppRule *> *appRules NS_AVAILABLE(10_11, 9_0);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod NS_AVAILABLE(10_11, 9_0);

/*!
 * @property reasserting
 * @discussion A flag that indicates to the framework if this NETunnelProvider is currently re-establishing the tunnel. Setting this flag will cause the session status visible to the user to change to "Reasserting". Clearing this flag will change the user-visible status of the session back to "Connected". Setting and clearing this flag only has an effect if the session is in the "Connected" state.
 */
@property BOOL reasserting NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWBonjourServiceEndpoint.h
//
//  NWBonjourService.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NWEndpoint;

/*!
 * @interface NWBonjourServiceEndpoint
 * @discussion NWBonjourServiceEndpoint is a subclass of NWEndpoint. It represents an endpoint 
 *		backed by a Bonjour service, specified with a name, type, and domain. For example, the 
 *		Bonjour service MyMusicStudio._music._tcp.local. has the name "MyMusicStudio", 
 *		the type "_music._tcp", and the domain "local".
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWBonjourServiceEndpoint : NWEndpoint

/*!
 * @method endpointWithName:type:domain:
 * @param name The Bonjour service name.
 * @param type The Bonjour service type.
 * @param domain The Bonjour service domain.
 * @return An initialized NWBonjourServiceEndpoint object.
 */
+ (instancetype)endpointWithName:(NSString *)name
							type:(NSString *)type
						  domain:(NSString *)domain NS_AVAILABLE(10_11, 9_0);

/*!
 * @property name
 * @discussion The endpoint's Bonjour service name.
 */
@property (readonly) NSString *name NS_AVAILABLE(10_11, 9_0);

/*!
 * @property type
 * @discussion The endpoint's Bonjour service type.
 */
@property (readonly) NSString *type NS_AVAILABLE(10_11, 9_0);

/*!
 * @property domain
 * @discussion The endpoint's Bonjour service domain.
 */
@property (readonly) NSString *domain NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NWUDPSession.h
//
//  NWUDPSession.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NWEndpoint;
@class NWPath;

/*!
 * @typedef NWUDPSessionState
 * @abstract UDP session state values
 */
typedef NS_ENUM(NSInteger, NWUDPSessionState) {
	/*! @constant NWUDPSessionStateInvalid The session is in an invalid or uninitialized state. */
	NWUDPSessionStateInvalid = 0,
	/*! @constant NWUDPSessionStateWaiting The session is waiting for better conditions before
	 *		attempting to make the session ready.
	 */
	NWUDPSessionStateWaiting = 1,
	/*! @constant NWUDPSessionStatePreparing The endpoint is being resolved */
	NWUDPSessionStatePreparing = 2,
	/*! @constant NWUDPSessionStateReady The session is ready for reading and writing data */
	NWUDPSessionStateReady = 3,
	/*! @constant NWUDPSessionStateFailed None of the currently resolved endpoints can be used
	 *		at this time, either due to problems with the path or the client rejecting the
	 *		endpoints.
	 */
	NWUDPSessionStateFailed = 4,
	/*! @constant NWUDPSessionStateCancelled The session has been cancelled by the client */
	NWUDPSessionStateCancelled = 5,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NWUDPSession
 * @discussion Open UDP datagram sessions to an endpoint, and send and receive datagrams.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWUDPSession : NSObject

/*!
 * @method initWithUpgradeForSession:
 * @discussion This convenience initializer can be used to create a new session based on the
 *		original session's endpoint and parameters.
 *
 *		The application should create an NWUDPSession and watch the "hasBetterPath" property. 
 *		When this property is YES, it should call initWithUpgradeForSession: to create a new
 *		session, with the goal to start transferring data on the new better path as soon as
 *		possible to reduce power and potentially monetary cost. When the new "upgrade" session
 *		becomes ready and when the application wraps up the previous application session on
 *		the original session, the application can start using the new "upgrade" session and
 *		tear down the original one.
 *
 * @param session The original session from which the application will upgrade
 * @return An initialized NWUDPSession object.
 */
- (instancetype)initWithUpgradeForSession:(NWUDPSession *)session NS_AVAILABLE(10_11, 9_0);

/*!
 * @property state
 * @discussion The current state of the UDP session. If the state is NWUDPSessionStateReady, 
 *		then the connection is eligible for reading and writing. The state will be
 *		NWUDPSessionStateFailed if the endpoint could not be resolved, or all endpoints have been 
 *		rejected. Use KVO to watch for changes.
 */
@property (readonly) NWUDPSessionState state NS_AVAILABLE(10_11, 9_0);

/*!
 * @property endpoint
 * @discussion The provided endpoint.
 */
@property (readonly) NWEndpoint *endpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property resolvedEndpoint
 * @discussion The currently targeted remote endpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWEndpoint *resolvedEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise. 
 *		Use KVO to watch this property.
 */
@property (readonly, getter=isViable) BOOL viable NS_AVAILABLE(10_11, 9_0);

/*!
 * @property hasBetterPath
 * @discussion YES if there is another path available that is preferred over the currentPath. 
 *		To take advantage of this path, create a new UDPSession. Use KVO to watch for changes.
 */
@property (readonly) BOOL hasBetterPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @property currentPath
 * @discussion The current evaluated path for the resolvedEndpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWPath *currentPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @method tryNextResolvedEndpoint
 * @discussion Mark the current value of resolvedEndpoint as unusable, and try to switch to the 
 *		next available endpoint. This should be used when the caller has attempted to communicate
 *		with the current resolvedEndpoint, and the caller has determined that it is unusable. If
 *		there are no other resolved endpoints, the session will move to the failed state.
 */
- (void)tryNextResolvedEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property maximumDatagramLength
 * @discussion The maximum size of a datagram to be written currently. If a datagram is written
 *		with a longer length, the datagram may be fragmented or encounter an error. Note that this
 *		value is not guaranteed to be the maximum datagram length for end-to-end communication 
 *		across the network. Use KVO to watch for changes.
 */
@property (readonly) NSUInteger maximumDatagramLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @method setReadHandler:maxDatagrams
 * @discussion Set a read handler for datagrams. Reads will be scheduled by the system, so this
 *		method only needs to be called once for a session.
 * @param handler A handler called when datagrams have been read, or when an error has occurred.
 * @param minDatagrams The maximum number of datagrams to send to the handler.
 */
- (void)setReadHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSError * __nullable error))handler
		  maxDatagrams:(NSUInteger)maxDatagrams NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeMultipleDatagrams:completionHandler
 * @discussion Write multiple datagrams. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagram An NSArray of NSData objects, containing the ordered list datagrams to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeMultipleDatagrams:(NSArray<NSData *> *)datagramArray
			 completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeDatagram:completionHandler
 * @discussion Write a single datagram. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagram An NSData containing the datagram to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeDatagram:(NSData *)datagram
	completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method cancel
 * @discussion Move into the NWUDPSessionStateCancelled state. The connection will be terminated,
 *		and all handlers will be cancelled.
 */
- (void)cancel NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NETunnelProviderManager.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNManager.h>
#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppRule;

/*!
 * @file NETunnelProviderManager
 * @discussion This file declares the NETunnelProviderManager API. The NETunnelProviderManager API is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelProviderManager
 * @discussion The NETunnelProviderManager class declares the programmatic interface for an object that is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NETunnelProviderManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NETunnelProvider configurations created by the calling app that have previously been saved to disk and returns them as NETunnelProviderManager objects.
 * @param completionHandler A block that takes an array NETunnelProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETunnelProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method copyAppRules
 * @discussion This function returns an array of NEAppRule objects.
 */
- (nullable NSArray<NEAppRule *> *)copyAppRules NS_AVAILABLE(10_11, 9_0);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterFlow.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 @define NEFilterFlowBytesMax The maximum number of bytes to be passed or peeked for a flow.
 This value indicates that all upcoming bytes should be passed when used as a pass value, and
 indicates that the flow should peek as many bytes as possible when used as a peek value.
 */
#define	NEFilterFlowBytesMax	UINT64_MAX

/*!
 * @file NEFilterFlow.h
 * @discussion This file declares the NEFilterFlow API.
 */

@class NWEndpoint;

/*!
 * @interface NEFilterFlow
 * @discussion The NEFilterFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered.
 *
 * NEFilterFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterFlow : NSObject <NSSecureCoding,NSCopying>
/*!
 * @property URL
 * @discussion The flow's HTTP request URL. Will be nil if the flow did not originate from WebKit.
 */
@property (readonly, nullable) NSURL *URL NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @interface NEFilterBrowserFlow
 * @discussion The NEFilterBrowserFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from NEFilterSource.
 *
 * NEFilterBrowserFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterBrowserFlow :  NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 *	@property request
 *	@discussion The NSURLRequest of the flow.
 */
@property (readonly) NSURLRequest *request NS_AVAILABLE(10_11, 9_0);

/*!
 *	@property response
 *	@discussion The NSURLResponse of the flow. This will be nil until the request is sent to the server and the response headers are received.
 */
@property (readonly, nullable) NSURLResponse *response NS_AVAILABLE(10_11, 9_0);
/*!
 *	@property parentURL
 *	@discussion The parent URL for the current flow which is created to load the sub frames because the flow with the parent URL was allowed. Will be nil if the parent flow does not exist.
 */
@property (readonly, nullable) NSURL *parentURL NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @interface NEFilterSocketFlow
 * @discussion The NEFilterSocketFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from the socket.
 *
 * NEFilterSocketFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterSocketFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 * @property remoteEndpoint
 * @discussion The flow's remote endpoint.
 */
@property (readonly) NWEndpoint *remoteEndpoint NS_AVAILABLE(NA, 9_0);

/*!
 * @property localEndpoint
 * @discussion The flow's local endpoint.
 */
@property (readonly) NWEndpoint *localEndpoint NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketFamily
 *	@discussion Socket family of the socket flow, such as PF_INET.
 */
@property int socketFamily NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketType
 *	@discussion Socket type of the socket flow, such as SOCK_STREAM.
 */
@property int socketType NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketProtocol
 *	@discussion Socket protocol of the socket flow, such as IPPROTO_TCP.
 */
@property int socketProtocol NS_AVAILABLE(NA, 9_0);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWHostEndpoint.h
//
//  NWHostEndpoint.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NWEndpoint;

/*!
 * @interface NWHostEndpoint
 * @discussion NWHostEndpoint is a subclass of NWEndpoint. It represents an endpoint backed by a 
 *		hostname and port. Note that a hostname string may be an IP or IPv6 address.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWHostEndpoint : NWEndpoint

/*!
 * @method endpointWithHostname:port:
 * @param hostname A string representation of the hostname or address, such as www.apple.com or 10.0.0.1.
 * @param port A string containing the port on the host, such as 80.
 * @return An initialized NWHostEndpoint object.
 */
+ (instancetype)endpointWithHostname:(NSString *)hostname
								port:(NSString *)port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property hostname
 * @discussion The endpoint's hostname.
 */
@property (readonly) NSString *hostname NS_AVAILABLE(10_11, 9_0);

/*!
 * @property port
 * @discussion The endpoint's port.
 */
@property (readonly) NSString *port NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEProvider.h
/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

@class NWTCPConnection;
@class NWTLSParameters;
@class NWUDPSession;
@class NWEndpoint;
@class NWHostEndpoint;
@class NWPath;

/*!
 * @typedef NEProviderStopReason
 * @abstract Provider stop reasons
 */
typedef NS_ENUM(NSInteger, NEProviderStopReason) {
	/*! @const NEProviderStopReasonNone No specific reason. */
	NEProviderStopReasonNone = 0,
	/*! @const NEProviderStopReasonUserInitiated The user stopped the provider. */
	NEProviderStopReasonUserInitiated = 1,
	/*! @const NEProviderStopReasonProviderFailed The provider failed. */
	NEProviderStopReasonProviderFailed = 2,
	/*! @const NEProviderStopReasonNoNetworkAvailable There is no network connectivity. */
	NEProviderStopReasonNoNetworkAvailable = 3,
	/*! @const NEProviderStopReasonUnrecoverableNetworkChange The device attached to a new network. */
	NEProviderStopReasonUnrecoverableNetworkChange = 4,
	/*! @const NEProviderStopReasonProviderDisabled The provider was disabled. */
	NEProviderStopReasonProviderDisabled = 5,
	/*! @const NEProviderStopReasonAuthenticationCanceled The authentication process was cancelled. */
	NEProviderStopReasonAuthenticationCanceled = 6,
	/*! @const NEProviderStopReasonConfigurationFailed The provider could not be configured. */
	NEProviderStopReasonConfigurationFailed = 7,
	/*! @const NEProviderStopReasonIdleTimeout The provider was idle for too long. */
	NEProviderStopReasonIdleTimeout = 8,
	/*! @const NEProviderStopReasonConfigurationDisabled The associated configuration was disabled. */
	NEProviderStopReasonConfigurationDisabled = 9,
	/*! @const NEProviderStopReasonConfigurationRemoved The associated configuration was deleted. */
	NEProviderStopReasonConfigurationRemoved = 10,
	/*! @const NEProviderStopReasonSuperceded A high-priority configuration was started. */
	NEProviderStopReasonSuperceded = 11,
	/*! @const NEProviderStopReasonUserLogout The user logged out. */
	NEProviderStopReasonUserLogout = 12,
	/*! @const NEProviderStopReasonUserSwitch The active user changed. */
	NEProviderStopReasonUserSwitch = 13,
	/*! @const NEProviderStopReasonConnectionFailed Failed to establish connection. */
	NEProviderStopReasonConnectionFailed = 14,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @file NEProvider.h
 * @discussion This file declares the NEProvider API. The NEProvider API declares the base class for Network Extension service providers.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEProvider
 * @discussion The NEProvider class declares the programmatic interface that is common for all Network Extension providers.
 *
 * See the sub classes of NEProvider for more details. Developers of Network Extension providers should create sub classes of the sub classes of NEProvider.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProvider : NSObject

/*!
 * @method sleepWithCompletionHandler:
 * @discussion This function is called by the framework when the system is about to go to sleep. Subclass developers can override this method to implement custom behavior such as closing connections or pausing some network activity.
 * @param completionHandler When the method is finished handling the sleep event it must execute this completion handler.
 */
- (void)sleepWithCompletionHandler:(void (^)(void))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method wake
 * @discussion This function is called by the framework immediately after the system wakes up from sleep. Subclass developers can override this method to implement custom behavior such as re-establishing connections or resuming some network activity.
 */
- (void)wake NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createTCPConnectionToEndpoint:enableTLS:TLSParameters:delegate:
 * @discussion This function can be called by subclass implementations to create a TCP connection to a given network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote network endpoint to connect to.
 * @param enableTLS A flag indicating if a TLS session should be negotiated on the connection.
 * @param TLSParameters A set of optional TLS parameters. Only valid if enableTLS is YES. If TLSParameters is nil, the default system parameters will be used for TLS negotiation.
 * @param delegate An object to use as the connections delegate. This object should conform to the NWTCPConnectionAuthenticationDelegate protocol.
 * @return An NWTCPConnection object.
 */
- (NWTCPConnection *)createTCPConnectionToEndpoint:(NWEndpoint *)remoteEndpoint enableTLS:(BOOL)enableTLS TLSParameters:(nullable NWTLSParameters *)TLSParameters delegate:(nullable id)delegate NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createUDPSessionToEndpoint:fromEndpoint:
 * @discussion This function can be called by subclass implementations to create a UDP session between a local network endpoint and a remote network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote endpoint to which UDP datagrams will be sent by the UDP session.
 * @param localEndpoint An NWHostEndpoint object that specifies the local IP address endpoint to use as the source endpoint of the UDP session.
 * @return An NWUDPSession object.
 */
- (NWUDPSession *)createUDPSessionToEndpoint:(NWEndpoint *)remoteEndpoint fromEndpoint:(nullable NWHostEndpoint *)localEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property defaultPath
 * @discussion The current default path for connections created by the provider. Use KVO to watch for network changes.
 */
@property (readonly, nullable) NWPath *defaultPath NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

