// ==========  CoreData.framework/Headers/NSPersistentHistoryTransaction.h
/*
    NSPersistentHistoryTransaction.h
    Core Data
    Copyright (c) 2016-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

@class NSNotification;
@class NSPersistentHistoryToken;
@class NSPersistentHistoryChange;
@class NSEntityDescription;
@class NSFetchRequest;
@class NSManagedObjectConext;

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryTransaction : NSObject <NSCopying>

+ (nullable NSEntityDescription *)entityDescriptionWithContext:(NSManagedObjectContext *)context API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@property (class,nullable,readonly) NSEntityDescription *entityDescription API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));
@property (class,nullable,readonly) NSFetchRequest *fetchRequest API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@property (readonly,copy) NSDate *timestamp;
@property (nullable,readonly,copy) NSArray<NSPersistentHistoryChange *>*changes;
@property (readonly) int64_t transactionNumber;
@property (readonly,copy) NSString *storeID;
@property (readonly,copy) NSString *bundleID;
@property (readonly,copy) NSString *processID;
@property (nullable,readonly,copy) NSString *contextName;
@property (nullable,readonly,copy) NSString *author;
@property (readonly,strong) NSPersistentHistoryToken *token;

// Get a notification that can be consumed by a NSManagedObjectContext
- (NSNotification *) objectIDNotification;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSFetchIndexDescription.h
/*
    NSFetchIndexDescription.h
    Core Data
    Copyright (c) 2017-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSPredicate.h>
#import <Foundation/NSString.h>

@class NSEntityDescription;
@class NSFetchIndexElementDescription;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSFetchIndexDescription : NSObject <NSCoding> {
}

- (instancetype)initWithName:(NSString*)name elements:(nullable NSArray <NSFetchIndexElementDescription *>*)elements;

@property (copy) NSString *name;
/* Will throw if the new value is invalid (ie includes both rtree and non-rtree elements). */
@property (copy) NSArray <NSFetchIndexElementDescription *>*elements;
@property (readonly, nonatomic, nullable, assign) NSEntityDescription *entity;

/* If the index should be a partial index, specifies the predicate selecting rows for indexing */
@property (nullable, copy) NSPredicate *partialIndexPredicate;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/CoreDataDefines.h
/*
    CoreDataDefines.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#ifndef _COREDATADEFINES_H
#define _COREDATADEFINES_H

#import <AvailabilityMacros.h>
#import <Availability.h>
#import <TargetConditionals.h>

//
//  Platform specific defs for externs
//

//
// For MACH
//

#if defined(__MACH__)

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C"
#define COREDATA_PRIVATE_EXTERN	__attribute__((visibility("hidden"))) extern "C"
#else
#define COREDATA_EXTERN		extern
#define COREDATA_PRIVATE_EXTERN	__attribute__((visibility("hidden"))) extern
#endif

//
// For Windows
//

#elif defined(WIN32)

#ifndef _NSBUILDING_COREDATA_DLL
#define _NSWINDOWS_DLL_GOOP	__declspec(dllimport)
#else
#define _NSWINDOWS_DLL_GOOP	__declspec(dllexport)
#endif

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C" _NSWINDOWS_DLL_GOOP
#define COREDATA_PRIVATE_EXTERN	extern
#else
#define COREDATA_EXTERN		_NSWINDOWS_DLL_GOOP extern
#define COREDATA_PRIVATE_EXTERN	extern
#endif

//
//  For Solaris
//

#elif defined(SOLARIS)

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C"
#define COREDATA_PRIVATE_EXTERN	extern "C"
#else
#define COREDATA_EXTERN		extern
#define COREDATA_PRIVATE_EXTERN	extern
#endif

#endif

//
//  Framework version
//

COREDATA_EXTERN double NSCoreDataVersionNumber;

#define NSCoreDataVersionNumber10_4       46.0
#define NSCoreDataVersionNumber10_4_3     77.0
#define NSCoreDataVersionNumber10_5       185.0
#define NSCoreDataVersionNumber10_5_3     186.0
#define NSCoreDataVersionNumber10_6		  246.0
#define NSCoreDataVersionNumber10_6_2	  250.0
#define NSCoreDataVersionNumber10_6_3	  251.0
#define NSCoreDataVersionNumber10_7       358.4
#define NSCoreDataVersionNumber10_7_2     358.12
#define NSCoreDataVersionNumber10_7_3     358.13
#define NSCoreDataVersionNumber10_7_4     358.14
#define NSCoreDataVersionNumber10_8       407.5
#define NSCoreDataVersionNumber10_8_2     407.7
#define NSCoreDataVersionNumber10_9       481.0
#define NSCoreDataVersionNumber10_9_2     481.1
#define NSCoreDataVersionNumber10_9_3     481.3
#define NSCoreDataVersionNumber10_10      526.0
#define NSCoreDataVersionNumber10_10_2    526.1
#define NSCoreDataVersionNumber10_10_3    526.2
#define NSCoreDataVersionNumber10_11      640.0
#define NSCoreDataVersionNumber10_11_3    641.3

#define NSCoreDataVersionNumber_iPhoneOS_3_0		241.0
#define NSCoreDataVersionNumber_iPhoneOS_3_1		248.0
#define NSCoreDataVersionNumber_iPhoneOS_3_2		310.2
#define NSCoreDataVersionNumber_iPhoneOS_4_0		320.5
#define NSCoreDataVersionNumber_iPhoneOS_4_1		320.11
#define NSCoreDataVersionNumber_iPhoneOS_4_2		320.15
#define NSCoreDataVersionNumber_iPhoneOS_4_3		320.17
#define NSCoreDataVersionNumber_iPhoneOS_5_0		386.1
#define NSCoreDataVersionNumber_iPhoneOS_5_1		386.5
#define NSCoreDataVersionNumber_iPhoneOS_6_0		419.0
#define NSCoreDataVersionNumber_iPhoneOS_6_1		419.1
#define NSCoreDataVersionNumber_iPhoneOS_7_0		479.1
#define NSCoreDataVersionNumber_iPhoneOS_7_1		479.3
#define NSCoreDataVersionNumber_iPhoneOS_8_0		519.0
#define NSCoreDataVersionNumber_iPhoneOS_8_3		519.15
#define NSCoreDataVersionNumber_iPhoneOS_9_0		640.0
#define NSCoreDataVersionNumber_iPhoneOS_9_2		641.4
#define NSCoreDataVersionNumber_iPhoneOS_9_3		641.6

#endif // _COREDATADEFINES_H
// ==========  CoreData.framework/Headers/NSEntityMigrationPolicy.h
/*
    NSEntityMigrationPolicy.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSError.h>

#import <CoreData/CoreDataDefines.h>

NS_ASSUME_NONNULL_BEGIN

/* To access the entity migration policy keys in property mapping value expressions implemented in source code use the constants as declared.  To access them in custom value expression strings in the mapping model editor in Xcode follow the syntax rules outlined in the predicate format string syntax guide and refer to them as:
 NSMigrationManagerKey           $manager
 NSMigrationSourceObjectKey      $source
 NSMigrationDestinationObjectKey $destination
 NSMigrationEntityMappingKey     $entityMapping
 NSMigrationPropertyMappingKey   $propertyMapping
 NSMigrationEntityPolicyKey      $entityPolicy
*/
COREDATA_EXTERN NSString * const NSMigrationManagerKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSMigrationSourceObjectKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSMigrationDestinationObjectKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSMigrationEntityMappingKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSMigrationPropertyMappingKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSMigrationEntityPolicyKey API_AVAILABLE(macosx(10.5),ios(3.0));

@class NSManagedObject;
@class NSEntityMapping;
@class NSMigrationManager;
@class NSError;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSEntityMigrationPolicy : NSObject


/* Invoked by the migration manager at the start of a given entity mapping.  This is also the precursor to the creation step.
*/
- (BOOL)beginEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked by the migration manager on each source instance (as specified by the sourceExpression in the mapping) to create the corresponding destination instance.  The method also associates the source and destination instances by calling NSMigrationManager's
associateSourceInstance:withDestinationInstance:forEntityMapping: method.  Subclass implementations of this method must be careful to 
associate the source and destination instances as required if super is not called. A return value of NO indicates an error.
*/
- (BOOL)createDestinationInstancesForSourceInstance:(NSManagedObject *)sInstance entityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Indicates the end of the creation step for the specified entity mapping, and the precursor to the next migration step.  Developers can override this method to set up or clean up information for further migration steps.
*/
- (BOOL)endInstanceCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Constructs the relationships between the newly-created destination instances.  The association lookup methods on the NSMigrationManager can be used to determine the appropriate relationship targets.  A return value of NO indicates an error.
*/
- (BOOL)createRelationshipsForDestinationInstance:(NSManagedObject *)dInstance entityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;

 
/* Indicates the end of the relationship creation step for the specified entity mapping.  This method is invoked after the createRelationshipsForDestinationInstance:entityMapping:manager:error: method, and can be used to clean up state from the creation of relationships, or prepare state for the performance of custom validation.
*/
- (BOOL)endRelationshipCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked during the validation step of the entity migration policy, providing the option of performing custom validation on migrated objects.  (Implementors must manually obtain the collection of objects they are interested in validating.) 
*/
- (BOOL)performCustomValidationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked by the migration manager at the end of a given entity mapping.  This is also the end to the validation step, which is the last step for migration.
*/
- (BOOL)endEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSExpressionDescription.h
/*
    NSExpressionDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>
#import <CoreData/NSAttributeDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class NSExpression;

/* Special property description type intended for use with the NSFetchRequest -propertiesToFetch method.
   An NSExpressionDescription describes a column to be returned from a fetch that may not appear 
   directly as an attribute or relationship on an entity. Examples would be: upper(attribute) or
   max(attribute). NSExpressionDescriptions cannot be set as properties on NSEntityDescription. */
API_AVAILABLE(macosx(10.6),ios(3.0))
@interface NSExpressionDescription : NSPropertyDescription {
}

@property (nullable, strong) NSExpression *expression;

@property () NSAttributeType expressionResultType;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSFetchIndexElementDescription.h
/*
    NSFetchIndexElementDescription.h
    Core Data
    Copyright (c) 2017-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

@class NSPropertyDescription;
@class NSFetchIndexDescription;


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSFetchIndexElementType) {
    NSFetchIndexElementTypeBinary,
    NSFetchIndexElementTypeRTree,
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSFetchIndexElementDescription : NSObject <NSCoding> {
}

- (instancetype)initWithProperty:(NSPropertyDescription*)property collationType:(NSFetchIndexElementType)collationType;

/* This may be an NSExpressionDescription that expresses a function */
@property (readonly, nullable, retain) NSPropertyDescription *property;
@property (readonly, nullable, retain) NSString *propertyName;
/* Default NSIndexTypeBinary */
@property NSFetchIndexElementType collationType;
/* Default YES. Control whether this is an ascending or descending index for indexes which support direction. */

@property (getter=isAscending) BOOL ascending;

@property (readonly, nonatomic, nullable, assign) NSFetchIndexDescription *indexDescription;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSAttributeDescription.h
/*
    NSAttributeDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSPropertyDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;

// types explicitly distinguish between bit sizes to ensure data store independence of the underlying operating system


typedef NS_ENUM(NSUInteger, NSAttributeType) {
    NSUndefinedAttributeType = 0,
    NSInteger16AttributeType = 100,
    NSInteger32AttributeType = 200,
    NSInteger64AttributeType = 300,
    NSDecimalAttributeType = 400,
    NSDoubleAttributeType = 500,
    NSFloatAttributeType = 600,
    NSStringAttributeType = 700,
    NSBooleanAttributeType = 800,
    NSDateAttributeType = 900,
    NSBinaryDataAttributeType = 1000,
    NSUUIDAttributeType API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1100,
    NSURIAttributeType API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1200,
    NSTransformableAttributeType API_AVAILABLE(macosx(10.5), ios(3.0)) = 1800, // If your attribute is of NSTransformableAttributeType, the attributeValueClassName must be set or attribute value class must implement NSCopying.
    NSObjectIDAttributeType API_AVAILABLE(macosx(10.6), ios(3.0)) = 2000
 };

// Attributes represent individual values like strings, numbers, dates, etc.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSAttributeDescription : NSPropertyDescription {
}

// NSUndefinedAttributeType is valid for transient properties - Core Data will still track the property as an id value and register undo/redo actions, etc. NSUndefinedAttributeType is illegal for non-transient properties.
@property () NSAttributeType attributeType;

@property (nullable, copy) NSString *attributeValueClassName;

@property (nullable, retain) id defaultValue;   // value is retained and not copied

/* Returns the version hash for the attribute.  This value includes the versionHash information from the NSPropertyDescription superclass, and the attribute type.*/
@property (readonly, copy) NSData *versionHash API_AVAILABLE(macosx(10.5),ios(3.0));

/* The name of the transformer used to convert a NSTransformedAttributeType.  The transformer must output NSData from transformValue and allow reverse transformation.  If this value is not set, or set to nil, Core Data will default to using a transformer which uses NSCoding to archive/unarchive the attribute value.*/
@property (nullable, copy) NSString *valueTransformerName API_AVAILABLE(macosx(10.5),ios(3.0));

@property () BOOL allowsExternalBinaryDataStorage API_AVAILABLE(macosx(10.7),ios(5.0));

/* Indicates if the value of the attribute should be captured on delete when Persistent History is enabled */
@property () BOOL preservesValueInHistoryOnDeletion API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentHistoryToken.h
/*
    NSPersistentHistoryToken.h
    Core Data
    Copyright (c) 2017-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryToken : NSObject <NSCopying, NSSecureCoding>
@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSPersistentHistoryChangeRequest.h
/*
    NSPersistentHistoryChangeRequest.h
    Core Data
    Copyright (c) 2014-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentHistoryTransaction;
@class NSPersistentHistoryToken;

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryChangeRequest : NSPersistentStoreRequest {
}

+ (nonnull instancetype)fetchHistoryAfterDate:(NSDate *)date;
+ (nonnull instancetype)fetchHistoryAfterToken:(nullable NSPersistentHistoryToken *)token;
+ (nonnull instancetype)fetchHistoryAfterTransaction:(nullable NSPersistentHistoryTransaction *)transaction;
+ (nonnull instancetype)fetchHistoryWithFetchRequest:(NSFetchRequest *)fetchRequest API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

+ (nonnull instancetype)deleteHistoryBeforeDate:(NSDate *)date;
+ (nonnull instancetype)deleteHistoryBeforeToken:(nullable NSPersistentHistoryToken *)token;
+ (nonnull instancetype)deleteHistoryBeforeTransaction:(nullable NSPersistentHistoryTransaction *)transaction;

// The type of result that should be returned from this request. Defaults to NSPersistentHistoryResultTypeTransactionsAndChanges
@property NSPersistentHistoryResultType resultType;
@property (nullable,readonly,strong) NSPersistentHistoryToken *token;
@property (nullable,nonatomic,strong) NSFetchRequest *fetchRequest API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPropertyDescription.h
/*
    NSPropertyDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSData;
@class NSPredicate;

// Properties describe values within a managed object. There are different types of properties, each of them represented by a subclass which encapsulates the specific property behavior.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSPropertyDescription : NSObject <NSCoding, NSCopying> {
}

@property (nonatomic, readonly, assign) NSEntityDescription *entity;

@property (nonatomic, copy) NSString *name;

// The optional flag specifies whether a property's value can be nil or not (before an object can be persisted).
@property (getter=isOptional) BOOL optional;

// The transient flag specifies whether a property's value is persisted or ignored when an object is persisted - transient properties are still managed for undo/redo, validation, etc.
@property (getter=isTransient) BOOL transient;

// Instead of individual methods to set/get parameters like length, min and max values, formats, etc., there is a list of predicates evaluated against the managed objects and corresponding error messages (which can be localized).
@property (readonly, strong) NSArray<NSPredicate *> *validationPredicates;
@property (readonly, strong) NSArray *validationWarnings;
- (void)setValidationPredicates:(nullable NSArray<NSPredicate *> *)validationPredicates withValidationWarnings:(nullable NSArray<NSString *> *)validationWarnings;

@property (nullable, nonatomic, strong) NSDictionary *userInfo;

/* Returns a boolean value indicating if the property is important for searching.  NSPersistentStores can optionally utilize this information upon store creation for operations like defining indexes.
*/
@property (getter=isIndexed) BOOL indexed API_DEPRECATED( "Use NSEntityDescription.indexes instead", macosx(10.5,10.13),ios(3.0,11.0),tvos(9.0, 11.0),watchos(2.0, 4.0));

/* Returns the version hash for the property.  The version hash is used to uniquely identify a property based on its configuration.  The version hash uses only values which affect the persistence of data and the user-defined versionHashModifier value.  (The values which affect persistence are the name of the property, the flags for isOptional, isTransient, and isReadOnly).  This value is stored as part of the version information in the metadata for stores, as well as a definition of a property involved in an NSPropertyMapping.
*/
@property (readonly, copy) NSData *versionHash API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns/sets the version hash modifier for the property.  This value is included in the version hash for the property, allowing developers to mark/denote a property as being a different "version" than another, even if all of the values which affects persistence are equal.  (Such a difference is important in cases where the design of a property is unchanged, but the format or content of data has changed.)
*/
@property (nullable, copy) NSString *versionHashModifier API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns a boolean value indicating if the property should be indexed by Spotlight.
*/
@property (getter=isIndexedBySpotlight) BOOL indexedBySpotlight API_AVAILABLE(macosx(10.6),ios(3.0));

/* Returns a boolean value indicating if the property data should be written out to the external record file.
*/
@property (getter=isStoredInExternalRecord) BOOL storedInExternalRecord API_DEPRECATED("Spotlight integration is deprecated. Use CoreSpotlight integration instead.", macosx(10.6,10.13),ios(3.0,11.0));

