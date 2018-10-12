// ==========  EventKit.framework/Headers/EKCalendar.h
//
//  EKCalendar.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKSource, NSColor;

/*!
    @class       EKCalendar
    @abstract    The EKCalendar class represents a calendar for events.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKCalendar : EKObject

// Create a new calendar in the specified event store. You should use calendarForEntityType in iOS 6 or later.
+ (EKCalendar*)calendarWithEventStore:(EKEventStore *)eventStore NS_DEPRECATED(NA, NA, 4_0, 6_0);

/*!
    @method     calendarForEntityType:
    @abstract   Creates a new autoreleased calendar that may contain the given entity type.
    @discussion You can only create calendars that accept either reminders or events via our API. 
                However, other servers might allow mixing the two (though it is not common).
 
    @param      entityType    The entity type that this calendar may support.
    @param      eventStore    The event store in which to create this calendar.
 */
+ (EKCalendar *)calendarForEntityType:(EKEntityType)entityType eventStore:(EKEventStore *)eventStore NS_AVAILABLE(10_8, 6_0);

/*!
    @property   source
    @abstract   The source representing the 'account' this calendar belongs to.
                This is only settable when initially creating a calendar and then
                effectively read-only after that. That is, you can create a calendar, 
                but you cannot move it to another source.
    @discussion This will be nil for new calendars until you set it.
*/
@property(null_unspecified, nonatomic, strong) EKSource        *source;

/*!
    @property   calendarIdentifier
    @abstract   A unique identifier for the calendar. It is not sync-proof in that a full
                sync will lose this identifier, so you should always have a back up plan for dealing
                with a calendar that is no longer fetchable by this property, e.g. by title, type, color, etc.
                Use [EKEventStore calendarWithIdentifier:] to look up the calendar by this value.
*/
@property(nonatomic, readonly) NSString         *calendarIdentifier NS_AVAILABLE(10_8, 5_0);

/*!
    @property   title
    @abstract   The title of the calendar.
*/
@property(nonatomic, copy)     NSString          *title;

/*!
    @property   type
    @abstract   The type of the calendar as a EKCalendarType. This is actually based on
                what source the calendar is in, as well as whether it is a subscribed calendar.
    @discussion CalDAV subscribed calendars have type EKCalendarTypeCalDAV with isSubscribed = YES. 
*/
@property(nonatomic, readonly)     EKCalendarType     type;

/*!
    @property   allowsContentModifications
    @abstract   Represents whether you can this add, remove, or modify items in this calendar.
*/
@property(nonatomic, readonly) BOOL allowsContentModifications;

/*!
    @property   subscribed
    @abstract   YES if this calendar is a subscribed calendar.
*/
@property(nonatomic, readonly, getter=isSubscribed) BOOL subscribed NS_AVAILABLE(10_8, 5_0);

/*!
    @property   immutable
    @abstract   If this is set to YES, it means you cannot modify any attributes of
                the calendar or delete it. It does NOT imply that you cannot add events 
                or reminders to the calendar.
*/
@property(nonatomic, readonly, getter=isImmutable) BOOL immutable NS_AVAILABLE(10_8, 5_0);

#if TARGET_OS_IPHONE
/*!
    @property   color
    @abstract   Returns the calendar color as a CGColorRef.
    @discussion This will be nil for new calendars until you set it.
*/
@property(null_unspecified, nonatomic) CGColorRef CGColor;
#else
/*!
    @property   color
    @abstract   Returns the calendar color as a NSColor.
    @discussion This will be nil for new calendars until you set it.
*/
@property(null_unspecified, nonatomic, copy) NSColor *color;
#endif

/*!
    @property   supportedEventAvailabilities
    @discussion Returns a bitfield of supported event availabilities, or EKCalendarEventAvailabilityNone
                if this calendar does not support setting availability on an event.
*/
@property(nonatomic, readonly) EKCalendarEventAvailabilityMask supportedEventAvailabilities;

/* 
    @property   allowedEntityTypes
    @discussion Returns the entity types this calendar can contain. While our API only allows creation
                of single-entity calendars, other servers might allow mixed-entity calendars.
*/
@property(nonatomic, readonly) EKEntityMask allowedEntityTypes NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKStructuredLocation.h
//
//  EKStructuredLocation.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKMapItem;

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface EKStructuredLocation : EKObject <NSCopying>

+ (instancetype)locationWithTitle:(NSString *)title;
+ (instancetype)locationWithMapItem:(MKMapItem *)mapItem NS_AVAILABLE(10_11, 9_0);

@property(nullable, nonatomic, strong) NSString     *title;
@property(nonatomic, strong, nullable) CLLocation   *geoLocation;
@property(nonatomic) double                radius; // 0 = use default, unit is meters

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EventKit.h
/*
 *  EventKit.h
 *  EventKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <TargetConditionals.h>
#import <Availability.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || !TARGET_OS_IPHONE

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>
#import <EventKit/EKAlarm.h>
#import <EventKit/EKEventStore.h>
#import <EventKit/EKCalendar.h>
#import <EventKit/EKError.h>
#import <EventKit/EKEvent.h>
#import <EventKit/EKParticipant.h>
#import <EventKit/EKRecurrenceRule.h>
#import <EventKit/EKReminder.h>
#import <EventKit/EKSource.h>
#import <EventKit/EKStructuredLocation.h>

#endif //#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

// ==========  EventKit.framework/Headers/EKRecurrenceDayOfWeek.h
//
//  EKRecurrenceDayOfWeek.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class      EKRecurrenceDayOfWeek
    @abstract   Class which represents a day of the week this recurrence will occur.
    @discussion EKRecurrenceDayOfWeek specifies either a simple day of the week, or the nth instance
                of a particular day of the week, such as the third Tuesday of every month. The week
                number is only valid when used with monthly or yearly recurrences, since it would
                be otherwise meaningless.

                Valid values for dayOfTheWeek are integers 1-7, which correspond to days of the week
                with Sunday = 1. Valid values for weekNumber portion are (+/-)1-53, where a negative
                value indicates a value from the end of the range. For example, in a yearly event -1
                means last week of the year. -1 in a Monthly recurrence indicates the last week of
                the month. 

                The value 0 also indicates the weekNumber is irrelevant (every Sunday, etc.).

                Day-of-week weekNumber values that are out of bounds for the recurrence type will
                result in an exception when trying to initialize the recurrence. In particular,
                weekNumber must be zero when passing EKRecurrenceDayOfWeek objects to initialize a weekly 
                recurrence.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceDayOfWeek : NSObject <NSCopying, NSSecureCoding> {
}

/*!
     @method     dayOfWeek:
     @abstract   Creates an autoreleased object with a day of the week and week number of zero.
*/
+ (instancetype)dayOfWeek:(EKWeekday)dayOfTheWeek;

/*!
     @method     dayOfWeek:weekNumber:
     @abstract   Creates an autoreleased object with a specific day of week and week number.
*/
+ (instancetype)dayOfWeek:(EKWeekday)dayOfTheWeek weekNumber:(NSInteger)weekNumber;

/*!
     @method     initWithDayOfTheWeek:weekNumber:
     @abstract   Creates an day-of-week object with a specific day of week and week number.
*/
- (id)initWithDayOfTheWeek:(EKWeekday)dayOfTheWeek weekNumber:(NSInteger)weekNumber;

/*!
     @property   dayOfTheWeek
     @abstract   The day of the week.
*/
@property(nonatomic, readonly) EKWeekday dayOfTheWeek;

/*!
     @property   weekNumber
     @abstract   The week number.
*/
@property(nonatomic, readonly) NSInteger weekNumber;

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKRecurrenceEnd.h
//
//  EKRecurrenceEnd.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class      EKRecurrenceEnd
    @abstract   Class which represents when a recurrence should end.
    @discussion EKRecurrenceEnd is an attribute of EKRecurrenceRule that defines how long
                the recurrence is scheduled to repeat. The recurrence can be defined either
                with an NSUInteger that indicates the total number times it repeats, or with
                an NSDate, after which it no longer repeats. An event which is set to never
                end should have its EKRecurrenceEnd set to nil.
                 
                If the end of the pattern is defines with an NSDate, the client must pass a
                valid NSDate, nil cannot be passed. If the end of the pattern is defined as
                terms of a number of occurrences, the occurrenceCount passed to the initializer
                must be positive, it cannot be 0. If the client attempts to initialize a
                EKRecurrenceEnd with a nil NSDate or OccurrenceCount of 0, an exception is raised.
                 
                A EKRecurrenceEnd initialized with an end date will return 0 for occurrenceCount.
                One initialized with a number of occurrences will return nil for its endDate.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceEnd : NSObject <NSCopying, NSSecureCoding> {
}

/*!
    @method     recurrenceEndWithEndDate:
    @abstract   Creates an autoreleased recurrence end with a specific end date.
*/
+ (instancetype)recurrenceEndWithEndDate:(NSDate *)endDate;

/*!
    @method     recurrenceEndWithOccurrenceCount:
    @abstract   Creates an autoreleased recurrence end with a maximum occurrence count.
*/
+ (instancetype)recurrenceEndWithOccurrenceCount:(NSUInteger)occurrenceCount;

/*!
    @property   endDate
    @abstract   The end date of this recurrence, or nil if it's count-based.
*/
@property(nonatomic, readonly, nullable) NSDate *endDate;

/*!
    @property   occurrenceCount
    @abstract   The maximum occurrence count, or 0 if it's date-based.
*/
@property(nonatomic, readonly) NSUInteger occurrenceCount;

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKEventStore.h
//
//  EKEventStore.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKCalendar, EKEvent, EKSource, EKReminder, EKCalendarItem;

/*!
    @enum           EKSpan
    @abstract       Values for controlling what occurrences to affect in a recurring event.
    @discussion     This enumerated type is used to indicate the scope of a change being made to a repeating event. EKSpanThisEvent 
                    indicates the changes should apply only to this event, EKSpanFutureEvents indicates the changes should apply to 
                    this event and all future events in the pattern.
    @constant       EKSpanThisEvent        Affect this event only.
    @constant       EKSpanFutureEvents     Affect this event and all after it.
*/

