// ==========  Security.framework/Headers/SecureTransport.h
/*
 * Copyright (c) 1999-2002,2005-2014 Apple Inc. All Rights Reserved.
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
#include <Security/CipherSuite.h>
#include <Security/SecTrust.h>
#include <sys/types.h>
#include <Availability.h>

#ifdef __cplusplus
extern "C" {
#endif

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/***********************
 *** Common typedefs ***
 ***********************/

/* Opaque reference to an SSL session context */
struct                      SSLContext;
typedef struct CF_BRIDGED_TYPE(id) SSLContext *SSLContextRef;

/* Opaque reference to an I/O connection (socket, endpoint, etc.) */
typedef const void *		SSLConnectionRef;

/* SSL Protocol version */
typedef CF_ENUM(int, SSLProtocol) {
	kSSLProtocolUnknown = 0,                /* no protocol negotiated/specified; use default */
	kSSLProtocol3       = 2,				/* SSL 3.0 */
	kTLSProtocol1       = 4,				/* TLS 1.0 */
    kTLSProtocol11      = 7,				/* TLS 1.1 */
    kTLSProtocol12      = 8,				/* TLS 1.2 */
    kDTLSProtocol1      = 9,                /* DTLS 1.0 */

    /* DEPRECATED on iOS */
    kSSLProtocol2       = 1,				/* SSL 2.0 */
    kSSLProtocol3Only   = 3,                /* SSL 3.0 Only */
    kTLSProtocol1Only   = 5,                /* TLS 1.0 Only */
    kSSLProtocolAll     = 6,                /* All TLS supported protocols */

};

/* SSL session options */
typedef CF_ENUM(int, SSLSessionOption) {
	/*
	 * Set this option to enable returning from SSLHandshake (with a result of
	 * errSSLServerAuthCompleted) when the server authentication portion of the
	 * handshake is complete. This disable certificate verification and
	 * provides an opportunity to perform application-specific server
	 * verification before deciding to continue.
	 */
	kSSLSessionOptionBreakOnServerAuth = 0,
	/*
	 * Set this option to enable returning from SSLHandshake (with a result of
	 * errSSLClientCertRequested) when the server requests a client certificate.
	 */
	kSSLSessionOptionBreakOnCertRequested = 1,
    /*
     * This option is the same as kSSLSessionOptionBreakOnServerAuth but applies
     * to the case where SecureTransport is the server and the client has presented
     * its certificates allowing the server to verify whether these should be
     * allowed to authenticate.
     */
    kSSLSessionOptionBreakOnClientAuth = 2,
    /*
     * Enable/Disable TLS False Start
     * When enabled, False Start will only be performed if a adequate cipher-suite is
     * negotiated.
     */
    kSSLSessionOptionFalseStart = 3,
    /*
     * Enable/Disable 1/n-1 record splitting for BEAST attack mitigation.
     * When enabled, record splitting will only be performed for TLS 1.0 connections
     * using a block cipher.
     */
    kSSLSessionOptionSendOneByteRecord = 4,
    /*
     * Allow/Disallow server identity change on renegotiation. Disallow by default
     * to avoid Triple Handshake attack.
     */
    kSSLSessionOptionAllowServerIdentityChange = 5,
    /*
     * Enable fallback countermeasures. Use this option when retyring a SSL connection
     * with a lower protocol version because of failure to connect.
     */
    kSSLSessionOptionFallback = 6,
    /*
     * Set this option to break from a client hello in order to check for SNI
     */
    kSSLSessionOptionBreakOnClientHello = 7,

};

/* State of an SSLSession */
typedef CF_ENUM(int, SSLSessionState) {
	kSSLIdle,					/* no I/O performed yet */
	kSSLHandshake,				/* SSL handshake in progress */
	kSSLConnected,				/* Handshake complete, ready for normal I/O */
	kSSLClosed,					/* connection closed normally */
	kSSLAborted					/* connection aborted */
};

/*
 * Status of client certificate exchange (which is optional
 * for both server and client).
 */
typedef CF_ENUM(int, SSLClientCertificateState) {
	/* Server hasn't asked for a cert. Client hasn't sent one. */
	kSSLClientCertNone,
	/* Server has asked for a cert, but client didn't send it. */
	kSSLClientCertRequested,
	/*
	 * Server side: We asked for a cert, client sent one, we validated
	 *				it OK. App can inspect the cert via
	 *				SSLGetPeerCertificates().
	 * Client side: server asked for one, we sent it.
	 */
	kSSLClientCertSent,
	/*
	 * Client sent a cert but failed validation. Server side only.
	 * Server app can inspect the cert via SSLGetPeerCertificates().
	 */
	kSSLClientCertRejected
} ;

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

/*************************************************
 *** OSStatus values unique to SecureTransport ***
 *************************************************/

/*
    Note: the comments that appear after these errors are used to create SecErrorMessages.strings.
    The comments must not be multi-line, and should be in a form meaningful to an end user. If
    a different or additional comment is needed, it can be put in the header doc format, or on a
    line that does not start with errZZZ.
*/

CF_ENUM(OSStatus) {
	errSSLProtocol				= -9800,	/* SSL protocol error */
	errSSLNegotiation			= -9801,	/* Cipher Suite negotiation failure */
	errSSLFatalAlert			= -9802,	/* Fatal alert */
	errSSLWouldBlock			= -9803,	/* I/O would block (not fatal) */
    errSSLSessionNotFound 		= -9804,	/* attempt to restore an unknown session */
    errSSLClosedGraceful 		= -9805,	/* connection closed gracefully */
    errSSLClosedAbort 			= -9806,	/* connection closed via error */
    errSSLXCertChainInvalid 	= -9807,	/* invalid certificate chain */
    errSSLBadCert				= -9808,	/* bad certificate format */
	errSSLCrypto				= -9809,	/* underlying cryptographic error */
	errSSLInternal				= -9810,	/* Internal error */
	errSSLModuleAttach			= -9811,	/* module attach failure */
    errSSLUnknownRootCert		= -9812,	/* valid cert chain, untrusted root */
    errSSLNoRootCert			= -9813,	/* cert chain not verified by root */
	errSSLCertExpired			= -9814,	/* chain had an expired cert */
	errSSLCertNotYetValid		= -9815,	/* chain had a cert not yet valid */
	errSSLClosedNoNotify		= -9816,	/* server closed session with no notification */
	errSSLBufferOverflow		= -9817,	/* insufficient buffer provided */
	errSSLBadCipherSuite		= -9818,	/* bad SSLCipherSuite */

	/* fatal errors detected by peer */
	errSSLPeerUnexpectedMsg		= -9819,	/* unexpected message received */
	errSSLPeerBadRecordMac		= -9820,	/* bad MAC */
	errSSLPeerDecryptionFail	= -9821,	/* decryption failed */
	errSSLPeerRecordOverflow	= -9822,	/* record overflow */
	errSSLPeerDecompressFail	= -9823,	/* decompression failure */
	errSSLPeerHandshakeFail		= -9824,	/* handshake failure */
	errSSLPeerBadCert			= -9825,	/* misc. bad certificate */
	errSSLPeerUnsupportedCert	= -9826,	/* bad unsupported cert format */
	errSSLPeerCertRevoked		= -9827,	/* certificate revoked */
	errSSLPeerCertExpired		= -9828,	/* certificate expired */
	errSSLPeerCertUnknown		= -9829,	/* unknown certificate */
	errSSLIllegalParam			= -9830,	/* illegal parameter */
	errSSLPeerUnknownCA 		= -9831,	/* unknown Cert Authority */
	errSSLPeerAccessDenied		= -9832,	/* access denied */
	errSSLPeerDecodeError		= -9833,	/* decoding error */
	errSSLPeerDecryptError		= -9834,	/* decryption error */
	errSSLPeerExportRestriction	= -9835,	/* export restriction */
	errSSLPeerProtocolVersion	= -9836,	/* bad protocol version */
	errSSLPeerInsufficientSecurity = -9837,	/* insufficient security */
	errSSLPeerInternalError		= -9838,	/* internal error */
	errSSLPeerUserCancelled		= -9839,	/* user canceled */
	errSSLPeerNoRenegotiation	= -9840,	/* no renegotiation allowed */

	/* non-fatal result codes */
	errSSLPeerAuthCompleted     = -9841,    /* peer cert is valid, or was ignored if verification disabled */
	errSSLClientCertRequested	= -9842,	/* server has requested a client cert */

	/* more errors detected by us */
	errSSLHostNameMismatch		= -9843,	/* peer host name mismatch */
	errSSLConnectionRefused		= -9844,	/* peer dropped connection before responding */
	errSSLDecryptionFail		= -9845,	/* decryption failure */
	errSSLBadRecordMac			= -9846,	/* bad MAC */
	errSSLRecordOverflow		= -9847,	/* record overflow */
	errSSLBadConfiguration		= -9848,	/* configuration error */
	errSSLUnexpectedRecord      = -9849,	/* unexpected (skipped) record in DTLS */
    errSSLWeakPeerEphemeralDHKey = -9850,	/* weak ephemeral dh key  */

    /* non-fatal result codes */
    errSSLClientHelloReceived   = -9851,    /* SNI */
};

