// ==========  Network.framework/Headers/connection.h
//
//  connection.h
//  Network
//
//  Copyright (c) 2015-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_H__
#define __NW_CONNECTION_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/endpoint.h>
#include <Network/parameters.h>
#include <Network/path.h>
#include <Network/content_context.h>
#include <Network/error.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_connection_t
 * @abstract
 *		A Network Connection is an object that represents a bi-directional data pipe between
 *		a local endpoint and a remote endpoint. A connection handles establishment of any
 *		transport, security, or application-level protocols required to transmit and receive
 *		user data. Multiple protocol instances may be attempted during the establishment phase
 *		of the connection. Multiple connections may be multiplexed over a single transport
 *		if they make use of a protocol that supports multiplexing.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_CONNECTION_IMPL
NW_OBJECT_DECL(nw_connection);
#endif // NW_CONNECTION_IMPL

/*!
 * @typedef nw_connection_state_t
 * @abstract
 *		Connection states sent by nw_connection_set_state_changed_handler.
 *		States generally progress forward and do not move backwards, with the
 *		exception of preparing and waiting, which may alternate before the connection
 *		becomes ready or failed.
 */
typedef enum {
	/*!
	 *	@const nw_connection_state_invalid The state of the connection is not valid. This state
	 *		will never be delivered in the connection's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_connection_state_invalid = 0,
	/*! @const nw_connection_state_waiting The connection is waiting for a usable network before re-attempting */
	nw_connection_state_waiting = 1,
	/*! @const nw_connection_state_preparing The connection is in the process of establishing */
	nw_connection_state_preparing = 2,
	/*! @const nw_connection_state_ready The connection is established and ready to send and receive data upon */
	nw_connection_state_ready = 3,
	/*! @const nw_connection_state_failed The connection has irrecoverably closed or failed */
	nw_connection_state_failed = 4,
	/*! @const nw_connection_state_cancelled The connection has been cancelled by the caller */
	nw_connection_state_cancelled = 5,
} nw_connection_state_t;

/*!
 * @function nw_connection_create
 *
 * @abstract
 *		Creates a networking connection to an endpoint.
 *
 * @param endpoint
 *		The remote endpoint to connect to.
 *
 * @param parameters
 *		The parameters to use for the connection. The data mode,
 *		either datagram or stream, must be set.
 *
 * @result
 *		Returns an allocated nw_connection_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_connection_t
nw_connection_create(nw_endpoint_t endpoint,
					 nw_parameters_t parameters);

/*!
 * @function nw_connection_copy_endpoint
 *
 * @abstract
 *		Retrieves the remote endpoint for a connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns an nw_endpoint_t object on success.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_connection_copy_endpoint(nw_connection_t connection);

/*!
 * @function nw_connection_copy_parameters
 *
 * @abstract
 *		Retrieves the parameters for a connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns an nw_parameters_t object on success.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_connection_copy_parameters(nw_connection_t connection);

#ifdef __BLOCKS__

typedef void (^nw_connection_state_changed_handler_t)(nw_connection_state_t state,
													  _Nullable nw_error_t error);

/*!
 * @function nw_connection_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		connection has been cancelled, the nw_connection_state_cancelled state will
 *		be delivered last.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The state changed handler to call when the connection state changes.
 *		Pass NULL to remove the state changed handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_state_changed_handler(nw_connection_t connection,
								_Nullable nw_connection_state_changed_handler_t handler);

typedef void (^nw_connection_boolean_event_handler_t)(bool value);

/*!
 * @function nw_connection_set_viability_changed_handler
 *
 * @abstract
 *		Define a callback to be fired when the viability of the connection changes.
 *		This indicates whether or not read and write calls will succeed on a ready
 *		connection.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the connection viability changes. The value will
 *		be true when the connection is viable, and false otherwise.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_viability_changed_handler(nw_connection_t connection,
											_Nullable nw_connection_boolean_event_handler_t handler);

/*!
 * @function nw_connection_set_better_path_available_handler
 *
 * @abstract
 *		Define a callback to be fired when a better path is available or not.
 *		This indicates whether or not a preferred path is available for the
 *		connection.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the better path availability changes. The value
 *		will be true when a better path is available, and false otherwise.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_better_path_available_handler(nw_connection_t connection,
												_Nullable nw_connection_boolean_event_handler_t handler);

typedef void (^nw_connection_path_event_handler_t)(nw_path_t path);

/*!
 * @function nw_connection_set_path_changed_handler
 *
 * @abstract
 *		Define a callback to be fired when the connection's path changes.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the connection's path changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_path_changed_handler(nw_connection_t connection,
									   _Nullable nw_connection_path_event_handler_t handler);
#endif // __BLOCKS__

/*!
 * @function nw_connection_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_connection_start().
 *
 * @param connection
 *		The connection object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_queue(nw_connection_t connection,
						dispatch_queue_t queue);

/*!
 * @function nw_connection_start
 *
 * @abstract
 *		Starts the connection, which will cause the connection
 *		to evaluate its path, do resolution, and try to become
 *		readable and writable.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_start(nw_connection_t connection);

/*!
 * @function nw_connection_restart
 *
 * @abstract
 *		Connections in the waiting state will normally re-attempt
 *		on network changes. Call nw_connection_restart() to force
 *		a connection in the waiting state to retry connection
 *		establishment even without a network change. Calls to restart
 *		for connections that are not in the waiting state will be
 *		ignored.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_restart(nw_connection_t connection);

/*!
 * @function nw_connection_cancel
 *
 * @abstract
 *		Cancel the connection. This will close the connection, and negotiate over the network
 *		if applicable for the protocol. The process of cancellation will be completed
 *		asynchronously, and the final callback event delivered to the caller will be a state
 *		update with a value of nw_listener_state_cancelled. Once this update is delivered, the
 *		caller may clean up any associated memory or objects.
 *
 *		Outstanding sends and receives will receive errors before the state changes to cancelled.
 *		There is no guarantee that any outstanding sends that have not yet delivered send completion handlers
 *		will send data before the connection is closed.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_cancel(nw_connection_t connection);

/*!
 * @function nw_connection_force_cancel
 *
 * @abstract
 *		A variant of nw_connection_cancel() that indicates that the protocol stack should
 *		not close gracefully, but close as quickly as possible without negotiation. For example,
 *		a force close would lead to TCP RST packets being sent, as opposed to negotiating with
 *		FIN packets.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_force_cancel(nw_connection_t connection);

/*!
 * @function nw_connection_cancel_current_endpoint
 *
 * @abstract
 *		Cancel the currently connected endpoint, causing the connection
 *		to fall through to the next endpoint if available, or fail if no
 *		more endpoints are available. This is primarily useful for connections
 *		which do not have reliable handshakes, such as UDP. If data is sent
 *		on the connection with no response, canceling the current endpoint
 *		will allow another address or interface to be attempted.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_cancel_current_endpoint(nw_connection_t connection);

#ifdef __BLOCKS__

/*!
 * @typedef nw_connection_receive_completion_t
 * @abstract
 *		A receive completion is invoked exactly once for a call to nw_connection_receive().
 *		The completion indicates that the requested content has been received (in which case
 *		the content is delivered), or else an error has occurred.
 *
 * @param content
 *		The received content, which has a length constrained by the call to nw_connection_receive().
 *		The content may be NULL in two cases: (1) the receive context (logical message) is now complete,
 *		and the callback is only delivering the completed event; or, (2) the connection encountered
 *		an error and there is no data to deliver. Note that the content may be non-NULL even in the
 *		case of an error if there was some data received before the error was encountered. The caller
 *		should process all content it receives, and not necessarily ignore data in case of errors.
 *
 * @param context
 *		The context (logical message) associated with the received content. This includes protocol metadata
 *		that lets the caller introspect information about the received content (such as flags on an IP packet).
 *		When the message has been completely received, the context will be delivered along with the
 *		is_complete flag.
 *
 *		For datagram protocols such as UDP, the context represents the properties of a single received
 *		datagram.
 *
 *		For protocols that only have a single context for the entire connection, such as stream protocols
 *		like TCP, the context will be marked as "final", which can be accessed with
 *		nw_content_context_get_is_final(). Once a final context is marked as complete, the recipient
 *		may assume that the connection has been closed in the receiving direction (a "read close"). For
 *		TCP, this represents receiving a FIN.
 *
 * @param is_complete
 *		An indication that this context (logical message) is now complete. Until this flag is
 *		set, the recipient should assume that there may be more bytes to read for this context.
 *		Note that even when reading datagrams, as from UDP, the context may be read in multiple
 *		chunks if the maximum_length was smaller than the full length of the message.
 *
 *		If is_complete is marked and the received context is the final context for connection,
 *		the caller may assume that the connection has been closed in the receiving direction.
 *
 * @param error
 *		An error will be sent if an error was encountered while trying to receive on the connection.
 *		There may still be content delivered along with the error, but this content may be shorter
 *		than the requested ranges. An error will be sent for any outstanding receive calls when the
 *		connection is cancelled.
 */
typedef void (^nw_connection_receive_completion_t)(_Nullable dispatch_data_t content,
												   _Nullable nw_content_context_t context,
												   bool is_complete,
												   _Nullable nw_error_t error);
/*!
 * @function nw_connection_receive
 *
 * @abstract
 *		Receive data from a connection. This may be called before the connection
 *		is ready, in which case the receive request will be queued until the
 *		connection is ready. The completion handler will be invoked exactly
 *		once for each call, so the client must call this function multiple
 *		times to receive multiple chunks of data. For protocols that
 *		support flow control, such as TCP, calling receive opens the receive
 *		window. If the client stops calling receive, the receive window will
 *		fill up and the remote peer will stop sending.
 *
 * @param connection
 *		The connection object on which to receive data. The connection should
 *		be in the ready state.
 *
 * @param minimum_incomplete_length
 *		The minimum length to receive from the connection, until the content
 *		is complete. Content will be delivered when at least the minimum is available,
 *		or the content is complete, whichever comes first.
 *
 * @param maximum_length
 *		The maximum length to receive from the connection.
 *
 * @param completion
 *		A callback to be called when content has been received.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_receive(nw_connection_t connection,
					  uint32_t minimum_incomplete_length,
					  uint32_t maximum_length,
					  nw_connection_receive_completion_t completion);

/*!
 * @function nw_connection_receive_message
 *
 * @abstract
 *		Receive a single atomic message from a connection. The completion
 *		handler will be invoked exactly once for each call, so the client
 *		must call this function multiple times to receive multiple messages.
 *
 * @param connection
 *		The connection object on which to receive the message. The connection
 *		should be in the ready state.
 *
 * @param completion
 *		A callback to be called when the message has been received, or an error
 *		has occurred.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_receive_message(nw_connection_t connection,
							  nw_connection_receive_completion_t completion);

/*!
 * @typedef nw_connection_send_completion_t
 * @abstract
 *		A send completion is invoked exactly once for a call to nw_connection_send().
 *		The completion indicates that the sent content has been processed by the stack
 *		(not necessarily that it has left the host), or else an error has occurred during
 *		sending.
 *
 * @param error
 *		An error will be sent if the associated content could not be fully sent before an
 *		error occurred. An error will be sent for any outstanding sends when the connection
 *		is cancelled.
 */
typedef void (^nw_connection_send_completion_t)(_Nullable nw_error_t error);

#define NW_CONNECTION_SEND_TYPE_DECL(name) \
	extern const nw_connection_send_completion_t _nw_connection_send_##name

/*!
 * @const NW_CONNECTION_SEND_IDEMPOTENT_CONTENT
 * @discussion A send callback override that causes the write call to
 *		be treated as idempotent. Idempotent content is allowed to be sent
 *		before the connection is ready, and may be replayed across parallel connection
 *		attempts. This content can be sent as part of fast-open protocols, which allows
 *		the data to be sent out sooner than if it were required to wait for
 *		connection establishment.
 *
 *		This override intentionally disallows the client from receiving callbacks
 *		for the write calls, since the content may be sent multiple times internally.
 *		For any large content, or content that need to be sensitive to sending backpressure,
 *		an explicit callback should be used.
 */
#define NW_CONNECTION_SEND_IDEMPOTENT_CONTENT (_nw_connection_send_idempotent_content)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONNECTION_SEND_TYPE_DECL(idempotent_content);

#define NW_CONTENT_CONTEXT_TYPE_DECL(name) \
	extern const nw_content_context_t _nw_content_context_##name

/*!
 * @const NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT
 * @discussion Use the default message context to send content with all default properties:
 *		default priority, no expiration, and not the final message. Marking this context
 *		as complete with a send indicates that the message content is now complete and any
 *		other messages that were blocked may be scheduled, but will not close the underlying
 *		connection. Use this context for any lightweight sends of datagrams or messages on
 *		top of a stream that do not require special properties.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT (_nw_content_context_default_message)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(default_message);

/*!
 * @const NW_CONNECTION_FINAL_MESSAGE_CONTEXT
 * @discussion Use the final message context to indicate that no more sends are expected
 *		once this context is complete. Like NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT, all
 *		properties are default. Marking a send as complete when using this context will close
 *		the sending side of the underlying connection. This is the equivalent of sending a FIN
 *		on a TCP stream.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_FINAL_MESSAGE_CONTEXT (_nw_content_context_final_send)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(final_send);

/*!
 * @const NW_CONNECTION_DEFAULT_STREAM_CONTEXT
 * @discussion Use the default stream context to indicate that this sending context is
 *		the one that represents the entire connection. All context properties are default.
 *		This context behaves in the same way as NW_CONNECTION_FINAL_MESSAGE_CONTEXT, such
 *		that marking the context complete by sending is_complete will close the sending
 *		side of the underlying connection (a FIN for a TCP stream).
 *
 *		Note that this context is a convenience for sending a single, final context.
 *		If the protocol used by the connection is a stream (such as TCP), the caller
 *		may still use NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT, NW_CONNECTION_FINAL_MESSAGE_CONTEXT,
 *		or a custom context with priorities and metadata to set properties of a particular
 *		chunk of stream data relative to other data on the stream.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_DEFAULT_STREAM_CONTEXT (_nw_content_context_default_stream)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(default_stream);

/*!
 * @function nw_connection_send
 *
 * @abstract
 *		Send data on a connection. This may be called before the connection is ready,
 *		in which case the send will be enqueued until the connection is ready to send.
 *		This is an asynchronous send and the completion block can be used to
 *		determine when the send is complete. There is nothing preventing a client
 *		from issuing an excessive number of outstanding sends. To minmize memory
 *		footprint and excessive latency as a consequence of buffer bloat, it is
 *		advisable to keep a low number of outstanding sends. The completion block
 *		can be used to pace subsequent sends.
 *
 * @param connection
 *		The connection object on which to send data.
 *
 * @param content
 *		A data object to send. This may be NULL only if this send is marking a context
 *		(a message or complete connection) as complete in the sending direction.
 *
 * @param context
 *		The context associated with the content, which represents a logical message
 *		to be sent on the connection. All content sent within a single context will
 *		be sent as an in-order unit, up until the point that the context is marked
 *		complete (see is_complete). Once a context is marked complete, it may be re-used
 *		as a new logical message. Protocols like TCP that cannot send multiple
 *		independent messages at once (serial streams) will only start processing a new
 *		context once the prior context has been marked complete.
 *
 *		The context can hold protocol metadata to define how to send content, such
 *		as flags for IP packets.
 *
 *		The context also can define properties that allow a message to ordered relative
 *		to other messages if multiple messages are queued. These properties include
 *		relative priority, expiration, and antecedent relationships. Some protocols
 *		support re-ordering messages within a single connection. For other protocols
 *		that do not, like TCP, these properties still take effect when enqueuing data
 *		into the stream's send buffer. The ordering of messages applies to the first
 *		calls to send on a given context.
 *
 *		In order to close a connection on the sending side (a "write close"), send
 *		a context that is marked as "final" and mark is_complete. The convenience definition
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT may be used to define the default final context
 *		for a connection. If the caller wants to treat the entire connection as a single
 *		stream, with only one context, set NW_CONNECTION_FINAL_MESSAGE_CONTEXT for all
 *		sends; marking is_complete on the final send call will send a "write close".
 *		Using NW_CONNECTION_DEFAULT_STREAM_CONTEXT has the same behavior as sending
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT.
 *
 *		To send basic datagrams on a connection, use NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT
 *		and pass is_complete as true for each datagram.
 *
 *		To send data as a single stream on a connection, use NW_CONNECTION_DEFAULT_STREAM_CONTEXT
 *		and pass is_complete as true only to mark the end of the stream.
 *
 * @param is_complete
 *		A flag indicating if the caller's sending context (logical message) is now complete.
 *
 *		Until a context is marked complete, content sent for other contexts may not
 *		be sent immediately (if the protocol requires sending bytes serially, like TCP).
 *
 *		For datagram protocols, like UDP, is_complete indicates that the content represents
 *		a complete datagram.
 *
 *		When sending directly on streaming protocols like TCP, is_complete can be used to
 *		indicate that the connection should send a "write close" (a TCP FIN) if the sending
 *		context is the final context on the connection. Specifically, to send a "write close",
 *		pass NW_CONNECTION_FINAL_MESSAGE_CONTEXT or NW_CONNECTION_DEFAULT_STREAM_CONTEXT for the
 *		context (or create a custom context and set nw_content_context_set_is_final()), and pass
 *		true for is_complete.
 *
 * @param completion
 *		A callback to be called when the data has been sent, or an error has occurred.
 *		This callback does not indicate that the remote side has acknowledged the data.
 *		This callback does indicate that the data has either been sent or it has been
 *		enqueued to be sent.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_send(nw_connection_t connection,
				   _Nullable dispatch_data_t content,
				   nw_content_context_t context,
				   bool is_complete,
				   nw_connection_send_completion_t completion);

/*!
 * @function nw_connection_batch
 *
 * @abstract
 *		Batch several send and/or receive operations together, to hint to
 *		the connection that multiple send or recieve operations are expected
 *		in quick succession.
 *
 * @param connection
 *		The connection object.
 *
 * @param batch_block
 *		The batch block will be invoked immediately upon calling this function.
 *		The client may call nw_connection_send() or nw_connection_receive()
 *		multiple times within the block, and the connection will attempt to
 *		batch these operations when the block returns.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_batch(nw_connection_t connection,
					NW_NOESCAPE dispatch_block_t batch_block);

#endif // __BLOCKS__

/*!
 * @function nw_connection_copy_description
 *
 * @abstract
 *		Copy a human-readable description of the connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a human-readable string description of the connection.
 *		The caller must call free() on the string.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_connection_copy_description(nw_connection_t connection);

/*!
 * @function nw_connection_copy_current_path
 *
 * @abstract
 *		Copy the current path for a connection. If a connection is
 *		established, this will reflect the connected path.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a retained path object, or NULL if the connection
 *		has not been started or has been cancelled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_path_t
nw_connection_copy_current_path(nw_connection_t connection);

/*!
 * @function nw_connection_copy_protocol_metadata
 *
 * @abstract
 *		Copy the connection-wide metadata for a specific protocol.
 *		This allows the caller to introspect per-protocol state,
 *		only once the connection has been established. This
 *		metadata is also available when receiving data through
 *		the content context.
 *
 * @param connection
 *		The connection object.
 *
 * @param definition
 *		The protocol definition for which metadata will be returned.
 *
 * @result
 *		Returns a retained protocol metadata object, or NULL if the connection
 *		has not been established yet, or is cancelled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_metadata_t
nw_connection_copy_protocol_metadata(nw_connection_t connection,
									 nw_protocol_definition_t definition);

/*!
 * @function nw_connection_get_maximum_datagram_size
 *
 * @abstract
 *		Check for the maximum datagram size that can be written
 *		on the connection. Any datagrams written should be less
 *		than or equal to this size.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a datagram size based on the current MTU and the
 *		overhead of the protocols being used.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_connection_get_maximum_datagram_size(nw_connection_t connection);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_CONNECTION_H__ */
// ==========  Network.framework/Headers/error.h
//
//  error.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ERROR_H__
#define __NW_ERROR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <dns_sd.h>

#include <CoreFoundation/CoreFoundation.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_error_t
 * @abstract
 *		A network error object with a domain and error code.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ERROR_IMPL
NW_OBJECT_DECL(nw_error);
#endif // NW_ERROR_IMPL


/*!
 * @typedef nw_error_domain_t
 * @abstract
 *		The enumeration of network error domains.
 */
typedef enum {
	/*! @const nw_error_domain_invalid */
	nw_error_domain_invalid = 0,
	/*! @const nw_error_domain_posix The error code will be a POSIX error as defined in <sys/errno.h> */
	nw_error_domain_posix = 1,
	/*! @const nw_error_domain_dns The error code will be a DNSServiceErrorType error as defined in <dns_sd.h> */
	nw_error_domain_dns = 2,
	/*! @const nw_error_domain_tls The error code will be a TLS error as defined in <Security/SecureTransport.h> */
	nw_error_domain_tls = 3
} nw_error_domain_t;

/*!
 * @function nw_error_get_error_domain
 *
 * @abstract
 *		Given a reference to a nw_error, returns the error domain.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The error domain.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_error_domain_t
nw_error_get_error_domain(nw_error_t error);

/*!
 * @function nw_error_get_error_code
 *
 * @abstract
 *		Given a reference to a nw_error, returns the error code.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The error code.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
int
nw_error_get_error_code(nw_error_t error);

/*!
 * @const kNWErrorDomainPOSIX
 * @abstract CFErrorRef domain corresponding to nw_error_domain_posix.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainPOSIX; // Values will be POSIX errors

/*!
 * @const kNWErrorDomainDNS
 * @abstract CFErrorRef domain corresponding to nw_error_domain_posix.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainDNS; // Values will be DNSServiceErrorType errors

/*!
 * @const kNWErrorDomainTLS
 * @abstract CFErrorRef domain corresponding to nw_error_domain_tls.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainTLS; // Values will be errSSL* errors

/*!
 * @function nw_error_copy_cf_error
 *
 * @abstract
 *		Given a reference to nw_error, returns a CFErrorRef representing the same error.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The CFErrorRef. The caller is responsible for calling CFRelease on the returned value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
CFErrorRef
nw_error_copy_cf_error(nw_error_t error);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_ERROR_H__ */
// ==========  Network.framework/Headers/advertise_descriptor.h
//
//  advertise_descriptor.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ADVERTISE_DESCRIPTOR_H__
#define __NW_ADVERTISE_DESCRIPTOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/txt_record.h>

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>

NW_ASSUME_NONNULL_BEGIN
__BEGIN_DECLS

/*!
 * @typedef nw_advertise_descriptor_t
 * @abstract
 *		An Advertise Descriptor is an abstract classification of properties
 *		that may be used to advertise a service, such as a Bonjour service type.
 */
#ifndef NW_SERVICE_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_advertise_descriptor);
#endif // NW_SERVICE_DESCRIPTOR_IMPL

