// ==========  CoreNFC.framework/Headers/NFCReaderSession.h
//
//  NFCReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCReaderSession_h
#define NFCReaderSession_h

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

/*!
 * @method invalidateSessionWithErrorMessage:
 *
 * @discussion Closes the reader session.  The session cannot be re-used.  The specified error message and an error symbol will be displayed momentarily
 *             on the action sheet before it is automatically dismissed.
 */
- (void)invalidateSessionWithErrorMessage:(NSString *)errorMessage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

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
 * @method readerSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)readerSession:(NFCReaderSession *)session didInvalidateWithError:(NSError *)error;

@optional
/*!
 * @method readerSession:didDetectTags:
 *
 * @param session   The session object used for tag detection.
 * @param tags      Array of @link NFCTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) in the polling sequence.
 */
- (void)readerSession:(NFCReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCTag>> *)tags;

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
 * @property readingAvailable
 *
 * @discussion YES if device supports NFC tag reading.
 */
@property (class, nonatomic, readonly) BOOL readingAvailable;

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
#import <CoreNFC/NFCTagReaderSession.h>
#import <CoreNFC/NFCNDEFReaderSession.h>
#import <CoreNFC/NSUserActivity+CoreNFC.h>
#if __has_include(<CoreNFC/NFCISO15693Tag.h>)
#import <CoreNFC/NFCISO15693Tag.h>
#endif
#if __has_include(<CoreNFC/NFCISO15693ReaderSession.h>)
#import <CoreNFC/NFCISO15693ReaderSession.h>
#endif
#import <CoreNFC/NFCFeliCaTag.h>
#import <CoreNFC/NFCISO7816Tag.h>
#import <CoreNFC/NFCMiFareTag.h>
#import <CoreNFC/NFCNDEFTag.h>
#import <CoreNFC/NFCNDEFPayload.h>
#import <CoreNFC/NFCNDEFMessage.h>
#import <CoreNFC/NFCVASReaderSession.h>
#endif
// ==========  CoreNFC.framework/Headers/NFCISO7816Tag.h
//
//  NFCISO7816Tag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCISO7816Tag_h
#define NFCISO7816Tag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class NFCISO7816APDU
 *
 * @discussion ISO7816 Application Data Unit (APDU).
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO7816APDU : NSObject<NSCopying>
/*!
 * @property instructionClass   Class (CLA) byte.
 */
@property (nonatomic, readonly, assign) uint8_t instructionClass;

/*!
 * @property instructionCode    Instruction (INS) byte.
 */
@property (nonatomic, readonly, assign) uint8_t instructionCode;

/*!
 * @property p1Parameter     P1 parameter.
 */
@property (nonatomic, readonly, assign) uint8_t p1Parameter;

/*!
 * @property p2Parameter     P2 parameter.
 */
@property (nonatomic, readonly, assign) uint8_t p2Parameter;

/*!
 * @property data   Data field; nil if data field is absent
 */
@property (nonatomic, readonly, copy, nullable) NSData *data;

/*!
 * @property expectedResponseLength     Expected response length (Le).  -1 means no response data field is expected.
 */
@property (readonly, assign, nonatomic) NSInteger expectedResponseLength;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithInstructionClass:instructionCode:p1Parameter:p2Parameter:data:expectedResponseLength:
 *
 * @param instructionClass  Instruction class (CLA) byte
 * @param instructionCode   Instruction code (INS) byte
 * @param p1Parameter       P1 parameter byte
 * @param p2Parameter       P2 parameter byte
 * @param data              Data to transmit.  Value of Lc field is set according to the data size.
 * @param expectedResponseLength Response data length (Le) in bytes. Valid range is from 1 to 65536 inclusively;
 *                               -1 means no response data field is expected.
 *
 * @discussion  Generates an ISO7816 APDU object.  The Lc value is generated base on the size of the data object; possible value ranges from
 *              1 to 65535 inclusively.  Use @link -initWithData: @link/ in cases where a finer control on the APDU format is required.
 */
- (instancetype)initWithInstructionClass:(uint8_t)instructionClass
                         instructionCode:(uint8_t)instructionCode
                             p1Parameter:(uint8_t)p1Parameter
                             p2Parameter:(uint8_t)p2Parameter
                                    data:(NSData *)data
                  expectedResponseLength:(NSInteger)expectedResponseLength;

/*!
 * @method initWithData:
 *
 * @param data  Data buffer containing the full APDU.
 *
 * @return nil if input data does not contain a valid APDU.
 */
- (_Nullable instancetype)initWithData:(NSData *)data;

@end

@protocol NFCTag, NFCNDEFTag;
/*!
 * @protocol NFCISO7816Tag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol
 *              when an ISO7816 compatible tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement and the "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *              key in the application's Info.plist to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation
 *              method if the required entitlement is missing or "com.apple.developer.nfc.readersession.iso7816.select-identifiers" does not contain
 *              at least one valid entry.
 *              When the reader discovered a compatible ISO14443 tag it automatically performs a SELECT command (by DF name) using the values provided in
 *              "com.apple.developer.nfc.readersession.iso7816.select-identifiers" in the specified array order.  The tag is
 *              returned from the [NFCTagReaderSessionDelegate readerSession:didDetectTags:] call on the first successful SELECT command.
 *              The initialSelectedAID property returns the application identifier of the selected application.  Tag will not be returned
 *              to the NFCTagReaderSessionDelegate if no application described in "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *              is found.  Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 *
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO7816Tag <NFCTag, NFCNDEFTag>

/*!
 * @property initialSelectedAID The Hex string of the application identifier (DF name) selected by the reader when the tag is discovered.
 *                              This will match one of the entries in the "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *                              in the Info.plist.
 */
@property (nonatomic, retain, readonly) NSString *initialSelectedAID API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion The hardware UID of the tag.
 */
@property (nonatomic, readonly, copy) NSData *identifier;

/*!
 * @discussion The optional historical bytes extracted from the Type A Answer To Select response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *historicalBytes;

/*!
 * @discussion The optional Application Data bytes extracted from the Type B Answer To Request response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *applicationData;

/*!
 * @discussion Indicates if @link applicationData @link/ follows proprietary data coding.  If false, the format of the application data is
 *             defined in the ISO14443-3 specification.
 */
@property (nonatomic, readonly) BOOL proprietaryApplicationDataCoding;

/*!
 * @method sendCommandAPDU:completionHandler:
 *
 * @param apdu              The command APDU object
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.  responseData may be
 *                          empty.  Command processing status bytes (SW1-SW2) are always valid.
 *
 * @discussion  Send a command APDU to the tag and receives a response APDU.  Note that a SELECT command with a P1 value of 0x04 (seelction by DF name)
 *              will be checked against the values listed in the "com.apple.developer.nfc.readersession.iso7816.select-identifiers" in the Info.plist.
 *              Selecting an application outside of the permissible list will result in a NFCReaderErrorSecurityViolation error.
 */
