// ==========  CoreNFC.framework/Headers/NFCReaderSession.h
//
//  NFCReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCReaderSession_h
#define NFCReaderSession_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif

#import <Foundation/Foundation.h>
#import <dispatch/dispatch.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCReaderSession;
@protocol NFCTag;

#pragma mark - NFCReaderSession, protocol of a reader session

/*!
 * @protocol NFCReaderSession
 *
 * @discussion General reader session functions
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCReaderSession <NSObject>

/*!
 * @property ready
 *
 * @return <i>YES</i> if the reader session is started and ready to use.
 *
 * @discussion The RF discovery polling begins immediately when a reader session is activated successfully.
 *             The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
@property (nonatomic, getter=isReady, readonly) BOOL ready;

/*!
 * @property alertMessage
 *
 * @discussion Descriptive text message that is displayed on the alert action sheet once tag scanning has started.  The string can be update
 *             dynamically in any thread context as long as the session is valid.  This should be set prior to calling @link beginSession @link/ to display
 *             the correct message.  Use this string to provide additional context about the NFC reader mode operation.
 */
@property (nonatomic, copy) NSString *alertMessage;

/*!
 * @method beginSession:
 *
 * @discussion      Starts the session.  The @link [NFCReaderSessionDelegate readerSessionDidBecomeActive:] @link/ will be called when the reader session
 *                  is activated successfully.  @link [NFCReaderSessionDelegate readerSession:didDetectTags:] @link/ will return tag objects that are
 *                  conformed to the @link NFCTag @link/ protocol.  @link [NFCReaderSessionDelegate readerSession:didInvalidateWithError:] will return
 *                  errors related to the session start.
 */
- (void)beginSession;

/*!
 * @method invalidateSession
 *
 * @discussion Closes the reader session.  The session cannot be re-used.
 */
- (void)invalidateSession;

@end

#pragma mark - NFCReaderSessionDelegate, Reader session callback delegate

/*!
 * @protocol NFCReaderSession
 *
 * @discussion General reader session callbacks
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCReaderSessionDelegate <NSObject>
@required

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 *                  The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
- (void)readerSessionDidBecomeActive:(NFCReaderSession *)session;

/*!
 * @method readerSession:didDetectTags:
 *
 * @param session   The session object used for tag detection.
 * @param tags      Array of @link NFCTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) in the polling sequence.
 */
- (void)readerSession:(NFCReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCTag>> *)tags;

/*!
 * @method readerSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)readerSession:(NFCReaderSession *)session didInvalidateWithError:(NSError *)error;

@end

#pragma mark - NFCReaderSession, Reader session base class

/*!
 * @class NFCReaderSession
 *
 * @discussion      This represents a NFC reader session for processing tags; this base class cannot be instantiate. Only one NFCReaderSession 
 *                  can be active at any time in the system.  Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCReaderSession : NSObject<NFCReaderSession>

@property (nonatomic, weak, readonly) id delegate;

/*!
 * @property sessionQueue
 *
 * @discussion  The NFCReaderSessionDelegate delegate callbacks and the completion block handlers for tag operation will be dispatched on this queue.
 */
@property (nonatomic, readonly) dispatch_queue_t sessionQueue;

- (instancetype)init NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END

#endif /* NFCReaderSession_h */
// ==========  CoreNFC.framework/Headers/CoreNFC.h
//
//  CoreNFC.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef CoreNFC_H
#define CoreNFC_H

#import <CoreNFC/NFCError.h>
#import <CoreNFC/NFCReaderSession.h>
#import <CoreNFC/NFCTag.h>
#import <CoreNFC/NFCNDEFReaderSession.h>
#if __has_include(<CoreNFC/NFCISO15693Tag.h>)
#import <CoreNFC/NFCISO15693Tag.h>
#endif
#if __has_include(<CoreNFC/NFCISO15693ReaderSession.h>)
#import <CoreNFC/NFCISO15693ReaderSession.h>
#endif
#endif
// ==========  CoreNFC.framework/Headers/NFCNDEFReaderSession.h
//
//  NFCNDEFReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCNDEFReaderSession_h
#define NFCNDEFReaderSession_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif

