// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Messaging.h
//
//  CSSearchableItemAttributeSet_Messaging.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

//Well-known mailbox identifiers
CORESPOTLIGHT_EXPORT NSString * const CSMailboxInbox NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxDrafts NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxSent NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxJunk NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxTrash NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxArchive NS_AVAILABLE(10_11, 9_0);

@interface CSSearchableItemAttributeSet (CSMessaging)

//Unique identifier for the account the item is associated with, if any
@property(nullable, copy) NSString *accountIdentifier;

//Array of the canonical handles of the account the item is associated with
//(IM handle, e-mail address, phone number...).
//E.g. in Mail's case, all the email addresses the account receives email on.
@property(nullable, copy) NSArray<NSString*> *accountHandles;

//Contains the HTML content of the document encoded as NSData of UTF-8 encoded string.
@property(nullable, copy) NSData *HTMLContentData;

//Contains the text content of the document.
@property(nullable, copy) NSString *textContent;

//An array of CSPerson objects representing the content of the From: field in an email
@property(nullable, copy) NSArray<CSPerson*> *authors;

//An array of CSPerson objects representing the content of the To: field in an email
@property(nullable, copy) NSArray<CSPerson*> *primaryRecipients;

//An array of CSPerson objects representing the content of the Cc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *additionalRecipients;

//An array of CSPerson objects representing the content of the Bcc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *hiddenAdditionalRecipients;

//Dictionary with all the headers of the message
//Keys are header names and values arrays of strings (because a header might be present multiple times in an email)
@property(nullable, copy) NSDictionary<NSString*,NSArray*> *emailHeaders;

//Array of Mailbox identifiers associated with the item. e.g. CSMailboxInbox, CSMailboxDrafts, CSMailboxSent, or a custom identifier etc.
@property(nullable, copy) NSArray<NSString*> *mailboxIdentifiers;

//The list of author/authors that have worked on this item.
//There could be 0 or more authors of a particular item.
//The order of the authors in the array is preserved, but is not intended to represent
//the main author or relative importance of the authors.
@property(nullable, copy) NSArray<NSString*> *authorNames;

//This attribute indicates the recipients of this item.
@property(nullable, copy) NSArray<NSString*> *recipientNames;

//This attribute indicates the author of the emails message addresses.
//(This is always the email address, and not the human readable version)
@property(nullable, copy) NSArray<NSString*> *authorEmailAddresses;

//This attribute indicates the reciepients email addresses.
//(This is always the email address,  and not the human readable version).
@property(nullable, copy) NSArray<NSString*> *recipientEmailAddresses;

//This attribute indicates the author addresses of the document.
@property(nullable, copy) NSArray<NSString*> *authorAddresses;

//This attribute indicates the recipient addresses of the document.
@property(nullable, copy) NSArray<NSString*> *recipientAddresses;

//Phone numbers for this item.
@property(nullable, copy) NSArray<NSString*> *phoneNumbers;

//Email addresses for this item.
@property(nullable, copy) NSArray<NSString*> *emailAddresses;

//Instant message addresses for this item.
@property(nullable, copy) NSArray<NSString*> *instantMessageAddresses;

//This attribute indicates if the document is likely to be considered junk.  Should be 1 if true, 0 otherwise
@property (nonatomic, strong, getter=isLikelyJunk) NSNumber *likelyJunk;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSBase.h
//
//  CSBase.h
//  CoreSpotlight
//
//  Copyright © 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#if !defined(CORESPOTLIGHT_EXPORT)
#define CORESPOTLIGHT_EXPORT extern
#endif

#ifndef CS_AVAILABLE
#define CS_AVAILABLE(mac, ios) NS_AVAILABLE(mac, ios)
#endif

#ifndef CS_CLASS_AVAILABLE
#define CS_CLASS_AVAILABLE(mac, ios) NS_CLASS_AVAILABLE(mac, ios)
#endif

#ifndef CS_DEPRECATED
#define CS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
#endif

#ifndef CS_TVOS_UNAVAILABLE
#define CS_TVOS_UNAVAILABLE __TVOS_PROHIBITED
#endif
// ==========  CoreSpotlight.framework/Headers/CSSearchableIndex.h
//
//  CSSearchableIndex.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItem.h>
#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

CORESPOTLIGHT_EXPORT NSString * const CSIndexErrorDomain CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;

typedef NS_ENUM(NSInteger, CSIndexErrorCode) {
    CSIndexErrorCodeUnknownError =                               -1,
    CSIndexErrorCodeIndexUnavailableError =                   -1000, //The indexer was unavailable
    CSIndexErrorCodeInvalidItemError =                        -1001, //The CSSearchableItem is invalid for some reason
    CSIndexErrorCodeInvalidClientStateError =                 -1002, //The provided clientState was not valid for some reason
    CSIndexErrorCodeRemoteConnectionError =                   -1003, //There was an error trying to communicate with the remote process
    CSIndexErrorCodeQuotaExceeded =                           -1004, //Quota for bundle was exceeded
    CSIndexErrorCodeIndexingUnsupported =                     -1005, //Indexing isn't supported on this device
} CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;

@protocol CSSearchableIndexDelegate;

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSSearchableIndex : NSObject

@property (weak,nullable) id<CSSearchableIndexDelegate> indexDelegate;

// Not all devices support indexing.  Call this method to check if indexing is supported on the current device.
+ (BOOL)isIndexingAvailable;

+ (instancetype)defaultSearchableIndex;