- (void)sendCommandAPDU:(NFCISO7816APDU *)apdu
      completionHandler:(void(^)(NSData *responseData, uint8_t sw1, uint8_t sw2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO7816Tag_h */
// ==========  CoreNFC.framework/Headers/NFCNDEFReaderSession.h
//
//  NFCNDEFReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCNDEFReaderSession_h
#define NFCNDEFReaderSession_h

#import <Foundation/Foundation.h>

@class NFCReaderSession;
@class NFCNDEFReaderSession;
@class NFCNDEFMessage;
@protocol NFCNDEFTag;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @protocol NFCNDEFReaderSessionDelegate
 *
 * @discussion NDEF reader session callbacks.  Presence of the -readerSession:didDetectTags: optional method will change the session behaviour
 *             into a read-write session where @link NFCNDEFTag @link/ objects are returned.
 *
 * @note       A read-write session does not trigger the -readerSession:didDetectNDEFs: method.
 * @note       A read-write session does not get invalidate automatically after a successful tag detection.  Invalidation occurs when
 *             the invalidation method is called explicitly or the 60 seconds session time limit is reached.
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
- (void)readerSession:(NFCNDEFReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSession:didDetectNDEFs:
 *
 * @param session   The session object used for tag detection.
 * @param messages  Array of @link NFCNDEFMessage @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) with NDEF messages in the polling sequence.  Polling
 *                  is automatically restarted once the detected tag is removed from the reader's read range.  This method
 *                  is only get call if the optional -readerSession:didDetectTags: method is not
 *                  implemented.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didDetectNDEFs:(NSArray<NFCNDEFMessage *> *)messages API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

@optional

/*!
 * @method readerSession:didDetectTags:
 *
 * @param session   The session object used for NDEF tag detection.
 * @param tags      Array of @link NFCNDEFTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NDEF tag(s) in the RF field.  Presence of this method overrides -readerSession:didDetectNDEFs: and enables
 *                  read-write capability for the session.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCNDEFTag>> *)tags API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 */
- (void)readerSessionDidBecomeActive:(NFCNDEFReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


#pragma mark - NDEF reader session

/*!
 * @class NFCNDEFReaderSession
 *
 * @discussion NFC reader session for processing NFC Data Exchange Format (NDEF) tags.  This session requires the "com.apple.developer.nfc.readersession.formats"
 *             entitlement in your process.  In addition your application's Info.plist must contain a non-empty usage description string.
 *             @link NFCReaderErrorSecurityViolation @link/ will be returned from @link [NFCNDEFReaderSessionDelegate readerSession:didInvalidateWithError:] @link/
 *             if the required entitlement is missing when session is started.
 *
 * @note       Only one NFCNDEFReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 * @note       If the delegate object implements the optional -readerSession:didDetectTags: method the NFCNDEFReaderSession will become a read-write session; see @link
 *             NFCNDEFReaderSessionDelegate @link/ for detail description.
 * @note       The error symbol will not be drawn on the action sheet if -invalidateSessionWithError: method is called on a session that is not a read-write session;
 *             -invalidateSession: method should be used in a read-only session.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFReaderSession : NFCReaderSession

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithDelegate:queue:invalidateAfterFirstRead:
 *
 * @param delegate  The session will hold a weak ARC reference to this @link NFCNDEFReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCNDEFReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 * @param invalidateAfterFirstRead  Session will automatically invalidate after the first NDEF tag is read successfully when this is set to YES, and
 *                                  -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorFirstNDEFTagRead in this case.
 *                                  Set to NO if the delegate object implements the -readerSession:didDetectTags: optional method.
 *
 * @return          A new NFCNDEFReaderSession instance.
 *
 * @discussion      A NDEF reader session will scan and detect NFC Forum tags that contain a valid NDEF message.  NFC Forum Tag type 1 to 5 that
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
 *
 *                  The session's mode of operation is determined by the implementation of the delegate object.  The -readerSession:didDetectTags: optional method will
 *                  enable the read-write capability and suppress the -readerSession:didDetectNDEFs: callback for the session.
 */
- (instancetype)initWithDelegate:(id<NFCNDEFReaderSessionDelegate>)delegate
                           queue:(nullable dispatch_queue_t)queue
        invalidateAfterFirstRead:(BOOL)invalidateAfterFirstRead NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new NDEF tags.  New tags discovered from polling will return in the subsequent @link [NFCNDEFReaderSessionDelegate readerSession:didDetectTags:]
 *             @link/ call.  Tags that are returned previously by @link [NFCNDEFReaderSessionDelegate -readerSession:didDetectTags:] @link/ will become invalid,
 *             and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader. Calling this method on an instance initiated with a delegate object that does not implement
 *             the optional -readerSession:didDetectTags: method has no effect as RF polling restart is done automatically.
 */
- (void)restartPolling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method connectToTag:completionHandler:
 *
 * @param tag   A NFCTag protocol compliant tag object that will be connect to.
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion  This method establishes a tag connection and activates the tag.  Connecting to the same tag that is currently opened has no effect.
 *              Connecting to a different tag will automatically terminate the previous tag connection and put it into the halt state.  Tag stays in the
 *              connected state until another tag is connected or the polling is restarted.
 */
- (void)connectToTag:(id<NFCNDEFTag>)tag completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif
// ==========  CoreNFC.framework/Headers/NFCVASReaderSession.h
//
//  NFCVASReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCVASReaderSession_h
#define NFCVASReaderSession_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCReaderSession;
@class NFCVASReaderSession;

/*!
 * @class NFCVASCommandConfiguration
 *
 * @discussion Configuration for one GET VAS DATA command.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASCommandConfiguration : NSObject<NSCopying>

/*!
 * @enum VASMode
 *
 * @constant VASModeURLOnly     URL VAS protocol only.
 * @constant VASModeNormal      Full VAS protocol.
 */
typedef NS_ENUM(NSInteger, VASMode) {
    VASModeURLOnly  = 0,
    VASModeNormal   = 1,
};

/*!
 * @property mode
 * @discussion  VAS protocol mode.
 */
@property (nonatomic, assign) VASMode mode;

/*!
 * @property passTypeIdentifier
 * @discussion  Wallet Pass Type Identifier of the Wallet Pass.  The string value will be used to calculate the
 *              Merchant ID value for the GET VAS DATA command.
 */
@property (nonatomic, retain) NSString *passTypeIdentifier;

/*!
 * @property url
 * @discussion  Merchant URL object.  Maximum length of the URL is 64 characters, including the schema.
 *              Set to nil to disable the merchant URL.
 */
@property (nonatomic, retain, nullable) NSURL *url;

/*!
 * @method initWithVASMode:passTypeIdentifier:url:
 *
 * @param mode                  VAS operation mode
 * @param passTypeIdentifier    Pass type identifier of the Wallet pass.
 * @param url                   URL for VAR URL Only mode.  Set to <i>nil</i> for VAS normal mode.
 */
- (instancetype)initWithVASMode:(VASMode)mode passTypeIdentifier:(NSString *)passTypeIdentifier url:(NSURL * _Nullable)url NS_DESIGNATED_INITIALIZER;
@end

/*!
 * @class NFCVASResponse
 *
 * @discussion Response from one GET VAS DATA command.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASResponse : NSObject<NSCopying>

/*!
 * @enum VASErrorCode
 *
 * @discussion Response APDU status word.
 */
typedef NS_ENUM(NSInteger, VASErrorCode) {
    VASErrorCodeSuccess                         = 0x9000,
    VASErrorCodeDataNotFound                    = 0x6A83,
    VASErrorCodeDataNotActivated                = 0x6287,
    VASErrorCodeWrongParameters                 = 0x6B00,
    VASErrorCodeWrongLCField                    = 0x6700,
    VASErrorCodeUserIntervention                = 0x6984,
    VASErrorCodeIncorrectData                   = 0x6A80,
    VASErrorCodeUnsupportedApplicationVersion   = 0x6340,
};

/*!
 * @property status
 *
 * @discussion Response APDU status.
 */
@property (nonatomic, assign, readonly) VASErrorCode status;

/*!
 * @property vasData
 *
 * @discussion VAS data.
 */
@property (nonatomic, retain, readonly) NSData *vasData;

/*!
 * @property mobileToken
 *
 * @discussion Mobile token value.
 */
@property (nonatomic, retain, readonly) NSData *mobileToken;

@end

/*!
 * @protocol    NFCVASReaderSessionDelegate
 *
 * @discussion  Value Added Service (VAS) reader session callbacks.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCVASReaderSessionDelegate <NSObject>
@optional

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for VAS tags.
 *                  The @link readerSession:didReceiveVASResponses: @link/ will be called when a VAS transaction is completed.
 */
- (void)readerSessionDidBecomeActive:(NFCVASReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

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
- (void)readerSession:(NFCVASReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSession:didReceiveVASResponses:
 *
 * @param session   The session object used for tag detection.
 * @param responses Array of @link NFCVASResponse @link/ objects.  The order of the response objects follows the
 *                  sequence of GET VAS DATA sent by the reader session.
 *
 * @discussion      Gets called when the reader completes the requested VAS transaction.  Polling
 *                  is automatically restarted once the detected tag is removed from the reader's read range.
 */
- (void)readerSession:(NFCVASReaderSession *)session didReceiveVASResponses:(NSArray<NFCVASResponse *> *)responses API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

/*!
 * @class NFCVASReaderSession
 *
 * @discussion Reader session for processing Value Added Service (VAS) tags.  This session requires the "com.apple.developer.nfc.readersession.formats"
 *             entitlement in your process.  In addition your application's Info.plist must contain a non-empty usage description string.
 *             @link NFCReaderErrorSecurityViolation @link/ will be returned from @link [NFCVASReaderSessionDelegate readerSession:didInvalidateWithError:] @link/
 *             if the required entitlement is missing when session is started.
 *
 * NOTE:
 * Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASReaderSession : NFCReaderSession

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithVASCommandConfigurations:delegate:queue:invalidateAfterFirstRead:
 *
 * @param commandConfigurations     NSArray of NFCVASCommandConfiguration objects.  Each NFCVASCommandConfiguration defines one GET VAS DATA command send to
 *                                  a compatible tag when discovered.  The order of elements in the array defines the order of the command execution.
 * @param delegate  The session will hold a weak ARC reference to this @link NFCVASReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCVASReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return          A new NFCVASReaderSession instance.
 *
 * @discussion      A VAS reader session will automatically scan and detect tag that is compatible with the VAS protocol.  The session will advertise as a
 *                  VAS App Only terminal.  A modal system UI will present once -beginSession is called to inform the start of the session; the UI sheet
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
- (instancetype)initWithVASCommandConfigurations:(NSArray<NFCVASCommandConfiguration *> *)commandConfigurations
                                        delegate:(id<NFCVASReaderSessionDelegate>)delegate
                                           queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
@end

NS_ASSUME_NONNULL_END

#endif /* NFCVASReaderSession_h */
// ==========  CoreNFC.framework/Headers/NFCNDEFPayload.h
//
//  NFCNDEFPayload.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFPayload_h
#define NFCNDEFPayload_h

#import <Foundation/Foundation.h>

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
 * @discussion  A NDEF message payload consists of Type Name Format, Type, Payload Identifier, and Payload data.
 *              The NDEF payload cannot result into a record that is greater than 128KB in size.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFPayload : NSObject<NSSecureCoding>

@property (nonatomic, assign) NFCTypeNameFormat typeNameFormat;
@property (nonatomic, copy) NSData *type;
@property (nonatomic, copy) NSData *identifier;
@property (nonatomic, copy) NSData *payload;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithFormat:type:identifier:paylaod:
 *
 * @param format        NFCTypeNameFormat value.
 * @param type          Identifier describing the type of the payload.  Empty data indicates field is absent from the payload.
 * @param identifier    Identifier in the form of a URI reference.  Empty data indicates field is absent from the payload.
 * @param payload       Payload data.  Empty data indicates field is absent from the payload.
 *
 * This initializer uses the maximum payload chunk size defined by the NFC NDEF specification, i.e. 2^32-1 octets.
 */
- (instancetype)initWithFormat:(NFCTypeNameFormat)format type:(NSData *)type identifier:(NSData *)identifier payload:(NSData *)payload API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method initWithFormat:type:identifier:paylaod:
 *
 * @param format        NFCTypeNameFormat value.
 * @param type          Identifier describing the type of the payload.  Empty data indicates field is absent from the payload.
 * @param identifier    Identifier in the form of a URI reference.  Empty data indicates field is absent from the payload.
 * @param payload       Payload data.  Empty data indicates field is absent from the payload.
 * @param chunkSize     Maximum size of a payload chunk.  0 means no chunking on the payload, i.e. payload is fit in a single record.
 */
- (instancetype)initWithFormat:(NFCTypeNameFormat)format type:(NSData *)type identifier:(NSData *)identifier payload:(NSData *)payload chunkSize:(size_t)chunkSize API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


@interface NFCNDEFPayload (ConvenienceHelpers)

/*!
 * @method wellKnownTypeURIRecordWithString:
 *
 * @param uri       URI string.  UTF-8 encoding representation will be used.
 *
 * @discussion      Used for creating NDEF URI payloads which cannot be represented with NSURL object.  These are URIs that contain characters
 *                  such as 'ä' and 'ö' which cannot be represent by the 7 bits ASCII encoding.
 */
+ (_Nullable instancetype)wellKnownTypeURIPayloadWithString:(NSString *)uri API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnownTypeURIPayloadWithURL:
 *
 * @param url       NSURL object.
 *
 * @discussion      Preferred convenience function for creating NDEF URI payload with common URLs such as "https://www.apple.com" or "tel:+1-555-555-5555".
 */
+ (_Nullable instancetype)wellKnownTypeURIPayloadWithURL:(NSURL *)url API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnowTypeTextPayloadWithString:locale:
 *
 * @param text      Text message.
 * @param locale    NSLocale object.  IANA language code specified by the locale will be saved with the payload.
 */
+ (_Nullable instancetype)wellKnowTypeTextPayloadWithString:(NSString *)text locale:(NSLocale *)locale API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method      wellKnownTypeURIPayload
 *
 * @return      NSURL object base on a valid Well Known Type URI payload. nil if payload is not a URI.
 */
- (NSURL * _Nullable)wellKnownTypeURIPayload API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnownTypeTextPayloadWithLocale:
 *
 * @param locale    Returns NSLocale object that is constructed from the IANA language code stored with the text payload.
 * @return          NSString object base on a valid Well Known Type Text payload.  nil if payload is not a text.
 */
- (NSString * _Nullable)wellKnownTypeTextPayloadWithLocale:(NSLocale * _Nullable * _Nonnull)locale API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end
NS_ASSUME_NONNULL_END

#endif /* NFCNDEFPayload_h */
// ==========  CoreNFC.framework/Headers/NFCNDEFMessage.h
//
//  NFCNDEFMessage.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFMessage_h
#define NFCNDEFMessage_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCNDEFPayload;
/*!
 * @class NFCNDEFMessage
 *
 * @discussion A NDEF message consists of payload records.  The maximum size of the NDEF message is limited to 128KB.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFMessage : NSObject<NSSecureCoding>

/*!
 * @property records
 *
 * @discussion Array of NFCNDEFPayload records contained in this message.
 */
@property (nonatomic, copy) NSArray<NFCNDEFPayload *> *records API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property length
 *
 * @discussion Length of the resulting NDEF message in bytes as it would be stored on a NFC tag.
 */
@property (nonatomic, readonly) NSUInteger length API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithNDEFRecords:
 *
 * @param records  NSArray of NFCNDEFPayload object.  An empty array will create an empty NDEF message.
 */
- (instancetype)initWithNDEFRecords:(NSArray<NFCNDEFPayload *> *)records API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method ndefMessageWithData:
 *
 * @param data  NSData storing raw bytes of a complete NDEF message.  The data content will be validated; all NDEF payloads must
 *              be valid according to the NFC Forum NDEF RTD specification and it shall only contain a single NDEF message.
 *
 */
+ (_Nullable instancetype)ndefMessageWithData:(NSData *)data API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCNDEFMessage_h */
// ==========  CoreNFC.framework/Headers/NFCTag.h
//
//  NFCTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCTag_h
#define NFCTag_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum NFCTagType
 *
 * @constant NFCTagTypeISO15693             ISO15693 tag.
 * @constant NFCTagTypeFeliCa               FeliCa tag.
 * @constant NFCTagTypeISO7816Compatible    ISO14443-4 type A / B tag with ISO7816 communication.
 * @constant NFCTagTypeMiFare               MiFare technology tag (MIFARE Plus, UltraLight, DESFire) base on ISO14443.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ENUM(NSUInteger, NFCTagType) {
    NFCTagTypeISO15693 = 1,
    NFCTagTypeFeliCa API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 2,
    NFCTagTypeISO7816Compatible API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 3,
    NFCTagTypeMiFare API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 4,
};

@protocol NFCReaderSession;
@protocol NFCNDEFTag;
@protocol NFCISO15693Tag;
@protocol NFCISO7816Tag;
@protocol NFCMiFareTag;
@protocol NFCFeliCaTag;

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
 *              unavailable.  Tag in disconnected state will return NO.
 *
 * @discussion  Check whether a detected tag is available.
 */
@property (nonatomic, getter=isAvailable, readonly) BOOL available;

/*!
 * @method asNFCISO15693Tag
 *
 * @return      Returns self if it conforms to the NFCISO15693Tag protocol; else returns nil.
 */
- (nullable id<NFCISO15693Tag>)asNFCISO15693Tag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method asNFCISO7816Tag
 *
 * @return      Returns self if it conforms to the NFCISO7816Tag protocol; else returns nil.
 */
- (nullable id<NFCISO7816Tag>)asNFCISO7816Tag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property asNFCFeliCaTag
 *
 * @discussion Returns nil if tag does not conform to NFCFeliCaTag.
 */
- (nullable id<NFCFeliCaTag>)asNFCFeliCaTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property asNFCMiFareTag
 *
 * @discussion Returns nil if tag does not conform to NFCMiFareTag.
 */
- (nullable id<NFCMiFareTag>)asNFCMiFareTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

#pragma mark - Tag command configuration

/*!
 * @interface   NFCTagCommandConfiguration
 *
 * @discussion  Define configuration parameters for tag commands.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
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
// ==========  CoreNFC.framework/Headers/NFCNDEFTag.h
//
//  NFCNDEFTag.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFTag_h
#define NFCNDEFTag_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCNDEFMessage;

/*!
 * @enum NFCNDEFStatus
 *
 * @constant NFCNDEFStatusNotSupport    Tag is not NDEF formatted; NDEF read and write are disallowed.
 * @constant NFCNDEFStatusReadWrite     Tag is NDEF read and writable.
 * @constant NFCNDEFStatusReadOnly      Tag is NDEF read-only; NDEF writing is disallowed.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ENUM(NSUInteger, NFCNDEFStatus) {
    NFCNDEFStatusNotSupported   = 1,
    NFCNDEFStatusReadWrite      = 2,
    NFCNDEFStatusReadOnly       = 3,
};

/*!
 * @protocol NFCNDEFTag
 *
 * @discussion Operations on a NDEF formatted tag.  Unless it is specified all block completion handlers are dispatched on the session work queue that is associated with the tag.
 *
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCNDEFTag <NSObject, NSSecureCoding, NSCopying>

/*!
 * @property available:
 *
 * @return      <i>YES</i> if NDEF tag is available in the current reader session.  A tag remove from the RF field will become
 *              unavailable.  Tag in disconnected state will return NO.
 *
 * @discussion  Check whether a detected NDEF tag is available.
 */
@property (nonatomic, getter=isAvailable, readonly) BOOL available;

/*!
 * @method queryNDEFStatusWithCompletionHandler:
 *
 * @param completionHandler Return the NFCNDEFStatus of the tag.  capacity indicates the maximum NDEF message size in bytes that can be store on the tag.
 *                          error returns a valid NSError object when query fails.
 *
 * @discussion Query the NDEF support status of the tag.
 */
- (void)queryNDEFStatusWithCompletionHandler:(void(^)(NFCNDEFStatus status, NSUInteger capacity, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readNDEFWithCompletionHandler:
 *
 * @param completionHandler Returns the NDEF message from read operation.  Successful read would return a valid NFCNDEFMessage object with NSError object set to nil;
 *                          read failure returns a nil NFCNDEFMessage and a valid NSError object.
 *
 * @discussion Reads NDEF message from the tag.
 */
- (void)readNDEFWithCompletionHandler:(void(^)(NFCNDEFMessage * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeNDEF:completionHandler:
 *
 * @param completionHandler  Returns operation status.  A nil NSError object indicates a successful write operation.
 *
 * @discussion Writes a NDEF message to the tag.
 */
- (void)writeNDEF:(NFCNDEFMessage *)ndefMessage completionHandler:(void(^)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeLockWithCompletionHandler:
 *
 * @param completionHandler Returns operation status. A nil NSError object indicates a successful lock operation.
 *
 * @discussion Locks the NDEF tag to read-only state; tag can no longer be written afterward.  This is a permanent operation.  A successful lock operaiton via this method
 *             will change the NFCNDEFStatus value of the tag to @link NFCNDEFStatusReadOnly @link/.
 */
- (void)writeLockWithCompletionHandler:(void(^)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  CoreNFC.framework/Headers/NFCError.h
//
//  NFCError.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCError_h
#define NFCError_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSErrorDomain const NFCErrorDomain;

/*!
 * @enum NFCReaderError
 *
 * @discussion  Possible errors returned by CoreNFC framework reader session.
 * @constant    NFCReaderErrorUnsupportedFeature                                Core NFC is not supported on the current platform.
 * @constant    NFCReaderErrorSecurityViolation                                 Missing required entitlement and/or privacy settings from the client app.
 * @constant    NFCReaderErrorInvalidParameter                                  Input parameter is invalid.
 * @constant    NFCReaderErrorInvalidParameterLength                            Length of input parameter is invalid, i.e. size of data container.
 * @constant    NFCReaderErrorParameterOutOfBound                               Parameter value is outside of the acceptable boundary / range.
 * @constant    NFCReaderTransceiveErrorTagConnectionLost                       Connection to the tag is lost.
 * @constant    NFCReaderTransceiveErrorRetryExceeded                           Maximum data transmission retry has reached.
 * @constant    NFCReaderTransceiveErrorTagResponseError                        Tag response is invalid.  Additional error information may be contain in the underlying user info dictionary.
 * @constant    NFCReaderTransceiveErrorSessionInvalidated                      Session has been previously invalidated.
 * @constant    NFCReaderTransceiveErrorTagNotConnected                         Tag is not in the connected state.
 * @constant    NFCReaderSessionInvalidationErrorUserCanceled                   Session is invalidated by the user.
 * @constant    NFCReaderSessionInvalidationErrorSessionTimeout                 Session is timed out.
 * @constant    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly  Session is terminated unexpectly.
 * @constant    NFCReaderSessionInvalidationErrorSystemIsBusy                   Core NFC is temporary unavailable due to system resource constraints.
 * @constant    NFCReaderSessionInvalidationErrorFirstNDEFTagRead               Session is terminated after the 1st NDEF tag is read.
 * @constant    NFCTagCommandConfigurationErrorInvalidParameters
 * @constant    NFCNdefReaderSessionErrorTagNotWritable                         NDEF tag is not writable.
 * @constant    NFCNdefReaderSessionErrorTagUpdateFailure                       NDEF tag write fails.
 * @constant    NFCNdefReaderSessionErrorTagSizeTooSmall                        NDEF tag memory size is too small to store the desired data.
 * @constant    NFCNdefReaderSessionErrorZeroLengthMessage                      NDEF tag does not contain any NDEF message.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ERROR_ENUM(NFCErrorDomain, NFCReaderError) {
    NFCReaderErrorUnsupportedFeature = 1,
    NFCReaderErrorSecurityViolation,
    NFCReaderErrorInvalidParameter API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderErrorInvalidParameterLength API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderErrorParameterOutOfBound API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),

    NFCReaderTransceiveErrorTagConnectionLost = 100,
    NFCReaderTransceiveErrorRetryExceeded,
    NFCReaderTransceiveErrorTagResponseError,
    NFCReaderTransceiveErrorSessionInvalidated API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderTransceiveErrorTagNotConnected API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),

    NFCReaderSessionInvalidationErrorUserCanceled = 200,
    NFCReaderSessionInvalidationErrorSessionTimeout,
    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly,
    NFCReaderSessionInvalidationErrorSystemIsBusy,
    NFCReaderSessionInvalidationErrorFirstNDEFTagRead,

    NFCTagCommandConfigurationErrorInvalidParameters = 300,

    NFCNdefReaderSessionErrorTagNotWritable API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 400 ,
    NFCNdefReaderSessionErrorTagUpdateFailure API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCNdefReaderSessionErrorTagSizeTooSmall API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCNdefReaderSessionErrorZeroLengthMessage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
};

#pragma mark - ISO15693 specific command response error code

/*!
 *  Key in NSError userInfo dictionary.  The corresponding value is the NSUInteger error code from tag's response.
 *  Refer to ISO15693 specification for the error code values.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCISO15693TagResponseErrorKey;

/*!
 *  Key in NSError userInfo dictionary.  Presence of this key indicates the received response packet length is invalid.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCTagResponseUnexpectedLengthErrorKey;

NS_ASSUME_NONNULL_END

#endif /* CNFCError_h */
// ==========  CoreNFC.framework/Headers/NFCFeliCaTag.h
//
//  NFCFeliCaTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCFeliCaTag_h
#define NFCFeliCaTag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag, NFCNDEFTag;

/*!
 * @protocol NFCFeliCaTag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol
 *              when a FeliCa tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement and the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *              key in the application's Info.plist to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation
 *              method if the required entitlement is missing or "com.apple.developer.nfc.readersession.felica.systemcodes" does not contain
 *              at least one valid entry.
 *              When the reader discovers a FeliCa tag it automatically performs a Polling command using the system code values provided in the
 *              "com.apple.developer.nfc.readersession.felica.systemcodes" in the specified array order. System code
 *              specified in the array must not contain a wildcard value (0xFF) in the upper or the lower byte, i.e. full
 *              matching value is required.  The tag is returned from the [NFCTagReaderSessionDelegate readerSession:didDetectTags:] call
 *              on the first successful Polling command matching one of the system codes.  Tag will not be returned
 *              to the NFCTagReaderSessionDelegate if no matching system is found based on entries listed in the Info.plist.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCFeliCaTag <NFCTag, NFCNDEFTag>

/*!
 * @discussion Request code parameter for the polling command
 */
typedef NS_ENUM(NSInteger, PollingRequestCode) {
    PollingRequestCodeNoRequest = 0,
    PollingRequestCodeSystemCode = 1,
    PollingRequestCodeCommunicationPerformance = 2,
};

/*!
 * @discussion Time slot parameter for the polling command
 */
typedef NS_ENUM(NSInteger, PollingTimeSlot) {
    PollingTimeSlotMax1 = 0,
    PollingTimeSlotMax2 = 1,
    PollingTimeSlotMax4 = 3,
    PollingTimeSlotMax8 = 7,
    PollingTimeSlotMax16 = 15,
};

/*!
 * @discussion Encryption Identifier parameter in response of Request Service V2
 */
typedef NS_ENUM(NSInteger, EncryptionId) {
    EncryptionIdAES = 0x4F,
    EncryptionIdAES_DES = 0x41,
};

@required

/*!
 * @property currentSystemCode  The system code most recently selected by the reader using the Polling command.
 *                              This will match one of the entries in the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *                              in the Info.plist.
 */
@property (nonatomic, retain, readonly) NSData *currentSystemCode API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property currentIDm         Manufacturer ID of the currently selected system.  Value is updated on each Polling command execution.
 *                              It will be empty if system selection fails.
 */
@property (nonatomic, retain, readonly) NSData *currentIDm API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

#pragma mark - Helper functions

/*
 *  The following commands are defined in FeliCa Card User's Manual Excerpted Edition Version 2.02 (No. M617-E02-02) which
 *  is publicly available from Sony Corporations.
 */

/*!
 * @method pollingWithSystemCode:requestCode:timeSlot:completionHandler:
 *
 * @param systemCode        Designation of System Code.  Wildcard value (0xFF) in the upper or the lower byte is not supported.
 * @param requestCode       Designation of Requset Data output.
 * @param timeSlot          Maximum number of slots possible to respond.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation
 *                          succeeds, else all other return values shall be ignored.  Non-zero length requestData is return when
 *                          requestCode is a non-zero parameter and feature is supported by the tag.  The @link currentIDM @link/ property will be updated
 *                          on each execution, except when an invalid systemCode is provided and the existing selected system will stay selected.
 *
 * @discussion              Polling command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 *                          System code must be one of the provided values in the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *                          in the Info.plist; @link NFCReaderErrorSecurityViolation @link/ will be returned when an invalid system code is used.
 *                          Polling with wildcard value in the upper or lower byte is not supported.
 */
- (void)pollingWithSystemCode:(NSData *)systemCode
                  requestCode:(PollingRequestCode)requestCode
                     timeSlot:(PollingTimeSlot)timeSlot
            completionHandler:(void(^)(NSData *pmm, NSData *requestData, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestServiceWithNodeCodeList:completionHandler:
 *
 * @param nodeCodeList      Node Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 32 inclusive.
 *                          Each node code should be 2 bytes stored in Little Endian format.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Node key version list is return as NSArray of NSData objects,
 *                          and each data object is stored in Little Endian format per FeliCa specification.
 *
 * @discussion              Request Service command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestServiceWithNodeCodeList:(NSArray<NSData *> *)nodeCodeList
                     completionHandler:(void(^)(NSArray<NSData *> *nodeKeyVersionList, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestResponseWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Valid mode value ranges from 0 to 3 inclusively.
 *
 * @discussion              Request Response command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestResponseWithCompletionHandler:(void(^)(NSInteger mode, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


/*!
 * @method readWithoutEncryptionWithServiceCodeList:blockList:completionHandler:
 *
 * @param serviceCodeList   Service Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 16 inclusive.
 *                          Each service code should be 2 bytes stored in Little Endian format.
 * @param blockList         Block List represent in a NSArray of NSData objects.  2-Byte or 3-Byte block list element is supported.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Valid read data blocks (block length of 16 bytes)
 *                          are returned in NSArray of NSData objects when Status Flag 1 equals zero.
 *
 * @discussion              Read Without Encrypton command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)readWithoutEncryptionWithServiceCodeList:(NSArray<NSData *> *)serviceCodeList
                                       blockList:(NSArray<NSData *> *)blockList
                               completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSArray<NSData*> *blockData, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeWithoutEncryptionWithServiceCodeList:blockList:blockData:completionHandler:
 *
 * @param serviceCodeList   Service Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 16 inclusive.
 *                          Each service code should be 2 bytes stored in Little Endian format.
 * @param blockList         Block List represent in a NSArray of NSData objects.  Total blockList items and blockData items should match.
 *                          2-Byte or 3-Byte block list element is supported.
 * @param blockData         Block data represent in a NSArray of NSData objects.  Total blockList items and blockData items should match.
 *                          Data block should be 16 bytes in length.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.
 *
 * @discussion              Write Without Encrypton command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)writeWithoutEncryptionWithServiceCodeList:(NSArray<NSData *> *)serviceCodeList
                                        blockList:(NSArray<NSData *> *)blockList
                                        blockData:(NSArray<NSData *> *)blockData
                                completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestSystemCodeWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Each system code is 2 bytes stored in Little Endian format.
 *
 * @discussion              Request System Code command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestSystemCodeWithCompletionHandler:(void(^)(NSArray<NSData *> *systemCodeList, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestServiceV2WithNodeCodeList:completionHandler:
 *
 * @param nodeCodeList      Node Code list represent in a NSArray of NSData.  Number of nodes specified should be between 1 to 32 inclusive.
 *                          Each node code should be 2 bytes stored in Little Endian format.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  encryptionIdentifier value shall be ignored if Status Flag 1 value indicates an error.
 *                          nodeKeyVerionListAES and nodeKeyVersionListDES may be empty depending on the Status Flag 1 value and the Encryption Identifier value.
 *                          The 2 bytes node key version (AES and DES) is in Little Endian format.
 *
 * @discussion              Request Service V2 command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestServiceV2WithNodeCodeList:(NSArray<NSData *> *)nodeCodeList
                       completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, EncryptionId encryptionIdentifier, NSArray<NSData *> *nodeKeyVersionListAES, NSArray<NSData *> *nodeKeyVersionListDES, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestSpecificationVersionWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  basicVersion and optionVersion may be empty depending on the Status Flag 1 value
 *                          and if the tag supports AES/DES.
 *
 * @discussion              Request Specification Verison command defined by FeliCa card specification.  This command supports response format version `00`h.
 *                          Refer to the FeliCa specification for details.
 */
- (void)requestSpecificationVersionWithCompletionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSData *basicVersion, NSData *optionVersion, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method resetModeWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.
 *
 * @discussion              Reset Mode command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)resetModeWithCompletionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


#pragma mark - Sending additional FeliCa commands

/*!
 * @method sendFeliCaCommandPacket:completionHandler:
 *
 * @param commandPacket     Command packet send to the FeliCa card.  Maximum packet length is 254.  Data length (LEN) byte and CRC bytes are calculated and inserted
 *                          automatically to the provided packet data frame.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion              Transmission of FeliCa Command Packet Data at the applicaiton layer.  Refer to the FeliCa specification for details.
 *                          Manufacturer ID (IDm) of the currently selected system can be read from the currentIDm property.
 */
- (void)sendFeliCaCommandPacket:(NSData *)commandPacket
              completionHandler:(void(^)(NSData *responsePacket, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif /* NFCFeliCaTag_h */
// ==========  CoreNFC.framework/Headers/NFCISO15693ReaderSession.h
//
//  NFCISO15693ReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//
#ifndef NFCISO15693ReaderSession_h
#define NFCISO15693ReaderSession_h

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
 * The NFCISO15693 tag object returned by this session will only respond to the legacy APIs that are introducted in iOS11.  
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693ReaderSession : NFCReaderSession

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
- (instancetype)initWithDelegate:(id<NFCReaderSessionDelegate>)delegate queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER NS_EXTENSION_UNAVAILABLE("Not available to extensions");

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new tags.  Tags that are returned previously by @link [NFCReaderSessionDelegate readerSession:didDetectTags:]
 *             @link/ will become invalid, and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader.
 */
- (void)restartPolling;

@end

NS_ASSUME_NONNULL_END

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

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCTagCommandConfiguration;
@protocol NFCTag, NFCNDEFTag;

/*!
 * @class       NFCISO15693CustomCommandConfiguration
 *
 * @discussion  Configuration options for the Manufacturer Custom command.
 */

NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
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
@property (nonatomic, copy) NSData *requestParameters;

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
                       requestParameters:(nullable NSData *)requestParameters;

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
                       requestParameters:(nullable NSData *)requestParameters
                          maximumRetries:(NSUInteger)maximumRetries
                           retryInterval:(NSTimeInterval)retryInterval;
@end

/*!
 * @class       NFCISO15693ReadMultipleBlocksConfiguration
 *
 * @discussion  Configuration options for the Read Multiple Blocks command.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions")  API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
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
 * @discussion  A @link NFCISO15693ReaderSession @link/ or @link NFCTagReaderSession @link/ reader session returns an instance conforming
 *              to this protocol when an ISO15693 tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              reader session work queue that is associated with the tag.  Your process requires to include the "com.apple.developer.nfc.readersession.formats"
 *              entitlement to receive this tag object from the @link NFCReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation method if the required
 *              entitlement is missing when session is started.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO15693Tag <NFCTag, NFCNDEFTag>

typedef NS_OPTIONS(uint8_t, RequestFlag) {
    RequestFlagDualSubCarriers      = (1 << 0),
    RequestFlagHighDataRate         = (1 << 1),
    RequestFlagProtocolExtension    = (1 << 3),
    RequestFlagSelect               = (1 << 4),
    RequestFlagAddress              = (1 << 5),
    RequestFlagOption               = (1 << 6),
};


@required

/*!
 * @discussion The 64 bit hardware UID of the tag. Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *identifier;

/*!
 * @discussion  The IC manufacturer code (bits 56 – 49) in UID according to ISO/IEC 7816-6:2004.
 */
@property (nonatomic, readonly) NSUInteger icManufacturerCode;

/*!
 * @discussion  The IC serial number (bits 48 – 1) in UID assigned by the manufacturer.  Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *icSerialNumber;


#pragma mark - Legacy APIs

/*
 * The following legacy methods require the "com.apple.developer.nfc.readersession.iso15693.tag-identifiers" entitlement in your process.
 * New replacement APIs has been made available for the general use without this entitlement.  Calling these APIs from a tag return by the
 * NFCTagReaderSession session will result in a NFCReaderErrorUnsupportedFeature error.
 */

/*!
 * @method sendCustomCommandWithConfiguration:completionHandler:
 *
 * @param commandConfiguration  Configuration for the Manufacturer Custom Command.
 * @param completionHandler     Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                              A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                              responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion Send a manufacturer dependent custom command using command code range from 0xA0 to 0xDF.  Refer to ISO15693-3
 *             specification for details.
 */
- (void)sendCustomCommandWithConfiguration:(NFCISO15693CustomCommandConfiguration *)commandConfiguration
                         completionHandler:(void(^)(NSData *customResponseParameters, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readMultipleBlocksWithConfiguration:completionHandler:
 *
 * @param readConfiguration Configuration For the Read Multiple Blocks command.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object.  All blocks are concatenated into the NSData object.
 *
 * @discussion  Performs read operation using Read Multiple Blocks command (0x23 command code) as defined in ISO15693-3 specification.
 *              Multiple Read Multiple Blocks commands will be sent if necessary to complete the operation.
 */
- (void)readMultipleBlocksWithConfiguration:(NFCISO15693ReadMultipleBlocksConfiguration *)readConfiguration
                          completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);


#pragma mark - Public APIs

@required
/*!
 * @method stayQuietWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Stay quiet command (0x02 command code) as defined in ISO15693-3 specification.
 */
- (void)stayQuietWithCompletionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readSingleBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object. If Option flag in the request flags is set,
 *                          then first byte of data block will contain the associated block security status.
 *
 * @discussion              Read single block command (0x20 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)readSingleBlockWithRequestFlags:(RequestFlag)flags
                            blockNumber:(uint8_t)blockNumber
                      completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeSingleBlockWithRequestFlags:blockNumber:dataBlock:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
 * @param dataBlock         A single block of data.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write single block command (0x21 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeSingleBlockWithRequestFlags:(RequestFlag)flags
                             blockNumber:(uint8_t)blockNumber
                               dataBlock:(NSData *)dataBlock
                       completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
* @method lockBlockWithRequestFlags:blockNumber:completionHandler:
*
* @param flags             Request flags.
* @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
* @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
*                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
*                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
*                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
*                          Successfully read data blocks will be returned from NSData object.
*
* @discussion              Lock block command (0x22 command code) as defined in ISO15693-3 specification.  Address flag is automatically
*                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
*/
- (void)lockBlockWithRequestFlags:(RequestFlag)flags
                      blockNumber:(uint8_t)blockNumber
                completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readMultipleBlocksWithRequestFlags:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSArray of NSData object. If Option flag in the request flags is set,
 *                          then first byte of each returned data block will contain the associated block security status.  Each data block element
 *                          would have identical size.
 *
 * @discussion              Read multiple blocks command (0x23 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)readMultipleBlocksWithRequestFlags:(RequestFlag)flags
                                blockRange:(NSRange)blockRange
                         completionHandler:(void(^)(NSArray<NSData *> *dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeMultipleBlocksWithRequestFlags:blockRange:dataBlocks:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param dataBlocks        Blocks of data represent in NSArray of NSData.  The number of blocks shall match the length value of the blockRange parameter.
 *                          Each block element should have identical size and should match the physical block size of the tag.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write multiple blocks command (0x24 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeMultipleBlocksWithRequestFlags:(RequestFlag)flags
                                 blockRange:(NSRange)blockRange
                                 dataBlocks:(NSArray<NSData *> *)dataBlocks
                          completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method selectWithRequestFlags:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Select command (0x25 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)selectWithRequestFlags:(RequestFlag)flags
             completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method resetToReadyWithRequestFlags:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Reset To Ready command (0x26 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)resetToReadyWithRequestFlags:(RequestFlag)flags
                   completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeAFIWithRequestFlag:afi:completionHandler:
 *
 * @param flags             Request flags.
 * @param afi               Application Family Identifier.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write AFI command (0x27 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeAFIWithRequestFlag:(RequestFlag)flags
                            afi:(uint8_t)afi
              completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method lockAFIWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Lock AFI command (0x28 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)lockAFIWithRequestFlag:(RequestFlag)flags
             completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeDSFIDWithRequestFlag:dsfid:completionHandler:
 *
 * @param flags             Request flags.
 * @param dsfid             Data Storage Format Identifier.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write DSFID command (0x29 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeDSFIDWithRequestFlag:(RequestFlag)flags
                            dsfid:(uint8_t)dsfid
                completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method lockDFSIDWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Lock DSFID command (0x2A command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)lockDFSIDWithRequestFlag:(RequestFlag)flags
               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method getSystemInfoWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Value of -1 will be returned from dsfid, afi, blockSize, blockNumber, or icReference if tag response does not contain the information.
 *                          blockSize returns the actual block size in bytes ranged from 1 to 32.  blockCount returns the actual number of blocks
 *                          ranged from 1 to 256 blocks.
 *
 * @discussion              Get system information command (0x2B command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)getSystemInfoWithRequestFlag:(RequestFlag)flags
                   completionHandler:(void(^)(NSInteger dsfid, NSInteger afi, NSInteger blockSize, NSInteger blockCount, NSInteger icReference, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method getMultipleBlockSecurityStatusWithRequestFlag:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          The 8 bits security status of the requested blocks are returned in NSArray; the array will be empty when error occurs.
 *
 * @discussion              Get multiple block security status command (0x2C command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)getMultipleBlockSecurityStatusWithRequestFlag:(RequestFlag)flags
                                           blockRange:(NSRange)blockRange
                                    completionHandler:(void(^)(NSArray<NSNumber *> *securityStatus, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


/*!
 * @method customCommandWithRequestFlag:customCommandCode:customRequestParameters:completionHandler:
 *
 * @param flags                     Request flags.
 * @param customCommandCode         Custom command code defined by the IC manufacturer.  Valid range is 0xA0 to 0xDF inclusively.
 * @param customRequestParameters   Custom request parameters defined by the command.
 * @param completionHandler         Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                                  A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                                  A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                                  responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                                  The custom reponse parameters are returned on success.
 *
 * @discussion                      Custom command (0xA0 to 0xDF command code) as defined in ISO15693-3 specification.  IC manufacturer code from the tag is
 *                                  automatically inserted after the command byte before appending the custom request parameters in forming the packet.
 */
- (void)customCommandWithRequestFlag:(RequestFlag)flags
                   customCommandCode:(NSInteger)customCommandCode
             customRequestParameters:(NSData *)customRequestParameters
                   completionHandler:(void(^)(NSData *customResponseParameters, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*
 * The following is defined by the NFC Forum Type 5 tag specification
 */

/*!
 * @method extendedReadSingleBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          If Option flag in the request flags is set, then first byte of the returned data block will contain the associated block security status.
 *
 * @discussion              Extended read single block command (0x30 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadSingleBlockWithRequestFlags:(RequestFlag)flags
                                    blockNumber:(NSInteger)blockNumber
                              completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedWriteSingleBlockWithRequestFlags:blockNumber:dataBlock:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param dataBlock         A single block of data.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Extended write single block command (0x31 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedWriteSingleBlockWithRequestFlags:(RequestFlag)flags
                                     blockNumber:(NSInteger)blockNumber
                                       dataBlock:(NSData *)dataBlock
                               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedLockBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Extende lock single block command (0x32 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedLockBlockWithRequestFlags:(RequestFlag)flags
                              blockNumber:(NSInteger)blockNumber
                        completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedReadMultipleBlocksWithRequestFlags:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 65535 inclusively.  Valid length is 1 to 65536 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object.  If Option flag in the request flags is set,
 *                          then first byte of each returned data blocks will contain the associated block security status.
 *
 * @discussion              Extended read multiple block command (0x33 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadMultipleBlocksWithRequestFlags:(RequestFlag)flags
                                        blockRange:(NSRange)blockRange
                                 completionHandler:(void(^)(NSArray<NSData *> *dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO15693Tag_h */
// ==========  CoreNFC.framework/Headers/NSUserActivity+CoreNFC.h
//
//  NSUserActivity+CoreNFC.h
//  CoreNFC NSUserActivity category
//
//  Copyright © 2017 Apple. All rights reserved.
//
#ifndef NSUserActivity_CoreNFC_h
#define NSUserActivity_CoreNFC_h

#import <Foundation/Foundation.h>

@class NFCNDEFMessage;

NS_ASSUME_NONNULL_BEGIN


/*!
 * @category    NSUserActivity
 *
 * @discussion  Core NFC category for NSUserActivity.
 */
@interface NSUserActivity (CoreNFC)
/*!
 *  @property ndefMessagePayload
 *
 *  @discussion The NFC NDEF message with an Universial Link object that triggers the application launch.
 */
@property (readonly, nonnull, nonatomic) NFCNDEFMessage *ndefMessagePayload API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  CoreNFC.framework/Headers/NFCMiFareTag.h
//
//  NFCMiFareTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCMiFareTag_h
#define NFCMiFareTag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag, NFCNDEFTag;
@class NFCISO7816APDU;

/*!
 * @enum NFCMiFareFamily
 *
 * @constant NFCMiFareUnknown       MiFare compatible ISO14443 Type A tag.
 * @constant NFCMiFareUltralight    MiFare Ultralight series.
 * @constant NFCMiFarePlus          MiFare Plus series.
 * @constant NFCMiFareDESFire       MiFare DESFire series.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ENUM(NSUInteger, NFCMiFareFamily) {
    NFCMiFareUnknown        = 1,
    NFCMiFareUltralight     = 2,
    NFCMiFarePlus           = 3,
    NFCMiFareDESFire        = 4,
};


/*!
 * @protocol NFCMiFareTag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol when a MiFare tag is detected.  Unless it is specified
 *              all block completion handlers are dispatched on the session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation method if the required entitlement
 *              is missing when session is started.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCMiFareTag <NFCTag, NFCNDEFTag>

/*!
 * @property mifareFamily   MiFare product type identifier.
 */
@property (nonatomic, readonly, assign) NFCMiFareFamily mifareFamily API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion The hardware UID of the tag.
 */
@property (nonatomic, readonly, copy) NSData *identifier;

/*!
 * @discussion The optional historical bytes extracted from the Answer To Select response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *historicalBytes;

/*!
 * @method sendMiFareCommand:completionHandler:
 *
 * @param command           The complete MiFare command.  The CRC bytes shall be included for MiFare UltraLight commands.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds. A @link NFCErrorDomain @link/ error
 *                          is returned when there is a communication issue with the tag. Successfully read data blocks will be returned from the NSData object.
 *
 * @discussion              Send native MIFARE command to a tag.  Support MIFARE UltraLight, Plus, and DESFire products.
 *                          Crypto1 protocol is not supported.  Command chainning is handled internally by the method and the full response composed of the
 *                          individual fragment is returned in the completion handler.
 */
- (void)sendMiFareCommand:(NSData *)command
        completionHandler:(void(^)(NSData *response, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method sendMiFareISO7816Command:completionHandler:
 *
 * @param apdu              The ISO7816-4 command APDU object.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag or tag does not support ISO7816-4 commands,
 *                          and all other parameters should be ignore.
 *
 * @discussion  Send a ISO7816 command APDU to the tag and receives a response APDU.  Only available when @link mifareFamily @link/ returns NFCMiFarePlus, NFCMiFareDESFire.
 */
- (void)sendMiFareISO7816Command:(NFCISO7816APDU *)apdu
      completionHandler:(void(^)(NSData *responseData, uint8_t sw1, uint8_t sw2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCMiFareTag_h */
// ==========  CoreNFC.framework/Headers/NFCTagReaderSession.h
//
//  NFCTagReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCTagReaderSession_h
#define NFCTagReaderSession_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag;
@class NFCTagReaderSession;

/*!
 * @protocol NFCTagReaderSessionDelegate
 *
 * @discussion Tag reader session delegate
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCTagReaderSessionDelegate <NSObject>
@required

/*!
 * @method tagReaderSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)tagReaderSession:(NFCTagReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@optional

/*!
 * @method tagReaderSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 *                  The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
- (void)tagReaderSessionDidBecomeActive:(NFCTagReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method tagReaderSession:didDetectTags:
 *
 * @param session   The session object used for tag detection.
 * @param tags      Array of @link NFCTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) in the polling sequence.
 */
- (void)tagReaderSession:(NFCTagReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCTag>> *)tags API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


#pragma mark - Raw tag reader session

/*!
 * @class NFCTagReaderSession
 *
 * @discussion  Reader session for processing NFC tags supporting one of the @link NFCTagType @link/ types.  @link [NFCTagReaderSessionDelegate readerSession:didDetectTags:] @link/
 *              will return tag objects matching the requested type for the session.  This session requires the "com.apple.developer.nfc.readersession.formats" entitlement
 *              in your process.  In addition your application's Info.plist must contain a non-empty usage description string. @link NFCReaderErrorSecurityViolation @link/ will be
 *              returned from @link [NFCTagReaderSessionDelegate tagReaderSession:didInvalidateWithError:] @link/ if the required entitlement is missing when session is started.
 *
 * NOTE:
 * - Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 * - If the session is configured with @link NFCPollingISO14443 @link/ and an ISO7816 compliant MiFare tag that contains one of the applications listed in the
 *   "com.apple.developer.nfc.readersession.iso7816.select-identifiers" array in Info.plist is found, then @link [NFCTagReaderSessionDelegate readerSession:didDetectTags:] @link/
 *   will return a tag instance conform to the @link NFCISO7816Tag @link/ protocol.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCTagReaderSession : NFCReaderSession

/*!
 *  @property connectedTag  Current connected tag object; nil if no tag is connected in the session.
 */
@property (nonatomic, readonly, retain, nullable) id<NFCTag> connectedTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @enum NFCPollingOption
 *
 * @constant NFCPollingISO14443     Support both Type A & B modulation.  NFCTagTypeISO7816Compatible and NFCTagTypeMiFare tags will be discovered.
 * @constant NFCPollingISO15693     NFCTagTypeISO15693 tag will be discovered.
 * @constant NFCPollingISO18092     NFCTagTypeFeliCa tag will be discovered.
 */
typedef NS_OPTIONS(NSInteger, NFCPollingOption) {
    NFCPollingISO14443      = 0x1,
    NFCPollingISO15693      = 0x2,
    NFCPollingISO18092      = 0x4,
};

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithPollingOption:delegate:queue:
 *
 * @param pollingOption Configures the RF polling of the reader session; multiple options can be OR'ed together.  This option affects the possible NFC tag type discover.
 * @param delegate      The session will hold a weak ARC reference to this @link NFCTagReaderSessionDelegate @link/ object.
 * @param queue         A dispatch queue where NFCTagReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                      cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return              A new NFCTagReaderSession instance.
 */
- (instancetype)initWithPollingOption:(NFCPollingOption)pollingOption
                             delegate:(id<NFCTagReaderSessionDelegate>)delegate
                                queue:(nullable dispatch_queue_t)queue API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions") ;

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new tags.  New tags discovered from polling will return in the subsequent @link [NFCTagReaderSessionDelegate tagReaderSession:didDetectTags:]
 *             @link/ call. Tags that are returned previously by @link [NFCTagReaderSessionDelegate tagReaderSession:didDetectTags:] @link/ will become invalid, 
 *             and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader.
 */
- (void)restartPolling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method connectToTag:completionHandler:
 *
 * @param tag   A NFCTag protocol compliant tag object that will be connected to.
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion  This method establishes a tag connection and activates the tag.  Connecting to the same tag that is currently opened has no effect.
 *              Connecting to a different tag will automatically terminate the previous tag connection and put it into the halt state.  Tag stays in the
 *              connected state until another tag is connected or the polling is restarted.
 */
- (void)connectToTag:(id<NFCTag>)tag completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCTagReaderSession_h */