/*!
 * @function nw_advertise_descriptor_create_bonjour_service
 *
 * @abstract
 *		Creates a new advertise descriptor object based on a Bonjour service type
 *		and optional domain. This object can be used with listener objects to
 *      specify the service the listener should advertise.
 *
 *      If the name is unspecified, the default name for the device will be used.
 *      If the domain is unspecified, the default domains for registration will be
 *      used. If the listener is local only, the domain 'local.' will be used
 *      regardless of the parameter passed to domain.
 *
 * @param name
 *		An optional Bonjour service name.
 *
 * @param type
 *		A Bonjour service type.
 *
 * @param domain
 *		An optional Bonjour service domain.
 *
 * @result
 *		An instantiated browse descriptor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_advertise_descriptor_t _Nullable
nw_advertise_descriptor_create_bonjour_service(const char * _Nullable name, const char * type, const char * _Nullable domain);

/*!
 * @function nw_advertise_descriptor_set_txt_record
 *
 * @abstract
 *		Set the TXT record for the advertise descriptor's service. You must call
 *      nw_listener_set_advertise_descriptor to update the listener's advertising
 *      afterwards in order for these changes to take effect.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify.
 *
 * @param txt_record
 *		A pointer to the TXT record.
 *
 * @param txt_length
 *		The length of the TXT record. The total size of a typical DNS-SD TXT record
 *		is intended to be small - 200 bytes or less. Using TXT records larger than
 *		1300 bytes is not recommended at this time.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_txt_record(nw_advertise_descriptor_t advertise_descriptor,
									   const void * _Nullable txt_record,
									   size_t txt_length);

/*!
 * @function nw_advertise_descriptor_set_no_auto_rename
 *
 * @abstract
 *		Disable auto-rename for the Bonjour service registration.
 *		Auto-rename is enabled by default.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify.
 *
 * @param no_auto_rename
 *		A boolean indicating if auto-rename should be disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor,
										   bool no_auto_rename);

/*!
 * @function nw_advertise_descriptor_get_no_auto_rename
 *
 * @abstract
 *		Check if auto-rename has been disabled for the Bonjour service
 *		registration.
 *
 * @param advertise_descriptor
 *		The advertise descriptor object.
 *
 * @result A boolean indicating if auto-rename is disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_advertise_descriptor_get_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor);

/*!
 * @function nw_advertise_descriptor_set_txt_record_object
 *
 * @abstract
 *		Set the TXT record object on the advertise descriptor.
 *
 * @param advertise_descriptor
 *		The advertise descriptor object.
 *
 * @param txt_record
 *		The TXT record object. If txt_record is NULL, the advertise_descriptor's
 *		current TXT record object will be removed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_advertise_descriptor_set_txt_record_object(nw_advertise_descriptor_t advertise_descriptor,
											  _Nullable nw_txt_record_t txt_record);

/*!
* @function nw_advertise_descriptor_copy_txt_record_object
*
* @abstract
*		Copies the TXT record object from the advertise descriptor.
*
* @param advertise_descriptor
*		The advertise descriptor object.
*
* @result
*		A copy of the TXT record object, or NULL if the advertise descriptor
*		does not have an associated TXT record.
*/
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_advertise_descriptor_copy_txt_record_object(nw_advertise_descriptor_t advertise_descriptor);

__END_DECLS
NW_ASSUME_NONNULL_END

#endif /* __NW_ADVERTISE_DESCRIPTOR_H__ */
// ==========  Network.framework/Headers/endpoint.h
//
//  endpoint.h
//  Network
//
//  Copyright (c) 2014-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ENDPOINT_H__
#define __NW_ENDPOINT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/interface.h>
#include <Network/txt_record.h>

#include <stdint.h>
#include <sys/socket.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_endpoint_t
 * @abstract
 *		A Network Endpoint is an abstract static representation of a local or remote
 *		network entity. Endpoints indicate specific instances that connections may
 *		be created between, such as Hostname + Port pairs, IP Address + Port pairs,
 *		and named Bonjour Services.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ENDPOINT_IMPL
NW_OBJECT_DECL(nw_endpoint);
#endif // NW_ENDPOINT_IMPL

/*!
 * @typedef nw_endpoint_type_t
 * @abstract
 *		Endpoint types represent a well-known form of endpoint. Values may be
 *		added to this enumeration, and some custom endpoint types may use
 *		values not defined in this enumeration.
 */
typedef enum {
	/*! @const nw_endpoint_type_invalid An invalid endpoint */
	nw_endpoint_type_invalid = 0,
	/*! @const nw_endpoint_type_address An IP Address + Port */
	nw_endpoint_type_address = 1,
	/*! @const nw_endpoint_type_host A Hostname + Port */
	nw_endpoint_type_host = 2,
	/*! @const nw_endpoint_type_bonjour_service A Bonjour Service Name + Type + Domain */
	nw_endpoint_type_bonjour_service = 3,
	/*! @const nw_endpoint_type_url A URL endpoint */
	nw_endpoint_type_url = 4,
} nw_endpoint_type_t;

/*!
 * @function nw_endpoint_get_type
 *
 * @abstract
 *		Retrieves the type of a network endpoint.
 *
 * @param endpoint
 *		The endpoint object for which to get the type.
 *
 * @result
 *		Returns the type of the network endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_endpoint_type_t
nw_endpoint_get_type(nw_endpoint_t endpoint);

#pragma mark - Host Endpoints

/*!
 * @function nw_endpoint_create_host
 *
 * @abstract
 *		Creates a network endpoint with a hostname and port. The hostname
 *		may be a string-encoding of an IP address, in which case the
 *		the endpoint will be treated as an endpoint with the type
 *		nw_endpoint_type_address. Otherwise, the endpoint will have the
 *		type nw_endpoint_type_host.
 *
 * @param hostname
 *		A hostname, such as "www.example.com", or "2607:ffff::1234:abcd".
 *
 * @param port
 *		A port number as a C string, such as "443", or a service
 *		name, such as "https".
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_host(const char *hostname, const char *port);

/*!
 * @function nw_endpoint_get_hostname
 *
 * @abstract
 *		Retrieves the hostname string for a network endpoint with
 *		the type nw_endpoint_type_host or nw_endpoint_type_url.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the hostname string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_host.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_hostname(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_copy_port_string
 *
 * @abstract
 *		Returns an allocated port string for a network endpoint with
 *		the type nw_endpoint_type_host or nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the port string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_host or
 *		nw_endpoint_type_address. This string must be freed with free().
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_endpoint_copy_port_string(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_port
 *
 * @abstract
 *		Retrieves the port for a network endpoint with the type
 *		nw_endpoint_type_url, nw_endpoint_type_host, or nw_endpoint_type_address.
 *		The port will be returned in Host Byte Order.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the port for the endpoint, or 0 if the endpoint is not
 *		of type nw_endpoint_type_host or nw_endpoint_type_address.
 *		The port will be returned in Host Byte Order.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint16_t
nw_endpoint_get_port(nw_endpoint_t endpoint);

#pragma mark - Address Endpoints

/*!
 * @function nw_endpoint_create_address
 *
 * @abstract
 *		Creates a network endpoint with a sockaddr struct. The endpoint
 *		will have the type nw_endpoint_type_address.
 *
 * @param address
 *		An address stored as a sockaddr.
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_address(const struct sockaddr *address);

/*!
 * @function nw_endpoint_copy_address_string
 *
 * @abstract
 *		Returns an allocated IP address string for a network endpoint with
 *		the type nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the IP address string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_address.
 *		This string must be freed with free().
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_endpoint_copy_address_string(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_address
 *
 * @abstract
 *		Retrieves the sockaddr struct for a network endpoint with
 *		the type nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the sockaddr struct for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_address.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const struct sockaddr *
nw_endpoint_get_address(nw_endpoint_t endpoint);

#pragma mark - Bonjour Service Endpoints

/*!
 * @function nw_endpoint_create_bonjour_service
 *
 * @abstract
 *		Creates a network endpoint for a Bonjour Service name, type, and
 *		domain. The endpoint will have the type nw_endpoint_type_bonjour_service.
 *
 * @param name
 *		The Bonjour Service name, such as "example".
 *
 * @param type
 *		The Bonjour Service type, such as "_http._tcp".
 *
 * @param domain
 *		The Bonjour Service domain, such as "local".
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_bonjour_service(const char *name, const char *type, const char *domain);

/*!
 * @function nw_endpoint_get_bonjour_service_name
 *
 * @abstract
 *		Retrieves the Bonjour Service name string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service name string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_name(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_bonjour_service_type
 *
 * @abstract
 *		Retrieves the Bonjour Service type string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service type string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_type(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_bonjour_service_domain
 *
 * @abstract
 *		Retrieves the Bonjour Service domain string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service domain string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_domain(nw_endpoint_t endpoint);

#pragma mark - URL Endpoints

/*!
 * @function nw_endpoint_create_url
 *
 * @abstract
 *		Creates a network endpoint with a URL. The endpoint will have the type
 *		nw_endpoint_type_url.
 *
 * @param url
 *		The URL string.
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters, or due to URL parsing failure.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_url(const char *url);

/*!
 * @function nw_endpoint_get_url
 *
 * @abstract
 *		Retrieves the URL string from a network endpoint of type
 *		nw_endpoint_type_url.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		The URL string, or NULL if the endpoint is not of type
 *		nw_endpoint_type_url.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char *
nw_endpoint_get_url(nw_endpoint_t endpoint);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_ENDPOINT_H__
// ==========  Network.framework/Headers/udp_options.h
//
//  udp_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_UDP_OPTIONS_H__
#define __NW_UDP_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_udp_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of UDP (User Datagram Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the transport protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_udp_definition(void);

#pragma mark - Options

/*!
 * @function nw_udp_create_options
 *
 * @abstract
 *		Create an instance of UDP protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_udp_create_options(void);

/*!
 * @function nw_udp_options_set_prefer_no_checksum
 *
 * @abstract
 *		Configure UDP to skip computing checksums when sending.
 *		This will only take effect when running over IPv4.
 *
 * @param options
 *		A UDP protocol options object.
 *
 * @param prefer_no_checksum
 *		A boolean that indicates if UDP is allowed to skip computing
 *		its checksum.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_udp_options_set_prefer_no_checksum(nw_protocol_options_t options,
									  bool prefer_no_checksum);

#pragma mark - Metadata

/*!
 * @function nw_udp_create_metadata
 *
 * @abstract
 *		Create an instance of UDP metadata that can be used
 *		to configure per-datagram options when sending data
 *		on a connection.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_udp_create_metadata(void);

/*!
 * @function nw_protocol_metadata_is_udp
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of UDP.
 *
 * @result
 *		Returns true if the metadata is for the default system UDP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_udp(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_UDP_OPTIONS_H__
// ==========  Network.framework/Headers/listener.h
//
//  listener.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_LISTENER_H__
#define __NW_LISTENER_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/connection.h>
#include <Network/advertise_descriptor.h>
#include <Network/error.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_listener_t
 * @abstract
 *		A Network Listener is an object that is able to receive incoming nw_connection_t
 *		objects by binding to a local endpoint. A listener will accept connections based
 *		on the protocols defined in its stack. For transport listeners (such as TCP and UDP),
 *		accepted connections will represent new local and remote address and port tuples.
 *		For listeners that include higher-level protocols that support multiplexing,
 *		accepted connections will represent multiplexed streams on a new or existing transport
 *		binding.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_LISTENER_IMPL
NW_OBJECT_DECL(nw_listener);
#endif // NW_LISTENER_IMPL

/*!
 * @typedef nw_listener_state_t
 * @abstract
 *		Listener states sent by nw_listener_set_state_changed_handler.
 *		States progress forward and do not move backwards.
 */
typedef enum {
	/*!
	 *	@const nw_listener_state_invalid The state of the listener is not valid. This state
	 *		will never be delivered in the listener's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_listener_state_invalid = 0,
	/*! @const nw_listener_state_waiting The listener is waiting for a usable network before being able to receive connections */
	nw_listener_state_waiting = 1,
	/*! @const nw_listener_state_ready The listener is ready and able to accept incoming connections */
	nw_listener_state_ready = 2,
	/*! @const nw_listener_state_failed The listener has irrecoverably closed or failed */
	nw_listener_state_failed = 3,
	/*! @const nw_listener_state_cancelled The listener has been cancelled by the caller */
	nw_listener_state_cancelled = 4,
} nw_listener_state_t;

/*!
 * @function nw_listener_create_with_port
 *
 * @abstract
 *		Creates a networking listener bound to a specified local port.
 *
 * @param port
 *		A port number as a C string, such as "443", or a service
 *		name, such as "https".
 *
 * @param parameters
 *		The parameters to use for the listener. These include the protocols to be
 *		used for the listener.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create_with_port(const char *port, nw_parameters_t parameters);

/*!
 * @function nw_listener_create
 *
 * @abstract
 *		Creates a networking listener. The listener will be assigned a random
 *		port upon which to listen unless otherwise specified by the parameters.
 *
 * @param parameters
 *		The parameters to use for the listener. These include the protocols to be
 *		used for the listener.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create(nw_parameters_t parameters);

/*!
 * @function nw_listener_create_with_connection
 *
 * @abstract
 *		Creates a networking listener based on an existing
 *		multiplexing connection. If there are multiple protocols
 *		in the connection that support listening for incoming flows,
 *		the listener will be hooked up the highest in the stack
 *		(the closest to the reading and writing of the client data).
 *
 * @param connection
 *		An existing connection that has a multiplexing protocol
 *		that supports receiving new connections.
 *
 * @param parameters
 *		The parameters to use for the listener. The protocol stack
 *		defined in the parameters must be able to join a protocol
 *		in the connection that supports listening protocols.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success. Use nw_release() to deallocate.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create_with_connection(nw_connection_t connection,
								   nw_parameters_t parameters);

/*!
 * @function nw_listener_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_listener_start().
 *
 * @param listener
 *		The listener object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_queue(nw_listener_t listener,
					  dispatch_queue_t queue);

#ifdef __BLOCKS__

typedef void (^nw_listener_state_changed_handler_t)(nw_listener_state_t state, _Nullable nw_error_t error);

/*!
 * @function nw_listener_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		connection has been cancelled, the nw_listener_state_cancelled state will
 *		be delivered last.
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The state changed handler to call when the listener state changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_state_changed_handler(nw_listener_t listener,
									  _Nullable nw_listener_state_changed_handler_t handler);

/*!
 * @typedef nw_listener_new_connection_handler_t
 *
 * @abstract
 *		The block called to notify client of a new connection.
 *
 * @param connection
 *		The new connection object. This connection is not yet started. Set the
 *		event handler and other settings on the connection before calling start.
 */
typedef void (^nw_listener_new_connection_handler_t)(nw_connection_t connection);

/*!
 * @function nw_listener_set_new_connection_handler
 *
 * @abstract
 *		Sets the client new connection handler. Must be called before
 *		nw_listener_start.
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The event handler to call when the listener receives a new connection.
 *		Pass NULL to remove the new connection handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_new_connection_handler(nw_listener_t listener,
									   _Nullable nw_listener_new_connection_handler_t handler);

#endif // __BLOCKS__

/*!
 * @define NW_LISTENER_INFINITE_CONNECTION_LIMIT
 * @discussion This value indicates that a listener should not limit incoming connections
 */
#define NW_LISTENER_INFINITE_CONNECTION_LIMIT UINT32_MAX

/*!
 * @function nw_listener_get_new_connection_limit
 *
 * @abstract
 *		Gets the listener new connection limit. The default value is
 *      NW_LISTENER_INFINITE_CONNECTION_LIMIT which indicates that
 *      the listener should not limit incoming connections. If the value
 *      is not NW_LISTENER_INFINITE_CONNECTION_LIMIT, it will be decremented
 *      by 1 every time a new connection is created. When the value becomes
 *      0, new connection handlers will no longer be invoked until
 *      nw_listener_set_new_connection_limit() is invoked with a value
 *      that is greater than 0. Incoming connections will eventually be rejected
 *      if nw_listener_set_new_connection_limit() is not called after the connection
 *      limit reaches 0.
 *
 * @param listener
 *		The listener object.
 *
 * @result
 *		Returns current new connection limit
 */
