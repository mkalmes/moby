// ==========  AddressBook.framework/Headers/ABGroup.h
/*
 *  ABGroup.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABGroup is a non-ordered collection of records.
 *
 */

#ifndef __ABGroup__
#define __ABGroup__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABSource.h>

AB_EXTERN const int kABGroupNameProperty AB_DEPRECATED("use CNGroup.name");

// ABGroupCreate creates a new group in the default source
AB_EXTERN ABRecordRef ABGroupCreate(void) AB_DEPRECATED("use [[CNMutableGroup alloc] init]");
AB_EXTERN ABRecordRef ABGroupCreateInSource(ABRecordRef source) AB_DEPRECATED("use [[CNMutableGroup alloc] init] and [CNSaveRequest addGroup:toContainerWithIdentifier:]");

AB_EXTERN ABRecordRef ABGroupCopySource(ABRecordRef group) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainerOfGroupWithIdentifier:] error:]");

AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembers(ABRecordRef group) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInGroupWithIdentifier:]");
AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembersWithSortOrdering(ABRecordRef group, ABPersonSortOrdering sortOrdering) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInGroupWithIdentifier:] and sortOrder");
AB_EXTERN bool ABGroupAddMember(ABRecordRef group, ABRecordRef person, CFErrorRef* error) AB_DEPRECATED("use [CNSaveRequest addMember:toGroup:]");
AB_EXTERN bool ABGroupRemoveMember(ABRecordRef group, ABRecordRef member, CFErrorRef* error) AB_DEPRECATED("use [CNSaveRequest removeMember:fromGroup:]");

// Finding groups
AB_EXTERN ABRecordRef ABAddressBookGetGroupWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:[CNGroup predicateForGroupsWithIdentifiers:] error:]");
AB_EXTERN CFIndex ABAddressBookGetGroupCount(ABAddressBookRef addressBook) AB_DEPRECATED("use count of fetch results for [CNContactStore groupsMatchingPredicate:nil error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroups(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:nil error:]");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroupsInSource(ABAddressBookRef addressBook, ABRecordRef source) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:[CNGroup predicateForGroupsInContainerWithIdentifier:] error:]");

#endif