#import <Foundation/Foundation.h>

@class NFCReaderSession;
@class NFCNDEFReaderSession;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @discussion Type Name Format value defined by NFC Data Exchange Format (NDEF) Technical Specification
 *             from NFC Forum.
 */
typedef NS_ENUM(uint8_t, NFCTypeNameFormat) {
    NFCTypeNameFormatEmpty             = 0x00,
    NFCTypeNameFormatNFCWellKnown      = 0x01,
    NFCTypeNameFormatMedia             = 0x02,
    NFCTypeNameFormatAbsoluteURI       = 0x03,
    NFCTypeNameFormatNFCExternal       = 0x04,
    NFCTypeNameFormatUnknown           = 0x05,
    NFCTypeNameFormatUnchanged         = 0x06
};

/*!
 * @class NFCNDEFPayload
 *
 * @discussion A NDEF message payload consists of Type Name Format, Type, Payload Identifier, and Payload data.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFPayload : NSObject<NSSecureCoding>

@property (nonatomic, assign) NFCTypeNameFormat typeNameFormat;
@property (nonatomic, copy) NSData *type;
@property (nonatomic, copy) NSData *identifier;
@property (nonatomic, copy) NSData *payload;

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 * @class NFCNDEFMessage
 *
 * @discussion A NDEF message consists of payload records.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFMessage : NSObject<NSSecureCoding>

@property (nonatomic, copy) NSArray<NFCNDEFPayload *>* records;

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 * @protocol NFCNDEFReaderSessionDelegate
 *
 * @discussion NDEF reader session callbacks.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCNDEFReaderSessionDelegate <NSObject>

@required

/*!
 * @method readerSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didInvalidateWithError:(NSError *)error;

/*!
 * @method readerSession:didDetectNDEFs:
 *
 * @param session   The session object used for tag detection.
 * @param messages  Array of @link NFCNDEFMessage @link/ objects. The order of the discovery on the tag is maintained.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) with NDEF messages in the polling sequence.  Polling
 *                  is automatically restarted once the detected tag is removed from the reader's read range.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didDetectNDEFs:(NSArray<NFCNDEFMessage *> *)messages;

@end

#pragma mark - NDEF reader session

/*!
 * @class NFCNDEFReaderSession
 *
 * @discussion Reader session for processing NFC Data Exchange Format (NDEF) tags.  This session requires the "com.apple.developer.nfc.readersession.formats"
 *             entitlement in your process.  In addition your application's Info.plist must contain a non-empty usage description string.
 *
 * NOTE:
 * Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFReaderSession : NFCReaderSession

/*!
 * @property readingAvailable
 *
 * @discussion YES if device supports NFC tag reading.
 */
@property (class, nonatomic, readonly) BOOL readingAvailable;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithDelegate:queue:
 *
 * @param delegate  The session will hold a weak ARC reference to this @link NFCNDEFReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCNDEFReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 * @param invalidateAfterFirstRead  Session will automatically invalidate after the first NDEF tag is read successfully when this is set to YES, and -readerSession:didInvalidateWithError:
 *                                  will return NFCReaderSessionInvalidationErrorFirstNDEFTagRead in this case.
 *
 * @return          A new NFCNDEFReaderSession instance.
 *
 * @discussion      A NDEF reader session will automatically scan and detect NFC Forum tags that contain a valid NDEF message.  NFC Forum Tag type 1 to 5 that 
 *                  is NDEF formatted are supported.  A modal system UI will present once -beginSession is called to inform the start of the session; the UI sheet
 *                  is automatically dismissed when the session is invalidated either by the user or by calling -invalidateSession.  The alertMessage property shall be set
 *                  prior to -beginSession to display a message on the action sheet UI for the tag scanning operation.
 *
 *                  The reader session has the following properties:
 *                  + An opened session has a 60 seconds time limit restriction after -beginSession is called; -readerSession:didInvalidateWithError: will return
 *                  NFCReaderSessionInvalidationErrorSessionTimeout error when the time limit is reached.
 *                  + Only 1 active reader session is allowed in the system; -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorSystemIsBusy
 *                  when a new reader session is initiated by -beginSession when there is an active reader session.  
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorUserCanceled when user clicks on the done button on the UI.
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly when the client application enters
 *                  the background state.
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderErrorUnsupportedFeature when 1) reader mode feature is not available on the hardware,
 *                  2) client application does not have the required entitlement.
 */
