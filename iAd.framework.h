// ==========  iAd.framework/Headers/AVPlayerViewController_iAdPreroll.h
//
//  AVPlayerViewController_iAdPreroll.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#import <AVKit/AVPlayerViewController.h>

@interface AVPlayerViewController (iAdPreroll)

NS_ASSUME_NONNULL_BEGIN

/*!
 * @method +preparePrerollAds
 *
 * @discussion
 * Inform iAd that the application intends to use AVPlayerViewController's
 * -playPrerollAdWithCompletionHandler: API. Ad metadata will be fetched eagerly,
 * increasing the likelihood of an ad being available when first requested.
 */
+ (void)preparePrerollAds NS_AVAILABLE_IOS(8_0);

/*!
 * @method -playPrerollAdWithCompletionHandler:
 *
 * @discussion
 * Request playback of a pre-roll video iAd.
 *
 * If -[AVPlayerViewController player] begins playing during a pre-roll ad, the
 * video ad will stop immediately.
 *
 * The completion handler's error argument will be non-nil if the pre-roll ad
 * could not be played. Errors can occur for a number of reasons, such as lack
 * of ad inventory, exceeding the maximum pre-roll ad playback frequency, iAd
 * account configuration issues, and media playback issues. See ADError for an
 * exhaustive list of possible errors.
 *
 * Passing nil as the completion handler is an error and will throw an exception.
 */
- (void)playPrerollAdWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(8_0);

/*!
 * @method -cancelPreroll
 *
 * @discussion
 * Cancel pre-roll video ad playback.
 */
- (void)cancelPreroll NS_AVAILABLE_IOS(8_0);

@end

NS_ASSUME_NONNULL_END
#endif
// ==========  iAd.framework/Headers/ADBannerView.h
//
//  ADBannerView.h
//  iAd
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

/*!
 * @const ADErrorDomain
 *
 * @discussion
 * Error domain for NSErrors passed to the following delegate methods:
 *
 *   • -[ADBannerViewDelegate bannerView:didFailToReceiveAdWithError:]
 *   • -[ADInterstitialAdDelegate interstitialAd:didFailWithError:]
 *
 */
extern NSString * const ADErrorDomain;

/*!
 * @enum ADError
 *
 * @const ADErrorUnknown
 * General errors that aren't covered by one of the more specific error reasons.
 *
 * @const ADErrorServerFailure
 * Unable to request ads and their resources from the iAd service.
 *
 * @const ADErrorInventoryUnavailable
 * No ads are available at the moment. Note that this error is *always* returned
 * to iPhone apps running in compatibility mode on iPad, since ads are not
 * supported in that configuration.
 *
 * @const ADErrorConfigurationError
 * There are iAd configuration issues that need to be resolved before ads can be
 * served. Generally, this means visiting ADC <http://developer.apple.com/>.
 *
 * @const ADErrorBannerVisibleWithoutContent
 * The banner is visible but had no ad. Generally, this means a banner was made
 * visible before the -bannerViewDidLoadAd: delegate method was called, or
 * remained visible after the -bannerView:didFailToReceiveAdWithError: delegate
 * method was called.
 *
 * @const ADErrorAdUnloaded
 * The ad being displayed in the banner was unloaded. Some examples of when this
 * might happen is when an ad expires, or when an ad is moved from a non-visible
 * banner to a visible banner.
 *
 * @const ADErrorLoadingThrottled
 * Unused.
 *
 * @const ADErrorApplicationInactive
 * Unused.
 *
 * @discussion
 * Error codes for NSErrors passed to the delegate via the
 * bannerView:didFailToReceiveAdWithError: delegate method.
 */
