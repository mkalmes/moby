// ==========  NewsstandKit.framework/Headers/NKIssue.h
//
//  NKIssue.h
//  NewsstandKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NKAssetDownload;

/*!
 @constant   NKIssueDownloadCompletedNotification
 @abstract   Notification when an issue's assets have all been downloaded.
 */
extern __attribute__((visibility ("default"))) NSString * __nonnull const NKIssueDownloadCompletedNotification NS_AVAILABLE_IOS(5_0);

typedef NS_ENUM(NSInteger, NKIssueContentStatus) {
    NKIssueContentStatusNone,
    NKIssueContentStatusDownloading,
    NKIssueContentStatusAvailable,
} NS_ENUM_AVAILABLE_IOS(5_0);


/*!
 @class      NKIssue
 @abstract   Represents the Newsstand issue and its location on disk.
 @discussion All Newsstand issues have a publication date and a unique name. 
 You register assets for download through this class.
 All of the Newsstand content that represents this issue should be
 placed in the URL provided by contentURL.
 If there are any downloading assets associated with this issue,
 the state of the issue is "downloading". If there are no outstanding
 downloading assets and the contentURL is non-empty, the state
 is "content available".
 An issue is created by adding it to the library with
 -[NKLibrary addIssueWithName:date:].
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_IOS(5_0) @interface NKIssue : NSObject

/*!
 @property   downloadingAssets
 @abstract   An array of NKAssetDownload associated with this issue.
 */
@property (readonly, copy) NSArray<NKAssetDownload *> *downloadingAssets;

/*!
 @property   contentURL
 @abstract   All content that represents this issue should be placed in the
 URL provided.
 */
@property (readonly, copy) NSURL   *contentURL;

/*!
 @property   status
 @abstract   The availability of this issue's content.
 @discussion If there are asset downloads associated with this issue, the status
 is NKIssueContentStatusDownloading. If there are no downloading assets
 and the directory represented by contentURL is non-empty, the status
 is NKIssueContentStatusAvailable. Otherwise, no content is available
 at the destination and the status is NKIssueContentStatusNone.
 */
@property (readonly) NKIssueContentStatus    status;

/*!
 @property   name
 @abstract   The unique name given to this issue
 */
@property (readonly, copy) NSString    *name;

/*!
 @property   date
 @abstract   The date of this issue
 */
@property (readonly, copy) NSDate  *date;

/*!
 @method     addAssetWithRequest:
 @abstract   Add a downloading asset to this issue. Initiate the download for this
 asset with the downloadWithDelegate: method on the NKAssetDownload.
 */
- (NKAssetDownload *)addAssetWithRequest:(NSURLRequest *)request;

@end
NS_ASSUME_NONNULL_END
// ==========  NewsstandKit.framework/Headers/NKNSURLConnectionAdditions.h
//
//  NKNSURLConnectionAdditions.h
//  NewsstandKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NKAssetDownload;


/*!
 @category   NKAssetDownloadAdditions(NSURLConnection)
 @abstract   NKAssetDownload extensions to NSURLConnection.
 @discussion This category provides a convenient way to look up an
 NKAssetDownload that is related to a NSURLConnection.
 */
@interface NSURLConnection (NKAssetDownloadAdditions)

/*!
 @property   newsstandAssetDownload
 @abstract   A pointer to the asset download that this connection is associated with.
 */
@property (readonly, weak, nullable) NKAssetDownload *newsstandAssetDownload NS_AVAILABLE_IOS(5_0);

@end
// ==========  NewsstandKit.framework/Headers/NewsstandKit.h
//
//  NewsstandKit.h
//  NewsstandKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <NewsstandKit/NKLibrary.h>
#import <NewsstandKit/NKIssue.h>
#import <NewsstandKit/NKAssetDownload.h>

#import <NewsstandKit/NKNSURLConnectionAdditions.h>
// ==========  NewsstandKit.framework/Headers/NKAssetDownload.h
//
//  NKAssetDownload.h
//  NewsstandKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NKIssue;