API_AVAILABLE(macos(10.15), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_listener_get_new_connection_limit(nw_listener_t listener);

/*!
 * @function nw_listener_set_new_connection_limit
 *
 * @abstract
 *		Sets the listener new connection limit. Use the value NW_LISTENER_INFINITE_CONNECTION_LIMIT
 *      to disable connection limits. If the value is not NW_LISTENER_INFINITE_CONNECTION_LIMIT,
 *      it will be decremented by 1 every time a new connection is created. When the value becomes
 *      0, new connection handlers will no longer be invoked until
 *      nw_listener_set_new_connection_limit() is invoked with a value
 *      that is greater than 0. Incoming connections will eventually be rejected
 *      if nw_listener_set_new_connection_limit() is not called after the connection
 *      limit reaches 0.
 *
 * @param listener
 *		The listener object.
 *
 * @param new_connection_limit
 *		The new connection limit. Pass NW_LISTENER_INFINITE_CONNECTION_LIMIT
 *      to disable new connection limiting.
 */
API_AVAILABLE(macos(10.15), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_new_connection_limit(nw_listener_t listener,
									 uint32_t new_connection_limit);

/*!
 * @function nw_listener_set_advertise_descriptor
 *
 * @abstract
 *		Describes the bonjour service the listener should register. Setting the
 *		advertise descriptor more than once may be used to update the TXT record.
 *
 * @param listener
 *		The listener object.
 *
 * @param advertise_descriptor
 *		The advertise_descriptor or NULL to prevent or remove registration of a service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_advertise_descriptor(nw_listener_t listener,
									 _Nullable nw_advertise_descriptor_t advertise_descriptor);

#ifdef __BLOCKS__

/*!
 * @typedef nw_listener_advertised_endpoint_changed_handler_t
 *
 * @abstract
 *		A block called to notify client of a change in advertised endpoints.
 *
 * @param advertised_endpoint
 *		An endpoint that is has been added or removed from the list of advertised
 *		endpoints for the listener.
 *
 * @param added
 *		A boolean indicating if the endpoint is being added or removed. If added,
 *		the value with be true; if removed, the value will be false.
 */
typedef void (^nw_listener_advertised_endpoint_changed_handler_t)(nw_endpoint_t advertised_endpoint,
																  bool added);

/*!
 * @function nw_listener_set_advertised_endpoint_changed_handler
 *
 * @abstract
 *		Sets the client advertised endpoint changed handler. The handler will be
 *		invoked for listeners which have called nw_listener_set_advertise_descriptor().
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The event handler to call when the listener adds or removes an advertised endpoint.
 *		Pass NULL to remove the handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_advertised_endpoint_changed_handler(nw_listener_t listener,
													_Nullable nw_listener_advertised_endpoint_changed_handler_t handler);

#endif // __BLOCKS__

/*!
 * @function nw_listener_get_port
 *
 * @abstract
 *		Gets the local port as a number in host byte order. If the listener was created with a
 *		port of 0 (let the system assign a port), nw_listener_get_port will return 0 until the
 *		listener is in the ready state.
 *
 * @param listener
 *		The listener to get the local port of.
 *
 * @result
 *		Returns a port in host byte order.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint16_t
nw_listener_get_port(nw_listener_t listener);

/*!
 * @function nw_listener_start
 *
 * @abstract
 *		Starts the listener, which will cause the listener
 *		to start listening for inbound connections.
 *
 * @param listener
 *		The listener object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_start(nw_listener_t listener);

/*!
 * @function nw_listener_cancel
 *
 * @abstract
 *		Cancel the listener. This will de-register the listener from the system. The process
 *		of cancellation will be completed asynchronously, and the final callback event
 *		delivered to the caller will be a state update with a value of nw_listener_state_cancelled.
 *		Once this update is delivered, the caller may clean up any associated memory or objects.
 *
 * @param listener
 *		The listener object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_cancel(nw_listener_t listener);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_LISTENER_H__ */
// ==========  Network.framework/Headers/browse_descriptor.h
//
//  browse_descriptor.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSE_DESCRIPTOR_H__
#define __NW_BROWSE_DESCRIPTOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <dispatch/dispatch.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browse_descriptor_t
 * @abstract
 *		A Browse Descriptor describes the service for which to browse. Examples
 *		include Bonjour service types, or devices owned by the same account.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSE_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_browse_descriptor);
#endif // NW_BROWSE_DESCRIPTOR_IMPL

/*!
 * @function nw_browse_descriptor_create_bonjour_service
 *
 * @abstract
 *		Creates a new browse descriptor object on a Bonjour service type and
 *		domain.
 *
 * @param type
 *		A Bonjour service type.
 *
 * @param domain
 *		An optional Bonjour service domain. If the domain is unspecified, the
 *		default domains for browsing will be used.
 *
 * @result
 *		An instantiated browse descriptor object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browse_descriptor_t
nw_browse_descriptor_create_bonjour_service(const char *type,
											const char * _Nullable domain);

/*!
 * @function nw_browse_descriptor_get_bonjour_service_type
 *
 * @abstract
 *		Returns the service type of a browse descriptor.
 *
 * @param descriptor
 *		A browse descriptor object.
 *
 * @result
 *		The service type.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char *
nw_browse_descriptor_get_bonjour_service_type(nw_browse_descriptor_t descriptor);

/*!
 * @function nw_browse_descriptor_get_bonjour_service_domain
 *
 * @abstract
 *		Returns the service domain of a browse descriptor, or NULL if NULL was
 *		provided while creating the descriptor.
 *
 * @param descriptor
 *		A browse descriptor object.
 *
 * @result
 *		The service domain.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char * _Nullable
nw_browse_descriptor_get_bonjour_service_domain(nw_browse_descriptor_t descriptor);

/*!
 * @function nw_browse_descriptor_set_include_txt_record
 *
 * @abstract
 *		Set a flag to allow or prohibit the browser from querying for TXT records
 *		while browsing. This flag should only be set if the client needs information
 *		from the TXT record during browsing, and may increase network traffic. By
 *		default, the browser will not automatically query for TXT records.
 *
 * @param descriptor
 *		The browse descriptor object.
 *
 * @param include_txt_record
 *		A flag indicating whether results should include a TXT record. If true,
 *		the browser will query for TXT records. If false, the browser will not
 *		query for TXT records.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browse_descriptor_set_include_txt_record(nw_browse_descriptor_t descriptor, bool include_txt_record);

/*!
 * @function nw_browse_descriptor_get_include_txt_record
 *
 * @abstract
 *		Check whether the browser is allowed to query for TXT records.
 *
 * @param descriptor
 *		The browse descriptor to check.
 *
 * @result
 *		Whether the browser is allowed to query for TXT records.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_browse_descriptor_get_include_txt_record(nw_browse_descriptor_t descriptor);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_BROWSE_DESCRIPTOR_H__
// ==========  Network.framework/Headers/path.h
//
//  path.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_H__
#define __NW_PATH_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/endpoint.h>
#include <Network/interface.h>
#include <Network/nw_object.h>

#include <stdbool.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_path_t
 * @abstract
 *		A Network Path object represents a snapshot of network path state. This state
 *		represents the known information about the local interface and routes that may
 *		be used to send and receive data. If the network path for a connection changes
 *		due to interface characteristics, addresses, or other attributes, a new nw_path_t
 *		object will be generated. Note that the differences in the path attributes may not
 *		be visible through public accessors, and these changes should be treated merely
 *		as an indication that something about the network has changed.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PATH_IMPL
NW_OBJECT_DECL(nw_path);
#endif // NW_PATH_IMPL

/*!
 * @typedef nw_path_status_t
 * @abstract
 *		A network path status indicates if there is a usable route available upon which to
 *		send and receive data.
 */
typedef enum {
	/*! @const nw_path_status_invalid The path is not valid */
	nw_path_status_invalid = 0,
	/*! @const nw_path_status_satisfied The path has a usable route upon which to send and receive data */
	nw_path_status_satisfied = 1,
	/*! @const nw_path_status_unsatisfied The path does not have a usable route. This may be due to a network interface being down, or due to system policy.  */
	nw_path_status_unsatisfied = 2,
	/*! @const nw_path_status_satisfiable The path does not currently have a usable route, but a connection attempt will trigger network attachment */
	nw_path_status_satisfiable = 3,
} nw_path_status_t;

/*!
 * @function nw_path_get_status
 *
 * @abstract
 *		Retrieves the status of a path. The status of a specific path object will never
 *		change, as the path object itself is static. If there is a network change, the
 *		object that generated the path object will generate a new path object.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns the status of the path, or nw_path_status_invalid if the object is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_path_status_t
nw_path_get_status(nw_path_t path);

#ifdef __BLOCKS__

typedef bool (^nw_path_enumerate_interfaces_block_t)(nw_interface_t interface);

/*!
 * @function nw_path_enumerate_interfaces
 *
 * @abstract
 *		List all interfaces associated with the path.
 *
 * @param path
 *		The path object to check.
 *
 * @param enumerate_block
 *		A block that will return the interfaces associated with the path. Returning
 *		true from the block will continue to enumerate, and returning false will stop
 *		enumerating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_enumerate_interfaces(nw_path_t path,
							 NW_NOESCAPE nw_path_enumerate_interfaces_block_t enumerate_block);

#endif // __BLOCKS__

/*!
 * @function nw_path_is_equal
 *
 * @abstract
 *		Compares two network path objects and checks if their content is equal.
 *		If they are not equal, they represent two different network states.
 *
 * @param path
 *		The first path object to compare.
 *
 * @param other_path
 *		The second path object to compare.
 *
 * @result
 *		Returns true if the paths are equivalent, or false if there is any difference
 *		between the paths.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_is_equal(nw_path_t path, nw_path_t other_path);

/*!
 * @function nw_path_is_expensive
 *
 * @abstract
 *		Checks if the path uses any network interfaces that are considered expensive
 *		to the user, such as, but not limited to, a cellular network.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface that is considered expensive,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_is_expensive(nw_path_t path);

/*!
 * @function nw_path_is_constrained
 *
 * @abstract
 *		Checks if the path uses any network interfaces that are considered constrained
 *		to the user.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface that is considered constrained,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_path_is_constrained(nw_path_t path);

/*!
 * @function nw_path_has_ipv4
 *
 * @abstract
 *		Checks if the path uses a network interface that supports IPv4 connectivity.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses a network interface that supports IPv4,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_ipv4(nw_path_t path);

/*!
 * @function nw_path_has_ipv6
 *
 * @abstract
 *		Checks if the path uses a network interface that supports IPv6 connectivity.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses a network interface that supports IPv6,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_ipv6(nw_path_t path);

/*!
 * @function nw_path_has_dns
 *
 * @abstract
 *		Checks if the path has a DNS server configuration set.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path has a DNS server configuration set,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_dns(nw_path_t path);

/*!
 * @function nw_path_uses_interface_type
 *
 * @abstract
 *		Checks if the path uses a network interface with the specified type.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface with the specified type,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_uses_interface_type(nw_path_t path,
							nw_interface_type_t interface_type);

/*!
 * @function nw_path_copy_effective_local_endpoint
 *
 * @abstract
 *		Retrieve the local endpoint that is being used, if present. If this path
 *		is the path from an nw_connection_t, it represents the address that data
 *		is sent from.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns an endpoint that is assigned as the local endpoint for this path,
 *		or NULL if the path does not have a fixed local endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_path_copy_effective_local_endpoint(nw_path_t path);

/*!
 * @function nw_path_copy_effective_remote_endpoint
 *
 * @abstract
 *		Retrieve the remote endpoint that is being used, if present. If this path
 *		is the path from an nw_connection_t, it represents the address that data
 *		is sent to.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns an endpoint that is assigned as the remote endpoint for this path,
 *		or NULL if the path does not have a fixed remote endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_path_copy_effective_remote_endpoint(nw_path_t path);

#ifdef __BLOCKS__

typedef bool (^nw_path_enumerate_gateways_block_t)(nw_endpoint_t gateway);

/*!
 * @function nw_path_enumerate_gateways
 *
 * @abstract
 *		List the IP addresses of the routers acting as the gateways for the path.
 *
 * @param path
 *		The path object to check.
 *
 * @param enumerate_block
 *		A block that will return the gateways associated with the path. Returning
 *		true from the block will continue to enumerate, and returning false will stop
 *		enumerating.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_path_enumerate_gateways(nw_path_t path,
						   NW_NOESCAPE nw_path_enumerate_gateways_block_t enumerate_block);

#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_H__) */

// ==========  Network.framework/Headers/content_context.h
//
//  content_context.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_CONTENT_CONTEXT_H__
#define __NW_CONTENT_CONTEXT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/nw_object.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_content_context_t
 * @abstract
 *		A Content Context represents a set of metadata associated with the act of
 *		sending or receiving data on a connection.
 *
 *		The number of contexts that will exist on a single connection will vary
 *		based on the protocol used by the connection. Protocols that present a
 *		byte-stream abstraction will have a single context in each direction
 *		(send and receive); protocols that present a datagram or message-based
 *		abstraction will have many contexts, one per datagram or message. The
 *		granularity of contexts will always represent the highest-level protocol
 *		in the connection. To be specific, if a byte-stream protocol is running
 *		a datagram protocol (such as TCP over IP), there will only be one context
 *		in each direction, as dictated by TCP; whereas if a message-based protocol
 *		is running over a byte-stream protocol (such as a framing protocol over TCP),
 *		there will be one context for each framed message.
 *
 *		When sending content, the context also allows the client of the API to specify
 *		how the content should be treated relative to other content on the connection,
 *		via priority, expiration, and dependencies.
 *
 *		A context may contain one or more metadata handles to set or access protocol-
 *		specific data associated with the content.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_CONTENT_CONTEXT_IMPL
NW_OBJECT_DECL(nw_content_context);
#endif // NW_CONTENT_CONTEXT_IMPL

/*!
 * @function nw_content_context_create
 * @discussion Create a context object to represent properties associated with
 *		networking content. If the same context object is associated with multiple
 *		content blobs, then those pieces of content will be considered to be continuations
 *		of the same message.
 * @param context_identifier A string description of the context
 * @result Returns a new context context object
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_content_context_t
nw_content_context_create(const char *context_identifier);

/*!
 * @function nw_content_context_get_identifier
 * @discussion Access the identifier description.
 * @result Returns the context's identifier string.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_content_context_get_identifier(nw_content_context_t context);

/*!
 * @function nw_content_context_get_is_final
 * @discussion Check if this is the final context for a connection. When receiving,
 *		once this context is complete, the connection is "read closed" and will not
 *		receive more content. See nw_content_context_set_is_final() for a description
 *		of how to set is_final for sending contexts.
 * @param context The context object
 * @result Returns true if the context is the final context for a connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_content_context_get_is_final(nw_content_context_t context);

/*!
 * @function nw_content_context_set_is_final
 * @discussion Mark whether or not this context is the final context for a
 *		connection. When sending, marking a context as final will perform
 *		a "write close" once the context is complete, indicating that no more content
 *		will be sent. As a convenience for sending a final context, use
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT.
 * @param context The context object
 * @param is_final If set to true, mark the context as the final context to send on a connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_is_final(nw_content_context_t context,
								bool is_final);

/*!
 * @function nw_content_context_get_expiration_milliseconds
 * @discussion Retrieve the number of milliseconds after which the content will expire.
 *		See nw_content_context_set_expiration_milliseconds for futher discussion.
 * @param context The context object
 * @result Returns content expiration, or 0 if not set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint64_t
nw_content_context_get_expiration_milliseconds(nw_content_context_t context);

/*!
 * @function nw_content_context_set_expiration_milliseconds
 * @discussion Set an expiration (in milliseconds) after which content may be dropped.
 *		If the expiration time is reached, the content may not be sent. If the value is
 *		0, there is no expiration for the content. The expiration timer starts when the
 *		content is enqueued using nw_connection_send().
 * @param context The context object
 * @param expiration_milliseconds The number of milliseconds after which content will expire
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_expiration_milliseconds(nw_content_context_t context,
											   uint64_t expiration_milliseconds);

/*!
 * @function nw_content_context_get_relative_priority
 * @discussion Get the relative priority for the content. See
 *		nw_content_context_set_relative_priority for futher discussion.
 * @param context The context object
 * @result Returns the relative priority, between 0.0 (lowest priority)
 *		to 1.0 (highest priority). The default value is 0.5.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
double
nw_content_context_get_relative_priority(nw_content_context_t context);

/*!
 * @function nw_content_context_set_relative_priority
 * @discussion Set A relative priority of the content, compared to other
 *		content on the same connection. Priorities range from 0.0 (lowest
 *		priority) to 1.0 (highest priority), where content with higher
 *		priority will scheduled first if all else is equal.
 *		The default value is 0.5.
 * @param context The context object
 * @param relative_priority The relative priority of the content, between
 *		0.0 (lowest priority) to 1.0 (highest priority).
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_relative_priority(nw_content_context_t context,
										 double relative_priority);

/*!
 * @function nw_content_context_set_antecedent
 * @discussion Set a context as an antecedent to this content context.
 *		The associated content will not be sent until all of its antecedents have been
 *		completed. If any of the antecedents fail with an error, this content will
 *		fail as well.
 * @param context The context object
 * @param antecendent_context A context associated with content that should precede
 *		this content.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_antecedent(nw_content_context_t context,
								  _Nullable nw_content_context_t antecendent_context);

/*!
 * @function nw_content_context_copy_antecedent
 * @discussion Copy the optional content context that must be sent prior to this
 *		content. See nw_content_context_set_antecedent for further discussion.
 * @param context The context object
 * @result Returns a context object set as the antecedent, or NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_content_context_t
nw_content_context_copy_antecedent(nw_content_context_t context);

/*!
 * @function nw_content_context_set_metadata_for_protocol
 * @discussion Set protocol-specific metadata to a parent content context. If
 *		metadata for the same protocol is set multiple times, the most recently
 *		set metadata will be applied.
 * @param context The context context parent object
 * @param protocol_metadata The per-protocol metadata context object to set
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_metadata_for_protocol(nw_content_context_t context,
											 nw_protocol_metadata_t protocol_metadata);

/*!
 * @function nw_content_context_copy_protocol_metadata
 * @discussion Copy the per-protocol metadata from a parent content context
 * @param context The context context parent object
 * @param protocol The definition identifier of the protocol to retrieve metadata for
 * @result Returns the metadata registered for the protocol, or NULL if there is none
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
_Nullable NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_content_context_copy_protocol_metadata(nw_content_context_t context,
										  nw_protocol_definition_t protocol);

#ifdef __BLOCKS__
/*!
 * @function nw_content_context_foreach_protocol_metadata
 * @discussion Access all per-protocol metadata objects from a parent content context
 * @param context The context context parent object
 * @param foreach_block A block in which protocol definition and metadata will be sent
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_foreach_protocol_metadata(nw_content_context_t context,
											 void (^foreach_block)(nw_protocol_definition_t definition,
																   nw_protocol_metadata_t metadata));
#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_CONTENT_CONTEXT_H__
// ==========  Network.framework/Headers/tls_options.h
//
//  tls_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_TLS_OPTIONS_H__
#define __NW_TLS_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <Security/Security.h>
#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_tls_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of TLS (Transport Layer Security). This protocol can be used
 *		as part of a connection's protocol stack as an application protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_tls_definition(void);

#pragma mark - Options

/*!
 * @function nw_tls_create_options
 *
 * @abstract
 *		Create an instance of TLS protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_tls_create_options(void);

/*!
 * @function nw_tls_copy_sec_protocol_options
 *
 * @abstract
 *		Access the sec_protocol_options_t for a given network protocol
 *		options instance. See <Security/SecProtocolOptions.h> for functions
 *		to futher configure security options.
 *
 * @param options
 *		An nw_protocol_options_t that has been created for TLS.
 *
 * @result
 *		Returns a retained sec_protocol_options_t object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED sec_protocol_options_t
nw_tls_copy_sec_protocol_options(nw_protocol_options_t options);

#pragma mark - Metadata

/*!
 * @function nw_protocol_metadata_is_tls
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of TLS.
 *
 * @result
 *		Returns true if the metadata is for the default system TLS,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_tls(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tls_copy_sec_protocol_metadata
 *
 * @abstract
 *		Access the sec_protocol_metadata_t for a given network protocol
 *		metadata instance. See <Security/SecProtocolMetadata.h> for functions
 *		to access security properties.
 *
 * @param metadata
 *		An nw_protocol_metadata_t for the TLS protocol.
 *
 * @result
 *		Returns a retained sec_protocol_metadata_t object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED sec_protocol_metadata_t
nw_tls_copy_sec_protocol_metadata(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_UDP_OPTIONS_H__
// ==========  Network.framework/Headers/ws_options.h
//
//  ws_options.h
//  libnetcore
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_WS_OPTIONS_H__
#define __NW_WS_OPTIONS_H__

#ifndef __NW_INDIRECT__
#error "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/error.h>
#include <Network/protocol_options.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

# pragma mark - WebSocket Constants

/*!
 * @typedef nw_ws_opcode_t
 * @abstract
 *		WebSocket opcodes that denote the type of frame sent or received by
 *		a WebSocket endpoint. Opcodes define the interpretation of their
 *		associated payload data.
 */
typedef enum {

	/*!
	 *	@const nw_ws_opcode_invalid Denotes an invalid frame.
	 */
	nw_ws_opcode_invalid = -1,

	/*!
	 *	@const nw_ws_opcode_cont Denotes a continuation frame.
	 */
	nw_ws_opcode_cont = 0x0,

	/*!
	 *	@const nw_ws_opcode_text Denotes a text frame.
	 */
	nw_ws_opcode_text = 0x1,

	/*!
	 *	@const nw_ws_opcode_text Denotes a binary frame.
	 */
	nw_ws_opcode_binary = 0x2,

	/*!
	 *	@const nw_ws_opcode_text Denotes a close frame.
	 */
	nw_ws_opcode_close = 0x8,

	/*!
	 *	@const nw_ws_opcode_text Denotes a ping frame.
	 */
	nw_ws_opcode_ping = 0x9,

	/*!
	 *	@const nw_ws_opcode_text Denotes a pong frame.
	 */
	nw_ws_opcode_pong = 0xA,

} nw_ws_opcode_t;

/*!
 * @typedef nw_ws_close_code_t
 * @abstract
 *		WebSocket close codes that describe the reason for closing a WebSocket
 *		connection. Endpoints MAY use the following pre-defined status codes
 *		when sending a Close frame.
 */
typedef enum {
	/*!
	 *	@const nw_ws_close_code_normal_closure Indicates a normal closure,
	 *		meaning that the purpose for which the connection was established
	 *		has been fulfilled.
	 */
	nw_ws_close_code_normal_closure = 1000,

	/*!
	 *	@const nw_ws_close_code_normal_going_away Indicates that an endpoint is
	 *		"going away", such as a server going down or a browser having
	 *		navigated away from a page.
	 */
	nw_ws_close_code_going_away = 1001,

	/*!
	 *	@const nw_ws_close_code_protocol_error Indicates that an endpoint is
	 *		terminating the connection due to a protocol error.
	 */
	nw_ws_close_code_protocol_error = 1002,

	/*!
	 *	@const nw_ws_close_code_normal_closure Indicates that an endpoint is
	 *		terminating the connection because it has received a type of data
	 *		it cannot accept (e.g., an endpoint that understands only text data
	 *		MAY send this if it receives a binary message).
	 */
	nw_ws_close_code_unsupported_data = 1003,

	/*!
	 *	@const nw_ws_close_code_no_status_received A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint. It
	 *		is designated for use in applications expecting a status code to
	 *		indicate that no status code was actually present.
	 */
	nw_ws_close_code_no_status_received = 1005,

	/*!
	 *	@const nw_ws_close_code_abnormal_closure A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint.
	 *		It is designated for use in applications expecting a status code to
	 *		indicate that the connection was closed abnormally, e.g., without
	 *		sending or receiving a Close control frame.
	 */
	nw_ws_close_code_abnormal_closure = 1006,

	/*!
	 *	@const nw_ws_close_code_invalid_frame_payload_data Indicates that an
	 *		endpoint is terminating the connection because it has received data
	 *		within a message that was not consistent with the type of the
	 *		message (e.g., non-UTF-8 [RFC3629] data within a text message).
	 */
	nw_ws_close_code_invalid_frame_payload_data = 1007,

	/*!
	 *	@const nw_ws_close_code_policy_violation Indicates that an endpoint is
	 *		terminating the connection because it has received a message that
	 *		violates its policy. This is a generic status code that can be
	 *		returned when there is no other more suitable status code (e.g.,
	 *		1003 or 1009) or if there is a need to hide specific details about
	 *		the policy.
	 */
	nw_ws_close_code_policy_violation = 1008,

	/*!
	 *	@const nw_ws_close_code_message_too_big Indicates that an endpoint is
	 *		terminating the connection because it has received a message that
	 *		is too big for it to process.
	 */
	nw_ws_close_code_message_too_big = 1009,

	/*!
	 *	@const nw_ws_close_code_mandatory_extension Indicates that an endpoint
	 *		(client) is terminating the connection because it has expected the
	 *		server to negotiate one or more extensions, but the server didn't
	 *		return them in the response message of the WebSocket handshake. The
	 *		list of extensions that are needed SHOULD appear in the /reason/
	 *		part of the Close frame. Note that this status code is not used by
	 *		the server, because it can fail the WebSocket handshake instead.
	 */
	nw_ws_close_code_mandatory_extension = 1010,

	/*!
	 *	@const nw_ws_close_code_internal_server_error Indicates that a server is
	 *		terminating the connection because it encountered an unexpected
	 *		condition that prevented it from fulfilling the request.
	 */
	nw_ws_close_code_internal_server_error = 1011,

	/*!
	 *	@const nw_ws_close_code_tls_handshake A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint. It
	 *		is designated for use in applications expecting a status code to
	 *		indicate that the connection was closed due to a failure to perform
	 *		a TLS handshake (e.g., the server certificate can't be verified).
	 */
	nw_ws_close_code_tls_handshake = 1015,
} nw_ws_close_code_t;

/*!
 * @typedef nw_ws_version_t
 * @abstract
 *		The WebSocket Protocol version.
 */
typedef enum {
	/*! @const nw_ws_version_invalid An invalid WebSocket version */
	nw_ws_version_invalid = 0,
	/*! @const nw_ws_version_13 WebSocket v13 as defined in RFC 6455 */
	nw_ws_version_13 = 1,
} nw_ws_version_t;

# pragma mark - WebSocket Definition

/*!
 * @function nw_protocol_copy_ws_definition
 *
 * @abstract
 *		Access the definition of the default system implementation of the
 *		WebSocket protocol. This protocol can be appended to a connection's
 *		protocol stack.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_ws_definition(void);

# pragma mark - WebSocket Options

/*!
 * @function nw_ws_create_options
 *
 * @abstract
 *		Create an instance of WebSocket protocol options. This object can be
 *		added to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_ws_create_options(nw_ws_version_t version);

/*!
 * @function nw_ws_options_add_additional_header
 *
 * @abstract
 *		Set additional HTTP headers to be sent by the client during the
 *		WebSocket handshake.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param name
 *		The HTTP header name.
 *
 * @param value
 *		The HTTP header value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_add_additional_header(nw_protocol_options_t options,
									const char *name, const char *value);

/*!
 * @function nw_ws_options_add_subprotocol
 *
 * @abstract
 *		Add to the list of subprotocols that will be presented to a
 *		WebSocket server during connection establishment.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param subprotocol
 *		The subprotocol supported by the client.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_add_subprotocol(nw_protocol_options_t options,
							  const char *subprotocol);

/*!
 * @function nw_ws_options_set_auto_reply_ping
 *
 * @abstract
 *		Set whether the WebSocket connection should automatically reply to all
 *		incoming pings.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param auto_reply_ping
 *		Whether the WebSocket connection should automatically reply to all
 *		incoming pings.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_auto_reply_ping(nw_protocol_options_t options,
								  bool auto_reply_ping);

/*!
 * @function nw_ws_options_set_skip_handshake
 *
 * @abstract
 *		Set whether the WebSocket protocol should skip the opening handshake
 *		and begin framing data as soon as a connection is established.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param skip_handshake
 *		Whether the WebSocket connection should skip the opening handshake.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_skip_handshake(nw_protocol_options_t options, bool skip_handshake);

/*!
 * @function nw_ws_options_set_maximum_message_size
 *
 * @abstract
 *		Set the maximum allowed message size to be received by the WebSocket
 *		connection. This does not limit the sending message size.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param maximum_message_size
 *		The maximum message size in bytes. A maximum message size of 0 means
 *		there is no receive limit. The default maximum message size is 0.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_maximum_message_size(nw_protocol_options_t options,
									   size_t maximum_message_size);

# pragma mark - WebSocket Metadata

/*!
 * @function nw_protocol_metadata_is_ws
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of WebSocket.
 *
 * @result
 *		Returns true if the metadata is for the default system
 *		implementation of WebSocket, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_protocol_metadata_is_ws(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ws_create_metadata
 *
 * @abstract
 *		Creates a protocol metadata object that can be used to define the
 *		content context of messages sent over a WebSocket connection.
 *
 * @param opcode
 *		Set the opcode on a WebSocket frame. This must be defined on create.
 *
 * @result
 *		Returns a retained metadata object representing the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_ws_create_metadata(nw_ws_opcode_t opcode);

/*!
 * @function nw_ws_metadata_get_opcode
 *
 * @abstract
 *		Get the opcode on a WebSocket frame.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @result
 *		The opcode on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_opcode_t
nw_ws_metadata_get_opcode(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ws_metadata_set_close_code
 *
 * @abstract
 *		Set the close code on a WebSocket frame. The WebSocket frame's opcode
 *		should be nw_ws_opcode_close.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @param close_code
 *		The close code on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_metadata_set_close_code(nw_protocol_metadata_t metadata, nw_ws_close_code_t close_code);

/*!
 * @function nw_ws_metadata_get_close_code
 *
 * @abstract
 *		Get the close code from a WebSocket frame. If the close code is equal
 *		to nw_ws_close_code_no_status_received, it means that a close code
 *		was not actually present in the WebSocket frame.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @result
 *		The close code on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_close_code_t
nw_ws_metadata_get_close_code(nw_protocol_metadata_t metadata);

#ifdef __BLOCKS__

/*!
 * @typedef nw_ws_pong_handler_t
 *
 * @abstract
 *		A block to be invoked when a pong reply is received after sending a ping
 *		message, or if the WebSocket connection has closed or failed.
 *
 * @param error
 *		An optional error if the WebSocket connection fails or closes before a
 *		pong reply is received.
 */
typedef void (^nw_ws_pong_handler_t)(nw_error_t _Nullable error);

/*!
 * @function nw_ws_metadata_set_pong_handler
 *
 * @abstract
 *		Set a callback that will notify the client when a pong message has been
 *		received for a ping message sent. The metadata object's associated
 *		opcode should be nw_ws_opcode_ping.
 *
 * @param metadata
 *		The WebSocket metadata object.
 *
 * @param client_queue
 *		The queue on which the pong handler will be delivered.
 *
 * @param pong_handler
 *		The handler that gets called when a pong reply is received.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_metadata_set_pong_handler(nw_protocol_metadata_t metadata,
								dispatch_queue_t client_queue,
								nw_ws_pong_handler_t pong_handler);

#endif // __BLOCKS__

# pragma mark - WebSocket Request

/*!
 * @typedef nw_ws_request_t
 * @abstract
 *		A WebSocket request represents a client's request to connect to a WebSocket
 *		server.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_WS_REQUEST_IMPL
NW_OBJECT_DECL(nw_ws_request);
#endif // NW_WS_REQUEST_IMPL

#ifdef __BLOCKS__

/*!
 * @typedef nw_ws_subprotocol_enumerator_t
 *
 * @abstract
 *		A block that can be applied to every subprotocol in a client's WebSocket
 *		request.
 *
 * @param subprotocol
 *		A subprotocol presented by the client.
 *
 * @result
 *		A boolean value that indicating if enumeration should continue.
 */
typedef bool (^nw_ws_subprotocol_enumerator_t)(const char *subprotocol);

/*!
 * @function nw_ws_request_enumerate_subprotocols
 *
 * @abstract
 *		Enumerates the list of subprotocols on the client's request.
 *
 * @param request
 *		The client request.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_request_enumerate_subprotocols(nw_ws_request_t request,
									 NW_NOESCAPE nw_ws_subprotocol_enumerator_t enumerator);

/*!
 * @typedef nw_ws_additional_header_enumerator_t
 *
 * @abstract
 *		A block that can be applied to every additional header in a client's
 *		WebSocket request.
 *
 * @param name
 *		The HTTP name.
 *
 * @param value
 *		The HTTP value.
 */
typedef bool (^nw_ws_additional_header_enumerator_t)(const char *name,
													 const char *value);

/*!
 * @function nw_ws_request_enumerate_additional_headers
 *
 * @abstract
 *		Enumerates the list of additional headers on the client's request.
 *
 * @param request
 *		The client request.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_request_enumerate_additional_headers(nw_ws_request_t request,
										   NW_NOESCAPE nw_ws_additional_header_enumerator_t enumerator);

#endif // __BLOCKS__

# pragma mark - WebSocket Response

/*!
 * @typedef nw_ws_response_t
 * @abstract
 *		A WebSocket response represents a server's response to a client's request
 *		to connect.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_WS_RESPONSE_IMPL
NW_OBJECT_DECL(nw_ws_response);
#endif // NW_WS_RESPONSE_IMPL

/*!
 * @typedef nw_ws_response_status_t
 * @abstract
 *		The status of a WebSocket server's response to a client's request to
 *		connect.
 */
typedef enum {

	/*!
	 *	@const nw_ws_response_status_invalid The response is invalid. This should
	 *		be treated as an unexpected value.
	 */
	nw_ws_response_status_invalid = 0,

	/*!
	 *	@const nw_ws_response_status_accept Accept the request to connect. The
	 *		WebSocket connection will begin framing data.
	 */
	nw_ws_response_status_accept = 1,

	/*!
	 *	@const nw_ws_response_status_accept Reject the request to connect. The
	 *		WebSocket connection will be closed.
	 */
	nw_ws_response_status_reject = 2,
} nw_ws_response_status_t;

/*!
 * @function nw_ws_response_create
 *
 * @abstract
 *      Create a server response to a WebSocket client's opening handshake.
 *
 * @param status
 *      The status of the response. If the status is nw_ws_response_status_accept,
 *      the server will accept the handshake and open the WebSocket connection.
 *      If the status is nw_ws_response_status_reject, the server will reject the
 *      handshake and respond with the HTTP error 400 Bad Request.
 *
 * @param selected_subprotocol
 *      The server's selected protocol from the client's list of proposed
 *		subprotocols. If the status of this response is nw_ws_response_status_reject,
 *      this parameter is ignored. Pass NULL to indicate the server did not find
 *      a suitable subprotocol, but has accepted the handshake anyways.
 *      Passing an empty string is prohibited by the WebSocket protocol.
 *
 * @result
 *      An instantiated WebSocket server response object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_ws_response_t
nw_ws_response_create(nw_ws_response_status_t status,
					  const char * _Nullable selected_subprotocol);

/*!
 * @function nw_ws_response_get_status
 *
 * @abstract
 *		Get the status from a WebSocket server's response. If the response is
 *		nil, the return value will be nw_ws_response_status_invalid.
 *
 * @param response
 *		The server response.
 *
 * @result
 *		The status of the server's response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_response_status_t
nw_ws_response_get_status(nw_ws_response_t _Nullable response);

/*!
 * @function nw_ws_response_get_selected_subprotocol
 *
 * @abstract
 *		Get the selected subprotocol from a WebSocket server's response.
 *
 * @param response
 *		The server response.
 *
 * @result
 *		The status of the server's response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char * _Nullable
nw_ws_response_get_selected_subprotocol(nw_ws_response_t response);

/*!
 * @function nw_ws_response_add_additional_header
 *
 * @abstract
 *		Add additional HTTP headers to be sent back to the WebSocket client in
 *		the server's response.
 *
 * @param response
 *		The server response.
 *
 * @param name
 *		The HTTP name.
 *
 * @param value
 *		The HTTP value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_response_add_additional_header(nw_ws_response_t response,
									 const char *name, const char *value);

/*!
 * @function nw_ws_metadata_copy_server_response
 *
 * @abstract
 *		Copy the WebSocket server's response to a client's request to connect.
 *		If this is called on a WebSocket server, the response object will contain
 *		the server's own response to the client.
 *
 * @param metadata
 *		The metadata object representing the WebSocket connection.
 *
 * @result
 *		The server response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_ws_response_t
nw_ws_metadata_copy_server_response(nw_protocol_metadata_t metadata);

#ifdef __BLOCKS__

/*!
 * @function nw_ws_response_enumerate_additional_headers
 *
 * @abstract
 *		Enumerates the list of additional headers on the server's response.
 *
 * @param response
 *		The server response.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_response_enumerate_additional_headers(nw_ws_response_t response,
											NW_NOESCAPE nw_ws_additional_header_enumerator_t enumerator);

/*!
 * @typedef nw_ws_client_request_handler_t
 *
 * @abstract
 *		A block to be invoked when a WebSocket server receives a WebSocket
 *		client's request to connect.
 *
 * @param request
 *		The client request.
 *
 * @result
 *		The server response.
 */
typedef _Nonnull nw_ws_response_t (^nw_ws_client_request_handler_t)(_Nonnull nw_ws_request_t request);

/*!
 * @typedef nw_ws_options_set_client_request_handler
 *
 * @abstract
 *		Set callback handler to be invoked when a WebSocket server receives a
 *		WebSocket client's request to connect.
 *
 * @param options
 *		The protocol options object.
 *
 * @param client_queue
 *		The queue on which the client request handler will be delivered.
 *
 * @param handler
 *		The callback handler.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_client_request_handler(nw_protocol_options_t options,
										 dispatch_queue_t client_queue,
										 nw_ws_client_request_handler_t handler);

#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_WS_OPTIONS_H__ */
// ==========  Network.framework/Headers/browser.h
//
//  browser.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSER_H__
#define __NW_BROWSER_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/parameters.h>
#include <Network/browse_descriptor.h>
#include <Network/browse_result.h>
#include <Network/error.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browser_t
 * @abstract
 *		A Network Browser may be used to browse for endpoints described by a
 *		browse descriptor and a parameters object.
 *
 *		It will asynchronously provide callbacks through the browse results changed
 *		handler as endpoints are added, removed, or changed. These endpoints are
 *		presented to the user as browse result objects, which contain additional
 *		information about each endpoint gathered during browsing.
 *
 *		The browser will report its state, which represents if it is actively
 *		browsing or if it encounters an error, through the state changed handler
 *		callback.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSER_IMPL
NW_OBJECT_DECL(nw_browser);
#endif // NW_BROWSER_IMPL

/*!
 * @typedef nw_browser_state_t
 * @abstract
 *		Browser states sent by nw_browser_set_state_changed_handler.
 *		States progress forward and do not move backwards.
 */
typedef enum {

	/*!
	 *	@const nw_browser_state_invalid The state of the browser is not valid.
	 * 		This state will never be delivered in the browser's state update
	 *		handler and can be treated as an unexpected value.
	 */
	nw_browser_state_invalid = 0,

	/*! @const nw_browser_state_ready The browser is ready and able to receive
	 *		endpoint updates. All callbacks from the browse_results_changed_handler
	 *		occur when the browser is in this state.
	 */
	nw_browser_state_ready = 1,

	/*! @const nw_browser_state_failed The browser has irrecoverably failed.
	 *		You should not try to call nw_browser_start() on the browser to restart
	 *		it. Instead, cancel the browser and create a new browser object.
	 */
	nw_browser_state_failed = 2,

	/*! @const nw_browser_state_cancelled The browser has been cancelled by
	 *		the caller. You should not try to call nw_browser_start() on the
	 *		browser to restart it. Instead, create a new browser object.
	 */
	nw_browser_state_cancelled = 3,
} nw_browser_state_t;

/*!
 * @function nw_browser_create
 *
 * @abstract
 *		Creates a new browser object, which can be used to browse for results
 *		matching a browse descriptor.
 *
 * @param descriptor
 *		A browse descriptor object that describes the type of service for which
 *		to browse.
 *
 * @param parameters
 *		Optional parameters to use for the new browser. If NULL, an empty parameters
 *		object is created internally.
 *
 * @result
 *		An instantiated browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browser_t
nw_browser_create(nw_browse_descriptor_t descriptor,
				  _Nullable nw_parameters_t parameters);

/*!
 * @function nw_browser_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 * 		be scheduled. This must be done before calling nw_browser_start().
 *
 * @param browser
 *		The browser object.
 *
 * @param queue
 *		The client's callback queue.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_queue(nw_browser_t browser,
					 dispatch_queue_t queue);

#ifdef __BLOCKS__

/*!
 * @typedef nw_browser_browse_results_changed_handler_t
 *
 * @abstract
 *		A block called to notify the user of any browse results that changed. To get
 *		the specific list of changes that occurred, call nw_browse_result_get_changes()
 *		with the old and new result.
 *
 * @param old_result
 *		The old value of the browse result. This value was previously provided to
 *		an invocation of the browse_results_changed_handler().
 *
 * @param new_result
 *		The new value of the browse result. This is a new instance of the result
 *		and replaces old_result.
 *
 * @param batch_complete
 *		A flag indicating if this is the last change in this batch. If
 *		batch_complete is true, the browser has no more immediate changes to
 *		report to the user, who should perform any pending UI updates. If
 *		batch_complete is false, the browser has more updates queued, which will
 *		be delivered in subsequent invocations of the browse_results_changed_handler().
 */
typedef void (^nw_browser_browse_results_changed_handler_t) (nw_browse_result_t old_result,
															 nw_browse_result_t new_result,
															 bool batch_complete);

/*!
 * @function nw_browser_set_browse_results_changed_handler
 *
 * @abstract
 *		Sets a callback handler to be invoked when the browser gets an update
 *		for changed browse results. This function must be called before starting
 *		the browser and must not be called after starting the browser.
 *
 * @param browser
 *		The browser object.
 *
 * @param handler
 *		The callback handler that fires when the browser gets an update for a
 *		changed browse result.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_browse_results_changed_handler(nw_browser_t browser,
												_Nullable nw_browser_browse_results_changed_handler_t handler);

/*!
 * @typedef nw_browser_state_changed_handler_t
 *
 * @abstract
 *		A block called when the browser changes state.
 *
 * @param state
 *		The new state of the browser.
 *
 * @param error
 *		An optional error that is associated with the new state. For example, if the
 *		browser encounters a DNS error, the callback will pass nw_browser_state_failed
 * 		as the new state and the DNS error as the error.
 */
typedef void (^nw_browser_state_changed_handler_t)(nw_browser_state_t state,
												   _Nullable nw_error_t error);

/*!
 * @function nw_browser_set_state_changed_handler
 *
 * @abstract
 *		Sets the state changed handler. For clients that need to perform cleanup
 *		when the browser has been cancelled, the nw_browser_state_cancelled state
 *		will be delivered last. This function must be called before starting the
 *		browser and must not be called after starting the browser.
 *
 * @param browser
 *		The browser object.
 *
 * @param state_changed_handler
 *		The state changed handler to call when the browser state changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_state_changed_handler(nw_browser_t browser,
									 _Nullable nw_browser_state_changed_handler_t state_changed_handler);

#endif // __BLOCKS__

/*!
 * @function nw_browser_start
 *
 * @abstract
 *		Starts the browser, which begins browsing for available endpoints.
 * 		You must call nw_browser_set_queue() before starting the browser.
 *
 * @param browser
 *		The browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_start(nw_browser_t browser);

/*!
 * @function nw_browser_cancel
 *
 * @abstract
 *		Cancels the browser. The process of cancellation will be completed
 *		asynchronously, and the final callback event delivered to the caller
 *		will be a state update with a value of nw_browser_state_cancelled.
 *		Once this update is delivered, the caller may clean up any associated
 *		memory or objects.
 *
 * @param browser
 *		The browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_cancel(nw_browser_t browser);

/*!
 * @function nw_browser_copy_parameters
 *
 * @abstract
 *		Returns a copy of the parameters passed to nw_browser_create().
 *
 * @param browser
 *		The browser object.
 *
 * @result
 *		Returns an nw_parameters_t object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_browser_copy_parameters(nw_browser_t browser);

/*!
 * @function nw_browser_copy_browse_descriptor
 *
 * @abstract
 *		Returns a copy of the browse_descriptor passed to nw_browser_create().
 *
 * @param browser
 *		The browser object.
 *
 * @result
 *		Returns a copy of the browse_descriptor passed to nw_browser_create().
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browse_descriptor_t
nw_browser_copy_browse_descriptor(nw_browser_t browser);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* defined(__NW_BROWSER_H__) */
// ==========  Network.framework/Headers/interface.h
//
//  interface.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//
#ifndef __NW_INTERFACE_H__
#define __NW_INTERFACE_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>

#include <stdbool.h>
#include <stdint.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_interface_t
 * @abstract
 *		A Network Interface is an object that represents a static snapshot of an interface
 *		that provides network connectivity, such as a Wi-Fi link, an Ethernet connection,
 *		a Cellular service, a VPN, or the loopback interface.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_INTERFACE_IMPL
NW_OBJECT_DECL(nw_interface);
#endif // NW_INTERFACE_IMPL

/*!
 * @typedef nw_interface_type_t
 * @abstract
 *		Interface types represent the underlying media for a network link, such as Wi-Fi or
 *		Cellular.
 */
typedef enum {
	/*! @const nw_interface_type_other A virtual or otherwise unknown interface type */
	nw_interface_type_other = 0,
	/*! @const nw_interface_type_wifi A Wi-Fi link */
	nw_interface_type_wifi = 1,
	/*! @const nw_interface_type_wifi A Cellular link */
	nw_interface_type_cellular = 2,
	/*! @const nw_interface_type_wired A Wired Ethernet link */
	nw_interface_type_wired = 3,
	/*! @const nw_interface_type_loopback The loopback interface */
	nw_interface_type_loopback = 4,
} nw_interface_type_t;

/*!
 * @function nw_interface_get_type
 *
 * @abstract
 *		Retrieves the type of an interface. This only accesses the type of the specific
 *		interface being queried, and will not take into account types used by interfaces
 *		that traffic will eventually be routed through. That is, if the interface is a virtual
 *		interface (such as a VPN) that eventually forwards traffic through Wi-Fi, the type
 *		will be nw_interface_type_other, not nw_interface_type_wifi.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the type of the interface.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_interface_type_t
nw_interface_get_type(nw_interface_t interface);

/*!
 * @function nw_interface_get_name
 *
 * @abstract
 *		Retrieves the name of an interface, to be used for reference or logging
 *		purposes.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the name of the interface as a NULL-terminated C string,
 *		or NULL if the interface is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_interface_get_name(nw_interface_t interface);

/*!
 * @function nw_interface_get_index
 *
 * @abstract
 *		Retrieves the index of an interface, to be used for reference or logging
 *		purposes. This is the same value as provided by if_nametoindex.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the index of the interface, or 0 if the interface is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_interface_get_index(nw_interface_t interface);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_INTERFACE_H__ */
// ==========  Network.framework/Headers/protocol_options.h
//
//  protocol_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_PROTOCOL_OPTIONS_H__
#define __NW_PROTOCOL_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_protocol_definition_t
 * @abstract
 *		A Network Protocol Definition is a handle that represents a protocol implementation
 *		that can be added into a protocol stack, configured, and used to tranmit data and
 *		metadata. For example, a protocol definition for TCP represents an implementation of
 *		TCP that can be used for a connection.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_DEFINITION_IMPL
NW_OBJECT_DECL(nw_protocol_definition);
#endif // NW_PROTOCOL_DEFINITION_IMPL

/*!
 * @function nw_protocol_definition_is_equal
 *
 * @abstract
 *		Compare two protocol definitions to check if they represent the same protocol.
 *
 * @param definition1
 *		The first definition to compare
 *
 * @param definition2
 *		The second definition to compare
 *
 * @result
 *		Returns true if the definitions represent the same protocol, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_definition_is_equal(nw_protocol_definition_t definition1, nw_protocol_definition_t definition2);

/*!
 * @typedef nw_protocol_options_t
 * @abstract
 *		A Network Protocol Options object holds a single definition (nw_protocol_definition_t)
 *		along with a set of protocol-specific options. The options are used to build protocol
 *		stack definitions in an nw_parameters_t object. Each protocol is responsible for
 *		defining its own accessor functions to set and get options.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_OPTIONS_IMPL
NW_OBJECT_DECL(nw_protocol_options);
#endif // NW_PROTOCOL_OPTIONS_IMPL

/*!
 * @function nw_protocol_options_copy_definition
 *
 * @abstract
 *		Retrieve the protocol definition for a given options object.
 *
 * @param options
 *		The protocol options to check
 *
 * @result
 *		Returns a reference-counted protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_options_copy_definition(nw_protocol_options_t options);

/*!
 * @typedef nw_protocol_metadata_t
 * @abstract
 *		A Network Protocol Metadata object holds a single definition (nw_protocol_definition_t)
 *		along with a set of protocol-specific metadata. This metadata allows clients to pass down
 *		protocol requirements specific to some content being sent, as well as to retrieve metadata
 *		specific to some content that was received. Each protocol is responsible for defining
 *		its own accessor functions to set and get metadata.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_METADATA_IMPL
NW_OBJECT_DECL(nw_protocol_metadata);
#endif // NW_PROTOCOL_METADATA_IMPL

/*!
 * @function nw_protocol_metadata_copy_definition
 *
 * @abstract
 *		Retrieve the protocol definition for a given metadata object.
 *
 * @param metadata
 *		The protocol metadata to check
 *
 * @result
 *		Returns a reference-counted protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_metadata_copy_definition(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_PROTOCOL_OPTIONS_H__
// ==========  Network.framework/Headers/path_monitor.h
//
//  path_monitor.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_MONITOR_H__
#define __NW_PATH_MONITOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/path.h>
#include <Network/interface.h>
#include <Network/nw_object.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_path_monitor_t
 * @abstract
 *		The Network Path Monitor allows the caller to fetch the current global path (or
 *		a path restricted to a specific network interface type). The path is delivered
 *		in a block that is called every time the network path changes.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PATH_MONITOR_IMPL
NW_OBJECT_DECL(nw_path_monitor);
#endif // NW_PATH_MONITOR_IMPL

/*!
 * @function nw_path_monitor_create
 *
 * @abstract
 *		Create a default path monitor, that will allow the enumeration of all available
 *		interfaces on the system.
 *
 * @result
 *		Returns an allocated nw_path_monitor_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_path_monitor_t
nw_path_monitor_create(void);

/*!
 * @function nw_path_monitor_create_with_type
 *
 * @abstract
 *		Create a path monitor specific to an interface type, that will allow the enumeration
 *		of any interface that matches the type on the system.
 *
 * @param required_interface_type
 *		An interface type that will filter any results that the path monitor returns.
 *
 * @result
 *		Returns an allocated nw_path_monitor_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_path_monitor_t
nw_path_monitor_create_with_type(nw_interface_type_t required_interface_type);

#ifdef __BLOCKS__

/*!
 * @typedef nw_path_monitor_cancel_handler_t
 * @abstract
 *		A block handler to be called when a path monitor is cancelled. This
 *		is used to allow clients to release any objects they have retained in
 *		association with the path monitor.
 */
typedef void (^nw_path_monitor_cancel_handler_t)(void);

/*!
 * @function nw_path_monitor_set_cancel_handler
 * @abstract
 *		Set a handler to be called on the queue provided to nw_path_monitor_set_queue
 *		once cancellation has completed. Once the cancel handler has been called, the
 *		update handler will not fire again.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param cancel_handler
 *		The block to call upon cancellation. Pass NULL to remove the cancel handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_cancel_handler(nw_path_monitor_t monitor,
								   nw_path_monitor_cancel_handler_t cancel_handler);

/*!
 * @typedef nw_path_monitor_update_handler_t
 * @abstract
 *		A block handler to be called whenever a path monitor has a new snapshot.
 *		This will be called one or more times after calling nw_path_monitor_start.
 */
typedef void (^nw_path_monitor_update_handler_t) (nw_path_t path);

/*!
 * @function nw_path_monitor_set_update_handler
 * @abstract
 *		Sets the client update handler. This block will be called with the
 *		current path when start is called and any time the path changes.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param update_handler
 *		The block to call when the path changes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_update_handler(nw_path_monitor_t monitor,
								   nw_path_monitor_update_handler_t update_handler);

#endif // __BLOCKS__

/*!
 * @function nw_path_monitor_set_queue
 * @abstract
 *		Sets the client update queue. All blocks will be scheduled on
 *		this queue. Call before calling nw_path_monitor_start.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param queue
 *		The dispatch queue on which to call the update and cancel handlers.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_queue(nw_path_monitor_t monitor, dispatch_queue_t queue);

/*!
 * @function nw_path_monitor_start
 * @abstract
 *		Starts the path monitor.
 *
 * @param monitor
 *		The path monitor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_start(nw_path_monitor_t monitor);

/*!
 * @function nw_path_monitor_cancel
 *
 * @abstract
 *		Cancel the path monitor.
 *
 * @param monitor
 *		The path monitor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_cancel(nw_path_monitor_t monitor);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_MONITOR_H__) */


// ==========  Network.framework/Headers/ip_options.h
//
//  ip_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_IP_OPTIONS_H__
#define __NW_IP_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/parameters.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_ip_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of IP (Internet Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the internet protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_ip_definition(void);

#pragma mark - Options

/*!
 * @typedef nw_ip_version_t
 * @abstract
 *		A specific version of the Internet Protocol.
 */
typedef enum {
	/*! @const nw_ip_version_any Allow any IP version */
	nw_ip_version_any = 0,
	/*! @const nw_ip_version_4 Use IP version 4 (IPv4) */
	nw_ip_version_4 = 4,
	/*! @const nw_ip_version_6 Use IP version 6 (IPv6) */
	nw_ip_version_6 = 6,
} nw_ip_version_t;

/*!
 * @function nw_ip_options_set_version
 *
 * @abstract
 *		Specify a single version of the Internet Protocol to allow.
 *		Setting this value will constrain which address endpoints can
 *		be used, and will filter DNS results during connection establishment.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param version
 *		A specific, restricted IP version.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_version(nw_protocol_options_t options,
						  nw_ip_version_t version);

/*!
 * @function nw_ip_options_set_hop_limit
 *
 * @abstract
 *		Configure the IP hop limit (or 'TTL' for IPv4).
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param hop_limit
 *		The hop limit to set on outgoing IP packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_hop_limit(nw_protocol_options_t options,
							uint8_t hop_limit);

/*!
 * @function nw_ip_options_set_use_minimum_mtu
 *
 * @abstract
 *		Configure IP to use the minimum MTU value, which
 *		is 1280 bytes for IPv6. This value has no effect for
 *		IPv4.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param use_minimum_mtu
 *		A boolean indicating that the IP should use
 *		its minimum MTU value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_use_minimum_mtu(nw_protocol_options_t options,
								  bool use_minimum_mtu);

/*!
 * @function nw_ip_options_set_disable_fragmentation
 *
 * @abstract
 *		Configure IP to disable fragmentation on outgoing
 *		packets.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param disable_fragmentation
 *		A boolean indicating that the IP should use
 *		disable fragmentation on outgoing packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_disable_fragmentation(nw_protocol_options_t options,
										bool disable_fragmentation);

/*!
 * @function nw_ip_options_set_calculate_receive_time
 *
 * @abstract
 *		Configure IP to calculate receive time for inbound
 *		packets.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param calculate_receive_time
 *		A boolean indicating that the IP packets
 *		should mark their receive time in IP metadata.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_calculate_receive_time(nw_protocol_options_t options,
										 bool calculate_receive_time);

/*!
 * @typedef nw_ip_local_address_preference_t
 * @abstract
 *		Preference for local addresses selection.
 */
typedef enum {
	/*! @const nw_ip_local_address_preference_default Use system default for address selection */
	nw_ip_local_address_preference_default = 0,
	/*! @const nw_ip_local_address_preference_temporary Prefer temporary (privacy) addresses */
	nw_ip_local_address_preference_temporary = 1,
	/*! @const nw_ip_local_address_preference_stable Prefer stable addresses */
	nw_ip_local_address_preference_stable = 2,
} nw_ip_local_address_preference_t;

/*!
 * @function nw_ip_options_set_local_address_preference
 *
 * @abstract
 *		Specify a preference for how to select local addresses for outbound
 *		connections.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param preference
 *		Preference for how to select local addresses.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ip_options_set_local_address_preference(nw_protocol_options_t options,
										   nw_ip_local_address_preference_t preference);

#pragma mark - Metadata

/*!
 * @function nw_ip_create_metadata
 *
 * @abstract
 *		Create an instance of IP metadata that can be used
 *		to configure per-packet options when sending data
 *		on a connection.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_ip_create_metadata(void);

/*!
 * @function nw_protocol_metadata_is_ip
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of IP.
 *
 * @result
 *		Returns true if the metadata is for the default system IP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_ip(nw_protocol_metadata_t metadata);

/*!
 * @typedef nw_ip_ecn_flag_t
 * @abstract
 *		ECN flags marked in IP headers to indicate congestion.
 */
typedef enum {
	/*! @const nw_ip_ecn_flag_non_ect Non ECN-Capable Transport, value 0b00*/
	nw_ip_ecn_flag_non_ect = 0,
	/*! @const nw_ip_ecn_flag_ect_0 ECN Capable Transport (0), value 0b10 */
	nw_ip_ecn_flag_ect_0 = 2,
	/*! @const nw_ip_ecn_flag_ect_1 ECN Capable Transport (1), value 0b01 */
	nw_ip_ecn_flag_ect_1 = 1,
	/*! @const nw_ip_ecn_flag_ce Congestion Experienced, value 0b11 */
	nw_ip_ecn_flag_ce = 3,
} nw_ip_ecn_flag_t;

/*!
 * @function nw_ip_metadata_set_ecn_flag
 *
 * @abstract
 *		Sets ECN flags on IP metadata. This will take effect if
 *		applied to any sent content.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @param ecn_flag
 *		The ECN flag to apply to packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_metadata_set_ecn_flag(nw_protocol_metadata_t metadata,
							nw_ip_ecn_flag_t ecn_flag);

/*!
 * @function nw_ip_metadata_get_ecn_flag
 *
 * @abstract
 *		Gets ECN flags from IP metadata. This will be set only
 *		for metadata associated with received content.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the ECN flag received from a packet.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_ip_ecn_flag_t
nw_ip_metadata_get_ecn_flag(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ip_metadata_set_service_class
 *
 * @abstract
 *		Sets service class on IP metadata. This will not generally
 *		translate into TOS or Traffic Class bits unless the network
 *		explictly supports it, but it will impact local queuing of
 *		packets.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @param service_class
 *		The service class to apply to packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_metadata_set_service_class(nw_protocol_metadata_t metadata,
								 nw_service_class_t service_class);

/*!
 * @function nw_ip_metadata_get_service_class
 *
 * @abstract
 *		Gets service class from IP metadata. This reflects the value
 *		set using nw_ip_metadata_set_service_class. It will not
 *		be received from the network.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the service class set on a packet.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_service_class_t
nw_ip_metadata_get_service_class(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ip_metadata_get_receive_time
 *
 * @abstract
 *		Access the time at which a packet was received. This is
 *		useful for calculating precise timing for round-trip-time
 *		estimates. Same as clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW).
 *
 *		The receive time will be 0 unless timestamps have been enabled
 *		using nw_ip_options_set_calculate_receive_time().
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the time that the packet was received.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint64_t
nw_ip_metadata_get_receive_time(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_IP_OPTIONS_H__
// ==========  Network.framework/Headers/parameters.h
//
//  parameters.h
//  Network
//
//  Copyright (c) 2014-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_PARAMETERS_H__
#define __NW_PARAMETERS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/interface.h>
#include <Network/endpoint.h>
#include <Network/nw_object.h>

#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_parameters_t
 * @abstract
 *		A Network Parameters object contains the parameters necessary to create
 *		a network connection or listener. Parameters include any preferences for
 *		network paths (such as requried, prohibited, and preferred networks, and local
 *		endpoint requirements); preferences for data transfer and quality of service;
 *		and the protocols to be used for a connection along with any protocol-specific
 *		options.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PARAMETERS_IMPL
NW_OBJECT_DECL(nw_parameters);
#endif // NW_PARAMETERS_IMPL

/*!
 * @typedef nw_protocol_stack_t
 * @abstract
 *		A Network Protocol Stack contains a list of protocols to use for a connection.
 *		The members of the protocol stack are nw_protocol_options_t objects, each
 *		defining which protocol to use within the stack along with any protocol-specific
 *		options. Each stack includes an array of application-level protocols, a single
 *		transport-level protocol, and an optional internet-level protocol. If the internet-
 *		level protocol is not specified, any available and applicable IP address family
 *		may be used.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_STACK_IMPL
NW_OBJECT_DECL(nw_protocol_stack);
#endif // NW_PROTOCOL_STACK_IMPL

#pragma mark - Initializers

#ifdef __BLOCKS__

typedef void (^nw_parameters_configure_protocol_block_t)(nw_protocol_options_t options);

#define NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(name) \
	extern const nw_parameters_configure_protocol_block_t _nw_parameters_configure_protocol_##name

#define NW_PARAMETERS_DEFAULT_CONFIGURATION (_nw_parameters_configure_protocol_default_configuration)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(default_configuration);

#define NW_PARAMETERS_DISABLE_PROTOCOL (_nw_parameters_configure_protocol_disable)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(disable);

/*!
 * @function nw_parameters_create_secure_tcp
 *
 * @abstract
 *		Creates a parameters object that is configured for TLS and TCP. The caller can use
 *		the default configuration for TLS and TCP, or set specific options for each protocol,
 *		or disable TLS.
 *
 * @param configure_tls
 *		A block to configure TLS. To use the default TLS configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. To disable TLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_tcp
 *		A block to configure TCP. To use the default TCP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable TCP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_secure_tcp(nw_parameters_configure_protocol_block_t configure_tls,
								nw_parameters_configure_protocol_block_t configure_tcp);

/*!
 * @function nw_parameters_create_secure_udp
 *
 * @abstract
 *		Creates a parameters object that is configured for DTLS and UDP. The caller can use
 *		the default configuration for DTLS and UDP, or set specific options for each protocol,
 *		or disable DTLS.
 *
 * @param configure_dtls
 *		A block to configure DTLS. To use the default DTLS configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. To disable DTLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_udp
 *		A block to configure UDP. To use the default UDP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable UDP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_secure_udp(nw_parameters_configure_protocol_block_t configure_dtls,
								nw_parameters_configure_protocol_block_t configure_udp);

/*!
 * @function nw_parameters_create_custom_ip
 *
 * @abstract
 *		Creates a parameters object that is configured for a custom IP protocol.
 *		This allows the caller to create connections and listeners that send
 *		and receive IP datagrams where the protocol header contained by the IP
 *		datagram is identified by the provided protocol number. Protocols already
 *		registered by the system, such as TCP and UDP, will not be allowed.
 *
 *		Calling processes must hold the "com.apple.developer.networking.custom-protocol"
 *		entitlement.
 *
 * @param custom_ip_protocol_number
 *		The protocol number identifying a protocol carried by IP, as defined
 *		in RFC 5237.
 *
 * @param configure_ip
 *		A block to configure IP. To use the default IP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable IP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_custom_ip(uint8_t custom_ip_protocol_number,
							   nw_parameters_configure_protocol_block_t configure_ip);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_create
 *
 * @abstract
 *		Creates a generic parameters object. Note that in order to use parameters
 *		with an nw_connection_t or an nw_listener_t, the parameters must have protocols
 *		added into the default nw_protocol_stack_t. Clients using standard protocol
 *		configurations should use nw_parameters_create_secure_tcp() or
 *		nw_parameters_create_secure_udp().
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create(void);

/*!
 * @function nw_parameters_copy
 *
 * @abstract
 *		Creates a deep copy of a parameters object that can be modified.
 *
 * @param parameters
 *		The existing parameters object to copy
 *
 * @result
 *		Returns a newly allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_copy(nw_parameters_t parameters);

#pragma mark - Path Selection

/*!
 * @function nw_parameters_require_interface
 *
 * @abstract
 *		Require any connections or listeners using these parameters to use
 *		the provided network interface, or none if NULL is passed.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface
 *		The interface to require for connections or listeners, or NULL to
 *		allow any interface.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_require_interface(nw_parameters_t parameters,
								_Nullable nw_interface_t interface);

/*!
 * @function nw_parameters_copy_required_interface
 *
 * @abstract
 *		Access the required network interface set on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the interface that is required by the parameters, or
 *		NULL if no interface is required.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_interface_t
nw_parameters_copy_required_interface(nw_parameters_t parameters);

/*!
 * @function nw_parameters_prohibit_interface
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		the provided network interface.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface
 *		The interface to prohibit for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_prohibit_interface(nw_parameters_t parameters,
								 nw_interface_t interface);

/*!
 * @function nw_parameters_clear_prohibited_interfaces
 *
 * @abstract
 *		Clear any interfaces that had been prohibited.
 *
 * @param parameters
 *		The parameters object to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_clear_prohibited_interfaces(nw_parameters_t parameters);

#ifdef __BLOCKS__

typedef bool (^nw_parameters_iterate_interfaces_block_t)(nw_interface_t interface);

/*!
 * @function nw_parameters_iterate_prohibited_interfaces
 *
 * @abstract
 *		List all prohibited network interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @param iterate_block
 *		A block that will return the interfaces prohibited by the parameters. Returning
 *		true from the block will continue to iterate, and returning false will stop
 *		iterating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_iterate_prohibited_interfaces(nw_parameters_t parameters,
											NW_NOESCAPE nw_parameters_iterate_interfaces_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_set_required_interface_type
 *
 * @abstract
 *		Require any connections or listeners using these parameters to use
 *		the provided network interface type.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface_type
 *		The interface type to require for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_required_interface_type(nw_parameters_t parameters,
									 nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_get_required_interface_type
 *
 * @abstract
 *		Access the required network interface type set on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the interface type that is required by the parameters, or
 *		nw_interface_type_other_t if no interface type is required.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_interface_type_t
nw_parameters_get_required_interface_type(nw_parameters_t parameters);

/*!
 * @function nw_parameters_prohibit_interface_type
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		the provided network interface type.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface_type
 *		The interface type to prohibit for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_prohibit_interface_type(nw_parameters_t parameters,
									  nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_clear_prohibited_interface_types
 *
 * @abstract
 *		Clear any interface types that had been prohibited.
 *
 * @param parameters
 *		The parameters object to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_clear_prohibited_interface_types(nw_parameters_t parameters);

#ifdef __BLOCKS__

typedef bool (^nw_parameters_iterate_interface_types_block_t)(nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_iterate_prohibited_interface_types
 *
 * @abstract
 *		List all prohibited network interface types.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @param iterate_block
 *		A block that will return the interface types prohibited by the parameters. Returning
 *		true from the block will continue to iterate, and returning false will stop
 *		iterating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_iterate_prohibited_interface_types(nw_parameters_t parameters,
												 NW_NOESCAPE nw_parameters_iterate_interface_types_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_set_prohibit_expensive
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		a network interface that is considered expensive by the system.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param prohibit_expensive
 *		If true, prohibit the use of any expensive interfaces. If false,
 *		allow expensive interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_prohibit_expensive(nw_parameters_t parameters,
									 bool prohibit_expensive);

/*!
 * @function nw_parameters_get_prohibit_expensive
 *
 * @abstract
 *		Check if the parameters prohibit expensive interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if expensive interfaces are prohibited, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_prohibit_expensive(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_prohibit_constrained
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		a network interface that is considered constrained by the system.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param prohibit_constrained
 *		If true, prohibit the use of any constrained interfaces. If false,
 *		allow constrained interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_parameters_set_prohibit_constrained(nw_parameters_t parameters,
									   bool prohibit_constrained);

/*!
 * @function nw_parameters_get_prohibit_constrained
 *
 * @abstract
 *		Check if the parameters prohibit constrained interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if constrained interfaces are prohibited, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_parameters_get_prohibit_constrained(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_reuse_local_address
 *
 * @abstract
 *		Allow any connections using these parameters to reuse
 *		local addresses already in use by other connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param reuse_local_address
 *		If true, allow the reuse of local addresses. If false,
 *		disallow the reuse of local addresses. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_reuse_local_address(nw_parameters_t parameters,
									  bool reuse_local_address);

/*!
 * @function nw_parameters_get_reuse_local_address
 *
 * @abstract
 *		Check if the parameters allow local address reuse.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if local address reuse is allowed, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_reuse_local_address(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_local_endpoint
 *
 * @abstract
 *		Specify a specific endpoint to use as the local endpoint.
 *		For connections, this will be used to initiate traffic;
 *		for listeners, this will be used for receiving incoming
 *		connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param local_endpoint
 *		The endpoint to set as the local endpoint. Pass NULL to
 *		clear the local endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_local_endpoint(nw_parameters_t parameters,
								 _Nullable nw_endpoint_t local_endpoint);

/*!
 * @function nw_parameters_copy_local_endpoint
 *
 * @abstract
 *		Extract the local endpoint set on the connection.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @result
 *		Returns the endpoint that is set in the parameters, or
 *		NULL if no local endpoint is set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_parameters_copy_local_endpoint(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_include_peer_to_peer
 *
 * @abstract
 *		Allow the inclusion of peer-to-peer interfaces when
 *		listening or establishing outbound connections. This parameter
 *		will not take effect if a specific interface is required.
 *		This parameter is applicable when advertising a Bonjour service
 *		on a listener, or connecting to a Bonjour service.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param include_peer_to_peer
 *		If true, allow advertising, resolving, and connecting over
 *		peer-to-peer interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_include_peer_to_peer(nw_parameters_t parameters,
									   bool include_peer_to_peer);

/*!
 * @function nw_parameters_get_include_peer_to_peer
 *
 * @abstract
 *		Check if the parameters allow the inclusion of
 *		peer-to-peer interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if peer-to-peer interfaces are allowed,
 *		or false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_include_peer_to_peer(nw_parameters_t parameters);

#pragma mark - Data Handling

/*!
 * @function nw_parameters_set_fast_open_enabled
 *
 * @abstract
 *		Use fast open for an outbound connection, which may be done at any
 *		protocol level. Use of fast open requires that the caller send
 *		idempotent data on the connection before the connection may move
 *		into the ready state. As a side effect, this may implicitly enable
 *		fast open for protocols in the stack, even if they did not have
 *		fast open explicitly enabled on them (such as the option to enable
 *		TCP Fast Open).
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param fast_open_enabled
 *		If true, indicate that fast open is requested and that idempotent data
 *		MUST be sent by the caller on the connection. If false,
 *		disallow the fast open at the top level protocol. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_fast_open_enabled(nw_parameters_t parameters,
									bool fast_open_enabled);

/*!
 * @function nw_parameters_get_fast_open_enabled
 *
 * @abstract
 *		Check if the parameters allow the use of fast open for the top level
 *		protocol.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if fast open is allowed for the top level protocol, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_fast_open_enabled(nw_parameters_t parameters);

/*!
 * @typedef nw_service_class_t
 * @abstract
 *		The network service class represents the network queuing priority to use
 *		for traffic generated by a connection.
 */
typedef enum {
	/*! @const nw_service_class_best_effort Default priority traffic */
	nw_service_class_best_effort = 0,
	/*! @const nw_service_class_background Bulk traffic, or traffic that can be de-prioritized behind foreground traffic */
	nw_service_class_background = 1,
	/*! @const nw_service_class_interactive_video Interactive video traffic */
	nw_service_class_interactive_video = 2,
	/*! @const nw_service_class_interactive_voice Interactive voice traffic */
	nw_service_class_interactive_voice = 3,
	/*! @const nw_service_class_responsive_data Interactive user data */
	nw_service_class_responsive_data = 4,
	/*! @const nw_service_class_signaling Bursty but short. Intolerant of delay and loss. For example, SIP. */
	nw_service_class_signaling = 5,
} nw_service_class_t;

/*!
 * @function nw_parameters_set_service_class
 *
 * @abstract
 *		Set the data service class to use for connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param service_class
 *		The service class value to use for connections. Defaults to nw_service_class_best_effort.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_service_class(nw_parameters_t parameters,
								nw_service_class_t service_class);

/*!
 * @function nw_parameters_get_service_class
 *
 * @abstract
 *		Check the service class configured on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the effective service class configured on the parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_service_class_t
nw_parameters_get_service_class(nw_parameters_t parameters);

/*!
 * @typedef nw_multipath_service_t
 * @abstract
 *		Multipath services represent the modes of multipath usage that are
 *		allowed for connections.
 */
typedef enum {
	/*! @const nw_multipath_service_disabled No multipath transport will be attempted */
	nw_multipath_service_disabled = 0,
	/*! @const nw_multipath_service_handover Only use the expensive interface when the when the primary one is not available */
	nw_multipath_service_handover = 1,
	/*! @const nw_multipath_service_interactive Use the expensive interface more aggressively to reduce latency */
	nw_multipath_service_interactive = 2,
	/*! @const nw_multipath_service_aggregate Use all available interfaces to provide the highest throughput and lowest latency */
	nw_multipath_service_aggregate = 3,
} nw_multipath_service_t;

/*!
 * @function nw_parameters_set_multipath_service
 *
 * @abstract
 *		Set the multipath service to use for connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param multipath_service
 *		The multipath service value to use for connections. Defaults to nw_multipath_service_disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_multipath_service(nw_parameters_t parameters,
									nw_multipath_service_t multipath_service);

/*!
 * @function nw_parameters_get_multipath_service
 *
 * @abstract
 *		Check the multipath service mode configured on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the multipath service configured on the parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_multipath_service_t
nw_parameters_get_multipath_service(nw_parameters_t parameters);

#pragma mark - Protocol Options

/*!
 * @function nw_parameters_copy_default_protocol_stack
 *
 * @abstract
 *		Retrieve the default protocol stack from a parameters object.
 *		Every parameters object will have a default protocol stack. For
 *		parameters created with a convenience initializer, this protocol
 *		stack will be pre-populated. For parameters created with the generic
 *		initializers, the stack will be empty.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns an nw_protocol_stack_t object that can be inspected and modified.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_stack_t
nw_parameters_copy_default_protocol_stack(nw_parameters_t parameters);

/*!
 * @function nw_protocol_stack_prepend_application_protocol
 *
 * @abstract
 *		Prepend an application-layer protocol onto the top of a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 *
 * @param protocol
 *		The protocol options to add to the stack, which contain the definition of the
 *		protocol to add.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_prepend_application_protocol(nw_protocol_stack_t stack,
											   nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_clear_application_protocols
 *
 * @abstract
 *		Remove all application-layer protocols from a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_clear_application_protocols(nw_protocol_stack_t stack);

#ifdef __BLOCKS__

typedef void (^nw_protocol_stack_iterate_protocols_block_t)(nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_iterate_application_protocols
 *
 * @abstract
 *		List all application protocols attached to a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @param iterate_block
 *		A block that will return the protocols attached to the stack.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_iterate_application_protocols(nw_protocol_stack_t stack,
												NW_NOESCAPE nw_protocol_stack_iterate_protocols_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_protocol_stack_copy_transport_protocol
 *
 * @abstract
 *		Access the transport-layer protocol used in a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @result
 *		Returns the transport protocol currently set in the protocol stack,
 *		or NULL if no transport protocol is set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_options_t
nw_protocol_stack_copy_transport_protocol(nw_protocol_stack_t stack);

/*!
 * @function nw_protocol_stack_set_transport_protocol
 *
 * @abstract
 *		Set the transport-layer protocol to use for a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 *
 * @param protocol
 *		The protocol options to set into the stack, which contain the definition of the
 *		protocol.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_set_transport_protocol(nw_protocol_stack_t stack,
										 nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_copy_internet_protocol
 *
 * @abstract
 *		Access the internet-layer protocol used in a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @result
 *		Returns the internet protocol currently set in the protocol stack,
 *		or NULL if no internet protocol is set. Note that this will generally
 *		be NULL, unless a specific IP family is being selected.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_options_t
nw_protocol_stack_copy_internet_protocol(nw_protocol_stack_t stack);

#pragma mark - Listener Options

/*!
 * @function nw_parameters_set_local_only
 *
 * @abstract
 *		Set to true to limit inbound connections to peers attached to the
 *		local link only. Defaults to false.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param local_only
 *		True to limit connections to the local link only.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_local_only(nw_parameters_t parameters,
							 bool local_only);

/*!
 * @function nw_parameters_get_local_only
 *
 * @abstract
 *		Indicates whether or not the parameters limit connections to the local
 *		link only.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if the parameters limit inbound connections to the local link.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_local_only(nw_parameters_t parameters);

#pragma mark - Proxy Options

/*!
 * @function nw_parameters_set_prefer_no_proxy
 *
 * @abstract
 *		Set to true to attempt connections without using proxies, only using any configured proxies if the connections
 * 		cannot otherwise be completed. Defaults to false.
 *
 * @param parameters
 *		The parameters to modify.
 *
 * @param prefer_no_proxy
 *		True to cause connections to be attempted without proxies.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_prefer_no_proxy(nw_parameters_t parameters, bool prefer_no_proxy);

/*!
 * @function nw_parameters_get_prefer_no_proxy
 *
 * @abstract
 *		Indicates whether or not the parameters cause connections to be attempted without proxies, only using proxies
 * 		if connections cannot otherwise be completed.
 *
 * @param parameters
 *		The parameters to get the property from.
 *
 * @result
 *		Returns true if the parameters cause connections to be attempted without proxies, only using proxies if
 *		connections cannot otherwise be completed.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_prefer_no_proxy(nw_parameters_t parameters);

#pragma mark - Resolution Options

/*!
 * @typedef nw_parameters_expired_dns_behavior_t
 * @abstract
 *		Expired DNS behavior defines whether or not a connection will allow the use
 *		of expired DNS answers during connection establishment.
 */
typedef enum {
	/*! @const nw_parameters_expired_dns_behavior_default Let the system determine whether or not to allow expired DNS answers  */
	nw_parameters_expired_dns_behavior_default = 0,
	/*! @const nw_parameters_expired_dns_behavior_allow Explicitly allow the use of expired DNS answers */
	nw_parameters_expired_dns_behavior_allow = 1,
	/*! @const nw_parameters_expired_dns_behavior_allow Explicitly prohibit the use of expired DNS answers */
	nw_parameters_expired_dns_behavior_prohibit = 2,
} nw_parameters_expired_dns_behavior_t;

/*!
 * @function nw_parameters_set_expired_dns_behavior
 *
 * @abstract
 *		Allow or prohibit the use of expired DNS answers during connection establishment.
 *		If allowed, a DNS answer that was previously returned may be re-used for new
 *		connections even after the answers are considered expired. A query for fresh answers
 *		will be sent in parallel, and the fresh answers will be used as alternate addresses
 *		in case the expired answers do not result in successful connections.
 *
 *		By default, this value is nw_parameters_expired_dns_behavior_default, which allows
 *		the system to determine if it is appropriate to use expired answers.
 *
 * @param parameters
 *		The parameters to modify.
 *
 * @param expired_dns_behavior
 *		Allow, prohibit, or use system default behavior for expired DNS answers.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_expired_dns_behavior(nw_parameters_t parameters,
									   nw_parameters_expired_dns_behavior_t expired_dns_behavior);


/*!
 * @function nw_parameters_get_expired_dns_behavior
 *
 * @abstract
 *		Check the effective expired DNS behavior of a connection.
 *		See nw_parameters_set_expired_dns_behavior() for a discussion on the use of expired
 *		DNS answers.
 *
 * @param parameters
 *		The parameters to check.
 *
 * @result
 *		Returns the current effective expired DNS answer behavior.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_parameters_expired_dns_behavior_t
nw_parameters_get_expired_dns_behavior(nw_parameters_t parameters);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PARAMETERS_H__) */
// ==========  Network.framework/Headers/Network.h
//
//  Network.h
//  Network
//
//  Copyright (c) 2014-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_H__
#define __NW_H__

#ifndef __NW_INDIRECT__
#define __NW_INDIRECT__
#define __NW_SET_INDIRECT__
#endif // __NW_INDIRECT__

#include <Network/advertise_descriptor.h>
#include <Network/browser.h>
#include <Network/browse_result.h>
#include <Network/browse_descriptor.h>
#include <Network/connection.h>
#include <Network/connection_report.h>
#include <Network/content_context.h>
#include <Network/endpoint.h>
#include <Network/ethernet_channel.h>
#include <Network/framer_options.h>
#include <Network/interface.h>
#include <Network/ip_options.h>
#include <Network/listener.h>
#include <Network/error.h>
#include <Network/parameters.h>
#include <Network/path_monitor.h>
#include <Network/path.h>
#include <Network/protocol_options.h>
#include <Network/tcp_options.h>
#include <Network/tls_options.h>
#include <Network/txt_record.h>
#include <Network/udp_options.h>
#include <Network/ws_options.h>

#ifdef __NW_SET_INDIRECT__
#undef __NW_INDIRECT__
#endif // __NW_SET_INDIRECT__

#endif // __NW_H__
// ==========  Network.framework/Headers/txt_record.h
//
//  txt_record.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_TXT_RECORD_H__
#define __NW_TXT_RECORD_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <stdlib.h>
#include <stdbool.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_txt_record_t
 * @abstract
 *		A TXT Record Object is used to provide additional information about a
 *		service during discovery. Two formats of the TXT record are supported:
 *
 *		1. A dictionary of key-value pairs as defined in RFC 1464.
 *		2. A buffer of bytes.
 *
 *		The format of a TXT Record object is defined at creation time and cannot
 *		be changed later. If the buffer provided to nw_txt_record_create_with_bytes()
 *		conforms to the key-value pair format, the TXT record object will be created
 *		as a dictionary. Otherwise, the TXT record object is created as a buffer
 *		of bytes and any key-value pair functions called on the object will fail.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_TXT_RECORD_IMPL
NW_OBJECT_DECL(nw_txt_record);
#endif // NW_TXT_RECORD_IMPL

/*!
 * @typedef nw_txt_record_find_key_t
 * @abstract
 *		An enumeration of possible find results when trying to find a key-value
 *		pair in the TXT record object.
 */
typedef enum {
	/*!
	 *	@const nw_txt_record_find_key_invalid The key is invalid. According
	 *		to RFC 1464, a key is invalid if it is an empty string, contains
	 *		non-ASCII characters, or has length greater than UINT8_MAX.
	 */
	nw_txt_record_find_key_invalid = 0,
	/*!
	 *	@const nw_txt_record_find_key_not_present The key-value pair does not exist in the TXT record.
	 */
	nw_txt_record_find_key_not_present = 1,
	/*!
	 *	@const nw_txt_record_find_key_no_value The key exists in the TXT record, but has no assigned value.
	 */
	nw_txt_record_find_key_no_value = 2,
	/*!
	 *	@const nw_txt_record_find_key_empty_value The key exists in the TXT record with an empty value.
	 */
	nw_txt_record_find_key_empty_value = 3,
	/*!
	 *	@const nw_txt_record_find_key_non_empty_value The key exists in the TXT record with a non-empty value.
	 */
	nw_txt_record_find_key_non_empty_value = 4,
} nw_txt_record_find_key_t;

/*!
 * @function nw_txt_record_create_with_bytes
 *
 * @abstract
 *		Create a new TXT record object from a buffer of bytes. If the buffer
 *		follows the key-value pair format as defined in RFC 1464, the TXT record
 *		object will be created as a dictionary. Otherwise, it is created as a
 *		TXT record buffer.
 *
 * @param txt_bytes
 *		The pointer to the buffer.
 *
 * @param txt_len
 *		The length of the buffer.
 *
 * @result
 *		An instantiated TXT record object.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 *		Returns NULL on failure. Fails if txt_bytes is NULL or if txt_len is 0.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_txt_record_t
nw_txt_record_create_with_bytes(const uint8_t * txt_bytes, size_t txt_len);

/*!
 * @function nw_txt_record_create_dictionary
 *
 * @abstract
 *		Create an empty TXT record dictionary.
 *
 * @result
 *		An empty TXT record dictionary.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_txt_record_t
nw_txt_record_create_dictionary(void);

/*!
 * @function nw_txt_record_copy
 *
 * @abstract
 *      Create a deep copy of an existing TXT record object.
 *
 * @param txt_record
 *      The TXT record object to be copied.
 *
 * @result
 *		A deep copy of the TXT record object.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_txt_record_copy(nw_txt_record_t _Nullable txt_record);

/*!
 * @function nw_txt_record_find_key
 *
 * @abstract
 *		Find a key-value pair in the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key of the key-value pair.
 *
 * @result
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_txt_record_find_key_t
nw_txt_record_find_key(nw_txt_record_t txt_record, const char *key);

#ifdef __BLOCKS__
/*!
 * @typedef nw_txt_record_access_key_t
 *
 * @abstract
 *		Access a value in the TXT record object with its key. Attempts to access
 *		or modify the TXT record object from within the block are prohibited.
 *
 * @param key
 *		The key of the value.
 *
 * @param found
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 *
 * @param value
 *		The value corresponding to the key. If the key does not exist or has no
 *		associated value, value will be NULL. Note that the bytes pointed to by
 *		value is only valid within the scope of the block.
 *
 * @param value_len
 *		The length of the value. If the key does not exist or has no associated
 *		value, value_len will be 0.
 *
 * @result
 *		An arbitrary return value defined by the user. For example, the user may
 *		want to return true if the operation succeeds.
 */
typedef bool (^nw_txt_record_access_key_t) (const char *key,
											const nw_txt_record_find_key_t found,
											const uint8_t * _Nullable value,
											const size_t value_len);

/*!
 * @function nw_txt_record_access_key
 *
 * @abstract
 *		Access a value in the TXT record object with its key. Attempts to access
 *		or modify the TXT record object from within the block are prohibited.
 *
 * @param txt_record
 *      The TXT record object.
 *
 * @param access_value
 *      The block that will be used to access the value of the given key.
 *
 * @result
 *      The return value of the access_value block. This is an arbitrary return
 *		value defined by the user.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_access_key(nw_txt_record_t txt_record, const char *key,
						 nw_txt_record_access_key_t access_value);
#endif // __BLOCKS__

/*!
 * @function nw_txt_record_set_key
 *
 * @abstract
 *		Set a key-value pair on the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key that will be inserted. If the key already exists in the TXT
 *		record object, the existing key-value pair will be replaced.
 *
 * @param value
 *		The value that will be inserted. If value is set to NULL, then the key
 *		will be inserted with no value.
 *
 * @param value_len
 *		The length of the value will be inserted. If value is set to zero, then the
 *		key will be inserted with a zero-length value. Inserting a NULL value
 *		with a non-zero length will fail.
 *
 * @result
 *		A boolean indicating if the key-value pair was inserted successfully.
 *		Returns false if the key is invalid. A key is invalid if it is an empty
 *		string, contains non-ASCII characters, or has length greater than
 *		UINT8_MAX.
 *
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_set_key(nw_txt_record_t txt_record, const char *key,
					  const uint8_t * _Nullable value, size_t value_len);

/*!
 * @function nw_txt_record_remove_key
 *
 * @abstract
 *		Removes a key-value pair in the TXT record object given its key.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key corresponding to the key-value pair.
 *
 * @result
 *		A boolean indicating if the key-value pair specified by the given key
 *		was removed. Returns false if the key is invalid or not present in the
 *		TXT dictionary. A key is invalid if it is an empty string, contains
 *		non-ASCII characters, or has length greater than UINT8_MAX.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_remove_key(nw_txt_record_t txt_record,
						 const char *key);

/*!
 * @function nw_txt_record_get_key_count
 *
 * @abstract
 *		Count the number of keys in the TXT record object.
 *
 * @param txt_record
 *		A TXT record object.
 *
 * @result
 *		The number of keys in the TXT record object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
size_t
nw_txt_record_get_key_count(nw_txt_record_t _Nullable txt_record);

#ifdef __BLOCKS__
/*!
 * @typedef nw_txt_record_access_bytes_t
 *
 * @abstract
 *		A block to access the raw TXT record inside the TXT record object. For
 *		example, the user can copy the raw TXT record into another buffer in the
 *		block, or read its contents.
 *
 * @param raw_txt_record
 *		The raw TXT record inside the TXT record object. Note that the bytes
 *		pointed to by raw_txt_record is only valid within the scope of the block.
 *
 * @param len
 *		The length of the raw TXT record.
 *
 * @result
 *		A user-defined return value. For example, the user may want to return a
 *	 	boolean indicating if the operation succeeds.
 */
typedef bool (^nw_txt_record_access_bytes_t) (const uint8_t *raw_txt_record,
											  size_t len);

/*!
 * @function nw_txt_record_access_bytes
 *
 * @abstract
 *		Access the raw TXT record inside the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param access_bytes
 *		The block that will be used to access the raw TXT record inside the TXT
 *		record object.
 *
 * @result
 *		The return value of the access_bytes block, which is defined by the user.
 *		For example, the user may want to return a boolean indicating if the
 *		operation succeeds.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_access_bytes(nw_txt_record_t txt_record,
						   nw_txt_record_access_bytes_t access_bytes);

/*!
 * @typedef nw_txt_record_applier_t
 *
 * @abstract
 *		A block that can be applied to every key-value pair in the TXT record
 *		object.
 *
 * @param key
 *		The key of the current iterating key-value pair. Note that key is only
 *		valid within the scope of the block.
 *
 * @param found
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 *
 * @param value
 *		The value of the current iterating key-value pair. Note that value is
 *		only valid within the scope of the block.
 *
 * @param value_len
 *		The length of the value.
 *
 * @result
 *		A boolean indicating whether iteration should continue.
 */
typedef bool (^nw_txt_record_applier_t) (const char *key,
										 const nw_txt_record_find_key_t found,
										 const uint8_t *value,
										 const size_t value_len);

/*!
 * @function nw_txt_record_apply
 *
 * @abstract
 *      Apply the block to every key-value pair in the TXT record object.
 *
 * @param txt_record
 *      The TXT record object.
 *
 * @param applier
 *      The block that will be applied to the entire TXT record object.
 *
 * @result
 *      A boolean indicating whether iteration of the TXT record object
 *		completed successfully. Iteration will only fail if the applier block
 *		returns false.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_apply(nw_txt_record_t txt_record,
					nw_txt_record_applier_t applier);
#endif // __BLOCKS__

/*!
 * @function nw_txt_record_is_equal
 *
 * @abstract
 *      Check if the two TXT record objects are equal.
 *
 * @param left
 *      The first TXT record object to be compared.
 *
 * @param right
 *      The second TXT record object to be compared.
 *
 * @result
 *      A boolean indicating if the two TXT record objects are equal. Two TXT
 *		record objects are equal if they contain the same set of key-value pairs,
 *		where keys are compared case-insensitively. For example, "ABC=1" and
 *		"abc=1" are identical key-value pairs. The ordering of the key-value
 *		pairs does not matter.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_is_equal(nw_txt_record_t _Nullable left,
					   nw_txt_record_t _Nullable right);

/*!
 * @function nw_txt_record_is_dictionary
 *
 * @abstract
 *      Check whether the TXT record is a dictionary or a buffer.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @result
 *      A boolean indicating whether the TXT record is a dictionary or a buffer.
 * 		If true, the TXT record is a dictionary. If false, the TXT record is a
 *		buffer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_is_dictionary(nw_txt_record_t txt_record);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* __NW_TXT_RECORD_H__ */
// ==========  Network.framework/Headers/nw_object.h
//
//  nw_object.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_OBJECT_H__
#define __NW_OBJECT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <sys/cdefs.h>
#include <os/object.h>
#include <TargetConditionals.h> // TARGET_OS_*

/*
 * By default, nw_objects are declared as Objective-C types when building
 * with an Objective-C compiler. This allows them to participate in ARC, in RR
 * management by the Blocks runtime and in leaks checking by the static
 * analyzer, and enables them to be added to Cocoa collections.
 * See <os/object.h> for details.
 */


#if OS_OBJECT_USE_OBJC
#  define NW_OBJECT_DECL(type) OS_OBJECT_DECL(type)
#else // OS_OBJECT_USE_OBJC
#  define NW_OBJECT_DECL(type)				\
		struct type;						\
		typedef	struct type *type##_t
#endif // OS_OBJECT_USE_OBJC


#if __has_feature(assume_nonnull)
#  define NW_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#  define NW_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else // assume_nonnull
#  define NW_ASSUME_NONNULL_BEGIN
#  define NW_ASSUME_NONNULL_END
#endif // assume_nonnull

#if __has_feature(nullability_on_arrays)
# define NW_NONNULL_ARRAY _Nonnull
#else // nullability_on_arrays
# define NW_NONNULL_ARRAY
#endif// nullability_on_arrays

#ifndef __has_attribute
#  define __has_attribute(x) 0
#endif // !__has_attribute

#ifndef NW_RETURNS_RETAINED
#  define NW_RETURNS_RETAINED OS_OBJECT_RETURNS_RETAINED
#endif // !NW_RETURNS_RETAINED

#if defined(__OBJC__) && __has_feature(attribute_ns_returns_not_retained)
#  define NW_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
#else // __OBJC__ && ns_returns_not_retained
#  define NW_RETURNS_NOT_RETAINED
#endif // __OBJC__ && ns_returns_not_retained

#if __has_attribute(noescape)
#define NW_NOESCAPE __attribute__((__noescape__))
#else // noescape
#define NW_NOESCAPE
#endif // noescape

#if defined(__OBJC__) && __has_attribute(ns_consumed)
#  define NW_RELEASES_ARGUMENT __attribute__((__ns_consumed__))
#else // __OBJC__ && ns_consumed
#  define NW_RELEASES_ARGUMENT
#endif // __OBJC__ && ns_consumed

#if defined(__OBJC__) && __has_attribute(objc_precise_lifetime)
#  define NW_VALID_UNTIL_END_OF_SCOPE __attribute__((objc_precise_lifetime))
#else // __OBJC__ && objc_precise_lifetime
#  define NW_VALID_UNTIL_END_OF_SCOPE
#endif // __OBJC__ && objc_precise_lifetime

#if defined(__OBJC__) && __has_attribute(objc_returns_inner_pointer)
#  define NW_RETURNS_INNER_POINTER __attribute__((objc_returns_inner_pointer))
#else // __OBJC__ && objc_returns_inner_pointer
#  define NW_RETURNS_INNER_POINTER
#endif // __OBJC__ && objc_returns_inner_pointer

#ifndef NW_UNSAFE_UNRETAINED
#  if defined(__OBJC__)
#	  define NW_UNSAFE_UNRETAINED __unsafe_unretained
#  else // __OBJC__
#	  define NW_UNSAFE_UNRETAINED
#  endif // __OBJC__
#endif // !NW_UNSAFE_UNRETAINED

#ifndef NW_EXPORT
#  define NW_EXPORT __attribute__((visibility("default")))
#endif // !NW_EXPORT

#ifndef NW_EXPORT_PROJECT
#  define NW_EXPORT_PROJECT NW_EXPORT
#endif // !NW_EXPORT

#ifndef NW_NOT_i386_MAC
#  if !TARGET_OS_OSX || !defined(__i386__)
#    define NW_NOT_i386_MAC 1
#  else // !TARGET_OS_OSX || !__i386__
#    define NW_NOT_i386_MAC 0
#  endif // !TARGET_OS_OSX || !__i386__
#endif // NW_NOT_i386_MAC


#if !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

__BEGIN_DECLS

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void *nw_retain(void *obj);

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void nw_release(void *obj);

__END_DECLS

#else // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

#undef nw_retain
#undef nw_release
#define nw_retain(object) [(object) retain]
#define nw_release(object) [(object) release]

#endif // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE


NW_OBJECT_DECL(nw_object);

#endif // __NW_OBJECT_H__
// ==========  Network.framework/Headers/connection_report.h
//
//  connection_report.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_REPORT_H__
#define __NW_CONNECTION_REPORT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/connection.h>
#include <Network/interface.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

#pragma mark - Establishment Report

/*!
 * @typedef nw_establishment_report_t
 * @abstract
 *		An Establishment Report contains information about how an nw_connection_t
 *		became established. This is intended to be used for analysis of performance
 *		after connection establishment. The report cannot be gathered until a
 *		connection is in the "ready" state.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ESTABLISHMENT_REPORT_IMPL
NW_OBJECT_DECL(nw_establishment_report);
#endif // NW_ESTABLISHMENT_REPORT_IMPL

#ifdef __BLOCKS__

typedef void (^nw_establishment_report_access_block_t)(_Nullable nw_establishment_report_t report);

/*!
 * @function nw_connection_access_establishment_report
 *
 * @abstract
 *		Access the establishment report for a connection. The report will be
 *		NULL until the connection is in the "ready" state.
 *
 *		The callback block will be invoked exactly once on the provided queue.
 *
 * @param connection
 *		An established connection.
 *
 * @param queue
 *		The dispatch queue on which to call the access_block.
 *
 * @param access_block
 *		A block to invoke with the establishment report, which may be NULL if the
 *		connection not ready.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_connection_access_establishment_report(nw_connection_t connection,
										  dispatch_queue_t queue,
										  nw_establishment_report_access_block_t access_block);

#endif // __BLOCKS__

/*!
 * @function nw_establishment_report_get_duration_milliseconds
 *
 * @abstract
 *		Retrieve the duration of the connection's establishment. This is
 *		the total time in milliseconds from when the connection attempt began
 *		until the connection becomes ready, including resolution, proxy
 *		evaluation, and protocol handshakes.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of milliseconds the connection took to establish.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_establishment_report_get_duration_milliseconds(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_attempt_started_after_milliseconds
 *
 * @abstract
 *		Retrieve the delay from calling start() after which the successful connection
 *		attempt began. For connections that succeed on the first attempt, this value
 *		will be 0. For connections that move into the "waiting" state, this
 *		value will be greater than 0.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of milliseconds from connection start to the beginning
 *		of the successful connection attempt.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_establishment_report_get_attempt_started_after_milliseconds(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_previous_attempt_count
 *
 * @abstract
 *		Retrieve the number of connection attempts made before the successful
 *		attempt. For connections that succeed on the first attempt, this value
 *		will be 0. For connections that move into the "waiting" state, this
 *		value will be greater than 0.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of connection attempts made before the successful attempt.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint32_t
nw_establishment_report_get_previous_attempt_count(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_used_proxy
 *
 * @abstract
 *		Check if the connection used a proxy during establishment.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns true if the connection used a proxy, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_establishment_report_get_used_proxy(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_proxy_configured
 *
 * @abstract
 *		Check if a proxy configuration applied to the connection,
 *		even if the connection did not end up using a proxy for the
 *		successful attempt.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns true if a proxy configuration applied to the connection,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_establishment_report_get_proxy_configured(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_copy_proxy_endpoint
 *
 * @abstract
 *		Access the endpoint of the proxy used by a connection, if applicable.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns an allocated endpoint object if a proxy was used by the connection,
 *		or NULL if no proxy was used.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_establishment_report_copy_proxy_endpoint(nw_establishment_report_t report);

#ifdef __BLOCKS__

/*!
 * @typedef nw_report_resolution_source_t
 * @abstract
 *		The source of a resolution indicates if the set of endpoints was resolved
 *		locally using a cache, or sent a query over the network.
 */
typedef enum {
	/*! @const nw_report_resolution_source_query A query was sent over the network */
	nw_report_resolution_source_query = 1,
	/*! @const nw_report_resolution_source_cache The local cache was used  */
	nw_report_resolution_source_cache = 2,
	/*! @const nw_report_resolution_source_expired_cache An expired entry in the local cache was used */
	nw_report_resolution_source_expired_cache = 3,
} nw_report_resolution_source_t;

typedef bool (^nw_report_resolution_enumerator_t)(nw_report_resolution_source_t source,
												  uint64_t milliseconds,
												  uint32_t endpoint_count,
												  nw_endpoint_t successful_endpoint,
												  nw_endpoint_t preferred_endpoint);

/*!
 * @function nw_establishment_report_enumerate_resolutions
 *
 * @abstract
 *		Enumerate the steps of connection establishment that involved endpoint
 *		resolution, such as DNS hostname resolution and Bonjour service resolution.
 *		The provided block will be called inline zero or more times.
 *
 * @param report
 *		An establishment report.
 *
 * @param enumerate_block
 *		A block to be invoked zero or more times, once for each step of resolution
 *		used during connection establishment.
 *
 *		The values passed to the enumerator are:
 *		- source: The source of the resolution (query or cache).
 *		- milliseconds: The number of milliseconds spent on this resolution step.
 *		- endpoint_count: The number of resolved endpoints discovered by the resolution step.
 *		- successful_endpoint: The resolved endpoint that led to a successful connection.
 *		- preferred_endpoint: The first resolved endpoint attempted, which may be the same as the successful_endpoint.
 *
 *		Returning true from the block indicates that the enumeration should continue.
 *		Returning false indicates that the enumeration should stop.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_establishment_report_enumerate_resolutions(nw_establishment_report_t report,
											  NW_NOESCAPE nw_report_resolution_enumerator_t enumerate_block);

typedef bool (^nw_report_protocol_enumerator_t)(nw_protocol_definition_t protocol,
												uint64_t handshake_milliseconds,
												uint64_t handshake_rtt_milliseconds);

/*!
 * @function nw_establishment_report_enumerate_protocols
 *
 * @abstract
 *		Enumerate the protocols used in the established connection.
 *		The provided block will be called inline zero or more times.
 *
 * @param report
 *		An establishment report.
 *
 * @param enumerate_block
 *		A block to be invoked zero or more times, once for each protocol
 *		used in the established connection.
 *
 *		The values passed to the enumerator are:
 *		- protocol: The protocol definition.
 *		- handshake_milliseconds: The number of milliseconds spent on the protocol's handshake.
 *		- handshake_rtt_milliseconds: The round trip time in milliseconds measured by the protocol's handshake.
 *
 *		Returning true from the block indicates that the enumeration should continue.
 *		Returning false indicates that the enumeration should stop.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_establishment_report_enumerate_protocols(nw_establishment_report_t report,
											NW_NOESCAPE nw_report_protocol_enumerator_t enumerate_block);

#endif // __BLOCKS__

#pragma mark - Data Transfer Report

/*!
 * @typedef nw_data_transfer_report_t
 * @abstract
 *		A Data Transfer Report contains performance information about data
 *		transferred on an nw_connection_t for certain span of time. Multiple reports
 *		can be retrieved from a single connection, starting and ending at different times.
 *		This allows throughput to be measured based on how an application is using
 *		a connection. A report may be created prior to a connection moving into
 *		the "ready" state, but measurements will not be collected until after the
 *		connection is ready.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_DATA_TRANSFER_REPORT_IMPL
NW_OBJECT_DECL(nw_data_transfer_report);
#endif // NW_DATA_TRANSFER_REPORT_IMPL

/*!
 * @function nw_connection_create_new_data_transfer_report
 *
 * @abstract
 *		Create a new data transfer report on a connection. Multiple
 *		reports may be created for a single connection. The report begins
 *		capturing data when the connection becomes ready, or when the
 *		report is created (whichever occurs last).
 *
 *		Call nw_data_transfer_report_collect() to complete collection of
 *		report, after which point the details of the report will be available.
 *
 * @param connection
 *		A connection object, in or before the ready state.
 *
 * @result
 *		Returns an allocated nw_data_transfer_report_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_data_transfer_report_t
nw_connection_create_new_data_transfer_report(nw_connection_t connection);

/*!
 * @typedef nw_data_transfer_report_state_t
 * @abstract
 *		The state of a Data Transfer Report indicates whether or not the contents
 *		have been collected, and are ready to be accessed.
 */
typedef enum {
	/*! @const nw_data_transfer_report_state_collecting The report is outstanding; values cannot be accessed. */
	nw_data_transfer_report_state_collecting = 1,
	/*! @const nw_data_transfer_report_state_collected The report is complete; values can now be accessed. */
	nw_data_transfer_report_state_collected = 2,
} nw_data_transfer_report_state_t;

/*!
 * @function nw_data_transfer_report_get_state
 *
 * @abstract
 *		Access the state of a data transfer report. Once a report
 *		is "collected", individual fields may be read.
 *
 * @param report
 *		A data transfer report to check.
 *
 * @result
 *		Returns the current state of the data transfer report.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_data_transfer_report_state_t
nw_data_transfer_report_get_state(nw_data_transfer_report_t report);

#ifdef __BLOCKS__

typedef void (^nw_data_transfer_report_collect_block_t)(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_collect
 *
 * @abstract
 *		Mark a data transfer report as complete, and request collection of
 *		values. Once the report has been collected, the callback block
 *		will be invoked exactly once on the provided dispatch queue.
 *
 *		If a connection is cancelled or fails prior to the report being collected,
 *		the report will automatically be collected. Calling
 *		nw_data_transfer_report_collect() will be redundant but not harmful.
 *
 * @param report
 *		A data transfer report to check.
 *
 * @param queue
 *		The dispatch queue on which to call the collect_block.
 *
 * @param collect_block
 *		A block to invoke once the report has been collected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_data_transfer_report_collect(nw_data_transfer_report_t report,
								dispatch_queue_t queue,
								nw_data_transfer_report_collect_block_t collect_block);

#endif // __BLOCKS__

/*!
 * @const NW_ALL_PATHS
 * @discussion Pass NW_ALL_PATHS to data transfer report accessors to sum
 *		values across paths where applicable. For values that cannot
 *		sum, the value of the primary path is used.
 */
NW_EXPORT extern const uint32_t _nw_data_transfer_report_all_paths;
#define NW_ALL_PATHS (_nw_data_transfer_report_all_paths)

/*!
 * @function nw_data_transfer_report_get_duration_milliseconds
 *
 * @abstract
 *		Retrieve the duration of the data transfer report. This is a length
 *		of time in milliseconds which can be used to calculate throughput
 *		when compared to application and transport byte counts.
 *
 *		The start time is calculated from when the report was created, or the connection
 *		became ready if the connection was not ready when the report was created.
 *		The duration ends when the report is collected, or the connection fails
 *		or is cancelled.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @result
 *		Returns the duration of the data transport report in milliseconds, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_duration_milliseconds(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_get_path_count
 *
 * @abstract
 *		Retrieve the number of paths used by the connection for the
 *		duration of the report. Any value greater than or equal to 0 and
 *		less than this count may be used as a "path_index" for retrieving
 *		specific details from the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @result
 *		Returns the number of paths used by the connection, which
 *		limits the value of the "path_index" parameter used in other report
 *		functions. Returns 0 if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint32_t
nw_data_transfer_report_get_path_count(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_get_received_ip_packet_count
 *
 * @abstract
 *		Retrieve the number of IP packets received on a given path for the
 *		duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of IP packets received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_ip_packet_count(nw_data_transfer_report_t report,
													 uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_ip_packet_count
 *
 * @abstract
 *		Retrieve the number of IP packets sent on a given path for the
 *		duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of IP packets sent, or 0 if the report is not
 *		in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_ip_packet_count(nw_data_transfer_report_t report,
												 uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_byte_count
 *
 * @abstract
 *		Retrieve the number of transport protocol bytes (such as TCP stream bytes)
 *		received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of transport protocol bytes received, or 0 if the
 *		report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_byte_count(nw_data_transfer_report_t report,
														  uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_duplicate_byte_count
 *
 * @abstract
 *		Retrieve the number of duplicate transport protocol bytes (such as
 *		duplicate TCP bytes) received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of duplicate transport protocol bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_duplicate_byte_count(nw_data_transfer_report_t report,
																	uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_out_of_order_byte_count
 *
 * @abstract
 *		Retrieve the number of out-of-order transport protocol bytes (such as
 *		out-of-order TCP bytes) received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of out-of-order transport protocol bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_out_of_order_byte_count(nw_data_transfer_report_t report,
																	   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_transport_byte_count
 *
 * @abstract
 *		Retrieve the number of transport protocol bytes (such as TCP stream bytes)
 *		sent on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of transport protocol bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_transport_byte_count(nw_data_transfer_report_t report,
													  uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_transport_retransmitted_byte_count
 *
 * @abstract
 *		Retrieve the number of retransmitted transport protocol bytes (such as
 *		retransmitted TCP bytes) sent on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of retransmitted transport protocol bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_transport_retransmitted_byte_count(nw_data_transfer_report_t report,
																	uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_smoothed_rtt_milliseconds
 *
 * @abstract
 *		Retrieve the smoothed average for the transport protocol's round trip time
 *		(RTT) on a given path for the duration of the report, measured in milliseconds.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the smoothed RTT as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_smoothed_rtt_milliseconds(nw_data_transfer_report_t report,
																uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_minimum_rtt_milliseconds
 *
 * @abstract
 *		Retrieve the minimum (best) round trip time (RTT) on a given path for
 *		the duration of the report, measured in milliseconds.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the minimum RTT as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_minimum_rtt_milliseconds(nw_data_transfer_report_t report,
															   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_rtt_variance
 *
 * @abstract
 *		Retrieve the variance of the round trip time (RTT) on a given path for
 *		the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the RTT variance as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_rtt_variance(nw_data_transfer_report_t report,
												   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_application_byte_count
 *
 * @abstract
 *		Retrieve the number of application bytes received on a given
 *		path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of application bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_application_byte_count(nw_data_transfer_report_t report,
															uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_application_byte_count
 *
 * @abstract
 *		Retrieve the number of application bytes sent on a given
 *		path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of application bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_application_byte_count(nw_data_transfer_report_t report,
														uint32_t path_index);

/*!
 * @function nw_data_transfer_report_copy_path_interface
 *
 * @abstract
 *		Retrieve the interface used for data transfer for a given
 *		path used by a connection.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns a retained nw_interface_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails if the report is not yet collected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_interface_t
nw_data_transfer_report_copy_path_interface(nw_data_transfer_report_t report,
											uint32_t path_index);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* defined(__NW_CONNECTION_REPORT_H__) */
// ==========  Network.framework/Headers/browse_result.h
//
//  browse_result.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSE_RESULT_H__
#define __NW_BROWSE_RESULT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/endpoint.h>
#include <Network/interface.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browse_result_t
 * @abstract
 *		A Browse Result represents the outcome of a browse operation. It contains
 *		an endpoint and additional information about the endpoint gathered during
 *		browsing.
 *
 *		For example, a Bonjour service may be advertised on multiple interfaces.
 *		The browser will provide a single browse result object for each collection
 *		of Bonjour endpoints sharing the same service instance name. The browse
 *		result will have an enumerable array of interfaces and the endpoints'
 *		common TXT record value.
 *
 *		Browse results may also be compared using nw_browse_result_get_changes()
 *		which describes the changes that occurred between an old and new browse
 *		result.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSE_RESULT_IMPL
NW_OBJECT_DECL(nw_browse_result);
#endif // NW_BROWSE_RESULT_IMPL

/*!
 * @typedef nw_browse_result_change_t
 * @abstract
 *		A nw_browse_result_change_t describes all changes that occurred between
 *		two browse results. Call nw_browse_result_get_changes() to get the
 *		changes between an old and a new browse result.
 */
typedef uint64_t nw_browse_result_change_t;

enum {
	/*!
	 *	@const nw_browse_result_change_invalid The browse result change is invalid.
	 */
	nw_browse_result_change_invalid = 0x00,

	/*!
	 *	@const nw_browse_result_change_identical The browse results being compared
	 *		are identical.
	 */
	nw_browse_result_change_identical = 0x01,

	/*!
	 *	@const nw_browse_result_change_result_added A browse result was added.
	 */
	nw_browse_result_change_result_added = 0x02,

	/*!
	 *	@const nw_browse_result_change_result_removed A browse result was removed.
	 */
	nw_browse_result_change_result_removed = 0x04,

	/*!
	 *	@const nw_browse_result_change_interface_added An interface became available.
	 */
	nw_browse_result_change_interface_added = 0x08,

	/*!
	 *	@const nw_browse_result_change_interface_removed An interface was removed.
	 */
	nw_browse_result_change_interface_removed = 0x10,

	/*!
	 *	@const nw_browse_result_change_txt_record_changed The TXT record changed.
	 */
	nw_browse_result_change_txt_record_changed = 0x20,
};

/*!
 * @function nw_browse_result_copy_endpoint
 *
 * @abstract
 *		Copies the endpoint associated with the browse result object.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		The associated endpoint.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_browse_result_copy_endpoint(nw_browse_result_t result);

/*!
 * @function nw_browse_result_get_changes
 *
 * @abstract
 *		Determines the set of all changes that occurred between an old and a new
 *		browse result. For example, if the return value of this function matches
 *		with nw_browse_result_change_interface_added and nw_browse_result_change_txt_record_changed,
 *		the caller can expect new_result to include a new interface and an updated
 *		txt record that was not present in old_result.
 *
 * @param old_result
 *		The old result.
 *
 * @param new_result
 *		The new result.
 *
 * @result
 *		A nw_browse_result_change_t describing all changes that occurred.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_browse_result_change_t
nw_browse_result_get_changes(_Nullable nw_browse_result_t old_result,
							 _Nullable nw_browse_result_t new_result);

/*!
 * @function nw_browse_result_get_interfaces_count
 *
 * @abstract
 *		Returns the number of interfaces on this browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		The number of interfaces available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
size_t
nw_browse_result_get_interfaces_count(nw_browse_result_t result);

/*!
 * @function nw_browse_result_copy_txt_record_object
 *
 * @abstract
 *		Copies the TXT record object from the browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		A copy of the TXT record object, or NULL if the browse result does not
 *		have an associated TXT record.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_browse_result_copy_txt_record_object(nw_browse_result_t result);

#ifdef __BLOCKS__

/*!
 * @typedef nw_browse_result_enumerate_interface_t
 *
 * @abstract
 *		A block that can be applied to every interface in the browse result.
 *
 * @param interface
 *		The interface object.
 *
 * @result
 *		A boolean value that indicating if enumeration should continue.
 */
typedef bool (^nw_browse_result_enumerate_interface_t)(nw_interface_t interface);

/*!
 * @function nw_browse_result_enumerate_interfaces
 *
 * @abstract
 *		Enumerates the list of interfaces on this browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @param enumerator
 *		The enumerator block.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browse_result_enumerate_interfaces(nw_browse_result_t result,
									  NW_NOESCAPE nw_browse_result_enumerate_interface_t enumerator);

#endif // __BLOCKS__


__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_BROWSE_RESULT_H__
// ==========  Network.framework/Headers/tcp_options.h
//
//  tcp_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_TCP_OPTIONS_H__
#define __NW_TCP_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_tcp_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of TCP (Transmission Control Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the transport protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_tcp_definition(void);

#pragma mark - Options

/*!
 * @function nw_tcp_create_options
 *
 * @abstract
 *		Create an instance of TCP protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_tcp_create_options(void);

/*!
 * @function nw_tcp_options_set_no_delay
 *
 * @abstract
 *		Configure TCP to disable Nagle's algorithm, which will
 *		delay sending packets to coalesce sending.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_delay
 *		A boolean indicating that TCP should disable
 *		Nagle's algorithm.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_delay(nw_protocol_options_t options,
							bool no_delay);

/*!
 * @function nw_tcp_options_set_no_push
 *
 * @abstract
 *		Wait to send TCP data until the connection has finished
 *		writing, or else the TCP send buffer is full.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_push
 *		A boolean indicating that TCP should be set into
 *		no-push mode.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_push(nw_protocol_options_t options,
						   bool no_push);

/*!
 * @function nw_tcp_options_set_no_options
 *
 * @abstract
 *		Disable sending TCP options and extensions.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_options
 *		A boolean indicating that TCP should be set into
 *		no-options mode.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_options(nw_protocol_options_t options,
							  bool no_options);

/*!
 * @function nw_tcp_options_set_enable_keepalive
 *
 * @abstract
 *		Enable sending TCP keepalive probes.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param enable_keepalive
 *		A boolean indicating that TCP should send keepalives.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_enable_keepalive(nw_protocol_options_t options,
									bool enable_keepalive);

/*!
 * @function nw_tcp_options_set_keepalive_count
 *
 * @abstract
 *		Configure the number of times TCP keepalive probes
 *		should be sent without reply before terminating
 *		the connection.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_count
 *		The number of keepalive probes to send before terminating
 *		the connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_count(nw_protocol_options_t options,
								   uint32_t keepalive_count);

/*!
 * @function nw_tcp_options_set_keepalive_idle_time
 *
 * @abstract
 *		Configure the amount of time that a connection must be
 *		idle before TCP should start sending keepalive probes.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_idle_time
 *		The number of seconds of idleness to wait before keepalive
 *		probes are sent by TCP.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_idle_time(nw_protocol_options_t options,
									   uint32_t keepalive_idle_time);

/*!
 * @function nw_tcp_options_set_keepalive_interval
 *
 * @abstract
 *		Configure the amount of time between sending TCP keepalive
 *		probes when the peer is not responding.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_interval
 *		The number of seconds of to wait before resending TCP
 *		keepalive probes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_interval(nw_protocol_options_t options,
									  uint32_t keepalive_interval);

/*!
 * @function nw_tcp_options_set_maximum_segment_size
 *
 * @abstract
 *		Directly configure the maximum segment size (MSS)
 *		TCP will use.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param maximum_segment_size
 *		The maximum segment size in bytes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_maximum_segment_size(nw_protocol_options_t options,
										uint32_t maximum_segment_size);

/*!
 * @function nw_tcp_options_set_connection_timeout
 *
 * @abstract
 *		Define a timeout value after which TCP connection
 *		establishment will give up.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param connection_timeout
 *		A timeout for TCP connection establishment, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_connection_timeout(nw_protocol_options_t options,
									  uint32_t connection_timeout);

/*!
 * @function nw_tcp_options_set_persist_timeout
 *
 * @abstract
 *		Define a timeout value after which TCP connections
 *		in the persist state will terminate. See RFC 6429.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param persist_timeout
 *		The TCP persist timeout, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_persist_timeout(nw_protocol_options_t options,
								   uint32_t persist_timeout);

/*!
 * @function nw_tcp_options_set_retransmit_connection_drop_time
 *
 * @abstract
 *		Define a timeout value after which TCP will drop
 *		a connection with unacknowledged retransmissions.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param retransmit_connection_drop_time
 *		A timeout for TCP retransmission attempts, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_retransmit_connection_drop_time(nw_protocol_options_t options,
												   uint32_t retransmit_connection_drop_time);

/*!
 * @function nw_tcp_options_set_retransmit_fin_drop
 *
 * @abstract
 *		Cause TCP to drop connections after not receiving
 *		an ACK multiple times after a FIN, currently set at three.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param retransmit_fin_drop
 *		A boolean to cause TCP to drop its connection after
 *		not receiving an ACK after a FIN.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_retransmit_fin_drop(nw_protocol_options_t options,
									   bool retransmit_fin_drop);

/*!
 * @function nw_tcp_options_set_disable_ack_stretching
 *
 * @abstract
 *		Configure TCP to disable ACK stretching. ACKs will be sent
 *		for every other data packet.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param disable_ack_stretching
 *		A boolean to cause TCP to disable ACK stretching.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_disable_ack_stretching(nw_protocol_options_t options,
										  bool disable_ack_stretching);

/*!
 * @function nw_tcp_options_set_enable_fast_open
 *
 * @abstract
 *		Configure TCP to enable TCP Fast Open (TFO). This may take effect
 *		even when TCP is not the top-level protocol in the protocol stack.
 *		For example, if TLS is running over TCP, the Client Hello message
 *		may be sent as fast open data.
 *
 *		If TCP is the top-level protocol in the stack (the one the application
 *		directly interacts with), TFO will be disabled unless the application
 *		indicated that it will provide its own fast open data by calling
 *		nw_parameters_set_fast_open_enabled().
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param enable_fast_open
 *		A boolean to enable TFO.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_enable_fast_open(nw_protocol_options_t options,
									bool enable_fast_open);

/*!
 * @function nw_tcp_options_set_disable_ecn
 *
 * @abstract
 *		Configure TCP to disable default Explicit Congestion
 *		Notification (ECN) behavior.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param disable_ecn
 *		A boolean to disable ECN support in TCP.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_disable_ecn(nw_protocol_options_t options,
							   bool disable_ecn);

#pragma mark - Metadata

/*!
 * @function nw_protocol_metadata_is_tcp
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of TCP.
 *
 * @result
 *		Returns true if the metadata is for the default system TCP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_tcp(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tcp_get_available_receive_buffer
 *
 * @abstract
 *		Fetch the number of bytes waiting to be read from the receive buffer.
 *
 * @result
 *		The number of bytes available in the receive buffer.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_tcp_get_available_receive_buffer(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tcp_get_available_send_buffer
 *
 * @abstract
 *		Fetch the number of bytes waiting to be acknowledged in the send buffer.
 *
 * @result
 *		The number of bytes waiting to be acknowledged.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_tcp_get_available_send_buffer(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_TCP_OPTIONS_H__
// ==========  Network.framework/Headers/ethernet_channel.h
//
//  ethernet_channel.h
//  Network
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ETHERNET_CHANNEL_H__
#define __NW_ETHERNET_CHANNEL_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/error.h>
#include <Network/parameters.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_ethernet_channel_t
 * @abstract
 *		An Ethernet channel is an object that represents a bi-directional data channel to send
 *      and receive Ethernet frames with a custom EtherType.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ETHERNET_CHANNEL_IMPL
NW_OBJECT_DECL(nw_ethernet_channel);
#endif // NW_ETHERNET_CHANNEL_IMPL

/*!
 * @typedef nw_ethernet_channel_state_t
 * @abstract
 *		Channel states sent by nw_ethernet_channel_set_state_changed_handler.
 *		States generally progress forward and do not move backwards, with the
 *		exception of preparing and waiting, which may alternate before the channel
 *		becomes ready or failed.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef enum {
	/*!
	 *	@const nw_ethernet_channel_state_invalid The state of the channel is not valid. This state
	 *		will never be delivered in the channel's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_ethernet_channel_state_invalid = 0,
	/*! @const nw_ethernet_channel_state_waiting The channel is waiting for a usable network before re-attempting */
	nw_ethernet_channel_state_waiting = 1,
	/*! @const nw_ethernet_channel_state_preparing The channel is in the process of establishing */
	nw_ethernet_channel_state_preparing = 2,
	/*! @const nw_ethernet_channel_state_ready The channel is established and ready to send and receive data */
	nw_ethernet_channel_state_ready = 3,
	/*! @const nw_ethernet_channel_state_failed The channel has irrecoverably closed or failed */
	nw_ethernet_channel_state_failed = 4,
	/*! @const nw_ethernet_channel_state_cancelled The channel has been cancelled by the caller */
	nw_ethernet_channel_state_cancelled = 5,
} nw_ethernet_channel_state_t;