typedef NS_ENUM(NSInteger, EKSpan) {
    EKSpanThisEvent,
    EKSpanFutureEvents
};


typedef void (^EKEventSearchCallback)(EKEvent *event, BOOL *stop);

/*!
    @class       EKEventStore
    @abstract    The EKEventStore class provides an interface for accessing and manipulating calendar events and reminders.
    @discussion  The EKEventStore class is the main point of contact for accessing Calendar data. You must
                 create a EKEventStore object in order to retrieve/add/delete events or reminders from the Calendar database.
                 
                 Events, Reminders, and Calendar objects retrieved from an event store cannot be used with any other event
                 store. It is generally best to hold onto a long-lived instance of an event store, most
                 likely as a singleton instance in your application.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKEventStore : NSObject

/*!
    @method     authorizationStatusForEntityType:
    @discussion Returns the authorization status for the given entity type
 */
+ (EKAuthorizationStatus)authorizationStatusForEntityType:(EKEntityType)entityType NS_AVAILABLE(10_9, 6_0);

/*!
    @method     initWithAccessToEntityTypes:
    @discussion Users are able to grant or deny access to event and reminder data on a per-app basis. To request access to
                event and/or reminder data, instantiate an EKEventStore using this method. This call will not block the
                program while the user is being asked to grant or deny access. Until access has been granted for an entity
                type, this event store will not contain any calendars for that entity type, and any attempt to save entities
                of that entity type will fail. If access is later granted or declined, the event store will broadcast an
                EKEventStoreChangedNotification. You can check the current access status for an entity type
                using +authorizationStatusForEntityType:. The user will only be prompted the first time access is requested; any
                subsequent instantiations of EKEventStore will use the existing permissions.
    @param      entityTypes         A bit mask of entity types to which you want access
*/
- (id)initWithAccessToEntityTypes:(EKEntityMask)entityTypes NS_DEPRECATED(10_8, 10_9, NA, NA);


/*!
        @method     init
 */
- (id)init NS_AVAILABLE(10_9, 4_0);

/*!
    @method     initWithSources:
    @abstract   Creates a new event store that only includes items and calendars for a subset of sources.
    @param      sources The sources you want this event store to recognize. This may include delegate sources.
 */
- (instancetype)initWithSources:(NSArray<EKSource *> *)sources NS_AVAILABLE(10_11, NA);

typedef void(^EKEventStoreRequestAccessCompletionHandler)(BOOL granted, NSError * __nullable error);

/*!
    @method     requestAccessToEntityType:completion:
    @discussion Users are able to grant or deny access to event and reminder data on a per-app basis. To request access to
                event and/or reminder data, call -requestAccessToEntityType:completion:. This will not block the app while
                the user is being asked to grant or deny access.
 
                Until access has been granted for an entity type, the event store will not contain any calendars for that
                entity type, and any attempt to save will fail. The user will only be prompted the first time access is
                requested; any subsequent instantiations of EKEventStore will use the existing permissions. When the user
                taps to grant or deny access, the completion handler will be called on an arbitrary queue.
*/
- (void)requestAccessToEntityType:(EKEntityType)entityType completion:(EKEventStoreRequestAccessCompletionHandler)completion NS_AVAILABLE(10_9, 6_0);

/*!
    @property   eventStoreIdentifier
    @abstract   Returns a unique identifier string representing this calendar store.
*/
@property(nonatomic, readonly) NSString *eventStoreIdentifier;

//----------------------------------------------------
// SOURCES
//----------------------------------------------------

/*!
    @property   delegateSources
    @abstract   Returns an unordered array of sources for all available delegates.
    @discussion By default, delegates are not included in an event store's sources. To work with delegates,
                you can create a new event store and pass in the sources, including sources returned from this
                method, that you're interested in.
    @see        initWithSources:
 */
@property (nonatomic, readonly) NSArray<EKSource *> *delegateSources NS_AVAILABLE(10_11, NA);

/*!
    @property   sources
    @abstract   Returns an unordered array of sources.
*/
@property (nonatomic, readonly) NSArray<EKSource *> *sources NS_AVAILABLE(10_8, 5_0);

/*!
    @method     sourceWithIdentifier:
    @abstract   Returns a source with a specified identifier.
*/
- (nullable EKSource *)sourceWithIdentifier:(NSString *)identifier NS_AVAILABLE(10_8, 5_0);

//----------------------------------------------------
// CALENDARS
//----------------------------------------------------

/*!
    @method     calendars
    @abstract   While this returns an array, the calendars are unordered. This call is deprecated
                 and only returns calendars that support events. If you want reminder calendars
                 you should use calendarsForEntityType:
*/
@property(nonatomic, readonly) NSArray<EKCalendar *> *calendars NS_DEPRECATED(NA, NA, 4_0, 6_0);

/*!
    @method     calendarsForEntityType
    @abstract   Returns calendars that support a given entity type (reminders, events)
 */
- (NSArray<EKCalendar *> *)calendarsForEntityType:(EKEntityType)entityType NS_AVAILABLE(10_8, 6_0);

/*!
    @property   defaultCalendarForNewEvents
    @abstract   Returns the calendar that events should be added to by default.
    @discussion This may be nil if there is no default calendar for new events.
*/
@property(nullable, nonatomic, readonly) EKCalendar *defaultCalendarForNewEvents;

/*!
    @method     defaultCalendarForNewReminders
    @abstract   Returns the calendar that reminders should be added to by default.
    @discussion This may be nil if there is no default calendar for new reminders.
*/
- (nullable EKCalendar *)defaultCalendarForNewReminders NS_AVAILABLE(10_8, 6_0);

/*!
    @method     calendarWithIdentifier:
    @abstract   Returns a calendar with a specified identifier.
*/
- (nullable EKCalendar *)calendarWithIdentifier:(NSString *)identifier NS_AVAILABLE(10_8, 5_0);

/*!
    @method     saveCalendar:commit:error:
    @abstract   Saves changes to a calendar, or adds a new calendar to the database.
    @discussion This method attempts to save the given calendar to the calendar database. It
                returns YES if successful and NO otherwise. Passing a calendar fetched from
                another EKEventStore instance into this function will raise an exception.
                On WatchOS, saving changes is not supported.

    @param      calendar    The calendar to save.
    @param      commit      Pass YES to cause the database to save. You can pass NO to save multiple
                            calendars and then call commit: to save them all at once.
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)saveCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;

/*!
    @method     removeCalendar:commit:error:
    @abstract   Removes a calendar from the database.
    @discussion This method attempts to delete the given calendar from the calendar database. It
                returns YES if successful and NO otherwise. Passing a calendar fetched from
                another EKEventStore instance into this function will raise an exception.

                If the calendar supports multiple entity types (allowedEntityTypes), but the user has 
                not granted you access to all those entity types, then we will delete all of the entity types 
                for which you have access and remove that entity type from the allowedEntityTypes.
                For example: If a calendar supports both events and reminders, but you only have access to reminders,
                we will delete all the reminders and make the calendar only support events.
 
                If you have access to all of its allowedEntityTypes, then it will delete the calendar and
                all of the events and reminders in the calendar.
 
                On WatchOS, modifying the database is not supported.
 
    @param      calendar    The calendar to delete.
    @param      commit      Pass YES to cause the database to save. You can pass NO to batch multiple
                            changes and then call commit: to save them all at once.
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)removeCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;

//----------------------------------------------------
// CALENDAR ITEMS (apply to both reminders and events)
//----------------------------------------------------

/*!
    @method     calendarItemWithIdentifier:
    @abstract   Returns either a reminder or the first occurrence of an event.
*/
- (nullable EKCalendarItem *)calendarItemWithIdentifier:(NSString *)identifier NS_AVAILABLE(10_8, 6_0);

/*!
    @method     calendarItemsWithExternalIdentifier:
    @abstract   Returns either matching reminders or the first occurrences of any events matching
                the given external identifier.
    @discussion This method returns a set of EKEvents or EKReminders with the given external identifier.
                Due to reasons discussed in -[EKCalendarItem calendarItemExternalIdentifier], there may be
                more than one matching calendar item.
 
    @param      externalIdentifier  The value obtained from EKCalendarItem's
                calendarItemExternalIdentifier property
    @result     An unsorted array of EKCalendarItem instances
*/
- (NSArray<EKCalendarItem *> *)calendarItemsWithExternalIdentifier:(NSString *)externalIdentifier NS_AVAILABLE(10_8, 6_0);

//----------------------------------------------------
// EVENTS
//----------------------------------------------------

/*!
    @method     saveEvent:span:error:
    @abstract   Saves changes to an event permanently.
    @discussion This method attempts to save the event to the calendar database. It returns YES if
                successful and NO otherwise. It's possible for this method to return NO, and error
                will be set to nil. This occurs if the event wasn't dirty and didn't need saving. This
                means the correct way to detect failure is a result of NO and a non-nil error parameter.
                Passing an event fetched from another EKEventStore instance into this function will
                raise an exception.

                After an event is successfully saved, it is also put into sync with the database, meaning
                that all fields you did not change will be updated to the latest values. If you save the
                event, but it was deleted by a different store/process, you will effectively recreate the
                event as a new event.
 
                On WatchOS, saving changes is not supported.
 
    @param      event       The event to save.
    @param      span        The span to use (this event, or this and future events).
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error NS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED;

/*!
    @method     removeEvent:span:error:
    @abstract   Removes an event from the calendar store.
    @discussion This method attempts to remove the event from the calendar database. It returns YES if
                successful and NO otherwise. It's possible for this method to return NO, and error
                will be set to nil. This occurs if the event wasn't ever added and didn't need removing. This
                means the correct way to detect failure is a result of NO and a non-nil error parameter.
                Passing an event from another CalendarStore into this function will raise an exception. After
                an event is removed, it is no longer tied to this calendar store, and all data in the event
                is cleared except for the eventIdentifier.
 
                On WatchOS, modifying the database is not supported.
 
    @param      event       The event to save.
    @param      span        The span to use (this event, or this and future events).
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error NS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED;

// These variants of the above allow you to batch changes by passing NO to commit. You can commit
// all changes later with [EKEventStore commit:]
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;

/*!
    @method     eventWithIdentifier:
    @abstract   Returns the first occurrence of an event matching the given event identifier.
 
    @param      identifier   The eventIdentifier to search for.
    @result     An EKEvent object, or nil if not found.
*/
- (nullable EKEvent *)eventWithIdentifier:(NSString *)identifier;