// ==========  AddressBook.framework/Headers/ABAddressBook.h
/*
 *  ABAddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __ABAddressBook__
#define __ABAddressBook__

#include <AddressBook/AddressBookDefines.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABRecord.h>

AB_EXTERN const CFStringRef ABAddressBookErrorDomain AB_DEPRECATED("use CNErrorDomain");

enum {
    kABOperationNotPermittedByStoreError = 0,   // deprecated, use CNErrorCodePolicyViolation
    kABOperationNotPermittedByUserError         // deprecated, use CNErrorCodeAuthorizationDenied
};

typedef CFTypeRef ABAddressBookRef AB_DEPRECATED("use CNContactStore");

// To check the app's access to contact data. Based upon the access, the app could
// display or hide its UI elements that would access any AddressBook API.
//
// kABAuthorizationStatusNotDetermined
// The user has not yet made a choice regarding whether this app can access the data class.
//
// kABAuthorizationStatusRestricted
// This application is not authorized to access the data class. The user cannot change
// this application’s status, possibly due to active restrictions such as parental controls
// being in place.
//
// kABAuthorizationStatusDenied
// The user explicitly denied access to the data class for this application.
//
// kABAuthorizationStatusAuthorized
// This application is authorized to access the data class.
//
typedef CF_ENUM(CFIndex, ABAuthorizationStatus) {
    kABAuthorizationStatusNotDetermined = 0,    // deprecated, use CNAuthorizationStatusNotDetermined
    kABAuthorizationStatusRestricted,           // deprecated, use CNAuthorizationStatusRestricted
    kABAuthorizationStatusDenied,               // deprecated, use CNAuthorizationStatusDenied
    kABAuthorizationStatusAuthorized            // deprecated, use CNAuthorizationStatusAuthorized
} AB_DEPRECATED("use CNAuthorizationStatus");
AB_EXTERN ABAuthorizationStatus ABAddressBookGetAuthorizationStatus(void) AB_DEPRECATED("use [CNContactStore authorizationStatusForEntityType:]");

// Call ABAddressBookCreateWithOptions to create an instance of AddressBook. The
// ABAddressBookRef will initially not have access to contact data. The app must
// then call ABAddressBookRequestAccessWithCompletion to request this access.
// The options argument is reserved for future use. Currently it will always be NULL.
// If access to contact data is already restricted or denied, this will fail returning
// a NULL ABAddressBookRef with error kABOperationNotPermittedByUserError.
AB_EXTERN ABAddressBookRef ABAddressBookCreateWithOptions(CFDictionaryRef options, CFErrorRef* error) AB_DEPRECATED("use [[CNContactStore alloc] init]");

AB_EXTERN ABAddressBookRef ABAddressBookCreate(void) AB_DEPRECATED("use [[CNContactStore alloc] init]");

// Users are able to grant or deny access to contact data on a per-app basis. To request
// access to contact data, call ABAddressBookRequestAccessWithCompletion. This will not
// block the app while the user is being asked to grant or deny access. Until access has
// been granted, a non-NULL ABAddressBookRef will not contain any contacts and any attempt to
// modify contacts will fail with CFErrorRef returning kABOperationNotPermittedByUserError.
// The user will only be prompted the first time access is requested; any subsequent calls
// to ABAddressBookCreateWithOptions will use the existing permissions. The completion
// handler is called on an arbitrary queue. If the ABAddressBookRef is used throughout the app,
// then all usage should be dispatched to the same queue to use ABAddressBookRef in a
// thread-safe manner.
typedef void(^ABAddressBookRequestAccessCompletionHandler)(bool granted, CFErrorRef error) AB_DEPRECATED("");
AB_EXTERN void ABAddressBookRequestAccessWithCompletion(ABAddressBookRef addressBook,  ABAddressBookRequestAccessCompletionHandler completion) AB_DEPRECATED("use [CNContactStore requestAccessForEntityType:completionHandler:]");

AB_EXTERN bool ABAddressBookSave(ABAddressBookRef addressBook, CFErrorRef* error) AB_DEPRECATED("use [CNContactStore executeSaveRequest:error:]");
AB_EXTERN bool ABAddressBookHasUnsavedChanges(ABAddressBookRef addressBook) AB_DEPRECATED("");

AB_EXTERN bool ABAddressBookAddRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error) AB_DEPRECATED("use CNSaveRequest");
AB_EXTERN bool ABAddressBookRemoveRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error) AB_DEPRECATED("use CNSaveRequest");

// Some labels are special keys representing generic labels. Use this function to obtain
// a localized string for a label to display to a user.
AB_EXTERN CFStringRef ABAddressBookCopyLocalizedLabel(CFStringRef label) AB_DEPRECATED("use [CNLabeledValue localizedStringForLabel:]");

// Register an external change callback if you want to be informed of changes to the
// shared Address Book database by other instances or processes. The callback will be
// invoked by CFRunLoop on the thread where it was registered. The ABAddressBook does
// not take any action by default to flush or synchronize cached state with the database.
// If you want to ensure that you don't see any stale values, use ABAddressBookRevert().

// The info argument may eventually contain information describing the change. Currently
// it will always be NULL.
typedef void (*ABExternalChangeCallback)(ABAddressBookRef addressBook, CFDictionaryRef info, void *context) AB_DEPRECATED("");

AB_EXTERN void ABAddressBookRegisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context) AB_DEPRECATED("use CNContactStoreDidChangeNotification");

// When unregistering a callback both the callback and the context need to match the ones
// that were registered.
AB_EXTERN void ABAddressBookUnregisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context) AB_DEPRECATED("");

// ABAddressBookRevert() discards all cached properties and any unsaved changes so that
// records and properties retrieved subsequently will reflect any changes made by external
// ABAddressBook instances. If records were deleted externally, the corresponding ABRecord
// instances will return NULL for all properties. If necessary you can identify these
// deleted records by checking whether the class accessor (eg. ABPersonGetPersonWithRecordID())
// returns the record.
AB_EXTERN void ABAddressBookRevert(ABAddressBookRef addressBook) AB_DEPRECATED("refetch CN objects");

#endif
// ==========  AddressBook.framework/Headers/ABPerson.h
/*
 *  ABPerson.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABPerson corresponds to a contact such as a person or organization.
 *
 */

#ifndef __ABPerson__
#define __ABPerson__

#include <CoreFoundation/CoreFoundation.h>

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABSource.h>

#include <Availability.h>

// ABPersonCreate creates a new person in the default source
AB_EXTERN ABRecordRef ABPersonCreate(void) AB_DEPRECATED("use [[CNMutableContact alloc] init]");
AB_EXTERN ABRecordRef ABPersonCreateInSource(ABRecordRef source) AB_DEPRECATED("use [[CNMutableContact alloc] init] and [CNSaveRequest addContact:toContainerWithIdentifier:]");