typedef NS_ENUM(NSInteger, ADError) {
#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorUnknown = 0,
    ADErrorServerFailure = 1,
    ADErrorLoadingThrottled = 2,
    ADErrorInventoryUnavailable = 3,
#endif
#if __IPHONE_4_1 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorConfigurationError = 4,
    ADErrorBannerVisibleWithoutContent = 5,
#endif
#if __IPHONE_4_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorApplicationInactive = 6,
#endif
#if __IPHONE_6_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAdUnloaded = 7,
#endif
#if __IPHONE_9_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAssetLoadFailure = 8,
#endif
#if __IPHONE_10_3 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ADErrorAdResponseValidateFailure = 9,
    ADErrorAdAssetLoadPending = 10
#endif
} NS_ENUM_DEPRECATED_IOS(4_0, 10_0);

/*!
 * @enum ADAdType
 *
 * @const ADAdTypeBanner A device-width banner ad. The banner height varies with
 * device type and orientation:
 *
 *   • On iPhone; portrait = DEVICE_WIDTH × 50px, landscape = DEVICE_WIDTH × 32px
 *   • On iPad; both portrait & landscape = DEVICE_WIDTH × 66px
 *
 * @const ADAdTypeMediumRectangle An 320 × 250px ad, based on the International
 * Advertising Bureau's "Medium Rectangle" Interactive Marketing Unit.
 *
 * @discussion
 * Ad types that can be passed to -[ADBannerView -initWithAdType:].
 */
typedef NS_ENUM(NSInteger, ADAdType) {
    ADAdTypeBanner,
    ADAdTypeMediumRectangle
} NS_ENUM_DEPRECATED_IOS(6_0, 10_0);

@protocol ADBannerViewDelegate;

/*!
 * @class ADBannerView
 *
 * @discussion
 * Provides a view for displaying iAds in an application. iAds are automatically
 * loaded, presented, and refreshed. When a banner view is tapped, the iAd will
 * begin its action. In most cases, the action displays a fullscreen interactive
 * iAd.
 *
 * Note: ADBannerViews must be added to a view hierarchy managed by a
 * UIViewController. If view controller containment is being used, the controller
 * managing the banner view must be correctly configured to ensure banner action
 * presentation works correctly.
 */
NS_CLASS_DEPRECATED_IOS(4_0, 10_0) @interface ADBannerView : UIView

/*!
 * @method initWithAdType:
 *
 * @discussion
 * Initialize the view with a specific ad type. The ad type cannot be changed
 * after initialization.
 */
- (nullable instancetype)initWithAdType:(ADAdType)type NS_AVAILABLE_IOS(6_0);

/*!
 * @property adType
 *
 * @return
 * The banner view's ad type.
 */
@property (nonatomic, readonly) ADAdType adType NS_AVAILABLE_IOS(6_0);

/*!
 * @property delegate
 *
 * @discussion
 * The banner view delegate is notified when events related to the banner view
 * and current ad occur, such as when a new ad is loaded, when errors occur
 * while fetching ads, or when banner actions begin and end.
 *
 * On iOS 5 and later, this property is a weak reference and cannot be used with
 * objects that modify the behavior of release or retain.
 */
@property (nullable, nonatomic, weak) id<ADBannerViewDelegate> delegate;

/*!
 * @property bannerLoaded
 *
 * @return
 * YES if an ad is currently loaded, NO otherwise.
 */
@property (nonatomic, readonly, getter=isBannerLoaded) BOOL bannerLoaded;

/*!
 * @property bannerViewActionInProgress
 *
 * @return
 * YES if the user is currently engaged with a fullscreen interactive ad.
 */
@property (nonatomic, readonly, getter=isBannerViewActionInProgress) BOOL bannerViewActionInProgress;

/*!
 * @method cancelBannerViewAction
 *
 * @discussion
 * Cancels the current in-progress banner view action. This should only be used
 * in cases where the user's attention is required immediately.
 */
- (void)cancelBannerViewAction;

/*!
 * @property advertisingSection
 *
 * @discussion
 * Reserved for future use.
 */
@property (nullable, nonatomic, copy) NSString *advertisingSection;

