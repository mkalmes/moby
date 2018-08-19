// ==========  Contacts.framework/Headers/CNGroup+Predicates.h
//
//  CNGroup+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNGroup.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match groups against.
 *
 * @discussion Can only use these predicates with CNContactStore.
 */
@interface CNGroup (Predicates)

+ (NSPredicate *)predicateForGroupsWithIdentifiers:(NSArray<NSString*> *)identifiers;

+ (NSPredicate *)predicateForSubgroupsInGroupWithIdentifier:(NSString *)parentGroupIdentifier NS_AVAILABLE(10_11, NA);

+ (NSPredicate *)predicateForGroupsInContainerWithIdentifier:(NSString *)containerIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContactFormatter.h
//
//  CNContactFormatter.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract The formatting styles for contact names.
 */
typedef NS_ENUM(NSInteger, CNContactFormatterStyle)
{
    /*! Combine the contact name components into a displayable full name. */
    CNContactFormatterStyleFullName,
    /*! Combine the contact phonetic name components into a displayable phonetic full name.*/
    CNContactFormatterStylePhoneticFullName,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract The formatting order of the contact name components.
 */
typedef NS_ENUM(NSInteger, CNContactDisplayNameOrder)
{
    CNContactDisplayNameOrderUserDefault,
    CNContactDisplayNameOrderGivenNameFirst,
    CNContactDisplayNameOrderFamilyNameFirst,
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Formats a contact name.
 *
 * @discussion This formatter handles international ordering and delimiting of the contact name components. This includes applying the user defaults when appropriate.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactFormatter : NSFormatter

/*!
 * @abstract The contact key descriptor required for the formatter.
 *
 * @discussion Use to fetch all contact keys required for the formatter style. Can combine key descriptors for different formatter styles in the fetch.
 *
 * @param style The formatting style to be used for the contact name.
 * @return The contact key descriptor for the formatting style.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeysForStyle:(CNContactFormatterStyle)style;


/*!
 * @abstract Formats the contact name.
 *
 * @param contact The contact whose name is to be formatted.
 * @param style The formatting style to be used for the contact name.
 * @return The formatted contact name.
 */
+ (nullable NSString *)stringFromContact:(CNContact *)contact style:(CNContactFormatterStyle)style;

/*!
 * @abstract Formats the contact name returning an attributed string.
 *
 * @discussion This behaves like +stringFromContact:style: except it returns an attributed string. Includes the attribute key CNContactPropertyAttribute.
 *
 * @param contact The contact whose name is to be formatted.
 * @param style The formatting style to be used for the contact name.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted contact name as an attributed string.
 */
+ (nullable NSAttributedString *)attributedStringFromContact:(CNContact *)contact style:(CNContactFormatterStyle)style defaultAttributes:(nullable NSDictionary *)attributes;

/*!
 * @abstract The recommended name order for a given contact.
 */
+ (CNContactDisplayNameOrder)nameOrderForContact:(CNContact *)contact;

/*!
 * @abstract The recommended delimiter to use between name components for a given contact.
 */
+ (NSString *)delimiterForContact:(CNContact *)contact;

/*!
 * @abstract The style for a contact formatter instance.
 *
 * @discussion The default value is CNContactFormatterStyleFullName.
 */
@property (NS_NONATOMIC_IOSONLY) CNContactFormatterStyle style;

/*!
 * @abstract Formats the contact name.
 *
 * @param contact The contact whose name is to be formatted.
 * @return The formatted contact name.
 */
- (nullable NSString *)stringFromContact:(CNContact *)contact;

/*!
 * @abstract Formats the contact name returning an attributed string.
 *
 * @discussion This behaves like -stringFromContact:style: except it returns an attributed string. CNContactPropertyAttribute key has the value of a CNContact name property key.
 *
 * @param contact The contact whose name is to be formatted.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted contact name as an attributed string.
 */
- (nullable NSAttributedString *)attributedStringFromContact:(CNContact *)contact defaultAttributes:(nullable NSDictionary *)attributes;

@end


// Attribute key whose value is a CNContact name component property key.
CONTACTS_EXTERN NSString * const CNContactPropertyAttribute;

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNPhoneNumber.h
//
//  CNPhoneNumber.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a phone number.
 *
 * @discussion CNPhoneNumber is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPhoneNumber : NSObject <NSCopying, NSSecureCoding>

/*! These will return nil if the stringValue is nil. */
+ (nullable instancetype)phoneNumberWithStringValue:(NSString *)stringValue;
- (nullable instancetype)initWithStringValue:(NSString *)string;

- (instancetype)init NS_DEPRECATED(10_11, 10_13, 9_0, 11_0, "Use initWithStringValue:");
+ (instancetype)new  NS_DEPRECATED(10_11, 10_13, 9_0, 11_0, "Use phoneNumberWithStringValue:");

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *stringValue;

@end


// Phone number labels
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberiPhone                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberMobile                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberMain                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberHomeFax               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberWorkFax               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberOtherFax              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberPager                 NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContactStore.h
//
//  CNContactStore.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact, CNGroup, CNContainer, CNContactFetchRequest, CNSaveRequest;

/*!
 * @abstract The entities the user can grant access to.
 */
typedef NS_ENUM(NSInteger, CNEntityType)
{
    /*! The user's contacts. */
    CNEntityTypeContacts
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract The authorization the user has given the application to access an entity type.
 */
typedef NS_ENUM(NSInteger, CNAuthorizationStatus)
{
    /*! The user has not yet made a choice regarding whether the application may access contact data. */
    CNAuthorizationStatusNotDetermined = 0,
    /*! The application is not authorized to access contact data.
     *  The user cannot change this application’s status, possibly due to active restrictions such as parental controls being in place. */
    CNAuthorizationStatusRestricted,
    /*! The user explicitly denied access to contact data for the application. */
    CNAuthorizationStatusDenied,
    /*! The application is authorized to access contact data. */
    CNAuthorizationStatusAuthorized
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Provides methods to fetch and save contacts.
 *
 * @discussion The CNContactStore is a thread safe class that can fetch and save contacts, fetch and save groups, and fetch containers.
 *
 * @note Some good practices are:
 * 1) Only fetch contact properties that will be used.
 * 2) When fetching all contacts and caching the results, first fetch all contact identifiers only. Then fetch batches of detailed contacts by identifiers as you need them.
 * 3) To aggregate several contact fetches collect a set of unique contact identifiers from the fetches. Then fetch batches of detailed contacts by identifiers.
 * 4) When CNContactStoreDidChangeNotification is posted, if you cache any fetched contacts/groups/containers then they must be refetched and the old cached objects released.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactStore : NSObject