AB_EXTERN ABRecordRef ABPersonCopySource(ABRecordRef person) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainerOfContactWithIdentifier:] error:]");

// Returns an array of all the linked people, including the person passed in. If the person is not linked, returns an array with the person passed in.
AB_EXTERN CFArrayRef ABPersonCopyArrayOfAllLinkedPeople(ABRecordRef person) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsLinkedToContact:] and unifyResults = NO");

AB_EXTERN ABPropertyType ABPersonGetTypeOfProperty(ABPropertyID property) AB_DEPRECATED("");
AB_EXTERN CFStringRef ABPersonCopyLocalizedPropertyName(ABPropertyID property) AB_DEPRECATED("use [CNContact localizedStringForKey:]");

typedef uint32_t ABPersonSortOrdering AB_DEPRECATED("use CNContactSortOrder");
enum {
    kABPersonSortByFirstName = 0,   // deprecated, use CNContactSortOrderGivenName
    kABPersonSortByLastName  = 1    // deprecated, use CNContactSortOrderFamilyName"
};

AB_EXTERN ABPersonSortOrdering ABPersonGetSortOrdering(void) AB_DEPRECATED("use [[CNContactsUserDefaults sharedDefaults] sortOrder]");

typedef uint32_t ABPersonCompositeNameFormat AB_DEPRECATED("");
enum  {
    kABPersonCompositeNameFormatFirstNameFirst = 0, // deprecated
    kABPersonCompositeNameFormatLastNameFirst  = 1  // deprecated
};

// Composite Names
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormat(void) AB_DEPRECATED("");
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormatForRecord(ABRecordRef record) AB_DEPRECATED("");
AB_EXTERN CFStringRef ABPersonCopyCompositeNameDelimiterForRecord(ABRecordRef record) AB_DEPRECATED("");

// Images
typedef enum {
    kABPersonImageFormatThumbnail = 0,      // deprecated
    kABPersonImageFormatOriginalSize = 2    // deprecated
} ABPersonImageFormat AB_DEPRECATED("");

AB_EXTERN bool ABPersonSetImageData(ABRecordRef person, CFDataRef imageData, CFErrorRef* error) AB_DEPRECATED("use CNMutableContact.imageData");
AB_EXTERN CFDataRef ABPersonCopyImageData(ABRecordRef person) AB_DEPRECATED("use CNContact.imageData");
AB_EXTERN CFDataRef ABPersonCopyImageDataWithFormat(ABRecordRef person, ABPersonImageFormat format) AB_DEPRECATED("use CNContact.imageData or CNContact.thumbnailImageData");

AB_EXTERN bool ABPersonHasImageData(ABRecordRef person) AB_DEPRECATED("");
AB_EXTERN bool ABPersonRemoveImageData(ABRecordRef person, CFErrorRef* error) AB_DEPRECATED("use CNMutableContact.imageData = nil");

// Sorting
AB_EXTERN CFComparisonResult ABPersonComparePeopleByName(ABRecordRef person1, ABRecordRef person2, ABPersonSortOrdering ordering) AB_DEPRECATED("use [CNContact comparatorForNameSortOrder:]");

// Finding people
AB_EXTERN CFIndex ABAddressBookGetPersonCount(ABAddressBookRef addressBook) AB_DEPRECATED("use count of fetch results for CNContactFetchRequest with predicate = nil");
AB_EXTERN ABRecordRef ABAddressBookGetPersonWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID) AB_DEPRECATED("use [CNContactStore unifiedContactWithIdentifier:keysToFetch:error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeople(ABAddressBookRef addressBook) AB_DEPRECATED("use CNContactFetchRequest with predicate = nil");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSource(ABAddressBookRef addressBook, ABRecordRef source) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInContainerWithIdentifier:] and unifyResults = NO");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSourceWithSortOrdering(ABAddressBookRef addressBook, ABRecordRef source, ABPersonSortOrdering sortOrdering) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInContainerWithIdentifier:] and unifyResults = NO and sortOrder");

AB_EXTERN CFArrayRef ABAddressBookCopyPeopleWithName(ABAddressBookRef addressBook, CFStringRef name) AB_DEPRECATED("use [CNContactStore unifiedContactsMatchingPredicate:[CNContact predicateForContactsMatchingName:] keysToFetch: error:]");

// VCard
    // Creates an array of people from a vcard representation. Source is optional. The people
    // will be created in the source given as the first argument, or the default source if NULL.