/*!
 * @function nw_ethernet_channel_create
 *
 * @abstract
 *		Creates an Ethernet channel with a custom EtherType.
 *
 * @param ether_type
 *		The custom EtherType to be used for all Ethernet frames in this channel. The
 *		EtherType is the two-octet field in an Ethernet frame, indicating the protocol
 *		encapsulated in the payload of the frame.  This parameter is in little-endian
 *		byte order.  Only custom EtherType values are supported. This parameter cannot
 *		be an EtherType already handled by the system, such as IPv4, IPv6, ARP, VLAN Tag,
 *		or 802.1x.
 *
 *		Calling processes must hold the "com.apple.developer.networking.custom-protocol"
 *		entitlement.
 *
 * @param interface
 *		The interface on which this custom Ethernet channel will be allowed.
 *
 * @result
 *		Returns an allocated nw_ethernet_channel_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NW_RETURNS_RETAINED nw_ethernet_channel_t
nw_ethernet_channel_create(uint16_t ether_type, nw_interface_t interface);

#ifdef __BLOCKS__

/*!
 * @typedef nw_ethernet_channel_state_changed_handler_t
 * @abstract
 *      A state change handler to handle state changes.
 *
 * @param state
 *	   The current state.
 *
 * @param error
 *     error if present, indicates the reason of the failure.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_state_changed_handler_t)(nw_ethernet_channel_state_t state, _Nullable nw_error_t error);

/*!
 * @function nw_ethernet_channel_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		channel has been cancelled, the nw_ethernet_channel_state_cancelled state will
 *		be delivered last.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 *
 * @param handler
 *		The state changed handler to call when the channel state changes.
 *		Pass NULL to remove the state changed handler.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_state_changed_handler(nw_ethernet_channel_t ethernet_channel,
											  _Nullable nw_ethernet_channel_state_changed_handler_t handler);

#endif // __BLOCKS__

/*!
 * @function nw_ethernet_channel_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_ethernet_channel_start().
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_queue(nw_ethernet_channel_t ethernet_channel, dispatch_queue_t queue);

/*!
 * @function nw_ethernet_channel_start
 *
 * @abstract
 *		Starts the Ethernet channel, which will cause the channel to evaluate
 *      its path, and try to become readable and writable.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_start(nw_ethernet_channel_t ethernet_channel);

/*!
 * @function nw_ethernet_channel_cancel
 *
 * @abstract
 *		Cancel the Ethernet channel. This will close the channel. The process of cancellation will be
 *      completed asynchronously, and the final callback event delivered to the caller will be
 *      a state update with a value of nw_ethernet_channel_state_cancelled. Once this update is
 *      delivered, the caller may clean up any associated memory or objects.
 *
 *		Outstanding sends and receives will receive errors before the state changes to cancelled.
 *		There is no guarantee that any outstanding sends that have not yet delivered
 *		completion handlers will send data before the channel is closed.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_cancel(nw_ethernet_channel_t ethernet_channel);

#ifdef __BLOCKS__

/*!
 * @typedef nw_ethernet_address_t
 * @abstract
 *		Address for an Ethernet Frame.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef unsigned char nw_ethernet_address_t[6];

/*!
 * @typedef nw_ethernet_channel_receive_handler_t
 * @abstract
 *		This receive handler is invoked when a frame of the set Ethertype is received from the Ethernet
 *      channel.
 *
 * @param content
 *		The received Ethernet payload, which has a length constrained by the maximum Ethernet frame size
 *      of 1518 minus Ethernet header size of (18/14 bytes with/without vlan tag).
 *
 * @param vlan_tag
 *      The vlan tag of the frame, 0 if there is no vlan tag.  This parameter is in little-endian
 *      byte order.
 *
 * @param local_address
 *		The local Ethernet address in the received Ethernet frame header.
 *
 * @param remote_address
 *		The remote Ethernet address in the received Ethernet frame header.
 *
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_receive_handler_t)(dispatch_data_t content,
													  uint16_t vlan_tag,
													  _Nonnull nw_ethernet_address_t local_address,
													  _Nonnull nw_ethernet_address_t remote_address);

/*!
 * @function nw_ethernet_channel_set_receive_handler
 *
 * @abstract
 *		Sets the Ethernet channel receive handler. Should be called before nw_ethernet_channel_start.
 *
 * @param ethernet_channel
 *		The Ethernet channel object.
 *
 * @param handler
 *		The event handler to call when the Ethernet channel receives a new frame.
 *		Pass NULL to remove the receive handler.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_receive_handler(nw_ethernet_channel_t ethernet_channel,
										_Nullable nw_ethernet_channel_receive_handler_t handler);

/*!
 * @typedef nw_ethernet_channel_send_completion_t
 * @abstract
 *		A send completion is invoked exactly once for a call to nw_ethernet_channel_send().
 *		The completion indicates that the sent Ethernet frame has been processed by the stack
 *		(not necessarily that it has left the host), or else an error has occurred during
 *		sending.
 *
 * @param error
 *		An error will be sent if the associated frame could not be fully sent before an
 *		error occurred. An error will be sent for any outstanding sends when the channel
 *		is cancelled.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_send_completion_t)(_Nullable nw_error_t error);

/*!
 * @function nw_ethernet_channel_send
 *
 * @abstract
 *		Send an Ethernet frame on a channel.  This must be called after the channel
 *      becomes ready.  This is an asynchronous send and the completion block can be used
 *      to determine when the send is complete.
 *
 * @param ethernet_channel
 *		The ethernet_channel object on which to send frame.
 *
 * @param content
 *		An Ethernet payload to send.
 *
 * @param vlan_tag
 *      The vlan tag of the frame, 0 if there is no vlan tag.
 *
 * @param remote_address
 *		Remote Ethernet address for this Ethernet frame.  This is a required parameter.
 *      Note that the local Ethernet address will be the Ethernet address of the specified
 *      interface of this Ethernet channel.
 *
 * @param completion
 *		A callback to be called when the data has been sent, or an error has occurred.
 *		This callback does not indicate that the remote side has acknowledged the data.
 *		This callback does indicate that the data has been sent.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_send(nw_ethernet_channel_t ethernet_channel,
						 dispatch_data_t content,
						 uint16_t vlan_tag,
						 _Nonnull nw_ethernet_address_t remote_address,
						 nw_ethernet_channel_send_completion_t completion);

#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_ETHERNET_CHANNEL_H__ */
// ==========  Network.framework/Headers/framer_options.h
//
//  framer_options.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_FRAMER_OPTIONS_H__
#define __NW_FRAMER_OPTIONS_H__

