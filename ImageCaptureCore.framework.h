// ==========  ImageCaptureCore.framework/Headers/ICCameraFile.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraFile.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICCameraItem.h>

CF_ASSUME_NONNULL_BEGIN

//----------------------------------------------------------------------------------------------------------------- ICCameraFile
/*!
 @class ICCameraFile
 @abstract This class represents a file on an ICCameraDevice object.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraFile : ICCameraItem {
}

/*!
 @property width
 @abstract Width of an image or movie frame.
 */
@property (nonatomic, readonly) NSInteger width IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property height
 @abstract Height of an image or movie frame.
 */
@property (nonatomic, readonly) NSInteger height IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property originalFilename
 @abstract Original filename on disk
 */
@property (nonatomic, readonly, nullable) NSString* originalFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property createdFilename
 @abstract Created filename
 */
@property (nonatomic, readonly, nullable) NSString* createdFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileSize
 @abstract ￼Size of file in bytes.
 */
@property (nonatomic, readonly) off_t fileSize IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property orientation
 @abstract ￼Desired orientation of image to use when it is downloaded.
 @discussion This property is set to ICEXIFOrientation1 initially. If the format of this file supports EXIF orientation tag, then this property will be updated to match the value of that tag, when the thumbnail or metadata for this file is received.
 */
@property (nonatomic, readwrite) ICEXIFOrientationType orientation IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property duration
 @abstract ￼Duration of audio/video file in seconds.
 */
@property (nonatomic, readonly) double duration IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property highFramerate
 @abstract True if file is a slo-mo or high framerate video file, nil otherwise.
 */
@property (nonatomic, readonly) BOOL highFramerate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property timeLapse
 @abstract True if file is a time-lapse video file, nil otherwise.
 */
@property (nonatomic, readonly) BOOL timeLapse IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property firstPicked
 @abstract True if file is a firstPicked nil otherwise.
 */
@property (nonatomic, readonly) BOOL firstPicked IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property originatingAssetID
 @abstract originatingAssetID of file if present, nil if not a HEIF or HVEC.
 */
@property (nonatomic, readonly, nullable) NSString* originatingAssetID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property groupUUID
 @abstract groupUUID of file if present, nil if file has no groupUUID.
 */
@property (nonatomic, readonly, nullable) NSString* groupUUID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property gpsString
 @abstract GPS String in standard format.
 */
@property (nonatomic, readonly, nullable) NSString* gpsString IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property relatedUUID
 @abstract Internal related UUID for dbg/aae/etc.
 */
@property (nonatomic, readonly, nullable) NSString* relatedUUID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property burstUUID
 @abstract burstUUID of file if present, nil if not in a burst.
 */
@property (nonatomic, readonly, nullable) NSString* burstUUID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property burstFavorite
 @abstract True if burst favorite, ignored if not in a burst or not a burst favorite.
 */
@property (nonatomic, readonly) BOOL burstFavorite IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property burstPicked
 @abstract True if burst user picked, ignored if not in a burst or not a burst user picked.
 */
@property (nonatomic, readonly) BOOL burstPicked IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property sidecarFiles
 @abstract This property is NULL if there are no sidecar files associated with this file. Otherwise it is an array of
 ICCameraFile instances of sidecar files associated with this file. An example of a sidecar file is a file with the same base
 name as this file and having an extension XMP.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* sidecarFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property pairedRawImage
 @abstract A single item subset of the sidecarFiles array, which contains the logical RAW compliment of a JPG or other
 format image.
 */
@property (nonatomic, readonly, nullable) ICCameraFile* pairedRawImage IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileCreationDate
 @abstract Properties will either represent the actual file creation
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* fileCreationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileModificationDate
 @abstract Properties will either represent the actual file modification
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* fileModificationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property exifCreationDate
 @abstract Properties will either represent the exif creation
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* exifCreationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property exifModificationDate
 @abstract Properties will either represent the exif modification
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* exifModificationDate IC_AVAILABLE(macos(10.4), ios(13.0));

#pragma mark - Block API

/*!
 @method requestThumbnailDataWithOptions:completion
 @abstract ￼Perform a thumbnail request and execute the block callback in place of the delegate.
 @param options: Options dictionary
 
 - 'kCGImageSourceThumbnailMaxPixelSize' - Request a width different from the embedded EXIF thumbnail
 
 @param completion: Completion block called with an NSData* object representing the JPG, and an NSError* for status.
 */
