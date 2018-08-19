// ==========  Messages.framework/Headers/MSMessageLiveLayout.h
/*!
 @header     MSMessageLiveLayout
 @copyright  Copyright (c) 2017 Apple Inc. All rights reserved.
 */

#import <Messages/Messages.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessageLiveLayout
 @abstract   The MSMessageLiveLayout is used to indicate a message should be rendered in Messages using an instance of `MSMessagesAppViewController` with a `presentationStyle` of `MSMessagesAppPresentationStyleTranscript`.
 */
NS_CLASS_AVAILABLE_IOS(11_0)
@interface MSMessageLiveLayout : MSMessageLayout

/*!
 @param alternateLayout The alternate layout of the message. This layout will be used on devices that don't support live layout or don't have the iMessage app installed.
 */
- (instancetype)initWithAlternateLayout:(MSMessageTemplateLayout *)alternateLayout NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @property   alternateLayout
 @abstract   The alternate layout of the message. This layout will be used on devices that don't support live layout or don't have the iMessage app installed.
 */
@property (nonatomic, readonly) MSMessageTemplateLayout *alternateLayout;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSMessage.h
/*!
 @header     MSMessage
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class MSMessageLayout, MSSession;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessage
 @abstract   The MSMessage encapsulates the data to be transferred to remote devices.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessage : NSObject <NSCopying, NSSecureCoding>

/*!
 @method     init
 @abstract   Initializes a new message that is not part of a session.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @method     initWithSession:
 @abstract   Initializes a message with a session.
 @see        insertMessage:completionHandler:
 @param      session  The session that new message will join.
 @discussion A message initialized with a session will be updated 
 and moved to the bottom of the conversation transcript when another message created
 with the same session is sent.
 */
- (instancetype)initWithSession:(MSSession *)session NS_DESIGNATED_INITIALIZER;

/*!
 @property   session
 @abstract   An MSSession that identifies the session that message belongs to.
 */
@property (nonatomic, readonly, nullable) MSSession *session;

/*!
 @property   pending
 @abstract   A BOOL representing whether the message is a pending message or is a message that has been sent/received.
 @discussion This value starts as `YES` when creating an `MSMessage` for sending. After calling `-[MSConversation insertMessage:completionHandler:]`, `isPending` still returns `YES` until `-[MSMessagesAppViewController didStartSendingMessage:conversation]` is called. This property is useful for knowing if the `selectedMessage` of `-[MSMessagesAppViewController activeConversation]` represents an unsent message.
 */
@property (nonatomic, readonly, getter=isPending) BOOL pending NS_AVAILABLE_IOS(11_0);

/*!
 @property   senderParticipantIdentifier
 @abstract   A NSUUID instance that identifies the participant that sent the message.
 @discussion This NSUUID identifies the message's sender. This value is scoped to
 the current device and will be different on all devices that participate in the
 conversation.
 */
@property (nonatomic, readonly) NSUUID *senderParticipantIdentifier;

/*!
 @property   layout
 @abstract   A subclass of MSMessageLayout.
 @discussion The MSMessageLayout subclass will be used to construct UI
 representing the message in the conversation transcript.
 */
@property (nonatomic, copy, nullable) MSMessageLayout *layout;

/*!
 @property   URL
 @abstract   A HTTP(S) or data URL used to encode data to be transferred in message.
 @discussion This URL should encode any data that is to be delivered to the extension running
 on the recipient's device(s). When no app exists on the receiving device that
 can consume the message, if this URL is a HTTP(S) url, it will be loaded in a web browser.
 */
@property (nonatomic, copy, nullable) NSURL *URL;

/*!
 @property   shouldExpire
 @abstract   A Boolean value that indicates whether the messages should expire after being read.
 @discussion YES if the message should expire after it is read. Expired messages will
 be deleted a short time after being read by the receiver. The user may opt to keep the message.
 This property defaults to NO.
 */
@property (nonatomic, assign) BOOL shouldExpire;