#ifndef __NW_INDIRECT__
#error "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/endpoint.h>
#include <Network/parameters.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

/*!
 * @typedef nw_framer_t
 * @abstract
 *		A Network Framer is an instance of a protocol in a connection's protocol
 *		stack that parses and writes messages on top of a transport protocol, such
 *		as a TCP stream. A framer can add and parse headers or delimiters around
 *		application data to provide a message-oriented abstraction.
 *
 *		In order to create a framer protocol, first define it using
 *		nw_framer_create_definition(). This can be used to create options with
 *		nw_framer_create_options(), which can be added to an nw_protocol_stack_t.
 *		The callbacks and actions for the framer's protocol instance can be
 *		set once an instance of the framer is delivered with the start_handler.
 *
 *		In order to send and receive framer messages on an nw_connection_t, use
 *		nw_framer_message_t as part of a nw_content_context_t.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_FRAMER_IMPL
NW_OBJECT_DECL(nw_framer);
#endif // NW_FRAMER_IMPL

NW_ASSUME_NONNULL_BEGIN

#pragma mark - Messages

/*!
 * @typedef nw_framer_message_t
 * @abstract
 *		A framer message is an instance of protocol metadata associated
 *		with the definition of a framer, created by nw_framer_create_definition().
 */
typedef nw_protocol_metadata_t nw_framer_message_t;