/* DEPRECATED aliases for errSSLPeerAuthCompleted */
#define errSSLServerAuthCompleted	errSSLPeerAuthCompleted
#define errSSLClientAuthCompleted	errSSLPeerAuthCompleted

/* DEPRECATED alias for the end of the error range */
#define errSSLLast errSSLUnexpectedRecord

typedef CF_ENUM(int, SSLProtocolSide)
{
    kSSLServerSide,
    kSSLClientSide
};

typedef CF_ENUM(int, SSLConnectionType)
{
    kSSLStreamType,
    kSSLDatagramType
};

typedef CF_ENUM(int, SSLSessionStrengthPolicy)
{
    kSSLSessionStrengthPolicyDefault,
    kSSLSessionStrengthPolicyATSv1
};

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
 * Return the CFTypeID for SSLContext objects.
 */
CFTypeID
SSLContextGetTypeID(void)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Create a new instance of an SSLContextRef using the specified allocator.
 */
__nullable
SSLContextRef
SSLCreateContext(CFAllocatorRef __nullable alloc, SSLProtocolSide protocolSide, SSLConnectionType connectionType)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/*
 * Create a new session context.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. Your code should use SSLCreateContext instead.
 */
OSStatus
SSLNewContext				(Boolean 			isServer,
							 SSLContextRef 		* __nonnull CF_RETURNS_RETAINED contextPtr)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Dispose of a session context.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. Your code should use CFRelease to dispose a session
 * created with SSLCreateContext.
 */
OSStatus
SSLDisposeContext			(SSLContextRef		context)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

#endif /* MAC OS X */

/*
 * Determine the state of an SSL/DTLS session.
 */
OSStatus
SSLGetSessionState			(SSLContextRef		context,
							 SSLSessionState	*state)		/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Set options for an SSL session. Must be called prior to SSLHandshake();
 * subsequently cannot be called while session is active.
 */
OSStatus
SSLSetSessionOption			(SSLContextRef		context,
							 SSLSessionOption	option,
							 Boolean			value)
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_5_0);

/*
 * Determine current value for the specified option in a given SSL session.
 */
OSStatus
SSLGetSessionOption			(SSLContextRef		context,
							 SSLSessionOption	option,
							 Boolean			*value)
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_5_0);

/********************************************************************
 *** Session context configuration, common to client and servers. ***
 ********************************************************************/

/*
 * Specify functions which do the network I/O. Must be called prior
 * to SSLHandshake(); subsequently cannot be called while a session is
 * active.
 */
OSStatus
SSLSetIOFuncs				(SSLContextRef		context,
							 SSLReadFunc 		readFunc,
							 SSLWriteFunc		writeFunc)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Set the minimum SSL protocol version allowed. Optional.
 * The default is the lower supported protocol.
 *
 * This can only be called when no session is active.
 *
 * For TLS contexts, legal values for minVersion are :
 *		kSSLProtocol3
 * 		kTLSProtocol1
 * 		kTLSProtocol11
 * 		kTLSProtocol12
 *
 * For DTLS contexts, legal values for minVersion are :
 *      kDTLSProtocol1
 */
OSStatus
SSLSetProtocolVersionMin  (SSLContextRef      context,
                           SSLProtocol        minVersion)
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Get minimum protocol version allowed
 */
OSStatus
SSLGetProtocolVersionMin  (SSLContextRef      context,
                           SSLProtocol        *minVersion)
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Set the maximum SSL protocol version allowed. Optional.
 * The default is the highest supported protocol.
 *
 * This can only be called when no session is active.
 *
 * For TLS contexts, legal values for minVersion are :
 *		kSSLProtocol3
 * 		kTLSProtocol1
 * 		kTLSProtocol11
 * 		kTLSProtocol12
 *
 * For DTLS contexts, legal values for minVersion are :
 *      kDTLSProtocol1
 */
OSStatus
SSLSetProtocolVersionMax  (SSLContextRef      context,
                           SSLProtocol        maxVersion)
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Get maximum protocol version allowed
 */
OSStatus
SSLGetProtocolVersionMax  (SSLContextRef      context,
                           SSLProtocol        *maxVersion)
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/*
 * Set allowed SSL protocol versions. Optional.
 * Specifying kSSLProtocolAll for SSLSetProtocolVersionEnabled results in
 * specified 'enable' boolean to be applied to all supported protocols.
 * The default is "all supported protocols are enabled".
 * This can only be called when no session is active.
 *
 * Legal values for protocol are :
 *		kSSLProtocol2
 *		kSSLProtocol3
 * 		kTLSProtocol1
 *		kSSLProtocolAll
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. You can use SSLSetProtocolVersionMin and/or
 * SSLSetProtocolVersionMax to specify which protocols are enabled.
 */
OSStatus
SSLSetProtocolVersionEnabled (SSLContextRef 	context,
							 SSLProtocol		protocol,
							 Boolean			enable)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

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
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Get/set SSL protocol version; optional. Default is kSSLProtocolUnknown,
 * in which case the highest possible version is attempted, but a lower
 * version is accepted if the peer requires it.
 * SSLSetProtocolVersion cannot be called when a session is active.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and deprecated on Mac OS X 10.8.
 * Use SSLSetProtocolVersionMin and/or SSLSetProtocolVersionMax to specify
 * which protocols are enabled.
 */
OSStatus
SSLSetProtocolVersion		(SSLContextRef 		context,
							 SSLProtocol		version)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);

/*
 * Obtain the protocol version specified in SSLSetProtocolVersion.
 * If SSLSetProtocolVersionEnabled() has been called for this session,
 * SSLGetProtocolVersion() may return errSecParam if the protocol enable
 * state can not be represented by the SSLProtocol enums (e.g.,
 * SSL2 and TLS1 enabled, SSL3 disabled).
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and deprecated on Mac OS X 10.8.
 * Use SSLGetProtocolVersionMin and/or SSLGetProtocolVersionMax to check
 * whether a protocol is enabled.
 */
OSStatus
SSLGetProtocolVersion		(SSLContextRef		context,
							 SSLProtocol		*protocol)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);

#endif /* MAC OS X */

/*
 * Specify this connection's certificate(s). This is mandatory for
 * server connections, optional for clients. Specifying a certificate
 * for a client enables SSL client-side authentication. The end-entity
 * cert is in certRefs[0]. Specifying a root cert is optional; if it's
 * not specified, the root cert which verifies the cert chain specified
 * here must be present in the system-wide set of trusted anchor certs.
 *
 * The certRefs argument is a CFArray containing SecCertificateRefs,
 * except for certRefs[0], which is a SecIdentityRef.
 *
 * Must be called prior to SSLHandshake(), or immediately after
 * SSLHandshake has returned errSSLClientCertRequested (i.e. before the
 * handshake is resumed by calling SSLHandshake again.)
 *
 * SecureTransport assumes the following:
 *
 *  -- The certRef references remain valid for the lifetime of the session.
 *  -- The certificate specified in certRefs[0] is capable of signing.
 *  -- The required capabilities of the certRef[0], and of the optional cert
 *     specified in SSLSetEncryptionCertificate (see below), are highly
 *     dependent on the application. For example, to work as a server with
 *     Netscape clients, the cert specified here must be capable of both
 *     signing and encrypting.
 */
OSStatus
SSLSetCertificate			(SSLContextRef		context,
							 CFArrayRef			certRefs)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Specify I/O connection - a socket, endpoint, etc., which is
 * managed by caller. On the client side, it's assumed that communication
 * has been established with the desired server on this connection.
 * On the server side, it's assumed that an incoming client request
 * has been established.
 *
 * Must be called prior to SSLHandshake(); subsequently can only be
 * called when no session is active.
 */
OSStatus
SSLSetConnection			(SSLContextRef                  context,
							 SSLConnectionRef __nullable	connection)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

OSStatus
SSLGetConnection			(SSLContextRef		context,
							 SSLConnectionRef	* __nonnull CF_RETURNS_NOT_RETAINED connection)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Specify the fully qualified doman name of the peer, e.g., "store.apple.com."
 * Optional; used to verify the common name field in peer's certificate.
 * Name is in the form of a C string; NULL termination optional, i.e.,
 * peerName[peerNameLen+1] may or may not have a NULL. In any case peerNameLen
 * is the number of bytes of the peer domain name.
 */