/*!
 @property   accessibilityLabel
 @abstract   A localized string describing the message.
 @discussion This string should provide a succinct description of the message. This
 will be used by the Accessibility Speech feature when speaking the message for users
 with disabilities.
 */
@property (nonatomic, copy, nullable) NSString *accessibilityLabel;

/*!
 @property   summaryText
 @abstract   A localized string describing the message.
 @discussion This string should provide a succinct description of the message. This
 will be used to provide a summary of the message in the UI.
 */
@property (nonatomic, copy, nullable) NSString *summaryText;

/*!
 @property   error
 @abstract   An error object that indicates why a message failed to send.
 @discussion This value is nil if the message is has not yet been sent, is still
 sending or has been sent successfully.
 */
@property (nonatomic, copy, nullable) NSError *error;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSStickerView.h
/*!
 @header     MSStickerView
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;

/*!
 @class      MSStickerView
 @abstract   A UIView subclass that can display sticker assets.
 @discussion This class is a UIView subclass intended to display stickers. It provides
 drag and drop functionality so that user may drag the displayed sticker from this
 view and place it in the Messages transcript.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerView : UIView

/*!
 @method   initWithFrame:sticker:
 @abstract   Initializes a MSStickerView with a frame and a MSSticker conforming object to display.
 */
- (instancetype)initWithFrame:(CGRect)frame sticker:(nullable MSSticker *)sticker;

/*!
 @property   sticker
 @abstract   The MSSticker object to display.
 @discussion Set this property to nil to remove the current sticker. Setting the
 sticker property does not change the size of a MSStickerView. Call sizeToFit to
 adjust the size of the view to match the sticker.
 */
@property (nonatomic, strong, readwrite, nullable) MSSticker *sticker;

/*!
 @property   animationDuration
 @abstract   The amount of time it takes to go through one cycle of the sticker animation.
 */
@property (nonatomic, readonly) NSTimeInterval animationDuration;

/*!
 @method    startAnimating
 @abstract  Starts animating the sticker in the receiver.
 @discussion This method always starts the animation from the first frame.
 */
- (void)startAnimating;

/*!
 @method    stopAnimating
 @abstract  Stops animating the sticker in the receiver.
 */
- (void)stopAnimating;

/*!
 @method   isAnimating
 @abstract   Returns a Boolean value indicating whether the animation is running.
 */
- (BOOL)isAnimating;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/Messages.h
//
//  Messages.h
//  Messages
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Messages/MessagesDefines.h>

#import <UIKit/UIKit.h>

#import <Messages/MSMessagesAppViewController.h>

#import <Messages/MSConversation.h>

#import <Messages/MSMessage.h>
#import <Messages/MSMessageLayout.h>
#import <Messages/MSMessageTemplateLayout.h>
#import <Messages/MSMessageLiveLayout.h>
#import <Messages/MSSession.h>

#import <Messages/MSSticker.h>
#import <Messages/MSStickerBrowserView.h>
#import <Messages/MSStickerBrowserViewController.h>
#import <Messages/MSStickerBrowserViewDataSource.h>
#import <Messages/MSStickerView.h>

#import <Messages/MSMessageError.h>
// ==========  Messages.framework/Headers/MSMessageTemplateLayout.h
/*!
 @header     MSMessageTemplateLayout
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Messages/MSMessageLayout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessageTemplateLayout
 @abstract   The MSMessageTemplateLayout encapsulates properties used in the construction of UI
 representing a message using the default message layout template.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessageTemplateLayout : MSMessageLayout

/*!
 @property   caption
 @abstract   Text to be used as a caption related to the message content.
 */
@property (nonatomic, copy, nullable) NSString *caption;

/*!
 @property   subcaption
 @abstract   Text to be used as a subcaption related to the message content.
 */
@property (nonatomic, copy, nullable) NSString *subcaption;

/*!
 @property   trailingCaption
 @abstract   Text to be drawn right aligned on the same line as the caption text.
 */
@property (nonatomic, copy, nullable) NSString *trailingCaption;