// Apps can set a name for the index instance. This name is used as a handle for the client state used with the batch API, allowing a single client to have multiple client states; you have to retrieve the client state for an index instance with the same name as you used when setting the client state.
- (instancetype)initWithName:(NSString *)name;

//Apps can set a default protection class for items in their entitlements.  You can alternately create an instance with a custom protection class to use on iOS.  It should be one of NSFileProtectionComplete, NSFileProtectionCompleteUnlessOpen, or NSFileProtectionCompleteUntilFirstUserAuthentication.
- (instancetype)initWithName:(NSString *)name protectionClass:(nullable NSFileProtectionType)protectionClass;

// Call this method to add or update items in the index.
// Completion handlers will be called once the data has been journaled by the index.  If the completion handler returns an error, the client should retry, as it was not journaled correctly.
// reindexSearchableItemsWithIdentifiers will be called if the journaling completed successfully but the data was not able to be indexed for some reason.
- (void)indexSearchableItems:(NSArray<CSSearchableItem *> *)items completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method to remove items with the given identifiers from the index.
// Completion handlers will be called once the data has been journaled by the index.  If the completion handler returns an error, the client should retry, as it was not journaled correctly.
// reindexSearchableItemsWithIdentifiers will be called if the journaling completed successfully but the data was not able to be indexed for some reason.
- (void)deleteSearchableItemsWithIdentifiers:(NSArray<NSString *> *)identifiers completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method on the index to remove any items from the index with the given domain identifiers.
// The delete is recursive so if domain identifiers are of the form <account-id>.<mailbox-id>, for example,
// calling delete with <account-id> will delete all the searchable items with that account and any mailbox.
- (void)deleteSearchableItemsWithDomainIdentifiers:(NSArray<NSString *> *)domainIdentifiers completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method to delete all searchable items from the index.
- (void)deleteAllSearchableItemsWithCompletionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

@end

@interface CSSearchableIndex (CSOptionalBatching)

//Batching:

//For some clients, it may be beneficial to batch updates to the index.  Those clients can use batching and persist client state information (< 250 bytes) in the index.  That state information can be used to determine where indexing needs to resume from in case of a client crash or jetsam. Batching is supported for indexSearchableItems deleteSearchableItemsWithIdentifiers.  Persisted client state will be reset whenever deleteAllSearchableItemsWithCompletionHandler is called.

//Note: Batching is unsupported for the CSSearchableIndex returned by the defaultSearchableIndex method

//Thread safety: In batch mode, the client takes responsibility for protecting the private CSSearchableIndex instance from concurrent access from multiple threads. Concurrent calls to the index instance will have undefined results. beginIndexBatch must not be called again before endIndexBatchWithClientState:completionHandler: has returned (it is however safe to call before the completionHandler passed to endIndexBatchWithClientState:completionHandler has been called).


//Begin a batch of index adds, updates, or deletes.
- (void)beginIndexBatch;

//End a batch passing in client state information to be persisted in the index.  The completion handler will be called once the client state has been persisted.
- (void)endIndexBatchWithClientState:(NSData *)clientState completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Async fetches the app's last stored client state information.
- (void)fetchLastClientStateWithCompletionHandler:(void (^)(NSData * __nullable clientState,NSError * __nullable error))completionHandler;

@end

//An application that is long running should provide a CSSearchableIndexDelegate conforming object to handle communication from the index.
//Alternatively, an app can provide an extension whose request handler conforms to this protocol and the extension will be called if the app isn't running.

CS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@protocol CSSearchableIndexDelegate <NSObject>

@required

// The index requests that the delegate should reindex all of its searchable data and clear any local state that it might have persisted because the index has been lost.
// The app or extension should call indexSearchableItems on the passed in CSSearchableIndex.
// The app or extension must call the acknowledgement handler once any client state information has been persisted, that way, in case of a crash, the indexer can call this again.
// If the app passes clientState information in a batch, the acknowledgement can be called right away.
// The passed in index shouldn't be used in an extension if a custom protection class is needed.
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexAllSearchableItemsWithAcknowledgementHandler:(void (^)(void))acknowledgementHandler;

// The index requests that the delegate should reindex the searchable data with the provided identifiers.
// The app or extension should call indexSearchableItems:completionHandler on the passed in index CSSearchableIndex to update the items' states.
// The app or extension must call the acknowledgement handler once any client state information has been persisted, that way, in case of a crash, the indexer can call this again.
// If the app passes clientState information in a batch, the acknowledgement can be called right away.
// The passed in index shouldn't be used in an extension if a custom protection class is needed.
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexSearchableItemsWithIdentifiers:(NSArray <NSString *> *)identifiers
 acknowledgementHandler:(void (^)(void))acknowledgementHandler;

@optional

//When on battery power, it is possible for indexing to slowed down to prevent battery drain.
//The developer may want to optionally implement these methods to receive notice that indexing is being throttled and react accordingly (e.g. by priortizing indexing of more important content).
- (void)searchableIndexDidThrottle:(CSSearchableIndex *)searchableIndex;
- (void)searchableIndexDidFinishThrottle:(CSSearchableIndex *)searchableIndex;

