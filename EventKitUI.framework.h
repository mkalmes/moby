// ==========  EventKitUI.framework/Headers/EKEventEditViewController.h
//
//  EKEventEditViewController.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKit/EventKit.h>
#import <EventKitUI/EventKitUIDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKEvent;

/*!
    @enum       EKEventEditViewAction
    @abstract   Represents actions that should cause the edit view controller to be dismissed
 
    @constant   EKEventEditViewActionCanceled    The Cancel button was pressed, or the Done button was pressed, but the event was not dirty.
    @constant   EKEventEditViewActionSaved       The event was saved.
    @constant   EKEventEditViewActionDeleted     The event was deleted, either by the user or by another calendar store.
*/

typedef NS_ENUM(NSInteger, EKEventEditViewAction) {
    EKEventEditViewActionCanceled,
    EKEventEditViewActionSaved,
    EKEventEditViewActionDeleted,
    
    // going away, use spelling above
    EKEventEditViewActionCancelled = EKEventEditViewActionCanceled
};

/*!
    @class      EKEventEditViewController
    @abstract   View controller to create/edit events.
    @discussion You can present this view controller to create a new event or edit an existing
                event. You should present it modally. To create a new event, you can either pass
                nil for the event parameter or pass a partially constructed event. If the event
                you pass has no calendar set, the default calendar as set in Settings will be used.
*/
@protocol EKEventEditViewDelegate;

NS_EXTENSION_UNAVAILABLE_IOS("EventKitUI is not supported in extensions")
EVENTKITUI_CLASS_AVAILABLE(4_0)
@interface EKEventEditViewController : UINavigationController

@property(nonatomic, weak, nullable) id<EKEventEditViewDelegate>  editViewDelegate;

/*!
    @property   eventStore
    @abstract   The event store to use to save events.
    @discussion You must set this before presenting the view controller.
*/
@property(nonatomic, retain, null_unspecified) EKEventStore   *eventStore;

/*!
    @property   event
    @abstract   The event to edit.
    @discussion You must set this before presenting the view controller. You can leave
                it set to nil and a new event will be created for you. If you pass an event
                here and it does not belong to the event store (if set) an exception will be
                raised.
*/
@property(nonatomic, retain, nullable) EKEvent *event;

/*!
    @method     cancelEditing
    @abstract   Ends the editing session discarding any changes to the event.
    @discussion This method simulates the user tapping the Cancel button. The delegate will not 
                receive the eventEditViewController:didCompleteWithAction: message, so you are
                responsible for dismissing the controller after calling this method.
 */
- (void)cancelEditing;

@end

/*!
    @enum       EKEventEditViewDelegate
    @abstract   Delegate protocol for event edit view controller.
*/

@protocol EKEventEditViewDelegate <NSObject>
@required

/*!
    @method     eventEditViewController:didCompleteWithAction:
    @abstract   Called to let delegate know the controller is done editing.
    @discussion When the user presses Cancel, presses Done, or deletes the event, this method
                is called. Your delegate is responsible for dismissing the controller. If the editing
                session is terminated programmatically using cancelEditing, 
                this method will not be called.
 
    @param      controller          the controller in question
    @param      action              the action that is causing the dismissal
*/
- (void)eventEditViewController:(EKEventEditViewController *)controller didCompleteWithAction:(EKEventEditViewAction)action;

@optional

/*!
    @method     eventEditViewControllerDefaultCalendarForNewEvents:
    @abstract   Allows you to supply your own default calendar for new events.
    @discussion This delegate method allows you to control what the editor chooses for the default calendar
                if it needs to fill in a calendar. This might be necessary if you either don't pass an initial
                event to the view controller, or you do, but you did not supply a calendar. In these cases, we
                we set the calendar to a default. If this is not implemented by the delegate, the controller
                will use the store's defaultCalendarForNewEvents.
*/

- (EKCalendar *)eventEditViewControllerDefaultCalendarForNewEvents:(EKEventEditViewController *)controller;


@end