#pragma mark - Privacy Access

/*!
 * @abstract Indicates the current authorization status to access contact data.
 *
 * @discussion Based upon the access, the application could display or hide its UI elements that would access any Contacts API. This method is thread safe.
 *
 * @return Returns the authorization status for the given entityType.
 */
+ (CNAuthorizationStatus)authorizationStatusForEntityType:(CNEntityType)entityType;

/*!
 * @abstract Request access to the user's contacts.
 *
 * @discussion Users are able to grant or deny access to contact data on a per-application basis. To request access to contact data, call requestAccessForEntityType:completionHandler:. This will not block the application while the user is being asked to grant or deny access. The user will only be prompted the first time access is requested; any subsequent CNContactStore calls will use the existing permissions. The completion handler is called on an arbitrary queue.
 *
 * @note Recommended to use CNContactStore instance methods in this completion handler instead of the UI main thread. This method is optional when CNContactStore is used on a background thread. If it is not used in that case, CNContactStore will block if the user is asked to grant or deny access.
 *
 * @param entityType Set to CNEntityTypeContacts.
 * @param completionHandler This block is called upon completion. If the user grants access then granted is YES and error is nil. Otherwise granted is NO with an error. 
 */
- (void)requestAccessForEntityType:(CNEntityType)entityType completionHandler:(void (^)(BOOL granted, NSError *__nullable error))completionHandler;


#pragma mark - Unified Contacts Helpers

/*!
 * @abstract Fetch all unified contacts matching a given predicate.
 *
 * @discussion Use only predicates from CNContact+Predicates.h. Compound predicates are not supported. Due to unification the returned contacts may have a different identifier. 
 *
 * @note To fetch all contacts use enumerateContactsWithFetchRequest:error:usingBlock:.
 *
 * @param predicate The predicate to match against.
 * @param keys The properties to fetch into the returned CNContact objects. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return An array of CNContact objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNContact*> *)unifiedContactsMatchingPredicate:(NSPredicate *)predicate keysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError *__nullable *__nullable)error;

/*!
 * @abstract Fetch a unified contact with a given identifier.
 *
 * @discussion Due to unification the returned contact may have a different identifier. To fetch a batch of contacts by identifiers use [CNContact predicateForContactsWithIdentifiers:].
 *
 * @param identifier The identifier of the contact to fetch.
 * @param keys The properties to fetch into the returned CNContact object. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return The unified contact matching or linked to the identifier. If no contact with the given identifier is found, nil is returned and error is set to CNErrorCodeRecordDoesNotExist.
 */
- (nullable CNContact *)unifiedContactWithIdentifier:(NSString *)identifier keysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError *__nullable *__nullable)error;

/*!
 * @abstract Fetch the unified contact that is the "me" card.
 *
 * @discussion Fetches the contact that is represented in the user interface as "My Card".
 *
 * @param keys The properties to fetch into the returned CNContact object. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return The unified contact that is the "me" card. If no "me" card is set, nil is returned.
 */
- (nullable CNContact *)unifiedMeContactWithKeysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_11, NA) __WATCHOS_PROHIBITED;


#pragma mark - Fetch and Save

/*!
 * @abstract Enumerates all contacts matching a contact fetch request.
 *
 * @discussion This method will wait until the enumeration is finished. If there are no results the block is not called and YES is returned.
 *
 * @param fetchRequest The contact fetch request that specifies the search criteria.
 * @param error If an error occurs, contains error information.
 * @param block Called for each matching contact. Set *stop to YES to stop the enumeration.
 * @return YES if successful, otherwise NO.
 */