@property (nullable, copy) NSString *renamingIdentifier API_AVAILABLE(macosx(10.6),ios(3.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSFetchRequest.h
/*
    NSFetchRequest.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSManagedObject.h>
#import <CoreData/NSManagedObjectID.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSManagedObjectModel;
@class NSPredicate;
@class NSPersistentStore;
@class NSSortDescriptor;

/* Definition of the possible result types a fetch request can return. */

typedef NS_OPTIONS(NSUInteger, NSFetchRequestResultType) {
    NSManagedObjectResultType		= 0x00,
    NSManagedObjectIDResultType		= 0x01,
    NSDictionaryResultType          API_AVAILABLE(macosx(10.6), ios(3.0)) = 0x02,
    NSCountResultType				API_AVAILABLE(macosx(10.6), ios(3.0)) = 0x04
};

/* Protocol conformance for possible result types a fetch request can return. */
@protocol NSFetchRequestResult <NSObject>
@end

@interface NSNumber (NSFetchedResultSupport) <NSFetchRequestResult>
@end

@interface NSDictionary (NSFetchedResultSupport) <NSFetchRequestResult>
@end

@interface NSManagedObject (NSFetchedResultSupport) <NSFetchRequestResult>
@end

@interface NSManagedObjectID (NSFetchedResultSupport) <NSFetchRequestResult>
@end

API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSFetchRequest<__covariant ResultType:id<NSFetchRequestResult>> : NSPersistentStoreRequest <NSCoding> {
}

+ (instancetype)fetchRequestWithEntityName:(NSString*)entityName API_AVAILABLE(macosx(10.7),ios(4.0));

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEntityName:(NSString*)entityName API_AVAILABLE(macosx(10.7),ios(4.0));

// Executes the fetch request using the current managed object context. This method must be called from within a block submitted to a managed object context.
- (nullable NSArray<ResultType> *)execute:(NSError **)error  API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

@property (nullable, nonatomic, strong) NSEntityDescription *entity;
@property (nullable, nonatomic, readonly, strong) NSString *entityName API_AVAILABLE(macosx(10.7),ios(4.0));

@property (nullable, nonatomic, strong) NSPredicate *predicate;

@property (nullable, nonatomic, strong) NSArray<NSSortDescriptor *> *sortDescriptors;

@property (nonatomic) NSUInteger fetchLimit;

@property (nullable, nonatomic, strong) NSArray<NSPersistentStore *> *affectedStores;

/* Returns/sets the result type of the fetch request (the instance type of objects returned from executing the request.)  Setting the value to NSManagedObjectIDResultType will demote any sort orderings to "best effort" hints if property values are not included in the request.  Defaults to NSManagedObjectResultType.   
*/
@property (nonatomic) NSFetchRequestResultType resultType API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns/sets if the fetch request includes subentities.  If set to NO, the request will fetch objects of exactly the entity type of the request;  if set to YES, the request will include all subentities of the entity for the request.  Defaults to YES. 
*/
@property (nonatomic) BOOL includesSubentities API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns/sets if, when the fetch is executed, property data is obtained from the persistent store.  If the value is set to NO, the request will not obtain property information, but only information to identify each object (used to create NSManagedObjectIDs.)  If managed objects for these IDs are later faulted (as a result attempting to access property values), they will incur subsequent access to the persistent store to obtain their property values.  Defaults to YES. 
*/
@property (nonatomic) BOOL includesPropertyValues API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns/sets if the objects resulting from a fetch request are faults.  If the value is set to NO, the returned objects are pre-populated with their property values (making them fully-faulted objects, which will immediately return NO if sent the -isFault message.)  If the value is set to YES, the returned objects are not pre-populated (and will receive a -didFireFault message when the properties are accessed the first time.)  This setting is not utilized if the result type of the request is NSManagedObjectIDResultType, as object IDs do not have property values.  Defaults to YES. 
*/
@property (nonatomic) BOOL returnsObjectsAsFaults API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns/sets an array of relationship keypaths to prefetch along with the entity for the request.  The array contains keypath strings in NSKeyValueCoding notation, as you would normally use with valueForKeyPath.  (Prefetching allows Core Data to obtain developer-specified related objects in a single fetch (per entity), rather than incurring subsequent access to the store for each individual record as their faults are tripped.)  Defaults to an empty array (no prefetching.) 
*/
@property (nullable, nonatomic, copy) NSArray<NSString *> *relationshipKeyPathsForPrefetching API_AVAILABLE(macosx(10.5),ios(3.0));


/* Results accommodate the currently unsaved changes in the NSManagedObjectContext.  When disabled, the fetch request skips checking unsaved changes and only returns objects that matched the predicate in the persistent store.  Defaults to YES.
*/
@property (nonatomic) BOOL includesPendingChanges API_AVAILABLE(macosx(10.6),ios(3.0));

/* Returns/sets if the fetch request returns only distinct values for the fields specified by propertiesToFetch. This value is only used for NSDictionaryResultType. Defaults to NO. */
@property (nonatomic) BOOL returnsDistinctResults API_AVAILABLE(macosx(10.6),ios(3.0));

/* Specifies a collection of either NSPropertyDescriptions or NSString property names that should be fetched. The collection may represent attributes, to-one relationships, or NSExpressionDescription.  If NSDictionaryResultType is set, the results of the fetch will be dictionaries containing key/value pairs where the key is the name of the specified property description.  If NSManagedObjectResultType is set, then NSExpressionDescription cannot be used, and the results are managed object faults partially pre-populated with the named properties */
@property (nullable, nonatomic, copy) NSArray *propertiesToFetch API_AVAILABLE(macosx(10.6),ios(3.0));

/* Allows you to specify an offset at which rows will begin being returned.  Effectively, the request will skip over 'offset' number of matching entries.  For example, given a fetch which would normally return a, b, c, and d, specifying an offset of 1 will return b, c, and d and an offset of 4  will return an empty array. Offsets are ignored in nested requests such as subqueries.  Default value is 0.  */
@property (nonatomic) NSUInteger fetchOffset API_AVAILABLE(macosx(10.6),ios(3.0));

/* This breaks the result set into batches.  The entire request will be evaluated, and the identities of all matching objects will be recorded, but no more than batchSize objects' data will be fetched from the persistent store at a time.  The array returned from executing the request will be a subclass that transparently faults batches on demand.  For purposes of thread safety, the returned array proxy is owned by the NSManagedObjectContext the request is executed against, and should be treated as if it were a managed object registered with that context.  A batch size of 0 is treated as infinite, which disables the batch faulting behavior.  The default is 0. */

@property (nonatomic) NSUInteger fetchBatchSize API_AVAILABLE(macosx(10.6),ios(3.0));

@property (nonatomic) BOOL shouldRefreshRefetchedObjects API_AVAILABLE(macosx(10.7),ios(5.0));

/* Specifies the way in which data should be grouped before a select statement is run in an SQL database.
 Values passed to propertiesToGroupBy must be NSPropertyDescriptions, NSExpressionDescriptions, or keypath strings; keypaths can not contain 
 any to-many steps. 
 If GROUP BY is used, then you must set the resultsType to NSDictionaryResultsType, and the SELECT values must be literals, aggregates, 
 or columns specified in the GROUP BY. Aggregates will operate on the groups specified in the GROUP BY rather than the whole table. */
@property (nullable, nonatomic, copy) NSArray *propertiesToGroupBy API_AVAILABLE(macosx(10.7),ios(5.0));

/* Specifies a predicate that will be used to filter rows being returned by a query containing a GROUP BY. If a having predicate is
 supplied, it will be run after the GROUP BY.  Specifying a HAVING predicate requires that a GROUP BY also be specified. */
@property (nullable, nonatomic, strong) NSPredicate *havingPredicate API_AVAILABLE(macosx(10.7),ios(5.0));

@end


@class NSAsynchronousFetchResult<ResultType:id<NSFetchRequestResult>>;

typedef void (^NSPersistentStoreAsynchronousFetchResultCompletionBlock)(NSAsynchronousFetchResult *result);

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSAsynchronousFetchRequest<ResultType:id<NSFetchRequestResult>> : NSPersistentStoreRequest {
}
@property (strong, readonly) NSFetchRequest<ResultType> * fetchRequest;
@property (nullable, strong, readonly) NSPersistentStoreAsynchronousFetchResultCompletionBlock completionBlock;
@property (nonatomic) NSInteger estimatedResultCount;

- (instancetype)initWithFetchRequest:(NSFetchRequest<ResultType> *)request completionBlock:(nullable void(^)(NSAsynchronousFetchResult<ResultType> *))blk;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSRelationshipDescription.h
/*
    NSRelationshipDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;

typedef NS_ENUM(NSUInteger, NSDeleteRule) {
    NSNoActionDeleteRule,
    NSNullifyDeleteRule,
    NSCascadeDeleteRule,
    NSDenyDeleteRule
} ;

// Relationships represent references to other objects. They usually come in pairs, where the reference back is called the "inverse".
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSRelationshipDescription : NSPropertyDescription {
}

@property (nullable, nonatomic, assign) NSEntityDescription *destinationEntity;
@property (nullable, nonatomic, assign) NSRelationshipDescription *inverseRelationship;

// Min and max count indicate the number of objects referenced (1/1 for a to-one relationship, 0 for the max count means undefined) - note that the counts are only enforced if the relationship value is not nil/"empty" (so as long as the relationship value is optional, there might be zero objects in the relationship, which might be less than the min count)
@property () NSUInteger maxCount;
@property () NSUInteger minCount;

@property () NSDeleteRule deleteRule;

@property (getter=isToMany, readonly) BOOL toMany;    // convenience method to test whether the relationship is to-one or to-many

// Returns the version hash for the relationship.  This value includes the versionHash information from the NSPropertyDescription superclass, the name of the destination entity and the inverse relationship, and the min and max count.
@property (readonly, copy) NSData *versionHash API_AVAILABLE(macosx(10.5),ios(3.0));

@property (getter=isOrdered) BOOL ordered API_AVAILABLE(macosx(10.7),ios(5.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSIncrementalStore.h
/*
    NSIncrementalStore.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSPersistentStore.h>
#import <CoreData/NSPersistentStoreRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSManagedObjectContext;
@class NSManagedObjectID;
@class NSManagedObject;
@class NSRelationshipDescription;
@class NSIncrementalStoreNode;
@class NSEntityDescription;

// Abstract class defining the API through which Core Data communicates with a store. 
// This API is designed to allow users to create persistent stores which load and save 
// data incrementally, allowing for the management of large and/or shared datasets.
API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSIncrementalStore : NSPersistentStore {
}

// CoreData expects loadMetadata: to validate that the URL used to create the store is usable
// (location exists, is writable (if applicable), schema is compatible, etc) and return an 
// error if there is an issue. 
// Any subclass of NSIncrementalStore which is file-based must be able to handle being initialized
// with a URL pointing to a zero-length file. This serves as an indicator that a new store is to be
// constructed at the specified location and allows applications using the store to securly create
// reservation files in known locations.
-(BOOL)loadMetadata:(NSError **)error; 

// API methods that must be overriden by a subclass:

// Return a value as appropriate for the request, or nil if the request cannot be completed.
// If the request is a fetch request whose result type is set to one of NSManagedObjectResultType, 
// NSManagedObjectIDResultType, NSDictionaryResultType, return an array containing all objects
// in the store matching the request.
// If the request is a fetch request whose result type is set to NSCountResultType, return an 
// array containing an NSNumber of all objects in the store matching the request.
// If the request is a save request, the result should be an empty array. Note that 
// save requests may have nil inserted/updated/deleted/locked collections; this should be
// treated as a request to save the store metadata.
// Note that subclasses of NSIncrementalStore should implement this method conservatively, 
// and expect that unknown request types may at some point be passed to the 
// method. The correct behavior in these cases would be to return nil and an error.
- (nullable id)executeRequest:(NSPersistentStoreRequest *)request withContext:(nullable NSManagedObjectContext*)context error:(NSError **)error;

// Returns an NSIncrementalStoreNode encapsulating the persistent external values for the object for an objectID. 
// It should include all attributes values and may include to-one relationship values as NSManagedObjectIDs.
// Should return nil and set the error if the object cannot be found.
- (nullable NSIncrementalStoreNode *)newValuesForObjectWithID:(NSManagedObjectID*)objectID withContext:(NSManagedObjectContext*)context error:(NSError**)error;

// Returns the relationship for the given relationship on the object with ID objectID. If the relationship
// is a to-one it should return an NSManagedObjectID corresponding to the destination or NSNull if the relationship value is nil.
// If the relationship is a to-many, should return an NSSet or NSArray containing the NSManagedObjectIDs of the related objects.
// Should return nil and set the error if the source object cannot be found.
- (nullable id)newValueForRelationship:(NSRelationshipDescription*)relationship forObjectWithID:(NSManagedObjectID*)objectID withContext:(nullable NSManagedObjectContext *)context error:(NSError **)error;


// API methods that may be overriden:
+ (id)identifierForNewStoreAtURL:(NSURL*)storeURL;

// Called before executeRequest with a save request, to assign permanent IDs to newly inserted objects; 
// must return the objectIDs in the same order as the objects appear in array.
- (nullable NSArray<NSManagedObjectID *> *)obtainPermanentIDsForObjects:(NSArray<NSManagedObject *> *)array error:(NSError **)error;

// Inform the store that the objects with ids in objectIDs are in use in a client NSManagedObjectContext
- (void)managedObjectContextDidRegisterObjectsWithIDs:(NSArray<NSManagedObjectID *> *)objectIDs;

// Inform the store that the objects with ids in objectIDs are no longer in use in a client NSManagedObjectContext
- (void)managedObjectContextDidUnregisterObjectsWithIDs:(NSArray<NSManagedObjectID *> *)objectIDs;


// API utility methods that should not be overriden (implemented by NSIncrementalStore):

// Returns a new objectID with retain count 1 that uses data as the key.
- (NSManagedObjectID *)newObjectIDForEntity:(NSEntityDescription *)entity referenceObject:(id)data;
// Returns the reference data used to construct the objectID. Will raise an NSInvalidArgumentException if the objectID was not created
// by this store.
- (id)referenceObjectForObjectID:(NSManagedObjectID *)objectID;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSQueryGenerationToken.h
/*
    NSQueryGenerationToken.h
    Core Data
    Copyright (c) 2016-2019, Apple Inc.
    All rights reserved.
*/
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0))
// Class used to track database generations for generational querying.
// See NSManagedObjectContext for details on how it is used.
@interface NSQueryGenerationToken : NSObject <NSCopying, NSSecureCoding>

@property (class, readonly, strong) NSQueryGenerationToken *currentQueryGenerationToken; // Used to inform a context that it should use the current generation

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSPersistentCloudKitContainerOptions.h
/*
    NSPersistentCloudKitContainerOptions.h
    Core Data
    Copyright (c) 2018-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>


NS_ASSUME_NONNULL_BEGIN

/**
 NSPersistentCloudKitContainerOptions provides customization of how NSPersistentCloudKitContainer aligns a given instance of NSPersistentStoreDescription with a CloudKit database.
 */
API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSPersistentCloudKitContainerOptions : NSObject
/**
 shouldInitializeSchema is generally only set once during development to fully materialize a CloudKit schema for a given managed object model.
 
 This should be set when you are ready to promote your schema to the Production CloudKit environment via the CloudKit dashboard using the following method:
 
 1. Set shouldInitializeSchema = YES
 2. Build and run your application so that it loads the CloudKit backed store (or stores)
 3. Use the CloudKit Dashboard to promote the resulting schema to production
 4. Set shouldInitializeSchema = NO
 
 */
@property(assign) BOOL shouldInitializeSchema;

/**
 The container identifier of the CKContainer to use with a given instance of NSPersistentStoreDescription
 */
@property(readonly, copy) NSString *containerIdentifier;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithContainerIdentifier:(NSString *)containerIdentifier NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSCoreDataCoreSpotlightDelegate.h
/*
    NSCoreDataCoreSpotlightDelegate.h
    Core Data
    Copyright (c) 2017-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>


@class NSManagedObjectContext;
@class NSPersistentStoreDescription;
@class NSManagedObjectModel;
@class NSManagedObject;
@class CSSearchableIndex;
@class CSSearchableItemAttributeSet;

NS_ASSUME_NONNULL_BEGIN

/* NSCoreDataSpotlightDelegate implements the CSSearchableIndexDelegate API, but can't
 publicly declare it due to linkage requirements.
 */
API_AVAILABLE(macosx(10.13),ios(11.0)) API_UNAVAILABLE(tvos,watchos)
@interface NSCoreDataCoreSpotlightDelegate : NSObject {
}

/* CoreSpotlight domain identifer; default nil */
- (NSString *)domainIdentifier;

/* CoreSpotlight index name; default is the store's identifier */
- (nullable NSString *)indexName;

- (instancetype)initForStoreWithDescription:(NSPersistentStoreDescription *)description  model:(NSManagedObjectModel *)model NS_DESIGNATED_INITIALIZER;

/* Create the searchable attributes for the managed object. Override to return nil if you don't
 want the object in the index for some reason.
 */
- (nullable CSSearchableItemAttributeSet *)attributeSetForObject:(NSManagedObject*)object;

/* CSSearchableIndexDelegate conformance */
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexAllSearchableItemsWithAcknowledgementHandler:(void (^)(void))acknowledgementHandler;

- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexSearchableItemsWithIdentifiers:(NSArray <NSString *> *)identifiers
 acknowledgementHandler:(void (^)(void))acknowledgementHandler;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSAtomicStoreCacheNode.h
/*
    NSAtomicStoreCacheNode.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSError.h>
#import <Foundation/NSURL.h>
#import <CoreData/NSManagedObjectID.h>
#import <CoreData/NSManagedObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSAtomicStoreCacheNode : NSObject {
}

/* The designated initializer for the cache node. */
- (instancetype)initWithObjectID:(NSManagedObjectID *)moid;

/* Returns the managed object ID for the cache node. */
@property (nonatomic, readonly, strong) NSManagedObjectID *objectID;

/* Returns the property cache dictionary for the cache node.  This dictionary is used by -valueForKey: and -setValue:forKey: for property values.  The default implementation will return nil unless the companion -setPropertyCache: method is invoked, or -setValue:forKey: is invoked on the cache node with non-nil property values.
*/
@property (nullable, nonatomic, strong) NSMutableDictionary<NSString *, id> *propertyCache;


/* Returns the value for the specified key.  Subclasses must return the appropriate object value for all property keys (as specified by the names of the NSPropertyDescriptions for the entity of this cache node.)  For attributes, these are instances of NSObject; for to-one relationships, the return value must be another cache node instance; for a to-many relationship, the return value must be an NSSet of the related cache nodes.  

The default implementation forwards the request to the -propertyCache dictionary if the key matches a property name of the entity for the cache node.  If the key does not represent a property, the standard -valueForKey: implementation will be used.
*/
- (nullable id)valueForKey:(NSString*)key;

/* Sets the value for the specified key.  The default implementation forwards the request to the -propertyCache dictionary if the key matches a property name of the entity for this cache node.  If the key does not represent a  property, the standard -setValue:forKey: implementation will be used. 
*/
- (void)setValue:(nullable id)value forKey:(NSString*)key;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentHistoryChange.h
/*
    NSPersistentHistoryChange.h
    Core Data
    Copyright (c) 2016-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSDictionary.h>
#import <Foundation/NSData.h>
#import <Foundation/NSSet.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentHistoryTransaction;
@class NSManagedObjectID;
@class NSPropertyDescription;
@class NSEntityDescription;
@class NSFetchRequest;
@class NSManagedObjectContext;

typedef NS_ENUM (NSInteger, NSPersistentHistoryChangeType) {
    NSPersistentHistoryChangeTypeInsert,
    NSPersistentHistoryChangeTypeUpdate,
    NSPersistentHistoryChangeTypeDelete,
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryChange : NSObject <NSCopying>

+ (nullable NSEntityDescription *)entityDescriptionWithContext:(NSManagedObjectContext *)context API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@property (class,nullable,readonly) NSEntityDescription *entityDescription API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));
@property (class,nullable,readonly) NSFetchRequest *fetchRequest API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

@property (readonly) int64_t changeID;
@property (readonly,copy) NSManagedObjectID *changedObjectID;
@property (readonly) NSPersistentHistoryChangeType changeType;
@property (nullable,readonly,copy) NSDictionary *tombstone;
@property (nullable,readonly,strong) NSPersistentHistoryTransaction *transaction;
@property (nullable,readonly,copy) NSSet<NSPropertyDescription *> *updatedProperties;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSBatchDeleteRequest.h
/*
    NSBatchDeleteRequest.h
    Core Data
    Copyright (c) 2015-2019, Apple Inc.
    All rights reserved.
*/


#import <Foundation/NSArray.h>

#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

@class NSFetchRequest;
@class NSManagedObjectID;

NS_ASSUME_NONNULL_BEGIN

//  Used to request that Core Data do a batch deletion of objects without faulting in
//  objects to be deleted.
//  May not be supported by all store types.
//  WARNING:
//  It is up to the developer creating the request to ensure that changes made by the request to
//  the underlying store do not violate any validation rules specified in the model beyond basic
//  delete rules (for example, minimum relationship counts).
API_AVAILABLE(macosx(10.11),ios(9.0))
@interface NSBatchDeleteRequest : NSPersistentStoreRequest {
}

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFetchRequest:(NSFetchRequest *)fetch NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjectIDs:(NSArray<NSManagedObjectID *> *)objects;

// The type of result that should be returned from this request. Defaults to NSBatchDeleteResultTypeStatusOnly
@property NSBatchDeleteRequestResultType resultType;

@property (readonly, copy) NSFetchRequest *fetchRequest;