/*!
    @method     eventsMatchingPredicate:
    @abstract   Searches for events that match the given predicate.
    @discussion This call executes a search for the events indicated by the predicate passed to it.
                It only includes events which have been committed (e.g. those saved using 
                saveEvent:commit:NO are not included until commit: is called.)
 
                It is synchronous. If you want async behavior, you should either use dispatch_async or
                NSOperation to run the query someplace other than the main thread, and then funnel the
                array back to the main thread.
 
    @param      predicate   The predicate to invoke. If this predicate was not created with the predicate
                            creation functions in this class, an exception is raised.
    @result     An array of EKEvent objects, or nil. There is no guaranteed order to the events.
*/
- (NSArray<EKEvent *> *)eventsMatchingPredicate:(NSPredicate *)predicate;

/*!
    @method     enumerateEventsMatchingPredicate:usingBlock:
    @abstract   Searches for events that match the given predicate.
    @discussion This call executes a search for the events indicated by the predicate passed to it, calling
                the block specified in the callback parameter for each event. It only includes events which 
                have been committed (e.g. those saved using saveEvent:commit:NO are not included until commit: is called.)
 
                This method is synchronous. If you want async behavior, you should either use dispatch_async or
                NSOperation to run the query someplace other than the main thread.
 
    @param      predicate   The predicate to invoke. If this predicate was not created with the predicate
                            creation functions in this class, an exception is raised.
    @param      block       The block to call for each event. Your block should return YES in the stop
                            parameter to stop iterating.
*/
- (void)enumerateEventsMatchingPredicate:(NSPredicate *)predicate usingBlock:(EKEventSearchCallback)block;

/*!
    @method     predicateForEventsWithStartDate:endDate:calendars:
    @abstract   Creates a predicate for use with eventsMatchingPredicate or enumerateEventsMatchingPredicate:usingBlock:.
    @discussion Creates a simple query predicate to search for events within a certain date range. At present,
                this will return events in the default time zone ([NSTimeZone defaultTimeZone]).

                For performance reasons, this method will only return events within a four year timespan.
                If the date range between the startDate and endDate is greater than four years, then it will be shortened 
                to the first four years.
 
    @param      startDate   The start date.
    @param      endDate     The end date.
    @param      calendars   The calendars to search for events in, or nil to search all calendars.
*/
- (NSPredicate *)predicateForEventsWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate calendars:(nullable NSArray<EKCalendar *> *)calendars;

//----------------------------------------------------
// REMINDERS
//----------------------------------------------------

/*!
    @method     saveReminder:commit:error:
    @abstract   Saves changes to a reminder.
    @discussion This method attempts to save the reminder to the event store database. It returns YES if
                successful and NO otherwise. Passing a reminder fetched from another EKEventStore instance
                into this function will raise an exception.

                After a reminder is successfully saved, its fields are updated to the latest values in
                the database.
 
                On WatchOS, saving changes is not supported.

    @param      reminder    The reminder to save.
    @param      commit      Whether to save to the database or not. Pass NO to batch changes together and
                            commit with [EKEventStore commit:].
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)saveReminder:(EKReminder *)reminder commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 6_0) __WATCHOS_PROHIBITED;

/*!
    @method     removeReminder:commit:error:
    @abstract   Removes a reminder from the event store.
    @discussion This method attempts to remove the reminder from the event store database. It returns YES if
                successful and NO otherwise. Passing a reminder from another EKEventStore into this function
                will raise an exception. After a reminder is removed, it is no longer tied to this event store.
 
                On WatchOS, modifying the database is not supported.

    @param      reminder    The reminder to save.
    @param      commit      Whether to save to the database or not. Pass NO to batch changes together and
                            commit with [EKEventStore commit:].
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)removeReminder:(EKReminder *)reminder commit:(BOOL)commit error:(NSError **)error NS_AVAILABLE(10_8, 6_0) __WATCHOS_PROHIBITED;

/*!
    @method     fetchRemindersMatchingPredicate:completion:
    @abstract   Fetches reminders asynchronously.
    @discussion This method fetches reminders asynchronously and returns a value which can be
                used in cancelFetchRequest: to cancel the request later if desired. The completion
                block is called with an array of reminders that match the given predicate (or potentially nil).
                This only includes reminders which have been committed (e.g. those saved using 
                saveReminder:commit:NO are not included until commit: is called.)
*/
- (id)fetchRemindersMatchingPredicate:(NSPredicate *)predicate completion:(void (^)(NSArray<EKReminder *> * __nullable reminders))completion NS_AVAILABLE(10_8, 6_0);

/*!
    @method     cancelFetchRequest:
    @discussion Given a value returned from fetchRemindersMatchingPredicate, this method can be used to
                cancel the request. Once called, the completion block specified in fetchReminders... will
                not be called.
*/
- (void)cancelFetchRequest:(id)fetchIdentifier NS_AVAILABLE(10_8, 6_0);

/*!
    @method     predicateForRemindersInCalendars:
    @abstract   Fetch all reminders in a set of calendars.
    @discussion You can pass nil for calendars to fetch from all available calendars.
*/
- (NSPredicate *)predicateForRemindersInCalendars:(nullable NSArray<EKCalendar *> *)calendars NS_AVAILABLE(10_8, 6_0);

/*!
    @method     predicateForIncompleteRemindersWithDueDateStarting:ending:calendars:
    @abstract   Fetch incomplete reminders in a set of calendars.
    @discussion You can use this method to search for incomplete reminders due in a range.
                You can pass nil for start date to find all reminders due before endDate.
                You can pass nil for both start and end date to get all incomplete reminders
                in the specified calendars.
                You can pass nil for calendars to fetch from all available calendars.
*/
- (NSPredicate *)predicateForIncompleteRemindersWithDueDateStarting:(nullable NSDate *)startDate ending:(nullable NSDate *)endDate calendars:(nullable NSArray<EKCalendar *> *)calendars NS_AVAILABLE(10_8, 6_0);


/*!
    @method     predicateForCompletedRemindersWithCompletionDateStarting:ending:calendars:
    @abstract   Fetch completed reminders in a set of calendars.
    @discussion You can use this method to search for reminders completed between a range of dates.
                You can pass nil for start date to find all reminders completed before endDate.
                You can pass nil for both start and end date to get all completed reminders
                in the specified calendars.
                You can pass nil for calendars to fetch from all available calendars.
*/
- (NSPredicate *)predicateForCompletedRemindersWithCompletionDateStarting:(nullable NSDate *)startDate ending:(nullable NSDate *)endDate calendars:(nullable NSArray<EKCalendar *> *)calendars NS_AVAILABLE(10_8, 6_0);

//----------------------------------------------------
// COMMIT, RESET, ROLLBACK
//----------------------------------------------------

/*!
    @method     commit:
    @abstract   Commits pending changes to the database.
    @discussion If you use saveCalendar/saveEvent/removeCalendar/removeEvent, etc. and you pass NO to their
                parameter, you are batching changes for a later commit. This method does that commit. This
                allows you to save the database only once for many additions or changes.  If you pass
                YES to methods' commit parameter, then you don't need to call this method.
 
                This method will return YES as long as nothing went awry, even if nothing was actually
                committed. If it returns NO, error should contain the reason it became unhappy.
 
                On WatchOS, modifying the database is not supported.
*/
- (BOOL)commit:(NSError **)error NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;

/*!
    @method     reset
    @abstract   Resets the event store.
    @discussion You can use this method to forget ALL changes made to the event store (all additions, all
                fetched objects, etc.). It essentially is as if you released the store and then created a
                new one. It brings it back to its initial state. All objects ever created/fetched, etc.
                using this store are no longer connected to it and are considered invalid.
*/
- (void)reset NS_AVAILABLE(10_8, 5_0);

/*!
    @method     refreshSourcesIfNecessary
    @abstract   Cause a sync to potentially occur taking into account the necessity of it.
    @discussion You can call this method to pull new data from remote sources.  
                This only updates the event store's data.  If you want to update your objects after 
                refreshing the sources, you should call refresh on each of them afterwards.
                On iOS, this sync only occurs if deemed necessary.  
                On OS X, this will occur regardless of necessity, but may change in a future release to match the iOS behavior.
                On WatchOS, initiating sync is not available. Sync will occur automatically with the paired iOS device.
 */
- (void)refreshSourcesIfNecessary NS_AVAILABLE(10_8, 5_0) __WATCHOS_PROHIBITED;

@end

/*!
    @constant   EKEventStoreChangedNotification
    @discussion Notification name sent out when the database is changed by either an external process,
                another event store in the same process, or by calling saveEvent: or removeEvent: on a
                store you are managing. When you receive this notification, you should consider all EKEvent
                instances you have to be invalid. If you had selected events for a date range using
                eventsMatchingPredicate, etc. for display, you should release them and re-fetch the events
                again. If you have an event you are actively using (e.g. you are currently viewing details
                for it or editing it), you can call [EKEvent refresh] to try to revalidate it against the
                latest state of the database. If that method returns YES, you can continue to use the event,
                otherwise, you should release it and abandon what you were doing with it. The view
                controllers provided by EventKitUI automatically deal with this for you.
                This notification will also be posted if access to events or reminders is changed by the user.
*/
EVENTKIT_EXTERN NSString *const EKEventStoreChangedNotification NS_AVAILABLE(10_8, 4_0);

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKObject.h
//
//  EKObject.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface EKObject : NSObject