- (BOOL)enumerateContactsWithFetchRequest:(CNContactFetchRequest *)fetchRequest error:(NSError *__nullable *__nullable)error usingBlock:(void (^)(CNContact *contact, BOOL *stop))block;

/*!
 * @abstract Fetch all groups matching a given predicate.
 *
 * @discussion Use only predicates from CNGroup+Predicates.h. Compound predicates are not supported.
 *
 * @param predicate The predicate to match against. Set to nil to match all groups.
 * @param error If an error occurs, contains error information.
 * @return An array of CNGroup objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNGroup*> *)groupsMatchingPredicate:(nullable NSPredicate *)predicate error:(NSError *__nullable *__nullable)error;

/*!
 * @abstract Fetch all containers matching a given predicate.
 *
 * @discussion Use only predicates from CNContainer+Predicates.h. Compound predicates are not supported.
 *
 * @param predicate The predicate to match against. Set to nil to match all containers.
 * @param error If an error occurs, contains error information.
 * @return An array of CNContainer objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNContainer*> *)containersMatchingPredicate:(nullable NSPredicate *)predicate error:(NSError *__nullable *__nullable)error;

/*!
 * @abstract Executes a save request.
 *
 * @discussion Do not access objects when save request is executing. A save request with contacts may modify the contacts while executing. A save request only applies the changes to the objects. If there are overlapping changes with multiple, concurrent CNSaveRequests then the last saved change wins.
 *
 * @param saveRequest Save request to execute.
 * @param error If an error occurs, contains error information.
 * @return YES if successful, otherwise NO.
 */
- (BOOL)executeSaveRequest:(CNSaveRequest *)saveRequest error:(NSError *__nullable *__nullable)error __WATCHOS_PROHIBITED;


#pragma mark - Miscellaneous

/*!
 *  @abstract The identifier of the default container.
 *
 *  @discussion This identifier can be used to fetch the default container.
 *
 *  @return The identifier of the default container. If the caller lacks Contacts authorization or an error occurs, nil is returned.
 */
- (nullable NSString *)defaultContainerIdentifier;

@end


#pragma mark - Constants

/*!
 * @abstract Notification posted when changes occur in another CNContactStore.
 */
CONTACTS_EXTERN NSString * const CNContactStoreDidChangeNotification NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContact+Predicates.h
//
//  CNContact+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match contacts against.
 *
 * @discussion Can only use these predicates with CNContactStore and CNContactFetchRequest.
 */
@interface CNContact (Predicates)

/*!
 * @abstract To fetch contacts matching a name.
 *
 * @discussion The name can contain any number of words.
 */
+ (NSPredicate *)predicateForContactsMatchingName:(NSString *)name;

/*! To fetch contacts matching contact identifiers. */
+ (NSPredicate *)predicateForContactsWithIdentifiers:(NSArray<NSString*> *)identifiers;

+ (NSPredicate *)predicateForContactsInGroupWithIdentifier:(NSString *)groupIdentifier;

+ (NSPredicate *)predicateForContactsInContainerWithIdentifier:(NSString *)containerIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContactRelation.h
//
//  CNContactRelation.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a related contact.
 *
 * @discussion CNContactRelation is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactRelation : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)contactRelationWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end