@end

/*!
 * @protocol ADBannerViewDelegate
 */
@protocol ADBannerViewDelegate <NSObject>
@optional

/*!
 * @method bannerViewWillLoadAd:
 *
 * @discussion
 * Called when a banner has confirmation that an ad will be presented, but
 * before the resources necessary for presentation have loaded.
 */
- (void)bannerViewWillLoadAd:(ADBannerView *)banner  NS_AVAILABLE_IOS(5_0);

/*!
 * @method bannerViewDidLoadAd:
 *
 * @discussion
 * Called each time a banner loads a new ad. Once a banner has loaded an ad, it
 * will display it until another ad is available.
 *
 * It's generally recommended to show the banner view when this method is called,
 * and hide it again when bannerView:didFailToReceiveAdWithError: is called.
 */
- (void)bannerViewDidLoadAd:(ADBannerView *)banner;

/*!
 * @method bannerView:didFailToReceiveAdWithError:
 *
 * @discussion
 * Called when an error has occurred while attempting to get ad content. If the
 * banner is being displayed when an error occurs, it should be hidden
 * to prevent display of a banner view with no ad content.
 *
 * @see ADError for a list of possible error codes.
 */
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error;

/*!
 * @method bannerViewActionShouldBegin:willLeaveApplication:
 *
 * Called when the user taps on the banner and some action is to be taken.
 * Actions either display full screen content modally, or take the user to a
 * different application.
 *
 * The delegate may return NO to block the action from taking place, but this
 * should be avoided if possible because most ads pay significantly more when
 * the action takes place and, over the longer term, repeatedly blocking actions
 * will decrease the ad inventory available to the application.
 *
 * Applications should reduce their own activity while the advertisement's action
 * executes.
 */
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave;

/*!
 * @method bannerViewActionDidFinish:
 *
 * Called when a modal action has completed and control is returned to the
 * application. Games, media playback, and other activities that were paused in
 * bannerViewActionShouldBegin:willLeaveApplication: should resume at this point.
 */
- (void)bannerViewActionDidFinish:(ADBannerView *)banner;

@end

CGSize ADClampedBannerSize(CGSize size);

NS_ASSUME_NONNULL_END

// ==========  iAd.framework/Headers/ADInterstitialAd.h
//
//  ADInterstitialAd.h
//  iAd
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iAd/ADBannerView.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

#define IAD_DEPRECATED_IOS_MSG(_iosIntro, _iosDep, _msg) \
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_##_iosIntro, __IPHONE_##_iosDep, _msg)

@protocol ADInterstitialAdDelegate;

/*!
 * ADInterstitialAd is a full screen advertisement, available on iPad since
 * iOS 4.3, and on iPhone since iOS 7.0.
 *
 * There are three ways to display an ADInterstitialAd:
 *
 *   • By providing a container view and calling -presentInView:
 *   • By providing a view controller and calling -presentFromViewController:
 *   • Indirectly, by setting the interstitial presentation policy on a view
 *     controller to Automatic or Manual (via -[UIViewController setInterstitialPresentationPolicy:]),
 *     and letting the framework manage presentation.
 *
 * An ADInterstitialAd should not be presented until it has loaded content. This
 * is indicated via the -interstitialAdDidLoad: delegate method, and can also be
 * queried via the loaded property. If the interstitial ad is presented when
 * loaded=NO, an exception will be thrown.
 *
 * Note that using interstitial ads on iPhones running iOS < 7.0 will cause an
 * exception to be thrown.
 */
NS_CLASS_DEPRECATED_IOS(4_3, 10_0) @interface ADInterstitialAd : NSObject

/*!
 * @property delegate
 *
 * @discussion
 * The interstitial ad delegate is notified when it has loaded, when errors
 * occur in getting ads, when actions begin and end, and when it has unloaded.
 *
 * On iOS 5 and later, this property is a weak reference and cannot be used with
 * objects that modify the behavior of release or retain.
 */