AB_EXTERN CFArrayRef ABPersonCreatePeopleInSourceWithVCardRepresentation(ABRecordRef source, CFDataRef vCardData) AB_DEPRECATED("use [CNContactVCardSerialization contactsWithData:error:]");
    // Creates a vCard representation of the people passed in.
AB_EXTERN CFDataRef ABPersonCreateVCardRepresentationWithPeople(CFArrayRef people) AB_DEPRECATED("use [CNContactVCardSerialization dataWithContacts:error:]");

// Generic labels
AB_EXTERN const CFStringRef kABWorkLabel AB_DEPRECATED("use CNLabelWork");
AB_EXTERN const CFStringRef kABHomeLabel AB_DEPRECATED("use CNLabelHome");
AB_EXTERN const CFStringRef kABOtherLabel AB_DEPRECATED("use CNLabelOther");

// Property keys
AB_EXTERN const ABPropertyID kABPersonFirstNameProperty AB_DEPRECATED("use CNContact.givenName");                               // First name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonLastNameProperty AB_DEPRECATED("use CNContact.familyName");                               // Last name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonMiddleNameProperty AB_DEPRECATED("use CNContact.middleName");                             // Middle name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonPrefixProperty AB_DEPRECATED("use CNContact.namePrefix");                                 // Prefix ("Sir" "Duke" "General") - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonSuffixProperty AB_DEPRECATED("use CNContact.nameSuffix");                                 // Suffix ("Jr." "Sr." "III") - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonNicknameProperty AB_DEPRECATED("use CNContact.nickname");                                 // Nickname - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonFirstNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticGivenName");               // First name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonLastNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticFamilyName");               // Last name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonMiddleNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticMiddleName");             // Middle name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonOrganizationProperty AB_DEPRECATED("use CNContact.organizationName");                     // Company name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonDepartmentProperty AB_DEPRECATED("use CNContact.departmentName");                         // Department name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonJobTitleProperty AB_DEPRECATED("use CNContact.jobTitle");                                 // Job Title - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonEmailProperty AB_DEPRECATED("use CNContact.emailAddresses");                              // Email(s) - kABMultiStringPropertyType
AB_EXTERN const ABPropertyID kABPersonBirthdayProperty AB_DEPRECATED("use CNContact.birthday");                                 // Birthday associated with this person - kABDateTimePropertyType
AB_EXTERN const ABPropertyID kABPersonNoteProperty AB_DEPRECATED("use CNContact.note");                                         // Note - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonCreationDateProperty AB_DEPRECATED("");                                                   // Creation Date (when first saved)
AB_EXTERN const ABPropertyID kABPersonModificationDateProperty AB_DEPRECATED("");                                               // Last saved date

// Addresses
AB_EXTERN const ABPropertyID kABPersonAddressProperty AB_DEPRECATED("use CNContact.postalAddresses");                           // Street address - kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonAddressStreetKey AB_DEPRECATED("use CNPostalAddress.street");
AB_EXTERN const CFStringRef kABPersonAddressCityKey AB_DEPRECATED("use CNPostalAddress.city");
AB_EXTERN const CFStringRef kABPersonAddressStateKey AB_DEPRECATED("use CNPostalAddress.state");
AB_EXTERN const CFStringRef kABPersonAddressZIPKey AB_DEPRECATED("use CNPostalAddress.postalCode");
AB_EXTERN const CFStringRef kABPersonAddressCountryKey AB_DEPRECATED("use CNPostalAddress.country");
AB_EXTERN const CFStringRef kABPersonAddressCountryCodeKey AB_DEPRECATED("use CNPostalAddress.ISOCountryCode");

/*
 * kABPersonAddressCountryCodeKey code must be in the form of 2 character iso 3166 country codes
 *
 * eg:
 *    fr = France
 *    us = United States
 * etc.
 *
 */

// Dates
AB_EXTERN const ABPropertyID kABPersonDateProperty AB_DEPRECATED("use CNContact.dates");                                        // Dates associated with this person - kABMultiDatePropertyType
AB_EXTERN const CFStringRef kABPersonAnniversaryLabel AB_DEPRECATED("use CNLabelDateAnniversary");

// Kind
AB_EXTERN const ABPropertyID kABPersonKindProperty AB_DEPRECATED("use CNContact.contactType");                                  // Person/Organization - kABIntegerPropertyType
AB_EXTERN const CFNumberRef kABPersonKindPerson AB_DEPRECATED("use CNContactTypePerson");
AB_EXTERN const CFNumberRef kABPersonKindOrganization AB_DEPRECATED("use CNContactTypeOrganization");