OSStatus
SSLSetPeerDomainName		(SSLContextRef		context,
							 const char			* __nullable peerName,
							 size_t				peerNameLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Determine the buffer size needed for SSLGetPeerDomainName().
 */
OSStatus
SSLGetPeerDomainNameLength	(SSLContextRef		context,
							 size_t				*peerNameLen)	// RETURNED
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Obtain the value specified in SSLSetPeerDomainName().
 */
OSStatus
SSLGetPeerDomainName		(SSLContextRef		context,
							 char				*peerName,		// returned here
							 size_t				*peerNameLen)	// IN/OUT
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Specify the Datagram TLS Hello Cookie.
 * This is to be called for server side only and is optional.
 * The default is a zero len cookie. The maximum cookieLen is 32 bytes.
 */
OSStatus
SSLSetDatagramHelloCookie	(SSLContextRef		dtlsContext,
                             const void         * __nullable cookie,
                             size_t             cookieLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Specify the maximum record size, including all DTLS record headers.
 * This should be set appropriately to avoid fragmentation
 * of Datagrams during handshake, as fragmented datagrams may
 * be dropped by some network.
 * This is for Datagram TLS only
 */
OSStatus
SSLSetMaxDatagramRecordSize (SSLContextRef		dtlsContext,
                             size_t             maxSize)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Get the maximum record size, including all Datagram TLS record headers.
 * This is for Datagram TLS only
 */
OSStatus
SSLGetMaxDatagramRecordSize (SSLContextRef		dtlsContext,
                             size_t             *maxSize)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Obtain the actual negotiated protocol version of the active
 * session, which may be different that the value specified in
 * SSLSetProtocolVersion(). Returns kSSLProtocolUnknown if no
 * SSL session is in progress.
 */
OSStatus
SSLGetNegotiatedProtocolVersion		(SSLContextRef		context,
									 SSLProtocol		*protocol)	/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Determine number and values of all of the SSLCipherSuites we support.
 * Caller allocates output buffer for SSLGetSupportedCiphers() and passes in
 * its size in *numCiphers. If supplied buffer is too small, errSSLBufferOverflow
 * will be returned.
 */
OSStatus
SSLGetNumberSupportedCiphers (SSLContextRef			context,
							  size_t				*numCiphers)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

OSStatus
SSLGetSupportedCiphers		 (SSLContextRef			context,
							  SSLCipherSuite		*ciphers,		/* RETURNED */
							  size_t				*numCiphers)	/* IN/OUT */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Specify a (typically) restricted set of SSLCipherSuites to be enabled by
 * the current SSLContext. Can only be called when no session is active. Default
 * set of enabled SSLCipherSuites is the same as the complete set of supported
 * SSLCipherSuites as obtained by SSLGetSupportedCiphers().
 */
OSStatus
SSLSetEnabledCiphers		(SSLContextRef			context,
							 const SSLCipherSuite	*ciphers,
							 size_t					numCiphers)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Determine number and values of all of the SSLCipherSuites currently enabled.
 * Caller allocates output buffer for SSLGetEnabledCiphers() and passes in
 * its size in *numCiphers. If supplied buffer is too small, errSSLBufferOverflow
 * will be returned.
 */
OSStatus
SSLGetNumberEnabledCiphers 	(SSLContextRef			context,
							 size_t					*numCiphers)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

OSStatus
SSLGetEnabledCiphers		(SSLContextRef			context,
							 SSLCipherSuite			*ciphers,		/* RETURNED */
							 size_t					*numCiphers)	/* IN/OUT */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/*
 * Enable/disable peer certificate chain validation. Default is enabled.
 * If caller disables, it is the caller's responsibility to call
 * SSLCopyPeerCertificates() upon successful completion of the handshake
 * and then to perform external validation of the peer certificate
 * chain before proceeding with data transfer.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To disable peer certificate chain validation, you
 * can instead use SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth
 * to true. This will disable verification and cause SSLHandshake to return with
 * an errSSLServerAuthCompleted result when the peer certificates have been
 * received; at that time, you can choose to evaluate peer trust yourself, or
 * simply call SSLHandshake again to proceed with the handshake.
 */
OSStatus
SSLSetEnableCertVerify		(SSLContextRef 			context,
							 Boolean				enableVerify)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Check whether peer certificate chain validation is enabled.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To check whether peer certificate chain validation
 * is enabled in a context, call SSLGetSessionOption to obtain the value of
 * the kSSLSessionOptionBreakOnServerAuth session option flag. If the value
 * of this option flag is true, then verification is disabled.
 */
OSStatus
SSLGetEnableCertVerify		(SSLContextRef 			context,
							 Boolean				*enableVerify)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Specify the option of ignoring certificates' "expired" times.
 * This is a common failure in the real SSL world. Default setting for this
 * flag is false, meaning expired certs result in an errSSLCertExpired error.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To ignore expired certificate errors, first disable
 * Secure Transport's automatic verification of peer certificates by calling
 * SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 * SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 * your code should obtain the SecTrustRef for the peer's certificates and
 * perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 * The SecTrustSetOptions function allows you to specify that the expiration
 * status of certificates should be ignored for this evaluation.
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
 *
 */
OSStatus
SSLSetAllowsExpiredCerts	(SSLContextRef		context,
							 Boolean			allowsExpired)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Obtain the current value of an SSLContext's "allowExpiredCerts" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X.
 */
OSStatus
SSLGetAllowsExpiredCerts	(SSLContextRef		context,
							 Boolean			*allowsExpired)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Similar to SSLSetAllowsExpiredCerts, SSLSetAllowsExpiredRoots allows the
 * option of ignoring "expired" status for root certificates only.
 * Default setting is false, i.e., expired root certs result in an
 * errSSLCertExpired error.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To ignore expired certificate errors, first disable
 * Secure Transport's automatic verification of peer certificates by calling
 * SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 * SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 * your code should obtain the SecTrustRef for the peer's certificates and
 * perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 * The SecTrustSetOptions function allows you to specify that the expiration
 * status of certificates should be ignored for this evaluation.
 *
 * See the description of the SSLSetAllowsExpiredCerts function (above)
 * for a code example. The kSecTrustOptionAllowExpiredRoot option can be used
 * instead of kSecTrustOptionAllowExpired to allow expired roots only.
 */
OSStatus
SSLSetAllowsExpiredRoots	(SSLContextRef		context,
							 Boolean			allowsExpired)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Obtain the current value of an SSLContext's "allow expired roots" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X.
 */
OSStatus
SSLGetAllowsExpiredRoots	(SSLContextRef		context,
							 Boolean			*allowsExpired)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Specify option of allowing for an unknown root cert, i.e., one which
 * this software can not verify as one of a list of known good root certs.
 * Default for this flag is false, in which case one of the following two
 * errors may occur:
 *    -- The peer returns a cert chain with a root cert, and the chain
 *       verifies to that root, but the root is not one of our trusted
 *       roots. This results in errSSLUnknownRootCert on handshake.
 *    -- The peer returns a cert chain which does not contain a root cert,
 *       and we can't verify the chain to one of our trusted roots. This
 *       results in errSSLNoRootCert on handshake.
 *
 * Both of these error conditions are ignored when the AllowAnyRoot flag is
 * true, allowing connection to a totally untrusted peer.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To ignore unknown root cert errors, first disable
 * Secure Transport's automatic verification of peer certificates by calling
 * SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 * SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 * your code should obtain the SecTrustRef for the peer's certificates and
 * perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *
 * See the description of the SSLSetAllowsExpiredCerts function (above)
 * for a code example. Note that an unknown root certificate will cause
 * SecTrustEvaluate to report kSecTrustResultRecoverableTrustFailure as the
 * trust result.
 */
OSStatus
SSLSetAllowsAnyRoot			(SSLContextRef		context,
							 Boolean			anyRoot)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Obtain the current value of an SSLContext's "allow any root" flag.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X.
 */
OSStatus
SSLGetAllowsAnyRoot			(SSLContextRef		context,
							 Boolean			*anyRoot) /* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Augment or replace the system's default trusted root certificate set
 * for this session. If replaceExisting is true, the specified roots will
 * be the only roots which are trusted during this session. If replaceExisting
 * is false, the specified roots will be added to the current set of trusted
 * root certs. If this function has never been called, the current trusted
 * root set is the same as the system's default trusted root set.
 * Successive calls with replaceExisting false result in accumulation
 * of additional root certs.
 *
 * The trustedRoots array contains SecCertificateRefs.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To trust specific roots in a session, first disable
 * Secure Transport's automatic verification of peer certificates by calling
 * SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true. When
 * SSLHandshake subsequently returns an errSSLServerAuthCompleted result,
 * your code should obtain the SecTrustRef for the peer's certificates and
 * perform a custom trust evaluation with SecTrust APIs (see SecTrust.h).
 *
 * See the description of the SSLSetAllowsExpiredCerts function (above)
 * for a code example. You can call SecTrustSetAnchorCertificates to
 * augment the system's trusted root set, or SecTrustSetAnchorCertificatesOnly
 * to make these the only trusted roots, prior to calling SecTrustEvaluate.
 */
OSStatus
SSLSetTrustedRoots			(SSLContextRef 		context,
							 CFArrayRef 		trustedRoots,
							 Boolean 			replaceExisting)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Obtain an array of SecCertificateRefs representing the current
 * set of trusted roots. If SSLSetTrustedRoots() has never been called
 * for this session, this returns the system's default root set.
 *
 * Caller must CFRelease the returned CFArray.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To get the current set of trusted roots, call the
 * SSLCopyPeerTrust function to obtain the SecTrustRef for the peer certificate
 * chain, then SecTrustCopyCustomAnchorCertificates (see SecTrust.h).
 */
OSStatus
SSLCopyTrustedRoots			(SSLContextRef 		context,
							 CFArrayRef 		* __nonnull CF_RETURNS_RETAINED trustedRoots)	/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

/*
 * Request peer certificates. Valid anytime, subsequent to a handshake attempt.
 *
 * The certs argument is a CFArray containing SecCertificateRefs.
 * Caller must CFRelease the returned array.
 *
 * The cert at index 0 of the returned array is the subject (end
 * entity) cert; the root cert (or the closest cert to it) is at
 * the end of the returned array.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. To get peer certificates, call SSLCopyPeerTrust
 * to obtain the SecTrustRef for the peer certificate chain, then use the
 * SecTrustGetCertificateCount and SecTrustGetCertificateAtIndex functions
 * to retrieve individual certificates in the chain (see SecTrust.h).
 */
OSStatus
SSLCopyPeerCertificates		(SSLContextRef 		context,
							 CFArrayRef			* __nonnull CF_RETURNS_RETAINED certs)		/* RETURNED */
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

#endif /* MAC OS X */

/*
 * Obtain a SecTrustRef representing peer certificates. Valid anytime,
 * subsequent to a handshake attempt. Caller must CFRelease the returned
 * trust reference.
 *
 * The returned trust reference will have already been evaluated for you,
 * unless one of the following is true:
 * - Your code has disabled automatic certificate verification, by calling
 *   SSLSetSessionOption to set kSSLSessionOptionBreakOnServerAuth to true.
 * - Your code has called SSLSetPeerID, and this session has been resumed
 *   from an earlier cached session.
 *
 * In these cases, your code should call SecTrustEvaluate prior to
 * examining the peer certificate chain or trust results (see SecTrust.h).
 *
 * NOTE: if you have not called SSLHandshake at least once prior to
 * calling this function, the returned trust reference will be NULL.
 */
OSStatus
SSLCopyPeerTrust			(SSLContextRef 		context,
							 SecTrustRef		* __nonnull CF_RETURNS_RETAINED trust)		/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_5_0);

/*
 * Specify some data, opaque to this library, which is sufficient
 * to uniquely identify the peer of the current session. An example
 * would be IP address and port, stored in some caller-private manner.
 * To be optionally called prior to SSLHandshake for the current
 * session. This is mandatory if this session is to be resumable.
 *
 * SecureTransport allocates its own copy of the incoming peerID. The
 * data provided in *peerID, while opaque to SecureTransport, is used
 * in a byte-for-byte compare to other previous peerID values set by the
 * current application. Matching peerID blobs result in SecureTransport
 * attempting to resume an SSL session with the same parameters as used
 * in the previous session which specified the same peerID bytes.
 */
OSStatus
SSLSetPeerID				(SSLContextRef 		context,
							 const void 		* __nullable peerID,
							 size_t				peerIDLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Obtain current PeerID. Returns NULL pointer, zero length if
 * SSLSetPeerID has not been called for this context.
 */
OSStatus
SSLGetPeerID				(SSLContextRef 		context,
							 const void 		* __nullable * __nonnull peerID,
							 size_t				*peerIDLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Obtain the SSLCipherSuite (e.g., SSL_RSA_WITH_DES_CBC_SHA) negotiated
 * for this session. Only valid when a session is active.
 */
OSStatus
SSLGetNegotiatedCipher		(SSLContextRef 		context,
							 SSLCipherSuite 	*cipherSuite)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);


/********************************************************
 *** Session context configuration, server side only. ***
 ********************************************************/

/*
 * This function is deprecated in OSX 10.11 and iOS 9.0 and
 * has no effect on the TLS handshake since OSX 10.10 and
 * iOS 8.0. Using separate RSA certificates for encryption
 * and signing is no longer supported.
 */
OSStatus
SSLSetEncryptionCertificate	(SSLContextRef		context,
							 CFArrayRef			certRefs)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_11, __IPHONE_5_0, __IPHONE_9_0);

/*
 * Specify requirements for client-side authentication.
 * Optional; Default is kNeverAuthenticate.
 *
 * Can only be called when no session is active.
 */
typedef CF_ENUM(int, SSLAuthenticate) {
	kNeverAuthenticate,			/* skip client authentication */
	kAlwaysAuthenticate,		/* require it */
	kTryAuthenticate			/* try to authenticate, but not an error
								 * if client doesn't have a cert */
};

OSStatus
SSLSetClientSideAuthenticate 	(SSLContextRef		context,
								 SSLAuthenticate	auth)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Add a DER-encoded distinguished name to list of acceptable names
 * to be specified in requests for client certificates.
 */
OSStatus
SSLAddDistinguishedName		(SSLContextRef 		context,
							 const void 		* __nullable derDN,
							 size_t 			derDNLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/*
 * Add a SecCertificateRef, or a CFArray of them, to a server's list
 * of acceptable Certificate Authorities (CAs) to present to the client
 * when client authentication is performed.
 *
 * If replaceExisting is true, the specified certificate(s) will replace
 * a possible existing list of acceptable CAs. If replaceExisting is
 * false, the specified certificate(s) will be appended to the existing
 * list of acceptable CAs, if any.
 *
 * Returns errSecParam if this is called on a SSLContextRef which
 * is configured as a client, or when a session is active.
 *
 * NOTE: this function is currently not available on iOS.
 */
OSStatus
SSLSetCertificateAuthorities(SSLContextRef		context,
							 CFTypeRef			certificateOrArray,
							 Boolean 			replaceExisting)
	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*
 * Obtain the certificates specified in SSLSetCertificateAuthorities(),
 * if any. Returns a NULL array if SSLSetCertificateAuthorities() has not
 * been called.
 * Caller must CFRelease the returned array.
 *
 * NOTE: this function is currently not available on iOS.
 */
OSStatus
SSLCopyCertificateAuthorities(SSLContextRef		context,
							  CFArrayRef		* __nonnull CF_RETURNS_RETAINED certificates)	/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

#endif /* MAC OS X */

/*
 * Obtain the list of acceptable distinguished names as provided by
 * a server (if the SSLContextRef is configured as a client), or as
 * specified by SSLSetCertificateAuthorities (if the SSLContextRef
 * is configured as a server).
 * The returned array contains CFDataRefs, each of which represents
 * one DER-encoded RDN.
 *
 * Caller must CFRelease the returned array.
 */
OSStatus
SSLCopyDistinguishedNames	(SSLContextRef		context,
							 CFArrayRef			* __nonnull CF_RETURNS_RETAINED names)
	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0);

/*
 * Obtain client certificate exchange status. Can be called
 * any time. Reflects the *last* client certificate state change;
 * subsequent to a renegotiation attempt by either peer, the state
 * is reset to kSSLClientCertNone.
 */
OSStatus
SSLGetClientCertificateState	(SSLContextRef				context,
								 SSLClientCertificateState	*clientState)
	__OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_5_0);


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/*
 * Specify Diffie-Hellman parameters. Optional; if we are configured to allow
 * for D-H ciphers and a D-H cipher is negotiated, and this function has not
 * been called, a set of process-wide parameters will be calculated. However
 * that can take a long time (30 seconds).
 *
 * NOTE: this function is currently not available on iOS.
 */