// Returns YES if this object or any sub-object (alarm, etc.) has uncommitted changes.
@property (nonatomic, readonly) BOOL hasChanges;

// Returns YES if this object has never been saved.
#if defined(__cplusplus)
- (BOOL)isNew;
#else
@property (nonatomic, readonly, getter=isNew) BOOL new;
#endif

// If this object is not new, this method will unload all loaded properties and clear any dirty state
- (void)reset;

// If this object is not new, this method will unload dirty state only.
- (void)rollback;

// Determines if the object is still valid (i.e. it still exists in the database), and unloads all
// properties that have not been modified. If this ever returns NO, it indicates the record was deleted
// and this instance should be discarded and no longer referenced.
- (BOOL)refresh;

@end
// ==========  EventKit.framework/Headers/EKReminder.h
//
//  EKReminder.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKCalendarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendar, EKRecurrenceRule, EKAlarm;

/*!
    @class      EKReminder
    @abstract   The EKReminder class represents a reminder (task/todo).
*/
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface EKReminder : EKCalendarItem

/*!
    @method     reminderWithEventStore:
    @abstract   Creates a new reminder in the given event store.
*/
+ (EKReminder *)reminderWithEventStore:(EKEventStore *)eventStore;

/*!
    @property   startDateComponents
    @abstract   The start date of the task, as date components.
    @discussion The use of date components allows the start date and its time zone to be represented in a single property. 
                A nil time zone represents a floating date.  Setting a date component without a hour, minute and second component will set allDay to YES.
                If you set this property, the calendar must be set to NSCalendarIdentifierGregorian. An exception is raised otherwise.
*/
@property(nonatomic, copy, nullable) NSDateComponents *startDateComponents;

/*!
    @property   dueDateComponents
    @abstract   The date by which this reminder should be completed.
    @discussion The use of date components allows the due date and its time zone to be represented in a single property. 
                A nil time zone represents a floating date.  Setting a date component without a hour, minute and second component will set allDay to YES.
                If you set this property, the calendar must be set to NSCalendarIdentifierGregorian. An exception is raised otherwise.
 
                On iOS, if you set the due date for a reminder, you must also set a start date, otherwise you will receive
                an error (EKErrorNoStartDate) when attempting to save this reminder. This is not a requirement on OS X.
*/
@property(nonatomic, copy, nullable) NSDateComponents *dueDateComponents;

//  These two properties are inextricably linked.  Setting completed to be YES, will set the completedDate to be now,
//  and setting any completedDate will change completed to be YES. Similarly, setting completed to be NO will set
//  the completedDate to be nil, and setting the completedDate changes completed to NO.
//  Note, you may encounter the case where isCompleted is YES, but completionDate is nil, if the reminder was completed using a different client.

/*!
    @property   completed
    @abstract   Whether or not the reminder is completed. 
    @discussion Setting it to YES will set the completed date to the current date. 
                Setting it to NO will set the completed date to nil.
*/
@property(nonatomic, getter=isCompleted) BOOL completed;

/*!
    @property   completionDate
    @abstract   The date on which this reminder was completed.
*/
@property(nonatomic, copy, nullable) NSDate *completionDate;

/*!
    @property   priority
    @abstract   The priority of the reminder.
    @discussion Priorities run from 1 (highest) to 9 (lowest).  A priority of 0 means no priority.
                Saving a reminder with any other priority will fail.
                Per RFC 5545, priorities of 1-4 are considered "high," a priority of 5 is "medium," and priorities of 6-9 are "low."
 */
@property(nonatomic) NSUInteger priority;

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKRecurrenceRule.h
//
//  EKRecurrenceRule.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKRecurrenceEnd.h>
#import <EventKit/EKRecurrenceDayOfWeek.h>
#import <EventKit/EKTypes.h>
#import <EventKit/EKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendarItem;

/*!
    @class      EKRecurrenceRule
    @abstract   Represents how an event repeats.
    @discussion This class describes the recurrence pattern for a repeating event. The recurrence rules that 
                can be expressed are not restricted to the recurrence patterns that can be set in Calendar's UI. 
 
                It is currently not possible to directly modify a EKRecurrenceRule or any of its properties. 
                This functionality is achieved by creating a new EKRecurrenceRule, and setting an event to use the new rule. 
                When a new recurrence rule is set on an EKEvent, that change is not saved until the client 
                has passed the modified event to EKEventStore's saveEvent: method.
 */
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceRule : EKObject <NSCopying>

/*!
    @method     initRecurrenceWithFrequency:interval:end:
    @abstract   Simple initializer to create a recurrence.
    @discussion This is used to create a simple recurrence with a specific type, interval and end. If interval is
                0, an exception is raised. The end parameter can be nil.
*/
- (instancetype)initRecurrenceWithFrequency:(EKRecurrenceFrequency)type interval:(NSInteger)interval end:(nullable EKRecurrenceEnd *)end;

/*!
    @method     initRecurrenceWithFrequency:interval:daysOfTheWeek:daysOfTheMonth:monthsOfTheYear:weeksOfTheYear:daysOfTheYear:setPositions:end:
    @abstract   The designated initializer.
    @discussion This can be used to build any kind of recurrence rule. But be aware that certain combinations make
                no sense and will be ignored. For example, if you pass daysOfTheWeek for a daily recurrence, they
                will be ignored.
    @param      type            The type of recurrence
    @param      interval        The interval. Passing zero will raise an exception.
    @param      daysOfTheWeek   An array of EKRecurrenceDayOfWeek objects. Valid for all recurrence types except daily. Ignored otherwise.
                                Corresponds to the BYDAY value in the iCalendar specification.
    @param      daysOfTheMonth  An array of NSNumbers ([+/-] 1 to 31). Negative numbers infer counting from the end of the month.
                                For example, -1 means the last day of the month. Valid only for monthly recurrences. Ignored otherwise.
                                Corresponds to the BYMONTHDAY value in the iCalendar specification.
    @param      monthsOfTheYear An array of NSNumbers (1 to 12). Valid only for yearly recurrences. Ignored otherwise. Corresponds to
                                the BYMONTH value in the iCalendar specification.
    @param      weeksOfTheYear  An array of NSNumbers ([+/1] 1 to 53). Negative numbers infer counting from the end of the year.
                                For example, -1 means the last week of the year. Valid only for yearly recurrences. Ignored otherwise.
                                Corresponds to the BYWEEKNO value in the iCalendar specification.
    @param      daysOfTheYear   An array of NSNumbers ([+/1] 1 to 366). Negative numbers infer counting from the end of the year.
                                For example, -1 means the last day of the year. Valid only for yearly recurrences. Ignored otherwise.
                                Corresponds to the BYYEARDAY value in the iCalendar specification.
    @param      setPositions    An array of NSNumbers ([+/1] 1 to 366). Used at the end of recurrence computation to filter the list
                                to the positions specified. Negative numbers indicate starting at the end, i.e. -1 indicates taking the
                                last result of the set. Valid when daysOfTheWeek, daysOfTheMonth, monthsOfTheYear, weeksOfTheYear, or 
                                daysOfTheYear is passed. Ignored otherwise. Corresponds to the BYSETPOS value in the iCalendar specification.
    @param      end             The recurrence end, or nil.
*/
- (instancetype)initRecurrenceWithFrequency:(EKRecurrenceFrequency)type
                         interval:(NSInteger)interval 
                    daysOfTheWeek:(nullable NSArray<EKRecurrenceDayOfWeek *> *)days
                   daysOfTheMonth:(nullable NSArray<NSNumber *> *)monthDays
                  monthsOfTheYear:(nullable NSArray<NSNumber *> *)months
                   weeksOfTheYear:(nullable NSArray<NSNumber *> *)weeksOfTheYear
                    daysOfTheYear:(nullable NSArray<NSNumber *> *)daysOfTheYear
                     setPositions:(nullable NSArray<NSNumber *> *)setPositions
                              end:(nullable EKRecurrenceEnd *)end;

/*  Properties that exist in all EKRecurrenceRules  */

/*!
    @property       calendarIdentifier;
    @discussion     Calendar used by this recurrence rule.
*/
@property(nonatomic, readonly) NSString *calendarIdentifier;

/*!
    @property       recurrenceEnd
    @discussion     This property defines when the the repeating event is scheduled to end. The end date can be specified by a number of
                    occurrences, or with an end date.
*/
@property(nonatomic, copy, nullable) EKRecurrenceEnd *recurrenceEnd;

/*!
    @property       frequency
    @discussion     This property designates the unit of time used to describe the recurrence pattern.
*/
@property(nonatomic, readonly) EKRecurrenceFrequency frequency;

/*!
    @property       interval
    @discussion     The interval of a EKRecurrenceRule is an integer value which specifies how often the recurrence rule repeats
                    over the unit of time described by the EKRecurrenceFrequency. For example, if the EKRecurrenceFrequency is
                    EKRecurrenceWeekly, then an interval of 1 means the pattern is repeated every week. A value of 2
                    indicates it is repeated every other week, 3 means every third week, and so on. The value must be a
                    positive integer; 0 is not a valid value, and nil will be returned if the client attempts to initialize a
                    rule with a negative or zero interval. 
*/
@property(nonatomic, readonly) NSInteger interval;

/*!
    @property       firstDayOfTheWeek
    @discussion     Recurrence patterns can specify which day of the week should be treated as the first day. Possible values for this
                    property are integers 0 and 1-7, which correspond to days of the week with Sunday = 1. Zero indicates that the 
                    property is not set for this recurrence. The first day of the week only affects the way the recurrence is expanded
                    for weekly recurrence patterns with an interval greater than 1. For those types of recurrence patterns, the 
                    Calendar framework will set firstDayOfTheWeek to be 2 (Monday). In all other cases, this property will be set 
                    to zero. The iCalendar spec stipulates that the default value is Monday if this property is not set.
*/
@property(nonatomic, readonly) NSInteger firstDayOfTheWeek;


/*  Properties that are only valid for certain EKRecurrenceRules  */

