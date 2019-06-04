// ==========  CarPlay.framework/Headers/CPTrip.h
//
//  CPTrip.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPRouteChoice describes a possible route for a @c CPTrip.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPRouteChoice : NSObject <NSCopying, NSSecureCoding>

/**
 Initialize a @c CPRouteChoice with summary variants, additional information variants, and selection summary variants.
 The variant strings should be provided as localized, displayable content.
 */
- (instancetype)initWithSummaryVariants:(NSArray<NSString *> *)summaryVariants additionalInformationVariants:(NSArray<NSString *> *)additionalInformationVariants selectionSummaryVariants:(NSArray<NSString *> *)selectionSummaryVariants NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 summaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Example: "Via I-280 S"
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *summaryVariants;

/**
 selectionSummaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space.
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *selectionSummaryVariants;

/**
 additionalInformationVariants is an array of additional information variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Examples: "Fastest Route", "Avoids Tolls"
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *additionalInformationVariants;

/**
 Any custom user info related to this route choice.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

/**
 @c CPTrip represents an origin and destination with route choices.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTrip : NSObject <NSSecureCoding>

/**
 Initialize a @c CPTrip with an origin item, destination item, and route choices.
 */
- (instancetype)initWithOrigin:(MKMapItem *)origin destination:(MKMapItem *)destination routeChoices:(NSArray<CPRouteChoice *> *)routeChoices NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 @c MKMapItem representing the origin for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *origin;

/**
 @c MKMapItem representing the destination for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *destination;

/**
 Array of @c CPRouteChoices for the trip.
 */
@property (nonatomic, readonly, copy) NSArray<CPRouteChoice *> *routeChoices;

/**
 Any custom user info related to this trip.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPVoiceControlTemplate.h
//
//  CPVoiceControlTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPVoiceControlState encapsulates the title variants and image(s) for a single voice control
 state, like listening, loading, or recognized.

 Your app may initialize the voice control template with one or more states, and
 you may call @c activateVoiceControlState: to switch between states you've defined.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPVoiceControlState : NSObject <NSSecureCoding>

/**
 Initialize a voice control state with a title and image.

 @param identifier A custom identifier you can use to identify this voice control state. You'll also
 switch to this state by specifying this identifier.
 @param titleVariants An array of title variants. The Voice Control template will select the longest
 variant that fits your specified content.
 @param image An image to be animated while this template is visible. The system
 enforces a minimum cycle duration of 0.3 seconds and a maximum cycle duration of 5 seconds.
 Voice Control state images may be a maximum of 150 by 150 points.
 @param repeats For an animated image, YES if the animation should repeat indefinitely, NO
 to run the animation only once.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                     titleVariants:(nullable NSArray <NSString *> *)titleVariants
                             image:(nullable UIImage *)image
                           repeats:(BOOL)repeats;

@property (nullable, nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;

@property (nullable, nonatomic, readonly, strong) UIImage *image;

@property (nonatomic, readonly, copy) NSString *identifier;

@property (nonatomic, readonly) BOOL repeats;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPVoiceControlTemplate : CPTemplate

/**
 Initialize a voice control template with a list of voice control states.

 @param voiceControlStates An array of voice control states for this template. Your app can switch between these states after the template is presented.

 @note By default, the Voice Control template will begin on the first state specified.

 @warning You may specify a maximum of 5 voice control states. If you specify more than 5, only the first 5 will be available.
 */
- (instancetype)initWithVoiceControlStates:(NSArray <CPVoiceControlState *> *)voiceControlStates;

@property (nonatomic, readonly, copy) NSArray <CPVoiceControlState *> *voiceControlStates;

/**
 Switch the voice control template to the state corresponding with a particular identifier.

 @param identifier An identifier corresponding to one of the voice control states used to initialize this template.

 @note The Voice Control template applies a rate-limit for voice control states; the template will
 ignore voice control state changes that occur too rapidly or frequently in a short period of time.

 @warning You must first present this voice control template through your @c CPInterfaceController before
 activating a voice control state, otherwise this method will have no effect.
 When the Voice Control template is first presented, the first state you specify in
 @c initWithVoiceControlStates: will be visible.
 */
- (void)activateVoiceControlStateWithIdentifier:(NSString *)identifier;

/**
 The currently-active voice control state identifier.
 */
@property (nonatomic, readonly, copy, nullable) NSString *activeStateIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPManeuver.h
//
//  CPManeuver.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPImageSet.h>
#import <Foundation/Foundation.h>
#import <CarPlay/CPTravelEstimates.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPManeuver describes a navigation instruction.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPManeuver : NSObject <NSCopying, NSSecureCoding>

/**
 symbolSet is a @c CPImageSet representing the maneuver.
 */
