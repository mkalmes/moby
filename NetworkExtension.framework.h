// ==========  NetworkExtension.framework/Headers/NWEndpoint.h
//
//  NWEndpoint
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWEndpoint_h_
#define __NWEndpoint_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWEndpoint
 * @discussion NWEndpoint is a generic class to represent network endpoints, such as a port on a remote server.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NWEndpoint : NSObject <NSSecureCoding, NSCopying>

@end

NS_ASSUME_NONNULL_END

#endif // __NWEndpoint_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NEVPNProtocolIPSec.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEVPNProtocolIPSec
 * @discussion The NEVPNProtocolIPSec class declares the programmatic interface of an object that manages the IPSec-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 1 for key negotiation.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNProtocolIPSec : NEVPNProtocol

/*!
 * @property authenticationMethod
 * @discussion The method used to authenticate with the IPSec server. Note that if this property is set to NEVPNIKEAuthenticationMethodNone, extended authentication will still be negotiated if useExtendedAuthentication is set to YES.
 */
@property NEVPNIKEAuthenticationMethod authenticationMethod API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property useExtendedAuthentication
 * @discussion A flag indicating if extended authentication will be negotiated. This authentication is in addition to the IKE authentication used to authenticate the endpoints of the IKE session.
 *   For IKE version 1, when this flag is set X-Auth authentication will be negotiated as part of the IKE session, using the username and password properties as the credential.
 *   For IKE version 2, when this flag is set EAP authentication will be negotiated as part of the IKE session, using the username, password, and/or identity properties as the credential depending on which EAP method the server requires.
 */
@property BOOL useExtendedAuthentication API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property sharedSecretReference
 * @discussion A persistent reference to a keychain item of class kSecClassGenericPassword containing the IKE shared secret.
 */
@property (copy, nullable) NSData *sharedSecretReference API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localIdentifier
 * @discussion A string identifying the local IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *localIdentifier API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property remoteIdentifier
 * @discussion A string identifying the remote IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *remoteIdentifier API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterSettings.h
/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterDataProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEFilterRule;

/*!
 * @interface NEFilterSettings
 * @discussion The NEFilterSettings class declares the programmatic interface for an object that contains filter settings.
 *
 * NEFilterSettings is used by NEFilterDataProviders to communicate the desired settings for the filter to the framework. The framework takes care of applying the contained settings to the system.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithRules:defaultAction:
 * @discussion Initialize a newly-allocated NEFilterSettings object with a set of filtering rules and a default filter action to takke if none
 *    of the rules match.
 * @param rules An NSArray containing an ordered list of NEFilterRule objects. The maximum number of rules that this array can contain is 1000.
 * @param defaultAction The NEFilterAction to take for flows of network data that do not match any of the specified rules. The default defaultAction is
 *     NEFilterActionFilterData. If defaultAction is NEFilterActionAllow or NEFilterActionDrop, then the rules array must contain at least one NEFilterRule.
 * @return the newly-initialized NEFilterSettings object.
 */
- (instancetype)initWithRules:(NSArray<NEFilterRule *> *)rules defaultAction:(NEFilterAction)defaultAction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property rules
 * @discussion An NSArray containing an ordered list of NEFilterRuleObjects. After the NEFilterSettings are applied to the system,
 *     each network flow is matched against these rules in order, and the NEFilterAction of the first rule that matches is taken:
 *         NEFilterActionAllow: Allow the flow of data to proceed on its journey through the networking stack without consulting this provider.
 *         NEFilterActionDrop: Drop the flow without consulting this provider.
 *         NEFilterActionFilterData: Call this provider's handleNewFlow: method with the flow.
 */
@property (readonly, copy) NSArray<NEFilterRule *> *rules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property defaultAction
 * @discussion An NEFilterAction containing the default action to take for flows of network data that do not match any of the specified rules.
 */
@property (readonly) NEFilterAction defaultAction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEDNSProxyProvider.h
/*
 * Copyright (c) 2017-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppProxyFlow;
@class NEDNSSettings;

/*!
 * @file NEDNSProxyProvider.h
 * @discussion This file declares the NEDNSProxyProvider API. The NEDNSProxyProvider is used to implement custom DNS proxy solutions.
 */

/*!
 * @interface NEDNSProxyProvider
 * @discussion The NEDNSProxyProvider class declares the programmatic interface for an object that implements the client side of a custom DNS proxy solution.
 *
 * NEDNSProxyProvider is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSProxyProvider : NEProvider

/*!
 * @method startProxyWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new proxy instance is being created. Subclasses must override this method to perform whatever steps are necessary to ready the proxy for handling flows of network data.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the proxy then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of starting the proxy is complete. If the proxy cannot be started then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the proxy was successfully started.
 */
- (void)startProxyWithOptions:(nullable NSDictionary<NSString *,id> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopProxyWithReason:completionHandler:
 * @discussion This function is called by the framework when the proxy is being stopped. Subclasses must override this method to perform whatever steps are necessary to stop the proxy.
 * @param reason An NEProviderStopReason indicating why the proxy is being stopped.
 * @param completionHandler A block that must be called when the proxy is completely stopped.
 */
- (void)stopProxyWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method cancelProxyWithError:
 * @discussion This function is called by proxy provider implementations to stop the proxy when a network error is encountered that renders the proxy no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the proxy provider implementation encountered.
 */
- (void)cancelProxyWithError:(nullable NSError *)error API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework to deliver a new network data flow to the proxy provider implementation. Subclasses must override this method to perform whatever steps are necessary to ready the proxy to receive data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES. In this case the proxy implementation is responsible for retaining the NEAppProxyFlow object.
 * @param flow The new flow
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewFlow:(NEAppProxyFlow *)flow API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleNewUDPFlow:initialRemoteEndpoint:
 * @discussion This function is called by the framework to deliver a new UDP data flow to the proxy provider implementation. Subclasses can override this method to perform whatever steps are necessary to ready the proxy to receive
 *     data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides
 *     to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES.
 *     In this case the proxy implementation is responsible for retaining the NEAppProxyUDPFlow object.
 *     The default implementation of this method calls -[NEAppProxyProvider handleNewFlow:] and returns its result.
 * @param flow The new UDP flow
 * @param remoteEndpoint The initial remote endpoint provided by the proxied app when the flow was opened.
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewUDPFlow:(NEAppProxyUDPFlow *)flow initialRemoteEndpoint:(NWEndpoint *)remoteEndpoint API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property systemDNSSettings
 * @discussion The current system DNS settings. Use KVO to watch for changes.
 */
@property (readonly, nullable) NSArray<NEDNSSettings *> *systemDNSSettings API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NETunnelProviderSession.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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

API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
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
- (BOOL)startTunnelWithOptions:(nullable NSDictionary<NSString *,id> *)options andReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopTunnel
 * @discussion This function is used to stop the tunnel. The tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopTunnel API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

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
- (BOOL)sendProviderMessage:(NSData *)messageData returnError:(NSError **)error responseHandler:(nullable void (^)( NSData * __nullable responseData))responseHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEVPNManager.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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

#if TARGET_OS_OSX
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNErrorDomain The VPN error domain */
NEVPN_EXPORT NSString * const NEVPNErrorDomain API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNConfigurationChangeNotification Name of the NSNotification that is posted when the VPN configuration changes. */
NEVPN_EXPORT NSString * const NEVPNConfigurationChangeNotification API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEVPNManager
 * @discussion The NEVPNManager class declares the programmatic interface for an object that manages Virtual Private Network (VPN) configurations.
 *
 * NEVPNManager declares methods and properties for configuring and controlling a VPN.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEVPNManager object for the calling process.
 */
+ (NEVPNManager *)sharedManager API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current VPN configuration from the caller's VPN preferences.
 * @param completionHandler A block that will be called on the main thread when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the VPN configuration from the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN is disabled and the VPN On Demand rules are de-activated.
 * @param completionHandler A block that will be called on the main thread when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the VPN configuration in the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN On Demand rules are activated.
 *
 * @param completionHandler A block that will be called on the main thread when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

#if TARGET_OS_OSX
/*!
 * @method setAuthorization:
 * @discussion This function sets an authorization object that can be used to obtain the authorization rights necessary to modify the system VPN configuration.
 * @param authorization The AuthorizationRef to use to obtain rights.
 */
- (void)setAuthorization:(AuthorizationRef)authorization API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property onDemandEnabled
 * @discussion Toggles VPN On Demand.
 */
@property (getter=isOnDemandEnabled) BOOL onDemandEnabled API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the VPN.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property protocol
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocol API_DEPRECATED_WITH_REPLACEMENT("Use protocolConfiguration instead", macos(10.11, 10.11), ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocolConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property connection
 * @discussion The NEVPNConnection object used for controlling the VPN tunnel.
 */
@property (readonly) NEVPNConnection *connection API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the VPN. Setting this property will disable VPN configurations of other apps. This property will be set to NO  when other VPN configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterDataProvider.h
/*
 * Copyright (c) 2015-2019 Apple Inc.
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
@class NEFilterSettings;

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
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterDataProvider : NEFilterProvider

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework when a filtering decision needs to be made about a new network data flow. Subclasses must override this method to implement the steps necessary to match the flow against some locally stored rules and return an appropriate verdict.
 * @param flow An NEFilterFlow object containing details about the new flow.
 * @return An NEFilterNewFlowVerdict object containing the veridct for the new flow.
 */
- (NEFilterNewFlowVerdict *)handleNewFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleInboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some inbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's inbound data at which readBytes begins.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleOutboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some outbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's outbound data at which readBytes begins.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleInboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the inbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleOutboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the outbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleRemediationForFlow:
 * @discussion This function is called by the framework after the user requests remediation for a blocked flow. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterRemediationVerdict verdict for the flow.
 */
- (NEFilterRemediationVerdict *)handleRemediationForFlow:(NEFilterFlow *)flow API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleRulesChanged
 * @discussion This function is called by the framework when -[NEFilterControlProvider notifyRulesChanged] is called. Subclasses should override this method to reload new rules from disk.
 */
- (void)handleRulesChanged API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method applyFilterRules:defaultAction:withCompletionHandler:
 * @discussion The provider calls this function to apply the current set of filtering rules associated with the provider and also change the default filtering action.
 * @param settings A NEFilterSettings object containing the filter settings to apply to the system. Pass nil to revert to the default settings, which are an
 *     empty list of rules and a default action of NEFilterActionFilterData.
 * @param completionHandler A block that will be executed when the settings have been applied to the system. If an error occurs then the error parameter will be non-nil.
 */
- (void)applySettings:(nullable NEFilterSettings *)settings completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method resumeFlow:withVerdict:
 * @discussion This function is called by the provider to resume a flow that was previously paused by the provider returning a pause verdict.
 * @param flow The flow to resume
 * @param verdict The next NEFilterDataVerdict for the flow. This verdict is used as the verdict corresponding to the
 *    flow handler callback (handleNewFlow:, handleInboundDataFromFlow:, etc.) that returned the pause verdict that
 *    paused the flow. This must be either a NEFilterDataVerdict or a NEFilterNewFlowVerdict. It is invalid to resume
 *    a flow that is not paused.
 */
- (void)resumeFlow:(NEFilterFlow *)flow withVerdict:(NEFilterVerdict *)verdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterDataVerdict
 * @discussion The NEFilterDataVerdict class declares the programmatic interface of an object that is the verdict for a flow of network data after some of the data has been seen by the filter.
 *
 * NEFilterDataVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterDataVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)allowVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)dropVerdict API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url. Passing nil will result into data provider being notified with the callback handleRemediationForFlow:
 * @param remediationButtonTextMapKey Remediation button map key used by the data plugin to get the remediation button text. Passing nil will set the button text to "Request Access"
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)remediateVerdictWithRemediationURLMapKey:(nullable NSString *)remediationURLMapKey remediationButtonTextMapKey:(nullable NSString *)remediationButtonTextMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dataVerdictWithPassBytes:peekBytes:
 * @discussion This class method returns a data verdict indicating that the filter is passing a given number of bytes through the filter and needs to see a given number of bytes after the bytes that are passed.
 * @param passBytes The number of bytes to pass through the filter.
 * @param peekBytes The number of bytes after the end of the bytes passed that the filter wants to see in the next call to -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:] or -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The data flow verdict.
 */
+ (NEFilterDataVerdict *)dataVerdictWithPassBytes:(NSUInteger)passBytes peekBytes:(NSUInteger)peekBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the data flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method pauseVerdict
 * @discussion This class method returns a verdict indicating that none of the data provider's handler callbacks shall be called for the flow until after the flow is resumed
 *     by a call to -[NEFilterDataProvider resumeFlow:withVerdict:]. TCP flows may be paused indefinitely. UDP flows will be dropped if not resumed within 10 seconds of
 *     being paused. It is invalid to pause a flow that is already paused.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)pauseVerdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterRemediationVerdict
 * @discussion The NEFilterRemediationVerdict class declares the programmatic interface of an object that is the verdict for a flow which has been blocked by the filter, but the user has made a request for remediation.
 *
 * NEFilterRemediationVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterRemediationVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) allowVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) dropVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the remediation. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEDNSSettings.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithServers:
 * @discussion Initialize a newly-allocated NEDNSSettings object.
 * @param servers An array of DNS server IP address strings.
 */
- (instancetype)initWithServers:(NSArray<NSString *> *)servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property servers
 * @discussion An array of DNS server address strings.
 */
@property (readonly) NSArray<NSString *> *servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*! 
 * @property searchDomains
 * @discussion An array of DNS server search domain strings.
 */
@property (copy, nullable) NSArray<NSString *> *searchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property domainName
 * @discussion A string containing the DNS domain.
 */
@property (copy, nullable) NSString *domainName API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain strings. If this property is non-nil, the DNS settings will only be used to resolve host names within the specified domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomainsNoSearch
 * @discussion A boolean indicating if the match domains should be appended to the search domain list.  Default is NO (match domains will be appended to the search domain list).
 */
@property BOOL matchDomainsNoSearch API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWTCPConnection.h
//
//  NWTCPConnection.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWTCPConnection_h_
#define __NWTCPConnection_h_

#import <Security/Security.h>


NS_ASSUME_NONNULL_BEGIN

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
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NWTCPConnection
 * @discussion Establish TCP connections to an endpoint, and send and receive data on the TCP connection.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
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
- (instancetype)initWithUpgradeForConnection:(NWTCPConnection *)connection API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property state
 * @discussion The status of the connection. Use KVO to watch this property to get updates.
 */
@property (readonly) NWTCPConnectionState state API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise. Use KVO to watch this property.
 */
@property (readonly, getter=isViable) BOOL viable API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property hasBetterPath
 * @discussion YES if the system determines there is a better path the destination can be reached if
 *		the caller creates a new connection using the same endpoint and parameters. This can
 *		be done using the convenience upgrade initializer method.
 *		Use KVO to watch this property to get updates.
 */
@property (readonly) BOOL hasBetterPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property endpoint
 * @discussion The destination endpoint with which this connection was created.
 */
@property (readonly) NWEndpoint *endpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property connectedPath
 * @discussion The network path over which the connection was established. The caller can query
 *		additional properties from the NWPath object for more information.
 *
 * 		Note that this contains a snapshot of information at the time of connection establishment
 * 		for this connection only. As a result, some underlying properties might change in time and
 * 		might not reflect the path for other connections that might be established at different times.
 */