@property (nullable, nonatomic, weak) id<ADInterstitialAdDelegate> delegate;

/*!
 * @property loaded
 *
 * @return
 * YES if an ad is loaded, NO otherwise. This property should always be checked
 * before the interstitial ad is presented.
 */
@property (nonatomic, readonly, getter=isLoaded) BOOL loaded;

/*!
 * @property actionInProgress
 *
 * @discussion
 * Actions display full screen content in a modal session. Use this property to
 * determine if such an action is currently in progress.
 */
@property (nonatomic, readonly, getter=isActionInProgress) BOOL actionInProgress;

/*!
 * @property cancelAction
 *
 * @discussion
 * Cancels the current in-progress action. This should only be used in cases
 * where the user's attention is required immediately. If this method is called,
 * -interstitialAdActionDidFinish: will not be called.
 */
- (void)cancelAction;

/*
 * @method presentInView:
 *
 * @discussion
 * This method should be used to display the interstitial in a view hierarchy.
 * The view hierarchy must be managed by a view controller and the size of the
 * container view must fit the following constraints:
 *
 *   • Width must be DEVICE_WIDTH for the current orientation.
 *   • Height must be at least (DEVICE_HEIGHT - STATUS_BAR_HEIGHT - NAVIGATION_BAR_HEIGHT - TAB_BAR_HEIGHT).
 *   • Height must not exceed DEVICE_HEIGHT
 *
 * @throws NSInternalInconsistencyException
 * If the container view is not already in a view controller's managed hierarchy,
 * an exception will be thrown.
 *
 * @throws NSInternalInconsistencyException
 * If the interstitial has not loaded at the time this method is invoked, an
 * exception will be thrown.
 *
 * @return
 * YES if the interstitial could be presented, NO otherwise.
 */
- (BOOL)presentInView:(UIView *)containerView;

/*!
 * @method presentFromViewController:
 *
 * @discussion
 * As of iOS 7.0, the interstitial ad presentation APIs on UIViewController
 * should be used instead of managing your own ADInterstitialAd and presenting
 * it via the presentFromViewController: API.
 *
 * On iOS < 7.0, this method should be used to present the interstitial ad in a
 * non-paging UI, such as a transition or at the end of a game level. When this
 * API is used, the framework will manage how the interstitial is displayed and
 * what happens when the user dismisses it.
 *
 * User dismissal of either the interstitial or the ad unit to which it is
 * linked will restore control to the application immediately.
 */
- (void)presentFromViewController:(UIViewController *)viewController IAD_DEPRECATED_IOS_MSG(4_3, 7_0, "Use -[UIViewController requestInterstitialAdPresentation] and related APIs documented in <iAd/UIViewControlleriAdAdditions.h>.");

@end

/*!
 * @protocol ADInterstitialAdDelegate
 */
@protocol ADInterstitialAdDelegate <NSObject>

/*!
 * @method interstitialAdDidUnload:
 *
 * @discussion
 * When this method is invoked, if the application is using -presentInView:, the
 * content will be unloaded from the container shortly after this method is
 * called and no new content will be loaded. This may occur either as a result
 * of user actions or if the ad content has expired.
 *
 * In the case of an interstitial presented via -presentInView:, the layout of
 * the app should be updated to reflect that an ad is no longer visible. e.g.
 * by removing the view used for presentation and replacing it with another view.
 */
- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd;

/*!
 * @method interstitialAd:didFailWithError:
 *
 * @discussion
 * Called when an error has occurred attempting to get ad content.
 *
 * @see ADError for a list of possible error codes.
 */
- (void)interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error;

@optional

/*!
 * @method interstitialAdWillLoad:
 *
 * @discussion
 * Called when the interstitial has confirmation that an ad will be presented,
 * but before the ad has loaded resources necessary for presentation.
 */