// Contact relation labels
CONTACTS_EXTERN NSString * const CNLabelContactRelationFather             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMother             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParent             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrother            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSister             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSon                NS_AVAILABLE(10_13, 11_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughter           NS_AVAILABLE(10_13, 11_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationChild              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFriend             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSpouse             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationPartner            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAssistant          NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationManager            NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNMutablePostalAddress.h
//
//  CNMutablePostalAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNPostalAddress.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a postal address.
 *
 * @discussion CNMutablePostalAddress is not thread safe.
 *
 * @note To remove properties when saving a mutable postal address, set string properties to empty values.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutablePostalAddress : CNPostalAddress

/*! multi-street address is delimited with carriage returns “\n” */
@property (copy, NS_NONATOMIC_IOSONLY) NSString *street;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *subLocality            NS_AVAILABLE(10_12_4, 10_3);
@property (copy, NS_NONATOMIC_IOSONLY) NSString *city;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *subAdministrativeArea  NS_AVAILABLE(10_12_4, 10_3);
@property (copy, NS_NONATOMIC_IOSONLY) NSString *state;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *postalCode;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *country;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *ISOCountryCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContainer+Predicates.h
//
//  CNContainer+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContainer.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match containers against.
 *
 * @discussion Can only use these predicates with CNContactStore.
 */
@interface CNContainer (Predicates)

+ (NSPredicate *)predicateForContainersWithIdentifiers:(NSArray<NSString*> *)identifiers;

/*! @discussion If the identifier is for a unified contact then the fetch will return an empty array. To fetch the containers of a unified contact, first fetch the linked contacts then fetch the container of each linked contact. */
+ (NSPredicate *)predicateForContainerOfContactWithIdentifier:(NSString *)contactIdentifier;

+ (NSPredicate *)predicateForContainerOfGroupWithIdentifier:(NSString *)groupIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNSocialProfile.h
//
//  CNSocialProfile.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a social profile.
 *
 * @discussion CNSocialProfile is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNSocialProfile : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *urlString;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *username;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *userIdentifier;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *service;

- (instancetype)initWithUrlString:(nullable NSString *)urlString username:(nullable NSString *)username userIdentifier:(nullable NSString *)userIdentifier service:(nullable NSString *)service;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

/*! Returns a user displayable service name. */
+ (NSString* )localizedStringForService:(NSString *)service;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNSocialProfileURLStringKey                     NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileUsernameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileUserIdentifierKey                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceKey                       NS_AVAILABLE(10_11, 9_0);

// Social profile services.
CONTACTS_EXTERN NSString * const CNSocialProfileServiceFacebook                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceFlickr                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceLinkedIn                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceMySpace                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceSinaWeibo                 NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceTencentWeibo              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceTwitter                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceYelp                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceGameCenter                NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNLabeledValue.h
//
//  CNLabeledValue.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A contact property that has a value and label.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNLabeledValue<ValueType : id <NSCopying, NSSecureCoding>> : NSObject <NSCopying, NSSecureCoding>

/*! The identifier is unique among contacts on the device. It can be saved and used for finding labeled values next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *label;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) ValueType value;

/*! Returns a new CNLabeledValue with a new identifier. */
+ (instancetype)labeledValueWithLabel:(nullable NSString *)label value:(ValueType)value;

/*! Initializes the CNLabeledValue with a new identifier. */
- (instancetype)initWithLabel:(nullable NSString *)label value:(ValueType)value;

/*! Returns a new CNLabeledValue with the existing value and identifier. */
- (instancetype)labeledValueBySettingLabel:(nullable NSString *)label;

/*! Returns a new CNLabeledValue with the existing label and identifier. */
- (instancetype)labeledValueBySettingValue:(ValueType)value;

/*! Returns a new CNLabeledValue with the existing identifier. */
- (instancetype)labeledValueBySettingLabel:(nullable NSString *)label value:(ValueType)value;

/*!
 * @abstract Get a localized label.
 *
 * @discussion Some labels are special keys representing generic labels. Use this to obtain a localized string for a label to display to a user.
 *
 * @param label to localize.
 * @return The localized string if a Contacts framework defined label, otherwise just returns the label.
 */
+ (NSString *)localizedStringForLabel:(NSString *)label;

@end


// Generic labels
CONTACTS_EXTERN NSString * const CNLabelHome                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelWork                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelOther                            NS_AVAILABLE(10_11, 9_0);

// Additional email labels
CONTACTS_EXTERN NSString * const CNLabelEmailiCloud                      NS_AVAILABLE(10_11, 9_0);

// URL address labels
CONTACTS_EXTERN NSString * const CNLabelURLAddressHomePage               NS_AVAILABLE(10_11, 9_0);

// Date labels
CONTACTS_EXTERN NSString * const CNLabelDateAnniversary                  NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNPostalAddressFormatter.h
//
//  CNPostalAddressFormatter.h
//  Contacts
//
//  Copyright (c) 2015–2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class CNPostalAddress;


/*!
 * @abstract The formatting styles for postal addresses.
 */
typedef NS_ENUM(NSInteger, CNPostalAddressFormatterStyle)
{
    /*! Combine the postal address components into a multi-line mailing address. */
    CNPostalAddressFormatterStyleMailingAddress,
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Formats a postal address.
 *
 * @discussion This formatter handles international formatting of a postal address.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPostalAddressFormatter : NSFormatter

/*!
 * @abstract Formats the postal address.
 *
 * @param postalAddress The postal address to be formatted.
 * @param style The formatting style to be used for the postal address.
 * @return The formatted postal address.
 */
+ (NSString *)stringFromPostalAddress:(CNPostalAddress *)postalAddress style:(CNPostalAddressFormatterStyle)style;


/*!
 * @abstract Formats the postal address returning an attributed string.
 *
 * @discussion This behaves like +stringFromPostalAddress: except it returns an attributed string. Includes attribute keys CNPostalAddressPropertyAttribute and CNPostalAddressLocalizedPropertyNameAttribute.
 *
 * @param postalAddress The postal address to be formatted.
 * @param style The formatting style to be used for the postal address.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted postal address as an attributed string.
 */
+ (NSAttributedString *)attributedStringFromPostalAddress:(CNPostalAddress *)postalAddress style:(CNPostalAddressFormatterStyle)style withDefaultAttributes:(NSDictionary *)attributes;

/*!
 * @abstract The style for a postal address formatter instance.
 *
 * @discussion The default value is CNPostalAddressFormatterStyleMailingAddress.
 */
@property (NS_NONATOMIC_IOSONLY) CNPostalAddressFormatterStyle style;

/*!
 * @abstract Formats the postal address.
 *
 * @param postalAddress The postal address to be formatted.
 * @return The formatted postal address.
 */
- (NSString *)stringFromPostalAddress:(CNPostalAddress *)postalAddress;

/*!
 * @abstract Formats the postal address returning an attributed string.
 *
 * @discussion This behaves like +stringFromPostalAddress: except it returns an attributed string. Includes attribute keys CNPostalAddressPropertyAttribute and CNPostalAddressLocalizedPropertyNameAttribute.
 *
 * @param postalAddress The postal address to be formatted.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted postal address as an attributed string.
 */
- (NSAttributedString *)attributedStringFromPostalAddress:(CNPostalAddress *)postalAddress withDefaultAttributes:(NSDictionary *)attributes;

@end


// Attribute key whose value is a CNPostalAddress property key.
CONTACTS_EXTERN NSString * const CNPostalAddressPropertyAttribute;

// Attribute key whose value is a localized version of the CNPostalAddress property key.
CONTACTS_EXTERN NSString * const CNPostalAddressLocalizedPropertyNameAttribute;

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNInstantMessageAddress.h
//
//  CNInstantMessageAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing an instant message address.
 *
 * @discussion CNInstantMessageAddress is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNInstantMessageAddress : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *username;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *service;

- (instancetype)initWithUsername:(NSString *)username service:(NSString *)service;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

/*! Returns a user displayable service name. */
+ (NSString *)localizedStringForService:(NSString *)service;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNInstantMessageAddressUsernameKey          NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageAddressServiceKey           NS_AVAILABLE(10_11, 9_0);

// Instant message services.
CONTACTS_EXTERN NSString * const CNInstantMessageServiceAIM                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceFacebook             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceGaduGadu             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceGoogleTalk           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceICQ                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceJabber               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceMSN                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceQQ                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceSkype                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceYahoo                NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContactsUserDefaults.h
//
//  CNContactUserDefaults.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContactFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The user defaults for contacts.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactsUserDefaults : NSObject

+ (instancetype)sharedDefaults;

@property (readonly, NS_NONATOMIC_IOSONLY) CNContactSortOrder sortOrder;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *countryCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNGroup.h
//
//  CNGroup.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a group.
 *
 * @discussion CNGroup is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNGroup : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! The identifier is unique among groups on the device. It can be saved and used for fetching groups next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNGroupIdentifierKey	NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNGroupNameKey			NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContact+NSItemProvider.h
//
//  CNContact+NSItemProvider.h
//  Contacts
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/CNContact.h>

@interface CNContact (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>

@end
// ==========  Contacts.framework/Headers/CNContactProperty.h
//
//  CNContactProperty.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact;


/*!
 * @abstract Contains related information for a specific contact property.
 *
 * @discussion CNContactProperty is used by the CNContactPicker to return the user's selected property.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactProperty : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CNContact *contact;

/*!
 * @abstract The key of the contact property, as defined in CNContact.h.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *key;

/*!
 * @abstract The value of the property.
 */
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) id value;

/*!
 * @abstract The identifier of the labeled value if the property is an array of labeled values, otherwise is nil.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

/*!
 * @abstract The label of the labeled value if the property is an array of labeled values, otherwise is nil.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *label;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNPostalAddress.h
//
//  CNPostalAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a postal address.
 *
 * @discussion CNPostalAddress is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPostalAddress : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! multi-street address is delimited with carriage returns “\n” */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *street;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *subLocality              NS_AVAILABLE(10_12_4, 10_3);
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *city;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *subAdministrativeArea    NS_AVAILABLE(10_12_4, 10_3);
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *state;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *postalCode;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *country;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *ISOCountryCode;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNPostalAddressStreetKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressSubLocalityKey                       NS_AVAILABLE(10_12_4, 10_3);
CONTACTS_EXTERN NSString * const CNPostalAddressCityKey                              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressSubAdministrativeAreaKey             NS_AVAILABLE(10_12_4, 10_3);
CONTACTS_EXTERN NSString * const CNPostalAddressStateKey                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressPostalCodeKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressCountryKey                           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressISOCountryCodeKey                    NS_AVAILABLE(10_11, 9_0);


NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNMutableGroup.h
//
//  CNMutableGroup.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNGroup.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a group.
 *
 * @discussion CNMutableGroup is not thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutableGroup : CNGroup

@property (copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContact.h
//
//  CNContact.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNLabeledValue.h>
#import <Contacts/CNPhoneNumber.h>
#import <Contacts/CNPostalAddress.h>
#import <Contacts/CNContactRelation.h>
#import <Contacts/CNSocialProfile.h>
#import <Contacts/CNInstantMessageAddress.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CNContactType)
{
    CNContactTypePerson,
    CNContactTypeOrganization,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract Sort order for contacts.
 *
 * @discussion CNContactSortOrderUserDefault is the user's preferred sort order.
 */
typedef NS_ENUM(NSInteger, CNContactSortOrder)
{
    CNContactSortOrderNone,
    CNContactSortOrderUserDefault,
    CNContactSortOrderGivenName,
    CNContactSortOrderFamilyName,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*! This protocol is reserved for Contacts framework usage. */
@protocol CNKeyDescriptor <NSObject, NSSecureCoding, NSCopying>
@end

/*! Allows contact property keys to be used with keysToFetch. */
@interface NSString (Contacts) <CNKeyDescriptor>
@end


/*!
 * @abstract An immutable value object representing a contact.
 *
 * @discussion CNContact is thread safe. 
 *
 * If using a CNContact instance where you are not certain of the keys that were fetched, use isKeyAvailable: or areKeysAvailable:. If these return NO you need to refetch the contact by the contact identifier with the keys you want to fetch. Accessing a property that was not fetched will throw CNContactPropertyNotFetchedExceptionName.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContact : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! The identifier is unique among contacts on the device. It can be saved and used for fetching contacts next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, NS_NONATOMIC_IOSONLY) CNContactType contactType;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *namePrefix;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *givenName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *middleName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *familyName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *previousFamilyName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *nameSuffix;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *nickname;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticGivenName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticMiddleName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticFamilyName;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *organizationName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *departmentName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *jobTitle;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *note;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSData *imageData;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSData *thumbnailImageData;
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL imageDataAvailable NS_AVAILABLE(NA, 9_0);

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPhoneNumber*>*>             *phoneNumbers;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                  *emailAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPostalAddress*>*>           *postalAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                  *urlAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNContactRelation*>*>         *contactRelations;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNSocialProfile*>*>           *socialProfiles;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNInstantMessageAddress*>*>   *instantMessageAddresses;

/*! The Gregorian birthday. */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *birthday;

/*! The alternate birthday (Lunisolar). */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *nonGregorianBirthday;

/*! Other Gregorian dates (anniversaries, etc). */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSDateComponents*>*> *dates;


// Key Availability

/*! Returns YES if the value for the specified key was fetched. */
- (BOOL)isKeyAvailable:(NSString *)key;

/*! Returns YES if the values for the keys specified by all the descriptors were fetched. */
- (BOOL)areKeysAvailable:(NSArray <id<CNKeyDescriptor>>*)keyDescriptors;


// Key Localization

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;


// Contact Sort Comparator

/*! The contact comparator for a given sort order. */
+ (NSComparator)comparatorForNameSortOrder:(CNContactSortOrder)sortOrder;

/*! Use to fetch all contact keys required for the contact sort comparator. */
+ (id<CNKeyDescriptor>)descriptorForAllComparatorKeys;


// Unification
/*! Returns YES if the receiver was fetched as a unified contact and includes the contact having contactIdentifier in its unification */
- (BOOL)isUnifiedWithContactWithIdentifier:(NSString*)contactIdentifier;

@end

CONTACTS_EXTERN NSString * const CNContactPropertyNotFetchedExceptionName;

// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContactIdentifierKey                      NS_AVAILABLE(10_11, 9_0);

// Optional properties that can be fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContactNamePrefixKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactGivenNameKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactMiddleNameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactFamilyNameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPreviousFamilyNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNameSuffixKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNicknameKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticGivenNameKey               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticMiddleNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticFamilyNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactOrganizationNameKey                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactDepartmentNameKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactJobTitleKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactBirthdayKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNonGregorianBirthdayKey            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNoteKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactImageDataKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactThumbnailImageDataKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactImageDataAvailableKey              NS_AVAILABLE(NA, 9_0);
CONTACTS_EXTERN NSString * const CNContactTypeKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneNumbersKey                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactEmailAddressesKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPostalAddressesKey                 NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactDatesKey                           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactUrlAddressesKey                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactRelationsKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactSocialProfilesKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactInstantMessageAddressesKey         NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/Contacts.h
//
//  Contacts.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContactStore.h>
#import <Contacts/CNContactFetchRequest.h>
#import <Contacts/CNSaveRequest.h>

#import <Contacts/CNContact.h>
#import <Contacts/CNContact+Predicates.h>
#import <Contacts/CNMutableContact.h>
#import <Contacts/CNContact+NSItemProvider.h>

#import <Contacts/CNLabeledValue.h>
#import <Contacts/CNPhoneNumber.h>
#import <Contacts/CNPostalAddress.h>
#import <Contacts/CNMutablePostalAddress.h>
#import <Contacts/CNInstantMessageAddress.h>
#import <Contacts/CNSocialProfile.h>
#import <Contacts/CNContactRelation.h>

#import <Contacts/CNGroup.h>
#import <Contacts/CNGroup+Predicates.h>
#import <Contacts/CNMutableGroup.h>

#import <Contacts/CNContainer.h>
#import <Contacts/CNContainer+Predicates.h>

#import <Contacts/CNContactFormatter.h>
#import <Contacts/CNPostalAddressFormatter.h>

#import <Contacts/CNContactVCardSerialization.h>
#import <Contacts/CNContactsUserDefaults.h>
#import <Contacts/CNContactProperty.h>
#import <Contacts/CNError.h>
// ==========  Contacts.framework/Headers/ContactsDefines.h
//
//  ContactsDefines.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define CONTACTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CONTACTS_EXTERN extern __attribute__((visibility ("default")))
#endif
// ==========  Contacts.framework/Headers/CNContactVCardSerialization.h
//
//  CNContactVCardSerialization.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNKeyDescriptor;

/*!
 * @abstract Contact vCard support.
 *
 * @discussion This converts between a contact and its vCard representation.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactVCardSerialization : NSObject

/*!
 *  @abstract Descriptor for all contact keys required by vCard serialization
 *
 *  @discussion This descriptor must be passed to the fetch request if the returned
 *              contacts are to be serialized with dataWithContacts:error:.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

+ (nullable NSData *)dataWithContacts:(NSArray *)contacts error:(NSError *__nullable *__nullable)error;
+ (nullable NSArray *)contactsWithData:(NSData *)data error:(NSError *__nullable *__nullable)error;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNError.h
//
//  CNError.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

CONTACTS_EXTERN NSString * const CNErrorDomain NS_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSInteger, CNErrorCode)
{
    CNErrorCodeCommunicationError = 1,
    CNErrorCodeDataAccessError = 2,
    
    CNErrorCodeAuthorizationDenied = 100,
    
    CNErrorCodeRecordDoesNotExist = 200,
    CNErrorCodeInsertedRecordAlreadyExists = 201,
    CNErrorCodeContainmentCycle = 202,
    CNErrorCodeContainmentScope = 203,
    CNErrorCodeParentRecordDoesNotExist = 204,
    
    CNErrorCodeValidationMultipleErrors = 300,
    CNErrorCodeValidationTypeMismatch = 301,
    CNErrorCodeValidationConfigurationError = 302,

    CNErrorCodePredicateInvalid = 400,
    
    CNErrorCodePolicyViolation = 500,
    
    CNErrorCodeClientIdentifierInvalid = 600,
    CNErrorCodeClientIdentifierDoesNotExist = 601,
    
    CNErrorCodeVCardMalformed NS_ENUM_AVAILABLE(10_13, 11_0) = 700,
    
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*! When available an array of one or more CNContact, CNGroup or CNContainer objects for which the error code applies. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoAffectedRecordsKey NS_AVAILABLE(10_11, 9_0);

/*! When available an array of one or more NSString objects for which the error code applies. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoAffectedRecordIdentifiersKey NS_AVAILABLE(10_11, 9_0);

/*! An array of NSErrors for CNErrorCodeValidationMultipleErrors. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoValidationErrorsKey NS_AVAILABLE(10_11, 9_0);

/*! An array of key paths associated with a given error. For validation errors this will contain key paths to specific object properties. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoKeyPathsKey NS_AVAILABLE(10_11, 9_0);
// ==========  Contacts.framework/Headers/CNContactFetchRequest.h
//
//  CNContactFetchRequest.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract Specifies the search criteria to fetch contacts.
 *
 * @discussion Used with [CNContactStore enumerateContactsWithFetchRequest:error:usingBlock:]. Can combine any of these options to create a contact fetch request.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactFetchRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

/*!
 *  @param      keysToFetch
 *              The properties to fetch for the returned contacts.
 *
 *  @discussion Only fetch the properties that will be used.
 */
- (instancetype)initWithKeysToFetch:(NSArray <id<CNKeyDescriptor>>*)keysToFetch NS_DESIGNATED_INITIALIZER;

/*!
 * @abstract The predicate to match contacts against.
 *
 * @discussion Use only predicates from CNContact+Predicates.h. Compound predicates are not supported. Set to nil to match all contacts.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSPredicate *predicate;

/*!
 * @abstract The properties to fetch in the returned contacts.
 *
 * @discussion Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<id<CNKeyDescriptor>> *keysToFetch;

/*!
 * @abstract To return mutable contacts.
 *
 * @discussion If YES returns CNMutableContact objects, otherwise returns CNContact objects. Default is NO.
 */
@property (NS_NONATOMIC_IOSONLY) BOOL mutableObjects;

/*!
 * @abstract To return linked contacts as unified contacts.
 *
 * @discussion If YES returns unified contacts, otherwise returns individual contacts. Default is YES.
 *
 * @note A unified contact is the aggregation of properties from a set of linked individual contacts. If an individual contact is not linked then the unified contact is simply that individual contact.
 */
@property (NS_NONATOMIC_IOSONLY) BOOL unifyResults;

/*!
 * @abstract To return contacts in a specific sort order.
 *
 * @discussion Default is CNContactSortOrderNone.
 */
@property (NS_NONATOMIC_IOSONLY) CNContactSortOrder sortOrder;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNMutableContact.h
//
//  CNMutableContact.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a contact.
 *
 * @discussion CNMutableContact is not thread safe. If this is a mutable copy of CNContact then it will throw CNContactPropertyNotFetchedExceptionName when accessing a property that was not fetched for the CNContact.
 *
 * @note To remove properties when saving a mutable contact, set string properties and array properties to empty values. Set other properties to nil.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutableContact : CNContact

@property (NS_NONATOMIC_IOSONLY) CNContactType contactType;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *namePrefix;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *givenName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *middleName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *familyName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *previousFamilyName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *nameSuffix;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *nickname;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticGivenName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticMiddleName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticFamilyName;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *organizationName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *departmentName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *jobTitle;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *note;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSData *imageData;

@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPhoneNumber*>*>               *phoneNumbers;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                    *emailAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPostalAddress*>*>             *postalAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                    *urlAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNContactRelation*>*>           *contactRelations;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNSocialProfile*>*>             *socialProfiles;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNInstantMessageAddress*>*>     *instantMessageAddresses;

/*! @abstract The Gregorian birthday.
 *
 *  @description Only uses day, month and year components. Needs to have at least a day and a month.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *birthday;

/*! @abstract The alternate birthday (Lunisolar).
 *
 *  @description Only uses day, month, year and calendar components. Needs to have at least a day and a month. Calendar must be Chinese, Hebrew or Islamic.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *nonGregorianBirthday;

/*! @abstract Other Gregorian dates (anniversaries, etc).
 *
 *  @description Only uses day, month and year components. Needs to have at least a day and a month.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSDateComponents*>*> *dates;

@end

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNContainer.h
//
//  CNContainer.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CNContainerType)
{
    CNContainerTypeUnassigned = 0,
    CNContainerTypeLocal,
    CNContainerTypeExchange,
    CNContainerTypeCardDAV
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract An immutable value object representing a container.
 *
 * @discussion CNContainer is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContainer : NSObject <NSCopying, NSSecureCoding>

/*! The identifier is unique among containers on the device. It can be saved and used for fetching containers next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;
@property (readonly, NS_NONATOMIC_IOSONLY) CNContainerType type;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContainerIdentifierKey	NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContainerNameKey			NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContainerTypeKey			NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Contacts.framework/Headers/CNSaveRequest.h
//
//  CNSaveRequest.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact, CNMutableContact, CNGroup, CNMutableGroup;


/*!
 * @abstract Specifies the changes to save.
 *
 * @discussion Create a new save request for each save execution on the contact store. Can have many changes batched into one save request. Do not access objects in the save request when it is executing.  A save request only applies the changes to the objects. If there are overlapping changes with multiple, concurrent CNSaveRequests then the last saved change wins.
 *
 * If adding an object (contact, group, container) and it is already in the contact store then the executing save request will fail to add that object and will return the error CNErrorCodeInsertedRecordAlreadyExists with CNErrorUserInfoAffectedRecordsKey value as an array containing that object.
 *
 * If updating/deleting an object (contact, group, container) and it is not in the contact store then the executing save request will fail to update/delete that object and will return the error CNErrorCodeRecordDoesNotExist with CNErrorUserInfoAffectedRecordsKey value as an array containing that object.
 *
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
__WATCHOS_PROHIBITED
@interface CNSaveRequest : NSObject

/*!
 * @abstract Add a new contact to the contact store.
 *
 * @discussion The contact may be modified by the executing save request. If the contact was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param contact The new contact to add.
 * @param identifier The container identifier to add the new contact to. Set to nil for the default container.
 */
- (void)addContact:(CNMutableContact *)contact toContainerWithIdentifier:(nullable NSString *)identifier;

/*!
 * @abstract Update an existing contact in the contact store.
 *
 * @discussion The contact must already exist in the contact store. The contact may be modified by the executing save request.
 */
- (void)updateContact:(CNMutableContact *)contact;

/*!
 * @abstract Delete a contact from the contact store.
 *
 * @discussion If the contact was previously specified to be added in the save request that will no longer occur.
 */
- (void)deleteContact:(CNMutableContact *)contact;

/*!
 * @abstract Add a new group to the contact store.
 *
 * @discussion If the group was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param group The new group to add.
 * @param identifier The container identifier to add the new group to. Set to nil for the default container.
 */
- (void)addGroup:(CNMutableGroup *)group toContainerWithIdentifier:(nullable NSString *)identifier;

/*!
 * @abstract Update an existing group in the contact store.
 *
 * @discussion The group must already exist in the contact store.
 */
- (void)updateGroup:(CNMutableGroup *)group;

/*!
 * @abstract Delete a group from the contact store.
 *
 * @discussion The contacts in the group are not deleted. If the group was previously specified to be added in the save request that will no longer occur.
 */
- (void)deleteGroup:(CNMutableGroup *)group;

/*!
 * @abstract Add a new subgroup to a group.
 *
 * @discussion If the subgroup was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param subgroup The new group to add.
 * @param group The group to add the subgroup to.
 */
- (void)addSubgroup:(CNGroup *)subgroup toGroup:(CNGroup *)group NS_AVAILABLE(10_11, NA);

/*!
 * @abstract Remove a subgroup from a group.
 *
 * @discussion The contacts in the subgroup's membership are not affected. If the subgroup was previously specified to be added in the save request that will no longer occur.
 *
 * @param subgroup The new group to add.
 * @param group The group to add the subgroup to.
 */
- (void)removeSubgroup:(CNGroup *)subgroup fromGroup:(CNGroup *)group NS_AVAILABLE(10_11, NA);

/*!
 * @abstract Add a new member to a group.
 *
 * @discussion If the membership was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param contact The new member to add to the group.
 * @param group The group to add the member to.
 */
- (void)addMember:(CNContact *)contact toGroup:(CNGroup *)group;

/*!
 * @abstract Remove a member from a group.
 *
 * @discussion The contact is not deleted. It is only removed as a member of the group. If the membership was previously specified to be added in the save request that will no longer occur.
 *
 * @param contact The member to remove from the group.
 * @param group The group to remove the member from.
 */
- (void)removeMember:(CNContact *)contact fromGroup:(CNGroup *)group;

@end

NS_ASSUME_NONNULL_END