@property (readonly, nullable) NWPath *connectedPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localAddress
 * @discussion The IP address endpoint from which the connection was connected.
 */
@property (readonly, nullable) NWEndpoint *localAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property remoteAddress
 * @discussion The IP address endpoint to which the connection was connected.
 */
@property (readonly, nullable) NWEndpoint *remoteAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property txtRecord
 * @discussion When the connection is connected to a Bonjour service endpoint, the TXT record associated
 * 		with the Bonjour service is available via this property. Beware that the value comes from
 * 		the network. Care must be taken when parsing this potentially malicious value.
 */
@property (readonly, nullable) NSData *txtRecord API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property error
 * @discussion The connection-wide error property indicates any fatal error that occurred while
 * 		processing the connection or performing data reading or writing.
 */
@property (readonly, nullable) NSError *error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method cancel:
 * @discussion Cancel the connection. This will clean up the resources associated with this object
 * 		and transition this object to NWTCPConnectionStateCancelled state.
 */
- (void)cancel API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method readLength:completionHandler:
 * @discussion Read "length" number of bytes. See readMinimumLength:maximumLength:completionHandler:
 * 		for a complete discussion of the callback behavior.
 * @param length The exact number of bytes the application wants to read
 * @param completion The completion handler to be invoked when there is data to read or an error occurred
 */
- (void)readLength:(NSUInteger)length completionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

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
- (void)readMinimumLength:(NSUInteger)minimum maximumLength:(NSUInteger)maximum completionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method write:completionHandler:
 * @discussion Write the given data object content. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param data The data object whose content will be written
 * @param completion The completion handler to be invoked when the data content has been written or an error has occurred.
 * 		If the error is nil, the write succeeded and the caller can write more data.
 */
- (void)write:(NSData *)data completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeClose:
 * @discussion Close this connection's write side such that further write requests won't succeed.
 * 		Note that this has the effect of closing the read side of the peer connection.
 * 		When the connection's read side and write side are closed, the connection is considered
 * 		disconnected and will transition to the appropriate state.
 */
- (void)writeClose API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

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

#endif // __NWTCPConnection_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NETransparentProxyManager.h
/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNManager.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETransparentProxyManager.h
 * @discussion This file declares the NETransparentProxyManager API. The NETransparentProxyManager API is used to configure and control transparent proxies provided by NEAppProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETransparentProxyManager
 * @discussion The NETransparentProxyManager class declares the programmatic interface for an object that is used to configure and control transparent proxies provided by NEAppProxyProviders.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NETransparentProxyManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the transparent proxy configurations associated with the calling app that have previously been saved to disk and returns them as NETransparentProxyManager objects.
 * @param completionHandler A block that takes an array NETransparentProxyManager objects. The array passed to the block may be empty if no transparent proxy configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETransparentProxyManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEAppRule.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithSigningIdentifier:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSigningIdentifier:designatedRequirement:
 * @discussion Initializes a newly-allocated NEAppRule object.
 * @param signingIdentifier The signing identifier of the executable that matches the rule.
 * @param designatedRequirement The designated requirement of the executable that matches the rule.
 */
- (instancetype)initWithSigningIdentifier:(NSString *)signingIdentifier designatedRequirement:(NSString *)designatedRequirement API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchSigningIdentifier
 * @discussion A string containing a signing identifier. If the code signature of the executable being evaluated has a signing identifier equal to this string and all other conditions of the rule match, then the rule matches.
 */
@property (readonly) NSString *matchSigningIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDesignatedRequirement
 * @discussion A string containing a designated requirement. If the code signature of the exectuable being evaluated has a designated requirement equal to this string and all other conditions of the rule match, then the rule matches. This property is required on Mac OS X.
 */
@property (readonly) NSString *matchDesignatedRequirement API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchPath
 * @discussion A string containing a file system path. If the file system path of the executable being evaluated is equal to this string and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSString *matchPath API_AVAILABLE(macos(10.11), ios(9.3)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomains
 * @discussion An array of strings. If the destination host of the network traffic being evaluated has a suffix equal to one of the strings in this array and all other conditions of the rule match, then the rule matches. This property is optional.
 */
@property (copy, nullable) NSArray *matchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NWTLSParameters.h
//
//  NWTLSParameters.h
//  NetworkExtension
//
//  Copyright (c) 2015-2016, 2018 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWTLSParameters_h_
#define __NWTLSParameters_h_


NS_ASSUME_NONNULL_BEGIN

@interface NWTLSParameters : NSObject

/*!
 * @property TLSSessionID
 * @discussion The session ID for the associated connection, used for TLS session resumption.
 *		This property is optional when using TLS.
 */
@property (nullable, copy) NSData *TLSSessionID API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property SSLCipherSuites
 * @discussion The set of allowed cipher suites, as defined in <Security/CipherSuite.h>.
 *		If set to nil, the default cipher suites will be used.
 */
@property (nullable, copy) NSSet<NSNumber *> *SSLCipherSuites API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property minimumSSLProtocolVersion
 * @discussion The minimum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version older than the minimum.
 */
@property (assign) NSUInteger minimumSSLProtocolVersion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property maximumSSLProtocolVersion
 * @discussion The maximum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version newer than the maximum.
 *		This property should be used with caution, since it may limit the use of preferred
 *		SSL protocols.
 */
@property (assign) NSUInteger maximumSSLProtocolVersion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWTLSParameters_h_
// ==========  NetworkExtension.framework/Headers/NEFilterProviderConfiguration.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterProviderConfiguration : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property filterBrowsers
 * @discussion If YES, the filter plugin will be allowed to filter browser traffic. If NO, the filter plugin will not see any browser flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterBrowsers API_DEPRECATED("filterBrowsers is not supported on macOS", macos(10.11, 10.15)) API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property filterSockets
 * @discussion If YES, the filter plugin will be allowed to filter socket traffic. If NO, the filter plugin will not see any socket flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterSockets API_AVAILABLE(ios(9.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property filterPackets
 * @discussion If YES, a NEFilterPacketProvider will be instantiated and will be allowed to filter packets.
 */
@property BOOL filterPackets API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property vendorConfiguration
 * @discussion An optional dictionary of plugin-specific keys to be passed to the plugin.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *vendorConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property serverAddress
 * @discussion The optional address of the server used to support the filter.
 */
@property (copy, nullable) NSString *serverAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property username
 * @discussion The optional username associated with the filter.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property organization
 * @discussion The optional organization associated with the filter.
 */
@property (copy, nullable) NSString *organization API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property passwordReference
 * @discussion The optional password keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *passwordReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property identityReference
 * @discussion The optional certificate identity keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *identityReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property filterDataProviderBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEFilterDataProvider app extension or system extension.
 *     If this property is nil, then the bundle identifier of the NEFilterDataProvider extension in the calling app's
 *     bundle is used, and if the calling app's bundle contains more than one NEFilterDataProvider extension then which one will
 *     be used is undefined.
 */
@property (copy, nullable) NSString *filterDataProviderBundleIdentifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property filterPacketProviderBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEFilterPacketProvider app extension or system extension.
 *     If this property is nil, then the bundle identifier of the NEFilterPacketProvider extension in the calling app's
 *     bundle is used, and if the calling app's bundle contains more than one NEFilterPacketProvider extension then which one will
 *     be used is undefined.
 */
@property (copy, nullable) NSString *filterPacketProviderBundleIdentifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEIPv4Settings.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEIPv4Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:subnetMasks:
 * @discussion Initialize a newly-allocated NEIPv4Settings object.
 * @param addresses An array of IPv4 addresses represented as dotted decimal strings.
 * @param subnetMasks An array of IPv4 subnet masks represented as dotted decimal strings.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses subnetMasks:(NSArray<NSString *> *)subnetMasks API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property addresses
 * @discussion An array of IPv4 addresses represented as dotted decimal strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property subnetMasks
 * @discussion An array of IPv4 subnet masks represented as dotted decimal strings. These subnet masks will be set along with their corresponding addresses from the addresses array on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *subnetMasks API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *includedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *excludedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEIPv4Route
 * @discussion The NEIPv4Route class declares the programmatic interface for an object that contains settings for an IPv4 route.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEIPv4Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:subnetMask:
 * @discussion Initialize a newly-allocated NEIPv4Route.
 * @param address The IPv4 address of the destination network.
 * @param subnetMask The subnet mask of the destination network.
 * @return The initialized NEIPv4Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address subnetMask:(NSString *)subnetMask API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property destinationAddress
 * @discussion An IPv4 address represented as a dotted decimal string. 
 */
@property (readonly) NSString *destinationAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property destinationSubnetMask
 * @discussion An IPv4 subnet mask represented as a dotted decimal string. This mask in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSString *destinationSubnetMask API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property gatewayAddress
 * @discussion The IPv4 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv4 default route.
 */
+ (NEIPv4Route * const)defaultRoute API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWPath.h
//
//  NWPath.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWPath_h_
#define __NWPath_h_


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
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NWPath
 * @discussion A network path, represented with NWPath, expresses the viability status and
 *		properties of the path that a networking connection will take on the device. For example,
 *		if the path status is NWPathStatusSatisfied, then a connection could use that path.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NWPath : NSObject

/*!
 * @property status
 * @discussion The evaluated NWPathStatus of the NWPath.
 */
@property (readonly) NWPathStatus status API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property expensive
 * @discussion Returns YES is the path is considered expensive, as when using a cellular data plan.
 */
@property (readonly, getter=isExpensive) BOOL expensive API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method isEqualToPath:
 * @param path An NWPath object to compare.
 * @return YES if the two path objects have the same content, NO otherwise.
 */
- (BOOL)isEqualToPath:(NWPath *)path API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWPath_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NEVPNProtocolIKEv2.h
/*
 * Copyright (c) 2014-2015, 2018-2019 Apple Inc.
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
	NEVPNIKEv2EncryptionAlgorithmAES128GCM API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos) = 5,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256GCM Advanced Encryption Standard 256 bit (AES256GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES256GCM API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos) = 6,
	/*! @const NEVPNIKEv2EncryptionAlgorithmChaCha20Poly1305 ChaCha20 and Poly1305 (ChaCha20Poly1305) */
	NEVPNIKEv2EncryptionAlgorithmChaCha20Poly1305 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos) = 7,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEVPNIKEv2DiffieHellmanGroup
 * @abstract IKEv2 Diffie Hellman groups
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DiffieHellmanGroup) {
	/*! @const NEVPNIKEv2DiffieHellmanGroupInvalid Diffie Hellman group 0 is not a valid DH group*/
	NEVPNIKEv2DiffieHellmanGroupInvalid = 0,
	/*! @const NEVPNIKEv2DiffieHellmanGroup1 Diffie Hellman group 1 (768-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup1 = 1,
	/*! @const NEVPNIKEv2DiffieHellmanGroup2 Diffie Hellman group 2 (1024-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup2 = 2,
	/*! @const NEVPNIKEv2DiffieHellmanGroup5 Diffie Hellman group 5 (1536-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup5 = 5,
	/*! @const NEVPNIKEv2DiffieHellmanGroup14 Diffie Hellman group 14 (2048-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup14 = 14,
	/*! @const NEVPNIKEv2DiffieHellmanGroup15 Diffie Hellman group 15 (3072-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup15 = 15,
	/*! @const NEVPNIKEv2DiffieHellmanGroup16 Diffie Hellman group 16 (4096-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup16 = 16,
	/*! @const NEVPNIKEv2DiffieHellmanGroup17 Diffie Hellman group 17 (6144-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup17 = 17,
	/*! @const NEVPNIKEv2DiffieHellmanGroup18 Diffie Hellman group 18 (8192-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup18 = 18,
	/*! @const NEVPNIKEv2DiffieHellmanGroup19 Diffie Hellman group 19 (256-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup19 = 19,
	/*! @const NEVPNIKEv2DiffieHellmanGroup20 Diffie Hellman group 20 (384-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup20 = 20,
	/*! @const NEVPNIKEv2DiffieHellmanGroup21 Diffie Hellman group 21 (521-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup21 = 21,
	/*! @const NEVPNIKEv2DiffieHellmanGroup31 Diffie Hellman group 31 (Curve25519) */
	NEVPNIKEv2DiffieHellmanGroup31 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos) = 31,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
	/*! @const NEVPNIKEv2CertificateTypeEd25519 Edwards 25519 curve */
	NEVPNIKEv2CertificateTypeEd25519 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos) = 5,
} API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEVPNIKEv2TLSVersion
 * @abstract TLS Versions for use in EAP-TLS
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2TLSVersion) {
	/*! @const NEVPNIKEv2TLSVersionDefault Use the default TLS configuration */
	NEVPNIKEv2TLSVersionDefault = 0,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.0 */
	NEVPNIKEv2TLSVersion1_0 = 1,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.1 */
	NEVPNIKEv2TLSVersion1_1 = 2,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.2 */
	NEVPNIKEv2TLSVersion1_2 = 3,
} API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @class NEVPNIKEv2SecurityAssociationParameters
 * @discussion The NEVPNIKEv2SecurityAssociationParameters class declares the programmatic interface of an object that manages parameters for an IPSec Security Association
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNIKEv2SecurityAssociationParameters : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property encryptionAlgorithm
 * @discussion The algorithm used by the Security Association to encrypt and decrypt data. Default is NEVPNIKEv2EncryptionAlgorithm3DES.
 */
@property NEVPNIKEv2EncryptionAlgorithm encryptionAlgorithm API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property integrityAlgorithm
 * @discussion The algorithm used by the Security Association to verify the integrity of data. Default is NEVPNIKEv2IntegrityAlgorithmSHA96. The IKE psedo-random function algorithm will be inferred based on the integrity algorithm.
 */
@property NEVPNIKEv2IntegrityAlgorithm integrityAlgorithm API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property diffieHellmanGroup
 * @discussion The Diffie Hellman group used by the Security Association. Default is NEVPNIKEv2DiffieHellmanGroup2.
 */
@property NEVPNIKEv2DiffieHellmanGroup diffieHellmanGroup API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property lifetimeMinutes
 * @discussion The life time of the Security Association, in minutes. Default is 60 for IKE Security Associations, and 30 for Child Security Associations. Before the lifetime is reached, IKEv2 will attempt to rekey the Security Association to maintain the connection.
 */
@property int32_t lifetimeMinutes API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEVPNProtocolIKEv2
 * @discussion The NEVPNProtocolIKEv2 class declares the programmatic interface of an object that manages the IKEv2-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 2 for key negotiation.
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNProtocolIKEv2 : NEVPNProtocolIPSec

/*!
 * @property deadPeerDetectionRate
 * @discussion How frequently the IKEv2 client will run the dead peer detection algorithm.  Default is NEVPNIKEv2DeadPeerDetectionRateMedium.
 */
@property NEVPNIKEv2DeadPeerDetectionRate deadPeerDetectionRate API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property serverCertificateIssuerCommonName
 * @discussion A string containing the Subject Common Name field of the Certificate Authority certificate that issued the IKEv2 server's certificate.
 */
@property (copy, nullable) NSString *serverCertificateIssuerCommonName API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property serverCertificateCommonName
 * @discussion A string containing the value to verify in the IKEv2 server certificate's Subject Common Name field.
 */
@property (copy, nullable) NSString *serverCertificateCommonName API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property certificateType
 * @discussion contains the type of certificate if an certificate is configured.  Default is RSA.
 */