- (instancetype)initWithDelegate:(id<NFCNDEFReaderSessionDelegate>)delegate queue:(nullable dispatch_queue_t)queue invalidateAfterFirstRead:(BOOL)invalidateAfterFirstRead NS_DESIGNATED_INITIALIZER;

NS_ASSUME_NONNULL_END

@end

#endif
// ==========  CoreNFC.framework/Headers/NFCTag.h
//
//  NFCTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCTag_h
#define NFCTag_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum NFCTagType
 *
 * @constant NFCTagTypeISO15693    ISO15693 tag.
 */
typedef NS_ENUM(NSUInteger, NFCTagType) {
    NFCTagTypeISO15693 = 1,
};

@protocol NFCReaderSession;

/*!
 * @protocol NFCTag
 *
 * @discussion A NFC / RFID tag object conforms to this protocol.  The NFCReaderSession returns an instance of this type when a tag is detected.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCTag <NSObject, NSSecureCoding, NSCopying>

@required

/*!
 * @property type
 * 
 * @discussion See @link CNFCTagType @link/
 */
@property (nonatomic, readonly, assign) NFCTagType type;

/*!
 * @property    session
 *
 * @discussion  Session that provides this tag.
 */
@property (nonatomic, weak, readonly) id<NFCReaderSession> session;

/*!
 * @property available:
 *
 * @return      <i>YES</i> if tag is available in the current reader session.  A tag remove from the RF field will become
 *              unavailable.
 *
 * @discussion  Check whether a detected tag is available.
 */
@property (nonatomic, getter=isAvailable, readonly) BOOL available;

@end

#pragma mark - Tag command configuration

/*!
 * @interface   NFCTagCommandConfiguration
 *
 * @discussion  Define configuration parameters for tag commands.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCTagCommandConfiguration : NSObject<NSCopying>

/*!
 * @discussion  Maximum number of retries.  Valid value is 0 to 256.  Default is 0.
 */
@property (nonatomic, assign) NSUInteger maximumRetries;

/*!
 * @discussion  Delay in seconds before retry occurs.  Default is 0.
 */
@property (nonatomic, assign) NSTimeInterval retryInterval;

@end

NS_ASSUME_NONNULL_END

#endif /* NFCTag_h */
// ==========  CoreNFC.framework/Headers/NFCError.h
//
//  NFCError.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCError_h
#define NFCError_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCErrorDomain;

/*!
 * @enum NFCReaderError
 *
 * @discussion Possible errors returned by CoreNFC framework reader session.
 */
typedef NS_ERROR_ENUM(NFCErrorDomain, NFCReaderError) {
    NFCReaderErrorUnsupportedFeature = 1,
    NFCReaderErrorSecurityViolation,

    NFCReaderTransceiveErrorTagConnectionLost = 100,
    NFCReaderTransceiveErrorRetryExceeded,
    NFCReaderTransceiveErrorTagResponseError,

    NFCReaderSessionInvalidationErrorUserCanceled = 200,
    NFCReaderSessionInvalidationErrorSessionTimeout,
    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly,
    NFCReaderSessionInvalidationErrorSystemIsBusy,
    NFCReaderSessionInvalidationErrorFirstNDEFTagRead,

    NFCTagCommandConfigurationErrorInvalidParameters = 300,
};

#pragma mark - ISO15693 specific command response error code

