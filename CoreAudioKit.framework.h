// ==========  CoreAudioKit.framework/Headers/CABTMIDILocalPeripheralViewController.h
// =================================================================================================
// CABTMIDILocalPeripheralViewController.h
// =================================================================================================
/*
 File:		CABTMIDILocalPeripheralViewController.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */

#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE_IOS(8_0)
@interface CABTMIDILocalPeripheralViewController : UIViewController
@end
// ==========  CoreAudioKit.framework/Headers/CoreAudioKit.h
#import <CoreAudioKit/CAInterAppAudioSwitcherView.h>
#import <CoreAudioKit/CAInterAppAudioTransportView.h>

#import <CoreAudioKit/CABTMIDILocalPeripheralViewController.h>
#import <CoreAudioKit/CABTMIDICentralViewController.h>

#import <CoreAudioKit/AUViewController.h>
// ==========  CoreAudioKit.framework/Headers/AUViewController.h
//
//  AUViewController.h
//	Framework: CoreAudioKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <AudioUnit/AudioUnit.h>
#import <Foundation/NSExtensionRequestHandling.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIViewController AUViewControllerBase;
#else
#import <AppKit/AppKit.h>
typedef NSViewController AUViewControllerBase;
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUViewController : AUViewControllerBase <NSExtensionRequestHandling>
@end

@interface AUAudioUnit (AUAudioUnit_ViewController)
/*!	@method	requestViewControllerWithCompletionHandler:
	@brief	Obtains an audio unit's view controller (and thereby a view).
	@discussion
		Asynchronously requests the audio unit's view controller. This method will later call the
		completion handler, in a thread/dispatch queue context internal to the implementation, with
		a view controller, or nil in the case of an audio unit without a custom view controller.
*/
- (void)requestViewControllerWithCompletionHandler:(void (^)(AUViewControllerBase * __nullable viewController))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreAudioKit.framework/Headers/CAInterAppAudioTransportView.h
// =================================================================================================
// CAInterAppAudioTransportView.h
// =================================================================================================
/*
 File:		CAInterAppAudioTransportView.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */

#import <UIKit/UIKit.h>
#import <AudioUnit/AudioUnit.h>

NS_CLASS_AVAILABLE_IOS(8_0)

NS_ASSUME_NONNULL_BEGIN
@interface CAInterAppAudioTransportView : UIView
@property(getter=isEnabled)							BOOL enabled;

@property(nonatomic,readonly,getter=isPlaying)		BOOL playing;
@property(nonatomic,readonly,getter=isRecording)	BOOL recording;
@property(nonatomic,readonly,getter=isConnected)	BOOL connected;

/* Appearance properties */
@property(nonatomic,strong)UIColor *labelColor;
@property(nonatomic,strong)UIFont  *currentTimeLabelFont;

@property(nonatomic,strong)UIColor *rewindButtonColor;
@property(nonatomic,strong)UIColor *playButtonColor;
@property(nonatomic,strong)UIColor *pauseButtonColor;
@property(nonatomic,strong)UIColor *recordButtonColor;

-(void) setOutputAudioUnit: (AudioUnit) au;

@end
NS_ASSUME_NONNULL_END
// ==========  CoreAudioKit.framework/Headers/CAInterAppAudioSwitcherView.h
// =================================================================================================
// CAInterAppAudioSwitcherView.h
// =================================================================================================
/*
 File:		CAInterAppAudioSwitcherView.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */


#import <AudioUnit/AudioUnit.h>
#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE_IOS(8_0)

NS_ASSUME_NONNULL_BEGIN
@interface CAInterAppAudioSwitcherView : UIView
@property (getter = isShowingAppNames) BOOL showingAppNames; // Defaults to NO

// Node apps should pass their output audio unit
// Host apps should pass null
- (void)setOutputAudioUnit:(nullable AudioUnit)au;
- (CGFloat) contentWidth;

@end
NS_ASSUME_NONNULL_END
// ==========  CoreAudioKit.framework/Headers/CABTMIDICentralViewController.h
// =================================================================================================
// CABTMIDICentralViewController.h
// =================================================================================================
/*
 File:		CABTMIDICentralViewController.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */

#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE_IOS(8_0)
@interface CABTMIDICentralViewController : UITableViewController
@end
