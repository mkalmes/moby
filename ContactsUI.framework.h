// ==========  ContactsUI.framework/Headers/UIApplicationShortcutIcon+Contacts.h
//
//  UIApplicationShortcutIcon+Contacts.h
//  ContactsUI
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Contacts/Contacts.h>
#import <UIKit/UIApplicationShortcutItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, uikitformac)
@interface UIApplicationShortcutIcon (ContactsUI)

+ (instancetype)iconWithContact:(CNContact *)contact;

@end

NS_ASSUME_NONNULL_END
// ==========  ContactsUI.framework/Headers/CNContactViewController.h
//
//  CNContactViewController.h
//  ContactsUI
//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Contacts/Contacts.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNContactViewControllerDelegate;


/*!
 * @abstract    The @c CNContactViewController is used to display a contact.
 * @discussion  This class can display a new contact, unknown contact or existing contact.
 *              You must use one of the class factory methods.
 */

NS_CLASS_AVAILABLE_IOS(9_0)
@interface CNContactViewController : UIViewController

/*!
 * @abstract    Descriptor for all keys that must be fetched on a contact before setting it on the view controller.
 * @discussion  If you want to display an existing contact in a @c CNContactViewController,
 *              this descriptor must have been included in the @c keysToFetch property of the
 *              @c CNContactFetchRequest. (A newly created @c CNMutableContact may be used safely.)
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

/*!
 * @abstract    Initializes a contact view controller for a known contact.
 * @discussion  Use this view controller for a contact that has been fetched
 *              from the user’s contacts database.
 *              Allows editing of the contact by default.
 * @note        All keys of the given contact must be fetched.
 * @see         contactStore
 * @see         allowsEditing
 */
+ (instancetype)viewControllerForContact:(CNContact *)contact;

/*!
 * @abstract    Initializes a contact view controller for an unknown contact.
 * @discussion  Use this view controller for a populated contact not fetched from the user’s contacts.
 *              Such a contact might be obtained by parsing a vCard or setting properties on a newly
 *              created @c CNMutableContact.
 *              This controller does not allow editing, but by default does allow actions
 *              for adding the contact to the contacts database.
 * @see         contactStore
 */
+ (instancetype)viewControllerForUnknownContact:(CNContact *)contact;

/*!
 * @abstract     Initializes a contact view controller for creating a new contact.
 * @discussion   Use this view controller with a contact to be added to the user's contacts.
 * @note         The given contact should be a newly initialized contact and
 *               not one fetched from the user's contacts.
 */
+ (instancetype)viewControllerForNewContact:(nullable CNContact *)contact;

/*!
 * @abstract     The contact being displayed.
 */
@property (nonatomic, strong, readonly) CNContact *contact;

/*!
 * @abstract     The @c CNContact property keys to display.
 * @discussion   If @c nil, all properties are displayed. (The property is @c nil by default.)
 * @note         All properties are visible when editing the contact.
 */
@property (nonatomic, copy, nullable) NSArray *displayedPropertyKeys;

/*!
 * @abstract    The delegate to be notified.
 */
@property (nonatomic, weak, nullable) id <CNContactViewControllerDelegate> delegate;

/*!
 * @abstract    The @c CNContactStore where the contact was fetched from or will be saved to.
 * @discussion  If @c contactStore is not set, actions for adding the contact to the
 *              user's contacts are disabled. This does not affect the ability to edit
 *              the contact.
 *
 *              If the user edits the contact and the editing is committed, the contact
 *              will be updated in the user's contacts database or added to the user's
 *              contacts database if not already present.
 *
 *              To prevent editing of a known contact, set @c allowsEditing to @c NO.
 * @see         allowsEditing
 */
@property (nonatomic, strong, nullable) CNContactStore *contactStore;

/*!
 * @abstract    A @c CNGroup where the new contact will be assigned membership.
 * @discussion  If not set the contact is added only to the default @c CNContainer with no group membership.
 * @note        When set to a group not in the default container, the container
 *              property must also be set to the container of parentGroup.
 */
@property (nonatomic, strong, nullable) CNGroup *parentGroup;

/*!
 * @abstract    A @c CNContainer where the new contact will be created.
 * @discussion  If not set the contact is added to the default container.
 */
@property (nonatomic, strong, nullable) CNContainer *parentContainer;

/*!
 * @abstract    The name to use if the contact has no display name.
 */
@property (nonatomic, copy, nullable) NSString *alternateName;

/*!
 * @abstract    The message to display under the name.
 */
@property (nonatomic, copy, nullable) NSString *message;

/*!
 * @abstract    Customization of the card.
 */
@property (nonatomic, assign) BOOL allowsEditing; // YES by default
@property (nonatomic, assign) BOOL allowsActions; // YES by default
@property (nonatomic, assign) BOOL shouldShowLinkedContacts; // NO by default

