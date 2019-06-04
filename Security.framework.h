// ==========  Security.framework/Headers/SecureTransport.h
/*
 * Copyright (c) 1999-2002,2005-2019 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * SecureTransport.h - Public API for Apple SSL/TLS Implementation
 */

#ifndef _SECURITY_SECURETRANSPORT_H_
#define _SECURITY_SECURETRANSPORT_H_

/*
 * This file describes the public API for an implementation of the
 * Secure Socket Layer, V. 3.0, Transport Layer Security, V. 1.0 to V. 1.2
 * and Datagram Transport Layer Security V. 1.0
 *
 * There are no transport layer dependencies in this library;
 * it can be used with sockets, Open Transport, etc. Applications using
 * this library provide callback functions which do the actual I/O
 * on underlying network connections. Applications are also responsible
 * for setting up raw network connections; the application passes in
 * an opaque reference to the underlying (connected) entity at the
 * start of an SSL session in the form of an SSLConnectionRef.
 *
 * Some terminology:
 *
 * A "client" is the initiator of an SSL Session. The canonical example
 * of a client is a web browser, when it's talking to an https URL.
 *
 * A "server" is an entity which accepts requests for SSL sessions made
 * by clients. E.g., a secure web server.

 * An "SSL Session", or "session", is bounded by calls to SSLHandshake()
 * and SSLClose(). An "Active session" is in some state between these
 * two calls, inclusive.
 *
 * An SSL Session Context, or SSLContextRef, is an opaque reference in this
 * library to the state associated with one session. A SSLContextRef cannot
 * be reused for multiple sessions.
 */

#include <CoreFoundation/CFArray.h>
#include <Security/SecProtocolOptions.h>
#include <Security/CipherSuite.h>
#include <Security/SecTrust.h>
#include <Security/SecBase.h>
#include <sys/types.h>
#include <Availability.h>

#ifdef __cplusplus
extern "C" {
#endif

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

#define __SECURETRANSPORT_API_DEPRECATED(...) \
    __API_DEPRECATED("No longer supported. Use Network.framework.", __VA_ARGS__)

/***********************
 *** Common typedefs ***
 ***********************/

/* Opaque reference to an SSL session context */
struct SSLContext;
typedef struct CF_BRIDGED_TYPE(id) SSLContext *SSLContextRef;

/* Opaque reference to an I/O connection (socket, endpoint, etc.) */
typedef const void *SSLConnectionRef;

/* SSL session options */
typedef CF_ENUM(int, SSLSessionOption) {
	/*
	 * Set this option to enable returning from SSLHandshake (with a result of
	 * errSSLServerAuthCompleted) when the server authentication portion of the
	 * handshake is complete. This disable certificate verification and
	 * provides an opportunity to perform application-specific server
	 * verification before deciding to continue.
	 */
	kSSLSessionOptionBreakOnServerAuth CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 0,
	/*
	 * Set this option to enable returning from SSLHandshake (with a result of
	 * errSSLClientCertRequested) when the server requests a client certificate.
	 */
	kSSLSessionOptionBreakOnCertRequested CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 1,
    /*
     * This option is the same as kSSLSessionOptionBreakOnServerAuth but applies
     * to the case where SecureTransport is the server and the client has presented
     * its certificates allowing the server to verify whether these should be
     * allowed to authenticate.
     */
    kSSLSessionOptionBreakOnClientAuth CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 2,
    /*
     * Enable/Disable TLS False Start
     * When enabled, False Start will only be performed if a adequate cipher-suite is
     * negotiated.
     */
    kSSLSessionOptionFalseStart CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 3,
    /*
     * Enable/Disable 1/n-1 record splitting for BEAST attack mitigation.
     * When enabled, record splitting will only be performed for TLS 1.0 connections
     * using a block cipher.
     */
    kSSLSessionOptionSendOneByteRecord CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 4,
    /*
     * Allow/Disallow server identity change on renegotiation. Disallow by default
     * to avoid Triple Handshake attack.
     */
    kSSLSessionOptionAllowServerIdentityChange CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 5,
    /*
     * Enable fallback countermeasures. Use this option when retyring a SSL connection
     * with a lower protocol version because of failure to connect.
     */
    kSSLSessionOptionFallback CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 6,
    /*
     * Set this option to break from a client hello in order to check for SNI
     */
    kSSLSessionOptionBreakOnClientHello CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 7,
    /*
     * Set this option to Allow renegotations. False by default.
     */
    kSSLSessionOptionAllowRenegotiation CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 8,
    /*
     * Set this option to enable session tickets. False by default.
     */
    kSSLSessionOptionEnableSessionTickets CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0) = 9,
};

/* State of an SSLSession */
typedef CF_CLOSED_ENUM(int, SSLSessionState) {
	kSSLIdle CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),        /* no I/O performed yet */
	kSSLHandshake CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),	/* SSL handshake in progress */
	kSSLConnected CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),	/* Handshake complete, ready for normal I/O */
	kSSLClosed CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),		/* connection closed normally */
	kSSLAborted	CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0)		/* connection aborted */
};

/*
 * Status of client certificate exchange (which is optional
 * for both server and client).
 */
typedef CF_ENUM(int, SSLClientCertificateState) {
	/* Server hasn't asked for a cert. Client hasn't sent one. */
	kSSLClientCertNone CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),
	/* Server has asked for a cert, but client didn't send it. */
	kSSLClientCertRequested CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),
	/*
	 * Server side: We asked for a cert, client sent one, we validated
	 *				it OK. App can inspect the cert via
	 *				SSLCopyPeerCertificates().
	 * Client side: server asked for one, we sent it.
	 */
	kSSLClientCertSent CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),
	/*
	 * Client sent a cert but failed validation. Server side only.
	 * Server app can inspect the cert via SSLCopyPeerCertificates().
	 */
	kSSLClientCertRejected CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0)
};

/*
 * R/W functions. The application using this library provides
 * these functions via SSLSetIOFuncs().
 *
 * Data's memory is allocated by caller; on entry to these two functions
 * the *length argument indicates both the size of the available data and the
 * requested byte count. Number of bytes actually transferred is returned in
 * *length.
 *
 * The application may configure the underlying connection to operate
 * in a non-blocking manner; in such a case, a read operation may
 * well return errSSLWouldBlock, indicating "I transferred less data than
 * you requested (maybe even zero bytes), nothing is wrong, except
 * requested I/O hasn't completed". This will be returned back up to
 * the application as a return from SSLRead(), SSLWrite(), SSLHandshake(),
 * etc.
 */
typedef OSStatus
(*SSLReadFunc) 				(SSLConnectionRef 	connection,
							 void 				*data, 			/* owned by
							 									 * caller, data
							 									 * RETURNED */
							 size_t 			*dataLength);	/* IN/OUT */
typedef OSStatus
(*SSLWriteFunc) 			(SSLConnectionRef 	connection,
							 const void 		*data,
							 size_t 			*dataLength);	/* IN/OUT */

/* DEPRECATED aliases for errSSLPeerAuthCompleted */
#define errSSLServerAuthCompleted	errSSLPeerAuthCompleted
#define errSSLClientAuthCompleted	errSSLPeerAuthCompleted

/* DEPRECATED alias for the end of the error range */
#define errSSLLast errSSLUnexpectedRecord

typedef CF_CLOSED_ENUM(int, SSLProtocolSide)
{
    kSSLServerSide CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),
    kSSLClientSide CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0)
};

typedef CF_ENUM(int, SSLConnectionType)
{
    kSSLStreamType CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0),
    kSSLDatagramType CF_ENUM_DEPRECATED(10_2, 10_15, 2_0, 13_0)
};

/*
 * Predefined TLS configuration constants
 */

/* Default configuration (has 3DES, no RC4) */
extern const CFStringRef kSSLSessionConfig_default
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.13), ios(5.0, 11.0));

/* ATS v1 Config: TLS v1.2, only PFS ciphersuites */
extern const CFStringRef kSSLSessionConfig_ATSv1
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* ATS v1 Config without PFS: TLS v1.2, include non PFS ciphersuites */
extern const CFStringRef kSSLSessionConfig_ATSv1_noPFS
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.2 to TLS v1.0, with default ciphersuites (no 3DES, no RC4) */
extern const CFStringRef kSSLSessionConfig_standard
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.2 to TLS v1.0, with default ciphersuites + RC4 + 3DES */
extern const CFStringRef kSSLSessionConfig_RC4_fallback
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.13), ios(5.0, 11.0));

/* TLS v1.0 only, with default ciphersuites + fallback SCSV */
extern const CFStringRef kSSLSessionConfig_TLSv1_fallback
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.0, with default ciphersuites + RC4 + 3DES + fallback SCSV */
extern const CFStringRef kSSLSessionConfig_TLSv1_RC4_fallback
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.13), ios(5.0, 11.0));

/* TLS v1.2 to TLS v1.0, defaults + RC4 + DHE ciphersuites */
extern const CFStringRef kSSLSessionConfig_legacy
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.2 to TLS v1.0, default + RC4 + DHE ciphersuites */
extern const CFStringRef kSSLSessionConfig_legacy_DHE
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.2, anonymous ciphersuites only */
extern const CFStringRef kSSLSessionConfig_anonymous
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/* TLS v1.2 to TLS v1.0, has 3DES, no RC4 */
extern const CFStringRef kSSLSessionConfig_3DES_fallback
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.13), ios(5.0, 11.0));

/* TLS v1.0, with default ciphersuites + 3DES, no RC4 */
extern const CFStringRef kSSLSessionConfig_TLSv1_3DES_fallback
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.13), ios(5.0, 11.0));


/******************
 *** Public API ***
 ******************/

/*
 * Secure Transport APIs require a SSLContextRef, which is an opaque
 * reference to the SSL session and its parameters. On Mac OS X 10.7
 * and earlier versions, a new context is created using SSLNewContext,
 * and is disposed by calling SSLDisposeContext.
 *
 * On i0S 5.0 and later, as well as Mac OS X versions after 10.7, the
 * SSLContextRef is a true CFType object with retain-release semantics.
 * New code should create a new context using SSLCreateContext (instead
 * of SSLNewContext), and dispose the context by calling CFRelease
 * (instead of SSLDisposeContext) when finished with it.
 */

/*
 * @function SSLContextGetTypeID
 * @abstract Return the CFTypeID for SSLContext objects.
 * @return CFTypeId for SSLContext objects.
 */
CFTypeID
SSLContextGetTypeID(void)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLCreateContext
 * @abstract Create a new instance of an SSLContextRef using the specified allocator.
 * @param alloc Allocator to use for memory.
 * @param protooclSide Client or server indication.
 * @param connectionType Type of connection.
 * @return A newly allocated SSLContextRef, or NULL on error.
 */
__nullable
SSLContextRef
SSLCreateContext(CFAllocatorRef __nullable alloc, SSLProtocolSide protocolSide, SSLConnectionType connectionType)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));


#if TARGET_OS_OSX
/*
 * @function SSLNewContext
 * @abstract Create a new session context.
 * @note
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. Your code should use SSLCreateContext instead.
 *
 * @param isServer Flag indicating if the context is for the server (true) or client (false).
 * @param contextPtr Pointer to SSLContextRef where result will be stored.
 * @return errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLNewContext				(Boolean 			isServer,
							 SSLContextRef 		* __nonnull CF_RETURNS_RETAINED contextPtr)	/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLDisposeContext
 * @abstract Dispose of a session context.
 * @note
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. Your code should use CFRelease to dispose a session
 * created with SSLCreateContext.
 *
 * @param context A SSLContextRef to deallocate and destroy.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLDisposeContext			(SSLContextRef		context)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

#endif /* MAC OS X */

/*
 * @function SSLGetSessionState
 * @abstract Determine the state of an SSL/DTLS session.
 * @param context A valid SSLContextRef.
 * @param state Output pointer to store the SSLSessionState.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetSessionState			(SSLContextRef		context,
							 SSLSessionState	*state)		/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetSessionOption
 * @abstract Set options for an SSL session. Must be called prior to SSLHandshake();
 *   subsequently cannot be called while session is active.
 * @param context A valid SSLContextRef.
 * @param option An option enumeration value.
 * @param value Value of the SSLSessionOption.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetSessionOption			(SSLContextRef		context,
							 SSLSessionOption	option,
							 Boolean			value)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.6, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetSessionOption
 * @abstract Determine current value for the specified option in a given SSL session.
 * @param context A valid SSLContextRef.
 * @param option An option enumeration value.
 * @param value Pointer to a Boolean where the SSLSessionOption value is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetSessionOption			(SSLContextRef		context,
							 SSLSessionOption	option,
							 Boolean			*value)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.6, 10.15), ios(5.0, 13.0));

/********************************************************************
 *** Session context configuration, common to client and servers. ***
 ********************************************************************/

/*
 * @function SSLSetIOFuncs
 * @abstract Specify functions which do the network I/O. Must be called prior
 *    to SSLHandshake(); subsequently cannot be called while a session is
 *    active.
 * @param context A valid SSLContextRef.
 * @param readFunc Pointer to a SSLReadFunc.
 * @param writeFunc Pointer to a SSLWriteFunc.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetIOFuncs				(SSLContextRef		context,
							 SSLReadFunc 		readFunc,
							 SSLWriteFunc		writeFunc)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));


/*
 * @function SSLSetSessionConfig
 * @absttact Set a predefined configuration for the SSL Session
 * @note This currently affect enabled protocol versions,
 *   enabled ciphersuites, and the kSSLSessionOptionFallback
 *   session option.
 * @param context A valid SSLContextRef.
 * @param config String name of constant TLS handshake configuration, e.g., kSSLSessionConfig_standard.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetSessionConfig(SSLContextRef context,
                    CFStringRef config)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.12, 10.15), ios(10.0, 13.0));

/*
 * @function SSLSetProtocolVersionMin
 * @abstract Set the minimum SSL protocol version allowed. Optional.
 *   The default is the lower supported protocol.
 * @note This can only be called when no session is active.
 *
 *   For TLS contexts, legal values for minVersion are :
 *	  	kSSLProtocol3
 * 		kTLSProtocol1
 * 		kTLSProtocol11
 * 		kTLSProtocol12
 *
 *   For DTLS contexts, legal values for minVersion are :
 *      kDTLSProtocol1
 * @param context A valid SSLContextRef.
 * @param minVersion Minimum TLS protocol version.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetProtocolVersionMin  (SSLContextRef      context,
                           SSLProtocol        minVersion)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetProtocolVersionMin
 * @abstract Get minimum protocol version allowed
 * @param context A valid SSLContextRef.
 * @param minVersion Pointer to SSLProtocol value where the minimum protocol version is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetProtocolVersionMin  (SSLContextRef      context,
                           SSLProtocol        *minVersion)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetProtocolVersionMax
 * @abstract Set the maximum SSL protocol version allowed. Optional.
 *   The default is the highest supported protocol.
 * @note
 *   This can only be called when no session is active.
 *
 *   For TLS contexts, legal values for maxVersion are :
 *		kSSLProtocol3
 * 		kTLSProtocol1
 * 		kTLSProtocol11
 * 		kTLSProtocol12
 *
 *   For DTLS contexts, legal values for maxVersion are :
 *      kDTLSProtocol1
 * @param context A valid SSLContextRef.
 * @param maxVersion Maximum TLS protocol version.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetProtocolVersionMax  (SSLContextRef      context,
                           SSLProtocol        maxVersion)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetProtocolVersionMax
 * @abstract Get maximum protocol version allowed
 * @param context A valid SSLContextRef.
 * @param maxVersion Pointer to SSLProtocol value where the maximum protocol version is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetProtocolVersionMax  (SSLContextRef      context,
                           SSLProtocol        *maxVersion)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));


#if TARGET_OS_OSX
/*
 * @function SSLSetProtocolVersionEnabled
 * @abstract Set allowed SSL protocol versions. Optional.
 * @discussion Specifying kSSLProtocolAll for SSLSetProtocolVersionEnabled results in
 *   specified 'enable' boolean to be applied to all supported protocols.
 *   The default is "all supported protocols are enabled".
 *   This can only be called when no session is active.
 *
 *   Legal values for protocol are :
 *		kSSLProtocol2
 *		kSSLProtocol3
 * 		kTLSProtocol1
 *		kSSLProtocolAll
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. You can use SSLSetProtocolVersionMin and/or
 * SSLSetProtocolVersionMax to specify which protocols are enabled.
 * @param context A valid SSLContextRef.
 * @param protocol A SSLProtocol enumerated value.
 * @param enable Boolean to enable or disable the designated protocol.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetProtocolVersionEnabled (SSLContextRef 	context,
							 SSLProtocol		protocol,
							 Boolean			enable)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * Obtain a value specified in SSLSetProtocolVersionEnabled.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. You can use SSLGetProtocolVersionMin and/or
 * SSLGetProtocolVersionMax to check whether a protocol is enabled.
 */
OSStatus
SSLGetProtocolVersionEnabled(SSLContextRef 		context,
							 SSLProtocol		protocol,
							 Boolean			*enable)	/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLSetProtocolVersion
 * @abstract Get/set SSL protocol version; optional. Default is kSSLProtocolUnknown,
 *   in which case the highest possible version is attempted, but a lower
 *   version is accepted if the peer requires it.
 * @discussion SSLSetProtocolVersion cannot be called when a session is active.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note this function is not available on iOS, and deprecated on Mac OS X 10.8.
 *   Use SSLSetProtocolVersionMin and/or SSLSetProtocolVersionMax to specify
 *   which protocols are enabled.
 * @param context A valid SSLContextRef.
 * @param protocol A SSLProtocol enumerated value.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetProtocolVersion		(SSLContextRef 		context,
							 SSLProtocol		version)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.8));

/*
 * @function SSLGetProtocolVersion
 * @abstract Obtain the protocol version specified in SSLSetProtocolVersion.
 * @discussion If SSLSetProtocolVersionEnabled() has been called for this session,
 *   SSLGetProtocolVersion() may return errSecParam if the protocol enable
 *   state can not be represented by the SSLProtocol enums (e.g.,
 *   SSL2 and TLS1 enabled, SSL3 disabled).
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note this function is not available on iOS, and deprecated on Mac OS X 10.8.
 *   Use SSLGetProtocolVersionMin and/or SSLGetProtocolVersionMax to check
 *   whether a protocol is enabled.
 * @param context A valid SSLContextRef.
 * @param protocol A SSLProtocol enumerated value pointer to store the protocol version.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetProtocolVersion		(SSLContextRef		context,
							 SSLProtocol		*protocol)	/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.8));

#endif /* MAC OS X */

/*
 * @function SSLSetCertificate
 * @abstract Specify this connection's certificate(s).
 * @discussion This is mandatory for server connections,and optional for
 *   clients. Specifying a certificate for a client enables SSL client-side
 *   authentication. The end-entity cert is in certRefs[0]. Specifying a root
 *   cert is optional; if it's not specified, the root cert which verifies the
 *   cert chain specified here must be present in the system-wide set of trusted
 *   anchor certs.
 *
 *   The certRefs argument is a CFArray containing SecCertificateRefs,
 *   except for certRefs[0], which is a SecIdentityRef.
 *
 *   Must be called prior to SSLHandshake(), or immediately after
 *   SSLHandshake has returned errSSLClientCertRequested (i.e. before the
 *   handshake is resumed by calling SSLHandshake again.)
 *
 *   SecureTransport assumes the following:
 *
 *    -- The certRef references remain valid for the lifetime of the session.
 *    -- The certificate specified in certRefs[0] is capable of signing.
 *    -- The required capabilities of the certRef[0], and of the optional cert
 *       specified in SSLSetEncryptionCertificate (see below), are highly
 *       dependent on the application. For example, to work as a server with
 *       Netscape clients, the cert specified here must be capable of both
 *       signing and encrypting.
 * @param context A valid SSLContextRef.
 * @param certRefs An array of SecCertificateRef instances.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetCertificate			(SSLContextRef		context,
							 CFArrayRef			_Nullable certRefs)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetConnection
 * @abstract Specify I/O connection - a socket, endpoint, etc., which is
 * managed by caller.
 * @discussion On the client side, it's assumed that communication
 *   has been established with the desired server on this connection.
 *   On the server side, it's assumed that an incoming client request
 *   has been established.
 *
 *   Must be called prior to SSLHandshake(); subsequently can only be
 *   called when no session is active.
 * @param context A valid SSLContextRef.
 * @param connection A SSLConnectionRef.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetConnection			(SSLContextRef                  context,
							 SSLConnectionRef __nullable	connection)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetConnection
 * @abstract Retrieve the I/O connection managed managed by the caller.
 * @param context A valid SSLContextRef.
 * @param connection A SSLConnectionRef pointer.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetConnection			(SSLContextRef		context,
							 SSLConnectionRef	* __nonnull CF_RETURNS_NOT_RETAINED connection)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetPeerDomainName
 * @abstract Specify the fully qualified doman name of the peer, e.g., "store.apple.com."
 * @discussion Optional; used to verify the common name field in peer's certificate.
 *   Name is in the form of a C string; NULL termination optional, i.e.,
 *   peerName[peerNameLen+1] may or may not have a NULL. In any case peerNameLen
 *   is the number of bytes of the peer domain name.
 * @param context A valid SSLContextRef.
 * @param peerName A C string carrying the peer domain name.
 * @param peerNameLen Length of the peer domain name string.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetPeerDomainName		(SSLContextRef		context,
							 const char			* __nullable peerName,
							 size_t				peerNameLen)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetPeerDomainNameLength
 * @abstract Determine the buffer size needed for SSLGetPeerDomainName().
 * @param context A valid SSLContextRef.
 * @param peerNameLen Pointer to where the length of the peer domain name string is stored
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetPeerDomainNameLength	(SSLContextRef		context,
							 size_t				*peerNameLen)	// RETURNED
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetPeerDomainName
 * @abstract Obtain the value specified in SSLSetPeerDomainName().
 * @param context A valid SSLContextRef.
 * @param peerName Pointer to where the peer domain name is stored.
 * @param peerNameLen Pointer to where the length of the peer domain name string is stored,
 *        up to the length specified by peerNameLen (on input).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetPeerDomainName		(SSLContextRef		context,
							 char				*peerName,		// returned here
							 size_t				*peerNameLen)	// IN/OUT
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLCopyRequestedPeerNameLength
 * @abstract [Server Only] obtain the hostname specified by the client in the ServerName extension (SNI)
 * @param context A valid SSLContextRef.
 * @param peerNameLen Pointer to where the length of the requested peer domain name string
 *        is stored, up to the length specified by peerNameLen (on input).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyRequestedPeerNameLength  (SSLContextRef  ctx,
                                 size_t         *peerNameLen)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.11, 10.15), ios(9.0, 13.0));

/*
 * @function SSLCopyRequestedPeerName
 * @abstract Determine the buffer size needed for SSLCopyRequestedPeerNameLength().
 * @param context A valid SSLContextRef.
 * @param peerName Pointer to where the requested peer domain name is stored.
 * @param peerNameLen Pointer to where the length of the requested peer domain name string
 *        is stored, up to the length specified by peerNameLen (on input).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyRequestedPeerName    (SSLContextRef      context,
                             char               *peerName,
                             size_t             *peerNameLen)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.11, 10.15), ios(9.0, 13.0));


/*
 * @function SSLSetDatagramHelloCookie
 * @abstract Specify the Datagram TLS Hello Cookie.
 * @discussion This is to be called for server side only and is optional.
 *  The default is a zero len cookie. The maximum cookieLen is 32 bytes.
 * @param context A valid SSLContextRef.
 * @param cookie Pointer to opaque cookie data.
 * @param cookieLen Length of cookie data.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetDatagramHelloCookie	(SSLContextRef		dtlsContext,
                             const void         * __nullable cookie,
                             size_t             cookieLen)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetMaxDatagramRecordSize
 * @abstract Specify the maximum record size, including all DTLS record headers.
 * @discussion This should be set appropriately to avoid fragmentation
 *   of Datagrams during handshake, as fragmented datagrams may
 *   be dropped by some network.
 * @note This is for Datagram TLS only
 * @param context A valid SSLContextRef.
 * @param maxSize Maximum size of datagram record(s).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetMaxDatagramRecordSize (SSLContextRef		dtlsContext,
                             size_t             maxSize)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetMaxDatagramRecordSize
 * @abstract Get the maximum record size, including all Datagram TLS record headers.
 * @note This is for Datagram TLS only
 * @param context A valid SSLContextRef.
 * @param maxSize Pointer where maximum size of datagram record(s) is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetMaxDatagramRecordSize (SSLContextRef		dtlsContext,
                             size_t             *maxSize)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetNegotiatedProtocolVersion
 * @abstract Obtain the actual negotiated protocol version of the active
 *   session, which may be different that the value specified in
 *   SSLSetProtocolVersion(). Returns kSSLProtocolUnknown if no
 *   SSL session is in progress.
 * @param context A valid SSLContextRef.
 * @param protocol Pointer where negotiated SSLProtocol is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetNegotiatedProtocolVersion		(SSLContextRef		context,
									 SSLProtocol		*protocol)	/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetNumberSupportedCiphers
 * @abstract Determine number and values of all of the SSLCipherSuites we support.
 *    Caller allocates output buffer for SSLGetSupportedCiphers() and passes in
 *    its size in *numCiphers. If supplied buffer is too small, errSSLBufferOverflow
 *    will be returned.
 * @param context A valid SSLContextRef.
 * @param numCiphers Pointer where number of supported ciphers is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetNumberSupportedCiphers (SSLContextRef			context,
							  size_t				*numCiphers)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetSupportedCiphers
 * @abstract Get the supported ciphers.
 * @param context A valid SSLContextRef.
 * @param ciphers Pointer to array of SSLCipherSuite values where supported ciphersuites
 *                are stored. This array size is specified by the input value of numCiphers.
 * @param numCiphers Pointer where number of supported ciphers is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetSupportedCiphers		 (SSLContextRef			context,
							  SSLCipherSuite		*ciphers,		/* RETURNED */
							  size_t				*numCiphers)	/* IN/OUT */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetNumberEnabledCiphers
 * @abstract Determine number and values of all of the SSLCipherSuites currently enabled.
 *    Caller allocates output buffer for SSLGetEnabledCiphers() and passes in
 *    its size in *numCiphers. If supplied buffer is too small, errSSLBufferOverflow
 *    will be returned.
 * @param context A valid SSLContextRef.
 * @param numCiphers Pointer where number of enabled ciphers is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetNumberEnabledCiphers     (SSLContextRef       context,
                                size_t              *numCiphers)
__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetEnabledCiphers
 * @abstract Specify a (typically) restricted set of SSLCipherSuites to be enabled by
 *    the current SSLContext. Can only be called when no session is active. Default
 *    set of enabled SSLCipherSuites is the same as the complete set of supported
 *    SSLCipherSuites as obtained by SSLGetSupportedCiphers().
 * @param context A valid SSLContextRef.
 * @param ciphers Array of enabled SSLCipherSuite values. This array size is specified
 *                by the input value of numCiphers.
 * @param numCiphers Pointer where number of enabled ciphers is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetEnabledCiphers		(SSLContextRef			context,
							 const SSLCipherSuite	*ciphers,
							 size_t					numCiphers)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetEnabledCiphers
 * @abstract Get the set of supported ciphersuites.
 * @param context A valid SSLContextRef.
 * @param ciphers Pointer to array of SSLCipherSuite values where enabled ciphersuites
 *                are stored. This array size is specified by the input value of numCiphers.
 * @param numCiphers Pointer where number of enabled ciphers is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetEnabledCiphers		(SSLContextRef			context,
							 SSLCipherSuite			*ciphers,		/* RETURNED */
							 size_t					*numCiphers)	/* IN/OUT */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetSessionTicketsEnabled
 * @abstract Forcibly enable or disable session ticket resumption.
 * @note By default, session tickets are disabled.
 * @param context A valid SSLContextRef.
 * @param enabled Boolean indicating if ticket support is enabled (true) or not (false).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetSessionTicketsEnabled     (SSLContextRef          context,
                                 Boolean                enabled)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.13, 10.15), ios(11.0, 13.0));


#if TARGET_OS_OSX
/*
 * @function SSLSetEnableCertVerify
 * @abstract Enable/disable peer certificate chain validation. Default is enabled.
 * @discussion If caller disables, it is the caller's responsibility to call
 *    SSLCopyPeerCertificates() upon successful completion of the handshake
 *    and then to perform external validation of the peer certificate
 *    chain before proceeding with data transfer.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To disable peer certificate chain validation, you
 *    can instead use SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth
 *    to true. This will disable verification and cause SSLHandshake to return with
 *    an errSSLServerAuthCompleted result when the peer certificates have been
 *    received; at that time, you can choose to evaluate peer trust yourself, or
 *    simply call SSLHandshake again to proceed with the handshake.
 * @param context A valid SSLContextRef.
 * @param enableVerify Boolean indicating if certificate verifiation is enabled (true) or disabled (false).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetEnableCertVerify		(SSLContextRef 			context,
							 Boolean				enableVerify)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLGetEnableCertVerify
 * @abstract Check whether peer certificate chain validation is enabled.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To check whether peer certificate chain validation
 *    is enabled in a context, call SSLGetSessionOption to obtain the value of
 *    the kSSLSessionOptionBreakOnServerAuth session option flag. If the value
 *    of this option flag is true, then verification is disabled.
 * @param context A valid SSLContextRef.
 * @param enableVerify Pointer to Boolean where enable bit is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetEnableCertVerify		(SSLContextRef 			context,
							 Boolean				*enableVerify)	/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLSetAllowsExpiredCerts
 * @abstract Specify the option of ignoring certificates' "expired" times.
 * @discussion This is a common failure in the real SSL world. Default setting for this
 *    flag is false, meaning expired certs result in an errSSLCertExpired error.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To ignore expired certificate errors, first disable
 *    Secure Transport's automatic verification of peer certificates by calling
 *    SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 *    SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 *    your code should obtain the SecTrustRef for the peer's certificates and
 *    perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *    The SecTrustSetOptions function allows you to specify that the expiration
 *    status of certificates should be ignored for this evaluation.
 *
 * Example:
 *
 *	status = SSLSetSessionOption(ctx, kSSLSessionOptionBreakOnServerAuth, true);
 *	do {
 *		status = SSLHandshake(ctx);
 *
 *		if (status == errSSLServerAuthCompleted) {
 *			SecTrustRef peerTrust = NULL;
 *			status = SSLCopyPeerTrust(ctx, &peerTrust);
 *			if (status == errSecSuccess) {
 *				SecTrustResultType trustResult;
 *				// set flag to allow expired certificates
 *				SecTrustSetOptions(peerTrust, kSecTrustOptionAllowExpired);
 *				status = SecTrustEvaluate(peerTrust, &trustResult);
 *				if (status == errSecSuccess) {
 *					// A "proceed" result means the cert is explicitly trusted,
 *					// e.g. "Always Trust" was clicked;
 *					// "Unspecified" means the cert has no explicit trust settings,
 *					// but is implicitly OK since it chains back to a trusted root.
 *					// Any other result means the cert is not trusted.
 *					//
 *					if (trustResult == kSecTrustResultProceed ||
 *						trustResult == kSecTrustResultUnspecified) {
 *						// certificate is trusted
 *						status = errSSLWouldBlock; // so we call SSLHandshake again
 *					} else if (trustResult == kSecTrustResultRecoverableTrustFailure) {
 *						// not trusted, for some reason other than being expired;
 *						// could ask the user whether to allow the connection here
 *						//
 *						status = errSSLXCertChainInvalid;
 *					} else {
 *						// cannot use this certificate (fatal)
 *						status = errSSLBadCert;
 *					}
 *				}
 *				if (peerTrust) {
 *					CFRelease(peerTrust);
 *				}
 *			}
 *		} // errSSLServerAuthCompleted
 *
 *	} while (status == errSSLWouldBlock);
 * @param context A valid SSLContextRef.
 * @param allowsExpired Boolean indicating if expired certificates are allowed (true) or not (false).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetAllowsExpiredCerts	(SSLContextRef		context,
							 Boolean			allowsExpired)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLGetAllowsExpiredCerts
 * @abstract Obtain the current value of an SSLContext's "allowExpiredCerts" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X.
 * @param context A valid SSLContextRef.
 * @param allowsExpired Pointer to Boolean where the expired certificate allowance Boolean is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetAllowsExpiredCerts	(SSLContextRef		context,
							 Boolean			*allowsExpired)	/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLSetAllowsExpiredRoots
 * @abstract Similar to SSLSetAllowsExpiredCerts, SSLSetAllowsExpiredRoots allows the
 *    option of ignoring "expired" status for root certificates only.
 * @discussion Default setting is false, i.e., expired root certs result in an
 *    errSSLCertExpired error.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To ignore expired certificate errors, first disable
 *    Secure Transport's automatic verification of peer certificates by calling
 *    SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 *    SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 *    your code should obtain the SecTrustRef for the peer's certificates and
 *    perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *    The SecTrustSetOptions function allows you to specify that the expiration
 *    status of certificates should be ignored for this evaluation.
 *
 *    See the description of the SSLSetAllowsExpiredCerts function (above)
 *    for a code example. The kSecTrustOptionAllowExpiredRoot option can be used
 *    instead of kSecTrustOptionAllowExpired to allow expired roots only.
 * @param context A valid SSLContextRef.
 * @param allowsExpired Boolean indicating if expired roots are allowed.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetAllowsExpiredRoots	(SSLContextRef		context,
							 Boolean			allowsExpired)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLGetAllowsExpiredRoots
 * @abstract Obtain the current value of an SSLContext's "allow expired roots" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X.
 * @param context A valid SSLContextRef.
 * @param allowsExpired Pointer to Boolean where the expired root certificate allowance
 *                      Boolean is stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetAllowsExpiredRoots	(SSLContextRef		context,
							 Boolean			*allowsExpired)	/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLSetAllowsAnyRoot
 * @abstract Specify option of allowing for an unknown root cert, i.e., one which
 * this software can not verify as one of a list of known good root certs.
 * @discussion Default for this flag is false, in which case one of the following two
 *    errors may occur:
 *       -- The peer returns a cert chain with a root cert, and the chain
 *          verifies to that root, but the root is not one of our trusted
 *          roots. This results in errSSLUnknownRootCert on handshake.
 *       -- The peer returns a cert chain which does not contain a root cert,
 *          and we can't verify the chain to one of our trusted roots. This
 *          results in errSSLNoRootCert on handshake.
 *
 *    Both of these error conditions are ignored when the AllowAnyRoot flag is
 *    true, allowing connection to a totally untrusted peer.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To ignore unknown root cert errors, first disable
 *    Secure Transport's automatic verification of peer certificates by calling
 *    SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 *    SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 *    your code should obtain the SecTrustRef for the peer's certificates and
 *    perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *
 *    See the description of the SSLSetAllowsExpiredCerts function (above)
 *    for a code example. Note that an unknown root certificate will cause
 *    SecTrustEvaluate to report kSecTrustResultRecoverableTrustFailure as the
 *    trust result.
 * @param context A valid SSLContextRef.
 * @param anyRoot Boolean indicating if any root is allowed (true) or not (false).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetAllowsAnyRoot			(SSLContextRef		context,
							 Boolean			anyRoot)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLGetAllowsAnyRoot
 * @abstract Obtain the current value of an SSLContext's "allow any root" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X.
 * @param context A valid SSLContextRef.
 * @param anyRoot Pointer to Boolean to store any root allowance Boolean.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetAllowsAnyRoot			(SSLContextRef		context,
							 Boolean			*anyRoot) /* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLSetTrustedRoots
 * @abstract Augment or replace the system's default trusted root certificate set
 * for this session.
 * @discussion If replaceExisting is true, the specified roots will
 *    be the only roots which are trusted during this session. If replaceExisting
 *    is false, the specified roots will be added to the current set of trusted
 *    root certs. If this function has never been called, the current trusted
 *    root set is the same as the system's default trusted root set.
 *    Successive calls with replaceExisting false result in accumulation
 *    of additional root certs.
 *
 *    The trustedRoots array contains SecCertificateRefs.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To trust specific roots in a session, first disable
 *    Secure Transport's automatic verification of peer certificates by calling
 *    SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 *    SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 *    your code should obtain the SecTrustRef for the peer's certificates and
 *    perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *
 *    See the description of the SSLSetAllowsExpiredCerts function (above)
 *    for a code example. You can call SecTrustSetAnchorCertificates to
 *    augment the system's trusted root set, or SecTrustSetAnchorCertificatesOnly
 *    to make these the only trusted roots, prior to calling SecTrustEvaluate.
 * @param context A valid SSLContextRef.
 * @param trustedRoots Array of SecCertificateRef roots.
 * @param replaceExisting Boolean indicating if provided roots should override all others for this connection.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetTrustedRoots			(SSLContextRef 		context,
							 CFArrayRef 		trustedRoots,
							 Boolean 			replaceExisting)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLCopyTrustedRoots
 * @abstract Obtain an array of SecCertificateRefs representing the current
 *    set of trusted roots.
 * @discussion If SSLSetTrustedRoots() has never been called
 *    for this session, this returns the system's default root set.
 *    Caller must CFRelease the returned CFArray.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To get the current set of trusted roots, call the
 *    SSLCopyPeerTrust function to obtain the SecTrustRef for the peer certificate
 *    chain, then SecTrustCopyCustomAnchorCertificates (see SecTrust.h).
 * @param context A valid SSLContextRef.
 * @param trustedRoots Array of SecCertificateRef roots.
 * @param replaceExisting Boolean indicating if provided roots should override all others for this connection.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyTrustedRoots			(SSLContextRef 		context,
							 CFArrayRef 		* __nonnull CF_RETURNS_RETAINED trustedRoots)	/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.5, 10.9));

/*
 * @function SSLCopyPeerCertificates
 * @abstract Request peer certificates. Valid anytime, subsequent to a handshake attempt.
 * @discussion The certs argument is a CFArray containing SecCertificateRefs.
 *    Caller must CFRelease the returned array.
 *
 *    The cert at index 0 of the returned array is the subject (end
 *    entity) cert; the root cert (or the closest cert to it) is at
 *    the end of the returned array.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. To get peer certificates, call SSLCopyPeerTrust
 *    to obtain the SecTrustRef for the peer certificate chain, then use the
 *    SecTrustGetCertificateCount and SecTrustGetCertificateAtIndex functions
 *    to retrieve individual certificates in the chain (see SecTrust.h).
 * @param context A valid SSLContextRef.
 * @param certs Pointer to CFArrayRef that will store a reference to the peer's certificates.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyPeerCertificates		(SSLContextRef 		context,
							 CFArrayRef			* __nonnull CF_RETURNS_RETAINED certs)		/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.5, 10.9));

#endif /* MAC OS X */

/*
 * @function SSLCopyPeerTrust
 * @abstract Obtain a SecTrustRef representing peer certificates. Valid anytime,
 *    subsequent to a handshake attempt. Caller must CFRelease the returned
 *    trust reference.
 * @discussion The returned trust reference will have already been evaluated for
 *    you, unless one of the following is true:
 *    - Your code has disabled automatic certificate verification, by calling
 *      SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true.
 *    - Your code has called SSLSetPeerID, and this session has been resumed
 *      from an earlier cached session.
 *
 *    In these cases, your code should call SecTrustEvaluate prior to
 *    examining the peer certificate chain or trust results (see SecTrust.h).
 *
 * @note If you have not called SSLHandshake at least once prior to
 *    calling this function, the returned trust reference will be NULL.
 * @param context A valid SSLContextRef.
 * @param trust Pointer to SecTrustRef where peer's SecTrustRef is copied (retained).
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyPeerTrust			(SSLContextRef 		context,
							 SecTrustRef		* __nonnull CF_RETURNS_RETAINED trust)		/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.6, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetPeerID
 * @discussion Specify some data, opaque to this library, which is sufficient
 *    to uniquely identify the peer of the current session. An example
 *    would be IP address and port, stored in some caller-private manner.
 *    To be optionally called prior to SSLHandshake for the current
 *    session. This is mandatory if this session is to be resumable.
 *
 *    SecureTransport allocates its own copy of the incoming peerID. The
 *    data provided in *peerID, while opaque to SecureTransport, is used
 *    in a byte-for-byte compare to other previous peerID values set by the
 *    current application. Matching peerID blobs result in SecureTransport
 *    attempting to resume an SSL session with the same parameters as used
 *    in the previous session which specified the same peerID bytes.
 * @param context A valid SSLContextRef.
 * @param peerID Opaque peer ID.
 * @param peerIDLen Length of opaque peer ID.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetPeerID				(SSLContextRef 		context,
							 const void 		* __nullable peerID,
							 size_t				peerIDLen)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetPeerID
 * @abstract Obtain current PeerID. Returns NULL pointer, zero length if
 *    SSLSetPeerID has not been called for this context.
 * @param context A valid SSLContextRef.
 * @param peerID Pointer to storage for the peer ID.
 * @param peerIDLen Pointer to storage for the peer ID length.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetPeerID				(SSLContextRef 		context,
							 const void 		* __nullable * __nonnull peerID,
							 size_t				*peerIDLen)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetNegotiatedCipher
 * @abstract Obtain the SSLCipherSuite (e.g., SSL_RSA_WITH_DES_CBC_SHA) negotiated
 *    for this session. Only valid when a session is active.
 * @param context A valid SSLContextRef.
 * @param cipherSuite Pointer to storage for negotiated SSLCipherSuite.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetNegotiatedCipher		(SSLContextRef 		context,
							 SSLCipherSuite 	*cipherSuite)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetALPNProtocols
 * @abstract Set the ALPN protocols to be passed in the ALPN negotiation.
 * @discussion This is the list of supported application-layer protocols supported.
 *
 *    The protocols parameter must be an array of CFStringRef values
 *    with ASCII-encoded reprensetations of the supported protocols, e.g., "http/1.1".
 *
 * @note See RFC 7301 for more information.
 * @param context A valid SSLContextRef.
 * @param protocols Array of CFStringRefs carrying application protocols.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetALPNProtocols         (SSLContextRef      context,
                             CFArrayRef         protocols)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.13, 10.15), ios(11.0, 13.0));

/*
 * @function SSLCopyALPNProtocols
 * @abstract Get the ALPN protocols associated with this SSL context.
 * @discussion This is the list of supported application-layer protocols supported.
 *
 *    The resultant protocols array will contain CFStringRef values containing
 *    ASCII-encoded representations of the supported protocols, e.g., "http/1.1".
 *
 *    See RFC 7301 for more information.
 *
 * @note The `protocols` pointer must be NULL, otherwise the copy will fail.
 *    This function will allocate memory for the CFArrayRef container
 *    if there is data to provide. Otherwise, the pointer will remain NULL.
 * @param context A valid SSLContextRef.
 * @param protocols Pointer to a CFArrayRef where peer ALPN protocols are stored.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyALPNProtocols        (SSLContextRef      context,
                             CFArrayRef         __nullable * __nonnull protocols)           /* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.13, 10.15), ios(11.0, 13.0));

/*
 * @function SSLSetOCSPResponse
 * @abstract Set the OCSP response for the given SSL session.
 * @discussion The response parameter must be a non-NULL CFDataRef containing the
 *    bytes of the OCSP response.
 * @param context A valid SSLContextRef.
 * @param response CFDataRef carrying OCSP response.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetOCSPResponse          (SSLContextRef      context,
                             CFDataRef          __nonnull response)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.13, 10.15), ios(11.0, 13.0));

/********************************************************
 *** Session context configuration, server side only. ***
 ********************************************************/

/*
 * @function SSLSetEncryptionCertificate
 * @discussion This function is deprecated in OSX 10.11 and iOS 9.0 and
 *    has no effect on the TLS handshake since OSX 10.10 and
 *    iOS 8.0. Using separate RSA certificates for encryption
 *    and signing is no longer supported.
 * @param context A valid SSLContextRef.
 * @param certRefs Array of certificates.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetEncryptionCertificate	(SSLContextRef		context,
							 CFArrayRef			certRefs)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.11), ios(5.0, 9.0));

/*
 * @enum SSLAuthenticate
 * @discussion Optional; Default is kNeverAuthenticate.
 *    Can only be called when no session is active.
 */
typedef CF_ENUM(int, SSLAuthenticate) {
	kNeverAuthenticate,			/* skip client authentication */
	kAlwaysAuthenticate,		/* require it */
	kTryAuthenticate			/* try to authenticate, but not an error if client doesn't have a cert */
};

/*
 * @function SSLSetClientSideAuthenticate
 * @abstract Specify requirements for client-side authentication.
 * @param context A valid SSLContextRef.
 * @param auth A SSLAuthenticate enumeration value.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetClientSideAuthenticate 	(SSLContextRef		context,
								 SSLAuthenticate	auth)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLAddDistinguishedName
 * @abstract Add a DER-encoded distinguished name to list of acceptable names
 *    to be specified in requests for client certificates.
 * @param context A valid SSLContextRef.
 * @param derDN A DER-encoded Distinguished Name blob.
 * @param derDNLen Length of the Distinguished Name blob.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLAddDistinguishedName		(SSLContextRef 		context,
							 const void 		* __nullable derDN,
							 size_t 			derDNLen)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.4, 10.15), ios(5.0, 13.0));


#if TARGET_OS_OSX
/*
 * @function SSLSetCertificateAuthorities
 * @abstract Add a SecCertificateRef, or a CFArray of them, to a server's list
 *    of acceptable Certificate Authorities (CAs) to present to the client
 *    when client authentication is performed.
 * @discussion If replaceExisting is true, the specified certificate(s) will
 *    replace a possible existing list of acceptable CAs. If replaceExisting
 *    is false, the specified certificate(s) will be appended to the existing
 *    list of acceptable CAs, if any.
 *
 *    Returns errSecParam if this is called on a SSLContextRef which
 *    is configured as a client, or when a session is active.
 *
 * @note this function is currently not available on iOS.
 * @param context A valid SSLContextRef.
 * @param certificateOrARray Either a SecCertificateRef (or CFArrayRef of them).
 * @param replaceExisting Boolean indicating if existing CAs should be overruled for this connection.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetCertificateAuthorities(SSLContextRef		context,
							 CFTypeRef			certificateOrArray,
							 Boolean 			replaceExisting)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.5, 10.15));

/*
 * @function SSLCopyCertificateAuthorities
 * @abstract Obtain the certificates specified in SSLSetCertificateAuthorities(),
 *    if any. Returns a NULL array if SSLSetCertificateAuthorities() has not been called.
 * @discussion Caller must CFRelease the returned array.
 *
 * @note This function is currently not available on iOS.
 * @param context A valid SSLContextRef.
 * @param certificates Pointer to CFArrayRef storage for retained copy of CAs for this connection.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyCertificateAuthorities(SSLContextRef		context,
							  CFArrayRef		* __nonnull CF_RETURNS_RETAINED certificates)	/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.5, 10.15));

#endif /* MAC OS X */

/*
 * @function SSLCopyDistinguishedNames
 * @abstract Obtain the list of acceptable distinguished names as provided by
 *    a server (if the SSLContextRef is configured as a client), or as
 *    specified by SSLSetCertificateAuthorities (if the SSLContextRef
 *    is configured as a server).
 * @discussion The returned array contains CFDataRefs, each of which represents
 *    one DER-encoded RDN. Caller must CFRelease the returned array.
 * @param context A valid SSLContextRef.
 * @param names Pointer to CFArrayRef storage for retained copy of Distinguished Names.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLCopyDistinguishedNames	(SSLContextRef		context,
							 CFArrayRef			* __nonnull CF_RETURNS_RETAINED names)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.5, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetClientCertificateState
 * @abstract Obtain client certificate exchange status.
 * @discussion Can be called any time.
 *    Reflects the *last* client certificate state change;
 *    subsequent to a renegotiation attempt by either peer, the state
 *    is reset to kSSLClientCertNone.
 * @param context A valid SSLContextRef.
 * @param clientState Pointer to SSLClientCertificateState storage.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetClientCertificateState	(SSLContextRef				context,
								 SSLClientCertificateState	*clientState)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.3, 10.15), ios(5.0, 13.0));


#if TARGET_OS_OSX
/*
 * @function SSLSetDiffieHellmanParams
 * @abstract Specify Diffie-Hellman parameters.
 * @discussion Optional; if we are configured to allow
 *    for D-H ciphers and a D-H cipher is negotiated, and this function has not
 *    been called, a set of process-wide parameters will be calculated. However
 *    that can take a long time (30 seconds).
 * @note This function is currently not available on iOS.
 * @param context A valid SSLContextRef.
 * @param clientState Pointer to SSLClientCertificateState storage.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetDiffieHellmanParams	(SSLContextRef			context,
                             const void 			* __nullable dhParams,
                             size_t					dhParamsLen)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15));

/*
 * @function SSLGetDiffieHellmanParams
 * @abstract Return parameter block specified in SSLSetDiffieHellmanParams.
 * @discussion Returned data is not copied and belongs to the SSLContextRef.
 * @note This function is currently not available on iOS.
 * @param context A valid SSLContextRef.
 * @param dhParams Pointer to storage for DH parameters (if set), of at length most |*dhParamsLen|.
 * @param dhParamsLen (Input and output) length of dhParams.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetDiffieHellmanParams	(SSLContextRef			context,
                             const void 			* __nullable * __nonnull dhParams,
                             size_t					*dhParamsLen)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15));

/*
 * @function SSLSetRsaBlinding
 * @abstract Enable/Disable RSA blinding.
 * @discussion This feature thwarts a known timing
 *    attack to which RSA keys are vulnerable; enabling it is a tradeoff
 *    between performance and security. The default for RSA blinding is
 *    enabled.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X. RSA blinding is enabled unconditionally, as
 *    it prevents a known way for an attacker to recover the private key,
 *    and the performance gain of disabling it is negligible.
 * @param context A valid SSLContextRef.
 * @param blinding Boolean indicating if RSA blinding is enabled.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetRsaBlinding			(SSLContextRef			context,
                             Boolean				blinding)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

/*
 * @function SSLGetRsaBlinding
 * @abstract Get RSA blinding state.
 * @discussion See SSLSetRsaBlinding().
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * @note This function is not available on iOS, and should be considered
 *    deprecated on Mac OS X.
 * @param context A valid SSLContextRef.
 * @param blinding Pointer to Boolean storage for RSA blinding state.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetRsaBlinding			(SSLContextRef			context,
                             Boolean				*blinding)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.9));

#endif /* MAC OS X */

/*******************************
 ******** I/O Functions ********
 *******************************/

/*
 * Note: depending on the configuration of the underlying I/O
 * connection, all SSL I/O functions can return errSSLWouldBlock,
 * indicating "not complete, nothing is wrong, except required
 * I/O hasn't completed". Caller may need to repeat I/Os as necessary
 * if the underlying connection has been configured to behave in
 * a non-blocking manner.
 */

/*
 * @function SSLHandshake
 * @abstract Perform the SSL handshake.
 * @discussion On successful return, session is ready for normal secure application
 *    I/O via SSLWrite and SSLRead.
 *
 *    Interesting error returns:
 *
 *     errSSLUnknownRootCert: Peer had a valid cert chain, but the root of
 *         the chain is unknown.
 *
 *     errSSLNoRootCert: Peer had a cert chain which did not end in a root.
 *
 *     errSSLCertExpired: Peer's cert chain had one or more expired certs.
 *
 *     errSSLXCertChainInvalid: Peer had an invalid cert chain (i.e.,
 *         signature verification within the chain failed, or no certs
 *         were found).
 *
 *     In all of the above errors, the handshake was aborted; the peer's
 *     cert chain is available via SSLCopyPeerTrust or SSLCopyPeerCertificates.
 *
 *     Other interesting result codes:
 *
 *     errSSLPeerAuthCompleted: Peer's cert chain is valid, or was ignored if
 *         cert verification was disabled via SSLSetEnableCertVerify. The application
 *         may decide to continue with the handshake (by calling SSLHandshake
 *         again), or close the connection at this point.
 *
 *     errSSLClientCertRequested: The server has requested a client certificate.
 *         The client may choose to examine the server's certificate and
 *         distinguished name list, then optionally call SSLSetCertificate prior
 *         to resuming the handshake by calling SSLHandshake again.
 *
 *    A return value of errSSLWouldBlock indicates that SSLHandshake has to be
 *    called again (and again and again until something else is returned).
 * @param context A valid SSLContextRef.
 * @result errSecSuccess on success, alternative error on failure or incomplete state.
 */
OSStatus
SSLHandshake				(SSLContextRef		context)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLReHandshake
 * @abstract Server Only: Request renegotation.
 * @discussion This will return an error if the server is already renegotiating, or if the session is closed.
 *    After this return without error, the application should call SSLHandshake() and/or SSLRead() as
 *    for the original handshake.
 * @param context A valid SSLContextRef.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLReHandshake				(SSLContextRef		context)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.12, 10.15), ios(10.0, 13.0));


/*
 * @function SSLWrite
 * @abstract Normal application-level write.
 * @discussion On both of these, a errSSLWouldBlock return and a partially completed
 *    transfer - or even zero bytes transferred - are NOT mutually exclusive.
 * @param context A valid SSLContextRef.
 * @param data Pointer to data to write.
 * @param dataLength Length of data to write.
 * @param processed Pointer to storage indicating how much data was written.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLWrite					(SSLContextRef		context,
							 const void *		__nullable data,
							 size_t				dataLength,
							 size_t 			*processed)		/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLRead
 * @abstract * @abstract Normal application-level write.
 * @discussion Data is mallocd by caller; available size specified in
 *    dataLength; actual number of bytes read returned in
 *    *processed.
 * @param context A valid SSLContextRef.
 * @param data Pointer to storage where data can be read.
 * @param dataLength Length of data storage.
 * @param processed Pointer to storage indicating how much data was read.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLRead						(SSLContextRef		context,
							 void *				data,			/* RETURNED */
							 size_t				dataLength,
							 size_t 			*processed)		/* RETURNED */
    __SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetBufferedReadSize
 * @abstract Determine how much data the client can be guaranteed to
 *    obtain via SSLRead() without blocking or causing any low-level
 *    read operations to occur.
 * @param context A valid SSLContextRef.
 * @param bufferSize Pointer to store the amount of buffered data to be read.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetBufferedReadSize		(SSLContextRef context,
							 size_t *bufferSize)				/* RETURNED */
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLGetDatagramWriteSize
 * @abstract Determine how much data the application can be guaranteed to write
 *    with SSLWrite() without causing fragmentation. The value is based on
 *    the maximum Datagram Record size defined by the application with
 *    SSLSetMaxDatagramRecordSize(), minus the DTLS Record header size.
 * @param context A valid SSLContextRef (for DTLS).
 * @param bufferSize Pointer to store the amount of data that can be written.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLGetDatagramWriteSize		(SSLContextRef dtlsContext,
							 size_t *bufSize)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.8, 10.15), ios(5.0, 13.0));

/*
 * @function SSLClose
 * @abstract Terminate current SSL session.
 * @param context A valid SSLContextRef.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLClose					(SSLContextRef		context)
	__SECURETRANSPORT_API_DEPRECATED(macos(10.2, 10.15), ios(5.0, 13.0));

/*
 * @function SSLSetError
 * @abstract Set the status of a SSLContextRef.
 * @discussion This is to be done after handling steps of the SSL handshake such
 *    as server certificate validation.
 * @param context A valid SSLContextRef.
 * @param status Error status to set internally, which will be translated to an alert.
 * @result errSecSuccess on success, alternative error on failure.
 */
OSStatus
SSLSetError                 (SSLContextRef      context,
                             OSStatus           status)
    __SECURETRANSPORT_API_DEPRECATED(macos(10.13, 10.15), ios(11.0, 13.0));

#undef __SECURETRANSPORT_API_DEPRECATED

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif /* !_SECURITY_SECURETRANSPORT_H_ */
// ==========  Security.framework/Headers/SecItem.h
/*
 * Copyright (c) 2006-2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
    @header SecItem
    SecItem defines CoreFoundation-based constants and functions for
    access to Security items (certificates, keys, identities, and
    passwords.)
*/

#ifndef _SECURITY_SECITEM_H_
#define _SECURITY_SECITEM_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @enum Class Key Constant
    @discussion Predefined key constant used to get or set item class values in
        a dictionary. Its value is one of the constants defined in the Value
        Constants for kSecClass.
    @constant kSecClass Specifies a dictionary key whose value is the item's
        class code.  You use this key to get or set a value of type CFTypeRef
        that contains the item class code.
*/
extern const CFStringRef kSecClass
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum Class Value Constants
    @discussion Predefined item class constants used to get or set values in
        a dictionary. The kSecClass constant is the key and its value is one
        of the constants defined here. Note: on Mac OS X 10.6, only items
        of class kSecClassInternetPassword are supported.
    @constant kSecClassInternetPassword Specifies Internet password items.
    @constant kSecClassGenericPassword Specifies generic password items.
    @constant kSecClassCertificate Specifies certificate items.
    @constant kSecClassKey Specifies key items.
    @constant kSecClassIdentity Specifies identity items.
*/
extern const CFStringRef kSecClassInternetPassword
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecClassGenericPassword
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassCertificate
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassKey
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassIdentity
    API_AVAILABLE(macos(10.7), ios(2.0));

/*!
    @enum Attribute Key Constants
    @discussion Predefined item attribute keys used to get or set values in a
        dictionary. Not all attributes apply to each item class. The table
        below lists the currently defined attributes for each item class:

    kSecClassGenericPassword item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrCreationDate
        kSecAttrModificationDate
        kSecAttrDescription
        kSecAttrComment
        kSecAttrCreator
        kSecAttrType
        kSecAttrLabel
        kSecAttrIsInvisible
        kSecAttrIsNegative
        kSecAttrAccount
        kSecAttrService
        kSecAttrGeneric
        kSecAttrSynchronizable

    kSecClassInternetPassword item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrCreationDate
        kSecAttrModificationDate
        kSecAttrDescription
        kSecAttrComment
        kSecAttrCreator
        kSecAttrType
        kSecAttrLabel
        kSecAttrIsInvisible
        kSecAttrIsNegative
        kSecAttrAccount
        kSecAttrSecurityDomain
        kSecAttrServer
        kSecAttrProtocol
        kSecAttrAuthenticationType
        kSecAttrPort
        kSecAttrPath
        kSecAttrSynchronizable

    kSecClassCertificate item attributes:
        kSecAttrAccessible    (iOS only)
        kSecAttrAccessControl (iOS only)
        kSecAttrAccessGroup   (iOS only)
        kSecAttrCertificateType
        kSecAttrCertificateEncoding
        kSecAttrLabel
        kSecAttrSubject
        kSecAttrIssuer
        kSecAttrSerialNumber
        kSecAttrSubjectKeyID
        kSecAttrPublicKeyHash
        kSecAttrSynchronizable

    kSecClassKey item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrKeyClass
        kSecAttrLabel
        kSecAttrApplicationLabel
        kSecAttrIsPermanent
        kSecAttrApplicationTag
        kSecAttrKeyType
        kSecAttrPRF    (OS X only)
        kSecAttrSalt   (OS X only)
        kSecAttrRounds (OS X only)
        kSecAttrKeySizeInBits
        kSecAttrEffectiveKeySize
        kSecAttrCanEncrypt
        kSecAttrCanDecrypt
        kSecAttrCanDerive
        kSecAttrCanSign
        kSecAttrCanVerify
        kSecAttrCanWrap
        kSecAttrCanUnwrap
        kSecAttrSynchronizable

     Note that the attributes kSecAttrCan* describe attributes of the
     key itself at relatively high level. Some of these attributes are
     mathematical -- for example, a DSA key cannot encrypt. Others are
     key-level policy issues -- for example, it is good cryptographic
     hygiene to use an RSA key either for encryption or signing but not
     both. Compare these to the certificate-level policy values in
     SecPolicy.h.

    kSecClassIdentity item attributes:
        Since an identity is the combination of a private key and a
        certificate, this class shares attributes of both kSecClassKey and
        kSecClassCertificate.

     @constant kSecAttrAccessible Specifies a dictionary key whose value
     indicates when your application needs access to an item's data.  You
     should choose the most restrictive option that meets your application's
     needs to allow the system to protect that item in the best way possible.
     See the "kSecAttrAccessible Value Constants" section for a list of
     values which can be specified.
     IMPORTANT: This attribute is currently not supported for OS X keychain
     items, unless the kSecAttrSynchronizable attribute is also present. If
     both attributes are specified on either OS X or iOS, the value for the
     kSecAttrAccessible key may only be one whose name does not end with
     "ThisDeviceOnly", as those cannot sync to another device.

     @constant kSecAttrAccessControl Specifies a dictionary key whose value
     is SecAccessControl instance which contains access control conditions
     for item.
     IMPORTANT: This attribute is mutually exclusive with kSecAttrAccess
     attribute.

     @constant kSecAttrAccess Specifies a dictionary key whose value
     is a SecAccessRef describing the access control settings for this item.
     This key is available on OS X only.

     @constant kSecAttrAccessGroup Specifies a dictionary key whose value is
     a CFStringRef indicating which access group a item is in.  The access
     groups that a particular application has membership in are determined by
     two entitlements for that application.  The application-identifier
     entitlement contains the application's single access group, unless
     there is a keychain-access-groups entitlement present.  The latter
     has as its value a list of access groups; the first item in this list
     is the default access group. Unless a specific access group is provided
     as the value of kSecAttrAccessGroup when SecItemAdd is called, new items
     are created in the application's default access group.  Specifying this
     attribute in SecItemCopyMatching, SecItemUpdate, or SecItemDelete calls
     limits the search to the specified access group (of which the calling
     application must be a member to obtain matching results.)  To share
     keychain items between multiple applications, each application must have
     a common group listed in its keychain-access-groups entitlement, and each
     must specify this shared access group name as the value for the
     kSecAttrAccessGroup key in the dictionary passed to SecItem functions.

     @constant kSecAttrSynchronizable Specifies a dictionary key whose value is
     a CFBooleanRef indicating whether the item in question can be synchronized.
     To add a new item which can be synced to other devices, or to obtain
     synchronizable results from a query, supply this key with a value of
     kCFBooleanTrue. If the key is not supplied, or has a value of
     kCFBooleanFalse, then no synchronizable items will be added or returned.
     A predefined value, kSecAttrSynchronizableAny, may be provided instead of
     kCFBooleanTrue if both synchronizable and non-synchronizable results are
     desired.

     IMPORTANT: Specifying the kSecAttrSynchronizable key has several caveats:

         - Updating or deleting items using the kSecAttrSynchronizable key will
           affect all copies of the item, not just the one on your local device.
           Be sure that it makes sense to use the same password on all devices
           before deciding to make a password synchronizable.
         - Only password items can currently be synchronized. Keychain syncing
           is not supported for certificates or cryptographic keys.
         - Items stored or obtained using the kSecAttrSynchronizable key cannot
           specify SecAccessRef-based access control with kSecAttrAccess. If a
           password is intended to be shared between multiple applications, the
           kSecAttrAccessGroup key must be specified, and each application
           using this password must have a 'keychain-access-groups' entitlement
           with the specified access group value.
         - Items stored or obtained using the kSecAttrSynchronizable key may
           not also specify a kSecAttrAccessible value which is incompatible
           with syncing (namely, those whose names end with "ThisDeviceOnly".)
         - Items stored or obtained using the kSecAttrSynchronizable key cannot
           be specified by reference. You must pass kSecReturnAttributes and/or
           kSecReturnData to retrieve results; kSecReturnRef is currently not
           supported for synchronizable items.
         - Persistent references to synchronizable items should be avoided;
           while they may work locally, they cannot be moved between devices,
           and may not resolve if the item is modified on some other device.
         - When specifying a query that uses the kSecAttrSynchronizable key,
           search keys are limited to the item's class and attributes.
           The only search constant which may be used is kSecMatchLimit; other
           constants using the kSecMatch prefix are not supported at this time.

    @constant kSecAttrSynchronizableAny Specifies that both synchronizable and
        non-synchronizable results should be returned from this query. This may be
        used as a value for the kSecAttrSynchronizable dictionary key in a call to
        SecItemCopyMatching, SecItemUpdate, or SecItemDelete.

    @constant kSecAttrCreationDate (read-only) Specifies a dictionary key whose
        value is the item's creation date. You use this key to get a value
        of type CFDateRef that represents the date the item was created.
    @constant kSecAttrModificationDate (read-only) Specifies a dictionary key
        whose value is the item's modification date. You use this key to get
        a value of type CFDateRef that represents the last time the item was
        updated.
    @constant kSecAttrDescription Specifies a dictionary key whose value is
        the item's description attribute. You use this key to set or get a
        value of type CFStringRef that represents a user-visible string
        describing this particular kind of item (e.g., "disk image password").
    @constant kSecAttrComment Specifies a dictionary key whose value is the
        item's comment attribute. You use this key to set or get a value of
        type CFStringRef containing the user-editable comment for this item.
    @constant kSecAttrCreator Specifies a dictionary key whose value is the
        item's creator attribute. You use this key to set or get a value of
        type CFNumberRef that represents the item's creator. This number is
        the unsigned integer representation of a four-character code (e.g.,
        'aCrt').
    @constant kSecAttrType Specifies a dictionary key whose value is the item's
        type attribute. You use this key to set or get a value of type
        CFNumberRef that represents the item's type. This number is the
        unsigned integer representation of a four-character code (e.g.,
        'aTyp').
    @constant kSecAttrLabel Specifies a dictionary key whose value is the
        item's label attribute. You use this key to set or get a value of
        type CFStringRef containing the user-visible label for this item.
    @constant kSecAttrIsInvisible Specifies a dictionary key whose value is the
        item's invisible attribute. You use this key to set or get a value
        of type CFBooleanRef that indicates whether the item is invisible
        (i.e., should not be displayed.)
    @constant kSecAttrIsNegative Specifies a dictionary key whose value is the
        item's negative attribute. You use this key to set or get a value of
        type CFBooleanRef that indicates whether there is a valid password
        associated with this keychain item. This is useful if your application
        doesn't want a password for some particular service to be stored in
        the keychain, but prefers that it always be entered by the user.
    @constant kSecAttrAccount Specifies a dictionary key whose value is the
        item's account attribute. You use this key to set or get a CFStringRef
        that contains an account name. (Items of class
        kSecClassGenericPassword, kSecClassInternetPassword have this
        attribute.)
    @constant kSecAttrService Specifies a dictionary key whose value is the
        item's service attribute. You use this key to set or get a CFStringRef
        that represents the service associated with this item. (Items of class
        kSecClassGenericPassword have this attribute.)
    @constant kSecAttrGeneric Specifies a dictionary key whose value is the
        item's generic attribute. You use this key to set or get a value of
        CFDataRef that contains a user-defined attribute. (Items of class
        kSecClassGenericPassword have this attribute.)
    @constant kSecAttrSecurityDomain Specifies a dictionary key whose value
        is the item's security domain attribute. You use this key to set or
        get a CFStringRef value that represents the Internet security domain.
        (Items of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrServer Specifies a dictionary key whose value is the
        item's server attribute. You use this key to set or get a value of
        type CFStringRef that contains the server's domain name or IP address.
        (Items of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrProtocol Specifies a dictionary key whose value is the
        item's protocol attribute. You use this key to set or get a value of
        type CFNumberRef that denotes the protocol for this item (see the
        SecProtocolType enum in SecKeychainItem.h). (Items of class
        kSecClassInternetPassword have this attribute.)
    @constant kSecAttrAuthenticationType Specifies a dictionary key whose value
        is the item's authentication type attribute. You use this key to set
        or get a value of type CFNumberRef that denotes the authentication
        scheme for this item (see the kSecAttrAuthenticationType value
        constants below).
    @constant kSecAttrPort Specifies a dictionary key whose value is the item's
        port attribute. You use this key to set or get a CFNumberRef value
        that represents an Internet port number. (Items of class
        kSecClassInternetPassword have this attribute.)
    @constant kSecAttrPath Specifies a dictionary key whose value is the item's
        path attribute, typically this is the path component of the URL.  You use
        this key to set or get a CFStringRef value that represents a path. (Items
        of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrSubject (read-only) Specifies a dictionary key whose
        value is the item's subject. You use this key to get a value of type
        CFDataRef that contains the X.500 subject name of a certificate.
        (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrIssuer (read-only) Specifies a dictionary key whose value
        is the item's issuer. You use this key to get a value of type
        CFDataRef that contains the X.500 issuer name of a certificate. (Items
        of class kSecClassCertificate have this attribute.)
    @constant kSecAttrSerialNumber (read-only) Specifies a dictionary key whose
        value is the item's serial number.  You use this key to get a value
        of type CFDataRef that contains the serial number data of a
        certificate. (Items of class kSecClassCertificate have this
        attribute.)
    @constant kSecAttrSubjectKeyID (read-only) Specifies a dictionary key whose
        value is the item's subject key ID. You use this key to get a value
        of type CFDataRef that contains the subject key ID of a certificate.
        (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrPublicKeyHash (read-only) Specifies a dictionary key
        whose value is the item's public key hash. You use this key to get a
        value of type CFDataRef that contains the hash of a certificate's
        public key. (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrCertificateType (read-only) Specifies a dictionary key
        whose value is the item's certificate type. You use this key to get
        a value of type CFNumberRef that denotes the certificate type
        (On iOS, currently the value of this attribute must be equal to the
        version of the X509 certificate.  So, 1 for v1, 2 for v2, and 3 for v3
        certificates). (On OSX, see the CSSM_CERT_TYPE enum in cssmtype.h).
        Only items of class kSecClassCertificate have this attribute.
    @constant kSecAttrCertificateEncoding (read-only) Specifies a dictionary
        key whose value is the item's certificate encoding. You use this key
        to get a value of type CFNumberRef that denotes the certificate
        encoding (On iOS, currently only the value 3 meaning
        kSecAttrCertificateEncodingDER is supported). On OSX, see the
        CSSM_CERT_ENCODING enum in cssmtype.h. Only items of class
        kSecClassCertificate have this attribute.
    @constant kSecAttrKeyClass (read only) Specifies a dictionary key whose
        value is one of kSecAttrKeyClassPublic, kSecAttrKeyClassPrivate or
        kSecAttrKeyClassSymmetric.
    @constant kSecAttrApplicationLabel Specifies a dictionary key whose value
        is the key's application label attribute. This is different from the
        kSecAttrLabel (which is intended to be human-readable). This attribute
        is used to look up a key programmatically; in particular, for keys of
        class kSecAttrKeyClassPublic and kSecAttrKeyClassPrivate, the value of
        this attribute is the hash of the public key. This item is a type of CFDataRef.
        Legacy keys may contain a UUID in this field as a CFStringRef.
    @constant kSecAttrIsPermanent Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question will be stored
        permanently.
     @constant kSecAttrIsSensitive Specifies a dictionary key whose value is a
        CFBooleanRef indicating that the key in question can only be exported
        in a wrapped (encrypted) format. OS X only.
     @constant kSecAttrIsExtractable Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question can be exported from
        its keychain container. OS X only.
    @constant kSecAttrApplicationTag Specifies a dictionary key whose value is a
        CFDataRef containing private tag data.
    @constant kSecAttrKeyType Specifies a dictionary key whose value is a
        CFNumberRef indicating the algorithm associated with this key
        (On iOS, currently only the value 42 is supported, alternatively you can use
        kSecAttrKeyTypeRSA). (On OSX, see the CSSM_ALGORITHMS enum in cssmtype.h).

    @constant kSecAttrPRF Specifies a dictionary key whose value is the PRF
        (pseudo-random function) for this key (see "kSecAttrPRF Value Constants".)
        OS X only.
    @constant kSecAttrSalt Specifies a dictionary key whose value is a
        CFData containing the salt to use for this key. OS X only.
    @constant kSecAttrRounds Specifies a dictionary key whose value is the
        number of rounds for the pseudo-random function specified by kSecAttrPRF.
        OS X only.
    @constant kSecAttrKeySizeInBits Specifies a dictionary key whose value
        is a CFNumberRef indicating the number of bits in this key.
    @constant kSecAttrEffectiveKeySize Specifies a dictionary key whose value
        is a CFNumberRef indicating the effective number of bits in this key.
        For example, a DES key has a kSecAttrKeySizeInBits of 64, but a
        kSecAttrEffectiveKeySize of 56 bits.
    @constant kSecAttrCanEncrypt Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        encrypt data.
    @constant kSecAttrCanDecrypt Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question can be used to
        decrypt data.
    @constant kSecAttrCanDerive Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        derive another key.
    @constant kSecAttrCanSign Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        create a digital signature.
    @constant kSecAttrCanVerify Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        verify a digital signature.
    @constant kSecAttrCanWrap Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        wrap another key.
    @constant kSecAttrCanUnwrap Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        unwrap another key.
    @constant kSecAttrSyncViewHint Specifies a dictionary key whose value is
        a CFStringRef. This value is part of the primary key of each item, and
        can be used to help distiguish Sync Views when defining their
        queries. iOS and sychronizable items only.
    @constant kSecAttrTokenID Specifies a dictionary key whose presence
        indicates that item is backed by external token. Value of this attribute
        is CFStringRef uniquely identifying containing token. When this attribute
        is not present, item is stored in internal keychain database.
        Note that once item is created, this attribute cannot be changed - in other
        words it is not possible to migrate existing items to, from or between tokens.
        Currently the only available value for this attribute is
        kSecAttrTokenIDSecureEnclave, which indicates that item (private key) is
        backed by device's Secure Enclave. iOS only.
 */
extern const CFStringRef kSecAttrAccessible
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccess
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrAccessControl
    API_AVAILABLE(macos(10.10), ios(8.0));
extern const CFStringRef kSecAttrAccessGroup
    API_AVAILABLE(macos(10.9), ios(3.0));
extern const CFStringRef kSecAttrSynchronizable
    API_AVAILABLE(macos(10.9), ios(7.0));
extern const CFStringRef kSecAttrSynchronizableAny
    API_AVAILABLE(macos(10.9), ios(7.0));
extern const CFStringRef kSecAttrCreationDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrModificationDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrDescription
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrComment
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCreator
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrLabel
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsInvisible
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsNegative
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAccount
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrService
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrGeneric
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSecurityDomain
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrServer
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocol
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPort
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPath
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSubject
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIssuer
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSerialNumber
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSubjectKeyID
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPublicKeyHash
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCertificateType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCertificateEncoding
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrKeyClass
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrApplicationLabel
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsPermanent
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsSensitive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsExtractable
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrApplicationTag
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrKeyType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPRF
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrSalt
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrRounds
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeySizeInBits
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrEffectiveKeySize
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanEncrypt
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanDecrypt
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanDerive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanSign
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanVerify
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanWrap
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanUnwrap
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSyncViewHint
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecAttrTokenID
    API_AVAILABLE(macos(10.12), ios(9.0));
extern const CFStringRef kSecAttrPersistantReference
    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
extern const CFStringRef kSecAttrPersistentReference
    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
    @enum kSecAttrAccessible Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrAccessible constant is the key and its
        value is one of the constants defined here.
        When asking SecItemCopyMatching to return the item's data, the error
        errSecInteractionNotAllowed will be returned if the item's data is not
        available until a device unlock occurs.
    @constant kSecAttrAccessibleWhenUnlocked Item data can only be accessed
        while the device is unlocked. This is recommended for items that only
        need be accesible while the application is in the foreground.  Items
        with this attribute will migrate to a new device when using encrypted
        backups.
    @constant kSecAttrAccessibleAfterFirstUnlock Item data can only be
        accessed once the device has been unlocked after a restart.  This is
        recommended for items that need to be accesible by background
        applications. Items with this attribute will migrate to a new device
        when using encrypted backups.
    @constant kSecAttrAccessibleAlways Item data can always be accessed
        regardless of the lock state of the device.  This is not recommended
        for anything except system use. Items with this attribute will migrate
        to a new device when using encrypted backups.
    @constant kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly Item data can
        only be accessed while the device is unlocked. This is recommended for
        items that only need to be accessible while the application is in the
        foreground and requires a passcode to be set on the device. Items with
        this attribute will never migrate to a new device, so after a backup
        is restored to a new device, these items will be missing. This
        attribute will not be available on devices without a passcode. Disabling
        the device passcode will cause all previously protected items to
        be deleted.
    @constant kSecAttrAccessibleWhenUnlockedThisDeviceOnly Item data can only
        be accessed while the device is unlocked. This is recommended for items
        that only need be accesible while the application is in the foreground.
        Items with this attribute will never migrate to a new device, so after
        a backup is restored to a new device, these items will be missing.
    @constant kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly Item data can
        only be accessed once the device has been unlocked after a restart.
        This is recommended for items that need to be accessible by background
        applications. Items with this attribute will never migrate to a new
        device, so after a backup is restored to a new device these items will
        be missing.
    @constant kSecAttrAccessibleAlwaysThisDeviceOnly Item data can always
        be accessed regardless of the lock state of the device.  This option
        is not recommended for anything except system use. Items with this
        attribute will never migrate to a new device, so after a backup is
        restored to a new device, these items will be missing.
*/
extern const CFStringRef kSecAttrAccessibleWhenUnlocked
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlock
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAlways
    API_DEPRECATED("Use an accessibility level that provides some user protection, such as kSecAttrAccessibleAfterFirstUnlock", macos(10.9, 10.14), ios(4.0, 12.0));
extern const CFStringRef kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly
    API_AVAILABLE(macos(10.10), ios(8.0));
extern const CFStringRef kSecAttrAccessibleWhenUnlockedThisDeviceOnly
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAlwaysThisDeviceOnly
    API_DEPRECATED("Use an accessibility level that provides some user protection, such as kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly", macos(10.9, 10.14), ios(4.0, 12.0));

/*!
    @enum kSecAttrProtocol Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrProtocol constant is the key and its
        value is one of the constants defined here.
    @constant kSecAttrProtocolFTP.
    @constant kSecAttrProtocolFTPAccount.
    @constant kSecAttrProtocolHTTP.
    @constant kSecAttrProtocolIRC.
    @constant kSecAttrProtocolNNTP.
    @constant kSecAttrProtocolPOP3.
    @constant kSecAttrProtocolSMTP.
    @constant kSecAttrProtocolSOCKS.
    @constant kSecAttrProtocolIMAP.
    @constant kSecAttrProtocolLDAP.
    @constant kSecAttrProtocolAppleTalk.
    @constant kSecAttrProtocolAFP.
    @constant kSecAttrProtocolTelnet.
    @constant kSecAttrProtocolSSH.
    @constant kSecAttrProtocolFTPS.
    @constant kSecAttrProtocolHTTPS.
    @constant kSecAttrProtocolHTTPProxy.
    @constant kSecAttrProtocolHTTPSProxy.
    @constant kSecAttrProtocolFTPProxy.
    @constant kSecAttrProtocolSMB.
    @constant kSecAttrProtocolRTSP.
    @constant kSecAttrProtocolRTSPProxy.
    @constant kSecAttrProtocolDAAP.
    @constant kSecAttrProtocolEPPC.
    @constant kSecAttrProtocolIPP.
    @constant kSecAttrProtocolNNTPS.
    @constant kSecAttrProtocolLDAPS.
    @constant kSecAttrProtocolTelnetS.
    @constant kSecAttrProtocolIMAPS.
    @constant kSecAttrProtocolIRCS.
    @constant kSecAttrProtocolPOP3S.
*/
extern const CFStringRef kSecAttrProtocolFTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPAccount
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIRC
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolNNTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolPOP3
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSMTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSOCKS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIMAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolLDAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolAppleTalk
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolAFP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolTelnet
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSSH
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPSProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSMB
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolRTSP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolRTSPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolDAAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolEPPC
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIPP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolNNTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolLDAPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolTelnetS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIMAPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIRCS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolPOP3S
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum kSecAttrAuthenticationType Value Constants
    @discussion Predefined item attribute constants used to get or set values
         in a dictionary. The kSecAttrAuthenticationType constant is the key
         and its value is one of the constants defined here.
    @constant kSecAttrAuthenticationTypeNTLM.
    @constant kSecAttrAuthenticationTypeMSN.
    @constant kSecAttrAuthenticationTypeDPA.
    @constant kSecAttrAuthenticationTypeRPA.
    @constant kSecAttrAuthenticationTypeHTTPBasic.
    @constant kSecAttrAuthenticationTypeHTTPDigest.
    @constant kSecAttrAuthenticationTypeHTMLForm.
    @constant kSecAttrAuthenticationTypeDefault.
*/
extern const CFStringRef kSecAttrAuthenticationTypeNTLM
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeMSN
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeDPA
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeRPA
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTTPBasic
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTTPDigest
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTMLForm
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeDefault
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum kSecAttrKeyClass Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrKeyClass constant is the key
        and its value is one of the constants defined here.
    @constant kSecAttrKeyClassPublic.
    @constant kSecAttrKeyClassPrivate.
    @constant kSecAttrKeyClassSymmetric.
*/
extern const CFStringRef kSecAttrKeyClassPublic
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyClassPrivate
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyClassSymmetric
    API_AVAILABLE(macos(10.7), ios(2.0));

/*!
    @enum kSecAttrKeyType Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrKeyType constant is the key
        and its value is one of the constants defined here.
    @constant kSecAttrKeyTypeECSECPrimeRandom.
    @constant kSecAttrKeyTypeEC This is the legacy name for kSecAttrKeyTypeECSECPrimeRandom, new applications should not use it.
    @constant kSecAttrKeyTypeDSA (OSX only)
    @constant kSecAttrKeyTypeAES (OSX only)
    @constant kSecAttrKeyType3DES (OSX only)
    @constant kSecAttrKeyTypeRC4 (OSX only)
    @constant kSecAttrKeyTypeRC2 (OSX only)
    @constant kSecAttrKeyTypeCAST (OSX only)
    @constant kSecAttrKeyTypeECDSA (deprecated; use kSecAttrKeyTypeECSECPrimeRandom instead.) (OSX only)
*/
extern const CFStringRef kSecAttrKeyTypeRSA
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyTypeDSA
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeAES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeDES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyType3DES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeRC4
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeRC2
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeCAST
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeECDSA
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeEC
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrKeyTypeECSECPrimeRandom
    API_AVAILABLE(macos(10.12), ios(10.0));

/*
     @enum kSecAttrPRF Value Constants
     @discussion Predefined item attribute constants used to specify the PRF
     to use with SecKeyDeriveFromPassword. OS X only.
     @constant kSecAttrPRFHmacAlgSHA1
     @constant kSecAttrPRFHmacAlgSHA224
     @constant kSecAttrPRFHmacAlgSHA256
     @constant kSecAttrPRFHmacAlgSHA384
     @constant kSecAttrPRFHmacAlgSHA512
*/
extern const CFStringRef kSecAttrPRFHmacAlgSHA1
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA224
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA256
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA384
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA512
      API_AVAILABLE(macos(10.7), ios(NA));


/*!
    @enum Search Constants
    @discussion Predefined search constants used to set values in a query
        dictionary. You can specify a combination of search attributes and
        item attributes when looking for matching items with the
        SecItemCopyMatching function.
    @constant kSecMatchPolicy Specifies a dictionary key whose value is a
        SecPolicyRef. If provided, returned certificates or identities must
        verify with this policy.
    @constant kSecMatchItemList OS X only. Specifies a dictionary key whose value is a
         CFArray of SecKeychainItemRef items. If provided, returned items will be
         limited to the subset which are contained in this list.
         @constant kSecMatchSearchList Specifies a dictionary key whose value is a
         CFArray of SecKeychainRef items. If provided, the search will be limited
         to the keychains contained in this list.
    @constant kSecMatchIssuers Specifies a dictionary key whose value is a
        CFArray of X.500 names (of type CFDataRef). If provided, returned
        certificates or identities will be limited to those whose
        certificate chain contains one of the issuers provided in this list.
    @constant kSecMatchEmailAddressIfPresent Specifies a dictionary key whose
        value is a CFStringRef containing an RFC822 email address. If
        provided, returned certificates or identities will be limited to those
        that contain the address, or do not contain any email address.
    @constant kSecMatchSubjectContains Specifies a dictionary key whose value
        is a CFStringRef. If provided, returned certificates or identities
        will be limited to those containing this string in the subject.
    @constant kSecMatchSubjectStartsWith OS X only. Specifies a dictionary key whose value
        is a CFStringRef. If provided, returned certificates or identities
        will be limited to those with subject names that start with this string.
    @constant kSecMatchSubjectEndsWith OS X only. Specifies a dictionary key whose value
         is a CFStringRef. If provided, returned certificates or identities
         will be limited to those with subject names that end with this string.
    @constant kSecMatchSubjectWholeString OS X only. Specifies a dictionary key whose
         value is a CFStringRef. If provided, returned certificates or identities
         will be limited to those matching this string exactly in the subject.
    @constant kSecMatchCaseInsensitive Specifies a dictionary key whose value
        is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then case-sensitive string matching is performed.
    @constant kSecMatchDiacriticInsensitive OS X only. Specifies a dictionary key whose
        value is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then diacritic-sensitive string matching is performed.
    @constant kSecMatchWidthInsensitive OS X only. Specifies a dictionary key whose
        value is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then string matching is width-sensitive (e.g. 'a' != 0xFF41).
    @constant kSecMatchTrustedOnly Specifies a dictionary key whose value is
        a CFBooleanRef. If provided with a value of kCFBooleanTrue, only
        certificates which can be verified back to a trusted anchor will be
        returned. If this value is kCFBooleanFalse, or is not provided, then
        both trusted and untrusted certificates may be returned.
    @constant kSecMatchValidOnDate Specifies a dictionary key whose value is
        of type CFDateRef. If provided, returned keys, certificates or
        identities will be limited to those which are valid for the given date.
        Pass a value of kCFNull to indicate the current date.
    @constant kSecMatchLimit Specifies a dictionary key whose value is a
        CFNumberRef. If provided, this value specifies the maximum number of
        results to return. If not provided, results are limited to the first
        item found. Predefined values are provided for a single item
        (kSecMatchLimitOne) and all matching items (kSecMatchLimitAll).
    @constant kSecMatchLimitOne Specifies that results are limited to the first
        item found; used as a value for the kSecMatchLimit dictionary key.
    @constant kSecMatchLimitAll Specifies that an unlimited number of results
        may be returned; used as a value for the kSecMatchLimit dictionary
        key.
*/
extern const CFStringRef kSecMatchPolicy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchItemList
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSearchList
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchIssuers
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchEmailAddressIfPresent
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSubjectContains
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSubjectStartsWith
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchSubjectEndsWith
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchSubjectWholeString
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchCaseInsensitive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchDiacriticInsensitive
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchWidthInsensitive
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchTrustedOnly
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchValidOnDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimit
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimitOne
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimitAll
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Return Type Key Constants
    @discussion Predefined return type keys used to set values in a dictionary.
        You use these keys to specify the type of results which should be
        returned by the SecItemCopyMatching or SecItemAdd function. You can
        specify zero or more of these return types. If more than one of these
        result types is specified, the result is returned as a CFDictionaryRef
        whose keys are the result types and values are the requested data.
    @constant kSecReturnData Specifies a dictionary key whose value is of type
        CFBooleanRef. A value of kCFBooleanTrue indicates that the data of
        an item (CFDataRef) should be returned. For keys and password
        items, data is secret (encrypted) and may require the user to enter
        a password for access.
    @constant kSecReturnAttributes Specifies a dictionary key whose value is
        of type CFBooleanRef. A value of kCFBooleanTrue indicates that the
        (non-encrypted) attributes of an item (CFDictionaryRef) should be
        returned.
    @constant kSecReturnRef Specifies a dictionary key whose value is a
        CFBooleanRef. A value of kCFBooleanTrue indicates that a reference
        should be returned. Depending on the item class requested, the
        returned reference(s) may be of type SecKeychainItemRef, SecKeyRef,
        SecCertificateRef, or SecIdentityRef.
    @constant kSecReturnPersistentRef Specifies a dictionary key whose value
        is of type CFBooleanRef. A value of kCFBooleanTrue indicates that a
        persistent reference to an item (CFDataRef) should be returned.
*/
extern const CFStringRef kSecReturnData
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnAttributes
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnRef
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnPersistentRef
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Value Type Key Constants
    @discussion Predefined value type keys used to pass values in a dictionary.
        You can specify zero or more of these types depending on the function
        you are calling.  For SecItemCopyMatching or SecItemAdd these are
        used as keys in the results dictionary.
    @constant kSecValueData Specifies a dictionary key whose value is of type
        CFDataRef.  For keys and password items, data is secret (encrypted)
        and may require the user to enter a password for access.
    @constant kSecValueRef Specifies a dictionary key whose value, depending
        on the item class requested, is of type SecKeychainItemRef, SecKeyRef,
        SecCertificateRef, or SecIdentityRef.
    @constant kSecValuePersistentRef Specifies a dictionary key whose value
        is of type CFDataRef.  The bytes in this CFDataRef can be stored by
        the caller and used on a subsequent invocation of the application (or
        even a different application) to retrieve the item referenced by it.
*/
extern const CFStringRef kSecValueData
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecValueRef
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecValuePersistentRef
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Other Constants
    @discussion Predefined constants used to set values in a dictionary.
    @constant kSecUseItemList Specifies a dictionary key whose value is a
        CFArray of items. If provided, this array is treated as the set of
        all possible items to search, or add if the API being called is
        SecItemAdd. The items in this array may be of type SecKeyRef,
        SecCertificateRef, SecIdentityRef, or CFDataRef (for a persistent
        item reference.) The items in the array must all be of the same
        type. When this attribute is provided, no keychains are searched.
    @constant kSecUseKeychain OS X only. Specifies a dictionary key whose value is a
        keychain reference. You use this key to specify a value of type
        SecKeychainRef to which SecItemAdd will add the provided item(s).
    @constant kSecUseOperationPrompt Specifies a dictionary key whose value
        is a CFStringRef that represents a user-visible string describing
        the operation for which the application is attempting to authenticate.
        The application is responsible for the text localization.
    @constant kSecUseNoAuthenticationUI OS X only. Specifies a dictionary key whose value
        is a CFBooleanRef. If provided with a value of kCFBooleanTrue, the error
        errSecInteractionNotAllowed will be returned if the item is attempting
        to authenticate with UI.
    @constant kSecUseAuthenticationUI Specifies a dictionary key whose value
        is one of kSecUseAuthenticationUIAllow, kSecUseAuthenticationUIFail, kSecUseAuthenticationUISkip.
    @constant kSecUseAuthenticationContext Specifies a dictionary key whose value
        is LAContext to be used for keychain item authentication.
        * If the item requires authentication and this key is omitted, a new context
          will be created just for the purpose of the single call.
        * If the specified context has been previously authenticated, the operation
          will succeed without asking user for authentication.
        * If the specified context has not been previously authenticated, the new
          authentication will be started on this context, allowing caller to
          eventually reuse the successfully authenticated context in subsequent
          keychain operations.
    @constant kSecUseDataProtectionKeychain Specifies a dictionary key whose value
        is a CFBooleanRef. Set to kCFBooleanTrue to use kSecAttrAccessGroup and/or
        kSecAttrAccessible on macOS without requiring the item to be marked synchronizable.
*/
extern const CFStringRef kSecUseItemList
    API_AVAILABLE(macos(10.6))
    API_DEPRECATED("Not implemented on this platform", ios(2.0, 12.0), tvos(9.0, 12.0), watchos(1.0, 5.0))
    API_UNAVAILABLE( uikitformac);
extern const CFStringRef kSecUseKeychain
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecUseOperationPrompt
    API_AVAILABLE(macos(10.10), ios(8.0));
extern const CFStringRef kSecUseNoAuthenticationUI
    API_DEPRECATED("Use kSecUseAuthenticationUI instead.", macos(10.10, 10.11), ios(8.0, 9.0));
extern const CFStringRef kSecUseAuthenticationUI
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseAuthenticationContext
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseDataProtectionKeychain
    API_AVAILABLE(macos(10.15), ios(13.0));

/*!
    @enum kSecUseAuthenticationUI Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecUseAuthenticationUI constant is the key and its
        value is one of the constants defined here.
        If the key kSecUseAuthenticationUI not provided then kSecUseAuthenticationUIAllow
        is used as default.
    @constant kSecUseAuthenticationUIAllow Specifies that authenticate UI can appear.
    @constant kSecUseAuthenticationUIFail Specifies that the error
        errSecInteractionNotAllowed will be returned if an item needs
        to authenticate with UI
    @constant kSecUseAuthenticationUIAllowSkip Specifies that all items which need
        to authenticate with UI will be silently skipped. This value can be used
        only with SecItemCopyMatching.
*/
extern const CFStringRef kSecUseAuthenticationUIAllow
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseAuthenticationUIFail
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseAuthenticationUISkip
    API_AVAILABLE(macos(10.11), ios(9.0));

/*!
     @enum kSecAttrTokenID Value Constants
     @discussion Predefined item attribute constant used to get or set values
         in a dictionary. The kSecAttrTokenID constant is the key and its value
         can be kSecAttrTokenIDSecureEnclave.
     @constant kSecAttrTokenIDSecureEnclave Specifies well-known identifier of the
         token implemented using device's Secure Enclave. The only keychain items
         supported by the Secure Enclave token are 256-bit elliptic curve keys
         (kSecAttrKeyTypeECSecPrimeRandom). Keys must be generated on the secure enclave using
         SecKeyGenerateKeyPair call with kSecAttrTokenID set to
         kSecAttrTokenIDSecureEnclave in the parameters dictionary, it is not
         possible to import pregenerated keys to kSecAttrTokenIDSecureEnclave token.
*/
extern const CFStringRef kSecAttrTokenIDSecureEnclave
    API_AVAILABLE(macos(10.12), ios(9.0));

/*!
     @enum kSecAttrAccessGroup Value Constants
     @constant kSecAttrAccessGroupToken Represents well-known access group
         which contains items provided by external token (typically smart card).
         This may be used as a value for kSecAttrAccessGroup attribute. Every
         application has access to this access group so it is not needed to
         explicitly list it in keychain-access-groups entitlement, but application
         must explicitly state this access group in keychain queries in order to
         be able to access items from external tokens.
*/
extern const CFStringRef kSecAttrAccessGroupToken
    API_AVAILABLE(macos(10.12), ios(10.0));

/*!
    @function SecItemCopyMatching
    @abstract Returns one or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Keychain
        Search Attributes" section for a description of currently defined
        search attributes.
    @param result On return, a CFTypeRef reference to the found item(s). The
        exact type of the result is based on the search attributes supplied
        in the query, as discussed below.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.

    A typical query consists of:

      * a kSecClass key, whose value is a constant from the Class
        Constants section that specifies the class of item(s) to be searched
      * one or more keys from the "Attribute Key Constants" section, whose value
        is the attribute data to be matched
      * one or more keys from the "Search Constants" section, whose value is
        used to further refine the search
      * a key from the "Return Type Key Constants" section, specifying the type of
        results desired

   Result types are specified as follows:

      * To obtain the data of a matching item (CFDataRef), specify
        kSecReturnData with a value of kCFBooleanTrue.
      * To obtain the attributes of a matching item (CFDictionaryRef), specify
        kSecReturnAttributes with a value of kCFBooleanTrue.
      * To obtain a reference to a matching item (SecKeychainItemRef,
        SecKeyRef, SecCertificateRef, or SecIdentityRef), specify kSecReturnRef
        with a value of kCFBooleanTrue.
      * To obtain a persistent reference to a matching item (CFDataRef),
        specify kSecReturnPersistentRef with a value of kCFBooleanTrue. Note
        that unlike normal references, a persistent reference may be stored
        on disk or passed between processes.
      * If more than one of these result types is specified, the result is
        returned as a CFDictionaryRef containing all the requested data.
      * If a result type is not specified, no results are returned.

    By default, this function returns only the first match found. To obtain
    more than one matching item at a time, specify kSecMatchLimit with a value
    greater than 1. The result will be a CFArrayRef containing up to that
    number of matching items; the items' types are described above.

    To filter a provided list of items down to those matching the query,
    specify a kSecMatchItemList whose value is a CFArray of SecKeychainItemRef,
    SecKeyRef, SecCertificateRef, or SecIdentityRef items. The objects in the
    provided array must be of the same type.

    On iOS, to convert from a persistent item reference to a normal item reference,
    specify a kSecValuePersistentRef whose value a CFDataRef (the persistent
    reference), and a kSecReturnRef whose value is kCFBooleanTrue.

    On OSX, to convert from persistent item references to normal item references,
    specify a kSecMatchItemList whose value is a CFArray containing one or
    more CFDataRef elements (the persistent reference), and a kSecReturnRef
    whose value is kCFBooleanTrue. The objects in the provided array must be
    of the same type.
*/
OSStatus SecItemCopyMatching(CFDictionaryRef query, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemAdd
    @abstract Add one or more items to a keychain.
    @param attributes A dictionary containing an item class specification and
        optional entries specifying the item's attribute values. See the
        "Attribute Key Constants" section for a description of currently defined
        attributes.
    @param result On return, a CFTypeRef reference to the newly added item(s).
        The exact type of the result is based on the values supplied
        in attributes, as discussed below. Pass NULL if this result is not
        required.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining an item are specified by adding key/value
        pairs to the attributes dictionary.  To add multiple items to a keychain
        at once use the kSecUseItemList key with an array of items as its value.
        This is currently only supported for non password items.

        On OSX, To add an item to a particular keychain, supply kSecUseKeychain
        with a SecKeychainRef as its value.

    Result types are specified as follows:

      * To obtain the data of the added item (CFDataRef), specify
        kSecReturnData with a value of kCFBooleanTrue.
      * To obtain all the attributes of the added item (CFDictionaryRef),
        specify kSecReturnAttributes with a value of kCFBooleanTrue.
      * To obtain a reference to the added item (SecKeychainItemRef, SecKeyRef,
        SecCertiicateRef, or SecIdentityRef), specify kSecReturnRef with a
        value of kCFBooleanTrue.
      * To obtain a persistent reference to the added item (CFDataRef), specify
        kSecReturnPersistentRef with a value of kCFBooleanTrue. Note that
        unlike normal references, a persistent reference may be stored on disk
        or passed between processes.
      * If more than one of these result types is specified, the result is
        returned as a CFDictionaryRef containing all the requested data.
      * On iOS, if a result type is not specified, no results are returned.
        On OSX, the added item is returned.
*/
OSStatus SecItemAdd(CFDictionaryRef attributes, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemUpdate
    @abstract Modify zero or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Attribute
        Constants" and "Search Constants" sections for a description of
        currently defined search attributes.
    @param attributesToUpdate A dictionary containing one or more attributes
        whose values should be set to the ones specified. Only real keychain
        attributes are permitted in this dictionary (no "meta" attributes are
        allowed.) See the "Attribute Key Constants" section for a description of
        currently defined value attributes.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.
*/
OSStatus SecItemUpdate(CFDictionaryRef query, CFDictionaryRef attributesToUpdate)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemDelete
    @abstract Delete zero or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Attribute
        Constants" and "Search Constants" sections for a description of
        currently defined search attributes.
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.

    By default, this function deletes all items matching the specified query.
    You can change this behavior by specifying one of the follow keys:

      * To delete an item identified by a transient reference, on iOS, specify
        kSecValueRef with a item reference. On OS X, give a kSecMatchItemList
        containing an item reference.
      * To delete an item identified by a persistent reference, on iOS, specify
        kSecValuePersistentRef with a persistent reference returned by
        using the kSecReturnPersistentRef key to SecItemCopyMatching or
        SecItemAdd. on OSX, use kSecMatchItemList with a persistent reference
        returned by using the kSecReturnPersistentRef key with
        SecItemCopyMatching or SecItemAdd.
      * To delete multiple items specify kSecMatchItemList with an array
        of references.
      * If more than one of these result keys is specified, the behavior is
        undefined.
*/
OSStatus SecItemDelete(CFDictionaryRef query)
    API_AVAILABLE(macos(10.6), ios(2.0));

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECITEM_H_ */
// ==========  Security.framework/Headers/Security.h
/*
 * Copyright (c) 2000-2011,2012,2013-2014,2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SECURITY_H_
#define _SECURITY_H_

#include <Security/SecBase.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>
#include <Security/SecAccessControl.h>
#include <Security/SecItem.h>
#include <Security/SecKey.h>
#include <Security/SecPolicy.h>
#include <Security/SecRandom.h>
#include <Security/SecImportExport.h>
#include <Security/SecTrust.h>
#include <Security/SecSharedCredential.h>
#include <Security/SecProtocolOptions.h>
#include <Security/SecProtocolMetadata.h>

#if SEC_OS_OSX_INCLUDES
#include <Security/AuthSession.h>
#endif

#if SEC_OS_OSX_INCLUDES
/* CDSA */
#include <Security/cssmconfig.h>
#include <Security/cssmapple.h>
#include <Security/certextensions.h>
#include <Security/cssm.h>
#include <Security/cssmaci.h>
#include <Security/cssmapi.h>
#include <Security/cssmcli.h>
#include <Security/cssmcspi.h>
#include <Security/cssmdli.h>
#include <Security/cssmerr.h>
#include <Security/cssmkrapi.h>
#include <Security/cssmkrspi.h>
#include <Security/cssmspi.h>
#include <Security/cssmtpi.h>
#include <Security/cssmtype.h>
#include <Security/emmspi.h>
#include <Security/emmtype.h>
#include <Security/mds.h>
#include <Security/mds_schema.h>
#include <Security/oidsalg.h>
#include <Security/oidsattr.h>
#include <Security/oidsbase.h>
#include <Security/oidscert.h>
#include <Security/oidscrl.h>
#include <Security/x509defs.h>

/* Security */
#include <Security/SecAccess.h>
#include <Security/SecACL.h>
#include <Security/SecCertificateOIDs.h>
#include <Security/SecIdentitySearch.h>
#include <Security/SecKeychain.h>
#include <Security/SecKeychainItem.h>
#include <Security/SecKeychainSearch.h>
#include <Security/SecPolicySearch.h>
#include <Security/SecTrustedApplication.h>
#include <Security/SecTrustSettings.h>

/* Code Signing */
#include <Security/SecStaticCode.h>
#include <Security/SecCode.h>
#include <Security/SecCodeHost.h>
#include <Security/SecRequirement.h>
#include <Security/SecTask.h>

/* Authorization */
#include <Security/Authorization.h>
#include <Security/AuthorizationTags.h>
#include <Security/AuthorizationDB.h>

/* CMS */
#include <Security/CMSDecoder.h>
#include <Security/CMSEncoder.h>

/* Secure Transport */
#include <Security/CipherSuite.h>
#include <Security/SecureTransport.h>

#ifdef __BLOCKS__
#include <Security/SecTransform.h>
#include <Security/SecCustomTransform.h>
#include <Security/SecDecodeTransform.h>
#include <Security/SecDigestTransform.h>
#include <Security/SecEncodeTransform.h>
#include <Security/SecEncryptTransform.h>
#include <Security/SecSignVerifyTransform.h>
#include <Security/SecReadTransform.h>
#endif

/* DER */
#include <Security/oids.h>

#endif // SEC_OS_OSX

#endif // _SECURITY_H_
// ==========  Security.framework/Headers/SecProtocolObject.h
/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef SecProtocolObject_h
#define SecProtocolObject_h

#include <sys/cdefs.h>
#include <os/object.h>

#if OS_OBJECT_USE_OBJC
#  define SEC_OBJECT_DECL(type) OS_OBJECT_DECL(type)
#else // OS_OBJECT_USE_OBJC
#  define SEC_OBJECT_DECL(type)                \
struct type;                        \
typedef    struct type *type##_t
#endif // OS_OBJECT_USE_OBJC

#if __has_feature(assume_nonnull)
#  define SEC_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#  define SEC_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else // !__has_feature(assume_nonnull)
#  define SEC_ASSUME_NONNULL_BEGIN
#  define SEC_ASSUME_NONNULL_END
#endif // !__has_feature(assume_nonnull)

#if defined(__OBJC__) && __has_attribute(ns_returns_retained)
#  define SEC_RETURNS_RETAINED __attribute__((__ns_returns_retained__))
#else // __OBJC__ && ns_returns_retained
#  define SEC_RETURNS_RETAINED
#endif // __OBJC__ && ns_returns_retained

#if !OS_OBJECT_USE_OBJC_RETAIN_RELEASE
__BEGIN_DECLS
__attribute__((visibility("default"))) void *sec_retain(void *obj);
__attribute__((visibility("default"))) void sec_release(void *obj);
__END_DECLS
#else // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE
#undef sec_retain
#undef sec_release
#define sec_retain(object) [(object) retain]
#define sec_release(object) [(object) release]
#endif // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

#ifndef SEC_OBJECT_IMPL
/*!
 * A `sec_object` is a generic, ARC-able type wrapper for common CoreFoundation Security types.
 */
SEC_OBJECT_DECL(sec_object);
#endif // !SEC_OBJECT_IMPL

#endif // SecProtocolObject_h
// ==========  Security.framework/Headers/SecCertificate.h
/*
 * Copyright (c) 2002-2017 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
     @header SecCertificate
    The functions provided in SecCertificate.h implement and manage a
    particular type of keychain item that represents a X.509 public key
    certificate. You can store a certificate in a keychain, but a
    certificate can also be a transient object.

     You can use a certificate as a keychain item in most functions.
*/

#ifndef _SECURITY_SECCERTIFICATE_H_
#define _SECURITY_SECCERTIFICATE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFError.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <Security/SecBase.h>

#if SEC_OS_OSX
#define _SECURITY_VERSION_GREATER_THAN_57610_

#include <Security/cssmtype.h>
#include <Security/x509defs.h>
#endif // SEC_OS_OSX

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
 @function SecCertificateGetTypeID
 @abstract Returns the type identifier of SecCertificate instances.
 @result The CFTypeID of SecCertificate instances.
 */
CFTypeID SecCertificateGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
 @function SecCertificateCreateWithData
 @abstract Create a certificate given it's DER representation as a CFData.
 @param allocator CFAllocator to allocate the certificate with.
 @param data DER encoded X.509 certificate.
 @result Return NULL if the passed-in data is not a valid DER-encoded
 X.509 certificate, return a SecCertificateRef otherwise.
 */
__nullable
SecCertificateRef SecCertificateCreateWithData(CFAllocatorRef __nullable allocator, CFDataRef data)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
 @function SecCertificateCopyData
 @abstract Return the DER representation of an X.509 certificate.
 @param certificate SecCertificate object created with
 SecCertificateCreateWithData().
 @result DER encoded X.509 certificate.
 */
CFDataRef SecCertificateCopyData(SecCertificateRef certificate)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
 @function SecCertificateCopySubjectSummary
 @abstract Return a simple string which hopefully represents a human
 understandable summary.
 @param certificate  A reference to the certificate from which to derive
 the subject summary string.
 @discussion All the data in this string comes from the certificate itself
 and thus it's in whatever language the certificate itself is in.
 @result A CFStringRef which the caller should CFRelease() once it's no
 longer needed.
 */
__nullable
CFStringRef SecCertificateCopySubjectSummary(SecCertificateRef certificate)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
 @function SecCertificateCopyCommonName
 @abstract Retrieves the common name of the subject of a given certificate.
 @param certificate A reference to the certificate from which to retrieve the common name.
 @param commonName On return, a reference to the common name. Your code must release this reference by calling the CFRelease function.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion All the data in this string comes from the certificate itself, and thus it's in whatever language the certificate itself is in.
 Note that the certificate's common name field may not be present, or may be inadequate to describe the certificate; for display purposes,
 you should consider using SecCertificateCopySubjectSummary instead of this function.
 */
OSStatus SecCertificateCopyCommonName(SecCertificateRef certificate, CFStringRef * __nonnull CF_RETURNS_RETAINED commonName)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_10_3);

/*!
 @function SecCertificateCopyEmailAddresses
 @abstract Returns an array of zero or more email addresses for the subject of a given certificate.
 @param certificate A reference to the certificate from which to retrieve the email addresses.
 @param emailAddresses On return, an array of zero or more CFStringRef elements corresponding to each email address found.
 Your code must release this array reference by calling the CFRelease function.
 @result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecCertificateCopyEmailAddresses(SecCertificateRef certificate, CFArrayRef * __nonnull CF_RETURNS_RETAINED emailAddresses)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_10_3);

/*!
 @function SecCertificateCopyNormalizedIssuerSequence
 @abstract Return the certificate's normalized issuer
 @param certificate The certificate from which to get values
 @discussion The issuer is a sequence in the format used by SecItemCopyMatching.  The content returned is a DER-encoded X.509 distinguished name. For a display version of the issuer, call SecCertificateCopyValues. The caller must CFRelease the value returned.
 */
__nullable
CFDataRef SecCertificateCopyNormalizedIssuerSequence(SecCertificateRef certificate)
    __OSX_AVAILABLE_STARTING(__MAC_10_12_4, __IPHONE_10_3);

/*!
 @function SecCertificateCopyNormalizedSubjectSequence
 @abstract Return the certificate's normalized subject
 @param certificate The certificate from which to get values
 @discussion The subject is a sequence in the format used by SecItemCopyMatching. The content returned is a DER-encoded X.509 distinguished name. For a display version of the subject, call SecCertificateCopyValues. The caller must CFRelease the value returned.
 */
__nullable
CFDataRef SecCertificateCopyNormalizedSubjectSequence(SecCertificateRef certificate)
    __OSX_AVAILABLE_STARTING(__MAC_10_12_4, __IPHONE_10_3);

/*!
 @function SecCertificateCopyKey
 @abstract Retrieves the public key for a given certificate.
 @param certificate A reference to the certificate from which to retrieve the public key.
 @result A reference to the public key for the specified certificate. Your code must release this reference by calling the CFRelease function. If the public key has an encoding issue or uses an unsupported algorithm, the returned reference will be null.
 @discussion RSA and ECDSA public keys are supported. All other public key algorithms are unsupported.
 */
__nullable CF_RETURNS_RETAINED
SecKeyRef SecCertificateCopyKey(SecCertificateRef certificate)
    API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

#if TARGET_OS_IPHONE
/*!
 @function SecCertificateCopyPublicKey
 @abstract Retrieves the public key for a given certificate.
 @param certificate A reference to the certificate from which to retrieve the public key.
 @result A reference to the public key for the specified certificate. Your code must release this reference by calling the CFRelease function.
 @discussion NOTE: Deprecated in iOS 12.0; use SecCertificateCopyKey instead for cross-platform availability.
 */
__nullable
SecKeyRef SecCertificateCopyPublicKey(SecCertificateRef certificate)
    API_DEPRECATED_WITH_REPLACEMENT("SecCertificateCopyKey", ios(10.3, 12.0)) API_UNAVAILABLE(macos, uikitformac);
#endif

#if TARGET_OS_OSX
/*!
 @function SecCertificateCopyPublicKey
 @abstract Retrieves the public key for a given certificate.
 @param certificate A reference to the certificate from which to retrieve the public key.
 @param key On return, a reference to the public key for the specified certificate. Your code must release this reference by calling the CFRelease function.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion NOTE: Deprecated in macOS 10.14; use SecCertificateCopyKey instead for cross-platform availability.
 */
OSStatus SecCertificateCopyPublicKey(SecCertificateRef certificate, SecKeyRef * __nonnull CF_RETURNS_RETAINED key)
    API_DEPRECATED_WITH_REPLACEMENT("SecCertificateCopyKey", macos(10.3, 10.14)) API_UNAVAILABLE(ios, tvos, watchos, uikitformac);
#endif

/*!
 @function SecCertificateCopySerialNumberData
 @abstract Return the certificate's serial number.
 @param certificate The certificate from which to get values.
 @param error An optional pointer to a CFErrorRef which will be set on return from the function if an error occurred. If not NULL, the caller is responsible for releasing the CFErrorRef.
 @discussion Return the content of a DER-encoded integer (without the tag and length fields) for this certificate's serial number. The caller must CFRelease the value returned.
 */
__nullable
CFDataRef SecCertificateCopySerialNumberData(SecCertificateRef certificate, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);

#if TARGET_OS_IPHONE
/*!
 @function SecCertificateCopySerialNumber
 @abstract Return the certificate's serial number.
 @param certificate The certificate from which to get values.
 @discussion Return the content of a DER-encoded integer (without the tag and length fields) for this certificate's serial number. The caller must CFRelease the value returned. NOTE: Deprecated in iOS 11.0; use SecCertificateCopySerialNumberData instead for cross-platform availability.
 */
__nullable
CFDataRef SecCertificateCopySerialNumber(SecCertificateRef certificate)
    API_DEPRECATED_WITH_REPLACEMENT("SecCertificateCopySerialNumberData", ios(10.3, 11.0)) API_UNAVAILABLE(macos, uikitformac);
#endif

#if TARGET_OS_OSX
/*!
 @function SecCertificateCopySerialNumber
 @abstract Return the certificate's serial number.
 @param certificate The certificate from which to get values.
 @param error An optional pointer to a CFErrorRef which will be set on return from the function if an error occurred. If not NULL, the caller is responsible for releasing the CFErrorRef.
 @discussion Return the content of a DER-encoded integer (without the tag and length fields) for this certificate's serial number. The caller must CFRelease the value returned. NOTE: Deprecated in macOS 10.13; use SecCertificateCopySerialNumberData instead for cross-platform availability.
 */
__nullable
CFDataRef SecCertificateCopySerialNumber(SecCertificateRef certificate, CFErrorRef *error)
    API_DEPRECATED_WITH_REPLACEMENT("SecCertificateCopySerialNumberData", macos(10.7, 10.13)) API_UNAVAILABLE(ios, tvos, watchos, uikitformac);
#endif

/*
 * Legacy functions (OS X only)
 */
#if SEC_OS_OSX
/*!
    @enum CertificateItemAttributes
    @abstract Indicates the type of a certificate item attribute.
    @constant kSecSubjectItemAttr Indicates a DER-encoded subject distinguished name.
    @constant kSecIssuerItemAttr Indicates a DER-encoded issuer distinguished name.
    @constant kSecSerialNumberItemAttr Indicates a DER-encoded certificate serial number (without the tag and length).
    @constant kSecPublicKeyHashItemAttr Indicates a public key hash.
    @constant kSecSubjectKeyIdentifierItemAttr Indicates a subject key identifier.
    @constant kSecCertTypeItemAttr Indicates a certificate type.
    @constant kSecCertEncodingItemAttr Indicates a certificate encoding.
*/
enum
{
    kSecSubjectItemAttr              = 'subj',
    kSecIssuerItemAttr               = 'issu',
    kSecSerialNumberItemAttr         = 'snbr',
    kSecPublicKeyHashItemAttr        = 'hpky',
    kSecSubjectKeyIdentifierItemAttr = 'skid',
    kSecCertTypeItemAttr             = 'ctyp',
    kSecCertEncodingItemAttr         = 'cenc'
} /*DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER*/;

#pragma mark ---- Certificate Operations ----

/*!
    @function SecCertificateCreateFromData
    @abstract Creates a certificate based on the input data, type, and encoding.
    @param data A pointer to the certificate data.
    @param type The certificate type as defined in cssmtype.h.
    @param encoding The certificate encoding as defined in cssmtype.h.
    @param certificate On return, a reference to the newly created certificate.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This API is deprecated in 10.7  Please use the SecCertificateCreateWithData API instead.
*/
OSStatus SecCertificateCreateFromData(const CSSM_DATA *data, CSSM_CERT_TYPE type, CSSM_CERT_ENCODING encoding, SecCertificateRef * __nonnull CF_RETURNS_RETAINED certificate)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateAddToKeychain
    @abstract Adds a certificate to the specified keychain.
    @param certificate A reference to a certificate.
    @param keychain A reference to the keychain in which to add the certificate. Pass NULL to add the certificate to the default keychain.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is successful only if the certificate was created using the SecCertificateCreateFromData or
    SecCertificateCreateWithData functions, and the certificate has not yet been added to the specified keychain.
*/
OSStatus SecCertificateAddToKeychain(SecCertificateRef certificate, SecKeychainRef __nullable keychain)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/*!
    @function SecCertificateGetData
    @abstract Retrieves the data for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the data.
    @param data On return, the CSSM_DATA structure pointed to by data is filled in. You must allocate the space for a CSSM_DATA structure before calling this function. This data pointer is only guaranteed to remain valid as long as the certificate remains unchanged and valid.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This API is deprecated in 10.7. Please use the SecCertificateCopyData API instead.
*/
OSStatus SecCertificateGetData(SecCertificateRef certificate, CSSM_DATA_PTR data)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateGetType
    @abstract Retrieves the type for a given certificate.
    @param certificate A reference to the certificate from which to obtain the type.
    @param certificateType On return, the certificate type of the certificate. Certificate types are defined in cssmtype.h.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This API is deprecated in 10.7. Please use the SecCertificateCopyValues API instead.
*/
OSStatus SecCertificateGetType(SecCertificateRef certificate, CSSM_CERT_TYPE *certificateType)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateGetSubject
    @abstract Retrieves the subject name for a given certificate.
    @param certificate A reference to the certificate from which to obtain the subject name.
    @param subject On return, a pointer to a CSSM_X509_NAME struct which contains the subject's X.509 name (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Prior to Mac OS X 10.5, this function did not return any output in the subject parameter. Your code should check the returned pointer value (in addition to the function result) before attempting to use it.
        For example:
        const CSSM_X509_NAME *subject = NULL;
        OSStatus status = SecCertificateGetSubject(certificate, &subject);
        if ( (status == errSecSuccess) && (subject != NULL) ) {
            // subject is valid
        }
       This API is deprecated in 10.7. Please use the SecCertificateCopyValues API instead.
*/
OSStatus SecCertificateGetSubject(SecCertificateRef certificate, const CSSM_X509_NAME * __nullable * __nonnull subject)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateGetIssuer
    @abstract Retrieves the issuer name for a given certificate.
    @param certificate A reference to the certificate from which to obtain the issuer name.
    @param issuer On return, a pointer to a CSSM_X509_NAME struct which contains the issuer's X.509 name (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Prior to Mac OS X 10.5, this function did not return any output in the issuer parameter. Your code should check the returned pointer value (in addition to the function result) before attempting to use it.
        For example:
        const CSSM_X509_NAME *issuer = NULL;
        OSStatus status = SecCertificateGetIssuer(certificate, &issuer);
        if ( (status == errSecSuccess) && (issuer != NULL) ) {
            // issuer is valid
        }
        This API is deprecated in 10.7. Please use the SecCertificateCopyValues API instead.
*/
OSStatus SecCertificateGetIssuer(SecCertificateRef certificate, const CSSM_X509_NAME * __nullable * __nonnull issuer)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateGetCLHandle
    @abstract Retrieves the certificate library handle for a given certificate.
    @param certificate A reference to the certificate from which to obtain the certificate library handle.
    @param clHandle On return, the certificate library handle of the given certificate. This handle remains valid at least as long as the certificate does.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This API is deprecated in 10.7. Please use the SecCertificateCopyValues API instead.
*/
OSStatus SecCertificateGetCLHandle(SecCertificateRef certificate, CSSM_CL_HANDLE *clHandle)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateGetAlgorithmID
    @abstract Retrieves the algorithm identifier for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the algorithm identifier.
    @param algid On return, a pointer to a CSSM_X509_ALGORITHM_IDENTIFIER struct which identifies the algorithm for this certificate (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    discussion This API is deprecated in 10.7. Please use the SecCertificateCopyValues API instead.
*/
OSStatus SecCertificateGetAlgorithmID(SecCertificateRef certificate, const CSSM_X509_ALGORITHM_IDENTIFIER * __nullable * __nonnull algid)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateCopyPreference
    @abstract Returns the preferred certificate for the specified name and key usage. If a preferred certificate does not exist for the specified name and key usage, NULL is returned.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate is requested.
    @param keyUsage A CSSM_KEYUSE key usage value, as defined in cssmtype.h. Pass 0 to ignore this parameter.
    @param certificate On return, a reference to the preferred certificate, or NULL if none was found. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will typically be used to obtain the preferred encryption certificate for an email recipient.
    This API is deprecated in 10.7. Please use the SecCertificateCopyPreferred API instead.
*/
OSStatus SecCertificateCopyPreference(CFStringRef name, uint32 keyUsage, SecCertificateRef * __nonnull CF_RETURNS_RETAINED certificate)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateCopyPreferred
    @abstract Returns the preferred certificate for the specified name and key usage. If a preferred certificate does not exist for the specified name and key usage, NULL is returned.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate is requested.
    @param keyUsage A CFArrayRef value, containing items defined in SecItem.h  Pass NULL to ignore this parameter. (kSecAttrCanEncrypt, kSecAttrCanDecrypt, kSecAttrCanDerive, kSecAttrCanSign, kSecAttrCanVerify, kSecAttrCanWrap, kSecAttrCanUnwrap)
    @result On return, a reference to the preferred certificate, or NULL if none was found. You are responsible for releasing this reference by calling the CFRelease function.
    @discussion This function will typically be used to obtain the preferred encryption certificate for an email recipient. If a preferred certificate has not been set
    for the supplied name, the returned reference will be NULL. Your code should then perform a search for possible certificates, using the SecItemCopyMatching API.
 */
__nullable
SecCertificateRef SecCertificateCopyPreferred(CFStringRef name, CFArrayRef __nullable keyUsage)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function SecCertificateSetPreference
    @abstract Sets the preferred certificate for a specified name, key usage, and date.
    @param certificate A reference to the certificate which will be preferred.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate will be associated.
    @param keyUsage A CSSM_KEYUSE key usage value, as defined in cssmtype.h. Pass 0 to avoid specifying a particular key usage.
    @param date (optional) A date reference. If supplied, the preferred certificate will be changed only if this date is later than the currently saved setting. Pass NULL if this preference should not be restricted by date.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will typically be used to set the preferred encryption certificate for an email recipient, either manually (when encrypting email to a recipient) or automatically upon receipt of encrypted email.
    This API is deprecated in 10.7. Plese use the SecCertificateSetPreferred API instead.
*/
OSStatus SecCertificateSetPreference(SecCertificateRef certificate, CFStringRef name, uint32 keyUsage, CFDateRef __nullable date)
    DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecCertificateSetPreferred
    @abstract Sets the preferred certificate for a specified name and optional key usage.
    @param certificate A reference to the preferred certificate. If NULL is passed, any existing preference for the specified name is cleared instead.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate will be associated.
    @param keyUsage A CFArrayRef value, containing items defined in SecItem.h  Pass NULL to ignore this parameter. (kSecAttrCanEncrypt, kSecAttrCanDecrypt, kSecAttrCanDerive, kSecAttrCanSign, kSecAttrCanVerify, kSecAttrCanWrap, kSecAttrCanUnwrap)
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will typically be used to set the preferred encryption certificate for an email recipient, either manually (when encrypting email to a recipient)
    or automatically upon receipt of encrypted email.
*/
OSStatus SecCertificateSetPreferred(SecCertificateRef __nullable certificate, CFStringRef name, CFArrayRef __nullable keyUsage)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
 @typedef SecKeyUsage
 @abstract Flags to indicate key usages in the KeyUsage extension of a certificate
 @constant kSecKeyUsageUnspecified No KeyUsage extension in certificate.
 @constant kSecKeyUsageDigitalSignature DigitalSignature bit set in KeyUsage extension.
 @constant kSecKeyUsageNonRepudiation NonRepudiation bit set in KeyUsage extension.
 @constant kSecKeyUsageContentCommitment ContentCommitment bit set in KeyUsage extension.
 @constant kSecKeyUsageKeyEncipherment KeyEncipherment bit set in KeyUsage extension.
 @constant kSecKeyUsageDataEncipherment DataEncipherment bit set in KeyUsage extension.
 @constant kSecKeyUsageKeyAgreement KeyAgreement bit set in KeyUsage extension.
 @constant kSecKeyUsageKeyCertSign KeyCertSign bit set in KeyUsage extension.
 @constant kSecKeyUsageCRLSign CRLSign bit set in KeyUsage extension.
 @constant kSecKeyUsageEncipherOnly EncipherOnly bit set in KeyUsage extension.
 @constant kSecKeyUsageDecipherOnly DecipherOnly bit set in KeyUsage extension.
 @constant kSecKeyUsageCritical KeyUsage extension is marked critical.
 @constant kSecKeyUsageAll For masking purposes, all SecKeyUsage values.
 */
typedef CF_OPTIONS(uint32_t, SecKeyUsage) {
    kSecKeyUsageUnspecified      = 0u,
    kSecKeyUsageDigitalSignature = 1u << 0,
    kSecKeyUsageNonRepudiation   = 1u << 1,
    kSecKeyUsageContentCommitment= 1u << 1,
    kSecKeyUsageKeyEncipherment  = 1u << 2,
    kSecKeyUsageDataEncipherment = 1u << 3,
    kSecKeyUsageKeyAgreement     = 1u << 4,
    kSecKeyUsageKeyCertSign      = 1u << 5,
    kSecKeyUsageCRLSign          = 1u << 6,
    kSecKeyUsageEncipherOnly     = 1u << 7,
    kSecKeyUsageDecipherOnly     = 1u << 8,
    kSecKeyUsageCritical         = 1u << 31,
    kSecKeyUsageAll              = 0x7FFFFFFFu
};

/*!
 @enum kSecPropertyKey
 @abstract Constants used to access dictionary entries returned by SecCertificateCopyValues
 @constant kSecPropertyKeyType The type of the entry
 @constant kSecPropertyKeyLabel The label of the entry
 @constant kSecPropertyKeyLocalizedLabel The localized label of the entry
 @constant kSecPropertyKeyValue The value of the entry
 */

extern const CFStringRef kSecPropertyKeyType __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyKeyLabel __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyKeyLocalizedLabel __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyKeyValue __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @enum kSecPropertyType
    @abstract Public Constants for property list values returned by SecCertificateCopyValues
    @discussion Note that kSecPropertyTypeTitle and kSecPropertyTypeError are defined in SecTrust.h
*/
extern const CFStringRef kSecPropertyTypeWarning __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeSuccess __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeSection __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeData __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeString __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeURL __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeDate __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPropertyTypeArray API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);
extern const CFStringRef kSecPropertyTypeNumber API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @function SecCertificateCopyValues
    @abstract        Creates a dictionary that represents a certificate's contents.
    @param certificate The certificate from which to get values
    @param keys        An array of string OID values, or NULL. If present, this is
                    the subset of values from the certificate to return. If NULL,
                    all values will be returned. Only OIDs that are top level keys
                    in the returned dictionary can be specified. Unknown OIDs are
                    ignored.
    @param error    An optional pointer to a CFErrorRef. This value is
                    set if an error occurred.  If not NULL the caller is
                    responsible for releasing the CFErrorRef.
    @discussion        The keys array will contain all of the keys used in the
                    returned dictionary. The top level keys in the returned
                    dictionary are OIDs, many of which are found in SecCertificateOIDs.h.
                    Each entry that is returned is itself a dictionary with four
                    entries, whose keys are kSecPropertyKeyType, kSecPropertyKeyLabel,
                    kSecPropertyKeyLocalizedLabel, kSecPropertyKeyValue. The label
                    entries may contain a descriptive (localized) string, or an
                    OID string. The kSecPropertyKeyType describes the type in the
                    value entry. The value entry may be any CFType, although it
                    is usually a CFStringRef, CFArrayRef or a CFDictionaryRef.
*/
__nullable
CFDictionaryRef SecCertificateCopyValues(SecCertificateRef certificate, CFArrayRef __nullable keys, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function             SecCertificateCopyLongDescription
    @abstract            Return the long description of a certificate
    @param alloc         The CFAllocator which should be used to allocate
                        memory for the dictionary and its storage for values. This
                        parameter may be NULL in which case the current default
                        CFAllocator is used. If this reference is not a valid
                        CFAllocator, the behavior is undefined.
    @param certificate    The certificate from which to retrieve the long description
    @param    error        An optional pointer to a CFErrorRef. This value is
                        set if an error occurred.  If not NULL the caller is
                        responsible for releasing the CFErrorRef.
    @result                A CFStringRef of the long description or NULL. If NULL and the error
                        parameter is supplied the error will be returned in the error parameter
    @discussion            Note that the format of this string may change in the future
*/

__nullable
CFStringRef SecCertificateCopyLongDescription(CFAllocatorRef __nullable alloc, SecCertificateRef certificate, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function             SecCertificateCopyShortDescription
    @abstract            Return the short description of a certificate
    @param alloc         The CFAllocator which should be used to allocate
                        memory for the dictionary and its storage for values. This
                        parameter may be NULL in which case the current default
                        CFAllocator is used. If this reference is not a valid
                        CFAllocator, the behavior is undefined.
    @param certificate    The certificate from which to retrieve the short description
    @param    error        An optional pointer to a CFErrorRef. This value is
                        set if an error occurred.  If not NULL the caller is
                        responsible for releasing the CFErrorRef.
    @result                A CFStringRef of the short description or NULL. If NULL and the error
                        parameter is supplied the error will be returned in the error parameter
 @discussion            Note that the format of this string may change in the future
*/

__nullable
CFStringRef SecCertificateCopyShortDescription(CFAllocatorRef __nullable alloc, SecCertificateRef certificate, CFErrorRef *error)
        __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function            SecCertificateCopyNormalizedIssuerContent
    @abstract            Return the certificate's normalized issuer
    @param certificate    The certificate from which to get values
    @param error        An optional pointer to a CFErrorRef. This value is
                        set if an error occurred.  If not NULL the caller is
                        responsible for releasing the CFErrorRef.
    @discussion            The issuer is a sequence in the format used by
                        SecItemCopyMatching.  The content returned is a DER-encoded
                        X.509 distinguished name. For a display version of the issuer,
                        call SecCertificateCopyValues. The caller must CFRelease
                        the value returned.
*/

__nullable
CFDataRef SecCertificateCopyNormalizedIssuerContent(SecCertificateRef certificate, CFErrorRef *error)
        __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_12_4, __IPHONE_NA, __IPHONE_NA, "SecCertificateCopyNormalizedIssuerContent is deprecated. Use SecCertificateCopyNormalizedIssuerSequence instead.");

/*!
    @function           SecCertificateCopyNormalizedSubjectContent
    @abstract           Return the certificate's normalized subject
    @param certificate  The certificate from which to get values
    @param error        An optional pointer to a CFErrorRef. This value is
                        set if an error occurred.  If not NULL the caller is
                        responsible for releasing the CFErrorRef.
    @discussion         The subject is a sequence in the format used by
                        SecItemCopyMatching. The content returned is a DER-encoded
                        X.509 distinguished name. For a display version of the subject,
                        call SecCertificateCopyValues. The caller must CFRelease
                        the value returned.
*/

__nullable
CFDataRef SecCertificateCopyNormalizedSubjectContent(SecCertificateRef certificate, CFErrorRef *error)
        __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_12_4, __IPHONE_NA, __IPHONE_NA, "SecCertificateCopyNormalizedSubjectContent is deprecated. Use SecCertificateCopyNormalizedSubjectSequence instead.");


#endif /* SEC_OS_OSX */

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECCERTIFICATE_H_ */
// ==========  Security.framework/Headers/SecProtocolTypes.h
/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef SecProtocolTypes_h
#define SecProtocolTypes_h

#include <Security/SecProtocolObject.h>
#include <Security/SecTrust.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>
#include <Security/CipherSuite.h>
#include <Security/SecBase.h>

#ifndef SEC_OBJECT_IMPL
/*!
 * These are os_object compatible and ARC-able wrappers around existing CoreFoundation
 * Security types, including: SecTrustRef, SecIdentityRef, and SecCertificateRef. They allow
 * clients to use these types in os_object-type APIs and data structures. The underlying
 * CoreFoundation types may be extracted and used by clients as needed.
 */
SEC_OBJECT_DECL(sec_trust);
SEC_OBJECT_DECL(sec_identity);
SEC_OBJECT_DECL(sec_certificate);
#endif // !SEC_OBJECT_IMPL

/*!
 * @enum tls_protocol_version_t enumeration
 * @abstract Enumerations for the set of supported TLS and DTLS protocol versions.
 *
 * @constant tls_protocol_version_TLSv10 TLS 1.0 [https://tools.ietf.org/html/rfc4346]
 * @constant tls_protocol_version_TLSv11 TLS 1.1 [https://tools.ietf.org/html/rfc2246]
 * @constant tls_protocol_version_TLSv12 TLS 1.2 [https://tools.ietf.org/html/rfc5246]
 * @constant tls_protocol_version_TLSv13 TLS 1.3 [https://tools.ietf.org/html/rfc8446]
 * @constant tls_protocol_version_DTLSv10 DTLS 1.0 [https://tools.ietf.org/html/rfc4347]
 * @constant tls_protocol_version_DTLSv12 DTLS 1.2 [https://tools.ietf.org/html/rfc6347]
 */
typedef CF_ENUM(uint16_t, tls_protocol_version_t) {
    tls_protocol_version_TLSv10 CF_SWIFT_NAME(TLSv10) = 0x0301,
    tls_protocol_version_TLSv11 CF_SWIFT_NAME(TLSv11) = 0x0302,
    tls_protocol_version_TLSv12 CF_SWIFT_NAME(TLSv12) = 0x0303,
    tls_protocol_version_TLSv13 CF_SWIFT_NAME(TLSv13) = 0x0304,
    tls_protocol_version_DTLSv10 CF_SWIFT_NAME(DTLSv10) = 0xfeff,
    tls_protocol_version_DTLSv12 CF_SWIFT_NAME(DTLSv12) = 0xfefd,
};

/*!
 * @enum tls_ciphersuite_t enumeration
 * @abstract Enumerations for the set of supported TLS and DTLS ciphersuites.
 *
 * See https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4
 * for ciphersuite codepoint allocations and reference RFCs.
 *
 * @constant tls_ciphersuite_RSA_WITH_3DES_EDE_CBC_SHA
 * @constant tls_ciphersuite_RSA_WITH_AES_128_CBC_SHA
 * @constant tls_ciphersuite_RSA_WITH_AES_256_CBC_SHA
 * @constant tls_ciphersuite_RSA_WITH_AES_128_GCM_SHA256
 * @constant tls_ciphersuite_RSA_WITH_AES_256_GCM_SHA384
 * @constant tls_ciphersuite_RSA_WITH_AES_128_CBC_SHA256
 * @constant tls_ciphersuite_RSA_WITH_AES_256_CBC_SHA256
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_128_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_256_CBC_SHA
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_128_CBC_SHA256
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_256_CBC_SHA384
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_128_GCM_SHA256
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_AES_256_GCM_SHA384
 * @constant tls_ciphersuite_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256
 * @constant tls_ciphersuite_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256
 * @constant tls_ciphersuite_AES_128_GCM_SHA256
 * @constant tls_ciphersuite_AES_256_GCM_SHA384
 * @constant tls_ciphersuite_CHACHA20_POLY1305_SHA256
 */
typedef CF_ENUM(uint16_t, tls_ciphersuite_t) {
    tls_ciphersuite_RSA_WITH_3DES_EDE_CBC_SHA CF_SWIFT_NAME(RSA_WITH_3DES_EDE_CBC_SHA) = 0x000A,
    tls_ciphersuite_RSA_WITH_AES_128_CBC_SHA CF_SWIFT_NAME(RSA_WITH_AES_128_CBC_SHA) = 0x002F,
    tls_ciphersuite_RSA_WITH_AES_256_CBC_SHA CF_SWIFT_NAME(RSA_WITH_AES_256_CBC_SHA) = 0x0035,
    tls_ciphersuite_RSA_WITH_AES_128_GCM_SHA256 CF_SWIFT_NAME(RSA_WITH_AES_128_GCM_SHA256) = 0x009C,
    tls_ciphersuite_RSA_WITH_AES_256_GCM_SHA384 CF_SWIFT_NAME(RSA_WITH_AES_256_GCM_SHA384) = 0x009D,
    tls_ciphersuite_RSA_WITH_AES_128_CBC_SHA256 CF_SWIFT_NAME(RSA_WITH_AES_128_CBC_SHA256) = 0x003C,
    tls_ciphersuite_RSA_WITH_AES_256_CBC_SHA256 CF_SWIFT_NAME(RSA_WITH_AES_256_CBC_SHA256) = 0x003D,
    tls_ciphersuite_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA CF_SWIFT_NAME(ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA) = 0xC008,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_CBC_SHA CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_128_CBC_SHA) = 0xC009,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_CBC_SHA CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_256_CBC_SHA) = 0xC00A,
    tls_ciphersuite_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA CF_SWIFT_NAME(ECDHE_RSA_WITH_3DES_EDE_CBC_SHA) = 0xC012,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_128_CBC_SHA CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_128_CBC_SHA) = 0xC013,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_256_CBC_SHA CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_256_CBC_SHA) = 0xC014,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_128_CBC_SHA256) = 0xC023,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_256_CBC_SHA384) = 0xC024,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_128_CBC_SHA256 CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_128_CBC_SHA256) = 0xC027,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_256_CBC_SHA384 CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_256_CBC_SHA384) = 0xC028,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_128_GCM_SHA256) = 0xC02B,
    tls_ciphersuite_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 CF_SWIFT_NAME(ECDHE_ECDSA_WITH_AES_256_GCM_SHA384) = 0xC02C,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_128_GCM_SHA256 CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_128_GCM_SHA256) = 0xC02F,
    tls_ciphersuite_ECDHE_RSA_WITH_AES_256_GCM_SHA384 CF_SWIFT_NAME(ECDHE_RSA_WITH_AES_256_GCM_SHA384) = 0xC030,
    tls_ciphersuite_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256 CF_SWIFT_NAME(ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256) = 0xCCA8,
    tls_ciphersuite_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 CF_SWIFT_NAME(ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256) = 0xCCA9,
    tls_ciphersuite_AES_128_GCM_SHA256 CF_SWIFT_NAME(AES_128_GCM_SHA256) = 0x1301,
    tls_ciphersuite_AES_256_GCM_SHA384 CF_SWIFT_NAME(AES_256_GCM_SHA384) = 0x1302,
    tls_ciphersuite_CHACHA20_POLY1305_SHA256 CF_SWIFT_NAME(CHACHA20_POLY1305_SHA256) = 0x1303,
};

/*!
 * @enum tls_ciphersuite_group_t enumeration
 * @abstract Convenience ciphersuite groups that collate ciphersuites of comparable security
 *  properties into a single alias.
 *
 * @constant tls_ciphersuite_group_default
 * @constant tls_ciphersuite_group_compatibility
 * @constant tls_ciphersuite_group_legacy
 * @constant tls_ciphersuite_group_ats
 * @constant tls_ciphersuite_group_ats_compatibility
 */
typedef CF_ENUM(uint16_t, tls_ciphersuite_group_t) {
    tls_ciphersuite_group_default,
    tls_ciphersuite_group_compatibility,
    tls_ciphersuite_group_legacy,
    tls_ciphersuite_group_ats,
    tls_ciphersuite_group_ats_compatibility,
};

/*!
 * @enum SSLProtocol enumeration
 * @abstract Enumerations for the set of supported TLS and DTLS protocol versions.
 *
 * @note This enumeration is deprecated. Use `tls_protocol_version_t` instead.
 */
typedef CF_ENUM(int, SSLProtocol) {
    kSSLProtocolUnknown CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 0,
    kTLSProtocol1 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 4,
    kTLSProtocol11 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 7,
    kTLSProtocol12 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 8,
    kDTLSProtocol1 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 9,
    kTLSProtocol13 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 10,
    kDTLSProtocol12 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 11,
    kTLSProtocolMaxSupported CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 999,
    kSSLProtocol2 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 1,
    kSSLProtocol3 CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 2,
    kSSLProtocol3Only CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 3,
    kTLSProtocol1Only CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 5,
    kSSLProtocolAll CF_ENUM_DEPRECATED(10_2, 10_15, 5_0, 13_0) = 6,
};

__BEGIN_DECLS

SEC_ASSUME_NONNULL_BEGIN

/*!
 * @function sec_trust_create
 *
 * @abstract
 *      Create an ARC-able `sec_trust_t` instance from a `SecTrustRef`.
 *
 * @param trust
 *      A `SecTrustRef` instance.
 *
 * @return a `sec_trust_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_trust_t
sec_trust_create(SecTrustRef trust);

/*!
 * @function sec_trust_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecTrustRef` instance.
 *
 * @param trust
 *      A `sec_trust_t` instance.
 *
 * @return The underlying `SecTrustRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SecTrustRef
sec_trust_copy_ref(sec_trust_t trust);

/*!
 * @function sec_identity_create
 *
 * @abstract
 *      Create an ARC-able `sec_identity_t` instance from a `SecIdentityRef`.
 *
 * @param identity
 *      A `SecIdentityRef` instance.
 *
 * @return a `sec_identity_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_identity_t
sec_identity_create(SecIdentityRef identity);

/*!
 * @function sec_identity_create_with_certificates
 *
 * @abstract
 *      Create an ARC-able `sec_identity_t` instance from a `SecIdentityRef` and
 *      array of SecCertificateRef instances.
 *
 * @param identity
 *      A `SecIdentityRef` instance.
 *
 * @param certificates
 *      An array of `SecCertificateRef` instances.
 *
 * @return a `sec_identity_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_identity_t
sec_identity_create_with_certificates(SecIdentityRef identity, CFArrayRef certificates);

#ifdef __BLOCKS__
/*!
 * @function sec_identity_access_certificates
 *
 * @abstract
 *      Access the certificates associated with the `sec_identity_t` instance.
 *
 * @param identity
 *      A `sec_identity_t` instance.
 *
 * @param handler
 *      A block to invoke one or more times with `sec_certificate_t` instances.
 *
 * @return Returns true if the peer certificates were accessible, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
sec_identity_access_certificates(sec_identity_t identity,
                                 void (^handler)(sec_certificate_t certificate));
#endif // __BLOCKS__

/*!
 * @function sec_identity_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecIdentityRef` instance.
 *
 * @param identity
 *      A `sec_identity_t` instance.
 *
 * @return The underlying `SecIdentityRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
_Nullable SecIdentityRef
sec_identity_copy_ref(sec_identity_t identity);

/*!
 * @function sec_identity_copy_certificates_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `CFArrayRef` container of `SecCertificateRef` types.
 *
 * @param identity
 *      A `sec_identity_t` instance.
 *
 * @return The underlying `CFArrayRef` container with `SecCertificateRef` instances.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
_Nullable CFArrayRef
sec_identity_copy_certificates_ref(sec_identity_t identity);

/*!
 * @function sec_certificate_create
 *
 * @abstract
 *      Create an ARC-able `sec_certificate_t` instance from a `SecCertificateRef`.
 *
 * @param certificate
 *      A `SecCertificateRef` instance.
 *
 * @return a `sec_certificate_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_certificate_t
sec_certificate_create(SecCertificateRef certificate);

/*!
 * @function sec_certificate_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecCertificateRef` instance.
 *
 * @param certificate
 *      A `sec_certificate_t` instance.
 *
 * @return The underlying `SecCertificateRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SecCertificateRef
sec_certificate_copy_ref(sec_certificate_t certificate);

SEC_ASSUME_NONNULL_END

__END_DECLS

#endif // SecProtocolTypes_h
// ==========  Security.framework/Headers/SecKey.h
/*
 * Copyright (c) 2006-2014,2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
	@header SecKey
	The functions provided in SecKey.h implement and manage a particular
    type of keychain item that represents a key.  A key can be stored in a
    keychain, but a key can also be a transient object.

	On OSX, you can use a SecKey as a SecKeychainItem in most functions.
*/

#ifndef _SECURITY_SECKEY_H_
#define _SECURITY_SECKEY_H_

#include <Availability.h>
#include <Security/SecBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <dispatch/dispatch.h>
#include <sys/types.h>

#if SEC_OS_OSX
#include <Security/SecAccess.h>
#include <Security/cssmtype.h>
#endif /* SEC_OS_OSX */

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

#if SEC_OS_OSX
/*!
	@enum KeyItemAttributeConstants
	@abstract Specifies keychain item attributes for keys.
    @constant kSecKeyKeyClass type uint32 (CSSM_KEYCLASS), value
    is one of CSSM_KEYCLASS_PUBLIC_KEY, CSSM_KEYCLASS_PRIVATE_KEY
    or CSSM_KEYCLASS_SESSION_KEY.
    @constant kSecKeyPrintName type blob, human readable name of
    the key.  Same as kSecLabelItemAttr for normal keychain items.
    @constant kSecKeyAlias type blob, currently unused.
    @constant kSecKeyPermanent type uint32, value is nonzero iff
    this key is permanent (stored in some keychain).  This is always
    1.
    @constant kSecKeyPrivate type uint32, value is nonzero iff this
    key is protected by a user login or a password, or both.
    @constant kSecKeyModifiable type uint32, value is nonzero iff
    attributes of this key can be modified.
    @constant kSecKeyLabel type blob, for private and public keys
    this contains the hash of the public key.  This is used to
    associate certificates and keys.  Its value matches the value
    of the kSecPublicKeyHashItemAttr of a certificate and it's used
    to construct an identity from a certificate and a key.
    For symmetric keys this is whatever the creator of the key
    passed in during the generate key call.
    @constant kSecKeyApplicationTag type blob, currently unused.
    @constant kSecKeyKeyCreator type data, the data points to a
    CSSM_GUID structure representing the moduleid of the csp owning
    this key.
    @constant kSecKeyKeyType type uint32, value is a CSSM_ALGORITHMS
    representing the algorithm associated with this key.
    @constant kSecKeyKeySizeInBits type uint32, value is the number
    of bits in this key.
    @constant kSecKeyEffectiveKeySize type uint32, value is the
    effective number of bits in this key.  For example a des key
    has a kSecKeyKeySizeInBits of 64 but a kSecKeyEffectiveKeySize
    of 56.
    @constant kSecKeyStartDate type CSSM_DATE.  Earliest date from
    which this key may be used.  If the value is all zeros or not
    present, no restriction applies.
    @constant kSecKeyEndDate type CSSM_DATE.  Latest date at
    which this key may be used.  If the value is all zeros or not
    present, no restriction applies.
    @constant kSecKeySensitive type uint32, iff value is nonzero
    this key cannot be wrapped with CSSM_ALGID_NONE.
    @constant kSecKeyAlwaysSensitive type uint32, value is nonzero
    iff this key has always been marked sensitive.
    @constant kSecKeyExtractable type uint32, value is nonzero iff
    this key can be wrapped.
    @constant kSecKeyNeverExtractable type uint32, value is nonzero
    iff this key was never marked extractable.
    @constant kSecKeyEncrypt type uint32, value is nonzero iff this
    key can be used in an encrypt operation.
    @constant kSecKeyDecrypt type uint32, value is nonzero iff this
    key can be used in a decrypt operation.
    @constant kSecKeyDerive type uint32, value is nonzero iff this
    key can be used in a deriveKey operation.
    @constant kSecKeySign type uint32, value is nonzero iff this
    key can be used in a sign operation.
    @constant kSecKeyVerify type uint32, value is nonzero iff this
    key can be used in a verify operation.
    @constant kSecKeySignRecover type uint32.
    @constant kSecKeyVerifyRecover type uint32.
    key can unwrap other keys.
    @constant kSecKeyWrap type uint32, value is nonzero iff this
    key can wrap other keys.
    @constant kSecKeyUnwrap type uint32, value is nonzero iff this
    key can unwrap other keys.
	@discussion
	The use of these enumerations has been deprecated.  Please
	use the equivalent items defined in SecItem.h
	@@@.
*/
CF_ENUM(int)
{
    kSecKeyKeyClass =          0,
    kSecKeyPrintName =         1,
    kSecKeyAlias =             2,
    kSecKeyPermanent =         3,
    kSecKeyPrivate =           4,
    kSecKeyModifiable =        5,
    kSecKeyLabel =             6,
    kSecKeyApplicationTag =    7,
    kSecKeyKeyCreator =        8,
    kSecKeyKeyType =           9,
    kSecKeyKeySizeInBits =    10,
    kSecKeyEffectiveKeySize = 11,
    kSecKeyStartDate =        12,
    kSecKeyEndDate =          13,
    kSecKeySensitive =        14,
    kSecKeyAlwaysSensitive =  15,
    kSecKeyExtractable =      16,
    kSecKeyNeverExtractable = 17,
    kSecKeyEncrypt =          18,
    kSecKeyDecrypt =          19,
    kSecKeyDerive =           20,
    kSecKeySign =             21,
    kSecKeyVerify =           22,
    kSecKeySignRecover =      23,
    kSecKeyVerifyRecover =    24,
    kSecKeyWrap =             25,
    kSecKeyUnwrap =           26
};

    /*!
    @enum SecCredentialType
    @abstract Determines the type of credential returned by SecKeyGetCredentials.
    @constant kSecCredentialTypeWithUI Operations with this key are allowed to present UI if required.
    @constant kSecCredentialTypeNoUI Operations with this key are not allowed to present UI, and will fail if UI is required.
    @constant kSecCredentialTypeDefault The default setting for determining whether to present UI is used. This setting can be changed with a call to SecKeychainSetUserInteractionAllowed.
*/
typedef CF_ENUM(uint32, SecCredentialType)
{
	kSecCredentialTypeDefault = 0,
	kSecCredentialTypeWithUI,
	kSecCredentialTypeNoUI
};
#endif /* SEC_OS_OSX */

/*!
    @typedef SecPadding
    @abstract Supported padding types.
*/
typedef CF_OPTIONS(uint32_t, SecPadding)
{
    kSecPaddingNone      = 0,
    kSecPaddingPKCS1     = 1,
    kSecPaddingOAEP      = 2, // __OSX_UNAVAILABLE __IOS_AVAILABLE(2.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0),

    /* For SecKeyRawSign/SecKeyRawVerify only,
     ECDSA signature is raw byte format {r,s}, big endian.
     First half is r, second half is s */
    kSecPaddingSigRaw  = 0x4000,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD2
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD2  = 0x8000, // __OSX_DEPRECATED(10.0, 10.12, "MD2 is deprecated") __IOS_DEPRECATED(2.0, 5.0, "MD2 is deprecated") __TVOS_UNAVAILABLE __WATCHOS_UNAVAILABLE,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD5
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD5  = 0x8001, // __OSX_DEPRECATED(10.0, 10.12, "MD5 is deprecated") __IOS_DEPRECATED(2.0, 5.0, "MD5 is deprecated") __TVOS_UNAVAILABLE __WATCHOS_UNAVAILABLE,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA1
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1SHA1 = 0x8002,
    
    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA224
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA224 = 0x8003, // __OSX_UNAVAILABLE __IOS_AVAILABLE(2.0),

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA256
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA256 = 0x8004, // __OSX_UNAVAILABLE __IOS_AVAILABLE(2.0),

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA384
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA384 = 0x8005, // __OSX_UNAVAILABLE __IOS_AVAILABLE(2.0),

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA512
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA512 = 0x8006, // __OSX_UNAVAILABLE __IOS_AVAILABLE(2.0),
};

#if SEC_OS_OSX
/*!
    @typedef SecKeySizes
    @abstract Supported key lengths.
*/
typedef CF_ENUM(uint32_t, SecKeySizes)
{
    kSecDefaultKeySize  = 0,

    // Symmetric Keysizes - default is currently kSecAES128 for AES.
    kSec3DES192         = 192,
    kSecAES128          = 128,
    kSecAES192          = 192,
    kSecAES256          = 256,

    // Supported ECC Keys for Suite-B from RFC 4492 section 5.1.1.
    // default is currently kSecp256r1
    kSecp192r1          = 192,
    kSecp256r1          = 256,
    kSecp384r1          = 384,
    kSecp521r1          = 521,  // Yes, 521

    // Boundaries for RSA KeySizes - default is currently 2048
    // RSA keysizes must be multiples of 8
    kSecRSAMin          = 1024,
    kSecRSAMax          = 4096
};
#endif /* SEC_OS_OSX */

/*!
	@enum Key Parameter Constants
	@discussion Predefined key constants used to get or set values in a dictionary.
	These are used to provide explicit parameters to key generation functions
	when non-default values are desired. See the description of the
	SecKeyGeneratePair API for usage information.
	@constant kSecPrivateKeyAttrs The value for this key is a CFDictionaryRef
	 containing attributes specific for the private key to be generated.
	@constant kSecPublicKeyAttrs The value for this key is a CFDictionaryRef
	 containing attributes specific for the public key to be generated.
*/
extern const CFStringRef kSecPrivateKeyAttrs
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_2_0);
extern const CFStringRef kSecPublicKeyAttrs
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_2_0);

/*!
	@function SecKeyGetTypeID
	@abstract Returns the type identifier of SecKey instances.
	@result The CFTypeID of SecKey instances.
*/
CFTypeID SecKeyGetTypeID(void)
	__OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);


#if SEC_OS_OSX
/*!
	@function SecKeyCreatePair
	@abstract Creates an asymmetric key pair and stores it in a specified keychain.
	@param keychainRef A reference to the keychain in which to store the private and public key items. Specify NULL for the default keychain.
	@param algorithm An algorithm for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param keySizeInBits A key size for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param contextHandle (optional) A CSSM_CC_HANDLE, or 0. If this argument is supplied, the algorithm and keySizeInBits parameters are ignored. If extra parameters are needed to generate a key (some algorithms require this), you should create a context using CSSM_CSP_CreateKeyGenContext, using the CSPHandle obtained by calling SecKeychainGetCSPHandle. Then use CSSM_UpdateContextAttributes to add parameters, and dispose of the context using CSSM_DeleteContext after calling this function.
	@param publicKeyUsage A bit mask indicating all permitted uses for the new public key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
	@param publicKeyAttr A bit mask defining attribute values for the new public key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
	@param privateKeyUsage A bit mask indicating all permitted uses for the new private key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
	@param privateKeyAttr A bit mask defining attribute values for the new private key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
	@param initialAccess (optional) A SecAccess object that determines the initial access rights to the private key. The public key is given "any/any" access rights by default.
	@param publicKey (optional) On return, the keychain item reference of the generated public key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned. Pass NULL if a reference to this key is not required.
	@param privateKey (optional) On return, the keychain item reference of the generated private key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned. Pass NULL if a reference to this key is not required.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This API is deprecated for 10.7. Please use the SecKeyGeneratePair API instead.
*/
OSStatus SecKeyCreatePair(
        SecKeychainRef _Nullable keychainRef,
        CSSM_ALGORITHMS algorithm,
        uint32 keySizeInBits,
        CSSM_CC_HANDLE contextHandle,
        CSSM_KEYUSE publicKeyUsage,
        uint32 publicKeyAttr,
        CSSM_KEYUSE privateKeyUsage,
        uint32 privateKeyAttr,
        SecAccessRef _Nullable initialAccess,
        SecKeyRef* _Nullable CF_RETURNS_RETAINED publicKey,
        SecKeyRef* _Nullable CF_RETURNS_RETAINED privateKey)
		CSSM_DEPRECATED;

/*!
	@function SecKeyGenerate
	@abstract Creates a symmetric key and optionally stores it in a specified keychain.
	@param keychainRef (optional) A reference to the keychain in which to store the generated key. Specify NULL to generate a transient key.
	@param algorithm An algorithm for the symmetric key. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param keySizeInBits A key size for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param contextHandle (optional) A CSSM_CC_HANDLE, or 0. If this argument is supplied, the algorithm and keySizeInBits parameters are ignored. If extra parameters are needed to generate a key (some algorithms require this), you should create a context using CSSM_CSP_CreateKeyGenContext, using the CSPHandle obtained by calling SecKeychainGetCSPHandle. Then use CSSM_UpdateContextAttributes to add parameters, and dispose of the context using CSSM_DeleteContext after calling this function.
	@param keyUsage A bit mask indicating all permitted uses for the new key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
	@param keyAttr A bit mask defining attribute values for the new key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
	@param initialAccess (optional) A SecAccess object that determines the initial access rights for the key. This parameter is ignored if the keychainRef is NULL.
	@param keyRef On return, a reference to the generated key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion This API is deprecated for 10.7.  Please use the SecKeyGenerateSymmetric API instead.
*/
OSStatus SecKeyGenerate(
        SecKeychainRef _Nullable keychainRef,
        CSSM_ALGORITHMS algorithm,
        uint32 keySizeInBits,
        CSSM_CC_HANDLE contextHandle,
        CSSM_KEYUSE keyUsage,
        uint32 keyAttr,
        SecAccessRef _Nullable initialAccess,
        SecKeyRef* _Nullable CF_RETURNS_RETAINED keyRef)
		CSSM_DEPRECATED;

/*!
    @function SecKeyGetCSSMKey
    @abstract Returns a pointer to the CSSM_KEY for the given key item reference.
    @param key A keychain key item reference. The key item must be of class type kSecPublicKeyItemClass, kSecPrivateKeyItemClass, or kSecSymmetricKeyItemClass.
    @param cssmKey On return, a pointer to a CSSM_KEY structure for the given key. This pointer remains valid until the key reference is released. The caller should not attempt to modify or free this data.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion  The CSSM_KEY is valid until the key item reference is released. This API is deprecated in 10.7. Its use should no longer be needed.
*/
OSStatus SecKeyGetCSSMKey(SecKeyRef key, const CSSM_KEY * _Nullable * __nonnull cssmKey)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;;

/*!
    @function SecKeyGetCSPHandle
    @abstract Returns the CSSM_CSP_HANDLE for the given key reference. The handle is valid until the key reference is released.
    @param keyRef A key reference.
    @param cspHandle On return, the CSSM_CSP_HANDLE for the given keychain.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This API is deprecated in 10.7. Its use should no longer be needed.
*/
OSStatus SecKeyGetCSPHandle(SecKeyRef keyRef, CSSM_CSP_HANDLE *cspHandle)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecKeyGetCredentials
    @abstract For a given key, return a pointer to a CSSM_ACCESS_CREDENTIALS structure which will allow the key to be used.
    @param keyRef The key for which a credential is requested.
    @param operation The type of operation to be performed with this key. See "Authorization tag type" for defined operations (cssmtype.h).
    @param credentialType The type of credential requested.
    @param outCredentials On return, a pointer to a CSSM_ACCESS_CREDENTIALS structure. This pointer remains valid until the key reference is released. The caller should not attempt to modify or free this data.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeyGetCredentials(
        SecKeyRef keyRef,
        CSSM_ACL_AUTHORIZATION_TAG operation,
        SecCredentialType credentialType,
        const CSSM_ACCESS_CREDENTIALS * _Nullable * __nonnull outCredentials)
		DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @function	SecKeyGenerateSymmetric
 @abstract	Generates a random symmetric key with the specified length
 and algorithm type.

 @param parameters A dictionary containing one or more key-value pairs.
 See the discussion sections below for a complete overview of options.
 @param error An optional pointer to a CFErrorRef. This value is set
 if an error occurred. If not NULL, the caller is responsible for
 releasing the CFErrorRef.
 @result On return, a SecKeyRef reference to the symmetric key, or
 NULL if the key could not be created.

 @discussion In order to generate a symmetric key, the parameters dictionary
 must at least contain the following keys:

 * kSecAttrKeyType with a value of kSecAttrKeyTypeAES or any other
 kSecAttrKeyType defined in SecItem.h
 * kSecAttrKeySizeInBits with a value being a CFNumberRef containing
 the requested key size in bits.  Example sizes for AES keys are:
 128, 192, 256, 512.

 To store the generated symmetric key in a keychain, set these keys:
 * kSecUseKeychain (value is a SecKeychainRef)
 * kSecAttrLabel (a user-visible label whose value is a CFStringRef,
 e.g. "My App's Encryption Key")
 * kSecAttrApplicationLabel (a label defined by your application, whose
 value is a CFDataRef and which can be used to find this key in a
 subsequent call to SecItemCopyMatching, e.g. "ID-1234567890-9876-0151")

 To specify the generated key's access control settings, set this key:
 * kSecAttrAccess (value is a SecAccessRef)

 The keys below may be optionally set in the parameters dictionary
 (with a CFBooleanRef value) to override the default usage values:

 * kSecAttrCanEncrypt (defaults to true if not explicitly specified)
 * kSecAttrCanDecrypt (defaults to true if not explicitly specified)
 * kSecAttrCanWrap (defaults to true if not explicitly specified)
 * kSecAttrCanUnwrap (defaults to true if not explicitly specified)

*/
_Nullable CF_RETURNS_RETAINED
SecKeyRef SecKeyGenerateSymmetric(CFDictionaryRef parameters, CFErrorRef *error)
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
 @function SecKeyCreateFromData
 @abstract Creates a symmetric key with the given data and sets the
 algorithm type specified.

 @param parameters A dictionary containing one or more key-value pairs.
 See the discussion sections below for a complete overview of options.
 @result On return, a SecKeyRef reference to the symmetric key.

 @discussion In order to generate a symmetric key the parameters dictionary must
 at least contain the following keys:

 * kSecAttrKeyType with a value of kSecAttrKeyTypeAES or any other
 kSecAttrKeyType defined in SecItem.h

 The keys below may be optionally set in the parameters dictionary
 (with a CFBooleanRef value) to override the default usage values:

 * kSecAttrCanEncrypt (defaults to true if not explicitly specified)
 * kSecAttrCanDecrypt (defaults to true if not explicitly specified)
 * kSecAttrCanWrap (defaults to true if not explicitly specified)
 * kSecAttrCanUnwrap (defaults to true if not explicitly specified)

*/
_Nullable
SecKeyRef SecKeyCreateFromData(CFDictionaryRef parameters,
	CFDataRef keyData, CFErrorRef *error)
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);


#ifdef __BLOCKS__
/*!
 @typedef SecKeyGeneratePairBlock
 @abstract Delivers the result from an asynchronous key pair generation.
 @param publicKey - the public key generated.   You must retain publicKey if you wish to use it after your block returns.
 @param privateKey - the private key generated.  You must retain publicKey if you wish to use it after your block returns.
 @param error - Any errors returned.   You must retain error if you wish to use it after your block returns.
 */

typedef void (^SecKeyGeneratePairBlock)(SecKeyRef publicKey, SecKeyRef privateKey,  CFErrorRef error);

/*!
 @function SecKeyGeneratePairAsync
 @abstract Generate a private/public keypair returning the values in a callback.
 @param parameters A dictionary containing one or more key-value pairs.
 @param deliveryQueue A dispatch queue to be used to deliver the results.
 @param result A callback function to result when the operation has completed.

 @discussion In order to generate a keypair the parameters dictionary must
 at least contain the following keys:

 * kSecAttrKeyType with a value being kSecAttrKeyTypeRSA or any other
 kSecAttrKeyType defined in SecItem.h
 * kSecAttrKeySizeInBits with a value being a CFNumberRef or CFStringRef
 containing the requested key size in bits.  Example sizes for RSA
 keys are: 512, 768, 1024, 2048.

 Setting the following attributes explicitly will override the defaults below.
 See SecItem.h for detailed information on these attributes including the types
 of the values.

 * kSecAttrLabel default NULL
 * kSecAttrIsPermanent if this key is present and has a Boolean
 value of true, the key or key pair will be added to the default
 keychain.
 * kSecAttrApplicationTag default NULL
 * kSecAttrEffectiveKeySize default NULL same as kSecAttrKeySizeInBits
 * kSecAttrCanEncrypt default false for private keys, true for public keys
 * kSecAttrCanDecrypt default true for private keys, false for public keys
 * kSecAttrCanDerive default true
 * kSecAttrCanSign default true for private keys, false for public keys
 * kSecAttrCanVerify default false for private keys, true for public keys
 * kSecAttrCanWrap default false for private keys, true for public keys
 * kSecAttrCanUnwrap default true for private keys, false for public keys

*/
void SecKeyGeneratePairAsync(CFDictionaryRef parameters,
    dispatch_queue_t deliveryQueue, SecKeyGeneratePairBlock result)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

#endif /* __BLOCKS__ */

// Derive, Wrap, and Unwrap

/*!
 @function SecKeyDeriveFromPassword
 @abstract Derives a symmetric key from a password.

 @param password The password from which the keyis to be derived.
 @param parameters A dictionary containing one or more key-value pairs.
 @param error If the call fails this will contain the error code.

 @discussion In order to derive a key the parameters dictionary must contain at least contain the following keys:
 * kSecAttrSalt - a CFData for the salt value for mixing in the pseudo-random rounds.
 * kSecAttrPRF - the algorithm to use for the pseudo-random-function.
   If 0, this defaults to kSecAttrPRFHmacAlgSHA1. Possible values are:

 * kSecAttrPRFHmacAlgSHA1
 * kSecAttrPRFHmacAlgSHA224
 * kSecAttrPRFHmacAlgSHA256
 * kSecAttrPRFHmacAlgSHA384
 * kSecAttrPRFHmacAlgSHA512

 * kSecAttrRounds - the number of rounds to call the pseudo random function.
   If 0, a count will be computed to average 1/10 of a second.
 * kSecAttrKeySizeInBits with a value being a CFNumberRef
   containing the requested key size in bits.  Example sizes for RSA keys are:
   512, 768, 1024, 2048.

 @result On success a SecKeyRef is returned.  On failure this result is NULL and the
 error parameter contains the reason.

*/
_Nullable CF_RETURNS_RETAINED
SecKeyRef SecKeyDeriveFromPassword(CFStringRef password,
    CFDictionaryRef parameters, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
 @function SecKeyWrapSymmetric
 @abstract Wraps a symmetric key with a symmetric key.

 @param keyToWrap The key which is to be wrapped.
 @param wrappingKey The key wrapping key.
 @param parameters The parameter list to use for wrapping the key.
 @param error If the call fails this will contain the error code.

 @result On success a CFDataRef is returned.  On failure this result is NULL and the
 error parameter contains the reason.

 @discussion In order to wrap a key the parameters dictionary may contain the following key:
 * kSecSalt - a CFData for the salt value for the encrypt.

*/
_Nullable
CFDataRef SecKeyWrapSymmetric(SecKeyRef keyToWrap,
    SecKeyRef wrappingKey, CFDictionaryRef parameters, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
 @function SecKeyUnwrapSymmetric
 @abstract Unwrap a wrapped symmetric key.

 @param keyToUnwrap The wrapped key to unwrap.
 @param unwrappingKey The key unwrapping key.
 @param parameters The parameter list to use for unwrapping the key.
 @param error If the call fails this will contain the error code.

 @result On success a SecKeyRef is returned.  On failure this result is NULL and the
 error parameter contains the reason.

 @discussion In order to unwrap a key the parameters dictionary may contain the following key:
 * kSecSalt - a CFData for the salt value for the decrypt.

*/
_Nullable
SecKeyRef SecKeyUnwrapSymmetric(CFDataRef _Nullable * __nonnull keyToUnwrap,
    SecKeyRef unwrappingKey, CFDictionaryRef parameters, CFErrorRef *error)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

#endif /* SEC_OS_OSX */

/*!
    @function SecKeyGeneratePair
    @abstract Generate a private/public keypair.
    @param parameters A dictionary containing one or more key-value pairs.
    See the discussion sections below for a complete overview of options.
    @param publicKey On return, a SecKeyRef reference to the public key.
    @param privateKey On return, a SecKeyRef reference to the private key.
    @result A result code. See "Security Error Codes" (SecBase.h).

    @discussion In order to generate a keypair the parameters dictionary must
                at least contain the following keys:

    * kSecAttrKeyType with a value of kSecAttrKeyTypeRSA or any other
        kSecAttrKeyType defined in SecItem.h
    * kSecAttrKeySizeInBits with a value being a CFNumberRef containing
        the requested key size in bits.  Example sizes for RSA keys are:
        512, 768, 1024, 2048.

    The values below may be set either in the top-level dictionary or in a
    dictionary that is the value of the kSecPrivateKeyAttrs or
    kSecPublicKeyAttrs key in the top-level dictionary.  Setting these
    attributes explicitly will override the defaults below.  See SecItem.h
    for detailed information on these attributes including the types of
    the values.

    * kSecAttrLabel default NULL
    * kSecUseKeychain default NULL, which specifies the default keychain
    * kSecAttrIsPermanent default false
        if this key is present and has a Boolean value of true, the key or 
        key pair will be added to the keychain.
    * kSecAttrTokenID default NULL
        The CFStringRef ID of the token to generate the key or keypair on. This
        attribute can contain CFStringRef and can be present only in the top-level
        parameters dictionary.
    * kSecAttrApplicationTag default NULL
    * kSecAttrEffectiveKeySize default NULL same as kSecAttrKeySizeInBits
    * kSecAttrCanEncrypt default false for private keys, true for public keys
    * kSecAttrCanDecrypt default true for private keys, false for public keys
    * kSecAttrCanDerive default true
    * kSecAttrCanSign default true for private keys, false for public keys
    * kSecAttrCanVerify default false for private keys, true for public keys
    * kSecAttrCanWrap default false for private keys, true for public keys
    * kSecAttrCanUnwrap default true for private keys, false for public keys

    NOTE: The function always saves keys in the keychain on macOS and as such attribute
    kSecAttrIsPermanent is ignored. The function respects attribute kSecAttrIsPermanent
    on iOS, tvOS and watchOS.
    It is recommended to use SecKeyCreateRandomKey() which respects kSecAttrIsPermanent
    on all platforms.
*/
OSStatus SecKeyGeneratePair(CFDictionaryRef parameters,
    SecKeyRef * _Nullable CF_RETURNS_RETAINED publicKey, SecKeyRef * _Nullable CF_RETURNS_RETAINED privateKey)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


#if SEC_OS_IPHONE
/*!
 @function SecKeyRawSign
 @abstract Given a private key and data to sign, generate a digital
 signature.
 @param key Private key with which to sign.
 @param padding See Padding Types above, typically kSecPaddingPKCS1SHA1.
 @param dataToSign The data to be signed, typically the digest of the
 actual data.
 @param dataToSignLen Length of dataToSign in bytes.
 @param sig Pointer to buffer in which the signature will be returned.
 @param sigLen IN/OUT maximum length of sig buffer on input, actualy
 length of sig on output.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion If the padding argument is kSecPaddingPKCS1, PKCS1 padding
 will be performed prior to signing. If this argument is kSecPaddingNone,
 the incoming data will be signed "as is".

 When PKCS1 padding is performed, the maximum length of data that can
 be signed is the value returned by SecKeyGetBlockSize() - 11.

 NOTE: The behavior this function with kSecPaddingNone is undefined if the
 first byte of dataToSign is zero; there is no way to verify leading zeroes
 as they are discarded during the calculation.

 If you want to generate a proper PKCS1 style signature with DER encoding
 of the digest type - and the dataToSign is a SHA1 digest - use
 kSecPaddingPKCS1SHA1.
 */
OSStatus SecKeyRawSign(
                       SecKeyRef           key,
                       SecPadding          padding,
                       const uint8_t       *dataToSign,
                       size_t              dataToSignLen,
                       uint8_t             *sig,
                       size_t              *sigLen)
__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
 @function SecKeyRawVerify
 @abstract Given a public key, data which has been signed, and a signature,
 verify the signature.
 @param key Public key with which to verify the signature.
 @param padding See Padding Types above, typically kSecPaddingPKCS1SHA1.
 @param signedData The data over which sig is being verified, typically
 the digest of the actual data.
 @param signedDataLen Length of signedData in bytes.
 @param sig Pointer to the signature to verify.
 @param sigLen Length of sig in  bytes.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion If the padding argument is kSecPaddingPKCS1, PKCS1 padding
 will be checked during verification. If this argument is kSecPaddingNone,
 the incoming data will be compared directly to sig.

 If you are verifying a proper PKCS1-style signature, with DER encoding
 of the digest type - and the signedData is a SHA1 digest - use
 kSecPaddingPKCS1SHA1.
 */
OSStatus SecKeyRawVerify(
                         SecKeyRef           key,
                         SecPadding          padding,
                         const uint8_t       *signedData,
                         size_t              signedDataLen,
                         const uint8_t       *sig,
                         size_t              sigLen)
__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
 @function SecKeyEncrypt
 @abstract Encrypt a block of plaintext.
 @param key Public key with which to encrypt the data.
 @param padding See Padding Types above, typically kSecPaddingPKCS1.
 @param plainText The data to encrypt.
 @param plainTextLen Length of plainText in bytes, this must be less
 or equal to the value returned by SecKeyGetBlockSize().
 @param cipherText Pointer to the output buffer.
 @param cipherTextLen On input, specifies how much space is available at
 cipherText; on return, it is the actual number of cipherText bytes written.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion If the padding argument is kSecPaddingPKCS1 or kSecPaddingOAEP,
 PKCS1 (respectively kSecPaddingOAEP) padding will be performed prior to encryption.
 If this argument is kSecPaddingNone, the incoming data will be encrypted "as is".
 kSecPaddingOAEP is the recommended value. Other value are not recommended
 for security reason (Padding attack or malleability).

 When PKCS1 padding is performed, the maximum length of data that can
 be encrypted is the value returned by SecKeyGetBlockSize() - 11.

 When memory usage is a critical issue, note that the input buffer
 (plainText) can be the same as the output buffer (cipherText).
 */
OSStatus SecKeyEncrypt(
                       SecKeyRef           key,
                       SecPadding          padding,
                       const uint8_t		*plainText,
                       size_t              plainTextLen,
                       uint8_t             *cipherText,
                       size_t              *cipherTextLen)
__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
 @function SecKeyDecrypt
 @abstract Decrypt a block of ciphertext.
 @param key Private key with which to decrypt the data.
 @param padding See Padding Types above, typically kSecPaddingPKCS1.
 @param cipherText The data to decrypt.
 @param cipherTextLen Length of cipherText in bytes, this must be less
 or equal to the value returned by SecKeyGetBlockSize().
 @param plainText Pointer to the output buffer.
 @param plainTextLen On input, specifies how much space is available at
 plainText; on return, it is the actual number of plainText bytes written.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion If the padding argument is kSecPaddingPKCS1 or kSecPaddingOAEP,
 the corresponding padding will be removed after decryption.
 If this argument is kSecPaddingNone, the decrypted data will be returned "as is".

 When memory usage is a critical issue, note that the input buffer
 (plainText) can be the same as the output buffer (cipherText).
 */
OSStatus SecKeyDecrypt(
                       SecKeyRef           key,                /* Private key */
                       SecPadding          padding,			/* kSecPaddingNone,
                                                             kSecPaddingPKCS1,
                                                             kSecPaddingOAEP */
                       const uint8_t       *cipherText,
                       size_t              cipherTextLen,		/* length of cipherText */
                       uint8_t             *plainText,	
                       size_t              *plainTextLen)		/* IN/OUT */
__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

#endif // SEC_OS_IPHONE

/*!
 @function SecKeyCreateRandomKey
 @abstract Generates a new public/private key pair.
 @param parameters A dictionary containing one or more key-value pairs.
    See the discussion sections below for a complete overview of options.
 @param error On error, will be populated with an error object describing the failure.
 See "Security Error Codes" (SecBase.h).
 @return Newly generated private key.  To get associated public key, use SecKeyCopyPublicKey().
 @discussion In order to generate a keypair the parameters dictionary must
    at least contain the following keys:

 * kSecAttrKeyType with a value being kSecAttrKeyTypeRSA or any other
 kSecAttrKeyType defined in SecItem.h
 * kSecAttrKeySizeInBits with a value being a CFNumberRef or CFStringRef
 containing the requested key size in bits.  Example sizes for RSA
 keys are: 512, 768, 1024, 2048.

 The values below may be set either in the top-level dictionary or in a
 dictionary that is the value of the kSecPrivateKeyAttrs or
 kSecPublicKeyAttrs key in the top-level dictionary.  Setting these
 attributes explicitly will override the defaults below.  See SecItem.h
 for detailed information on these attributes including the types of
 the values.

 * kSecAttrLabel default NULL
 * kSecAttrIsPermanent if this key is present and has a Boolean value of true,
   the key or key pair will be added to the default keychain.
 * kSecAttrTokenID if this key should be generated on specified token.  This
   attribute can contain CFStringRef and can be present only in the top-level
   parameters dictionary.
 * kSecAttrApplicationTag default NULL
 * kSecAttrEffectiveKeySize default NULL same as kSecAttrKeySizeInBits
 * kSecAttrCanEncrypt default false for private keys, true for public keys
 * kSecAttrCanDecrypt default true for private keys, false for public keys
 * kSecAttrCanDerive default true
 * kSecAttrCanSign default true for private keys, false for public keys
 * kSecAttrCanVerify default false for private keys, true for public keys
 * kSecAttrCanWrap default false for private keys, true for public keys
 * kSecAttrCanUnwrap default true for private keys, false for public keys
 */
SecKeyRef _Nullable SecKeyCreateRandomKey(CFDictionaryRef parameters, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCreateWithData
    @abstract Create a SecKey from a well-defined external representation.
    @param keyData CFData representing the key. The format of the data depends on the type of key being created.
    @param attributes Dictionary containing attributes describing the key to be imported. The keys in this dictionary
    are kSecAttr* constants from SecItem.h.  Mandatory attributes are:
     * kSecAttrKeyType
     * kSecAttrKeyClass
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result A SecKey object representing the key, or NULL on failure.
    @discussion This function does not add keys to any keychain, but the SecKey object it returns can be added
    to keychain using the SecItemAdd function.
    The requested data format depend on the type of key (kSecAttrKeyType) being created:
     * kSecAttrKeyTypeRSA               PKCS#1 format, public key can be also in x509 public key format
     * kSecAttrKeyTypeECSECPrimeRandom  ANSI X9.63 format (04 || X || Y [ || K])
 */
SecKeyRef _Nullable SecKeyCreateWithData(CFDataRef keyData, CFDictionaryRef attributes, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyGetBlockSize
    @abstract Returns block length of the key in bytes.
    @param key The key for which the block length is requested.
    @result The block length of the key in bytes.
    @discussion If for example key is an RSA key the value returned by
    this function is the size of the modulus.
 */
size_t SecKeyGetBlockSize(SecKeyRef key)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @function SecKeyCopyExternalRepresentation
    @abstract Create an external representation for the given key suitable for the key's type.
    @param key The key to be exported.
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result A CFData representing the key in a format suitable for that key type.
    @discussion This function may fail if the key is not exportable (e.g., bound to a smart card or Secure Enclave).
    The format in which the key will be exported depends on the type of key:
     * kSecAttrKeyTypeRSA               PKCS#1 format
     * kSecAttrKeyTypeECSECPrimeRandom  ANSI X9.63 format (04 || X || Y [ || K])
 */
CFDataRef _Nullable SecKeyCopyExternalRepresentation(SecKeyRef key, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCopyAttributes
    @abstract Retrieve keychain attributes of a key.
    @param key The key whose attributes are to be retrieved.
    @result Dictionary containing attributes of the key. The keys that populate this dictionary are defined
    and discussed in SecItem.h.
    @discussion The attributes provided by this function are:
    * kSecAttrCanEncrypt
    * kSecAttrCanDecrypt
    * kSecAttrCanDerive
    * kSecAttrCanSign
    * kSecAttrCanVerify
    * kSecAttrKeyClass
    * kSecAttrKeyType
    * kSecAttrKeySizeInBits
    * kSecAttrTokenID
    * kSecAttrApplicationLabel
    Other values returned in that dictionary are RFU.
 */
CFDictionaryRef _Nullable SecKeyCopyAttributes(SecKeyRef key)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCopyPublicKey
    @abstract Retrieve the public key from a key pair or private key.
    @param key The key from which to retrieve a public key.
    @result The public key or NULL if public key is not available for specified key.
    @discussion Fails if key does not contain a public key or no public key can be computed from it.
 */
SecKeyRef _Nullable SecKeyCopyPublicKey(SecKeyRef key)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @enum SecKeyAlgorithm
    @abstract Available algorithms for performing cryptographic operations with SecKey object.  String representation
    of constant can be used for logging or debugging purposes, because they contain human readable names of the algorithm.

    @constant kSecKeyAlgorithmRSASignatureRaw
    Raw RSA sign/verify operation, size of input data must be the same as value returned by SecKeyGetBlockSize().

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15Raw
    RSA sign/verify operation, assumes that input data is digest and OID and digest algorithm as specified in PKCS# v1.5.
    This algorithm is typically not used directly, instead use algorithm with specified digest, like
    kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA256.

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA1
    RSA signature with PKCS#1 padding, input data must be SHA-1 generated digest.

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA224
    RSA signature with PKCS#1 padding, input data must be SHA-224 generated digest.

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA256
    RSA signature with PKCS#1 padding, input data must be SHA-256 generated digest.

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA384
    RSA signature with PKCS#1 padding, input data must be SHA-384 generated digest.

    @constant kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA512
    RSA signature with PKCS#1 padding, input data must be SHA-512 generated digest.

    @constant kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA1
    RSA signature with PKCS#1 padding, SHA-1 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA224
    RSA signature with PKCS#1 padding, SHA-224 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA256
    RSA signature with PKCS#1 padding, SHA-256 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA384
    RSA signature with PKCS#1 padding, SHA-384 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA512
    RSA signature with PKCS#1 padding, SHA-512 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSASignatureDigestPSSSHA1
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, input data must be SHA-1 generated digest.
    PSS padding is calculated using MGF1 with SHA1 and saltLength parameter is set to 20 (SHA-1 output size).

    @constant kSecKeyAlgorithmRSASignatureDigestPSSSHA224
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, input data must be SHA-224 generated digest.
    PSS padding is calculated using MGF1 with SHA224 and saltLength parameter is set to 28 (SHA-224 output size).

    @constant kSecKeyAlgorithmRSASignatureDigestPSSSHA256
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, input data must be SHA-256 generated digest.
    PSS padding is calculated using MGF1 with SHA256 and saltLength parameter is set to 32 (SHA-256 output size).

    @constant kSecKeyAlgorithmRSASignatureDigestPSSSHA384
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, input data must be SHA-384 generated digest.
    PSS padding is calculated using MGF1 with SHA384 and saltLength parameter is set to 48 (SHA-384 output size).

    @constant kSecKeyAlgorithmRSASignatureDigestPSSSHA512
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, input data must be SHA-512 generated digest.
    PSS padding is calculated using MGF1 with SHA512 and saltLength parameter is set to 64 (SHA-512 output size).

    @constant kSecKeyAlgorithmRSASignatureMessagePSSSHA1
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, SHA-1 digest is generated from input data of any size.
    PSS padding is calculated using MGF1 with SHA1 and saltLength parameter is set to 20 (SHA-1 output size).

    @constant kSecKeyAlgorithmRSASignatureMessagePSSSHA224
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, SHA-224 digest is generated from input data of any size.
    PSS padding is calculated using MGF1 with SHA224 and saltLength parameter is set to 28 (SHA-224 output size).

    @constant kSecKeyAlgorithmRSASignatureMessagePSSSHA256
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, SHA-256 digest is generated from input data of any size.
    PSS padding is calculated using MGF1 with SHA256 and saltLength parameter is set to 32 (SHA-256 output size).

    @constant kSecKeyAlgorithmRSASignatureMessagePSSSHA384
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, SHA-384 digest is generated from input data of any size.
    PSS padding is calculated using MGF1 with SHA384 and saltLength parameter is set to 48 (SHA-384 output size).

    @constant kSecKeyAlgorithmRSASignatureMessagePSSSHA512
    RSA signature with RSASSA-PSS padding according to PKCS#1 v2.1, SHA-512 digest is generated from input data of any size.
    PSS padding is calculated using MGF1 with SHA512 and saltLength parameter is set to 64 (SHA-512 output size).

    @constant kSecKeyAlgorithmECDSASignatureRFC4754
    ECDSA algorithm, signature is concatenated r and s, big endian, data is message digest.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest created by SHA1 algorithm.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest created by SHA224 algorithm.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest created by SHA256 algorithm.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest created by SHA384 algorithm.

    @constant kSecKeyAlgorithmECDSASignatureDigestX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, input data is message digest created by SHA512 algorithm.

    @constant kSecKeyAlgorithmECDSASignatureMessageX962SHA1
    ECDSA algorithm, signature is in DER x9.62 encoding, SHA-1 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmECDSASignatureMessageX962SHA224
    ECDSA algorithm, signature is in DER x9.62 encoding, SHA-224 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmECDSASignatureMessageX962SHA256
    ECDSA algorithm, signature is in DER x9.62 encoding, SHA-256 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmECDSASignatureMessageX962SHA384
    ECDSA algorithm, signature is in DER x9.62 encoding, SHA-384 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmECDSASignatureMessageX962SHA512
    ECDSA algorithm, signature is in DER x9.62 encoding, SHA-512 digest is generated from input data of any size.

    @constant kSecKeyAlgorithmRSAEncryptionRaw
    Raw RSA encryption or decryption, size of data must match RSA key modulus size.  Note that direct
    use of this algorithm without padding is cryptographically very weak, it is important to always introduce
    some kind of padding.  Input data size must be less or equal to the key block size and returned block has always
    the same size as block size, as returned by SecKeyGetBlockSize().

    @constant kSecKeyAlgorithmRSAEncryptionPKCS1
    RSA encryption or decryption, data is padded using PKCS#1 padding scheme.  This algorithm should be used only for
    backward compatibility with existing protocols and data. New implementations should choose cryptographically
    stronger algorithm instead (see kSecKeyAlgorithmRSAEncryptionOAEP).  Input data must be at most
    "key block size - 11" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA1
    RSA encryption or decryption, data is padded using OAEP padding scheme internally using SHA1. Input data must be at most
    "key block size - 42" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().  Use kSecKeyAlgorithmRSAEncryptionOAEPSHA1AESGCM to be able to encrypt and decrypt arbitrary long data.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA224
    RSA encryption or decryption, data is padded using OAEP padding scheme internally using SHA224. Input data must be at most
    "key block size - 58" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().  Use kSecKeyAlgorithmRSAEncryptionOAEPSHA224AESGCM to be able to encrypt and decrypt arbitrary long data.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA256
    RSA encryption or decryption, data is padded using OAEP padding scheme internally using SHA256. Input data must be at most
    "key block size - 66" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().  Use kSecKeyAlgorithmRSAEncryptionOAEPSHA256AESGCM to be able to encrypt and decrypt arbitrary long data.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA384
    RSA encryption or decryption, data is padded using OAEP padding scheme internally using SHA384. Input data must be at most
    "key block size - 98" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().  Use kSecKeyAlgorithmRSAEncryptionOAEPSHA384AESGCM to be able to encrypt and decrypt arbitrary long data.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA512
    RSA encryption or decryption, data is padded using OAEP padding scheme internally using SHA512. Input data must be at most
    "key block size - 130" bytes long and returned block has always the same size as block size, as returned
    by SecKeyGetBlockSize().  Use kSecKeyAlgorithmRSAEncryptionOAEPSHA512AESGCM to be able to encrypt and decrypt arbitrary long data.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA1AESGCM
    Randomly generated AES session key is encrypted by RSA with OAEP padding.  User data are encrypted using session key in GCM
    mode with all-zero 16 bytes long IV (initialization vector).  Finally 16 byte AES-GCM tag is appended to ciphertext.
    256bit AES key is used if RSA key is 4096bit or bigger, otherwise 128bit AES key is used.  Raw public key data is used
    as authentication data for AES-GCM encryption.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA224AESGCM
    Randomly generated AES session key is encrypted by RSA with OAEP padding.  User data are encrypted using session key in GCM
    mode with all-zero 16 bytes long IV (initialization vector).  Finally 16 byte AES-GCM tag is appended to ciphertext.
    256bit AES key is used if RSA key is 4096bit or bigger, otherwise 128bit AES key is used.  Raw public key data is used
    as authentication data for AES-GCM encryption.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA256AESGCM
    Randomly generated AES session key is encrypted by RSA with OAEP padding.  User data are encrypted using session key in GCM
    mode with all-zero 16 bytes long IV (initialization vector).  Finally 16 byte AES-GCM tag is appended to ciphertext.
    256bit AES key is used if RSA key is 4096bit or bigger, otherwise 128bit AES key is used.  Raw public key data is used
    as authentication data for AES-GCM encryption.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA384AESGCM
    Randomly generated AES session key is encrypted by RSA with OAEP padding.  User data are encrypted using session key in GCM
    mode with all-zero 16 bytes long IV (initialization vector).  Finally 16 byte AES-GCM tag is appended to ciphertext.
    256bit AES key is used if RSA key is 4096bit or bigger, otherwise 128bit AES key is used.  Raw public key data is used
    as authentication data for AES-GCM encryption.

    @constant kSecKeyAlgorithmRSAEncryptionOAEPSHA512AESGCM
    Randomly generated AES session key is encrypted by RSA with OAEP padding.  User data are encrypted using session key in GCM
    mode with all-zero 16 bytes long IV (initialization vector).  Finally 16 byte AES-GCM tag is appended to ciphertext.
    256bit AES key is used if RSA key is 4096bit or bigger, otherwise 128bit AES key is used.  Raw public key data is used
    as authentication data for AES-GCM encryption.

    @constant kSecKeyAlgorithmECIESEncryptionStandardX963SHA1AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA1.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionStandardX963SHA224AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA224AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA224.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionStandardX963SHA256AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA256.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionStandardX963SHA384AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA384AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA384.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionStandardX963SHA512AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA512AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA512.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionCofactorX963SHA1AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA256AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA1.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionCofactorX963SHA224AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA224AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA224.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionCofactorX963SHA256AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA256AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA256.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionCofactorX963SHA384AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA384AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA384.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionCofactorX963SHA512AESGCM
    Legacy ECIES encryption or decryption, use kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA512AESGCM in new code.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA512.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG and all-zero 16 byte long IV (initialization vector).

    @constant kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA224AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA224.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA256.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA384AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA384.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA512AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA512.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA224AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA224.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA256AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA256.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA384AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA384.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA512AESGCM
    ECIES encryption or decryption.  This algorithm does not limit the size of the message to be encrypted or decrypted.
    Encryption is done using AES-GCM with key negotiated by kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA512.  AES Key size
    is 128bit for EC keys <=256bit and 256bit for bigger EC keys. Ephemeral public key data is used as sharedInfo for KDF.
    AES-GCM uses 16 bytes long TAG, AES key is first half of KDF output and 16 byte long IV (initialization vector) is second half
    of KDF output.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactor
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys.
    This algorithm does not accept any parameters, length of output raw shared secret is given by the length of the key.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA1
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA1 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA224
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA224 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA256
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA256 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA384
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA384 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA512
    Compute shared secret using ECDH cofactor algorithm, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA512 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandard
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys.
    This algorithm does not accept any parameters, length of output raw shared secret is given by the length of the key.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA1
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA1 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA224
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA224 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA256
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA256 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA384
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA384 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.

    @constant kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA512
    Compute shared secret using ECDH algorithm without cofactor, suitable only for kSecAttrKeyTypeECSECPrimeRandom keys
    and apply ANSI X9.63 KDF with SHA512 as hashing function.  Requires kSecKeyKeyExchangeParameterRequestedSize and allows
    kSecKeyKeyExchangeParameterSharedInfo parameters to be used.
  */

typedef CFStringRef SecKeyAlgorithm CF_STRING_ENUM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureRaw
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15Raw
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPKCS1v15SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePKCS1v15SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPSSSHA1
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPSSSHA224
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPSSSHA256
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPSSSHA384
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureDigestPSSSHA512
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePSSSHA1
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePSSSHA224
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePSSSHA256
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePSSSHA384
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSASignatureMessagePSSSHA512
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureRFC4754
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureDigestX962SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureMessageX962SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureMessageX962SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureMessageX962SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureMessageX962SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDSASignatureMessageX962SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionRaw
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionPKCS1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA1AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA224AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA256AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA384AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmRSAEncryptionOAEPSHA512AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardX963SHA1AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardX963SHA224AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardX963SHA256AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardX963SHA384AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardX963SHA512AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorX963SHA1AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorX963SHA224AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorX963SHA256AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorX963SHA384AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorX963SHA512AESGCM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA224AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA384AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA512AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA224AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA256AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA384AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECIESEncryptionCofactorVariableIVX963SHA512AESGCM
__OSX_AVAILABLE(10.13) __IOS_AVAILABLE(11.0) __TVOS_AVAILABLE(11.0) __WATCHOS_AVAILABLE(4.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandard
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeStandardX963SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactor
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA1
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA224
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA256
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA384
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyAlgorithm kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA512
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCreateSignature
    @abstract Given a private key and data to sign, generate a digital signature.
    @param key Private key with which to sign.
    @param algorithm One of SecKeyAlgorithm constants suitable to generate signature with this key.
    @param dataToSign The data to be signed, typically the digest of the actual data.
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result The signature over dataToSign represented as a CFData, or NULL on failure.
    @discussion Computes digital signature using specified key over input data.  The operation algorithm
    further defines the exact format of input data, operation to be performed and output signature.
 */
CFDataRef _Nullable SecKeyCreateSignature(SecKeyRef key, SecKeyAlgorithm algorithm, CFDataRef dataToSign, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyVerifySignature
    @abstract Given a public key, data which has been signed, and a signature, verify the signature.
    @param key Public key with which to verify the signature.
    @param algorithm One of SecKeyAlgorithm constants suitable to verify signature with this key.
    @param signedData The data over which sig is being verified, typically the digest of the actual data.
    @param signature The signature to verify.
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result True if the signature was valid, False otherwise.
    @discussion Verifies digital signature operation using specified key and signed data.  The operation algorithm
    further defines the exact format of input data, signature and operation to be performed.
 */
Boolean SecKeyVerifySignature(SecKeyRef key, SecKeyAlgorithm algorithm, CFDataRef signedData, CFDataRef signature, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCreateEncryptedData
    @abstract Encrypt a block of plaintext.
    @param key Public key with which to encrypt the data.
    @param algorithm One of SecKeyAlgorithm constants suitable to perform encryption with this key.
    @param plaintext The data to encrypt. The length and format of the data must conform to chosen algorithm,
    typically be less or equal to the value returned by SecKeyGetBlockSize().
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result The ciphertext represented as a CFData, or NULL on failure.
    @discussion Encrypts plaintext data using specified key.  The exact type of the operation including the format
    of input and output data is specified by encryption algorithm.
 */
CFDataRef _Nullable SecKeyCreateEncryptedData(SecKeyRef key, SecKeyAlgorithm algorithm, CFDataRef plaintext,
                                               CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCreateDecryptedData
    @abstract Decrypt a block of ciphertext.
    @param key Private key with which to decrypt the data.
    @param algorithm One of SecKeyAlgorithm constants suitable to perform decryption with this key.
    @param ciphertext The data to decrypt. The length and format of the data must conform to chosen algorithm,
    typically be less or equal to the value returned by SecKeyGetBlockSize().
    @param error On error, will be populated with an error object describing the failure.
    See "Security Error Codes" (SecBase.h).
    @result The plaintext represented as a CFData, or NULL on failure.
    @discussion Decrypts ciphertext data using specified key.  The exact type of the operation including the format
    of input and output data is specified by decryption algorithm.
 */
CFDataRef _Nullable SecKeyCreateDecryptedData(SecKeyRef key, SecKeyAlgorithm algorithm, CFDataRef ciphertext,
                                               CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @enum SecKeyKeyExchangeParameter SecKey Key Exchange parameters
    @constant kSecKeyKeyExchangeParameterRequestedSize Contains CFNumberRef with requested result size in bytes.
    @constant kSecKeyKeyExchangeParameterSharedInfo Contains CFDataRef with additional shared info
    for KDF (key derivation function).
 */
typedef CFStringRef SecKeyKeyExchangeParameter CF_STRING_ENUM
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyKeyExchangeParameter kSecKeyKeyExchangeParameterRequestedSize
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);
extern const SecKeyKeyExchangeParameter kSecKeyKeyExchangeParameterSharedInfo
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyCopyKeyExchangeResult
    @abstract Perform Diffie-Hellman style of key exchange operation, optionally with additional key-derivation steps.
    @param algorithm One of SecKeyAlgorithm constants suitable to perform this operation.
    @param publicKey Remote party's public key.
    @param parameters Dictionary with parameters, see SecKeyKeyExchangeParameter constants.  Used algorithm
    determines the set of required and optional parameters to be used.
    @param error Pointer to an error object on failure.
    See "Security Error Codes" (SecBase.h).
    @result Result of key exchange operation as a CFDataRef, or NULL on failure.
 */
CFDataRef _Nullable SecKeyCopyKeyExchangeResult(SecKeyRef privateKey, SecKeyAlgorithm algorithm, SecKeyRef publicKey, CFDictionaryRef parameters, CFErrorRef *error)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @enum SecKeyOperationType
    @abstract Defines types of cryptographic operations available with SecKey instance.

    @constant kSecKeyOperationTypeSign
    Represents SecKeyCreateSignature()

    @constant kSecKeyOperationTypeVerify
    Represents SecKeyVerifySignature()

    @constant kSecKeyOperationTypeEncrypt
    Represents SecKeyCreateEncryptedData()

    @constant kSecKeyOperationTypeDecrypt
    Represents SecKeyCreateDecryptedData()

    @constant kSecKeyOperationTypeKeyExchange
    Represents SecKeyCopyKeyExchangeResult()
 */
typedef CF_ENUM(CFIndex, SecKeyOperationType) {
    kSecKeyOperationTypeSign        = 0,
    kSecKeyOperationTypeVerify      = 1,
    kSecKeyOperationTypeEncrypt     = 2,
    kSecKeyOperationTypeDecrypt     = 3,
    kSecKeyOperationTypeKeyExchange = 4,
} __OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/*!
    @function SecKeyIsAlgorithmSupported
    @abstract Checks whether key supports specified algorithm for specified operation.
    @param key Key to query
    @param operation Operation type for which the key is queried
    @param algorithm Algorithm which is queried
    @return True if key supports specified algorithm for specified operation, False otherwise.
 */
Boolean SecKeyIsAlgorithmSupported(SecKeyRef key, SecKeyOperationType operation, SecKeyAlgorithm algorithm)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECKEY_H_ */
// ==========  Security.framework/Headers/SecTrust.h
/*
 * Copyright (c) 2002-2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
    @header SecTrust
    The functions and data types in SecTrust implement trust computation
    and allow the caller to apply trust decisions to the evaluation.
 */

#ifndef _SECURITY_SECTRUST_H_
#define _SECURITY_SECTRUST_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AvailabilityMacros.h>
#include <Availability.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecTrustResultType
    @abstract Specifies the trust result type.
    @discussion SecTrustResultType results have two dimensions.  They specify
    both whether evaluation succeeded and whether this is because of a user
    decision.  The commonly expected result is kSecTrustResultUnspecified,
    which indicates a positive result that wasn't decided by the user.  The
    common failure is kSecTrustResultRecoverableTrustFailure, which means a
    negative result.  kSecTrustResultProceed and kSecTrustResultDeny are the
    positive and negative result respectively when decided by the user.  User
    decisions are persisted through the use of SecTrustCopyExceptions() and
    SecTrustSetExceptions().  Finally, kSecTrustResultFatalTrustFailure is a
    negative result that must not be circumvented.
    @constant kSecTrustResultInvalid Indicates an invalid setting or result.
    This result usually means that SecTrustEvaluate has not yet been called.
    @constant kSecTrustResultProceed Indicates you may proceed.  This value
    may be returned by the SecTrustEvaluate function or stored as part of
    the user trust settings.
    @constant kSecTrustResultConfirm Indicates confirmation with the user
    is required before proceeding.  Important: this value is no longer returned
    or supported by SecTrustEvaluate or the SecTrustSettings API starting in
    OS X 10.5; its use is deprecated in OS X 10.9 and later, as well as in iOS.
    @constant kSecTrustResultDeny Indicates a user-configured deny; do not
    proceed. This value may be returned by the SecTrustEvaluate function
    or stored as part of the user trust settings.
    @constant kSecTrustResultUnspecified Indicates the evaluation succeeded
    and the certificate is implicitly trusted, but user intent was not
    explicitly specified.  This value may be returned by the SecTrustEvaluate
    function or stored as part of the user trust settings.
    @constant kSecTrustResultRecoverableTrustFailure Indicates a trust policy
    failure which can be overridden by the user.  This value may be returned
    by the SecTrustEvaluate function but not stored as part of the user
    trust settings.
    @constant kSecTrustResultFatalTrustFailure Indicates a trust failure
    which cannot be overridden by the user.  This value may be returned by the
    SecTrustEvaluate function but not stored as part of the user trust
    settings.
    @constant kSecTrustResultOtherError Indicates a failure other than that
    of trust evaluation. This value may be returned by the SecTrustEvaluate
    function but not stored as part of the user trust settings.
 */
typedef CF_ENUM(uint32_t, SecTrustResultType) {
    kSecTrustResultInvalid  CF_ENUM_AVAILABLE(10_3, 2_0) = 0,
    kSecTrustResultProceed  CF_ENUM_AVAILABLE(10_3, 2_0) = 1,
    kSecTrustResultConfirm  CF_ENUM_DEPRECATED(10_3, 10_9, 2_0, 7_0) = 2,
    kSecTrustResultDeny  CF_ENUM_AVAILABLE(10_3, 2_0) = 3,
    kSecTrustResultUnspecified  CF_ENUM_AVAILABLE(10_3, 2_0) = 4,
    kSecTrustResultRecoverableTrustFailure  CF_ENUM_AVAILABLE(10_3, 2_0) = 5,
    kSecTrustResultFatalTrustFailure  CF_ENUM_AVAILABLE(10_3, 2_0) = 6,
    kSecTrustResultOtherError  CF_ENUM_AVAILABLE(10_3, 2_0) = 7
};

/*!
    @typedef SecTrustRef
    @abstract CFType used for performing X.509 certificate trust evaluations.
 */
typedef struct CF_BRIDGED_TYPE(id) __SecTrust *SecTrustRef;

/*!
    @enum Trust Property Constants
    @discussion Predefined key constants used to obtain values in a
        per-certificate dictionary of trust evaluation results,
        as retrieved from a call to SecTrustCopyProperties.
    @constant kSecPropertyTypeTitle Specifies a key whose value is a
        CFStringRef containing the title (display name) of this certificate.
    @constant kSecPropertyTypeError Specifies a key whose value is a
        CFStringRef containing the reason for a trust evaluation failure.
 */
extern const CFStringRef kSecPropertyTypeTitle
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPropertyTypeError
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);

/*!
    @enum Trust Result Constants
    @discussion Predefined key constants used to obtain values in a
        dictionary of trust evaluation results for a certificate chain,
        as retrieved from a call to SecTrustCopyResult.
    @constant kSecTrustEvaluationDate
        This key will be present if a trust evaluation has been performed
        and results are available. Its value is a CFDateRef representing
        when the evaluation for this trust object took place.
    @constant kSecTrustExtendedValidation
        This key will be present and have a value of kCFBooleanTrue
        if this chain was validated for EV.
    @constant kSecTrustOrganizationName
        Organization name field of subject of leaf certificate. This
        field is meant to be displayed to the user as the validated
        name of the company or entity that owns the certificate if the
        kSecTrustExtendedValidation key is present.
    @constant kSecTrustResultValue
        This key will be present if a trust evaluation has been performed.
        Its value is a CFNumberRef representing the SecTrustResultType result
        for the evaluation.
    @constant kSecTrustRevocationChecked
        This key will be present iff this chain had its revocation checked.
        The value will be a kCFBooleanTrue if revocation checking was
        successful and none of the certificates in the chain were revoked.
        The value will be kCFBooleanFalse if no current revocation status
        could be obtained for one or more certificates in the chain due
        to connection problems or timeouts.  This is a hint to a client
        to retry revocation checking at a later time.
    @constant kSecTrustRevocationValidUntilDate
        This key will be present iff kSecTrustRevocationChecked has a
        value of kCFBooleanTrue. The value will be a CFDateRef representing
        the earliest date at which the revocation info for one of the
        certificates in this chain might change.
    @constant kSecTrustCertificateTransparency
        This key will be present and have a value of kCFBooleanTrue
        if this chain is CT qualified.
    @constant kSecTrustCertificateTransparencyWhiteList
        This key will be present and have a value of kCFBooleanTrue
        if this chain is EV, not CT qualified, but included of the CT WhiteList.
 */
extern const CFStringRef kSecTrustEvaluationDate
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustExtendedValidation
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustOrganizationName
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustResultValue
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustRevocationChecked
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustRevocationValidUntilDate
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecTrustCertificateTransparency
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
extern const CFStringRef kSecTrustCertificateTransparencyWhiteList
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_12, __MAC_10_13, __IPHONE_10_0, __IPHONE_11_0);

#ifdef __BLOCKS__
/*!
    @typedef SecTrustCallback
    @abstract Delivers the result from an asynchronous trust evaluation.
    @param trustRef A reference to the trust object which has been evaluated.
    @param trustResult The trust result of the evaluation. Additional status
    information can be obtained by calling SecTrustCopyProperties().
 */
typedef void (^SecTrustCallback)(SecTrustRef trustRef, SecTrustResultType trustResult);
#endif /* __BLOCKS__ */


/*!
    @function SecTrustGetTypeID
    @abstract Returns the type identifier of SecTrust instances.
    @result The CFTypeID of SecTrust instances.
 */
CFTypeID SecTrustGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @function SecTrustCreateWithCertificates
    @abstract Creates a trust object based on the given certificates and
    policies.
    @param certificates The group of certificates to verify.  This can either
    be a CFArrayRef of SecCertificateRef objects or a single SecCertificateRef
    @param policies An array of one or more policies. You may pass a
    SecPolicyRef to represent a single policy.
    @param trust On return, a pointer to the trust management reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion If multiple policies are passed in, all policies must verify
    for the chain to be considered valid.
 */
OSStatus SecTrustCreateWithCertificates(CFTypeRef certificates,
    CFTypeRef __nullable policies, SecTrustRef * __nonnull CF_RETURNS_RETAINED trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @function SecTrustSetPolicies
    @abstract Set the policies for which trust should be verified.
    @param trust A trust reference.
    @param policies An array of one or more policies. You may pass a
    SecPolicyRef to represent a single policy.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will invalidate the existing trust result,
    requiring a fresh evaluation for the newly-set policies.
 */
OSStatus SecTrustSetPolicies(SecTrustRef trust, CFTypeRef policies)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_6_0);

/*!
    @function SecTrustCopyPolicies
    @abstract Returns an array of policies used for this evaluation.
    @param trust  A reference to a trust object.
    @param policies On return, an array of policies used by this trust.
    Call the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustCopyPolicies(SecTrustRef trust, CFArrayRef * __nonnull CF_RETURNS_RETAINED policies)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_7_0);

/*!
    @function SecTrustSetNetworkFetchAllowed
    @abstract Specifies whether a trust evaluation is permitted to fetch missing
    intermediate certificates from the network.
    @param trust A trust reference.
    @param allowFetch If true, and a certificate's issuer is not present in the
    trust reference but its network location is known, the evaluation is permitted
    to attempt to download it automatically. Pass false to disable network fetch
    for this trust evaluation.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion By default, network fetch of missing certificates is enabled if
    the trust evaluation includes the SSL policy, otherwise it is disabled.
 */
OSStatus SecTrustSetNetworkFetchAllowed(SecTrustRef trust,
    Boolean allowFetch)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @function SecTrustGetNetworkFetchAllowed
    @abstract Returns whether a trust evaluation is permitted to fetch missing
    intermediate certificates from the network.
    @param trust A trust reference.
    @param allowFetch On return, the boolean pointed to by this parameter is
    set to true if the evaluation is permitted to download missing certificates.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion By default, network fetch of missing certificates is enabled if
    the trust evaluation includes the SSL policy, otherwise it is disabled.
 */
OSStatus SecTrustGetNetworkFetchAllowed(SecTrustRef trust,
    Boolean *allowFetch)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @function SecTrustSetAnchorCertificates
    @abstract Sets the anchor certificates for a given trust.
    @param trust A reference to a trust object.
    @param anchorCertificates An array of anchor certificates.
    Pass NULL to restore the default set of anchor certificates.
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion Calling this function without also calling
    SecTrustSetAnchorCertificatesOnly() will disable trusting any
    anchors other than the ones in anchorCertificates.
 */
OSStatus SecTrustSetAnchorCertificates(SecTrustRef trust,
    CFArrayRef __nullable anchorCertificates)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @function SecTrustSetAnchorCertificatesOnly
    @abstract Reenables trusting anchor certificates in addition to those
    passed in via the SecTrustSetAnchorCertificates API.
    @param trust A reference to a trust object.
    @param anchorCertificatesOnly If true, disables trusting any anchors other
    than the ones passed in via SecTrustSetAnchorCertificates().  If false,
    the built in anchor certificates are also trusted.
    @result A result code.  See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustSetAnchorCertificatesOnly(SecTrustRef trust,
    Boolean anchorCertificatesOnly)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @function SecTrustCopyCustomAnchorCertificates
    @abstract Returns an array of custom anchor certificates used by a given
    trust, as set by a prior call to SecTrustSetAnchorCertificates, or NULL if
    no custom anchors have been specified.
    @param trust  A reference to a trust object.
    @param anchors On return, an array of custom anchor certificates (roots)
    used by this trust, or NULL if no custom anchors have been specified. Call
    the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustCopyCustomAnchorCertificates(SecTrustRef trust,
    CFArrayRef * __nonnull CF_RETURNS_RETAINED anchors)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_7_0);

/*!
    @function SecTrustSetVerifyDate
    @abstract Set the date for which the trust should be verified.
    @param trust A reference to a trust object.
    @param verifyDate The date for which to verify trust.
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion This function lets you evaluate certificate validity for a
    given date (for example, to determine if a signature was valid on the date
    it was signed, even if the certificate has since expired.) If this function
    is not called, the time at which SecTrustEvaluate() is called is used
    implicitly as the verification time.
 */
OSStatus SecTrustSetVerifyDate(SecTrustRef trust, CFDateRef verifyDate)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @function SecTrustGetVerifyTime
    @abstract Returns the verify time.
    @param trust A reference to the trust object being verified.
    @result A CFAbsoluteTime value representing the time at which certificates
    should be checked for validity.
    @discussion This function retrieves the verification time for the given
    trust reference, as set by a prior call to SecTrustSetVerifyDate(). If the
    verification time has not been set, this function returns a value of 0,
    indicating that the current date/time is implicitly used for verification.
 */
CFAbsoluteTime SecTrustGetVerifyTime(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @function SecTrustEvaluate
    @abstract Evaluates a trust reference synchronously.
    @param trust A reference to the trust object to evaluate.
    @param result A pointer to a result type.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will completely evaluate trust before returning,
    possibly including network access to fetch intermediate certificates or to
    perform revocation checking. Since this function can block during those
    operations, you should call it from within a function that is placed on a
    dispatch queue, or in a separate thread from your application's main
    run loop. Alternatively, you can use the SecTrustEvaluateAsync function.
 */
OSStatus SecTrustEvaluate(SecTrustRef trust, SecTrustResultType *result)
    API_DEPRECATED_WITH_REPLACEMENT("SecTrustEvaluateWithError",
                                    macos(10.3, 10.15),
                                    ios(2.0, 13.0),
                                    watchos(1.0, 6.0),
                                    tvos(2.0, 13.0));

#ifdef __BLOCKS__
/*!
    @function SecTrustEvaluateAsync
    @abstract Evaluates a trust reference asynchronously.
    @param trust A reference to the trust object to evaluate.
    @param queue A dispatch queue on which the result callback should be
    executed. Pass NULL to use the current dispatch queue.
    @param result A SecTrustCallback block which will be executed when the
    trust evaluation is complete.
    @result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustEvaluateAsync(SecTrustRef trust,
    dispatch_queue_t __nullable queue, SecTrustCallback result)
    API_DEPRECATED_WITH_REPLACEMENT("SecTrustEvaluateAsyncWithError",
                                macos(10.7, 10.15),
                                ios(7.0, 13.0),
                                watchos(1.0, 6.0),
                                tvos(7.0, 13.0));
#endif

/*!
     @function SecTrustEvaluateWithError
     @abstract Evaluates a trust reference synchronously.
     @param trust A reference to the trust object to evaluate.
     @param error A pointer to an error object
     @result A boolean value indicating whether the certificate is trusted
     @discussion This function will completely evaluate trust before returning,
     possibly including network access to fetch intermediate certificates or to
     perform revocation checking. Since this function can block during those
     operations, you should call it from within a function that is placed on a
     dispatch queue, or in a separate thread from your application's main
     run loop.
     If the certificate is trusted and the result is true, the error will be set to NULL.
     If the certificate is not trusted or the evaluation was unable to complete, the result
     will be false and the error will be set with a description of the failure.
     The error contains a code for the most serious error encountered (if multiple trust
     failures occurred). The localized description indicates the certificate with the most
     serious problem and the type of error. The underlying error contains a localized
     description of each certificate in the chain that had an error and all errors found
     with that certificate.
 */
__attribute__((warn_unused_result)) bool
SecTrustEvaluateWithError(SecTrustRef trust, CFErrorRef _Nullable * _Nullable CF_RETURNS_RETAINED error)
    API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

#ifdef __BLOCKS__
/*!
     @typedef SecTrustWithErrorCallback
     @abstract Delivers the result from an asynchronous trust evaluation.
     @param trustRef A reference to the trust object which has been evaluated.
     @param result A boolean value indicating whether the certificate is trusted.
     @param error An error if the trust evaluation failed.
 */
typedef void (^SecTrustWithErrorCallback)(SecTrustRef trustRef, bool result, CFErrorRef _Nullable error);

/*!
    @function SecTrustEvaluateAsyncWithError
    @abstract Evaluates a trust reference asynchronously.
    @param trust A reference to the trust object to evaluate.
    @param queue A dispatch queue on which the result callback will be executed. Note that this
    function MUST be called from that queue.
    @param result A SecTrustWithErrorCallback block which will be executed when the trust evaluation
    is complete.
    The block is guaranteed to be called exactly once when the result code is errSecSuccess, and not
    called otherwise. Note that this block may be called synchronously inline if no asynchronous
    operations are required.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If the certificate is trusted, the callback will return a result parameter of true
    and the error will be set to NULL.
    If the certificate is not trusted or the evaluation was unable to complete, the result parameter
    will be false and the error will be set with a description of the failure. The error contains a
    code for the most serious error encountered (if multiple trust failures occurred). The localized
    description indicates the certificate with the most serious problem and the type of error. The
    underlying error contains a localized description of each certificate in the chain that had an
    error and all errors found with that certificate.
 */
OSStatus SecTrustEvaluateAsyncWithError(SecTrustRef trust, dispatch_queue_t queue, SecTrustWithErrorCallback result)
    API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
#endif /* __BLOCKS__ */

/*!
    @function SecTrustGetTrustResult
    @param trust A reference to a trust object.
    @param result A pointer to the result from the most recent call to
    SecTrustEvaluate for this trust reference. If SecTrustEvaluate has not been
    called or trust parameters have changed, the result is kSecTrustResultInvalid.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function replaces SecTrustGetResult for the purpose of
    obtaining the current evaluation result of a given trust reference.
 */
OSStatus SecTrustGetTrustResult(SecTrustRef trust,
    SecTrustResultType *result)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);

/*!
    @function SecTrustCopyPublicKey
    @abstract Return the public key for a leaf certificate after it has
    been evaluated.
    @param trust A reference to the trust object which has been evaluated.
    @result The certificate's public key, or NULL if it the public key could
    not be extracted (this can happen if the public key algorithm is not
    supported).  The caller is responsible for calling CFRelease on the
    returned key when it is no longer needed.
 */
__nullable
SecKeyRef SecTrustCopyPublicKey(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @function SecTrustGetCertificateCount
    @abstract Returns the number of certificates in an evaluated certificate
    chain.
    @param trust A reference to a trust object.
    @result The number of certificates in the trust chain, including the anchor.
    @discussion Important: if the trust reference has not yet been evaluated,
    this function will evaluate it first before returning. If speed is critical,
    you may want to call SecTrustGetTrustResult first to make sure that a
    result other than kSecTrustResultInvalid is present for the trust object.
 */
CFIndex SecTrustGetCertificateCount(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @function SecTrustGetCertificateAtIndex
    @abstract Returns a certificate from the trust chain.
    @param trust Reference to a trust object.
    @param ix The index of the requested certificate.  Indices run from 0
    (leaf) to the anchor (or last certificate found if no anchor was found).
    The leaf cert (index 0) is always present regardless of whether the trust
    reference has been evaluated or not.
    @result A SecCertificateRef for the requested certificate.
 */
__nullable
SecCertificateRef SecTrustGetCertificateAtIndex(SecTrustRef trust, CFIndex ix)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @function SecTrustCopyExceptions
    @abstract Returns an opaque cookie which will allow future evaluations
    of the current certificate to succeed.
    @param trust A reference to an evaluated trust object.
    @result An opaque cookie which when passed to SecTrustSetExceptions() will
    cause a call to SecTrustEvaluate() return kSecTrustResultProceed.  This
    will happen upon subsequent evaluation of the current certificate unless
    some new error starts happening that wasn't being reported when the cookie
    was returned from this function (for example, if the certificate expires
    then evaluation will start failing again until a new cookie is obtained.)
    @discussion Normally this API should only be called once the errors have
    been presented to the user and the user decided to trust the current
    certificate chain regardless of the errors being presented, for the
    current application/server/protocol combination.
 */
CFDataRef SecTrustCopyExceptions(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);

/*!
    @function SecTrustSetExceptions
    @abstract Set a trust cookie to be used for evaluating this certificate chain.
    @param trust A reference to a trust object.
    @param exceptions An exceptions cookie as returned by a call to
    SecTrustCopyExceptions() in the past.  You may pass NULL to clear any
    exceptions which have been previously set on this trust reference.
    @result Upon calling SecTrustEvaluate(), any failures that were present at the
    time the exceptions object was created are ignored, and instead of returning
    kSecTrustResultRecoverableTrustFailure, kSecTrustResultProceed will be returned
    (if the certificate for which exceptions was created matches the current leaf
    certificate).
    @result Returns true if the exceptions cookies was valid and matches the current
    leaf certificate, false otherwise.  This function will invalidate the existing
    trust result, requiring a subsequent evaluation for the newly-set exceptions.
    Note that this function returning true doesn't mean the caller can skip calling
    SecTrustEvaluate, as there may be new errors since the exceptions cookie was
    created (for example, a certificate may have subsequently expired.)
    @discussion Clients of this interface will need to establish the context of this
    exception to later decide when this exception cookie is to be used.
    Examples of this context would be the server we are connecting to, the ssid
    of the wireless network for which this cert is needed, the account for which
    this cert should be considered valid, and so on.
 */
bool SecTrustSetExceptions(SecTrustRef trust, CFDataRef __nullable exceptions)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);

/*!
    @function SecTrustCopyProperties
    @abstract Return a property array for this trust evaluation.
    @param trust A reference to a trust object. If the trust has not been
    evaluated, the returned property array will be empty.
    @result A property array. It is the caller's responsibility to CFRelease
    the returned array when it is no longer needed.
    @discussion This function returns an ordered array of CFDictionaryRef
    instances for each certificate in the chain. Indices run from 0 (leaf) to
    the anchor (or last certificate found if no anchor was found.) See the
    "Trust Property Constants" section for a list of currently defined keys.
 */
__nullable
CFArrayRef SecTrustCopyProperties(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @function SecTrustCopyResult
    @abstract Returns a dictionary containing information about the
    evaluated certificate chain for use by clients.
    @param trust A reference to a trust object.
    @result A dictionary with various fields that can be displayed to the user,
    or NULL if no additional info is available or the trust has not yet been
    validated.  The caller is responsible for calling CFRelease on the value
    returned when it is no longer needed.
    @discussion Returns a dictionary for the overall trust evaluation. See the
    "Trust Result Constants" section for a list of currently defined keys.
 */
__nullable
CFDictionaryRef SecTrustCopyResult(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @function SecTrustSetOCSPResponse
    @abstract Attach OCSPResponse data to a trust object.
    @param trust A reference to a trust object.
    @param responseData This may be either a CFData object containing a single
    DER-encoded OCSPResponse (per RFC 2560), or a CFArray of these.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Allows the caller to provide OCSPResponse data (which may be
    obtained during a TLS/SSL handshake, per RFC 3546) as input to a trust
    evaluation. If this data is available, it can obviate the need to contact
    an OCSP server for current revocation information.
 */
OSStatus SecTrustSetOCSPResponse(SecTrustRef trust, CFTypeRef __nullable responseData)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
     @function SecTrustSignedCertificateTimestamps
     @abstract Attach SignedCertificateTimestamp data to a trust object.
     @param trust A reference to a trust object.
     @param sctArray is a CFArray of CFData objects each containing a SCT (per RFC 6962).
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion Allows the caller to provide SCT data (which may be
     obtained during a TLS/SSL handshake, per RFC 6962) as input to a trust
     evaluation.
 */
OSStatus SecTrustSetSignedCertificateTimestamps(SecTrustRef trust, CFArrayRef __nullable sctArray)
    API_AVAILABLE(macos(10.14.2), ios(12.1.1), tvos(12.1.1), watchos(5.1.1));

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

/*
 *  Legacy functions (OS X only)
 */
#if TARGET_OS_OSX
#include <Security/cssmtype.h>
#include <Security/cssmapple.h>

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecTrustUserSetting
    @abstract Specifies a user-specified trust setting value.
    @discussion Deprecated in OS X 10.9. User trust settings are managed by
    functions in SecTrustSettings.h (starting with OS X 10.5), and by the
    SecTrustCopyExceptions and SecTrustSetExceptions functions (starting with
    iOS 4 and OS X 10.9). The latter two functions are recommended for both OS X
    and iOS, as they avoid the need to explicitly specify these values.
 */
typedef SecTrustResultType SecTrustUserSetting
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);

/*!
    @typedef SecTrustOptionFlags
    @abstract Options for customizing trust evaluation.
    @constant kSecTrustOptionAllowExpired Allow expired certificates.
    @constant kSecTrustOptionLeafIsCA Allow CA as leaf certificate.
    @constant kSecTrustOptionFetchIssuerFromNet Allow network fetch of CA cert.
    @constant kSecTrustOptionAllowExpiredRoot Allow expired roots.
    @constant kSecTrustOptionRequireRevPerCert Require positive revocation
    check per certificate.
    @constant kSecTrustOptionUseTrustSettings Use TrustSettings instead of
    anchors.
    @constant kSecTrustOptionImplicitAnchors Properly self-signed certs are
    treated as anchors implicitly.
 */
typedef CF_OPTIONS(uint32_t, SecTrustOptionFlags) {
    kSecTrustOptionAllowExpired       = 0x00000001,
    kSecTrustOptionLeafIsCA           = 0x00000002,
    kSecTrustOptionFetchIssuerFromNet = 0x00000004,
    kSecTrustOptionAllowExpiredRoot   = 0x00000008,
    kSecTrustOptionRequireRevPerCert  = 0x00000010,
    kSecTrustOptionUseTrustSettings   = 0x00000020,
    kSecTrustOptionImplicitAnchors    = 0x00000040
};

/*!
    @function SecTrustSetOptions
    @abstract Sets optional flags for customizing a trust evaluation.
    @param trustRef A trust reference.
    @param options Flags to change evaluation behavior for this trust.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is not available on iOS. Use SecTrustSetExceptions
    and SecTrustCopyExceptions to modify default trust results, and
    SecTrustSetNetworkFetchAllowed to specify whether missing CA certificates
    can be fetched from the network.
 */
OSStatus SecTrustSetOptions(SecTrustRef trustRef, SecTrustOptionFlags options)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function SecTrustSetParameters
    @abstract Sets the action and action data for a trust object.
    @param trustRef The reference to the trust to change.
    @param action A trust action.
    @param actionData A reference to data associated with this action.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is deprecated in OS X 10.7 and later, where it
    was replaced by SecTrustSetOptions, and is not available on iOS. Your code
    should use SecTrustSetExceptions and SecTrustCopyExceptions to modify default
    trust results, and SecTrustSetNetworkFetchAllowed to specify whether missing
    CA certificates can be fetched from the network.
 */
OSStatus SecTrustSetParameters(SecTrustRef trustRef,
    CSSM_TP_ACTION action, CFDataRef actionData)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustSetKeychains
    @abstract Sets the keychains for a given trust object.
    @param trust A reference to a trust object.
    @param keychainOrArray A reference to an array of keychains to search, a
    single keychain, or NULL to use the default keychain search list.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is deprecated in macOS 10.13 and later. Beginning in
    macOS 10.12, this function no longer affected the behavior of the trust
    evaluation: the user's keychain search list and the system
    anchors keychain are searched for certificates to complete the chain. To change
    the keychains that are searched, callers must use SecKeychainSetSearchList to
    change the user's keychain search list.
    Note: this function was never applicable to iOS.
 */
OSStatus SecTrustSetKeychains(SecTrustRef trust, CFTypeRef __nullable keychainOrArray)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_13, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustGetResult
    @abstract Returns detailed information on the outcome of an evaluation.
    @param trustRef A reference to a trust object.
    @param result A pointer to the result from the call to SecTrustEvaluate.
    @param certChain On return, a pointer to the certificate chain used to
    validate the input certificate. Call the CFRelease function to release
    this pointer.
    @param statusChain On return, a pointer to the status of the certificate
    chain. Do not attempt to free this pointer; it remains valid until the
    trust is destroyed or the next call to SecTrustEvaluate.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is deprecated in OS X 10.7 and later,
    and is not available on iOS.
    To get the complete certificate chain, use SecTrustGetCertificateCount and
    SecTrustGetCertificateAtIndex. To get detailed status information for each
    certificate, use SecTrustCopyProperties. To get the overall trust result
    for the evaluation, use SecTrustGetTrustResult.
 */
OSStatus SecTrustGetResult(SecTrustRef trustRef, SecTrustResultType * __nullable result,
    CFArrayRef * __nullable CF_RETURNS_RETAINED certChain, CSSM_TP_APPLE_EVIDENCE_INFO * __nullable * __nullable statusChain)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustGetCssmResult
    @abstract Gets the CSSM trust result.
    @param trust A reference to a trust.
    @param result On return, a pointer to the CSSM trust result.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is deprecated in OS X 10.7 and later,
    and is not available on iOS.
    To get detailed status information for each certificate, use
    SecTrustCopyProperties. To get the overall trust result for the evaluation,
    use SecTrustGetTrustResult.
 */
OSStatus SecTrustGetCssmResult(SecTrustRef trust,
    CSSM_TP_VERIFY_CONTEXT_RESULT_PTR __nullable * __nonnull result)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustGetCssmResultCode
    @abstract Gets the result code from the most recent call to SecTrustEvaluate
    for the specified trust.
    @param trust A reference to a trust.
    @param resultCode On return, the result code produced by the most recent
    evaluation of the given trust (cssmerr.h). The value of resultCode is
    undefined if SecTrustEvaluate has not been called.
    @result A result code. See "Security Error Codes" (SecBase.h). Returns
    errSecTrustNotAvailable if SecTrustEvaluate has not been called for the
    specified trust.
    @discussion This function is deprecated in OS X 10.7 and later,
    and is not available on iOS.
    To get detailed status information for each certificate, use
    SecTrustCopyProperties. To get the overall trust result for the evaluation,
    use SecTrustGetTrustResult.
 */
OSStatus SecTrustGetCssmResultCode(SecTrustRef trust, OSStatus *resultCode)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustGetTPHandle
    @abstract Gets the CSSM trust handle
    @param trust A reference to a trust.
    @param handle On return, a CSSM trust handle.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is deprecated in OS X 10.7 and later.
 */
OSStatus SecTrustGetTPHandle(SecTrustRef trust, CSSM_TP_HANDLE *handle)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
    @function SecTrustCopyAnchorCertificates
    @abstract Returns an array of default anchor (root) certificates used by
    the system.
    @param anchors On return, an array containing the system's default anchors
    (roots). Call the CFRelease function to release this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function is not available on iOS, as certificate data
    for system-trusted roots is currently unavailable on that platform.
 */
OSStatus SecTrustCopyAnchorCertificates(CFArrayRef * __nonnull CF_RETURNS_RETAINED anchors)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

#endif /* TARGET_OS_MAC && !TARGET_OS_IPHONE */

__END_DECLS

#endif /* !_SECURITY_SECTRUST_H_ */
// ==========  Security.framework/Headers/SecPolicy.h
/*
 * Copyright (c) 2002-2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
     @header SecPolicy
     The functions provided in SecPolicy.h provide an interface to various
     X.509 certificate trust policies.
 */

#ifndef _SECURITY_SECPOLICY_H_
#define _SECURITY_SECPOLICY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <Security/SecBase.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
     @enum Policy Constants
     @discussion Predefined constants used to specify a policy.
     @constant kSecPolicyAppleX509Basic
     @constant kSecPolicyAppleSSL
     @constant kSecPolicyAppleSMIME
     @constant kSecPolicyAppleEAP
     @constant kSecPolicyAppleiChat
     @constant kSecPolicyAppleIPsec
     @constant kSecPolicyApplePKINITClient
     @constant kSecPolicyApplePKINITServer
     @constant kSecPolicyAppleCodeSigning
     @constant kSecPolicyMacAppStoreReceipt
     @constant kSecPolicyAppleIDValidation
     @constant kSecPolicyAppleTimeStamping
     @constant kSecPolicyAppleRevocation
     @constant kSecPolicyApplePassbookSigning
     @constant kSecPolicyApplePayIssuerEncryption
 */
extern const CFStringRef kSecPolicyAppleX509Basic
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleSSL
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleSMIME
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleEAP
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleIPsec
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
#if TARGET_OS_OSX
extern const CFStringRef kSecPolicyAppleiChat
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);
#endif
extern const CFStringRef kSecPolicyApplePKINITClient
    API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);
extern const CFStringRef kSecPolicyApplePKINITServer
    API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);
extern const CFStringRef kSecPolicyAppleCodeSigning
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyMacAppStoreReceipt
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_9_0);
extern const CFStringRef kSecPolicyAppleIDValidation
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleTimeStamping
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
extern const CFStringRef kSecPolicyAppleRevocation
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecPolicyApplePassbookSigning
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecPolicyApplePayIssuerEncryption
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*!
    @enum Policy Value Constants
    @abstract Predefined property key constants used to get or set values in
    a dictionary for a policy instance.
    @discussion
        All policies will have the following read-only value:
            kSecPolicyOid       (the policy object identifier)

        Additional policy values which your code can optionally set:
            kSecPolicyName      (name which must be matched)
            kSecPolicyClient    (evaluate for client, rather than server)
            kSecPolicyRevocationFlags   (only valid for a revocation policy)
            kSecPolicyTeamIdentifier    (only valid for a Passbook signing policy)

    @constant kSecPolicyOid Specifies the policy OID (value is a CFStringRef)
    @constant kSecPolicyName Specifies a CFStringRef (or CFArrayRef of same)
        containing a name which must be matched in the certificate to satisfy
        this policy. For SSL/TLS, EAP, and IPSec policies, this specifies the
        server name which must match the common name of the certificate.
        For S/MIME, this specifies the RFC822 email address. For Passbook
        signing, this specifies the pass signer.
    @constant kSecPolicyClient Specifies a CFBooleanRef value that indicates
        this evaluation should be for a client certificate. If not set (or
        false), the policy evaluates the certificate as a server certificate.
    @constant kSecPolicyRevocationFlags Specifies a CFNumberRef that holds a
        kCFNumberCFIndexType bitmask value. See "Revocation Policy Constants"
        for a description of individual bits in this value.
    @constant kSecPolicyTeamIdentifier Specifies a CFStringRef containing a
        team identifier which must be matched in the certificate to satisfy
        this policy. For the Passbook signing policy, this string must match
        the Organizational Unit field of the certificate subject.
 */
extern const CFStringRef kSecPolicyOid
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyName
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyClient
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyRevocationFlags
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecPolicyTeamIdentifier
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


/*!
 @function SecPolicyGetTypeID
 @abstract Returns the type identifier of SecPolicy instances.
 @result The CFTypeID of SecPolicy instances.
 */
CFTypeID SecPolicyGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
 @function SecPolicyCopyProperties
 @abstract Returns a dictionary of this policy's properties.
 @param policyRef A policy reference.
 @result A properties dictionary. See "Policy Value Constants" for a list
 of currently defined property keys. It is the caller's responsibility to
 CFRelease this reference when it is no longer needed.
 @result A result code. See "Security Error Codes" (SecBase.h).
 @discussion This function returns the properties for a policy, as set by the
 policy's construction function or by a prior call to SecPolicySetProperties.
 */
__nullable
CFDictionaryRef SecPolicyCopyProperties(SecPolicyRef policyRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);

/*!
 @function SecPolicyCreateBasicX509
 @abstract Returns a policy object for the default X.509 policy.
 @result A policy object. The caller is responsible for calling CFRelease
 on this when it is no longer needed.
 */
SecPolicyRef SecPolicyCreateBasicX509(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
 @function SecPolicyCreateSSL
 @abstract Returns a policy object for evaluating SSL certificate chains.
 @param server Passing true for this parameter creates a policy for SSL
 server certificates.
 @param hostname (Optional) If present, the policy will require the specified
 hostname to match the hostname in the leaf certificate.
 @result A policy object. The caller is responsible for calling CFRelease
 on this when it is no longer needed.
 */
SecPolicyRef SecPolicyCreateSSL(Boolean server, CFStringRef __nullable hostname)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
     @enum Revocation Policy Constants
     @abstract Predefined constants which allow you to specify how revocation
     checking will be performed for a trust evaluation.
     @constant kSecRevocationOCSPMethod If this flag is set, perform revocation
     checking using OCSP (Online Certificate Status Protocol).
     @constant kSecRevocationCRLMethod If this flag is set, perform revocation
     checking using the CRL (Certificate Revocation List) method.
     @constant kSecRevocationPreferCRL If this flag is set, then CRL revocation
     checking will be preferred over OCSP (by default, OCSP is preferred.)
     Note that this flag only matters if both revocation methods are specified.
     @constant kSecRevocationRequirePositiveResponse If this flag is set, then
     the policy will fail unless a verified positive response is obtained. If
     the flag is not set, revocation checking is done on a "best attempt" basis,
     where failure to reach the server is not considered fatal.
     @constant kSecRevocationNetworkAccessDisabled If this flag is set, then
     no network access is performed; only locally cached replies are consulted.
     This constant disallows network access for both revocation checks and
     intermediate CA issuer fetching.
     @constant kSecRevocationUseAnyAvailableMethod Specifies that either
     OCSP or CRL may be used, depending on the method(s) specified in the
     certificate and the value of kSecRevocationPreferCRL.
 */
CF_ENUM(CFOptionFlags) {
    kSecRevocationOCSPMethod = (1 << 0),
    kSecRevocationCRLMethod = (1 << 1),
    kSecRevocationPreferCRL = (1 << 2),
    kSecRevocationRequirePositiveResponse = (1 << 3),
    kSecRevocationNetworkAccessDisabled = (1 << 4),
    kSecRevocationUseAnyAvailableMethod = (kSecRevocationOCSPMethod |
                                           kSecRevocationCRLMethod)
};

/*!
     @function SecPolicyCreateRevocation
     @abstract Returns a policy object for checking revocation of certificates.
     @result A policy object. The caller is responsible for calling CFRelease
     on this when it is no longer needed.
     @param revocationFlags Flags to specify revocation checking options.
     @discussion Use this function to create a revocation policy with behavior
     specified by revocationFlags. See the "Revocation Policy Constants" section
     for a description of these flags. Note: it is usually not necessary to
     create a revocation policy yourself unless you wish to override default
     system behavior (e.g. to force a particular method, or to disable
     revocation checking entirely.)
 */
__nullable
SecPolicyRef SecPolicyCreateRevocation(CFOptionFlags revocationFlags)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
     @function SecPolicyCreateWithProperties
     @abstract Returns a policy object based on an object identifier for the
     policy type. See the "Policy Constants" section for a list of defined
     policy object identifiers.
     @param policyIdentifier The identifier for the desired policy type.
     @param properties (Optional) A properties dictionary. See "Policy Value
     Constants" for a list of currently defined property keys.
     @result The returned policy reference, or NULL if the policy could not be
     created.
 */
__nullable
SecPolicyRef SecPolicyCreateWithProperties(CFTypeRef policyIdentifier,
                                           CFDictionaryRef __nullable properties)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

/*
 *  Legacy functions (OS X only)
 */
#if TARGET_OS_OSX
#include <Security/cssmtype.h>

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @enum Policy Value Constants (OS X)
    @discussion Predefined property key constants used to get or set values in
        a dictionary for a policy instance.

        Some policy values may specify CFBooleanRef key usage constraints:
            kSecPolicyKU_DigitalSignature
            kSecPolicyKU_NonRepudiation
            kSecPolicyKU_KeyEncipherment
            kSecPolicyKU_DataEncipherment
            kSecPolicyKU_KeyAgreement
            kSecPolicyKU_KeyCertSign
            kSecPolicyKU_CRLSign
            kSecPolicyKU_EncipherOnly
            kSecPolicyKU_DecipherOnly

        kSecPolicyKU policy values define certificate-level key purposes,
        in contrast to the key-level definitions in SecItem.h

        For example, a key in a certificate might be acceptable to use for
        signing a CRL, but not for signing another certificate. In either
        case, this key would have the ability to sign (i.e. kSecAttrCanSign
        is true), but may only sign for specific purposes allowed by these
        policy constants. Similarly, a public key might have the capability
        to perform encryption or decryption, but the certificate in which it
        resides might have a decipher-only certificate policy.

        These constants correspond to values defined in RFC 5280, section
        4.2.1.3 (Key Usage) which define the purpose of a key contained in a
        certificate, in contrast to section 4.1.2.7 which define the uses that
        a key is capable of.

        Note: these constants are not available on iOS. Your code should
        avoid direct reliance on these values for making policy decisions
        and use higher level policies where possible.

    @constant kSecPolicyKU_DigitalSignature Specifies that the certificate must
        have a key usage that allows it to be used for signing.
    @constant kSecPolicyKU_NonRepudiation Specifies that the certificate must
        have a key usage that allows it to be used for non-repudiation.
    @constant kSecPolicyKU_KeyEncipherment Specifies that the certificate must
        have a key usage that allows it to be used for key encipherment.
    @constant kSecPolicyKU_DataEncipherment Specifies that the certificate must
        have a key usage that allows it to be used for data encipherment.
    @constant kSecPolicyKU_KeyAgreement Specifies that the certificate must
        have a key usage that allows it to be used for key agreement.
    @constant kSecPolicyKU_KeyCertSign Specifies that the certificate must
        have a key usage that allows it to be used for signing certificates.
    @constant kSecPolicyKU_CRLSign Specifies that the certificate must
        have a key usage that allows it to be used for signing CRLs.
    @constant kSecPolicyKU_EncipherOnly Specifies that the certificate must
        have a key usage that permits it to be used for encryption only.
    @constant kSecPolicyKU_DecipherOnly Specifies that the certificate must
        have a key usage that permits it to be used for decryption only.
 */
extern const CFStringRef kSecPolicyKU_DigitalSignature
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_NonRepudiation
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_KeyEncipherment
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_DataEncipherment
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_KeyAgreement
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_KeyCertSign
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_CRLSign
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_EncipherOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyKU_DecipherOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
     @function SecPolicyCreateWithOID
     @abstract Returns a policy object based on an object identifier for the
     policy type. See the "Policy Constants" section for a list of defined
     policy object identifiers.
     @param policyOID The OID of the desired policy.
     @result The returned policy reference, or NULL if the policy could not be
     created.
     @discussion This function is deprecated in Mac OS X 10.9 and later;
     use SecPolicyCreateWithProperties (or a more specific policy creation
     function) instead.
 */
__nullable
SecPolicyRef SecPolicyCreateWithOID(CFTypeRef policyOID)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);

/*!
     @function SecPolicyGetOID
     @abstract Returns a policy's object identifier.
     @param policyRef A policy reference.
     @param oid On return, a pointer to the policy's object identifier.
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This function is deprecated in Mac OS X 10.7 and later;
     use SecPolicyCopyProperties instead.
 */
OSStatus SecPolicyGetOID(SecPolicyRef policyRef, CSSM_OID *oid)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
     @function SecPolicyGetValue
     @abstract Returns a policy's value.
     @param policyRef A policy reference.
     @param value On return, a pointer to the policy's value.
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This function is deprecated in Mac OS X 10.7 and later;
     use SecPolicyCopyProperties instead.
 */
OSStatus SecPolicyGetValue(SecPolicyRef policyRef, CSSM_DATA *value)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
     @function SecPolicySetValue
     @abstract Sets a policy's value.
     @param policyRef A policy reference.
     @param value The value to be set into the policy object, replacing any
     previous value.
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This function is deprecated in Mac OS X 10.7 and later. Policy
     instances should be considered read-only; in cases where your code would
     consider changing properties of a policy, it should instead create a new
     policy instance with the desired properties.
 */
OSStatus SecPolicySetValue(SecPolicyRef policyRef, const CSSM_DATA *value)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

/*!
     @function SecPolicySetProperties
     @abstract Sets a policy's properties.
     @param policyRef A policy reference.
     @param properties A properties dictionary. See "Policy Value Constants"
     for a list of currently defined property keys. This dictionary replaces the
     policy's existing properties, if any. Note that the policy OID (specified
     by kSecPolicyOid) is a read-only property of the policy and cannot be set.
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This function is deprecated in Mac OS X 10.9 and later. Policy
     instances should be considered read-only; in cases where your code would
     consider changing properties of a policy, it should instead create a new
     policy instance with the desired properties.
 */
OSStatus SecPolicySetProperties(SecPolicyRef policyRef,
                                CFDictionaryRef properties)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);

/*!
     @function SecPolicyGetTPHandle
     @abstract Returns the CSSM trust policy handle for the given policy.
     @param policyRef A policy reference.
     @param tpHandle On return, a pointer to a value of type CSSM_TP_HANDLE.
     @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This function is deprecated in Mac OS X 10.7 and later.
 */
OSStatus SecPolicyGetTPHandle(SecPolicyRef policyRef, CSSM_TP_HANDLE *tpHandle)
    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

#endif /* TARGET_OS_MAC && !TARGET_OS_IPHONE */

__END_DECLS

#endif /* !_SECURITY_SECPOLICY_H_ */
// ==========  Security.framework/Headers/SecProtocolOptions.h
/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef SecProtocolOptions_h
#define SecProtocolOptions_h

#include <Security/SecProtocolObject.h>
#include <Security/SecProtocolTypes.h>
#include <Security/SecProtocolMetadata.h>
#include <Security/SecTrust.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>

#include <dispatch/dispatch.h>
#include <os/object.h>

/*!
 * The following diagram shows how clients interact with sec_protocol_options
 * and sec_protocol_metadata when configuring and using network security protocols.
 *
 *                    +--------+
 *                    | Client |
 *                    +-+---/ \+
 *                      |    |
 *        +-------------+    +-------------+
 *        | (1) set             (2) get    |
 *        | options             metadata   |
 * +-----\ /---------------+  +------------+----------+
 * | sec_protocol_options  |  | sec_protocol_metadata |
 * +-----------------------+  +-----------------------+
 *
 * Clients configure security protocols with `sec_protocol_options` instances.
 * And they inspect protocol instances using `sec_protocol_metadata` instances.
 */

#ifndef SEC_OBJECT_IMPL
/*!
 * A `sec_protocol_options` instance is a container of options for security protocol instances,
 * such as TLS. Protocol options are used to configure security protocols in the network stack.
 * For example, clients may set the maximum and minimum allowed TLS versions through protocol
 * options.
 */
SEC_OBJECT_DECL(sec_protocol_options);
#endif // !SEC_OBJECT_IMPL

__BEGIN_DECLS

SEC_ASSUME_NONNULL_BEGIN

/*!
 * @function sec_protocol_options_are_equal
 *
 * @abstract
 *      Compare two `sec_protocol_options_t` instances.
 *
 * @param optionsA
 *      A `sec_protocol_options_t` instance.
 *
 * @param optionsB
 *      A `sec_protocol_options_t` instance.
 *
 * @return True if equal, and false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
sec_protocol_options_are_equal(sec_protocol_options_t optionsA, sec_protocol_options_t optionsB);

/*!
 * @function sec_protocol_options_set_local_identity
 *
 * @abstract
 *      Set the local identity to be used for this protocol instance.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param identity
 *      A `sec_identity_t` instance carrying the private key and certificate.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_local_identity(sec_protocol_options_t options, sec_identity_t identity);

/*!
 * @function sec_protocol_options_append_tls_ciphersuite
 *
 * @abstract
 *      Append a TLS ciphersuite to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param ciphersuite
 *      A `tls_ciphersuite_t` value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
sec_protocol_options_append_tls_ciphersuite(sec_protocol_options_t options, tls_ciphersuite_t ciphersuite);

/*!
 * @function sec_protocol_options_add_tls_ciphersuite
 *
 * @abstract
 *      Add a TLS ciphersuite to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param ciphersuite
 *      A SSLCipherSuite value.
 */
API_DEPRECATED("Use sec_protocol_options_append_tls_ciphersuite", macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
API_UNAVAILABLE(uikitformac)
void
sec_protocol_options_add_tls_ciphersuite(sec_protocol_options_t options, SSLCipherSuite ciphersuite);

/*!
 * @function sec_protocol_options_append_tls_ciphersuite_group
 *
 * @abstract
 *      Append a TLS ciphersuite group to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param group
 *      A SSLCipherSuiteGroup value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
sec_protocol_options_append_tls_ciphersuite_group(sec_protocol_options_t options, tls_ciphersuite_group_t group);

/*!
 * @function sec_protocol_options_add_tls_ciphersuite_group
 *
 * @abstract
 *      Add a TLS ciphersuite group to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param group
 *      A SSLCipherSuiteGroup value.
 */
API_DEPRECATED("Use sec_protocol_options_append_tls_ciphersuite_group", macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
API_UNAVAILABLE(uikitformac)
void
sec_protocol_options_add_tls_ciphersuite_group(sec_protocol_options_t options, SSLCiphersuiteGroup group);

/*!
 * @function sec_protocol_options_set_tls_min_version
 *
 * @abstract
 *      Set the minimum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A SSLProtocol enum value.
 */
API_DEPRECATED_WITH_REPLACEMENT("sec_protocol_options_set_min_tls_protocol_version",
                                macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
API_UNAVAILABLE(uikitformac)
void
sec_protocol_options_set_tls_min_version(sec_protocol_options_t options, SSLProtocol version);

/*!
 * @function sec_protocol_options_set_min_tls_protocol_version
 *
 * @abstract
 *      Set the minimum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A tls_protocol_version_t enum value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
sec_protocol_options_set_min_tls_protocol_version(sec_protocol_options_t options, tls_protocol_version_t version);

/*!
 * @function sec_protocol_options_get_default_min_tls_protocol_version
 *
 * @abstract
 *      Get the system default minimum TLS protocol version.
 *
 * @return The default minimum TLS version.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
tls_protocol_version_t
sec_protocol_options_get_default_min_tls_protocol_version(void);

/*!
 * @function sec_protocol_options_get_default_min_dtls_protocol_version
 *
 * @abstract
 *      Get the system default minimum DTLS protocol version.
 *
 * @return The default minimum DTLS version.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
tls_protocol_version_t
sec_protocol_options_get_default_min_dtls_protocol_version(void);

/*!
 * @function sec_protocol_options_set_tls_max_version
 *
 * @abstract
 *      Set the maximum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A SSLProtocol enum value.
 */
API_DEPRECATED_WITH_REPLACEMENT("sec_protocol_options_set_max_tls_protocol_version",
                                macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
API_UNAVAILABLE(uikitformac)
void
sec_protocol_options_set_tls_max_version(sec_protocol_options_t options, SSLProtocol version);

/*!
 * @function sec_protocol_options_set_max_tls_protocol_version
 *
 * @abstract
 *      Set the maximum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A tls_protocol_version_t enum value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
sec_protocol_options_set_max_tls_protocol_version(sec_protocol_options_t options, tls_protocol_version_t version);

/*!
 * @function sec_protocol_options_get_default_max_tls_protocol_version
 *
 * @abstract
 *      Get the system default maximum TLS protocol version.
 *
 * @return The default maximum TLS version.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
tls_protocol_version_t
sec_protocol_options_get_default_max_tls_protocol_version(void);

/*!
 * @function sec_protocol_options_get_default_max_tls_protocol_version
 *
 * @abstract
 *      Get the system default maximum DTLS protocol version.
 *
 * @return The default maximum DTLS version.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
tls_protocol_version_t
sec_protocol_options_get_default_max_dtls_protocol_version(void);

/*!
 * @function sec_protocol_options_add_tls_application_protocol
 *
 * @abstract
 *      Add an application protocol supported by clients of this protocol instance.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param application_protocol
 *      A NULL-terminated string defining the application protocol.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_tls_application_protocol(sec_protocol_options_t options, const char *application_protocol);

/*!
 * @function sec_protocol_options_set_tls_server_name
 *
 * @abstract
 *      Set the server (domain) name to be used in the TLS SNI. This will override
 *      the server name obtained from the endpoint.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param server_name
 *      A NULL-terminated string carrying the server (domain) name.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_server_name(sec_protocol_options_t options, const char *server_name);

/*!
 * @function sec_protocol_options_set_tls_diffie_hellman_parameters
 *
 * @abstract
 *      Set the supported Diffie-Hellman parameters.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param params
 *      A dispatch_data_t containing legacy Diffie-Hellman parameters.
 */
API_DEPRECATED("DHE ciphersuites are no longer supported", macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
void
sec_protocol_options_set_tls_diffie_hellman_parameters(sec_protocol_options_t options, dispatch_data_t params);

/*!
 * @function sec_protocol_options_add_pre_shared_key
 *
 * @abstract
 *      Add a pre-shared key (PSK) and its identity to the options.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param psk
 *      A dispatch_data_t containing a PSK blob.
 *
 * @param psk_identity
 *      A dispatch_data_t containing a PSK identity blob.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_pre_shared_key(sec_protocol_options_t options, dispatch_data_t psk, dispatch_data_t psk_identity);

/*!
 * @function sec_protocol_options_set_tls_tickets_enabled
 *
 * @abstract
 *      Enable or disable TLS session ticket support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param tickets_enabled
 *      Flag to enable or disable TLS session ticket support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_tickets_enabled(sec_protocol_options_t options, bool tickets_enabled);

/*!
 * @function sec_protocol_options_set_tls_is_fallback_attempt
 *
 * @abstract
 *      Signal if this is a TLS fallback attempt.
 *
 *      A fallback attempt is one following a previously failed TLS connection
 *      due to version or parameter incompatibility, e.g., when speaking to a server
 *      that does not support a client-offered ciphersuite.
 *
 *      Clients MUST NOT enable fallback for fresh connections.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param is_fallback_attempt
 *      Set a flag indicating that this is a TLS fallback attempt.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_is_fallback_attempt(sec_protocol_options_t options, bool is_fallback_attempt);

/*!
 * @function sec_protocol_options_set_tls_resumption_enabled
 *
 * @abstract
 *      Enable or disable TLS session resumption.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param resumption_enabled
 *      Flag to enable or disable TLS session resumption.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_resumption_enabled(sec_protocol_options_t options, bool resumption_enabled);

/*!
 * @function sec_protocol_options_set_tls_false_start_enabled
 *
 * @abstract
 *      Enable or disable TLS False Start.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param false_start_enabled
 *      Flag to enable or disable TLS False Start.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_false_start_enabled(sec_protocol_options_t options, bool false_start_enabled);

/*!
 * @function nw_protocol_options_set_tls_ocsp_enabled
 *
 * @abstract
 *      Enable or disable OCSP support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param ocsp_enabled
 *      Flag to enable or disable OCSP support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_ocsp_enabled(sec_protocol_options_t options, bool ocsp_enabled);

/*!
 * @function sec_protocol_options_set_tls_sct_enabled
 *
 * @abstract
 *      Enable or disable SCT (signed certificate timestamp) support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param sct_enabled
 *      Flag to enable or disable SCT support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_sct_enabled(sec_protocol_options_t options, bool sct_enabled);

/*!
 * @function sec_protocol_options_set_tls_renegotiation_enabled
 *
 * @abstract
 *      Enable or disable TLS (1.2 and prior) session renegotiation. This defaults to `true`.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param renegotiation_enabled
 *      Flag to enable or disable TLS (1.2 and prior) session renegotiation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_renegotiation_enabled(sec_protocol_options_t options, bool renegotiation_enabled);

/*!
 * @function sec_protocol_options_set_peer_authentication_required
 *
 * @abstract
 *      Enable or disable peer authentication. Clients default to true, whereas servers default to false.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param peer_authentication_required
 *      Flag to enable or disable mandatory peer authentication.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_peer_authentication_required(sec_protocol_options_t options, bool peer_authentication_required);

#ifdef __BLOCKS__

/*!
 * @block sec_protocol_key_update_complete_t
 *
 * @abstract
 *      Block to be invoked when a key update event is handled.
 */
typedef void (^sec_protocol_key_update_complete_t)(void);

/*!
 * @block sec_protocol_key_update_t
 *
 * @abstract
 *      Block to be invoked when the protocol key MUST be updated.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param complete
 *      A `sec_protocol_key_update_complete_t` to be invoked when the key update is complete.
 */
typedef void (^sec_protocol_key_update_t)(sec_protocol_metadata_t metadata, sec_protocol_key_update_complete_t complete);

/*!
 * @block sec_protocol_challenge_complete_t
 *
 * @abstract
 *      Block to be invoked when an identity (authentication) challenge is complete.
 *
 *      Note: prior to macOS 10.15, iOS 13.0, watchOS 6.0, and tvOS 13.0, calling this
 *      block with a NULL `identity` argument was prohibited.
 *
 * @param identity
 *      A `sec_identity_t` containing the identity to use for this challenge.
 */
typedef void (^sec_protocol_challenge_complete_t)(sec_identity_t __nullable identity);

/*!
 * @block sec_protocol_challenge_t
 *
 * @abstract
 *      Block to be invoked when the protocol instance is issued a challenge (e.g., a TLS certificate request).
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param complete
 *      A `sec_protocol_challenge_complete_t` to be invoked when the challenge is complete.
 */
typedef void (^sec_protocol_challenge_t)(sec_protocol_metadata_t metadata, sec_protocol_challenge_complete_t complete);

/*!
 * @block sec_protocol_verify_complete_t
 *
 * @abstract
 *      Block to be invoked when verification is complete.
 *
 * @param result
 *      A `bool` indicating if verification succeeded or failed.
 */
typedef void (^sec_protocol_verify_complete_t)(bool result);

/*!
 * @block sec_protocol_verify_t
 *
 * @abstract
 *      Block to be invoked when the protocol instance must verify the peer.
 *
 *      NOTE: this may be called one or more times for a given connection.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param trust_ref
 *      A `sec_trust_t` instance.
 *
 * @param complete
 *      A `sec_protocol_verify_finish_t` to be invoked when verification is complete.
 */
typedef void (^sec_protocol_verify_t)(sec_protocol_metadata_t metadata, sec_trust_t trust_ref, sec_protocol_verify_complete_t complete);

/*!
 * @function sec_protocol_options_set_key_update_block
 *
 * @abstract
 *      Set the key update block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param key_update_block
 *      A `sec_protocol_key_update_t` block.
 *
 * @params key_update_queue
 *      A `dispatch_queue_t` on which the key update block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_key_update_block(sec_protocol_options_t options, sec_protocol_key_update_t key_update_block, dispatch_queue_t key_update_queue);

/*!
 * @function sec_protocol_options_set_challenge_block
 *
 * @abstract
 *      Set the challenge block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @params challenge_block
 *      A `sec_protocol_challenge_t` block.
 *
 * @params challenge_queue
 *      A `dispatch_queue_t` on which the challenge block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_challenge_block(sec_protocol_options_t options, sec_protocol_challenge_t challenge_block, dispatch_queue_t challenge_queue);

/*!
 * @function sec_protocol_options_set_verify_block
 *
 * @abstract
 *      Set the verify block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @params verify_block
 *      A `sec_protocol_verify_t` block.
 *
 * @params verify_block_queue
 *      A `dispatch_queue_t` on which the verify block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_verify_block(sec_protocol_options_t options, sec_protocol_verify_t verify_block, dispatch_queue_t verify_block_queue);

#endif // __BLOCKS__

SEC_ASSUME_NONNULL_END

__END_DECLS

#endif // SecProtocolOptions_h
// ==========  Security.framework/Headers/SecBase.h
/*
 * Copyright (c) 2000-2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SECURITY_SECBASE_H_
#define _SECURITY_SECBASE_H_

#include <TargetConditionals.h>
#include <CoreFoundation/CFBase.h>
#include <Availability.h>

// Truth table for following declarations:
//
//                          TARGET_OS_OSX   TARGET_OS_OSX   TARGET_OS_IPHONE    TARGET_OS_IPHONE    TARGET_OS_UIKITFORMAC
//                                          SEC_IOS_ON_OSX                      SEC_IOS_ON_OSX
// =================================================================================================================
// SEC_OS_IPHONE            0               1               1                   1                   1
// SEC_OS_OSX               1               0               0                   0                   0
// SEC_OS_OSX_INCLUDES      1               1               0                   0                   0

#if TARGET_OS_OSX
  #ifdef SEC_IOS_ON_OSX
    #define SEC_OS_IPHONE 1

    #define SEC_OS_OSX 0
    #define SEC_OS_OSX_INCLUDES 1
  #endif // SEC_IOS_ON_OSX
#endif // TARGET_OS_OSX

#if TARGET_OS_UIKITFORMAC
  #define SEC_OS_IPHONE 1

  #define SEC_OS_OSX 0
  #define SEC_OS_OSX_INCLUDES 0
#endif // TARGET_OS_UIKITFORMAC

#ifndef SEC_OS_IPHONE
    // block above did not fire; set flags to current platform
    #define SEC_OS_IPHONE TARGET_OS_IPHONE

    #define SEC_OS_OSX TARGET_OS_OSX
    #define SEC_OS_OSX_INCLUDES TARGET_OS_OSX
#endif

#if SEC_OS_IPHONE
#include <sys/cdefs.h>
#endif

#if defined(__clang__)
#define SEC_DEPRECATED_ATTRIBUTE DEPRECATED_ATTRIBUTE
#else
#define SEC_DEPRECATED_ATTRIBUTE
#endif

#define CSSM_DEPRECATED API_DEPRECATED("CSSM is not supported", macos(10.0, 10.7)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac)

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

#define SECURITY_TYPE_UNIFICATION 1

/*!
    @typedef SecCertificateRef
    @abstract CFType representing a X.509 certificate.
    See SecCertificate.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecCertificate *SecCertificateRef;

#if TARGET_OS_OSX
typedef struct __SecCertificate OpaqueSecCertificateRef;
#endif

/*!
    @typedef SecIdentityRef
    @abstract CFType representing an identity, which contains
    a SecKeyRef and an associated SecCertificateRef. See
    SecIdentity.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecIdentity *SecIdentityRef;

#if TARGET_OS_OSX
typedef struct __SecIdentity OpaqueSecIdentityRef;
#endif

/*!
    @typedef SecKeyRef
    @abstract CFType representing a cryptographic key. See
    SecKey.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKey *SecKeyRef;

#if TARGET_OS_OSX
typedef struct __SecKey OpaqueSecKeyRef;
#endif

/*!
    @typedef SecPolicyRef
    @abstract CFType representing a X.509 certificate trust policy.
    See SecPolicy.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecPolicy *SecPolicyRef;

/*!
    @typedef SecAccessControl
    @abstract CFType representing access control for an item.
    SecAccessControl.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecAccessControl *SecAccessControlRef;

/*!
    @typedef SecKeychainRef
    @abstract Contains information about a keychain.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKeychain *SecKeychainRef
    API_AVAILABLE(macos(10.0)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
    @typedef SecKeychainItemRef
    @abstract Contains information about a keychain item.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKeychainItem *SecKeychainItemRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainSearchRef
    @abstract Contains information about a keychain search.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKeychainSearch *SecKeychainSearchRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainAttrType
    @abstract Represents a keychain attribute type.
*/
typedef OSType SecKeychainAttrType API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @struct SecKeychainAttribute
    @abstract Contains keychain attributes.
    @field tag A 4-byte attribute tag.
    @field length The length of the buffer pointed to by data.
    @field data A pointer to the attribute data.
*/
struct API_UNAVAILABLE(ios, watchos, tvos, uikitformac) SecKeychainAttribute
{
    SecKeychainAttrType tag;
    UInt32 length;
    void * __nullable data;
};
typedef struct SecKeychainAttribute SecKeychainAttribute API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainAttributePtr
    @abstract Represents a pointer to a keychain attribute structure.
*/
typedef SecKeychainAttribute *SecKeychainAttributePtr API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainAttributeList
    @abstract Represents a list of keychain attributes.
    @field count An unsigned 32-bit integer that represents the number of keychain attributes in the array.
    @field attr A pointer to the first keychain attribute in the array.
*/
struct API_UNAVAILABLE(ios, watchos, tvos, uikitformac) SecKeychainAttributeList
{
    UInt32 count;
    SecKeychainAttribute * __nullable attr;
};
typedef struct SecKeychainAttributeList SecKeychainAttributeList API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainStatus
    @abstract Represents the status of a keychain.
*/
typedef UInt32 SecKeychainStatus API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecTrustedApplicationRef
    @abstract Contains information about a trusted application.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecTrustedApplication *SecTrustedApplicationRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecAccessRef
    @abstract Contains information about an access.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecAccess *SecAccessRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

#if TARGET_OS_OSX
typedef struct __SecAccess OpaqueSecAccessRef;
#endif

/*!
    @typedef SecACLRef
    @abstract Contains information about an access control list (ACL) entry.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecACL *SecACLRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecPasswordRef
    @abstract Contains information about a password.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecPassword *SecPasswordRef API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @typedef SecKeychainAttributeInfo
    @abstract Represents an attribute.
    @field count The number of tag-format pairs in the respective arrays.
    @field tag A pointer to the first attribute tag in the array.
    @field format A pointer to the first CSSM_DB_ATTRIBUTE_FORMAT in the array.
    @discussion Each tag and format item form a pair.
*/
struct API_UNAVAILABLE(ios, watchos, tvos, uikitformac) SecKeychainAttributeInfo
{
    UInt32 count;
    UInt32 *tag;
    UInt32 * __nullable format;
};
typedef struct SecKeychainAttributeInfo SecKeychainAttributeInfo API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*!
    @function SecCopyErrorMessageString
    @abstract Returns a string describing the specified error result code.
    @param status An error result code of type OSStatus or CSSM_RETURN, as returned by a Security or CSSM function.
    @reserved Reserved for future use. Your code should pass NULL in this parameter.
    @result A reference to an error string, or NULL if no error string is available for the specified result code. Your code must release this reference by calling the CFRelease function.
*/
__nullable
CFStringRef SecCopyErrorMessageString(OSStatus status, void * __nullable reserved)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_11_3);


/*!
@enum Security Error Codes
@abstract Result codes returned from Security framework functions.
@constant errSecSuccess No error.
@constant errSecUnimplemented Function or operation not implemented.
@constant errSecDiskFull Disk Full error.
@constant errSecIO I/O error.
@constant errSecParam One or more parameters passed to a function were not valid.
@constant errSecWrPerm    Write permissions error.
@constant errSecAllocate Failed to allocate memory.
@constant errSecUserCanceled User canceled the operation.
@constant errSecBadReq Bad parameter or invalid state for operation.
@constant errSecInternalComponent
@constant errSecCoreFoundationUnknown
@constant errSecNotAvailable No keychain is available.
@constant errSecReadOnly Read only error.
@constant errSecAuthFailed Authorization/Authentication failed.
@constant errSecNoSuchKeychain The keychain does not exist.
@constant errSecInvalidKeychain The keychain is not valid.
@constant errSecDuplicateKeychain A keychain with the same name already exists.
@constant errSecDuplicateCallback The specified callback is already installed.
@constant errSecInvalidCallback The specified callback is not valid.
@constant errSecDuplicateItem The item already exists.
@constant errSecItemNotFound The item cannot be found.
@constant errSecBufferTooSmall The buffer is too small.
@constant errSecDataTooLarge The data is too large.
@constant errSecNoSuchAttr The attribute does not exist.
@constant errSecInvalidItemRef The item reference is invalid.
@constant errSecInvalidSearchRef The search reference is invalid.
@constant errSecNoSuchClass The keychain item class does not exist.
@constant errSecNoDefaultKeychain A default keychain does not exist.
@constant errSecInteractionNotAllowed User interaction is not allowed.
@constant errSecReadOnlyAttr The attribute is read only.
@constant errSecWrongSecVersion The version is incorrect.
@constant errSecKeySizeNotAllowed The key size is not allowed.
@constant errSecNoStorageModule There is no storage module available.
@constant errSecNoCertificateModule There is no certificate module available.
@constant errSecNoPolicyModule There is no policy module available.
@constant errSecInteractionRequired User interaction is required.
@constant errSecDataNotAvailable The data is not available.
@constant errSecDataNotModifiable The data is not modifiable.
@constant errSecCreateChainFailed The attempt to create a certificate chain failed.
@constant errSecACLNotSimple The access control list is not in standard simple form.
@constant errSecPolicyNotFound The policy specified cannot be found.
@constant errSecInvalidTrustSetting The specified trust setting is invalid.
@constant errSecNoAccessForItem The specified item has no access control.
@constant errSecInvalidOwnerEdit Invalid attempt to change the owner of this item.
@constant errSecTrustNotAvailable No trust results are available.
@constant errSecUnsupportedFormat Import/Export format unsupported.
@constant errSecUnknownFormat Unknown format in import.
@constant errSecKeyIsSensitive Key material must be wrapped for export.
@constant errSecMultiplePrivKeys An attempt was made to import multiple private keys.
@constant errSecPassphraseRequired Passphrase is required for import/export.
@constant errSecInvalidPasswordRef The password reference was invalid.
@constant errSecInvalidTrustSettings The Trust Settings Record was corrupted.
@constant errSecNoTrustSettings No Trust Settings were found.
@constant errSecPkcs12VerifyFailure MAC verification failed during PKCS12 Import.
@constant errSecDecode Unable to decode the provided data.

@discussion The assigned error space is discontinuous: e.g. -25240..-25279, -25290..-25329, -68608..-67585, and so on.
*/

/*
    Note: the comments that appear after these errors are used to create SecErrorMessages.strings.
    The comments must not be multi-line, and should be in a form meaningful to an end user. If
    a different or additional comment is needed, it can be put in the header doc format, or on a
    line that does not start with errZZZ.
*/

CF_ENUM(OSStatus)
{
    errSecSuccess                            = 0,       /* No error. */
    errSecUnimplemented                      = -4,      /* Function or operation not implemented. */
    errSecDiskFull                           = -34,     /* The disk is full. */
    errSecDskFull __attribute__((deprecated("use errSecDiskFull"))) = errSecDiskFull,
    errSecIO                                 = -36,     /* I/O error. */
    errSecOpWr                               = -49,     /* File already open with write permission. */
    errSecParam                              = -50,     /* One or more parameters passed to a function were not valid. */
    errSecWrPerm                             = -61,     /* Write permissions error. */
    errSecAllocate                           = -108,    /* Failed to allocate memory. */
    errSecUserCanceled                       = -128,    /* User canceled the operation. */
    errSecBadReq                             = -909,    /* Bad parameter or invalid state for operation. */

    errSecInternalComponent                  = -2070,
    errSecCoreFoundationUnknown              = -4960,

    errSecMissingEntitlement                 = -34018,    /* A required entitlement isn't present. */

    errSecNotAvailable                       = -25291,    /* No keychain is available. You may need to restart your computer. */
    errSecReadOnly                           = -25292,    /* This keychain cannot be modified. */
    errSecAuthFailed                         = -25293,    /* The user name or passphrase you entered is not correct. */
    errSecNoSuchKeychain                     = -25294,    /* The specified keychain could not be found. */
    errSecInvalidKeychain                    = -25295,    /* The specified keychain is not a valid keychain file. */
    errSecDuplicateKeychain                  = -25296,    /* A keychain with the same name already exists. */
    errSecDuplicateCallback                  = -25297,    /* The specified callback function is already installed. */
    errSecInvalidCallback                    = -25298,    /* The specified callback function is not valid. */
    errSecDuplicateItem                      = -25299,    /* The specified item already exists in the keychain. */
    errSecItemNotFound                       = -25300,    /* The specified item could not be found in the keychain. */
    errSecBufferTooSmall                     = -25301,    /* There is not enough memory available to use the specified item. */
    errSecDataTooLarge                       = -25302,    /* This item contains information which is too large or in a format that cannot be displayed. */
    errSecNoSuchAttr                         = -25303,    /* The specified attribute does not exist. */
    errSecInvalidItemRef                     = -25304,    /* The specified item is no longer valid. It may have been deleted from the keychain. */
    errSecInvalidSearchRef                   = -25305,    /* Unable to search the current keychain. */
    errSecNoSuchClass                        = -25306,    /* The specified item does not appear to be a valid keychain item. */
    errSecNoDefaultKeychain                  = -25307,    /* A default keychain could not be found. */
    errSecInteractionNotAllowed              = -25308,    /* User interaction is not allowed. */
    errSecReadOnlyAttr                       = -25309,    /* The specified attribute could not be modified. */
    errSecWrongSecVersion                    = -25310,    /* This keychain was created by a different version of the system software and cannot be opened. */
    errSecKeySizeNotAllowed                  = -25311,    /* This item specifies a key size which is too large or too small. */
    errSecNoStorageModule                    = -25312,    /* A required component (data storage module) could not be loaded. You may need to restart your computer. */
    errSecNoCertificateModule                = -25313,    /* A required component (certificate module) could not be loaded. You may need to restart your computer. */
    errSecNoPolicyModule                     = -25314,    /* A required component (policy module) could not be loaded. You may need to restart your computer. */
    errSecInteractionRequired                = -25315,    /* User interaction is required, but is currently not allowed. */
    errSecDataNotAvailable                   = -25316,    /* The contents of this item cannot be retrieved. */
    errSecDataNotModifiable                  = -25317,    /* The contents of this item cannot be modified. */
    errSecCreateChainFailed                  = -25318,    /* One or more certificates required to validate this certificate cannot be found. */
    errSecInvalidPrefsDomain                 = -25319,    /* The specified preferences domain is not valid. */
    errSecInDarkWake                         = -25320,    /* In dark wake, no UI possible */

    errSecACLNotSimple                       = -25240,    /* The specified access control list is not in standard (simple) form. */
    errSecPolicyNotFound                     = -25241,    /* The specified policy cannot be found. */
    errSecInvalidTrustSetting                = -25242,    /* The specified trust setting is invalid. */
    errSecNoAccessForItem                    = -25243,    /* The specified item has no access control. */
    errSecInvalidOwnerEdit                   = -25244,    /* Invalid attempt to change the owner of this item. */
    errSecTrustNotAvailable                  = -25245,    /* No trust results are available. */
    errSecUnsupportedFormat                  = -25256,    /* Import/Export format unsupported. */
    errSecUnknownFormat                      = -25257,    /* Unknown format in import. */
    errSecKeyIsSensitive                     = -25258,    /* Key material must be wrapped for export. */
    errSecMultiplePrivKeys                   = -25259,    /* An attempt was made to import multiple private keys. */
    errSecPassphraseRequired                 = -25260,    /* Passphrase is required for import/export. */
    errSecInvalidPasswordRef                 = -25261,    /* The password reference was invalid. */
    errSecInvalidTrustSettings               = -25262,    /* The Trust Settings Record was corrupted. */
    errSecNoTrustSettings                    = -25263,    /* No Trust Settings were found. */
    errSecPkcs12VerifyFailure                = -25264,    /* MAC verification failed during PKCS12 import (wrong password?) */
    errSecNotSigner                          = -26267,    /* A certificate was not signed by its proposed parent. */

    errSecDecode                             = -26275,    /* Unable to decode the provided data. */

    errSecServiceNotAvailable                = -67585,    /* The required service is not available. */
    errSecInsufficientClientID               = -67586,    /* The client ID is not correct. */
    errSecDeviceReset                        = -67587,    /* A device reset has occurred. */
    errSecDeviceFailed                       = -67588,    /* A device failure has occurred. */
    errSecAppleAddAppACLSubject              = -67589,    /* Adding an application ACL subject failed. */
    errSecApplePublicKeyIncomplete           = -67590,    /* The public key is incomplete. */
    errSecAppleSignatureMismatch             = -67591,    /* A signature mismatch has occurred. */
    errSecAppleInvalidKeyStartDate           = -67592,    /* The specified key has an invalid start date. */
    errSecAppleInvalidKeyEndDate             = -67593,    /* The specified key has an invalid end date. */
    errSecConversionError                    = -67594,    /* A conversion error has occurred. */
    errSecAppleSSLv2Rollback                 = -67595,    /* A SSLv2 rollback error has occurred. */
    errSecQuotaExceeded                      = -67596,    /* The quota was exceeded. */
    errSecFileTooBig                         = -67597,    /* The file is too big. */
    errSecInvalidDatabaseBlob                = -67598,    /* The specified database has an invalid blob. */
    errSecInvalidKeyBlob                     = -67599,    /* The specified database has an invalid key blob. */
    errSecIncompatibleDatabaseBlob           = -67600,    /* The specified database has an incompatible blob. */
    errSecIncompatibleKeyBlob                = -67601,    /* The specified database has an incompatible key blob. */
    errSecHostNameMismatch                   = -67602,    /* A host name mismatch has occurred. */
    errSecUnknownCriticalExtensionFlag       = -67603,    /* There is an unknown critical extension flag. */
    errSecNoBasicConstraints                 = -67604,    /* No basic constraints were found. */
    errSecNoBasicConstraintsCA               = -67605,    /* No basic CA constraints were found. */
    errSecInvalidAuthorityKeyID              = -67606,    /* The authority key ID is not valid. */
    errSecInvalidSubjectKeyID                = -67607,    /* The subject key ID is not valid. */
    errSecInvalidKeyUsageForPolicy           = -67608,    /* The key usage is not valid for the specified policy. */
    errSecInvalidExtendedKeyUsage            = -67609,    /* The extended key usage is not valid. */
    errSecInvalidIDLinkage                   = -67610,    /* The ID linkage is not valid. */
    errSecPathLengthConstraintExceeded       = -67611,    /* The path length constraint was exceeded. */
    errSecInvalidRoot                        = -67612,    /* The root or anchor certificate is not valid. */
    errSecCRLExpired                         = -67613,    /* The CRL has expired. */
    errSecCRLNotValidYet                     = -67614,    /* The CRL is not yet valid. */
    errSecCRLNotFound                        = -67615,    /* The CRL was not found. */
    errSecCRLServerDown                      = -67616,    /* The CRL server is down. */
    errSecCRLBadURI                          = -67617,    /* The CRL has a bad Uniform Resource Identifier. */
    errSecUnknownCertExtension               = -67618,    /* An unknown certificate extension was encountered. */
    errSecUnknownCRLExtension                = -67619,    /* An unknown CRL extension was encountered. */
    errSecCRLNotTrusted                      = -67620,    /* The CRL is not trusted. */
    errSecCRLPolicyFailed                    = -67621,    /* The CRL policy failed. */
    errSecIDPFailure                         = -67622,    /* The issuing distribution point was not valid. */
    errSecSMIMEEmailAddressesNotFound        = -67623,    /* An email address mismatch was encountered. */
    errSecSMIMEBadExtendedKeyUsage           = -67624,    /* The appropriate extended key usage for SMIME was not found. */
    errSecSMIMEBadKeyUsage                   = -67625,    /* The key usage is not compatible with SMIME. */
    errSecSMIMEKeyUsageNotCritical           = -67626,    /* The key usage extension is not marked as critical. */
    errSecSMIMENoEmailAddress                = -67627,    /* No email address was found in the certificate. */
    errSecSMIMESubjAltNameNotCritical        = -67628,    /* The subject alternative name extension is not marked as critical. */
    errSecSSLBadExtendedKeyUsage             = -67629,    /* The appropriate extended key usage for SSL was not found. */
    errSecOCSPBadResponse                    = -67630,    /* The OCSP response was incorrect or could not be parsed. */
    errSecOCSPBadRequest                     = -67631,    /* The OCSP request was incorrect or could not be parsed. */
    errSecOCSPUnavailable                    = -67632,    /* OCSP service is unavailable. */
    errSecOCSPStatusUnrecognized             = -67633,    /* The OCSP server did not recognize this certificate. */
    errSecEndOfData                          = -67634,    /* An end-of-data was detected. */
    errSecIncompleteCertRevocationCheck      = -67635,    /* An incomplete certificate revocation check occurred. */
    errSecNetworkFailure                     = -67636,    /* A network failure occurred. */
    errSecOCSPNotTrustedToAnchor             = -67637,    /* The OCSP response was not trusted to a root or anchor certificate. */
    errSecRecordModified                     = -67638,    /* The record was modified. */
    errSecOCSPSignatureError                 = -67639,    /* The OCSP response had an invalid signature. */
    errSecOCSPNoSigner                       = -67640,    /* The OCSP response had no signer. */
    errSecOCSPResponderMalformedReq          = -67641,    /* The OCSP responder was given a malformed request. */
    errSecOCSPResponderInternalError         = -67642,    /* The OCSP responder encountered an internal error. */
    errSecOCSPResponderTryLater              = -67643,    /* The OCSP responder is busy, try again later. */
    errSecOCSPResponderSignatureRequired     = -67644,    /* The OCSP responder requires a signature. */
    errSecOCSPResponderUnauthorized          = -67645,    /* The OCSP responder rejected this request as unauthorized. */
    errSecOCSPResponseNonceMismatch          = -67646,    /* The OCSP response nonce did not match the request. */
    errSecCodeSigningBadCertChainLength      = -67647,    /* Code signing encountered an incorrect certificate chain length. */
    errSecCodeSigningNoBasicConstraints      = -67648,    /* Code signing found no basic constraints. */
    errSecCodeSigningBadPathLengthConstraint = -67649,    /* Code signing encountered an incorrect path length constraint. */
    errSecCodeSigningNoExtendedKeyUsage      = -67650,    /* Code signing found no extended key usage. */
    errSecCodeSigningDevelopment             = -67651,    /* Code signing indicated use of a development-only certificate. */
    errSecResourceSignBadCertChainLength     = -67652,    /* Resource signing has encountered an incorrect certificate chain length. */
    errSecResourceSignBadExtKeyUsage         = -67653,    /* Resource signing has encountered an error in the extended key usage. */
    errSecTrustSettingDeny                   = -67654,    /* The trust setting for this policy was set to Deny. */
    errSecInvalidSubjectName                 = -67655,    /* An invalid certificate subject name was encountered. */
    errSecUnknownQualifiedCertStatement      = -67656,    /* An unknown qualified certificate statement was encountered. */
    errSecMobileMeRequestQueued              = -67657,
    errSecMobileMeRequestRedirected          = -67658,
    errSecMobileMeServerError                = -67659,
    errSecMobileMeServerNotAvailable         = -67660,
    errSecMobileMeServerAlreadyExists        = -67661,
    errSecMobileMeServerServiceErr           = -67662,
    errSecMobileMeRequestAlreadyPending      = -67663,
    errSecMobileMeNoRequestPending           = -67664,
    errSecMobileMeCSRVerifyFailure           = -67665,
    errSecMobileMeFailedConsistencyCheck     = -67666,
    errSecNotInitialized                     = -67667,    /* A function was called without initializing CSSM. */
    errSecInvalidHandleUsage                 = -67668,    /* The CSSM handle does not match with the service type. */
    errSecPVCReferentNotFound                = -67669,    /* A reference to the calling module was not found in the list of authorized callers. */
    errSecFunctionIntegrityFail              = -67670,    /* A function address was not within the verified module. */
    errSecInternalError                      = -67671,    /* An internal error has occurred. */
    errSecMemoryError                        = -67672,    /* A memory error has occurred. */
    errSecInvalidData                        = -67673,    /* Invalid data was encountered. */
    errSecMDSError                           = -67674,    /* A Module Directory Service error has occurred. */
    errSecInvalidPointer                     = -67675,    /* An invalid pointer was encountered. */
    errSecSelfCheckFailed                    = -67676,    /* Self-check has failed. */
    errSecFunctionFailed                     = -67677,    /* A function has failed. */
    errSecModuleManifestVerifyFailed         = -67678,    /* A module manifest verification failure has occurred. */
    errSecInvalidGUID                        = -67679,    /* An invalid GUID was encountered. */
    errSecInvalidHandle                      = -67680,    /* An invalid handle was encountered. */
    errSecInvalidDBList                      = -67681,    /* An invalid DB list was encountered. */
    errSecInvalidPassthroughID               = -67682,    /* An invalid passthrough ID was encountered. */
    errSecInvalidNetworkAddress              = -67683,    /* An invalid network address was encountered. */
    errSecCRLAlreadySigned                   = -67684,    /* The certificate revocation list is already signed. */
    errSecInvalidNumberOfFields              = -67685,    /* An invalid number of fields were encountered. */
    errSecVerificationFailure                = -67686,    /* A verification failure occurred. */
    errSecUnknownTag                         = -67687,    /* An unknown tag was encountered. */
    errSecInvalidSignature                   = -67688,    /* An invalid signature was encountered. */
    errSecInvalidName                        = -67689,    /* An invalid name was encountered. */
    errSecInvalidCertificateRef              = -67690,    /* An invalid certificate reference was encountered. */
    errSecInvalidCertificateGroup            = -67691,    /* An invalid certificate group was encountered. */
    errSecTagNotFound                        = -67692,    /* The specified tag was not found. */
    errSecInvalidQuery                       = -67693,    /* The specified query was not valid. */
    errSecInvalidValue                       = -67694,    /* An invalid value was detected. */
    errSecCallbackFailed                     = -67695,    /* A callback has failed. */
    errSecACLDeleteFailed                    = -67696,    /* An ACL delete operation has failed. */
    errSecACLReplaceFailed                   = -67697,    /* An ACL replace operation has failed. */
    errSecACLAddFailed                       = -67698,    /* An ACL add operation has failed. */
    errSecACLChangeFailed                    = -67699,    /* An ACL change operation has failed. */
    errSecInvalidAccessCredentials           = -67700,    /* Invalid access credentials were encountered. */
    errSecInvalidRecord                      = -67701,    /* An invalid record was encountered. */
    errSecInvalidACL                         = -67702,    /* An invalid ACL was encountered. */
    errSecInvalidSampleValue                 = -67703,    /* An invalid sample value was encountered. */
    errSecIncompatibleVersion                = -67704,    /* An incompatible version was encountered. */
    errSecPrivilegeNotGranted                = -67705,    /* The privilege was not granted. */
    errSecInvalidScope                       = -67706,    /* An invalid scope was encountered. */
    errSecPVCAlreadyConfigured               = -67707,    /* The PVC is already configured. */
    errSecInvalidPVC                         = -67708,    /* An invalid PVC was encountered. */
    errSecEMMLoadFailed                      = -67709,    /* The EMM load has failed. */
    errSecEMMUnloadFailed                    = -67710,    /* The EMM unload has failed. */
    errSecAddinLoadFailed                    = -67711,    /* The add-in load operation has failed. */
    errSecInvalidKeyRef                      = -67712,    /* An invalid key was encountered. */
    errSecInvalidKeyHierarchy                = -67713,    /* An invalid key hierarchy was encountered. */
    errSecAddinUnloadFailed                  = -67714,    /* The add-in unload operation has failed. */
    errSecLibraryReferenceNotFound           = -67715,    /* A library reference was not found. */
    errSecInvalidAddinFunctionTable          = -67716,    /* An invalid add-in function table was encountered. */
    errSecInvalidServiceMask                 = -67717,    /* An invalid service mask was encountered. */
    errSecModuleNotLoaded                    = -67718,    /* A module was not loaded. */
    errSecInvalidSubServiceID                = -67719,    /* An invalid subservice ID was encountered. */
    errSecAttributeNotInContext              = -67720,    /* An attribute was not in the context. */
    errSecModuleManagerInitializeFailed      = -67721,    /* A module failed to initialize. */
    errSecModuleManagerNotFound              = -67722,    /* A module was not found. */
    errSecEventNotificationCallbackNotFound  = -67723,    /* An event notification callback was not found. */
    errSecInputLengthError                   = -67724,    /* An input length error was encountered. */
    errSecOutputLengthError                  = -67725,    /* An output length error was encountered. */
    errSecPrivilegeNotSupported              = -67726,    /* The privilege is not supported. */
    errSecDeviceError                        = -67727,    /* A device error was encountered. */
    errSecAttachHandleBusy                   = -67728,    /* The CSP handle was busy. */
    errSecNotLoggedIn                        = -67729,    /* You are not logged in. */
    errSecAlgorithmMismatch                  = -67730,    /* An algorithm mismatch was encountered. */
    errSecKeyUsageIncorrect                  = -67731,    /* The key usage is incorrect. */
    errSecKeyBlobTypeIncorrect               = -67732,    /* The key blob type is incorrect. */
    errSecKeyHeaderInconsistent              = -67733,    /* The key header is inconsistent. */
    errSecUnsupportedKeyFormat               = -67734,    /* The key header format is not supported. */
    errSecUnsupportedKeySize                 = -67735,    /* The key size is not supported. */
    errSecInvalidKeyUsageMask                = -67736,    /* The key usage mask is not valid. */
    errSecUnsupportedKeyUsageMask            = -67737,    /* The key usage mask is not supported. */
    errSecInvalidKeyAttributeMask            = -67738,    /* The key attribute mask is not valid. */
    errSecUnsupportedKeyAttributeMask        = -67739,    /* The key attribute mask is not supported. */
    errSecInvalidKeyLabel                    = -67740,    /* The key label is not valid. */
    errSecUnsupportedKeyLabel                = -67741,    /* The key label is not supported. */
    errSecInvalidKeyFormat                   = -67742,    /* The key format is not valid. */
    errSecUnsupportedVectorOfBuffers         = -67743,    /* The vector of buffers is not supported. */
    errSecInvalidInputVector                 = -67744,    /* The input vector is not valid. */
    errSecInvalidOutputVector                = -67745,    /* The output vector is not valid. */
    errSecInvalidContext                     = -67746,    /* An invalid context was encountered. */
    errSecInvalidAlgorithm                   = -67747,    /* An invalid algorithm was encountered. */
    errSecInvalidAttributeKey                = -67748,    /* A key attribute was not valid. */
    errSecMissingAttributeKey                = -67749,    /* A key attribute was missing. */
    errSecInvalidAttributeInitVector         = -67750,    /* An init vector attribute was not valid. */
    errSecMissingAttributeInitVector         = -67751,    /* An init vector attribute was missing. */
    errSecInvalidAttributeSalt               = -67752,    /* A salt attribute was not valid. */
    errSecMissingAttributeSalt               = -67753,    /* A salt attribute was missing. */
    errSecInvalidAttributePadding            = -67754,    /* A padding attribute was not valid. */
    errSecMissingAttributePadding            = -67755,    /* A padding attribute was missing. */
    errSecInvalidAttributeRandom             = -67756,    /* A random number attribute was not valid. */
    errSecMissingAttributeRandom             = -67757,    /* A random number attribute was missing. */
    errSecInvalidAttributeSeed               = -67758,    /* A seed attribute was not valid. */
    errSecMissingAttributeSeed               = -67759,    /* A seed attribute was missing. */
    errSecInvalidAttributePassphrase         = -67760,    /* A passphrase attribute was not valid. */
    errSecMissingAttributePassphrase         = -67761,    /* A passphrase attribute was missing. */
    errSecInvalidAttributeKeyLength          = -67762,    /* A key length attribute was not valid. */
    errSecMissingAttributeKeyLength          = -67763,    /* A key length attribute was missing. */
    errSecInvalidAttributeBlockSize          = -67764,    /* A block size attribute was not valid. */
    errSecMissingAttributeBlockSize          = -67765,    /* A block size attribute was missing. */
    errSecInvalidAttributeOutputSize         = -67766,    /* An output size attribute was not valid. */
    errSecMissingAttributeOutputSize         = -67767,    /* An output size attribute was missing. */
    errSecInvalidAttributeRounds             = -67768,    /* The number of rounds attribute was not valid. */
    errSecMissingAttributeRounds             = -67769,    /* The number of rounds attribute was missing. */
    errSecInvalidAlgorithmParms              = -67770,    /* An algorithm parameters attribute was not valid. */
    errSecMissingAlgorithmParms              = -67771,    /* An algorithm parameters attribute was missing. */
    errSecInvalidAttributeLabel              = -67772,    /* A label attribute was not valid. */
    errSecMissingAttributeLabel              = -67773,    /* A label attribute was missing. */
    errSecInvalidAttributeKeyType            = -67774,    /* A key type attribute was not valid. */
    errSecMissingAttributeKeyType            = -67775,    /* A key type attribute was missing. */
    errSecInvalidAttributeMode               = -67776,    /* A mode attribute was not valid. */
    errSecMissingAttributeMode               = -67777,    /* A mode attribute was missing. */
    errSecInvalidAttributeEffectiveBits      = -67778,    /* An effective bits attribute was not valid. */
    errSecMissingAttributeEffectiveBits      = -67779,    /* An effective bits attribute was missing. */
    errSecInvalidAttributeStartDate          = -67780,    /* A start date attribute was not valid. */
    errSecMissingAttributeStartDate          = -67781,    /* A start date attribute was missing. */
    errSecInvalidAttributeEndDate            = -67782,    /* An end date attribute was not valid. */
    errSecMissingAttributeEndDate            = -67783,    /* An end date attribute was missing. */
    errSecInvalidAttributeVersion            = -67784,    /* A version attribute was not valid. */
    errSecMissingAttributeVersion            = -67785,    /* A version attribute was missing. */
    errSecInvalidAttributePrime              = -67786,    /* A prime attribute was not valid. */
    errSecMissingAttributePrime              = -67787,    /* A prime attribute was missing. */
    errSecInvalidAttributeBase               = -67788,    /* A base attribute was not valid. */
    errSecMissingAttributeBase               = -67789,    /* A base attribute was missing. */
    errSecInvalidAttributeSubprime           = -67790,    /* A subprime attribute was not valid. */
    errSecMissingAttributeSubprime           = -67791,    /* A subprime attribute was missing. */
    errSecInvalidAttributeIterationCount     = -67792,    /* An iteration count attribute was not valid. */
    errSecMissingAttributeIterationCount     = -67793,    /* An iteration count attribute was missing. */
    errSecInvalidAttributeDLDBHandle         = -67794,    /* A database handle attribute was not valid. */
    errSecMissingAttributeDLDBHandle         = -67795,    /* A database handle attribute was missing. */
    errSecInvalidAttributeAccessCredentials  = -67796,    /* An access credentials attribute was not valid. */
    errSecMissingAttributeAccessCredentials  = -67797,    /* An access credentials attribute was missing. */
    errSecInvalidAttributePublicKeyFormat    = -67798,    /* A public key format attribute was not valid. */
    errSecMissingAttributePublicKeyFormat    = -67799,    /* A public key format attribute was missing. */
    errSecInvalidAttributePrivateKeyFormat   = -67800,    /* A private key format attribute was not valid. */
    errSecMissingAttributePrivateKeyFormat   = -67801,    /* A private key format attribute was missing. */
    errSecInvalidAttributeSymmetricKeyFormat = -67802,    /* A symmetric key format attribute was not valid. */
    errSecMissingAttributeSymmetricKeyFormat = -67803,    /* A symmetric key format attribute was missing. */
    errSecInvalidAttributeWrappedKeyFormat   = -67804,    /* A wrapped key format attribute was not valid. */
    errSecMissingAttributeWrappedKeyFormat   = -67805,    /* A wrapped key format attribute was missing. */
    errSecStagedOperationInProgress          = -67806,    /* A staged operation is in progress. */
    errSecStagedOperationNotStarted          = -67807,    /* A staged operation was not started. */
    errSecVerifyFailed                       = -67808,    /* A cryptographic verification failure has occurred. */
    errSecQuerySizeUnknown                   = -67809,    /* The query size is unknown. */
    errSecBlockSizeMismatch                  = -67810,    /* A block size mismatch occurred. */
    errSecPublicKeyInconsistent              = -67811,    /* The public key was inconsistent. */
    errSecDeviceVerifyFailed                 = -67812,    /* A device verification failure has occurred. */
    errSecInvalidLoginName                   = -67813,    /* An invalid login name was detected. */
    errSecAlreadyLoggedIn                    = -67814,    /* The user is already logged in. */
    errSecInvalidDigestAlgorithm             = -67815,    /* An invalid digest algorithm was detected. */
    errSecInvalidCRLGroup                    = -67816,    /* An invalid CRL group was detected. */
    errSecCertificateCannotOperate           = -67817,    /* The certificate cannot operate. */
    errSecCertificateExpired                 = -67818,    /* An expired certificate was detected. */
    errSecCertificateNotValidYet             = -67819,    /* The certificate is not yet valid. */
    errSecCertificateRevoked                 = -67820,    /* The certificate was revoked. */
    errSecCertificateSuspended               = -67821,    /* The certificate was suspended. */
    errSecInsufficientCredentials            = -67822,    /* Insufficient credentials were detected. */
    errSecInvalidAction                      = -67823,    /* The action was not valid. */
    errSecInvalidAuthority                   = -67824,    /* The authority was not valid. */
    errSecVerifyActionFailed                 = -67825,    /* A verify action has failed. */
    errSecInvalidCertAuthority               = -67826,    /* The certificate authority was not valid. */
    errSecInvaldCRLAuthority                 = -67827,    /* The CRL authority was not valid. */
    errSecInvalidCRLEncoding                 = -67828,    /* The CRL encoding was not valid. */
    errSecInvalidCRLType                     = -67829,    /* The CRL type was not valid. */
    errSecInvalidCRL                         = -67830,    /* The CRL was not valid. */
    errSecInvalidFormType                    = -67831,    /* The form type was not valid. */
    errSecInvalidID                          = -67832,    /* The ID was not valid. */
    errSecInvalidIdentifier                  = -67833,    /* The identifier was not valid. */
    errSecInvalidIndex                       = -67834,    /* The index was not valid. */
    errSecInvalidPolicyIdentifiers           = -67835,    /* The policy identifiers are not valid. */
    errSecInvalidTimeString                  = -67836,    /* The time specified was not valid. */
    errSecInvalidReason                      = -67837,    /* The trust policy reason was not valid. */
    errSecInvalidRequestInputs               = -67838,    /* The request inputs are not valid. */
    errSecInvalidResponseVector              = -67839,    /* The response vector was not valid. */
    errSecInvalidStopOnPolicy                = -67840,    /* The stop-on policy was not valid. */
    errSecInvalidTuple                       = -67841,    /* The tuple was not valid. */
    errSecMultipleValuesUnsupported          = -67842,    /* Multiple values are not supported. */
    errSecNotTrusted                         = -67843,    /* The certificate was not trusted. */
    errSecNoDefaultAuthority                 = -67844,    /* No default authority was detected. */
    errSecRejectedForm                       = -67845,    /* The trust policy had a rejected form. */
    errSecRequestLost                        = -67846,    /* The request was lost. */
    errSecRequestRejected                    = -67847,    /* The request was rejected. */
    errSecUnsupportedAddressType             = -67848,    /* The address type is not supported. */
    errSecUnsupportedService                 = -67849,    /* The service is not supported. */
    errSecInvalidTupleGroup                  = -67850,    /* The tuple group was not valid. */
    errSecInvalidBaseACLs                    = -67851,    /* The base ACLs are not valid. */
    errSecInvalidTupleCredendtials           = -67852,    /* The tuple credentials are not valid. */
    errSecInvalidEncoding                    = -67853,    /* The encoding was not valid. */
    errSecInvalidValidityPeriod              = -67854,    /* The validity period was not valid. */
    errSecInvalidRequestor                   = -67855,    /* The requestor was not valid. */
    errSecRequestDescriptor                  = -67856,    /* The request descriptor was not valid. */
    errSecInvalidBundleInfo                  = -67857,    /* The bundle information was not valid. */
    errSecInvalidCRLIndex                    = -67858,    /* The CRL index was not valid. */
    errSecNoFieldValues                      = -67859,    /* No field values were detected. */
    errSecUnsupportedFieldFormat             = -67860,    /* The field format is not supported. */
    errSecUnsupportedIndexInfo               = -67861,    /* The index information is not supported. */
    errSecUnsupportedLocality                = -67862,    /* The locality is not supported. */
    errSecUnsupportedNumAttributes           = -67863,    /* The number of attributes is not supported. */
    errSecUnsupportedNumIndexes              = -67864,    /* The number of indexes is not supported. */
    errSecUnsupportedNumRecordTypes          = -67865,    /* The number of record types is not supported. */
    errSecFieldSpecifiedMultiple             = -67866,    /* Too many fields were specified. */
    errSecIncompatibleFieldFormat            = -67867,    /* The field format was incompatible. */
    errSecInvalidParsingModule               = -67868,    /* The parsing module was not valid. */
    errSecDatabaseLocked                     = -67869,    /* The database is locked. */
    errSecDatastoreIsOpen                    = -67870,    /* The data store is open. */
    errSecMissingValue                       = -67871,    /* A missing value was detected. */
    errSecUnsupportedQueryLimits             = -67872,    /* The query limits are not supported. */
    errSecUnsupportedNumSelectionPreds       = -67873,    /* The number of selection predicates is not supported. */
    errSecUnsupportedOperator                = -67874,    /* The operator is not supported. */
    errSecInvalidDBLocation                  = -67875,    /* The database location is not valid. */
    errSecInvalidAccessRequest               = -67876,    /* The access request is not valid. */
    errSecInvalidIndexInfo                   = -67877,    /* The index information is not valid. */
    errSecInvalidNewOwner                    = -67878,    /* The new owner is not valid. */
    errSecInvalidModifyMode                  = -67879,    /* The modify mode is not valid. */
    errSecMissingRequiredExtension           = -67880,    /* A required certificate extension is missing. */
    errSecExtendedKeyUsageNotCritical        = -67881,    /* The extended key usage extension was not marked critical. */
    errSecTimestampMissing                   = -67882,    /* A timestamp was expected but was not found. */
    errSecTimestampInvalid                   = -67883,    /* The timestamp was not valid. */
    errSecTimestampNotTrusted                = -67884,    /* The timestamp was not trusted. */
    errSecTimestampServiceNotAvailable       = -67885,    /* The timestamp service is not available. */
    errSecTimestampBadAlg                    = -67886,    /* An unrecognized or unsupported Algorithm Identifier in timestamp. */
    errSecTimestampBadRequest                = -67887,    /* The timestamp transaction is not permitted or supported. */
    errSecTimestampBadDataFormat             = -67888,    /* The timestamp data submitted has the wrong format. */
    errSecTimestampTimeNotAvailable          = -67889,    /* The time source for the Timestamp Authority is not available. */
    errSecTimestampUnacceptedPolicy          = -67890,    /* The requested policy is not supported by the Timestamp Authority. */
    errSecTimestampUnacceptedExtension       = -67891,    /* The requested extension is not supported by the Timestamp Authority. */
    errSecTimestampAddInfoNotAvailable       = -67892,    /* The additional information requested is not available. */
    errSecTimestampSystemFailure             = -67893,    /* The timestamp request cannot be handled due to system failure. */
    errSecSigningTimeMissing                 = -67894,    /* A signing time was expected but was not found. */
    errSecTimestampRejection                 = -67895,    /* A timestamp transaction was rejected. */
    errSecTimestampWaiting                   = -67896,    /* A timestamp transaction is waiting. */
    errSecTimestampRevocationWarning         = -67897,    /* A timestamp authority revocation warning was issued. */
    errSecTimestampRevocationNotification    = -67898,    /* A timestamp authority revocation notification was issued. */
    errSecCertificatePolicyNotAllowed        = -67899,    /* The requested policy is not allowed for this certificate. */
    errSecCertificateNameNotAllowed          = -67900,    /* The requested name is not allowed for this certificate. */
    errSecCertificateValidityPeriodTooLong   = -67901,    /* The validity period in the certificate exceeds the maximum allowed. */
};


/*!
 @enum SecureTransport Error Codes
 @abstract Result codes returned from SecureTransport and SecProtocol functions. This is also the domain
   for TLS errors in the network stack.

 @constant errSSLProtocol SSL protocol error
 @constant errSSLNegotiation Cipher Suite negotiation failure
 @constant errSSLFatalAlert Fatal alert
 @constant errSSLWouldBlock I/O would block (not fatal)
 @constant errSSLSessionNotFound attempt to restore an unknown session
 @constant errSSLClosedGraceful connection closed gracefully
 @constant errSSLClosedAbort connection closed via error
 @constant errSSLXCertChainInvalid invalid certificate chain
 @constant errSSLBadCert bad certificate format
 @constant errSSLCrypto underlying cryptographic error
 @constant errSSLInternal Internal error
 @constant errSSLModuleAttach module attach failure
 @constant errSSLUnknownRootCert valid cert chain, untrusted root
 @constant errSSLNoRootCert cert chain not verified by root
 @constant errSSLCertExpired chain had an expired cert
 @constant errSSLCertNotYetValid chain had a cert not yet valid
 @constant errSSLClosedNoNotify server closed session with no notification
 @constant errSSLBufferOverflow insufficient buffer provided
 @constant errSSLBadCipherSuite bad SSLCipherSuite
 @constant errSSLPeerUnexpectedMsg unexpected message received
 @constant errSSLPeerBadRecordMac bad MAC
 @constant errSSLPeerDecryptionFail decryption failed
 @constant errSSLPeerRecordOverflow record overflow
 @constant errSSLPeerDecompressFail decompression failure
 @constant errSSLPeerHandshakeFail handshake failure
 @constant errSSLPeerBadCert misc. bad certificate
 @constant errSSLPeerUnsupportedCert bad unsupported cert format
 @constant errSSLPeerCertRevoked certificate revoked
 @constant errSSLPeerCertExpired certificate expired
 @constant errSSLPeerCertUnknown unknown certificate
 @constant errSSLIllegalParam illegal parameter
 @constant errSSLPeerUnknownCA unknown Cert Authority
 @constant errSSLPeerAccessDenied access denied
 @constant errSSLPeerDecodeError decoding error
 @constant errSSLPeerDecryptError decryption error
 @constant errSSLPeerExportRestriction export restriction
 @constant errSSLPeerProtocolVersion bad protocol version
 @constant errSSLPeerInsufficientSecurity insufficient security
 @constant errSSLPeerInternalError internal error
 @constant errSSLPeerUserCancelled user canceled
 @constant errSSLPeerNoRenegotiation no renegotiation allowed
 @constant errSSLPeerAuthCompleted peer cert is valid, or was ignored if verification disabled
 @constant errSSLClientCertRequested server has requested a client cert
 @constant errSSLHostNameMismatch peer host name mismatch
 @constant errSSLConnectionRefused peer dropped connection before responding
 @constant errSSLDecryptionFail decryption failure
 @constant errSSLBadRecordMac bad MAC
 @constant errSSLRecordOverflow record overflow
 @constant errSSLBadConfiguration configuration error
 @constant errSSLUnexpectedRecord unexpected (skipped) record in DTLS
 @constant errSSLWeakPeerEphemeralDHKey weak ephemeral dh key
 @constant errSSLClientHelloReceived SNI
 @constant errSSLTransportReset transport (socket) shutdown, e.g., TCP RST or FIN.
 @constant errSSLNetworkTimeout network timeout triggered
 @constant errSSLConfigurationFailed TLS configuration failed
 @constant errSSLUnsupportedExtension unsupported TLS extension
 @constant errSSLUnexpectedMessage peer rejected unexpected message
 @constant errSSLDecompressFail decompression failed
 @constant errSSLHandshakeFail handshake failed
 @constant errSSLDecodeError decode failed
 @constant errSSLInappropriateFallback inappropriate fallback
 @constant errSSLMissingExtension missing extension
 @constant errSSLBadCertificateStatusResponse bad OCSP response
 @constant errSSLCertificateRequired certificate required
 @constant errSSLUnknownPSKIdentity unknown PSK identity
 @constant errSSLUnrecognizedName unknown or unrecognized name
 @constant errSSLATSViolation ATS violation
 @constant errSSLATSMinimumVersionViolation ATS violation: minimum protocol version is not ATS compliant
 @constant errSSLATSCiphersuiteViolation ATS violation: selected ciphersuite is not ATS compliant
 @constant errSSLATSMinimumKeySizeViolation ATS violation: peer key size is not ATS compliant
 @constant errSSLATSLeafCertificateHashAlgorithmViolation ATS violation: peer leaf certificate hash algorithm is not ATS compliant
 @constant errSSLATSCertificateHashAlgorithmViolation ATS violation: peer certificate hash algorithm is not ATS compliant
 @constant errSSLATSCertificateTrustViolation ATS violation: peer certificate is not issued by trusted peer
 */

/*
 Note: the comments that appear after these errors are used to create SecErrorMessages.strings.
 The comments must not be multi-line, and should be in a form meaningful to an end user. If
 a different or additional comment is needed, it can be put in the header doc format, or on a
 line that does not start with errZZZ.
 */
CF_ENUM(OSStatus) {
    errSSLProtocol                                  = -9800,    /* SSL protocol error */
    errSSLNegotiation                               = -9801,    /* Cipher Suite negotiation failure */
    errSSLFatalAlert                                = -9802,    /* Fatal alert */
    errSSLWouldBlock                                = -9803,    /* I/O would block (not fatal) */
    errSSLSessionNotFound                           = -9804,    /* attempt to restore an unknown session */
    errSSLClosedGraceful                            = -9805,    /* connection closed gracefully */
    errSSLClosedAbort                               = -9806,    /* connection closed via error */
    errSSLXCertChainInvalid                         = -9807,    /* invalid certificate chain */
    errSSLBadCert                                   = -9808,    /* bad certificate format */
    errSSLCrypto                                    = -9809,    /* underlying cryptographic error */
    errSSLInternal                                  = -9810,    /* Internal error */
    errSSLModuleAttach                              = -9811,    /* module attach failure */
    errSSLUnknownRootCert                           = -9812,    /* valid cert chain, untrusted root */
    errSSLNoRootCert                                = -9813,    /* cert chain not verified by root */
    errSSLCertExpired                               = -9814,    /* chain had an expired cert */
    errSSLCertNotYetValid                           = -9815,    /* chain had a cert not yet valid */
    errSSLClosedNoNotify                            = -9816,    /* server closed session with no notification */
    errSSLBufferOverflow                            = -9817,    /* insufficient buffer provided */
    errSSLBadCipherSuite                            = -9818,    /* bad SSLCipherSuite */

    /* fatal errors detected by peer */
    errSSLPeerUnexpectedMsg                         = -9819,    /* unexpected message received */
    errSSLPeerBadRecordMac                          = -9820,    /* bad MAC */
    errSSLPeerDecryptionFail                        = -9821,    /* decryption failed */
    errSSLPeerRecordOverflow                        = -9822,    /* record overflow */
    errSSLPeerDecompressFail                        = -9823,    /* decompression failure */
    errSSLPeerHandshakeFail                         = -9824,    /* handshake failure */
    errSSLPeerBadCert                               = -9825,    /* misc. bad certificate */
    errSSLPeerUnsupportedCert                       = -9826,    /* bad unsupported cert format */
    errSSLPeerCertRevoked                           = -9827,    /* certificate revoked */
    errSSLPeerCertExpired                           = -9828,    /* certificate expired */
    errSSLPeerCertUnknown                           = -9829,    /* unknown certificate */
    errSSLIllegalParam                              = -9830,    /* illegal parameter */
    errSSLPeerUnknownCA                             = -9831,    /* unknown Cert Authority */
    errSSLPeerAccessDenied                          = -9832,    /* access denied */
    errSSLPeerDecodeError                           = -9833,    /* decoding error */
    errSSLPeerDecryptError                          = -9834,    /* decryption error */
    errSSLPeerExportRestriction                     = -9835,    /* export restriction */
    errSSLPeerProtocolVersion                       = -9836,    /* bad protocol version */
    errSSLPeerInsufficientSecurity                  = -9837,    /* insufficient security */
    errSSLPeerInternalError                         = -9838,    /* internal error */
    errSSLPeerUserCancelled                         = -9839,    /* user canceled */
    errSSLPeerNoRenegotiation                       = -9840,    /* no renegotiation allowed */

    /* non-fatal result codes */
    errSSLPeerAuthCompleted                         = -9841,    /* peer cert is valid, or was ignored if verification disabled */
    errSSLClientCertRequested                       = -9842,    /* server has requested a client cert */

    /* more errors detected by us */
    errSSLHostNameMismatch                          = -9843,    /* peer host name mismatch */
    errSSLConnectionRefused                         = -9844,    /* peer dropped connection before responding */
    errSSLDecryptionFail                            = -9845,    /* decryption failure */
    errSSLBadRecordMac                              = -9846,    /* bad MAC */
    errSSLRecordOverflow                            = -9847,    /* record overflow */
    errSSLBadConfiguration                          = -9848,    /* configuration error */
    errSSLUnexpectedRecord                          = -9849,    /* unexpected (skipped) record in DTLS */
    errSSLWeakPeerEphemeralDHKey                    = -9850,    /* weak ephemeral dh key  */

    /* non-fatal result codes */
    errSSLClientHelloReceived                       = -9851,    /* SNI */

    /* fatal errors resulting from transport or networking errors */
    errSSLTransportReset                            = -9852,    /* transport (socket) shutdown, e.g., TCP RST or FIN. */
    errSSLNetworkTimeout                            = -9853,    /* network timeout triggered */

    /* fatal errors resulting from software misconfiguration */
    errSSLConfigurationFailed                       = -9854,    /* TLS configuration failed */

    /* additional errors */
    errSSLUnsupportedExtension                      = -9855,    /* unsupported TLS extension */
    errSSLUnexpectedMessage                         = -9856,    /* peer rejected unexpected message */
    errSSLDecompressFail                            = -9857,    /* decompression failed */
    errSSLHandshakeFail                             = -9858,    /* handshake failed */
    errSSLDecodeError                               = -9859,    /* decode failed */
    errSSLInappropriateFallback                     = -9860,    /* inappropriate fallback */
    errSSLMissingExtension                          = -9861,    /* missing extension */
    errSSLBadCertificateStatusResponse              = -9862,    /* bad OCSP response */
    errSSLCertificateRequired                       = -9863,    /* certificate required */
    errSSLUnknownPSKIdentity                        = -9864,    /* unknown PSK identity */
    errSSLUnrecognizedName                          = -9865,    /* unknown or unrecognized name */

    /* ATS compliance violation errors */
    errSSLATSViolation                              = -9880,    /* ATS violation */
    errSSLATSMinimumVersionViolation                = -9881,    /* ATS violation: minimum protocol version is not ATS compliant */
    errSSLATSCiphersuiteViolation                   = -9882,    /* ATS violation: selected ciphersuite is not ATS compliant */
    errSSLATSMinimumKeySizeViolation                = -9883,    /* ATS violation: peer key size is not ATS compliant */
    errSSLATSLeafCertificateHashAlgorithmViolation  = -9884,    /* ATS violation: peer leaf certificate hash algorithm is not ATS compliant */
    errSSLATSCertificateHashAlgorithmViolation      = -9885,    /* ATS violation: peer certificate hash algorithm is not ATS compliant */
    errSSLATSCertificateTrustViolation              = -9886,    /* ATS violation: peer certificate is not issued by trusted peer */
};

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* _SECURITY_SECBASE_H_ */
// ==========  Security.framework/Headers/SecSharedCredential.h
/*
 * Copyright (c) 2014-2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 @header SecSharedCredential
 SecSharedCredential defines CoreFoundation-based functions for
 storing and requesting shared password-based credentials.
 These credentials are currently able to be shared with Safari and
 applications which have a 'com.apple.developer.associated-domains'
 entitlement that includes the domain being requested.
 */

#ifndef _SECURITY_SECSHAREDCREDENTIAL_H_
#define _SECURITY_SECSHAREDCREDENTIAL_H_

#include <Security/SecItem.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AvailabilityMacros.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

#ifdef __BLOCKS__

/*!
    @enum Credential Key Constants
    @discussion Predefined key constants used to get values in a dictionary
        of credentials returned by SecRequestWebCredential.
    @constant kSecSharedPassword Specifies a dictionary key whose value is a
        shared password. You use this key to get a value of type CFStringRef
        that contains a password.
*/
extern const CFStringRef kSecSharedPassword API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos, watchos);

/*!
 @function SecAddSharedWebCredential
 @abstract Asynchronously store (or update) a shared password for a website.
 @param fqdn The fully qualified domain name of the website requiring the password.
 @param account The account name associated with this password.
 @param password The password to be stored. Pass NULL to remove a shared password if it exists.
 @param completionHandler A block which will be invoked when the function has completed. If the shared password was successfully added (or removed), the CFErrorRef parameter passed to the block will be NULL. If the error parameter is non-NULL, an error occurred and the error reference will hold the result. Note: the error reference will be automatically released after this handler is called, though you may optionally retain it for as long as needed.
 @discussion This function adds a shared password item which will be accessible by Safari and applications that have the specified fully-qualified domain name in their 'com.apple.developer.associated-domains' entitlement. If a shared password item already exists for the specified website and account, it will be updated with the provided password. To remove a password, pass NULL for the password parameter.

 Note: since a request involving shared web credentials may potentially require user interaction or other verification to be approved, this function is dispatched asynchronously; your code provides a completion handler that will be called once the results (if any) are available.
 */
void SecAddSharedWebCredential(CFStringRef fqdn, CFStringRef account, CFStringRef __nullable password,
    void (^completionHandler)(CFErrorRef __nullable error)) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos, watchos);

/*!
 @function SecRequestSharedWebCredential
 @abstract Asynchronously obtain one or more shared passwords for a website.
 @param fqdn (Optional) Fully qualified domain name of the website for which passwords are being requested. If NULL is passed in this argument, the domain name(s) listed in the calling application's 'com.apple.developer.associated-domains' entitlement are searched implicitly.
 @param account (Optional) Account name for which passwords are being requested. The account may be NULL to request all shared credentials which are available for the site, allowing the caller to discover an existing account.
 @param completionHandler A block which will be called to deliver the requested credentials. If no matching items were found, the credentials array will be empty, and the CFErrorRef parameter will provide the error result. Note: the credentials and error references will be automatically released after this handler is called, though you may optionally retain either for as long as needed.
 @discussion This function requests one or more shared passwords for a given website, depending on whether the optional account parameter is supplied. To obtain results, the website specified in the fqdn parameter must be one which matches an entry in the calling application's 'com.apple.developer.associated-domains' entitlement.

 If matching shared password items are found, the credentials provided to the completionHandler will be a CFArrayRef containing CFDictionaryRef entries. Each dictionary entry will contain the following pairs (see Security/SecItem.h):
        key: kSecAttrServer     value: CFStringRef (the website)
        key: kSecAttrAccount    value: CFStringRef (the account)
        key: kSecSharedPassword value: CFStringRef (the password)

 If the found item specifies a non-standard port number (i.e. other than 443 for https), the following key may also be present:
        key: kSecAttrPort       value: CFNumberRef (the port number)

 Note: since a request involving shared web credentials may potentially require user interaction or other verification to be approved, this function is dispatched asynchronously; your code provides a completion handler that will be called once the results (if any) are available.
 */
void SecRequestSharedWebCredential(CFStringRef __nullable fqdn, CFStringRef __nullable account,
    void (^completionHandler)(CFArrayRef __nullable credentials, CFErrorRef __nullable error)) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos, watchos);

/*!
 @function SecCreateSharedWebCredentialPassword
 @abstract Returns a randomly generated password.
 @return CFStringRef password in the form xxx-xxx-xxx-xxx where x is taken from the sets "abcdefghkmnopqrstuvwxy", "ABCDEFGHJKLMNPQRSTUVWXYZ", "3456789" with at least one character from each set being present.
*/
__nullable
CFStringRef SecCreateSharedWebCredentialPassword(void) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos, watchos);


#endif /* __BLOCKS__ */

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECSHAREDCREDENTIAL_H_ */

// ==========  Security.framework/Headers/SecImportExport.h
/*
 * Copyright (c) 2000-2011,2012-2014,2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
     @header SecImportExport
     contains import/export functionality for keys and certificates.
*/
#ifndef _SECURITY_SECIMPORTEXPORT_H_
#define _SECURITY_SECIMPORTEXPORT_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>

#if SEC_OS_OSX
#include <Security/cssmtype.h>
#include <Security/SecAccess.h>
#include <Security/SecKeychain.h>
#include <stdint.h>
#endif /* SEC_OS_OSX */

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

#if SEC_OS_OSX
/*
 * Supported import/export Formats
 */
typedef CF_ENUM(uint32_t, SecExternalFormat)
{
     /*
      * When importing: unknown format
      * When exporting: default format for item
      */
     kSecFormatUnknown = 0,

     /*
      * Public and Private Key formats.
      * Default for export is kSecFormatOpenSSL.
      */
     kSecFormatOpenSSL,                 /* a.k.a. X509 for public keys */
     kSecFormatSSH,                     /* OpenSSH v.1 */
     kSecFormatBSAFE,

     /* Symmetric Key Formats */
     kSecFormatRawKey,                  /* raw unformatted key bits; default */

     /* Formats for wrapped symmetric and private keys */
     kSecFormatWrappedPKCS8,
     kSecFormatWrappedOpenSSL,          /* traditional openssl */
     kSecFormatWrappedSSH,              /* OpenSSH v.1 */
     kSecFormatWrappedLSH,

     /* Formats for certificates */
     kSecFormatX509Cert,                /* DER encoded; default */

     /* Aggregate Types */
     kSecFormatPEMSequence,             /* sequence of certs and/or keys, implies PEM
                                         *    armour. Default format for multiple items */
     kSecFormatPKCS7,                   /* sequence of certs */
     kSecFormatPKCS12,                  /* set of certs and private keys */
     kSecFormatNetscapeCertSequence,    /* sequence of certs, form netscape-cert-sequence */

     /* Added in Mac OS X 10.5 */
     kSecFormatSSHv2                    /* OpenSSH v.2. Note that OpenSSH v2 private keys
                                         * are in format kSecFormatOpenSSL or
                                         * kSecFormatWrappedOpenSSL. */
};

/*
 * Indication of basic item type when importing.
 */
typedef CF_ENUM(uint32_t, SecExternalItemType) {
     kSecItemTypeUnknown,               /* caller doesn't know what this is */
     kSecItemTypePrivateKey,
     kSecItemTypePublicKey,
     kSecItemTypeSessionKey,
     kSecItemTypeCertificate,
     kSecItemTypeAggregate               /* PKCS7, PKCS12, kSecFormatPEMSequence, etc. */
};

/*
 * Flags passed to SecKeychainItemExport() and SecKeychainItemImport().
 */
typedef CF_OPTIONS(uint32_t, SecItemImportExportFlags)
{
     kSecItemPemArmour               = 0x00000001,   /* exported blob is PEM formatted */
};

/*
 * SecKeyRef-specific flags, specified in SecKeyImportExportParameters.flags
 */
typedef CF_OPTIONS(uint32_t, SecKeyImportExportFlags)
{
     /*
      * When true, prevents the importing of more than one private key
      * in a given SecKeychainItemImport().
      */
     kSecKeyImportOnlyOne          = 0x00000001,

     /*
      * When true, passphrase for import/export is obtained by user prompt
      * instead of by caller-supplied data (SecKeyImportExportParameters.passphrase).
      * This is the preferred method for obtaining a user-supplied passphrase
      * as it avoids having the cleartext passphrase appear in the app's
      * address space at any time.
      */
     kSecKeySecurePassphrase          = 0x00000002,

     /*
      * When true, imported private keys will have no Access Control List
      * (ACL) attached to them. In the absence of both this bit and the accessRef
      * field in SecKeyImportExportParameters (see below), imported private
      * keys are given a default ACL.
      */
     kSecKeyNoAccessControl          = 0x00000004
};

/*
 * Version of a SecKeyImportExportParameters.
 */
#define SEC_KEY_IMPORT_EXPORT_PARAMS_VERSION          0

/*
 * Parameters specific to SecKeyRefs.
 */
typedef struct API_UNAVAILABLE(ios, watchos, tvos, uikitformac)
{
     /* for import and export */
     uint32_t                    version;        /* SEC_KEY_IMPORT_EXPORT_PARAMS_VERSION */
     SecKeyImportExportFlags flags;              /* SecKeyImportExportFlags bits */
     CFTypeRef __nullable           passphrase;  /* kSecFormatPKCS12, kSecFormatWrapped*
                                                  *    formats only. Legal types are
                                                  *    CFStringRef and CFDataRef. */
     CFStringRef                    alertTitle;  /* title of secure passphrase alert panel */
     CFStringRef                    alertPrompt; /* prompt in secure passphrase alert panel */

     /* for import only */
     SecAccessRef __nullable accessRef;          /* specifies the initial ACL of imported
                                                  *    key(s) */
     CSSM_KEYUSE                    keyUsage;    /* CSSM_KEYUSE_DECRYPT, CSSM_KEYUSE_SIGN,
                                                  *    etc. */
     CSSM_KEYATTR_FLAGS          keyAttributes;  /* CSSM_KEYATTR_PERMANENT, etc. */
} SecKeyImportExportParameters API_UNAVAILABLE(ios, watchos, tvos, uikitformac);


typedef struct API_UNAVAILABLE(ios, watchos, tvos, uikitformac)
{
     /* for import and export */
     uint32_t                    version;        /* SEC_KEY_IMPORT_EXPORT_PARAMS_VERSION */
     SecKeyImportExportFlags flags;              /* SecKeyImportExportFlags bits */
     CFTypeRef __nullable           passphrase;    /* kSecFormatPKCS12, kSecFormatWrapped*
                                                  *    formats only. Legal types are
                                                  *    CFStringRef and CFDataRef. */
     CFStringRef __nullable         alertTitle;  /* title of secure passphrase alert panel */
     CFStringRef __nullable         alertPrompt; /* prompt in secure passphrase alert panel */

     /* for import only */
     SecAccessRef __nullable     accessRef;      /* specifies the initial ACL of imported
                                                  *    key(s) */
     CFArrayRef __nullable   keyUsage;           /* An Array containing usage attributes from SecItem.h, e.g.
                                                  *     kSecAttrCanEncrypt;, kSecAttrCanDecrypt, kSecAttrCanDerive, etc.
                                                  */
     CFArrayRef __nullable   keyAttributes;      /* An array containing zero or more key attributes
                                                  *    for an imported key. Possible values (from SecItem.h):
                                                  *    kSecAttrIsPermanent, kSecAttrIsSensitive, kSecAttrIsExtractable
                                                  *    Pass NULL in this field to use default attributes:
                                                  *    - kSecAttrIsPermanent if a keychain is specified
                                                  *    - kSecAttrIsSensitive for private keys
                                                  *    - kSecAttrIsExtractable by default
                                                  */
} SecItemImportExportKeyParameters API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*
 * SecKeychainItemExport()
 *
 * This function takes one or more SecKeychainItemRefs and creates an
 * external representation of the item(s) in the form of a CFDataRef.
 * Caller specifies the format of the external representation via a
 * SecExternalFormat enum. Caller may specify kSecFormatUnknown for
 * the format, in which case a the default format for the item
 * being exported is used (as described in the SecExternalFormat enums).
 * PEM armouring is optional and is specified by the kSecItemPemArmour
 * flag in importFlags.
 *
 * If exactly one item is to be exported, the keychainItemOrArray argument
 * can be a SecKeychainItem. Otherwise this argument is a CFArrayRef
 * containing a number of SecKeychainItems.
 *
 * The exported item(s) is (are) returned to the caller via the
 * CFDataRef *exportedData argument. Caller must CFRelease the result.
 *
 * The following SecKeychainItems may be exported:
 *
 *   SecCertificateRef
 *   SecKeyRef
 *   SecIdentityRef
 *
 *
 * Key-related SecKeyImportExportParameters fields
 * -----------------------------------------------
 *
 * When exporting SecKeyRefs in one of the wrapped formats
 * (kSecFormatWrappedOpenSSL, kSecFormatWrappedSSH,
 * kSecFormatWrappedPKCS8), or in PKCS12 format, caller must
 * either explicitly specify the passphrase field or set
 * the kSecKeySecurePassphrase bit in SecKeyImportExportFlags.
 *
 * If kSecKeySecurePassphrase is selected, caller can optionally
 * specify strings for the passphrase panel's title bar and for
 * the prompt which appears in the panel via the alertTitle and
 * alertPrompt fields in SecKeyImportExportParameters.
 *
 * If an explicit passphrase is specified, note that PKCS12
 * explicitly requires that passphrases are in Unicode format;
 * passing in a CFStringRef as the passphrase is the safest way
 * to ensure that this requirement is met (and that the result
 * will be compatible with other implementations). If a CFDataRef
 * is supplied as the passphrase for a PKCS12 export operation,
 * the referent data is assumed to be in UTF8 form and will be
 * converted as appropriate.
 *
 * If no key items are being exported, the keyParams argument may be NULL.
 * @discussion This API has been deprecated. Please us the SecItemExport API instead.
 */
OSStatus SecKeychainItemExport(
     CFTypeRef                              keychainItemOrArray,
     SecExternalFormat                      outputFormat,
     SecItemImportExportFlags               flags,                  /* kSecItemPemArmour, etc. */
     const SecKeyImportExportParameters * __nullable keyParams,     /* optional */
     CFDataRef * __nonnull CF_RETURNS_RETAINED exportedData)        /* external representation returned here */
          API_DEPRECATED_WITH_REPLACEMENT("SecItemExport", macos(10.0, 10.7)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*
 * SecItemExport()
 *
 * This function takes one or more SecItemRefs and creates an
 * external representation of the item(s) in the form of a CFDataRef.
 * Caller specifies the format of the external representation via a
 * SecExternalFormat enum. Caller may specify kSecFormatUnknown for
 * the format, in which case a the default format for the item
 * being exported is used (as described in the SecExternalFormat enums).
 * PEM armouring is optional and is specified by the kSecItemPemArmour
 * flag in importFlags.
 *
 * If exactly one item is to be exported, the keychainItemOrArray argument
 * can be a SecKeychainItem. Otherwise this argument is a CFArrayRef
 * containing a number of SecKeychainItems.
 *
 * The exported item(s) is (are) returned to the caller via the
 * CFDataRef *exportedData argument. Caller must CFRelease the result.
 *
 * The following SecKeychainItems may be exported:
 *
 *   SecCertificateRef
 *   SecKeyRef
 *   SecIdentityRef
 *
 *
 * Key-related SecItemExport fields
 * -----------------------------------------------
 *
 * When exporting SecKeyRefs in one of the wrapped formats
 * (kSecFormatWrappedOpenSSL, kSecFormatWrappedSSH,
 * kSecFormatWrappedPKCS8), or in PKCS12 format, caller must
 * either explicitly specify the passphrase field or set
 * the kSecKeySecurePassphrase bit in SecKeyImportExportFlags.
 *
 * If kSecKeySecurePassphrase is selected, caller can optionally
 * specify strings for the passphrase panel's title bar and for
 * the prompt which appears in the panel via the alertTitle and
 * alertPrompt fields in SecItemImportExportKeyParameters.
 *
 * If an explicit passphrase is specified, note that PKCS12
 * explicitly requires that passphrases are in Unicode format;
 * passing in a CFStringRef as the passphrase is the safest way
 * to ensure that this requirement is met (and that the result
 * will be compatible with other implementations). If a CFDataRef
 * is supplied as the passphrase for a PKCS12 export operation,
 * the referent data is assumed to be in UTF8 form and will be
 * converted as appropriate.
 *
 * If no key items are being exported, the keyParams argument may be NULL.
 *
 */
OSStatus SecItemExport(
     CFTypeRef                              secItemOrArray,
     SecExternalFormat                      outputFormat,
     SecItemImportExportFlags               flags,                   /* kSecItemPemArmour, etc. */
     const SecItemImportExportKeyParameters * __nullable keyParams,  /* optional */
     CFDataRef * __nonnull CF_RETURNS_RETAINED exportedData)         /* external representation returned here */
          API_AVAILABLE(macos(10.7), ios(NA));
/*
 * SecKeychainItemImport()
 *
 * This function takes a CFDataRef containing the external representation
 * of one or more objects and creates SecKeychainItems corresponding to
 * those objects and optionally imports those SecKeychainItems into a
 * specified keychain. The format of the incoming representation is
 * specified by one or more of the following:
 *
 * -- A SecExternalFormat. This optional in/out argument is used when
 *    the caller knows exactly what format the external representation
 *    is in. It's also used to return to the caller the format which the
 *    function actually determines the external representation to be in.
 *    A value of kSecFormatUnknown is specified on entry when the caller
 *    wishes to know the inferred format on return.
 *
 * -- A SecExternalItemType - optional, in/out. Used to specify what kind
 *    of item is in the incoming representation, if known by the caller.
 *    It's also used to return to the caller the item type which the
 *    function actually determines the external representation to contain.
 *    A value of kSecItemTypeUnknown is specified on entry when the caller
 *    wishes to know the inferred item type on return.
 *
 * -- fileNameOrExtension, a CFStringRef. This optional argument contains
 *    the name of the file from which the external representation was
 *    obtained; it can also be simply an extension like CFSTR(".p7r").
 *    This is a convenience for apps like KeychainAccess which can import a
 *    number of different formats.
 *
 * The SecKeychainItemImport() call does its best to figure out what is
 * in an incoming external item given the info provided by the above three
 * arguments. In most cases, SecKeychainItemImport() can even figure out
 * what's in an external item if none of these are specified, but it would
 * be unwise for an application to count on that ability.
 *
 * PEM formatting is determined internally via inspection of the incoming
 * data, so the kSecItemPemArmour in the flags field is ignored.
 *
 * Zero, one, or both of the following occurs upon successful completion
 * of this function:
 *
 * -- The imported item(s) is (are) imported to the specified importKeychain.
 *    If importKeychain is NULL, this step does not occur.
 *
 * -- The imported item(s) is (are) returned to the caller via the
 *    CFArrayRef *outItems argument. If outItems is NULL, this step
 *    does not occur. If outItems is NON-NULL, then *outItems will be
 *    a CFArrayRef containing a number of SecKeychainItems upon return.
 *    Caller must CFRelease the result.
 *
 * The possible types of returned SecKeychainItems are:
 *
 *   SecCertificateRef
 *   SecKeyRef
 *   SecIdentityRef
 *
 * Note that when importing a PKCS12 blob, typically one SecIdentityRef
 * and zero or more additional SecCertificateRefs are returned in
 * outItems. No SecKeyRefs will appear there unless a key
 * is found in the incoming blob with does not have a matching
 * certificate.
 *
 * A typical case in which an app specifies the outItems
 * argument and a NULL for importKeychain is when the app wishes to
 * perform some user interaction, perhaps on a per-item basis, before
 * committing to actually import the item(s). In this case, if the app
 * does wish to proceed with the import, the standard import calls
 * (SecCertificateAddToKeychain(), SecKeyAddToKeychain (implementation
 * TBD)) would be used.
 *
 * Passing in NULL for both outItems and importKeychain
 * is a perfectly acceptable way of using this function to determine,
 * in a non-intrusive way, what is inside a given data blob. No effect
 * other than returning inputFormat and/or itemType occurs in this
 * case.

 *
 * Key-related SecKeyImportExportParameters fields
 * -----------------------------------------------
 *
 * If importKeychain is NULL, the kSecKeyImportOnlyOne bit in the flags
 * argument is ignored. Otherwise, if the kSecKeyImportOnlyOne bit is set, and
 * there is more than one key in the incoming external representation, no
 * items will be imported to the specified keychain and errSecMultipleKeys will
 * be returned.
 *
 * The accessRef field allows the caller to specify the initial SecAccessRef
 * for imported private keys. If more than one private key is being imported,
 * all private keys get the same initial SecAccessRef. If this field is NULL
 * when private keys are being imported, then the ACL attached to imported
 * private keys depends on the kSecKeyNoAccessControl bit in the specified
 * keyParams->flags. If this bit is 0, or keyParams is NULL, the default ACL
 * will be used. If this bit is 1, no ACL will be attached to imported
 * private keys.
 *
 * keyUsage and keyAttributes specify the low-level usage and attribute flags
 * of imported keys. Each is a word of bits. The default value for keyUsage
 * (used when keyParams is NULL or if keyParams->keyUsage is zero) is
 * CSSM_KEYUSE_ANY. The default value for keyAttributes defaults is
 * CSSM_KEYATTR_SENSITIVE | CSSM_KEYATTR_EXTRACTABLE; the CSSM_KEYATTR_PERMANENT
 * bit is also added to the default if a non-NULL importKeychain is provided.
 *
 * The following are valid bits in keyAttributes:
 *
 *   CSSM_KEYATTR_PERMANENT
 *   CSSM_KEYATTR_SENSITIVE
 *   CSSM_KEYATTR_EXTRACTABLE
 *
 * If the CSSM_KEYATTR_PERMANENT is set then the importKeychain argument must
 * be valid or errSecInvalidKeychain will be returned if in fact any keys are found
 * in the external representation.
 *
 * Note that if the caller does not set the CSSM_KEYATTR_EXTRACTABLE, this key
 * will never be able to be extracted from the keychain in any form, not even
 * in wrapped form. The CSSM_KEYATTR_SENSITIVE indicates that the key can only
 * be extracted in wrapped form.
 *
 * The CSSM_KEYATTR_RETURN_xxx bits are always forced to
 * CSSM_KEYATTR_RETURN_REF regardless of the specified keyAttributes
 * field.
 *
 * When importing SecKeyRefs in one of the wrapped formats
 * (kSecFormatWrappedOpenSSL, kSecFormatWrappedSSH,
 * kSecFormatWrappedPKCS8), or in PKCS12 format, caller must
 * either explicitly specify the passphrase field or set
 * the kSecKeySecurePassphrase bit in SecKeyImportExportFlags.
 *
 * If kSecKeySecurePassphrase is selected, caller can optionally
 * specify strings for the passphrase panel's title bar and for
 * the prompt which appears in the panel via the alertTitle and
 * alertPrompt fields in SecKeyImportExportParameters.
 *
 * If an explicit passphrase is specified, note that PKCS12
 * explicitly requires that passphrases are in Unicode format;
 * passing in a CFStringRef as the passphrase is the safest way
 * to ensure that this requirement is met (and that the result
 * will be compatible with other implementations). If a CFDataRef
 * is supplied as the passphrase for a PKCS12 export operation,
 * the referent data is assumed to be in UTF8 form and will be
 * converted as appropriate.

 * If no key items are being imported, the keyParams argument may be NULL.
 *
 * The SecItemImportExportFlags argument is currently unused; caller should pass
 * in 0.
 *
 * @discussion  This API has been deprecated.  Please use the SecItemImport API instead.
 */
OSStatus SecKeychainItemImport(
     CFDataRef                                   importedData,
     CFStringRef     __nullable                    fileNameOrExtension, /* optional */
     SecExternalFormat * __nullable      inputFormat,                   /* optional, IN/OUT */
     SecExternalItemType     * __nullable    itemType,                  /* optional, IN/OUT */
     SecItemImportExportFlags               flags,
     const SecKeyImportExportParameters * __nullable keyParams,         /* optional */
     SecKeychainRef __nullable               importKeychain,            /* optional */
     CFArrayRef * __nullable CF_RETURNS_RETAINED outItems)              /* optional */
          API_DEPRECATED_WITH_REPLACEMENT("SecItemImport", macos(10.0, 10.7)) API_UNAVAILABLE(ios, watchos, tvos, uikitformac);

/*
 * SecItemImport()
 *
 * This function takes a CFDataRef containing the external representation
 * of one or more objects and creates SecKeychainItems corresponding to
 * those objects and optionally imports those SecKeychainItems into a
 * specified keychain. The format of the incoming representation is
 * specified by one or more of the following:
 *
 * -- A SecExternalFormat. This optional in/out argument is used when
 *    the caller knows exactly what format the external representation
 *    is in. It's also used to return to the caller the format which the
 *    function actually determines the external representation to be in.
 *    A value of kSecFormatUnknown is specified on entry when the caller
 *    wishes to know the inferred format on return.
 *
 * -- A SecExternalItemType - optional, in/out. Used to specify what kind
 *    of item is in the incoming representation, if known by the caller.
 *    It's also used to return to the caller the item type which the
 *    function actually determines the external representation to contain.
 *    A value of kSecItemTypeUnknown is specified on entry when the caller
 *    wishes to know the inferred item type on return.
 *
 * -- fileNameOrExtension, a CFStringRef. This optional argument contains
 *    the name of the file from which the external representation was
 *    obtained; it can also be simply an extension like CFSTR(".p7r").
 *    This is a convenience for apps like KeychainAccess which can import a
 *    number of different formats.
 *
 * The SecItemImport() call does its best to figure out what is
 * in an incoming external item given the info provided by the above three
 * arguments. In most cases, SecItemImport() can even figure out
 * what's in an external item if none of these are specified, but it would
 * be unwise for an application to count on that ability.
 *
 * PEM formatting is determined internally via inspection of the incoming
 * data, so the kSecItemPemArmour in the flags field is ignored.
 *
 * Zero, one, or both of the following occurs upon successful completion
 * of this function:
 *
 * -- The imported item(s) is (are) imported to the specified importKeychain.
 *    If importKeychain is NULL, this step does not occur.
 *
 * -- The imported item(s) is (are) returned to the caller via the
 *    CFArrayRef *outItems argument. If outItems is NULL, this step
 *    does not occur. If outItems is NON-NULL, then *outItems will be
 *    a CFArrayRef containing a number of SecKeychainItems upon return.
 *    Caller must CFRelease the result.
 *
 * The possible types of returned SecKeychainItems are:
 *
 *   SecCertificateRef
 *   SecKeyRef
 *   SecIdentityRef
 *
 * Note that when importing a PKCS12 blob, typically one SecIdentityRef
 * and zero or more additional SecCertificateRefs are returned in
 * outItems. No SecKeyRefs will appear there unless a key
 * is found in the incoming blob with does not have a matching
 * certificate.
 *
 * A typical case in which an app specifies the outItems
 * argument and a NULL for importKeychain is when the app wishes to
 * perform some user interaction, perhaps on a per-item basis, before
 * committing to actually import the item(s). In this case, if the app
 * does wish to proceed with the import, the standard import calls
 * (SecCertificateAddToKeychain(), SecKeyAddToKeychain (implementation
 * TBD)) would be used.
 *
 * Passing in NULL for both outItems and importKeychain
 * is a perfectly acceptable way of using this function to determine,
 * in a non-intrusive way, what is inside a given data blob. No effect
 * other than returning inputFormat and/or itemType occurs in this
 * case.

 *
 * Key-related SecItemImportExportKeyParameters fields
 * -----------------------------------------------
 *
 * If importKeychain is NULL, the kSecKeyImportOnlyOne bit in the flags
 * argument is ignored. Otherwise, if the kSecKeyImportOnlyOne bit is set, and
 * there is more than one key in the incoming external representation, no
 * items will be imported to the specified keychain and errSecMultipleKeys will
 * be returned.
 *
 * The accessRef field allows the caller to specify the initial SecAccessRef
 * for imported private keys. If more than one private key is being imported,
 * all private keys get the same initial SecAccessRef. If this field is NULL
 * when private keys are being imported, then the ACL attached to imported
 * private keys depends on the kSecKeyNoAccessControl bit in the specified
 * keyParams->flags. If this bit is 0, or keyParams is NULL, the default ACL
 * will be used. If this bit is 1, no ACL will be attached to imported
 * private keys.
 *
 * keyUsage and keyAttributes specify the low-level usage and attribute flags
 * of imported keys. These fields contain a CFArray whose values are constants
 * from SecItem.h.
 *
 * Possible values in the keyUsage array:
 *
 *   kSecAttrCanEncrypt
 *   kSecAttrCanDecrypt
 *   kSecAttrCanDerive
 *   kSecAttrCanSign
 *   kSecAttrCanVerify
 *   kSecAttrCanWrap
 *   kSecAttrCanUnwrap
 *
 * If keyUsage is set to NULL, then any key usage is permitted.
 *
 * Possible values in the keyAttributes array:
 *
 *   kSecAttrIsPermanent
 *   kSecAttrIsSensitive
 *   kSecAttrIsExtractable
 *
 * If keyAttributes is set to NULL, then default values are used:
 *   kSecAttrIsPermanent if an import keychain is specified
 *   kSecAttrIsSensitive for non-public keys
 *   kSecAttrIsExtractable
 *
 * If the kSecAttrIsPermanent attribute is set, then the
 * importKeychain argument must be valid or errSecInvalidKeychain
 * will be returned even if keys were able to be imported.
 *
 * Note that if the caller provides a keyAttributes array but
 * does not set kSecAttrIsExtractable, this key will never be
 * able to be extracted from the keychain in any form, not even
 * in wrapped form. kSecAttrIsSensitive indicates that the key
 * can only be extracted in wrapped form.
 *
 * When importing SecKeyRefs in one of the wrapped formats
 * (kSecFormatWrappedOpenSSL, kSecFormatWrappedSSH,
 * kSecFormatWrappedPKCS8), or in PKCS12 format, caller must
 * either explicitly specify the passphrase field or set
 * the kSecKeySecurePassphrase bit in SecKeyImportExportFlags.
 *
 * If kSecKeySecurePassphrase is selected, caller can optionally
 * specify strings for the passphrase panel's title bar and for
 * the prompt which appears in the panel via the alertTitle and
 * alertPrompt fields in SecItemImportExportKeyParameters.
 *
 * If an explicit passphrase is specified, note that PKCS12
 * explicitly requires that passphrases are in Unicode format;
 * passing in a CFStringRef as the passphrase is the safest way
 * to ensure that this requirement is met (and that the result
 * will be compatible with other implementations). If a CFDataRef
 * is supplied as the passphrase for a PKCS12 export operation,
 * the referent data is assumed to be in UTF8 form and will be
 * converted as appropriate.

 * If no key items are being imported, the keyParams argument may be NULL.
 *
 * The SecItemImportExportFlags argument is currently unused; caller should pass
 * in 0.
 */
OSStatus SecItemImport(
     CFDataRef                                   importedData,
     CFStringRef __nullable                    fileNameOrExtension, /* optional */
     SecExternalFormat * __nullable      inputFormat,               /* optional, IN/OUT */
     SecExternalItemType     * __nullable    itemType,              /* optional, IN/OUT */
     SecItemImportExportFlags               flags,
     const SecItemImportExportKeyParameters * __nullable keyParams, /* optional */
     SecKeychainRef __nullable               importKeychain,        /* optional */
     CFArrayRef * __nullable CF_RETURNS_RETAINED outItems)          /* optional */
          API_AVAILABLE(macos(10.7), ios(NA));
#endif /* SEC_OS_OSX */

/*!
    @enum Import/Export options
    @discussion Predefined key constants used when passing dictionary-based arguments to import/export functions.
    @constant kSecImportExportPassphrase Specifies a passphrase represented by a CFStringRef to be used when exporting to (or importing from) PKCS#12 format.
     @constant kSecImportExportKeychain On OSX, specifies a keychain represented by a SecKeychainRef to be used as the target when importing from PKCS#12 format.
     @constant kSecImportExportAccess On OSX, specifies an access represented by a SecAccessRef for the initial access (ACL) of a key imported from PKCS#12 format.
*/
extern const CFStringRef kSecImportExportPassphrase
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecImportExportKeychain
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecImportExportAccess
    API_AVAILABLE(macos(10.7), ios(NA));

/*!
    @enum Import/Export item description
    @discussion Predefined key constants used to pass back a CFArray with a
        CFDictionary per item.

    @constant kSecImportItemLabel a CFStringRef representing the item label.
        This implementation specific identifier cannot be expected to have
        any format.
    @constant kSecImportItemKeyID a CFDataRef representing the key id.  Often
        the SHA-1 digest of the public key.
    @constant kSecImportItemIdentity a SecIdentityRef representing the identity.
    @constant kSecImportItemTrust a SecTrustRef set up with all relevant
        certificates.  Not guaranteed to succesfully evaluate.
    @constant kSecImportItemCertChain a CFArrayRef holding all relevant
        certificates for this item's identity
*/
extern const CFStringRef kSecImportItemLabel
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecImportItemKeyID
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecImportItemTrust
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecImportItemCertChain
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecImportItemIdentity
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
     @function SecPKCS12Import
     @abstract Imports the contents of a PKCS12 formatted blob.
     @param pkcs12_data The PKCS#12 formatted data to be imported.
     @param options A dictionary containing import options. A
       kSecImportExportPassphrase entry is required at minimum. Only password-based
       PKCS12 blobs are currently supported.
     @param items On return, an array containing a dictionary for every item
       extracted. Use kSecImportItem constants to access specific elements of
       these dictionaries. Your code must CFRelease the array when it is no longer
       needed.
     @result errSecSuccess in case of success. errSecDecode means either the
       blob can't be read or it is malformed. errSecAuthFailed means an
       incorrect password was supplied, or data in the container is damaged.
*/
OSStatus SecPKCS12Import(CFDataRef pkcs12_data, CFDictionaryRef options, CFArrayRef * __nonnull CF_RETURNS_RETAINED items)
     API_AVAILABLE(macos(10.6), ios(2.0));


CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECIMPORTEXPORT_H_ */
// ==========  Security.framework/Headers/CipherSuite.h
/*
 * Copyright (c) 1999-2002,2005-2007,2010-2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * CipherSuite.h - SSL Cipher Suite definitions.
 */

#ifndef _SECURITY_CIPHERSUITE_H_
#define _SECURITY_CIPHERSUITE_H_

#include <TargetConditionals.h>
#include <stdint.h>
#include <CoreFoundation/CFBase.h> /* CF_ENUM */

/*
 * Defined as enum for debugging, but in the protocol
 * it is actually exactly two bytes
 */
#if TARGET_OS_IPHONE && !TARGET_OS_UIKITFORMAC
/* 16-bit value on iOS */
typedef uint16_t SSLCipherSuite;
#else
/* 32-bit value elsewhere */
typedef uint32_t SSLCipherSuite;
#endif

CF_ENUM(SSLCipherSuite)
{   SSL_NULL_WITH_NULL_NULL =                   0x0000,
    SSL_RSA_WITH_NULL_MD5 =                     0x0001,
    SSL_RSA_WITH_NULL_SHA =                     0x0002,
    SSL_RSA_EXPORT_WITH_RC4_40_MD5 =            0x0003,
    SSL_RSA_WITH_RC4_128_MD5 =                  0x0004,
    SSL_RSA_WITH_RC4_128_SHA =                  0x0005,
    SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5 =        0x0006,
    SSL_RSA_WITH_IDEA_CBC_SHA =                 0x0007,
    SSL_RSA_EXPORT_WITH_DES40_CBC_SHA =         0x0008,
    SSL_RSA_WITH_DES_CBC_SHA =                  0x0009,
    SSL_RSA_WITH_3DES_EDE_CBC_SHA =             0x000A,
    SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA =      0x000B,
    SSL_DH_DSS_WITH_DES_CBC_SHA =               0x000C,
    SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA =          0x000D,
    SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA =      0x000E,
    SSL_DH_RSA_WITH_DES_CBC_SHA =               0x000F,
    SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA =          0x0010,
    SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA =     0x0011,
    SSL_DHE_DSS_WITH_DES_CBC_SHA =              0x0012,
    SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA =         0x0013,
    SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA =     0x0014,
    SSL_DHE_RSA_WITH_DES_CBC_SHA =              0x0015,
    SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA =         0x0016,
    SSL_DH_anon_EXPORT_WITH_RC4_40_MD5 =        0x0017,
    SSL_DH_anon_WITH_RC4_128_MD5 =              0x0018,
    SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA =     0x0019,
    SSL_DH_anon_WITH_DES_CBC_SHA =              0x001A,
    SSL_DH_anon_WITH_3DES_EDE_CBC_SHA =         0x001B,
    SSL_FORTEZZA_DMS_WITH_NULL_SHA =            0x001C,
    SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA =    0x001D,

	/* TLS addenda using AES, per RFC 3268 */
	TLS_RSA_WITH_AES_128_CBC_SHA	  =			0x002F,
	TLS_DH_DSS_WITH_AES_128_CBC_SHA	  =			0x0030,
	TLS_DH_RSA_WITH_AES_128_CBC_SHA   =			0x0031,
	TLS_DHE_DSS_WITH_AES_128_CBC_SHA  =			0x0032,
	TLS_DHE_RSA_WITH_AES_128_CBC_SHA  =			0x0033,
	TLS_DH_anon_WITH_AES_128_CBC_SHA  =			0x0034,
	TLS_RSA_WITH_AES_256_CBC_SHA      =			0x0035,
	TLS_DH_DSS_WITH_AES_256_CBC_SHA   =			0x0036,
	TLS_DH_RSA_WITH_AES_256_CBC_SHA   =			0x0037,
	TLS_DHE_DSS_WITH_AES_256_CBC_SHA  =			0x0038,
	TLS_DHE_RSA_WITH_AES_256_CBC_SHA  =			0x0039,
	TLS_DH_anon_WITH_AES_256_CBC_SHA  =			0x003A,

	/* ECDSA addenda, RFC 4492 */
	TLS_ECDH_ECDSA_WITH_NULL_SHA           =	0xC001,
	TLS_ECDH_ECDSA_WITH_RC4_128_SHA        =	0xC002,
	TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA   =	0xC003,
	TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA    =	0xC004,
	TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA    =	0xC005,
	TLS_ECDHE_ECDSA_WITH_NULL_SHA          =	0xC006,
	TLS_ECDHE_ECDSA_WITH_RC4_128_SHA       =	0xC007,
	TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA  =	0xC008,
	TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA   =	0xC009,
	TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA   =	0xC00A,
	TLS_ECDH_RSA_WITH_NULL_SHA             =	0xC00B,
	TLS_ECDH_RSA_WITH_RC4_128_SHA          =	0xC00C,
	TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA     =	0xC00D,
	TLS_ECDH_RSA_WITH_AES_128_CBC_SHA      =	0xC00E,
	TLS_ECDH_RSA_WITH_AES_256_CBC_SHA      =	0xC00F,
	TLS_ECDHE_RSA_WITH_NULL_SHA            =	0xC010,
	TLS_ECDHE_RSA_WITH_RC4_128_SHA         =	0xC011,
	TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA    =	0xC012,
	TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA     =	0xC013,
	TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA     =	0xC014,
	TLS_ECDH_anon_WITH_NULL_SHA            =	0xC015,
	TLS_ECDH_anon_WITH_RC4_128_SHA         =	0xC016,
	TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA    =	0xC017,
	TLS_ECDH_anon_WITH_AES_128_CBC_SHA     =	0xC018,
	TLS_ECDH_anon_WITH_AES_256_CBC_SHA     =	0xC019,

    /* ECDHE_PSK Cipher Suites for Transport Layer Security (TLS), RFC 5489 */
    TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA     =    0xC035,
    TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA     =    0xC036,

    /* ChaCha20-Poly1305 Cipher Suites for Transport Layer Security (TLS), RFC 7905 */
    TLS_PSK_WITH_CHACHA20_POLY1305_SHA256  =    0xCCAB,

    /* TLS 1.2 addenda, RFC 5246 */

    /* Initial state. */
    TLS_NULL_WITH_NULL_NULL                   = 0x0000,

    /* Server provided RSA certificate for key exchange. */
    TLS_RSA_WITH_NULL_MD5                     = 0x0001,
    TLS_RSA_WITH_NULL_SHA                     = 0x0002,
    TLS_RSA_WITH_RC4_128_MD5                  = 0x0004,
    TLS_RSA_WITH_RC4_128_SHA                  = 0x0005,
    TLS_RSA_WITH_3DES_EDE_CBC_SHA             = 0x000A,
    TLS_RSA_WITH_NULL_SHA256                  = 0x003B,
    TLS_RSA_WITH_AES_128_CBC_SHA256           = 0x003C,
    TLS_RSA_WITH_AES_256_CBC_SHA256           = 0x003D,

    /* Server-authenticated (and optionally client-authenticated) Diffie-Hellman. */
    TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA          = 0x000D,
    TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA          = 0x0010,
    TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA         = 0x0013,
    TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA         = 0x0016,
    TLS_DH_DSS_WITH_AES_128_CBC_SHA256        = 0x003E,
    TLS_DH_RSA_WITH_AES_128_CBC_SHA256        = 0x003F,
    TLS_DHE_DSS_WITH_AES_128_CBC_SHA256       = 0x0040,
    TLS_DHE_RSA_WITH_AES_128_CBC_SHA256       = 0x0067,
    TLS_DH_DSS_WITH_AES_256_CBC_SHA256        = 0x0068,
    TLS_DH_RSA_WITH_AES_256_CBC_SHA256        = 0x0069,
    TLS_DHE_DSS_WITH_AES_256_CBC_SHA256       = 0x006A,
    TLS_DHE_RSA_WITH_AES_256_CBC_SHA256       = 0x006B,

    /* Completely anonymous Diffie-Hellman */
    TLS_DH_anon_WITH_RC4_128_MD5              = 0x0018,
    TLS_DH_anon_WITH_3DES_EDE_CBC_SHA         = 0x001B,
    TLS_DH_anon_WITH_AES_128_CBC_SHA256       = 0x006C,
    TLS_DH_anon_WITH_AES_256_CBC_SHA256       = 0x006D,

    /* Addendum from RFC 4279, TLS PSK */
    TLS_PSK_WITH_RC4_128_SHA                  = 0x008A,
    TLS_PSK_WITH_3DES_EDE_CBC_SHA             = 0x008B,
    TLS_PSK_WITH_AES_128_CBC_SHA              = 0x008C,
    TLS_PSK_WITH_AES_256_CBC_SHA              = 0x008D,
    TLS_DHE_PSK_WITH_RC4_128_SHA              = 0x008E,
    TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA         = 0x008F,
    TLS_DHE_PSK_WITH_AES_128_CBC_SHA          = 0x0090,
    TLS_DHE_PSK_WITH_AES_256_CBC_SHA          = 0x0091,
    TLS_RSA_PSK_WITH_RC4_128_SHA              = 0x0092,
    TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA         = 0x0093,
    TLS_RSA_PSK_WITH_AES_128_CBC_SHA          = 0x0094,
    TLS_RSA_PSK_WITH_AES_256_CBC_SHA          = 0x0095,

    /* RFC 4785 - Pre-Shared Key (PSK) Ciphersuites with NULL Encryption */
    TLS_PSK_WITH_NULL_SHA                     = 0x002C,
    TLS_DHE_PSK_WITH_NULL_SHA                 = 0x002D,
    TLS_RSA_PSK_WITH_NULL_SHA                 = 0x002E,

    /* Addenda from rfc 5288 AES Galois Counter Mode (GCM) Cipher Suites for TLS. */
    TLS_RSA_WITH_AES_128_GCM_SHA256           = 0x009C,
    TLS_RSA_WITH_AES_256_GCM_SHA384           = 0x009D,
    TLS_DHE_RSA_WITH_AES_128_GCM_SHA256       = 0x009E,
    TLS_DHE_RSA_WITH_AES_256_GCM_SHA384       = 0x009F,
    TLS_DH_RSA_WITH_AES_128_GCM_SHA256        = 0x00A0,
    TLS_DH_RSA_WITH_AES_256_GCM_SHA384        = 0x00A1,
    TLS_DHE_DSS_WITH_AES_128_GCM_SHA256       = 0x00A2,
    TLS_DHE_DSS_WITH_AES_256_GCM_SHA384       = 0x00A3,
    TLS_DH_DSS_WITH_AES_128_GCM_SHA256        = 0x00A4,
    TLS_DH_DSS_WITH_AES_256_GCM_SHA384        = 0x00A5,
    TLS_DH_anon_WITH_AES_128_GCM_SHA256       = 0x00A6,
    TLS_DH_anon_WITH_AES_256_GCM_SHA384       = 0x00A7,

    /* RFC 5487 - PSK with SHA-256/384 and AES GCM */
    TLS_PSK_WITH_AES_128_GCM_SHA256           = 0x00A8,
    TLS_PSK_WITH_AES_256_GCM_SHA384           = 0x00A9,
    TLS_DHE_PSK_WITH_AES_128_GCM_SHA256       = 0x00AA,
    TLS_DHE_PSK_WITH_AES_256_GCM_SHA384       = 0x00AB,
    TLS_RSA_PSK_WITH_AES_128_GCM_SHA256       = 0x00AC,
    TLS_RSA_PSK_WITH_AES_256_GCM_SHA384       = 0x00AD,

    TLS_PSK_WITH_AES_128_CBC_SHA256           = 0x00AE,
    TLS_PSK_WITH_AES_256_CBC_SHA384           = 0x00AF,
    TLS_PSK_WITH_NULL_SHA256                  = 0x00B0,
    TLS_PSK_WITH_NULL_SHA384                  = 0x00B1,

    TLS_DHE_PSK_WITH_AES_128_CBC_SHA256       = 0x00B2,
    TLS_DHE_PSK_WITH_AES_256_CBC_SHA384       = 0x00B3,
    TLS_DHE_PSK_WITH_NULL_SHA256              = 0x00B4,
    TLS_DHE_PSK_WITH_NULL_SHA384              = 0x00B5,

    TLS_RSA_PSK_WITH_AES_128_CBC_SHA256       = 0x00B6,
    TLS_RSA_PSK_WITH_AES_256_CBC_SHA384       = 0x00B7,
    TLS_RSA_PSK_WITH_NULL_SHA256              = 0x00B8,
    TLS_RSA_PSK_WITH_NULL_SHA384              = 0x00B9,

    /* TLS 1.3 standard cipher suites for ChaCha20+Poly1305.
       Note: TLS 1.3 ciphersuites do not specify the key exchange
       algorithm -- they only specify the symmetric ciphers. */
    TLS_AES_128_GCM_SHA256                    = 0x1301,
    TLS_AES_256_GCM_SHA384                    = 0x1302,
    TLS_CHACHA20_POLY1305_SHA256              = 0x1303,
    TLS_AES_128_CCM_SHA256                    = 0x1304,
    TLS_AES_128_CCM_8_SHA256                  = 0x1305,

    /* Addenda from rfc 5289  Elliptic Curve Cipher Suites with
       HMAC SHA-256/384. */
    TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256   = 0xC023,
    TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384   = 0xC024,
    TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256    = 0xC025,
    TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384    = 0xC026,
    TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256     = 0xC027,
    TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384     = 0xC028,
    TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256      = 0xC029,
    TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384      = 0xC02A,

    /* Addenda from rfc 5289  Elliptic Curve Cipher Suites with
       SHA-256/384 and AES Galois Counter Mode (GCM) */
    TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256   = 0xC02B,
    TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384   = 0xC02C,
    TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256    = 0xC02D,
    TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384    = 0xC02E,
    TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256     = 0xC02F,
    TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384     = 0xC030,
    TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256      = 0xC031,
    TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384      = 0xC032,

    /* Addenda from rfc 7905  ChaCha20-Poly1305 Cipher Suites for
     Transport Layer Security (TLS). */
    TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256   = 0xCCA8,
    TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 = 0xCCA9,

    /* RFC 5746 - Secure Renegotiation */
    TLS_EMPTY_RENEGOTIATION_INFO_SCSV         = 0x00FF,

	/* Tags for SSL 2 cipher kinds which are not specified
	 * for SSL 3. */
    SSL_RSA_WITH_RC2_CBC_MD5 =                  0xFF80,
    SSL_RSA_WITH_IDEA_CBC_MD5 =                 0xFF81,
    SSL_RSA_WITH_DES_CBC_MD5 =                  0xFF82,
    SSL_RSA_WITH_3DES_EDE_CBC_MD5 =             0xFF83,
    SSL_NO_SUCH_CIPHERSUITE =                   0xFFFF
};

/*
 * Convenience ciphersuite groups that collate ciphersuites of comparable security
 * properties into a single alias.
 */
typedef CF_ENUM(int, SSLCiphersuiteGroup) {
    kSSLCiphersuiteGroupDefault,
    kSSLCiphersuiteGroupCompatibility,
    kSSLCiphersuiteGroupLegacy,
    kSSLCiphersuiteGroupATS,
    kSSLCiphersuiteGroupATSCompatibility,
};

#endif	/* !_SECURITY_CIPHERSUITE_H_ */
// ==========  Security.framework/Headers/SecRandom.h
/*
 * Copyright (c) 2007-2009,2011-2013,2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
     @header SecRandom
     The functions provided in SecRandom.h implement high-level accessors
     to cryptographically secure random numbers.
*/

#ifndef _SECURITY_SECRANDOM_H_
#define _SECURITY_SECRANDOM_H_

#include <Security/SecBase.h>
#include <stdint.h>
#include <sys/types.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecRandomRef
    @abstract Reference to a (pseudo) random number generator.
*/
typedef const struct __SecRandom * SecRandomRef;

/* This is a synonym for NULL, if you'd rather use a named constant.   This
   refers to a cryptographically secure random number generator.  */
extern const SecRandomRef kSecRandomDefault
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
     @function SecRandomCopyBytes

     @abstract
     Return count random bytes in *bytes, allocated by the caller. It
     is critical to check the return value for error.

     @param rnd
     Only @p kSecRandomDefault is supported.

     @param count
     The number of bytes to generate.

     @param bytes
     A buffer to fill with random output.

     @result Return 0 on success, any other value on failure.

     @discussion
     If @p rnd is unrecognized or unsupported, @p kSecRandomDefault is
     used.
*/
int SecRandomCopyBytes(SecRandomRef __nullable rnd, size_t count, void *bytes)
    __attribute__ ((warn_unused_result))
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECRANDOM_H_ */
// ==========  Security.framework/Headers/SecAccessControl.h
/*
 * Copyright (c) 2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 @header SecAccessControl
 SecAccessControl defines access rights for items.
 */

#ifndef _SECURITY_SECACCESSCONTROL_H_
#define _SECURITY_SECACCESSCONTROL_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFError.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
 @function SecAccessControlGetTypeID
 @abstract Returns the type identifier of SecAccessControl instances.
 @result The CFTypeID of SecAccessControl instances.
 */
CFTypeID SecAccessControlGetTypeID(void)
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/*!
 @typedef SecAccessControlCreateFlags
 
 @constant kSecAccessControlUserPresence
 User presence policy using biometry or Passcode. Biometry does not have to be available or enrolled. Item is still
 accessible by Touch ID even if fingers are added or removed. Item is still accessible by Face ID if user is re-enrolled.
 
 @constant kSecAccessControlBiometryAny
 Constraint: Touch ID (any finger) or Face ID. Touch ID or Face ID must be available. With Touch ID
 at least one finger must be enrolled. With Face ID user has to be enrolled. Item is still accessible by Touch ID even
 if fingers are added or removed. Item is still accessible by Face ID if user is re-enrolled.

 @constant kSecAccessControlTouchIDAny
 Deprecated, please use kSecAccessControlBiometryAny instead.
 
 @constant kSecAccessControlBiometryCurrentSet
 Constraint: Touch ID from the set of currently enrolled fingers. Touch ID must be available and at least one finger must
 be enrolled. When fingers are added or removed, the item is invalidated. When Face ID is re-enrolled this item is invalidated.

 @constant kSecAccessControlTouchIDCurrentSet
 Deprecated, please use kSecAccessControlBiometryCurrentSet instead.
 
 @constant kSecAccessControlDevicePasscode
 Constraint: Device passcode

 @constant kSecAccessControlWatch
 Constraint: Watch

 @constant kSecAccessControlOr
 Constraint logic operation: when using more than one constraint, at least one of them must be satisfied.
 
 @constant kSecAccessControlAnd
 Constraint logic operation: when using more than one constraint, all must be satisfied.
 
 @constant kSecAccessControlPrivateKeyUsage
 Create access control for private key operations (i.e. sign operation)
 
 @constant kSecAccessControlApplicationPassword
 Security: Application provided password for data encryption key generation. This is not a constraint but additional item
 encryption mechanism.
*/
typedef CF_OPTIONS(CFOptionFlags, SecAccessControlCreateFlags) {
    kSecAccessControlUserPresence           = 1u << 0,
    kSecAccessControlBiometryAny            API_AVAILABLE(macos(10.13.4), ios(11.3)) = 1u << 1,
    kSecAccessControlTouchIDAny             API_DEPRECATED_WITH_REPLACEMENT("kSecAccessControlBiometryAny", macos(10.12.1, 10.13.4), ios(9.0, 11.3)) = 1u << 1,
    kSecAccessControlBiometryCurrentSet     API_AVAILABLE(macos(10.13.4), ios(11.3)) = 1u << 3,
    kSecAccessControlTouchIDCurrentSet      API_DEPRECATED_WITH_REPLACEMENT("kSecAccessControlBiometryCurrentSet", macos(10.12.1, 10.13.4), ios(9.0, 11.3)) = 1u << 3,
    kSecAccessControlDevicePasscode         API_AVAILABLE(macos(10.11), ios(9.0)) = 1u << 4,
    kSecAccessControlWatch                  API_AVAILABLE(macos(10.15), ios(NA)) = 1u << 5,
    kSecAccessControlOr                     API_AVAILABLE(macos(10.12.1), ios(9.0)) = 1u << 14,
    kSecAccessControlAnd                    API_AVAILABLE(macos(10.12.1), ios(9.0)) = 1u << 15,
    kSecAccessControlPrivateKeyUsage        API_AVAILABLE(macos(10.12.1), ios(9.0)) = 1u << 30,
    kSecAccessControlApplicationPassword    API_AVAILABLE(macos(10.12.1), ios(9.0)) = 1u << 31,
} __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/*!
 @function SecAccessControlCreateWithFlags
 @abstract Creates new access control object based on protection type and additional flags.
 @discussion Created access control object should be used as a value for kSecAttrAccessControl attribute in SecItemAdd,
 SecItemUpdate or SecKeyGeneratePair functions.  Accessing keychain items or performing operations on keys which are
 protected by access control objects can block the execution because of UI which can appear to satisfy the access control
 conditions, therefore it is recommended to either move those potentially blocking operations out of the main
 application thread or use combination of kSecUseAuthenticationContext and kSecUseAuthenticationUI attributes to control
 where the UI interaction can appear.
 @param allocator Allocator to be used by this instance.
 @param protection Protection class to be used for the item. One of kSecAttrAccessible constants.
 @param flags If no flags are set then all operations are allowed.
 @param error Additional error information filled in case of failure.
 @result Newly created access control object.
 */
__nullable
SecAccessControlRef SecAccessControlCreateWithFlags(CFAllocatorRef __nullable allocator, CFTypeRef protection,
                                                    SecAccessControlCreateFlags flags, CFErrorRef *error)
API_AVAILABLE(macos(10.10), ios(8.0));

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif // _SECURITY_SECACCESSCONTROL_H_
// ==========  Security.framework/Headers/SecIdentity.h
/*
 * Copyright (c) 2002-2011,2012-2013,2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
     @header SecIdentity
    The functions provided in SecIdentity.h implement a convenient way to
    match private keys with certificates.
*/

#ifndef _SECURITY_SECIDENTITY_H_
#define _SECURITY_SECIDENTITY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>

#include <Security/SecBase.h>
#include <AvailabilityMacros.h>

#if SEC_OS_OSX
#include <Security/cssmtype.h>
#endif

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
     @function SecIdentityGetTypeID
     @abstract Returns the type identifier of SecIdentity instances.
     @result The CFTypeID of SecIdentity instances.
*/
CFTypeID SecIdentityGetTypeID(void)
     __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#if SEC_OS_OSX
/*!
    @function SecIdentityCreateWithCertificate
    @abstract Creates a new identity reference for the given certificate, assuming the associated private key is in one of the specified keychains.
    @param keychainOrArray A reference to an array of keychains to search, a single keychain, or NULL to search the user's default keychain search list.
    @param certificateRef A certificate reference.
    @param identityRef On return, an identity reference. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCreateWithCertificate(
               CFTypeRef __nullable keychainOrArray,
               SecCertificateRef certificateRef,
            SecIdentityRef * __nonnull CF_RETURNS_RETAINED identityRef)
     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
#endif

/*!
    @function SecIdentityCopyCertificate
    @abstract Returns a reference to a certificate for the given identity
    reference.
    @param identityRef An identity reference.
    @param certificateRef On return, a pointer to the found certificate
    reference. You are responsible for releasing this reference by calling
    the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyCertificate(
            SecIdentityRef identityRef,
            SecCertificateRef * __nonnull CF_RETURNS_RETAINED certificateRef)
     __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
     @function SecIdentityCopyPrivateKey
    @abstract Returns the private key associated with an identity.
    @param identityRef An identity reference.
    @param privateKeyRef On return, a pointer to the private key for the given
    identity. On iOS, the private key must be of class type kSecAppleKeyItemClass.
    You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyPrivateKey(
            SecIdentityRef identityRef,
            SecKeyRef * __nonnull CF_RETURNS_RETAINED privateKeyRef)
     __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#if SEC_OS_OSX
/*!
    @function SecIdentityCopyPreference
    @abstract Returns the preferred identity for the specified name and key usage, optionally limiting the result to an identity issued by a certificate whose subject is one of the distinguished names in validIssuers. If a preferred identity does not exist, NULL is returned.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies the service requiring an identity.
    @param keyUsage A CSSM_KEYUSE key usage value, as defined in cssmtype.h. Pass 0 to ignore this parameter.
    @param validIssuers (optional) An array of CFDataRef instances whose contents are the subject names of allowable issuers, as returned by a call to SSLCopyDistinguishedNames (SecureTransport.h). Pass NULL if any issuer is allowed.
    @param identity On return, a reference to the preferred identity, or NULL if none was found. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This API is deprecated in 10.7. Please use the SecIdentityCopyPreferred API instead.
*/
OSStatus SecIdentityCopyPreference(CFStringRef name, CSSM_KEYUSE keyUsage, CFArrayRef __nullable validIssuers, SecIdentityRef * __nonnull CF_RETURNS_RETAINED identity)
     DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecIdentityCopyPreferred
    @abstract Returns the preferred identity for the specified name and key usage, optionally limiting the result to an identity issued by a certificate whose subject is one of the distinguished names in validIssuers. If a preferred identity does not exist, NULL is returned.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies the service requiring an identity.
    @param keyUsage A CFArrayRef value, containing items defined in SecItem.h  Pass NULL to ignore this parameter. (kSecAttrCanEncrypt, kSecAttrCanDecrypt, kSecAttrCanDerive, kSecAttrCanSign, kSecAttrCanVerify, kSecAttrCanWrap, kSecAttrCanUnwrap)
    @param validIssuers (optional) An array of CFDataRef instances whose contents are the subject names of allowable issuers, as returned by a call to SSLCopyDistinguishedNames (SecureTransport.h). Pass NULL if any issuer is allowed.
    @result An identity or NULL, if the preferred identity has not been set. Your code should then typically perform a search for possible identities using the SecItem APIs.
    @discussion If a preferred identity has not been set for the supplied name, the returned identity reference will be NULL. Your code should then perform a search for possible identities, using the SecItemCopyMatching API.
*/
__nullable
SecIdentityRef SecIdentityCopyPreferred(CFStringRef name, CFArrayRef __nullable keyUsage, CFArrayRef __nullable validIssuers)
     __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function SecIdentitySetPreference
    @abstract Sets the preferred identity for the specified name and key usage.
    @param identity A reference to the identity which will be preferred.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies a service requiring this identity.
    @param keyUsage A CSSM_KEYUSE key usage value, as defined in cssmtype.h. Pass 0 to specify any key usage.
    @result A result code. See "Security Error Codes" (SecBase.h).
     @discussion This API is deprecated in 10.7. Please use the SecIdentitySetPreferred API instead.
*/
OSStatus SecIdentitySetPreference(SecIdentityRef identity, CFStringRef name, CSSM_KEYUSE keyUsage)
     DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecIdentitySetPreferred
    @abstract Sets the preferred identity for the specified name and key usage.
    @param identity A reference to the identity which will be preferred. If NULL is passed, any existing preference for the specified name is cleared instead.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies a service requiring this identity.
    @param keyUsage A CFArrayRef value, containing items defined in SecItem.h  Pass NULL to specify any key usage. (kSecAttrCanEncrypt, kSecAttrCanDecrypt, kSecAttrCanDerive, kSecAttrCanSign, kSecAttrCanVerify, kSecAttrCanWrap, kSecAttrCanUnwrap)
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentitySetPreferred(SecIdentityRef __nullable identity, CFStringRef name, CFArrayRef __nullable keyUsage)
     __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
     @function     SecIdentityCopySystemIdentity
     @abstract     Obtain the system-wide SecIdentityRef associated with
                   a specified domain.
     @param        domain  Identifies the SecIdentityRef to be obtained, typically
                           in the form "com.apple.subdomain...".
     @param        idRef     On return, the system SecIdentityRef assicated with
                             the specified domain. Caller must CFRelease this when
                             finished with it.
     @param        actualDomain (optional) The actual domain name of the
                                the returned identity is returned here. This
                                may be different from the requested domain.
    @result        A result code.  See "Security Error Codes" (SecBase.h).
     @discussion   If no system SecIdentityRef exists for the specified
                   domain, a domain-specific alternate may be returned
                   instead, typically (but not exclusively) the
                   kSecIdentityDomainDefault SecIdentityRef.
 */
OSStatus SecIdentityCopySystemIdentity(
   CFStringRef domain,
   SecIdentityRef * __nonnull CF_RETURNS_RETAINED idRef,
   CFStringRef * __nullable CF_RETURNS_RETAINED actualDomain) /* optional */
     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*!
     @function     SecIdentitySetSystemIdentity
     @abstract     Assign the supplied SecIdentityRef to the specified
                   domain.
     @param        domain Identifies the domain to which the specified
                   SecIdentityRef will be assigned.
     @param        idRef (optional) The identity to be assigned to the specified
                   domain. Pass NULL to delete a possible entry for the specified
                   domain; in this case, it is not an error if no identity
                   exists for the specified domain.
    @result        A result code.  See "Security Error Codes" (SecBase.h).
     @discussion   The caller must be running as root.
*/
OSStatus SecIdentitySetSystemIdentity(
   CFStringRef domain,
   SecIdentityRef __nullable idRef)
     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*
 * Defined system identity domains.
 */

/*!
     @const kSecIdentityDomainDefault The system-wide default identity.
 */
extern const CFStringRef kSecIdentityDomainDefault __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*!
     @const kSecIdentityDomainKerberosKDC Kerberos KDC identity.
*/
extern const CFStringRef kSecIdentityDomainKerberosKDC __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

#endif // SEC_OS_OSX

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECIDENTITY_H_ */
// ==========  Security.framework/Headers/SecProtocolMetadata.h
/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef SecProtocolMetadata_h
#define SecProtocolMetadata_h

#include <Security/SecProtocolObject.h>
#include <Security/SecProtocolTypes.h>
#include <Security/SecProtocolOptions.h>

#include <dispatch/dispatch.h>
#include <os/object.h>

/*!
 * The following diagram shows how clients interact with sec_protocol_options
 * and sec_protocol_metadata when configuring and using network security protocols.
 *
 *                    +--------+
 *                    | Client |
 *                    +-+---/ \+
 *                      |    |
 *        +-------------+    +-------------+
 *        | (1) set             (2) get    |
 *        | options             metadata   |
 * +-----\ /---------------+  +------------+----------+
 * | sec_protocol_options  |  | sec_protocol_metadata |
 * +-----------------------+  +-----------------------+
 *
 * Clients configure security protocols with `sec_protocol_options` instances.
 * And they inspect protocol instances using `sec_protocol_metadata` instances.
 */

#ifndef SEC_OBJECT_IMPL
/*!
 * A `sec_protocol_metadata` instance conatins read-only properties of a connected and configured
 * security protocol. Clients use this object to read information about a protocol instance. Properties
 * include, for example, the negotiated TLS version, ciphersuite, and peer certificates.
 */
SEC_OBJECT_DECL(sec_protocol_metadata);
#endif // !SEC_OBJECT_IMPL

__BEGIN_DECLS

SEC_ASSUME_NONNULL_BEGIN

/*!
 * @function sec_protocol_metadata_get_negotiated_protocol
 *
 * @abstract
 *      Get the application protocol negotiated, e.g., via the TLS ALPN extension.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A NULL-terminated string carrying the negotiated protocol.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char * _Nullable
sec_protocol_metadata_get_negotiated_protocol(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_copy_peer_public_key
 *
 * @abstract
 *      Get the protocol instance peer's public key.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A `dispatch_data_t` containing the peer's raw public key.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable dispatch_data_t
sec_protocol_metadata_copy_peer_public_key(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_get_negotiated_tls_protocol_version
 *
 * @abstract
 *      Get the negotiated TLS version.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A `tls_protocol_version_t` value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
tls_protocol_version_t
sec_protocol_metadata_get_negotiated_tls_protocol_version(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_get_negotiated_protocol_version
 *
 * @abstract
 *      Get the negotiated TLS version.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A SSLProtocol enum of the TLS version.
 */
API_DEPRECATED_WITH_REPLACEMENT("sec_protocol_metadata_get_negotiated_tls_protocol_version",
                                macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
SSLProtocol
sec_protocol_metadata_get_negotiated_protocol_version(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_get_negotiated_tls_ciphersuite
 *
 * @abstract
 *      Get the negotiated TLS ciphersuite.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A `tls_ciphersuite_t`.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
tls_ciphersuite_t
sec_protocol_metadata_get_negotiated_tls_ciphersuite(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_get_negotiated_ciphersuite
 *
 * @abstract
 *      Get the negotiated TLS ciphersuite.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A SSLCipherSuite.
 */
API_DEPRECATED_WITH_REPLACEMENT("sec_protocol_metadata_get_negotiated_tls_ciphersuite",
                                macos(10.14, 10.15), ios(12.0, 13.0), watchos(5.0, 6.0), tvos(12.0, 13.0))
API_UNAVAILABLE(uikitformac)
SSLCipherSuite
sec_protocol_metadata_get_negotiated_ciphersuite(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_get_early_data_accepted
 *
 * @abstract
 *      Determine if early data was accepted by the peer.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return A bool indicating if early data was accepted.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_get_early_data_accepted(sec_protocol_metadata_t metadata);

#ifdef __BLOCKS__
/*!
 * @function sec_protocol_metadata_access_peer_certificate_chain
 *
 * @abstract
 *      Get the certificate chain of the protocol instance peer.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param handler
 *      A block to invoke one or more times with sec_certificate_t objects
 *
 * @return Returns true if the peer certificates were accessible, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_access_peer_certificate_chain(sec_protocol_metadata_t metadata,
                                                    void (^handler)(sec_certificate_t certificate));

/*!
 * @function sec_protocol_metadata_copy_ocsp_response
 *
 * @abstract
 *      Get the OCSP response from the protocol instance peer.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param handler
 *      A block to invoke one or more times with OCSP data
 *
 * @return Returns true if the OSCP response was accessible, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_access_ocsp_response(sec_protocol_metadata_t metadata,
                                           void (^handler)(dispatch_data_t ocsp_data));

/*!
 * @function sec_protocol_metadata_access_supported_signature_algorithms
 *
 * @abstract
 *      Get the signature algorithms supported by the peer. Clients may call this
 *      in response to a challenge block.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param handler
 *      A block to invoke one or more times with OCSP data
 *
 * @return Returns true if the supported signature list was accessible, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_access_supported_signature_algorithms(sec_protocol_metadata_t metadata,
                                                            void (^handler)(uint16_t signature_algorithm));

/*!
 * @function sec_protocol_metadata_access_distinguished_names
 *
 * @abstract
 *      Get the X.509 Distinguished Names from the protocol instance peer.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param handler
 *      A block to invoke one or more times with distinguished_name data
 *
 * @return Returns true if the distinguished names were accessible, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_access_distinguished_names(sec_protocol_metadata_t metadata,
                                                 void (^handler)(dispatch_data_t distinguished_name));
#endif // __BLOCKS__

/*!
 * @function sec_protocol_metadata_get_server_name
 *
 * @abstract
 *      Obtain the server name offered by a client or server during
 *      connection establishmet. This is the value commonly carried
 *      in the TLS SNI extesion.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return Returns A NULL-terminated string carrying the server name, or NULL
 *      if none was provided.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char * _Nullable
sec_protocol_metadata_get_server_name(sec_protocol_metadata_t metadata);

/*!
 * @function sec_protocol_metadata_peers_are_equal
 *
 * @abstract
 *      Compare peer information for two `sec_protocol_metadata` instances.
 *      This comparison does not include protocol configuration options, e.g., ciphersuites.
 *
 * @param metadataA
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param metadataB
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return Returns true if both metadata values refer to the same peer, and false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_peers_are_equal(sec_protocol_metadata_t metadataA, sec_protocol_metadata_t metadataB);

/*!
 * @function sec_protocol_metadata_challenge_parameters_are_equal
 *
 * @abstract
 *      Compare challenge-relevant information for two `sec_protocol_metadata` instances.
 *
 *      This comparison includes all information relevant to a challenge request, including:
 *      distinguished names, signature algorithms, and supported certificate types.
 *      See Section 7.4.4 of RFC5246 for more details.
 *
 * @param metadataA
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param metadataB
 *      A `sec_protocol_metadata_t` instance.
 *
 * @return Returns true if both metadata values have the same challenge parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
sec_protocol_metadata_challenge_parameters_are_equal(sec_protocol_metadata_t metadataA, sec_protocol_metadata_t metadataB);

/*!
 * @function sec_protocol_metadata_create_secret
 *
 * @abstract
 *      Export a secret, e.g., a cryptographic key, derived from the protocol metadata using a label string.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param label_len
 *      Length of the KDF label string.
 *
 * @param label
 *      KDF label string.
 *
 * @param exporter_length
 *      Length of the secret to be exported.
 *
 * @return Returns a dispatch_data_t object carrying the exported secret.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable dispatch_data_t
sec_protocol_metadata_create_secret(sec_protocol_metadata_t metadata, size_t label_len,
                                    const char *label, size_t exporter_length);

/*!
 * @function sec_protocol_metadata_create_secret_with_context
 *
 * @abstract
 *      Export a secret, e.g., a cryptographic key, derived from the protocol metadata using a label and context string.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param label_len
 *      Length of the KDF label string.
 *
 * @param label
 *      KDF label string.
 *
 * @param context_len
 *      Length of the KDF context string.
 *
 * @param context
 *      Constant opaque context value
 *
 * @param exporter_length
 *      Length of the secret to be exported.
 *
 * @return Returns a dispatch_data_t object carrying the exported secret.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable dispatch_data_t
sec_protocol_metadata_create_secret_with_context(sec_protocol_metadata_t metadata, size_t label_len,
                                                 const char *label, size_t context_len,
                                                 const uint8_t *context, size_t exporter_length);

SEC_ASSUME_NONNULL_END

__END_DECLS

#endif // SecProtocolMetadata_h
