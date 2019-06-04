// ==========  FileProviderUI.framework/Headers/FileProviderUI.h
//
//  FileProviderUI.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionController.h>
#import <FileProviderUI/FPUIActionExtensionViewController.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>
// ==========  FileProviderUI.framework/Headers/FPUIBase.h
//
//  FPUIBase.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <TargetConditionals.h>

#define FPUI_EXPORT __attribute__((visibility("default")))
#define FPUI_AVAILABLE(...) FPUI_EXPORT API_AVAILABLE(__VA_ARGS__)
// ==========  FileProviderUI.framework/Headers/FPUIActionExtensionViewController.h
//
//  FPUIActionExtensionViewController.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <FileProviderUI/FPUIBase.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#if __has_include(<FileProvider/FileProvider.h>)
#import <FileProvider/FileProvider.h>
#else
typedef NSString *NSFileProviderItemIdentifier NS_EXTENSIBLE_STRING_ENUM;
#endif

#import <FileProviderUI/FPUIActionExtensionContext.h>

NS_ASSUME_NONNULL_BEGIN

FPUI_AVAILABLE(ios(11.0), macos(10.15))
#if TARGET_OS_OSX
@interface FPUIActionExtensionViewController : NSViewController
#else
@interface FPUIActionExtensionViewController : UIViewController
#endif

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

typedef NSString * FPUIActionIdentifier NS_EXTENSIBLE_STRING_ENUM;

typedef NS_ENUM(NSUInteger, FPUIExtensionErrorCode) {
    FPUIExtensionErrorCodeUserCancelled,
    FPUIExtensionErrorCodeFailed,
} API_AVAILABLE(ios(11.0)) __TVOS_UNAVAILABLE;


FPUI_AVAILABLE(ios(11.0), macos(10.15))
@interface FPUIActionExtensionContext : NSExtensionContext

@property (readonly, copy, nullable) NSFileProviderDomainIdentifier domainIdentifier;

/// The extension should call this method when the action did terminate successfully.
- (void)completeRequest;
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;


/// The extension should call this method when the action failed.
/// The error's Domain should be FPUIErrorDomain and the code should be a value of type FPUIErrorCode.
- (void)cancelRequestWithError:(NSError *)error;
    
@end

NS_ASSUME_NONNULL_END
// ==========  FileProviderUI.framework/Headers/FPUIActionExtensionController.h
//
//  FPUIActionExtensionController.h
//  FileProviderUI
//
//  Created by Rony Fadel on 3/21/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/FileProvider.h>
#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>

@class FPUIActionExtensionContext;

NS_ASSUME_NONNULL_BEGIN

FPUI_AVAILABLE(ios(13.0), macos(10.15))
@interface FPUIActionExtensionController : NSObject

@property (nonatomic, readonly, strong) FPUIActionExtensionContext *extensionContext;

// To be overridden by the subclass
- (NSProgress *_Nullable)performActionWithIdentifier:(FPUIActionIdentifier)actionIdentifier itemIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)itemIdentifiers NS_SWIFT_NAME( perform(_:itemIdentifiers:) );

@end

NS_ASSUME_NONNULL_END