// Phone numbers
AB_EXTERN const ABPropertyID kABPersonPhoneProperty AB_DEPRECATED("use CNContact.phoneNumbers");                                // Generic phone number - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonPhoneMobileLabel AB_DEPRECATED("use CNLabelPhoneNumberMobile");
AB_EXTERN const CFStringRef kABPersonPhoneIPhoneLabel AB_DEPRECATED("use CNLabelPhoneNumberiPhone");
AB_EXTERN const CFStringRef kABPersonPhoneMainLabel AB_DEPRECATED("use CNLabelPhoneNumberMain");
AB_EXTERN const CFStringRef kABPersonPhoneHomeFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberHomeFax");
AB_EXTERN const CFStringRef kABPersonPhoneWorkFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberWorkFax");
AB_EXTERN const CFStringRef kABPersonPhoneOtherFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberOtherFax");
AB_EXTERN const CFStringRef kABPersonPhonePagerLabel AB_DEPRECATED("use CNLabelPhoneNumberPager");

// IM
AB_EXTERN const ABPropertyID kABPersonInstantMessageProperty AB_DEPRECATED("use CNContact.instantMessageAddresses");            // Instant Messaging - kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceKey AB_DEPRECATED("use CNInstantMessageAddress.service");             // Service ("Yahoo", "Jabber", etc.)
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceYahoo AB_DEPRECATED("use CNInstantMessageServiceYahoo");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceJabber AB_DEPRECATED("use CNInstantMessageServiceJabber");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceMSN AB_DEPRECATED("use CNInstantMessageServiceMSN");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceICQ AB_DEPRECATED("use CNInstantMessageServiceICQ");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceAIM AB_DEPRECATED("use CNInstantMessageServiceAIM");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceQQ AB_DEPRECATED("use CNInstantMessageServiceQQ");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGoogleTalk AB_DEPRECATED("use CNInstantMessageServiceGoogleTalk");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceSkype AB_DEPRECATED("use CNInstantMessageServiceSkype");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceFacebook AB_DEPRECATED("use CNInstantMessageServiceFacebook");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGaduGadu AB_DEPRECATED("use CNInstantMessageServiceGaduGadu");

AB_EXTERN const CFStringRef kABPersonInstantMessageUsernameKey AB_DEPRECATED("use CNInstantMessageAddress.username");           // Username

// URLs
AB_EXTERN const ABPropertyID kABPersonURLProperty AB_DEPRECATED("use CNContact.urlAddresses");                                  // URL - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonHomePageLabel AB_DEPRECATED("use CNLabelURLAddressHomePage");                              // Home Page

// Related names
AB_EXTERN const ABPropertyID kABPersonRelatedNamesProperty AB_DEPRECATED("use CNContact.contactRelations");                     // Names - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonFatherLabel AB_DEPRECATED("use CNLabelContactRelationFather");                             // Father
AB_EXTERN const CFStringRef kABPersonMotherLabel AB_DEPRECATED("use CNLabelContactRelationMother");                             // Mother
AB_EXTERN const CFStringRef kABPersonParentLabel AB_DEPRECATED("use CNLabelContactRelationParent");                             // Parent
AB_EXTERN const CFStringRef kABPersonBrotherLabel AB_DEPRECATED("use CNLabelContactRelationBrother");                           // Brother
AB_EXTERN const CFStringRef kABPersonSisterLabel AB_DEPRECATED("use CNLabelContactRelationSister");                             // Sister
AB_EXTERN const CFStringRef kABPersonChildLabel AB_DEPRECATED("use CNLabelContactRelationChild");                               // Child
AB_EXTERN const CFStringRef kABPersonFriendLabel AB_DEPRECATED("use CNLabelContactRelationFriend");                             // Friend
AB_EXTERN const CFStringRef kABPersonSpouseLabel AB_DEPRECATED("use CNLabelContactRelationSpouse");                             // Spouse
AB_EXTERN const CFStringRef kABPersonPartnerLabel AB_DEPRECATED("use CNLabelContactRelationPartner");                           // Partner
AB_EXTERN const CFStringRef kABPersonAssistantLabel AB_DEPRECATED("use CNLabelContactRelationAssistant");                       // Assistant
AB_EXTERN const CFStringRef kABPersonManagerLabel AB_DEPRECATED("use CNLabelContactRelationManager");                           // Manager
    