@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentStoreResult.h
/*
    NSPersistentStoreResult.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSError;
@class NSProgress;
@class NSManagedObjectContext;
@class NSFetchRequest;
@class NSPersistentStoreAsynchronousResult;
@class NSAsynchronousFetchResult;
@class NSAsynchronousFetchRequest;

typedef NS_ENUM(NSUInteger, NSBatchUpdateRequestResultType) {
    NSStatusOnlyResultType = 0x0,            // Return a status boolean
    NSUpdatedObjectIDsResultType = 0x1,      // Return the object IDs of the rows that were updated
    NSUpdatedObjectsCountResultType = 0x2    // Return the number of rows that were updated
} API_AVAILABLE(macosx(10.10), ios(8.0));

typedef NS_ENUM(NSUInteger, NSBatchDeleteRequestResultType) {
    NSBatchDeleteResultTypeStatusOnly = 0x0, // Return a status boolean
    NSBatchDeleteResultTypeObjectIDs = 0x1,  // Return the object IDs of the rows that were deleted
    NSBatchDeleteResultTypeCount = 0x2,      // Return the number of rows that were deleted
} API_AVAILABLE(macosx(10.11), ios(9.0));


typedef NS_ENUM(NSInteger, NSPersistentHistoryResultType) {
    NSPersistentHistoryResultTypeStatusOnly = 0x0,
    NSPersistentHistoryResultTypeObjectIDs = 0x1,   // Return the object IDs of the changes objects
    NSPersistentHistoryResultTypeCount = 0x2,       // Return the number of changes
    NSPersistentHistoryResultTypeTransactionsOnly = 0x3,// Return the transactions since
    NSPersistentHistoryResultTypeChangesOnly = 0x4,     // Return the changes since
    NSPersistentHistoryResultTypeTransactionsAndChanges = 0x5,// Return the transactions and changes since
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

// Used to wrap the result of whatever is returned by the persistent store coordinator when
// -[NSManagedObjectContext executeRequest:error:] is called
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreResult : NSObject

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreAsynchronousResult : NSPersistentStoreResult {
}

@property (strong, readonly) NSManagedObjectContext* managedObjectContext;
@property (nullable, strong, readonly) NSError* operationError;
@property (nullable, strong, readonly) NSProgress* progress;

- (void)cancel;

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSAsynchronousFetchResult<ResultType:id<NSFetchRequestResult>> : NSPersistentStoreAsynchronousResult {
}

@property (strong, readonly) NSAsynchronousFetchRequest<ResultType> * fetchRequest;
@property (nullable, strong, readonly) NSArray<ResultType> * finalResult;

@end

// The result returned when executing an NSBatchUpdateRequest
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSBatchUpdateResult : NSPersistentStoreResult {
}

// Return the result. See NSBatchUpdateRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchUpdateRequestResultType resultType;

@end


// The result returned when executing an NSBatchDeleteRequest
API_AVAILABLE(macosx(10.11),ios(9.0))
@interface NSBatchDeleteResult : NSPersistentStoreResult {
}

// Return the result. See NSBatchDeleteRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchDeleteRequestResultType resultType;

@end


// The result returned when executing an NSPersistentHistoryChangeRequest
API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryResult : NSPersistentStoreResult {
}

// Return the result. See NSPersistentHistoryResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSPersistentHistoryResultType resultType;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentStoreCoordinator.h
/*
    NSPersistentStoreCoordinator.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSError.h>
#import <Foundation/NSLock.h>
#import <CoreData/CoreDataDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURL;
@class NSValue;
@class NSManagedObjectID;
@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSPersistentStore;
@class NSPersistentStoreRequest;
@class NSPersistentStoreDescription;

// Persistent store types supported by Core Data:
COREDATA_EXTERN NSString * const NSSQLiteStoreType API_AVAILABLE(macosx(10.4),ios(3.0));
COREDATA_EXTERN NSString * const NSXMLStoreType API_AVAILABLE(macosx(10.4)) API_UNAVAILABLE(ios);
COREDATA_EXTERN NSString * const NSBinaryStoreType API_AVAILABLE(macosx(10.4),ios(3.0));
COREDATA_EXTERN NSString * const NSInMemoryStoreType API_AVAILABLE(macosx(10.4),ios(3.0));

// Persistent store metadata dictionary keys:

// key in the metadata dictionary to identify the store type
COREDATA_EXTERN NSString * const NSStoreTypeKey API_AVAILABLE(macosx(10.4),ios(3.0));    

// key in the metadata dictionary to identify the store UUID - the store UUID is useful to identify stores through URI representations, but it is NOT guaranteed to be unique (while the UUID generated for new stores is unique, users can freely copy files and thus the UUID stored inside, so developers that track/reference stores explicitly do need to be aware of duplicate UUIDs and potentially override the UUID when a new store is added to the list of known stores in their application)
COREDATA_EXTERN NSString * const NSStoreUUIDKey API_AVAILABLE(macosx(10.4),ios(3.0));    

/* A notification posted before the list of open persistent stores changes, similar to NSPersistentStoreCoordinatorStoresDidChangeNotification.  If the application is running, Core Data will post this before responding to iCloud account changes or "Delete All" from Documents & Data.
 */
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorStoresWillChangeNotification API_AVAILABLE(macosx(10.9),ios(7.0));

// user info dictionary contains information about the stores that were added or removed
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorStoresDidChangeNotification API_AVAILABLE(macosx(10.4),ios(3.0));    

// sent during the invocation of NSPersistentStore's willRemoveFromPersistentStoreCoordinator during store deallocation or removal
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorWillRemoveStoreNotification API_AVAILABLE(macosx(10.5),ios(3.0));    

// User info keys for NSPersistentStoreCoordinatorStoresDidChangeNotification:

// The object values for NSAddedPersistentStoresKey and NSRemovedPersistentStoresKey will be arrays containing added/removed stores
COREDATA_EXTERN NSString * const NSAddedPersistentStoresKey API_AVAILABLE(macosx(10.4),ios(3.0));
COREDATA_EXTERN NSString * const NSRemovedPersistentStoresKey API_AVAILABLE(macosx(10.4),ios(3.0));

// The object value for NSUUIDChangedPersistentStoresKey will be an array where the object at index 0 will be the old store instance, and the object at index 1 the new
COREDATA_EXTERN NSString * const NSUUIDChangedPersistentStoresKey API_AVAILABLE(macosx(10.4),ios(3.0));

// Persistent store option keys:

// flag indicating whether a store is treated as read-only or not - default is NO
COREDATA_EXTERN NSString * const NSReadOnlyPersistentStoreOption API_AVAILABLE(macosx(10.4),ios(3.0));    

// flag indicating whether an XML file should be validated with the DTD while opening - default is NO
COREDATA_EXTERN NSString * const NSValidateXMLStoreOption API_AVAILABLE(macosx(10.4)) API_UNAVAILABLE(ios);    

// Migration keys:

/* Options key specifying the connection timeout for Core Data stores.  This value (an NSNumber) represents the duration, in seconds, Core Data will wait while attempting to create a connection to a persistent store.  If a connection is unable to be made within that timeframe, the operation is aborted and an error is returned.  
*/
COREDATA_EXTERN NSString * const NSPersistentStoreTimeoutOption API_AVAILABLE(macosx(10.5),ios(3.0));

/* Options key for a dictionary of sqlite pragma settings with pragma values indexed by pragma names as keys.  All pragma values must be specified as strings.  The fullfsync and synchronous pragmas control the tradeoff between write performance (write to disk speed & cache utilization) and durability (data loss/corruption sensitivity to power interruption).  For more information on pragma settings visit <http://sqlite.org/pragma.html>
*/
COREDATA_EXTERN NSString * const NSSQLitePragmasOption API_AVAILABLE(macosx(10.5),ios(3.0));

/* Option key to run an analysis of the store data to optimize indices based on statistical information when the store is added to the coordinator.  This invokes SQLite's ANALYZE command.  Ignored by other stores.
*/
COREDATA_EXTERN NSString * const NSSQLiteAnalyzeOption API_AVAILABLE(macosx(10.5),ios(3.0));

/* Option key to rebuild the store file, forcing a database wide defragmentation when the store is added to the coordinator.  This invokes SQLite's VACUUM command.  Ignored by other stores.
 */
COREDATA_EXTERN NSString * const NSSQLiteManualVacuumOption API_AVAILABLE(macosx(10.6),ios(3.0));

/* Options key to ignore the built-in versioning provided by Core Data.  If the value for this key (an NSNumber) evaluates to YES (using boolValue), Core Data will not compare the version hashes between the managed object model in the coordinator and the metadata for the loaded store.  (It will, however, continue to update the version hash information in the metadata.)  This key is specified by default for all applications linked on or before Mac OS X 10.4.
*/
COREDATA_EXTERN NSString * const NSIgnorePersistentStoreVersioningOption API_AVAILABLE(macosx(10.5),ios(3.0));

/* Options key to automatically attempt to migrate versioned stores.  If the value for this key (an NSNumber) evaluates to YES (using boolValue) Core Data will, if the version hash information for added store is determined to be incompatible with the model for the coordinator, attempt to locate the source and mapping models in the application bundles, and perform a migration.  
*/
COREDATA_EXTERN NSString * const NSMigratePersistentStoresAutomaticallyOption API_AVAILABLE(macosx(10.5),ios(3.0));

/* When combined with NSMigratePersistentStoresAutomaticallyOption, coordinator will attempt to infer a mapping model if none can be found */
COREDATA_EXTERN NSString * const NSInferMappingModelAutomaticallyOption API_AVAILABLE(macosx(10.6),ios(3.0));

/* Key to represent the version hash information (dictionary) for the model used to create a persistent store.  This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionHashesKey API_AVAILABLE(macosx(10.5),ios(3.0));    

/* Key to represent the version identifier for the model used to create the store. This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionIdentifiersKey API_AVAILABLE(macosx(10.5),ios(3.0));    

/* Key to represent the earliest version of MacOS X the persistent store should support.  Backward compatibility may preclude some features.  The numeric values are defined in AvailabilityMacros.h
*/
COREDATA_EXTERN NSString * const NSPersistentStoreOSCompatibility API_AVAILABLE(macosx(10.5),ios(3.0));    

/* User info key specifying the maximum connection pool size that should be used on a store that supports concurrent request handling, the value should be an NSNumber. The connection pool size determines the number of requests a store can handle concurrently, and should be a function of how many contexts are attempting to access store data at any time. Generally, application developers should not set this, and should use the default value. The default connection pool size is implementation dependent and may vary by store type and/or platform.
 */
COREDATA_EXTERN NSString * const NSPersistentStoreConnectionPoolMaxSizeKey API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* Spotlight indexing and external record support keys */

COREDATA_EXTERN NSString * const NSCoreDataCoreSpotlightExporter API_AVAILABLE(macosx(10.13),ios(11.0)) API_UNAVAILABLE(tvos,watchos);


/* store option for the destroy... and replace... to indicate that the store file should be destroyed even if the operation might be unsafe (overriding locks
 */
COREDATA_EXTERN NSString * const NSPersistentStoreForceDestroyOption API_AVAILABLE(macosx(10.8),ios(6.0));

/* Key to represent the protection class for the persistent store.  Backward compatibility may preclude some features.  The acceptable values are those defined in Foundation for the NSFileProtectionKey.  The default value of NSPersistentStoreFileProtectionKey is NSFileProtectionCompleteUntilFirstUserAuthentication for all applications built on or after iOS5.  The default value for all older applications is NSFileProtectionNone. */
COREDATA_EXTERN NSString * const NSPersistentStoreFileProtectionKey API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macosx);

/* Dictionary key for enabling persistent history - default is NO */
COREDATA_EXTERN NSString * const NSPersistentHistoryTrackingKey API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

/*
 Allows developers to provide an additional set of classes (which must implement NSSecureCoding) that should be used while
 decoding a binary store.
 Using this option is preferable to using NSBinaryStoreInsecureDecodingCompatibilityOption.
 */
COREDATA_EXTERN NSString * const NSBinaryStoreSecureDecodingClasses API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

/*
 Indicate that the binary store should be decoded insecurely. This may be necessary if a store has metadata or transformable
 properties containing non-standard classes. If possible, developers should use the NSBinaryStoreSecureDecodingClasses option
 to specify the contained classes, allowing the binary store to to be securely decoded.
 Applications linked before the availability date will default to using this option.
 */
COREDATA_EXTERN NSString * const NSBinaryStoreInsecureDecodingCompatibilityOption API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

/* When NSPersistentStoreRemoteChangeNotificationPostOptionKey is set to YES, a NSPersistentStoreRemoteChangeNotification is posted for every
 write to the store, this includes writes that are done by other processes
 */
COREDATA_EXTERN NSString * const NSPersistentStoreRemoteChangeNotificationPostOptionKey API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

/* NSPersistentStoreRemoteChangeNotification is posted for all cross process writes to the store
 The payload is the store UUID (NSStoreUUIDKey), store URL (NSPersistentStoreURLKey), and NSPersistentHistoryToken for the transaction (if NSPersistentHistoryTrackingKey was also set)
 */
COREDATA_EXTERN NSString * const NSPersistentStoreRemoteChangeNotification API_AVAILABLE(macosx(10.14),ios(12.0),tvos(12.0),watchos(5.0));

/* Keys found in the UserInfo for a NSPersistentStoreRemoteChangeNotification */
COREDATA_EXTERN NSString * const NSPersistentStoreURLKey API_AVAILABLE(macosx(10.14),ios(12.0),tvos(12.0),watchos(5.0));
COREDATA_EXTERN NSString * const NSPersistentHistoryTokenKey API_AVAILABLE(macosx(10.14),ios(12.0),tvos(12.0),watchos(5.0));

API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSPersistentStoreCoordinator : NSObject <NSLocking> {
}

- (instancetype)initWithManagedObjectModel:(NSManagedObjectModel *)model NS_DESIGNATED_INITIALIZER;

@property (readonly, strong) NSManagedObjectModel *managedObjectModel;

@property (readonly, strong) NSArray<__kindof NSPersistentStore *> *persistentStores;

/* custom name for a coordinator.  Coordinators will set the label on their queue */
@property (nullable, copy) NSString *name  API_AVAILABLE(macosx(10.10),ios(8.0));

- (nullable __kindof NSPersistentStore *)persistentStoreForURL:(NSURL *)URL;
- (NSURL *)URLForPersistentStore:(NSPersistentStore *)store;

/* Sets the URL for the specified store in the coordinator.  For atomic stores, this will alter the location to which the next save operation will persist the file;  for non-atomic stores, invoking this method will release the existing connection and create a new one at the specified URL.  (For non-atomic stores, a store must pre-exist at the destination URL; a new store will not be created.)
 */
- (BOOL)setURL:(NSURL*)url forPersistentStore:(NSPersistentStore *)store API_AVAILABLE(macosx(10.5),ios(3.0));

/* Adds the store at the specified URL (of the specified type) to the coordinator with the model configuration and options.  The configuration can be nil -- then it's the complete model; storeURL is usually the file location of the database
 */
- (nullable __kindof NSPersistentStore *)addPersistentStoreWithType:(NSString *)storeType configuration:(nullable NSString *)configuration URL:(nullable NSURL *)storeURL options:(nullable NSDictionary *)options error:(NSError **)error;

- (void)addPersistentStoreWithDescription:(NSPersistentStoreDescription *)storeDescription completionHandler:(void (^)(NSPersistentStoreDescription *, NSError * _Nullable))block API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

- (BOOL)removePersistentStore:(NSPersistentStore *)store error:(NSError **)error;

/* Sets the metadata stored in the persistent store during the next save operation executed on it; the store type and UUID (NSStoreTypeKey and NSStoreUUIDKey) are always added automatically (but NSStoreUUIDKey is only added if it is not set manually as part of the dictionary argument)
 */
- (void)setMetadata:(nullable NSDictionary<NSString *, id> *)metadata forPersistentStore:(NSPersistentStore *)store;

/* Returns the metadata currently stored or to-be-stored in the persistent store
 */
- (NSDictionary<NSString *, id> *)metadataForPersistentStore:(NSPersistentStore *)store;

/* Given a URI representation of an object ID, returns an object ID if a matching store is available or nil if a matching store cannot be found (the URI representation contains a UUID of the store the ID is coming from, and the coordinator can match it against the stores added to it)
 */
- (nullable NSManagedObjectID *)managedObjectIDForURIRepresentation:(NSURL *)url;

/* Sends a request to all of the stores associated with this coordinator.
 Returns an array if successful,  nil if not.
 The contents of the array will vary depending on the request type: NSFetchRequest results will be an array of managed objects, managed object IDs, or NSDictionaries;
 NSSaveChangesRequests will an empty array. User defined requests will return arrays of arrays, where the nested array is the result returned form a single store.
 */
- (nullable id)executeRequest:(NSPersistentStoreRequest *)request withContext:(NSManagedObjectContext *)context error:(NSError**)error API_AVAILABLE(macosx(10.7),ios(5.0));

/* Returns a dictionary of the registered store types:  the keys are the store type strings and the values are the NSPersistentStore subclasses wrapped in NSValues.
*/
@property(class, readonly, strong) NSDictionary<NSString *, NSValue *> *registeredStoreTypes API_AVAILABLE(macosx(10.5),ios(3.0));

/* Registers the specified NSPersistentStore subclass for the specified store type string.  This method must be invoked before a custom subclass of NSPersistentStore can be loaded into a persistent store coordinator.  Passing nil for the store class argument will unregister the specified store type.
*/
+ (void)registerStoreClass:(nullable Class)storeClass forStoreType:(NSString *)storeType API_AVAILABLE(macosx(10.5),ios(3.0));

/* Allows to access the metadata stored in a persistent store without warming up a CoreData stack; the guaranteed keys in this dictionary are NSStoreTypeKey and NSStoreUUIDKey. If storeType is nil, Core Data will guess which store class should be used to get/set the store file's metadata. 
 */
+ (nullable NSDictionary<NSString *, id> *)metadataForPersistentStoreOfType:(NSString*)storeType URL:(NSURL *)url options:(nullable NSDictionary *)options error:(NSError **)error API_AVAILABLE(macosx(10.9),ios(7.0));
+ (BOOL)setMetadata:(nullable NSDictionary<NSString *, id> *)metadata forPersistentStoreOfType:(NSString*)storeType URL:(NSURL*)url options:(nullable NSDictionary*)options error:(NSError**)error API_AVAILABLE(macosx(10.9),ios(7.0));

    
/* Used for save as - performance may vary depending on the type of old and new store; the old store is usually removed from the coordinator by the migration operation, and therefore is no longer a useful reference after invoking this method 
*/
- (nullable NSPersistentStore *)migratePersistentStore:(NSPersistentStore *)store toURL:(NSURL *)URL options:(nullable NSDictionary *)options withType:(NSString *)storeType error:(NSError **)error;

/* delete or truncate the target persistent store in accordance with the store class's requirements.  It is important to pass similar options as addPersistentStoreWithType: ... SQLite stores will honor file locks, journal files, journaling modes, and other intricacies.  It is not possible to unlink a database file safely out from underneath another thread or process, so this API performs a truncation.  Other stores will default to using NSFileManager.
 */
- (BOOL)destroyPersistentStoreAtURL:(NSURL *)url withType:(NSString *)storeType options:(nullable NSDictionary *)options error:(NSError**)error API_AVAILABLE(macosx(10.11),ios(9.0));

/* copy or overwrite the target persistent store in accordance with the store class's requirements.  It is important to pass similar options as addPersistentStoreWithType: ... SQLite stores will honor file locks, journal files, journaling modes, and other intricacies.  Other stores will default to using NSFileManager.
 */
- (BOOL)replacePersistentStoreAtURL:(NSURL *)destinationURL destinationOptions:(nullable NSDictionary *)destinationOptions withPersistentStoreFromURL:(NSURL *)sourceURL sourceOptions:(nullable NSDictionary *)sourceOptions storeType:(NSString *)storeType error:(NSError**)error API_AVAILABLE(macosx(10.11),ios(9.0));

/* asynchronously performs the block on the coordinator's queue.  Encapsulates an autorelease pool. */
- (void)performBlock:(void (^)(void))block  API_AVAILABLE(macosx(10.10),ios(8.0));

/* synchronously performs the block on the coordinator's queue.  May safely be called reentrantly. Encapsulates an autorelease pool. */
- (void)performBlockAndWait:(void (NS_NOESCAPE ^)(void))block  API_AVAILABLE(macosx(10.10),ios(8.0));

 /*
  *   DEPRECATED
  */
    
    