@property NEVPNIKEv2CertificateType certificateType API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property useConfigurationAttributeInternalIPSubnet
 * @discussion Boolean indicating if client should use INTERNAL_IP4_SUBNET / INTERNAL_IP6_SUBNET attributes.  Default is False.
 */
@property BOOL useConfigurationAttributeInternalIPSubnet API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property IKESecurityAssociationParameters
 * @discussion Parameters for the IKE SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *IKESecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property childSecurityAssociationParameters
 * @discussion Parameters for the child SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *childSecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property disableMOBIKE
 * @discussion Disable MOBIKE negotiation. Default is NO.
 */
@property BOOL disableMOBIKE API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property disableRedirect
 * @discussion Disable Server Redirect. Default is NO.
 */
@property BOOL disableRedirect API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enablePFS
 * @discussion Enable Perfect Forward Secrecy. Default is NO.
 */
@property BOOL enablePFS API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enableRevocationCheck
 * @discussion Enable certificate revocation check. Default is NO.
 */
@property BOOL enableRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property strictRevocationCheck
 * @discussion Require positive certificate revocation check response for peer certificate validation to pass. Default is NO.
 */
@property BOOL strictRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property minimumTLSVersion
 * @discussion Sets a minimum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion minimumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property maximumTLSVersion
 * @discussion Sets a maximum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion maximumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enableFallback
 * @discussion Enable Fallback is used to support Wi-Fi Assist. Wi-Fi Assist allows connections for foreground apps to switch over
 *     to Cellular Data when WiFi connectivity is poor. By setting the EnableFallback key, the device will bring up a tunnel over
 *     Cellular Data to carry traffic that is eligible for Wi-Fi Assist and also requires VPN. Enabling fallback requires that the
 *     server support multiple tunnels for a single user. Default is NO.
 */
@property BOOL enableFallback API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEDNSProxyProviderProtocol.h
/*
 * Copyright (c) 2017-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSProxyProviderProtocol.h
 * @discussion This file declares the NEDNSProxyProviderProtocol API. The NEDNSProxyProviderProtocol API is used to specify configuration settings that are specific to Network Extensions provided by NEDNSProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEDNSProxyProviderProtocol
 * @discussion The NEDNSProxyProviderProtocol class declares the programmatic interface for an object that contains NEDNSProxyProvider-specific configuration settings.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSProxyProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NEDNSProxyProvider vendor-specific configuration parameters. This dictionary is passed as-is to NEDNSProxyProviders when a DNS proxy is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEDNSProxyProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEOnDemandRule.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEOnDemandRuleInterfaceType
 * @abstract On Demand rule network interface types
 */
typedef NS_ENUM(NSInteger, NEOnDemandRuleInterfaceType) {
	/*! @const NEOnDemandRuleInterfaceTypeAny */
	NEOnDemandRuleInterfaceTypeAny API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos) = 0,
	/*! @const NEOnDemandRuleInterfaceTypeEthernet Wired Ethernet */
	NEOnDemandRuleInterfaceTypeEthernet API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos) = 1,
	/*! @const NEOnDemandRuleInterfaceTypeWiFi WiFi */
	NEOnDemandRuleInterfaceTypeWiFi API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos) = 2,
	/*! @const NEOnDemandRuleInterfaceTypeCellular Cellular */
	NEOnDemandRuleInterfaceTypeCellular API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos) = 3,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEOnDemandRule
 * @discussion The NEOnDemandRule class declares the programmatic interface for an object that defines an On Demand rule. 
 *
 * NEOnDemandRule is an abstract base class from which other action-specific rule classes are derived.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEOnDemandRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property action
 * @discussion The rule's action
 */
@property (readonly) NEOnDemandRuleAction action API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property DNSSearchDomainMatch
 * @discussion An array of NSString objects. If the current default search domain is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current default search domain does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSSearchDomainMatch API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property DNSServerAddressMatch
 * @discussion An array of DNS server IP addresses represented as NSString objects. If each of the current default DNS servers is equal to one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the default DNS servers do not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *DNSServerAddressMatch API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property interfaceTypeMatch
 * @discussion The type of interface that this rule matches. If the current primary network interface is of this type and all of the other conditions in the rule match, then the rule matches. If this property is 0 (the default), then the current primary interface type does not factor into the rule match.
 */
@property NEOnDemandRuleInterfaceType interfaceTypeMatch API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property SSIDMatch
 * @discussion An array of NSString objects. If the Service Set Identifier (SSID) of the current primary connected network matches one of the strings in this array and all of the other conditions in the rule match, then the rule matches. If this property is nil (the default), then the current primary connected network SSID does not factor into the rule match.
 */
@property (copy, nullable) NSArray<NSString *> *SSIDMatch API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If a request sent to this URL results in a HTTP 200 OK response and all of the other conditions in the rule match, then then rule matches. If this property is nil (the default), then an HTTP request does not factor into the rule match.
 */
@property (copy, nullable) NSURL *probeURL API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEOnDemandRuleConnect
 * @discussion The NEOnDemandRuleConnect class declares the programmatic interface for an object that defines an On Demand rule with the "Connect" action.
 *
 * When rules of this class match, the VPN connection is started whenever an application running on the system opens a network connection.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
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
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
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
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
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
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEOnDemandRuleEvaluateConnection : NEOnDemandRule

/*!
 * @property connectionRules
 * @discussion An array of NEEvaluateConnectionRule objects. Each NEEvaluateConnectionRule object is evaluated in order against the properties of the network connection being established.
 */
@property (copy, nullable) NSArray<NEEvaluateConnectionRule *> *connectionRules API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEEvaluateConnectionRule
 * @discussion The NEEvaluateConnectionRule class declares the programmatic interface for an object that associates properties of network connections with an action.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEEvaluateConnectionRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithMatchDomains:andAction
 * @discussion Initialize an NEEvaluateConnectionRule instance with a list of destination host domains and an action
 */
- (instancetype)initWithMatchDomains:(NSArray<NSString *> *)domains andAction:(NEEvaluateConnectionRuleAction)action API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property action
 * @discussion The action to take if the properties of the network connection being established match the rule.
 */
@property (readonly) NEEvaluateConnectionRuleAction action API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomains
 * @discussion An array of NSString objects. If the host name of the destination of the network connection being established shares a suffix with one of the strings in this array, then the rule matches.
 */
@property (readonly) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property useDNSServers
 * @discussion An array of NSString objects. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded, the DNS servers specified in this array are used to resolve the host name of the destination while evaluating connectivity to the destination. If the resolution fails for any reason, the VPN is started.
 */
@property (copy, nullable) NSArray<NSString *> *useDNSServers API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property probeURL
 * @discussion An HTTP or HTTPS URL. If the rule matches the connection being established and the action is NEEvaluateConnectionRuleActionConnectIfNeeded and a request sent to this URL results in a response with an HTTP response code other than 200, then the VPN is started.
 */
@property (copy, nullable) NSURL *probeURL API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacketTunnelNetworkSettings.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEPacketTunnelNetworkSettings : NETunnelNetworkSettings

/*!
 * @property IPv4Settings
 * @discussion An NEIPv4Settings object that contains the desired tunnel IPv4 settings.
 */
@property (copy, nullable) NEIPv4Settings *IPv4Settings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property IPv6Settings
 * @discussion An NEIPv6Settings object that contains the desired tunnel IPv6 settings.
 */
@property (copy, nullable) NEIPv6Settings *IPv6Settings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property tunnelOverheadBytes
 * @discussion An NSNumber object containing the number of bytes of overhead appended to each outbound packet through the tunnel. The MTU for the TUN interface is computed by subtracting this value from the MTU of the primary physical interface.
 */
@property (copy, nullable) NSNumber *tunnelOverheadBytes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property MTU
 * @discussion An NSNumber object containing the Maximum Transmission Unit (MTU) size in bytes to assign to the TUN interface. If this property is set, the tunnelOverheadBytes property is ignored.
 */
@property (copy, nullable) NSNumber *MTU API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEHotspotHelper.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
#import <os/availability.h>

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
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @interface NEHotspotNetwork
 * @discussion
 *   The NEHotspotNetwork class conveys information about the
 *   network to the HotspotHelper. When the HotspotHelper is asked
 *   to evaluate the current network or filter the Wi-Fi scan list, it
 *   annotates the NEHotspotNetwork via the setConfidence method.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotNetwork : NSObject

/*!
 * @property SSID
 * @discussion The SSID for the Wi-Fi network.
 */
@property (readonly) NSString * SSID
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property BSSID
 * @discussion The BSSID for the Wi-Fi network.
 */
@property (readonly) NSString * BSSID
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property signalStrength
 * @discussion
 *   The signal strength for the Wi-Fi network. The value lies within
 *   the range 0.0 (weak/no signal) to 1.0 (strong signal).
 */
@property (readonly) double signalStrength
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property secure
 * @discussion Indicates whether the network is secure
 */
@property (readonly, getter=isSecure) BOOL secure
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property autoJoined
 * @discussion
 *   Indicates whether the network was joined automatically
 *   (YES) or joined by the user (NO).
 */
@property (readonly, getter=didAutoJoin) BOOL autoJoined
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property justJoined
 * @discussion
 *   Indicates whether the network was just joined. Useful in the
 *   Maintaining state to differentiate whether the Maintain command
 *   is for the initial join, or the subsequent periodic callback.
 */
@property (readonly, getter=didJustJoin) BOOL justJoined
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotHelperCommand : NSObject

/*!
 * @property commandType
 * @discussion
 *   The type of the command.
 */
@property (readonly) NEHotspotHelperCommandType commandType
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property network
 * @discussion
 *   The network associated with the command. May be nil.
 */
@property (readonly, nullable) NEHotspotNetwork * network
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property networkList
 * @discussion
 *   The list of networks associated with a command. Will be nil unless
 *   the command type is kNEHotspotHelperCommandTypeFilterScanList.
 *   This property returns an NSArray of NEHotspotNetwork.
 */
@property (readonly, nullable) NSArray<NEHotspotNetwork *> * networkList
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEHotspotHelperResponse
 * @discussion
 *   The HotspotHelper creates an NEHotspotHelperResponse object to provide
 *   the results of running the corresponding NEHotspotHelperCommand.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method deliver
 * @abstract
 *   Delivers the response to the command.
 * @discussion
 *   Deliver the NEHotspotHelperResponse to the HotspotHelper infrastructure.
 */
- (void)deliver
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @interface NEHotspotHelper
 * @discussion
 *   The NEHotspotHelper class allows an application to register itself as a
 *   HotspotHelper.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
+ (NSArray *_Nullable)supportedNetworkInterfaces /* of NEHotspotNetwork */
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NETunnelProviderProtocol.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NETunnelProvider vendor-specific configuration parameters. This dictionary is passed as-is to NETunnelProviders when a tunnel is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NETunnelProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEPacketTunnelProvider.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEPacketTunnelProvider : NETunnelProvider

/*!
 * @method startTunnelWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new tunnel is being created. Subclasses must override this method to perform whatever steps are necessary to establish the tunnel.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the tunnel then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of startingt the tunnel is complete. If the tunnel cannot be established then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the tunnel was successfully established.
 */
- (void)startTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopTunnelWithReason:completionHandler:
 * @discussion This function is called by the framework when the tunnel is being destroyed. Subclasses must override this method to perform whatever steps are necessary to tear down the tunnel.
 * @param reason An NEProviderStopReason indicating why the tunnel is being stopped.
 * @param completionHandler A block that must be called when the tunnel is completely torn down.
 */
- (void)stopTunnelWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method cancelTunnelWithError:
 * @discussion This function is called by tunnel provider implementations to initiate tunnel destruction when a network error is encountered that renders the tunnel no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the tunnel provider implementation encountered.
 */
- (void)cancelTunnelWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property packetFlow
 * @discussion An NEPacketFlow object that the tunnel provider implementation should use to receive packets from the network stack and inject packets into the network stack. Every time the tunnel is started the packet flow object is in an initialized state and must be explicitly opened before any packets can be received or injected.
 */
@property (readonly) NEPacketTunnelFlow *packetFlow API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method createTCPConnectionThroughTunnelToEndpoint:enableTLS:TLSParameters:delegate:
 * @discussion This function can be called by subclass implementations to create a TCP connection to a given network endpoint, through the tunnel established by the provider. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote network endpoint to connect to.
 * @param enableTLS A flag indicating if a TLS session should be negotiated on the connection.
 * @param TLSParameters A set of optional TLS parameters. Only valid if enableTLS is YES. If TLSParameters is nil, the default system parameters will be used for TLS negotiation.
 * @param delegate An object to use as the connection delegate. This object should conform to the NWTCPConnectionAuthenticationDelegate protocol.
 * @return An NWTCPConnection object.
 */
- (NWTCPConnection *)createTCPConnectionThroughTunnelToEndpoint:(NWEndpoint *)remoteEndpoint enableTLS:(BOOL)enableTLS TLSParameters:(nullable NWTLSParameters *)TLSParameters delegate:(nullable id)delegate API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method createUDPSessionThroughTunnelToEndpoint:fromEndpoint:
 * @discussion This function can be called by subclass implementations to create a UDP session between a local network endpoint and a remote network endpoint, through the tunnel established by the provider. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote endpoint to which UDP datagrams will be sent by the UDP session.
 * @param localEndpoint An NWHostEndpoint object that specifies the local IP address endpoint to use as the source endpoint of the UDP session.
 * @return An NWUDPSession object.
 */
- (NWUDPSession *)createUDPSessionThroughTunnelToEndpoint:(NWEndpoint *)remoteEndpoint fromEndpoint:(nullable NWHostEndpoint *)localEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NetworkExtension.h
/*
 * Copyright (c) 2014-2015, 2017-2019 Apple Inc.
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
#import <NetworkExtension/NEDNSProxyManager.h>
#import <NetworkExtension/NEDNSProxyProvider.h>
#import <NetworkExtension/NEDNSProxyProviderProtocol.h>
#import <NetworkExtension/NEDNSSettings.h>
#import <NetworkExtension/NEFilterControlProvider.h>
#import <NetworkExtension/NEFilterDataProvider.h>
#import <NetworkExtension/NEFilterFlow.h>
#import <NetworkExtension/NEFilterManager.h>
#import <NetworkExtension/NEFilterPacketProvider.h>
#import <NetworkExtension/NEFilterProvider.h>
#import <NetworkExtension/NEFilterProviderConfiguration.h>
#import <NetworkExtension/NEFilterRule.h>
#import <NetworkExtension/NEFilterSettings.h>
#import <NetworkExtension/NEFlowMetaData.h>
#import <NetworkExtension/NEHotspotHelper.h>
#import <NetworkExtension/NEHotspotConfigurationManager.h>
#import <NetworkExtension/NEIPv4Settings.h>
#import <NetworkExtension/NEIPv6Settings.h>
#import <NetworkExtension/NENetworkRule.h>
#import <NetworkExtension/NEOnDemandRule.h>
#import <NetworkExtension/NEPacket.h>
#import <NetworkExtension/NEPacketTunnelFlow.h>
#import <NetworkExtension/NEPacketTunnelNetworkSettings.h>
#import <NetworkExtension/NEPacketTunnelProvider.h>
#import <NetworkExtension/NEProvider.h>
#import <NetworkExtension/NEProxySettings.h>
#import <NetworkExtension/NETransparentProxyManager.h>
#import <NetworkExtension/NETransparentProxyNetworkSettings.h>
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
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyProviderManager : NETunnelProviderManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NEAppProxy configurations associated with the calling app that have previously been saved to disk and returns them as NEAppProxyProviderManager objects.
 * @param completionHandler A block that takes an array NEAppProxyProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NEAppProxyProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEVPNProtocol.h
/*
 * NEVPNProtocol.h
 *
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNProtocol : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property serverAddress
 * @discussion The VPN server. Depending on the protocol, may be an IP address, host name, or URL.
 */