NS_ASSUME_NONNULL_END
// ==========  EventKitUI.framework/Headers/EventKitUIDefines.h
/*
 *  EventKitUIDefines.h
 *  EventKitUI
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifdef __cplusplus
#define EVENTKITUI_EXTERN               extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKITUI_EXTERN               extern __attribute__((visibility ("default")))
#endif

#define EVENTKITUI_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)

#ifndef EKUI_HAS_HEADER
#if defined(__has_include)
#define EKUI_HAS_HEADER(include_path) (__has_include(include_path))
#else
#define EKUI_HAS_HEADER(include_path) (0)
#endif
#endif

#ifndef EKUI_IS_IOS
#if defined(TARGET_OS_IOS)
#define EKUI_IS_IOS (TARGET_OS_IOS)
#else
#define EKUI_IS_IOS (0)
#endif
#endif

#ifndef EKUI_IS_SIMULATOR
#if defined(TARGET_OS_SIMULATOR)
#define EKUI_IS_SIMULATOR (TARGET_OS_SIMULATOR)
#else
#define EKUI_IS_SIMULATOR (0)
#endif
#endif
// ==========  EventKitUI.framework/Headers/EKCalendarChooser.h
//
//  EKCalendarChooser.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUIDefines.h>
#import <EventKit/EventKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, EKCalendarChooserSelectionStyle) {
    EKCalendarChooserSelectionStyleSingle,
    EKCalendarChooserSelectionStyleMultiple
};

typedef NS_ENUM(NSInteger, EKCalendarChooserDisplayStyle) {
    EKCalendarChooserDisplayAllCalendars,
    EKCalendarChooserDisplayWritableCalendarsOnly
};

@protocol EKCalendarChooserDelegate;


EVENTKITUI_EXTERN @interface EKCalendarChooser : UIViewController

- (id)initWithSelectionStyle:(EKCalendarChooserSelectionStyle)selectionStyle
                displayStyle:(EKCalendarChooserDisplayStyle)displayStyle
                  eventStore:(EKEventStore *)eventStore;

// variant to only show calendars for events or reminders.
- (id)initWithSelectionStyle:(EKCalendarChooserSelectionStyle)style 
                displayStyle:(EKCalendarChooserDisplayStyle)displayStyle
                  entityType:(EKEntityType)entityType
                  eventStore:(EKEventStore *)eventStore;

@property(nonatomic, readonly) EKCalendarChooserSelectionStyle    selectionStyle;

@property(nonatomic, weak, nullable) id<EKCalendarChooserDelegate>        delegate;

// When used in a navigation controller (presented modally), you can enable
// the done/cancel buttons and get informed when pressed via the delegate.
@property(nonatomic) BOOL showsDoneButton;
@property(nonatomic) BOOL showsCancelButton;

// Regardless of whether the chooser allows you to select one or multiple
// calendars, the selection is always expressed as a set.
@property(nonatomic, copy) NSSet<EKCalendar *> *selectedCalendars;

@end

@protocol EKCalendarChooserDelegate <NSObject>
@optional

// Called whenever the selection is changed by the user
- (void)calendarChooserSelectionDidChange:(EKCalendarChooser *)calendarChooser;

// These are called when the corresponding button is pressed to dismiss the
// controller. It is up to the recipient to dismiss the chooser.
- (void)calendarChooserDidFinish:(EKCalendarChooser *)calendarChooser;
- (void)calendarChooserDidCancel:(EKCalendarChooser *)calendarChooser;

@end

NS_ASSUME_NONNULL_END
// ==========  EventKitUI.framework/Headers/EventKitUI.h
/*
 *  EventKitUI.h
 *  EventKitUI
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <EventKit/EventKit.h>

#import <EventKitUI/EventKitUIDefines.h>
#import <EventKitUI/EKEventEditViewController.h>
#import <EventKitUI/EKEventViewController.h>
#import <EventKitUI/EKCalendarChooser.h>
// ==========  EventKitUI.framework/Headers/EKEventViewController.h
//
//  EKEventViewController.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUIDefines.h>
#import <EventKitUI/EventKitUIBundle.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEvent, EKEventStore;

typedef NS_ENUM(NSInteger, EKEventViewAction) {
    EKEventViewActionDone,                  // simply closed
    EKEventViewActionResponded,             // event invitation was responded to and saved
    EKEventViewActionDeleted,               // event was deleted
};

/*!
    @class      EKEventViewController
    @abstract   View controller to view event detail.
    @discussion You can use this view controller to display the details of an event. You
                can also optionally choose to allow the user to edit the event by displaying
                an edit button. While you can use this view controller to display events that
                have not been saved, the edit button will not appear in this situation. If
                you have pushed this view controller onto a navigation controller stack, and
                the underlying event gets deleted, this controller will remove itself from
                the stack and clear its event property.
*/
@protocol EKEventViewDelegate;