OSStatus SSLSetDiffieHellmanParams	(SSLContextRef			context,
									 const void 			* __nullable dhParams,
									 size_t					dhParamsLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/*
 * Return parameter block specified in SSLSetDiffieHellmanParams.
 * Returned data is not copied and belongs to the SSLContextRef.
 *
 * NOTE: this function is currently not available on iOS.
 */
OSStatus SSLGetDiffieHellmanParams	(SSLContextRef			context,
									 const void 			* __nullable * __nonnull dhParams,
									 size_t					*dhParamsLen)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/*
 * Enable/Disable RSA blinding. This feature thwarts a known timing
 * attack to which RSA keys are vulnerable; enabling it is a tradeoff
 * between performance and security. The default for RSA blinding is
 * enabled.
 *
 * ==========================
 * MAC OS X ONLY (DEPRECATED)
 * ==========================
 * NOTE: this function is not available on iOS, and should be considered
 * deprecated on Mac OS X. RSA blinding is enabled unconditionally, as
 * it prevents a known way for an attacker to recover the private key,
 * and the performance gain of disabling it is negligible.
 */
OSStatus SSLSetRsaBlinding			(SSLContextRef			context,
									 Boolean				blinding)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

OSStatus SSLGetRsaBlinding			(SSLContextRef			context,
									 Boolean				*blinding)
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);

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
 * Perform the SSL handshake. On successful return, session is
 * ready for normal secure application I/O via SSLWrite and SSLRead.
 *
 * Interesting error returns:
 *
 *  errSSLUnknownRootCert: Peer had a valid cert chain, but the root of
 *      the chain is unknown.
 *
 *  errSSLNoRootCert: Peer had a cert chain which did not end in a root.
 *
 *  errSSLCertExpired: Peer's cert chain had one or more expired certs.
 *
 *  errSSLXCertChainInvalid: Peer had an invalid cert chain (i.e.,
 *      signature verification within the chain failed, or no certs
 *      were found).
 *
 *  In all of the above errors, the handshake was aborted; the peer's
 *  cert chain is available via SSLCopyPeerTrust or SSLCopyPeerCertificates.
 *
 *  Other interesting result codes:
 *
 *  errSSLPeerAuthCompleted: Peer's cert chain is valid, or was ignored if
 *      cert verification was disabled via SSLSetEnableCertVerify. The application
 *      may decide to continue with the handshake (by calling SSLHandshake
 *      again), or close the connection at this point.
 *
 *  errSSLClientCertRequested: The server has requested a client certificate.
 *      The client may choose to examine the server's certificate and
 *      distinguished name list, then optionally call SSLSetCertificate prior
 *      to resuming the handshake by calling SSLHandshake again.
 *
 * A return value of errSSLWouldBlock indicates that SSLHandshake has to be
 * called again (and again and again until something else is returned).
 */
