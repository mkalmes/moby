// ==========  MessageUI.framework/Headers/MFMessageComposeViewController.h

/*!
 @header     MFMessageComposeViewController
 @abstract   The MFMessageComposeViewController class provides an interface for editing and sending a text
			 message.
 @discussion MFMessageComposeViewController is used for implementing a simple interface for users to enter
			 and send a text message including multimedia attachments.
 @copyright  Copyright 2009 - 2016 Apple Inc. All rights reserved.
 */
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MessageComposeResult
 @abstract   Composition result sent to the delegate upon user completion.
 @discussion This result will inform the client of the user's message composition action.  If the
			 user cancels the composition, <tt>MessageComposeResultCancelled</tt> will be sent to the delegate.
			 Typically <tt>MessageComposeResultSent</tt> will be sent, but <tt>MessageComposeResultFailed</tt> will
			 be sent in the case of failure. </p>Send may only be interpreted as a successful queueing of
			 the message for later sending. The actual send will occur when the device is able to send.
 @constant   MessageComposeResultCancelled   User canceled the composition.
 @constant   MessageComposeResultSent        User successfully sent/queued the message.
 @constant   MessageComposeResultFailed      User's attempt to save or send was unsuccessful.
 */

typedef NS_ENUM(NSInteger, MessageComposeResult) {
    MessageComposeResultCancelled,
    MessageComposeResultSent,
    MessageComposeResultFailed
} API_AVAILABLE(ios(4.0));

/*!
 @constant  MFMessageComposeViewControllerAttachmentURL   The url for the given attachment.
*/
extern NSString *const MFMessageComposeViewControllerAttachmentURL;

/*!
 @constant  MFMessageComposeViewControllerAttachmentAlternateFilename   The alternate filename for the given attachment.
 */
extern NSString *const MFMessageComposeViewControllerAttachmentAlternateFilename;

/*!
 @const      MFMessageComposeViewControllerTextMessageAvailabilityDidChangeNotification
 @abstract   Notification posted when the value of <tt>+[MFMessageComposeViewController canSendText]</tt> has changed.
 @discussion This notification is posted when the value of <tt>+[MFMessageComposeViewController canSendText]</tt>
             has changed. Clients should invalidate any caches and update UI as appropriate.
*/
extern NSString *const MFMessageComposeViewControllerTextMessageAvailabilityDidChangeNotification API_AVAILABLE(ios(5.0));

/*!
 @const      MFMessageComposeViewControllerTextMessageAvailabilityKey
 @abstract   UserInfo key for MFMessageComposeViewControllerTextMessageAvailabilityDidChangeNotification
             containing the value of <tt>+[MFMessageComposeViewController canSendText]</tt>
 @discussion The value of this key is an NSNumber containing a BOOL value. This value matches
             the result of <tt>+[MFMessageComposeViewController canSendText]</tt>.
*/
extern NSString *const MFMessageComposeViewControllerTextMessageAvailabilityKey API_AVAILABLE(ios(5.0));

@class MSMessage;
@protocol MFMessageComposeViewControllerDelegate;

/*!
 @class       MFMessageComposeViewController
 @abstract    The MFMessageComposeViewController class provides an interface for editing and sending a message.
 @discussion  The MFMessageComposeViewController class manages all user interaction.  The client needs to set
			  the recipient or recipients.  The client may also set the body of the message. After setup, the
			  client needs to only display the view.
			  </p>The provided delegate will be informed of the user's composition completion and how they chose
			  to complete the operation.
			  <p>Prior to use, clients should verify the user has set up the device for sending messages via
			  <tt>+[MFMessageComposeViewController canSendText]</tt>.
 */
API_AVAILABLE(ios(4.0))
@interface MFMessageComposeViewController : UINavigationController {
}

/*!
 @method     canSendText
 @abstract   Returns <tt>YES</tt> if the user has set up the device for sending text only messages.
 @discussion If the return value is YES, the client can set the recipients and body of the message.
			 If the return value is NO, the client may notify the user of the failure, or the
			 client may open an SMS URL via <tt>-[UIApplication openURL:]</tt>.
 */
+ (BOOL)canSendText;

/*!
 @method     canSendSubject
 @abstract   Returns <tt>YES</tt> if the user has set up the device for including subjects in messages.</tt>.
 */
+ (BOOL)canSendSubject API_AVAILABLE(ios(7.0));

/*!
 @method     canSendAttachments
 @abstract   Returns <tt>YES</tt> if the user has set up the device for including attachments in messages.</tt>.
 */
+ (BOOL)canSendAttachments API_AVAILABLE(ios(7.0));