@property (copy, nullable) NSString *serverAddress API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property username
 * @discussion The username component of the VPN authentication credential.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property passwordReference
 * @discussion The password component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassGenericPassword class.
 */
@property (copy, nullable) NSData *passwordReference API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property identityReference
 * @discussion The certificate and private key component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassIdentity class.
 */
@property (copy, nullable) NSData *identityReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property identityData
 * @discussion The PKCS12 data for the VPN authentication identity. The value is a NSData in PKCS12 format.
 */
@property (copy, nullable) NSData *identityData API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property identityDataPassword 
 * @discussion The password to be used to decrypt the PKCS12 identity data.
 */
@property (copy, nullable) NSString *identityDataPassword API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property disconnectOnSleep
 * @discussion If YES, the VPN connection will be disconnected when the device goes to sleep. The default is NO.
 */
@property BOOL disconnectOnSleep API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object containing the proxy settings to use for connections routed through the tunnel.
 */
@property (copy, nullable) NEProxySettings *proxySettings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property includeAllNetworks
 * @discussion If YES, all traffic will be sent over the tunnel, and all traffic will be dropped if the tunnel is down. The default is NO.
 */
@property BOOL includeAllNetworks API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property excludeLocalNetworks
 * @discussion If YES, all traffic destined for local networks will be excluded from the tunnel. The default is NO.
 */
@property BOOL excludeLocalNetworks API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyTCPFlow.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyTCPFlow : NEAppProxyFlow

/*!
 * @method readDataWithCompletionHandler:
 * @discussion Read data from the flow.
 * @param completionHandler A block that will be executed when some data is read from the flow. The block is passed either the data that was read or a non-nil error if an error occurred. If data has a length of 0 then no data can be subsequently read from the flow. The completion handler is only called for the single read operation that was initiated by calling this method. If the caller wants to read more data then it should call this method again to schedule another read operation and another execution of the completion handler block.
 */
- (void)readDataWithCompletionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeData:completionHandler
 * @discussion Write data to the flow.
 * @param data The data to write.
 * @param completionHandler A block that will be executed when the data is written into the associated socket's receive buffer. The caller should use this callback as an indication that it is possible to write more data to the flow without using up excessive buffer memory. If an error occurs while writing the data then a non-nil NSError object is passed to the block.
 */
- (void)writeData:(NSData *)data withCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property remoteEndpoint
 * @discussion An NWEndpoint object containing information about the intended remote endpoint of the flow.
 */
@property (readonly) NWEndpoint *remoteEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NENetworkRule.h
/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NENetworkRule.h
 * @discussion This file declares the NENetworkRule API. The NENetworkRule API is used to specify a rule that matches network traffic.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @typedef NENetworkRuleProtocol
 * @abstract IP protocols
 */
typedef NS_ENUM(NSInteger, NENetworkRuleProtocol) {
	/*! @const NENetworkRuleProtocolAny Matches TCP and UDP traffic */
	NENetworkRuleProtocolAny = 0,
	/*! @const NENetworkRuleProtocolTCP Matches TCP traffic */
	NENetworkRuleProtocolTCP = 1,
	/*! @const NENetworkRuleProtocolUDP Matches UDP traffic */
	NENetworkRuleProtocolUDP = 2,
} NS_SWIFT_NAME(NENetworkRule.Protocol) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @typedef NETrafficDirection
 * @abstract The direction of network traffic
 */
typedef NS_ENUM(NSInteger, NETrafficDirection) {
	/*! @const NETrafficDirectionAny Any direction */
	NETrafficDirectionAny = 0,
	/*! @const NETrafficDirectionInbound Inbound direction */
	NETrafficDirectionInbound = 1,
	/*! @const NETrafficDirectionOutbound Outbound direction */
	NETrafficDirectionOutbound = 2,
} API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@class NWHostEndpoint;

/*!
 * @interface NENetworkRule
 * @discussion The NENetworkRule class declares the programmatic interface of an object that contains a specification of a rule that matches the attributes of network traffic.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NENetworkRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationNetwork:prefix:protocol
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific network.
 * @param networkEndpoint An endpoint object that contains the port and address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *        If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given address or network.
 * @param destinationPrefix An integer that in combination with the address in the endpoint specifies the destination network that the rule matches.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationNetwork:(NWHostEndpoint *)networkEndpoint prefix:(NSUInteger)destinationPrefix protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method initWithDestinationHost:protocol:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific DNS domain.
 * @param hostEndpoint An endpoint object that contains the port and hostname or domain that the rule matches. This endpoint must contain a hostname, not an address.
 *    If the port string of the NWHostEndpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given hostname or domain.
 *    If the hostname string of the endpoint consists of a single label, then the rule will match traffic destined to the specific host with that single label as its name.
 *    If the hostname string of the endpoint consists of 2 or more labels, then the rule will match traffic destined to hosts within the domain specified by the hostname string.
 *    Examples:
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"com" port:@"0"] protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to the host named "com".
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"0"] protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to hosts in the "example.com" DNS domain, including all DNS queries for names in the example.com DNS domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"53"] protocol:NENetworkRuleProtocolAny] - matches all DNS queries/responses for hosts in the "example.com" domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"443"] protocol:NENetworkRuleProtocolTCP] - matches all TCP port 443 traffic to hosts in the "example.com" domain.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationHost:(NWHostEndpoint *)hostEndpoint protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method initWithRemoteNetwork:prefix:localNetwork:prefix:interface:protocol:direction:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches traffic by remote network, local network, protocol, and direction.
 * @param remoteNetwork An endpoint object that contains the remote port and the remote address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *    If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port coming from the remote network.
 *    Pass nil to cause the rule to match any remote network.
 * @param remotePrefix An integer that in combination with the address in remoteNetwork specifies the remote network that the rule matches.
 * @param localNetwork An endpoint object that contains the local port and the local address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *    If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port coming from the local network.
 *    Pass nil to cause the rule to match any local network.
 * @param localPrefix An integer that in combination with the address in localNetwork specifies the local network that the rule matches. This parameter
 *    is ignored if localNetwork is nil.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @param direction A NETrafficDirection value indicating the direction of network traffic that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithRemoteNetwork:(nullable NWHostEndpoint *)remoteNetwork
						 remotePrefix:(NSUInteger)remotePrefix
						 localNetwork:(nullable NWHostEndpoint *)localNetwork
						  localPrefix:(NSUInteger)localPrefix
							 protocol:(NENetworkRuleProtocol)protocol
							direction:(NETrafficDirection)direction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchRemoteEndpoint
 * @discussion The remote endpoint that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchRemoteEndpoint API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchRemotePrefix
 * @discussion A number that specifies the remote sub-network that the rule matches. This property is set to NSNotFound for rules where matchRemoteEndpoint does not contain an IP address.
 */
@property (readonly) NSUInteger matchRemotePrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchLocalNetwork
 * @discussion The local network that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchLocalNetwork API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchLocalPrefix
 * @discussion A number that specifies the local sub-network that the rule matches. This property is set to NSNotFound for rules with a nil matchLocalNetwork property.
 */
@property (readonly) NSUInteger matchLocalPrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchProtocol
 * @discussion A NENetworkRuleProtocol value containing the protocol that the rule matches.
 */
@property (readonly) NENetworkRuleProtocol matchProtocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchDirection
 * @discussion A NETrafficDirection value indicating the network traffic direction that the rule matches.
 */
@property (readonly) NETrafficDirection matchDirection API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEProxySettings.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEProxyServer : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddress:port:
 * @discussion This function initializes a newly-allocated NEProxyServer object
 * @param address The string representation of the proxy server IP address.
 * @param port The TCP port of the proxy server.
 */
- (instancetype)initWithAddress:(NSString *)address port:(NSInteger)port API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property address
 * @discussion The string representation of the proxy server IP address.
 */
@property (readonly) NSString *address API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property port
 * @discussion The TCP port of the proxy server.
 */
@property (readonly) NSInteger port API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property authenticationRequired
 * @discussion A flag indicating if the server requires authentication credentials.
 */
@property BOOL authenticationRequired API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property username
 * @discussion The username portion of the authentication credential to use when communicating with the proxy server.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property password
 * @discussion The password portion of the authentication credential to use when communicating with the proxy server. This property is only saved persistently if the username property is non-nil and non-empty and if the authenticationRequired flag is set.
 */
@property (copy, nullable) NSString *password API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEProxySettings
 * @discussion The NEProxySettings class declares the programmatic interface for an object that contains proxy settings.
 *
 * NEProxySettings is used in the context of a Network Extension configuration to specify the proxy that should be used for network traffic when the Network Extension is active.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEProxySettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property autoProxyConfigurationEnabled
 * @discussion A boolean indicating if proxy auto-configuration is enabled.
 */
@property BOOL autoProxyConfigurationEnabled API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property proxyAutoConfigurationURL
 * @discussion A URL specifying where the PAC script is located.
 */
@property (copy, nullable) NSURL *proxyAutoConfigurationURL API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property proxyAutoConfigurationJavaScript
 * @discussion A string containing the PAC JavaScript source code.
 */
@property (copy, nullable) NSString *proxyAutoConfigurationJavaScript API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property HTTPEnabled
 * @discussion A boolean indicating if the static HTTP proxy is enabled.
 */
@property BOOL HTTPEnabled API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property HTTPServer
 * @discussion A NEProxyServer object containing the HTTP proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPServer API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property HTTPSEnabled
 * @discussion A boolean indicating if the static HTTPS proxy is enabled.
 */
@property BOOL HTTPSEnabled API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property HTTPSServer
 * @discussion A NEProxyServer object containing the HTTPS proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPSServer API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property excludeSimpleHostnames
 * @discussion A flag indicating if the proxy settings should not be used for network destinations specified using single-label host names.
 */
@property BOOL excludeSimpleHostnames API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property exceptionList
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will not be used for the connection.
 */
@property (copy, nullable) NSArray<NSString *> *exceptionList API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomains
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will be used for the connection. Otherwise the proxy settings will not be used. If this property is nil then all connections to which the Network Extension applies will use the proxy settings.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyFlow.h
/*
 * Copyright (c) 2015, 2017-2018 Apple Inc.
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
	/*! @const NEAppProxyFlowErrorDatagramTooLarge An attempt was made to write a datagram that is larger than the socket's receive window */
	NEAppProxyFlowErrorDatagramTooLarge API_AVAILABLE(macos(10.11), ios(9.3)) API_UNAVAILABLE(watchos, tvos) = 9,
	/*! @const NEAppProxyFlowErrorReadAlreadyPending A read operation on the flow is already pending */
	NEAppProxyFlowErrorReadAlreadyPending API_AVAILABLE(macos(10.11), ios(9.3)) API_UNAVAILABLE(watchos, tvos) = 10,
} API_AVAILABLE(macos(10.11), ios(9.0));

/*! @const NEAppProxyErrorDomain The NEAppProxyFlow error domain */
NEAPPPROXYFLOW_EXPORT NSString * const NEAppProxyErrorDomain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEAppProxyFlow
 * @discussion The NEAppProxyFlow class is an abstract base class that declares the programmatic interface for a flow of network data.
 *
 * NEAppProxyFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyFlow : NSObject

/*!
 * @method openWithLocalEndpoint:completionHandler:
 * @discussion This function is used by an NEProvider implementation to indicate that it is ready to handle flow data.
 * @param localEndpoint The address and port that should be used as the local endpoint of the socket associated with this flow. If the source application already specifed a local endpoint by binding the socket then this parameter is ignored.
 * @param completionHandler A block that is called when the process of opening flow is complete. A nil value passed to this block indicates that the flow was opened successfully. A non-nil NSError value indicates that the flow failed to open successfully.
 */