- (void)lock API_DEPRECATED( "Use -performBlockAndWait: instead", macosx(10.4,10.10), ios(3.0,8.0));
- (void)unlock API_DEPRECATED( "Use -performBlockAndWait: instead", macosx(10.4,10.10), ios(3.0,8.0));
- (BOOL)tryLock API_DEPRECATED( "Use -performBlock: instead", macosx(10.4,10.10), ios(3.0,8.0));
    
+ (nullable NSDictionary<NSString *, id> *)metadataForPersistentStoreOfType:(nullable NSString *)storeType URL:(NSURL *)url error:(NSError **)error API_DEPRECATED("Use -metadataForPersistentStoreOfType:URL:options:error: and pass in an options dictionary matching addPersistentStoreWithType", macosx(10.5,10.11), ios(3.0,9.0));

+ (BOOL)setMetadata:(nullable NSDictionary<NSString *, id> *)metadata forPersistentStoreOfType:(nullable NSString *)storeType URL:(NSURL*)url error:(NSError **)error API_DEPRECATED("Use  -setMetadata:forPersistentStoreOfType:URL:options:error: and pass in an options dictionary matching addPersistentStoreWithType", macosx(10.5,10.11), ios(3.0,9.0));

/*
 Delete all ubiquitous content for all peers for the persistent store at the given URL and also delete the local store file. storeOptions should contain the options normally passed to addPersistentStoreWithType:URL:options:error. Errors may be returned as a result of file I/O, iCloud network or iCloud account issues.
 */
+ (BOOL)removeUbiquitousContentAndPersistentStoreAtURL:(NSURL *)storeURL options:(nullable NSDictionary *)options error:(NSError**)error API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.7,10.12), ios(5.0,10.0));


@end

/*
 NSPersistentStoreUbiquitousTransitionTypeAccountAdded
 This value indicates that a new iCloud account is available, and the persistent store in use will / did transition to the new account.
 It is only possible to discern this state when the application is running, and therefore this transition type will only be posted if the account changes while the application is running or in the background.
 
 NSPersistentStoreUbiquitousTransitionTypeAccountRemoved
 This value indicates that no iCloud account is available, and the persistent store in use will / did transition to the “local” store.
 It is only possible to discern this state when the application is running, and therefore this transition type will only be posted if the account is removed while the application is running or in the background.
 
 NSPersistentStoreUbiquitousTransitionTypeContentRemoved
 This value indicates that the user has wiped the contents of the iCloud account, usually using Delete All from Documents & Data in Settings. The Core Data integration will transition to an empty store file as a result of this event.
 
 NSPersistentStoreUbiquitousTransitionTypeInitialImportCompleted
 This value indicates that the Core Data integration has finished building a store file that is consistent with the contents of the iCloud account, and is readyto replace the fallback store with that file.
 */
typedef NS_ENUM(NSUInteger, NSPersistentStoreUbiquitousTransitionType) {
    NSPersistentStoreUbiquitousTransitionTypeAccountAdded = 1,
    NSPersistentStoreUbiquitousTransitionTypeAccountRemoved,
    NSPersistentStoreUbiquitousTransitionTypeContentRemoved,
    NSPersistentStoreUbiquitousTransitionTypeInitialImportCompleted
} API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));

/* option indicating that a persistent store has a given name in ubiquity, this option is required for ubiquity to function  */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousContentNameKey API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.7,10.12), ios(5.0,10.0));

/* option indicating the log path to use for ubiquity logs, this option is optional for ubiquity, a default path will be generated for the store if none is provided */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousContentURLKey API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.7,10.12), ios(5.0,10.0));

/* Notification sent after records are imported from the ubiquity store. The notification is sent with the object set to the NSPersistentStoreCoordinator instance which registered the store. */
COREDATA_EXTERN NSString * const NSPersistentStoreDidImportUbiquitousContentChangesNotification API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.7,10.12), ios(5.0,10.0));

/*
 In the NSPersistentStoreCoordinatorStoresWillChangeNotification / NSPersistentStoreCoordinatorStoresDidChangeNotification userInfo dictionaries, this identifies the type of event. This could be one of the NSPersistentStoreUbiquitousTransitionType enum values as an NSNumber
 */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousTransitionTypeKey API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));

/*
 Optionally specified string which will be mixed in to Core Data’s identifier for each iCloud peer. The value must be an alphanumeric string without any special characters, whitespace or punctuation.  The primary use for this option is to allow multiple applications on the same peer (device) to share a Core Data store integrated with iCloud. Each application will require its own store file.
 */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousPeerTokenOption API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));

/* NSNumber boolean indicating that the receiver should remove all associated ubiquity metadata from a persistent store. This is mostly used during migration or copying to disassociate a persistent store file from an iCloud account
 */
COREDATA_EXTERN NSString * const NSPersistentStoreRemoveUbiquitousMetadataOption API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));

/* NSString specifying the iCloud container identifier Core Data should pass to  -URLForUbiquitousContainerIdentifier:
 */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousContainerIdentifierKey API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));

/* NSNumber boolean indicating that the receiver should erase the local store file and rebuild it from the iCloud data in Mobile Documents.
 */
COREDATA_EXTERN NSString * const NSPersistentStoreRebuildFromUbiquitousContentOption API_DEPRECATED("Please see the release notes and Core Data documentation.", macosx(10.9,10.12), ios(7.0,10.0));
    

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSPersistentStore.h
/*
    NSPersistentStore.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSError.h>
#import <Foundation/NSURL.h>

NS_ASSUME_NONNULL_BEGIN

@class NSManagedObjectID;
@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSPersistentStore;
@class NSPersistentStoreRequest;
@class NSPersistentStoreCoordinator;

@class NSCoreDataCoreSpotlightDelegate;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSPersistentStore : NSObject {
}

/* Get metadata from the persistent store at url. Must be overriden by subclasses.
   Subclasses should validate that the URL is the type of URL they are expecting, and 
   should verify that the file contents are appropriate for the store type before
   attempting to read from it. This method should never raise an exception.
 */
+ (nullable NSDictionary<NSString *, id> *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error;
/* Set the medatada of the store at url to metadata. Must be overriden by subclasses. */
+ (BOOL)setMetadata:(nullable NSDictionary<NSString *, id> *)metadata forPersistentStoreWithURL:(NSURL*)url error:(NSError **)error;

/* Returns the NSMigrationManager class optimized for this store class.  Subclasses of NSPersistentStore can override this to provide a custom migration manager subclass (eg to take advantage of store-specific functionality to improve migration performance).
 */
+ (Class)migrationManagerClass API_AVAILABLE(macosx(10.6),ios(3.0));

/* the designated initializer for object stores. */
- (instancetype)initWithPersistentStoreCoordinator:(nullable NSPersistentStoreCoordinator *)root configurationName:(nullable NSString *)name URL:(NSURL *)url options:(nullable NSDictionary *)options NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*  Store metadata must be accessible before -load: is called, but there is no way to return an error if the store is invalid 
*/
-(BOOL)loadMetadata:(NSError **)error; 

/* the bridge between the control & access layers. */
@property (nullable, nonatomic, readonly, weak) NSPersistentStoreCoordinator *persistentStoreCoordinator;

@property (readonly, copy) NSString *configurationName; // Which configuration does this store contain 
@property (nullable, readonly, strong) NSDictionary *options; // the options the store was initialized with

@property (nullable, strong) NSURL *URL;

@property (null_resettable, copy) NSString *identifier;

@property (readonly, copy) NSString *type; // stores always know their type

@property (getter=isReadOnly) BOOL readOnly;     // Do we know a priori the store is read only? 

@property (null_resettable, nonatomic, strong) NSDictionary<NSString *, id> *metadata; // includes store type and UUID

// Gives the store a chance to do any post-init work that's necessary
- (void)didAddToPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator;

// Gives the store a chance to do any non-dealloc teardown (for example, closing a network connection) 
// before removal.
- (void)willRemoveFromPersistentStoreCoordinator:(nullable NSPersistentStoreCoordinator *)coordinator;

/* Return the Core Spotlight exporter if one exists for this store. The exporter
    can be set as part of the store options when it is added to the coordinator. */
@property (nonatomic, readonly) NSCoreDataCoreSpotlightDelegate *coreSpotlightExporter API_AVAILABLE(macosx(10.13),ios(11.0)) API_UNAVAILABLE(tvos,watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/CoreData.h
/*
    CoreData.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

#import <CoreData/CoreDataDefines.h>
#import <CoreData/CoreDataErrors.h>

#import <CoreData/NSAttributeDescription.h>
#import <CoreData/NSDerivedAttributeDescription.h>
#import <CoreData/NSEntityDescription.h>
#import <CoreData/NSFetchedPropertyDescription.h>
#import <CoreData/NSPropertyDescription.h>
#import <CoreData/NSExpressionDescription.h>
#import <CoreData/NSRelationshipDescription.h>
#import <CoreData/NSFetchIndexDescription.h>
#import <CoreData/NSFetchIndexElementDescription.h>
#import <CoreData/NSFetchRequest.h>
#import <CoreData/NSFetchRequestExpression.h>
#import <CoreData/NSManagedObjectModel.h>

#import <CoreData/NSManagedObject.h>
#import <CoreData/NSManagedObjectID.h>
#import <CoreData/NSManagedObjectContext.h>
#import <CoreData/NSPersistentStoreCoordinator.h>

#import <CoreData/NSPersistentStore.h>
#import <CoreData/NSAtomicStore.h>
#import <CoreData/NSAtomicStoreCacheNode.h>

#import <CoreData/NSEntityMigrationPolicy.h>
#import <CoreData/NSMappingModel.h>
#import <CoreData/NSEntityMapping.h>
#import <CoreData/NSPropertyMapping.h>
#import <CoreData/NSMigrationManager.h>

#import <CoreData/NSIncrementalStore.h>
#import <CoreData/NSIncrementalStoreNode.h>

#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>
#import <CoreData/NSSaveChangesRequest.h>
#import <CoreData/NSBatchUpdateRequest.h>
#import <CoreData/NSBatchDeleteRequest.h>

#import <CoreData/NSMergePolicy.h>

#import <CoreData/NSFetchedResultsController.h>
#import <CoreData/NSQueryGenerationToken.h>
#import <CoreData/NSPersistentStoreDescription.h>
#import <CoreData/NSPersistentContainer.h>

#import <CoreData/NSFetchIndexDescription.h>
#import <CoreData/NSFetchIndexElementDescription.h>
#import <CoreData/NSPersistentHistoryChange.h>
#import <CoreData/NSPersistentHistoryChangeRequest.h>
#import <CoreData/NSPersistentHistoryToken.h>
#import <CoreData/NSPersistentHistoryTransaction.h>
#import <CoreData/NSPersistentCloudKitContainer.h>
#import <CoreData/NSPersistentCloudKitContainerOptions.h>

#import <CoreData/NSCoreDataCoreSpotlightDelegate.h>
// ==========  CoreData.framework/Headers/NSMigrationManager.h
/*
    NSMigrationManager.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSEntityMapping;
@class NSManagedObjectContext;
@class NSManagedObject;
@class NSManagedObjectModel;
@class NSMappingModel;
@class NSMigrationContext;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSMigrationManager : NSObject {
}

/* Creates a migration manager instance with the corresponding source and destination models.  (All validation of the arguments is performed during migrateStoreFromURL:toURL:)  As with the NSPersistentStoreCoordinator, once models are added to the migration manager they are immutable and cannot be altered.*/

- (instancetype)initWithSourceModel:(NSManagedObjectModel *)sourceModel destinationModel:(NSManagedObjectModel *)destinationModel;

/* Migrates of the store at the specified source URL to the store at the destination URL, performing all of the mappings in the mapping model.  A store must exist at the source URL;  if a store does not exist at the destination URL, one will be created (otherwise the migration will append to the existing store.)  Invoking this method will perform compatibility checks on the source and destination models (and the mapping model.)  If an error occurs during the validation or migration, this method will return NO.*/
- (BOOL)migrateStoreFromURL:(NSURL *)sourceURL type:(NSString *)sStoreType options:(nullable NSDictionary *)sOptions withMappingModel:(nullable NSMappingModel *)mappings toDestinationURL:(NSURL *)dURL destinationType:(NSString *)dStoreType destinationOptions:(nullable NSDictionary *)dOptions error:(NSError **)error;

/* Tries to use a store specific migration manager to perform the store migration, note that a store specific migration manager class is not guaranteed to perform any of the migration manager delegate callbacks or update values for the observable properties.  
 Defaults to YES */
@property () BOOL usesStoreSpecificMigrationManager API_AVAILABLE(macosx(10.7),ios(5.0));

/* Resets the association tables for the migration.  (Note this does NOT reset the source or destination contexts).*/
- (void)reset;

/* Accessors for the mapping model, source model, and destination model*/
@property (readonly, strong) NSMappingModel *mappingModel;
@property (readonly, strong) NSManagedObjectModel *sourceModel;
@property (readonly, strong) NSManagedObjectModel *destinationModel;

/* Accessors for the managed object contexts used for reading the source and destination stores.  These contexts are created lazily, as part of the initialization of two Core Data stacks (one for reading, the other for writing data.)  */
@property (readonly, strong) NSManagedObjectContext *sourceContext;
@property (readonly, strong) NSManagedObjectContext *destinationContext;

/* Returns the NSEntityDescription for the source and destination entities, respectively, of the entity mapping.  (Entity mappings do not store the actual description objects, but rather the name and version information of the entity.)*/
- (nullable NSEntityDescription *)sourceEntityForEntityMapping:(NSEntityMapping *)mEntity;
- (nullable NSEntityDescription *)destinationEntityForEntityMapping:(NSEntityMapping *)mEntity;

/* Associates the source instance with the specified destination instance for the given entity mapping.  Since the migration is performed as a three-step process (first create the data, then relate the data, then validate the data) it is necessary to be able to associate data between the source and destination stores, in order to allow for relationship creation/fixup after the creation pass.  This method is called in the default
implementation of NSEntityMigrationPolicy's createDestinationInstancesForSourceInstance:entityMapping:manager:error: method.*/
- (void)associateSourceInstance:(NSManagedObject *)sourceInstance withDestinationInstance:(NSManagedObject *)destinationInstance forEntityMapping:(NSEntityMapping *)entityMapping;

/* Returns the managed object instances created in the destination store for the given entity mapping for the specified source instances.*/
- (NSArray<__kindof NSManagedObject *> *)destinationInstancesForEntityMappingNamed:(NSString *)mappingName sourceInstances:(nullable NSArray<__kindof NSManagedObject *> *)sourceInstances;
 
/* Returns the managed object instances in the source store used to create the specified destination instances for the given entity mapping.*/
- (NSArray<__kindof NSManagedObject *> *)sourceInstancesForEntityMappingNamed:(NSString *)mappingName destinationInstances:(nullable NSArray<__kindof NSManagedObject *> *)destinationInstances;

/* Observable property that can be used to determine progress of the migration process.  Returns the current entity mapping being processed. Each entity is processed a total of three times (instance creation, relationship creation, validation)*/
@property (readonly, strong) NSEntityMapping *currentEntityMapping;

/* Observable property that can be used to determine progress of the migration process.  Returns the percentage complete of the migration process.  The progress value is a number from 0 to 1 indicating percent complete.*/
@property (readonly) float migrationProgress;

/* Returns/sets the user info for the migration manager*/
@property (nullable, nonatomic, strong) NSDictionary *userInfo;

/* Cancels the migration with the specified error. Calling this method causes migrateStoreFromURL:type:options:withMappingModel:toDestinationURL:destinationType:destinationOptions:error: to abort the migration and return the specified error.  */
- (void)cancelMigrationWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSAtomicStore.h
/*
    NSAtomicStore.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSError.h>
#import <Foundation/NSURL.h>
#import <CoreData/NSPersistentStore.h>
#import <CoreData/NSAtomicStoreCacheNode.h>
#import <CoreData/NSManagedObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentStoreCoordinator;
@class NSEntityDescription;
@class NSManagedObjectID;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSAtomicStore : NSPersistentStore {
}

// API method that may be overriden by subclasses for custom initialization
- (instancetype)initWithPersistentStoreCoordinator:(nullable NSPersistentStoreCoordinator *)coordinator configurationName:(nullable NSString *)configurationName URL:(NSURL *)url options:(nullable NSDictionary *)options;

// API method that must be overriden by subclasses
- (BOOL)load:(NSError **)error;

// API method that must be overriden by subclasses
- (BOOL)save:(NSError **)error;

// API method that must be overriden by subclasses
- (NSAtomicStoreCacheNode *)newCacheNodeForManagedObject:(NSManagedObject *)managedObject;

// API method that must be overriden by subclasses
- (void)updateCacheNode:(NSAtomicStoreCacheNode *)node fromManagedObject:(NSManagedObject *)managedObject;

// Utility method with implementation provided by NSAtomicStore
- (NSSet<__kindof NSAtomicStoreCacheNode *> *)cacheNodes;

// Utility method with implementation provided by NSAtomicStore
- (void)addCacheNodes:(NSSet<__kindof NSAtomicStoreCacheNode *> *)cacheNodes;

// Called before cache nodes are removed
- (void)willRemoveCacheNodes:(NSSet<__kindof NSAtomicStoreCacheNode *> *)cacheNodes;

// Utility method with implementation provided by NSAtomicStore
- (nullable NSAtomicStoreCacheNode *)cacheNodeForObjectID:(NSManagedObjectID *)objectID;

// Utility method with implementation provided by NSAtomicStore
- (NSManagedObjectID *)objectIDForEntity:(NSEntityDescription *)entity referenceObject:(id)data;

// This method MUST return a new unique primary key reference data for an instance of entity. This 
// primary key value MUST be an id

// API method that must be overriden by subclasses
- (id)newReferenceObjectForManagedObject:(NSManagedObject *)managedObject;

// Utility method with implementation provided by NSAtomicStore
- (id)referenceObjectForObjectID:(NSManagedObjectID *)objectID;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSFetchedResultsController.h
/*
    NSFetchedResultsController.h
    Core Data
    Copyright (c) 2009-2019, Apple Inc.
    All rights reserved.
*/

/*
 Class Overview
 ==============
 
 This class is intended to efficiently manage the results returned from a Core Data fetch request.
 
 You configure an instance of this class using a fetch request that specifies the entity, optionally a filter predicate, and an array containing at least one sort ordering. When you execute the fetch, the instance efficiently collects information about the results without the need to bring all the result objects into memory at the same time. As you access the results, objects are automatically faulted into memory in batches to match likely access patterns, and objects from previous accessed disposed of. This behavior further serves to keep memory requirements low, so even if you traverse a collection containing tens of thousands of objects, you should never have more than tens of them in memory at the same time.
 
 This class is tailored to work in conjunction with views that present collections of objects. These views typically expect their data source to present results as a list of sections made up of rows. NSFetchedResultsController can efficiently analyze the result of the fetch request and pre-compute all the information about sections in the result set. Moreover, the controller can cache the results of this computation so that if the same data is subsequently re-displayed, the work does not have to be repeated. In addition:
 * The controller monitors changes to objects in its associated managed object context, and updates the results accordingly. It reports changes in the results set to its delegate.
 * The controller automatically purges unneeded objects if it receives an application low memory notification.
 * The controller maintains a persistent cache of the section information across application launches if the cacheName is not nil.  If caching is enabled, you must not mutate the fetch request, its predicate, or its sort descriptor without first calling +deleteCacheWithName:
 
 Typical use
 ===========
 
	Developers create an instance of NSFetchedResultsController and configure it with a fetchRequest.  It is expected that the sort descriptor used in the request groups the results into sections. This allows for section information to be pre-computed.
	After creating an instance, the performFetch: method should be called to actually perform the fetching.
	Once started, convenience methods on the instance can be used for configuring the initial state of the view.

	The instance of NSFetchedResultsController also registers to receive change notifications on the managed object context that holds the fetched objects. Any change in the context that affects the result set or section information is properly processed. A delegate can be set on the class so that it's also notified when the result objects have changed. This would typically be used to update the display of the view.
	WARNING: The controller only performs change tracking if a delegate is set and responds to any of the change tracking notification methods.  See the NSFetchedResultsControllerDelegate protocol for which delegate methods are change tracking.
 
 Handling of Invalidated Objects
 ===============================
	
 When a managed object context notifies the NSFetchedResultsController of individual objects being invalidated (NSInvalidatedObjectsKey), the controller treats these as deleted objects and sends the proper delegate calls.
 It's possible for all the objects in a managed object context to be invalidated simultaneously. This can happen as a result of calling -reset on NSManagedObjectContext, or if a store is removed from the the NSPersistentStoreCoordinator. When this happens, NSFetchedResultsController currently does not invalidate all objects, nor does it send individual notifications for object deletions. Instead, developers must call performFetch: again to reset the state of the controller if all the objects in a context have been invalidated. They should also reset the state of their view.
 
 */

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSError.h>
#import <Foundation/NSIndexPath.h>
#import <Foundation/NSOrderedCollectionDifference.h>
#import <CoreData/NSManagedObjectContext.h>
#import <CoreData/NSManagedObject.h>
#import <CoreData/NSFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NSFetchedResultsControllerDelegate;
@protocol NSFetchedResultsSectionInfo;

@class NSDiffableDataSourceSnapshot<ItemIdentifierType, SectionIdentifierType>;

API_AVAILABLE(macosx(10.12),ios(3.0))
@interface NSFetchedResultsController<ResultType:id<NSFetchRequestResult>> : NSObject

/* ========================================================*/
/* ========================= INITIALIZERS ====================*/
/* ========================================================*/

/* Initializes an instance of NSFetchedResultsController
	fetchRequest - the fetch request used to get the objects. It's expected that the sort descriptor used in the request groups the objects into sections.
	context - the context that will hold the fetched objects
	sectionNameKeyPath - keypath on resulting objects that returns the section name. This will be used to pre-compute the section information.
	cacheName - Section info is cached persistently to a private file under this name. Cached sections are checked to see if the time stamp matches the store, but not if you have illegally mutated the readonly fetch request, predicate, or sort descriptor.
 */
- (instancetype)initWithFetchRequest:(NSFetchRequest<ResultType> *)fetchRequest managedObjectContext: (NSManagedObjectContext *)context sectionNameKeyPath:(nullable NSString *)sectionNameKeyPath cacheName:(nullable NSString *)name;

/* Executes the fetch request on the store to get objects.
    Returns YES if successful or NO (and an error) if a problem occurred. 
    An error is returned if the fetch request specified doesn't include a sort descriptor that uses sectionNameKeyPath.
    After executing this method, the fetched objects can be accessed with the property 'fetchedObjects'
*/
- (BOOL)performFetch:(NSError **)error;

/* ========================================================*/
/* ====================== CONFIGURATION ===================*/
/* ========================================================*/

/* NSFetchRequest instance used to do the fetching. You must not change it, its predicate, or its sort descriptor after initialization without disabling caching or calling +deleteCacheWithName.  The sort descriptor used in the request groups objects into sections. 
*/
@property(nonatomic,readonly) NSFetchRequest<ResultType> *fetchRequest;

/* Managed Object Context used to fetch objects. The controller registers to listen to change notifications on this context and properly update its result set and section information. 
*/
@property (nonatomic,readonly) NSManagedObjectContext *managedObjectContext;

/* The keyPath on the fetched objects used to determine the section they belong to. 
*/
@property (nonatomic,nullable, readonly) NSString *sectionNameKeyPath;

/* Name of the persistent cached section information. Use nil to disable persistent caching, or +deleteCacheWithName to clear a cache.
*/
@property (nonatomic,nullable, readonly) NSString *cacheName;

/* Delegate that is notified when the result set changes.
*/
@property(nullable, nonatomic, assign) id< NSFetchedResultsControllerDelegate > delegate;

/* Deletes the cached section information with the given name.
    If name is nil, then all caches are deleted.
*/
+ (void)deleteCacheWithName:(nullable NSString *)name;

/* ========================================================*/
/* ============= ACCESSING OBJECT RESULTS =================*/
/* ========================================================*/

/* Returns the results of the fetch.
    Returns nil if the performFetch: hasn't been called.
*/
@property  (nullable, nonatomic, readonly) NSArray<ResultType> *fetchedObjects;

/* Returns the fetched object at a given indexPath.
*/
- (ResultType)objectAtIndexPath:(NSIndexPath *)indexPath;

/* Returns the indexPath of a given object.
*/
-(nullable NSIndexPath *)indexPathForObject:(ResultType)object;

/* ========================================================*/
/* =========== CONFIGURING SECTION INFORMATION ============*/
/* ========================================================*/
/*	These are meant to be optionally overridden by developers.
*/

/* Returns the corresponding section index entry for a given section name.	
    Default implementation returns the capitalized first letter of the section name.
    Developers that need different behavior can implement the delegate method -(NSString*)controller:(NSFetchedResultsController *)controller sectionIndexTitleForSectionName
    Only needed if a section index is used.
*/
- (nullable NSString *)sectionIndexTitleForSectionName:(NSString *)sectionName;

/* Returns the array of section index titles.
    Default implementation returns the array created by calling sectionIndexTitleForSectionName: on all the known sections.
    Developers should override this method if they wish to return a different array for the section index.
    Only needed if a section index is used.
*/
@property (nonatomic, readonly) NSArray<NSString *> *sectionIndexTitles;

/* ========================================================*/
/* =========== QUERYING SECTION INFORMATION ===============*/
/* ========================================================*/

/* Returns an array of objects that implement the NSFetchedResultsSectionInfo protocol.
   This provide a convenience interface for determining the number of sections, the names and titles of the sections, and access to the model objects that belong to each section.
*/
@property (nullable, nonatomic, readonly) NSArray<id<NSFetchedResultsSectionInfo>> *sections;

/* Returns the section number for a given section title and index in the section index.
*/
- (NSInteger)sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)sectionIndex;

@end

// ================== PROTOCOLS ==================

@protocol NSFetchedResultsSectionInfo

/* Name of the section
*/
@property (nonatomic, readonly) NSString *name;

/* Title of the section (used when displaying the index)
*/
@property(nullable, nonatomic, readonly) NSString *indexTitle;

/* Number of objects in section
*/
@property (nonatomic, readonly) NSUInteger numberOfObjects;

/* Returns the array of objects in the section.
*/
@property (nullable, nonatomic, readonly) NSArray *objects;

@end // NSFetchedResultsSectionInfo


typedef NS_ENUM(NSUInteger, NSFetchedResultsChangeType) {
    NSFetchedResultsChangeInsert = 1,
    NSFetchedResultsChangeDelete = 2,
    NSFetchedResultsChangeMove = 3,
    NSFetchedResultsChangeUpdate = 4
} API_AVAILABLE(macosx(10.12), ios(3.0));


@protocol NSFetchedResultsControllerDelegate <NSObject>
@optional

#pragma mark -
#pragma mark ***** Snapshot Based Content Change Reporting *****

/* Called when the contents of the fetched results controller change.
 * If this method is implemented, no other delegate methods will be invoked.
 */
- (void)controller:(NSFetchedResultsController *)controller didChangeContentWithSnapshot:(NSDiffableDataSourceSnapshot<NSManagedObjectID *, NSString *> *)snapshot API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

#pragma mark -
#pragma mark ***** Difference Based Content Change Reporting *****

/* Called when the contents of the fetched results controller change.
 * If this method is implemented and the controller is configured with
 * sectionNameKeyPath = nil, no other delegate methods will be invoked.
 *
 * This method is only invoked if the controller's `sectionNameKeyPath`
 * property is nil and `controller:didChangeContentWithSnapshot:` is not
 * implemented.
 */
- (void)controller:(NSFetchedResultsController *)controller didChangeContentWithDifference:(NSOrderedCollectionDifference<NSManagedObjectID *> *)diff API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

#pragma mark -
#pragma mark ***** Legacy Content Change Reporting *****

/* Notifies the delegate that a fetched object has been changed due to an add, remove, move, or update. Enables NSFetchedResultsController change tracking.
	controller - controller instance that noticed the change on its fetched objects
	anObject - changed object
	indexPath - indexPath of changed object (nil for inserts)
	type - indicates if the change was an insert, delete, move, or update
	newIndexPath - the destination path of changed object (nil for deletes)
	
	Changes are reported with the following heuristics:

	Inserts and Deletes are reported when an object is created, destroyed, or changed in such a way that changes whether it matches the fetch request's predicate. Only the Inserted/Deleted object is reported; like inserting/deleting from an array, it's assumed that all objects that come after the affected object shift appropriately.
	Move is reported when an object changes in a manner that affects its position in the results.  An update of the object is assumed in this case, no separate update message is sent to the delegate.
	Update is reported when an object's state changes, and the changes do not affect the object's position in the results.
*/
@optional
- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(nullable NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type newIndexPath:(nullable NSIndexPath *)newIndexPath;

/* Notifies the delegate of added or removed sections.  Enables NSFetchedResultsController change tracking.

	controller - controller instance that noticed the change on its sections
	sectionInfo - changed section
	index - index of changed section
	type - indicates if the change was an insert or delete

	Changes on section info are reported before changes on fetchedObjects. 
*/
@optional
- (void)controller:(NSFetchedResultsController *)controller didChangeSection:(id <NSFetchedResultsSectionInfo>)sectionInfo atIndex:(NSUInteger)sectionIndex forChangeType:(NSFetchedResultsChangeType)type;

/* Notifies the delegate that section and object changes are about to be processed and notifications will be sent.  Enables NSFetchedResultsController change tracking.
   Clients may prepare for a batch of updates by using this method to begin an update block for their view.
*/
@optional
- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller;

/* Notifies the delegate that all section and object changes have been sent. Enables NSFetchedResultsController change tracking.
   Clients may prepare for a batch of updates by using this method to begin an update block for their view.
   Providing an empty implementation will enable change tracking if you do not care about the individual callbacks.
*/
@optional
- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller;

/* Asks the delegate to return the corresponding section index entry for a given section name.	Does not enable NSFetchedResultsController change tracking.
    If this method isn't implemented by the delegate, the default implementation returns the capitalized first letter of the section name (seee NSFetchedResultsController sectionIndexTitleForSectionName:)
    Only needed if a section index is used.
*/
@optional
- (nullable NSString *)controller:(NSFetchedResultsController *)controller sectionIndexTitleForSectionName:(NSString *)sectionName API_AVAILABLE(macosx(10.12),ios(4.0));

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSPersistentStoreDescription.h
/*
    NSPersistentStoreDescription.h
    Core Data
    Copyright (c) 2016-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSDate.h>

@class NSURL;

NS_ASSUME_NONNULL_BEGIN

// An instance of NSPersistentStoreDescription encapsulates all information needed to describe a persistent store.
API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0))
@interface NSPersistentStoreDescription : NSObject <NSCopying> {
}

+ (instancetype)persistentStoreDescriptionWithURL:(NSURL *)URL;

@property (copy) NSString *type;
@property (copy, nullable) NSString *configuration;
@property (copy, nullable) NSURL *URL;
@property (nonatomic, copy, readonly) NSDictionary<NSString *, NSObject *> *options;

- (void)setOption:(nullable NSObject *)option forKey:(NSString *)key;

// Store options
@property (getter = isReadOnly) BOOL readOnly;
@property NSTimeInterval timeout;
@property (nonatomic, copy, readonly) NSDictionary<NSString *, NSObject *> *sqlitePragmas;

- (void)setValue:(nullable NSObject *)value forPragmaNamed:(NSString *)name;

// addPersistentStore-time behaviours
@property BOOL shouldAddStoreAsynchronously;
@property BOOL shouldMigrateStoreAutomatically;
@property BOOL shouldInferMappingModelAutomatically;

// Returns a store description instance with default values for the store located at `URL` that can be used immediately with `addPersistentStoreWithDescription:completionHandler:`.
- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

@end

@class NSPersistentCloudKitContainerOptions;
@interface NSPersistentStoreDescription (NSPersistentCloudKitContainerAdditions)
/**
 Use this property to apply customized instances of NSPersistentCloudKitContainerOptions to
 a store description you wish to use with CloudKit.
 */
@property(strong, nullable) NSPersistentCloudKitContainerOptions *cloudKitContainerOptions API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));
@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSFetchRequestExpression.h
/*
    NSFetchRequestExpression.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSExpression.h>

NS_ASSUME_NONNULL_BEGIN

static const NSExpressionType NSFetchRequestExpressionType = (NSExpressionType)50;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSFetchRequestExpression : NSExpression {
}

/* Returns an expression which will evaluate to the result of executing a fetch request on a context.  The first argument must be an expression which evaluates to an NSFetchRequest *, and the second must be an expression which evaluates to an NSManagedObjectContext *.  If the desired result is simply the count for the request, the "countOnly" argument should be YES.
*/
+ (NSExpression*)expressionForFetch:(NSExpression*)fetch context:(NSExpression*)context countOnly:(BOOL)countFlag;


