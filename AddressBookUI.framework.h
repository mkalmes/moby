// ==========  AddressBookUI.framework/Headers/ABUnknownPersonViewController.h
//
//  ABUnknownPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABUnknownPersonViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use +[CNContactViewController viewControllerForUnknownContact:] from ContactsUI.framework instead")
@interface ABUnknownPersonViewController : UIViewController

// ABPersonViewController does not support subclassing in iOS 7.0 and later. A nil instance will be returned.

@property(nonatomic,assign,nullable) id<ABUnknownPersonViewControllerDelegate> unknownPersonViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

    // All the fields specified in displayedPerson will be displayed in the view
    // and used if the unknown person is added to Address Book or merged into an
    // existing person in Address Book.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef displayedPerson;

    // An alternateName can be provided to replace the First and Last name
    // in case they are not available.
@property(nonatomic,copy,nullable) NSString *alternateName;
    // The message will be displayed below the alternateName.
@property(nonatomic,copy,nullable) NSString *message;

    // Specifies whether buttons appear to let the user perform actions such as sharing the contact,
    // initiating a FaceTime call, or sending a text message.
@property(nonatomic) BOOL allowsActions;
    // Whether options to create a contact or add to an existing contact should be
    // made available to the user.
@property(nonatomic) BOOL allowsAddingToAddressBook;

@end


@protocol ABUnknownPersonViewControllerDelegate <NSObject>

    // Called when picking has completed.  If picking was canceled, 'person' will be NULL.
    // Otherwise, person will be either a non-NULL resolved contact, or newly created and
    // saved contact, in both cases, person will be a valid contact in the Address Book.
    // It is up to the delegate to dismiss the view controller.
- (void)unknownPersonViewController:(ABUnknownPersonViewController *)unknownCardViewController didResolveToPerson:(nullable ABRecordRef)person;

@optional
    // Called when the user selects an individual value in the unknown person view, identifier will be kABMultiValueInvalidIdentifier if a single value property was selected.
    // Return NO if you do not want anything to be done or if you are handling the actions yourself.
    // Return YES if you want the ABUnknownPersonViewController to perform its default action.