//  The properties that follow are only valid for certain recurrence rules, and are always arrays. For recurrence rules
//  that can be expressed with one of the simple initializers, the arrays will contain a single object, corresponding 
//  to the day of the week, the day of the month, the "NthWeekDay" (for example, the fourth Thursday), or the month of 
//  the year the event recurs. The objects will be NSNumbers, except in the "NthWeekDay" case just mentioned, when
//  the array will contain a CalNthWeekDay instead of an NSNumber.
//  
//  Repeating events using one of the advanced initializers may recur multiple times in the specified time period, for 
//  example, the first and sixteenth days of a month. When this is true, the arrays may contain more than one entry.
//  
//  These properties will only be valid for certain EKRecurrenceRules, depending on how the rule's recurrence is 
//  defined. The constraints on when these properties is valid are described below. When these constraints are not met,
//  the property's value will be nil.

/*!
    @property       daysOfTheWeek
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyWeekly, EKRecurrenceFrequencyMonthly, or 
                    EKRecurrenceFrequencyYearly. This property can be accessed as an array containing one or more EKRecurrenceDayOfWeek objects
                    corresponding to the days of the week the event recurs. For all other EKRecurrenceRules, this property is nil.
                    This property corresponds to BYDAY in the iCalendar specification.
*/
@property(nonatomic, readonly, nullable) NSArray<EKRecurrenceDayOfWeek *> *daysOfTheWeek;

/*!
    @property       daysOfTheMonth
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyMonthly, and that were initialized 
                    with one or more specific days of the month (not with a day of the week and week of the month). This property can be
                    accessed as an array containing one or more NSNumbers corresponding to the days of the month the event recurs.
                    For all other EKRecurrenceRules, this property is nil. This property corresponds to BYMONTHDAY in the iCalendar 
                    specification.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *daysOfTheMonth;

/*!
    @property       daysOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the days of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYYEARDAY in the iCalendar specification. It should
                    contain values between 1 to 366 or -366 to -1.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *daysOfTheYear;

/*!
    @property       weeksOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the weeks of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYWEEK in the iCalendar specification. It should
                    contain integers from 1 to 53 or -1 to -53.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *weeksOfTheYear;

/*!
    @property       monthsOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the months of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYMONTH in the iCalendar specification.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *monthsOfTheYear;

/*!
    @property       setPositions
    @discussion     This property is valid for rules which have a valid daysOfTheWeek, daysOfTheMonth, weeksOfTheYear, or monthsOfTheYear property. 
                    It allows you to specify a set of ordinal numbers to help choose which objects out of the set of selected events should be
                    included. For example, setting the daysOfTheWeek to Monday-Friday and including a value of -1 in the array would indicate
                    the last weekday in the recurrence range (month, year, etc). This value corresponds to the iCalendar BYSETPOS property.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *setPositions;

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKTypes.h
//
//  EKTypes.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @enum       EKAuthorizationStatus
    @abstract   This enumerated type is used to indicate the currently granted authorization status for a specific
                entity type.
    @constant   EKAuthorizationStatusNotDetermined  The user has not yet made a choice regarding whether this application
                                                    may access the service.
    @constant   EKAuthorizationStatusRestricted     This application is not authorized to access the service.
                                                    The user cannot change this application’s status, possibly due to
                                                    active restrictions such as parental controls being in place.
    @constant   EKAuthorizationStatusDenied         The user explicitly denied access to the service for this application.
    @constant   EKAuthorizationStatusAuthorized     This application is authorized to access the service.
 */
typedef NS_ENUM(NSInteger, EKAuthorizationStatus) {
    EKAuthorizationStatusNotDetermined = 0,
    EKAuthorizationStatusRestricted,
    EKAuthorizationStatusDenied,
    EKAuthorizationStatusAuthorized,
} NS_AVAILABLE(10_9, 6_0);


typedef NS_ENUM(NSInteger, EKWeekday) {
    EKWeekdaySunday = 1,
    EKWeekdayMonday,
    EKWeekdayTuesday,
    EKWeekdayWednesday,
    EKWeekdayThursday,
    EKWeekdayFriday,
    EKWeekdaySaturday,
    
    EKSunday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdaySunday instead") = EKWeekdaySunday,
    EKMonday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayMonday instead") = EKWeekdayMonday,
    EKTuesday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayTuesday instead") = EKWeekdayTuesday,
    EKWednesday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayWednesday instead") = EKWeekdayWednesday,
    EKThursday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayThursday instead") = EKWeekdayThursday,
    EKFriday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayFriday instead") = EKWeekdayFriday,
    EKSaturday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdaySaturday instead") = EKWeekdaySaturday,
};

/*!
    @enum       EKRecurrenceFrequency
    @abstract   The frequency of a recurrence
    @discussion EKRecurrenceFrequency designates the unit of time used to describe the recurrence.
                It has four possible values, which correspond to recurrence rules that are defined
                in terms of days, weeks, months, and years.
*/
typedef NS_ENUM(NSInteger, EKRecurrenceFrequency) {
    EKRecurrenceFrequencyDaily,
    EKRecurrenceFrequencyWeekly,
    EKRecurrenceFrequencyMonthly,
    EKRecurrenceFrequencyYearly
};

/*!
 @enum       EKParticipantType
 @abstract   Value representing the type of attendee.
 */
typedef NS_ENUM(NSInteger, EKParticipantType) {
    EKParticipantTypeUnknown,
    EKParticipantTypePerson,
    EKParticipantTypeRoom,
    EKParticipantTypeResource,
    EKParticipantTypeGroup
};

/*!
 @enum       EKParticipantRole
 @abstract   Value representing the role of a meeting participant.
 */
typedef NS_ENUM(NSInteger, EKParticipantRole) {
    EKParticipantRoleUnknown,
    EKParticipantRoleRequired,
    EKParticipantRoleOptional,
    EKParticipantRoleChair,
    EKParticipantRoleNonParticipant
};

/*!
 @enum       EKParticipantScheduleStatus
 @abstract   Value representing the status of a meeting invite.
 
 @constant   EKParticipantScheduleStatusNone                     Default value. Indicates that no
                                                                 invitation has been sent yet.
 @constant   EKParticipantScheduleStatusPending                  The invitation is in the process of being
                                                                 sent.
 @constant   EKParticipantScheduleStatusSent                     The invitation has been sent, but we have
                                                                 no way of determing if it was successfully
                                                                 delivered.
 @constant   EKParticipantScheduleStatusDelivered                The invitation has been sent and
                                                                 successfully delivered.
 @constant   EKParticipantScheduleStatusRecipientNotRecognized   The invitation wasn't delivered because we
                                                                 source doesn't recognize the recipient.
 @constant   EKParticipantScheduleStatusNoPrivileges             The invitation wasn't delivered because of
                                                                 insufficient privileges.
 @constant   EKParticipantScheduleStatusDeliveryFailed           The invitation wasn't delivered most
                                                                 likely due to a temporary failure.
 @constant   EKParticipantScheduleStatusCannotDeliver            The invitation wasn't delivered because
                                                                 we're unsure how to deliver it. This is a
                                                                 permanent failure.
 @constant   EKParticipantScheduleStatusRecipientNotAllowed      The invitation wasn't delivered because
                                                                 scheduling with the participant isn't
                                                                 allowed. This is a permanent failure.
 */
typedef NS_ENUM(NSInteger, EKParticipantScheduleStatus) {
    EKParticipantScheduleStatusNone,
    EKParticipantScheduleStatusPending,
    EKParticipantScheduleStatusSent,
    EKParticipantScheduleStatusDelivered,
    EKParticipantScheduleStatusRecipientNotRecognized,
    EKParticipantScheduleStatusNoPrivileges,
    EKParticipantScheduleStatusDeliveryFailed,
    EKParticipantScheduleStatusCannotDeliver,
    EKParticipantScheduleStatusRecipientNotAllowed,
};

/*!
 @enum       EKParticipantStatus
 @abstract   Value representing the status of a meeting participant.
 */
typedef NS_ENUM(NSInteger, EKParticipantStatus) {
    EKParticipantStatusUnknown,
    EKParticipantStatusPending,
    EKParticipantStatusAccepted,
    EKParticipantStatusDeclined,
    EKParticipantStatusTentative,
    EKParticipantStatusDelegated,
    EKParticipantStatusCompleted,
    EKParticipantStatusInProcess
};

/*!
 @enum       EKCalendarType
 @abstract   An enum representing the type of a calendar.
 
 @constant   EKCalendarTypeLocal        This calendar is sync'd from either Mobile Me or tethered.
 @constant   EKCalendarTypeCalDAV       This calendar is from a CalDAV server.
 @constant   EKCalendarTypeExchange     This calendar comes from an Exchange server.
 @constant   EKCalendarTypeSubscription This is a locally subscribed calendar.
 @constant   EKCalendarTypeBirthday     This is the built-in birthday calendar.
 */

typedef NS_ENUM(NSInteger, EKCalendarType) {
    EKCalendarTypeLocal,
    EKCalendarTypeCalDAV,
    EKCalendarTypeExchange,
    EKCalendarTypeSubscription,
    EKCalendarTypeBirthday
};

// Event availability support (free/busy)
typedef NS_OPTIONS(NSUInteger, EKCalendarEventAvailabilityMask) {
    EKCalendarEventAvailabilityNone         = 0,    // calendar doesn't support event availability
    
    EKCalendarEventAvailabilityBusy         = (1 << 0),
    EKCalendarEventAvailabilityFree         = (1 << 1),
    EKCalendarEventAvailabilityTentative    = (1 << 2),
    EKCalendarEventAvailabilityUnavailable  = (1 << 3),
};

typedef NS_ENUM(NSInteger, EKSourceType) {
    EKSourceTypeLocal,
    EKSourceTypeExchange,
    EKSourceTypeCalDAV,
    EKSourceTypeMobileMe,
    EKSourceTypeSubscribed,
    EKSourceTypeBirthdays
};