// The developer may provided a NSData representation if type was specified in providerDataTypeIdentifiers property.
- (nullable NSData *)dataForSearchableIndex:(CSSearchableIndex *)searchableIndex itemIdentifier:(NSString *)itemIdentifier typeIdentifier:(NSString *)typeIdentifier error:(out NSError ** __nullable)outError CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// The developer may provided a NSURL to file representation representation if type was specified from providerDataTypeIdentifiers or providerInPlaceFileTypeIdentifiers property.
- (nullable NSURL *)fileURLForSearchableIndex:(CSSearchableIndex *)searchableIndex itemIdentifier:(NSString *)itemIdentifier typeIdentifier:(NSString *)typeIdentifier inPlace:(BOOL)inPlace error:(out NSError ** __nullable)outError CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Categories.h
//
//  CSSearchableItemAttributeSet_Categories.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet_General.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Documents.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Events.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Messaging.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Media.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Images.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Places.h>
// ==========  CoreSpotlight.framework/Headers/CSPerson.h
//
//  CSPerson.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSPerson : NSObject <NSSecureCoding,NSCopying>

- (instancetype)initWithDisplayName:(nullable NSString *)displayName handles:(NSArray<NSString*> *)handles handleIdentifier:(NSString *)handleIdentifier;

@property (readonly,nullable) NSString *displayName; //An optional display name for displaying this recipient

@property (readonly) NSArray<NSString*> *handles; //An array of contact handles, e.g. phone numbers

@property (readonly) NSString *handleIdentifier; //A CNContactPropertyKey to identify the type of of handle, e.g. CNContactPhoneNumbersKey

@property (copy,nullable) NSString *contactIdentifier; //If the property has already been resolved, the identifier for the Contact

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_General.h
//
//  CSSearchableItemAttributeSet_General.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSGeneral)

//A localized string to be displayed in the UI for this item.
@property(nullable, copy) NSString *displayName;

//An array of localized strings of alternate display names for this item.
@property(nullable, copy) NSArray<NSString*> *alternateNames;

//This is the complete path to the item.
@property(nullable, copy) NSString *path;

//Optional file URL representing the content to be indexed
//Applications that are also 'Documents & Data' clients can set this property to allow Spotlight to deduplicate
//their searchable items against the iCloud Drive's items. When this property is set, Spotlight will not display
//the iCloud Drive's searchable items that have the same contentURL property.
@property(nullable, strong) NSURL *contentURL;

//Optional file URL pointing to a thumbnail image for this item
@property(nullable, strong) NSURL *thumbnailURL;

//Optional image data for thumbnail for this item
@property(nullable, copy) NSData *thumbnailData;

//For activities, this is the unique identifier for the item this activity is related to. If the item doesn't exist in the index, the activity will not get stored. When the item is deleted, the activity will also be deleted.
@property(nullable, copy) NSString *relatedUniqueIdentifier;

//For activities, this is the unique identifier for an item this activity is related to. Unlike relatedUniqueIdentifier, this attribute does not link the life time of the items.
@property(nullable, copy) NSString *weakRelatedUniqueIdentifier CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;


//This is the date that the last metadata attribute was changed.
@property(nullable, strong) NSDate *metadataModificationDate;

//UTI Type pedigree for an item.  Common types can be found in UTCoreTypes.h
@property(nullable, copy) NSString *contentType;

@property(nullable, copy) NSArray<NSString*> *contentTypeTree;

//Represents keywords associated with this particular item.
//Example Keywords might be Birthday,Important etc.
@property(nullable, copy) NSArray<NSString*> *keywords;

//The title of this particular item.
//Title of the document, or it could be the title of this mp3 or a subject of a mail message.
@property(nullable, copy) NSString *title;

//A version specifier for this item.
@property(nullable, copy) NSString *version;

//This property is used to indicate if the indexed item was created by the user
//It is used to distinguish pushed app content from content that required explicit user interaction
//Example content that may set this field: user created notes, documents
@property(nullable, strong, getter=isUserCreated) NSNumber *userCreated CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property is used to indicate if the indexed item has been purchased or otherwise acquired by the user
//Example content are songs bought by a user and made searchable
@property(nullable, strong, getter=isUserOwned) NSNumber *userOwned CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property is used to indicate if the indexed item was selected by the user
//It is used to distinguish pushed app content from content that a user has chosen to add to a collection
//Example content that may set this field: downloaded media content, bookmarked websites/news articles
@property(nullable, strong, getter=isUserCurated) NSNumber *userCurated CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property allows content donors to provide a ranking signal to each indexed item
//It will inform the ranker, allowing it to distinguish more easily between otherwise similar items
//This is query-independent and should be used to indicate the relative importance of an item w.r.t. all other items for the same application
//Expected value ∈ [0-100]; preferably integral values
//Monotonically increasing with larger values being considered better results
@property(nullable, strong) NSNumber *rankingHint CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// This property has the same semantics as -[CSSearchableItem domainIdentifier].
// It can be set on the contentAttributeSet property of a NSUserActivity instance and then used to delete the user activity
// by calling [[CSSearchableIndex defaultSearchableIndex] deleteSearchableItemsWithDomainIdentifiers:].
@property(nullable, copy) NSString *domainIdentifier CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;

@end

@interface CSSearchableItemAttributeSet (CSActionExtras)
// If supportsPhoneCall is 1 and the item has the phoneNumbers property, then the phone number may be used to initiate phone calls. This should be used to indicate that using the phone number is appropriate, and a primary action for the user. For example, supportsPhoneCall would be set on a business, but not an academic paper that happens to have phone numbers for the authors or the institution.
@property(nullable, strong) NSNumber *supportsPhoneCall;

// If supportsNavigation is set to 1, and the item has the latitude and longitude properties set, then the latitude and longitude may be used for navigation. For example, supportsNavigation would be set on a restaurant review, but not on a photo.
@property(nullable, strong) NSNumber *supportsNavigation;
@end