/* Returns the expression for the fetch request:  evaluating it must return an NSFetchRequest *.
*/
@property (readonly, strong) NSExpression *requestExpression;


/* Returns the expression for the managed object context:  evaluating it must return an NSManagedObjectContext *.
*/
@property (readonly, strong) NSExpression *contextExpression; 


/* Boolean indicating if the request will return object values or merely the count.  If the value returns NO, the managed object context (from the contextExpression) will perform executeFetchRequest:error: with the requestExpression;  if the value returns YES, the managed object context will perform countForFetchRequest:error with the requestExpression.
*/
@property (getter=isCountOnlyRequest, readonly) BOOL countOnlyRequest;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSEntityDescription.h
/*
    NSEntityDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSRange.h>

NS_ASSUME_NONNULL_BEGIN

@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSManagedObject;
@class NSData;
@class NSPropertyDescription;
@class NSRelationshipDescription;
@class NSAttributeDescription;
@class NSFetchIndexDescription;
@class NSExpression;

// Entities describe the "types" of objects available.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSEntityDescription : NSObject <NSCoding, NSCopying, NSFastEnumeration> {
}

+ (nullable NSEntityDescription *)entityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;
+ (__kindof NSManagedObject *)insertNewObjectForEntityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;

@property (readonly, assign) NSManagedObjectModel *managedObjectModel;
@property (null_resettable, copy) NSString *managedObjectClassName;

@property (nullable, copy) NSString *name;

@property (getter=isAbstract) BOOL abstract;
@property (readonly, copy) NSDictionary<NSString *, NSEntityDescription *> *subentitiesByName;
@property (strong) NSArray<NSEntityDescription *> *subentities;
@property (nullable, readonly, assign) NSEntityDescription *superentity;

@property (readonly, copy) NSDictionary<NSString *, __kindof NSPropertyDescription *> *propertiesByName;
@property (strong) NSArray<__kindof NSPropertyDescription *> *properties;

@property (nullable, nonatomic, strong) NSDictionary *userInfo;

// convenience methods to get the most common (and most relevant) types of properties for an entity
@property (readonly, copy) NSDictionary<NSString *, NSAttributeDescription *> *attributesByName;
@property (readonly, copy) NSDictionary<NSString *, NSRelationshipDescription *> *relationshipsByName;
- (NSArray<NSRelationshipDescription *> *)relationshipsWithDestinationEntity:(NSEntityDescription *)entity;

/* Returns a boolean indicating if the receiver is a subentity of the specified entity.  (This method is the Core Data entity inheritance equivalent of -isKindOfClass:)
*/
- (BOOL)isKindOfEntity:(NSEntityDescription *)entity API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns the version hash for the entity.  The version hash is used to uniquely identify an entity based on the collection and configuration of properties for the entity.  The version hash uses only values which affect the persistence of data and the user-defined versionHashModifier value.  (The values which affect persistence are the name of the entity, the version hash of the superentity (if present), if the entity is abstract, and all of the version hashes for the properties.)  This value is stored as part of the version information in the metadata for stores which use this entity, as well as a definition of an entity involved in an NSEntityMapping.
*/
@property (readonly, copy) NSData *versionHash API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns/sets the version hash modifier for the entity.  This value is included in the version hash for the entity, allowing developers to mark/denote an entity as being a different "version" than another, even if all of the values which affect persistence are equal.  (Such a difference is important in cases where the structure of an entity is unchanged, but the format or content of data has changed.)
*/
@property (nullable, copy) NSString *versionHashModifier API_AVAILABLE(macosx(10.5),ios(3.0));

@property (nullable, copy) NSString *renamingIdentifier API_AVAILABLE(macosx(10.6),ios(3.0));

/* Returns/sets the set of indexes for the entity. Returns/takes an array of NSFetchIndexDescription instances. This value does not form part of the entity's version hash, and may be ignored by stores which do not natively support indexing.
    IMPORTANT: Indexes should be the last things set in a model. Changing an entity hierarchy in any way that could affect the validity of indexes (adding or removing super/subentities, adding or removing properties anywhere in the hierarchy) will cause all exisiting indexes for entities in that hierarchy to be dropped.
 */
@property (copy) NSArray <NSFetchIndexDescription *>*indexes API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));


/* Returns/sets uniqueness constraints for the entity. A uniqueness constraint is a set of one or more attributes whose value must be unique over the set of instances of that entity.

    Sets an array of arrays, each of which contains one or more NSAttributeDescription or NSString instances (strings must be the names of attributes on the entity) on which the constraint is registered.
    Returns an array of arrays, each of which contains instances of NSString which identify the attributes on the entity that comprise the constraint.
    This value forms part of the entity's version hash. Stores which do not support uniqueness constraints should refuse to initialize when given a model containing such constraints.
    Discussion: uniqueness constraint violations can be computationally expensive to handle. It is highly suggested that there be only one uniqueness constraint per entity hierarchy,
    although subentites may extend a sueprentity's constraint.
*/
                                                                                                                                                                      
@property (strong)NSArray<NSArray<id> *> *uniquenessConstraints API_AVAILABLE(macosx(10.11),ios(9.0));

/*  Getter returns an array of arrays of NSPropertyDescription objects describing the components of the indexes.
    Setter takes an array of arrays of NSPropertyDescription objects and/or strings that are the names of properties of the entity on which the index is created. The special strings @"self" and @"entity" can be used to indicate that an index should contain a reference to the object's primary or entity key.
    This value does not form part of the entity's version hash, and may be ignored by stores which do not natively support compound indexes.
 */
@property (strong) NSArray<NSArray<id> *> *compoundIndexes API_DEPRECATED( "Use NSEntityDescription.indexes instead", macosx(10.5,10.13),ios(3.0,11.0),tvos(9.0, 11.0),watchos(2.0, 4.0));