/*!
 *  Key in NSError userInfo dictionary.  The corresponding value is the NSUInteger error code from tag's response.
 *  Refer to ISO15693 specification for the error code values.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCISO15693TagResponseErrorKey;


NS_ASSUME_NONNULL_END

#endif /* CNFCError_h */
// ==========  CoreNFC.framework/Headers/NFCISO15693ReaderSession.h
//
//  NFCISO15693ReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//
#ifndef NFCISO15693ReaderSession_h
#define NFCISO15693ReaderSession_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif

#import <Foundation/Foundation.h>

@protocol NFCReaderSessionDelegate;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - ISO15693 reader session

/*!
 * @class NFCISO15693ReaderSession
 *
 * @discussion Reader session for processing ISO15693 tags.  @link [NFCReaderSessionDelegate readerSession:didDetectTags:] @link/ will return tag objects that
 *             are conformed to the NFCISO15693Tag protocol.  This session requires the "com.apple.developer.nfc.readersession.formats" entitlement in your process.
 *
 * NOTE:
 * Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693ReaderSession : NFCReaderSession

/*!
 * @property readingAvailable
 *
 * @discussion YES if device supports NFC tag reading.
 */
@property (class, nonatomic, readonly) BOOL readingAvailable;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithQueue:
 *
 * @param delegate  The session will hold a weak ARC reference to this @link NFCReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return          A new NFCISO15693ReaderSession instance.
 */
- (instancetype)initWithDelegate:(id<NFCReaderSessionDelegate>)delegate queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new tags.  Tags that are returned previously by @link [NFCReaderSessionDelegate readerSession:didDetectTags:]
 *             @link/ will become invalid, and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader.
 */
- (void)restartPolling;

NS_ASSUME_NONNULL_END

@end

#endif
// ==========  CoreNFC.framework/Headers/NFCISO15693Tag.h
//
//  NFCISO15693Tag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCISO15693Tag_h
#define NFCISO15693Tag_h

#ifndef CoreNFC_H
#error Please import <CoreNFC/CoreNFC.h> from your source file
#endif


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCTagCommandConfiguration;
@protocol NFCTag;

/*!
 * @class       NFCISO15693CustomCommandConfiguration
 *
 * @discussion  Configuration options for the Manufacturer Custom command.
 */

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693CustomCommandConfiguration : NFCTagCommandConfiguration

/*!
 * @discussion  Manufacturer code. Valid range is 0x00 to 0xFF.
 */
@property (nonatomic, assign) NSUInteger manufacturerCode;

/*!
 * @discussion  Manufacturer Custom Command Index.  Valid range is 0xA0 to 0xDF.
 */
@property (nonatomic, assign) NSUInteger customCommandCode;

/*!
 * @discussion  Custom request data.
 */
@property (nonatomic, copy) NSData * requestParameters;

/*!
 * @method initWithManufacturerCode:customCommandCode:requestParameters:
 *
 * @param manufacturerCode      8 bits manufacturer code.
 * @param customCommandCode     8 bits custom command code.  Valid range is 0xA0 to 0xDF.
 * @param requestParameters     Optional custom request parameters.
 *
 * @discussion  Initialize with default zero maximum retry and zero retry interval.
 */
- (instancetype)initWithManufacturerCode:(NSUInteger)manufacturerCode
                       customCommandCode:(NSUInteger)customCommandCode
                       requestParameters:(nullable NSData*)requestParameters;

/*!
 * @method initWithManufacturerCode:customCommandCode:requestParameters:maximumRetries:retryInterval:
 *
 * @param manufacturerCode      8 bits manufacturer code.
 * @param customCommandCode     8 bits custom command code.  Valid range is 0xA0 to 0xDF.
 * @param requestParameters     Optional custom request parameters.
 * @param maximumRetries        Maximum number of retry attempt when tag response is not recevied.
 * @param retryInterval         Time interval wait between each retry attempt.
 */
- (instancetype)initWithManufacturerCode:(NSUInteger)manufacturerCode
                       customCommandCode:(NSUInteger)customCommandCode
                       requestParameters:(nullable NSData*)requestParameters
                          maximumRetries:(NSUInteger)maximumRetries
                           retryInterval:(NSTimeInterval)retryInterval;