OSStatus
SSLHandshake				(SSLContextRef		context)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Normal application-level read/write. On both of these, a errSSLWouldBlock
 * return and a partially completed transfer - or even zero bytes transferred -
 * are NOT mutually exclusive.
 */
OSStatus
SSLWrite					(SSLContextRef		context,
							 const void *		__nullable data,
							 size_t				dataLength,
							 size_t 			*processed)		/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * data is mallocd by caller; available size specified in
 * dataLength; actual number of bytes read returned in
 * *processed.
 */
OSStatus
SSLRead						(SSLContextRef		context,
							 void *				data,			/* RETURNED */
							 size_t				dataLength,
							 size_t 			*processed)		/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Determine how much data the client can be guaranteed to
 * obtain via SSLRead() without blocking or causing any low-level
 * read operations to occur.
 */
OSStatus
SSLGetBufferedReadSize		(SSLContextRef context,
							 size_t *bufSize)					/* RETURNED */
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Determine how much data the application can be guaranteed to write
 * with SSLWrite() without causing fragmentation. The value is based on
 * the maximum Datagram Record size defined by the application with
 * SSLSetMaxDatagramRecordSize(), minus the DTLS Record header size.
 */
OSStatus
SSLGetDatagramWriteSize		(SSLContextRef dtlsContext,
							 size_t *bufSize)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/*
 * Terminate current SSL session.
 */
OSStatus
SSLClose					(SSLContextRef		context)
	__OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_5_0);

/*
 * Set the minimum acceptable strength of policy to be negotiated for an
 * ATS session
 */
OSStatus
SSLSetSessionStrengthPolicy(SSLContextRef context,
                            SSLSessionStrengthPolicy policyStrength);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @enum Class Value Constants
    @discussion Predefined item class constants used to get or set values in
        a dictionary. The kSecClass constant is the key and its value is one
        of the constants defined here.
    @constant kSecClassGenericPassword Specifies generic password items.
    @constant kSecClassInternetPassword Specifies Internet password items.
    @constant kSecClassCertificate Specifies certificate items.
    @constant kSecClassKey Specifies key items.
    @constant kSecClassIdentity Specifies identity items.
*/
extern const CFStringRef kSecClassGenericPassword
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecClassInternetPassword
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecClassCertificate
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecClassKey
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecClassIdentity
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
    @enum Attribute Key Constants
    @discussion Predefined item attribute keys used to get or set values in a
        dictionary. Not all attributes apply to each item class. The table
        below lists the currently defined attributes for each item class:

    kSecClassGenericPassword item attributes:
        kSecAttrAccessible
        kSecAttrAccessControl
        kSecAttrAccessGroup
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
        kSecAttrAccessible
        kSecAttrAccessControl
        kSecAttrAccessGroup
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
        kSecAttrAccessible
        kSecAttrAccessControl
        kSecAttrAccessGroup
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
        kSecAttrAccessible
        kSecAttrAccessControl
        kSecAttrAccessGroup
        kSecAttrKeyClass
        kSecAttrLabel
        kSecAttrApplicationLabel
        kSecAttrIsPermanent
        kSecAttrApplicationTag
        kSecAttrKeyType
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
        (Currently only the value of this attribute must be equal to the
        version of the X509 certificate.  So 1 for v1 2 for v2 and 3 for v3
        certificates). Only items of class kSecClassCertificate have this
        attribute.
    @constant kSecAttrCertificateEncoding (read-only) Specifies a dictionary
        key whose value is the item's certificate encoding. You use this key
        to get a value of type CFNumberRef that denotes the certificate
        encoding (Currently only the value 3 meaning
        kSecAttrCertificateEncodingDER is supported). Only items of class
        kSecClassCertificate have this attribute.
    @constant kSecAttrKeyClass (read only) Specifies a dictionary key whose
        value is one of kSecAttrKeyClassPublic, kSecAttrKeyClassPrivate or
        kSecAttrKeyClassSymmetric.
    @constant kSecAttrApplicationLabel Specifies a dictionary key whose value
        is the key's application label attribute. This is different from the
        kSecAttrLabel (which is intended to be human-readable). This attribute
        is used to look up a key programmatically; in particular, for keys of
        class kSecAttrKeyClassPublic and kSecAttrKeyClassPrivate, the value of
        this attribute is the hash of the public key.
    @constant kSecAttrIsPermanent Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question will be stored
        permanently.
    @constant kSecAttrApplicationTag Specifies a dictionary key whose value is a
        CFDataRef containing private tag data.
    @constant kSecAttrKeyType Specifies a dictionary key whose value is a
        CFNumberRef indicating the algorithm associated with this key
        (Currently only the value 42 is supported, alternatively you can use
        kSecAttrKeyTypeRSA).
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
	queries.
    @constant kSecAttrTokenID Specifies a dictionary key whose presence
	indicates that item is backed by external token. Value of this attribute
	is CFStringRef uniquely identifying containing token. When this attribute
	is not present, item is stored in internal keychain database.
	Note that once item is created, this attribute cannot be changed - in other
	words it is not possible to migrate existing items to, from or between tokens.
	Currently the only available value for this attribute is
	kSecAttrTokenIDSecureEnclave, which indicates that item (private key) is
	backed by device's Secure Enclave.
 */
extern const CFStringRef kSecAttrAccessible
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessControl
    __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
extern const CFStringRef kSecAttrAccessGroup
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_3_0);
extern const CFStringRef kSecAttrSynchronizable
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
extern const CFStringRef kSecAttrCreationDate
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrModificationDate
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrDescription
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrComment
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCreator
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrType
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrLabel
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrIsInvisible
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrIsNegative
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAccount
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrService
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrGeneric
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrSecurityDomain
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrServer
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocol
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationType
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrPort
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrPath
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrSubject
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrIssuer
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrSerialNumber
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrSubjectKeyID
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrPublicKeyHash
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCertificateType
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCertificateEncoding
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeyClass
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrApplicationLabel
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrIsPermanent
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrApplicationTag
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeyType
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeySizeInBits
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrEffectiveKeySize
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanEncrypt
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanDecrypt
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanDerive
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanSign
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanVerify
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanWrap
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrCanUnwrap
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrSyncViewHint
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
extern const CFStringRef kSecAttrTokenID
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

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
         only be accessed while the device is unlocked. This class is only 
         available if a passcode is set on the device. This is recommended for
         items that only need to be accessible while the application is in the
         foreground. Items with this attribute will never migrate to a new 
         device, so after a backup is restored to a new device, these items 
         will be missing. No items can be stored in this class on devices 
         without a passcode. Disabling the device passcode will cause all 
         items in this class to be deleted.
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
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlock
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessibleAlways
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
extern const CFStringRef kSecAttrAccessibleWhenUnlockedThisDeviceOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);
extern const CFStringRef kSecAttrAccessibleAlwaysThisDeviceOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolFTPAccount
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolHTTP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolIRC
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolNNTP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolPOP3
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolSMTP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolSOCKS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolIMAP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolLDAP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolAppleTalk
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolAFP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolTelnet
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolSSH
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolFTPS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolHTTPS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolHTTPProxy
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolHTTPSProxy
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolFTPProxy
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolSMB
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolRTSP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolRTSPProxy
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolDAAP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolEPPC
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolIPP
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolNNTPS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolLDAPS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolTelnetS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolIMAPS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolIRCS
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrProtocolPOP3S
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeMSN
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeDPA
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeRPA
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeHTTPBasic
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeHTTPDigest
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeHTMLForm
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecAttrAuthenticationTypeDefault
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeyClassPrivate
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeyClassSymmetric
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @enum kSecAttrKeyType Value Constants
    @discussion Predefined item attribute constants used to get or set values
		in a dictionary. The kSecAttrKeyType constant is the key
		and its value is one of the constants defined here.
    @constant kSecAttrKeyTypeRSA.
    @constant kSecAttrKeyTypeEC.