/*!
 @property   trailingSubcaption
 @abstract   Text to be drawn right aligned on the same line as the subcaption text.
 */
@property (nonatomic, copy, nullable) NSString *trailingSubcaption;

/*!
 @property   image
 @abstract   A UIImage object used to construct the message representation in the conversation transcript.
 @discussion When this property and the mediaURL property are both set, the mediaURL
 property will be ignored.
 */
@property (nonatomic, strong, nullable) UIImage *image;

/*!
 @property   mediaFileURL
 @abstract   The URL to a media file used to construct the message representation in the conversation transcript.
 @discussion This must be a file URL, the data contained in the file must conform to
 kUTTypeImage or kUTTypeMovie. When image property and
 this property are both set, then this property will be ignored.
 */
@property (nonatomic, copy, nullable) NSURL *mediaFileURL;

/*!
 @property   imageTitle
 @abstract   Title text associated with the image or media .
 */
@property (nonatomic, copy, nullable) NSString *imageTitle;

/*!
 @property   imageSubtitle
 @abstract   Subtitle text associated with the image or media .
 */
@property (nonatomic, copy, nullable) NSString *imageSubtitle;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSMessageError.h
//
//  MSMessageError.h
//  Messages
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Messages/MessagesDefines.h>

MESSAGES_EXTERN NSString *const MSStickersErrorDomain NS_AVAILABLE_IOS(10_0);

MESSAGES_EXTERN NSString *const MSMessagesErrorDomain NS_AVAILABLE_IOS(10_0);

typedef NS_ENUM(NSInteger, MSMessageErrorCode) {
    MSMessageErrorCodeUnknown NS_ENUM_AVAILABLE_IOS(11_0) = -1,
    MSMessageErrorCodeFileNotFound = 1,
    MSMessageErrorCodeFileUnreadable,
    MSMessageErrorCodeImproperFileType,
    MSMessageErrorCodeImproperFileURL,
    MSMessageErrorCodeStickerFileImproperFileAttributes,
    MSMessageErrorCodeStickerFileImproperFileSize,
    MSMessageErrorCodeStickerFileImproperFileFormat,
    MSMessageErrorCodeURLExceedsMaxSize,
    MSMessageErrorCodeSendWithoutRecentInteraction NS_ENUM_AVAILABLE_IOS(11_0),
    MSMessageErrorCodeSendWhileNotVisible NS_ENUM_AVAILABLE_IOS(11_0),
    MSMessageErrorCodeAPIUnavailableInPresentationContext NS_ENUM_AVAILABLE_IOS(12_0),
} NS_ENUM_AVAILABLE_IOS(10_0);
// ==========  Messages.framework/Headers/MSMessageLayout.h
/*!
 @header     MSMessageLayout
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessageLayout
 @abstract   The MSMessageLayout is an abstract base for classes that define a messages presentation in the conversation transcript.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessageLayout : NSObject <NSCopying>
@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MessagesDefines.h
//
//  MessagesDefines.h
//  Messages
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define MESSAGES_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define MESSAGES_EXTERN extern __attribute__((visibility("default")))
#endif
// ==========  Messages.framework/Headers/MSSticker.h
/*!
 @header     MSSticker
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSSticker : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method     initWithContentsOfFileURL:localizedDescription:error:
 @abstract   Initializes a sticker with the contents of the URL and the localized description.
 @discussion Initializes a sticker with the contents of the URL and the localized description.
 The specified file must have a maximum size of 500KB and must conform to kUTTypePNG, kUTTypeGIF
 or kUTTypeJPEG. The image loaded from the file must be no smaller than 300px X 300px and must
 be no larger 618px x 618px. This localized description string is limited to 150 Unicode
 characters in length.
 @param      fileURL    The URL from which to read sticker data.
 @param      localizedDescription   A succinct localized string describing the sticker.
 @param      error  If this method could not initialize a sticker, this will contain an NSError object describing the failure.
 @return     A new sticker object or nil if the method could not initialize a sticker from the specified file and localizedDescription.
 */