/*!
 * @function nw_framer_protocol_create_message
 *
 * @abstract
 *		Create an instance of a framer message on which per-
 *		message options can be configured when sending data
 *		on a connection. This is intended to be used by the
 *		application above the connection to send message data
 *		down to the framer protocol instance.
 *
 * @param definition
 *		The framer protocol definition, as retrieved from
 *		nw_protocol_options_copy_definition() on the framer options.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_framer_message_t
nw_framer_protocol_create_message(nw_protocol_definition_t definition);

/*!
 * @function nw_protocol_metadata_is_framer_message
 *
 * @abstract
 *		Checks if a protocol metadata object is a framer protocol
 *		message. This indicates whether or not it is compatible
 *		with the framer message setters and accessors.
 *
 * @param metadata
 *		The protocol metadata to check.
 *
 * @result
 *		Returns true if the metadata is associated with a framer
 *		protocol definition, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_protocol_metadata_is_framer_message(nw_protocol_metadata_t metadata);

/*!
 * @function nw_framer_message_create
 *
 * @abstract
 *		Create a framer message, given a framer instance. This
 *		is intended to be used within the implementation of
 *		the framer protocol to create messages that are delivered
 *		as input to the application.
 *
 * @param framer
 *		The framer instance object.
 *
 * @result
 *		Returns a retained framer message object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_framer_message_t
nw_framer_message_create(nw_framer_t framer);

#ifdef __BLOCKS__

/*!
 * @typedef nw_framer_message_dispose_value_t
 *
 * @abstract
 *		A block to be invoked when a value stored in a framer message is disposed.
 *		If the value was created using malloc(), for example, it should be freed here.
 *
 * @param value
 *		A pointer to the stored message value.
 */