- (BOOL)unknownPersonViewController:(ABUnknownPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  AddressBookUI.framework/Headers/ABPeoplePickerNavigationController.h
//
//  ABPeoplePickerNavigationController.h
//  AddressBookUI
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <UIKit/UINavigationController.h>
#import <AddressBook/ABAddressBook.h>
#import <AddressBook/ABMultiValue.h>
#import <AddressBook/ABRecord.h>

@protocol ABPeoplePickerNavigationControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use CNContactPickerViewController from ContactsUI.framework instead")
@interface ABPeoplePickerNavigationController : UINavigationController

// The ABPeoplePickerNavigationController allows the user to select a person or property by presenting the entire Address Book.
//
// In iOS 7.0 and later ABPeoplePickerNavigationController does not support subclassing. In the future, a nil instance will be returned.
//
// In iOS 8.0 and later the app does not need access to the user’s contacts and the user will not be prompted for access.
// If the app does not have access to the user's contacts a temporary copy of the selected person is returned to the app.
// If the app has access to the user's contacts the selected person is returned to the app from the ABPeoplePickerNavigationController.addressBook instance.

// Optional to get the selected contact, selected property or cancellation of the people picker.
//
@property(nonatomic,assign,nullable) id<ABPeoplePickerNavigationControllerDelegate> peoplePickerDelegate;

// An array of ABPropertyIDs listing the properties that should be visible when viewing a person.
// If you are interested in one particular type of data (for example a phone number), displayedProperties
// should be an array with a single NSNumber instance (representing kABPersonPhoneProperty).
// Note that name information will always be shown if available.
//
@property(nonatomic,copy,nullable) NSArray<NSNumber*> *displayedProperties;

// The Address Book to browse. Contacts will be returned from this ABAddressBook instance.
// If not set, a new ABAddressBook will be created the first time the property is accessed.
// Note this property is only used if the app has access to the user's contacts, otherwise it remains NULL.
//
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

// Optionally determines if a person can be selected or not.
// If not set, all persons will be selectable.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForEnablingPerson NS_AVAILABLE_IOS(8_0);

// Optionally determines if a selected person should be returned to the app (predicate evaluates to TRUE),
// or if the selected person should be displayed (predicate evaluates to FALSE).
// If not set and -peoplePickerNavigationController:didSelectPerson: is implemented the selected person is returned to the app,
// or if not set and -peoplePickerNavigationController:didSelectPerson:identifier: is implemented the selected person is displayed.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForSelectionOfPerson NS_AVAILABLE_IOS(8_0);

// Optionally determines if a selected property should be returned to the app (predicate evaluates to TRUE),
// or if the default action for the property should be performed (predicate evaluates to FALSE).
// If not set and -peoplePickerNavigationController:didSelectPerson:identifier: is implemented the selected property is returned to the app.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForSelectionOfProperty NS_AVAILABLE_IOS(8_0);

@end


// Constants to use in predicates:
// A LabeledValue has a 'label' property and a 'value' property.
// A PhoneNumber has a 'stringValue' property, a 'countryCode' property, a 'formattedStringValue' property and a 'normalizedStringValue' property
// A InstantMessageAddress has a 'username' property and a 'service' property
// A SocialProfile has a 'username' property and a 'service' property
// A PostalAddress has a 'street' property, a 'subLocality' property, a 'city' property, a 'subAdministrativeArea' property, a 'state' property, a 'postalCode' property, a 'country' property and a 'ISOCountryCode' property
//
extern NSString * const ABPersonNamePrefixProperty NS_AVAILABLE_IOS(8_0);               // "namePrefix"                 NSString
extern NSString * const ABPersonGivenNameProperty NS_AVAILABLE_IOS(8_0);                // "givenName"                  NSString
extern NSString * const ABPersonMiddleNameProperty NS_AVAILABLE_IOS(8_0);               // "middleName"                 NSString
extern NSString * const ABPersonFamilyNameProperty NS_AVAILABLE_IOS(8_0);               // "familyName"                 NSString
extern NSString * const ABPersonNameSuffixProperty NS_AVAILABLE_IOS(8_0);               // "nameSuffix"                 NSString
extern NSString * const ABPersonPreviousFamilyNameProperty NS_AVAILABLE_IOS(8_0);       // "previousFamilyName"         NSString
extern NSString * const ABPersonNicknameProperty NS_AVAILABLE_IOS(8_0);                 // "nickname"                   NSString
extern NSString * const ABPersonPhoneticGivenNameProperty NS_AVAILABLE_IOS(8_0);        // "phoneticGivenName"          NSString
extern NSString * const ABPersonPhoneticMiddleNameProperty NS_AVAILABLE_IOS(8_0);       // "phoneticMiddleName"         NSString
extern NSString * const ABPersonPhoneticFamilyNameProperty NS_AVAILABLE_IOS(8_0);       // "phoneticFamilyName"         NSString
extern NSString * const ABPersonOrganizationNameProperty NS_AVAILABLE_IOS(8_0);         // "organizationName"           NSString
extern NSString * const ABPersonDepartmentNameProperty NS_AVAILABLE_IOS(8_0);           // "departmentName"             NSString
extern NSString * const ABPersonJobTitleProperty NS_AVAILABLE_IOS(8_0);                 // "jobTitle"                   NSString
extern NSString * const ABPersonBirthdayProperty NS_AVAILABLE_IOS(8_0);                 // "birthday"                   NSDateComponents
extern NSString * const ABPersonNoteProperty NS_AVAILABLE_IOS(8_0);                     // "note"                       NSString
extern NSString * const ABPersonPhoneNumbersProperty NS_AVAILABLE_IOS(8_0);             // "phoneNumbers"               array of LabeledValue with PhoneNumber values
extern NSString * const ABPersonEmailAddressesProperty NS_AVAILABLE_IOS(8_0);           // "emailAddresses"             array of LabeledValue with NSString values
extern NSString * const ABPersonUrlAddressesProperty NS_AVAILABLE_IOS(8_0);             // "urlAddresses"               array of LabeledValue with NSString values
extern NSString * const ABPersonDatesProperty NS_AVAILABLE_IOS(8_0);                    // "dates"                      array of LabeledValue with NSDateComponents values
extern NSString * const ABPersonInstantMessageAddressesProperty NS_AVAILABLE_IOS(8_0);  // "instantMessageAddresses"    array of LabeledValue with InstantMessageAddress values
extern NSString * const ABPersonRelatedNamesProperty NS_AVAILABLE_IOS(8_0);             // "relatedNames"               array of LabeledValue with NSString values
extern NSString * const ABPersonSocialProfilesProperty NS_AVAILABLE_IOS(8_0);           // "socialProfiles"             array of LabeledValue with SocialProfile values
extern NSString * const ABPersonPostalAddressesProperty NS_AVAILABLE_IOS(8_0);          // "postalAddresses"            array of LabeledValue with PostalAddress values


@protocol ABPeoplePickerNavigationControllerDelegate <NSObject>

@optional

// Called after a person has been selected by the user.
- (void)peoplePickerNavigationController:(ABPeoplePickerNavigationController*)peoplePicker didSelectPerson:(ABRecordRef)person NS_AVAILABLE_IOS(8_0);

// Called after a property has been selected by the user.
- (void)peoplePickerNavigationController:(ABPeoplePickerNavigationController*)peoplePicker didSelectPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier NS_AVAILABLE_IOS(8_0);

// Called after the user has pressed cancel.
- (void)peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker;


// Deprecated, use predicateForSelectionOfPerson and/or -peoplePickerNavigationController:didSelectPerson: instead.
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person NS_DEPRECATED_IOS(2_0, 8_0);

// Deprecated, use predicateForSelectionOfProperty and/or -peoplePickerNavigationController:didSelectPerson:property:identifier: instead.
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier NS_DEPRECATED_IOS(2_0, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  AddressBookUI.framework/Headers/ABNewPersonViewController.h
//
//  ABNewPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABNewPersonViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use +[CNContactViewController viewControllerForNewContact:] from ContactsUI.framework instead")
@interface ABNewPersonViewController : UIViewController

// ABNewPersonViewController does not support subclassing in iOS 7.0 and later. A nil instance will be returned.

@property(nonatomic,assign,nullable) id<ABNewPersonViewControllerDelegate> newPersonViewDelegate;
- (id<ABNewPersonViewControllerDelegate>)newPersonViewDelegate __attribute__((objc_method_family(none)));

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

    // Specify a displayedPerson to prefill some fields in the card. This is optional.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite,nullable) ABRecordRef displayedPerson;
    // Specify a parentGroup the person should be added to when saved. This is optional.
@property(nonatomic,readwrite,nullable) ABRecordRef parentGroup;

@end

@protocol ABNewPersonViewControllerDelegate <NSObject>

    // Called when the user selects Save or Cancel. If the new person was saved, person will be
    // a valid person that was saved into the Address Book. Otherwise, person will be NULL.
    // It is up to the delegate to dismiss the view controller.
- (void)newPersonViewController:(ABNewPersonViewController *)newPersonView didCompleteWithNewPerson:(nullable ABRecordRef)person;

@end

NS_ASSUME_NONNULL_END
// ==========  AddressBookUI.framework/Headers/ABPersonViewController.h
//
//  ABPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <AddressBook/AddressBook.h>

@protocol ABPersonViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use +[CNContactViewController viewControllerForContact:] from ContactsUI.framework instead")
@interface ABPersonViewController : UIViewController <UIViewControllerRestoration>

// ABPersonViewController does not support subclassing in iOS 7.0 and later. A nil instance will be returned.

@property(nonatomic,assign,nullable) id<ABPersonViewControllerDelegate> personViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef displayedPerson;


    // An array of NSNumber instances representing the properties (ABPropertyID) that should
    // be visible when viewing the person. Note that all the properties are visible when
    // editing a person.
@property(nonatomic,copy,nullable) NSArray<NSNumber*> *displayedProperties;

    // Indicates whether an edit/save button should be shown.
@property(nonatomic) BOOL allowsEditing;

    // Specifies whether buttons appear to let the user perform actions such as sharing the contact,
    // initiating a FaceTime call, or sending a text message.
@property(nonatomic) BOOL allowsActions NS_AVAILABLE_IOS(4_0);

    // Indicates whether to show data from people linked to the displayedPerson, defaults to NO
@property(nonatomic) BOOL shouldShowLinkedPeople NS_AVAILABLE_IOS(4_0);

	// Indicates whether to highlight a certain value for the displayedPerson,
    // if a single value property is specified, identifier will be ignored.
- (void)setHighlightedItemForProperty:(ABPropertyID)property withIdentifier:(ABMultiValueIdentifier)identifier;

@end

@protocol ABPersonViewControllerDelegate <NSObject>

    // Called when the user selects an individual value in the Person view, identifier will be kABMultiValueInvalidIdentifier if a single value property was selected.
    // Return NO if you do not want anything to be done or if you are handling the actions yourself.
    // Return YES if you want the ABPersonViewController to perform its default action.
- (BOOL)personViewController:(ABPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier;

@end

NS_ASSUME_NONNULL_END
// ==========  AddressBookUI.framework/Headers/ABAddressFormatting.h
//
//  ABAddressFormatting.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <AddressBook/AddressBook.h>

#if defined(__cplusplus)
extern "C" {
#endif    

NS_ASSUME_NONNULL_BEGIN
    
    // address: an address dictionary obtained representing the address (kABPersonAddressProperty) of a person (ABRecordRef)
    // addCountryName: whether to always include the country name in the address string, regardless of whether it is specified
    //                 in the dictionary. If not specified by the user a localized country name will be added.
    // returns a formatted multi line string that contains the full address. The string is likely to contain line endings.
NSString *ABCreateStringWithAddressDictionary(NSDictionary *address, BOOL addCountryName) NS_RETURNS_RETAINED AB_DEPRECATED("Use CNPostalAddressFormatter from Contacts.framework instead");

NS_ASSUME_NONNULL_END
    
#if defined(__cplusplus)
}
#endif
// ==========  AddressBookUI.framework/Headers/AddressBookUI.h
/*
 *  AddressBookUI.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <AddressBook/AddressBook.h>

#import <AddressBookUI/ABPeoplePickerNavigationController.h>
#import <AddressBookUI/ABPersonViewController.h>
#import <AddressBookUI/ABNewPersonViewController.h>
#import <AddressBookUI/ABUnknownPersonViewController.h>
#import <AddressBookUI/ABAddressFormatting.h>