- (nullable instancetype)initWithContentsOfFileURL:(NSURL *)fileURL localizedDescription:(NSString *)localizedDescription error:(NSError *_Nullable *)error NS_DESIGNATED_INITIALIZER;

/*!
 @property   imageFileURL
 @abstract   The file URL to the Sticker was initialized with.
 */
@property (nonatomic, strong, readonly) NSURL *imageFileURL;

/*!
 @property   localizedDescription
 @abstract   A succinct localized string describing the sticker.
 */
@property (nonatomic, copy, readonly) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSStickerBrowserView.h
/*!
 @header     MSStickerBrowserView
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Messages/MSStickerBrowserViewDataSource.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MSStickerSize
 @abstract   Sticker size is used to control the display size of the stickers in the Sticker Browser View.
 @constant   MSStickerSizeSmall     Stickers will be drawn in a small frame.
 @constant   MSStickerSizeRegular   Stickers will be drawn in a medium frame.
 @constant   MSStickerSizeLarge     Stickers will be drawn in a large frame.
 */
typedef NS_ENUM(NSInteger, MSStickerSize) {
    MSStickerSizeSmall,
    MSStickerSizeRegular,
    MSStickerSizeLarge,
} NS_ENUM_AVAILABLE_IOS(10_0);

/*!
 @class      MSStickerBrowserView
 @abstract   A UIView subclass that can display a collection of sticker assets.
 @discussion This class is a UIView subclass intended to display a collection of
 stickers. It provides drag and drop functionality so that user may drag an individual
 stickers from this view and place it in the Messages transcript. Stickers may also be
 tapped to add them directly to Messages input field.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerBrowserView : UIView

/*!
 @method   initWithFrame:
 @abstract   Initializes a MSStickerBrowserView with a frame using the regular size class.
 */
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

/*!
 @method   initWithFrame:stickerSize:
 @abstract   Initializes a MSStickerBrowserView with a frame and sticker size class.
 @discussion Sticker images will be laid out in a grid similar to a UICollectionView
 configured with flow layout.
 @property size hints the size of the cells, the size a sticker is drawn at will
 vary based on the device. Sticker images will be scaled down to fit in the grid cell. If the
 sticker image is smaller than the cell size measured in pixels then it will be  centered
 in the grid cell.
 */
- (instancetype)initWithFrame:(CGRect)frame stickerSize:(MSStickerSize)stickerSize NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The sticker size class.
 */
@property (nonatomic, assign, readonly) MSStickerSize stickerSize;

/*!
 @abstract The Sticker Browser View data source.
 */
@property (nonatomic, weak, nullable) id<MSStickerBrowserViewDataSource> dataSource;

/*!
 @abstract The Sticker Browser View content offset.
 */
@property (nonatomic, assign, readwrite) CGPoint contentOffset;

/*!
 @abstract The Sticker Browser View content inset.
 */
@property (nonatomic, assign, readwrite) UIEdgeInsets contentInset;

/*!
 @abstract animate Sticker Browser View at constant velocity to new offset.
 */
- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;


/*!
 @abstract Asks the Sticker Browser View to reload its data from its data source.
 */
- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSConversation.h
/*!
 @header     MSConversation
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;
@class MSMessage;

NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSConversation : NSObject

/*!
 @property   localParticipantIdentifier
 @abstract   A NSUUID that identifies conversation participant on this device.
 @discussion This NSUUID  that identifies conversation participant on this device,
 this value will be stable while the extension is enabled. If the extension is
 disabled and re-enabled or the containing App is removed and re-installed this
 value will change.
 */
@property (nonatomic, readonly) NSUUID *localParticipantIdentifier;

/*!
 @property   remoteParticipantIdentifiers
 @abstract   A NSArray of NSUUID instances, each uniquely identifies a remote participant in the conversation.
 @discussion Each NSUUID identifies the a remote participant in the conversation scoped to
 this device. These values will be stable while the extension is enabled. If the extension
 is disabled and re-enabled or the containing App is removed and re-installed these
 values will change.
 */