// Social Profile
AB_EXTERN const ABPropertyID kABPersonSocialProfileProperty AB_DEPRECATED("use CNContact.socialProfiles");                      // kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonSocialProfileURLKey AB_DEPRECATED("use CNSocialProfile.urlString");                        // string representation of a url for the social profile
    // the following properties are optional
    AB_EXTERN const CFStringRef kABPersonSocialProfileServiceKey AB_DEPRECATED("use CNSocialProfile.service");                  // string representing the name of the service (Twitter, Facebook, LinkedIn, etc.)
    AB_EXTERN const CFStringRef kABPersonSocialProfileUsernameKey AB_DEPRECATED("use CNSocialProfile.username");                // string representing the user visible name
    AB_EXTERN const CFStringRef kABPersonSocialProfileUserIdentifierKey AB_DEPRECATED("use CNSocialProfile.userIdentifier");    // string representing the service specific identifier (optional)

AB_EXTERN const CFStringRef kABPersonSocialProfileServiceTwitter AB_DEPRECATED("use CNSocialProfileServiceTwitter");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceSinaWeibo AB_DEPRECATED("use CNSocialProfileServiceSinaWeibo");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceGameCenter AB_DEPRECATED("use CNSocialProfileServiceGameCenter");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFacebook AB_DEPRECATED("use CNSocialProfileServiceFacebook");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceMyspace AB_DEPRECATED("use CNSocialProfileServiceMySpace");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceLinkedIn AB_DEPRECATED("use CNSocialProfileServiceLinkedIn");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFlickr AB_DEPRECATED("use CNSocialProfileServiceFlickr");

// Alternate birthday
AB_EXTERN const ABPropertyID kABPersonAlternateBirthdayProperty AB_DEPRECATED("use CNContact.nonGregorianBirthday");            // kABDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayCalendarIdentifierKey AB_DEPRECATED("use NSDateComponents.calendar");     // string representing the calendar identifier for CFCalendarRef
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayEraKey AB_DEPRECATED("use NSDateComponents.era");                         // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayYearKey AB_DEPRECATED("use NSDateComponents.year");                       // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayMonthKey AB_DEPRECATED("use NSDateComponents.month");                     // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayIsLeapMonthKey AB_DEPRECATED("use NSDateComponents.isLeapMonth");         // CFNumberRef - kCFNumberCharType (aka NSNumber Bool type)
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayDayKey AB_DEPRECATED("use NSDateComponents.day");                         // CFNumberRef - kCFNumberNSIntegerType

#endif
// ==========  AddressBook.framework/Headers/AddressBook.h
/*
 *  AddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *
 *  !!!! DEPRECATED !!!!
 *
 *  AddressBook framework is deprecated as of iOS 9.0
 *  Please use Contacts framework instead.
 *
 *  !!!! DEPRECATED !!!!
 *
 *
 *  This library is not threadsafe. Recommended practice is to use
 *  a separate ABAddressBook instance on each thread in your
 *  application. You can register a callback on each instance
 *  that will be invoked when another instance in another thread
 *  or process makes changes to the shared AddressBook database.
 *  
 *  Alternately if needed, multiple threads could use a shared 
 *  ABAddressBook instance by serializing all AddressBook API usage 
 *  with the same dispatch queue. It is important to follow these 
 *  rules when doing this:
 *  1) Threads can only use value types from the block's
 *     ABRecordRef and ABMultiValueRef objects.
 *  2) Threads can reference these objects by their ABRecordID
 *     and ABMultiValueIdentifier.
 *  3) The AddressBook change callback must also be serialized
 *     with the same dispatch queue. For example, to revert
 *     the ABAddressBook instance.
 *
 *  Changes to records have no external effect until the ABAddressBook
 *  is saved. It is possible for other ABAddressBook instances to make
 *  conflicting changes during that time. To reduce the likelihood
 *  of that event, save the ABAddressBook as soon as possible after
 *  each set of related changes.
 *
 */

#ifndef __AddressBook__
#define __AddressBook__

#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABGroup.h>
#include <AddressBook/ABMultiValue.h>

#endif


// ==========  AddressBook.framework/Headers/ABMultiValue.h
/*
 *  ABMultiValue.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  MultiValues are ordered, homogeneous collections of values. Each
 *  value has a unique persistent identifier which can be use to
 *  identify the value across changes to the MultiValue (ie. when
 *  the value's index may have changed). Each value may also have a
 *  non-unique string label.
 *
 */

