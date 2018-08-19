// ==========  IntentsUI.framework/Headers/INUIAddVoiceShortcutViewController.h
//
//  INUIAddVoiceShortcutViewController.h
//  IntentsUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

@class INShortcut;
@class INVoiceShortcut;
@protocol INUIAddVoiceShortcutViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A view controller that will take the user through the setup flow to add a shortcut to Siri.
 @discussion First create the @c INShortcut object that represents the shortcut the user wants to perform. Then create an @c INUIAddVoiceShortcutViewController object and set its delegate. Then, present the view controller modally from another view controller in your app. The delegate must dismiss the view controller when the user completes the set up.
 */
API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, tvos)
@interface INUIAddVoiceShortcutViewController : UIViewController

@property (nonatomic, nullable, weak) id<INUIAddVoiceShortcutViewControllerDelegate> delegate;

/*!
 @param shortcut The shortcut is what will be run when the resulting voice shortcut is invoked. It also provides the suggested invocation phrase, via the @c suggestedInvocationPhrase property on the intent or user activity.
 */
- (instancetype)initWithShortcut:(INShortcut *)shortcut;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, tvos)
@protocol INUIAddVoiceShortcutViewControllerDelegate <NSObject>

/*!
 @abstract Called after the user finishes the setup flow for the voice shortcut, with either the successfully-added voice shortcut, or an error.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)addVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)controller didFinishWithVoiceShortcut:(nullable INVoiceShortcut *)voiceShortcut error:(nullable NSError *)error;

/*!
 @abstract Called if the user cancels the setup flow; the voice shortcut was not added.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)addVoiceShortcutViewControllerDidCancel:(INUIAddVoiceShortcutViewController *)controller;

@end

NS_ASSUME_NONNULL_END
// ==========  IntentsUI.framework/Headers/IntentsUI.h
//
//  IntentsUI.h
//  IntentsUI
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for IntentsUI.
FOUNDATION_EXPORT double IntentsUIVersionNumber;

//! Project version string for IntentsUI.
FOUNDATION_EXPORT const unsigned char IntentsUIVersionString[];

#import <IntentsUI/INImage+IntentsUI.h>
#import <IntentsUI/INUIAddVoiceShortcutButton.h>
#import <IntentsUI/INUIAddVoiceShortcutViewController.h>
#import <IntentsUI/INUIEditVoiceShortcutViewController.h>
#import <IntentsUI/INUIHostedViewControlling.h>
#import <IntentsUI/INUIHostedViewSiriProviding.h>
// ==========  IntentsUI.framework/Headers/INUIHostedViewSiriProviding.h
//
//  INUIHostedViewSiriProviding.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos, tvos)
@protocol INUIHostedViewSiriProviding <NSObject>

@optional

@property (nonatomic, assign, readonly) BOOL displaysMap;
@property (nonatomic, assign, readonly) BOOL displaysMessage;
@property (nonatomic, assign, readonly) BOOL displaysPaymentTransaction;

@end

NS_ASSUME_NONNULL_END

// ==========  IntentsUI.framework/Headers/INUIHostedViewControlling.h
//
//  INUIHostedViewControlling.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>

#import <Foundation/Foundation.h>

@class INInteraction;

@class INParameter;

typedef NS_ENUM(NSUInteger, INUIHostedViewContext) {
    INUIHostedViewContextSiriSnippet,
    INUIHostedViewContextMapsCard,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);

typedef NS_ENUM(NSUInteger, INUIInteractiveBehavior) {
    INUIInteractiveBehaviorNone,
    INUIInteractiveBehaviorNextView, // Show UI representing navigation to a new view, such as a navigation chevron
    INUIInteractiveBehaviorLaunch, // Show UI representing a launch to leave the context, such as a button
    INUIInteractiveBehaviorGenericAction, // Show UI representing a generic follow-on action within the context, such as a large tap target
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macosx, watchos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos, tvos)
@protocol INUIHostedViewControlling <NSObject>

@optional

/*!
 @abstract Perform configuration of UI based on the provided INInteraction object.
 @discussion When configuration is complete for the given interaction, the hosted view controller should call the completion block with its view's desired size. This size will be constrained between hostedViewMinimumAllowedSize and hostedViewMaximumAllowedSize of the extension context.
 
 @param  interaction The input interaction
 @param  context The hosting context for this interaction. The hosted view will be displayed alongside this context -- for instance, a Siri result snippet, or a place card within Maps.
 @param  completion The response handling block takes one parameter corresponding the optional desiredSize property of the INUIHostedViewControlling protocol
 
 @see  INInteraction
 */
- (void)configureWithInteraction:(INInteraction *)interaction context:(INUIHostedViewContext)context completion:(void (^)(CGSize desiredSize))completion;