NS_EXTENSION_UNAVAILABLE_IOS("EventKitUI is not supported in extensions")
EVENTKITUI_CLASS_AVAILABLE(4_0)
@interface EKEventViewController : UIViewController

@property(nonatomic, weak, nullable) id<EKEventViewDelegate>  delegate __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2);

/*!
    @property   event
    @abstract   Specifies the event to view.
    @discussion You must set this prior to displaying the view controller.
*/
@property(nonatomic, retain, null_unspecified) EKEvent *event;

/*!
    @property   allowsEditing
    @abstract   Determines whether Edit button can be shown. 
    @discussion Note that even if this is enabled, the edit button may not appear if this event
                is in a read-only calendar, such as a subscribed calendar. It may also not appear
                if the event was not created by the current user (i.e. it's an event they were
                invited to). And lastly, if the event was never saved, the edit button will not
                appear.
*/
@property(nonatomic) BOOL      allowsEditing;

/*!
    @property   allowsCalendarPreview
    @abstract   Determines whether event can be shown in calendar day view preview.
    @discussion This option only affects calendar invites at present. If the event is an invite,
                and this option is set, a table cell will appear that allows the user to preview 
                the event along with their other events for the day.
*/
@property(nonatomic) BOOL      allowsCalendarPreview;

@end


@protocol EKEventViewDelegate <NSObject>
@required

/*!
 @method     eventViewController:didCompleteWithAction:
 @abstract   Called to let delegate know that an action has occurred that should cause the
             controller to be dismissed.
 @discussion If the user taps a button which deletes the event, or responds to an invite, this
             method is called on the delegate so that the delegate can decide to dismiss
             the view controller. When presented in a popover, it also reports when the Done
             button is pressed.
 
 @param      controller          the controller in question
 @param      action              the action that is triggering the dismissal
 */
- (void)eventViewController:(EKEventViewController *)controller didCompleteWithAction:(EKEventViewAction)action __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2);

@end

NS_ASSUME_NONNULL_END
// ==========  EventKitUI.framework/Headers/EventKitUIBundle.h
//
//  EventKitUIBundle.h
//  EventKitUI
//
//  Created by Greg Novick on 2/26/08.
//  Copyright 2008 Apple Computer, Inc. All rights reserved.
//

#import <EventKitUI/EventKitUIDefines.h>
#import <Foundation/Foundation.h>

EVENTKITUI_EXTERN NSBundle *EventKitUIBundle(void);

// ==========  EventKitUI.framework/Headers/UIFont+EKDayOccurrenceView.h
//
//  UIFont+EKDayOccurrenceView.h
//  EventKitUI
//
//  Created by harry-dev on 4/18/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIFont (EKDayOccurrenceView)

@property (nonatomic, readonly, class) UIFont *ek_defaultOccurrenceSecondaryTextFont;

+ (UIFont *)ek_defaultOccurrencePrimaryTextFontForSizeClass:(UIUserInterfaceSizeClass)sizeClass;
+ (UIFont *)ek_defaultOccurrenceSmallPrimaryTextFontForSizeClass:(UIUserInterfaceSizeClass)sizeClass;

@end

NS_ASSUME_NONNULL_END