#ifndef __ABMultiValue__
#define __ABMultiValue__

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABRecord.h>

typedef CFTypeRef ABMultiValueRef AB_DEPRECATED("use NSArray of CNLabeledValue");

typedef int32_t ABMultiValueIdentifier AB_DEPRECATED("use CNLabeledValue.identifier");
#define kABMultiValueInvalidIdentifier -1

// Type of the contained values
AB_EXTERN ABPropertyType ABMultiValueGetPropertyType(ABMultiValueRef multiValue) AB_DEPRECATED("");

AB_EXTERN CFIndex ABMultiValueGetCount(ABMultiValueRef multiValue) AB_DEPRECATED("use NSArray.count with the labeled value property");

AB_EXTERN CFTypeRef ABMultiValueCopyValueAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] value] with the labeled value property");
AB_EXTERN CFArrayRef ABMultiValueCopyArrayOfAllValues(ABMultiValueRef multiValue) AB_DEPRECATED("use [NSArray enumerateObjectsUsingBlock:] with the labeled value property and collect the values");

AB_EXTERN CFStringRef ABMultiValueCopyLabelAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] label] with the labeled value property");
    
AB_EXTERN CFIndex ABMultiValueGetIndexForIdentifier(ABMultiValueRef multiValue, ABMultiValueIdentifier identifier) AB_DEPRECATED("use [NSArray indexOfObjectPassingTest:] with the labeled value property and find the identifier");
AB_EXTERN ABMultiValueIdentifier ABMultiValueGetIdentifierAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] identifier] with the labeled value property");
    
AB_EXTERN CFIndex ABMultiValueGetFirstIndexOfValue(ABMultiValueRef multiValue, CFTypeRef value) AB_DEPRECATED("use [NSArray indexOfObjectPassingTest:] with the labeled value property and find the value");

// Mutable multivalues

typedef CFTypeRef ABMutableMultiValueRef AB_DEPRECATED("use NSMutableArray of CNLabeledValue");

AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutable(ABPropertyType type) AB_DEPRECATED("use [[NSMutableArray alloc] init]");
AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutableCopy(ABMultiValueRef multiValue) AB_DEPRECATED("use [NSArray mutableCopy]");
 
AB_EXTERN bool ABMultiValueAddValueAndLabel(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, ABMultiValueIdentifier *outIdentifier) AB_DEPRECATED("use [NSMutableArray addObject:[CNLabeledValue labeledValueWithLabel:value:]]");
AB_EXTERN bool ABMultiValueInsertValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, CFIndex index, ABMultiValueIdentifier *outIdentifier) AB_DEPRECATED("use [NSMutableArray insertObject:[CNLabeledValue labeledValueWithLabel:value:] atIndex:]");
AB_EXTERN bool ABMultiValueRemoveValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [NSMutableArray removeObjectAtIndex:]");
AB_EXTERN bool ABMultiValueReplaceValueAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFIndex index) AB_DEPRECATED("use [NSMutableArray replaceObjectAtIndex: withObject:[CNLabeledValue labeledValueBySettingValue:]]");
AB_EXTERN bool ABMultiValueReplaceLabelAtIndex(ABMutableMultiValueRef multiValue, CFStringRef label, CFIndex index) AB_DEPRECATED("use [NSMutableArray replaceObjectAtIndex: withObject:[CNLabeledValue labeledValueBySettingLabel:]]");
    
#endif

// ==========  AddressBook.framework/Headers/ABSource.h
/*
 *  ABSource.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 */


#ifndef __ABSource__
#define __ABSource__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>

#include <Availability.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

#define kABSourceTypeSearchableMask  0x01000000 // deprecated

enum {
    kABSourceTypeLocal       = 0x0,                                                     // deprecated, use CNContainerTypeLocal
    kABSourceTypeExchange    = 0x1,                                                     // deprecated, used CNContainerTypeExchange
    kABSourceTypeExchangeGAL = kABSourceTypeExchange | kABSourceTypeSearchableMask,     // deprecated

    kABSourceTypeMobileMe    = 0x2,                                                     // deprecated

    kABSourceTypeLDAP        = 0x3 | kABSourceTypeSearchableMask,                       // deprecated
    
    kABSourceTypeCardDAV     = 0x4,                                                     // deprecated, use CNContainerTypeCardDAV
    kABSourceTypeCardDAVSearch = kABSourceTypeCardDAV | kABSourceTypeSearchableMask,    // deprecated
};
typedef int ABSourceType AB_DEPRECATED("");