/* Expression used to compute the CoreSpotlight display name for instance of this entity. */
@property (nonatomic, retain) NSExpression *coreSpotlightDisplayNameExpression API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSSaveChangesRequest.h
/*
    NSSaveChangesRequest.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <CoreData/NSPersistentStoreRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentStoreRequest;
@class NSManagedObject;

API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSSaveChangesRequest : NSPersistentStoreRequest {
}

// Default initializer.
- (instancetype)initWithInsertedObjects:(nullable NSSet<NSManagedObject *> *)insertedObjects updatedObjects:(nullable NSSet<NSManagedObject *> *)updatedObjects deletedObjects:(nullable NSSet<NSManagedObject *> *)deletedObjects lockedObjects:(nullable NSSet<NSManagedObject *> *)lockedObjects;

// Objects that were inserted into the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *insertedObjects;
// Objects that were modified in the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *updatedObjects;
// Objects that were deleted from the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *deletedObjects;
// Objects that were flagged for optimistic locking on the calling context via detectConflictsForObject:.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *lockedObjects;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentStoreRequest.h
/*
    NSPersistentStoreRequest.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentStore;

typedef NS_ENUM(NSUInteger, NSPersistentStoreRequestType) {
    NSFetchRequestType = 1,
    NSSaveRequestType,
    NSBatchUpdateRequestType API_AVAILABLE(macosx(10.10), ios(8.0)) = 6,
    NSBatchDeleteRequestType API_AVAILABLE(macosx(10.11), ios(9.0)) = 7
};

API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSPersistentStoreRequest : NSObject <NSCopying> {
}

// Stores this request should be sent to.
@property (nullable, nonatomic, strong) NSArray<NSPersistentStore *> *affectedStores;

// The type of the request.
@property (readonly) NSPersistentStoreRequestType requestType;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSIncrementalStoreNode.h
/*
    NSIncrementalStoreNode.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSManagedObjectID.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPropertyDescription;

// Provides the basic unit of external data that the Core Data stack interacts with.
API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSIncrementalStoreNode : NSObject {
}

// Returns an object initialized with the following values
// objectID -> The NSManagedObjectID corresponding to the object whose values are cached
//
// values -> A dictionary containing the values persisted in an external store with keys corresponding to the names of the NSPropertyDescriptions
//      in the NSEntityDescription described by the NSManagedObjectID.  Unknown or unmodeled keys will be stripped out.
//
//		For attributes: an immutable value (NSNumber, NSString, NSData etc).  Missing attribute keys will assume a nil value.
//
//		For to-one relationships: the NSManagedObjectID of the related object or NSNull for nil relationship values. A missing key will be resolved lazily through calling
//          -newValueForRelationship:forObjectWithID:withContext:error: on the NSPersistentStore.  Lazy resolution for to-ones is discouraged.
//
//      For to-many relationships: an NSArray or NSSet containing the NSManagedObjectIDs of the related objects.  Empty to-many relationships must
//          be represented by an empty non-nil collection.  A missing key will be resolved lazily through calling.  Lazy resolution for to-manys is encouraged.
//          -newValueForRelationship:forObjectWithID:withContext:error: on the NSPersistentStore
//
// version -> The revision number of this state; used for conflict detection and merging 
- (instancetype)initWithObjectID:(NSManagedObjectID*)objectID withValues:(NSDictionary<NSString *, id> *)values version:(uint64_t)version;

// Update the values and version to reflect new data being saved to or loaded from the external store.  
// The values dictionary is in the same format as the initializer
- (void)updateWithValues:(NSDictionary<NSString *, id> *)values version:(uint64_t)version;

// Return the object ID that identifies the data stored by this node
@property (nonatomic, readonly, strong) NSManagedObjectID *objectID;

// Return the version of data in this node.
@property (nonatomic, readonly) uint64_t version;

// May return NSNull for to-one relationships.  If a relationship is nil, clients should  invoke -newValueForRelationship:forObjectWithID:withContext:error: on the NSPersistentStore
- (nullable id)valueForPropertyDescription:(NSPropertyDescription*)prop;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSEntityMapping.h
/*
    NSEntityMapping.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSExpression.h>
#import <Foundation/NSData.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSPropertyMapping;

/*  mapping types */

typedef NS_ENUM(NSUInteger, NSEntityMappingType) {
    NSUndefinedEntityMappingType    = 0x00,
    NSCustomEntityMappingType       = 0x01,         /* developer handles destination instance creation */
    NSAddEntityMappingType          = 0x02,         /* new entity in destination */
    NSRemoveEntityMappingType	    = 0x03,         /* source instances aren't mapped to destination */
    NSCopyEntityMappingType         = 0x04,         /* migrate instances as-is */
    NSTransformEntityMappingType    = 0x05,         /* entity exists in source and destination and is mapped */
};

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSEntityMapping : NSObject {
}

/* Returns/sets the name of the mapping. The name is used only as a means of distinguishing mappings in a model.  If not specified, defaults to the string composed by the source entity name followed by the destination entity name (ex. SourceName->DestinationName)
*/
@property (null_resettable, copy) NSString *name;

/* Returns/sets the mapping type.  (If a custom entity mapping type is utilized, the developer must specify a migrationPolicyClassName as well.) 
*/
@property () NSEntityMappingType mappingType;

/* Returns/sets the source entity name for the mapping.  (Mappings are not directly bound to NSEntityDescriptions;  developers can use the sourceEntityForEntityMapping: API on the NSMigrationManager to retrieve the entity description for this name.)
*/
@property (nullable, copy) NSString *sourceEntityName;

/* Returns/sets the version hash for the source entity for the mapping.  VersionHashes are calculated by the Core Data framework (see NSEntityDescrition's versionHash method). The sourceEntityVersionHash must equal the version hash of the source entity represented by the mapping.
*/
@property (nullable, copy) NSData *sourceEntityVersionHash;

/* Returns/sets the destination entity name for the mapping.  (Mappings are not directly bound to NSEntityDescriptions;  developers can use the destinationEntityForEntityMapping: API on the NSMigrationManager to retrieve the entity description for this name.)
*/
@property (nullable, copy) NSString *destinationEntityName;

/* Returns/sets the version hash for the destination entity for the mapping.  VersionHashes are calculated by the Core Data framework (see NSEntityDescrition's versionHash method). The destinationEntityVersionHash must equal the version hash of the destination entity represented by the mapping.
*/
@property (nullable, copy) NSData *destinationEntityVersionHash;

/* Returns/sets the array of attribute mappings for the entity mapping.  The order of mappings in this collection dictates the order in which the mappings will be processed during a migration.
*/
@property (nullable, strong) NSArray<NSPropertyMapping *> *attributeMappings;

/* Returns/sets the array of relationship mappings for the entity mapping.  The order of mappings in this collection dictates the order in which the mappings will be processed during a migration.
*/
@property (nullable, strong) NSArray<NSPropertyMapping *> *relationshipMappings;

/* Returns/sets the source expression for the mapping.  The source expression is used to obtain the collection of managed object instances to process through the mapping.  The expression can be a fetch request expression, or any other expression which evaluates to a collection.  
*/
@property (nullable, strong) NSExpression *sourceExpression;

/* Returns/sets the user info dictionary for the mapping
*/
@property (nullable, nonatomic, strong) NSDictionary *userInfo;

/* Returns/sets the class name of the migration policy for the class.  If not specified, the default migration class name is NSEntityMigrationPolicy, though developers can specify a subclass for specific behavior.
*/
@property (nullable, copy) NSString *entityMigrationPolicyClassName;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSFetchedPropertyDescription.h
/*
    NSFetchedPropertyDescription.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFetchRequest;

// Fetched properties allow to specify related objects through a "weakly" resolved property, so there is no actual join necessary.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSFetchedPropertyDescription : NSPropertyDescription {
}

// As part of the predicate for a fetched property, you can use the two variables $FETCH_SOURCE (which is the managed object fetching the property) and $FETCHED_PROPERTY (which is the NSFetchedPropertyDescription instance).
@property (nullable, strong) NSFetchRequest *fetchRequest;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSManagedObjectModel.h
/*
    NSManagedObjectModel.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSFetchRequest;
@class NSData;
@class NSBundle;

// Models describe object graphs to be managed. Models (and their entities/properties/fetch request templates) are editable until they are used by a persistent store coordinator, allowing developers to create/modify them dynamically. However, once a model is being used, it MUST NOT be changed. When the persistent store coordinator first fetches data using a model, it will become uneditable. Any attempt to mutate a model or any of its subobjects after that point will cause an exception to be thrown. If you need to modify a model that is in use, create a copy, modify the copy, and then discard the objects with the old model.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSManagedObjectModel : NSObject <NSCoding, NSCopying, NSFastEnumeration> {
}

+ (nullable NSManagedObjectModel *)mergedModelFromBundles:(nullable NSArray<NSBundle *> *)bundles;  // looks up all models in the specified bundles and merges them; if nil is specified as argument, uses the main bundle

+ (nullable NSManagedObjectModel *)modelByMergingModels:(nullable NSArray<NSManagedObjectModel *> *)models;    // combines multiple models (typically from different frameworks) into one

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;

@property (readonly, copy) NSDictionary<NSString *, NSEntityDescription *> *entitiesByName;
@property (strong) NSArray<NSEntityDescription *> *entities;

@property (readonly, strong) NSArray<NSString *> *configurations;    // returns all available configuration names
- (nullable NSArray<NSEntityDescription *> *)entitiesForConfiguration:(nullable NSString *)configuration;
- (void)setEntities:(NSArray<NSEntityDescription *> *)entities forConfiguration:(NSString *)configuration;

// fetch request templates allow to pre-define queries and their parameters in the model (with the tool) - typically they contain variables that need to be substituted at runtime.
- (void)setFetchRequestTemplate:(nullable NSFetchRequest *)fetchRequestTemplate forName:(NSString *)name;
- (nullable NSFetchRequest *)fetchRequestTemplateForName:(NSString *)name;
- (nullable NSFetchRequest *)fetchRequestFromTemplateWithName:(NSString *)name substitutionVariables:(NSDictionary<NSString *, id> *)variables;    // returns a copy of the fetch request template with the variable bindings substituted - this is the usual way to bind an "abstractly" defined fetch request template to a concrete fetch

/*
 NSDictionary containing localized string values for entities, properties, and error strings related to this model. The key and value pattern follows:
 key = "Entity/NonLocalizedEntityName"
 value = "LocalizedEntityName"
 
 // for properties of the same non-localized name in differenct entities, which should have different localized names
 key = "Property/NonLocalizedPropertyName/Entity/EntityName" 
 value = "LocalizedPropertyName"
 
 key = "Property/NonLocalizedPropertyName"
 value = "LocalizedPropertyName"
 
 key = "ErrorString/NonLocalizedErrorString"
 value = "LocalizedErrorString"
 */
@property (nullable, strong) NSDictionary<NSString *, NSString *> *localizationDictionary;

/* Returns the managed object model used to create the store for the specified metadata.  This method is a companion to the mergedModelFromBundles: method;  in this case, the framework uses the version information stored in the metadata for a store to locate the models/entities used to create the store in the available bundles, and return the model.  If the model for the store cannot be found, this method will return nil.
*/
+ (nullable NSManagedObjectModel *)mergedModelFromBundles:(nullable NSArray<NSBundle *> *)bundles forStoreMetadata:(NSDictionary<NSString *, id> *)metadata API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns a merged model from the specified array for the version information in the provided metadata.  (This is the companion method to mergedModelFromBundles:forStoreMetadata:)  If a model cannot be created to match the version information in the specified metadata, this method will return nil.  
*/
+ (nullable NSManagedObjectModel *)modelByMergingModels:(NSArray<NSManagedObjectModel *> *)models forStoreMetadata:(NSDictionary<NSString *, id> *)metadata API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns the dictionary of fetch request templates, keyed by name, for the model.  If the template contains a predicate with substitution variables, you should instead use fetchRequestFromTemplateWithName:substitutionVariables: to create a new fetch request.
*/
@property (readonly, copy) NSDictionary<NSString *, NSFetchRequest *> *fetchRequestTemplatesByName API_AVAILABLE(macosx(10.5),ios(3.0));

/* Returns the collection of developer-defined version identifiers for the model.  For models created in Xcode, this value is set by the developer in the model inspector. Merged models return the combined  collection of identifiers. This value is meant to be used as a debugging hint to help developers determine the models that were combined to create a merged model. The framework does not give models a default identifier, nor does it depend this value at runtime.
*/
@property (copy) NSSet *versionIdentifiers API_AVAILABLE(macosx(10.5),ios(3.0));


/* Compares the version information in the store metadata with the entity version of a given configuration. Returns NO if there are differences between the version information.  (For information on specific differences, developers should utilize the entityVersionHashesByName method, and perform a comparison.)
*/
- (BOOL)isConfiguration:(nullable NSString *)configuration compatibleWithStoreMetadata:(NSDictionary<NSString *, id> *)metadata API_AVAILABLE(macosx(10.5),ios(3.0));


/* Returns a dictionary of the version hashes for the entities in the model, keyed by entity name.  (The dictionary of version hash information is used by Core Data to determine schema compatibility.)
*/
@property (readonly, copy) NSDictionary<NSString *, NSData *> *entityVersionHashesByName API_AVAILABLE(macosx(10.5),ios(3.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSMergePolicy.h
/*
    NSMergePolicy.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <CoreData/CoreDataDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSMergePolicy;
@class NSManagedObject;

// Default policy for all managed object contexts - save returns with an error that contains the object IDs of the objects that had conflicts(NSInsertedObjectsKey, NSUpdatedObjectsKey).
COREDATA_EXTERN id NSErrorMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the external changes trump the in memory ones.
COREDATA_EXTERN id NSMergeByPropertyStoreTrumpMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the in memory changes trump the external ones.
COREDATA_EXTERN id NSMergeByPropertyObjectTrumpMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy overwrites all state for the changed objects in conflict The current object's state is pushed upon the persistent store.
COREDATA_EXTERN id NSOverwriteMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy discards all state for the changed objects in conflict. The persistent store's version of the object is used.
COREDATA_EXTERN id NSRollbackMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    


typedef NS_ENUM(NSUInteger, NSMergePolicyType) {
    NSErrorMergePolicyType                      = 0x00,
    NSMergeByPropertyStoreTrumpMergePolicyType	= 0x01,
    NSMergeByPropertyObjectTrumpMergePolicyType = 0x02,
    NSOverwriteMergePolicyType                  = 0x03,
    NSRollbackMergePolicyType                   = 0x04
};

API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSMergeConflict : NSObject {
}

@property (readonly, retain) NSManagedObject* sourceObject;
@property (nullable, readonly, retain) NSDictionary<NSString *, id> * objectSnapshot;
@property (nullable, readonly, retain) NSDictionary<NSString *, id> * cachedSnapshot;
@property (nullable, readonly, retain) NSDictionary<NSString *, id> * persistedSnapshot;
@property (readonly) NSUInteger newVersionNumber;
@property (readonly) NSUInteger oldVersionNumber;

/*
 * There are two situations in which a conflict may occur:
 * 
 * 1. Between the NSManagedObjectContext and its in-memory cached state at the NSPersistentStoreCoordinator layer.
 *    In this case, the merge conflict has a source object and a cached snapshot but no persisted snapshot (persnap is nil).
 *
 * 2. Between the cached state at the NSPersistentStoreCoordinator and the external store (file, database, etc.).
 *    In this case, the merge conflict has a cached snapshot and a persisted snapshot.  The source object is also provided as a convenience,
 *    but it is not directly involved in the conflict.
 * 
 *  Snapshot dictionaries include values for all attributes and to-one relationships, but not to-many relationships.  
 *   Relationship values are NSManagedObjectID references. to-many relationships must be pulled from the persistent store as needed. 
 *
 *  A newVersion number of 0 means the object was deleted and the corresponding snapshot is nil.
 */
- (instancetype)initWithSource:(NSManagedObject*)srcObject newVersion:(NSUInteger)newvers oldVersion:(NSUInteger)oldvers cachedSnapshot:(nullable NSDictionary<NSString *, id> *)cachesnap persistedSnapshot:(nullable NSDictionary<NSString *, id>  *)persnap NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@end

/* Used to report merge conflicts which include uniqueness constraint violations. Optimistic locking failures will be reported
 separately from uniquness conflicts and will be resolved first. Each constraint violated will result in a separate NSMergeConflict,
 although if an entity hierarchy has a constraint which is extended in subentities, all constraint violations for that constraint
 will be collapsed into a single report.
 */
API_AVAILABLE(macosx(10.11),ios(9.0))
@interface NSConstraintConflict : NSObject {
}

@property (readonly, copy) NSArray <NSString *> *constraint; // The constraint which has been violated.
@property (readonly, copy) NSDictionary <NSString *, id> *constraintValues; // The values which the conflictingObjects had when this conflict was created. May no longer match the values of any conflicted object if something else resolved the conflict.
@property (nullable, readonly, retain) NSManagedObject *databaseObject; // Object whose DB row is using constraint values. May be null if this is a context-level violation.
@property (nullable, readonly, retain) NSDictionary<NSString *, id> *databaseSnapshot; // DB row already using constraint values. May be null if this is a context-level violation.
@property (readonly, copy) NSArray <NSManagedObject *> *conflictingObjects; // The objects in violation of the constraint. May contain one (in the case of a db level conflict) or more objects.
@property (readonly, copy) NSArray <NSDictionary *> *conflictingSnapshots; // The original property values of objects in violation of the constraint.  Will contain as many objects as there are conflictingObjects. If an object was unchanged, its snapshot will instead be -[NSNull null].

/*
 * There are two situations in which a constraint conflict may occur:
 *
 * 1. Between multiple objects being saved in a single managed object context. In this case, the conflict
 *      will have a nil database object/snapshot, and multiple conflicting objects/snapshots representing
 *      the state of the objects when they were first faulted or inserted into the context.
 *
 * 2. Between a single object being saved in a managed object context and the external store. In this case, the
 *      constraint conflict will have a database object, the current row snapshot for the database object, plus a
 *      a single conflicting object and its snapshot from when it was first faulted or inserted.
 *
 *  Snapshot dictionaries include values for all attributes and to-one relationships, but not to-many relationships.
 *   Relationship values are NSManagedObjectID references. to-many relationships must be pulled from the persistent store as needed.
 */
- (instancetype)initWithConstraint:(NSArray<NSString *> *)contraint databaseObject:(nullable NSManagedObject*)databaseObject databaseSnapshot:(nullable NSDictionary *)databaseSnapshot conflictingObjects:(NSArray<NSManagedObject *> *)conflictingObjects conflictingSnapshots:(NSArray  *)conflictingSnapshots NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(macosx(10.7),ios(5.0))
@interface NSMergePolicy : NSObject {
}

@property (class, readonly, strong) NSMergePolicy *errorMergePolicy API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));
@property (class, readonly, strong) NSMergePolicy *rollbackMergePolicy API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));
@property (class, readonly, strong) NSMergePolicy *overwriteMergePolicy API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));
@property (class, readonly, strong) NSMergePolicy *mergeByPropertyObjectTrumpMergePolicy API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));
@property (class, readonly, strong) NSMergePolicy *mergeByPropertyStoreTrumpMergePolicy API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

@property (readonly) NSMergePolicyType mergeType;

/*
 * In a subclass implementation of initWithMergeType:, you should invoke super with the NSMergePolicyType that is closest to the behavior you want.
 * This will make it easier to use the superclass's implementation of -resolveConflicts:error:, and then customize the results.  You are strongly encouraged to do so.
 * Due to the complexity of merging to-many relationships, this class is designed with the expectation that you call super as the base implemenation.
 */
- (id)initWithMergeType:(NSMergePolicyType)ty NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*
 * In a subclass, you are strongly encouraged to override initWithMergeType: and customize the results from calling super instead of performing your own actions from scratch.
 * Correctly merging to-many relationships is very challenging and any mistakes will cause permanent data corruption in the form of dangling foreign keys.
 * Calls -resolveOptimisticLockingVersionConflicts:error: and then -resolveConstraintConflicts:error:
 */
- (BOOL)resolveConflicts:(NSArray *)list error:(NSError **)error;

/* Resolve optimistic locking failures for the list of failures. In a subclass, you are strongly encouraged to override initWithMergeType: and customize 
 *  the results from calling super instead of performing your own actions from scratch. Correctly merging to-many relationships is very challenging and
 *  any mistakes will cause permanent data corruption in the form of dangling foreign keys.
 * Will be called before -resolveConstraintConflicts:error:
 */
- (BOOL)resolveOptimisticLockingVersionConflicts:(NSArray<NSMergeConflict *> *)list error:(NSError **)error API_AVAILABLE(macosx(10.11),ios(9.0));

/* Resolve uniqueness constraint violations for the list of failures.
 *  Will be called after -resolveOptimisticLockingVersionConflicts:error:
 */