/*!
 @method     isSupportedAttachmentUTI:
 @abstract   Returns <tt>YES</tt>if the attachment at the specified URL could be accepted by the current composition.
 @discussion If the return value is YES, the UTI is acceptable for attachment to a message, a return value of NO
 indicates that the given UTI is unsupported.
 */
+ (BOOL)isSupportedAttachmentUTI:(NSString *)uti API_AVAILABLE(ios(7.0));

/*!
 @property   messageComposeDelegate
 @abstract   This property is the delegate for the MFMessageComposeViewController method callbacks.
 */
@property (nonatomic, nullable, assign) id<MFMessageComposeViewControllerDelegate> messageComposeDelegate;

/*!
 @method     disableUserAttachments;
 @abstract   Calling this method will disable the camera/attachment button in the view controller.  After the controller has been presented,
             this call will have no effect.  The camera / attachment button is visible by default.
 */
- (void)disableUserAttachments API_AVAILABLE(ios(7.0));

/*!
 @property   recipients
 @abstract   This property sets the initial value of the To field for the message to the specified addresses.
 @discussion This property will set the initial value of the To field for the message from an NSArray of
			 NSString instances specifying the message addresses of recipients. This should be called prior
			 to display.
			 </p>After the view has been presented to the user, this property will no longer change the value.
 */
@property (nonatomic, nullable, copy) NSArray<NSString *> *recipients;

/*!
 @property   body
 @abstract   This property sets the initial value of the body of the message to the specified content.
 @discussion This property will set the initial value of the body of the message.  This should be called prior
			 to display.
			 </p>After the view has been presented to the user, this property will no longer change the value.
 */
@property (nonatomic, nullable, copy) NSString *body;

/*!
 @property   subject
 @abstract   This property sets the initial value of the subject of the message to the specified content.
 @discussion This property will set the initial value of the subject of the message.  This should be called prior
 to display.
 </p>After the view has been presented to the user, this property will no longer change the value.
 */
@property (nonatomic, nullable, copy) NSString *subject API_AVAILABLE(ios(7.0));

/*!
 @property   attachments
 @abstract   This property returns an NSArray of NSDictionaries describing the properties of the current attachments.
 @discussion This property returns an NSArray of NSDictionaries describing the properties of the current attachments.
             See MFMessageComposeViewControllerAttachmentURL, MFMessageComposeViewControllerAttachmentAlternateFilename.
 */
@property (nonatomic, nullable, readonly, copy) NSArray<NSDictionary *> *attachments API_AVAILABLE(ios(7.0));

/*!
 @property   message
 @abstract   This property sets the initial interactive message.
 */
@property (nonatomic, nullable, copy) MSMessage *message API_AVAILABLE(ios(10.0));

/*!
 @method     addAttachmentURL:withAlternateFilename:
 @abstract   Returns <tt>YES</tt>if the attachment at the specified URL was added to the composition successfully.
 @discussion If the return value is YES, the attachment was added to the composition. If the return value is NO,
             the attachment was not added to the composition.  All attachment URLs must be file urls.  The file
             URL must not be NIL.  The alternate filename will be display to the user in leiu of the attachments URL.
             The alternate filename may be NIL.
 */
- (BOOL)addAttachmentURL:(NSURL *)attachmentURL withAlternateFilename:(nullable NSString *)alternateFilename API_AVAILABLE(ios(7.0));

/*!
 @method     addAttachmentData:typeIdentifier:filename:
 @abstract   Returns <tt>YES</tt>if the attachment was added to the composition successfully.
 @discussion If the return value is YES, the attachment was added to the composition. If the return value is NO,
 the attachment was not added to the composition.  The data and typeIdentifer must be non-nil.  typeIdentifier should be a valid Uniform Type Identifier.
 */
- (BOOL)addAttachmentData:(NSData *)attachmentData typeIdentifier:(NSString *)uti filename:(NSString *)filename API_AVAILABLE(ios(7.0));

@end


/*!
 @protocol    MFMessageComposeViewControllerDelegate
 @abstract    Protocol for delegate callbacks to MFMessageComposeViewControllerDelegate instances.
 @discussion  This protocol will be implemented by delegates of MFMessageComposeViewController instances.
			  It will be called at various times while the user is composing, sending, or canceling
			  message composition.
 */
@protocol MFMessageComposeViewControllerDelegate <NSObject>
@required
/*!
 @method     messageComposeViewController:didFinishWithResult:
 @abstract   Delegate callback which is called upon user's completion of message composition.
 @discussion This delegate callback will be called when the user completes the message composition.
			 How the user chose to complete this task will be given as one of the parameters to the
			 callback.  Upon this call, the client should remove the view associated with the controller,
			 typically by dismissing modally.
 @param      controller   The MFMessageComposeViewController instance which is returning the result.
 @param      result       MessageComposeResult indicating how the user chose to complete the composition process.
 */
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result;