@interface CSSearchableItemAttributeSet(CSContainment)
@property(nullable, copy) NSString *containerTitle;
@property(nullable, copy) NSString *containerDisplayName;
@property(nullable, copy) NSString *containerIdentifier;
@property(nullable, strong) NSNumber *containerOrder;
@end

@interface CSSearchableItemAttributeSet (CSItemProvider)
// The string value of type identifer can only be used by one providerTypeIdentifier array.

// An array of types identifiers that owner can provided a NSData representation.
@property(nullable, copy) NSArray<NSString *> *providerDataTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// An array of types identifiers that owner can provided a NSURL to file representation.
@property(nullable, copy) NSArray<NSString *> *providerFileTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// An array of types identifiers that owner can provided a NSURL to inplace file representation.
@property(nullable, copy) NSArray<NSString *> *providerInPlaceFileTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

@end

// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Images.h
//
//  CSSearchableItemAttributeSet_Images.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

@interface CSSearchableItemAttributeSet (CSImages)

//The height of the item in pixels (ie Image height or Video frame height)
@property(nullable, strong) NSNumber *pixelHeight;

//The width of the item in pixels (ie Image width or Video frame width)
@property(nullable, strong) NSNumber *pixelWidth;

//The total number of pixels in the item.
@property(nullable, strong) NSNumber *pixelCount;

//What color space model is this item following (For example, "RGB", "CMYK", "YUV", "YCbCr")
@property(nullable, copy) NSString *colorSpace;

//Number of bits per sample
//For example bit depth of an image (8-bit, 16-bit etc..) or bit
//depth per audio sample of uncompressed audio data (8, 16, 24, 32, 64, etc..)
@property(nullable, strong) NSNumber *bitsPerSample;

//Indicates if the flash was used to take the picture.  Should be 1 if flash is on, 0 otherwise.
@property(nullable, strong, getter=isFlashOn) NSNumber *flashOn;

//The actual focal length of the lens in mm.
@property(nullable, strong) NSNumber *focalLength;

//Indicates if the focal length is 35mm.  Should be 1 if true, 0 otherwise
@property(nullable, strong, getter=isFocalLength35mm) NSNumber *focalLength35mm;

//Device make that was used to acquire this item
@property(nullable, copy) NSString *acquisitionMake;

//Device model that was used to acquire this item
@property(nullable, copy) NSString *acquisitionModel;

//The owner of the camera used to capture this image.
@property(nullable, copy) NSString *cameraOwner;

//The model of the lens used to capture this image.
@property(nullable, copy) NSString *lensModel;

//The ISO Speed the camera was set to when the image was taken. Examples are 100, 200, 400, etc.
@property(nullable, strong) NSNumber *ISOSpeed;

//The orientation of the data.  Should be 0 for Landscape or 1 for Portrait.
@property(nullable, strong) NSNumber *orientation;

//The names of the various layers in the file
@property(nullable, copy) NSArray<NSString*> *layerNames;

//The white balance setting of the camera when the image was acquired.  Should be 0 for Auto or 1 for Manual.
@property(nullable, strong) NSNumber *whiteBalance;

//The size of the lens aperture as a log-scale APEX value when the image was acquired.
@property(nullable, strong) NSNumber *aperture;

//Name of the color profile used for the image
@property(nullable, copy) NSString *profileName;

//Resolution width of this image in DPI
@property(nullable, strong) NSNumber *resolutionWidthDPI;

//Resolution height of this image in DPI
@property(nullable, strong) NSNumber *resolutionHeightDPI;

//Mode that was used for the exposure.  Should be 0 for AutoExposure, 1 for Manual, 2 for AutoBracket.
@property(nullable, strong) NSNumber *exposureMode;

//Time that the lens was open during exposure in seconds
@property(nullable, strong) NSNumber *exposureTime;

//The verion of the EXIF header that was used to generate the metadata
@property(nullable, copy) NSString *EXIFVersion;

//The version of GPSInfoIFD header that was used to generate the metadata
@property(nullable, copy) NSString *EXIFGPSVersion;

//Indicates if this image file has an alpha channel.  Should be 0 for no alpha channel, 1 for alpha channel.
@property(nullable, strong) NSNumber *hasAlphaChannel;

//Indicates if red-eye reduction was used to take the picture.  Should be 0 for no red-eye, 1 for red-eye
@property(nullable, strong,getter=isRedEyeOn) NSNumber *redEyeOn;

//The metering mode for the image (Average, Partial, Pattern, ...)
@property(nullable, copy) NSString *meteringMode;

//The smallest F number of the lens. The unit is the APEX
//value. Ordinarily it is given in the range of 00.00 to 99.99.
@property(nullable, strong) NSNumber *maxAperture;

//The focal length of the lens divided by the diameter of the aperture when the image was acquired.
@property(nullable, strong) NSNumber *fNumber;

//The class of the program used by the camera to set exposure when the picture is taken (Manual, Normal, Aperture Priority, ...)
@property(nullable, copy) NSString *exposureProgram;

//The time  of the exposure as a string, e.g. "1/250 seconds".
@property(nullable, copy) NSString *exposureTimeString;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Documents.h
//
//  CSSearchableItemAttributeSet_Documents.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSDocuments)

///Subject of the this item.
@property(nullable, copy) NSString *subject;

//Theme of the this item.
@property(nullable, copy) NSString *theme;

//An account of the content of the resource. Description may include
//but is not limited to: an abstract, table of contents, reference
//to a graphical representation of content or a free-text account of
//the content.
@property(nullable, copy) NSString *contentDescription;

//Used  to reference to the resource within a given
//context. Recommended best practice is to identify the resource by
//means of a string or number conforming to a formal identification system.
@property(nullable, copy) NSString *identifier;