- (void)interstitialAdWillLoad:(ADInterstitialAd *)interstitialAd NS_AVAILABLE_IOS(5_0);

/*!
 * @method interstitialAdDidLoad:
 *
 * @discussion
 * Called when the interstitial ad has finished loading ad content. The delegate
 * should implement this method so it knows when the interstitial ad is ready to
 * be presented.
 */
- (void)interstitialAdDidLoad:(ADInterstitialAd *)interstitialAd;

/*!
 * @method interstitialAdActionShouldBegin:willLeaveApplication:
 *
 * @discussion
 * Called when the user chooses to interact with the interstitial ad.
 *
 * The delegate may return NO to block the action from taking place, but this
 * should be avoided if possible because most ads pay significantly more when
 * the action takes place and, over the longer term, repeatedly blocking actions
 * will decrease the ad inventory available to the application.
 *
 * Applications should reduce their own activity while the advertisement's action
 * executes.
 */
- (BOOL)interstitialAdActionShouldBegin:(ADInterstitialAd *)interstitialAd willLeaveApplication:(BOOL)willLeave;

/*!
 * @method interstitialAdActionDidFinish:
 * This message is sent when the action has completed and control is returned to
 * the application. Games, media playback, and other activities that were paused
 * in response to the beginning of the action should resume at this point.
 */
- (void)interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd;

@end

@interface ADInterstitialAdPresentationViewController : UIViewController

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (id)initForInterstitialAd:(ADInterstitialAd *)interstitialAd;
#pragma clang diagnostic pop
- (BOOL)shouldTestVisibilityAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END

// ==========  iAd.framework/Headers/ADBannerView_Deprecated.h
//
//  ADBannerView_Deprecated.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#import <iAd/ADBannerView.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @category ADBannerView (Deprecated)
 *
 * @discussion
 * These banner view resizing APIs have been deprecated and should no longer be
 * used when targeting iOS 6.0 or later.
 *
 * To resize a banner view on iOS 6.0 or later, call -sizeThatFits: on the banner
 * view, specifying the bounds of the view that contains your banner, and use the
 * returned size to resize the banner view. Based on the size you provide, the
 * banner will be sized to the correct width and height for the current device
 * type and orientation, as per the ADAdTypeBanner documentation.
 *
 * A full example of this - including how to handle resizing on devices running
 * older versions of iOS - can be found in the 'iAdSuite' sample project on the
 * ADC website <http://developer.apple.com>.
 */
@interface ADBannerView (Deprecated)

@property (nullable, nonatomic, copy) NSSet *requiredContentSizeIdentifiers NS_DEPRECATED_IOS(4_0, 6_0);

@property (nullable, nonatomic, copy) NSString *currentContentSizeIdentifier NS_DEPRECATED_IOS(4_0, 6_0);

+ (CGSize)sizeFromBannerContentSizeIdentifier:(NSString *)contentSizeIdentifier NS_DEPRECATED_IOS(4_0, 6_0);

@end

extern NSString * const ADBannerContentSizeIdentifier320x50 NS_DEPRECATED_IOS(4_0, 4_2);
extern NSString * const ADBannerContentSizeIdentifier480x32 NS_DEPRECATED_IOS(4_0, 4_2);
extern NSString * const ADBannerContentSizeIdentifierPortrait NS_DEPRECATED_IOS(4_2, 6_0);
extern NSString * const ADBannerContentSizeIdentifierLandscape NS_DEPRECATED_IOS(4_2, 6_0);

NS_ASSUME_NONNULL_END
// ==========  iAd.framework/Headers/UIViewControlleriAdAdditions.h
//
//  UIViewControlleriAdAdditions.h
//  iAd
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#pragma clang system_header