/*!
 @abstract Perform configuration of UI based on the provided INInteraction and INParameter objects.
 @discussion When configuration is complete for the given parameters and interaction, the hosted view controller should call the completion block with whether it was successful, the parameters it configured itself with, and its view's desired size. The size of the view will ultimately be constrained between hostedViewMinimumAllowedSize and hostedViewMaximumAllowedSize of the extension context.
 
 @param  parameters The parameters of the interaction for which to configure the view
 @param  interaction The input interaction
 @param  interactiveBehavior The behavior that will be driven by user interaction of this view
 @param  context The hosting context for this interaction. The hosted view will be displayed within/alongside this context -- for instance, a Siri result snippet, or a place card within Maps.
 @param  completion The response handling block takes the following: A) a success boolean, which tells the hosted view context if this view was successfully configured, B) the set of parameters that this view was successfully configured for, and C) a desiredSize for this view to be sized at within the hosted view context.
 
 @see  INParameter
 @see  INInteraction
 */
- (void)configureViewForParameters:(NSSet <INParameter *> *)parameters ofInteraction:(INInteraction *)interaction interactiveBehavior:(INUIInteractiveBehavior)interactiveBehavior context:(INUIHostedViewContext)context completion:(void (^)(BOOL success, NSSet <INParameter *> *configuredParameters, CGSize desiredSize))completion API_AVAILABLE(ios(11.0));

@end

@interface NSExtensionContext (INUIHostedViewControlling)

@property (nonatomic, assign, readonly) CGSize hostedViewMinimumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);
@property (nonatomic, assign, readonly) CGSize hostedViewMaximumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);

- (NSString *)interfaceParametersDescription API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macosx, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  IntentsUI.framework/Headers/INUIEditVoiceShortcutViewController.h
//
//  INUIEditVoiceShortcutViewController.h
//  IntentsUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

@class INVoiceShortcut;
@protocol INUIEditVoiceShortcutViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A view controller that shows the details of a voice shortcut, and lets the user edit the phrase.
 @discussion To have the user edit a voice shortcut, create an @c INUIEditVoiceShortcutViewController object with the @c INVoiceShortcut that they wish to edit, and set its delegate. Then, present the view controller modally from another view controller in your app. Your delegate must dismiss the view controller when the user finishes editing.
 */
API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, tvos)
@interface INUIEditVoiceShortcutViewController : UIViewController

@property (nonatomic, nullable, weak) id<INUIEditVoiceShortcutViewControllerDelegate> delegate;

/*!
 @param voiceShortcut The voice shortcut to be edited.
 */
- (instancetype)initWithVoiceShortcut:(INVoiceShortcut *)voiceShortcut;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, tvos)
@protocol INUIEditVoiceShortcutViewControllerDelegate <NSObject>

/*!
 @abstract Called if the user updates the voice shortcut, with either the successfully-updated voice shortcut, or an error.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)controller didUpdateVoiceShortcut:(nullable INVoiceShortcut *)voiceShortcut error:(nullable NSError *)error;

/*!
 @abstract Called if the user deletes the voice shortcut.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)controller didDeleteVoiceShortcutWithIdentifier:(NSUUID *)deletedVoiceShortcutIdentifier;

/*!
 @abstract Called if the user cancelled; no changes were made to the voice shortcut.
 @discussion Your implementation of this method should dismiss the view controller.
 */
- (void)editVoiceShortcutViewControllerDidCancel:(INUIEditVoiceShortcutViewController *)controller;

@end

NS_ASSUME_NONNULL_END
// ==========  IntentsUI.framework/Headers/INImage+IntentsUI.h
//
//  INImage+IntentsUI.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Intents/INImage.h>

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@class INIntentResponse;

NS_ASSUME_NONNULL_BEGIN

@interface INImage (IntentsUI)

+ (instancetype)imageWithCGImage:(CGImageRef)imageRef API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);
+ (instancetype)imageWithUIImage:(UIImage *)image API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

/*!
 @abstract Returns the image size at which the image for an INIntentResponse will be displayed
 */
+ (CGSize)imageSizeForIntentResponse:(INIntentResponse *)response API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

- (void)fetchUIImageWithCompletion:(void (^)(UIImage * _Nullable image))completion API_AVAILABLE(ios(11.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  IntentsUI.framework/Headers/INUIAddVoiceShortcutButton.h
//
//  INUIAddVoiceShortcutButton
//  IntentsUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, INUIAddVoiceShortcutButtonStyle) {
    INUIAddVoiceShortcutButtonStyleWhite = 0,
    INUIAddVoiceShortcutButtonStyleWhiteOutline,
    INUIAddVoiceShortcutButtonStyleBlack,
    INUIAddVoiceShortcutButtonStyleBlackOutline
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macosx, tvos);

@class INShortcut, INUIAddVoiceShortcutButton, INUIAddVoiceShortcutViewController, INUIEditVoiceShortcutViewController;

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@protocol INUIAddVoiceShortcutButtonDelegate <NSObject>

- (void)presentAddVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)addVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;
- (void)presentEditVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)editVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@interface INUIAddVoiceShortcutButton : UIButton

- (instancetype)initWithStyle:(INUIAddVoiceShortcutButtonStyle)style;

@property (nonatomic, readonly) INUIAddVoiceShortcutButtonStyle style;

@property (nonatomic, weak) id<INUIAddVoiceShortcutButtonDelegate> delegate;
@property (nonatomic, strong, nullable) INShortcut *shortcut;

@end

NS_ASSUME_NONNULL_END