- (void)openWithLocalEndpoint:(nullable NWHostEndpoint *)localEndpoint completionHandler:(void (^)(NSError *__nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method closeReadWithError:
 * @discussion This function is used by an NEProvider implementation to indicate that it does not want to receive any more data from the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeReadWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method closeWriteWithError:
 * @discussion This functions is used by an NEProvider implementation to indicate that it does not have any more data to write to the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeWriteWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property metaData
 * @discussion An NEFlowMetaData object containing meta data for the flow.
 */
@property (readonly) NEFlowMetaData *metaData API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyUDPFlow.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyUDPFlow : NEAppProxyFlow

/*!
 * @method readDatagramWithCompletionHandler:
 * @discussion Read a datagram from the flow.
 * @param completionHandler A block that will be executed when datagrams have been read from the flow. The block takes the datagrams that were read, the destination endpoints of the datagrams, and an NSError. If an error occurred while reading then the error parameter will be non-nil. If the datagrams and remoteEndpoints arrays are non-nill but 
 */
- (void)readDatagramsWithCompletionHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSArray<NWEndpoint *> * __nullable remoteEndpoints,  NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeDatagram:sentByEndpoint:completionHandler:
 * @discussion Write a datagram to the flow.
 * @param datagrams An array of NSData objects containing the data to be written.
 * @param remoteEndpoints The source endpoints of the datagrams.
 * @param completionHandler A block that will be executed when the datagrams have been written to the corresponding socket's receive buffer.
 */
- (void)writeDatagrams:(NSArray<NSData *> *)datagrams sentByEndpoints:(NSArray<NWEndpoint *> *)remoteEndpoints completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localEndpoint
 * @discussion An NWEndpoint object containing the local endpoint of the flow's corresponding socket.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NETunnelNetworkSettings.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
 * NETunnelNetworkSettings is used by NETunnelProviders to communicate the desired network settings for the tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelNetworkSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithTunnelRemoteAddress:
 * @discussion This function initializes a newly-allocated NETunnelNetworkSettings object with a given tunnel remote address.
 * @param address The address of the remote endpoint that is providing the tunnel service.
 */
- (instancetype)initWithTunnelRemoteAddress:(NSString *)address API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property tunnelRemoteAddress
 * @discussion A string containing the IP address of the remote endpoint that is providing the tunnel service.
 */
@property (readonly) NSString *tunnelRemoteAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property DNSSettings
 * @discussion An NEDNSSettings object that contains the desired tunnel DNS settings.
 */
@property (copy, nullable) NEDNSSettings *DNSSettings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object that contains the desired tunnel proxy settings.
 */
@property (copy, nullable) NEProxySettings *proxySettings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEAppProxyProvider.h
/*
 * Copyright (c) 2015, 2017, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppProxyFlow;
@class NEAppProxyUDPFlow;
@class NWEndpoint;

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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyProvider : NETunnelProvider

/*!
 * @method startProxyWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new proxy instance is being created. Subclasses must override this method to perform whatever steps are necessary to ready the proxy for handling flows of network data.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the proxy then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of starting the proxy is complete. If the proxy cannot be started then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the proxy was successfully started.
 */
- (void)startProxyWithOptions:(nullable NSDictionary<NSString *,id> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopProxyWithReason:completionHandler:
 * @discussion This function is called by the framework when the proxy is being stopped. Subclasses must override this method to perform whatever steps are necessary to stop the proxy.
 * @param reason An NEProviderStopReason indicating why the proxy is being stopped.
 * @param completionHandler A block that must be called when the proxy is completely stopped.
 */
- (void)stopProxyWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method cancelProxyWithError:
 * @discussion This function is called by proxy provider implementations to stop the proxy when a network error is encountered that renders the proxy no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the proxy provider implementation encountered.
 */
- (void)cancelProxyWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework to deliver a new network data flow to the proxy provider implementation. Subclasses must override this method to perform whatever steps are necessary to ready the proxy to receive data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES. In this case the proxy implementation is responsible for retaining the NEAppProxyFlow object.
 * @param flow The new flow
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewFlow:(NEAppProxyFlow *)flow API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleNewUDPFlow:initialRemoteEndpoint:
 * @discussion This function is called by the framework to deliver a new UDP data flow to the proxy provider implementation. Subclasses can override this method to perform whatever steps are necessary to ready the proxy to receive
 *     data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides
 *     to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES.
 *     In this case the proxy implementation is responsible for retaining the NEAppProxyUDPFlow object.
 *     The default implementation of this method calls -[NEAppProxyProvider handleNewFlow:] and returns its result.
 * @param flow The new UDP flow
 * @param remoteEndpoint The initial remote endpoint provided by the proxied app when the flow was opened.
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewUDPFlow:(NEAppProxyUDPFlow *)flow initialRemoteEndpoint:(NWEndpoint *)remoteEndpoint API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEDNSProxyManager.h
/*
 * Copyright (c) 2017-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSProxyManager.h
 * @discussion This file declares the NEDNSProxyManager API. The NEDNSProxyManager API is used to configure and control DNS proxies.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create DNS proxy configurations.
 */

#if defined(__cplusplus)
#define NEDNSPROXY_EXPORT extern "C"
#else
#define NEDNSPROXY_EXPORT extern
#endif

@class NEDNSProxyProviderProtocol;

/*!
 * @typedef NEDNSProxyError
 * @abstract DNS proxy error codes
 */
typedef NS_ENUM(NSInteger, NEDNSProxyManagerError) {
	/*! @const NEDNSProxyManagerErrorConfigurationInvalid The DNS proxy configuration is invalid */
	NEDNSProxyManagerErrorConfigurationInvalid = 1,
	/*! @const NEDNSProxyManagerErrorConfigurationDisabled The DNS proxy configuration is not enabled. */
	NEDNSProxyManagerErrorConfigurationDisabled = 2,
	/*! @const NEDNSProxyManagerErrorConfigurationStale The DNS proxy configuration needs to be loaded. */
	NEDNSProxyManagerErrorConfigurationStale = 3,
	/*! @const NEDNSProxyManagerErrorConfigurationCannotBeRemoved The DNS proxy configuration cannot be removed. */
	NEDNSProxyManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEDNSProxyManagerErrorDomain The DNS proxy error domain */
NEDNSPROXY_EXPORT NSString * const NEDNSProxyErrorDomain API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEDNSProxyConfigurationDidChangeNotification Name of the NSNotification that is posted when the DNS proxy configuration changes. */
NEDNSPROXY_EXPORT NSString * const NEDNSProxyConfigurationDidChangeNotification API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEDNSProxyManager
 * @discussion The NEDNSProxyManager class declares the programmatic interface for an object that manages DNS proxy configurations.
 *
 * NEDNSProxyManager declares methods and properties for configuring and controlling a DNS proxy.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSProxyManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEDNSProxyManager object for the calling process.
 */
+ (NEDNSProxyManager *)sharedManager API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current DNS proxy configuration from the caller's DNS proxy preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the DNS proxy configuration from the caller's DNS proxy preferences. If the DNS proxy is enabled, the DNS proxy becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the DNS proxy configuration in the caller's DNS proxy preferences. If the DNS proxy is enabled, it will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the DNS proxy.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerProtocol
 * @discussion An NEDNSProxyProviderProtocol object containing the provider-specific portion of the DNS proxy configuration.
 */
@property (strong, nullable) NEDNSProxyProviderProtocol *providerProtocol API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the DNS proxy. Setting this property will disable DNS proxy configurations of other apps. This property will be set to NO when other DNS proxy configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterProvider.h
/*
 * Copyright (c) 2015-2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>
#import <NetworkExtension/NEFilterFlow.h>

@class NEFilterProviderConfiguration;
@class NEFilterReport;

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
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationURLs API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);			// Key for RemediationURL
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationButtonTexts API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);	// Key for Remediation button text

/*!
 *	Strings which can be appended or inserted into the remediation URL
 */
#define	NEFilterProviderRemediationURLFlowURLHostname			@"NE_FLOW_HOSTNAME"	// Browser flow URL Hostname
#define NEFilterProviderRemediationURLFlowURL					@"NE_FLOW_URL"		// Browser flow URL
#define NEFilterProviderRemediationURLOrganization				@"NE_ORGANIZATION"	// Organization in filter provider configuration
#define NEFilterProviderRemediationURLUsername					@"NE_USERNAME"		// Username in the filter provider configuration

/*!
 * @file NEFilterProvider.h
 * @discussion This file declares the NEFilterProvider API. The NEFilterProvider API is used to implement custom content
 * filtering solutions.
 */

/*!
 * @interface NEFilterProvider
 * @discussion The NEFilterProvider class is an abstract base class that declares the programmatic interface of an
 * object that implements a socket filter.
 *
 * NEFilterProvider is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterProvider : NEProvider

/*!
 * @method startFilterWithCompletionHandler:
 * @discussion This function is called by the framework when the content filter is being started. Subclasses must
 * override this method and perform whatever steps are necessary to start the filter.
 * @param completionHandler A block that must be called when the process of starting the filter is complete. If the
 * filter was started successfully, subclass implementations must pass the nil value to this block. If an error occurred
 * while starting the filter, sublcass implementations must pass a non-nil NSError containing more details about the error.
 */
- (void)startFilterWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopFilterWithReason:completionHandler:
 * @discussion This function is called by the framework when the content filter is being stopped. Subclasses must
 * override this method and perform whatever steps are necessary to stop the filter.
 * @param reason An NEProviderStopReason indicating why the filter is being stopped.
 * @param completionHandler A block that must be called when the process of stopping the filter is complete.
 */
- (void)stopFilterWithReason:(NEProviderStopReason)reason
		   completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property filterConfiguration
 * @discussion An NEContentFilterConfiguration object containing the current filter configuration. The value of this
 * property can change during the lifetime of a filter. Filter implementations can use KVO to be notified when the
 * configuration changes.
 */
@property (readonly) NEFilterProviderConfiguration *filterConfiguration API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleReport:
 * @discussion This function is called by the framework when the data provider extension returns a verdict with the report property set to True.
 *     Subclass implementations may override this method to handle the flow report.
 * @param report The report being delivered.
 */
- (void)handleReport:(NEFilterReport *)report API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEFilterVerdict
 * @discussion The NEFilterVerdict class declares the programmatic interface for an object that is the verdict for a
 * flow of network data.
 *
 * NEFilterVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterVerdict : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property shouldReport
 * @discussion Whether or not to send a report to the control provider's -[NEFilterProvider handleReport:]
 * method when processing this verdict and when the flow is closed. Since the data provider does not need to wait
 * for a response from the control provider before continuing to process the flow, this is a more efficient way to
 * report a flow to the control provider than returning a "need rules" verdict. If the verdict originates in the
 * control provider, this property has no effect. This property applies when the action taken upon a flow is allow,
 * deny, remediate, or filterData (filterData for new flows only). Setting this flag on a verdict for a socket
 * flow will also cause the data provider's -[NEFilterProvider handleReport:] method to be called when the flow
 * is closed.
 */
@property BOOL shouldReport API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEFilterNewFlowVerdict
 * @discussion The NEFilterNewFlowVerdict declares the programmatic interface of an object that is the verdict for a
 * new flow of network data before any of the flow's data has been seen by the filter.
 *
 * NEFilterNewFlowVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterNewFlowVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle
 * the new flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider
 * to decide on the new flow again.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) allowVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) dropVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to
 * the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)remediateVerdictWithRemediationURLMapKey:(NSString *)remediationURLMapKey
										 remediationButtonTextMapKey:(NSString *)remediationButtonTextMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method URLAppendStringVerdictWithMapKey
 * @discussion This class method returns a verdict indicating that safe search URL for the new should be specified
 * @param urlAppendMapKey URL Append map key to be used by the data plugin to notify what the url should be appended with
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)URLAppendStringVerdictWithMapKey:(NSString *)urlAppendMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method filterDataVerdictWithFilterInbound:peekInboundBytes:filterOutbound:peekOutboundBytes:
 * @discussion This class method returns a new flow verdict indicating that the filter needs to make a decision about
 * a new flow after seeing a portion of the flow's data.
 * @param filterInbound A boolean indicating if the filter needs to see inbound data
 * @param peekInboundBytes The number of inbound bytes that the filter needs to see in the subsequent call to
 * -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @param filterOutbound  boolean indicating if the filter needs to see outbound data
 * @param peekOutboundBytes The number of outbound bytes that the filter needs to see in the subsequent call to
 * -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The new flow verdict.
 */
+ (NEFilterNewFlowVerdict *)filterDataVerdictWithFilterInbound:(BOOL)filterInbound
											  peekInboundBytes:(NSUInteger)peekInboundBytes
												filterOutbound:(BOOL)filterOutbound
											 peekOutboundBytes:(NSUInteger)peekOutboundBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method pauseVerdict
 * @discussion This class method returns a verdict indicating that none of the data provider's handler callbacks shall be called for the flow until after the flow is resumed
 *     by a call to -[NEFilterDataProvider resumeFlow:withVerdict:]. TCP flows may be paused indefinitely. UDP flows will be dropped if not resumed within 10 seconds of
 *     being paused. It is invalid to pause a flow that is already paused.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)pauseVerdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterControlVerdict
 * @discussion The NEFilterControlVerdict declares the programmatic interface of an object that is the verdict for a
 * new flow of network data by the control provider.
 *
 * NEFilterControlVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterControlVerdict : NEFilterNewFlowVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be allowed to go through, and also
 * tell the data provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)allowVerdictWithUpdateRules:(BOOL)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dropVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be dropped, and also tell the data
 * provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)dropVerdictWithUpdateRules:(BOOL)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method updateRules
 * @discussion This class method returns a verdict indicating that the flow should be handled by the data provider,
 * and the rules needed by the data provider have been set.
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end


/*!
 * @typedef NEFilterAction
 * @abstract A NEFilterAction represents the possible actions taken upon a NEFilterFlow that can be reported by the
 * data provider extension to the control provider extension.
 */
typedef NS_ENUM(NSInteger, NEFilterAction){
	/*! @const NEFilterActionInvalid Invalid action, represents an error */
	NEFilterActionInvalid API_AVAILABLE(macos(10.15), ios(11.0)) = 0,
	/*! @const NEFilterActionAllow Allowing the flow */
	NEFilterActionAllow API_AVAILABLE(macos(10.15), ios(11.0)) = 1,
	/*! @const NEFilterActionDrop Dropping the flow */
	NEFilterActionDrop API_AVAILABLE(macos(10.15), ios(11.0)) = 2,
	/*! @const NEFilterActionRemediate Remediating the flow (a "content blocked" page displayed to the user) */
	NEFilterActionRemediate API_AVAILABLE(ios(11.0)) = 3,
	/*! @const NEFilterActionFilterData Filtering data on the flow */
	NEFilterActionFilterData API_AVAILABLE(macos(10.15), ios(11.0)) = 4,
} API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEFilterReportEvent
 * @abstract A NEFilterReportEvent represents the event that is being reported by the NEFilterReport.
 */
typedef NS_ENUM(NSInteger, NEFilterReportEvent) {
	/*! @const NEFilterReportEventNewFlow The report is reporting a new flow */
	NEFilterReportEventNewFlow = 1,
	/*! @const NEFilterReportEventDataDecision The report is reporting a pass/block decision made after analyzing some amount of a flow's data */
	NEFilterReportEventDataDecision = 2,
	/*! @const NEFilterReportEventFlowClosed The report is reporting that a flow has been closed */
	NEFilterReportEventFlowClosed = 3,
} NS_SWIFT_NAME(NEFilterReport.Event) API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEFilterReport
 * @discussion The NEFilterReport declares the programmatic interface of an object that is a report of actions taken by
 * the data provider.
 *
 * NEFilterReport is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterReport : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property flow
 * @discussion The flow on which the described action was taken.
 */
@property (readonly, nullable) NEFilterFlow *flow API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property action
 * @discussion The action taken upon the reported flow.
 */
@property (readonly) NEFilterAction action API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property type
 * @discussion The type of the report.
 */
@property (readonly) NEFilterReportEvent event API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property bytesInboundCount
 * @discussion The number of inbound bytes received from the flow. This property is only non-zero when the report event is NEFilterReportEventFlowClosed.
 */
@property (readonly) NSUInteger bytesInboundCount API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property bytesOutboundCount
 * @discussion The number of outbound bytes sent on the flow. This property is only non-zero when the report event is NEFilterReportEventFlowClosed.
 */
@property (readonly) NSUInteger bytesOutboundCount API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@end


NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacketTunnelFlow.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NEPacket;

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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEPacketTunnelFlow : NSObject

/*!
 * @method readPacketsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NSData objects and an array of NSNumber objects. The NSData and NSNumber in corresponding indicies in the array represent one packet. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketsWithCompletionHandler:(void (^)(NSArray<NSData *> *packets, NSArray<NSNumber *> *protocols))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writePackets:completionHandler:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NSData objects, each containing packet data to be written.
 * @param protocols An array of NSNumber objects. Each number contains the protocol of the packet in the corresponding index in the packets array.
 */
- (BOOL)writePackets:(NSArray<NSData *> *)packets withProtocols:(NSArray<NSNumber *> *)protocols API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method readPacketObjectsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NEPacket objects. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketObjectsWithCompletionHandler:(void (^)(NSArray<NEPacket *> *packets))completionHandler API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writePacketObjects:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NEPacket objects, each containing packet data and protocol family to be written.
 */
- (BOOL)writePacketObjects:(NSArray<NEPacket *> *)packets API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterManager.h
/*
 * Copyright (c) 2013-2015, 2018, 2019 Apple Inc.
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
 * @typedef NEFilterManagerError
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEFilterErrorDomain The filter error domain */
NEFILTER_EXPORT NSString * const NEFilterErrorDomain API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEFilterConfigurationDidChangeNotification Name of the NSNotification that is posted when the filter configuration changes. */
NEFILTER_EXPORT NSString * const NEFilterConfigurationDidChangeNotification API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEFilterManagerGrade
 * @abstract Filter grade
 */
typedef NS_ENUM(NSInteger, NEFilterManagerGrade) {
	/*! @const NEFilterManagerGradeFirewall The filter acts as a firewall, blocking some network traffic. Firewall grade filters see network traffic before other filter grades. */
	NEFilterManagerGradeFirewall = 1,
	/*! @const NEFilterManagerGradeInspector The filter acts as an inspector of network traffic. Inspector grade filters see network traffic after firewall grade filters. */
	NEFilterManagerGradeInspector = 2,
} NS_SWIFT_NAME(NEFilterManager.Grade) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @interface NEFilterManager
 * @discussion The NEFilterManager class declares the programmatic interface for an object that manages content filtering configurations.
 *
 * NEFilterManager declares methods and properties for configuring and controlling a filter.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEFilterManager object for the calling process.
 */