@property (nonatomic, readonly) NSArray<NSUUID *> *remoteParticipantIdentifiers;

/*!
 @property   selectedMessage
 @abstract   An MSMessage instance that may be edited and returned to Messages
 @discussion If the extension has been invoked in response to the user interacting with
 a message in the conversation transcript this property will contain the message.
 Otherwise this property will be nil. The message object provided may be saved to the
 file system. Later, this saved object may be loaded, modified and staged for sending.
 */
@property (nonatomic, readonly, nullable) MSMessage *selectedMessage;

/*!
 @method     insertMessage:completionHandler:
 @abstract   Stages the provided MSMessage object for sending.
 @discussion This method inserts a MSMessage object into the Messages input field,
 Subsequent calls to this method will replace any existing message on the input field. 
 If the message was successfully inserted on the input field, the completion handler
 will be called with a nil error parameter otherwise the error parameter will be
 populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      message            The MSMessage instance describing the message to be sent.
 @param      completionHandler  A completion handler called when the message has been staged or if there was an error.
 */
- (void)insertMessage:(MSMessage *)message completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertSticker:completionHandler:
 @abstract   The sticker is inserted into the Messages.app input field.
 @param      sticker            The sticker to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertSticker:(MSSticker *)sticker completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertText:completionHandler:
 @abstract   The NSString instance provided in the text parameter is inserted into the Messages.app input field.
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      text               The text to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertText:(NSString *)text completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     insertAttachment:withAlternateFilename:completionHandler:
 @abstract   The NSURL instance provided in the URL parameter is inserted into the Messages.app
 input field. This must be a file URL.
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext` if the attachment type is not an image type supported by `MSSticker`.
 @param      URL                The URL to the media file to be inserted.
 @param      filename           If you supply a string here, the message UI uses it for the attachment. Use an alternate filename to better describe the attachment or to make the name more readable.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)insertAttachment:(NSURL *)URL withAlternateFilename:(nullable NSString *)filename completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method     sendMessage:completionHandler:
 @abstract   Start sending a message
 @discussion This method begins sending the provided MSMessage. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      message            The MSMessage instance describing the message to be sent.
 @param      completionHandler  A completion handler called when the message has been staged or if there was an error.
 */
- (void)sendMessage:(MSMessage *)message completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendSticker:completionHandler:
 @abstract   Start sending a sticker
 @discussion Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      sticker            The sticker to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendSticker:(MSSticker *)sticker completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendText:completionHandler:
 @abstract   Start sending text
 @discussion This method begins sending the provided NSString. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      text               The text to be inserted.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendText:(NSString *)text completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

/*!
 @method     sendAttachment:withAlternateFilename:completionHandler:
 @abstract   Start sending a file located at the provided URL. This must be a file URL.
 @discussion This method begins sending the file at the provided file URL. The app must be visible and have had a recent touch interaction since either last launch or last send to succeed. If the message started sending successfully, the completion handler will be called with a nil error parameter. Otherwise the error parameter will be populated with an NSError object describing the failure.
 Calling this method when the presentation context is `MSMessagesAppPresentationContextMedia` will result in the completion handler getting called with an error object whose error code is `MSMessageErrorCodeAPIUnavailableInPresentationContext`.
 @param      URL                The URL to the media file to be inserted.
 @param      filename           If you supply a string here, the message UI uses it for the attachment. Use an alternate filename to better describe the attachment or to make the name more readable.
 @param      completionHandler  A completion handler called when the insert is complete.
 */
- (void)sendAttachment:(NSURL *)URL withAlternateFilename:(nullable NSString *)filename completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSStickerBrowserViewController.h
/*!
 @header     MSStickerBrowserViewController
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Messages/MSStickerBrowserView.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract The MSStickerBrowserViewController class creates a controller object that manages a MSStickerBrowserView.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerBrowserViewController : UIViewController <MSStickerBrowserViewDataSource>

/*!
 @method   initWithStickerSize:
 @abstract Initializes a MSStickerBrowserViewController and configures it's MSStickerBrowserView with the provided sticker size class.
 */
- (instancetype)initWithStickerSize:(MSStickerSize)stickerSize NS_DESIGNATED_INITIALIZER;

/*!
 @property   stickerBrowserView
 @abstract   Returns the sticker browser view managed by the controller object.
 */
@property (nonatomic, strong, readonly) MSStickerBrowserView *stickerBrowserView;

/*!
 * @abstract Controls the size of the stickers are displayed at in the sticker browser view.
 */
@property (nonatomic, readonly) MSStickerSize stickerSize;

@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSSession.h
/*!
 @header     MSSession
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MSSession
 @abstract A MSSession establishes a relationship between a sequence of messages within a conversation.
 @discussion Messages created with the same session are represented as a single
 entry in the conversation transcript.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSSession : NSObject <NSSecureCoding>
@end

NS_ASSUME_NONNULL_END
// ==========  Messages.framework/Headers/MSMessagesAppViewController.h
/*!
 @header     MSMessagesAppViewController
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class MSConversation, MSMessage;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MSMessagesAppPresentationStyle
 @abstract   Describes how the extension is presented in Messages.
 @constant   MSMessagesAppPresentationStyleCompact     The extension's UI is presented compact in the keyboard area.
 @constant   MSMessagesAppPresentationStyleExpanded   The extension's UI is presented expanded taking up most of the screen.
 @constant   MSMessagesAppPresentationStyleTranscript   The extension's UI is presented in the transcript of the conversation in Messages.
 */
typedef NS_ENUM(NSUInteger, MSMessagesAppPresentationStyle) {
    MSMessagesAppPresentationStyleCompact,
    MSMessagesAppPresentationStyleExpanded,
    MSMessagesAppPresentationStyleTranscript NS_ENUM_AVAILABLE_IOS(11_0),
} NS_ENUM_AVAILABLE_IOS(10_0);


/*!
 @enum       MSMessagesAppPresentationContext
 @abstract   Describes the context for which the extension was launched
 @constant   MSMessagesAppPresentationContextMessages   The extension was launched for presentation in Messages
 @constant   MSMessagesAppPresentationContextMedia      The extension was launched for presentation over media content, such as a photo or camera feed
 */
typedef NS_ENUM(NSUInteger, MSMessagesAppPresentationContext) {
    MSMessagesAppPresentationContextMessages,
    MSMessagesAppPresentationContextMedia,
} NS_ENUM_AVAILABLE_IOS(12_0);


NS_AVAILABLE_IOS(11_0)
@protocol MSMessagesAppTranscriptPresentation

/*!
 @method     contentSizeThatFits:
 @abstract   The content size of the view controller's view fitting the constraining size.
 @discussion This method will only be called if the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      size    The maximum size the view will be displayed at.
 */
- (CGSize)contentSizeThatFits:(CGSize)size NS_AVAILABLE_IOS(11_0);

@end


NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSMessagesAppViewController : UIViewController <MSMessagesAppTranscriptPresentation>

/*!
 @property   activeConversation
 @abstract   Current active conversation.
 */
@property (nonatomic, strong, readonly, nullable) MSConversation *activeConversation;

/*!
 @property   presentationStyle
 @abstract   Get the presentation extension's current presentation style.
 */
@property (nonatomic, assign, readonly) MSMessagesAppPresentationStyle presentationStyle;

/*!
 @property   presentationContext
 @abstract   The context for which the extension was launched
 */
@property (nonatomic, readonly) MSMessagesAppPresentationContext presentationContext NS_AVAILABLE_IOS(12_0);

/*!
 @method     requestPresentationStyle:
 @abstract   Requests that Messages transition the extension to the specified presentation style.
 @discussion When the current `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`, a new instance of `MSMessagesAppViewController` will be instantiated with the requested presentation style if needed.
 @param      presentationStyle   The presentation style to transition to. `MSMessagesAppPresentationStyleTranscript` is not a valid presentation style to request.
 */
- (void)requestPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle;

/*!
 @method     willBecomeActiveWithConversation:
 @abstract   Called when the extension is about to become active.
 @param      conversation   The current conversation.
 */
- (void)willBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didBecomeActiveWithConversation:
 @abstract   Called when the extension has become active active.
 @param      conversation   The current conversation.
 */
- (void)didBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     willResignActiveWithConversation:
 @abstract   Called when the extension will resign active.
 @param      conversation   The current conversation.
 */
- (void)willResignActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didResignActiveWithConversation:
 @abstract   Called when the extension has resigned active.
 @param      conversation   The current conversation.
 */
- (void)didResignActiveWithConversation:(MSConversation *)conversation;

@end


@interface MSMessagesAppViewController (CompactOrExpandedPresentation)

/*!
 @method     dismiss
 @abstract   Tells Messages to dismiss the extension and present the keyboard.
 @discussion Calling this method does nothing when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 */
- (void)dismiss NS_AVAILABLE_IOS(10_0);

/*!
 @method     willSelectMessage:conversation:
 @abstract   Informs the extension that a new message will be selected in the conversation.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
- (void)willSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didSelectMessage:conversation:
 @abstract   Informs the extension that a new message has been selected in the conversation.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
- (void)didSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didReceiveMessage:conversation:
 @abstract   Informs the extension that a new message has arrived.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message received.
 @param      conversation    The conversation.
 */
- (void)didReceiveMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didStartSendingMessage:conversation:
 @abstract   Informs the extension that the message send has been triggered.
 @discussion This is called when a user interaction with Messages start the message send process. It does not guarantee the message will be successfully sent or delivered. This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript` or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message being sent.
 @param      conversation    The conversation the message belongs to.
 */