@end

/*!
 * @class       NFCISO15693ReadMultipleBlocksConfiguration
 *
 * @discussion  Configuration options for the Read Multiple Blocks command.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693ReadMultipleBlocksConfiguration : NFCTagCommandConfiguration

/*!
 * @discussion  Range to read in blocks.  Valid start index range is 0x00 to 0xFF.  Length shall not be 0.
 */
@property (nonatomic, assign) NSRange range;

/*!
 * @discussion  Number of blocks to read per Read Multiple Blocks command. This may be limited by the tag hardware.
 */
@property (nonatomic, assign) NSUInteger chunkSize;

/*!
 * @discussion  Initialize with default zero maximum retry and zero retry interval.
 */
- (instancetype)initWithRange:(NSRange)range
                    chunkSize:(NSUInteger)chunkSize;
/*!
 * @method initWithRange:chunkSize:maximumRetries:retryInterval:
 *
 * @param range             Read range specify by the starting block index and the total number of blocks.
 * @param chunkSize         Specify number of blocks parameter for the Read multiple blocks command.
 * @param maximumRetries    Maximum number of retry attempt when tag response is not recevied.
 * @param retryInterval     Time interval wait between each retry attempt.
 */
- (instancetype)initWithRange:(NSRange)range
                    chunkSize:(NSUInteger)chunkSize
               maximumRetries:(NSUInteger)maximumRetries
                retryInterval:(NSTimeInterval)retryInterval;

@end

/*!
 * @protocol NFCISO15693Tag
 *
 * @discussion  A @link NFCISO15693ReaderSession @link/ reader session returns an instance conforming to this protocol
 *              when a tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              [NFCISO15693ReaderSession sessionQueue] session work queue that is associated with the tag.
 *              This tag class requires the "com.apple.developer.nfc.readersession.iso15693.tag-identifiers" entitlement in your process.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO15693Tag <NFCTag>

@required

/*!
 * @discussion The 64 bit hardware UID of the tag. Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData * identifier;

/*!
 * @discussion  The IC manufacturer code (bits 56 – 49) in UID according to ISO/IEC 7816-6:2004.
 */
@property (nonatomic, readonly) NSUInteger icManufacturerCode;

/*!
 * @discussion  The IC serial number (bits 48 – 1) in UID assigned by the manufacturer.  Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData * icSerialNumber;

/*!
 * @method sendCustomCommandWithConfiguration:completionHandler:
 *
 * @param commandConfiguration  Configuration for the Manufacturer Custom Command.
 * @param completionHandler     Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                              A @link NFCISO15693TagResponseErrorDomain @link/ error is returned when the tag responded to the command
 *                              with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion Send a manufacturer dependent custom command using command code range from 0xA0 to 0xDF.  Refer to ISO15693-3
 *             specification for details.
 */
- (void)sendCustomCommandWithConfiguration:(NFCISO15693CustomCommandConfiguration *)commandConfiguration
                          completionHandler:(void(^)(NSData * customResponseParameters, NSError * _Nullable error))completionHandler;

/*!
 * @method readMultipleBlocksWithConfiguration:completionHandler:
 *
 * @param readConfiguration Configuration For the Read Multiple Blocks command.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCISO15693TagResponseErrorDomain @link/ error is returned when the tag responded to the command
 *                          with an error, and the error code value is defined in ISO15693-3 specification. Successfully read data blocks
 *                          will be return from NSData object.  All blocks are concatenated into the NSData object.
 *
 * @discussion  Performs read operation using Read Multiple Blocks command (0x23 command code) as defined in IOS15693-3 specification.
 *              Multiple Read Multiple Blocks commands will be sent if necessary to complete the operation.
 */
- (void)readMultipleBlocksWithConfiguration:(NFCISO15693ReadMultipleBlocksConfiguration *)readConfiguration
                           completionHandler:(void(^)(NSData * data, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO15693Tag_h */