+ (NEFilterManager *)sharedManager API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current filter configuration from the caller's filter preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the filter configuration from the caller's filter preferences. If the filter is enabled, the filter becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the filter configuration in the caller's filter preferences. If the filter is enabled, it will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the filter.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerConfiguration
 * @discussion An NEFilterProviderConfiguration object containing the provider-specific portion of the filter configuration.
 */
@property (strong, nullable) NEFilterProviderConfiguration *providerConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the filter. On iOS, setting this property will disable filter configurations of other apps, and this property will be set to NO when other filter configurations are enabled.
 *     On macOS, up to 4 filter configurations of the same grade can be enabled simultaneously.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property grade
 * @discussion The grade of the filter. The default grade is NEFilterManagerGradeFirewall.
 */
@property NEFilterManagerGrade grade API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEVPNConnection.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

#if !defined(NEVPN_EXPORT)
#define NEVPN_EXPORT extern
#endif

@class NEVPNManager;

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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNStatusDidChangeNotification Name of the NSNotification that is posted when the VPN status changes. */
NEVPN_EXPORT NSString * const NEVPNStatusDidChangeNotification API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNConnectionStartOptionUsername Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the username saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionUsername API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNConnectionStartOptionPassword Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the password saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionPassword API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEVPNConnection
 * @discussion The NEVPNConnection class declares the programmatic interface for an object that manages VPN connections.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNConnection : NSObject

/*!
 * @method startVPNTunnelAndReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelAndReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
- (BOOL)startVPNTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options andReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopVPNTunnel:
 * @discussion This function is used to stop the VPN tunnel. The VPN tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopVPNTunnel API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property status
 * @discussion The current status of the VPN.
 */
@property (readonly) NEVPNStatus status API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property connectedDate
 * @discussion The date and time when the connection status changed to NEVPNStatusConnected. This property is nil if the connection is not fully established.
 */
@property (readonly, nullable) NSDate *connectedDate API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property manager
 * @discussion The NEVPNManager associated with this NEVPNConnection.
 */
@property (readonly) NEVPNManager *manager API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEPacket.h
/*
 * Copyright (c) 2016 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <netinet/in.h>
#import <NetworkExtension/NENetworkRule.h>
#import "NEFilterFlow.h"

NS_ASSUME_NONNULL_BEGIN

@class NEFlowMetaData;

/*!
 * @interface NEPacket
 * @discussion An NEPacket object represents the data, protocol family, and metadata associated with an IP packet. 
 *	These packets are used to read and write on an NEPacketTunnelFlow.
 *
 * NEPacket is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
__attribute__((visibility("default")))
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NEPacket : NSObject <NSCopying,NSSecureCoding>

/*!
 * @method initWithData:protocolFamily:
 * @discussion Initializes a new NEPacket object with data and protocol family.
 * @param data The content of the packet.
 * @param protocolFamily The protocol family of the packet (such as AF_INET or AF_INET6).
 */
- (instancetype)initWithData:(NSData *)data
			  protocolFamily:(sa_family_t)protocolFamily API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @property data
 * @discussion The data content of the packet.
 */
@property (readonly, copy) NSData *data API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @property protocolFamily
 * @discussion The protocol family of the packet (such as AF_INET or AF_INET6).
 */
@property (readonly) sa_family_t protocolFamily API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @property direction
 * @discussion The direction of the packet.
 */
@property (readonly) NETrafficDirection direction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property metadata
 * @discussion Metadata about the source application and flow for this packet.
 *	This property will only be non-nil when the routing method for the NEPacketTunnelProvider
 *	is NETunnelProviderRoutingMethodSourceApplication.
 */
@property (readonly, nullable) NEFlowMetaData *metadata API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEFilterControlProvider.h
/*
 * Copyright (c) 2015-2018 Apple Inc.
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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
@property (copy, nullable) NSDictionary<NSString *, NSDictionary<NSString *, NSObject *> *> *remediationMap API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property URLAppendStringMap
 * @discussion A dictionary containing strings to be appended to URLs.
 */
@property (copy, nullable) NSDictionary<NSString *, NSString *> *URLAppendStringMap API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleRemediationForFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterRemediateVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to remediate the given flow.
 * @param flow An NEFilterFlow object containing details about the flow that requires remediation.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleRemediationForFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);


/*!
 * @method handleNewFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterNewFlowVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to fetch new rules pertaining to the given flow and place them on disk in a location accessible by the NEFilterDataProvider.
 * @param flow An NEFilterFlow object containing details about the flow that requires a rules update.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleNewFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method notifyRulesChanged
 * @discussion This function is called by filter control implementations to notify the data provider "out of band" that the rules changed.
 */
- (void)notifyRulesChanged API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEIPv6Settings.h
/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEIPv6Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:networkPrefixLengths:
 * @discussion Initialize a newly-allocated NEIPv6Settings object.
 * @param addresses An array of IPv6 addresses represented as dotted decimal strings.
 * @param networkPrefixLengths An array of NSNumber objects each containing the length in bits of the network prefix of the corresponding address in the addresses parameter.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses networkPrefixLengths:(NSArray<NSNumber *> *)networkPrefixLengths API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property addresses
 * @discussion An array of IPv6 addresses represented strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property networkPrefixLengths
 * @discussion An array of NSNumber objects each representing the length in bits of the network prefix of the corresponding address in the addresses property.
 */
@property (readonly) NSArray<NSNumber *> *networkPrefixLengths API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *includedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *excludedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEIPv6Route
 * @discussion The NEIPv6Route class declares the programmatic interface for an object that contains settings for an IPv6 route.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0))
@interface NEIPv6Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:networkPrefixLength:
 * @discussion Initialize a newly-allocated NEIPv6Route.
 * @param address The IPv6 address of the destination network.
 * @param networkPrefixLength A number containing the length in bits of the network prefix of the destination network.
 * @return The initialized NEIPv6Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address networkPrefixLength:(NSNumber *)networkPrefixLength API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property destinationAddress
 * @discussion An IPv6 address represented as a string.
 */
@property (readonly) NSString *destinationAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property destinationNetworkPrefixLength
 * @discussion A number containing the length in bits of the network prefix of the destination network. This prefix in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSNumber *destinationNetworkPrefixLength API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property gatewayAddress
 * @discussion The IPv6 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv6 default route.
 */
+ (NEIPv6Route * const)defaultRoute API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NETransparentProxyNetworkSettings.h
/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETransparentProxyNetworkSettings.h
 * @discussion This file declares the NETransparentProxyNetworkSettings API. The NETransparentProxyNetworkSettings API is used to specify the network traffic that will be routed through a transparent proxy.
 *
 * This API is part of NetworkExtension.framework
 */

@class NENetworkRule;

/*!
 * @interface NETransparentProxyNetworkSettings
 * @discussion The NETransparentProxyNetworkSettings class declares the programmatic interface for an object that contains network settings.
 *
 * NETransparentProxyNetworkSettings is used by NEAppProxyProviders to communicate the desired network settings for the proxy to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NETransparentProxyNetworkSettings : NETunnelNetworkSettings

/*!
 * @property includedNetworkRules
 * @discussion An array of NENetworkRule objects that collectively specify the traffic that will be routed through the transparent proxy. The following restrictions
 *    apply to each NENetworkRule in this list:
 *    Restrictions for rules with an address endpoint:
 *        If the port string of the endpoint is "0" or is the empty string, then the address of the endpoint must be a non-wildcard address (i.e. "0.0.0.0" or "::").
 *        If the address is a wildcard address (i.e. "0.0.0.0" or "::"), then the port string of the endpoint must be non-empty and must not be "0".
 *        A port string of "53" is not allowed. Destination Domain-based rules must be used to match DNS traffic.
 *        The matchLocalNetwork property must be nil.
 *        The matchDirection property must be NETrafficDirectionOutbound.
 */
@property (copy, nullable) NSArray<NENetworkRule *> *includedNetworkRules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property excludedNetworkRules
 * @discussion An array of NENetworkRule objects that collectively specify the traffic that will not be routed through the transparent proxy. The following restrictions
 *    apply to each NENetworkRule in this list:
 *    Restrictions for rules with an address endpoint:
 *        If the port string of the endpoint is "0" or is the empty string, then the address of the endpoint must be a non-wildcard address (i.e. "0.0.0.0" or "::").
 *        If the address is a wildcard address (i.e. "0.0.0.0" or "::"), then the port string of the endpoint must be non-empty and must not be "0".
 *        A port string of "53" is not allowed. Destination Domain-based rules must be used to match DNS traffic.
 *        The matchLocalNetwork property must be nil.
 *        The matchDirection property must be NETrafficDirectionOutbound.
 */
@property (copy, nullable) NSArray<NENetworkRule *> *excludedNetworkRules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEFilterRule.h
/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterDataProvider.h>

@class NENetworkRule;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFilterRule
 * @discussion The NEFilterRule class declares the programmatic interface of an object that defines a rule for matching network traffic and the action to take when the rule matches.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithNetworkRule:action:
 * @discussion Initialize a newly-allocated NEFilterRule object
 * @param networkRule A NENetworkRule object that defines the network traffic characteristics that this rule matches.
 * @param action The action to take when this rule matches.
 */
- (instancetype)initWithNetworkRule:(NENetworkRule *)networkRule action:(NEFilterAction)action API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchNetworkRule
 * @discussion The NENetworkRule that defines the network traffic characteristics that this rule matches.
 */
@property (readonly, copy) NENetworkRule *networkRule API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property action
 * @discussion The action to take when this rule matches network traffic.
 */
@property (readonly) NEFilterAction action API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end


NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NETunnelProvider.h
/*
 * Copyright (c) 2015, 2018, 2019 Apple Inc.
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
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NETunnelProviderRoutingMethod
 * @abstract Network traffic routing methods.
 */
typedef NS_ENUM(NSInteger, NETunnelProviderRoutingMethod) {
	/*! @const NETunnelProviderRoutingMethodDestinationIP Route network traffic to the tunnel based on destination IP */
	NETunnelProviderRoutingMethodDestinationIP = 1,
	/*! @const NETunnelProviderRoutingMethodSourceApplication Route network traffic to the tunnel based on source application */
	NETunnelProviderRoutingMethodSourceApplication = 2,
	/*! @const NETunnelProviderRoutingMethodNetworkRule Route traffic to the tunnel (or proxy) based on NENetworkRule objects specified by the provider */
	NETunnelProviderRoutingMethodNetworkRule API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos) = 3,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);


/*! @const NETunnelProviderErrorDomain The tunnel provider error domain */
NETUNNELPROVIDER_EXPORT NSString * const NETunnelProviderErrorDomain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NETunnelProvider
 * @discussion The NETunnelProvider class declares the programmatic interface for an object that provides a network tunnel service.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProvider : NEProvider

/*!
 * @method handleAppMessage:completionHandler:
 * @discussion This function is called by the framework when the container app sends a message to the provider. Subclasses should override this method to handle the message and optionally send a response.
 * @param messageData An NSData object containing the message sent by the container app.
 * @param completionHandler A block that the method can execute to send a response to the container app. If this parameter is non-nil then the method implementation should always execute the block. If this parameter is nil then the method implementation should treat this as an indication that the container app is not expecting a response.
 */
- (void)handleAppMessage:(NSData *)messageData completionHandler:(nullable void (^)(NSData * __nullable responseData))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method setTunnelNetworkSettings:completionHandler:
 * @discussion This function is called by tunnel provider implementations to set the network settings of the tunnel, including IP routes, DNS servers, and virtual interface addresses depending on the tunnel type. Subclasses should not override this method. This method can be called multiple times during the lifetime of a particular tunnel. It is not necessary to call this function with nil to clear out the existing settings before calling this function with a non-nil configuration.
 * @param tunnelNetworkSettings An NETunnelNetworkSettings object containing all of the desired network settings for the tunnel. Pass nil to clear out the current network settings.
 * @param completionHandler A block that will be called by the framework when the process of setting or clearing the network settings is complete. If an error occurred during the process of setting or clearing the IP network settings then a non-nill NSError object will be passed to this block containing error details.
 */
- (void)setTunnelNetworkSettings:(nullable NETunnelNetworkSettings *)tunnelNetworkSettings completionHandler:(nullable void (^)( NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the provider's current configuration. The value of this property may change during the lifetime of the tunnel provided by this NETunnelProvider, KVO can be used to detect when changes occur.  For different protocol types, this property will contain the corresponding subclass.   For NEVPNProtocolTypePlugin protocol type, this property will contain the NETunnelProviderProtocol subclass.  For NEVPNProtocolTypeIKEv2 protocol type, this property will contain the NEVPNProtocolIKEv2 subclass.
 */
@property (readonly) NEVPNProtocol *protocolConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property appRules
 * @discussion An array of NEAppRule objects specifying which applications are currently being routed through the tunnel provided by this NETunnelProvider. If application-based routing is not enabled for the tunnel, then this property is set to nil. 
 */
@property (readonly, nullable) NSArray<NEAppRule *> *appRules API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property reasserting
 * @discussion A flag that indicates to the framework if this NETunnelProvider is currently re-establishing the tunnel. Setting this flag will cause the session status visible to the user to change to "Reasserting". Clearing this flag will change the user-visible status of the session back to "Connected". Setting and clearing this flag only has an effect if the session is in the "Connected" state.
 */
@property BOOL reasserting API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NWBonjourServiceEndpoint.h
//
//  NWBonjourServiceEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWBonjourServiceEndpoint_h_
#define __NWBonjourServiceEndpoint_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWBonjourServiceEndpoint
 * @discussion NWBonjourServiceEndpoint is a subclass of NWEndpoint. It represents an endpoint
 *		backed by a Bonjour service, specified with a name, type, and domain. For example, the
 *		Bonjour service MyMusicStudio._music._tcp.local. has the name "MyMusicStudio",
 *		the type "_music._tcp", and the domain "local".
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
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
						  domain:(NSString *)domain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property name
 * @discussion The endpoint's Bonjour service name.
 */
@property (readonly) NSString *name API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property type
 * @discussion The endpoint's Bonjour service type.
 */
@property (readonly) NSString *type API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property domain
 * @discussion The endpoint's Bonjour service domain.
 */
@property (readonly) NSString *domain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWBonjourServiceEndpoint_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NWUDPSession.h
//
//  NWUDPSession.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__


#ifndef __NWUDPSession_h_
#define __NWUDPSession_h_


NS_ASSUME_NONNULL_BEGIN

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
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NWUDPSession
 * @discussion Open UDP datagram sessions to an endpoint, and send and receive datagrams.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
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
- (instancetype)initWithUpgradeForSession:(NWUDPSession *)session API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property state
 * @discussion The current state of the UDP session. If the state is NWUDPSessionStateReady,
 *		then the connection is eligible for reading and writing. The state will be
 *		NWUDPSessionStateFailed if the endpoint could not be resolved, or all endpoints have been
 *		rejected. Use KVO to watch for changes.
 */
@property (readonly) NWUDPSessionState state API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property endpoint
 * @discussion The provided endpoint.
 */
@property (readonly) NWEndpoint *endpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property resolvedEndpoint
 * @discussion The currently targeted remote endpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWEndpoint *resolvedEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise.
 *		Use KVO to watch this property.
 */
@property (readonly, getter=isViable) BOOL viable API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property hasBetterPath
 * @discussion YES if there is another path available that is preferred over the currentPath.
 *		To take advantage of this path, create a new UDPSession. Use KVO to watch for changes.
 */
@property (readonly) BOOL hasBetterPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property currentPath
 * @discussion The current evaluated path for the resolvedEndpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWPath *currentPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method tryNextResolvedEndpoint
 * @discussion Mark the current value of resolvedEndpoint as unusable, and try to switch to the
 *		next available endpoint. This should be used when the caller has attempted to communicate
 *		with the current resolvedEndpoint, and the caller has determined that it is unusable. If
 *		there are no other resolved endpoints, the session will move to the failed state.
 */
- (void)tryNextResolvedEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property maximumDatagramLength
 * @discussion The maximum size of a datagram to be written currently. If a datagram is written
 *		with a longer length, the datagram may be fragmented or encounter an error. Note that this
 *		value is not guaranteed to be the maximum datagram length for end-to-end communication
 *		across the network. Use KVO to watch for changes.
 */
@property (readonly) NSUInteger maximumDatagramLength API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method setReadHandler:maxDatagrams
 * @discussion Set a read handler for datagrams. Reads will be scheduled by the system, so this
 *		method only needs to be called once for a session.
 * @param handler A handler called when datagrams have been read, or when an error has occurred.
 * @param maxDatagrams The maximum number of datagrams to send to the handler.
 */
- (void)setReadHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSError * __nullable error))handler
		  maxDatagrams:(NSUInteger)maxDatagrams API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeMultipleDatagrams:completionHandler
 * @discussion Write multiple datagrams. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagramArray An NSArray of NSData objects, containing the ordered list datagrams to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeMultipleDatagrams:(NSArray<NSData *> *)datagramArray
			 completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeDatagram:completionHandler
 * @discussion Write a single datagram. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagram An NSData containing the datagram to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeDatagram:(NSData *)datagram
	completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method cancel
 * @discussion Move into the NWUDPSessionStateCancelled state. The connection will be terminated,
 *		and all handlers will be cancelled.
 */