@property (nullable, nonatomic, strong) CPImageSet *symbolSet API_DEPRECATED_WITH_REPLACEMENT("symbolImage", ios(12.0, 13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 symbolImage is a @c UIImage representing the maneuver. Provide variants for UIUserInterfaceStyleLight and UIUserInterfaceStyleDark that will be used against light backgrounds and dark backgrounds.
 */
@property (nullable, nonatomic, strong) UIImage *symbolImage;

/**
 junctionImage is a @c UIImage used to display a junction for the maneuver.
 
 @note The maximum image size is 140 points by 100 points. If necessary, images will be scaled down to fit while maintaining the aspect ratio.
 */
@property (nullable, nonatomic, strong) UIImage *junctionImage;

/**
 instructionVariants is an array of @c NSString representing the instruction for this maneuver, arranged from most to least preferred. You must provide at least one variant.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, copy) NSArray<NSString *> *instructionVariants;

/**
   initialTravelEstimates represents the estimates beginning from the end of the preceding maneuver.
*/
@property (nullable, nonatomic, strong) CPTravelEstimates *initialTravelEstimates;

/**
 attributedInstructionVariants is an array of @c NSAttributedString representing the instruction for this maneuver,
 arranged from most to least preferred.
 
 @c attributedInstructionVariants will be preferred over instructionVariants. You must provide at least one variant for each maneuver.
 
 Only one attribute is presently supported: text attachments. You may annotate a maneuver instruction with an image
 by including a text attachment. The maximum text attachment image size is 64x16 points.

 @warning All attributes other than text attachment attributes will be removed from your attributed string.

 @see +[NSAttributedString attributedStringWithAttachment:], -[NSTextAttachment image]
 */
@property (nonatomic, copy) NSArray<NSAttributedString *> *attributedInstructionVariants;

/**
 Any custom user info related to this maneuver.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPMapButton.h
//
//  CPMapButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMapButton : NSObject <NSSecureCoding>

/**
 Initializes a new map button.

 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.
 */
- (instancetype)initWithHandler:(void (^ _Nullable)(CPMapButton *mapButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 A Boolean value indicating whether the button is hidden.

 @discussion Setting the value of this property to @c YES hides the button and setting it to @c NO shows it. The default value is @c NO.
 */
@property (nonatomic, assign, getter=isHidden) BOOL hidden;

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nullable, nonatomic, strong) UIImage *image;

/**
 The image displayed on the button when focused.

 @discussion The button will automatically create a focused image using the alpha values from the source image.

 @note If unspecified, the button will use the default @c image
 */
@property (nullable, nonatomic, strong) UIImage *focusedImage;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPTripPreviewTextConfiguration.h
//
//  CPTripPreviewTextConfiguration.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTripPreviewTextConfiguration : NSObject <NSSecureCoding>

- (instancetype)initWithStartButtonTitle:(nullable NSString *)startButtonTitle
             additionalRoutesButtonTitle:(nullable NSString *)additionalRoutesButtonTitle
                     overviewButtonTitle:(nullable NSString *)overviewButtonTitle;

@property (nonatomic, copy, readonly, nullable) NSString *startButtonTitle;
@property (nonatomic, copy, readonly, nullable) NSString *additionalRoutesButtonTitle;
@property (nonatomic, copy, readonly, nullable) NSString *overviewButtonTitle;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPListSection.h
//
//  CPListSection.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListItem.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPListSection models a single section of items appearing in a @c CPListTemplate.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListSection : NSObject <NSSecureCoding>

/**
 Create a section with a list of items and an optional header and identifier.
 */
- (instancetype)initWithItems:(NSArray<CPListItem *> *)items
                       header:(nullable NSString *)header
            sectionIndexTitle:(nullable NSString *)sectionIndexTitle;

/**
 Create a section by specifying a list of items.
 */
- (instancetype)initWithItems:(NSArray <CPListItem *> *)items;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Optional string to use for a header in this section.
 */
@property (nullable, nonatomic, readonly, copy) NSString *header;

/**
 An optional section index title to use in a table displaying this section.
 The system will enforce a maximum length of 1 for each section index title - in other words,
 you must choose single-character section index titles.
 */
@property (nullable, nonatomic, readonly, copy) NSString *sectionIndexTitle;

/**
 Items appearing in this section.
 */
@property (nonatomic, readonly, copy) NSArray <CPListItem *> *items;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CarPlay.h
//
//  CarPlay.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <CarPlay/CPActionSheetTemplate.h>
#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPAlertTemplate.h>
#import <CarPlay/CPBarButton.h>
#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPGridButton.h>
#import <CarPlay/CPGridTemplate.h>
#import <CarPlay/CPImageSet.h>
#import <CarPlay/CPInterfaceController.h>
#import <CarPlay/CPListItem.h>
#import <CarPlay/CPListSection.h>
#import <CarPlay/CPListTemplate.h>
#import <CarPlay/CPManeuver.h>
#import <CarPlay/CPMapButton.h>
#import <CarPlay/CPMapTemplate.h>
#import <CarPlay/CPNavigationAlert.h>
#import <CarPlay/CPNavigationSession.h>
#import <CarPlay/CPSearchTemplate.h>
#import <CarPlay/CPSessionConfiguration.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPTravelEstimates.h>
#import <CarPlay/CPTrip.h>
#import <CarPlay/CPTripPreviewTextConfiguration.h>
#import <CarPlay/CPVoiceControlTemplate.h>
// ==========  CarPlay.framework/Headers/CPInterfaceController.h
//
//  CPInterfaceController.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertTemplate.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPWindow.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class CPManeuver, CPNavigationAlert;
@protocol CPInterfaceControllerDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPInterfaceController : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 The delegate for this interface controller.
 */
@property (nonatomic, weak) id<CPInterfaceControllerDelegate> delegate;

/**
 Set the preferred interface style to UIUserInterfaceStyleDark for all templates. Set this value to YES prior to setting a root template
 or pushing any templates for first appearance to have style UIUserInterfaceStyleDark.
 */
@property (nonatomic, assign) BOOL prefersDarkUserInterfaceStyle API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

#pragma mark - Templates

/**
 Set the root template. If no existing templates exist in the template navigation hierarchy, the animated flag will be ignored.
 If there is an existing template navigation hierarchy, the existing stack will be replaced by the new root template.
 */
- (void)setRootTemplate:(__kindof CPTemplate *)rootTemplate animated:(BOOL)animated;

/**
 Push a new template onto the template navigation hierarchy, showing it immediately.
 */
- (void)pushTemplate:(__kindof CPTemplate *)templateToPush animated:(BOOL)animated;

/**
 Pop back a single level in the template navigation hierarchy.
 */
- (void)popTemplateAnimated:(BOOL)animated;

/**
 Pop back to the first template in the template navigation hierarchy.
 */
- (void)popToRootTemplateAnimated:(BOOL)animated;

/**
 Pop back to a specified template.
 
 targetTemplate must exist in the current template navigation hierarchy.
 */
- (void)popToTemplate:(__kindof CPTemplate *)targetTemplate animated:(BOOL)animated;

/**
 Present a template modally over the navigation hierarchy. Only one template may be presented at a time.

 @note Supported template types: @c CPActionSheetTemplate, @c CPAlertTemplate, @c CPVoiceControlTemplate
 */
- (void)presentTemplate:(__kindof CPTemplate *)templateToPresent animated:(BOOL)animated;

/**
 Dismiss the current modally-presented template, optionally animating the dismissal.

 @note If there is no current modally-presented template, this method will have no effect.
 */
- (void)dismissTemplateAnimated:(BOOL)animated;

/**
 The current modally-presented template.

 @warning Reading this property may synchronously perform an IPC call to retrieve the current presented template.
 */
@property (nonatomic, readonly, nullable) __kindof CPTemplate *presentedTemplate;

/**
 Returns the root template.
 */
@property (nonatomic, readonly) __kindof CPTemplate *rootTemplate;

/**
 The top template in the navigation hierarchy.

 @warning Reading this property may synchronously perform an IPC call to retrieve the current top-most template.
 */
@property (nullable, nonatomic, readonly, strong) CPTemplate *topTemplate;

/**
 The current stack of templates in the navigation hierarchy.

 @warning Reading this property may synchronously perform an IPC call to retrieve the current stack of templates.
 */
@property (nonatomic, readonly, strong) NSArray<CPTemplate *> *templates;

@end


/**
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPInterfaceControllerDelegate <NSObject>

@optional

- (void)templateWillAppear:(CPTemplate *)aTemplate animated:(BOOL)animated;
- (void)templateDidAppear:(CPTemplate *)aTemplate animated:(BOOL)animated;
- (void)templateWillDisappear:(CPTemplate *)aTemplate animated:(BOOL)animated;
- (void)templateDidDisappear:(CPTemplate *)aTemplate animated:(BOOL)animated;

@end


/**
 A set of methods that are called by the @c UIApplication singleton in response to CarPlay lifecycle events.

 @discussion This must be implemented by the same object that serves as your application's delegate object.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPApplicationDelegate <UIApplicationDelegate>

@required

/**
 The CarPlay screen has connected and is ready to present content.

 Your app should create its view controller and assign it to the @c rootViewController property
 of this window.

 @note It is the responsibility of the delegate to maintain a reference to the interface controller beyond the scope of this method.
 */
- (void)application:(UIApplication *)application didConnectCarInterfaceController:(CPInterfaceController *)interfaceController toWindow:(CPWindow *)window;

/**
 The CarPlay screen has disconnected.
 */
- (void)application:(UIApplication *)application didDisconnectCarInterfaceController:(CPInterfaceController *)interfaceController fromWindow:(CPWindow *)window;

@optional

/**
 If your application posts a @c CPNavigationAlert while backgrounded, a notification banner may be presented to the user.
 If the user taps on that banner, your application will launch on the car screen and this method will be called
 with the alert the user tapped.
 */
- (void)application:(UIApplication *)application didSelectNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 If your application posts a @c CPManeuver while backgrounded, a notification banner may be presented to the user.
 If the user taps on that banner, your application will launch on the car screen and this method will be called
 with the maneuver the user tapped.
 */
- (void)application:(UIApplication *)application didSelectManeuver:(CPManeuver *)maneuver;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPGridButton.h
//
//  CPGridButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPGridButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a button with a title and image.

 @param titleVariants An array of title variants for this button, arranged from most to least preferred. You must provide at least one title.
 @param image The image displayed on the button. It must be non-nil for the button to be displayed.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.

 The image must be non-nil and the title must be a non-zero length string for the button to be displayed.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants image:(UIImage *)image handler:(void (^ _Nullable)(CPGridButton *barButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nonatomic, readonly) UIImage *image;

/**
 An array of title variants for this button, arranged from most to least preferred.
 The system will select a title from your list of provided variants that fits the available space.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray <NSString *> *titleVariants;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPMapTemplate.h
//
//  CPMapTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//


#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPMapButton.h>
#import <CarPlay/CPNavigationAlert.h>
#import <CarPlay/CPNavigationSession.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPTrip.h>
#import <CarPlay/CPTripPreviewTextConfiguration.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, CPPanDirection) {
    CPPanDirectionNone = 0,
    CPPanDirectionLeft = 1 << 0,
    CPPanDirectionRight = 1 << 1,
    CPPanDirectionUp = 1 << 2,
    CPPanDirectionDown = 1 << 3,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_OPTIONS(NSInteger, CPManeuverDisplayStyle) {
    CPManeuverDisplayStyleDefault,
    CPManeuverDisplayStyleLeadingSymbol,
    CPManeuverDisplayStyleTrailingSymbol,
    CPManeuverDisplayStyleSymbolOnly,
    CPManeuverDisplayStyleInstructionOnly
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ENUM(NSUInteger, CPTimeRemainingColor) {
    CPTimeRemainingColorDefault = 0,
    CPTimeRemainingColorGreen,
    CPTimeRemainingColorOrange,
    CPTimeRemainingColorRed,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ENUM(NSUInteger, CPTripEstimateStyle) {
    CPTripEstimateStyleLight = 0,
    CPTripEstimateStyleDark
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

@protocol CPMapTemplateDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMapTemplate : CPTemplate <CPBarButtonProviding>

/**
 Background color to use when displaying guidance. The system will automatically determine if the provided
 color meets contrast requirements. If the provided color does not meet contrast requirements, the system
 default will be used. Font color will automatically be adjusted by the system to correspond with this color.
 Alpha values will be ignored.
 */
@property (nonatomic, strong) UIColor *guidanceBackgroundColor;

/**
 The style used to display trip estimates during active navigation. If not set, will update automatically with changes to UIUserInterfaceStyle.
 */
@property (nonatomic, assign) CPTripEstimateStyle tripEstimateStyle;

/**
 An array of bar buttons to be displayed on the trailing bottom corner of the map template.
 @note The map template may display a maximum of 4 buttons. Setting more than 4 buttons to this
 property will only display the first 4 buttons.
 */
@property (nonatomic, strong) NSArray<CPMapButton *> *mapButtons;

/**
 * Display a preview for a trip. Used to provide an overview for the upcoming trip or can show multiple trip options,
 * such as for search results. Trip previews can appear over an active navigation session. Number of trips will be
 * limited to 12.
 */
- (void)showTripPreviews:(NSArray<CPTrip *> *)tripPreviews textConfiguration:(nullable CPTripPreviewTextConfiguration *)textConfiguration;

/**
 * Display the route choices for a single trip. Trip previews can appear over an active navigation session.
 */
- (void)showRouteChoicesPreviewForTrip:(CPTrip *)tripPreview textConfiguration:(nullable CPTripPreviewTextConfiguration *)textConfiguration;

/**
 * Stop displaying any currently shown trip previews.
 */
- (void)hideTripPreviews;

/**
 * Updates the arrival time, time remaining and distance remaining estimates for a trip preview or actively navigating trip with the default color for time remaining.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forTrip:(CPTrip *)trip;

/**
 * Updates the arrival time, time remaining and distance remaining estimates for a trip preview or actively navigating trip with a specified color for time remaining.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forTrip:(CPTrip *)trip withTimeRemainingColor:(CPTimeRemainingColor)timeRemainingColor;

/**
 * Begins guidance for a trip.
 @return CPNavigationSession maintain a reference to the navigation session to perform guidance updates
 */
- (CPNavigationSession *)startNavigationSessionForTrip:(CPTrip *)trip;

/**
 Automatically shows and hides the navigation bar. Defaults to YES.
 */
@property (nonatomic, assign) BOOL automaticallyHidesNavigationBar;

/**
 Hides the map buttons when hiding the navigation bar. Defaults to YES.
 */
@property (nonatomic, assign) BOOL hidesButtonsWithNavigationBar;

@property (nullable, nonatomic, weak) id<CPMapTemplateDelegate> mapDelegate;


#pragma mark - Panning

/**
 Shows the panning interface on the map interface if not already visible.

 When showing the panning interface, a maximum of two mapButtons will be visible.
 If more than two mapButtons are visible when the template transitions to panning mode,
 the system will hide one or more map buttons beginning from the end of the mapButtons array.

 @note The system will not provide a button to dismiss the UI. You are required to provide
 a button in the map template navigation bar that will dismiss the panning interface.
 */
- (void)showPanningInterfaceAnimated:(BOOL)animated;

/**
 Dismisses the panning interface on the map interface if it is visible.
 @note When dismissing the panning interface, mapButtons previously hidden by the system will no longer be hidden.
 */
- (void)dismissPanningInterfaceAnimated:(BOOL)animated;

/**
 Returns YES when the panning interface is visible.
 */
@property (nonatomic, readonly, getter=isPanningInterfaceVisible) BOOL panningInterfaceVisible;

#pragma mark - Navigation Alerts

/**
 The currently-visible navigation alert, if any.
 */
@property (nullable, nonatomic, readonly, strong) CPNavigationAlert *currentNavigationAlert;

/**
 Display a navigation alert on this map template. Your @c CPMapTemplateDelegate will be notified
 of navigation alert lifecycle events.

 @param navigationAlert The navigation alert to display.
 @param animated YES to animate the presentation of this alert, or NO to display it immediately.

 @warning If a navigation alert is already visible, this method has no effect.
 You must dismiss the currently-visible navigation alert before presenting a new alert.
 */
- (void)presentNavigationAlert:(CPNavigationAlert *)navigationAlert animated:(BOOL)animated;

/**
 Dismiss the currently-visible navigation alert on this map template.

 @param animated Whether the dismissal should be animated (YES) or not (NO).
 @param completion A block invoked after the alert has been dismissed. The BOOL argument
 in the completion block indicates whether any visible alert was dismissed (YES) or
 if no action was taken because there was no alert to dismiss (NO).
 */
- (void)dismissNavigationAlertAnimated:(BOOL)animated completion:(void (^)(BOOL dismissed))completion;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPMapTemplateDelegate <NSObject>
@optional

#pragma mark - Notification Policy
/**
 Determines if the maneuver should be presented as a notification when the app is in the background.
 @return YES if the maneuver should appear as a notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldShowNotificationForManeuver:(CPManeuver *)maneuver;

/**
 Determines if the updated distance remaining for the maneuver should be presented as a notification when the app is in the background.
  @return YES if the updated estimates should appear in the notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldUpdateNotificationForManeuver:(CPManeuver *)maneuver withTravelEstimates:(CPTravelEstimates *)travelEstimates;

/**
 Determines if the navigation alert should be presented as a notification when the app is in the background.
  @return YES if the alert should appear as a notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldShowNotificationForNavigationAlert:(CPNavigationAlert *)navigationAlert;

#pragma mark - Panning
/**
 This will be called when the pan interface appears on the map interface.
 */
- (void)mapTemplateDidShowPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 This will be called when the pan interface will disappear on the map interface.
 */
- (void)mapTemplateWillDismissPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 This will be called when the pan interface disappears on the map interface.
 */
- (void)mapTemplateDidDismissPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 Called when a pan button is pressed/selected for an extended duration.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panBeganWithDirection:(CPPanDirection)direction;

/**
 Called when a pan button is released after an extended duration.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panEndedWithDirection:(CPPanDirection)direction;

/**
 Called when a pan button is pressed/selected momentarily.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panWithDirection:(CPPanDirection)direction;

/**
 Called when a pan gesture begins. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplateDidBeginPanGesture:(CPMapTemplate *)mapTemplate;

/**
 Called when a pan gesture changes. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didUpdatePanGestureWithTranslation:(CGPoint)translation velocity:(CGPoint)velocity;

/**
 Called when a pan gesture ends. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didEndPanGestureWithVelocity:(CGPoint)velocity;

#pragma mark - Alerts

/**
 Called when the map interface is about to display a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate willShowNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 Called when the map interface has displayed a navigation alert.

 To take action in response to button presses on the navigation alert, see -[CPAlertAction handler].
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didShowNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 Called when the map interface is preparing to dismiss a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate willDismissNavigationAlert:(CPNavigationAlert *)navigationAlert dismissalContext:(CPNavigationAlertDismissalContext)dismissalContext;

/**
 Called when the map interface has completed dismissal of a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didDismissNavigationAlert:(CPNavigationAlert *)navigationAlert dismissalContext:(CPNavigationAlertDismissalContext)dismissalContext;


#pragma mark - Trips

/**
 Called when the user has selected a route choice to preview.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate selectedPreviewForTrip:(CPTrip *)trip usingRouteChoice:(CPRouteChoice *)routeChoice;

/**
 Called when the user has selected a route choice to navigate.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate startedTrip:(CPTrip *)trip usingRouteChoice:(CPRouteChoice *)routeChoice;

/**
 Called when navigation has been canceled by the system.
 
 @note In CarPlay systems that have native navigation, it is expected that only either the native navigation or the iPhone
 can be actively navigating. When navigation begins in the native system, all CarPlay supported navigation
 apps that are actively navigating will need to end their navigation session.
 */
- (void)mapTemplateDidCancelNavigation:(CPMapTemplate *)mapTemplate;

#pragma mark - Display Style
/**
 Changes the visual layout of the maneuver.
 @return a CPManeuverDisplayStyle value representing the style to be used for displaying the maneuver
 */
- (CPManeuverDisplayStyle)mapTemplate:(CPMapTemplate *)mapTemplate displayStyleForManeuver:(CPManeuver *)maneuver;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPNavigationSession.h
//
//  CPNavigationSession.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPManeuver.h>
#import <CarPlay/CPTravelEstimates.h>
#import <CarPlay/CPTrip.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPTripPauseReason) {
    CPTripPauseReasonArrived          = 1,
    CPTripPauseReasonLoading          = 2,
    CPTripPauseReasonLocating         = 3,
    CPTripPauseReasonRerouting        = 4,
    CPTripPauseReasonProceedToRoute   = 5,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 @c CPNavigationSession represents the active navigation session. A @c CPNavigationSession will be created for you
 when calling startNavigationSessionForTrip: on @c CYMapTemplate
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNavigationSession : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Pause the current trip.
 
 @param reason The reason navigation was paused.
 @param description An optional description of the pause reason. If @c nil, a system-provided string will be used.
 */
- (void)pauseTripForReason:(CPTripPauseReason)reason description:(nullable NSString *)description;

/**
 Finish the trip.
 */
- (void)finishTrip;

/**
 Cancel the trip.
 */
- (void)cancelTrip;

/**
 The next maneuvers that should be performed to follow the current route.
 Multiple maneuvers are displayed simultaneously, however the system may limit the number of maneuvers shown at the same time.
 */
@property (nonatomic, readwrite, copy) NSArray<CPManeuver *> *upcomingManeuvers;

/**
 The trip associated with this navigation session.
 */
@property (nonatomic, readonly, strong) CPTrip *trip;

/**
 Update the travel estimates for the active navigation session and maneuver.
 
 @param estimates The updated travel estimates.
 @param maneuver The maneuver pertaining to this update.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forManeuver:(CPManeuver *)maneuver;


@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPAlertTemplate.h
//
//  CPAlertTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPAlertTemplate represents a modal alert that must be dismissed with a button press
 before the user may return to using the app.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPAlertTemplate : CPTemplate

/**
 Initialize a @c CPAlertTemplate by specifying a list of title variants and at least one action.

 @param titleVariants a list of title variants
 @param actions the alert actions

 */
- (instancetype)initWithTitleVariants:(NSArray<NSString *> *)titleVariants
                              actions:(NSArray <CPAlertAction *> *)actions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, readonly) NSArray<NSString *> *titleVariants;

#pragma mark - Actions

@property (nonatomic, strong, readonly) NSArray <CPAlertAction *> *actions;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPWindow.h
//
//  CPWindow.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class CPTemplateApplicationScene;

/**
 @c CPWindow is the main window for content presented on the car screen.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPWindow : UIWindow

/**
 @c mapButtonSafeAreaLayoutGuide can be used to layout content that appears above the map buttons presented on the map template.
 */
@property (nonatomic, readonly) UILayoutGuide *mapButtonSafeAreaLayoutGuide;

/**
 @c windowScene is not available for CPWindow's
 */
@property(nullable, nonatomic, weak) UIWindowScene *windowScene NS_UNAVAILABLE;

/**
 @c back-reference to the CPTemplateApplicationScene containing this CPWindow
 */
@property(nullable, nonatomic, weak) CPTemplateApplicationScene *templateApplicationScene;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPSearchTemplate.h
//
//  CPSearchTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListItem.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPSearchTemplateDelegate;


API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPSearchTemplate : CPTemplate

@property (nullable, nonatomic, weak) id<CPSearchTemplateDelegate> delegate;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPSearchTemplateDelegate <NSObject>

/**
 The user has entered characters in the search text field.
 
 @param searchTemplate The search template in use by the user
 @param searchText The search text entered by the user
 @param completionHandler You must call the completionHandler with updated search results
 */
- (void)searchTemplate:(CPSearchTemplate *)searchTemplate updatedSearchText:(NSString *)searchText completionHandler:(void (^)(NSArray <CPListItem *> *searchResults))completionHandler;

/**
 The user has selected an item in the search result list.
 
 @param searchTemplate The search template in use by the user
 @param item The item selected by the user
 @param completionHandler You must call the completionHandler when you have handled the row selection in the search result
 */
- (void)searchTemplate:(CPSearchTemplate *)searchTemplate selectedResult:(CPListItem *)item completionHandler:(void (^)(void))completionHandler;

@optional

/**
 The user has selected the keyboard's search button. Generally, you should push a @c CPListTemplate containing the current search results.

 @param searchTemplate The search template in use by the user
 */
- (void)searchTemplateSearchButtonPressed:(CPSearchTemplate *)searchTemplate;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPGridTemplate.h
//
//  CPGridTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPGridButton.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPGridTemplate : CPTemplate <CPBarButtonProviding>

/**
 Initialize a grid template with an array of @c CPGridButton and a title.
 @note A grid template will only display the first 8 buttons in the provided gridButtons array.
 A grid template presenting more than 4 buttons will balance the buttons between 2 rows.
 */
- (instancetype)initWithTitle:(nullable NSString *)title gridButtons:(NSArray <CPGridButton *> *)gridButtons;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Array of grid buttons displayed on the template
 */
@property (nonatomic, readonly) NSArray <CPGridButton *> *gridButtons;

/**
 Title shown in template's navigation bar
 */
@property (nonatomic, readonly) NSString *title;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPSessionConfiguration.h
//
//  CPSessionConfiguration.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, CPLimitableUserInterface) {
    CPLimitableUserInterfaceKeyboard        = 1 << 0,
    CPLimitableUserInterfaceLists           = 1 << 1,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

@protocol CPSessionConfigurationDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPSessionConfiguration : NSObject

- (instancetype)initWithDelegate:(id <CPSessionConfigurationDelegate>)delegate NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// A bitmask of what type of user interfaces are limited
@property (nonatomic, readonly) CPLimitableUserInterface limitedUserInterfaces;
@property (nonatomic, weak) id<CPSessionConfigurationDelegate> delegate;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPSessionConfigurationDelegate <NSObject>

// This delegate is called whenever the types of limited user interfaces have changed.
- (void)sessionConfiguration:(CPSessionConfiguration *)sessionConfiguration limitedUserInterfacesChanged:(CPLimitableUserInterface)limitedUserInterfaces;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPTemplate.h
//
//  CPTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Abstract superclass for a template object.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTemplate : NSObject <NSSecureCoding>

/**
 Any custom data or an object associated with this template can be stored in this property.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPNavigationAlert.h
//
//  CPNavigationAlert.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPImageSet.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Reasons why your navigation alert was dismissed.
 */
typedef NS_ENUM(NSUInteger, CPNavigationAlertDismissalContext) {
    CPNavigationAlertDismissalContextTimeout = 0,    // The banner was visible long enough to reach its timeout.
    CPNavigationAlertDismissalContextUserDismissed,  // The banner was dismissed in response to a user button press.
    CPNavigationAlertDismissalContextSystemDismissed // The banner was dismissed because of a request by the app.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Your @c CPNavigationAlert may specify a duration for which the alert will be visible onscreen,
 or 0 for an alert that is visible indefinitely.

 For non-indefinite alerts, this is the minimum duration the alert will be visible.
 */
static NSTimeInterval const CPNavigationAlertMinimumDuration = 5;

/**
 @c CPNavigationAlert is a banner alert that can display map or navigation-related information to the user.
*/
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNavigationAlert : NSObject <NSSecureCoding>

/**
 Fully specify a @c CPNavigationAlert with a title, image, primary and secondary action,
 and duration.

 @param titleVariants An array of titles. The system will select a title that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param subtitleVariants An array of subtitles. The system will select a subtitle that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param imageSet An optional @c CPImageSet to display in this navigation alert. Animated images are not supported.
 If an animated image is provided, only the first image from each image set will be used.

 @param primaryAction The alert must include at least one action button.

 @param secondaryAction An optional secondary button to display on the trailing edge of this alert.

 @param duration The duration for which this alert should be visible. Specify 0 for an alert
 that displays indefinitely.

 @return an initialized @c CPNavigationAlert.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                             imageSet:(nullable CPImageSet *)imageSet
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration API_DEPRECATED_WITH_REPLACEMENT("initWithTitleVariants:subtitleVariants:image:primaryAction:secondaryAction:duration", ios(12.0, 13.0)) API_UNAVAILABLE(macos, watchos, tvos);

- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                                image:(nullable UIImage *)image
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration;

/**
 The navigation alert may be updated with new title and subtitle variants, either
 after it has already been displayed on screen, or before its initial presentation on screen.

 Updating an alert that has been already been dismissed has no effect.

 @param newTitleVariants an updated array of title variants
 @param newSubtitleVariants an updated array of subtitle variants
 */
- (void)updateTitleVariants:(NSArray <NSString *> *)newTitleVariants
           subtitleVariants:(NSArray <NSString *> *)newSubtitleVariants;

@property (nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;
@property (nonatomic, readonly, copy) NSArray <NSString *> *subtitleVariants;
@property (nullable, nonatomic, readonly, copy) CPImageSet *imageSet;
@property (nullable, nonatomic, readonly, copy) UIImage *image;
@property (nonatomic, readonly, strong) CPAlertAction *primaryAction;
@property (nullable, nonatomic, readonly, strong) CPAlertAction *secondaryAction;
@property (nonatomic, readonly) NSTimeInterval duration;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPImageSet.h
//
//  CPImageSet.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)

@interface CPImageSet : NSObject <NSSecureCoding>

- (instancetype)initWithLightContentImage:(UIImage *)lightImage darkContentImage:(UIImage *)darkImage;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) UIImage *lightContentImage;
@property (nonatomic, readonly) UIImage *darkContentImage;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPActionSheetTemplate.h
//
//  CPActionSheetTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPActionSheetTemplate represents an action sheet that must be dismissed with a button press
 before the user may return to using the app.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPActionSheetTemplate : CPTemplate

/**
 Initialize a @c CPActionSheetTemplate with a title and/or message, and at least one action.

 @param title The title of the action sheet.
 @param message Descriptive message that provides more detail about the reason for the action sheet.
 @param actions The actions for the action sheet.
 */
- (instancetype)initWithTitle:(nullable NSString *)title message:(nullable NSString *)message actions:(NSArray<CPAlertAction *> *)actions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, readonly, nullable) NSString *title;
@property (nonatomic, copy, readonly, nullable) NSString *message;

@property (nonatomic, strong, readonly) NSArray<CPAlertAction *> *actions;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPTravelEstimates.h
//
//  CPTravelEstimates.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPTravelEstimates describes the time and distance remaining for the active navigation session.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTravelEstimates : NSObject <NSSecureCoding>

/**
 Initialize a @c CPTravelEstimates with distance and time remaining.

 @note A distance value less than 0 or a time remaining value less than 0 will render
 as "--" in the ETA and trip preview cards, indicating that distance or time remaining are
 unavailable, due to route calculations/rerouting or internet connectivity problems.
 Values less than 0 are distinguished from distance or time values equal to 0; your app may
 display 0 as the user is imminently arriving at their destination.
 */
- (instancetype)initWithDistanceRemaining:(NSMeasurement<NSUnitLength *> *)distance timeRemaining:(NSTimeInterval)time NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Distance remaining.
 */
@property (nonatomic, readonly, copy) NSMeasurement<NSUnitLength *> *distanceRemaining;

/**
 Time remaining.
 */
@property (nonatomic, readonly, assign) NSTimeInterval timeRemaining;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPListItem.h
//
//  CPListItem.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

extern CGSize const CPMaximumListItemImageSize; // 44 x 44

/**
 @c CPListItem describes a single object appearing in a list template.
 Each @c CPListItem is displayed in a single cell in the list.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListItem : NSObject <NSSecureCoding>

/**
 Initialize a list item with text, detailtext, an image, and a disclosure indicator.

 @note The maximum image size is 44 points by 44 points. If you supply a larger image,
 it will be scaled down to this size.
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText
                       image:(nullable UIImage *)image
    showsDisclosureIndicator:(BOOL)showsDisclosureIndicator;

/**
 Initialize a list item with text, detail text, and an image.

 @note The maximum image size is 44 points by 44 points. If you supply a larger image,
 it will be scaled down to this size.
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText
                       image:(nullable UIImage *)image;

/**
 Initialize a list item with text and detail text.
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText;

/**
 The primary text shown in a cell displaying this list item.
 */
@property (nullable, nonatomic, readonly, copy) NSString *text;

/**
 Any extra text displayed below the primary text in a cell displaying this list item.
 */
@property (nullable, nonatomic, readonly, copy) NSString *detailText;

/**
 An image displayed on the leading side of a cell displaying this list item.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 */
@property (nullable, nonatomic, readonly, strong) UIImage *image;

/**
 If YES, a cell displaying this list item will render with a disclosure indicator
 in the trailing side of the cell.

 Defaults to NO.
 */
@property (nonatomic, readonly, assign) BOOL showsDisclosureIndicator;

/**
 Any custom user info related to this item.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPListTemplate.h
//
//  CPListTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPListItem.h>
#import <CarPlay/CPListSection.h>
#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPListTemplateDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListTemplate : CPTemplate <CPBarButtonProviding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Initialize a list template with one or more sections of items and an optional title.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                     sections:(NSArray <CPListSection *> *)sections;

/**
 The list template's delegate is informed of list selection events.
 */
@property (nullable, nonatomic, weak) id<CPListTemplateDelegate> delegate;

/**
 The sections displayed in this list.
 */
@property (nonatomic, readonly, copy) NSArray <CPListSection *> *sections;

/**
 Title shown in the navigation bar while this template is visible.
 */
@property (nullable, nonatomic, readonly, copy) NSString *title;

/**
 Update the list of sections displayed in this list template, reloading
 the table view displaying this list.
 */
- (void)updateSections:(NSArray <CPListSection *> *)sections;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPListTemplateDelegate <NSObject>

/**
 The user has selected an item in the list template.
 
 Your app has an opportunity to perform any necessary operations to prepare for completing
 this item selection. The list template will display a spinner after a short delay.
 
 You must call the completion block after your app has finished loading and updated its UI.
 
 @param listTemplate The list template containing this item
 @param item The item selected by the user
 @param completionHandler A completion block you must call after you have updated your UI.
 */
- (void)listTemplate:(CPListTemplate *)listTemplate didSelectListItem:(CPListItem *)item completionHandler:(void (^)(void))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPAlertAction.h
//
//  CPAlertAction.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPAlertActionStyle) {
    CPAlertActionStyleDefault = 0, // A style that indicates a default action.
    CPAlertActionStyleCancel,     // A style that indicates the action will cancel and leave data unchanged.
    CPAlertActionStyleDestructive // A style that indicates the button might change or delete data.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 @c CPAlertAction represents a single action that appears inside of a @c CPActionSheetTemplate or @c CPAlertTemplate.

 The style of the parent template and the style of the @c CPAlertAction will together
 determine the action's appearance.

 The action has a customizable title, style, and a block callback
 that is invoked when the user taps this button.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPAlertAction : NSObject <NSSecureCoding>

typedef void (^CPAlertActionHandler) (CPAlertAction *);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Create an alert action with a title, display style, and a callback handler that is invoked
 when the user taps this action.
 */
- (instancetype)initWithTitle:(NSString *)title
                        style:(CPAlertActionStyle)style
                      handler:(CPAlertActionHandler)handler;

@property (nonatomic, copy, readonly) NSString *title;
@property (nonatomic, assign, readonly) CPAlertActionStyle style;
@property (nonatomic, copy, readonly) CPAlertActionHandler handler;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPBarButton.h
//
//  CPBarButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Specifies the style of a @c CPBarButton
 */
typedef NS_ENUM(NSUInteger, CPBarButtonType) {
    CPBarButtonTypeText,
    CPBarButtonTypeImage,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 A button for placement in a navigation bar.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPBarButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a new bar button of the specified type.

 @param type The button type. See @c CPBarButtonType for the possible values.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.
 */
- (instancetype)initWithType:(CPBarButtonType)type handler:(void (^ _Nullable)(CPBarButton *barButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 The button type.

 @discussion See @c CPBarButtonType for the possible values.
 */
@property (nonatomic, readonly, assign) CPBarButtonType buttonType;

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.

 @note The setter has no effect unless the button is of type @c CPBarButtonTypeImage
 */
@property (nullable, nonatomic, strong) UIImage *image;

/**
 The title displayed on the button.

 @note The setter has no effect unless the button is of type @c CPBarButtonTypeText
 */
@property (nullable, nonatomic, copy) NSString *title;

@end

NS_ASSUME_NONNULL_END
// ==========  CarPlay.framework/Headers/CPBarButtonProviding.h
//
//  CPBarButtonProviding.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButton.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPBarButtonProviding <NSObject>

/**
 An array of bar buttons to be displayed on the leading side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the leading space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *leadingNavigationBarButtons;

/**
 An array of bar buttons to be displayed on the trailing side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the trailing space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *trailingNavigationBarButtons;

@property (nonatomic, strong, nullable) CPBarButton *backButton;

@end

NS_ASSUME_NONNULL_END