- (BOOL)resolveConstraintConflicts:(NSArray<NSConstraintConflict *> *)list error:(NSError **)error API_AVAILABLE(macosx(10.11),ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSBatchUpdateRequest.h
/*
    NSBatchUpdateRequest.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSPredicate.h>
#import <Foundation/NSDictionary.h>

#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;

//  Used to request that Core Data do a batch update of data in a persistent store without
//  loading any data into memory. May not be supported by all store types.
//  WARNING:
//  It is up to the developer creating the request to ensure that changes made by the request to
//  the underlying store do not violate any validation rules specified in the model.
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSBatchUpdateRequest : NSPersistentStoreRequest {
}

+ (instancetype)batchUpdateRequestWithEntityName:(NSString*)entityName;

- (instancetype)initWithEntityName:(NSString *)entityName NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEntity:(NSEntityDescription *)entity NS_DESIGNATED_INITIALIZER;

@property (copy, readonly) NSString* entityName;
@property (strong, readonly) NSEntityDescription *entity;
@property (nullable, strong) NSPredicate *predicate;

// Should the update include subentities? Defaults to YES.
@property BOOL includesSubentities;

// The type of result that should be returned from this request. Defaults to NSStatusOnlyResultType
@property NSBatchUpdateRequestResultType resultType;

// Dictionary of NSPropertyDescription|property name string -> constantValue/NSExpression pairs describing the desired updates.
// The expressions can be any NSExpression that evaluates to a scalar value.
@property (nullable, copy) NSDictionary *propertiesToUpdate;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSManagedObject.h
/*
    NSManagedObject.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSKeyValueObserving.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEntityDescription;
@class NSError;
@class NSManagedObjectContext;
@class NSManagedObjectID;
@class NSFetchRequest;

typedef NS_OPTIONS(NSUInteger, NSSnapshotEventType) {
	NSSnapshotEventUndoInsertion = 1 << 1,
	NSSnapshotEventUndoDeletion = 1 << 2,
	NSSnapshotEventUndoUpdate = 1 << 3,
	NSSnapshotEventRollback = 1 << 4,
	NSSnapshotEventRefresh = 1 << 5,
	NSSnapshotEventMergePolicy = 1 << 6
};

API_AVAILABLE(macosx(10.4),ios(3.0)) NS_REQUIRES_PROPERTY_DEFINITIONS
@interface NSManagedObject : NSObject {
}

/*  Distinguish between changes that should and should not dirty the object for any key unknown to Core Data.  10.5 & earlier default to NO.  10.6 and later default to YES. */
/*    Similarly, transient attributes may be individually flagged as not dirtying the object by adding +(BOOL)contextShouldIgnoreChangesFor<key> where <key> is the property name. */
@property(class, readonly) BOOL contextShouldIgnoreUnmodeledPropertyChanges API_AVAILABLE(macosx(10.6),ios(3.0));

/* The Entity represented by this subclass. This method is only legal to call on subclasses of NSManagedObject that represent a single entity in the model.
 */
+ (NSEntityDescription*)entity API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* A new fetch request initialized with the Entity represented by this subclass. This property's getter is only legal to call on subclasses of NSManagedObject that represent a single entity in the model.
 */
+ (NSFetchRequest*)fetchRequest API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* The designated initializer. */
- (__kindof NSManagedObject*)initWithEntity:(NSEntityDescription *)entity insertIntoManagedObjectContext:(nullable NSManagedObjectContext *)context NS_DESIGNATED_INITIALIZER;

/* Returns a new object, inserted into managedObjectContext. This method is only legal to call on subclasses of NSManagedObject that represent a single entity in the model. 
 */
-(instancetype)initWithContext:(NSManagedObjectContext*)moc API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

// identity
@property (nullable, nonatomic, readonly, assign) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, readonly, strong) NSEntityDescription *entity;
@property (nonatomic, readonly, strong) NSManagedObjectID *objectID;

// state - methods
@property (nonatomic, getter=isInserted, readonly) BOOL inserted;
@property (nonatomic, getter=isUpdated, readonly) BOOL updated;
@property (nonatomic, getter=isDeleted, readonly) BOOL deleted;

@property (nonatomic, readonly) BOOL hasChanges API_AVAILABLE(macosx(10.7),ios(5.0));

/* returns YES if any persistent properties do not compare isEqual to their last saved state.  Relationship faults will not be unnecessarily fired.  This differs from the existing -hasChanges method which is a simple dirty flag and also includes transient properties */
@property (nonatomic, readonly) BOOL hasPersistentChangedValues API_AVAILABLE(macosx(10.9),ios(7.0));

// this information is useful in many situations when computations are optional - this can be used to avoid growing the object graph unnecessarily (which allows to control performance as it can avoid time consuming fetches from databases)
@property (nonatomic, getter=isFault, readonly) BOOL fault;    

// returns a Boolean indicating if the relationship for the specified key is a fault.  If a value of NO is returned, the resulting relationship is a realized object;  otherwise the relationship is a fault.  If the specified relationship is a fault, calling this method does not result in the fault firing.
- (BOOL)hasFaultForRelationshipNamed:(NSString *)key API_AVAILABLE(macosx(10.5),ios(3.0)); 

/* returns an array of objectIDs for the contents of a relationship.  to-one relationships will return an NSArray with a single NSManagedObjectID.  Optional relationships may return an empty NSArray.  The objectIDs will be returned in an NSArray regardless of the type of the relationship.  */
- (NSArray<NSManagedObjectID *> *)objectIDsForRelationshipNamed:(NSString *)key API_AVAILABLE(macosx(10.11),ios(8.3));

/* Allow developers to determine if an object is in a transitional phase when receiving a KVO notification.  Returns 0 if the object is fully initialized as a managed object and not transitioning to or from another state */
@property (nonatomic, readonly) NSUInteger faultingState API_AVAILABLE(macosx(10.5),ios(3.0));

// lifecycle/change management (includes key-value observing methods)
- (void)willAccessValueForKey:(nullable NSString *)key; // read notification
- (void)didAccessValueForKey:(nullable NSString *)key;           // read notification (together with willAccessValueForKey used to maintain inverse relationships, to fire faults, etc.) - each read access has to be wrapped in this method pair (in the same way as each write access has to be wrapped in the KVO method pair)

// KVO change notification
- (void)willChangeValueForKey:(NSString *)key;
- (void)didChangeValueForKey:(NSString *)key;
- (void)willChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;
- (void)didChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;

// invoked after a fetch or after unfaulting (commonly used for computing derived values from the persisted properties)
- (void)awakeFromFetch;    

// invoked after an insert (commonly used for initializing special default/initial settings)
- (void)awakeFromInsert;

/* Callback for undo, redo, and other multi-property state resets */
- (void)awakeFromSnapshotEvents:(NSSnapshotEventType)flags API_AVAILABLE(macosx(10.6),ios(3.0));

/* Callback before delete propagation while the object is still alive.  Useful to perform custom propagation before the relationships are torn down or reconfigure KVO observers. */
- (void)prepareForDeletion API_AVAILABLE(macosx(10.6),ios(3.0));

// commonly used to compute persisted values from other transient/scratchpad values, to set timestamps, etc. - this method can have "side effects" on the persisted values
- (void)willSave;    

// commonly used to notify other objects after a save
- (void)didSave;    

// invoked automatically by the Core Data framework before receiver is converted (back) to a fault.  This method is the companion of the -didTurnIntoFault method, and may be used to (re)set state which requires access to property values (for example, observers across keypaths.)  The default implementation does nothing.  
- (void)willTurnIntoFault API_AVAILABLE(macosx(10.5),ios(3.0));

// commonly used to clear out additional transient values or caches
- (void)didTurnIntoFault;    

// value access (includes key-value coding methods)

// KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (nullable id)valueForKey:(NSString *)key;    

// KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (void)setValue:(nullable id)value forKey:(NSString *)key;    

// primitive methods give access to the generic dictionary storage from subclasses that implement explicit accessors like -setName/-name to add custom document logic
- (nullable id)primitiveValueForKey:(NSString *)key;    
- (void)setPrimitiveValue:(nullable id)value forKey:(NSString *)key;

// returns a dictionary of the last fetched or saved keys and values of this object.  Pass nil to get all persistent modeled properties.
- (NSDictionary<NSString *, id> *)committedValuesForKeys:(nullable NSArray<NSString *> *)keys;

// returns a dictionary with the keys and (new) values that have been changed since last fetching or saving the object (this is implemented efficiently without firing relationship faults)
- (NSDictionary<NSString *, id> *)changedValues;

- (NSDictionary<NSString *, id> *)changedValuesForCurrentEvent API_AVAILABLE(macosx(10.7),ios(5.0));

// validation - in addition to KVC validation managed objects have hooks to validate their lifecycle state; validation is a critical piece of functionality and the following methods are likely the most commonly overridden methods in custom subclasses
- (BOOL)validateValue:(id _Nullable * _Nonnull)value forKey:(NSString *)key error:(NSError **)error;    // KVC
- (BOOL)validateForDelete:(NSError **)error;
- (BOOL)validateForInsert:(NSError **)error;
- (BOOL)validateForUpdate:(NSError **)error;

    
@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentContainer.h
/*
    NSPersistentContainer.h
    Core Data
    Copyright (c) 2016-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <CoreData/NSManagedObjectContext.h>
#import <CoreData/NSPersistentStoreCoordinator.h>
#import <CoreData/NSManagedObjectModel.h>
#import <CoreData/NSPersistentStoreDescription.h>

@class NSURL;

NS_ASSUME_NONNULL_BEGIN

// An instance of NSPersistentContainer includes all objects needed to represent a functioning Core Data stack, and provides convenience methods and properties for common patterns.
API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0))
@interface NSPersistentContainer : NSObject {
}

+ (instancetype)persistentContainerWithName:(NSString *)name;
+ (instancetype)persistentContainerWithName:(NSString *)name managedObjectModel:(NSManagedObjectModel *)model;

+ (NSURL *)defaultDirectoryURL;

@property (copy, readonly) NSString *name;
@property (strong, readonly) NSManagedObjectContext *viewContext;
@property (strong, readonly) NSManagedObjectModel *managedObjectModel;
@property (strong, readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (copy) NSArray<NSPersistentStoreDescription *> *persistentStoreDescriptions;

// Creates a container using the model named `name` in the main bundle
- (instancetype)initWithName:(NSString *)name;

- (instancetype)initWithName:(NSString *)name managedObjectModel:(NSManagedObjectModel *)model NS_DESIGNATED_INITIALIZER;

// Load stores from the storeDescriptions property that have not already been successfully added to the container. The completion handler is called once for each store that succeeds or fails.
- (void)loadPersistentStoresWithCompletionHandler:(void (^)(NSPersistentStoreDescription *, NSError * _Nullable))block;

- (NSManagedObjectContext *)newBackgroundContext NS_RETURNS_RETAINED;
- (void)performBackgroundTask:(void (^)(NSManagedObjectContext *))block;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSManagedObjectID.h
/*
    NSManagedObjectID.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentStore;
@class NSEntityDescription;
@class NSURL;

// Managed object IDs are opaque identifiers for managed objects.
API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSManagedObjectID : NSObject <NSCopying> {
}

@property (readonly, strong) NSEntityDescription *entity;    // entity for the object identified by an ID
@property (nullable, readonly, weak) NSPersistentStore *persistentStore;    // persistent store that fetched the object identified by an ID

@property (getter=isTemporaryID, readonly) BOOL temporaryID;    // indicates whether or not this ID will be replaced later, such as after a save operation (temporary IDs are assigned to newly inserted objects and replaced with permanent IDs when an object is written to a persistent store); most IDs return NO

- (NSURL *)URIRepresentation;    // URI which provides an archivable reference to the object which this ID refers

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSManagedObjectContext.h
/*
    NSManagedObjectContext.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSLock.h>
#import <CoreData/CoreDataDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSError;
@class NSFetchRequest;
@class NSPersistentStoreRequest;
@class NSPersistentStoreResult;
@class NSManagedObject;
@class NSManagedObjectID;
@class NSPersistentStore;
@class NSPersistentStoreCoordinator;
@class NSPropertyDescription;
@class NSQueryGenerationToken;
@class NSUndoManager;
@class NSNotification;

// Notifications immediately before and immediately after the context saves.  The user info dictionary contains information about the objects that changed and what changed
COREDATA_EXTERN NSString * const NSManagedObjectContextWillSaveNotification API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSManagedObjectContextDidSaveNotification API_AVAILABLE(macosx(10.4),ios(3.0));

// Notification when objects in a context changed:  the user info dictionary contains information about the objects that changed and what changed
COREDATA_EXTERN NSString * const NSManagedObjectContextObjectsDidChangeNotification API_AVAILABLE(macosx(10.4),ios(3.0));    

// User info keys for NSManagedObjectContextObjectsDidChangeNotification:  the values for these keys are sets of managed objects
COREDATA_EXTERN NSString * const NSInsertedObjectsKey API_AVAILABLE(macosx(10.4),ios(3.0));
COREDATA_EXTERN NSString * const NSUpdatedObjectsKey API_AVAILABLE(macosx(10.4),ios(3.0));
COREDATA_EXTERN NSString * const NSDeletedObjectsKey API_AVAILABLE(macosx(10.4),ios(3.0));

COREDATA_EXTERN NSString * const NSRefreshedObjectsKey API_AVAILABLE(macosx(10.5),ios(3.0));
COREDATA_EXTERN NSString * const NSInvalidatedObjectsKey API_AVAILABLE(macosx(10.5),ios(3.0));

COREDATA_EXTERN NSString * const NSManagedObjectContextQueryGenerationKey API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

// User info keys for NSManagedObjectContextObjectsDidChangeNotification:  the values for these keys are arrays of objectIDs
COREDATA_EXTERN NSString * const NSInvalidatedAllObjectsKey API_AVAILABLE(macosx(10.5),ios(3.0)); // All objects in the context have been invalidated

// Default policy for all managed object contexts - save returns with an error that contains the object IDs of the objects that had conflicts(NSInsertedObjectsKey, NSUpdatedObjectsKey).
COREDATA_EXTERN id NSErrorMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the external changes trump the in memory ones.
COREDATA_EXTERN id NSMergeByPropertyStoreTrumpMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the in memory changes trump the external ones.
COREDATA_EXTERN id NSMergeByPropertyObjectTrumpMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy overwrites all state for the changed objects in conflict The current object's state is pushed upon the persistent store.
COREDATA_EXTERN id NSOverwriteMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

// This singleton policy discards all state for the changed objects in conflict. The persistent store's version of the object is used.
COREDATA_EXTERN id NSRollbackMergePolicy API_AVAILABLE(macosx(10.4),ios(3.0));    

typedef NS_ENUM(NSUInteger, NSManagedObjectContextConcurrencyType) {
    NSConfinementConcurrencyType API_DEPRECATED( "Use another NSManagedObjectContextConcurrencyType", macosx(10.4,10.11), ios(3.0,9.0)) = 0x00,
    NSPrivateQueueConcurrencyType		= 0x01,
    NSMainQueueConcurrencyType			= 0x02
} API_AVAILABLE(macosx(10.7), ios(5.0));

API_AVAILABLE(macosx(10.4),ios(3.0))
@interface NSManagedObjectContext : NSObject <NSCoding, NSLocking> {
}

+ (instancetype)new API_DEPRECATED( "Use -initWithConcurrencyType: instead", macosx(10.4,10.11), ios(3.0,9.0));
- (instancetype)init API_DEPRECATED( "Use -initWithConcurrencyType: instead", macosx(10.4,10.11), ios(3.0,9.0));
- (instancetype)initWithConcurrencyType:(NSManagedObjectContextConcurrencyType)ct NS_DESIGNATED_INITIALIZER  API_AVAILABLE(macosx(10.7),ios(5.0));

/* asynchronously performs the block on the context's queue.  Encapsulates an autorelease pool and a call to processPendingChanges */
- (void)performBlock:(void (^)(void))block API_AVAILABLE(macosx(10.7),ios(5.0));

/* synchronously performs the block on the context's queue.  May safely be called reentrantly.  */
- (void)performBlockAndWait:(void (NS_NOESCAPE ^)(void))block API_AVAILABLE(macosx(10.7),ios(5.0));

/* coordinator which provides model and handles persistency (multiple contexts can share a coordinator) */
@property (nullable, strong) NSPersistentStoreCoordinator *persistentStoreCoordinator;

@property (nullable, strong) NSManagedObjectContext *parentContext API_AVAILABLE(macosx(10.7),ios(5.0));

/* custom label for a context.  NSPrivateQueueConcurrencyType contexts will set the label on their queue */
@property (nullable, copy) NSString *name API_AVAILABLE(macosx(10.10),ios(8.0));

@property (nullable, nonatomic, strong) NSUndoManager *undoManager;

@property (nonatomic, readonly) BOOL hasChanges;
@property (nonatomic, readonly, strong) NSMutableDictionary *userInfo API_AVAILABLE(macosx(10.7),ios(5.0));
@property (readonly) NSManagedObjectContextConcurrencyType concurrencyType API_AVAILABLE(macosx(10.7),ios(5.0));

/* returns the object for the specified ID if it is registered in the context already or nil. It never performs I/O. */
- (nullable __kindof NSManagedObject *)objectRegisteredForID:(NSManagedObjectID *)objectID;

/* returns the object for the specified ID if it is already registered, otherwise it creates a fault corresponding to that objectID.  It never returns nil, and never performs I/O.  The object specified by objectID is assumed to exist, and if that assumption is wrong the fault may throw an exception when used. */
- (__kindof NSManagedObject *)objectWithID:(NSManagedObjectID *)objectID;

/* returns the object for the specified ID if it is already registered in the context, or faults the object into the context.  It might perform I/O if the data is uncached.  If the object cannot be fetched, or does not exist, or cannot be faulted, it returns nil.  Unlike -objectWithID: it never returns a fault.  */
- (nullable __kindof NSManagedObject*)existingObjectWithID:(NSManagedObjectID*)objectID error:(NSError**)error API_AVAILABLE(macosx(10.6),ios(3.0));

// method to fetch objects from the persistent stores into the context (fetch request defines the entity and predicate as well as a sort order for the objects); context will match the results from persistent stores with current changes in the context (so inserted objects are returned even if they are not persisted yet); to fetch a single object with an ID if it is not guaranteed to exist and thus -objectWithObjectID: cannot be used, one would create a predicate like [NSComparisonPredicate predicateWithLeftExpression:[NSExpression expressionForKeyPath:@"objectID"] rightExpression:[NSExpression expressionForConstantValue:<object id>] modifier:NSPredicateModifierDirect type:NSEqualToPredicateOperatorType options:0]
- (nullable NSArray *)executeFetchRequest:(NSFetchRequest *)request error:(NSError **)error;

// returns the number of objects a fetch request would have returned if it had been passed to -executeFetchRequest:error:.   If an error occurred during the processing of the request, this method will return NSNotFound. 
- (NSUInteger) countForFetchRequest: (NSFetchRequest *)request error: (NSError **)error API_AVAILABLE(macosx(10.5),ios(3.0)) __attribute__((swift_error(nonnull_error)));

// Method to pass a request to the store without affecting the contents of the managed object context.
// Will return an NSPersistentStoreResult which may contain additional information about the result of the action
// (ie a batch update result may contain the object IDs of the objects that were modified during the update).
// A request may succeed in some stores and fail in others. In this case, the error will contain information
// about each individual store failure.
// Will always reject NSSaveChangesRequests.
- (nullable __kindof NSPersistentStoreResult *)executeRequest:(NSPersistentStoreRequest*)request error:(NSError **)error API_AVAILABLE(macosx(10.10),ios(8.0));

- (void)insertObject:(NSManagedObject *)object;
- (void)deleteObject:(NSManagedObject *)object;

// if flag is YES, merges an object with the state of the object available in the persistent store coordinator; if flag is NO, simply refaults an object without merging (which also causes other related managed objects to be released, so you can use this method to trim the portion of your object graph you want to hold in memory) 
- (void)refreshObject:(NSManagedObject *)object mergeChanges:(BOOL)flag;    

// marks an object for conflict detection, which means that the save fails if the object has been altered in the persistent store by another application.  This allows optimistic locking for unchanged objects.  Conflict detection is always performed on changed or deleted objects.
- (void)detectConflictsForObject:(NSManagedObject *)object;    

// key-value observation
- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable id)object change:(nullable NSDictionary<NSString *, id> *)change context:(nullable void *)context;