- (void)cancel API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWUDPSession_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NETunnelProviderManager.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProviderManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NETunnelProvider configurations created by the calling app that have previously been saved to disk and returns them as NETunnelProviderManager objects.
 * @param completionHandler A block that takes an array NETunnelProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETunnelProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method copyAppRules
 * @discussion This function returns an array of NEAppRule objects.
 */
- (nullable NSArray<NEAppRule *> *)copyAppRules API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterFlow.h
/*
 * Copyright (c) 2015, 2016, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NENetworkRule.h>

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
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterFlow : NSObject <NSSecureCoding,NSCopying>
/*!
 * @property URL
 * @discussion The flow's HTTP request URL. Will be nil if the flow did not originate from WebKit.
 */
@property (readonly, nullable) NSURL *URL API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppUniqueIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property sourceAppIdentifier
 * @discussion A string containing the identifier of the source application of the flow. This identifier stays the same for all versions and builds of the application. This identifier is unique among all applications.
 */
@property (readonly, nullable) NSString *sourceAppIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property sourceAppVersion
 * @discussion The short version string of the source application. Will be nil if the app info is unavailable.
 */
@property (readonly, nullable) NSString *sourceAppVersion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 *	@property direction
 *	@discussion Initial direciton of the flow (outgoing or incoming flow)
 */
@property (readonly) NETrafficDirection direction API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property sourceAppAuditToken
 *	@discussion Audit token of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppAuditToken API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterBrowserFlow
 * @discussion The NEFilterBrowserFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from NEFilterSource.
 *
 * NEFilterBrowserFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterBrowserFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 *	@property request
 *	@discussion The NSURLRequest of the flow. This property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLRequest *request API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 *	@property response
 *	@discussion The NSURLResponse of the flow. This will be nil until the request is sent to the server and the response headers are received. And this property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLResponse *response API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
/*!
 *	@property parentURL
 *	@discussion The parent URL for the current flow which is created to load the sub frames because the flow with the parent URL was allowed. Will be nil if the parent flow does not exist.
 */
@property (readonly, nullable) NSURL *parentURL API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
@end

/*!
 * @interface NEFilterSocketFlow
 * @discussion The NEFilterSocketFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from the socket.
 *
 * NEFilterSocketFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterSocketFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 * @property remoteEndpoint
 * @discussion The flow's remote endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *remoteEndpoint API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localEndpoint
 * @discussion The flow's local endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property socketFamily
 *	@discussion Socket family of the socket flow, such as PF_INET.
 */
@property (readonly) int socketFamily API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property socketType
 *	@discussion Socket type of the socket flow, such as SOCK_STREAM.
 */
@property (readonly) int socketType API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property socketProtocol
 *	@discussion Socket protocol of the socket flow, such as IPPROTO_TCP.
 */
@property (readonly) int socketProtocol API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END

// ==========  NetworkExtension.framework/Headers/NEFilterPacketProvider.h
/*
 * Copyright (c) 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Network/Network.h>
#import <NetworkExtension/NEFilterProvider.h>
#import <NetworkExtension/NENetworkRule.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterPacketProvider.h
 * @discussion This file declares the NEFilterPacketProvider API. The NEFilterPacketProvider API is used to implement custom network packet filters.
 *
 * This API is part of NetworkExtension.framework.
 */

@class NEFilterPacketSet;
@class NEPacket;

/*!
 * @interface NEFilterPacketContext
 * @discussion The NEFilterPacketContext class identifies the current filtering context.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterPacketContext : NSObject
@end

/*!
 * @typedef NEFilterPacketProviderVerdict
 * @abstract Verdict for a packet
 */
typedef NS_ENUM(NSInteger, NEFilterPacketProviderVerdict) {
	/*! @const NEFilterPacketProviderVerdictAllow Allow a packet */
	NEFilterPacketProviderVerdictAllow = 0,
	/*! @const NEFilterPacketProviderVerdictDrop Drop a packet */
	NEFilterPacketProviderVerdictDrop = 1,
	/* @const NEFilterPacketProviderVerdictDelay Delay a packet until a future verdict */
	NEFilterPacketProviderVerdictDelay = 2,
} NS_SWIFT_NAME(NEFilterPacketProvider.Verdict) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @typedef NEFilterPacketHandler
 * @discussion A block that makes a filtering decision about a network packet.
 * @param context The context of the current packet filter.
 * @param interface The ingress or egress interface of the packet.
 * @param direction The direction of the packet.
 * @param packetBytes The packet bytes.
 * @param packetLength The length of packetBytes.
 * @return A NEFilterPacketProviderVerdict. If the returned verdict is NEFilterPacketProviderVerdictDelay, then the framework assumes that the block already called -[NEFilterPacketProvider delayCurrentPacket] to obtain a reference to the packet.
 */
typedef NEFilterPacketProviderVerdict (^NEFilterPacketHandler)(NEFilterPacketContext *context, _Nonnull nw_interface_t interface, NETrafficDirection direction, const void *packetBytes, const size_t packetLength)
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @interface NEFilterPacketProvider
 * @discussion The NEFilterPacketProvider class declares the programmatic interface for an object that evaluates network packets decisions about whether to block, allow, or delay the packets.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterPacketProvider : NEFilterProvider

/*!
 * @property packetHandler
 * @discussion A block to be set to handle each packet received or to be sent.  A verdict
 *             to allow, drop or delay must be returned to indicate the treatment of
 *             the packet.  Since there may be multiple filtering sources presenting
 *             frames to the provider, this packet handler may be executed by multiple
 *			   simultaneous threads.  This packet handler must be able to handle execution
 *			   in a multi-threaded environment.
 */
@property (strong, nullable) NEFilterPacketHandler packetHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method delayCurrentPacket
 * @discussion This function is used to delay a packet currently presented by packetHandler.
 *             This function is only valid within the packetHandler block and a verdict of
 *             NEFilterPacketProviderVerdictDelay must be returned after a packet is delayed.  A delayed
 *             packet will be prevented from continuing its journey through the networking stack until
 *             it is either allowed by calling allow() or is dropped by being released.
 * @param context The context of the current packet filter which is passed to the packetHandler block.
 *		   The packetHandler block must pass this context when calling delayCurrentPacket().
 */
- (NEPacket *)delayCurrentPacket:(NEFilterPacketContext *)context API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method allowPacket:
 * @discussion This function is used to allow a previously-delayed packet to continue its journey into or out of the networking stack.
 * @param packet A NEPacket object that contains the data of the packet that was previously delayed by the NEFilterPacketProvider.
 */
- (void)allowPacket:(NEPacket *)packet API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEHotspotConfigurationManager.h
/*
 * Copyright © 2017-2019 Apple Inc.
 * All rights reserved.
 */

/*!
 * @file NEHotspotConfigurationManager.h
 *
 * @discussion
 *   The NEHotspotConfigurationManager interface allows an application to
 *   configure Wi-Fi networks.
 *   An application can use NEHotspotConfiguration API to configure
 *   Open, WEP, WPA/WPA2 Personal, WPA/WPA2 Enterprise and Hotspot 2.0 Wi-Fi networks.
 *
 *   An application that needs access to the NEHotspotConfiguration API must have
 *   the “com.apple.developer.networking.HotspotConfiguration” entitlement.
 *
 *
 * @ignorefuncmacro NS_OPTIONS
 * @ignorefuncmacro NS_ENUM
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEHSCFG_EXPORT extern "C"
#else
#define NEHSCFG_EXPORT extern
#endif

/*!
 * @typedef NEHotspotConfigurationEAPType
 * @abstract EAP Type.
 * @const NEHotspotConfigurationEAPTypeTLS EAP-TLS.
 * @const NEHotspotConfigurationEAPTypeTTLS TTLS.
 * @const NEHotspotConfigurationEAPTypePEAP PEAP.
 * @const NEHotspotConfigurationEAPTypeFAST EAP-FAST.
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationEAPType) {
	NEHotspotConfigurationEAPTypeEAPTLS = 13,
	NEHotspotConfigurationEAPTypeEAPTTLS = 21,
	NEHotspotConfigurationEAPTypeEAPPEAP = 25,
	NEHotspotConfigurationEAPTypeEAPFAST = 43
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.EAPType);

/*!
 * @typedef NEHotspotConfigurationEAPTTLSInnerAuthenticationType
 * @abstract TTLS Inner Authentication Type.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationPAP PAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationCHAP CHAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAP MSCHAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAPv2 MSCHAPv2.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationEAP EAP (Default).
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationTTLSInnerAuthenticationType) {
	NEHotspotConfigurationEAPTTLSInnerAuthenticationPAP = 0,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationCHAP = 1,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAP = 2,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAPv2 = 3,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationEAP = 4
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.TTLSInnerAuthenticationType);

/*!
 * @typedef NEHotspotConfigurationEAPTLSVersion
 * @abstract TLS version to use during TLS handshke.
 * @const NEHotspotConfigurationEAPTLSVersion_1_0 TLS version 1.0.
 * @const NEHotspotConfigurationEAPTLSVersion_1_1 TLS version 1.1.
 * @const NEHotspotConfigurationEAPTLSVersion_1_1 TLS version 1.2 (Default).
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationEAPTLSVersion) {
	NEHotspotConfigurationEAPTLSVersion_1_0 = 0,
	NEHotspotConfigurationEAPTLSVersion_1_1 = 1,
	NEHotspotConfigurationEAPTLSVersion_1_2 = 2,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.TLSVersion);

/*!
 * @interface NEHotspotHS20Settings
 * @discussion
 *   NEHotspotHS20Settings class provides a set of properties that are required
 *   to discover and negotiate Hotspot 2.0 Wi-Fi networks.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotHS20Settings : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property domainName
 * @discussion Domain Name of Legacy Hotspot or Hotspot 2.0 Wi-Fi Network.
 *   This Domain Name is used for Wi-Fi Hotspot 2.0 negotiation.
 */
@property (nonnull, readonly) NSString *domainName API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property roamingEnabled
 * @discussion If set to YES, allows connection to networks of roaming service
 *   providers. Defaults to NO.
 */
@property (getter=isRoamingEnabled) BOOL roamingEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property roamingConsortiumOIs
 * @discussion Array of Roaming Consortium Organization Identifiers used
 *   for Wi-Fi Hotspot 2.0 negotiation.
 */
@property (copy) NSArray<NSString *> *roamingConsortiumOIs API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property naiRealmNames
 * @discussion Array of Network Access Identifier Realm names used for
 *   Wi-Fi Hotspot 2.0 negotiation.
 */
@property (copy) NSArray<NSString *> *naiRealmNames API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property MCCAndMNCs
 * @discussion Array of Mobile Country Code (MCC)/Mobile Network Code (MNC)
 *   pairs used for Wi-Fi Hotspot 2.0 negotiation. Each string must contain
 *   exactly six digits.
 */
@property (copy) NSArray<NSString *> *MCCAndMNCs API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithDomainName:roamingEnabled
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotHSSettings object.
 *   This initializer is used to configure Legacy Hotspot or HS2.0 Wi-Fi Networks.
 *
 * @param domainName The domain name of HS2.0 Wi-Fi Network
 * @param roamingEnabled If YES, allows connections to networks of roaming service providers.
 */
- (instancetype)initWithDomainName:(NSString *)domainName
						   roamingEnabled:(BOOL)roamingEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEHotspotEAPSettings
 * @discussion
 *   NEHotspotEAPSettings class provides a set of properties that are required
 *   to configure a WPA/WPA2 Enterprise or Hotspot 2.0 Wi-Fi networks.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotEAPSettings : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property supportedEAPTypes
 * @discussion Array of supported EAP Types. Refer to NEHotspotConfigurationEAPType
 *   for valid values.
 */
@property (copy) NSArray<NSNumber *> *supportedEAPTypes API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property username
 * @discussion A UTF-8 encoded string containing username component of the user authentication
 *   credentials. Length of this property must be between 1 and 253 characters.
 */
@property (copy) NSString *username API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property outerIdentity
 * @discussion Identity string to be used in EAP-Response/Identity of the outer phase. This key is only
 *   relevant to TTLS, PEAP, and EAP-FAST.
 */
@property (copy) NSString *outerIdentity API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property ttlsInnerAuthentication
 * @discussion Specifies the inner authentication used by the TTLS module.
 *   Possible values are PAP, CHAP, MSCHAP, MSCHAPv2, and EAP. Defaults to EAP.
 */
@property NEHotspotConfigurationTTLSInnerAuthenticationType ttlsInnerAuthenticationType API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property password
 * @discussion The password component of the 802.1X authentication credential.
 *   Length of this property must be between 1 and 64 characters.
 */
@property (copy) NSString *password API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property trustedServerNames
 * @discussion Array of server certificate common names that will be used to verify server's certificate.
 *   The string could have wildcards to specify the name, such as "*.mycompany.net". If a server presents
 *   a certificate with DNSName or Common Name that isn't in this list, it won't be trusted.
 */
@property (copy) NSArray<NSString *> *trustedServerNames API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property isTLSClientCertificateRequired
 * @discussion If YES, supports two-factor authentication for EAP-TTLS, PEAP, or EAP-FAST.
 *   If NO, allows for zero-factor authentication for EAP-TLS. The default is YES for EAP-TLS,
 *   and NO for other EAP types.
 */
@property (getter=isTLSClientCertificateRequired) BOOL tlsClientCertificateRequired API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property preferredTLSVersion
 * @discussion TLS version to use during the TLS handshake.
 *   Default value is NEHotspotConfigurationEAPTLSVersion_1_2.
 */