@end

NS_ASSUME_NONNULL_END
// ==========  MessageUI.framework/Headers/MFMailComposeViewController.h
/*!
    @header     MFMailComposeViewController
    @abstract   The MFMailComposeViewController class provides an interface for editing and sending email.
    @discussion MFMailComposeViewController is used for implementing a simple interface for users to enter
                and send email.
    @copyright  Copyright 2008-2016 Apple Inc. All rights reserved.
*/
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


/*!
    @enum       MFMailComposeResult
    @abstract   Composition result sent to the delegate upon user completion.
    @discussion This result will inform of the user's choice in regards to email composition.  If the user
                cancels the composition, <tt>MFMailComposeResultCancelled</tt> will be sent to the delegate.
                Typically <tt>MFMailComposeResultSent</tt> or <tt>MFMailComposeResultSaved</tt> will
                be sent, but <tt>MFMailComposeResultFailed</tt> will be sent in the case of failure.
                </p>Send may only be interpreted as a successful queueing of the message for later sending.
                The actual send will occur when the device is able to send.
    @constant   MFMailComposeResultCancelled   User canceled the composition.
    @constant   MFMailComposeResultSaved       User successfully saved the message.
    @constant   MFMailComposeResultSent        User successfully sent/queued the message.
    @constant   MFMailComposeResultFailed      User's attempt to save or send was unsuccessful.
*/
typedef NS_ENUM(NSInteger, MFMailComposeResult) {
    MFMailComposeResultCancelled,
    MFMailComposeResultSaved,
    MFMailComposeResultSent,
    MFMailComposeResultFailed
} API_AVAILABLE(ios(3.0));

/*!
    @const      MFMailComposeErrorDomain
    @abstract   Error domain for NSError values stemming from the MFMailCompose API.
    @discussion This error domain is used as the domain for all NSError instances stemmming from the
                MFMailCompose API.  Valid error code values are declared in the <tt>MFMailComposeErrorCode</tt>
                space.
*/
extern NSErrorDomain const MFMailComposeErrorDomain API_AVAILABLE(ios(3.0));

/*!
    @enum       MFMailComposeErrorCode
    @abstract   Error codes for NSError values stemming from the MFMailCompose API.
    @discussion These error codes are used as the codes for all NSError instances stemmming from the
                MFMailCompose API.  These are the only valid values for NSError instances with the
                <tt>MFMailComposeErrorDomain</tt> domain.
    @constant   MFMailComposeErrorCodeSaveFailed    Generic error indicating a save failed.
    @constant   MFMailComposeErrorCodeSendFailed    Generic error indicating a send failed.
*/
typedef NS_ENUM(NSInteger, MFMailComposeErrorCode) {
    MFMailComposeErrorCodeSaveFailed,
    MFMailComposeErrorCodeSendFailed
} API_AVAILABLE(ios(3.0));

@protocol MFMailComposeViewControllerDelegate;

/*!
    @class       MFMailComposeViewController
    @abstract    The MFMailComposeViewController class provides an interface for editing and sending email.
    @discussion  The MFMailComposeViewController class manages all user interaction.  The client needs to set the recipient or
                 recipients.  The client may also set the subject and the body of the message.  Attachments may be added, if
                 so desired.  After setup, the client needs to only display the view.</p>The provided delegate will be informed
                 of the user's composition completion and how they chose to complete the operation.<p>Prior to use, clients
                 should verify the user has set up the device for sending email via <tt>+[MFMailComposeViewController canSendMail]</tt>.
*/
API_AVAILABLE(ios(3.0))
@interface MFMailComposeViewController : UINavigationController
{
@private
    id _internal;
}

/*!
    @method     canSendMail
    @abstract   Returns <tt>YES</tt> if the user has set up the device for sending email.
    @discussion The client may continue to set the recipients and content if the return value was <tt>YES</tt>.  If <tt>NO</tt>
                was the result, the client has a couple options.  It may choose to simply notify the user of the inability to
                send mail, or it may issue a "mailto" URL via <tt>-[UIApplication openURL:]</tt>.
*/
+ (BOOL)canSendMail;

/*!
    @property   mailComposeDelegate
    @abstract   This property is the delegate for the MFMailComposeViewControllerDelegate method callbacks.
 */
@property (nonatomic, nullable, weak) id<MFMailComposeViewControllerDelegate> mailComposeDelegate;