/*!
 @enum       EKEntityType
 @abstract   A value which specifies an entity type of event or reminder.
 */
typedef NS_ENUM(NSUInteger, EKEntityType) {
    EKEntityTypeEvent,
    EKEntityTypeReminder
};

/*!
 @enum       EKEntityMask
 @abstract   A bitmask based on EKEntityType that can be used to specify multiple entities at once.
 */
typedef NS_OPTIONS(NSUInteger, EKEntityMask) {
    EKEntityMaskEvent      = (1 << EKEntityTypeEvent),
    EKEntityMaskReminder   = (1 << EKEntityTypeReminder)
};

/*!
 @enum       EKAlarmProximity
 @abstract   A value indicating whether an alarm is triggered by entering or exiting a geofence.
 
 @constant   EKAlarmProximityNone       The alarm has no proximity trigger.
 @constant   EKAlarmProximityEnter      The alarm is set to fire when entering a region (geofence).
 @constant   EKAlarmProximityLeave      The alarm is set to fire when leaving a region (geofence).
 */
typedef NS_ENUM(NSInteger, EKAlarmProximity) {
    EKAlarmProximityNone,
    EKAlarmProximityEnter,
    EKAlarmProximityLeave
};

/*!
 @enum       EKAlarmType
 @abstract   A value which specifies the action that occurs when the alarm is triggered.
 
 @constant   EKAlarmTypeDisplay          The alarm displays a message.
 @constant   EKAlarmTypeAudio            The alarm plays a sound.
 @constant   EKAlarmTypeProcedure        The alarm opens a URL.
 @constant   EKAlarmTypeEmail            The alarm sends an email.
 */
typedef NS_ENUM(NSInteger, EKAlarmType) {
    EKAlarmTypeDisplay,
    EKAlarmTypeAudio,
    EKAlarmTypeProcedure,
    EKAlarmTypeEmail
};

/*!
 @enum       EKReminderPriority
 @abstract   A priority for a reminder.
 @discussion RFC 5545 allows priority to be specified with an integer in the range of 0-9,
             with 0 representing an undefined priority, 1 the highest priority, and 9 the lowest priority.
             Clients are encouraged to use these values when setting a reminders's priority,
             but is is possible to specify any integer value from 0 to 9.
 
 @constant   EKReminderPriorityNone          The reminder has no priority set.
 @constant   EKReminderPriorityHigh          The reminder is high priority.
 @constant   EKReminderPriorityMedium        The reminder is medium priority.
 @constant   EKReminderPriorityLow           The reminder is low priority.
 */
typedef NS_ENUM(NSUInteger, EKReminderPriority) {
    EKReminderPriorityNone     = 0,
    EKReminderPriorityHigh     = 1,
    EKReminderPriorityMedium   = 5,
    EKReminderPriorityLow      = 9
};

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKEvent.h
//
//  EKEvent.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKCalendarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendar, EKRecurrenceRule, EKAlarm, EKParticipant, EKStructuredLocation;

typedef NS_ENUM(NSInteger, EKEventAvailability) {
    EKEventAvailabilityNotSupported = -1,
    EKEventAvailabilityBusy = 0,
    EKEventAvailabilityFree,
    EKEventAvailabilityTentative,
    EKEventAvailabilityUnavailable
};

typedef NS_ENUM(NSInteger, EKEventStatus) {
    EKEventStatusNone = 0,
    EKEventStatusConfirmed,
    EKEventStatusTentative,
    EKEventStatusCanceled,
};


/*!
    @class      EKEvent
    @abstract   The EKEvent class represents an occurrence of an event.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKEvent : EKCalendarItem

/*!
    @method     eventWithEventStore:
    @abstract   Creates a new autoreleased event object.
*/
+ (EKEvent *)eventWithEventStore:(EKEventStore *)eventStore;

/*!
    @property   eventIdentifier
    @abstract   A unique identifier for this event.
    @discussion This identifier can be used to look the event up using [EKEventStore eventWithIdentifier:].
                You can use this not only to simply fetch the event, but also to validate the event
                has not been deleted out from under you when you get an external change notification
                via the EKEventStore database changed notification. If eventWithIdentifier: returns nil,
                the event was deleted.

                Please note that if you change the calendar of an event, this ID will likely change. It is
                currently also possible for the ID to change due to a sync operation. For example, if
                a user moved an event on a different client to another calendar, we'd see it as a 
                completely new event here.
 
                This may be nil for events that have not been saved.
*/
@property(null_unspecified, nonatomic, readonly) NSString *eventIdentifier;

/*!
    @property   allDay
    @abstract   Indicates this event is an 'all day' event.
*/
@property(nonatomic, getter=isAllDay) BOOL allDay;

/*!
     @property   startDate
     @abstract   The start date for the event.
     @discussion This property represents the start date for this event. Floating events (such
                 as all-day events) are currently always returned in the default time zone.
                 ([NSTimeZone defaultTimeZone])

                 This will be nil for new events until you set it.
 */
@property(null_unspecified, nonatomic, copy) NSDate *startDate;

/*!
    @property   endDate
    @abstract   The end date for the event.
    @discussion This will be nil for new events until you set it.
*/
@property(null_unspecified, nonatomic, copy) NSDate *endDate;

/*!
    @property   structuredLocation
    @abstract   Allows you to set a structured location (a location with a potential geo-coordinate) on an
                event. The getter for EKEvent’s location property just returns the structured location’s title.
                The setter for EKEvent’s location property is equivalent to
                [event setStructuredLocation:[EKStructuredLocation locationWithTitle:…]].
 */
@property(nonatomic, copy, nullable) EKStructuredLocation *structuredLocation NS_AVAILABLE(10_11, 9_0);

/*!
    @method     compareStartDateWithEvent
    @abstract   Comparison function you can pass to sort NSArrays of EKEvents by start date.
*/
- (NSComparisonResult)compareStartDateWithEvent:(EKEvent *)other;

/*!
    @property   organizer
    @abstract   The organizer of this event, or nil.
*/
@property(nonatomic, readonly, nullable) EKParticipant *organizer;

/*!
    @property   availability
    @abstract   The availability setting for this event.
    @discussion The availability setting is used by CalDAV and Exchange servers to indicate
                how the time should be treated for scheduling. If the calendar the event is
                currently in does not support event availability, EKEventAvailabilityNotSupported
                is returned.
*/
@property(nonatomic) EKEventAvailability    availability;

/*!
    @property   status
    @abstract   The status of the event.
    @discussion While the status offers four different values in the EKEventStatus enumeration,
                in practice, the only actionable and reliable status is canceled. Any other status
                should be considered informational at best. You cannot set this property. If you
                wish to cancel an event, you should simply remove it using removeEvent:.
*/
@property(nonatomic, readonly) EKEventStatus          status;

/*!
    @property   isDetached
    @abstract   Represents whether this event is detached from a recurring series.
    @discussion If this EKEvent is an instance of a repeating event, and an attribute of this 
                EKEvent has been changed from the default value generated by the repeating event,
                isDetached will return YES. If the EKEvent is unchanged from its default state, or
                is not a repeating event, isDetached returns NO.
*/
@property(nonatomic, readonly) BOOL isDetached;

/*!
    @property   occurrenceDate:
    @abstract   The occurrence date of an event if it is part of a recurring series.
    @discussion This is only set if the event is part of a recurring series. It returns
                the date on which this event was originally scheduled to occur. For occurrences
                that are unmodified from the recurring series, this is the same as the start date.
                This value will remain the same even if the event has been detached and its start 
                date has changed. Floating events (such as all-day events) are currently returned
                in the default time zone. ([NSTimeZone defaultTimeZone])
 
                This will be nil for new events until you set startDate.
 */
@property(null_unspecified, nonatomic, readonly) NSDate *occurrenceDate NS_AVAILABLE(10_8, 9_0);

/*!
     @method     refresh
     @abstract   Refreshes an event object to ensure it's still valid.
     @discussion When the database changes, your application is sent an EKEventStoreChangedNotification
                 note. You should generally consider all EKEvent instances to be invalid as soon as
                 you receive the notification. However, for events you truly care to keep around, you
                 can call this method. It ensures the record is still valid by ensuring the event and
                 start date are still valid. It also attempts to refresh all properties except those
                 you might have modified. If this method returns NO, the record has been deleted or is
                 otherwise invalid. You should not continue to use it. If it returns YES, all is still
                 well, and the record is ready for continued use. You should only call this method on
                 events that are more critical to keep around if possible, such as an event that is
                 being actively edited, as this call is fairly heavyweight. Do not use it to refresh
                 the entire selected range of events you might have had selected. It is mostly pointless
                 anyway, as recurrence information may have changed.
*/
- (BOOL)refresh;

/*!
    @method     birthdayContactIdentifier
    @abstract   Specifies the contact identifier of the person this event was created for.
    @discussion This property is only valid for events in the built-in Birthdays calendar. It specifies
                the contact identifier (for use with the Contacts framework) of the person this event was
                created for. For any other type of event, this property returns nil.
 */
@property(nonatomic, readonly, nullable) NSString *birthdayContactIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
    @property   birthdayPersonID
    @abstract   Specifies the address book ID of the person this event was created for.
    @discussion  This property is only valid for events in the built-in Birthdays calendar. It specifies
                the Address Book ID of the person this event was created for. For any other type of event,
                this property returns -1.
*/
@property(nonatomic, readonly) NSInteger birthdayPersonID NS_DEPRECATED_IOS(5_0, 9_0, "Use birthdayContactIdentifier instead");

/*!
    @property   birthdayPersonUniqueID
    @abstract   Specifies the address book unique ID of the person this event was created for.
    @discussion This property is only valid for events in the built-in Birthdays calendar. It specifies
                the Address Book unique ID of the person this event was created for. For any other type of event,
                this property returns nil.
 */
@property(nonatomic, readonly, nullable) NSString *birthdayPersonUniqueID NS_DEPRECATED_MAC(10_8, 10_11, "Use birthdayContactIdentifier instead");

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKAlarm.h
//
//  EKAlarm.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKCalendarItem, EKStructuredLocation;