- (void)didStartSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     didCancelSendingMessage:conversation:
 @abstract   Informs the extension that the user has removed the message from the input field.
 @discussion This method will not be called when the `presentationStyle` is MSMessagesAppPresentationStyleTranscript or the `presentationContext` is `MSMessagesAppPresentationContextMedia`.
 @param      message    The message sent.
 @param      conversation    The conversation.
 */
- (void)didCancelSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation NS_AVAILABLE_IOS(10_0);

/*!
 @method     willTransitionToPresentationStyle:
 @abstract   Called when the extension is about to transition to a new presentation style.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      presentationStyle   The new presentation style.
 */
- (void)willTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle NS_AVAILABLE_IOS(10_0);

/*!
 @method     didTransitionToPresentationStyle:
 @abstract   Called when the extension finished transitioning to a presentation style.
 @discussion This method will not be called when the `presentationStyle` is `MSMessagesAppPresentationStyleTranscript`.
 @param      presentationStyle   The new presentation style.
 */
- (void)didTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle NS_AVAILABLE_IOS(10_0);

@end


NS_ASSUME_NONNULL_END


// ==========  Messages.framework/Headers/MSStickerBrowserViewDataSource.h
/*!
 @header     MSStickerBrowserViewDataSource
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;
@class MSStickerBrowserView;

/*!
 * @abstract The MSStickerBrowserViewDataSource protocol declares the methods that the Sticker Browser View uses to access the contents of its data source object.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@protocol MSStickerBrowserViewDataSource <NSObject>

/*!
 * @abstract Returns the number of Stickers that the sticker browser should show.
 * @param stickerBrowserView The sticker browser view .
 * @result The number of stickers.
 */
- (NSInteger)numberOfStickersInStickerBrowserView:(MSStickerBrowserView *)stickerBrowserView;

/*!
 * @abstract Returns the sticker that the sticker browser should show in the browser.
 * @param stickerBrowserView The sticker browser view.
 * @param index The index of the sticker to show.
 * @result A MSSticker object.
 */
- (MSSticker *)stickerBrowserView:(MSStickerBrowserView *)stickerBrowserView stickerAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