typedef void (^nw_framer_message_dispose_value_t)(void *value);

/*!
 * @function nw_framer_message_set_value
 *
 * @abstract
 *		Set a key-value pair on a framer message, with a custom
 *		dispose function for the value.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param value
 *		A pointer to the value to store.
 *
 * @param dispose_value
 *		A block to invoke to dispose the stored value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_message_set_value(nw_framer_message_t message,
							const char *key,
							void * _Nullable value,
							_Nullable nw_framer_message_dispose_value_t dispose_value);

/*!
 * @function nw_framer_message_access_value
 *
 * @abstract
 *		Access the value with a key on a framer message.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param access_value
 *		A block to invoke inline with the pointer to the stored value.
 *		This pointer may be NULL if no value is stored for the key.
 *
 * @return
 *		Returns the boolean value returned by the access_value block,
 *		or else false if the parameters were invalid.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_message_access_value(nw_framer_message_t message,
							   const char *key,
							   NW_NOESCAPE bool (^access_value)(const void * _Nullable value));

#endif // __BLOCKS__

#ifdef __OBJC__

/*!
 * @function nw_framer_message_set_object_value
 *
 * @abstract
 *		Set a key-value pair on a framer message, where the
 *		value is a reference-counted object.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param value
 *		A reference counted object to store.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_message_set_object_value(nw_framer_message_t message,
								   const char *key,
								   _Nullable id value);

/*!
 * @function nw_framer_message_copy_object_value
 *
 * @abstract
 *		Copy the stored object value using a key on a framer message.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @return
 *		Returns a reference counted object with a +1 reference count,
 *		or NULL if no value was found for the specified key.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable id
nw_framer_message_copy_object_value(nw_framer_message_t message,
									const char *key);

#endif // __OBJC__

#pragma mark - Framer Options

#ifdef __BLOCKS__

typedef enum {
	nw_framer_start_result_ready = 1,
	nw_framer_start_result_will_mark_ready = 2,
} nw_framer_start_result_t;

/*!
 * @typedef nw_framer_start_result_t
 *
 * @abstract
 *		A block to be invoked when starting a new instance of the framer
 *		protocol. This may occur more than once for a single nw_connection.
 *
 * @param framer
 *		A new instance of the framer protocol. This handle should be used
 *		to set callbacks, such as with nw_framer_set_input_handler()
 *		and nw_framer_set_output_handler(); and to perform actions, such
 *		as nw_framer_deliver_input() and nw_framer_write_output().
 *
 * @result
 *		Return whether or not the start should implicitly mark the protocol
 *		as "ready" using nw_framer_start_result_ready, or that the protocol
 *		will call nw_framer_mark_ready() later using
 *		nw_framer_start_result_will_mark_ready.
 */