*/
extern const CFStringRef kSecAttrKeyTypeRSA
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFStringRef kSecAttrKeyTypeEC
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_4_0);

/*!
    @enum kSecAttrSynchronizable Value Constants
    @discussion Predefined item attribute constants used to get or set values
		in a dictionary. The kSecAttrSynchronizable constant is the key
		and its value is one of the constants defined here.
    @constant kSecAttrSynchronizableAny Specifies that both synchronizable and
        non-synchronizable results should be returned from this query. This may
        be used as a value for the kSecAttrSynchronizable dictionary key in a
        call to SecItemCopyMatching, SecItemUpdate, or SecItemDelete.
*/
extern const CFStringRef kSecAttrSynchronizableAny
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @enum Search Constants
    @discussion Predefined search constants used to set values in a query
        dictionary. You can specify a combination of search attributes and
        item attributes when looking for matching items with the
        SecItemCopyMatching function.
    @constant kSecMatchPolicy Specifies a dictionary key whose value is a
        SecPolicyRef. If provided, returned certificates or identities must
        verify with this policy.
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
    @constant kSecMatchCaseInsensitive Specifies a dictionary key whose value
        is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then case-sensitive string matching is performed.
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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchItemList
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchSearchList
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchIssuers
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchEmailAddressIfPresent
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchSubjectContains
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchCaseInsensitive
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchTrustedOnly
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchValidOnDate
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchLimit
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchLimitOne
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecMatchLimitAll
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);


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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecReturnAttributes
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecReturnRef
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecReturnPersistentRef
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);


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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecValueRef
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecValuePersistentRef
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);


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
    @constant kSecUseOperationPrompt Specifies a dictionary key whose value
        is a CFStringRef that represents a user-visible string describing
        the operation for which the application is attempting to authenticate.
        The application is responsible for the text localization.
    @constant kSecUseNoAuthenticationUI Specifies a dictionary key whose value
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
          eventually reuse the sucessfully authenticated context in subsequent
          keychain operations.
*/
extern const CFStringRef kSecUseItemList
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecUseOperationPrompt
    __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
extern const CFStringRef kSecUseNoAuthenticationUI
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_10, __MAC_10_11, __IPHONE_8_0, __IPHONE_9_0, "Use a kSecAuthenticationUI instead.");
extern const CFStringRef kSecUseAuthenticationUI
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
extern const CFStringRef kSecUseAuthenticationContext
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
extern const CFStringRef kSecUseAuthenticationUIFail
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
extern const CFStringRef kSecUseAuthenticationUISkip
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*!
     @enum kSecAttrTokenID Value Constants
     @discussion Predefined item attribute constant used to get or set values
         in a dictionary. The kSecAttrTokenID constant is the key and its value
         can be kSecAttrTokenIDSecureEnclave.
     @constant kSecAttrTokenIDSecureEnclave Specifies well-known identifier of the
         token implemented using device's Secure Enclave. The only keychain items
         supported by the Secure Enclave token are 256-bit elliptic curve keys
         (kSecAttrKeyTypeEC).  Keys must be generated on the secure enclave using
         SecKeyGenerateKeyPair call with kSecAttrTokenID set to
         kSecAttrTokenIDSecureEnclave in the parameters dictionary, it is not
         possible to import pregenerated keys to kSecAttrTokenIDSecureEnclave token.
*/
extern const CFStringRef kSecAttrTokenIDSecureEnclave
    __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0);

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

    To convert from a persistent item reference to a normal item reference,
    specify a kSecValuePersistentRef whose value a CFDataRef (the persistent
    reference), and a kSecReturnRef whose value is kCFBooleanTrue.
