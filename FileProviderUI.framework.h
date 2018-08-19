// ==========  FileProviderUI.framework/Headers/FileProviderUI.h
//
//  FileProviderUI.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionViewController.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>
// ==========  FileProviderUI.framework/Headers/FPUIBase.h
//
//  DOCBase.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>

#define FPUI_EXPORT __attribute__((visibility("default")))
#define FPUI_AVAILABLE FPUI_EXPORT API_AVAILABLE(ios(11.0))
// ==========  FileProviderUI.framework/Headers/FPUIActionExtensionViewController.h
//
//  FPUIActionExtensionViewController.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <FileProvider/FileProvider.h>

#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>


NS_ASSUME_NONNULL_BEGIN

FPUI_AVAILABLE @interface FPUIActionExtensionViewController : UIViewController

@property (nonatomic, readonly, strong) FPUIActionExtensionContext *extensionContext;

// To be overridden by the subclass
- (void)prepareForError:(NSError *)error NS_SWIFT_NAME( prepare(forError:) );

// To be overridden by the subclass
- (void)prepareForActionWithIdentifier:(NSString *)actionIdentifier itemIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)itemIdentifiers NS_SWIFT_NAME( prepare(forAction:itemIdentifiers:) );
    
@end

NS_ASSUME_NONNULL_END
// ==========  FileProviderUI.framework/Headers/FPUIActionExtensionContext.h
//
//  FPUIActionExtensionContext.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <FileProvider/FileProvider.h>
#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>


NS_ASSUME_NONNULL_BEGIN

extern NSString *const FPUIErrorDomain API_AVAILABLE(ios(11.0)) __TVOS_UNAVAILABLE;

typedef NS_ENUM(NSUInteger, FPUIExtensionErrorCode) {
    FPUIExtensionErrorCodeUserCancelled,
    FPUIExtensionErrorCodeFailed,
} API_AVAILABLE(ios(11.0)) __TVOS_UNAVAILABLE;


FPUI_AVAILABLE @interface FPUIActionExtensionContext : NSExtensionContext

@property (readonly, copy, nullable) NSFileProviderDomainIdentifier domainIdentifier;

/// The extension should call this method when the action did terminate successfully.
- (void)completeRequest;
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;


/// The extension should call this method when the action failed.
/// The error's Domain should be FPUIErrorDomain and the code should be a value of type FPUIErrorCode.
- (void)cancelRequestWithError:(NSError *)error;
    
@end

NS_ASSUME_NONNULL_END