/*!
 @class      NKAssetDownload
 @abstract   Represents a downloading asset for an issue.
 @discussion An NKIssue may have one or more assets that together form the structure
 of the Newsstand issue. You generate a downloading asset by constructing
 an NSURLRequest adding the request to the NKIssue using
 -[NKIssue addAssetWithRequest:]. Begin downloading the asset by calling
 -[NKAssetDownload downloadWithDelegate:].
 Upon download completion, you will need to put your uncompressed content
 in the URL specified by -[NKIssue contentURL].
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_IOS(5_0) @interface NKAssetDownload : NSObject

/*!
 @property   issue
 @abstract   A pointer to the issue that this asset is associated with.
 */
@property (readonly, weak, nullable) NKIssue *issue; // back-pointer to the issue this asset is associated with

/*!
 @property   identifier
 @abstract   A unique identifier representing the asset.
 */
@property (readonly, copy) NSString *identifier;

/*!
 @property   userInfo
 @abstract   Application specific information that is saved with the asset. Can be nil.
 @discussion You may add arbitrary key-value pairs to this dictionary. However, the keys
 and values must be valid property-list types; if any are not, an exception is raised.
 Using this property you can save download related information such as file name/paths,
 encoding mechanisms, custom identifiers, etc.  However, performance concerns dictate
 that you should make this content as minimal as possible.
 */
@property (copy, nullable) NSDictionary *userInfo;

/*!
 @property   URLRequest
 @abstract   The NSURLRequest of the download
 */
@property (readonly, copy) NSURLRequest *URLRequest;

/*!
 @method     downloadWithDelegate:
 @abstract   Begins downloading the asset with the specified delegate. Delegate
 may not be nil.
 */
- (NSURLConnection *)downloadWithDelegate:(id <NSURLConnectionDownloadDelegate>)delegate;

@end
NS_ASSUME_NONNULL_END
// ==========  NewsstandKit.framework/Headers/NKLibrary.h
//
//  NKLibrary.h
//  NewsstandKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NKIssue;
@class NKAssetDownload;


/*!
 @class      NKLibrary
 @abstract   Represents the library of Newsstand issues
 @discussion This is the library of Newsstand issues. Upon launch, one can
 get the issues in the Newsstand library and determine any outstanding
 downloading assets. To reconnect with any outstanding background
 download of content, you will be required to call 
 -[NKAssetDownload downloadWithDelegate:].
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_IOS(5_0) @interface NKLibrary : NSObject

/*!
 @property   issues
 @abstract   The Newsstand issues in the library
 */
@property (readonly, strong) NSArray<NKIssue *> *issues;

/*!
 @property   downloadingAssets
 @abstract   The assets that are currently being downloaded in this
 Newsstand library. The issue that this asset is associated with
 can be determined from the asset itself.
 */
@property (readonly, strong) NSArray<NKAssetDownload *> *downloadingAssets;

/*!
 @property   currentlyReadingIssue
 @abstract   The issue that is currently being read by the user. Clients should
 set this property to the currently read issue to prevent data
 from being purged when under disk pressure.
 */
@property (strong, nullable) NKIssue *currentlyReadingIssue;

/*!
 @method     sharedLibrary
 @abstract   The application's shared Newsstand Content Library
 */
+ (nullable NKLibrary *)sharedLibrary;

/*!
 @method     issueWithName:
 @abstract   Return the issue identified by the given name if it exists.
 */
- (nullable NKIssue *)issueWithName:(NSString *)name;

/*!
 @method     addIssueWithName:date:
 @abstract   Add a new issue to the Newsstand Content Library.
 */
- (NKIssue *)addIssueWithName:(NSString *)name date:(NSDate *)date;

/*!
 @method     removeIssue:
 @abstract   Remove the issue from the library
 */
- (void)removeIssue:(NKIssue *)issue;

@end
NS_ASSUME_NONNULL_END