/*!
 * @enum ADInterstitialPresentationPolicy
 *
 * @constant ADInterstitialPresentationPolicyNone Default policy - this is effectively
 * the same as the Manual policy except that setting the Manual policy will trigger
 * the +prepareInterstitialAds logic if needed.
 *
 * @constant ADInterstitialPresentationPolicyAutomatic Automatic policy - the framework
 * determines when an interstitial will be presented.
 *
 * @constant ADInterstitialPresentationPolicyManual Manual policy - the application
 * determines when an interstitial should be presented and calls an API from the
 * iAdAdditions category.
 *
 * @discussion
 * Policy options governing how and when interstitial ads may be presented from
 * a given view controller.
 */
typedef NS_ENUM(NSInteger, ADInterstitialPresentationPolicy) {
    ADInterstitialPresentationPolicyNone = 0,
    ADInterstitialPresentationPolicyAutomatic,
    ADInterstitialPresentationPolicyManual
}  NS_ENUM_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @category UIViewController (iAdAdditions)
 *
 * @discussion
 * This category on UIViewController provides an interface for configuring the kind
 * of ads that should be shown with the view controller's content. Two types of
 * ads may be shown - banners and interstitials. Banner ads will be displayed below
 * the content which will be resized appropriately based on the size of the banner.
 * Interstitials can be displayed automatically or upon request. Automatic display
 * of interstitials will be tied to the appearance of the view, with the frequency
 * of presentation managed by the framework. On-request display of interstitials
 * is subject to similar internal constraints.
*/
@interface UIViewController (iAdAdditions)

/*!
 * @method prepareInterstitials
 *
 * @discussion
 * Ads involve network requests, so if an application needs to use interstitial
 * ads and wants to ensure early availability, this method can be called to trigger
 * a prefetch. If this method is not called, the first fetch will occur when a
 * view controller's interstitialPresentationPolicy is set to something other
 * than ADInterstitialPresentationPolicyNone.
 */
+ (void)prepareInterstitialAds NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @property interstitialPresentationPolicy
 *
 * @discussion
 * The presentation policy determines whether the timing of presentation is entirely
 * managed by the framework or should only take place when the application calls
 * -requestInterstitialAdPresentation. By default the policy is "None", so to be
 * able to present an interstitial it must be changed to either "Automatic" or "Manual".
 */
@property (nonatomic, assign) ADInterstitialPresentationPolicy interstitialPresentationPolicy NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @property canDisplayBannerAds
 *
 * @discussion
 * Set this to enable automatic management of banner ad display with the view controller.
 * It's important to note that this will modify the view hierarchy of the view controller
 * by inserting a new container view above the view controller's view. The impact
 * is that the view controller's view property will no longer return the originally
 * provided view, it will return the new container. To access the original view,
 * use the originalContentView property.
 *
 * @seealso originalContentView
 */
@property (nonatomic, assign) BOOL canDisplayBannerAds NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @property originalContentView
 *
 * @discussion
 * If banner ads have not been enabled, originalContentView will return the view
 * controller's view. If banner ads are enabled, originalContentView returns the
 * view that was previously the view controller's view. If banner ads are then subsequently
 * disabled, the view controller's content view will remain embedded - that operation
 * will not be reversed.
 */
@property (nullable, nonatomic, retain, readonly) UIView *originalContentView NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @property presentingFullScreenAd
 *
 * @discussion
 * Can be used to query the controller to determine if it is presenting a full screen
 * ad, which may be an interstitial or the iAd shown when the user taps a banner.
 */
@property (nonatomic, readonly, getter=isPresentingFullScreenAd) BOOL presentingFullScreenAd NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @property displayingBannerAd
 *
 * @discussion
 * Can be used to query the controller to determine if it is displaying a banner ad.
 */
@property (nonatomic, readonly, getter=isDisplayingBannerAd) BOOL displayingBannerAd NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @method requestInterstitialAdPresentation
 *
 * @return
 * Returns YES if an interstitial can be displayed, NO if not.
 *
 * @discussion
 * Call at any time to request that an interstitial ad be presented. This is appropriate
 * for view controllers that are on screen for long periods of time and internally
 * manage significant state changes, such as game levels. Returns YES if an interstitial
 * will be presented.
 */