*/
OSStatus SecItemCopyMatching(CFDictionaryRef query, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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

    Result types are specified as follows:

      * To obtain the data of the added item (CFDataRef), specify
        kSecReturnData with a value of kCFBooleanTrue.
      * To obtain all the attributes of the added item (CFDictionaryRef),
        specify kSecReturnAttributes with a value of kCFBooleanTrue.
      * To obtain a reference to the added item (SecKeychainItemRef, SecKeyRef,
        SecCertificateRef, or SecIdentityRef), specify kSecReturnRef with a
        value of kCFBooleanTrue.
      * To obtain a persistent reference to the added item (CFDataRef), specify
        kSecReturnPersistentRef with a value of kCFBooleanTrue. Note that
        unlike normal references, a persistent reference may be stored on disk
        or passed between processes.
      * If more than one of these result types is specified, the result is
        returned as a CFDictionaryRef containing all the requested data.
      * If a result type is not specified, no results are returned.
*/
OSStatus SecItemAdd(CFDictionaryRef attributes, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
OSStatus SecItemUpdate(CFDictionaryRef query,
    CFDictionaryRef attributesToUpdate)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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

      * To delete an item identified by a transient reference, specify
        kSecValueRef with a reference returned by using the kSecReturnRef
        key in a previous call to SecItemCopyMatching or SecItemAdd.
      * To delete an item identified by a persistent reference, specify
        kSecValuePersistentRef with a persistent reference returned by
        using the kSecReturnPersistentRef key to SecItemCopyMatching or
        SecItemAdd.
      * To delete multiple items specify kSecMatchItemList with an array
        of references.
      * If more than one of these result keys is specified, the behavior is
        undefined.
*/
OSStatus SecItemDelete(CFDictionaryRef query)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECITEM_H_ */
// ==========  Security.framework/Headers/Security.h
/*
 * Copyright (c) 2007-2008,2012,2014 Apple Inc. All Rights Reserved.
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

#include <Security/SecBase.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>
#include <Security/SecImportExport.h>
#include <Security/SecAccessControl.h>
#include <Security/SecItem.h>
#include <Security/SecKey.h>
#include <Security/SecPolicy.h>
#include <Security/SecRandom.h>
#include <Security/SecSharedCredential.h>
#include <Security/SecTrust.h>

// ==========  Security.framework/Headers/SecCertificate.h
/*
 * Copyright (c) 2006-2009,2012-2015 Apple Inc. All Rights Reserved.
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

#include <Security/SecBase.h>
#include <CoreFoundation/CFData.h>

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
    @param certificate DER encoded X.509 certificate.
	@result Return NULL if the passed-in data is not a valid DER-encoded
    X.509 certificate, return a SecCertificateRef otherwise.
*/
__nullable
SecCertificateRef SecCertificateCreateWithData(CFAllocatorRef __nullable allocator,
    CFDataRef data) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
    @param certificate SecCertificate object created with
    SecCertificateCreateWithData().
    @discussion All the data in this string comes from the certificate itself
    and thus it's in whatever language the certificate itself is in.
	@result A CFStringRef which the caller should CFRelease() once it's no
    longer needed.
*/
CFStringRef SecCertificateCopySubjectSummary(SecCertificateRef certificate)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECCERTIFICATE_H_ */

// ==========  Security.framework/Headers/SecKey.h
/*
 * Copyright (c) 2006-2009,2011-2013 Apple Inc. All Rights Reserved.
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

	You can use a key as a keychain item in most functions.
*/

#ifndef _SECURITY_SECKEY_H_
#define _SECURITY_SECKEY_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <sys/types.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/* Padding Types (iPhone OS 2.0 and later only). */
typedef CF_OPTIONS(uint32_t, SecPadding)
{
    kSecPaddingNone      = 0,
    kSecPaddingPKCS1     = 1, // For EC, defaults to a signature in x9.62 DER encoding.
    kSecPaddingOAEP      = 2,

    /* For SecKeyRawSign/SecKeyRawVerify only,
     ECDSA signature is raw byte format {r,s}, big endian.
     First half is r, second half is s */
    kSecPaddingSigRaw  = 0x4000,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD2
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD2  = 0x8000,  /* Unsupported as of iOS 5.0 */

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD5
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD5  = 0x8001,  /* Unsupported as of iOS 5.0 */

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA1
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1SHA1 = 0x8002,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA224
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA224 = 0x8003,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA256
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA256 = 0x8004,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA384
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA384 = 0x8005,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA512
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA512 = 0x8006,
};


/*!
	@function SecKeyGetTypeID
	@abstract Returns the type identifier of SecKey instances.
	@result The CFTypeID of SecKey instances.
*/
CFTypeID SecKeyGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @enum Dictionary key constants for SecKeyGeneratePair API.
    @discussion Predefined key constants used to get or set values
		in a dictionary.
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
    @function SecKeyGeneratePair
    @abstract Generate a private/public keypair.
    @param parameters A dictionary containing one or more key-value pairs.
	See the discussion sections below for a complete overview of options.
    @param publicKey On return, a SecKeyRef reference to the public key.
    @param privateKey On return, a SecKeyRef reference to the private key.
    @result A result code. See "Security Error Codes" (SecBase.h).
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
	  * kSecAttrIsPermanent if this key is present and has a Boolean
	    value of true, the key or key pair will be added to the default
	    keychain.
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
OSStatus SecKeyGeneratePair(CFDictionaryRef parameters, SecKeyRef * __nullable CF_RETURNS_RETAINED publicKey,
    SecKeyRef * __nullable CF_RETURNS_RETAINED privateKey) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


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

/*!
    @function SecKeyGetBlockSize
    @abstract Decrypt a block of ciphertext. 
    @param key The key for which the block length is requested.
    @result The block length of the key in bytes.
    @discussion If for example key is an RSA key the value returned by 
    this function is the size of the modulus.
 */
size_t SecKeyGetBlockSize(SecKeyRef key)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECKEY_H_ */
// ==========  Security.framework/Headers/SecTrust.h
/*
 * Copyright (c) 2002-2010,2012-2014 Apple Inc. All Rights Reserved.
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

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecTrustResultType
    @abstract Specifies the trust result type.
    @discussion SecTrustResultType results have two dimensions.  They specify
    both whether evaluation suceeded and whether this is because of a user
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
typedef uint32_t SecTrustResultType;
enum {
    kSecTrustResultInvalid = 0,
    kSecTrustResultProceed = 1,
    kSecTrustResultConfirm SEC_DEPRECATED_ATTRIBUTE = 2,
    kSecTrustResultDeny = 3,
    kSecTrustResultUnspecified = 4,
    kSecTrustResultRecoverableTrustFailure = 5,
    kSecTrustResultFatalTrustFailure = 6,
    kSecTrustResultOtherError = 7
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
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion Calling this function without also calling
    SecTrustSetAnchorCertificatesOnly() will disable trusting any
    anchors other than the ones in anchorCertificates.
 */
OSStatus SecTrustSetAnchorCertificates(SecTrustRef trust,
    CFArrayRef anchorCertificates)
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
OSStatus SecTrustEvaluate(SecTrustRef trust, SecTrustResultType * __nullable result)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
#endif

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
    not be extracted (this can happen with DSA certificate chains if the
    parameters in the chain cannot be found).  The caller is responsible
    for calling CFRelease on the returned key when it is no longer needed.
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
    SecTrustCopyExceptions() in the past.
    @result Upon calling SecTrustEvaluate(), any failures that where present at the
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
bool SecTrustSetExceptions(SecTrustRef trust, CFDataRef exceptions)
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

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

/*
 *  Legacy functions (OS X only)
 */
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
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
typedef uint32_t SecTrustOptionFlags;
enum {
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
    @discussion By default, the user's keychain search list and the system
    anchors keychain are searched for certificates to complete the chain. You
    can specify a zero-element array if you do not want any keychains searched.
    Note: this function is not applicable to iOS.
 */
OSStatus SecTrustSetKeychains(SecTrustRef trust, CFTypeRef __nullable keychainOrArray)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

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
    CFArrayRef * __nonnull CF_RETURNS_RETAINED certChain, CSSM_TP_APPLE_EVIDENCE_INFO * __nullable * __nonnull statusChain)
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
 * Copyright (c) 2002-2010,2012-2014 Apple Inc. All Rights Reserved.
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
	@constant kSecPolicyAppleIPsec
	@constant kSecPolicyApplePKINITClient
	@constant kSecPolicyApplePKINITServer
	@constant kSecPolicyAppleCodeSigning
	@constant kSecPolicyMacAppStoreReceipt
	@constant kSecPolicyAppleIDValidation
	@constant kSecPolicyAppleTimeStamping
	@constant kSecPolicyAppleRevocation
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
extern const CFStringRef kSecPolicyApplePKINITClient
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFStringRef kSecPolicyApplePKINITServer
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
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
            kSecPolicyRevocationFlags (only valid for a revocation policy)

    @constant kSecPolicyOid Specifies the policy OID (value is a CFStringRef)
    @constant kSecPolicyName Specifies a CFStringRef (or CFArrayRef of same)
        containing a name which must be matched in the certificate to satisfy
        this policy. For SSL/TLS, EAP, and IPSec policies, this specifies the
        server name which must match the common name of the certificate.
        For S/MIME, this specifies the RFC822 email address.
    @constant kSecPolicyClient Specifies a CFBooleanRef value that indicates
        this evaluation should be for a client certificate. If not set (or
        false), the policy evaluates the certificate as a server certificate.
    @constant kSecPolicyRevocationFlags Specifies a CFNumberRef that holds a
        kCFNumberCFIndexType bitmask value. See "Revocation Policy Constants"
        for a description of individual bits in this value.
 */
extern const CFStringRef kSecPolicyOid
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyName
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyClient
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_7_0);
extern const CFStringRef kSecPolicyRevocationFlags
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
SecPolicyRef SecPolicyCreateWithProperties(CFTypeRef policyIdentifier,
	CFDictionaryRef __nullable properties)
	__OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

/*
 *  Legacy functions (OS X only)
 */
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
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
// ==========  Security.framework/Headers/SecBase.h
/*
 * Copyright (c) 2000-2009,2011-2014 Apple Inc. All Rights Reserved.
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
	@header SecBase
	SecBase contains common declarations for the Security functions.
*/

#ifndef _SECURITY_SECBASE_H_
#define _SECURITY_SECBASE_H_

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CFBase.h>

#if defined(__clang__)
#define SEC_DEPRECATED_ATTRIBUTE DEPRECATED_ATTRIBUTE
#else
#define SEC_DEPRECATED_ATTRIBUTE
#endif

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecCertificateRef
    @abstract CFType representing a X.509 certificate.
    See SecCertificate.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecCertificate *SecCertificateRef;

/*!
    @typedef SecIdentityRef
    @abstract CFType representing an identity, which contains
    a SecKeyRef and an associated SecCertificateRef. See
    SecIdentity.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecIdentity *SecIdentityRef;

/*!
    @typedef SecKeyRef
    @abstract CFType representing a cryptographic key. See
    SecKey.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKey *SecKeyRef;

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

/***********************************************
 *** OSStatus values unique to Security APIs ***
 ***********************************************/

/*
    Note: the comments that appear after these errors are used to create
    SecErrorMessages.strings. The comments must not be multi-line, and
    should be in a form meaningful to an end user. If a different or
    additional comment is needed, it can be put in the header doc format,
    or on a line that does not start with errZZZ.
*/

CF_ENUM(OSStatus)
{
    errSecSuccess                               = 0,       /* No error. */
    errSecUnimplemented                         = -4,      /* Function or operation not implemented. */
    errSecIO                                    = -36,     /*I/O error (bummers)*/
    errSecOpWr                                  = -49,     /*file already open with with write permission*/
    errSecParam                                 = -50,     /* One or more parameters passed to a function where not valid. */
    errSecAllocate                              = -108,    /* Failed to allocate memory. */
    errSecUserCanceled                          = -128,    /* User canceled the operation. */
    errSecBadReq                                = -909,    /* Bad parameter or invalid state for operation. */
    errSecInternalComponent                     = -2070,
    errSecNotAvailable                          = -25291,  /* No keychain is available. You may need to restart your computer. */
    errSecDuplicateItem                         = -25299,  /* The specified item already exists in the keychain. */
    errSecItemNotFound                          = -25300,  /* The specified item could not be found in the keychain. */
    errSecInteractionNotAllowed                 = -25308,  /* User interaction is not allowed. */
    errSecDecode                                = -26275,  /* Unable to decode the provided data. */
    errSecAuthFailed                            = -25293,  /* The user name or passphrase you entered is not correct. */
};

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECBASE_H_ */
// ==========  Security.framework/Headers/SecSharedCredential.h
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
extern const CFStringRef kSecSharedPassword
    __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0) __WATCHOS_UNAVAILABLE;

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
    void (^completionHandler)(CFErrorRef __nullable error))
    __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0) __WATCHOS_UNAVAILABLE;

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
    void (^completionHandler)(CFArrayRef __nullable credentials, CFErrorRef __nullable error))
    __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0) __WATCHOS_UNAVAILABLE;