/*!
    @class          EKAlarm
    @abstract       The EKAlarm class provides an interface for accessing and manipulating calendar event alarms.
    @discussion     The EKAlarm class represents alarms on an event. An alarm can be relative (e.g. 15 mins before) 
                    or absolute (specific time).
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKAlarm : EKObject <NSCopying> {
}

/*!
    @method     alarmWithAbsoluteDate:
    @abstract   Creates a new autoreleased alarm with an absolute trigger time.
    @param      date    The date the alarm should fire.
*/
+ (EKAlarm *)alarmWithAbsoluteDate:(NSDate *)date;

/*!
    @method     alarmWithRelativeOffset:
    @abstract   Creates a new autoreleased alarm with a relative trigger time.
    @discussion Creates a new autoreleased alarm with a relative trigger time. This offset
                is added to the start date of the event.

    @param      offset    The offset from the event start that the alarm should fire.
*/
+ (EKAlarm *)alarmWithRelativeOffset:(NSTimeInterval)offset;

/*!
    @property   relativeOffset
    @abstract   Specifies a relative offset from an event start date to fire an alarm.
    @discussion Set this property to an appropriate negative value to establish an alarm trigger
                relative to the start date/time of an event. Setting this clears any existing
                date trigger.
*/
@property(nonatomic) NSTimeInterval relativeOffset;

/*!
    @property   absoluteDate
    @abstract   Represents an alarm that fires at a specific date.
    @discussion Set this property to a date to establish an absolute alarm trigger. Setting this
                clears any relative interval trigger.
*/
@property(nonatomic, copy, nullable) NSDate *absoluteDate;

/*!
    @property   structuredLocation
    @discussion Allows you to set a structured location (a location with a potential geo-coordinate)
                on an alarm. This is used in conjunction with proximity to do geofence-based
                triggering of reminders.
 */
@property(nonatomic, copy, nullable) EKStructuredLocation   *structuredLocation;

/*!
    @property   proximity
    @discussion Defines whether this alarm triggers via entering/exiting a geofence as defined by
                structuredLocation.
 */
@property(nonatomic) EKAlarmProximity    proximity;

/*!
 @property   type
 @abstract   The type of alarm, based on the action taken when triggering the alarm.
 @discussion This field is read-only; to change the type of alarm, set emailAddress for EKAlarmTypeEmail,
             soundName for EKAlarmTypeAudio or url for EKAlarmTypeProcedure.
             Setting all of those to nil will change it to EKAlarmTypeDisplay.
 */
@property(nonatomic, readonly) EKAlarmType type NS_AVAILABLE(10_8, NA);

/*!
 @property   emailAddress
 @abstract   An email address that is the recipient of an email alarm, which is an alarm that triggers an email message.
 @discussion When you set the emailAddress property, the action property is set to EKAlarmTypeEmail,
             and the soundName and url properties are set to nil.
 */
@property(nonatomic, copy, nullable) NSString *emailAddress NS_AVAILABLE(10_8, NA);

/*!
 @property   soundName
 @abstract   The name of the sound to play when the alarm triggers.
 @discussion The value of this property is the name of a system sound that can be used with
             the soundNamed: class method to create an NSSound object. When you set the soundName property,
             the action property is set to EKAlarmTypeAudio, and the emailAddress and url properties are set to nil.
 */
@property(nonatomic, copy, nullable) NSString *soundName NS_AVAILABLE(10_8, NA);

/*!
 @property   url
 @abstract   The URL to open when the alarm triggers.
 @discussion When you set the url property, the action property is set to EKAlarmTypeProcedure,
             and the emailAddress and soundName properties are set to nil.
             Note: Starting with OS X 10.9, it is not possible to create new procedure alarms or view URLs for existing procedure alarms.
             Trying to save or modify a procedure alarm will result in a save error.
             Editing other aspects of events or reminders that have existing procedure alarms is allowed as long as the alarm isn't modified.
 */
@property(nonatomic, copy, nullable) NSURL *url NS_DEPRECATED(10_8, 10_9, NA, NA);

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKSource.h
//
//  EKSource.h
//  EventKit
//
//  Copyright 2009-2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKCalendar;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface EKSource : EKObject

@property(nonatomic, readonly) NSString        *sourceIdentifier;
@property(nonatomic, readonly) EKSourceType     sourceType;
@property(nonatomic, readonly) NSString        *title;
/*!
 @property    calendars
 @abstract    This is now deprecated in favor of -[EKSource calendarsForEntityType:]
 */
@property(nonatomic, readonly) NSSet<EKCalendar *> *calendars NS_DEPRECATED(NA, NA, 4_0, 6_0);


/*!
 @method      calendarsForEntityType
 @abstract    Returns the calendars that belong to this source that 
              support a given entity type (reminders, events)
 */
- (NSSet<EKCalendar *> *)calendarsForEntityType:(EKEntityType)entityType NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EventKitDefines.h
//
//  EventKitDefines.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define EVENTKIT_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKIT_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#if !TARGET_OS_IPHONE

static inline void NS_DEPRECATED(10_8, 10_10, NA, NA) EK_LOSE_FRACTIONAL_SECONDS_DO_NOT_USE (void) { ; }
// an NSDate with no fractional seconds will use a tagged pointer, which is much more efficient to create/store
#define EK_LOSE_FRACTIONAL_SECONDS(date) ({EK_LOSE_FRACTIONAL_SECONDS_DO_NOT_USE(); __typeof__(date) __datevalue = (date); (__datevalue ? [NSDate dateWithTimeIntervalSinceReferenceDate:floor([__datevalue timeIntervalSinceReferenceDate])] : nil); })

static inline void NS_DEPRECATED(10_8, 10_10, NA, NA) DATE_COMPONENTS_DO_NOT_USE (void) { ; }
#define DATE_COMPONENTS ({DATE_COMPONENTS_DO_NOT_USE(); (NSCalendarUnitEra | NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay); })

static inline void NS_DEPRECATED(10_8, 10_10, NA, NA) DATETIME_COMPONENTS_DO_NOT_USE (void) { ; }
#define DATETIME_COMPONENTS ({DATETIME_COMPONENTS_DO_NOT_USE(); (DATE_COMPONENTS | NSCalendarUnitHour | NSCalendarUnitMinute | NSCalendarUnitSecond); })

#endif
// ==========  EventKit.framework/Headers/EKError.h
//
//  EKError.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>

/*!
    @const      EKErrorDomain 
    @abstract   Error domain for NSError values stemming from the EventKit Framework API.
    @discussion This error domain is used as the domain for all NSError instances stemming from the
                EventKit Framework.
*/
EVENTKIT_EXTERN NSString *const EKErrorDomain NS_AVAILABLE(10_8, 4_0);

/*!
    @enum       EKErrorCode
    @abstract   Error codes for NSError values stemming from the Calendar Framework.
    @discussion These error codes are used as the codes for all NSError instances stemmming from the
                Calendar Framework.
 
    @constant   EKErrorEventNotMutable                  The event is not mutable and cannot be saved/deleted.
    @constant   EKErrorNoCalendar                       The event has no calendar set.
    @constant   EKErrorNoStartDate                      The event has no start date set.
    @constant   EKErrorNoEndDate                        The event has no end date set.
    @constant   EKErrorDatesInverted                    The end date is before the start date.
    @constant   EKErrorInternalFailure                  An internal error occurred.
    @constant   EKErrorCalendarReadOnly                 Calendar can not have events added to it.
    @constant   EKErrorDurationGreaterThanRecurrence    The duration of an event is greater than the recurrence interval.
    @constant   EKErrorAlarmGreaterThanRecurrence       The alarm interval is greater than the recurrence interval
    @constant   EKErrorStartDateTooFarInFuture          The start date is further into the future than the calendar will display.
    @constant   EKErrorStartDateCollidesWithOtherOccurrence The start date specified collides with another occurrence of that event, and the current calendar doesn't allow it.
    @constant   EKErrorObjectBelongsToDifferentStore    The object you are passing doesn't belong to the calendar store you're dealing with.
    @constant   EKErrorInvitesCannotBeMoved             The event is an invite, and therefore cannot move to another calendar.
    @constant   EKErrorInvalidSpan                      An invalid span was passed when saving/deleting.
    @constant   EKErrorCalendarHasNoSource              An attempt to save a calendar with no source set was made.
    @constant   EKErrorCalendarSourceCannotBeModified   The calendar cannot be moved to another source.
    @constant   EKErrorCalendarIsImmutable              The calendar is immutable and cannot be modified or deleted.
    @constant   EKErrorSourceDoesNotAllowCalendarAddDelete   Some sources (accounts) do not allow calendars to be added or removed.
    @constant   EKErrorRecurringReminderRequiresDueDate A recurring reminder requires a due date.
    @constant   EKErrorStructuredLocationsNotSupported  The source this calendar belongs to does not support structured locations.
    @constant   EKErrorReminderLocationsNotSupported    This source doesn't support locations on Reminders.
    @constant   EKErrorAlarmProximityNotSupported       This source doesn't allow alarm proximity (geofencing).
    @constant   EKErrorCalendarDoesNotAllowEvents       You are trying to add an event to a calendar that does not allow events.
    @constant   EKErrorCalendarDoesNotAllowReminders    You are trying to add a reminder to a calendar that does not allow reminders.
    @constant   EKErrorSourceDoesNotAllowReminders      You are trying to add a calendar that allows reminders to a source that does not allow them.
    @constant   EKErrorSourceDoesNotAllowEvents         You are trying to add a calendar that allows events to a source that does not allow them.
    @constant   EKErrorPriorityIsInvalid                You have set an invalid priority for a reminder.  Priorities must be between 0 and 9.
    @constant   EKErrorInvalidEntityType                This is not a valid EKEntityType
    @constant   EKErrorProcedureAlarmsNotMutable        Procedure alarms may not be created or modified.
    @constant   EKErrorEventStoreNotAuthorized          The user has not authorized your application to access their events and/or reminders.
    @constant   EKErrorOSNotSupported                   The action is not supported on the current operating system.
*/

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || !TARGET_OS_IPHONE
typedef NS_ENUM(NSInteger, EKErrorCode) {
    EKErrorEventNotMutable,
    EKErrorNoCalendar,
    EKErrorNoStartDate,
    EKErrorNoEndDate,
    EKErrorDatesInverted,
    EKErrorInternalFailure,
    EKErrorCalendarReadOnly,
    EKErrorDurationGreaterThanRecurrence,
    EKErrorAlarmGreaterThanRecurrence,
    EKErrorStartDateTooFarInFuture,
    EKErrorStartDateCollidesWithOtherOccurrence,
    EKErrorObjectBelongsToDifferentStore,
    EKErrorInvitesCannotBeMoved,
    EKErrorInvalidSpan,
    EKErrorCalendarHasNoSource,
    EKErrorCalendarSourceCannotBeModified,
    EKErrorCalendarIsImmutable,
    EKErrorSourceDoesNotAllowCalendarAddDelete,
    EKErrorRecurringReminderRequiresDueDate,
    EKErrorStructuredLocationsNotSupported,
    EKErrorReminderLocationsNotSupported,
    EKErrorAlarmProximityNotSupported,
    EKErrorCalendarDoesNotAllowEvents,
    EKErrorCalendarDoesNotAllowReminders,
    EKErrorSourceDoesNotAllowReminders,
    EKErrorSourceDoesNotAllowEvents,
    EKErrorPriorityIsInvalid,
    EKErrorInvalidEntityType,
    EKErrorProcedureAlarmsNotMutable,
    EKErrorEventStoreNotAuthorized,
    EKErrorOSNotSupported,

    EKErrorLast // used internally
};
#endif
// ==========  EventKit.framework/Headers/EKParticipant.h
//
//  EKParticipant.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