// usually contexts process changes to the object graph coalesced at the end of the event - this method triggers it explicitly
- (void)processPendingChanges;    

// specifies the store a newly inserted object will be saved in.  Unnecessary unless there are multiple writable persistent stores added to the NSPersistentStoreCoordinator which support this object's entity.
- (void)assignObject:(id)object toPersistentStore:(NSPersistentStore *)store;    

@property (nonatomic, readonly, strong) NSSet<__kindof NSManagedObject *> *insertedObjects;
@property (nonatomic, readonly, strong) NSSet<__kindof NSManagedObject *> *updatedObjects;
@property (nonatomic, readonly, strong) NSSet<__kindof NSManagedObject *> *deletedObjects;
@property (nonatomic, readonly, strong) NSSet<__kindof NSManagedObject *> *registeredObjects;

- (void)undo;
- (void)redo;
- (void)reset;
- (void)rollback;
- (BOOL)save:(NSError **)error;

/* calls -refreshObject:mergeChanges: on all currently registered objects with this context.  It handles dirtied objects and clearing the context reference queue */
- (void)refreshAllObjects API_AVAILABLE(macosx(10.11),ios(8.3));

- (void)lock API_DEPRECATED( "Use a queue style context and -performBlockAndWait: instead", macosx(10.4,10.10), ios(3.0,8.0));
- (void)unlock API_DEPRECATED( "Use a queue style context and -performBlockAndWait: instead", macosx(10.4,10.10), ios(3.0,8.0));
- (BOOL)tryLock API_DEPRECATED( "Use a queue style context and -performBlock: instead", macosx(10.4,10.10), ios(3.0,8.0));
    
// whether or not the context propagates deletes to related objects at the end of the event, or only at save time
@property (nonatomic) BOOL propagatesDeletesAtEndOfEvent;   // The default is YES.

// whether or not the context holds a retain on all registered objects, or only upon objects necessary for a pending save (inserted, updated, deleted, or locked)
@property (nonatomic) BOOL retainsRegisteredObjects;   // The default is NO.

/*  set the rule to handle inaccessible faults.  If YES, then the managed object is marked deleted and all its properties, including scalars, nonnullable, and mandatory properties, will be nil or zero’d out.  If NO, the context will throw an exception. Managed objects that are inaccessible because their context is nil due to memory management issues will throw an exception regardless. */
@property BOOL shouldDeleteInaccessibleFaults API_AVAILABLE(macosx(10.11),ios(9.0));

/*  this method will not be called from APIs which return an NSError like -existingObjectWithID:error: nor for managed objects with a nil context (e.g. the fault is inaccessible because the object or its context have been released) this method will not be called if Core Data determines there is an unambiguously correct action to recover.  This might happen if a fault was tripped during delete propagation.  In that case, the fault will simply be deleted.  triggeringProperty may be nil when either all properties are involved, or Core Data is unable to determine the reason for firing the fault. the default implementation logs and then returns the value of -shouldDeleteInaccessibleFaults. */
- (BOOL)shouldHandleInaccessibleFault:(NSManagedObject*)fault forObjectID:(NSManagedObjectID*)oid triggeredByProperty:(nullable NSPropertyDescription*)property API_AVAILABLE(macosx(10.11),ios(9.0));

// Staleness interval is the relative time until cached data should be considered stale. The value is applied on a per object basis. For example, a value of 300.0 informs the context to utilize cached information for no more than 5 minutes after that object was originally fetched. This does not affect objects currently in use. Principly, this controls whether fulfilling a fault uses data previously fetched by the application, or issues a new fetch.  It is a hint which may not be supported by all persistent store types.
@property () NSTimeInterval stalenessInterval; // a negative value is considered infinite.  The default is infinite staleness.
 // acceptable merge policies are listed above as id constants
@property (strong) id mergePolicy;    // default: NSErrorMergePolicy

/* Converts the object IDs of the specified objects to permanent IDs.  This implementation will convert the object ID of each managed object in the specified array to a permanent ID.  Any object in the target array with a permanent ID will be ignored;  additionally, any managed object in the array not already assigned to a store will be assigned, based on the same rules Core Data uses for assignment during a save operation (first writable store supporting the entity, and appropriate for the instance and its related items.)  Although the object will have a permanent ID, it will still respond positively to -isInserted until it is saved.  If an error is encountered obtaining an identifier, the return value will be NO.
*/
- (BOOL)obtainPermanentIDsForObjects:(NSArray<NSManagedObject *> *)objects error:(NSError **)error API_AVAILABLE(macosx(10.5),ios(3.0));

/* Merges the changes specified in notification object received from another context's NSManagedObjectContextDidSaveNotification into the receiver.  This method will refresh any objects which have been updated in the other context, fault in any newly inserted objects, and invoke deleteObject: on those which have been deleted.  The developer is only responsible for the thread safety of the receiver.
*/
- (void)mergeChangesFromContextDidSaveNotification:(NSNotification *)notification API_AVAILABLE(macosx(10.5),ios(3.0));

/* Similar to mergeChangesFromContextDidSaveNotification, this method handles changes from potentially other processes or serialized state.  It more efficiently
 * merges changes into multiple contexts, as well as nested context. The keys in the dictionary should be one those from an
 *  NSManagedObjectContextObjectsDidChangeNotification: NSInsertedObjectsKey, NSUpdatedObjectsKey, etc.
 *  the values should be an NSArray of either NSManagedObjectID or NSURL objects conforming to valid results from -URIRepresentation
 */
+ (void)mergeChangesFromRemoteContextSave:(NSDictionary*)changeNotificationData intoContexts:(NSArray<NSManagedObjectContext*> *)contexts API_AVAILABLE(macosx(10.11),ios(9.0));

/* Return the query generation currently in use by this context. Will be one of the following:
 * - nil, default value => this context is not using generational querying
 * - an opaque token => specifies the generation of data this context is vending
 *
 * All child contexts will return nil.
 */
@property (nullable, nonatomic, strong, readonly) NSQueryGenerationToken *queryGenerationToken API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* Set the query generation this context should use. Must be one of the following values:
 * - nil => this context will not use generational querying
 * - the value returned by +[NSQueryGenerationToken currentQueryGenerationToken] => this context will pin itself to the generation of the database when it first loads data
 * - the result of calling -[NSManagedObjectContext queryGenerationToken] on another managed object context => this context will be set to whatever query generation the original context is currently using;
 *
 * Query generations are for fetched data only; they are not used during saving. If a pinned context saves,
 * its query generation will be updated after the save. Executing a NSBatchUpdateRequest or NSBatchDeleteRequest 
 * will not cause the query generation to advance, since these do not otherwise consider or affect the 
 * managed object context's content.
 *
 * All nested contexts will defer to their parent context’s data. It is a programmer error to try to set
 * the queryGenerationToken on a child context.
 *
 * Query generations are tracked across the union of stores. Additions to the persistent store coordinator's
 * persistent stores will be ignored until the context's query generation is updated to include them.
 *
 * May partially fail if one or more stores being tracked by the token are removed from the persistent
 * store coordinator.
 */
- (BOOL)setQueryGenerationFromToken:(nullable NSQueryGenerationToken *)generation error:(NSError **)error API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* Whether the context automatically merges changes saved to its coordinator or parent context. Setting this property to YES when the context is pinned to a non-current query generation is not supported.
 */
@property (nonatomic) BOOL automaticallyMergesChangesFromParent API_AVAILABLE(macosx(10.12),ios(10.0),tvos(10.0),watchos(3.0));

/* Set the author for the context, this will be used as an identifier in the Persistent History Transactions (NSPersistentHistoryTransaction)
 */
@property (nullable, copy) NSString *transactionAuthor API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSMappingModel.h
/*
    NSMappingModel.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN

@class NSBundle;
@class NSError;
@class NSManagedObjectModel;
@class NSEntityMapping;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSMappingModel: NSObject {
}

/* Returns the mapping model to translate data from the source to the destination model.  This method is a companion to the mergedModelFromBundles: methods;  in this case, the framework uses the version information from the models to locate the appropriate mapping model in the available bundles.  If the mapping model for the models cannot be found, this method returns nil. 
*/
+ (nullable NSMappingModel *)mappingModelFromBundles:(nullable NSArray<NSBundle *> *)bundles forSourceModel:(nullable NSManagedObjectModel *)sourceModel destinationModel:(nullable NSManagedObjectModel *)destinationModel;

/* Returns a newly created mapping model to translate data from the source to the destination model, if possible.  The differences between the source and destination model are compared and if all changes are simple enough to be able to reasonably infer a data migration mapping model, such a model is created and returned.  If the mapping model can not be created, nil is returned and an error code is returned to indicate why inferring a mapping model automatically failed.
 */
+ (nullable NSMappingModel *)inferredMappingModelForSourceModel:(NSManagedObjectModel *)sourceModel destinationModel:(NSManagedObjectModel *)destinationModel error:(NSError **)error API_AVAILABLE(macosx(10.6),ios(3.0));

/* Loads the mapping model from the specified URL.
*/
- (nullable instancetype)initWithContentsOfURL:(nullable NSURL *)url;


/* Returns/sets the collection of entity mappings for the model.  The order of the mappings dictates the order in which they will be processed during migration.
*/
@property (null_resettable, strong) NSArray<NSEntityMapping *> *entityMappings;


/* Returns a dictionary of the entity mappings for the model, keyed by their respective name.  (This API is provided for quick access to a mapping by name, rather than iterating the ordered entityMapping array.)
*/
@property (readonly, copy) NSDictionary<NSString *, NSEntityMapping *> *entityMappingsByName;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSDerivedAttributeDescription.h
/*
    NSDerivedAttributeDescription.h
    Core Data
    Copyright (c) 2018-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSAttributeDescription.h>

@class NSExpression;
@class NSPredicate;

NS_ASSUME_NONNULL_BEGIN

/* Class that describes an attribute whose value should be derived from one or more
 other properties and how that derivation should be done.
 This is primarily intended to optimize fetch performance. Some use cases:
 * creating a derived 'searchName' attribute that reflects a 'name' attribute with
 case and diacritics stripped for more efficient comparisons during fetching
 * creating a 'relationshipCount' attribute reflecting the number of objects in
 a relationship and so avoid having to do a join during fetching
 
 IMPORTANT: Derived attributes will be recomputed during save, so unsaved changes
 will not be reflected in a managed object's property until after a save+refresh. */

API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSDerivedAttributeDescription : NSAttributeDescription

/* Instance of NSExpression that will be used to generate the derived data.
 When using derived attributes in an SQL store, this expression should be
 * a keypath expression (including @operation components)
 * a function expression using one of the predefined functions defined
 in NSExpression.h
 Any keypaths used in the expression must be accessible from the entity on which
 the derived attribute is specified.
 If a store is added to a coordinator whose model contains derived attributes of
 a type not supported by the store, the add will fail and an NSError will be returned. */
@property (strong, nullable) NSExpression *derivationExpression;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/CoreDataErrors.h
/*
    CoreDataErrors.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

/* NSError codes for Core Data added errors in NSCocoaErrorDomain. Foundation error codes can be found in <Foundation/FoundationErrors.h>. AppKit error codes can be found in <AppKit/AppKitErrors.h>.
*/

#import <CoreData/CoreDataDefines.h>

NS_ASSUME_NONNULL_BEGIN

// User info keys for errors created by Core Data:
COREDATA_EXTERN NSString * const NSDetailedErrorsKey API_AVAILABLE(macosx(10.4),ios(3.0));           // if multiple validation errors occur in one operation, they are collected in an array and added with this key to the "top-level error" of the operation

COREDATA_EXTERN NSString * const NSValidationObjectErrorKey API_AVAILABLE(macosx(10.4),ios(3.0));    // object that failed to validate for a validation error
COREDATA_EXTERN NSString * const NSValidationKeyErrorKey API_AVAILABLE(macosx(10.4),ios(3.0));       // key that failed to validate for a validation error
COREDATA_EXTERN NSString * const NSValidationPredicateErrorKey API_AVAILABLE(macosx(10.4),ios(3.0)); // for predicate-based validation, the predicate for the condition that failed to validate
COREDATA_EXTERN NSString * const NSValidationValueErrorKey API_AVAILABLE(macosx(10.4),ios(3.0));     // if non-nil, the value for the key that failed to validate for a validation error

COREDATA_EXTERN NSString * const NSAffectedStoresErrorKey API_AVAILABLE(macosx(10.4),ios(3.0));      // stores prompting an error
COREDATA_EXTERN NSString * const NSAffectedObjectsErrorKey API_AVAILABLE(macosx(10.4),ios(3.0));     // objects prompting an error

COREDATA_EXTERN NSString * const NSPersistentStoreSaveConflictsErrorKey API_AVAILABLE(macosx(10.7),ios(5.0));     // key in NSError's userInfo specifying the NSArray of NSMergeConflict

COREDATA_EXTERN NSString * const NSSQLiteErrorDomain API_AVAILABLE(macosx(10.5),ios(3.0));           // Predefined domain for SQLite errors, value of "code" will correspond to preexisting values in SQLite.

enum : NSInteger {
    NSManagedObjectValidationError                   = 1550,   // generic validation error
    NSManagedObjectConstraintValidationError         = 1551,   // one or more uniqueness constraints were violated
    NSValidationMultipleErrorsError                  = 1560,   // generic message for error containing multiple validation errors
    NSValidationMissingMandatoryPropertyError        = 1570,   // non-optional property with a nil value
    NSValidationRelationshipLacksMinimumCountError   = 1580,   // to-many relationship with too few destination objects
    NSValidationRelationshipExceedsMaximumCountError = 1590,   // bounded, to-many relationship with too many destination objects
    NSValidationRelationshipDeniedDeleteError        = 1600,   // some relationship with NSDeleteRuleDeny is non-empty
    NSValidationNumberTooLargeError                  = 1610,   // some numerical value is too large
    NSValidationNumberTooSmallError                  = 1620,   // some numerical value is too small
    NSValidationDateTooLateError                     = 1630,   // some date value is too late
    NSValidationDateTooSoonError                     = 1640,   // some date value is too soon
    NSValidationInvalidDateError                     = 1650,   // some date value fails to match date pattern
    NSValidationStringTooLongError                   = 1660,   // some string value is too long
    NSValidationStringTooShortError                  = 1670,   // some string value is too short
    NSValidationStringPatternMatchingError           = 1680,   // some string value fails to match some pattern
    NSValidationInvalidURIError                      = 1690,   // some URI value cannot be represented as a string
    
    NSManagedObjectContextLockingError               = 132000, // can't acquire a lock in a managed object context
    NSPersistentStoreCoordinatorLockingError         = 132010, // can't acquire a lock in a persistent store coordinator
    
    NSManagedObjectReferentialIntegrityError         = 133000, // attempt to fire a fault pointing to an object that does not exist (we can see the store, we can't see the object)
    NSManagedObjectExternalRelationshipError         = 133010, // an object being saved has a relationship containing an object from another store
    NSManagedObjectMergeError                        = 133020, // merge policy failed - unable to complete merging
    NSManagedObjectConstraintMergeError              = 133021, // merge policy failed - unable to complete merging due to multiple conflicting constraint violations
    
    NSPersistentStoreInvalidTypeError                = 134000, // unknown persistent store type/format/version
    NSPersistentStoreTypeMismatchError               = 134010, // returned by persistent store coordinator if a store is accessed that does not match the specified type
    NSPersistentStoreIncompatibleSchemaError         = 134020, // store returned an error for save operation (database level errors ie missing table, no permissions)
    NSPersistentStoreSaveError                       = 134030, // unclassified save error - something we depend on returned an error
    NSPersistentStoreIncompleteSaveError             = 134040, // one or more of the stores returned an error during save (stores/objects that failed will be in userInfo)
	NSPersistentStoreSaveConflictsError				 = 134050, // an unresolved merge conflict was encountered during a save.  userInfo has NSPersistentStoreSaveConflictsErrorKey

    NSCoreDataError                                  = 134060, // general Core Data error
    NSPersistentStoreOperationError                  = 134070, // the persistent store operation failed 
    NSPersistentStoreOpenError                       = 134080, // an error occurred while attempting to open the persistent store
    NSPersistentStoreTimeoutError                    = 134090, // failed to connect to the persistent store within the specified timeout (see NSPersistentStoreTimeoutOption)
	NSPersistentStoreUnsupportedRequestTypeError	 = 134091, // an NSPersistentStore subclass was passed an NSPersistentStoreRequest that it did not understand
    
    NSPersistentStoreIncompatibleVersionHashError    = 134100, // entity version hashes incompatible with data model
    NSMigrationError                                 = 134110, // general migration error
    NSMigrationConstraintViolationError              = 134111, // migration failed due to a violated uniqueness constraint
    NSMigrationCancelledError                        = 134120, // migration failed due to manual cancellation
    NSMigrationMissingSourceModelError               = 134130, // migration failed due to missing source data model
    NSMigrationMissingMappingModelError              = 134140, // migration failed due to missing mapping model
    NSMigrationManagerSourceStoreError               = 134150, // migration failed due to a problem with the source data store
    NSMigrationManagerDestinationStoreError          = 134160, // migration failed due to a problem with the destination data store
    NSEntityMigrationPolicyError                     = 134170, // migration failed during processing of the entity migration policy 

    NSSQLiteError                                    = 134180,  // general SQLite error 

    NSInferredMappingModelError                      = 134190, // inferred mapping model creation error
    NSExternalRecordImportError                      = 134200, // general error encountered while importing external records
    
    NSPersistentHistoryTokenExpiredError             = 134301  // The history token passed to NSPersistentChangeRequest was invalid
};

NS_ASSUME_NONNULL_END
// ==========  CoreData.framework/Headers/NSPersistentCloudKitContainer.h
/*
    NSPersistentCloudKitContainer.h
    Core Data
    Copyright (c) 2018-2019, Apple Inc.
    All rights reserved.
*/



#import <CoreData/NSPersistentContainer.h>

NS_ASSUME_NONNULL_BEGIN

/*
 NSPersistentCloudKitContainer managed one or more persistent stores that are backed by a CloudKit private database.
 
 By default, NSPersistentContainer contains a single store description which, if not customized otherwise, is assigned
 to the first CloudKit container identifier in an application's entitlements.
 
 Instances of NSPersistentCloudKitContainerOptions can be used to customize this behavior or create additional instances of
 NSPersistentStoreDescription backed by different containers.
 
 As NSPersistentCloudKitContainer is a subclass of NSPersistentContainer, it can manage both CloudKit backed and non-cloud stores.
 */
@class CKRecord;
@class CKRecordID;
API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSPersistentCloudKitContainer : NSPersistentContainer

/**
 These methods provide access to the underlying CKRecord, or CKRecordID, backing a given NSManagedObjectID.
 */
- (nullable CKRecord *)recordForManagedObjectID:(NSManagedObjectID *)managedObjectID;
- (NSDictionary<NSManagedObjectID *, CKRecord *> *)recordsForManagedObjectIDs:(NSArray<NSManagedObjectID *> *)managedObjectIDs;
- (nullable CKRecordID *)recordIDForManagedObjectID:(NSManagedObjectID *)managedObjectID;
- (NSDictionary<NSManagedObjectID *, CKRecordID *> *)recordIDsForManagedObjectIDs:(NSArray<NSManagedObjectID *> *)managedObjectIDs;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreData.framework/Headers/NSPropertyMapping.h
/*
    NSPropertyMapping.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>


NS_ASSUME_NONNULL_BEGIN

@class NSExpression;

API_AVAILABLE(macosx(10.5),ios(3.0))
@interface NSPropertyMapping : NSObject {
}

/* Returns/sets the name of the property in the destination entity for the mapping.  
*/
@property (nullable, copy) NSString *name;

/* Returns/sets the value expression for the property mapping.  The expression is used to create the value for the destination property.
*/
@property (nullable, strong) NSExpression *valueExpression;

/* Returns/sets the user info for the property mapping.
*/
@property (nullable, strong) NSDictionary *userInfo;

@end

NS_ASSUME_NONNULL_END