#endif

AB_EXTERN const ABPropertyID kABSourceNameProperty AB_DEPRECATED("use CNContainer.name"); // string
AB_EXTERN const ABPropertyID kABSourceTypeProperty AB_DEPRECATED("use CNContainer.type"); // CFNumberRef of ABSourceType (int)

AB_EXTERN ABRecordRef ABAddressBookCopyDefaultSource(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[CNContactStore.defaultContainerIdentifier]] error:]");

AB_EXTERN ABRecordRef ABAddressBookGetSourceWithRecordID(ABAddressBookRef addressBook, ABRecordID sourceID) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers:] error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllSources(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:nil error:]");

#endif
// ==========  AddressBook.framework/Headers/ABRecord.h
/*
 *  ABRecord.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABRecord corresponds to a persistent item, currently either
 *  a contact or a group. Records have a unique persistent integer
 *  ID and a collection of properties with integer keys.
 *
 */

#ifndef __ABRecord__
#define __ABRecord__

#include <AddressBook/AddressBookDefines.h>
#include <CoreFoundation/CoreFoundation.h>
        
typedef CFTypeRef ABRecordRef AB_DEPRECATED("use CNContact, CNGroup, or CNContainer");

typedef int32_t ABRecordID AB_DEPRECATED("use CN object's identifier");
typedef int32_t ABPropertyID AB_DEPRECATED("");

typedef uint32_t ABRecordType AB_DEPRECATED("");
enum {
    kABPersonType = 0,
    kABGroupType  = 1,
    kABSourceType = 2
};

#define kABMultiValueMask (1 << 8) // deprecated
#define kABRecordInvalidID -1 // deprecated
#define kABPropertyInvalidID -1 // deprecated

typedef uint32_t ABPropertyType AB_DEPRECATED("");
enum {
    kABInvalidPropertyType         = 0x0,                                           // deprecated
    kABStringPropertyType          = 0x1,                                           // deprecated
    kABIntegerPropertyType         = 0x2,                                           // deprecated
    kABRealPropertyType            = 0x3,                                           // deprecated
    kABDateTimePropertyType        = 0x4,                                           // deprecated
    kABDictionaryPropertyType      = 0x5,                                           // deprecated
    kABMultiStringPropertyType     = kABMultiValueMask | kABStringPropertyType,     // deprecated
    kABMultiIntegerPropertyType    = kABMultiValueMask | kABIntegerPropertyType,    // deprecated
    kABMultiRealPropertyType       = kABMultiValueMask | kABRealPropertyType,       // deprecated
    kABMultiDateTimePropertyType   = kABMultiValueMask | kABDateTimePropertyType,   // deprecated
    kABMultiDictionaryPropertyType = kABMultiValueMask | kABDictionaryPropertyType, // deprecated
};

AB_EXTERN ABRecordID ABRecordGetRecordID(ABRecordRef record) AB_DEPRECATED("use CN object's identifier");
AB_EXTERN ABRecordType ABRecordGetRecordType(ABRecordRef record) AB_DEPRECATED("");

AB_EXTERN CFTypeRef ABRecordCopyValue(ABRecordRef record, ABPropertyID property) AB_DEPRECATED("use CN object's properties");
AB_EXTERN bool ABRecordSetValue(ABRecordRef record, ABPropertyID property, CFTypeRef value, CFErrorRef* error) AB_DEPRECATED("use CN mutable object's properties");
AB_EXTERN bool ABRecordRemoveValue(ABRecordRef record, ABPropertyID property, CFErrorRef* error) AB_DEPRECATED("use CN mutable object's properties, setting to @"", @[], or nil");
    
AB_EXTERN CFStringRef ABRecordCopyCompositeName(ABRecordRef record) AB_DEPRECATED("use CNContactFormatter or CN object's name");

#endif

// ==========  AddressBook.framework/Headers/AddressBookDefines.h
//
//  AddressBookDefines.h
//  AddressBook
//
//  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
//

#ifndef AddressBook_AddressBookDefines_h
#define AddressBook_AddressBookDefines_h

#ifdef __cplusplus
    #define AB_EXTERN extern "C" __attribute__((visibility ("default")))
#else
    #define AB_EXTERN extern __attribute__((visibility ("default")))
#endif

#ifdef AB_IGNORE_DEPRECATION
    #define AB_DEPRECATED(msg)
#else
    #include <Availability.h>
    #define AB_DEPRECATED(msg) __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0, msg)
#endif

#endif