//A class of entity for whom the resource is intended or useful. A
//class of entity may be determined by the creator or the publisher
//or by a third party.
@property(nullable, copy) NSArray<NSString*> *audiences;

//Size of the document in MB.
@property(nullable, strong) NSNumber *fileSize;

//Number of pages in the item.
@property(nullable, strong) NSNumber *pageCount;

//Width in points (72 points per inch) of the document page
//(first page only for PDF's - other pages within the PDF may
//not be the same width).
@property(nullable, strong) NSNumber *pageWidth;

//Height in points (72 points per inch) of the document page
//(first page only for PDF's - other pages within the PDF may
//not be the same height).
@property(nullable, strong) NSNumber *pageHeight;

//Security (encryption) method used in the file
@property(nullable, strong) NSString *securityMethod;

//Application used to create the document content (e.g. "Word",
//"Framemaker", etc.).
@property(nullable, copy) NSString *creator;

//Software used to convert the original content into a PDF stream
//(e.g. "Distiller", etc.).
@property(nullable, copy) NSArray<NSString*> *encodingApplications;

//Kind that this item represents.
@property(nullable, copy) NSString *kind;

//Array of font names used in the item.
@property(nullable, copy) NSArray<NSString*> *fontNames;

@end
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Media.h
//
//  CSSearchableItemAttributeSet_Media.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_General.h>

NS_ASSUME_NONNULL_BEGIN

@interface CSSearchableItemAttributeSet (CSMedia)

//The list of editor/editors that have worked on this item.
@property(nullable, copy) NSArray<NSString*> *editors;

//The list of people who are visible in an image or movie or written about in a document.
@property(nullable, copy) NSArray<NSString*> *participants;

//The list of projects that this item is part of.
//For example if you were working on a movie, all of the movie files could be marked
//as belonging to the project "My movie"
@property(nullable, copy) NSArray<NSString*> *projects;

// This is the date that the file was last downloaded / received.
@property(nullable, strong) NSDate *downloadedDate;

//This attribute indicates where the item was obtained from.
//Examples:
//- downloaded file may refer to the site they were downloaded from,the refering URL, etc
//- files received by email may indicate who sent the file, the message subject, etc
@property(nullable, copy) NSArray<NSString*> *contentSources;

//This is a comment related to a file.
@property(nullable, copy) NSString *comment;

//This is the copyright of the content.
@property(nullable, copy) NSString *copyright;

//This is the date that the item was last used
@property(nullable, strong) NSDate *lastUsedDate;

//This is the date that the contents of the item were created
@property(nullable, strong) NSDate *contentCreationDate;

//This is the date that the contents of the item were last modified
@property(nullable, strong) NSDate *contentModificationDate;

//This is the date that the item was moved into the current location.
@property(nullable, strong) NSDate *addedDate;

//This is the duration, in seconds, of the content of the item (if appropriate).
@property(nullable, strong) NSNumber *duration;

//A list of contacts that are somehow associated with this document, beyond what is captured as Author.
@property(nullable, copy) NSArray<NSString*> *contactKeywords;

//The codecs used to encode/decode the media
@property(nullable, copy) NSArray<NSString*> *codecs;

//Media types present in the content
@property(nullable, copy) NSArray<NSString*> *mediaTypes;

//Whether the content is prepared for streaming.  Should be 0 for not streamable, 1 for streamable.
@property (nullable, strong, getter=isStreamable) NSNumber *streamable;

//The total bit rate (audio & video combined) of the media
@property(nullable, strong) NSNumber *totalBitRate;
//The video bit rate
@property(nullable, strong) NSNumber *videoBitRate;
//The audio bit rate
@property(nullable, strong) NSNumber *audioBitRate;

//The delivery type of the item.  Should be 0 for fast start and 1 for RTSP.
@property(nullable, strong) NSNumber *deliveryType;

//Used to indicate company/Organization that created the document.
@property(nullable, copy) NSArray<NSString*> *organizations;

//Used to indicate the role of the document creator
@property(nullable, copy) NSString *role;

//Used to designate the languages of the intellectual content of the
//resource. Recommended best practice for the values of the Language
//element is defined by BCP 47.
@property(nullable, copy) NSArray<NSString*> *languages;

//Used to provide a link to information about rights held in and
//over the resource. Typically a Rights element will contain a
//rights management statement for the resource, or reference a
//service providing such information. Rights information often
//encompasses Intellectual Property Rights (IPR), Copyright, and
//various Property Rights. If the rights element is absent, no
//assumptions can be made about the status of these and other rights
//with respect to the resource.
@property(nullable, copy) NSString *rights;

//Used to designate the entity responsible for making the resource
//available. Examples of a Publisher include a person, an
//organization, or a service. Typically, the name of a Publisher
//should be used to indicate the entity.
@property(nullable, copy) NSArray<NSString*> *publishers;

//Used to designate the entity responsible for making contributions
//to the content of the resource. Examples of a Contributor include
//a person, an organization or a service. Typically, the name of a
//Contributor should be used to indicate the entity.
@property(nullable, copy) NSArray<NSString*> *contributors;

//Used to designate the extent or scope of the content of the
//resource. Coverage will typically include spatial location
//(a place name or geographic co-ordinates), temporal period (a period label, date, or date range)
//or jurisdiction (such as a named administrative entity).
//Recommended best practice is to select a value from a controlled vocabulary, and that, where appropriate,
//named places or time periods be used in preference to numeric identifiers such as sets of co-ordinates or date ranges.
@property(nullable, copy) NSArray<NSString*> *coverage;