/*!
 * @abstract    Highlight a property.
 * @discussion  Indicates whether to highlight a certain property value for the contact.
 *              If a single value property key is specified, identifier will be ignored.
 */
- (void)highlightPropertyWithKey:(NSString *)key identifier:(nullable NSString *)identifier;

@end


NS_AVAILABLE_IOS(9_0)
@protocol CNContactViewControllerDelegate <NSObject>
@optional

/*!
 * @abstract    Called when the user selects a single property.
 * @discussion  Return @c NO if you do not want anything to be done or if you are handling the actions yourself.
 * @return      @c YES if you want the default action performed for the property otherwise return @c NO.
 */
- (BOOL)contactViewController:(CNContactViewController *)viewController shouldPerformDefaultActionForContactProperty:(CNContactProperty *)property;

/*!
 * @abstract    Called when the view has completed.
 * @discussion  If creating a new contact, the new contact added to the contacts list will be passed.
 *              If adding to an existing contact, the existing contact will be passed.
 * @note        It is up to the delegate to dismiss the view controller.
 */
- (void)contactViewController:(CNContactViewController *)viewController didCompleteWithContact:(nullable CNContact *)contact;

@end

NS_ASSUME_NONNULL_END
// ==========  ContactsUI.framework/Headers/ContactsUI.h
//
//  ContactsUI.h
//  ContactsUI
//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <ContactsUI/CNContactPickerViewController.h>
#import <ContactsUI/CNContactViewController.h>
#import <ContactsUI/UIApplicationShortcutIcon+Contacts.h>
// ==========  ContactsUI.framework/Headers/CNContactPickerViewController.h
//
//  CNContactPickerViewController.h
//  ContactsUI
//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Contacts/Contacts.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNContactPickerDelegate;


/*!
 * @abstract    The CNContactPickerViewController allows the user to select one or multiple contacts or properties.
 * @discussion  The entire list of contacts will be presented to the user.
 *              The picker supports both single selection and multi-selection.
 *              The app does not need access to the user’s contacts and the user will
 *              not be prompted for access. It will only have access to the final selection of the user.
 *              Changing the predicates only takes effect before the view is presented.
 */
NS_CLASS_AVAILABLE_IOS(9_0)
@interface CNContactPickerViewController : UIViewController

/*!
 * @abstract    The CNContact property keys to display in the contact detail card.
 * @discussion  If not set all properties are displayed.
 */
@property (nonatomic, copy, nullable) NSArray<NSString*> *displayedPropertyKeys;

/*!
 * @abstract    The delegate to be notified when the user selects a contact or property.
 */
@property (nonatomic, weak, nullable) id <CNContactPickerDelegate> delegate;

/*!
 * @abstract    The predicate to determine if a contact is selectable in the list.
 * @discussion  If not set all contacts are selectable.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForEnablingContact; // e.g. emailAddresses.@count > 0

/*!
 * @abstract    The predicate to control the selection of a contact.
 * @discussion  It determines whether a selected contact should be returned (predicate evaluates to TRUE)
 *              or if the contact detail card should be displayed (evaluates to FALSE).
 *              If not set the picker displays the contact detail card when the contact is selected.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForSelectionOfContact; // e.g. emailAddresses.@count == 1

/*!
 * @abstract    The predicate to control the selection of a property.
 * @discussion  It determines whether a selected property should be returned (predicate evaluates to TRUE)
 *              or if the default action for the property should be performed (predicate evaluates to FALSE).
 *              If not set the picker returns the first selected property.
 *              The predicate is evaluated on the CNContactProperty that is being selected.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForSelectionOfProperty; // e.g. (key == 'emailAddresses') AND (value LIKE '*@apple.com')

@end


NS_AVAILABLE_IOS(9_0)
@protocol CNContactPickerDelegate <NSObject>

@optional

/*!
 * @abstract    Invoked when the picker is closed.
 * @discussion  The picker will be dismissed automatically after a contact or property is picked.
 */
- (void)contactPickerDidCancel:(CNContactPickerViewController *)picker;

/*!
 * @abstract    Singular delegate methods.
 * @discussion  These delegate methods will be invoked when the user selects a single contact or property.
 */
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContact:(CNContact *)contact;
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContactProperty:(CNContactProperty *)contactProperty;

/*!
 * @abstract    Plural delegate methods.
 * @discussion  These delegate methods will be invoked when the user is done selecting multiple contacts or properties.
 *              Implementing one of these methods will configure the picker for multi-selection.
 */
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContacts:(NSArray<CNContact*> *)contacts;
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContactProperties:(NSArray<CNContactProperty*> *)contactProperties;

@end

NS_ASSUME_NONNULL_END