/*!
    @method     setSubject:
    @abstract   This method sets the Subject header for the email message.
    @discussion This method will set the Subject header for the email message.  This should be called prior to display.
                Newlines are removed from the parameter.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      subject  A NSString specifying the message's Subject header.
*/
- (void)setSubject:(NSString *)subject;

/*!
    @method     setToRecipients:
    @abstract   This method sets the To header for the email message to the specified email addresses.
    @discussion This method will set the To header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      toRecipients  A NSArray of NSString instances specifying the email addresses of recipients.
*/
- (void)setToRecipients:(nullable NSArray<NSString *> *)toRecipients;

/*!
    @method     setCcRecipients:
    @abstract   This method sets the CC header for the email message to the specified email addresses.
    @discussion This method will set the CC header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      ccRecipients  A NSArray of NSString instances specifying the email addresses of recipients.
 */
- (void)setCcRecipients:(nullable NSArray<NSString *> *)ccRecipients;

/*!
    @method     setBccRecipients:
    @abstract   This method sets the BCC header for the email message to the specified email addresses.
    @discussion This method will set the BCC header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      bccRecipients    A NSArray of NSString instances specifying the email addresses of recipients.
 */
- (void)setBccRecipients:(nullable NSArray<NSString *> *)bccRecipients;

/*!
    @method     setMessageBody:isHTML:
    @abstract   This method sets the body of the email message to the specified content.
    @discussion This method will set the body of the email message.  This should be called prior to display.
                The user's signature, if specified, will be added after the body content.
    @param      body A NSString containing the body contents of the email message.
    @param      isHTML  A boolean value indicating if the body argument is to be interpreted as HTML content.
*/
- (void)setMessageBody:(NSString *)body isHTML:(BOOL)isHTML;

/*!
    @method     addAttachmentData:mimeType:fileName:
    @abstract   This method adds the specified attachment to the email message.
    @discussion This method adds the specified attachment to the email message.  This should be called prior to display.
                Attachments will be appended to the end of the message.
    @param      attachment   NSData containing the contents of the attachment.  Must not be <tt>nil</tt>.
    @param      mimeType     NSString specifying the MIME type for the attachment, as specified by the IANA
                                (http://www.iana.org/assignments/media-types/). Must not be <tt>nil</tt>.
    @param      filename     NSString specifying the intended filename for the attachment.  This is displayed below
                                the attachment's icon if the attachment is not decoded when displayed.  Must not be <tt>nil</tt>.
*/
- (void)addAttachmentData:(NSData *)attachment mimeType:(NSString *)mimeType fileName:(NSString *)filename;

/*!
 @method     setPreferredSendingEmailAddress:
 @abstract   This method sets the preferred sending account of the email message.
 @discussion This method will set the sending account of the message to the specified email address if the user has an account with such an address set up. If there is no account with such an address, the default account will be used instead.
 The sending email address should be specified as per RFC5322.
 After the view has been presented to the user, this method will no longer change the value.
 @param      emailAddress  A NSString specifying the preferred email address used to send this message.
 */
- (void)setPreferredSendingEmailAddress:(NSString *)emailAddress API_AVAILABLE(ios(11.0));

@end


/*!
    @protocol    MFMailComposeViewControllerDelegate
    @abstract    Protocol for delegate callbacks to MFMailComposeViewController instances.
    @discussion  This protocol must be implemented for delegates of MFMailComposeViewController instances.  It will
                 be called at various times while the user is composing, sending, saving, or canceling email composition.
*/
@protocol MFMailComposeViewControllerDelegate <NSObject>
@optional
/*!
    @method     mailComposeController:didFinishWithResult:error:
    @abstract   Delegate callback which is called upon user's completion of email composition.
    @discussion This delegate callback will be called when the user completes the email composition.  How the user chose
                to complete this task will be given as one of the parameters to the callback.  Upon this call, the client
                should remove the view associated with the controller, typically by dismissing modally.
    @param      controller   The MFMailComposeViewController instance which is returning the result.
    @param      result       MFMailComposeResult indicating how the user chose to complete the composition process.
    @param      error        NSError indicating the failure reason if failure did occur.  This will be <tt>nil</tt> if
                             result did not indicate failure.
*/
- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
// ==========  MessageUI.framework/Headers/MessageUI.h
/*
 *  MessageUI.h
 *  MessageUI
 *
 *  Copyright 2009, 2010 Apple Inc. All rights reserved.
 *
 */


#import <MessageUI/MFMailComposeViewController.h>
#import <MessageUI/MFMessageComposeViewController.h>