//User rating of this item out of 5 stars
@property(nullable, strong) NSNumber *rating;

//A description of the rating.  E.g. the number of reviewers.
@property(nullable, copy) NSString *ratingDescription;

//User play count of this item
@property(nullable, strong) NSNumber *playCount;

//Information about the item
@property(nullable, copy) NSString *information;

//Director of the item (e.g. movie director)
@property(nullable, copy) NSString *director;

//Producer of the content
@property(nullable, copy) NSString *producer;

//Genre of the item (e.g. movie genre)
@property(nullable, copy) NSString *genre;

//Performers in the movie
@property(nullable, copy) NSArray<NSString*> *performers;

//Original format of the movie
@property(nullable, copy) NSString *originalFormat;

//Original source of the movie
@property(nullable, copy) NSString *originalSource;

//Whether or not the item is local. Should be 1 if true, 0 otherwise.
@property(nullable, strong, getter=isLocal) NSNumber *local;

//Whether or not the item has explicit content. Should be 1 if explicit, 0 for clean.
@property(nullable, strong) NSNumber *contentRating;

//URL of the item
@property(nullable, strong) NSURL *URL;

@end

@interface CSSearchableItemAttributeSet (CSMusic)

//The sample rate of the audio data contained in the file. The sample rate is a
//float value representing hz (audio_frames/second). For example: 44100.0, 22254.54.
@property(nullable, strong) NSNumber *audioSampleRate;

//The number of channels in the audio data contained in the file. This item only represents
//the number of discreet channels of audio data found in the file. It does not indicate
//any configuration of the data in regards to a user's speaker setup.
@property(nullable, strong) NSNumber *audioChannelCount;

//The tempo of the music contained in the audio file in Beats Per Minute.
@property(nullable, strong) NSNumber *tempo;

//The musical key of the song/composition contained in an audio file.
//For example: C, Dm, F#m, Bb.
@property(nullable, copy) NSString *keySignature;

//The time signature of the musical composition contained in the audio/MIDI file.
//For example: "4/4", "7/8".
@property(nullable, copy) NSString *timeSignature;

//The name of the application that encoded the data contained in the audio file.
@property(nullable, copy) NSString *audioEncodingApplication;

//The composer of the song/composition contained in the audio file.
@property(nullable, copy) NSString *composer;

//The lyricist/text writer for song/composition contained in the audio file.
@property(nullable, copy) NSString *lyricist;

//The title for a collection of media. This is analagous to a record album,
//or photo album whichs are collections of audio or images.
@property(nullable, copy) NSString *album;

//The artist for the media
@property(nullable, copy) NSString *artist;

//The track number of a song/composition when it is part of an album
@property(nullable, strong) NSNumber *audioTrackNumber;

//The recording date of the song/composition. This information differs from
//the contentCreationDate attribute as it indicates the date that the
//'art' was created, in contrast to contentCreationDate which for example, could indicate
//the creation date of an edited or 'mastered' version of the original art.
@property(nullable, strong) NSDate *recordingDate;

//The musical genre of the song/composition contained in the audio file.
//For example: Jazz, Pop, Rock, Classical.
@property(nullable, copy) NSString *musicalGenre;

//This attribute indicates whether the MIDI sequence contained in the file is setup for use with a General MIDI device.  Should be 1 if true, 0 otherwise.
@property(nullable, strong,getter=isGeneralMIDISequence) NSNumber *generalMIDISequence;

//Meta data attribute that stores the category of
//instrument. Files should have an instrument associated with
//them ("Other Instrument" is provided as a catch-all). For some
//categories, like "Keyboards" there are instrument names which
//provide a more detailed instrument definition (e.g., Piano,Organ, etc.)
@property(nullable, copy) NSString *musicalInstrumentCategory;

//Meta data attribute that stores the name of instrument
//(relative to the instrument category) Files can have an
//instrument name associated with them if they have certain
//instrument categories (e.g., the category Percussion has
//                       multiple instruments, including Conga and Bongo).
@property(nullable, copy) NSString *musicalInstrumentName;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CoreSpotlight.h
//
//  CoreSpotlight.h
//  CoreSpotlight
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#define  CoreSpotlightAPIVersion 40

#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSSearchableItem.h>
#import <CoreSpotlight/CSPerson.h>
#import <CoreSpotlight/CSSearchableIndex.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_Categories.h>
#import <CoreSpotlight/CSIndexExtensionRequestHandler.h>
#import <CoreSpotlight/CSSearchQuery.h>

//! Project version number for CoreSpotlight.
CORESPOTLIGHT_EXPORT double CoreSpotlightVersionNumber;

//! Project version string for CoreSpotlight.
CORESPOTLIGHT_EXPORT const unsigned char CoreSpotlightVersionString[];
// ==========  CoreSpotlight.framework/Headers/CSSearchableItem.h
//
//  CSSearchableItem.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

// When opening a document from Spotlight, the application's application:willContinueUserActivityWithType:
// method will get called with CSSearchableItemActionType, followed by  application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair where CSSearchableItemActivityIdentifier is the key
// and the value is the uniqueIdentifier used when creating the item.
CORESPOTLIGHT_EXPORT NSString * const CSSearchableItemActionType CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;
CORESPOTLIGHT_EXPORT NSString * const CSSearchableItemActivityIdentifier CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;