- (BOOL)requestInterstitialAdPresentation NS_DEPRECATED_IOS(7_0, 10_0);

/*!
 * @method shouldPresentInterstitialAd
 *
 * @return
 * Should return YES to allow presentation to proceed, NO to prevent it. The default
 * implementation always returns YES.
 *
 * @discussion
 * Subclasses should override this method if they use ADInterstitialPresentationPolicyAutomatic
 * and require the ability to selectively prevent presentation based on application
 * state. The method will be invoked when the framework is about to present an interstitial
 * ad in the ADInterstitialPresentationPolicyAutomatic configuration.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL shouldPresentInterstitialAd NS_DEPRECATED_IOS(7_0, 10_0);

@end

NS_ASSUME_NONNULL_END

// ==========  iAd.framework/Headers/ADClient.h
//
//  ADClient.h
//  iAd
//
//  Copyright 2013 Apple, Inc. All rights reserved.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(7_1) @interface ADClient : NSObject

/*!
 * @method sharedClient
 *
 * @return
 * The shared singleton instance of ADClient.
 *
 * @discussion
 * ADClient is a singleton object.
 */
+ (ADClient *)sharedClient NS_AVAILABLE_IOS(7_1);

/*!
 * @const ADClientErrorDomain
 *
 * @discussion
 * Error domain for NSErrors passed to the completionHandler as a 
 * result of calling:
 *
 *   • -[[ADClient SharedClient] requestAttributionDetailsWithBlock]
 *
 */
extern NSString * const ADClientErrorDomain;

/*!
 * @enum ADClientError
 *
 * @const ADClientErrorUnknown
 * General errors that aren't covered by one of the more specific error reasons.
 * This is generally related to connectivity issues.
 *
 * @const ADClientErrorLimitAdTracking
 * The device has Limit Ad Tracking enabled. It will not be possible to recieve
 * attribution details for app purchases made on this device.
 *
 * @const ADClientErrorMissingData
 * The downloaded app received a payload lacking enough data to perform an
 * Attribution Check.
 *
 * @const ADClientErrorCorruptResponse
 * The response received from the Attribution Server was corrupt.
 *
 * @discussion
 * Error codes for NSErrors passed to the completionHandler block
 * when calling the requestAttributionDetailsWithBlock method.
 */
typedef NS_ENUM(NSInteger, ADClientError) {
    ADClientErrorUnknown = 0,
    ADClientErrorLimitAdTracking = 1,
    ADClientErrorMissingData = 2,
    ADClientErrorCorruptResponse = 3
};

/*!
 * @method determineAppInstallationAttributionWithCompletionHandler:
 *
 * @param completionHandler
 * A block accepting one BOOL argument that will be called when app installation
 * attribution status has been determined. If this installation of the app is
 * attributed to an iAd impression, the completion handler will be called with
 * YES. Otherwise, or if the user has enabled Limit Ad Tracking, the completion
 * handler will be called with NO.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine if it was installed by the user in
 * response to seeing an iAd for the app.
 */
- (void)determineAppInstallationAttributionWithCompletionHandler:(void (^)(BOOL appInstallationWasAttributedToiAd))completionHandler NS_DEPRECATED_IOS(7_1, 9_0, "Use requestAttributionDetailsWithBlock instead.");

/*!
 * @method lookupAdConversionDetails:
 *
 * @param completionHandler
 * This method is deprecated.
 * A block will be called with iAdImpressionDate = nil
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine when an iAd was shown to the user
 * which resulted in the user's purchase of the app.
 */
- (void)lookupAdConversionDetails:(void (^)(NSDate * _Nullable appPurchaseDate, NSDate * _Nullable iAdImpressionDate))completionHandler NS_DEPRECATED_IOS(8_0, 9_0, "Use requestAttributionDetailsWithBlock instead.");