- (void)requestThumbnailDataWithOptions:(NSDictionary<ICCameraItemThumbnailOption, id>*)options
                             completion:(void (^)(NSData* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestMetadataDictionaryWithOptions:completion
 @abstract ￼Perform a metadata request and execute the block callback in place of the delegate.
 @param options: Options dictionary
 @param completion: Completion block called with an NSDictionary* object containing the metadata, and an NSError* for status.
 */
- (void)requestMetadataDictionaryWithOptions:(NSDictionary<ICCameraItemMetadataOption, id>*)options
                                  completion:(void (^)(NSDictionary* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestDownloadWithOptions:progressDelegate:completion
 @abstract ￼Perform a download request and execute the block callback in place of the delegate.
 @param options: Dictionary Keys:
 
 - `ICDownloadsDirectoryURL`
 - `ICSaveAsFilename`
 - `ICOverwriteExistingFile`
 - `ICDeleteAfterDownload`
 - `ICAdjustCreationDate`
 
 @param completion: Completion block to executed after request has returned,
 @param filename: The name of the file as written to disk.
 @param error:
 */
- (NSProgress* _Nullable)requestDownloadWithOptions:(NSDictionary<ICDownloadOption, id>*)options
                                         completion:(void (^)(NSString* _Nullable filename, NSError* _Nullable error))completion
    IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestReadDataAtOffset:length:completion
 @abstract This method asynchronously reads data of a specified length from a specified offset.
 @param offset: The offset into the file to start reading from
 @param length: The length of data to be read.
 @param completion: Completion block called with an NSData* object representing the data, and an NSError* for status.
 */
- (void)requestReadDataAtOffset:(off_t)offset
                         length:(off_t)length
                     completion:(void (^)(NSData* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(10.15))IC_UNAVAILABLE(ios);

@end

CF_ASSUME_NONNULL_END
// ==========  ImageCaptureCore.framework/Headers/ICCameraDevice.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>

#import <ImageCaptureCore/ICCameraItem.h>
#import <ImageCaptureCore/ICDevice.h>
#import <CoreGraphics/CoreGraphics.h>

@class ICCameraFile;

CF_ASSUME_NONNULL_BEGIN

@protocol ICCameraDeviceDownloadDelegate;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a camera

/*!
  @const      ICCameraDeviceCanTakePicture
  @abstract   ICCameraDeviceCanTakePicture
  @discussion Indicates that the camera can capture a picture while it is connected, if the client sends a 'requestTakePicture' message to it.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanTakePicture IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera
  @abstract   ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera
  @discussion Indicates that the camera can capture a picture while it is connected, if the user presses the shutter release on the camera.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanDeleteOneFile
  @abstract   ICCameraDeviceCanDeleteOneFile
  @discussion Indicates that the camera can delete a file at a time while it is connected.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanDeleteOneFile IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanDeleteAllFiles
  @abstract   ICCameraDeviceCanDeleteAllFiles
  @discussion Indicates that the camera can delete all files in a single operation while it is connected.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanDeleteAllFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanSyncClock
  @abstract   ICCameraDeviceCanSyncClock
  @discussion Indicates that the camera can synchronize its date and time with that of the host computer.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanSyncClock IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanReceiveFile
  @abstract   ICCameraDeviceCanReceiveFile
  @discussion Indicates that the host can upload files to the camera.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanReceiveFile IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanAcceptPTPCommands
  @abstract   ICCameraDeviceCanAcceptPTPCommands
  @discussion Indicates that the camera can accept PTP commands.
*/
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanAcceptPTPCommands IC_AVAILABLE(macos(10.4), ios(13.0));

typedef NSString* ICUploadOption NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

typedef NSString* ICDeleteResult NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteSuccessful
  @abstract   ICDeleteSuccessful
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
*/
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteSuccessful IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteCanceled
  @abstract   ICDeleteCanceled
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
*/
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteCanceled IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteFailed
  @abstract   ICDeleteFailed
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
*/
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteFailed IC_AVAILABLE(macos(10.4), ios(13.0));

typedef NSString* ICDeleteError NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteErrorReadOnly
  @abstract   ICDeleteErrorReadOnly
  @discussion The value for this key should be an ICCameraItem*
*/
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorReadOnly IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteErrorFileMissing
  @abstract   ICDeleteErrorFileMissing
  @discussion The value for this key should be an ICCameraItem*
*/
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorFileMissing IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteErrorDeviceMissing
  @abstract   ICDeleteErrorDeviceMissing
  @discussion The value for this key should be an ICCameraItem*
*/
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorDeviceMissing IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteErrorDeviceMissing
  @abstract   ICDeleteErrorDeviceMissing
  @discussion The value for this key should be an ICCameraItem*
*/
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorCanceled IC_AVAILABLE(macos(10.4), ios(13.0));

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@protocol ICDeviceDelegate;

//--------------------------------------------------------------------------------------------------------------- ICCameraDevice
/*!
  @class ICCameraDevice
  @abstract ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraDevice : ICDevice

/*!
  @property contentCatalogPercentCompleted
  @abstract ￼Indicates the percentage of content cataloging completed on the device. Its value ranges from 0 to 100.
*/
@property (nonatomic, readonly) NSUInteger contentCatalogPercentCompleted IC_AVAILABLE(macos(10.14), ios(13.0));

/*!
  @property contents
  @abstract ￼Contents of the camera. The structure of the elements in this array will reflect the folder structure of the storage reported by the camera. Each item in this array will correspond to a storage on the camera.
*/
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* contents IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property mediaFiles
  @abstract ￼The property mediaFiles represents all image, movie and audio files on the camera. These files are returned as a single array without regard to the folder hierarchy used to store these files on the camera.
*/
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* mediaFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property ejectable
 @abstract ￼Indicates whether the device can be 'soft' removed or disconnected.
 */
@property (nonatomic, readonly, getter=isEjectable) BOOL ejectable IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property locked
 @abstract ￼Indicates whether the device is locked.  A locked device does not allow for deletion of any asset.
 */
@property (nonatomic, readonly, getter=isLocked) BOOL locked IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property accessRestrictedAppleDevice
  @abstract Set to YES if the device is made by Apple and is pass-coded locked and connected to an untrusted host.
*/
@property (nonatomic, readonly, getter=isAccessRestrictedAppleDevice) BOOL accessRestrictedAppleDevice IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property iCloudPhotosEnabled
  @abstract Set to YES if the device is made by Apple and is pass-coded locked and connected to an untrusted host.
*/
@property (nonatomic, readonly) BOOL iCloudPhotosEnabled IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property mountPoint
  @abstract Filesystem mount point for a device with transportType of ICTransportTypeMassStorage. This will be NULL for all other devices.
*/
@property (nonatomic, readonly, nullable) NSString* mountPoint IC_AVAILABLE(macos(10.4));

/*!
  @property tetheredCaptureEnabled
  @abstract This property is set to YES when tethered capture is enabled on the device.
  @discussion Use 'requestEnableTethering' and 'requestDisableTethering' to enable or disable tethered capture on the device.
*/
@property (nonatomic, readonly) BOOL tetheredCaptureEnabled IC_AVAILABLE(macos(10.4));

/*!
  @method filesOfType:
  @abstract This method returns an array of files on the camera of type fileType.
  @discussion The fileType string is one of the following Uniform Type Identifier strings: kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
*/
- (nullable NSArray<NSString*>*)filesOfType:(NSString*)fileUTType IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method requestSyncClock
  @abstract Synchronize camera's clock with the computer's clock. You should send this request only if the camera has the 'ICCameraDeviceCanSyncClock' capability.
*/
- (void)requestSyncClock;

/*!
  @method requestDeleteFiles
  @abstract Deletes files.
*/
- (void)requestDeleteFiles:(NSArray<ICCameraItem*>*)files IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method requestDeleteFiles:deleteFailed:completion
  @abstract Allows for deletion of an array of ICCameraItem objects, with the added ability to catch delete failures using the
  'deleteFailed' block, and a completion block that will return the overall state of the request.
 
 The deleteFailed block will return:
       - NSDictionary<ICDeleteError, ICCameraItem*>*
 
 The completion block will return:
   — error:
       - nil if successful
       - NSError* with an code set to ICReturnDeleteFilesFailed if any file failed.
 
   - result: NSDictionary<ICDeleteResult, NSArray<ICCameraItem*>*>* result
       - ICDeleteSuccessful: NSArray<ICCameraItem*>* success
       - ICDeleteFailed: NSArray<ICCameraItem*>* failed
 */
- (NSProgress*)requestDeleteFiles:(NSArray<ICCameraItem*>*)files
              deleteFailed:(void (^)(NSDictionary<ICDeleteError, ICCameraItem*>*))deleteFailed
                completion:(void (^)(NSDictionary<ICDeleteResult, NSArray<ICCameraItem*>*>* result, NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @method requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:
  @abstract Download a file from the camera. Please refer to the top of this header for information about the options.
 @discussion The downloadDelegate passed must not be nil. When this request is completed, the didDownloadSelector of the downloadDelegate object is called.The didDownloadSelector should have the same signature as: - (void)didDownloadFile:(ICCameraFile*)file error:(NSError*)error options:(NSDictionary*)options contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestDownloadFile:(ICCameraFile*)file
                    options:(NSDictionary<ICDownloadOption, id>*)options
           downloadDelegate:(id<ICCameraDeviceDownloadDelegate>)downloadDelegate
        didDownloadSelector:(SEL)selector
                contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cancelDownload
  @abstract Cancels the current download operation.
*/
- (void)cancelDownload IC_AVAILABLE(macos(10.4));

/*!
 @property timeOffset
 @abstract Indicates the time offset, in seconds, between the camera's clock and the computer's clock￼. This value is positive if the camera's clock is ahead of the computer's clock. This property should be ignored if the camera's capabilities property does not contain ICCameraDeviceCanSyncClock.
 */
@property (readonly) NSTimeInterval timeOffset IC_AVAILABLE(macos(10.4));

/*!
 @property batteryLevelAvailable
 @abstract Indicates if the device has reported battery charge level￼.
 */
@property (readonly) BOOL batteryLevelAvailable IC_AVAILABLE(macos(10.4));

/*!
 @property batteryLevel
 @abstract ￼Indicates the battery charge level. Its value ranges from 0 to 100.
 */
@property (readonly) NSUInteger batteryLevel IC_AVAILABLE(macos(10.4));

/*!
 @method cancelDelete
 @abstract Cancels the current delete operation started by sending a 'requestDeleteFiles:'.
 */
- (void)cancelDelete IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestEnableTethering
 @abstract Send this message to enable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability.
 */
- (void)requestEnableTethering IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestDisableTethering
 @abstract Send this message to disable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability and if your process has already sent a 'requestEnableTethering' to it.
 */
- (void)requestDisableTethering IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestTakePicture
 @abstract Capture a new image using the camera, the camera capabilities include 'ICCameraDeviceCanTakePicture'.
 @discussion You MUST send 'requestEnableTethering' message to the camera before sending 'requestTakePicture' message.
 */
- (void)requestTakePicture IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestUploadFile:options:uploadDelegate:didUploadSelector:contextInfo:
  @abstract Upload a file at fileURL to the camera. The options dictionary is not used in this version.
  @discussion The uploadDelegate passed must not be nil. When this request is completed, the didUploadSelector of the uploadDelegate object is called. The didUploadSelector should have the same signature as: - (void)didUploadFile:(NSURL*)fileURL error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestUploadFile:(NSURL*)fileURL
                  options:(NSDictionary<ICUploadOption, id>*)options
           uploadDelegate:(id)uploadDelegate
        didUploadSelector:(SEL)selector
              contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestReadDataFromFile:atOffset:length:readDelegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously reads data of a specified length from a specified offset.
  @discussion The readDelegate passed must not be nil. When this request is completed, the didReadDataSelector of the readDelegate object is called. The didReadDataSelector should have the same signature as: - (void)didReadData:(NSData*)data fromFile:(ICCameraFile*)file error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestReadDataFromFile:(ICCameraFile*)file
                       atOffset:(off_t)offset
                         length:(off_t)length
                   readDelegate:(id)readDelegate
            didReadDataSelector:(SEL)selector
                    contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:
  @abstract This method asynchronously sends a PTP command to a camera.
  @discussion This should be sent only if the 'capabilities' property contains 'ICCameraDeviceCanAcceptPTPCommands'. All PTP cameras have this capability. The response to this command will be delivered using didSendCommandSelector of sendCommandDelegate. The didSendCommandSelector should have the same signature as: - (void)didSendPTPCommand:(NSData*)command inData:(NSData*)data response:(NSData*)response error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestSendPTPCommand:(NSData*)command
                      outData:(NSData*)data
          sendCommandDelegate:(id)sendCommandDelegate
       didSendCommandSelector:(SEL)selector
                  contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------- ICCameraDeviceDelegate
/*!
  @protocol ICCameraDeviceDelegate  <ICDeviceDelegate>
  @abstract A delegate of ICCameraDevice must conform to ICCameraDeviceDelegate protocol.
  @discussion The ICCameraDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/
@protocol ICCameraDeviceDelegate <ICDeviceDelegate>

/*!
  @method cameraDevice:didAddItems:
  @abstract This message is sent when objects are added to the device.
  @discussion The objects in items are instances ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didAddItems:(NSArray<ICCameraItem*>*)items IC_AVAILABLE(macos(10.4), ios(13.0));
/*!
  @method cameraDevice:didRemoveItems:
  @abstract This message is sent when objects are removed from the device.
  @discussion The objects in items are instances ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didRemoveItems:(NSArray<ICCameraItem*>*)items IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didReceiveThumbnail:forItem:error:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveThumbnail:(nullable CGImageRef)thumbnail
                forItem:(ICCameraItem*)item
                  error:(nullable NSError*)error IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method cameraDevice:didReceiveMetadata:forItem:error:
 @abstract This message is sent when the metadata requested for an item on a device is available.
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveMetadata:(nullable NSDictionary*)metadata
               forItem:(ICCameraItem*)item
                 error:(nullable NSError*)error IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method cameraDevice:didRenameItems:
 @abstract This message is sent when an object or objects are renamed on the device.
 @discussion The objects may be instances of ICCameraFolder or ICCameraFile class.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didRenameItems:(NSArray<ICCameraItem*>*)items IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDeviceDidChangeCapability:
  @abstract This message is sent when a capability of a device changes.
  @discussion Detailed capabilitiy descriptions are provided at the top of this header file.
*/
- (void)cameraDeviceDidChangeCapability:(ICCameraDevice*)camera IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didReceivePTPEvent:
  @abstract This message is sent to the delegate to convey a PTP event.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceivePTPEvent:(NSData*)eventData IC_AVAILABLE(macos(10.4));

/*!
  @method deviceDidBecomeReadyWithCompleteContentCatalog:
  @abstract This message is sent when the camera device is done enumerating its content and is ready to receive requests.
  @discussion A session must be opened on the device in order to enumerate its content and make it ready to receive requests.
*/
- (void)deviceDidBecomeReadyWithCompleteContentCatalog:(ICCameraDevice*)device IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @method deviceDidRemoveAccessRestriction:
 @abstract This message is sent when an Apple device has been unlocked, paired to the host, and media is available.
 */
- (void)cameraDeviceDidRemoveAccessRestriction:(ICDevice*)device;

/*!
 @method deviceDidEnableAccessRestriction:
 @abstract This message is sent when an Apple device has been locked, and media is unavailable until the restriction
 has been removed.
 */
- (void)cameraDeviceDidEnableAccessRestriction:(ICDevice*)device;

@optional

/*!
 @method cameraDevice:shouldGetThumbnailOfItem:
 @abstract This message is sent when the camera device is about to execute queued requests for the thumbnail of a specific item.
 If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
 a request down to the camera device, speeding up the exection queue.
 */
- (BOOL)cameraDevice:(ICCameraDevice*)cameraDevice shouldGetThumbnailOfItem:(ICCameraItem*)item IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @abstract This message is sent when the camera device is about to execute queued requests for the metadata of a specific item.
 If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
 a request down to the camera device, speeding up the execution queue.
 */
- (BOOL)cameraDevice:(ICCameraDevice*)cameraDevice shouldGetMetadataOfItem:(ICCameraItem*)item IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didCompleteDeleteFilesWithError:
  @abstract This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
  @discusson This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didCompleteDeleteFilesWithError:(nullable NSError*)error IC_AVAILABLE(macos(10.4), ios(13.0));

#pragma mark - Deprecated

/*!
  @method cameraDevice:didAddItem:
  @abstract This message is sent when an object is added to the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera
          didAddItem:(ICCameraItem*)item IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didAddItems:", macos(10.4, 10.15));

/*!
 @method cameraDevice:didRemoveItem:
 @abstract This message is sent when an object is removed from the device.
 @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
 */
- (void)cameraDevice:(ICCameraDevice*)camera
       didRemoveItem:(ICCameraItem*)item IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didRemoveItems:", macos(10.4, 10.15));

/*!
  @method cameraDevice:didReceiveThumbnailForItem:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveThumbnailForItem:(ICCameraItem*)item
    IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didReceiveThumbnail:forItem:error:", macos(10.4, 10.15));

/*!
  @method cameraDevice:didReceiveMetadataForItem:
  @abstract This message is sent when the metadata requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveMetadataForItem:(ICCameraItem*)item
    IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didReceiveMetadata:forItem:error:", macos(10.4, 10.15));

@end

/*!
  @protocol ICCameraDeviceDownloadDelegate <NSObject>
  @abstract The object passed in as 'downloadDelegate' in the 'requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:' message must conform to ICCameraDeviceDownloadDelegate protocol.
*/
@protocol ICCameraDeviceDownloadDelegate <NSObject>

@optional

/*!
  @method didDownloadFile:error:options:contextInfo:
  @abstract This message is sent to the delegate when the requested download operation is complete.
*/
- (void)didDownloadFile:(ICCameraFile*)file
                  error:(nullable NSError*)error
                options:(NSDictionary<NSString*, id>*)options
            contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4));

/*!
  @method didReceiveDownloadProgressForFile:downloadedBytes:maxBytes:
  @abstract This message is sent to the delegate to provide status of the download operation.
*/
- (void)didReceiveDownloadProgressForFile:(ICCameraFile*)file downloadedBytes:(off_t)downloadedBytes maxBytes:(off_t)maxBytes IC_AVAILABLE(macos(10.4), ios(13.0));

@end

NS_ASSUME_NONNULL_END

// ==========  ImageCaptureCore.framework/Headers/ICCameraItem.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraItem.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <ImageCaptureCore/ImageCaptureConstants.h>
#import <ImageCaptureCore/ICDevice.h>
#import <CoreGraphics/CoreGraphics.h>

@class ICCameraDevice;
@class ICCameraFolder;
@class ICCameraFile;

CF_ASSUME_NONNULL_BEGIN

//----------------------------------------------------------------------------------------------------------------- ICCameraItem
/*!
  @class ICCameraItem
  @abstract ICCameraItem is an abstract class that represents an item in an ICCameraDevice object. ICCameraDevice object creates
  instances of two concrete subclasses of ICCameraItem: ICCameraFolder and ICCameraFile.
*/

@protocol ICCameraDeviceDownloadDelegate;

typedef NSString* ICCameraItemMetadataOption NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));
typedef NSString* ICCameraItemThumbnailOption NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

IMAGECAPTURE_EXTERN ICCameraItemThumbnailOption const ICImageSourceThumbnailMaxPixelSize IC_AVAILABLE(macos(10.15), ios(13.0));
IMAGECAPTURE_EXTERN ICCameraItemThumbnailOption const ICImageSourceShouldCache IC_AVAILABLE(macos(10.15), ios(13.0));

typedef NSString* ICDownloadOption NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

//------------------------------------------------------------------------------------------------------------------------------
// Allowed keys in the options dictionary used when downloading a file from the camera

/*!
  @const      ICDownloadsDirectoryURL
  @abstract   ICDownloadsDirectoryURL
  @discussion The value for this key should be an NSURL object referencing a writable directory. The downloaded files will be saved in that directory.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICDownloadsDirectoryURL IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICSaveAsFilename
  @abstract   ICSaveAsFilename
  @discussion The value for this key should be an NSString object containing the name to be used for the downloaded file.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICSaveAsFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICSavedFilename
  @abstract   ICSavedFilename
  @discussion The value for this key will be an NSString object containing the actual name of the saved file. The options dictionary returned in didDownloadFile:error:options:contextInfo: will have this key.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICSavedFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICSavedAncillaryFiles
  @abstract   ICSavedAncillaryFiles
  @discussion The value for this key will be an NSArray object containing names of files associated with the primary file that is downloaded. The options dictionary returned in didDownloadFile:error:options:contextInfo: may have this key.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICSavedAncillaryFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICOverwrite
  @abstract   ICOverwrite
  @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the downloaded file will overwrite an existing file with the same name and extension.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICOverwrite IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDeleteAfterSuccessfulDownload
  @abstract   ICDeleteAfterSuccessfulDownload
  @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the file will be deleted from the device after it is succcessfully downloaded.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICDeleteAfterSuccessfulDownload IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICDownloadSidecarFiles
  @abstract   ICDownloadSidecarFiles
  @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, all sidecar files will be downloaded along with the media file.
*/
IMAGECAPTURE_EXTERN ICDownloadOption const ICDownloadSidecarFiles IC_AVAILABLE(macos(10.4), ios(13.0));

IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraItem : NSObject
{
}

/*!
  @property device
  @abstract ￼Parent device of this item.
*/
@property (nonatomic, readonly, nullable) ICCameraDevice* device IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property parentFolder
  @abstract ￼Parent folder of this folder. The root folder's parentFolder is nil.
*/
@property (nonatomic, readonly, nullable) ICCameraFolder* parentFolder IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @property name
  @abstract ￼Name of this item.
*/
@property (nonatomic, readonly, nullable) NSString* name IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @property UTI
  @abstract ￼Item UTI. This is an Uniform Type Identifier string. It is one of: kUTTypeFolder, kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
*/
@property (nonatomic, readonly, nullable) NSString* UTI IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @property fileSystemPath
  @abstract ￼The file system path of the item for items on a device with transportType of ICTransportTypeMassStorage.
*/
@property (nonatomic, readonly, nullable) NSString* fileSystemPath IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @property locked
  @abstract ￼Indicates the protection state of this item. It is locked if the storage card in the camera is locked.
*/
@property (nonatomic, readonly, getter=isLocked) BOOL locked IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @property raw
  @abstract ￼Indicates if the file is a raw image file.
*/
@property (nonatomic, readonly, getter=isRaw) BOOL raw IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property inTemporaryStore
  @abstract ￼Indicates if this folder is in a temporary store. A temporary store may be used by the device when images are
   captures on the device when it is tethered to the computer.
*/
@property (nonatomic, readonly, getter=isInTemporaryStore) BOOL inTemporaryStore IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property creationDate
  @abstract ￼Creation date of this file. This information is usually the same as the EXIF creation date.
*/
@property (nonatomic, readonly, nullable) NSDate* creationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property modificationDate
  @abstract ￼Modification date of this file. This information is usually the same as the EXIF modification date.
*/
@property (nonatomic, readonly, nullable) NSDate* modificationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property thumbnail
 @abstract ￼Thumbnail for the item. The value of this property is NULL unless a 'requestThumbnail' message is sent to this object.
*/
@property (nonatomic, readonly, nullable) CGImageRef thumbnail IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property metadata
 @abstract ￼Metadata for the item. The value of this property is NULL unless a 'requestMetadata' message is sent to this object.
*/
@property (nonatomic, readonly, nullable) NSDictionary* metadata IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property userData
  @abstract ￼A mutable dictionary to store arbitrary key-value pairs associated with a camera item object. This can be used by
   view objects that bind to this object to store "house-keeping" information.
*/
@property (nonatomic, readonly, nullable) NSMutableDictionary* userData IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property ptpObjectHandle
  @abstract PTP object handle value if the item is on a camera that uses PTP protocol. The value of this property is set to 0
   if the camera does not use PTP protocol.
*/
@property (nonatomic, readonly) unsigned int ptpObjectHandle IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property addedAfterContentCatalogCompleted
 @abstract This property is set if the file is captured on the device after the device's content is fully enumerated. This does
 not apply to files added as a result of adding a new store to the device.
 */
@property (nonatomic, readonly, getter=wasAddedAfterContentCatalogCompleted) BOOL addedAfterContentCatalogCompleted IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method requestThumbnail
  @abstract This method requests thumbnail for the item. If one is not readily available, accessing this property will send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method "cameraDevice:didReceiveThumbnail:forItem:error:", if this method is implemented by the delegate.
*/
- (void)requestThumbnail IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestMetadata
 @abstract ￼Metadata for the file if one is readily available. If one is not readily available, accessing this property will send a message to the device requesting metadata for the file. The delegate of the device will be notified via method "cameraDevice:didReceiveMetadata:forItem:error:", if this method is implemented by the delegate.
*/
- (void)requestMetadata  IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method flushThumbnailCache
 @abstract ￼Deletes cached thumbnail for the item.
*/
- (void)flushThumbnailCache  IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method flushMetadataCache
 @abstract ￼Deletes cached metadata for the item.
*/
- (void)flushMetadataCache IC_AVAILABLE(macos(10.15), ios(13.0));

#pragma mark - Deprecated

/*!
 @property thumbnailIfAvailable
 @abstract ￼Thumbnail for the item if one is readily available. If one is not readily available, accessing this property will
 send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method
 "cameraDevice:didReceiveThumbnailForItem:", if this method is implemented on by the delegate.
*/
@property (nullable, readonly) CGImageRef thumbnailIfAvailable IC_DEPRECATED_WITH_REPLACEMENT(
    "Use requestThumbnail, or requestThumbnailWithOptions:completion", macos(10.4,10.15));

/*!
 @property largeThumbnailIfAvailable
 @abstract Large thumbnail for the item if one is readily available. If one is not readily available, accessing this property
 will send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method
 "cameraDevice:didReceiveThumbnailForItem:", if this method is implemented on by the delegate.
 */
@property (nullable, readonly) CGImageRef largeThumbnailIfAvailable IC_DEPRECATED_WITH_REPLACEMENT(
    "Use requestThumbnail, or requestThumbnailWithOptions:completion", macos(10.4, 10.15));

/*!
 @property metadataIfAvailable
 @abstract ￼Metadata for the file if one is readily available. If one is not readily available, accessing this property will
 send a message to the device requesting metadata for the file. The delegate of the device will be notified via method
 "cameraDevice:didReceiveMetadataForItem:", if this method is implemented on by the delegate.
*/
@property (nullable, readonly) NSDictionary<NSString*, id>* metadataIfAvailable IC_DEPRECATED_WITH_REPLACEMENT(
    "Use requestMetadata for the delegate based API, or requestMetadataDictionaryWithOptions:completion", macos(10.4, 10.15));

@end

CF_ASSUME_NONNULL_END
// ==========  ImageCaptureCore.framework/Headers/ImageCaptureConstants.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ImageCaptureConstants.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <Foundation/Foundation.h>


#define   ICRunLoopMode   @"com.apple.ImageCaptureCore"

//------------------------------------------------------------------------------------------------------------------------------
/*!
  @ICEXIFOrientationType
  @abstract Type representing EXIF Orientation tag value
  @discussion The meaning of this value is defined by the EXIF specification. Here is what the letter F would look like if it were tagged correctly and displayed by a program that ignores the orientation tag (thus showing the stored image):

               1             2             3             4

            8888888       8888888            88       88
            88                 88            88       88
            8888             8888          8888       8888
            88                 88            88       88
            88                 88       8888888       8888888

               5             6             7             8

            8888888888    88                    88    8888888888
            88  88        88  88            88  88        88  88
            88            8888888888    8888888888            88

*/

extern NSErrorDomain const ICErrorDomain API_AVAILABLE(macos(10.15), ios(13.0));

typedef NS_ENUM(NSUInteger, ICEXIFOrientationType)
{
    ICEXIFOrientation1  = 1,    // Normal
    ICEXIFOrientation2  = 2,    // Flipped horizontally
    ICEXIFOrientation3  = 3,    // Rotated 180°
    ICEXIFOrientation4  = 4,    // Flipped vertically
    ICEXIFOrientation5  = 5,    // Rotated 90° CCW and flipped vertically
    ICEXIFOrientation6  = 6,    // Rotated 90° CCW
    ICEXIFOrientation7  = 7,    // Rotated 90° CW and flipped vertically
    ICEXIFOrientation8  = 8     // Rotated 90° CW
};

//------------------------------------------------------------------------------------------------------------------------------

typedef NS_ENUM(NSInteger)
{
    ICReturnCodeThumbnailOffset           = -21000,
    ICReturnCodeMetadataOffset            = -21050,
    ICReturnCodeDownloadOffset            = -21100,
    ICReturnCodeDeleteOffset              = -21150,
    ICReturnCodeExFATOffset               = -21200,
    ICReturnCodePTPOffset                 = -21250,
    ICReturnCodeSystemOffset              = -21300,
    ICReturnCodeDeviceOffset              = -21350,
    ICReturnCodeDeviceConnection          = -21400,
} ICReturnCodeOffset;


typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnThumbnailErrorCode) {

    /* Item does not have thumbnail available. */
    ICReturnThumbnailNotAvailable               = ICReturnCodeThumbnailOffset,
    /* Item thumbnail request is being serviced. */
    ICReturnThumbnailAlreadyFetching            = ICReturnCodeThumbnailOffset -1,
    /* Item thumbnail request has been canceled. */
    ICReturnThumbnailCanceled                   = ICReturnCodeThumbnailOffset -2,
    /* Item thumbnail request completed with invalid result. */
    ICReturnThumbnailInvalid                    = ICReturnCodeThumbnailOffset -3,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnMetadataErrorCode) {

    /* Item does not have metadata available. */
    ICReturnMetadataNotAvailable                = ICReturnCodeMetadataOffset,
    /* Item metadata request is being serviced. */
    ICReturnMetadataAlreadyFetching             = ICReturnCodeMetadataOffset -1,
    /* Item metadata request has been canceled. */
    ICReturnMetadataCanceled                    = ICReturnCodeMetadataOffset -2,
    /* Item metadata request completed with invalid result. */
    ICReturnMetadataInvalid                     = ICReturnCodeMetadataOffset -3,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnConnectionErrorCode) {

    /* Device driver exited without request. */
    ICReturnConnectionDriverExited                  = ICReturnCodeDeviceOffset,
    /* Device closed session without request. */
    ICReturnConnectionClosedSessionSuddenly         = ICReturnCodeDeviceOffset -1,
    /* Device ejected without request. */
    ICReturnConnectionEjectedSuddenly               = ICReturnCodeDeviceOffset -2,
    /* Device reports session is already open. */
    ICReturnConnectionSessionAlreadyOpen            = ICReturnCodeDeviceOffset -3,
    /* Device reports eject has failed. */
    ICReturnConnectionEjectFailed                   = ICReturnCodeDeviceOffset -4,
    /* Failed to open a connection to the device. */
    ICReturnConnectionFailedToOpen                  = ICReturnCodeDeviceConnection,
    /* Failed to open the device. */
    ICReturnConnectionFailedToOpenDevice            = ICReturnCodeDeviceConnection -1,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICLegacyReturnCode)
{
    /* An error occurred in communication between different components of Image Capture framework. */
    ICLegacyReturnCodeCommunicationErr                = -9900,
    /* The specified device is not found. */
    ICLegacyReturnCodeDeviceNotFoundErr               = -9901,
    /* The specified device is not open. */
    ICLegacyReturnCodeDeviceNotOpenErr                = -9902,
    /* Encountered a corrupt file */
    ICLegacyReturnCodeFileCorruptedErr                = -9903,
    /* There is Pending I/O */
    ICLegacyReturnCodeIOPendingErr                    = -9904,
    /* The specified object is invalid */
    ICLegacyReturnCodeInvalidObjectErr                = -9905,
    /* The specified property is invalid */
    ICLegacyReturnCodeInvalidPropertyErr              = -9906,
    /* The index of the object specified is outside of the available object indexes */
    ICLegacyReturnCodeIndexOutOfRangeErr              = -9907,
    /* Specifi property type not found on object */
    ICLegacyReturnCodePropertyTypeNotFoundErr         = -9908,
    /* Unable to yield device to a secondary process */
    ICLegacyReturnCodeCannotYieldDevice               = -9909,
    /* Device does not support data type */
    ICLegacyReturnCodeDataTypeNotFoundErr             = -9910,
    /* Unable to allocate memory */
    ICLegacyReturnCodeDeviceMemoryAllocationErr       = -9911,
    /* Generic internal error */
    ICLegacyReturnCodeDeviceInternalErr               = -9912,
    /* Generic parameter invalid error */
    ICLegacyReturnCodeDeviceInvalidParamErr           = -9913,
    /* Device already opened */
    ICLegacyReturnCodeDeviceAlreadyOpenErr            = -9914,
    /* Device USB locationID is not valid */
    ICLegacyReturnCodeDeviceLocationIDNotFoundErr     = -9915,
    /* Device FireWire GUID is not valid */
    ICLegacyReturnCodeDeviceGUIDNotFoundErr           = -9916,
    /* Device IOService point is not valid */
    ICLegacyReturnCodeDeviceIOServicePathNotFoundErr  = -9917,
    /* Device is not supported under ICA */
    ICLegacyReturnCodeDeviceUnsupportedErr            = -9918,
    /* Generic framework internal error */
    ICLegacyReturnCodeFrameworkInternalErr            = -9919,
    /* Generic ImageCaptureExtension internal error */
    ICLegacyReturnCodeExtensionInternalErr            = -9920,
    /* Session is invalid */
    ICLegacyReturnCodeInvalidSessionErr               = -9921,
};


typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnCode) {

    /* Operation successful. */
    ICReturnSuccess                               = 0,
    /* An invalid parameter was found. */
    ICReturnInvalidParam                          = -9922,
    /* Communication between different components of Image Capture timed out. */
    ICReturnCommunicationTimedOut                 = -9923,
    /* The scan operation is canceled. */
    ICReturnScanOperationCanceled                 = -9924,
    /*  Scanner is being used by a local user. */
    ICReturnScannerInUseByLocalUser               = -9925,
    /* Scanner is being used by a remote user. */
    ICReturnScannerInUseByRemoteUser              = -9926,
    /* Failed to open a session on a specified device. */
    ICReturnDeviceFailedToOpenSession             = -9927,
    /* Failed to close a session on a specified device. */
    ICReturnDeviceFailedToCloseSession            = -9928,
    /* Failed to select a functional unit on the specified scanner. */
    ICReturnScannerFailedToSelectFunctionalUnit   = -9929,
    /* Overview scan operation failed to complete on the specified scanner. */
    ICReturnScannerFailedToCompleteOverviewScan   = -9930,
    /* Scan operation failed to complete on the specified scanner. */
    ICReturnScannerFailedToCompleteScan           = -9931,
    /* An unsolicited status information was received from a scanner. */
    ICReturnReceivedUnsolicitedScannerStatusInfo  = -9932,
    /* An unsolicited error information was received from a scanner. */
    ICReturnReceivedUnsolicitedScannerErrorInfo   = -9933,
    /* A non-specific error occurred while downloading a file. */
    ICReturnDownloadFailed                        = -9934,
    /* A non-specific error occurred while updownloading a file. */
    ICReturnUploadFailed                          = -9935,
    /* Failed to complete a pass-through (e.g., PTP pass-through) command. */
    ICReturnFailedToCompletePassThroughCommand    = -9936,
    /* A download operation was canceled. */
    ICReturnDownloadCanceled                      = -9937,
    /* Failed to enable tethered-capture on a camera device. */
    ICReturnFailedToEnabeTethering                = -9938,
    /* Failed to disable tethered-capture on a camera device. */
    ICReturnFailedToDisabeTethering               = -9939,
    /* A request to send a message to a device failed. */
    ICReturnFailedToCompleteSendMessageRequest    = -9940,
    /* A request to delete files failed. */
    ICReturnDeleteFilesFailed                     = -9941,
    /*  A request to delete files was canceled. */
    ICReturnDeleteFilesCanceled                   = -9942,
    /* The device is locked with a passcode. Its contents cannot be seen unless it is unlocked. */
    ICReturnDeviceIsPasscodeLocked                = -9943,
    /* Failed to take a tethered-capture picture on a camera device. */
    ICReturnDeviceFailedToTakePicture             = -9944,
    /* Failed to open session because software to communicate with the device is not installed. */
    ICReturnDeviceSoftwareNotInstalled            = -9945,
    /*  Failed to open session because software to communicate with the device is being installed. */
    ICReturnDeviceSoftwareIsBeingInstalled        = -9946,
    /* Software installation for the device has completed successfully. */
    ICReturnDeviceSoftwareInstallationCompleted   = -9947,
    /* Software installation for the device has been canceled. */
    ICReturnDeviceSoftwareInstallationCanceled    = -9948,
    /* Software installation for the device failed. */
    ICReturnDeviceSoftwareInstallationFailed      = -9949,
    /* Software for the device is not available from Apple. */
    ICReturnDeviceSoftwareNotAvailable            = -9950,
    /* A pairing request for a Apple Device failed. */
    ICReturnDeviceCouldNotPair                    = -9951,
    /* A unpairing request for a Apple Device failed. */
    ICReturnDeviceCouldNotUnpair                  = -9952,
    /* The device reports credentials are required to open the device. */
    ICReturnDeviceNeedsCredentials                = -9953,
    /* The device is currently enumerating assets. */
    ICReturnDeviceIsBusyEnumerating               = -9954,
    /* The device has experienced a general failure. */
    ICReturnDeviceCommandGeneralFailure           = -9955,
    /* Failed to complete a data transaction. */
    ICReturnDeviceFailedToCompleteTransfer        = -9956,
    /* Failed to send data. */
    ICReturnDeviceFailedToSendData                = -9957,
    /* Session is not open. */
    ICReturnSessionNotOpened                      = -9958,
    /* EXFAT volume is invalid, and cannot be enumerated. */
    ICReturnExFATVolumeInvalid                  = ICReturnCodeExFATOffset,
    /* Multierror */
    ICReturnMultiErrorDictionary                = -30000,
};

#define ICReturnDeviceIsAccessRestrictedAppleDevice ICReturnDeviceIsPasscodeLocked

//------------------------------------------------------------------------------------------------------------------------------
// ==========  ImageCaptureCore.framework/Headers/ICScannerBandData.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerBandData.h
//  ImageCaptureCore
//
//  Copyright (c) 2011 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICScannerFunctionalUnits.h>
#import <ImageCaptureCore/ImageCapturePlatform.h>

//------------------------------------------------------------------------------------------------------------ ICScannerBandData

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerBandData : NSObject

/*!
 @property fullImageWidth
 @abstract Describes the full image width of the banded image.
*/
@property(readonly)                         NSUInteger              fullImageWidth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property fullImageHeight
 @abstract Describes the full image height of the banded image.
*/
@property(readonly)                         NSUInteger              fullImageHeight IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bitsPerPixel
 @abstract Describes the number of bits per pixel for banded the image.
*/
@property(readonly)                         NSUInteger              bitsPerPixel IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bitsPerComponent
 @abstract Describes the number of bits per component for the banded image.
*/
@property(readonly)                         NSUInteger              bitsPerComponent IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property numComponents
 @abstract Describes how many components are contained within the banded image.
*/
@property(readonly)                         NSUInteger              numComponents IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bigEndian
 @abstract Describes if the banded image data is reported in big endian.
*/
@property(readonly,getter=isBigEndian)      BOOL                    bigEndian IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property pixelDataType
 @abstract Type of pixel data that is contained in the band.
*/
@property(readonly)                         ICScannerPixelDataType  pixelDataType IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property colorSyncProfilePath
 @abstract Returns the path to the color profile matching the banded data.
*/
@property(readonly, retain, nullable)       NSString*               colorSyncProfilePath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bytesPerRow
 @abstract Descries how many bytes are in each image band row.
*/
@property(readonly)                         NSUInteger              bytesPerRow IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataStartRow
 @abstract Describes the start row of the image band.
*/
@property(readonly)                         NSUInteger              dataStartRow IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataNumRows
 @abstract Describes the number of rows contained in the image band.
*/
@property(readonly)                         NSUInteger              dataNumRows IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataSize
 @abstract Describes the actual data size of the image band buffer.
*/
@property(readonly)                         NSUInteger              dataSize IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataBuffer
 @abstract The pointer to the data buffer object.
*/
@property(readonly, retain, nullable)       NSData*                 dataBuffer IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------------------------------
// ==========  ImageCaptureCore.framework/Headers/ICScannerDevice.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
  @header ICScannerDevice
    ICScannerDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class. In this release, an instance of ICScannerDevice class is intended to be used by the IKScannerDeviceView object. The IKScannerDeviceView class encapsulates the complexities of setting scan parameters, performing scans and saving the result. The developer should consider using IKScannerDeviceView instead of building their own views using the ICScannerDevice object.
*/

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICScannerFunctionalUnits.h>
#import <ImageCaptureCore/ICScannerBandData.h>
#import <ImageCaptureCore/ImageCapturePlatform.h>

NS_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify button-press on a device.
/*!
 @const      ICButtonTypeScan
 @abstract   ICButtonTypeScan
 @discussion Indicates that the "Scan" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeMail
 @abstract   ICButtonTypeMail
 @discussion Indicates that the "Mail" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeMail IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeCopy
 @abstract   ICButtonTypeCopy
 @discussion Indicates that the "Copy" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeCopy IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeWeb
 @abstract   ICButtonTypeWeb
 @discussion Indicates that the "Web" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeWeb IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypePrint
 @abstract   ICButtonTypePrint
 @discussion Indicates that the "Print" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypePrint IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeTransfer
 @abstract   ICButtonTypeTransfer
 @discussion Indicates that the "Transfer" button on the device was pressed.
 */


IMAGECAPTURE_EXTERN NSString *const ICButtonTypeTransfer IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
  @const      ICScannerStatusWarmingUp
  @abstract   ICScannerStatusWarmingUp
  @discussion A non-localized notification string to indicate that the scanner is warming up.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusWarmingUp IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @const      ICScannerStatusWarmUpDone
  @abstract   ICScannerStatusWarmUpDone
  @discussion A non-localized notification string to indicate that the scanner has warmed up.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusWarmUpDone IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @const      ICScannerStatusRequestsOverviewScan
  @abstract   ICScannerStatusRequestsOverviewScan
  @discussion A non-localized notification string to indicate that the scanner is requesting an overview scan to be performed.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusRequestsOverviewScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICScannerTransferMode
  @abstract Transfer mode to be used when transferring scan data from the scanner functional unit.
  @constant ICScannerTransferModeFileBased Save the scan as a file.
  @constant ICScannerTransferModeMemoryBased Transfer the scan as data.
*/

typedef NS_ENUM( NSUInteger, ICScannerTransferMode ) {
    ICScannerTransferModeFileBased   = 0,
    ICScannerTransferModeMemoryBased = 1
} IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICScannerDevice;

//------------------------------------------------------------------------------------------------------ ICScannerDeviceDelegate
/*!
  @protocol ICScannerDeviceDelegate <ICDeviceDelegate>
  @abstract A delegate of ICScannerDevice must conform to ICScannerDeviceDelegate protocol.
  @discussion The ICScannerDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@protocol ICScannerDeviceDelegate <ICDeviceDelegate>

@optional

/*!
  @method scannerDeviceDidBecomeAvailable:
  @abstract This message is sent when another client closes an open session on the scanner.
  @discusson Scanners require exclusive access, only one client can open a session on a scanner. The scanner is available if it does not have a session opened by another client. Attempting to open a session on a scanner that already has an open session for another client will result in an error. A client that wants to open a session on a scanner as soon as it is available should implement this method and send "requestOpenSession" message to scanner object from that method.
*/
- (void)scannerDeviceDidBecomeAvailable:(ICScannerDevice*)scanner IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didSelectFunctionalUnit:error:
  @abstract This message is sent when a functional unit is selected on the scanner device.
  @discusson A functional unit is selected immediately after the scanner device is instantiated and in response to "requestSelectFunctionalUnit:" message.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didSelectFunctionalUnit:(ICScannerFunctionalUnit*)functionalUnit error:(nullable NSError*)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didScanToURL:data:
  @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
  @discusson This method has been deprecated and superceded by the didScanToURL: method for file based transfer, along with the didScanToBandData: for memory based transfer.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToURL:(NSURL*)url data:(NSData*)data IC_DEPRECATED("Use didScanToURL: for file URLs and didScanToBandData: for memory based transfers",macos(10.6,10.7)) IC_UNAVAILABLE(ios);

/*!
 @method scannerDevice:didScanToURL:
 @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 @discusson This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 */
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToURL:(NSURL*)url IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

/*!
 @method scannerDevice:didScanToBandData:
 @abstract This message is sent when the scanner device receives the requested scan progress notification and a band of data is sent for each notification received.
 @discusson In memory transfer mode, this will send a band of size that has been selected by the client via the maxMemoryBandSize property.
 */
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToBandData:(ICScannerBandData*)data IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didCompleteOverviewScanWithError:
  @abstract This message is sent after the scanner device completes an overview scan.
  @discusson This message is sent after the scanner device completes an overview scan.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didCompleteOverviewScanWithError:(nullable NSError*)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didCompleteScanWithError:
  @abstract This message is sent after the scanner device completes a scan.
  @discusson This message is sent after the scanner device completes a scan.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didCompleteScanWithError:(nullable NSError*)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------------------------------
/*!
  @class ICScannerDevice
  @abstract ICScannerDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
  @discussion In this release, an instance of ICScannerDevice class is intended to be used by the ICScannerDeviceView object. The ICScannerDeviceView class encapsulates the complexities of setting scan parameters, performing scans and saving the result. The developer should consider using ICScannerDeviceView instead of building their own views using the ICScannerDevice object.
*/
__attribute__((visibility("default")))
IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerDevice : ICDevice
{
@private
    id _scannerProperties;
}

/*!
  @property availableFunctionalUnitTypes
  @abstract ￼An array of functional unit types available on this scanner device. This is an array of NSNumber objects whose values are of type ICScannerFunctionalUnitType.
*/
@property ( readonly ) NSArray<NSNumber*>* availableFunctionalUnitTypes IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property selectedFunctionalUnit
  @abstract ￼The currently selected functional unit on the scanner device.
*/
@property ( readonly ) ICScannerFunctionalUnit* selectedFunctionalUnit IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property transferMode
  @abstract ￼The transfer mode for scanned document.
*/
@property ICScannerTransferMode transferMode IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property maxMemoryBandSize
 @abstract ￼The total maximum band size requested when performing a ICScannerTransferModeMemoryBased.
 
 */
@property UInt32 maxMemoryBandSize IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property downloadsDirectory
  @abstract ￼The downloads directory.
*/
@property ( retain ) NSURL* downloadsDirectory IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property documentName
  @abstract ￼The document name.
*/
@property ( copy ) NSString* documentName IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property documentUTI
  @abstract ￼The document UTI. Currently supported UTIs are: kUTTypeJPEG, kUTTypeJPEG2000, kUTTypeTIFF, kUTTypePNG etc.
*/
@property ( copy ) NSString* documentUTI IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property defaultUsername
 @abstract If the device is protected, instead of prompting the user for a username, this property
        can be set to default to a specific username as a convience.  The value will persist until
        reset by setting it to nil.
 */
@property ( copy ) NSString* defaultUsername IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestOpenSessionWithCredentials:
 @abstract This message requests to open a session on the protected device with the authorized username and
           passcode.  If the device reports back a failure of credentials, they can be provided here for the
           launch.
           A client MUST open a session on a device in order to use the device.
 @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message. No more messages will be sent to the delegate if this request fails.
 */
- (void)requestOpenSessionWithCredentials:(NSString*)username password:(NSString*)password IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestSelectFunctionalUnit:delegate:selector:contextInfo:
  @abstract Requests the scanner device to select a functional unit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didSelectFunctionalUnit:error:' message.
*/
- (void)requestSelectFunctionalUnit:(ICScannerFunctionalUnitType)type IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestOverviewScan
  @abstract Starts an overview scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteOverviewScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestOverviewScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestScan
  @abstract Starts a scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method cancelScan
  @abstract Cancels the current scan operation started by sending a 'requestOverviewScan' or 'requestScan'.
*/
- (void)cancelScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
// ==========  ImageCaptureCore.framework/Headers/ICScannerFunctionalUnits.h

//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerFunctionalUnits.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2011 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
  @header ICScannerFunctionalUnit
  @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitPositiveTransparency, ICScannerFunctionalUnitNegativeTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

//------------------------------------------------------------------------------------------------------------------------------

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <ImageCaptureCore/ImageCaptureConstants.h>
#import <Foundation/Foundation.h>

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICScannerFunctionalUnitType
  @abstract Scanner Functional Unit Types
  @constant ICScannerFunctionalUnitTypeFlatbed Flatbed functional unit.
  @constant ICScannerFunctionalUnitTypePositiveTransparency Transparency functional unit for scanning positives.
  @constant ICScannerFunctionalUnitTypeNegativeTransparency Transparency functional unit for scanning negatives.
  @constant ICScannerFunctionalUnitTypeDocumentFeeder Document feeder functional unit.
*/

typedef NS_ENUM(NSUInteger, ICScannerFunctionalUnitType)
{
    ICScannerFunctionalUnitTypeFlatbed              = 0,
    ICScannerFunctionalUnitTypePositiveTransparency = 1,
    ICScannerFunctionalUnitTypeNegativeTransparency = 2,
    ICScannerFunctionalUnitTypeDocumentFeeder       = 3
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerMeasurementUnit
  @abstract Unit of measurement used by the scanner. This corresponds to values used for ICAP_UNITS as defined in the TWAIN Specification.
  @constant ICScannerMeasurementUnitInches      1 inch  = 2.54         cm
  @constant ICScannerMeasurementUnitCentimeters 1 cm    = 1.00         cm or 1/2.54 inches
  @constant ICScannerMeasurementUnitPicas       1 pica  = .42333333    cm or 1/6    inches
  @constant ICScannerMeasurementUnitPoints      1 point = .0352777775  cm or 1/72   inches
  @constant ICScannerMeasurementUnitTwips       1 twip  = .0001763888  cm or 1/1440 inches
  @constant ICScannerMeasurementUnitPixels
*/

typedef NS_ENUM(NSUInteger, ICScannerMeasurementUnit)
{
    ICScannerMeasurementUnitInches      = 0,
    ICScannerMeasurementUnitCentimeters = 1,
    ICScannerMeasurementUnitPicas       = 2,
    ICScannerMeasurementUnitPoints      = 3,
    ICScannerMeasurementUnitTwips       = 4,
    ICScannerMeasurementUnitPixels      = 5
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerBitDepth
  @abstract Bits per channel in the scanned image.
  @constant ICScannerBitDepth1Bit 1-bit image.
  @constant ICScannerBitDepth8Bits Image with 8 bits per channel.
  @constant ICScannerBitDepth16Bits Image with 16 bits per channel.
*/

typedef NS_ENUM(NSUInteger, ICScannerBitDepth)
{
    ICScannerBitDepth1Bit   = 1,
    ICScannerBitDepth8Bits  = 8,
    ICScannerBitDepth16Bits = 16
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerColorDataFormatType
  @abstract Identifies color data formats. Only relevant for multi-channel data. Corresponds to "ICAP_PLANARCHUNKY" of the TWAIN Specification.
  @constant ICScannerColorDataFormatTypeChunky For multi-channel data (e.g., RGB) data from all channels are interleaved.
  @constant ICScannerColorDataFormatTypePlanar For multi-channel data (e.g., RGB) each channel is transferred sequentially.
*/

typedef NS_ENUM(NSUInteger, ICScannerColorDataFormatType)
{
    ICScannerColorDataFormatTypeChunky  = 0,
    ICScannerColorDataFormatTypePlanar  = 1
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerPixelDataType
  @abstract Pixel data types. Corresponds to "ICAP_PIXELTYPE" of the TWAIN Specification.
  @constant ICScannerPixelDataTypeBW Monochrome 1 bit pixel image.
  @constant ICScannerPixelDataTypeGray 8 bit pixel Gray color space.
  @constant ICScannerPixelDataTypeRGB Color image RGB color space.
  @constant ICScannerPixelDataTypePalette Indexed Color image.
  @constant ICScannerPixelDataTypeCMY Color image in CMY color space.
  @constant ICScannerPixelDataTypeCMYK Color image in CMYK color space.
  @constant ICScannerPixelDataTypeYUV Color image in YUV color space.
  @constant ICScannerPixelDataTypeYUVK Color image in YUVK color space.
  @constant ICScannerPixelDataTypeCIEXYZ Color image in CIEXYZ color space.
*/

typedef NS_ENUM(NSUInteger, ICScannerPixelDataType)
{
    ICScannerPixelDataTypeBW      = 0,
    ICScannerPixelDataTypeGray    = 1,
    ICScannerPixelDataTypeRGB     = 2,
    ICScannerPixelDataTypePalette = 3,
    ICScannerPixelDataTypeCMY     = 4,
    ICScannerPixelDataTypeCMYK    = 5,
    ICScannerPixelDataTypeYUV     = 6,
    ICScannerPixelDataTypeYUVK    = 7,
    ICScannerPixelDataTypeCIEXYZ  = 8
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerDocumentType
  @abstract Document size types. Corresponds to "ICAP_SUPPORTEDSIZES" used by the Image Catpure scanner modules. Also refer to TWAIN 1.9 Specification, page 9-483.
  @constant ICScannerDocumentTypeDefault This is the platten size. Not valid for scanners without a platten.
  @constant ICScannerDocumentTypeA4             A4,                               210.00 mm x  297.00 mm
  @constant ICScannerDocumentTypeB5             B5/JIS B5,                        182.00 mm x  257.00 mm
  @constant ICScannerDocumentTypeUSLetter       US Letter,        8.5” x 11.0”,   215.90 mm x  279.40 mm
  @constant ICScannerDocumentTypeUSLegal        US Legal,         8.5” x 14.0”,   215.90 mm x  355.60 mm
  @constant ICScannerDocumentTypeA5             A5,                               148.00 mm x  210.00 mm
  @constant ICScannerDocumentTypeISOB4          B4/ISO B4,                        250.00 mm x  353.00 mm
  @constant ICScannerDocumentTypeISOB6          B6/ISO B6,                        125.00 mm x  176.00 mm
  @constant ICScannerDocumentTypeUSLedger       US Ledger,         11” x 17.0”,   279.40 mm x  431.80 mm
  @constant ICScannerDocumentTypeUSExecutive    US Executive,    7.25" x 10.5",   184.15 mm x  266.70 mm
  @constant ICScannerDocumentTypeA3             A3,                               297.00 mm x  420.00 mm
  @constant ICScannerDocumentTypeISOB3          B3/ISO B3,                        353.00 mm x  500.00 mm
  @constant ICScannerDocumentTypeA6             A6,                               105.00 mm x  148.00 mm
  @constant ICScannerDocumentTypeC4             C4,                               229.00 mm x  324.00 mm
  @constant ICScannerDocumentTypeC5             C5,                               162.00 mm x  229.00 mm
  @constant ICScannerDocumentTypeC6             C6,                               114.00 mm x  162.00 mm
  @constant ICScannerDocumentType4A0            4A0,                             1682.00 mm x 2378.00 mm
  @constant ICScannerDocumentType2A0            2A0,                             1189.00 mm x 1682.00 mm
  @constant ICScannerDocumentTypeA0             A0,                               841.00 mm x 1189.00 mm
  @constant ICScannerDocumentTypeA1             A1,                               594.00 mm x  841.00 mm
  @constant ICScannerDocumentTypeA2             A2,                               420.00 mm x  594.00 mm
  @constant ICScannerDocumentTypeA7             A7,                                74.00 mm x  105.00 mm
  @constant ICScannerDocumentTypeA8             A8,                                52.00 mm x   74.00 mm
  @constant ICScannerDocumentTypeA9             A9,                                37.00 mm x   52.00 mm
  @constant ICScannerDocumentType10             A10,                               26.00 mm x   37.00 mm
  @constant ICScannerDocumentTypeISOB0          ISO B0,                          1000.00 mm x 1414.00 mm
  @constant ICScannerDocumentTypeISOB1          ISO B1,                           707.00 mm x 1000.00 mm
  @constant ICScannerDocumentTypeISOB2          ISO B2,                           500.00 mm x  707.00 mm
  @constant ICScannerDocumentTypeISOB5          ISO B5,                           176.00 mm x  250.00 mm
  @constant ICScannerDocumentTypeISOB7          ISO B7,                            88.00 mm x  125.00 mm
  @constant ICScannerDocumentTypeISOB8          ISO B8,                            62.00 mm x   88.00 mm
  @constant ICScannerDocumentTypeISOB9          ISO B9,                            44.00 mm x   62.00 mm
  @constant ICScannerDocumentTypeISOB10         ISO B10,                           31.00 mm x   44.00 mm
  @constant ICScannerDocumentTypeJISB0          JIS B0,                          1030.00 mm x 1456.00 mm
  @constant ICScannerDocumentTypeJISB1          JIS B1,                           728.00 mm x 1030.00 mm
  @constant ICScannerDocumentTypeJISB2          JIS B2,                           515.00 mm x  728.00 mm
  @constant ICScannerDocumentTypeJISB3          JIS B3,                           364.00 mm x  515.00 mm
  @constant ICScannerDocumentTypeJISB4          JIS B4,                           257.00 mm x  364.00 mm
  @constant ICScannerDocumentTypeJISB6          JIS B6,                           128.00 mm x  182.00 mm
  @constant ICScannerDocumentTypeJISB7          JIS B7,                            91.00 mm x  128.00 mm
  @constant ICScannerDocumentTypeJISB8          JIS B8,                            64.00 mm x   91.00 mm
  @constant ICScannerDocumentTypeJISB9          JIS B9,                            45.00 mm x   64.00 mm
  @constant ICScannerDocumentTypeJISB10         JIS B10,                           32.00 mm x   45.00 mm
  @constant ICScannerDocumentTypeC0             C0,                               917.00 mm x 1297.00 mm
  @constant ICScannerDocumentTypeC1             C1,                               648.00 mm x  917.00 mm
  @constant ICScannerDocumentTypeC2             C2,                               458.00 mm x  648.00 mm
  @constant ICScannerDocumentTypeC3             C3,                               324.00 mm x  458.00 mm
  @constant ICScannerDocumentTypeC7             C7,                                81.00 mm x  114.00 mm
  @constant ICScannerDocumentTypeC8             C8,                                57.00 mm x   81.00 mm
  @constant ICScannerDocumentTypeC9             C9,                                40.00 mm x   57.00 mm
  @constant ICScannerDocumentTypeC10            C10,                               28.00 mm x   40.00 mm
  @constant ICScannerDocumentTypeUSStatement    US Statement,     5.5” x  8.5”,   139.70 mm x  215.90 mm
  @constant ICScannerDocumentTypeBusinessCard   Business Card,                     90.00 mm x   55.00 mm

  @constant ICScannerDocumentTypeE              Japanese E,      3.25" x 4.75"     82.55 mm x  120.65 mm      11:16
  @constant ICScannerDocumentType3R             3R,              3.5"  x 5"        88.90 mm x  127.00 mm       7:10
  @constant ICScannerDocumentType4R             4R,              4"    x 6"       101.60 mm x  152.40 mm       2:3
  @constant ICScannerDocumentType5R             5R,              5"    x 7"       127.00 mm x  177.80 mm       5:7
  @constant ICScannerDocumentType6R             6R,              6"    x 8"       152.40 mm x  203.20 mm       3:4
  @constant ICScannerDocumentType8R             8R,              8"    x 10"      203.20 mm x  254.00 mm       4:5
  @constant ICScannerDocumentTypeS8R            S8R              8"    x 12"      203.20 mm x  304.80 mm       2:3
  @constant ICScannerDocumentType10R            10R,             10"   x 12"      254.00 mm x  304.80 mm       5:6
  @constant ICScannerDocumentTypeS10R           S10R,            10"   x 15"      254.00 mm x  381.00 mm       2:3
  @constant ICScannerDocumentType11R            11R,             11"   x 14"      279.40 mm x  355.60 mm      11:14
  @constant ICScannerDocumentType12R            12R,             12"   x 15"      304.80 mm x  381.00 mm       4:5
  @constant ICScannerDocumentTypeS12R           S12R,            12"   x 18"      304.80 mm x  457.20 mm       2:3
  @constant ICScannerDocumentTypeS12R           S12R,            12"   x 18"      304.80 mm x  457.20 mm       2:3

  @constant ICScannerDocumentType110            Instamatic 110,                    13.00 mm x   17.00 mm
  @constant ICScannerDocumentTypeAPSH           APS High Definition,               30.20 mm x   16.70 mm
  @constant ICScannerDocumentTypeAPSC           APS Classic,                       25.10 mm x   16.70 mm
  @constant ICScannerDocumentTypeAPSP           APS Panoramic,                     30.20 mm x    9.50 mm
  @constant ICScannerDocumentType135            Standard 35 mm,                    36.00 mm x   24.00 mm
  @constant ICScannerDocumentTypeMF             Medium Format,                     60.00 mm x   60.00 mm
  @constant ICScannerDocumentTypeLF             Large Format,                     100.00 mm x  120.00 mm
*/

typedef NS_ENUM(NSUInteger, ICScannerDocumentType)
{
    ICScannerDocumentTypeDefault      = 0,
    ICScannerDocumentTypeA4           = 1,
    ICScannerDocumentTypeB5           = 2,
    ICScannerDocumentTypeUSLetter     = 3,
    ICScannerDocumentTypeUSLegal      = 4,
    ICScannerDocumentTypeA5           = 5,
    ICScannerDocumentTypeISOB4        = 6,
    ICScannerDocumentTypeISOB6        = 7,
    ICScannerDocumentTypeUSLedger     = 9,
    ICScannerDocumentTypeUSExecutive  = 10,
    ICScannerDocumentTypeA3           = 11,
    ICScannerDocumentTypeISOB3        = 12,
    ICScannerDocumentTypeA6           = 13,
    ICScannerDocumentTypeC4           = 14,
    ICScannerDocumentTypeC5           = 15,
    ICScannerDocumentTypeC6           = 16,
    ICScannerDocumentType4A0          = 17,
    ICScannerDocumentType2A0          = 18,
    ICScannerDocumentTypeA0           = 19,
    ICScannerDocumentTypeA1           = 20,
    ICScannerDocumentTypeA2           = 21,
    ICScannerDocumentTypeA7           = 22,
    ICScannerDocumentTypeA8           = 23,
    ICScannerDocumentTypeA9           = 24,
    ICScannerDocumentType10           = 25,
    ICScannerDocumentTypeISOB0        = 26,
    ICScannerDocumentTypeISOB1        = 27,
    ICScannerDocumentTypeISOB2        = 28,
    ICScannerDocumentTypeISOB5        = 29,
    ICScannerDocumentTypeISOB7        = 30,
    ICScannerDocumentTypeISOB8        = 31,
    ICScannerDocumentTypeISOB9        = 32,
    ICScannerDocumentTypeISOB10       = 33,
    ICScannerDocumentTypeJISB0        = 34,
    ICScannerDocumentTypeJISB1        = 35,
    ICScannerDocumentTypeJISB2        = 36,
    ICScannerDocumentTypeJISB3        = 37,
    ICScannerDocumentTypeJISB4        = 38,
    ICScannerDocumentTypeJISB6        = 39,
    ICScannerDocumentTypeJISB7        = 40,
    ICScannerDocumentTypeJISB8        = 41,
    ICScannerDocumentTypeJISB9        = 42,
    ICScannerDocumentTypeJISB10       = 43,
    ICScannerDocumentTypeC0           = 44,
    ICScannerDocumentTypeC1           = 45,
    ICScannerDocumentTypeC2           = 46,
    ICScannerDocumentTypeC3           = 47,
    ICScannerDocumentTypeC7           = 48,
    ICScannerDocumentTypeC8           = 49,
    ICScannerDocumentTypeC9           = 50,
    ICScannerDocumentTypeC10          = 51,
    ICScannerDocumentTypeUSStatement  = 52,
    ICScannerDocumentTypeBusinessCard = 53,
    
    ICScannerDocumentTypeE            = 60,
    ICScannerDocumentType3R           = 61,
    ICScannerDocumentType4R           = 62,
    ICScannerDocumentType5R           = 63,
    ICScannerDocumentType6R           = 64,
    ICScannerDocumentType8R           = 65,
    ICScannerDocumentTypeS8R          = 66,
    ICScannerDocumentType10R          = 67,
    ICScannerDocumentTypeS10R         = 68,
    ICScannerDocumentType11R          = 69,
    ICScannerDocumentType12R          = 70,
    ICScannerDocumentTypeS12R         = 71,
    ICScannerDocumentType110          = 72,
    ICScannerDocumentTypeAPSH         = 73,
    ICScannerDocumentTypeAPSC         = 74,
    ICScannerDocumentTypeAPSP         = 75,
    ICScannerDocumentType135          = 76,
    ICScannerDocumentTypeMF           = 77,
    ICScannerDocumentTypeLF           = 78
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerFunctionalUnitState
  @abstract A flag to indicate the scanner functional unit's state
  @constant ICScannerStateReady The scanner functional unit is ready for operation.
  @constant ICScannerStateScanInProgress The scanner functional unit is performing a scan.
  @constant ICScannerStateOverviewScanInProgress The scanner functional unit is performing an overview scan.
*/

typedef NS_ENUM(NSUInteger, ICScannerFunctionalUnitState)
{
    ICScannerFunctionalUnitStateReady                  = (1 << 0),
    ICScannerFunctionalUnitStateScanInProgress         = (1 << 1),
    ICScannerFunctionalUnitStateOverviewScanInProgress = (1 << 2)
}IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerFeatureType
  @abstract Scanner Feature Types
  @constant ICScannerFeatureTypeEnumeration This feature can have one of several discrete values, strings or numbers.
  @constant ICScannerFeatureTypeRange This value of this feature lies within a range.
  @constant ICScannerFeatureTypeBoolean The value of this feature can be YES or NO.
*/

typedef NS_ENUM(NSUInteger, ICScannerFeatureType)
{
    ICScannerFeatureTypeEnumeration = 0,
    ICScannerFeatureTypeRange       = 1,
    ICScannerFeatureTypeBoolean     = 2,
    ICScannerFeatureTypeTemplate    = 3
}IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//------------------------------------------------------------------------------------------------------------- ICScannerFeature
/*!
  @class ICScannerFeature
  @abstract ICScannerFeature class is an abstract base class used to describe a scanner feature. ImageCaptureCore defines three concrete subclasses of ICScannerFeature: ICScannerFeatureEnumeration, ICScannerFeatureRange and ICScannerFeatureBoolean.
  @discussion The scanner functional units may have one or more instances of these classes to allow users to choose scanner-specific settings or operations before performing a scan.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeature : NSObject
{
@private
    id _sfProps;
}

/*!
  @property type
  @abstract ￼Scanner feature type.
*/
@property (readonly) ICScannerFeatureType type;

/*!
  @property internalName
  @abstract ￼The internal name of this feature.
*/
@property (readonly, nullable) NSString* internalName;

/*!
  @property humanReadableName
  @abstract The human readable name of this feature.
*/
@property (readonly, nullable) NSString* humanReadableName;

/*!
  @property tooltip
  @abstract ￼Tooltip text describing the feature.
*/
@property (readonly, nullable) NSString* tooltip;
@end

    //-------------------------------------------------------------------------------------------------- ICScannerFeatureEnumeration
    /*!
  @class ICScannerFeatureEnumeration
  @abstract ICScannerFeatureEnumeration object is used to represent a feature of a scanner functional unit that can have one of several discrete values.
*/

NS_ASSUME_NONNULL_BEGIN

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureEnumeration : ICScannerFeature
{
@private
    id _evProps;
}

/*!
  @property currentValue
  @abstract The current value. The current value can be set to one of the possible values in the "values" property below￼.
*/
@property (assign) id currentValue;

/*!
  @property defaultValue
  @abstract ￼The default value. The default value can be set to one of the possible values in the "values" property below.
*/
@property (readonly) id defaultValue;

/*!
  @property values
  @abstract An array of possible values. All items in this array must be of same type￼.
*/
@property (readonly) NSArray<NSNumber*>* values;

/*!
  @property menuItemLabels
  @abstract ￼The human readable menu item labels to be used in a menu to allow the user to select the current value from an array of possible values.
*/
@property (readonly) NSArray<NSString*>* menuItemLabels;

/*!
  @property menuItemLabelsTooltips
  @abstract ￼Tooltip text associated with the menu items.
*/
@property (readonly) NSArray<NSString*>* menuItemLabelsTooltips;
@end

    //-------------------------------------------------------------------------------------------------------- ICScannerFeatureRange
    /*!
  @class ICScannerFeatureRange
  @abstract ICScannerFeatureRange object is used to represent a property of a scanner functional unit whose value lies within a range.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureRange : ICScannerFeature
{
@private
    id _rvProps;
}

/*!
  @property currentValue
  @abstract ￼The current value. Attempting to set the current value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the current value.
*/
@property (assign) CGFloat currentValue;

/*!
  @property defaultValue
  @abstract The default value￼. Attempting to set the default value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the default value.
*/
@property (readonly) CGFloat defaultValue;

/*!
  @property minValue
  @abstract The minimum value.
*/
@property (readonly) CGFloat minValue;

/*!
  @property maxValue
  @abstract ￼The maximum value.
*/
@property (readonly) CGFloat maxValue;

/*!
  @property stepSize
  @abstract ￼The step size.
*/
@property (readonly) CGFloat stepSize;
@end

    //----------------------------------------------------------------------------------------------------- ICScannerFeatureBoolean
    /*!
  @class ICScannerFeatureBoolean
  @abstract ICScannerFeatureBoolean object is used to represent a property of a scanner functional unit whose value can be YES or NO.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureBoolean : ICScannerFeature
{
@private
    id _bvProps;
}

/*!
  @property value
  @abstract ￼The value of this feature.
*/
@property (readwrite) BOOL value;
@end

    //---------------------------------------------------------------------------------------------------- ICScannerFeatureTemplate
    /*!
  @class ICScannerFeatureTemplate
  @abstract ICScannerFeatureTemplate object is used to define a group of one or more rectangular scan areas that can be used with a scanner functional unit.
*/

    IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios) @interface ICScannerFeatureTemplate : ICScannerFeature
{
@private
    id _tvProps;
}

@property (readonly) NSArray<NSMutableArray*>* targets;
@end

    //------------------------------------------------------------------------------------------------------ ICScannerFunctionalUnit
    /*!
  @class ICScannerFunctionalUnit
  @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitPositiveTransparency, ICScannerFunctionalUnitNegativeTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

    IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios) @interface ICScannerFunctionalUnit : NSObject
{
@private
    id _fuProps;
}

/*!
  @property type
  @abstract ￼Functional unit type.
*/
@property (readonly) ICScannerFunctionalUnitType type;

/*!
  @property pixelDataType
  @abstract ￼The pixel data type.
*/
@property (readwrite) ICScannerPixelDataType pixelDataType;

/*!
  @property supportedBitDepths
  @abstract ￼Supported bit depths. The values in this set are valid values defined by ICScannerBitDepth.
*/
@property (readonly) NSIndexSet* supportedBitDepths;

/*!
  @property bitDepth
  @abstract ￼The bit depth to use when performing the final scan. This will always be one of the supported bit depths.
*/
@property (readwrite) ICScannerBitDepth bitDepth;

/*!
  @property supportedMeasurementUnits
  @abstract ￼Supported measurement units. The values in this set are valid values defined by ICScannerMeasurementUnit.
*/
@property (readonly) NSIndexSet* supportedMeasurementUnits;

/*!
  @property measurementUnit
  @abstract ￼Current measurement unit. This will always be one of the supported measurement units.
*/
@property (readwrite) ICScannerMeasurementUnit measurementUnit;

/*!
  @property supportedResolutions
  @abstract ￼Supported scan resolutions in DPI.
*/
@property (readonly) NSIndexSet* supportedResolutions;

/*!
  @property preferredResolutions
  @abstract ￼Preferred scan resolutions in DPI.
*/
@property (readonly) NSIndexSet* preferredResolutions;

/*!
  @property resolution
  @abstract ￼Current scan resolution. This will always be one of the supported resolution values.
*/
@property (readwrite) NSUInteger resolution;

/*!
  @property nativeXResolution
  @abstract ￼Optical resolution along the X axis.
*/
@property (readonly) NSUInteger nativeXResolution;

/*!
  @property nativeYResolution
  @abstract ￼Optical resolution along the Y axis.
*/
@property (readonly) NSUInteger nativeYResolution;

/*!
  @property supportedScaleFactors
  @abstract ￼Supported scale factors in percentage.
*/
@property (readonly) NSIndexSet* supportedScaleFactors;

/*!
  @property preferredScaleFactors
  @abstract ￼Preferred scale factors in percentage.
*/
@property (readonly) NSIndexSet* preferredScaleFactors;

/*!
  @property scaleFactor
  @abstract ￼Current scale factor. This will always be one of the supported scale factor values.
*/
@property (readwrite) NSUInteger scaleFactor;

/*!
  @property templates
  @abstract An array of objects of type ICScannerFeatureTemplate.
*/
@property (readonly) NSArray<ICScannerFeatureTemplate*>* templates;

/*!
  @property vendorFeatures
  @abstract An array of objects of type ICScannerFeature.
*/
@property (readonly, nullable) NSArray<ICScannerFeature*>* vendorFeatures;

/*!
  @property physicalSize
  @abstract ￼Physical size of the scan area in current measurement unit.
*/
@property (readonly) ICSize physicalSize;

/*!
  @property scanArea
  @abstract ￼This property along with scanAreaOrientation describes the area to be scanned.
*/
@property (readwrite) ICRect scanArea;

/*!
  @property scanAreaOrientation
  @abstract ￼Desired orientation of the scan area. This property along with scanArea describes the area to be scanned.
  @discussion This property is set to ICEXIFOrientation1 initially. This property is not used by the ICScannerFunctionalUnitDocumentFeeder subclass.
*/
@property (readwrite) ICEXIFOrientationType scanAreaOrientation;

/*!
  @property acceptsThresholdForBlackAndWhiteScanning
  @abstract ￼Indicates if this functional unit accepts threshold value to be used when performing a scan in black & white.
*/
@property (readonly) BOOL acceptsThresholdForBlackAndWhiteScanning;

/*!
  @property usesThresholdForBlackAndWhiteScanning
  @abstract ￼Indicates if this functional unit uses threshold value to be used when performing a scan in black & white.
*/
@property (readwrite) BOOL usesThresholdForBlackAndWhiteScanning;

/*!
  @property defaultThresholdForBlackAndWhiteScanning
  @abstract ￼Default threshold value used when performing a scan in black & white. This value is from 0 to 255.
*/
@property (readonly) unsigned char defaultThresholdForBlackAndWhiteScanning;

/*!
  @property thresholdForBlackAndWhiteScanning
  @abstract ￼Threshold value to be used when performing a scan in black & white. This value should be from 0 to 255.
*/
@property (readwrite) unsigned char thresholdForBlackAndWhiteScanning;

/*!
  @property state
  @abstract ￼Indicates the current state of the functional unit.
*/
@property (readonly) ICScannerFunctionalUnitState state;

/*!
  @property scanInProgress
  @abstract ￼Indicates if a scan is in progress.
*/
@property (readonly) BOOL scanInProgress;

/*!
  @property scanProgressPercentDone
  @abstract ￼Indicates percentage of scan completed.
*/
@property (readonly) CGFloat scanProgressPercentDone;

/*!
  @property canPerformOverviewScan
  @abstract ￼Indicates if this functional unit can perfrom an overview scan. Not all functional units can perform an overview scan. For example, a document feeder or a sheet feeder unit cannot perform an overview scan.
*/
@property (readonly) BOOL canPerformOverviewScan;

/*!
  @property overviewScanInProgress
  @abstract ￼Indicates if an overview scan is in progress.
*/
@property (readonly) BOOL overviewScanInProgress;

/*!
  @property overviewImage
  @abstract ￼Overview scan image. This property will be NULL for functional units that do not support overview scans.
*/
@property (readonly, nullable) CGImageRef overviewImage;

/*!
  @property overviewResolution
  @abstract ￼Overview image resolution. Value assigned to this will be contrained by resolutions allowed by the device.
*/
@property (readwrite) NSUInteger overviewResolution;

@end

    //----------------------------------------------------------------------------------------------- ICScannerFunctionalUnitFlatbed
    /*!
  @class ICScannerFunctionalUnitFlatbed
  @abstract ICScannerFunctionalUnitFlatbed is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the flatbed  unit on the scanner.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitFlatbed : ICScannerFunctionalUnit
{
@private
    id _fbProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly, nonnull) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------- ICScannerFunctionalUnitPositiveTransparency
    /*!
  @class ICScannerFunctionalUnitPositiveTransparency
  @abstract ICScannerFunctionalUnitPositiveTransparency is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the transparency unit on the scanner for scanning postives
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitPositiveTransparency : ICScannerFunctionalUnit
{
@private
    id _ptrProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------- ICScannerFunctionalUnitNegativeTransparency
    /*!
  @class ICScannerFunctionalUnitNegativeTransparency
  @abstract ICScannerFunctionalUnitNegativeTransparency is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the transparency unit on the scanner for scanning negatives.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitNegativeTransparency : ICScannerFunctionalUnit
{
@private
    id _ntrProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------------- ICScannerFunctionalUnitDocumentFeeder
    /*!
  @class ICScannerFunctionalUnitDocumentFeeder
  @abstract ICScannerFunctionalUnitDocumentFeeder is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the document feeder unit on the scanner.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitDocumentFeeder : ICScannerFunctionalUnit
{
@private
    id _dfProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

/*!
  @property supportsDuplexScanning
  @abstract ￼Indicates whether duplex scanning is supported.
*/
@property (readonly) BOOL supportsDuplexScanning;

/*!
  @property duplexScanningEnabled
  @abstract ￼Indicates whether duplex scanning is enabled.
*/
@property (readwrite) BOOL duplexScanningEnabled;

/*!
  @property documentLoaded
  @abstract ￼Indicates whether the feeder has documents to scan.
  @discussion This value will change when the document is loaded or removed from the feeder, if the scanner module has the capability to detect this state.
*/
@property (readonly) BOOL documentLoaded;

/*!
  @property oddPageOrientation
  @abstract ￼Desired orientation of the odd pages of the scanned document.
  @discussion This property is set to ICEXIFOrientation1 initially.
*/
@property (readwrite) ICEXIFOrientationType oddPageOrientation;

/*!
  @property evenPageOrientation
  @abstract ￼Desired orientation of the even pages of the scanned document.
  @discussion This property is set to ICEXIFOrientation1 initially.
*/
@property (readwrite) ICEXIFOrientationType evenPageOrientation;

/*!
 @property reverseFeederPageOrder
 @abstract ￼Indicates whether the document feeder reads pages from back to front.
 
 */
@property (readonly) BOOL reverseFeederPageOrder;

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
// ==========  ImageCaptureCore.framework/Headers/ImageCaptureCore.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ImageCaptureCore.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICCameraItem.h>
#import <ImageCaptureCore/ICCameraFile.h>
#import <ImageCaptureCore/ICCameraFolder.h>
#import <ImageCaptureCore/ICCameraDevice.h>
#import <ImageCaptureCore/ICDeviceBrowser.h>
#import <ImageCaptureCore/ICScannerDevice.h>
#import <ImageCaptureCore/ICScannerFunctionalUnits.h>
#import <ImageCaptureCore/ICScannerBandData.h>

//------------------------------------------------------------------------------------------------------------------------------
// ==========  ImageCaptureCore.framework/Headers/ImageCapturePlatform.h
//
//  ImageCapturePlatform.h
//  ImageCapture
//

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
    #define IMAGECAPTURE_PLATFORM_IOS
#elif ( TARGET_OS_SIMULATOR  )
    #define IMAGECAPTURE_PLATFORM_SIM
#elif ( TARGET_OS_TV  )
    #define IMAGECAPTURE_PLATFORM_TV
#else
    #define IMAGECAPTURE_PLATFORM_OSX
#endif

#if (TARGET_OS_IPHONE && !( TARGET_OS_SIMULATOR ) && !( TARGET_OS_TV ) )
    #define IMAGECAPTURE_IOS
#endif

#if (!TARGET_OS_IPHONE && ( TARGET_OS_SIMULATOR || TARGET_OS_TV ) )
    #define IMAGECAPTURE_SIM
#endif

#if ( (TARGET_OS_IPHONE || TARGET_OS_OSX ) && !TARGET_OS_SIMULATOR && !TARGET_OS_TV )
    #define IMAGECAPTURE_IOS_OSX
#endif

#if ( (TARGET_OS_IPHONE || TARGET_OS_OSX || TARGET_OS_SIMULATOR ) && !TARGET_OS_TV )
#define IMAGECAPTURE_IOS_OSX_SIM
#endif

#if (TARGET_OS_IPHONE || TARGET_OS_SIMULATOR  )
    #define IMAGECAPTURE_IOS_SIM
#endif

#ifndef IMAGECAPTURE_EXTERN
    #ifdef __cplusplus
        #define IMAGECAPTURE_EXTERN extern "C" __attribute__((visibility ("default")))
    #else
        #define IMAGECAPTURE_EXTERN extern __attribute__((visibility ("default")))
    #endif
#endif

// Deprecation &  macros
#if defined(IMAGECAPTURE_INTERNAL_BUILD)

// Suppressed macros for internal builds still implementing and testing deprecated methods
#define IC_AVAILABLE(args...) \
API_AVAILABLE(args)

#define IC_UNAVAILABLE(args...) \
API_UNAVAILABLE(args)

#define IC_DEPRECATED( args... )

#define IC_DEPRECATED_WITH_REPLACEMENT(msg, args... )

// External builds
#else

#define IC_AVAILABLE(args...) \
API_AVAILABLE(args)

#define IC_UNAVAILABLE(args...) \
API_UNAVAILABLE(args)

#define IC_DEPRECATED( args... ) \
API_DEPRECATED( args )

#define IC_DEPRECATED_WITH_REPLACEMENT( args... ) \
API_DEPRECATED_WITH_REPLACEMENT( args )

#endif

#if defined(IMAGECAPTURE_PLATFORM_OSX)

// macOS
#import <Cocoa/Cocoa.h>
#import <Foundation/NSGeometry.h>

#define ICPoint                                                NSPoint
#define ICRect                                                 NSRect
#define ICSize                                                 NSSize

#elif defined(IMAGECAPTURE_PLATFORM_IOS) || defined(IMAGECAPTURE_PLATFORM_SIM)

// iOS
#import <Foundation/Foundation.h>

#define ICPoint                                                CGPoint
#define ICRect                                                 CGRect
#define ICSize                                                 CGSize

#else

#error "Failure: ImageCapture -- unsupported platform"

#endif

// ==========  ImageCaptureCore.framework/Headers/ICDeviceBrowser.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDeviceBrowser.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
  @header ICDeviceBrowser
  @discussion The ICDeviceBrowser object is used to discover devices that vend media to Image Capture.
*/

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <ImageCaptureCore/ICDevice.h>

//------------------------------------------------------------------------------------------------------------------------------
// Forward declarations

@class ICDevice;
@class ICCameraDevice;
@class ICDeviceBrowser;

NS_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------ ICDeviceBrowserDelegate
/*!
  @protocol ICDeviceBrowserDelegate <NSObject>
  @abstract A delegate of ICDeviceBrowser must conform to ICDeviceBrowserDelegate protocol.
*/

@protocol ICDeviceBrowserDelegate <NSObject>

@required

/*!
  @method deviceBrowser:didAddDevice:moreComing:
  @abstract This message is sent to the delegate to inform that a device has been added.
  @discussion If several devices are found during the initial search, then this message is sent once for each device with the value of 'moreComing' set to YES in each message except the last one.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser didAddDevice:(ICDevice*)device moreComing:(BOOL)moreComing IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method deviceBrowser:didRemoveDevice:moreGoing:
  @abstract This message is sent to the delegate to inform that a device has been removed.
  @discussion If several devices are removed at the same time, then this message is sent once for each device with the value of 'moreGoing' set to YES in each message except the last one.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser didRemoveDevice:(ICDevice*)device moreGoing:(BOOL)moreGoing IC_AVAILABLE(macos(10.4),ios(13.0));

@optional

/*!
  @method deviceBrowser:deviceDidChangeName:
  @abstract This message is sent if the name of a device changes.
  @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser deviceDidChangeName:(ICDevice*)device IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method deviceBrowser:deviceDidChangeSharingState:
  @abstract This message is sent when the sharing state of a device has changes.
  @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser deviceDidChangeSharingState:(ICDevice*)device NS_DEPRECATED(10_4, 10_13, NA, NA);

/*!
  @method deviceBrowser:requestsSelectDevice:
  @abstract This message is sent when an event that occurred on the device may be of interest to the client application.
  @discussion In Mac OS X 10.6, this message is sent when a button is pressed on a device and the current application is the target for that button press. In the case of the button-press event, if a session is open on the device, this message will not be sent to the browser delegate, instead the message 'device:didReceiveButtonPress:' is sent to the device delegate.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser requestsSelectDevice:(ICDevice*)device IC_AVAILABLE(macos(10.4));

/*!
  @method deviceBrowserDidEnumerateLocalDevices:
  @abstract This message is sent after the device browser completes sending 'deviceBrowser:didAddDevice:moreComing:' message for all local devices.
  @discusson Detecting locally connected devices (USB and FireWire devices) is faster than detecting devices connected using a network protocol. An Image Capture client application may use this message to update its user interface to let the user know that it has completed looking for locally connected devices and then start looking for network devices.
*/
- (void)deviceBrowserDidEnumerateLocalDevices:(ICDeviceBrowser*)browser IC_AVAILABLE(macos(10.4));

@end

//-------------------------------------------------------------------------------------------------------------- ICDeviceBrowser
/*!
  @class ICDeviceBrowser
  @abstract The ICDeviceBrowser object is used to find devices such as digital cameras and scanners that are supported by Image Capture. These device may be directly attached to the USB or FireWire bus on the host computer, or available over a TCP/IP network. This object communicates with an Image Capture agent process asynchronously to accomplish this.
*/
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICDeviceBrowser : NSObject
{
@private
    id _privateData;
}

/*!
  @property delegate
  @abstract The delegate. It must conform to ICDeviceBrowserDelegate protocol. The messages this delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
@property (assign, nullable) id<ICDeviceBrowserDelegate> delegate;

/*!
  @property browsing
  @abstract Indicates whether the device browser is browsing for devices.
*/
@property (readonly, getter=isBrowsing) BOOL browsing;

/*!
  @property browsedDeviceTypeMask
  @abstract A mask whose set bits indicate the type of device(s) being browsed after the receiver receives the start message. This property can be changed while the browser is browsing for devices. This property can be constructed by OR'd values of ICDeviceTypeMask with values of ICDeviceLocationTypeMask.
*/
@property (readwrite) ICDeviceTypeMask browsedDeviceTypeMask IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property devices
  @abstract All devices found by the browser. This property will change as devices appear and disappear. This array is empty before the first invocation of the delegate method 'deviceBrowser:didAddDevice:moreComing:'.
*/
@property (readonly, nullable) NSArray<ICDevice*>* devices IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method preferredDevice
  @abstract This method returns a device object that should be selected by the client application when it is launched.
  @discussion If the client application that calls this method is the auto-launch application associated with a device and that device is the last device attached (through USB, FireWire or network), then that device will be the preferred device. The best place to call this method is in the implmentation of the ICDeviceBrowser delegate method "deviceBrowser:didAddDevice:moreComing:", if the "moreComing" parameter passed to the delegate is "NO"; or in the delegate method "deviceBrowserDidEnumerateLocalDevices:".
*/
- (nullable ICDevice*)preferredDevice IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method init
  @abstract This is the designated initializer.
*/
- (id)init IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method start:
  @abstract This message tells the receiver to start looking for devices.
  @discussion Make sure that the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. The messages the delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
- (void)start IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
  @method stop:
  @abstract This method tells the receiver to stop looking for devices.
  @discussion This will free all device instances that are not in use.
*/
- (void)stop IC_AVAILABLE(macos(10.4),ios(13.0));

@end

NS_ASSUME_NONNULL_END
// ==========  ImageCaptureCore.framework/Headers/ICDevice.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <CoreGraphics/CGImage.h>

@protocol ICDeviceDelegate;

//------------------------------------------------------------------------------------------------------------------------------
/*!
 @const ICDeviceType
 @abstract Image Capture Device Types
 @constant ICDeviceTypeCamera Camera device.
 @constant ICDeviceTypeScanner Scanner device.
 */

typedef NS_ENUM(NSUInteger, ICDeviceType)
{
    ICDeviceTypeCamera  = 0x00000001,
    ICDeviceTypeScanner = 0x00000002
} IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const ICDeviceLocationType
 @abstract Image Capture Device Location Types
 @constant ICDeviceLocationTypeLocal Device found directly attached to the Macintosh via its USB or FireWire port.
 @constant ICDeviceLocationTypeShared Device found over the network by searching for devices shared by other Macintosh hosts.
 @constant ICDeviceLocationTypeBonjour Device found over the network by searching for Bonjour services supported by Image Capture.
 @constant ICDeviceLocationTypeBluetooth Device found as a paired Bluetooth device.
 */
typedef NS_ENUM(NSUInteger, ICDeviceLocationType)
{
    ICDeviceLocationTypeLocal     = 0x00000100,
    ICDeviceLocationTypeShared    = 0x00000200,
    ICDeviceLocationTypeBonjour   = 0x00000400,
    ICDeviceLocationTypeBluetooth = 0x00000800
}  IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const ICDeviceTypeMask
 @abstract Image Capture Device Type Mask
 @constant ICDeviceTypeMaskCamera Mask to detect a camera device.
 @constant ICDeviceTypeMaskScanner Mask to detect a scanner device.
 */
typedef NS_ENUM(NSUInteger, ICDeviceTypeMask)
{
    ICDeviceTypeMaskCamera  = 0x00000001,
    ICDeviceTypeMaskScanner = 0x00000002
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const ICDeviceLocationTypeMask
 @abstract Image Capture Device Location Type Mask
 @constant ICDeviceLocationTypeMaskLocal Mask to detect a local (e.g., USB or FireWire) device.
 @constant ICDeviceLocationTypeMaskShared Mask to detect a device by another Macintosh host.
 @constant ICDeviceLocationTypeMaskBonjour Mask to detect a network device that publishes a Bonjour service.
 @constant ICDeviceLocationTypeMaskBluetooth Mask to detect paired Bluetooth device.
 @constant ICDeviceLocationTypeMaskRemote Mask to detect a remote (shared, Bonjour, Bluetooth) device.
 */
typedef NS_ENUM( NSUInteger, ICDeviceLocationTypeMask )
{
    ICDeviceLocationTypeMaskLocal     = 0x00000100,
    ICDeviceLocationTypeMaskShared    = 0x00000200,
    ICDeviceLocationTypeMaskBonjour   = 0x00000400,
    ICDeviceLocationTypeMaskBluetooth = 0x00000800,
    ICDeviceLocationTypeMaskRemote    = 0x0000FE00
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@class ICDevice,ICCameraDevice,NSError, NSDictionary, NSData, NSMutableDictionary;

CF_ASSUME_NONNULL_BEGIN

typedef NSString* ICDeviceTransport NS_TYPED_ENUM IC_AVAILABLE(macos(10.15), ios(13.0));

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify the transport type used by a device.

/*!
 @const      ICTransportTypeUSB
 @abstract   ICTransportTypeUSB
 @discussion Indicates that the device uses USB transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeUSB IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICTransportTypeFireWire
 @abstract   ICTransportTypeFireWire
 @discussion Indicates that the device uses FireWire transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeFireWire IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICTransportTypeBluetooth
 @abstract   ICTransportTypeBluetooth
 @discussion Indicates that the device uses Bluetooth transport.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeBluetooth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICTransportTypeMassStorage
 @abstract   ICTransportTypeMassStorage
 @discussion Indicates that the device use mounts as a mass-storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeMassStorage IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICTransportTypeExFAT
 @abstract   ICTransportTypeExFAT
 @discussion Indicates that the device use mounts as a exFat storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeExFAT IC_AVAILABLE(ios(10.0)) IC_UNAVAILABLE(macos);

/*!
 @const      ICTransportTypeTCPIP
 @abstract   ICTransportTypeTCPIP
 @discussion Indicates that the device uses TCP/IP transport. These devices are discovered using Bonjour.
 */
IMAGECAPTURE_EXTERN ICDeviceTransport const ICTransportTypeTCPIP IC_AVAILABLE(macos(10.4),ios(13.0));

typedef NSString* ICDeviceStatus NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
 @const      ICStatusNotificationKey
 @abstract   ICStatusNotificationKey
 @discussion Key for a non-localized notification string.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICStatusNotificationKey IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @const      ICStatusCodeKey
 @abstract   ICStatusCodeKey
 @discussion One of values defined in ICReturnCode.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICStatusCodeKey IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICLocalizedStatusNotificationKey
 @abstract   ICLocalizedStatusNotificationKey
 @discussion Key for a localized notification string.
 */
IMAGECAPTURE_EXTERN ICDeviceStatus const ICLocalizedStatusNotificationKey IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

typedef NSString* ICDeviceCapability NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a device
/*!
 @const      ICDeviceCanEjectOrDisconnect
 @abstract   ICDeviceCanEjectOrDisconnect
 @discussion Indicates either the device is mounted as a mass-storage volume and can be ejected or the it is a remote device with an active connection that can be disconnected.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICDeviceCanEjectOrDisconnect IC_AVAILABLE(macos(10.4), ios(13.0));

typedef NSString* ICSessionOptions NS_TYPED_ENUM IC_AVAILABLE(macos(10.15),ios(13.0));

IMAGECAPTURE_EXTERN ICSessionOptions const ICEnumerationChronologicalOrder IC_AVAILABLE(macos(10.15),ios(13.0));

typedef NSString* ICDeviceLocationOptions NS_TYPED_ENUM;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device location description.
/*!
 @const      ICDeviceLocationDescriptionUSB
 @abstract   ICDeviceLocationDescriptionUSB
 @discussion This description is returned for locationDescription property of a device connected to a USB port.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionUSB IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionFireWire
 @abstract   ICDeviceLocationDescriptionFireWire
 @discussion This description is returned for locationDescription property of a device connected to a FireWire port.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionFireWire IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionBluetooth
 @abstract   ICDeviceLocationDescriptionBluetooth
 @discussion This description is returned for locationDescription property of a device connected via Bluetooth.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionBluetooth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);
/*!
 @const      ICDeviceLocationDescriptionMassStorage
 @abstract   ICDeviceLocationDescriptionMassStorage
 @discussion This description is returned for locationDescription property of a device that is mounted as a mass-storage volume.
 */
IMAGECAPTURE_EXTERN ICDeviceLocationOptions const ICDeviceLocationDescriptionMassStorage IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//--------------------------------------------------------------------------------------------------------------------- ICDevice
/*!
 @class ICDevice
 @abstract ICDevice is an abstract class that represents a device supported by Image Capture facility. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICDevice : NSObject

/*!
 @property delegate
 @abstract The delegate to receive messages once a session is opened on the device. It must conform to ICDeviceDelegate protocol. In addition it should respond to selectors defined in ICCameraDeviceDelegate protocol in order to effectively interact with the device object. The messages this delegate can expect to receive are described by these protocols.
 */
@property (nonatomic, readwrite, assign, nullable) id <ICDeviceDelegate> delegate IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property type
 @abstract ￼The type of the device as defined by ICDeviceType OR'd with its ICDeviceLocationType. The type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceTypeMask. The location type of this device can be obtained by AND'ing the value retuned by this property with an appropriate ICDeviceLocationTypeMask.
 */
@property (nonatomic, readonly) ICDeviceType type IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property capabilities
 @abstract ￼The capabilities of the device as reported by the device module.
 */
@property (nonatomic, readonly) NSArray<NSString*>* capabilities IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property name
 @abstract ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device. This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.
 */
@property (nonatomic, readonly, copy, nullable) NSString* name IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property productKind
 @abstract ￼Type of the device. Possible values are: @"iPhone", @"iPod", @"Camera".
 */
@property (nonatomic, readonly, copy, nullable) NSString* productKind IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property icon
 @abstract ￼Icon image for the device.
 */
@property (nonatomic, readonly, nullable) CGImageRef icon IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property transportType
 @abstract ￼The transport type used by the device. The possible values are: ICTransportTypeUSB or ICTransportTypeMassStorage.
 */
@property (nonatomic, readonly, copy, nullable) NSString* transportType IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property UUIDString
 @abstract ￼A string representation of the Universally Unique ID of the device.
 */
@property (nonatomic, readonly, copy, nullable) NSString* UUIDString IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property locationDescription
 @abstract ￼A non-localized location description string for the device.
 @discussion The value returned in one of the location description strings defined above, or location obtained from the Bonjour TXT record of a network device.
 */
@property (nonatomic, readonly, nullable) NSString* locationDescription IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property hasOpenSession
 @abstract ￼Indicates whether the device has an open session.
 */
@property (nonatomic, readonly) BOOL hasOpenSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property userData
 @abstract ￼Client convenience bookkeeping object retained by the framework.
 */
@property (nonatomic, readonly, nullable) NSMutableDictionary* userData IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property modulePath
 @abstract ￼Filesystem path of the device module that is associated with this device. Camera-specific capabilities are defined in ICCameraDevice.h and scanner-specific capabilities are defined in ICScannerDevice.h.
 */
@property (nonatomic, readonly ) NSString* modulePath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property moduleVersion
 @abstract ￼The bundle version of the device module associated with this device. This may change if an existing device module associated with this device is updated or a new device module for this device is installed.
 */
@property (nonatomic, readonly, nullable) NSString* moduleVersion IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property serialNumberString
 @abstract ￼The serial number of the device. This will be NULL if the device does not provide a serial number.
 */
@property (nonatomic, readonly, nullable) NSString* serialNumberString IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property usbLocationID
 @abstract ￼The USB location of which the device is occupying.
 */
@property (nonatomic, readonly) int usbLocationID IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property usbProductID
 @abstract ￼The USB PID associated with the device attached.
 */
@property (nonatomic, readonly) int usbProductID IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @property usbVendorID
 @abstract ￼The USB VID associated with the device attached.
 */
@property (nonatomic, readonly) int usbVendorID IC_AVAILABLE(macos(10.4),ios(13.0));


#pragma mark - Delegate API

/*!
 @method requestOpenSession
 @abstract This message requests to open a session on the device.
 @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message. No more messages will be sent to the delegate if this request fails.
 */
- (void)requestOpenSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @method requestCloseSession
 @abstract This message requests to close a previously opened session on this device.
 @discussion This request is completed when the delegate receives a "device:didCloseSessionWithError:" message. This will be the last message sent to the delegate.
 */
- (void)requestCloseSession IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @method requestEject
 @abstract Eject the media if permitted by the device, or disconnect from a remote device.
 */
- (void)requestEject IC_AVAILABLE(macos(10.4), ios(13.0));

#pragma mark - Block API

/*!
 @method requestOpenSessionWithOptions:completion
 @abstract This message requests to open a session on the device.
 @discussion This request will execute the completion handler provided upon return.
 */
- (void)requestOpenSessionWithOptions:(NSDictionary<ICSessionOptions, id>*)options
                           completion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestCloseSessionWithOptions:completion
 @abstract This message requests to close a previously opened session on this device.
 @discussion This request will execute the completion handler provided upon return. This will be the last message sent to the delegate.
 */
- (void)requestCloseSessionWithOptions:(NSDictionary<ICSessionOptions, id>*)options
                            completion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method requestEjectWithCompletion:
 @abstract Eject the media, or disconnect the device - if permitted by the device.
 @discussion This request will execute the completion handler provided upon return.
 */
- (void)requestEjectWithCompletion:(void (^)(NSError* _Nullable error))completion IC_AVAILABLE(macos(10.15), ios(13.0));

#pragma mark - macOS only

/*!
 @property autolaunchApplicationPath
 @abstract ￼Filesystem path of an application that is to be automatically launched when this device is added.
 */
@property (nonatomic, readwrite, copy, nullable) NSString* autolaunchApplicationPath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property remote
 @abstract ￼Indicates whether the device is a remote device published by Image Capture device sharing facility.
 @property name
 @abstract ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device. This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.
 */
@property (readonly, getter=isRemote) BOOL remote IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property persistentIDString
 @abstract ￼A string representation of the persistent ID of the device.
 @method requestCloseSessionWithOptions
 @abstract This message requests to open a session on the device.
 @discussion This request will execute the completion handler provided upon return.
 */
@property (nonatomic, readonly, nullable) NSString* persistentIDString IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestSendMessage:outData:maxReturnDataSize:sendMessageDelegate:didSendMessageSelector:contextInfo:
 @abstract This method asynchronously sends an arbitrary message with optional data to a device.
 @discussion This method allows developers to send a private message from a client application to a device module. This method is the functional equivalent of calling ICAObjectSendMessage() found in ImageCaptureCore.framework, which has been deprecated in Mac OS X 10.6. The response to this command will be delivered using didSendMessageSelector of sendMessageDelegate. The didSendMessageSelector should have the same signature as: - (void)didSendMessage:(UInt32)messageCode inData:(NSData*)data error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully. NOTE: This method SHOULD NOT BE USED to send PTP pass-through commands to a PTP camera. Please refer to 'requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:' defined in ICCameraDevice.h for sending PTP pass-through commands.
 */
- (void)requestSendMessage:(unsigned int)messageCode outData:(NSData*)data maxReturnedDataSize:(unsigned int)maxReturnedDataSize sendMessageDelegate:(id)sendMessageDelegate didSendMessageSelector:(SEL)selector contextInfo:(void*)contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - Deprecated

/*!
 @method requestEjectOrDisconnect
 @abstract Eject the media if permitted by the device, or disconnect from a remote device.
 */
- (void)requestEjectOrDisconnect IC_DEPRECATED_WITH_REPLACEMENT("Use requestEject, or requestEjectWithCompletion:", macos(10.4,10.15)) IC_UNAVAILABLE(ios);

/*!
 @method requestYield
 @abstract This message requests the device module in control of this device to yield control.
 @discussion This message should be used only if the client is planning on communicating with the device directly. The device module may not yield control of the device if it has an open session.
 */
- (void)requestYield IC_DEPRECATED("Requesting a device yield is no longer avaialble", macos(10.4,10.15)) IC_UNAVAILABLE(ios);

/*!
 @method moduleExecutableArchitecture
 @abstract Reports the device module servicing the requests executable architecture.
 */
@property (readonly) int moduleExecutableArchitecture IC_DEPRECATED("Module executable architecture is no longer available",macos(10.4,10.15)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------------- ICDeviceDelegate
/*!
 @protocol ICDeviceDelegate <NSObject>
 @abstract A delegate of ICDevice must conform to ICDeviceDelegate protocol.
 */

@protocol ICDeviceDelegate <NSObject>

@required

/*!
 @method device:didCloseSessionWithError:
 @abstract This message is sent when a session is closed on a device.
 @discussion This message completes the process initiated by the message "requestCloseSession" sent to the device object. This message is also sent if the device module in control of the device ceases to control the device.
 */
- (void)device:(ICDevice*)device didCloseSessionWithError:(NSError*)error IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method didRemoveDevice:
 @abstract This message is sent to the delegate to inform that a device has been removed.
 */
- (void)didRemoveDevice:(ICDevice*)device IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didOpenSessionWithError:
 @abstract This message is sent when a session is opened on a device.
 @discussion This message completes the process initiated by the message "requestOpenSession" sent to the device object.
 */
- (void)device:(ICDevice*)device didOpenSessionWithError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

@optional

/*!
 @method deviceDidBecomeReady:
 @abstract This message is sent when the device is ready to receive requests.
 */
- (void)deviceDidBecomeReady:(ICDevice*)device IC_AVAILABLE(macos(10.4),ios(13.0));


/*!
 @method deviceDidChangeName:
 @abstract This message is sent if the name of a device changes.
 @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
 */
- (void)deviceDidChangeName:(ICDevice*)device IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method device:didReceiveStatusInformation:
 @abstract This message is sent to the device delegate when status information is received from a device.
 @discussion The 'status' dictionary contains two keys, ICStatusNotificationKey and ICLocalizedStatusNotificationKey, which are defined above.  Status information keys are located in their respective ICDevice type class header. */
- (void)device:(ICDevice*)device didReceiveStatusInformation:( NSDictionary<ICDeviceStatus,id>*)status IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didEncounterError:
 @abstract This message is sent to the device delegate a device encounters an error.
 */
- (void)device:(ICDevice*)device didEncounterError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

/*!
 @method device:didEjectWithError:
 @abstract This message is sent to the device delegate when the eject has completed.
 */
- (void)device:(ICDevice*)device didEjectWithError:(NSError* _Nullable) error IC_AVAILABLE(macos(10.4),ios(13.0));

#pragma mark - ICDeviceDelegate Deprecated

/*!
 @method deviceDidChangeSharingState:
 @abstract This message is sent when the sharing state of a device has changes.
 @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
 */
- (void)deviceDidChangeSharingState:(ICDevice*)device IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end



CF_ASSUME_NONNULL_END

// ==========  ImageCaptureCore.framework/Headers/ICCameraFolder.h
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraFolder.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICCameraItem.h>

CF_ASSUME_NONNULL_BEGIN

//--------------------------------------------------------------------------------------------------------------- ICCameraFolder
/*!
 @class ICCameraFolder
 @abstract This class represents a folder on an ICCameraDevice object.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraFolder : ICCameraItem
{
}

/*!
 @property contents
 @abstract ￼A list of items contained by this folder.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* contents IC_AVAILABLE(macos(10.4), ios(13.0));

@end

CF_ASSUME_NONNULL_END