// When continuing a query from Spotlight, the application's -application:willContinueUserActivityWithType:
// method will get called with CSQueryContinuationActionType, followed by -application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair with CSSearchQueryString as the key
// and the value is the string the application should use when performing its query.
// The application should declare that it supports the query continuation by adding the CoreSpotlightContinuation key to its Info.plist:
//
//    <key>CoreSpotlightContinuation</key>
//    <true/>
//
CORESPOTLIGHT_EXPORT NSString * const CSQueryContinuationActionType CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;
CORESPOTLIGHT_EXPORT NSString * const CSSearchQueryString CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;


CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSSearchableItem : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithUniqueIdentifier:(nullable NSString *)uniqueIdentifier //Can be null, one will be generated
                        domainIdentifier:(nullable NSString *)domainIdentifier
                            attributeSet:(CSSearchableItemAttributeSet *)attributeSet;

// Should be unique to your application group.
// REQUIRED since this is the way you will refer to the item to update the index / delete it from the index
// Starts with an UUID for ease of use, but you can replace it with an UID of your own before the item is first indexed if you wish.
@property (copy) NSString *uniqueIdentifier;

// An optional identifier that represents the "domain" or owner of this item.
// This might be an identifier for a mailbox in an account whose indexed data you may want to remove when the account is deleted.
// In that case the domainIdentifier should be of the form <account-id>.<mailbox-id> where <account-id> and <mailbox-id> should not contains periods.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id>.<mailbox-id> will delete all items with that domain identifier.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id> will delete all items with <account-id> and any <mailbox-id>.
@property (copy, nullable) NSString *domainIdentifier;

// Searchable items have an expiration date or time to live.  By default it's set to 1 month.
@property (copy, null_resettable) NSDate * expirationDate;

// Set of attributes containing meta data for the item
@property (strong) CSSearchableItemAttributeSet *attributeSet;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Places.h
//
//  CSSearchableItemAttributeSet_Places.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSPlaces)

//A publishable entry providing a synopsis of the contents of the item.
@property(nullable, copy) NSString *headline;

//Other editorial instructions concerning the use of the item, such as embargoes and warnings.
@property(nullable, copy) NSString *instructions;

//The location (e.g., street name) for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *thoroughfare;

//The sub-location (e.g., street number) for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *subThoroughfare;

//The postal code for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *postalCode;

//Identifies city of item origin according to guidelines established by the provider.
@property(nullable, copy) NSString *city;

//Identifies Province/State of origin according to guidelines established by the provider.
@property(nullable, copy) NSString *stateOrProvince;

//Provides full, publishable, name of the country/primary location where the
//intellectual property of the item was created,according to guidelines of the provider.
@property(nullable, copy) NSString *country;

// The fully formatted address of the item (obtained from MapKit)
@property(nullable, copy) NSString *fullyFormattedAddress;

//The altitude of the item in meters above sea level, expressed
//using the WGS84 datum.  Negative values lie below sea level.
@property(nullable, strong) NSNumber *altitude;

//The latitude of the item in degrees north of the equator, expressed
//using the WGS84 datum.  Negative values lie south of the equator.
@property(nullable, strong) NSNumber *latitude;

//The longitude of the item in degrees east of the prime meridian,
//expressed using the WGS84 datum.  Negative values lie west of the prime meridian.
@property(nullable, strong) NSNumber *longitude;

//The speed of the item, in kilometers per hour.
@property(nullable, strong) NSNumber *speed;

//The timestamp on the item.  This generally is used to indicate the time at
//which the event captured by the item took place.
@property(nullable, strong) NSDate *timestamp;

//The direction of the item's image, in degrees from true north.
@property(nullable, strong) NSNumber *imageDirection;

//The name of the location or point of interest associated with the item. The name may be user provided.
@property(nullable, copy) NSString *namedLocation;

//The direction of travel of the item, in degrees from true north.
@property(nullable, strong) NSNumber *GPSTrack;

@property(nullable, copy) NSString *GPSStatus;

@property(nullable, copy) NSString *GPSMeasureMode;

@property(nullable, strong) NSNumber *GPSDOP;

@property(nullable, copy) NSString *GPSMapDatum;

@property(nullable, strong) NSNumber *GPSDestLatitude;

@property(nullable, strong) NSNumber *GPSDestLongitude;

@property(nullable, strong) NSNumber *GPSDestBearing;

@property(nullable, strong) NSNumber *GPSDestDistance;

@property(nullable, copy) NSString *GPSProcessingMethod;

@property(nullable, copy) NSString *GPSAreaInformation;

@property(nullable, strong) NSDate *GPSDateStamp;

@property(nullable, strong) NSNumber *GPSDifferental;

@end
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet_Events.h
//
//  CSSearchableItemAttributeSet_Events.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSEvents)

//Date this item is due.
@property(nullable, strong) NSDate *dueDate;

//Date the item was completed
@property(nullable, strong) NSDate *completionDate;

//Start date of this item.
@property(nullable, strong) NSDate *startDate;

//End date for this item.
@property(nullable, strong) NSDate *endDate;

//Important dates associated with this item
@property(nullable, copy) NSArray<NSDate *> *importantDates;

//Whether this event covers complete days
@property(nullable, strong) NSNumber *allDay;

@end
// ==========  CoreSpotlight.framework/Headers/CSSearchQuery.h
//
//  CSSearchQuery.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

CORESPOTLIGHT_EXPORT NSString * const CSSearchQueryErrorDomain API_AVAILABLE(macos(10.12), ios(10.0)) CS_TVOS_UNAVAILABLE;