typedef nw_framer_start_result_t (^nw_framer_start_handler_t)(nw_framer_t framer);

/*!
 * @define NW_FRAMER_CREATE_FLAGS_DEFAULT
 * @discussion Empty flags to define default options on a framer protocol.
 */
#define NW_FRAMER_CREATE_FLAGS_DEFAULT				0x00

/*!
 * @function nw_framer_create_definition
 *
 * @abstract
 *		Create a protocol definition for a custom framer protocol.
 *
 * @param identifier
 *		A string identifier used to name this framer protocol. This does not
 *		define uniqueness, and is primarily used for logging and debugging.
 *
 * @param flags
 *		Flags to describe extended options on framer protocol behavior,
 *		all prefixed with "NW_FRAMER_CREATE_FLAGS_".
 *
 * @param start_handler
 *		A block to be invoked when starting a new instance of the framer
 *		protocol. This may occur more than once for a single nw_connection.
 *
 * @result
 *		Returns a retained protocol definition that can be used with protocol
 *		options and metadata.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_framer_create_definition(const char *identifier,
							uint32_t flags,
							nw_framer_start_handler_t start_handler);

/*!
 * @function nw_framer_create_options
 *
 * @abstract
 *		Create protocol options from a framer definition. This object can
 *		be added to an nw_protocol_stack_t to be used in an nw_connection_t
 *		or an nw_listener_t.
 *
 * @param framer_definition
 *		A protocol definition created with nw_framer_create_definition().
 *
 * @result
 *		Returns a retained protocol options object to add into a protocol
 *		stack.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_framer_create_options(nw_protocol_definition_t framer_definition);

#pragma mark - Framer Implementation Callbacks

/*!
 * @typedef nw_framer_input_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever new input
 *		data is available to be parsed. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_input() and nw_framer_deliver_input().
 *
 *		Each invocation represents new data being available
 *		to read from the network. This data may be insufficient
 *		to complete a message, or may contain multiple messages.
 *		Implementations are expected to try to parse messages
 *		in a loop until parsing fails to read enough to continue.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @result
 *		Return a hint of the number of bytes that should be present
 *		before invoking this handler again. Returning 0 indicates
 *		that the handler should be invoked once any data is available.
 */
typedef size_t (^nw_framer_input_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_input_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever new input
 *		data is available to be parsed. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_input() and nw_framer_deliver_input().
 *
 *		This setter is required, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param input_handler
 *		The block to invoke whenever new input data is available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_input_handler(nw_framer_t framer,
							nw_framer_input_handler_t input_handler);

/*!
 * @typedef nw_framer_output_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever an output
 *		message is ready to be sent. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_output() and nw_framer_write_output().
 *
 *		Each invocation represents a single complete or partial
 *		message that is being sent. The implementation is
 *		expected to write this message or let it be dropped
 *		in this handler.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @param message
 *		The framer message being sent.
 *
 * @param message_length
 *		The length of the data associated with this message send.
 *		If the message is not complete, the length represents the
 *		partial message length being sent, which may be smaller
 *		than the complete message length.
 *
 * @param is_complete
 *		A boolean indicating whether or not the message is now complete.
 */
typedef void (^nw_framer_output_handler_t)(nw_framer_t framer,
										   nw_framer_message_t message,
										   size_t message_length,
										   bool is_complete);

/*!
 * @function nw_framer_set_output_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever an output
 *		message is ready to be sent. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_output() and nw_framer_write_output().
 *
 *		This setter is required, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param output_handler
 *		The block to invoke whenever a new output message is ready
 *		to be sent.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_output_handler(nw_framer_t framer,
							 nw_framer_output_handler_t output_handler);

/*!
 * @typedef nw_framer_wakeup_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever the wakeup timer
 *		set via nw_framer_schedule_wakeup() fires. This is intended to
 *		be used for sending keepalives or other control traffic.
 *
 * @param framer
 *		The instance of the framer protocol.
 */
typedef void (^nw_framer_wakeup_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_wakeup_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever the wakeup timer
 *		set via nw_framer_schedule_wakeup() fires. This is intended to
 *		be used for sending keepalives or other control traffic.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param wakeup_handler
 *		The block to invoke whenever the timeout set by
 *		nw_framer_schedule_wakeup() is reached.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_wakeup_handler(nw_framer_t framer,
							 nw_framer_wakeup_handler_t wakeup_handler);

/*!
 * @typedef nw_framer_stop_handler_t
 *
 * @abstract
 *		A handler block to be invoked when the connection
 *		is being disconnected, to allow the framer implementation
 *		a chance to send any final data.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @result
 *		Return true if the framer is done and the connection
 *		can be fully disconnected, or false the stop should
 *		be delayed. If false, the implementation must later
 *		call nw_framer_mark_failed_with_error().
 */
typedef bool (^nw_framer_stop_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_stop_handler
 *
 * @abstract
 *		Set a handler block to be invoked when the connection
 *		is being disconnected, to allow the framer implementation
 *		a chance to send any final data.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param stop_handler
 *		The block to invoke when the connection is disconnected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_stop_handler(nw_framer_t framer,
						   nw_framer_stop_handler_t stop_handler);

/*!
 * @typedef nw_framer_cleanup_handler_t
 *
 * @abstract
 *		A handler block to be invoked when the protocol stack
 *		is being torn down and deallocated. This is the opportunity
 *		for the framer implementation to release any state it may
 *		have saved.
 *
 * @param framer
 *		The instance of the framer protocol.
 */
typedef void (^nw_framer_cleanup_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_cleanup_handler
 *
 * @abstract
 *		Set a handler block to be invoked when the protocol stack
 *		is being torn down and deallocated. This is the opportunity
 *		for the framer implementation to release any state it may
 *		have saved.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param cleanup_handler
 *		The block to invoke when the protocol stack is being deallocated.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_cleanup_handler(nw_framer_t framer,
							  nw_framer_cleanup_handler_t cleanup_handler);

#pragma mark - Framer Implementation Actions

/*!
 * @function nw_framer_mark_ready
 *
 * @abstract
 *		Mark the connection associated with the framer instance
 *		as ready (see nw_connection_state_ready). This is intended
 *		to be used by protocols that require a handshake before being
 *		able to send application data. This should only be called
 *		if the return value to the nw_framer_start_handler_t block
 *		was nw_framer_start_result_will_call_ready.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_mark_ready(nw_framer_t framer);

/*!
 * @function nw_framer_prepend_application_protocol
 *
 * @abstract
 *		Dynamically add a protocol to a connection establishment
 *		attempt "above" the framer protocol. This means that the
 *		protocol above will start running once the framer becomes
 *		ready by calling nw_framer_mark_ready(). This can only
 *		be used with framers that return a value of
 *		nw_framer_start_result_will_call_ready to their start
 *		handlers. An example of using this functionality is
 *		adding a security protocol, like TLS, above a framer
 *		once that framer completes its initial handshake.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param protocol_options
 *		Protocol options for an application protocol to dynamically
 *		add "above" the framer.
 *
 * @result Returns true if the protocol was successfully added,
 *		or false it it could not be added. This will fail if
 *		the framer is already marked ready.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_prepend_application_protocol(nw_framer_t framer,
									   nw_protocol_options_t protocol_options);

/*!
 * @function nw_framer_mark_failed_with_error
 *
 * @abstract
 *		Mark the connection associated with the framer instance
 *		as failed (see nw_connection_state_failed).
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param error_code
 *		An error code to describe why the connection failed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_mark_failed_with_error(nw_framer_t framer, int error_code);

/*!
 * @typedef nw_framer_parse_completion_t
 *
 * @abstract
 *		A completion block that is invoked inline to parse available
 *		bytes, either input or output. This is the way a framer can
 *		access the underlying buffer for data being sent or received.
 *		The block has a side effect of advancing the parsing cursor
 *		by the number of bytes specified in the return value.
 *
 * @param buffer
 *		The buffer of bytes being sent or received.
 *
 * @param buffer_length
 *		The number of valid bytes in buffer.
 *
 * @param is_complete
 *		The boolean indicating if this section of the buffer indicates
 *		the end of a message or stream.
 *
 * @result
 *		Return the number of bytes by which to advance the input or
 *		output cursor. For example, if nw_framer_parse_input() is called
 *		and the completion returns 0, calling nw_framer_parse_input() again
 *		will allow the implementation to start parsing again at the same
 *		start location. However, if the completion returns 10, the next
 *		call to nw_framer_parse_input() will return bytes starting from 10
 *		bytes beyond the previous call.
 *
 *		The cursors also define the offsets at which data being delivered
 *		or written using nw_framer_deliver_input_no_copy() and
 *		nw_framer_write_output_no_copy() will start.
 *
 *		The returned value for incrementing the cursor may be larger than
 *		the length of the buffer just parsed. This allows an implementation
 *		to "skip" ahead by a number of bytes if it knows it does not
 *		need to parse more.
 */
typedef size_t (^nw_framer_parse_completion_t)(uint8_t * _Nullable buffer,
											   size_t buffer_length,
											   bool is_complete);

/*!
 * @function nw_framer_parse_input
 *
 * @abstract
 *		Parse currently available input from the location of the input
 *		cursor in the stream or message being parsed.
 *
 *		The parse completion block will always be invoked inline exactly once.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param minimum_incomplete_length
 *		The minimum number of bytes to parse. If this amount is
 *		not available, the parse completion block will be invoked
 *		with 0 bytes.
 *
 * @param maximum_length
 *		The maximum number of bytes to parse as a contiguous buffer.
 *		If temp_buffer is not NULL, then this represents the length
 *		of valid bytes in temp_buffer.
 *
 * @param temp_buffer
 *		A buffer provided by the caller to copy parse bytes into.
 *		If it is not NULL, it must have at least maximum_length bytes
 *		available, and any parsed bytes will be copied into the buffer.
 *		If it is NULL, the buffer provided in the completion will not
 *		copy unless a copy is required to provide the minimum bytes
 *		as a contiguous buffer. The temp_buffer allows the caller to
 *		guarantee alignment properties of the buffer it parses.
 *
 * @param parse
 *		The completion that provides the bytes to parse, which will
 *		be called exactly once.
 *
 * @result
 *		Returns true if the parse succeeded, or false if not enough
 *		bytes were available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_parse_input(nw_framer_t framer,
					  size_t minimum_incomplete_length,
					  size_t maximum_length,
					  uint8_t * _Nullable temp_buffer,
					  NW_NOESCAPE nw_framer_parse_completion_t parse);

/*!
 * @function nw_framer_deliver_input
 *
 * @abstract
 *		Deliver arbitrary data to the application. This is intended to
 *		deliver any data that is generated or transformed by the
 *		protocol instance. It will incur a copy of bytes.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param input_buffer
 *		The bytes to deliver to the application. This must be non-NULL.
 *		If an empty message needs to be delivered, use
 *		nw_framer_deliver_input_no_copy().
 *
 * @param input_length
 *		The length of input_buffer. This must be non-zero.
 *
 * @param message
 *		The message to associate with the received data.
 *
 * @param is_complete
 *		A boolean indicating whether or not this data represents
 *		the end of the message.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_deliver_input(nw_framer_t framer,
						const uint8_t *input_buffer,
						size_t input_length,
						nw_framer_message_t message,
						bool is_complete);

/*!
 * @function nw_framer_deliver_input_no_copy
 *
 * @abstract
 *		Deliver bytes directly to the application without any
 *		transformation or copy. The bytes will start at the current
 *		input cursor used for parsing, and will implicitly advance
 *		the cursor by the length being delivered.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param input_length
 *		The number of input bytes to deliver. This will advance
 *		the parsing cursor by the specified number of bytes.
 *
 *		The length may be 0, which can be used to indicate the
 *		end of the message if is_complete is set.
 *
 * @param message
 *		The message to associate with the received data.
 *
 * @param is_complete
 *		A boolean indicating whether or not this data represents
 *		the end of the message.
 *
 * @result
 *		Returns true if the input was delivered immediately, or
 *		false if it will be delivered once more bytes become available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_deliver_input_no_copy(nw_framer_t framer,
								size_t input_length,
								nw_framer_message_t message,
								bool is_complete);

/*!
 * @function nw_framer_pass_through_input
 *
 * @abstract
 *		Mark the input side of the framer as a pass-through, which
 *		means the framer will not be notified of any further input
 *		data.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_pass_through_input(nw_framer_t framer);

/*!
 * @function nw_framer_parse_output
 *
 * @abstract
 *		Parse currently available output from a message from the location
 *		of the output cursor in the message being parsed.
 *
 *		The parse completion block will always be invoked inline exactly once.
 *
 *		This function must only be called from within the output handler
 *		set with nw_framer_set_output_handler().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param minimum_incomplete_length
 *		The minimum number of bytes to parse. If this amount is
 *		not available, the parse completion block will be invoked
 *		with 0 bytes.
 *
 * @param maximum_length
 *		The maximum number of bytes to parse as a contiguous buffer.
 *		If temp_buffer is not NULL, then this represents the length
 *		of valid bytes in temp_buffer.
 *
 * @param temp_buffer
 *		A buffer provided by the caller to copy parse bytes into.
 *		If it is not NULL, it must have at least maximum_length bytes
 *		available, and any parsed bytes will be copied into the buffer.
 *		If it is NULL, the buffer provided in the completion will not
 *		copy unless a copy is required to provide the minimum bytes
 *		as a contiguous buffer. The temp_buffer allows the caller to
 *		guarantee alignment properties of the buffer it parses.
 *
 * @param parse
 *		The completion that provides the bytes to parse, which will
 *		be called exactly once.
 *
 * @result
 *		Returns true if the parse succeeded, or false if not enough
 *		bytes were available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_parse_output(nw_framer_t framer,
					   size_t minimum_incomplete_length,
					   size_t maximum_length,
					   uint8_t * _Nullable temp_buffer,
					   NW_NOESCAPE nw_framer_parse_completion_t parse);

/*!
 * @function nw_framer_write_output
 *
 * @abstract
 *		Write arbitrary bytes as part of an outbound message. This
 *		is intended to be used for adding headers around application
 *		data, or writing any other data that is generated or transformed
 *		by the protocol instance. It does not pass along data directly
 *		from the application.
 *
 *		This variant will copy bytes.
 *
 *		This function may be called as part of any framer callback,
 *		not just the output handler.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_buffer
 *		The bytes to write.
 *
 * @param output_length
 *		The length of output_buffer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_write_output(nw_framer_t framer,
					   const uint8_t *output_buffer,
					   size_t output_length);

/*!
 * @function nw_framer_write_output_data
 *
 * @abstract
 *		Write arbitrary bytes as part of an outbound message. This
 *		is intended to be used for adding headers around application
 *		data, or writing any other data that is generated or transformed
 *		by the protocol instance. It does not pass along data directly
 *		from the application.
 *
 *		This variant is the same as nw_framer_write_output(), but allows
 *		the implementation to pass its buffer as a dispatch_data_t to
 *		avoid a copy.
 *
 *		This function may be called as part of any framer callback,
 *		not just the output handler.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_data
 *		A dispatch_data_t to write.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_write_output_data(nw_framer_t framer,
							dispatch_data_t output_data);

/*!
 * @function nw_framer_write_output_no_copy
 *
 * @abstract
 *		Write bytes directly from the application without any
 *		transformation or copy. The bytes will start at the current
 *		output cursor used for parsing, and will implicitly advance
 *		the cursor by the length being written.
 *
 *		This function must only be called from within the output handler
 *		set with nw_framer_set_output_handler().
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_length
 *		The number of application bytes to write. This will advance
 *		the parsing cursor by the specified number of bytes.
 *
 * @return
 *		Returns true if the write could be completed, otherwise
 *		false if the call was made from an invalid context
 *		or with an invalid number of bytes.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_write_output_no_copy(nw_framer_t framer,
							   size_t output_length);

/*!
 * @function nw_framer_pass_through_output
 *
 * @abstract
 *		Mark the output side of the framer as a pass-through, which
 *		means the framer will not be notified of any further output
 *		data.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_pass_through_output(nw_framer_t framer);

#define NW_FRAMER_WAKEUP_TIME_FOREVER (~0ull)

/*!
 * @function nw_framer_schedule_wakeup
 *
 * @abstract
 *		Schedule a wakeup on the framer instance for a number of
 *		milliseconds into the future. If this is called multiple
 *		times before the timeout is reached, the new value replaces
 *		the previous value.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param milliseconds
 *		The number of milliseconds into the future at which to
 *		invoke the wakeup handler. Pass the reserved value
 *		NW_FRAMER_WAKEUP_TIME_FOREVER to push the wakeup timer
 *		out to "forever", effectively unscheduling the timer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_schedule_wakeup(nw_framer_t framer,
						  uint64_t milliseconds);

/*!
 * @typedef nw_framer_block_t
 *
 * @abstract
 *		A block to perform actions on a framer's scheduling context.
 */
typedef void (^nw_framer_block_t)(void);

/*!
 * @function nw_framer_async
 *
 * @abstract
 *		Schedule a block asynchronously on the framer instance. This
 *		must be used anytime the caller wants to perform any other
 *		action on the framer instance while not directly in the callstack
 *		of a callback from the framer.
 *
 * @param framer
 *		The framer instance object.
 *
 * @param async_block
 *		A block to execute on the correct scheduling context for the
 *		framer instance.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_async(nw_framer_t framer,
				nw_framer_block_t async_block);

#endif // __BLOCKS__

#pragma mark - Framer Implementation Accessors

/*!
 * @function nw_framer_copy_remote_endpoint
 *
 * @abstract
 *		Access the remote endpoint being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained endpoint object representing
 *		the remote side of a connection.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_framer_copy_remote_endpoint(nw_framer_t framer);

/*!
 * @function nw_framer_copy_local_endpoint
 *
 * @abstract
 *		Access the local endpoint being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained endpoint object representing
 *		the local side of a connection.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_framer_copy_local_endpoint(nw_framer_t framer);

/*!
 * @function nw_framer_copy_parameters
 *
 * @abstract
 *		Access the parameters being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained parameters object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_framer_copy_parameters(nw_framer_t framer);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_FRAMER_OPTIONS_H__