#if TARGET_OS_IPHONE
#if !TARGET_OS_WATCH
#import <AddressBook/ABPerson.h>
#endif
#else
#import <AddressBook/AddressBook.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if !TARGET_OS_IPHONE
@class ABPerson, ABAddressBook;
#endif

/*!
    @class      EKParticipant
    @abstract   Abstract class representing a participant attached to an event.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKParticipant : EKObject <NSCopying> {
}

/*!
    @property   url
    @abstract   URL representing this participant.
*/
@property(nonatomic, readonly) NSURL           *URL;

/*!
    @property   name
    @abstract   Name of this participant.
*/
@property(nonatomic, readonly, nullable) NSString        *name;

/*!
    @property   participantStatus
    @abstract   The status of the attendee.
    @discussion Returns the status of the attendee as a EKParticipantStatus value.
*/
@property(nonatomic, readonly) EKParticipantStatus participantStatus;

/*!
    @property   participantRole
    @abstract   The role of the attendee.
    @discussion Returns the role of the attendee as a EKParticipantRole value.
*/
@property(nonatomic, readonly) EKParticipantRole participantRole;

/*!
    @property   participantType
    @abstract   The type of the attendee.
    @discussion Returns the type of the attendee as a EKParticipantType value.
*/
@property(nonatomic, readonly) EKParticipantType participantType;

/*!
    @property   currentUser
    @abstract   A boolean indicating whether this participant represents the
                owner of this account.
 */
@property(nonatomic, readonly, getter=isCurrentUser) BOOL currentUser NS_AVAILABLE(10_9, 6_0);

/*!
    @method     contactPredicate
    @abstract   Returns a predicate to use with Contacts.framework to retrieve the corresponding
                CNContact instance.
    @discussion This method returns a predicate that can be used with a CNContactStore to fetch
                a CNContact instance for this participant, if one exists.
 */
@property(nonatomic, readonly) NSPredicate *contactPredicate NS_AVAILABLE(10_11, 9_0);

#if TARGET_OS_IPHONE
#if !TARGET_OS_WATCH
/*!
    @method     ABRecordWithAddressBook
    @abstract   Returns the ABRecordRef that represents this participant.
    @discussion This method returns the ABRecordRef that represents this participant,
                if a match can be found based on email address in the address book
                passed. If we cannot find the participant, nil is returned.
*/
- (nullable ABRecordRef)ABRecordWithAddressBook:(ABAddressBookRef)addressBook NS_DEPRECATED_IOS(4_0, 9_0, "Use contactPredicate instead") CF_RETURNS_NOT_RETAINED;
#endif
#else
/*!
    @method     ABPersonInAddressBook
    @abstract   Returns the ABPerson that represents this participant.
    @discussion This method returns the ABPerson that represents this participant,
                if a match can be found based on email address in the address book
                passed. If we cannot find the participant, nil is returned.
 */
- (nullable ABPerson *)ABPersonInAddressBook:(ABAddressBook *)addressBook NS_DEPRECATED_MAC(10_8, 10_11, "Use contactPredicate instead");
#endif

@end

NS_ASSUME_NONNULL_END
// ==========  EventKit.framework/Headers/EKCalendarItem.h
//
//  EKCalendarItem.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <EventKit/EKObject.h>
#import <EventKit/EventKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class EKRecurrenceRule, EKAlarm, EKCalendar, EKParticipant;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface EKCalendarItem : EKObject

/*!
    @property   UUID
    @discussion This is now deprecated; use calendarItemIdentifier instead.
 */
@property(nonatomic, readonly) NSString *UUID NS_DEPRECATED(NA, NA, 5_0, 6_0);

/*!
    @property calendar
    @abstract The calendar that this calendar item belongs to.
    @discussion This will be nil for new calendar items until you set it.
 */
@property(nonatomic, strong, null_unspecified) EKCalendar *calendar;

/*!
    @property   calendarItemIdentifier
    @abstract   A unique identifier for a calendar item.
    @discussion Item identifiers are not sync-proof in that a full sync will lose
                this identifier, so you should always have a back up plan for dealing
                with a reminder that is no longer fetchable by this property, e.g. by title, etc.
                Use [EKEventStore calendarItemWithIdentifier:] to look up the item by this value.
*/
@property(nonatomic, readonly) NSString *calendarItemIdentifier NS_AVAILABLE(10_8, 6_0);

/*!
    @property   calendarItemExternalIdentifier
    @abstract   A server-provided identifier for this calendar item
    @discussion This identifier, provided by the server, allows you to reference the same event or reminder across
                multiple devices. For calendars stored locally on the device, including the birthday calendar,
                it simply passes through to calendarItemIdentifier.
 
                This identifier is unique as of creation for every calendar item.  However, there are some
                cases where duplicate copies of a calendar item can exist in the same database, including:
                - A calendar item was imported from an ICS file into multiple calendars
                - An event was created in a calendar shared with the user and the user was also invited to the event
                - The user is a delegate of a calendar that also has this event
                - A subscribed calendar was added to multiple accounts
                In such cases, you should choose between calendar items based on other factors, such as
                the calendar or source.

                This identifier is the same for all occurrences of a recurring event. If you wish to differentiate
                between occurrences, you may want to use the start date.
 
                This may be nil for new calendar items that do not yet belong to a calendar.
 
                In addition, there are two caveats for Exchange-based calendars:
                - This identifier will be different between EventKit on iOS versus OS X
                - This identifier will be different between devices for EKReminders
*/
@property(nonatomic, readonly, null_unspecified) NSString *calendarItemExternalIdentifier NS_AVAILABLE(10_8, 6_0);

/*!
    @property title
    @abstract The title of this calendar item.
    @discussion This will be nill for new calendar items until you set it.
 */
@property(nonatomic, copy, null_unspecified) NSString *title;
@property(nonatomic, copy, nullable) NSString *location;
@property(nonatomic, copy, nullable) NSString *notes;
@property(nonatomic, copy, nullable) NSURL *URL NS_AVAILABLE(10_8, 5_0);

@property(nonatomic, readonly, nullable) NSDate *lastModifiedDate;
@property(nonatomic, readonly, nullable, strong) NSDate *creationDate NS_AVAILABLE(10_8, 5_0);
@property(nonatomic, copy, nullable) NSTimeZone *timeZone  NS_AVAILABLE(10_8, 5_0);

// These exist to do simple checks for the presence of data without
// loading said data. While at present only hasRecurrenceRules has a
// fast path, it is a good idea to use these if you only need to know
// the data exists anyway since at some point they will all be a
// simple check.
@property(nonatomic, readonly) BOOL hasAlarms  NS_AVAILABLE(10_8, 5_0);
@property(nonatomic, readonly) BOOL hasRecurrenceRules  NS_AVAILABLE(10_8, 5_0);
@property(nonatomic, readonly) BOOL hasAttendees  NS_AVAILABLE(10_8, 5_0);
@property(nonatomic, readonly) BOOL hasNotes  NS_AVAILABLE(10_8, 5_0);

// An array of EKParticipant objects
@property(nonatomic, readonly, nullable) NSArray<__kindof EKParticipant *> *attendees;


// An array of EKAlarm objects
@property(nonatomic, copy, nullable) NSArray<EKAlarm *> *alarms;

/*!
    @method     addAlarm:
    @abstract   Adds an alarm to this item.
    @discussion This method add an alarm to an item. Be warned that some calendars can only
                allow a certain maximum number of alarms. When this item is saved, it will
                truncate any extra alarms from the array.
*/
- (void)addAlarm:(EKAlarm *)alarm;

/*!
    @method     removeAlarm:
    @abstract   Removes an alarm from this item.
*/
- (void)removeAlarm:(EKAlarm *)alarm;

/*!
    @property   recurrenceRules
    @abstract   An array of EKRecurrenceRules, or nil if none.
*/
@property(nonatomic, copy, nullable) NSArray<EKRecurrenceRule *> *recurrenceRules NS_AVAILABLE(10_8, 5_0);

- (void)addRecurrenceRule:(EKRecurrenceRule *)rule;
- (void)removeRecurrenceRule:(EKRecurrenceRule *)rule;

@end

NS_ASSUME_NONNULL_END