/*!
 * @method requestAttributionDetailsWithBlock:
 *
 * @param completionHandler
 * A block which will be called with details related to the attribution status of the app.
 * The attributionDetails dictionary will contain purchase and impression dates
 * as well as other specific campaign related information provided by iAd. If the attributionDetails
 * dictionary is nil, an NSError is passed with an ADClientError enum.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine when an iAd was shown to the user
 * which resulted in the user's purchase of the app.
 */
- (void)requestAttributionDetailsWithBlock:(void (^)(NSDictionary<NSString *, NSObject *> * _Nullable attributionDetails, NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(9_0);

/*!
 * @method addClientToSegments:replaceExisting:
 *
 * @param segmentIdentifiers
 * Array of NSString objects identifying which segments to add the client to.
 * May be nil.
 *
 * @param replaceExisting
 * If YES, the client will be removed from all existing segments prior to
 * being added to the specified segments.
 *
 * @discussion
 * Enables apps to add users to custom segments owned and defined by the calling
 * application.  If Limit Ad Tracking is enabled on the device, this method will
 * have no effect.
 */
- (void)addClientToSegments:(NSArray<NSString *> *)segmentIdentifiers replaceExisting:(BOOL)replaceExisting NS_AVAILABLE_IOS(8_0);

@end

NS_ASSUME_NONNULL_END

// ==========  iAd.framework/Headers/ADCommonDefinitions.h
//
//  ADCommonDefinitions.h
//  iAd
//
//  Created by Dheeraj Goswami on 9/19/17.
//

#ifndef ADCommonDefinitions_h
#define ADCommonDefinitions_h

#define IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#define IS_RETINA ([[UIScreen mainScreen] scale] >= 2.0)

#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
#define SCREEN_MAX_LENGTH (MAX(SCREEN_WIDTH, SCREEN_HEIGHT))
#define SCREEN_MIN_LENGTH (MIN(SCREEN_WIDTH, SCREEN_HEIGHT))

#define IS_IPHONE_4 (IS_IPHONE && SCREEN_MAX_LENGTH < 568.0)
#define IS_IPHONE_5_OR_SE (IS_IPHONE && SCREEN_MAX_LENGTH == 568.0)
#define IS_IPHONE_6_OR_7_OR_8 (IS_IPHONE && SCREEN_MAX_LENGTH == 667.0)
#define IS_IPHONE_6P_OR_7P_OR_8P (IS_IPHONE && SCREEN_MAX_LENGTH == 736.0)
#define IS_IPHONE_X (IS_IPHONE && SCREEN_MAX_LENGTH == 812.0)

#endif /* ADCommonDefinitions_h */
// ==========  iAd.framework/Headers/iAd.h
/*
 *  iAd.h
 *  iAd
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 */

#import <iAd/ADBannerView.h>
#import <iAd/ADBannerView_Deprecated.h>
#import <iAd/ADClient.h>
#import <iAd/ADInterstitialAd.h>
#import <iAd/AVPlayerViewController_iAdPreroll.h>
#import <iAd/UIViewControlleriAdAdditions.h>
// ==========  iAd.framework/Headers/ADActionViewControllerInterface.h
//
//  ADSActionViewControllerInterface.h
//  iAd
//
//  Created by David Wilson on 3/28/14.
//
//

#import <Foundation/Foundation.h>

@class ADAdSpace;

@protocol ADActionViewControllerInterface <NSObject>

@property (nonatomic, readonly) BOOL readyForPresentation;
@property (nonatomic, weak, readonly) ADAdSpace *adSpace;

- (void)dismiss;

- (void)clientApplicationDidEnterBackground;
- (void)clientApplicationCancelledAction;

@end

@protocol ADActionViewControllerChildInterface <NSObject>

- (void)actionViewControllerClosed;

@end