typedef NS_ENUM(NSInteger, CSSearchQueryErrorCode) {
    CSSearchQueryErrorCodeUnknown = -2000,
    CSSearchQueryErrorCodeIndexUnreachable = -2001,
    CSSearchQueryErrorCodeInvalidQuery = -2002,
    CSSearchQueryErrorCodeCancelled = -2003,
} API_AVAILABLE(macos(10.12), ios(10.0)) CS_TVOS_UNAVAILABLE;

@class CSSearchableItem;

API_AVAILABLE(macos(10.12), ios(10.0)) CS_TVOS_UNAVAILABLE
@interface CSSearchQuery : NSObject

- (instancetype)init NS_UNAVAILABLE;

// queryString: The query string (e.g., 'contentType == "public.email-message" && subject != "Re:*"')
// attributes: The attributes to be fetched for the searchable items
- (instancetype)initWithQueryString:(NSString *)queryString attributes:(NSArray<NSString *> * _Nullable)attributes;

@property (readonly, getter=isCancelled) BOOL cancelled;

// The query will update the count before each foundItemsHandler invocation to reflect
// the number of items found so far; if foundItemsHandler is nil then the count will
// contain the total number of found items when the query completes.
@property (readonly) NSUInteger foundItemCount;

// The foundItemsHandler will be invoked repeatedly with a new batch of searchable items.
// The query serializes all the foundItemsHandler invocations.
@property (nullable, copy) void (^foundItemsHandler)(NSArray<CSSearchableItem *> *items);

@property (nullable, copy) void (^completionHandler)(NSError * _Nullable error);

// An array of NSFileProtectionComplete, NSFileProtectionCompleteUnlessOpen,
// or NSFileProtectionCompleteUntilFirstUserAuthentication.
// By default the data protection will be read from the "com.apple.developer.default-data-protection"
// entitlement if any or NSFileProtectionCompleteUntilFirstUserAuthentication will be used otherwise.
@property (copy) NSArray<NSFileProtectionType> *protectionClasses;

- (void)start;
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreSpotlight.framework/Headers/CSSearchableItemAttributeSet.h
//
//  CSSearchableItemAttributeSet.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSPerson.h>

NS_ASSUME_NONNULL_BEGIN

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
// CSSearchableItemAttribute encapsulates a set of properties of an CSSearchableItem.
// CSSearchableItemAttribute set should only be mutated from one thread at a time. Concurrent access to properties has undefined behavior.
@interface CSSearchableItemAttributeSet : NSObject <NSCopying,NSSecureCoding>

//Creates an attribute set for the given content type.
- (instancetype)initWithItemContentType:(nonnull NSString *)itemContentType;

@end

//CSLocalizedString can be used in place of NSString to support localization
CS_TVOS_UNAVAILABLE
@interface CSLocalizedString : NSString

//Takes a dictionary of preferred codes to the localized string for that language
- (instancetype)initWithLocalizedStrings:(NSDictionary *)localizedStrings;

//Returns the localized string for the current language
- (NSString *)localizedString;

@end

//CSCustomAttributeKey allows you to specify a custom attribute as well as various other properties of that attribute.
CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSCustomAttributeKey : NSObject <NSCopying,NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

//Key names should be ASCII only, with no punctuation other than '_'.
//It is recommended keys be of the form "com_mycompany_myapp_keyname"
//Keys starting with 'kMD' are reserved.
- (nullable instancetype)initWithKeyName:(NSString *)keyName;
- (nullable instancetype)initWithKeyName:(NSString *)keyName
                              searchable:(BOOL)searchable
                     searchableByDefault:(BOOL)searchableByDefault
                                  unique:(BOOL)unique
                             multiValued:(BOOL)multiValued NS_DESIGNATED_INITIALIZER;

@property (readonly) NSString *keyName;

//Can this attribute be searched on? By default, YES
@property (readonly,getter=isSearchable) BOOL searchable;

//Is this property searchable by default? By default, NO
@property (readonly, getter=isSearchableByDefault) BOOL searchableByDefault;

//Should values be uniqued to save storage? By default, NO. Set this to YES when there is a small set of known values, or values are likely to be frequently repeating for other reasons.
@property (readonly, getter=isUnique) BOOL unique;

//Is this attribute expecting multiple values to be associated with it, i.e. are values arrays?  By default, NO
@property (readonly, getter=isMultiValued) BOOL multiValued;

@end

//Use these methods to set custom attributes on an attribute set
//Values must be common plist types (NSString,NSNumber,NSNull,NSData,NSDate) or CSPerson, or arrays (NSArray) of these types.
@interface CSSearchableItemAttributeSet (CSCustomAttributes)

- (void)setValue:(nullable id<NSSecureCoding>)value forCustomKey:(CSCustomAttributeKey *)key;
- (nullable id<NSSecureCoding>)valueForCustomKey:(CSCustomAttributeKey *)key;

@end

#if __OBJC2__

//Attributes to be indexed for a given NSUserActivity
@interface NSUserActivity (CSSearchableItemAttributeSet)

@property (nullable, copy) CSSearchableItemAttributeSet *contentAttributeSet CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;

@end

#endif

NS_ASSUME_NONNULL_END

#ifndef CoreSpotlightAPIVersion
#import <CoreSpotlight/CSSearchableItemAttributeSet_Categories.h>
#endif


// ==========  CoreSpotlight.framework/Headers/CSIndexExtensionRequestHandler.h
//
//  CSIndexExtensionRequestHandler.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableIndex.h>
#import <CoreSpotlight/CSBase.h>

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSIndexExtensionRequestHandler : NSObject <NSExtensionRequestHandling,CSSearchableIndexDelegate>

@end