@property NEHotspotConfigurationEAPTLSVersion preferredTLSVersion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method setIdentity
 * @discussion Setter to configure the EAP peer identity. The application needs to store
 * this identity in keychain access group "$(TeamIdentifierPrefix)com.apple.networkextensionsharing".
 * The API uses SecItemCopyMatching to obtain persistent reference for this identity from application's
 * keychain and uses that at the time of EAP authentication.
 * This property is mandatory when EAP-TLS is desired or tlsClientCertificateRequired is set to YES.
 *
 * @param identity The identity of the EAP Peer. This is a SecIdentityRef object that contains
 * a SecKeyRef object and an associated SecCertificateRef object.
 * @result returns NO if the parameter is not an object of SecIdentityRef type or if the persistent reference
 * is not found in the application's keychain else returns YES.
 *
 */
- (BOOL) setIdentity:(SecIdentityRef) identity API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method setTrustedServerCertificates
 * @discussion Setter to configure an array of trusted server certificates used for trust evaluation of
 * the server certificate.
 *
 * @param certificates Each value in the array is a SecCertificateRef object. Application needs to store
 * the certificates in keychain access group "$(TeamIdentifierPrefix)com.apple.networkextensionsharing".
 * The API uses SecItemCopyMatching to obtain persistent reference for each certificate from application's
 * keychain and uses that at the time os EAP authentication.
 * Number of elements in the array cannot be more than 10.
 *
 * @result returns NO if any element in the array is not an object of type SecCertificateRef or if API
 * fails to find persistent reference for each element from the application's keychain else return YES.
 */
- (BOOL) setTrustedServerCertificates:(NSArray *) certificates API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEHotspotConfiguration
 * @discussion
 *   The NEHotspotConfiguration class represents set of properties that are required
 *   to configure a Wi-Fi Network.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotConfiguration : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property SSID
 * @discussion SSID of the Wi-Fi Network.
 */
@property (readonly) NSString * SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property joinOnce
 * @discussion if set to YES the configuration will not be persisted. Default is NO.
 */
@property BOOL joinOnce API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property lifeTimeInDays
 * @discussion The lifetime of the configuration in days. The configuration is stored for the
 *   number of days specified by this property. The minimum value is 1 day and maximum value is 365 days.
 *   A configuration does not get deleted automatically if this property is not set or set to an invalid value.
 *   This property does not apply to Enterprise and HS2.0 networks.
 */
@property (copy) NSNumber * lifeTimeInDays API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property hidden
 * @discussion if set to YES the system will perform active scan of the SSID. Default is NO.
 */
@property BOOL hidden API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used to configure open Wi-Fi Networks.
 *
 * @param SSID The SSID of the Open Wi-Fi Network.
 *   Length of SSID must be between 1 and 32 characters.
 */
- (instancetype)initWithSSID:(NSString *)SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:passphrase:isWEP
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure either WEP or WPA/WPA2 Personal Wi-Fi Networks.
 *
 * @param SSID The SSID of the WEP or WPA/WPA2 Personal Wi-Fi Network
 * @param passphrase The passphrase credential.
 *   For WPA/WPA2 Personal networks: between 8 and 63 characters.
 *   For Static WEP(64bit)  : 10 Hex Digits
 *   For Static WEP(128bit) : 26 Hex Digits
 * @param isWEP YES specifies WEP Wi-Fi Network else WPA/WPA2 Personal Wi-Fi Network
 */
- (instancetype)initWithSSID:(NSString *)SSID
					  passphrase:(NSString *)passphrase isWEP:(BOOL)isWEP API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:eapSettings
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure WPA/WPA2 Enterprise Wi-Fi Networks.
 *
 * @param SSID The SSID of WPA/WPA2 Enterprise Wi-Fi Network
 * @param eapSettings EAP configuration
 */
- (instancetype)initWithSSID:(NSString *)SSID
					  eapSettings:(NEHotspotEAPSettings *)eapSettings API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithHS20Settings:eapSettings
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure HS2.0 Wi-Fi Networks.
 *
 * @param hs20Settings Hotspot 2.0 configuration
 * @param eapSettings EAP configuration
 */
- (instancetype)initWithHS20Settings:(NEHotspotHS20Settings *)hs20Settings
						eapSettings:(NEHotspotEAPSettings *)eapSettings API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);


@end

/*! @const NEHotspotConfigurationErrorDomain The Hotspot Configuration error domain */
NEHSCFG_EXPORT NSString * const NEHotspotConfigurationErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @typedef NEHotspotConfigurationError
 * @abstract Hotspot Configuration error codes
 * @const NEHotspotConfigurationErrorInvalid The Wi-Fi configuration is invalid
 * @const NEHotspotConfigurationErrorInvalidSSID The given SSID string is invalid.
 * @const NEHotspotConfigurationErrorInvalidWPAPassphrase The given WPA/WPA2 Personal passphrase is invalid.
 * @const NEHotspotConfigurationErrorInvalidWEPPassphrase The given WEP passphrase is invalid.
 * @const NEHotspotConfigurationErrorInvalidEAPSettings  Invalid EAP Settings.
 * @const NEHotspotConfigurationErrorInvalidHS20Settings Invalid Hotspot 2.0 Settings.
 * @const NEHotspotConfigurationErrorInvalidHS20DomainName The given Hotspot 2.0 domain name is invalid.
 * @const NEHotspotConfigurationErrorUserDenied Failed to get the user's approval to add a new configuration.
 * @const NEHotspotConfigurationErrorInternal An internal error was encountered.
 * @const NEHotspotConfigurationErrorPending Previous request by the calling application is pending.
 * @const NEHotspotConfigurationErrorSystemConfiguration The calling application cannot modify the System(MDM/Carrier) configuration.
 * @const NEHotspotConfigurationErrorUnknown An unknown configuration error occurred.
 * @const NEHotspotConfigurationErrorJoinOnceNotSupported JoinOnce option is not support for EAP configuration.
 * @const NEHotspotConfigurationErrorAlreadyAssociated Wi-Fi is already associated.
 * @const NEHotspotConfigurationErrorApplicationIsNotInForeground The application is not in the foreground.
 */
typedef NS_ERROR_ENUM(NEHotspotConfigurationErrorDomain, NEHotspotConfigurationError) {
	NEHotspotConfigurationErrorInvalid 				= 0,
	NEHotspotConfigurationErrorInvalidSSID 				= 1,
	NEHotspotConfigurationErrorInvalidWPAPassphrase 		= 2,
	NEHotspotConfigurationErrorInvalidWEPPassphrase 		= 3,
	NEHotspotConfigurationErrorInvalidEAPSettings 			= 4,
	NEHotspotConfigurationErrorInvalidHS20Settings 			= 5,
	NEHotspotConfigurationErrorInvalidHS20DomainName 		= 6,
	NEHotspotConfigurationErrorUserDenied 				= 7,
	NEHotspotConfigurationErrorInternal 				= 8,
	NEHotspotConfigurationErrorPending 				= 9,
	NEHotspotConfigurationErrorSystemConfiguration 			= 10,
	NEHotspotConfigurationErrorUnknown 				= 11,
	NEHotspotConfigurationErrorJoinOnceNotSupported 		= 12,
	NEHotspotConfigurationErrorAlreadyAssociated 			= 13,
	NEHotspotConfigurationErrorApplicationIsNotInForeground 	= 14
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @interface NEHotspotConfigurationManager
 * @discussion
 *   The NEHotspotConfigurationManager class allows an application to
 *   Add/Update/Remove Wi-Fi Network Configuraton.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotConfigurationManager : NSObject

@property (class, readonly, strong) NEHotspotConfigurationManager *sharedManager;

/*!
 * @method applyConfiguration:
 * @discussion This function adds or updates a Wi-Fi network configuration.
 * @param configuration NEHotspotConfiguration object containing the Wi-Fi network configuration.
 * @param completionHandler A block that will be called when add/update operation is completed.
 *   This could be nil if application does not intend to receive the result.
 *   The NSError passed to this block will be nil if the configuration is successfully stored, non-nil otherwise.
 *   If the configuration is found invalid or API encounters some other error then completionHandler is called
 *   with instance of NSError containing appropriate error code. This API attempts to join the Wi-Fi network
 *   if the configuration is successfully added or updated and the network is found nearby.
 *
 */
- (void)applyConfiguration:(NEHotspotConfiguration *)configuration
						completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method removeConfigurationForSSID:
 * @discussion This function removes Wi-Fi configuration.
 *   If the joinOnce property was set to YES, invoking this method will disassociate from the Wi-Fi network
 *   after the configuration is removed.
 * @param SSID Wi-Fi SSID for which the configuration is to be deleted.
 */
- (void)removeConfigurationForSSID:(NSString *)SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method removeConfigurationForNetworkName:
 * @discussion This function removes Wi-Fi configuration.
 * @param domainName HS2.0 domainName for which the configuration is to be deleted.
 */
- (void)removeConfigurationForHS20DomainName:(NSString *)domainName API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);


/*!
 * @method getConfiguredSSIDsWithCompletionHandler:
 * @discussion This function returns array of SSIDs and HS2.0 Domain Names that the calling application has configured.
 *   It returns nil if there are no networks configurred by the calling application.
 */
- (void)getConfiguredSSIDsWithCompletionHandler:(void (^)(NSArray<NSString *> *))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NEFlowMetaData.h
/*
 * Copyright (c) 2016-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFlowMetaData
 * @discussion The NEFlowMetaData class declares the programmatic interface for an object that contains extra information about a flow.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFlowMetaData : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow. The data object may be empty in cases where the flow originates from a system process.
 */
@property (readonly) NSData *sourceAppUniqueIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property sourceAppSigningIdentifier
 * @discussion A string containing the signing identifier (almost always equivalent to the bundle identifier) of the source app of the flow. The string may be empty in cases where the flow originates from a system process.
 */
@property (readonly) NSString *sourceAppSigningIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property sourceAppAuditToken
 *	@discussion Audit token of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppAuditToken API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  NetworkExtension.framework/Headers/NWHostEndpoint.h
//
//  NWHostEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWHostEndpoint_h_
#define __NWHostEndpoint_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWHostEndpoint
 * @discussion NWHostEndpoint is a subclass of NWEndpoint. It represents an endpoint backed by a
 *		hostname and port. Note that a hostname string may be an IP or IPv6 address.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NWHostEndpoint : NWEndpoint

/*!
 * @method endpointWithHostname:port:
 * @param hostname A string representation of the hostname or address, such as www.apple.com or 10.0.0.1.
 * @param port A string containing the port on the host, such as 80.
 * @return An initialized NWHostEndpoint object.
 */
+ (instancetype)endpointWithHostname:(NSString *)hostname
								port:(NSString *)port API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property hostname
 * @discussion The endpoint's hostname.
 */
@property (readonly) NSString *hostname API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property port
 * @discussion The endpoint's port.
 */
@property (readonly) NSString *port API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWHostEndpoint_h_

#endif // __NE_TAPI__
// ==========  NetworkExtension.framework/Headers/NEProvider.h
/*
 * Copyright (c) 2015, 2018 Apple Inc.
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
	/*! @const NEProviderStopReasonSleep The device went to sleep and disconnectOnSleep is enabled in the configuration */
	NEProviderStopReasonSleep API_AVAILABLE(macos(10.15), ios(13.0)) = 15,
	/*! @const NEProviderStopReasonAppUpdate The NEProvider is being updated */
	NEProviderStopReasonAppUpdate API_AVAILABLE(macos(10.15), ios(13.0)) = 16,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEProvider : NSObject

/*!
 * @method sleepWithCompletionHandler:
 * @discussion This function is called by the framework when the system is about to go to sleep. Subclass developers can override this method to implement custom behavior such as closing connections or pausing some network activity.
 * @param completionHandler When the method is finished handling the sleep event it must execute this completion handler.
 */
- (void)sleepWithCompletionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method wake
 * @discussion This function is called by the framework immediately after the system wakes up from sleep. Subclass developers can override this method to implement custom behavior such as re-establishing connections or resuming some network activity.
 */
- (void)wake API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method createTCPConnectionToEndpoint:enableTLS:TLSParameters:delegate:
 * @discussion This function can be called by subclass implementations to create a TCP connection to a given network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote network endpoint to connect to.
 * @param enableTLS A flag indicating if a TLS session should be negotiated on the connection.
 * @param TLSParameters A set of optional TLS parameters. Only valid if enableTLS is YES. If TLSParameters is nil, the default system parameters will be used for TLS negotiation.
 * @param delegate An object to use as the connections delegate. This object should conform to the NWTCPConnectionAuthenticationDelegate protocol.
 * @return An NWTCPConnection object.
 */
- (NWTCPConnection *)createTCPConnectionToEndpoint:(NWEndpoint *)remoteEndpoint enableTLS:(BOOL)enableTLS TLSParameters:(nullable NWTLSParameters *)TLSParameters delegate:(nullable id)delegate API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method createUDPSessionToEndpoint:fromEndpoint:
 * @discussion This function can be called by subclass implementations to create a UDP session between a local network endpoint and a remote network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote endpoint to which UDP datagrams will be sent by the UDP session.
 * @param localEndpoint An NWHostEndpoint object that specifies the local IP address endpoint to use as the source endpoint of the UDP session.
 * @return An NWUDPSession object.
 */
- (NWUDPSession *)createUDPSessionToEndpoint:(NWEndpoint *)remoteEndpoint fromEndpoint:(nullable NWHostEndpoint *)localEndpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method displayMessage:completionHandler:
 * @discussion This method can be called by subclass implementations to display a message to the user.
 * @param message The message to be displayed.
 * @param completionHandler A block that is executed when the user acknowledges the message. If this method is called on a NEFilterDataProvider instance or the message cannot be displayed, then the completion handler block will be executed immediately with success parameter set to NO. If the message was successfully displayed to the user, then the completion handler block is executed with the success parameter set to YES when the user dismisses the message.
 */
- (void)displayMessage:(NSString *)message completionHandler:(void (^)(BOOL success))completionHandler API_DEPRECATED_WITH_REPLACEMENT("UILocalNotification", macos(10.12, 10.14), ios(10.0, 12.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method startSystemExtensionMode
 * @discussion Start the Network Extension machinery in a system extension (.system bundle). This class method will cause the calling system extension to start handling
 *    requests from nesessionmanager to instantiate appropriate NEProvider sub-class instances. The system extension must declare a mapping of Network Extension extension points to
 *    NEProvider sub-class instances in its Info.plist:
 *        Key: NetworkExtension
 *        Type: Dictionary containing information about the NetworkExtension capabilities of the system extension.
 *
 *            Key: NEProviderClasses
 *            Type: Dictionary mapping NetworkExtension extension point identifiers to NEProvider sub-classes
 *
 *    Example:
 *
 *        <key>NetworkExtension</key>
 *        <dict>
 *            <key>NEProviderClasses</key>
 *            <dict>
 *                <key>com.apple.networkextension.app-proxy</key>
 *                <string>$(PRODUCT_MODULE_NAME).AppProxyProvider</string>
 *                <key>com.apple.networkextension.filter-data</key>
 *                <string>$(PRODUCT_MODULE_NAME).FilterDataProvider</string>
 *            </dict>
 *        </dict>
 *
 *    This method should be called as early as possible after the system extension starts.
 */
+ (void)startSystemExtensionMode API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property defaultPath
 * @discussion The current default path for connections created by the provider. Use KVO to watch for network changes.
 */
@property (readonly, nullable) NWPath *defaultPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