/*!
 @function SecCreateSharedWebCredentialPassword
 @abstract Returns a randomly generated password.
 @return CFStringRef password in the form xxx-xxx-xxx-xxx where x is taken from the sets "abcdefghkmnopqrstuvwxy", "ABCDEFGHJKLMNPQRSTUVWXYZ", "3456789" with at least one character from each set being present.
*/
__nullable
CFStringRef SecCreateSharedWebCredentialPassword(void)
__OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0) __WATCHOS_UNAVAILABLE;


#endif /* __BLOCKS__ */

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECSHAREDCREDENTIAL_H_ */

// ==========  Security.framework/Headers/SecImportExport.h
/*
 * Copyright (c) 2007-2009,2012-2013 Apple Inc. All Rights Reserved.
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
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @enum Import/Export options
    @discussion Predefined key constants used to pass in arguments to the
        import/export functions
    @constant kSecImportExportPassphrase Specifies a passphrase represented by
        a CFStringRef to be used to encrypt/decrypt.
*/
extern const CFStringRef kSecImportExportPassphrase
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemKeyID
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemTrust
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemCertChain
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemIdentity
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
	@function SecPKCS12Import
	@abstract return contents of a PKCS#12 formatted blob.
    @param pkcs12_data PKCS#12 formatted data
    @param options Dictionary containing options for decode.  A 
        kSecImportExportPassphrase is required at a minimum.  Only password-
        based PKCS#12 blobs are currently supported.
    @param items Array containing a dictionary for every item extracted.  See
        kSecImportItem constants.
	@result errSecSuccess in case of success. errSecDecode means either the
        blob can't be read or it is malformed. errSecAuthFailed means an
        incorrect password was passed, or data in the container got damaged.
*/
OSStatus SecPKCS12Import(CFDataRef pkcs12_data, CFDictionaryRef options,
    CFArrayRef * __nonnull CF_RETURNS_RETAINED items) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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

/*
 * Defined as enum for debugging, but in the protocol
 * it is actually exactly two bytes
 */
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* 32-bit value on OS X */
typedef uint32_t SSLCipherSuite;
#else
/* 16-bit value on iOS */
typedef uint16_t SSLCipherSuite;
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

    /* TLS 1.2 addenda, RFC 5246 */

    /* Initial state. */
    TLS_NULL_WITH_NULL_NULL                   = 0x0000,

    /* Server provided RSA certificate for key exchange. */
    TLS_RSA_WITH_NULL_MD5                     = 0x0001,
    TLS_RSA_WITH_NULL_SHA                     = 0x0002,
    TLS_RSA_WITH_RC4_128_MD5                  = 0x0004,
    TLS_RSA_WITH_RC4_128_SHA                  = 0x0005,
    TLS_RSA_WITH_3DES_EDE_CBC_SHA             = 0x000A,
    //TLS_RSA_WITH_AES_128_CBC_SHA              = 0x002F,
    //TLS_RSA_WITH_AES_256_CBC_SHA              = 0x0035,
    TLS_RSA_WITH_NULL_SHA256                  = 0x003B,
    TLS_RSA_WITH_AES_128_CBC_SHA256           = 0x003C,
    TLS_RSA_WITH_AES_256_CBC_SHA256           = 0x003D,

    /* Server-authenticated (and optionally client-authenticated) Diffie-Hellman. */
    TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA          = 0x000D,
    TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA          = 0x0010,
    TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA         = 0x0013,
    TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA         = 0x0016,
    //TLS_DH_DSS_WITH_AES_128_CBC_SHA           = 0x0030,
    //TLS_DH_RSA_WITH_AES_128_CBC_SHA           = 0x0031,
    //TLS_DHE_DSS_WITH_AES_128_CBC_SHA          = 0x0032,
    //TLS_DHE_RSA_WITH_AES_128_CBC_SHA          = 0x0033,
    //TLS_DH_DSS_WITH_AES_256_CBC_SHA           = 0x0036,
    //TLS_DH_RSA_WITH_AES_256_CBC_SHA           = 0x0037,
    //TLS_DHE_DSS_WITH_AES_256_CBC_SHA          = 0x0038,
    //TLS_DHE_RSA_WITH_AES_256_CBC_SHA          = 0x0039,
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
    //TLS_DH_anon_WITH_AES_128_CBC_SHA          = 0x0034,
    //TLS_DH_anon_WITH_AES_256_CBC_SHA          = 0x003A,
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

    /* Addenda from rfc 5288 AES Galois Counter Mode (GCM) Cipher Suites
       for TLS. */
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

    /* RFC 5746 - Secure Renegotiation */
    TLS_EMPTY_RENEGOTIATION_INFO_SCSV         = 0x00FF,
	/*
	 * Tags for SSL 2 cipher kinds which are not specified
	 * for SSL 3.
	 */
    SSL_RSA_WITH_RC2_CBC_MD5 =                  0xFF80,
    SSL_RSA_WITH_IDEA_CBC_MD5 =                 0xFF81,
    SSL_RSA_WITH_DES_CBC_MD5 =                  0xFF82,
    SSL_RSA_WITH_3DES_EDE_CBC_MD5 =             0xFF83,
    SSL_NO_SUCH_CIPHERSUITE =                   0xFFFF
};

#endif	/* !_SECURITY_CIPHERSUITE_H_ */
// ==========  Security.framework/Headers/SecRandom.h
/*
 * Copyright (c) 2007-2009,2012-2013 Apple Inc. All Rights Reserved.
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
    @abstract Reference to a (psuedo) random number generator.
*/
typedef const struct __SecRandom * SecRandomRef;

/* This is a synonym for NULL, if you'd rather use a named constant.   This
   refers to a cryptographically secure random number generator.  */
extern const SecRandomRef kSecRandomDefault
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
	@function SecRandomCopyBytes
	@abstract Return count random bytes in *bytes, allocated by the caller.
	@result Return 0 on success or -1 if something went wrong, check errno
    to find out the real error.
*/
int SecRandomCopyBytes(SecRandomRef __nullable rnd, size_t count, uint8_t *bytes)
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

typedef CF_OPTIONS(CFIndex, SecAccessControlCreateFlags) {
    kSecAccessControlUserPresence           = 1 << 0,                                 // User presence policy using Touch ID or Passcode. Touch ID does not have to be available or enrolled. Item is still accessible by Touch ID even if fingers are added or removed.
    kSecAccessControlTouchIDAny             CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 1,   // Constraint: Touch ID (any finger). Touch ID must be available and at least one finger must be enrolled. Item is still accessible by Touch ID even if fingers are added or removed.
    kSecAccessControlTouchIDCurrentSet      CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 3,   // Constraint: Touch ID from the set of currently enrolled fingers. Touch ID must be available and at least one finger must be enrolled. When fingers are added or removed, the item is invalidated.
    kSecAccessControlDevicePasscode         CF_ENUM_AVAILABLE(10_11, 9_0) = 1 << 4,   // Constraint: Device passcode
    kSecAccessControlOr                     CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 14,  // Constraint logic operation: when using more than one constraint, at least one of them must be satisfied.
    kSecAccessControlAnd                    CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 15,  // Constraint logic operation: when using more than one constraint, all must be satisfied.
    kSecAccessControlPrivateKeyUsage        CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 30,  // Create access control for private key operations (i.e. sign operation)
    kSecAccessControlApplicationPassword    CF_ENUM_AVAILABLE(NA, 9_0)    = 1 << 31,  // Security: Application provided password for data encryption key generation. This is not a constraint but additional item encryption mechanism.
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
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif // _SECURITY_SECACCESSCONTROL_H_
// ==========  Security.framework/Headers/SecIdentity.h
/*
 * Copyright (c) 2002-2004,2007-2009,2012-2013 Apple Inc. All Rights Reserved.
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

#include <Security/SecBase.h>
#include <CoreFoundation/CFBase.h>

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

/*!
	@function SecIdentityCopyCertificate
    @abstract Returns a reference to a certificate for the given identity
    reference.
    @param identityRef An identity reference.
	@param certificateRef On return, a pointer to the found certificate
    reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
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
    identity. The private key must be of class type kSecAppleKeyItemClass.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyPrivateKey(
            SecIdentityRef identityRef, 
            SecKeyRef * __nonnull CF_RETURNS_RETAINED privateKeyRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECIDENTITY_H_ */
