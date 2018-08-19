// ==========  Network.framework/Headers/connection.h
//
//  connection.h
//  Network
//
//  Copyright (c) 2015-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_H__
#define __NW_CONNECTION_H__

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
 *		There is no guarantee that any outstanding sends that have not yet send completion handlers
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
 *		The content may be NULL in two cases: (1) the receieve context (logical message) is now complete,
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
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_ERROR_H__
#define __NW_ERROR_H__

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
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_ADVERTISE_DESCRIPTOR_H__
#define __NW_ADVERTISE_DESCRIPTOR_H__

#include <Network/nw_object.h>

#include <sys/types.h>
#include <stdbool.h>

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
 *		Set the TXT record to use when initially registering the service.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify
 *
 * @param txt_record
 *		A pointer to the TXT record.
 *
 * @param txt_length
 *		The length of the TXT record.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_txt_record(nw_advertise_descriptor_t advertise_descriptor,
									   const void *txt_record,
									   size_t txt_length);

/*!
 * @function nw_advertise_descriptor_set_no_auto_rename
 *
 * @abstract
 *		Disable auto-rename for the Bonjour service registration.
 *		Auto-rename is enabled by default.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify
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
 *		The advertise descriptor to modify
 *
 * @result A boolean indicating if auto-rename is disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_advertise_descriptor_get_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor);

__END_DECLS
NW_ASSUME_NONNULL_END

#endif /* __NW_ADVERTISE_DESCRIPTOR_H__ */
// ==========  Network.framework/Headers/endpoint.h
//
//  endpoint.h
//  Network
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_ENDPOINT_H__
#define __NW_ENDPOINT_H__

#include <Network/nw_object.h>

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
 *		added to this enumeration, and some custom endpoint types may used
 *		values not defined in this enumeration.
 */
typedef enum {
	/*! @const nw_endpoint_type_invalid An invalid endpoint */
	nw_endpoint_type_invalid = 0,
	/*! @const nw_endpoint_type_invalid An IP Address + Port */
	nw_endpoint_type_address = 1,
	/*! @const nw_endpoint_type_invalid A Hostname + Port */
	nw_endpoint_type_host = 2,
	/*! @const nw_endpoint_type_invalid A Bonjour Service Name + Type + Domain */
	nw_endpoint_type_bonjour_service = 3,
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
 *		the type nw_endpoint_type_host.
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
 *		Retrieves the port for a network endpoint with
 *		the type nw_endpoint_type_host or nw_endpoint_type_address.
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

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_ENDPOINT_H__
// ==========  Network.framework/Headers/udp_options.h
//
//  udp_options.h
//  Network
//
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_UDP_OPTIONS_H__
#define __NW_UDP_OPTIONS_H__

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
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_LISTENER_H__
#define __NW_LISTENER_H__

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
// ==========  Network.framework/Headers/path.h
//
//  path.h
//  Network
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_H__
#define __NW_PATH_H__

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

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_H__) */

// ==========  Network.framework/Headers/content_context.h
//
//  content_context.h
//  Network
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_CONTENT_CONTEXT_H__
#define __NW_CONTENT_CONTEXT_H__

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
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_TLS_OPTIONS_H__
#define __NW_TLS_OPTIONS_H__

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
// ==========  Network.framework/Headers/interface.h
//
//  interface.h
//  Network
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//
#ifndef __NW_INTERFACE_H__
#define __NW_INTERFACE_H__

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
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_PROTOCOL_OPTIONS_H__
#define __NW_PROTOCOL_OPTIONS_H__

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
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_MONITOR_H__
#define __NW_PATH_MONITOR_H__

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
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_IP_OPTIONS_H__
#define __NW_IP_OPTIONS_H__

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
 *		be used, and will filter DNS results during connection establishement.
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
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_PARAMETERS_H__
#define __NW_PARAMETERS_H__

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
 *		block and operate on the the nw_protocol_options_t object. To disable TLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_tcp
 *		A block to configure TCP. To use the default TCP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the the nw_protocol_options_t object. It is invalid to try
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
 *		block and operate on the the nw_protocol_options_t object. To disable DTLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_udp
 *		A block to configure UDP. To use the default UDP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the the nw_protocol_options_t object. It is invalid to try
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
//  nw.h
//  Network
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_H__
#define __NW_H__

#ifndef __NW_INDIRECT__
#define __NW_INDIRECT__
#define __NW_SET_INDIRECT__
#endif // __NW_INDIRECT__

#include <Network/advertise_descriptor.h>
#include <Network/connection.h>
#include <Network/content_context.h>
#include <Network/endpoint.h>
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
#include <Network/udp_options.h>

#ifdef __NW_SET_INDIRECT__
#undef __NW_INDIRECT__
#endif // __NW_SET_INDIRECT__

#endif // __NW_NETWORK_BASE_H__
// ==========  Network.framework/Headers/nw_object.h
//
//  nw_object.h
//  Network
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#ifndef nw_object_h
#define nw_object_h

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
#  if defined(__OBJC__) && __has_attribute(ns_returns_retained)
#    define NW_RETURNS_RETAINED __attribute__((__ns_returns_retained__))
#  else // __OBJC__ && ns_returns_retained
#    define NW_RETURNS_RETAINED
#  endif // __OBJC__ && ns_returns_retained
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

#endif // nw_object_h
// ==========  Network.framework/Headers/tcp_options.h
//
//  tcp_options.h
//  Network
//
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_TCP_OPTIONS_H__
#define __NW_TCP_OPTIONS_H__

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
