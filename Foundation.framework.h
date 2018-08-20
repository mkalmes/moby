// ==========  Foundation.framework/Headers/NSPredicate.h
/*	NSPredicate.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSOrderedSet.h>

@class NSDictionary <KeyType, ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

// Predicates wrap some combination of expressions and operators and when evaluated return a BOOL.

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSPredicate : NSObject <NSSecureCoding, NSCopying> {
    struct _predicateFlags {
        unsigned int _evaluationBlocked:1;
        unsigned int _reservedPredicateFlags:31;
    } _predicateFlags;
#ifdef __LP64__
    uint32_t reserved;
#endif
}

// Parse predicateFormat and return an appropriate predicate
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat argumentArray:(nullable NSArray *)arguments;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat, ...;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat arguments:(va_list)argList;

+ (nullable NSPredicate *)predicateFromMetadataQueryString:(NSString *)queryString NS_AVAILABLE_MAC(10_9);

+ (NSPredicate *)predicateWithValue:(BOOL)value;    // return predicates that always evaluate to true/false

+ (NSPredicate*)predicateWithBlock:(BOOL (^)(id evaluatedObject, NSDictionary<NSString *, id> * __nullable bindings))block NS_AVAILABLE(10_6, 4_0);

@property (readonly, copy) NSString *predicateFormat;    // returns the format string of the predicate

- (instancetype)predicateWithSubstitutionVariables:(NSDictionary<NSString *, id> *)variables;    // substitute constant values for variables

- (BOOL)evaluateWithObject:(nullable id)object;    // evaluate a predicate against a single object

- (BOOL)evaluateWithObject:(nullable id)object substitutionVariables:(nullable NSDictionary<NSString *, id> *)bindings NS_AVAILABLE(10_5, 3_0); // single pass evaluation substituting variables from the bindings dictionary for any variable expressions encountered

- (void)allowEvaluation NS_AVAILABLE(10_9, 7_0); // Force a predicate which was securely decoded to allow evaluation

@end

@interface NSArray<ObjectType> (NSPredicateSupport)
- (NSArray<ObjectType> *)filteredArrayUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and return a filtered array
@end

@interface NSMutableArray<ObjectType> (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and filter the mutable array directly
@end


@interface NSSet<ObjectType> (NSPredicateSupport)
- (NSSet<ObjectType> *)filteredSetUsingPredicate:(NSPredicate *)predicate NS_AVAILABLE(10_5, 3_0);    // evaluate a predicate against a set of objects and return a filtered set
@end

@interface NSMutableSet<ObjectType> (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate NS_AVAILABLE(10_5, 3_0);    // evaluate a predicate against a set of objects and filter the mutable set directly
@end

@interface NSOrderedSet<ObjectType> (NSPredicateSupport)

- (NSOrderedSet<ObjectType> *)filteredOrderedSetUsingPredicate:(NSPredicate *)p NS_AVAILABLE(10_7, 5_0);    // evaluate a predicate against an ordered set of objects and return a filtered ordered set

@end

@interface NSMutableOrderedSet<ObjectType> (NSPredicateSupport)

- (void)filterUsingPredicate:(NSPredicate *)p NS_AVAILABLE(10_7, 5_0);  // evaluate a predicate against an ordered set of objects and filter the mutable ordered set directly

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSLocale.h
/*	NSLocale.h
	Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreFoundation/CFLocale.h>

@class NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSString;

// Toll-free bridged with CFLocaleRef

NS_ASSUME_NONNULL_BEGIN

@interface NSLocale : NSObject <NSCopying, NSSecureCoding>

- (nullable id)objectForKey:(id)key;

- (nullable NSString *)displayNameForKey:(id)key value:(id)value;

- (instancetype)initWithLocaleIdentifier:(NSString *)string NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSLocale (NSExtendedLocale)

@property (readonly, copy) NSString *localeIdentifier;  // same as NSLocaleIdentifier

@end

@interface NSLocale (NSLocaleCreation)

+ (NSLocale *)autoupdatingCurrentLocale NS_AVAILABLE(10_5, 2_0); // generally you should use this method

+ (NSLocale *)currentLocale;	// an object representing the user's current locale
+ (NSLocale *)systemLocale;	// the default generic root locale with little localization

+ (instancetype)localeWithLocaleIdentifier:(NSString *)ident NS_AVAILABLE(10_6, 4_0);

- (instancetype)init NS_UNAVAILABLE;     /* do not invoke; not a valid initializer for this class */

@end

@interface NSLocale (NSLocaleGeneralInfo)

+ (NSArray<NSString *> *)availableLocaleIdentifiers;
+ (NSArray<NSString *> *)ISOLanguageCodes;
+ (NSArray<NSString *> *)ISOCountryCodes;
+ (NSArray<NSString *> *)ISOCurrencyCodes;
+ (NSArray<NSString *> *)commonISOCurrencyCodes NS_AVAILABLE(10_5, 2_0);

+ (NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_5, 2_0); // note that this list does not indicate what language the app is actually running in; the [NSBundle mainBundle] object determines that at launch and knows that information

+ (NSDictionary<NSString *, NSString *> *)componentsFromLocaleIdentifier:(NSString *)string;
+ (NSString *)localeIdentifierFromComponents:(NSDictionary<NSString *, NSString *> *)dict;

+ (NSString *)canonicalLocaleIdentifierFromString:(NSString *)string;
+ (NSString *)canonicalLanguageIdentifierFromString:(NSString *)string;

+ (nullable NSString *)localeIdentifierFromWindowsLocaleCode:(uint32_t)lcid NS_AVAILABLE(10_6, 4_0);
+ (uint32_t)windowsLocaleCodeFromLocaleIdentifier:(NSString *)localeIdentifier NS_AVAILABLE(10_6, 4_0);

typedef NS_ENUM(NSUInteger, NSLocaleLanguageDirection) {
    NSLocaleLanguageDirectionUnknown = kCFLocaleLanguageDirectionUnknown,
    NSLocaleLanguageDirectionLeftToRight = kCFLocaleLanguageDirectionLeftToRight,
    NSLocaleLanguageDirectionRightToLeft = kCFLocaleLanguageDirectionRightToLeft,
    NSLocaleLanguageDirectionTopToBottom = kCFLocaleLanguageDirectionTopToBottom,
    NSLocaleLanguageDirectionBottomToTop = kCFLocaleLanguageDirectionBottomToTop
};

+ (NSLocaleLanguageDirection)characterDirectionForLanguage:(NSString *)isoLangCode NS_AVAILABLE(10_6, 4_0);
+ (NSLocaleLanguageDirection)lineDirectionForLanguage:(NSString *)isoLangCode NS_AVAILABLE(10_6, 4_0);

@end


FOUNDATION_EXPORT NSString * const NSCurrentLocaleDidChangeNotification NS_AVAILABLE(10_5, 2_0);


FOUNDATION_EXPORT NSString * const NSLocaleIdentifier;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleLanguageCode;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCountryCode;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleScriptCode;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleVariantCode;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleExemplarCharacterSet;// NSCharacterSet
FOUNDATION_EXPORT NSString * const NSLocaleCalendar;		// NSCalendar
FOUNDATION_EXPORT NSString * const NSLocaleCollationIdentifier; // NSString
FOUNDATION_EXPORT NSString * const NSLocaleUsesMetricSystem;	// NSNumber boolean
FOUNDATION_EXPORT NSString * const NSLocaleMeasurementSystem;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleDecimalSeparator;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleGroupingSeparator;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCurrencySymbol;      // NSString
FOUNDATION_EXPORT NSString * const NSLocaleCurrencyCode;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCollatorIdentifier NS_AVAILABLE(10_6, 4_0);  // NSString
FOUNDATION_EXPORT NSString * const NSLocaleQuotationBeginDelimiterKey NS_AVAILABLE(10_6, 4_0);	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleQuotationEndDelimiterKey NS_AVAILABLE(10_6, 4_0);	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleAlternateQuotationBeginDelimiterKey NS_AVAILABLE(10_6, 4_0);	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleAlternateQuotationEndDelimiterKey NS_AVAILABLE(10_6, 4_0);	// NSString


#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

// Values for NSCalendar identifiers (not the NSLocaleCalendar property key)
FOUNDATION_EXPORT NSString * const NSGregorianCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierGregorian instead");
FOUNDATION_EXPORT NSString * const NSBuddhistCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierBuddhist instead");
FOUNDATION_EXPORT NSString * const NSChineseCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierChinese instead");
FOUNDATION_EXPORT NSString * const NSHebrewCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierHebrew instead");
FOUNDATION_EXPORT NSString * const NSIslamicCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierIslamic instead");
FOUNDATION_EXPORT NSString * const NSIslamicCivilCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierIslamicCivil instead");
FOUNDATION_EXPORT NSString * const NSJapaneseCalendar NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarIdentifierJapanese instead");
FOUNDATION_EXPORT NSString * const NSRepublicOfChinaCalendar NS_CALENDAR_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarIdentifierRepublicOfChina instead");
FOUNDATION_EXPORT NSString * const NSPersianCalendar NS_CALENDAR_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarIdentifierPersian instead");
FOUNDATION_EXPORT NSString * const NSIndianCalendar NS_CALENDAR_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarIdentifierIndian instead");
FOUNDATION_EXPORT NSString * const NSISO8601Calendar NS_CALENDAR_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarIdentifierISO8601 instead");

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSLock.h
/*	NSLock.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_ASSUME_NONNULL_BEGIN

@protocol NSLocking

- (void)lock;
- (void)unlock;

@end

@interface NSLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (BOOL)tryLock;
- (BOOL)lockBeforeDate:(NSDate *)limit;

@property (nullable, copy) NSString *name NS_AVAILABLE(10_5, 2_0);

@end

@interface NSConditionLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (instancetype)initWithCondition:(NSInteger)condition NS_DESIGNATED_INITIALIZER;

@property (readonly) NSInteger condition;
- (void)lockWhenCondition:(NSInteger)condition;
- (BOOL)tryLock;
- (BOOL)tryLockWhenCondition:(NSInteger)condition;
- (void)unlockWithCondition:(NSInteger)condition;
- (BOOL)lockBeforeDate:(NSDate *)limit;
- (BOOL)lockWhenCondition:(NSInteger)condition beforeDate:(NSDate *)limit;

@property (nullable, copy) NSString *name NS_AVAILABLE(10_5, 2_0);

@end

@interface NSRecursiveLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (BOOL)tryLock;
- (BOOL)lockBeforeDate:(NSDate *)limit;

@property (nullable, copy) NSString *name NS_AVAILABLE(10_5, 2_0);

@end



NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSCondition : NSObject <NSLocking> {
@private
    void *_priv;
}

- (void)wait;
- (BOOL)waitUntilDate:(NSDate *)limit;
- (void)signal;
- (void)broadcast;

@property (nullable, copy) NSString *name NS_AVAILABLE(10_5, 2_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSFileVersion.h
/*
	NSFileVersion.h
	Copyright (c) 2010-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSDate, NSDictionary, NSError, NSString, NSURL;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSFileVersionAddingOptions) {

    /* Whether +addVersionOfItemAtURL:withContentsOfURL:options:error: can move the new version contents file into the version store instead of copying it. Moving is much faster. See the comment for -temporaryDirectoryURLForNewVersionOfItemAtURL: for an example of when this useful.
    */
    NSFileVersionAddingByMoving = 1 << 0

};

typedef NS_OPTIONS(NSUInteger, NSFileVersionReplacingOptions) {

    /* Whether -replaceItemAtURL:options:error: must move the version's contents out of the version store instead of copying it. This is useful when you want to promote a version's contents to a separate file. You wouldn't use this to restore a version of a file.
    */
    NSFileVersionReplacingByMoving = 1 << 0

};

/* Instances of NSFileVersion for the same version of the same file are equal, and instances of NSFileVersion for different versions of the same file are not equal, but the equality of NSFileVersions for different files is undefined. Repeated invocations of the methods that return NSFileVersions do not necessarily return the exact same instance of NSFileVersion.
*/
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSFileVersion : NSObject {
@private
    NSURL *_fileURL;
    id _addition;
    id _deadVersionIdentifier;
    id _nonLocalVersion;
    NSURL *_contentsURL;
    BOOL _isBackup;
    NSString *_localizedName;
    NSString *_localizedComputerName;
    NSDate *_modificationDate;
    BOOL _isResolved;
    BOOL _contentsURLIsAccessed;
    id _reserved;
    NSString *_name;
}

/* Return an NSFileVersion that represents the contents of the file located by a URL, or nil if there is no such file.
*/
+ (nullable NSFileVersion *)currentVersionOfItemAtURL:(NSURL *)url;

/* Return an array of NSFileVersions associated with the file located by a URL, or nil if there is no such file. The array never contains an NSFileVersion equal to what +currentVersionOfItemAtURL: would return.
*/
+ (nullable NSArray<NSFileVersion *> *)otherVersionsOfItemAtURL:(NSURL *)url;

/* Return an array of NSFileVersions that represent unresolved conflicts for the file located by a URL, or nil if there is no such file.
*/
+ (nullable NSArray<NSFileVersion *> *)unresolvedConflictVersionsOfItemAtURL:(NSURL *)url;

/* Asynchronously return an array of NSFileVersions associated with the file located by the given URL, or nil if there is no such file or another error occurs. Versions returned by this method do not initially have their contents stored locally on the device, so a download may be required before you are able to access them. File attributes are accessible via -[NSURL getPromisedItemResourceValue:forKey:error:]. You can request a download by performing a coordinated read with NSFileCoordinator on the URL property of the resulting NSFileVersions.
 
When a version is successfully downloaded, its contents are cached locally, and the version will no longer be returned by this method. The version will be returned by +[NSFileVersion otherVersionsOfItemAtURL:] instead, but will retain the same persistentIdentifier value. If the local version is later discarded, future invocations of this method may resume returning the version.
 
If you need to get all versions for a document, both local and non-local, you should use an NSFilePresenter that implements -presentedItemDidGainVersion: and -presentedItemDidLoseVersion: and invoke +[NSFileCoordinator addFilePresenter:], +[NSFileVersion otherVersionsOfItemAtURL:], and this method within a single coordinated read.
*/
+ (void)getNonlocalVersionsOfItemAtURL:(NSURL *)url completionHandler:(void (^)(NSArray<NSFileVersion *> * __nullable nonlocalFileVersions, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/* For a file located by a URL, return the NSFileVersion identified by a persistent identifier of the sort returned by -persistentIdentifier, or nil if the version no longer exists.
*/
+ (nullable NSFileVersion *)versionOfItemAtURL:(NSURL *)url forPersistentIdentifier:(id)persistentIdentifier;

/* Add a new version of the file located by a URL, with the contents coming from a file located by either the same or a different URL, and return a new instance that represents the version if successful. If not successful, return NO after setting *outError to an NSError that encapsulates why not.

You can add versions only on Mac OS X.

When adding or removing versions of a file you should do it as part of a "coordinated" write to the file. The NSFileCoordinator class that you use to do coordinated file access is declared in <Foundation/NSFileCoordinator.h>. Using it properly ensures that NSFilePresenters of the file, or directories that contain the file, receive accurate notifications about versions being added or removed. NSFilePresenter is declared in <Foundation/NSFilePresenter.h>. For example, use -[NSFileCoordinator coordinateWritingItemAtURL:options:error:byAccessor:] when the file URL and the contents url are the same. (NSFileVersion doesn't simply use NSFileCoordinator itself because that would be insufficient when the adding or removing of versions is part of a larger operation that should be treated as one coordinated file access.)
*/
+ (nullable NSFileVersion *)addVersionOfItemAtURL:(NSURL *)url withContentsOfURL:(NSURL *)contentsURL options:(NSFileVersionAddingOptions)options error:(NSError **)outError NS_AVAILABLE_MAC(10_7);

/* Given a URL, create a new directory that is suitable for using as the container of a new temporary file that you will create and use with NSFileVersionAddingByMoving. This is useful when you want to create a new version of a file out of something other than the file's current contents, for example, the contents in memory of a document that has not yet been saved to its file. You must remove this directory when you are done with it, using -[NSFileManager removeItemAtURL:error:] for example.
*/
+ (NSURL *)temporaryDirectoryURLForNewVersionOfItemAtURL:(NSURL *)url NS_AVAILABLE_MAC(10_7);

/* The location of the receiver's storage, or possibly nil if the receiver's storage has been deleted. The storage is read-only. The URL will have an arcane path. You must not derive user-presentable text from it.
*/
@property (readonly, copy) NSURL *URL;

/* The user-presentable name of the version, or possibly nil if the receiver's storage has been deleted. This will be different from the user-presentable name of the versioned file if, for example, the file has been renamed since the version was added.
*/
@property (nullable, readonly, copy) NSString *localizedName;

/* The user-presentable name of the computer on which the version was saved, or possibly nil if the receiver's storage has been deleted, or nil if no computer name was recorded. The computer name is guaranteed to have been recorded only if the version is a conflict version. This will be different from that computer's current name if the computer's name has been changed since the version was retrieved from that computer.
*/
@property (nullable, readonly, copy) NSString *localizedNameOfSavingComputer;

/* The modification date of the version, or possibly nil if the receiver's storage has been deleted.
*/
@property (nullable, readonly, copy) NSDate *modificationDate;

/* An object that can be encoded and, after subsequent decoding, passed to -versionOfItemAtURL:forPersistentIdentifier: to create a new instance of NSFileVersion that is equal to the receiver.
*/
@property (readonly, retain) id<NSCoding> persistentIdentifier;

/* Whether the version was created as a result of the discovery of a conflict between two writers of the versioned file.
*/
@property (readonly, getter=isConflict) BOOL conflict;

/* If the version is a conflict version, whether the conflict has been resolved. If the version is not a conflict version, simply YES.

The operating system's reaction to your setting this to YES is complicated and subject to change in future releases. One result however is that the version won't appear in arrays returned by +unresolvedConflictVersionsOfItemAtURL: anymore, unless setting fails.

Once you have indicated that a conflict has been resolved you cannot make it unresolved again. Setting this to NO causes an exception to be thrown.
*/
@property (getter=isResolved) BOOL resolved;

/* Whether the system is allowed to automatically delete the receiver's storage in the future, at an unpredictable time.

Setting this to YES can fail so you must not depend on discarding for correct operation.

Once you have indicated that a version is discardable you cannot make it undiscardable again. Setting this to NO causes an exception to be thrown.

You cannot make the versioned file itself discardable. Setting the value of this property always throws an exception when sent to the result of invoking +currentVersionOfItemAtURL:.

Versions can be discardable only on Mac OS X.
*/
@property (getter=isDiscardable) BOOL discardable NS_AVAILABLE_MAC(10_7);

/* Whether the version has local contents. Versions that are returned by +getNonlocalVersionsOfItemAtURL:completionHandler: do not initially have local contents. You can only access their contents, either directly via the URL or by invoking -replaceItemAtURL:options:error:, from within a coordinated read on the NSFileVersion's URL.
*/
@property (readonly) BOOL hasLocalContents NS_AVAILABLE(10_10, 8_0);

/* Whether the version has a thumbnail image available. Thumbnails for versions from +getNonlocalVersionsOfItemAtURL:completionHandler: may not immediately be available. As soon as it becomes available, this property will change from NO to YES. You can use KVO to be notified of this change. If a thumbnail is available, you can access it using NSURLThumbnailKey or NSURLThumbnailDictionaryKey.
*/
@property (readonly) BOOL hasThumbnail NS_AVAILABLE(10_10, 8_0);

/* If the passed-in URL locates a file, replace the file with a file whose contents are taken from the version but whose display name is taken from the file. If the passed-in URL does not locate a file then simply write one. If successful, return a URL that locates the resulting file; it may be different from the passed-in URL. The one exception to taking the display name from an existing file is if the version is of a different type than the overwritten file. In that case the file name extension will be taken from the version. (When file name extensions are being hidden in a user-friendly way this is not actually an exception.) If not successful, return NO after setting *outError to an NSError that encapsulates why not.

When you use NSFileVersionReplacingByMoving you remove a version of the file, and should do it as part of a coordinated write to the file. The advice about this for +addVersionOfItemAtURL:withContentsOfURL:options:error: applies here too. When you use it to promote a version to a separate file you actually write to two files, and should do it as part of a coordinated write to two files, using -[NSFileCoordinator coordinateWritingItemAtURL:options:writingItemAtURL:options:error:byAccessor:], most likely using NSFileCoordinatorWritingForReplacing for the file you're promoting the version to.
*/
- (nullable NSURL *)replaceItemAtURL:(NSURL *)url options:(NSFileVersionReplacingOptions)options error:(NSError **)error;

/* Delete the receiver's storage, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates why not. Subsequent invocations of +versionsOfItemAtURL: won't include an NSFileVersion for a successfully removed version.

You cannot use this method to delete the versioned file itself. This method always throws an exception when sent to the result of invoking +currentVersionOfItemAtURL:. Use -[NSFileManager removeItemAtURL:error:] for that instead.

When removing versions of a file you should do it as part of a coordinated write to the file. The advice about this for +addVersionOfItemAtURL:withContentsOfURL:options:error: applies here too.
*/
- (BOOL)removeAndReturnError:(NSError **)outError;

/* Delete all of the versions associated with the file located by a URL, except for the current one, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates why not.

When removing versions of a file you should do it as part of a coordinated write to the file. The advice about this for +addVersionOfItemAtURL:withContentsOfURL:options:error: applies here too.
*/
+ (BOOL)removeOtherVersionsOfItemAtURL:(NSURL *)url error:(NSError **)outError;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSNull.h
/*	NSNull.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSNull : NSObject <NSCopying, NSSecureCoding>

+ (NSNull *)null;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSAttributedString.h
/*	NSAttributedString.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/


#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_0, 3_2)
@interface NSAttributedString : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

@property (readonly, copy) NSString *string;
- (NSDictionary<NSString *, id> *)attributesAtIndex:(NSUInteger)location effectiveRange:(nullable NSRangePointer)range;

@end

@interface NSAttributedString (NSExtendedAttributedString)

@property (readonly) NSUInteger length;
- (nullable id)attribute:(NSString *)attrName atIndex:(NSUInteger)location effectiveRange:(nullable NSRangePointer)range;
- (NSAttributedString *)attributedSubstringFromRange:(NSRange)range;

- (NSDictionary<NSString *, id> *)attributesAtIndex:(NSUInteger)location longestEffectiveRange:(nullable NSRangePointer)range inRange:(NSRange)rangeLimit;
- (nullable id)attribute:(NSString *)attrName atIndex:(NSUInteger)location longestEffectiveRange:(nullable NSRangePointer)range inRange:(NSRange)rangeLimit;

- (BOOL)isEqualToAttributedString:(NSAttributedString *)other;

- (instancetype)initWithString:(NSString *)str;
- (instancetype)initWithString:(NSString *)str attributes:(nullable NSDictionary<NSString *, id> *)attrs;
- (instancetype)initWithAttributedString:(NSAttributedString *)attrStr;

typedef NS_OPTIONS(NSUInteger, NSAttributedStringEnumerationOptions) {
  NSAttributedStringEnumerationReverse = (1UL << 1),
  NSAttributedStringEnumerationLongestEffectiveRangeNotRequired = (1UL << 20)
};

- (void)enumerateAttributesInRange:(NSRange)enumerationRange options:(NSAttributedStringEnumerationOptions)opts usingBlock:(void (^)(NSDictionary<NSString *, id> *attrs, NSRange range, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateAttribute:(NSString *)attrName inRange:(NSRange)enumerationRange options:(NSAttributedStringEnumerationOptions)opts usingBlock:(void (^)(id __nullable value, NSRange range, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

@end

NS_CLASS_AVAILABLE(10_0, 3_2)
@interface NSMutableAttributedString : NSAttributedString

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str;
- (void)setAttributes:(nullable NSDictionary<NSString *, id> *)attrs range:(NSRange)range;

@end

@interface NSMutableAttributedString (NSExtendedMutableAttributedString)

@property (readonly, retain) NSMutableString *mutableString;

- (void)addAttribute:(NSString *)name value:(id)value range:(NSRange)range;
- (void)addAttributes:(NSDictionary<NSString *, id> *)attrs range:(NSRange)range;
- (void)removeAttribute:(NSString *)name range:(NSRange)range;

- (void)replaceCharactersInRange:(NSRange)range withAttributedString:(NSAttributedString *)attrString;
- (void)insertAttributedString:(NSAttributedString *)attrString atIndex:(NSUInteger)loc;
- (void)appendAttributedString:(NSAttributedString *)attrString;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)setAttributedString:(NSAttributedString *)attrString;

- (void)beginEditing;
- (void)endEditing;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSExtensionItem.h
/*	NSExtensionItem.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <Foundation/NSItemProvider.h>

#if __OBJC2__
// A NSExtensionItem is an immutable collection of values representing different aspects of an item for the extension to act upon.
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSExtensionItem : NSObject<NSCopying, NSSecureCoding>

// (optional) title for the item
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedTitle;

// (optional) content text
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedContentText;

// (optional) Contains images, videos, URLs, etc. This is not meant to be an array of alternate data formats/types, but instead a collection to include in a social media post for example. These items are always typed NSItemProvider.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSArray *attachments;

// (optional) dictionary of key-value data. The key/value pairs accepted by the service are expected to be specified in the extension's Info.plist. The values of NSExtensionItem's properties will be reflected into the dictionary.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSDictionary *userInfo;

@end

// Keys corresponding to properties exposed on the NSExtensionItem interface
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionItemAttributedTitleKey NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionItemAttributedContentTextKey NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionItemAttachmentsKey NS_AVAILABLE(10_10, 8_0);

NS_ASSUME_NONNULL_END
#endif
// ==========  Foundation.framework/Headers/NSURL.h
/*	NSURL.h
	Copyright (c) 1997-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSCharacterSet.h>
#if !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLHandle.h>
#endif

@class NSArray<ObjectType>, NSNumber, NSData, NSDictionary<KeyType, ObjectType>;

NS_ASSUME_NONNULL_BEGIN

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
@interface NSURL: NSObject <NSSecureCoding, NSCopying>
#else
@interface NSURL: NSObject <NSSecureCoding, NSCopying, NSURLHandleClient>
#endif
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    __strong void *_reserved;
}


/* As more schemes are used and understood, strong constants for them will be added here
 */
FOUNDATION_EXPORT NSString *NSURLFileScheme;


/* Convenience initializers
 */
- (nullable instancetype)initWithScheme:(NSString *)scheme host:(nullable NSString *)host path:(NSString *)path NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use NSURLComponents instead, which lets you create a valid URL with any valid combination of URL components and subcomponents (not just scheme, host and path), and lets you set components and subcomponents with either percent-encoded or un-percent-encoded strings."); // this call percent-encodes both the host and path, so this cannot be used to set a username/password or port in the hostname part or with a IPv6 '[...]' type address. NSURLComponents handles IPv6 addresses correctly.

/* Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
- (instancetype)initFileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER; // Better to use initFileURLWithPath:isDirectory:relativeToURL: if you know if the path is a directory vs non-directory, as it saves an I/O.

- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (instancetype)initFileURLWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

/* Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);
/* Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
+ (NSURL *)fileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0); // Better to use fileURLWithPath:isDirectory:relativeToURL: if you know if the path is a directory vs non-directory, as it saves an I/O.

+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0);
+ (NSURL *)fileURLWithPath:(NSString *)path; // Better to use fileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

/* Initializes a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
- (instancetype)initFileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER;

/* Initializes and returns a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
+ (NSURL *)fileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_9, 7_0);

/* These methods expect their string arguments to contain any percent escape codes that are necessary. It is an error for URLString to be nil.
 */
- (nullable instancetype)initWithString:(NSString *)URLString;
- (nullable instancetype)initWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL NS_DESIGNATED_INITIALIZER;
+ (nullable instancetype)URLWithString:(NSString *)URLString;
+ (nullable instancetype)URLWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL;


/* Initializes a newly created NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
- (instancetype)initWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes and returns a newly created NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
+ (NSURL *)URLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);

/* Initializes a newly created absolute NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
- (instancetype)initAbsoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes and returns a newly created absolute NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
+ (NSURL *)absoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);

/* Returns the data representation of the URL's relativeString. If the URL was initialized with -initWithData:relativeToURL:, the data representation returned are the same bytes as those used at initialization; otherwise, the data representation returned are the bytes of the relativeString encoded with NSUTF8StringEncoding.
 */
@property (readonly, copy) NSData *dataRepresentation NS_AVAILABLE(10_11, 9_0);

@property (readonly, copy) NSString *absoluteString;
@property (nullable, readonly, copy) NSString *relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
@property (nullable, readonly, copy) NSURL *baseURL; // may be nil.
@property (readonly, copy) NSURL *absoluteURL; // if the receiver is itself absolute, this will return self.

/* Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
 */
@property (readonly, copy) NSString *scheme;
@property (readonly, copy) NSString *resourceSpecifier;

/* If the URL conforms to rfc 1808 (the most common form of URL), the following accessors will return the various components; otherwise they return nil.  The litmus test for conformance is as recommended in RFC 1808 - whether the first two characters of resourceSpecifier is @"//".  In all cases, they return the component's value after resolving the receiver against its base URL.
 */
@property (nullable, readonly, copy) NSString *host;
@property (nullable, readonly, copy) NSNumber *port;
@property (nullable, readonly, copy) NSString *user;
@property (nullable, readonly, copy) NSString *password;
@property (nullable, readonly, copy) NSString *path;
@property (nullable, readonly, copy) NSString *fragment;
@property (nullable, readonly, copy) NSString *parameterString;
@property (nullable, readonly, copy) NSString *query;
@property (nullable, readonly, copy) NSString *relativePath; // The same as path if baseURL is nil

/* Determines if a given URL string's path represents a directory (i.e. the path component in the URL string ends with a '/' character). This does not check the resource the URL refers to.
 */
@property (readonly) BOOL hasDirectoryPath NS_AVAILABLE(10_11, 9_0);

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
- (BOOL)getFileSystemRepresentation:(char *)buffer maxLength:(NSUInteger)maxBufferLength NS_AVAILABLE(10_9, 7_0);

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding. The returned C string will be automatically freed just as a returned object would be released; your code should copy the representation or use getFileSystemRepresentation:maxLength: if it needs to store the representation outside of the autorelease context in which the representation is created.
 */
@property (readonly) __strong const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER NS_AVAILABLE(10_9, 7_0);

@property (readonly, getter=isFileURL) BOOL fileURL; // Whether the scheme is file:; if [myURL isFileURL] is YES, then [myURL path] is suitable for input into NSFileManager or NSPathUtilities.

@property (nullable, readonly, copy) NSURL *standardizedURL;


/* Returns whether the URL's resource exists and is reachable. This method synchronously checks if the resource's backing store is reachable. Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file or copying resource properties, it is more efficient to simply try the operation and handle failures. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. For other URL types, NO is returned. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW NS_AVAILABLE(10_6, 4_0);


/* Working with file reference URLs
 */

/* Returns whether the URL is a file reference URL. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)isFileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file reference URL that refers to the same resource as a specified file URL. File reference URLs use a URL path syntax that identifies a file system object by reference, not by path. This form of file URL remains valid when the file system path of the URL’s underlying resource changes. An error will occur if the url parameter is not a file URL. File reference URLs cannot be created to file system objects which do not exist or are not reachable. In some areas of the file system hierarchy, file reference URLs cannot be generated to the leaf node of the URL path. A file reference URL's path should never be persistently stored because is not valid across system restarts, and across remounts of volumes -- if you want to create a persistent reference to a file system object, use a bookmark (see -bookmarkDataWithOptions:includingResourceValuesForKeys:relativeToURL:error:). Symbol is present in iOS 4, but performs no operation.
 */
- (nullable NSURL *)fileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file path URL that refers to the same resource as a specified URL. File path URLs use a file system style path. An error will occur if the url parameter is not a file URL. A file reference URL's resource must exist and be reachable to be converted to a file path URL. Symbol is present in iOS 4, but performs no operation.
 */
@property (nullable, readonly, copy) NSURL *filePathURL NS_AVAILABLE(10_6, 4_0);


/* Resource access

 The behavior of resource value caching is slightly different between the NSURL and CFURL API.
 
 When the NSURL methods which get, set, or use cached resource values are used from the main thread, resource values cached by the URL (except those added as temporary properties) are removed the next time the main thread's run loop runs. -removeCachedResourceValueForKey: and -removeAllCachedResourceValues also may be used to remove cached resource values.
 
 The CFURL functions do not automatically remove any resource values cached by the URL. The client has complete control over the cache lifetime. If you are using CFURL API, you must use CFURLClearResourcePropertyCacheForKey or CFURLClearResourcePropertyCache to remove cached resource values.
 */

/* Returns the resource value identified by a given resource key. This method first checks if the URL object already caches the resource value. If so, it returns the cached resource value to the caller. If not, then this method synchronously obtains the resource value from the backing store, adds the resource value to the URL object's cache, and returns the resource value to the caller. The type of the resource value varies by resource property (see resource key definitions). If this method returns YES and value is populated with nil, it means the resource property is not available for the specified resource and no errors occurred when determining the resource property was not available. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)getResourceValue:(out id __nullable * __nonnull)value forKey:(NSString *)key error:(out NSError ** __nullable)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values identified by specified array of resource keys. This method first checks if the URL object already caches the resource values. If so, it returns the cached resource values to the caller. If not, then this method synchronously obtains the resource values from the backing store, adds the resource values to the URL object's cache, and returns the resource values to the caller. The type of the resource values vary by property (see resource key definitions). If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available for the specified resource and no errors occurred when determining those resource properties were not available. If this method returns NULL, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (nullable NSDictionary<NSString *, id> *)resourceValuesForKeys:(NSArray<NSString *> *)keys error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets the resource value identified by a given resource key. This method writes the new resource value out to the backing store. Attempts to set a read-only resource property or to set a resource property not supported by the resource are ignored and are not considered errors. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)setResourceValue:(nullable id)value forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets any number of resource values of a URL's resource. This method writes the new resource values out to the backing store. Attempts to set read-only resource properties or to set resource properties not supported by the resource are ignored and are not considered errors. If an error occurs after some resource properties have been successfully changed, the userInfo dictionary in the returned error contains an array of resource keys that were not set with the key kCFURLKeysOfUnsetValuesKey. The order in which the resource values are set is not defined. If you need to guarantee the order resource values are set, you should make multiple requests to this method or to -setResourceValue:forKey:error: to guarantee the order. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)setResourceValues:(NSDictionary<NSString *, id> *)keyedValues error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

FOUNDATION_EXPORT NSString * const NSURLKeysOfUnsetValuesKey NS_AVAILABLE(10_7, 5_0); // Key for the resource properties that have not been set after setResourceValues:error: returns an error, returned as an array of of strings.

/* Removes the cached resource value identified by a given resource value key from the URL object. Removing a cached resource value may remove other cached resource values because some resource values are cached as a set of values, and because some resource values depend on other resource values (temporary resource values have no dependencies). This method is currently applicable only to URLs for file system resources.
 */
- (void)removeCachedResourceValueForKey:(NSString *)key NS_AVAILABLE(10_9, 7_0);

/* Removes all cached resource values and all temporary resource values from the URL object. This method is currently applicable only to URLs for file system resources.
 */
- (void)removeAllCachedResourceValues NS_AVAILABLE(10_9, 7_0);

/* Sets a temporary resource value on the URL object. Temporary resource values are for client use. Temporary resource values exist only in memory and are never written to the resource's backing store. Once set, a temporary resource value can be copied from the URL object with -getResourceValue:forKey:error: or -resourceValuesForKeys:error:. To remove a temporary resource value from the URL object, use -removeCachedResourceValueForKey:. Care should be taken to ensure the key that identifies a temporary resource value is unique and does not conflict with system defined keys (using reverse domain name notation in your temporary resource value keys is recommended). This method is currently applicable only to URLs for file system resources.
 */
- (void)setTemporaryResourceValue:(nullable id)value forKey:(NSString *)key NS_AVAILABLE(10_9, 7_0);

/*
 The File System Resource Keys
 
 URLs to file system resources support the properties defined below. Note that not all property values will exist for all file system URLs. For example, if a file is located on a volume that does not support creation dates, it is valid to request the creation date property, but the returned value will be nil, and no error will be generated.
 */

/* Resource keys applicable to all file system objects
 */
FOUNDATION_EXPORT NSString * const NSURLNameKey                        NS_AVAILABLE(10_6, 4_0); // The resource name provided by the file system (Read-write, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLocalizedNameKey               NS_AVAILABLE(10_6, 4_0); // Localized or extension-hidden name as displayed to users (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLIsRegularFileKey               NS_AVAILABLE(10_6, 4_0); // True for regular files (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsDirectoryKey                 NS_AVAILABLE(10_6, 4_0); // True for directories (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsSymbolicLinkKey              NS_AVAILABLE(10_6, 4_0); // True for symlinks (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsVolumeKey                    NS_AVAILABLE(10_6, 4_0); // True for the root directory of a volume (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsPackageKey                   NS_AVAILABLE(10_6, 4_0); // True for packaged directories (Read-only 10_6 and 10_7, read-write 10_8, value type boolean NSNumber). Note: You can only set or clear this property on directories; if you try to set this property on non-directory objects, the property is ignored. If the directory is a package for some other reason (extension type, etc), setting this property to false will have no effect.
FOUNDATION_EXPORT NSString * const NSURLIsApplicationKey               NS_AVAILABLE(10_11, 9_0); // True if resource is an application (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLApplicationIsScriptableKey     NS_AVAILABLE(10_11, NA); // True if the resource is scriptable. Only applies to applications (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsSystemImmutableKey           NS_AVAILABLE(10_6, 4_0); // True for system-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsUserImmutableKey             NS_AVAILABLE(10_6, 4_0); // True for user-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsHiddenKey                    NS_AVAILABLE(10_6, 4_0); // True for resources normally not displayed to users (Read-write, value type boolean NSNumber). Note: If the resource is a hidden because its name starts with a period, setting this property to false will not change the property.
FOUNDATION_EXPORT NSString * const NSURLHasHiddenExtensionKey          NS_AVAILABLE(10_6, 4_0); // True for resources whose filename extension is removed from the localized name property (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLCreationDateKey                NS_AVAILABLE(10_6, 4_0); // The date the resource was created (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLContentAccessDateKey           NS_AVAILABLE(10_6, 4_0); // The date the resource was last accessed (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLContentModificationDateKey     NS_AVAILABLE(10_6, 4_0); // The time the resource content was last modified (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLAttributeModificationDateKey   NS_AVAILABLE(10_6, 4_0); // The time the resource's attributes were last modified (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLLinkCountKey                   NS_AVAILABLE(10_6, 4_0); // Number of hard links to the resource (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLParentDirectoryURLKey          NS_AVAILABLE(10_6, 4_0); // The resource's parent directory, if any (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLVolumeURLKey                   NS_AVAILABLE(10_6, 4_0); // URL of the volume on which the resource is stored (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLTypeIdentifierKey              NS_AVAILABLE(10_6, 4_0); // Uniform type identifier (UTI) for the resource (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLocalizedTypeDescriptionKey    NS_AVAILABLE(10_6, 4_0); // User-visible type or "kind" description (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLabelNumberKey                 NS_AVAILABLE(10_6, 4_0); // The label number assigned to the resource (Read-write, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLLabelColorKey                  NS_AVAILABLE(10_6, 4_0); // The color of the assigned label (Read-only, value type NSColor)
FOUNDATION_EXPORT NSString * const NSURLLocalizedLabelKey              NS_AVAILABLE(10_6, 4_0); // The user-visible label text (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLEffectiveIconKey               NS_AVAILABLE(10_6, 4_0); // The icon normally displayed for the resource (Read-only, value type NSImage)
FOUNDATION_EXPORT NSString * const NSURLCustomIconKey                  NS_AVAILABLE(10_6, 4_0); // The custom icon assigned to the resource, if any (Currently not implemented, value type NSImage)
FOUNDATION_EXPORT NSString * const NSURLFileResourceIdentifierKey      NS_AVAILABLE(10_7, 5_0); // An identifier which can be used to compare two file system objects for equality using -isEqual (i.e, two object identifiers are equal if they have the same file system path or if the paths are linked to same inode on the same file system). This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSObject>)
FOUNDATION_EXPORT NSString * const NSURLVolumeIdentifierKey            NS_AVAILABLE(10_7, 5_0); // An identifier that can be used to identify the volume the file system object is on. Other objects on the same volume will have the same volume identifier and can be compared using for equality using -isEqual. This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSObject>)
FOUNDATION_EXPORT NSString * const NSURLPreferredIOBlockSizeKey        NS_AVAILABLE(10_7, 5_0); // The optimal block size when reading or writing this file's data, or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsReadableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can read the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsWritableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can write to the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsExecutableKey                NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileSecurityKey                NS_AVAILABLE(10_7, 5_0); // The file system object's security information encapsulated in a NSFileSecurity object. (Read-write, Value type NSFileSecurity)
FOUNDATION_EXPORT NSString * const NSURLIsExcludedFromBackupKey        NS_AVAILABLE(10_8, 5_1); // true if resource should be excluded from backups, false otherwise (Read-write, value type boolean NSNumber). This property is only useful for excluding cache and other application support files which are not needed in a backup. Some operations commonly made to user documents will cause this property to be reset to false and so this property should not be used on user documents.
FOUNDATION_EXPORT NSString * const NSURLTagNamesKey                    NS_AVAILABLE(10_9, NA);	// The array of Tag names (Read-write, value type NSArray of NSString)
FOUNDATION_EXPORT NSString * const NSURLPathKey                        NS_AVAILABLE(10_8, 6_0); // the URL's path as a file system path (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLIsMountTriggerKey              NS_AVAILABLE(10_7, 5_0); // true if this URL is a file system trigger directory. Traversing or opening a file system trigger will cause an attempt to mount a file system on the trigger directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLGenerationIdentifierKey NS_AVAILABLE(10_10, 8_0); // An opaque generation identifier which can be compared using isEqual: to determine if the data in a document has been modified. For URLs which refer to the same file inode, the generation identifier will change when the data in the file's data fork is changed (changes to extended attributes or other file system metadata do not change the generation identifier). For URLs which refer to the same directory inode, the generation identifier will change when direct children of that directory are added, removed or renamed (changes to the data of the direct children of that directory will not change the generation identifier). The generation identifier is persistent across system restarts. The generation identifier is tied to a specific document on a specific volume and is not transferred when the document is copied to another volume. This property is not supported by all volumes. (Read-only, value type id <NSCopying, NSCoding, NSObject>
FOUNDATION_EXPORT NSString * const NSURLDocumentIdentifierKey NS_AVAILABLE(10_10, 8_0); // The document identifier -- a value assigned by the kernel to a document (which can be either a file or directory) and is used to identify the document regardless of where it gets moved on a volume. The document identifier survives "safe save” operations; i.e it is sticky to the path it was assigned to (-replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is the preferred safe-save API). The document identifier is persistent across system restarts. The document identifier is not transferred when the file is copied. Document identifiers are only unique within a single volume. This property is not supported by all volumes. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLAddedToDirectoryDateKey NS_AVAILABLE(10_10, 8_0); // The date the resource was created, or renamed into or within its parent directory. Note that inconsistent behavior may be observed when this attribute is requested on hard-linked items. This property is not supported by all volumes. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLQuarantinePropertiesKey NS_AVAILABLE(10_10, NA); // The quarantine properties as defined in LSQuarantine.h. To remove quarantine information from a file, pass NSNull as the value when setting this property. (Read-write, value type NSDictionary)
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeKey            NS_AVAILABLE(10_7, 5_0); // Returns the file system object type. (Read-only, value type NSString)

/* The file system object type values returned for the NSURLFileResourceTypeKey
 */
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeNamedPipe      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeCharacterSpecial NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeDirectory      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeBlockSpecial   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeRegular        NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSymbolicLink   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSocket         NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeUnknown        NS_AVAILABLE(10_7, 5_0);

FOUNDATION_EXPORT NSString * const NSURLThumbnailDictionaryKey         NS_AVAILABLE(10_10, 8_0); // dictionary of NSImage/UIImage objects keyed by size
FOUNDATION_EXPORT NSString * const NSURLThumbnailKey                   NS_AVAILABLE_MAC(10_10); // returns all thumbnails as a single NSImage

/* size keys for the dictionary returned by NSURLThumbnailDictionaryKey
 */
FOUNDATION_EXPORT NSString * const NSThumbnail1024x1024SizeKey         NS_AVAILABLE(10_10, 8_0); // size key for a 1024 x 1024 thumbnail image

/* Resource keys applicable only to regular files
 */
FOUNDATION_EXPORT NSString * const NSURLFileSizeKey                    NS_AVAILABLE(10_6, 4_0); // Total file size in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileAllocatedSizeKey           NS_AVAILABLE(10_6, 4_0); // Total size allocated on disk for the file in bytes (number of blocks times block size) (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLTotalFileSizeKey               NS_AVAILABLE(10_7, 5_0); // Total displayable size of the file in bytes (this may include space used by metadata), or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLTotalFileAllocatedSizeKey      NS_AVAILABLE(10_7, 5_0); // Total allocated size of the file in bytes (this may include space used by metadata), or nil if not available. This can be less than the value returned by NSURLTotalFileSizeKey if the resource is compressed. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsAliasFileKey                 NS_AVAILABLE(10_6, 4_0); // true if the resource is a Finder alias file or a symlink, false otherwise ( Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileProtectionKey              NS_AVAILABLE_IOS(9_0); // The protection level for this file

/* The protection level values returned for the NSURLFileProtectionKey
 */
FOUNDATION_EXPORT NSString * const NSURLFileProtectionNone NS_AVAILABLE_IOS(9_0); // The file has no special protections associated with it. It can be read from or written to at any time.
FOUNDATION_EXPORT NSString * const NSURLFileProtectionComplete NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be read from or written to while the device is locked or booting.
FOUNDATION_EXPORT NSString * const NSURLFileProtectionCompleteUnlessOpen NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk. Files can be created while the device is locked, but once closed, cannot be opened again until the device is unlocked. If the file is opened when unlocked, you may continue to access the file normally, even if the user locks the device. There is a small performance penalty when the file is created and opened, though not when being written to or read from. This can be mitigated by changing the file protection to NSURLFileProtectionComplete when the device is unlocked.
FOUNDATION_EXPORT NSString * const NSURLFileProtectionCompleteUntilFirstUserAuthentication NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be accessed until after the device has booted. After the user unlocks the device for the first time, your app can access the file and continue to access it even if the user subsequently locks the device.

/* Volumes resource keys 
 
 As a convenience, volume resource values can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
 */
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedFormatDescriptionKey NS_AVAILABLE(10_6, 4_0); // The user-visible volume format (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeTotalCapacityKey              NS_AVAILABLE(10_6, 4_0); // Total volume capacity in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeAvailableCapacityKey          NS_AVAILABLE(10_6, 4_0); // Total free space in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeResourceCountKey              NS_AVAILABLE(10_6, 4_0); // Total number of resources on the volume (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsPersistentIDsKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports persistent object identifiers and can look up file system objects by their IDs (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSymbolicLinksKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports symbolic links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsHardLinksKey          NS_AVAILABLE(10_6, 4_0); // true if the volume format supports hard links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsJournalingKey         NS_AVAILABLE(10_6, 4_0); // true if the volume format supports a journal used to speed recovery in case of unplanned restart (such as a power outage or crash). This does not necessarily mean the volume is actively using a journal. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsJournalingKey               NS_AVAILABLE(10_6, 4_0); // true if the volume is currently using a journal for speedy recovery after an unplanned restart. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSparseFilesKey        NS_AVAILABLE(10_6, 4_0); // true if the volume format supports sparse files, that is, files which can have 'holes' that have never been written to, and thus do not consume space on disk. A sparse file may have an allocated size on disk that is less than its logical length (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsZeroRunsKey           NS_AVAILABLE(10_6, 4_0); // For security reasons, parts of a file (runs) that have never been written to must appear to contain zeroes. true if the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCaseSensitiveNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format treats upper and lower case characters in file and directory names as different. Otherwise an upper case character is equivalent to a lower case character, and you can't have two names that differ solely in the case of the characters. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCasePreservedNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format preserves the case of file and directory names.  Otherwise the volume may change the case of some characters (typically making them all upper or all lower case). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRootDirectoryDatesKey NS_AVAILABLE(10_7, 5_0); // true if the volume supports reliable storage of times for the root directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsVolumeSizesKey        NS_AVAILABLE(10_7, 5_0); // true if the volume supports returning volume size values (NSURLVolumeTotalCapacityKey and NSURLVolumeAvailableCapacityKey). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRenamingKey           NS_AVAILABLE(10_7, 5_0); // true if the volume can be renamed. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsAdvisoryFileLockingKey NS_AVAILABLE(10_7, 5_0); // true if the volume implements whole-file flock(2) style advisory locks, and the O_EXLOCK and O_SHLOCK flags of the open(2) call. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsExtendedSecurityKey   NS_AVAILABLE(10_7, 5_0); // true if the volume implements extended security (ACLs). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsBrowsableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume should be visible via the GUI (i.e., appear on the Desktop as a separate volume). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeMaximumFileSizeKey            NS_AVAILABLE(10_7, 5_0); // The largest file size (in bytes) supported by this file system, or nil if this cannot be determined. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsEjectableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is ejectable from the drive mechanism under software control. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsRemovableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is removable from the drive mechanism. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsInternalKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume's device is connected to an internal bus, false if connected to an external bus, or nil if not available. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsAutomountedKey              NS_AVAILABLE(10_7, 5_0); // true if the volume is automounted. Note: do not mistake this with the functionality provided by kCFURLVolumeSupportsBrowsingKey. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsLocalKey                    NS_AVAILABLE(10_7, 5_0); // true if the volume is stored on a local device. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsReadOnlyKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume is read-only. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeCreationDateKey               NS_AVAILABLE(10_7, 5_0); // The volume's creation date, or nil if this cannot be determined. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLVolumeURLForRemountingKey           NS_AVAILABLE(10_7, 5_0); // The NSURL needed to remount a network volume, or nil if not available. (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLVolumeUUIDStringKey                 NS_AVAILABLE(10_7, 5_0); // The volume's persistent UUID as a string, or nil if a persistent UUID is not available for the volume. (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeNameKey                       NS_AVAILABLE(10_7, 5_0); // The name of the volume (Read-write if NSURLVolumeSupportsRenamingKey is YES, otherwise read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedNameKey              NS_AVAILABLE(10_7, 5_0); // The user-presentable name of the volume (Read-only, value type NSString)

/* Ubiquitous item resource keys
 */
FOUNDATION_EXPORT NSString * const NSURLIsUbiquitousItemKey                     NS_AVAILABLE(10_7, 5_0); // true if this item is synced to the cloud, false if it is only a local file. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // true if this item has conflicts outstanding. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadedKey           NS_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use NSURLUbiquitousItemDownloadingStatusKey instead"); // equivalent to NSURLUbiquitousItemDownloadingStatusKey == NSURLUbiquitousItemDownloadingStatusCurrent. Has never behaved as documented in earlier releases, hence deprecated.  (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadingKey          NS_AVAILABLE(10_7, 5_0); // true if data is being downloaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadedKey             NS_AVAILABLE(10_7, 5_0); // true if there is data present in the cloud for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadingKey            NS_AVAILABLE(10_7, 5_0); // true if data is being uploaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentDownloadedKey      NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentDownloadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentUploadedKey        NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentUploadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusKey      NS_AVAILABLE(10_9, 7_0); // returns the download status of this item. (Read-only, value type NSString). Possible values below.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingErrorKey       NS_AVAILABLE(10_9, 7_0); // returns the error when downloading the item from iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemUploadingErrorKey         NS_AVAILABLE(10_9, 7_0); // returns the error when uploading the item to iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadRequestedKey      NS_AVAILABLE(10_10, 8_0); // returns whether a download of this item has already been requested with an API like -startDownloadingUbiquitousItemAtURL:error: (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemContainerDisplayNameKey   NS_AVAILABLE(10_10, 8_0); // returns the name of this item's container as displayed to users.


/* The values returned for the NSURLUbiquitousItemDownloadingStatusKey
 */
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusNotDownloaded  NS_AVAILABLE(10_9, 7_0); // this item has not been downloaded yet. Use startDownloadingUbiquitousItemAtURL:error: to download it.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusDownloaded     NS_AVAILABLE(10_9, 7_0); // there is a local version of this item available. The most current version will get downloaded as soon as possible.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusCurrent        NS_AVAILABLE(10_9, 7_0); // there is a local version of this item and it is the most up-to-date version known to this device.

/* Working with Bookmarks and alias (bookmark) files 
 */

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkCreationOptions) {
    NSURLBookmarkCreationPreferFileIDResolution NS_ENUM_DEPRECATED(10_6, 10_9, 4_0, 7_0) = ( 1UL << 8 ), /* This option does nothing and has no effect on bookmark resolution */
    NSURLBookmarkCreationMinimalBookmark = ( 1UL << 9 ), /* creates bookmark data with "less" information, which may be smaller but still be able to resolve in certain ways */
    NSURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ), /* include the properties required by writeBookmarkData:toURL:options: in the bookmark data created */
    NSURLBookmarkCreationWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 11 ), /* include information in the bookmark data which allows the same sandboxed process to access the resource after being relaunched */
    NSURLBookmarkCreationSecurityScopeAllowOnlyReadAccess NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 12 ), /* if used with kCFURLBookmarkCreationWithSecurityScope, at resolution time only read access to the resource will be granted */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkResolutionOptions) {
    NSURLBookmarkResolutionWithoutUI = ( 1UL << 8 ), /* don't perform any user interaction during bookmark resolution */
    NSURLBookmarkResolutionWithoutMounting = ( 1UL << 9 ), /* don't mount a volume during bookmark resolution */
    NSURLBookmarkResolutionWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 10 ) /* use the secure information included at creation time to provide the ability to access the resource in a sandboxed process */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NSUInteger NSURLBookmarkFileCreationOptions;

/* Returns bookmark data for the URL, created with specified options and resource values. If this method returns nil, the optional error is populated.
 */
- (nullable NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(nullable NSArray<NSString *> *)keys relativeToURL:(nullable NSURL *)relativeURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes a newly created NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
- (nullable instancetype)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * __nullable)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
/* Creates and Initializes an NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
+ (nullable instancetype)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * __nullable)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values for properties identified by a specified array of keys contained in specified bookmark data. If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available in the bookmark data.
 */
+ (nullable NSDictionary<NSString *, id> *)resourceValuesForKeys:(NSArray<NSString *> *)keys fromBookmarkData:(NSData *)bookmarkData NS_AVAILABLE(10_6, 4_0);

/* Creates an alias file on disk at a specified location with specified bookmark data. bookmarkData must have been created with the NSURLBookmarkCreationSuitableForBookmarkFile option. bookmarkFileURL must either refer to an existing file (which will be overwritten), or to location in an existing directory. If this method returns NO, the optional error is populated.
*/
+ (BOOL)writeBookmarkData:(NSData *)bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes and returns bookmark data derived from an alias file pointed to by a specified URL. If bookmarkFileURL refers to an alias file created prior to OS X v10.6 that contains Alias Manager information but no bookmark data, this method synthesizes bookmark data for the file. If this method returns nil, the optional error is populated.
*/
+ (nullable NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Creates and initializes a NSURL that refers to the location specified by resolving the alias file at url. If the url argument does not refer to an alias file as defined by the NSURLIsAliasFileKey property, the NSURL returned is the same as url argument. This method fails and returns nil if the url argument is unreachable, or if the original file or directory could not be located or is not reachable, or if the original file or directory is on a volume that could not be located or mounted. If this method fails, the optional error is populated. The NSURLBookmarkResolutionWithSecurityScope option is not supported by this method.
 */
+ (nullable instancetype)URLByResolvingAliasFileAtURL:(NSURL *)url options:(NSURLBookmarkResolutionOptions)options error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/*  Given a NSURL created by resolving a bookmark data created with security scope, make the resource referenced by the url accessible to the process. When access to this resource is no longer needed the client must call stopAccessingSecurityScopedResource. Each call to startAccessingSecurityScopedResource must be balanced with a call to stopAccessingSecurityScopedResource (Note: this is not reference counted).
 */
- (BOOL)startAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

/*  Revokes the access granted to the url by a prior successful call to startAccessingSecurityScopedResource.
 */
- (void)stopAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

@end


@interface NSURL (NSPromisedItems)

/* Get resource values from URLs of 'promised' items. A promised item is not guaranteed to have its contents in the file system until you use NSFileCoordinator to perform a coordinated read on its URL, which causes the contents to be downloaded or otherwise generated. Promised item URLs are returned by various APIs, including currently:
 - NSMetadataQueryUbiquitousDataScope
 - NSMetadataQueryUbiquitousDocumentsScope
 - An NSFilePresenter presenting the contents of the directory located by -URLForUbiquitousContainerIdentifier: or a subdirectory thereof
 
 The following methods behave identically to their similarly named methods above (-getResourceValue:forKey:error:, etc.), except that they allow you to get resource values and check for presence regardless of whether the promised item's contents currently exist at the URL. You must use these APIs instead of the normal NSURL resource value APIs if and only if any of the following are true:
 - You are using a URL that you know came directly from one of the above APIs
 - You are inside the accessor block of a coordinated read or write that used NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly, NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingContentIndependentMetadataOnly
 
 Most of the NSURL resource value keys will work with these APIs. However, there are some that are tied to the item's contents that will not work, such as NSURLContentAccessDateKey or NSURLGenerationIdentifierKey. If one of these keys is used, the method will return YES, but the value for the key will be nil.
*/
- (BOOL)getPromisedItemResourceValue:(id __nullable * __nonnull)value forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (nullable NSDictionary<NSString *, id> *)promisedItemResourceValuesForKeys:(NSArray<NSString *> *)keys error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (BOOL)checkPromisedItemIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW NS_AVAILABLE(10_10, 8_0);

@end



NS_CLASS_AVAILABLE(10_10, 8_0)
// NSURLQueryItem encapsulates a single query name-value pair. The name and value strings of a query name-value pair are not percent encoded. For use with the NSURLComponents queryItems property.
@interface NSURLQueryItem : NSObject <NSSecureCoding, NSCopying> {
@private
    NSString *_name;
    NSString *_value;
}
- (instancetype)initWithName:(NSString *)name value:(nullable NSString *)value NS_DESIGNATED_INITIALIZER;
+ (instancetype)queryItemWithName:(NSString *)name value:(nullable NSString *)value;
@property (readonly) NSString *name;
@property (nullable, readonly) NSString *value;
@end


NS_CLASS_AVAILABLE(10_9, 7_0)
@interface NSURLComponents : NSObject <NSCopying>

// Initialize a NSURLComponents with all components undefined. Designated initializer.
- (instancetype)init;

// Initialize a NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
- (nullable instancetype)initWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initializes and returns a newly created NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
+ (nullable instancetype)componentsWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initialize a NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
- (nullable instancetype)initWithString:(NSString *)URLString;

// Initializes and returns a newly created NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
+ (nullable instancetype)componentsWithString:(NSString *)URLString;

// Returns a URL created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
@property (nullable, readonly, copy) NSURL *URL;

// Returns a URL created from the NSURLComponents relative to a base URL. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
- (nullable NSURL *)URLRelativeToURL:(nullable NSURL *)baseURL;

// Returns a URL string created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
@property (nullable, readonly, copy) NSString *string NS_AVAILABLE(10_10, 8_0);

// Warning: IETF STD 66 (rfc3986) says the use of the format "user:password" in the userinfo subcomponent of a URI is deprecated because passing authentication information in clear text has proven to be a security risk. However, there are cases where this practice is still needed, and so the user and password components and methods are provided.

// Getting these properties removes any percent encoding these components may have (if the component allows percent encoding). Setting these properties assumes the subcomponent or component string is not percent encoded and will add percent encoding (if the component allows percent encoding).
@property (nullable, copy) NSString *scheme; // Attempting to set the scheme with an invalid scheme string will cause an exception.
@property (nullable, copy) NSString *user;
@property (nullable, copy) NSString *password;
@property (nullable, copy) NSString *host;
@property (nullable, copy) NSNumber *port; // Attempting to set a negative port number will cause an exception.
@property (nullable, copy) NSString *path;
@property (nullable, copy) NSString *query;
@property (nullable, copy) NSString *fragment;

// Getting these properties retains any percent encoding these components may have. Setting these properties assumes the component string is already correctly percent encoded. Attempting to set an incorrectly percent encoded string will cause an exception. Although ';' is a legal path character, it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
@property (nullable, copy) NSString *percentEncodedUser;
@property (nullable, copy) NSString *percentEncodedPassword;
@property (nullable, copy) NSString *percentEncodedHost;
@property (nullable, copy) NSString *percentEncodedPath;
@property (nullable, copy) NSString *percentEncodedQuery;
@property (nullable, copy) NSString *percentEncodedFragment;

/* These properties return the character range of a component in the URL string returned by -[NSURLComponents string]. If the component does not exist in the NSURLComponents object, {NSNotFound, 0} is returned. Note: Zero length components are legal. For example, the URL string "scheme://:@/?#" has a zero length user, password, host, query and fragment; the URL strings "scheme:" and "" both have a zero length path.
 */
@property (readonly) NSRange rangeOfScheme NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfUser NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPassword NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfHost NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPort NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPath NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfQuery NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfFragment NS_AVAILABLE(10_11, 9_0);

// The getter method that underlies the queryItems property parses the query string based on these delimiters and returns an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, in the order in which they appear in the original query string.  Note that a name may appear more than once in a single query string, so the name values are not guaranteed to be unique. If the NSURLComponents object has an empty query component, queryItems returns an empty NSArray. If the NSURLComponents object has no query component, queryItems returns nil.
// The setter method that underlies the queryItems property combines an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, into a query string and sets the NSURLComponents' query property. Passing an empty NSArray to setQueryItems sets the query component of the NSURLComponents object to an empty string. Passing nil to setQueryItems removes the query component of the NSURLComponents object.
// Note: If a name-value pair in a query is empty (i.e. the query string starts with '&', ends with '&', or has "&&" within it), you get a NSURLQueryItem with a zero-length name and and a nil value. If a query's name-value pair has nothing before the equals sign, you get a zero-length name. If a query's name-value pair has nothing after the equals sign, you get a zero-length value. If a query's name-value pair has no equals sign, the query name-value pair string is the name and you get a nil value.
@property (nullable, copy) NSArray<NSURLQueryItem *> *queryItems NS_AVAILABLE(10_10, 8_0);

@end


@interface NSCharacterSet (NSURLUtilities)

// Predefined character sets for the six URL components and subcomponents which allow percent encoding. These character sets are passed to -stringByAddingPercentEncodingWithAllowedCharacters:.

// Returns a character set containing the characters allowed in an URL's user subcomponent.
+ (NSCharacterSet *)URLUserAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's password subcomponent.
+ (NSCharacterSet *)URLPasswordAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's host subcomponent.
+ (NSCharacterSet *)URLHostAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's path component. ';' is a legal path character, but it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
+ (NSCharacterSet *)URLPathAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's query component.
+ (NSCharacterSet *)URLQueryAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's fragment component.
+ (NSCharacterSet *)URLFragmentAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

@end


@interface NSString (NSURLUtilities)

// Returns a new string made from the receiver by replacing all characters not in the allowedCharacters set with percent encoded characters. UTF-8 encoding is used to determine the correct percent encoded characters. Entire URL strings cannot be percent-encoded. This method is intended to percent-encode an URL component or subcomponent string, NOT the entire URL string. Any characters in allowedCharacters outside of the 7-bit ASCII range are ignored.
- (nullable NSString *)stringByAddingPercentEncodingWithAllowedCharacters:(NSCharacterSet *)allowedCharacters NS_AVAILABLE(10_9, 7_0);

// Returns a new string made from the receiver by replacing all percent encoded sequences with the matching UTF-8 characters.
@property (nullable, readonly, copy) NSString *stringByRemovingPercentEncoding NS_AVAILABLE(10_9, 7_0);


- (nullable NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use -stringByAddingPercentEncodingWithAllowedCharacters: instead, which always uses the recommended UTF-8 encoding, and which encodes for a specific URL component or subcomponent since each URL component or subcomponent has different rules for what characters are valid.");
- (nullable NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use -stringByRemovingPercentEncoding instead, which always uses the recommended UTF-8 encoding.");

@end


@interface NSURL (NSURLPathUtilities)
    
/* The following methods work on the path portion of a URL in the same manner that the NSPathUtilities methods on NSString do.
 */
+ (nullable NSURL *)fileURLWithPathComponents:(NSArray<NSString *> *)components NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSArray<NSString *> *pathComponents NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSString *lastPathComponent NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSString *pathExtension NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory NS_AVAILABLE(10_7, 5_0);
@property (nullable, readonly, copy) NSURL *URLByDeletingLastPathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *URLByDeletingPathExtension NS_AVAILABLE(10_6, 4_0);

/* The following methods work only on `file:` scheme URLs; for non-`file:` scheme URLs, these methods return the URL unchanged.
 */
@property (nullable, readonly, copy) NSURL *URLByStandardizingPath NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *URLByResolvingSymlinksInPath NS_AVAILABLE(10_6, 4_0);

@end


#if (TARGET_OS_MAC || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSFileSecurity encapsulates a file system object's security information. NSFileSecurity and CFFileSecurity are toll-free bridged. Use the CFFileSecurity API for access to the low-level file security properties encapsulated by NSFileSecurity.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSFileSecurity : NSObject <NSCopying, NSCoding>
- (nullable instancetype) initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
@end
#endif


/* deprecated interfaces
 */

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSURLClient and NSURLLoading are deprecated; use NSURLConnection instead.
 */

/* Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.
 */
@interface NSObject (NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidFinishLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidCancelLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
@end

@interface NSURL (NSURLLoading)
- (nullable NSData *)resourceDataUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (nullable id)propertyForKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* These attempt to write the given arguments for the resource specified by the URL; they return success or failure
 */
- (BOOL)setResourceData:(NSData *)data NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded
@end
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSData.h
/*	NSData.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;

NS_ASSUME_NONNULL_BEGIN

/****************	Read/Write Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataReadingOptions) {
    NSDataReadingMappedIfSafe =   1UL << 0,	// Hint to map the file in if possible and safe
    NSDataReadingUncached = 1UL << 1,	// Hint to get the file not to be cached in the kernel
    NSDataReadingMappedAlways NS_ENUM_AVAILABLE(10_7, 5_0) = 1UL << 3,	// Hint to map the file in if possible. This takes precedence over NSDataReadingMappedIfSafe if both are given.
    
    // Options with old names for NSData reading methods. Please stop using these old names.
    NSDataReadingMapped = NSDataReadingMappedIfSafe,	// Deprecated name for NSDataReadingMappedIfSafe
    NSMappedRead = NSDataReadingMapped,			// Deprecated name for NSDataReadingMapped
    NSUncachedRead = NSDataReadingUncached		// Deprecated name for NSDataReadingUncached
};

typedef NS_OPTIONS(NSUInteger, NSDataWritingOptions) {
    NSDataWritingAtomic = 1UL << 0,	// Hint to use auxiliary file when saving; equivalent to atomically:YES
    NSDataWritingWithoutOverwriting NS_ENUM_AVAILABLE(10_8, 6_0) = 1UL << 1, // Hint to  prevent overwriting an existing file. Cannot be combined with NSDataWritingAtomic.

    NSDataWritingFileProtectionNone NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0x10000000,
    NSDataWritingFileProtectionComplete NS_ENUM_AVAILABLE_IOS(4_0)                              = 0x20000000,
    NSDataWritingFileProtectionCompleteUnlessOpen NS_ENUM_AVAILABLE_IOS(5_0)                    = 0x30000000,
    NSDataWritingFileProtectionCompleteUntilFirstUserAuthentication NS_ENUM_AVAILABLE_IOS(5_0)  = 0x40000000,
    NSDataWritingFileProtectionMask NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0xf0000000,

    // Options with old names for NSData writing methods. Please stop using these old names.
    NSAtomicWrite = NSDataWritingAtomic	    // Deprecated name for NSDataWritingAtomic
};


/****************	Data Search Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataSearchOptions) {
    NSDataSearchBackwards = 1UL << 0,
    NSDataSearchAnchored = 1UL << 1
} NS_ENUM_AVAILABLE(10_6, 4_0);


/****************        Base 64 Options	****************/

typedef NS_OPTIONS(NSUInteger, NSDataBase64EncodingOptions) {
    // Use zero or one of the following to control the maximum line length after which a line ending is inserted. No line endings are inserted by default.
    NSDataBase64Encoding64CharacterLineLength = 1UL << 0,
    NSDataBase64Encoding76CharacterLineLength = 1UL << 1,

    // Use zero or more of the following to specify which kind of line ending is inserted. The default line ending is CR LF.
    NSDataBase64EncodingEndLineWithCarriageReturn = 1UL << 4,
    NSDataBase64EncodingEndLineWithLineFeed = 1UL << 5,

} NS_ENUM_AVAILABLE(10_9, 7_0);


typedef NS_OPTIONS(NSUInteger, NSDataBase64DecodingOptions) {
    // Use the following option to modify the decoding algorithm so that it ignores unknown non-Base64 bytes, including line ending characters.
    NSDataBase64DecodingIgnoreUnknownCharacters = 1UL << 0
} NS_ENUM_AVAILABLE(10_9, 7_0);


/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

@property (readonly) NSUInteger length;
/*
 The -bytes method returns a pointer to a contiguous region of memory managed by the receiver.
 If the regions of memory represented by the receiver are already contiguous, it does so in O(1) time, otherwise it may take longer
 Using -enumerateByteRangesUsingBlock: will be efficient for both contiguous and discontiguous data.
 */
@property (readonly) const void *bytes NS_RETURNS_INNER_POINTER;

@end

@interface NSData (NSExtendedData)

@property (readonly, copy) NSString *description;
- (void)getBytes:(void *)buffer length:(NSUInteger)length;
- (void)getBytes:(void *)buffer range:(NSRange)range;
- (BOOL)isEqualToData:(NSData *)other;
- (NSData *)subdataWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
- (BOOL)writeToFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (BOOL)writeToURL:(NSURL *)url options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (NSRange)rangeOfData:(NSData *)dataToFind options:(NSDataSearchOptions)mask range:(NSRange)searchRange NS_AVAILABLE(10_6, 4_0);

/*
 'block' is called once for each contiguous region of memory in the receiver (once total for contiguous NSDatas), until either all bytes have been enumerated, or the 'stop' parameter is set to YES.
 */
- (void) enumerateByteRangesUsingBlock:(void (^)(const void *bytes, NSRange byteRange, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);

@end

@interface NSData (NSDataCreation)

+ (instancetype)data;
+ (instancetype)dataWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path;
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url;
- (instancetype)initWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length deallocator:(nullable void (^)(void *bytes, NSUInteger length))deallocator NS_AVAILABLE(10_9, 7_0);
- (nullable instancetype)initWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
- (instancetype)initWithData:(NSData *)data;
+ (instancetype)dataWithData:(NSData *)data;

@end

@interface NSData (NSDataBase64Encoding)

/* Create an NSData from a Base-64 encoded NSString using the given options. By default, returns nil when the input is not recognized as valid Base-64.
*/
- (nullable instancetype)initWithBase64EncodedString:(NSString *)base64String options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64 encoded NSString from the receiver's contents using the given options.
*/
- (NSString *)base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create an NSData from a Base-64, UTF-8 encoded NSData. By default, returns nil when the input is not recognized as valid Base-64.
*/
- (nullable instancetype)initWithBase64EncodedData:(NSData *)base64Data options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64, UTF-8 encoded NSData from the receiver's contents using the given options.
*/
- (NSData *)base64EncodedDataWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

@end


@interface NSData (NSDeprecated)

- (void)getBytes:(void *)buffer NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "This method is unsafe because it could potentially cause buffer overruns. Use -getBytes:length: instead.");
+ (nullable id)dataWithContentsOfMappedFile:(NSString *)path NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use +dataWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");
- (nullable id)initWithContentsOfMappedFile:(NSString *)path  NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use -initWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");

/* These methods first appeared in NSData.h on OS X 10.9 and iOS 7.0. They are deprecated in the same releases in favor of the methods in the NSDataBase64Encoding category. However, these methods have existed for several releases, so they may be used for applications targeting releases prior to OS X 10.9 and iOS 7.0.
*/
- (nullable id)initWithBase64Encoding:(NSString *)base64String NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);
- (NSString *)base64Encoding NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData

@property (readonly) void *mutableBytes NS_RETURNS_INNER_POINTER;
@property NSUInteger length;

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;
- (void)appendData:(NSData *)other;
- (void)increaseLengthBy:(NSUInteger)extraLength;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
- (void)resetBytesInRange:(NSRange)range;
- (void)setData:(NSData *)data;
- (void)replaceBytesInRange:(NSRange)range withBytes:(nullable const void *)replacementBytes length:(NSUInteger)replacementLength;

@end

@interface NSMutableData (NSMutableDataCreation)

+ (nullable instancetype)dataWithCapacity:(NSUInteger)aNumItems;
+ (nullable instancetype)dataWithLength:(NSUInteger)length;
- (nullable instancetype)initWithCapacity:(NSUInteger)capacity;
- (nullable instancetype)initWithLength:(NSUInteger)length;

@end

/****************	    Purgeable Data	****************/

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSPurgeableData : NSMutableData <NSDiscardableContent> {
@private
    NSUInteger _length;
    int32_t _accessCount;
    uint8_t _private[32];
    void *_reserved;
}

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDecimalNumber.h
/*	NSDecimalNumber.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>
#import <Foundation/NSScanner.h>
#import <Foundation/NSDecimal.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN

/***************	Exceptions		***********/

FOUNDATION_EXPORT NSString * const NSDecimalNumberExactnessException;
FOUNDATION_EXPORT NSString * const NSDecimalNumberOverflowException;
FOUNDATION_EXPORT NSString * const NSDecimalNumberUnderflowException;
FOUNDATION_EXPORT NSString * const NSDecimalNumberDivideByZeroException;

/***************	Rounding and Exception behavior		***********/

@class NSDecimalNumber;

@protocol NSDecimalNumberBehaviors

- (NSRoundingMode)roundingMode;

- (short)scale;
    // The scale could return NO_SCALE for no defined scale.

- (nullable NSDecimalNumber *)exceptionDuringOperation:(SEL)operation error:(NSCalculationError)error leftOperand:(NSDecimalNumber *)leftOperand rightOperand:(nullable NSDecimalNumber *)rightOperand;
    // Receiver can raise, return a new value, or return nil to ignore the exception.

@end

/***************	NSDecimalNumber: the class		***********/

@interface NSDecimalNumber : NSNumber {
@private
    signed   int _exponent:8;
    unsigned int _length:4;
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:1;
    unsigned int _hasExternalRefCount:1;
    unsigned int _refs:16;
    unsigned short _mantissa[0]; /* GCC */
}

- (instancetype)initWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
- (instancetype)initWithDecimal:(NSDecimal)dcm NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithString:(nullable NSString *)numberValue;
- (instancetype)initWithString:(nullable NSString *)numberValue locale:(nullable id)locale;

- (NSString *)descriptionWithLocale:(nullable id)locale;

@property (readonly) NSDecimal decimalValue;

+ (NSDecimalNumber *)decimalNumberWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
+ (NSDecimalNumber *)decimalNumberWithDecimal:(NSDecimal)dcm;
+ (NSDecimalNumber *)decimalNumberWithString:(nullable NSString *)numberValue;
+ (NSDecimalNumber *)decimalNumberWithString:(nullable NSString *)numberValue locale:(nullable id)locale;

+ (NSDecimalNumber *)zero;
+ (NSDecimalNumber *)one;
+ (NSDecimalNumber *)minimumDecimalNumber;
+ (NSDecimalNumber *)maximumDecimalNumber;
+ (NSDecimalNumber *)notANumber;

- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByRaisingToPower:(NSUInteger)power;
- (NSDecimalNumber *)decimalNumberByRaisingToPower:(NSUInteger)power withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power;
- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;


- (NSDecimalNumber *)decimalNumberByRoundingAccordingToBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;
    // Round to the scale of the behavior.

- (NSComparisonResult)compare:(NSNumber *)decimalNumber;
    // compare two NSDecimalNumbers

+ (void)setDefaultBehavior:(id <NSDecimalNumberBehaviors>)behavior;

+ (id <NSDecimalNumberBehaviors>)defaultBehavior;
    // One behavior per thread - The default behavior is
    //   rounding mode: NSRoundPlain
    //   scale: No defined scale (full precision)
    //   ignore exactnessException
    //   raise on overflow, underflow and divide by zero.

@property (readonly) const char *objCType NS_RETURNS_INNER_POINTER;
    // return 'd' for double
    
@property (readonly) double doubleValue;
    // return an approximate double value
    
@end

/***********	A class for defining common behaviors		*******/

@interface NSDecimalNumberHandler : NSObject <NSDecimalNumberBehaviors, NSCoding> {
  @private
    signed int _scale:16;
    unsigned _roundingMode:3;
    unsigned _raiseOnExactness:1;
    unsigned _raiseOnOverflow:1;
    unsigned _raiseOnUnderflow:1;
    unsigned _raiseOnDivideByZero:1;
    unsigned _unused:9;
    void *_reserved2;
    void *_reserved;
}

+ (NSDecimalNumberHandler *)defaultDecimalNumberHandler;
    // rounding mode: NSRoundPlain
    // scale: No defined scale (full precision)
    // ignore exactnessException (return nil)
    // raise on overflow, underflow and divide by zero.

- (instancetype)initWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero NS_DESIGNATED_INITIALIZER;

+ (instancetype)decimalNumberHandlerWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero;

@end

/***********	Extensions to other classes		*******/

@interface NSNumber (NSDecimalNumberExtensions)

@property (readonly) NSDecimal decimalValue;
    // Could be silently inexact for float and double.

@end

@interface NSScanner (NSDecimalNumberScanning)

- (BOOL)scanDecimal:(nullable NSDecimal *)dcm;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSHTTPCookieStorage.h
/*	
    NSHTTPCookieStorage.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;
@class NSHTTPCookie;
@class NSURL;
@class NSDate;
@class NSURLSessionTask;
@class NSSortDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*!
    @enum NSHTTPCookieAcceptPolicy
    @abstract Values for the different cookie accept policies
    @constant NSHTTPCookieAcceptPolicyAlways Accept all cookies
    @constant NSHTTPCookieAcceptPolicyNever Reject all cookies
    @constant NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain Accept cookies
    only from the main document domain
*/
typedef NS_ENUM(NSUInteger, NSHTTPCookieAcceptPolicy) {
    NSHTTPCookieAcceptPolicyAlways,
    NSHTTPCookieAcceptPolicyNever,
    NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain
};


@class NSHTTPCookieStorageInternal;

/*!
    @class NSHTTPCookieStorage 
    @discussion NSHTTPCookieStorage implements a singleton object (shared
    instance) which manages the shared cookie store.  It has methods
    to allow clients to set and remove cookies, and get the current
    set of cookies.  It also has convenience methods to parse and
    generate cookie-related HTTP header fields.
*/

@interface NSHTTPCookieStorage : NSObject
{
    @private
    NSHTTPCookieStorageInternal *_internal;
}

/*!
    @method sharedHTTPCookieStorage
    @abstract Get the shared cookie storage in the default location.
    @result The shared cookie storage
*/
+ (NSHTTPCookieStorage *)sharedHTTPCookieStorage;

/*!
    @method sharedCookieStorageForGroupContainerIdentifier:
    @abstract Get the cookie storage for the container associated with the specified application group identifier
    @param identifier The application group identifier
    @result A cookie storage with a persistent store in the application group container
    @discussion By default, applications and associated app extensions have different data containers, which means
    that the sharedHTTPCookieStorage singleton will refer to different persistent cookie stores in an application and
    any app extensions that it contains. This method allows clients to create a persistent cookie storage that can be
    shared among all applications and extensions with access to the same application group. Subsequent calls to this
    method with the same identifier will return the same cookie storage instance.
 */
+ (NSHTTPCookieStorage *)sharedCookieStorageForGroupContainerIdentifier:(NSString *)identifier NS_AVAILABLE(10_11, 9_0);

/*!
    @method cookies
    @abstract Get all the cookies
    @result An NSArray of NSHTTPCookies
*/
@property (nullable , readonly, copy) NSArray<NSHTTPCookie *> *cookies;

/*!
    @method setCookie:
    @abstract Set a cookie
    @discussion The cookie will override an existing cookie with the
    same name, domain and path, if any.
*/
- (void)setCookie:(NSHTTPCookie *)cookie;

/*!
    @method deleteCookie:
    @abstract Delete the specified cookie
*/
- (void)deleteCookie:(NSHTTPCookie *)cookie;

/*!
 @method removeCookiesSince:
 @abstract Delete all cookies from the cookie storage since the provided date.
 */
- (void)removeCookiesSinceDate:(NSDate *)date NS_AVAILABLE(10_10, 8_0);

/*!
    @method cookiesForURL:
    @abstract Returns an array of cookies to send to the given URL.
    @param URL The URL for which to get cookies.
    @result an NSArray of NSHTTPCookie objects.
    @discussion The cookie manager examines the cookies it stores and
    includes those which should be sent to the given URL. You can use
    <tt>+[NSCookie requestHeaderFieldsWithCookies:]</tt> to turn this array
    into a set of header fields to add to a request.
*/
- (nullable NSArray<NSHTTPCookie *> *)cookiesForURL:(NSURL *)URL;

/*!
    @method setCookies:forURL:mainDocumentURL:
    @abstract Adds an array cookies to the cookie store, following the
    cookie accept policy.
    @param cookies The cookies to set.
    @param URL The URL from which the cookies were sent.
    @param mainDocumentURL The main document URL to be used as a base for the "same
    domain as main document" policy.
    @discussion For mainDocumentURL, the caller should pass the URL for
    an appropriate main document, if known. For example, when loading
    a web page, the URL of the main html document for the top-level
    frame should be passed. To save cookies based on a set of response
    headers, you can use <tt>+[NSCookie
    cookiesWithResponseHeaderFields:forURL:]</tt> on a header field
    dictionary and then use this method to store the resulting cookies
    in accordance with policy settings.
*/
- (void)setCookies:(NSArray<NSHTTPCookie *> *)cookies forURL:(nullable NSURL *)URL mainDocumentURL:(nullable NSURL *)mainDocumentURL;

/*!
    @method cookieAcceptPolicy
    @abstract The cookie accept policy preference of the
    receiver.
*/
@property NSHTTPCookieAcceptPolicy cookieAcceptPolicy;

/*!
  @method sortedCookiesUsingDescriptors:
  @abstract Returns an array of all cookies in the store, sorted according to the key value and sorting direction of the NSSortDescriptors specified in the parameter.
  @param sortOrder an array of NSSortDescriptors which represent the preferred sort order of the resulting array.
  @discussion proper sorting of cookies may require extensive string conversion, which can be avoided by allowing the system to perform the sorting.  This API is to be preferred over the more generic -[NSHTTPCookieStorage cookies] API, if sorting is going to be performed.
*/
- (NSArray<NSHTTPCookie *> *)sortedCookiesUsingDescriptors:(NSArray<NSSortDescriptor *> *) sortOrder NS_AVAILABLE(10_7, 5_0);

@end

@interface NSHTTPCookieStorage (NSURLSessionTaskAdditions)
- (void)storeCookies:(NSArray<NSHTTPCookie *> *)cookies forTask:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
- (void)getCookiesForTask:(NSURLSessionTask *)task completionHandler:(void (^) (NSArray<NSHTTPCookie *> * __nullable cookies))completionHandler NS_AVAILABLE(10_10, 8_0);
@end

/*!
    @const NSHTTPCookieManagerAcceptPolicyChangedNotification
    @discussion Name of notification that should be posted to the
    distributed notification center whenever the accept cookies
    preference is changed
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieManagerAcceptPolicyChangedNotification;

/*!
    @const NSHTTPCookieManagerCookiesChangedNotification
    @abstract Notification sent when the set of cookies changes
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieManagerCookiesChangedNotification;

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSOrthography.h
/*	NSOrthography.h
	Copyright (c) 2008-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>;

NS_ASSUME_NONNULL_BEGIN

/* NSOrthography is a class used to describe the linguistic content of a piece of text, especially for the purposes of spelling and grammar checking.  It describes (a) which scripts the text contains, (b) a dominant language and possibly other languages for each of these scripts, and (c) a dominant script and language for the text as a whole.  Scripts are uniformly described by standard four-letter tags (Latn, Grek, Cyrl, etc.) with the supertags Jpan and Kore typically used for Japanese and Korean text, Hans and Hant for Chinese text; the tag Zyyy is used if a specific script cannot be identified.  Languages are uniformly described by BCP-47 tags, preferably in canonical form; the tag und is used if a specific language cannot be determined. */

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSOrthography : NSObject <NSCopying, NSCoding>

/* These are the primitive properties which a subclass must implement.  The dominantScript should be a script tag (such as Latn, Cyrl, and so forth) and the languageMap should be a dictionary whose keys are script tags and whose values are arrays of language tags (such as en, fr, de, and so forth). */
@property (readonly, copy) NSString *dominantScript;
@property (readonly, copy) NSDictionary<NSString *, NSArray<NSString *> *> *languageMap;
- (instancetype)initWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSOrthography (NSOrthographyExtended)

/* languagesForScript: returns the list of languages for the specified script, and dominantLanguageForScript: returns the first item on that list. */
- (nullable NSArray<NSString *> *)languagesForScript:(NSString *)script NS_AVAILABLE(10_6, 4_0);
- (nullable NSString *)dominantLanguageForScript:(NSString *)script NS_AVAILABLE(10_6, 4_0);

/*  The dominantLanguage is the first in the list of languages for the dominant script, allScripts includes the dominant script and all others appearing as keys in the language map, and allLanguages includes all languages appearing in the values of the language map. */
@property (readonly, copy) NSString *dominantLanguage NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSArray<NSString *> *allScripts NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSArray<NSString *> *allLanguages NS_AVAILABLE(10_6, 4_0);

@end

@interface NSOrthography (NSOrthographyCreation)

+ (instancetype)orthographyWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map NS_AVAILABLE(10_6, 4_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLError.h
/*	
    NSURLError.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.
    
    Public header file.
*/
#if TARGET_OS_IPHONE
#if __has_include(<CFNetwork/CFNetwork.h>)
#import <CFNetwork/CFNetwork.h>
#endif
#elif TARGET_OS_WIN32
#import <CFNetwork/CFNetwork.h>
#else
#import <CoreServices/CoreServices.h>
#endif

#import <Foundation/NSObjCRuntime.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

/*
    @discussion Constants used by NSError to differentiate between "domains" of error codes, serving as a discriminator for error codes that originate from different subsystems or sources.
    @constant NSURLErrorDomain Indicates an NSURL error.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorDomain;

/*!
    @const NSURLErrorFailingURLErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the URL which caused a load to fail.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSURLErrorFailingURLStringErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSString object for the URL which caused a load to fail.
    @discussion This constant supersedes NSErrorFailingURLStringKey, which was deprecated in Mac OS X 10.6.  Both constants refer to the same value for backward-compatibility, but this symbol name has a better prefix.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLStringErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSErrorFailingURLStringKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSString object for the URL which caused a load to fail.
    @discussion This constant is deprecated in Mac OS X 10.6, and is superseded by NSURLErrorFailingURLStringErrorKey.  Both constants refer to the same value for backward-compatibility, but the new symbol name has a better prefix.
*/
FOUNDATION_EXPORT NSString * const NSErrorFailingURLStringKey NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);

/*!
    @const NSURLErrorFailingURLPeerTrustErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the SecTrustRef object representing the state of a failed SSL handshake.
 */
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLPeerTrustErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSURLErrorBackgroundTaskCancelledReasonKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSNumber corresponding to the reason why a background
	NSURLSessionTask was cancelled
 */
FOUNDATION_EXPORT NSString * const NSURLErrorBackgroundTaskCancelledReasonKey NS_AVAILABLE(10_10, 8_0);

/*!
    @enum Codes associated with NSURLErrorBackgroundTaskCancelledReasonKey
    @abstract Constants used by NSError to indicate why a background NSURLSessionTask was cancelled.
 */

NS_ENUM(NSInteger)
{
    NSURLErrorCancelledReasonUserForceQuitApplication =    0,
    NSURLErrorCancelledReasonBackgroundUpdatesDisabled =   1,
    NSURLErrorCancelledReasonInsufficientSystemResources NS_ENUM_AVAILABLE(10_10, 8_0) = 2,
    
} NS_ENUM_AVAILABLE(10_10, 7_0);

/*!
    @enum NSURL-related Error Codes
    @abstract Constants used by NSError to indicate errors in the NSURL domain
*/
NS_ENUM(NSInteger)
{
    NSURLErrorUnknown = 			-1,
    NSURLErrorCancelled = 			-999,
    NSURLErrorBadURL = 				-1000,
    NSURLErrorTimedOut = 			-1001,
    NSURLErrorUnsupportedURL = 			-1002,
    NSURLErrorCannotFindHost = 			-1003,
    NSURLErrorCannotConnectToHost = 		-1004,
    NSURLErrorNetworkConnectionLost = 		-1005,
    NSURLErrorDNSLookupFailed = 		-1006,
    NSURLErrorHTTPTooManyRedirects = 		-1007,
    NSURLErrorResourceUnavailable = 		-1008,
    NSURLErrorNotConnectedToInternet = 		-1009,
    NSURLErrorRedirectToNonExistentLocation = 	-1010,
    NSURLErrorBadServerResponse = 		-1011,
    NSURLErrorUserCancelledAuthentication = 	-1012,
    NSURLErrorUserAuthenticationRequired = 	-1013,
    NSURLErrorZeroByteResource = 		-1014,
    NSURLErrorCannotDecodeRawData =             -1015,
    NSURLErrorCannotDecodeContentData =         -1016,
    NSURLErrorCannotParseResponse =             -1017,
    NSURLErrorAppTransportSecurityRequiresSecureConnection NS_ENUM_AVAILABLE(10_11, 9_0) = -1022,
    NSURLErrorFileDoesNotExist = 		-1100,
    NSURLErrorFileIsDirectory = 		-1101,
    NSURLErrorNoPermissionsToReadFile = 	-1102,
    NSURLErrorDataLengthExceedsMaximum NS_ENUM_AVAILABLE(10_5, 2_0) =	-1103,
    
    // SSL errors
    NSURLErrorSecureConnectionFailed = 		-1200,
    NSURLErrorServerCertificateHasBadDate = 	-1201,
    NSURLErrorServerCertificateUntrusted = 	-1202,
    NSURLErrorServerCertificateHasUnknownRoot = -1203,
    NSURLErrorServerCertificateNotYetValid = 	-1204,
    NSURLErrorClientCertificateRejected = 	-1205,
    NSURLErrorClientCertificateRequired =	-1206,
    NSURLErrorCannotLoadFromNetwork = 		-2000,
    
    // Download and file I/O errors
    NSURLErrorCannotCreateFile = 		-3000,
    NSURLErrorCannotOpenFile = 			-3001,
    NSURLErrorCannotCloseFile = 		-3002,
    NSURLErrorCannotWriteToFile = 		-3003,
    NSURLErrorCannotRemoveFile = 		-3004,
    NSURLErrorCannotMoveFile = 			-3005,
    NSURLErrorDownloadDecodingFailedMidStream = -3006,
    NSURLErrorDownloadDecodingFailedToComplete =-3007,

    NSURLErrorInternationalRoamingOff NS_ENUM_AVAILABLE(10_7, 3_0) =         -1018,
    NSURLErrorCallIsActive NS_ENUM_AVAILABLE(10_7, 3_0) =                    -1019,
    NSURLErrorDataNotAllowed NS_ENUM_AVAILABLE(10_7, 3_0) =                  -1020,
    NSURLErrorRequestBodyStreamExhausted NS_ENUM_AVAILABLE(10_7, 3_0) =      -1021,
    
    NSURLErrorBackgroundSessionRequiresSharedContainer NS_ENUM_AVAILABLE(10_10, 8_0) = -995,
    NSURLErrorBackgroundSessionInUseByAnotherProcess NS_ENUM_AVAILABLE(10_10, 8_0) = -996,
    NSURLErrorBackgroundSessionWasDisconnected NS_ENUM_AVAILABLE(10_10, 8_0)= -997,
};

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSPointerFunctions.h
/*
 *  NSPointerFunctions.h
 *
 *  Copyright (c) 2005-2015, Apple Inc. All rights reserved.
 *
 */
 

#import <Foundation/NSObject.h>

#if !defined(__FOUNDATION_NSPOINTERFUNCTIONS__)
#define __FOUNDATION_NSPOINTERFUNCTIONS__ 1

NS_ASSUME_NONNULL_BEGIN

/*

  NSPointerFunctions

  This object defines callout functions appropriate for managing a pointer reference held somewhere else.

  Used by NSHashTable, NSMapTable, and NSPointerArray, this object defines the acquision and retention behavior for the pointers provided to these collection objects.

   The functions are separated into two clusters - those that define "personality", such as object or cString, and those that describe memory management issues such as a memory deallocation function.  Common personalities and memory manager selections are provided as enumerations, and further customization is provided by methods such that the composition of the actual list of functions is done opaquely such that they can be extended in the future.

  The pointer collections copy NSPointerFunctions objects on input and output, and so NSPointerFunctions is not usefully subclassed.

*/


typedef NS_OPTIONS(NSUInteger, NSPointerFunctionsOptions) {
    // Memory options are mutually exclusive
    
    // default is strong
    NSPointerFunctionsStrongMemory NS_ENUM_AVAILABLE(10_5, 6_0) = (0UL << 0),       // use strong write-barrier to backing store; use GC memory on copyIn
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
    NSPointerFunctionsZeroingWeakMemory NS_ENUM_DEPRECATED_MAC(10_5, 10_8) = (1UL << 0),  // deprecated; uses GC weak read and write barriers, and dangling pointer behavior otherwise 
#endif
    NSPointerFunctionsOpaqueMemory NS_ENUM_AVAILABLE(10_5, 6_0) = (2UL << 0),
    NSPointerFunctionsMallocMemory NS_ENUM_AVAILABLE(10_5, 6_0) = (3UL << 0),       // free() will be called on removal, calloc on copyIn
    NSPointerFunctionsMachVirtualMemory NS_ENUM_AVAILABLE(10_5, 6_0) = (4UL << 0),
    NSPointerFunctionsWeakMemory NS_ENUM_AVAILABLE(10_8, 6_0) = (5UL << 0),         // uses weak read and write barriers appropriate for ARC or GC
    
    // Personalities are mutually exclusive
    // default is object.  As a special case, 'strong' memory used for Objects will do retain/release under non-GC
    NSPointerFunctionsObjectPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (0UL << 8),         // use -hash and -isEqual, object description
    NSPointerFunctionsOpaquePersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (1UL << 8),         // use shifted pointer hash and direct equality
    NSPointerFunctionsObjectPointerPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (2UL << 8),  // use shifted pointer hash and direct equality, object description
    NSPointerFunctionsCStringPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (3UL << 8),        // use a string hash and strcmp, description assumes UTF-8 contents; recommended for UTF-8 (or ASCII, which is a subset) only cstrings
    NSPointerFunctionsStructPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (4UL << 8),         // use a memory hash and memcmp (using size function you must set)
    NSPointerFunctionsIntegerPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = (5UL << 8),        // use unshifted value as hash & equality

    NSPointerFunctionsCopyIn NS_ENUM_AVAILABLE(10_5, 6_0) = (1UL << 16),      // the memory acquire function will be asked to allocate and copy items on input
};

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSPointerFunctions : NSObject <NSCopying>
// construction
- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options NS_DESIGNATED_INITIALIZER;
+ (NSPointerFunctions *)pointerFunctionsWithOptions:(NSPointerFunctionsOptions)options;

// pointer personality functions
@property (nullable) NSUInteger (*hashFunction)(const void *item, NSUInteger (* __nullable size)(const void *item));
@property (nullable) BOOL (*isEqualFunction)(const void *item1, const void*item2, NSUInteger (* __nullable size)(const void *item));
@property (nullable) NSUInteger (*sizeFunction)(const void *item);
@property (nullable) NSString * __nullable (*descriptionFunction)(const void *item);

// custom memory configuration
@property (nullable) void (*relinquishFunction)(const void *item, NSUInteger (* __nullable size)(const void *item));
@property (nullable) void * __nonnull (*acquireFunction)(const void *src, NSUInteger (* __nullable size)(const void *item), BOOL shouldCopy);

// GC requires that read and write barrier functions be used when pointers are from GC memory
@property BOOL usesStrongWriteBarrier;             // pointers should (not) be assigned using the GC strong write barrier
@property BOOL usesWeakReadAndWriteBarriers;       // pointers should (not) use GC weak read and write barriers
@end

NS_ASSUME_NONNULL_END

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

#else

#if defined(__has_include)
#if __has_include(<Foundation/NSPointerFunctionsPriv.h>)
#include <Foundation/NSPointerFunctionsPriv.h>
#endif
#endif

#endif

/*
   Cheat Sheet
 
   Long Integers (other than zero)   (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsIntegerPersonality)
      useful for, well, anything that can be jammed into a long int
 
   Strongly held objects             (NSPointerFunctionsStrongMemory | NSPointerFunctionsObjectPersonality)
      used for retained objects under ARC and/or manual retain-release, or GC; uses isEqual: as necessary
 
   Zeroing weak object references    (NSPointerFunctionsWeakMemory   | NSPointerFunctionsObjectPersonality)
      used to hold references that won't keep the object alive.  Note that objects implementing custom retain-release must also implement allowsWeakReference and retainWeakReference (or are using GC instead)
 
   Unsafe unretained objects         (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsObjectPersonality)
      used where zeroing weak is not possible and where, somehow, the objects are removed before being deallocated.
 
   C String where table keeps copy   (NSPointerFunctionsStrongMemory | NSPointerFunctionsCStringPersonality | NSPointerFunctionsCopyIn)
      used to capture a null-terminated string from a source with unknown lifetime.  Keeps string alive under GC.  Under ARC/RR, table will deallocate its copy when removed.  Generally, "C Strings" is a term for UTF8 strings as well.
 
   C String, owned elsewhere         (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsCStringPersonality)
      used to hold C string pointers to storage not at all managed by the table.
 
 
   The NSPointerFunctionsObjectPersonality dictates using isEqual: for the equality test.  In some situations == should be used, such as when trying to build a cache of unique immutable "value" objects that implement isEqual:.  In those cases use NSPointerFunctionsObjectPointerPersonality instead.

   Deprecated
 
   GC Zeroing - ARC/RR unsafe weak   (NSPointerFunctionsZeroingWeakMemory   | NSPointerFunctionsObjectPersonality)
       under GC these are zeroing weak but under manual retain-release (or ARC) these are unsafe unretained. Move to NSPointerFunctionsWeakMemory or NSPointerFunctionsOpaqueMemory instead.
 
 
   Example
       Lets say you have a source of C Strings that often repeat and you need to provide unique NSString counterparts.  For this you likely want a NSMapTable with strong copy-in C Strings as the keys and weak NSString values.  As long as the NSString counterparts are in use, they stay in the table and don't need to be created each time they show up.
       NSMapTable *mt = [[NSMapTable alloc] 
                            initWithKeyOptions: (NSPointerFunctionsStrongMemory | NSPointerFunctionsCStringPersonality | NSPointerFunctionsCopyIn)
                            valueOptions:(NSPointerFunctionsWeakMemory   | NSPointerFunctionsObjectPersonality)
                            capacity:0];
       ...
       // given a C string, look it up and, if not found, create and save the NSString version in the table
       const char *cString = ...;
       NSString *result = [mt objectForKey:(id)cString];
       if (!result) {
            result = [NSString stringWithCString:cString];
            [mt setObject:result forKey:(id)cString];
        }
        return result;
*/

#endif

// ==========  Foundation.framework/Headers/NSException.h
/*	NSException.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <stdarg.h>
#import <setjmp.h>

@class NSString, NSDictionary, NSArray<ObjectType>, NSNumber;

NS_ASSUME_NONNULL_BEGIN

/***************	Generic Exception names		***************/

FOUNDATION_EXPORT NSString * const NSGenericException;
FOUNDATION_EXPORT NSString * const NSRangeException;
FOUNDATION_EXPORT NSString * const NSInvalidArgumentException;
FOUNDATION_EXPORT NSString * const NSInternalInconsistencyException;

FOUNDATION_EXPORT NSString * const NSMallocException;

FOUNDATION_EXPORT NSString * const NSObjectInaccessibleException;
FOUNDATION_EXPORT NSString * const NSObjectNotAvailableException;
FOUNDATION_EXPORT NSString * const NSDestinationInvalidException;
    
FOUNDATION_EXPORT NSString * const NSPortTimeoutException;
FOUNDATION_EXPORT NSString * const NSInvalidSendPortException;
FOUNDATION_EXPORT NSString * const NSInvalidReceivePortException;
FOUNDATION_EXPORT NSString * const NSPortSendException;
FOUNDATION_EXPORT NSString * const NSPortReceiveException;

FOUNDATION_EXPORT NSString * const NSOldStyleException;

/***************	Exception object	***************/

#if __OBJC2__
__attribute__((__objc_exception__))
#endif
@interface NSException : NSObject <NSCopying, NSCoding> {
    @private
    NSString		*name;
    NSString		*reason;
    NSDictionary	*userInfo;
    id			reserved;
}

+ (NSException *)exceptionWithName:(NSString *)name reason:(nullable NSString *)reason userInfo:(nullable NSDictionary *)userInfo;
- (instancetype)initWithName:(NSString *)aName reason:(nullable NSString *)aReason userInfo:(nullable NSDictionary *)aUserInfo NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) NSString *name;
@property (nullable, readonly, copy) NSString *reason;
@property (nullable, readonly, copy) NSDictionary *userInfo;

@property (readonly, copy) NSArray<NSNumber *> *callStackReturnAddresses NS_AVAILABLE(10_5, 2_0);
@property (readonly, copy) NSArray<NSString *> *callStackSymbols NS_AVAILABLE(10_6, 4_0);

- (void)raise;

@end

@interface NSException (NSExceptionRaisingConveniences)

+ (void)raise:(NSString *)name format:(NSString *)format, ... NS_FORMAT_FUNCTION(2,3);
+ (void)raise:(NSString *)name format:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(2,0);

@end


#define NS_DURING		@try {
#define NS_HANDLER		} @catch (NSException *localException) {
#define NS_ENDHANDLER		}
#define NS_VALUERETURN(v,t)	return (v)
#define NS_VOIDRETURN		return


typedef void NSUncaughtExceptionHandler(NSException *exception);

FOUNDATION_EXPORT NSUncaughtExceptionHandler * __nullable NSGetUncaughtExceptionHandler(void);
FOUNDATION_EXPORT void NSSetUncaughtExceptionHandler(NSUncaughtExceptionHandler * __nullable);


#if __clang__
#define __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wformat-extra-args\"")

#define __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS _Pragma("clang diagnostic pop")
#else
#define __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS
#define __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

@class NSAssertionHandler;

#if (defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__)) || (defined(__cplusplus) && (201103L <= __cplusplus))

#if !defined(NS_BLOCK_ASSERTIONS)

#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...)	\
    do {				\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {		\
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
		object:self file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}				\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) \
    do {				\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {		\
            NSString *__assert_fn__ = [NSString stringWithUTF8String:__PRETTY_FUNCTION__]; \
            __assert_fn__ = __assert_fn__ ? __assert_fn__ : @"<Unknown Function>"; \
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:__assert_fn__ \
		file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}				\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif

#else // NS_BLOCK_ASSERTIONS defined

#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...) do {} while (0)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) do {} while (0)
#endif

#endif

#if !defined(_NSAssertBody)
#define NSAssert1(condition, desc, arg1) NSAssert((condition), (desc), (arg1))
#define NSAssert2(condition, desc, arg1, arg2) NSAssert((condition), (desc), (arg1), (arg2))
#define NSAssert3(condition, desc, arg1, arg2, arg3) NSAssert((condition), (desc), (arg1), (arg2), (arg3))
#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
#define NSParameterAssert(condition) NSAssert((condition), @"Invalid parameter not satisfying: %@", @#condition)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert1(condition, desc, arg1) NSCAssert((condition), (desc), (arg1))
#define NSCAssert2(condition, desc, arg1, arg2) NSCAssert((condition), (desc), (arg1), (arg2))
#define NSCAssert3(condition, desc, arg1, arg2, arg3) NSCAssert((condition), (desc), (arg1), (arg2), (arg3))
#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
#define NSCParameterAssert(condition) NSCAssert((condition), @"Invalid parameter not satisfying: %@", @#condition)
#endif

#endif


/* Non-vararg implementation of asserts (ignore) */
#if !defined(NS_BLOCK_ASSERTIONS)
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {				\
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {				\
            NSString *__assert_fn__ = [NSString stringWithUTF8String:__PRETTY_FUNCTION__]; \
            __assert_fn__ = __assert_fn__ ? __assert_fn__ : @"<Unknown Function>"; \
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:__assert_fn__ file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif
#else
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#endif


/*
 * Asserts to use in Objective-C method bodies
 */
 
#if !defined(NSAssert)
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5)) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSAssert3(condition, desc, arg1, arg2, arg3)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSAssert2(condition, desc, arg1, arg2)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSAssert1(condition, desc, arg1)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSAssert(condition, desc)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), 0, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

#if !defined(NSParameterAssert)
#define NSParameterAssert(condition)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif


#if !defined(NSCAssert)
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5)) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSCAssert3(condition, desc, arg1, arg2, arg3)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSCAssert2(condition, desc, arg1, arg2)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSCAssert1(condition, desc, arg1)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

#define NSCAssert(condition, desc)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), 0, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

#if !defined(NSCParameterAssert)
#define NSCParameterAssert(condition)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif


FOUNDATION_EXPORT NSString * const NSAssertionHandlerKey NS_AVAILABLE(10_6, 4_0);

@interface NSAssertionHandler : NSObject {
    @private
    void *_reserved;
}

+ (NSAssertionHandler *)currentHandler;

- (void)handleFailureInMethod:(SEL)selector object:(id)object file:(NSString *)fileName lineNumber:(NSInteger)line description:(nullable NSString *)format,... NS_FORMAT_FUNCTION(5,6);

- (void)handleFailureInFunction:(NSString *)functionName file:(NSString *)fileName lineNumber:(NSInteger)line description:(nullable NSString *)format,... NS_FORMAT_FUNCTION(4,5);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLSession.h
/*	NSURLSession.h
	Copyright (c) 2013-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLRequest.h>
#import <Foundation/NSHTTPCookieStorage.h>

#include <Security/SecureTransport.h>

@class NSString;
@class NSURL;
@class NSError;
@class NSArray<ObjectType>;
@class NSDictionary<KeyType, ObjectType>;
@class NSInputStream;
@class NSOutputStream;
@class NSData;
@class NSOperationQueue;

@class NSURLCache;
@class NSURLResponse;
@class NSHTTPURLResponse;
@class NSHTTPCookie;
@class NSCachedURLResponse;
@class NSURLAuthenticationChallenge;
@class NSURLProtectionSpace;
@class NSURLCredential;
@class NSURLCredentialStorage;
@class NSURLSessionDataTask;
@class NSURLSessionUploadTask;
@class NSURLSessionDownloadTask;
@class NSNetService;

/*

 NSURLSession is a replacement API for NSURLConnection.  It provides
 options that affect the policy of, and various aspects of the
 mechanism by which NSURLRequest objects are retrieved from the
 network.

 An NSURLSession may be bound to a delegate object.  The delegate is
 invoked for certain events during the lifetime of a session, such as
 server authentication or determining whether a resource to be loaded
 should be converted into a download.
 
 NSURLSession instances are threadsafe.

 The default NSURLSession uses a system provided delegate and is
 appropriate to use in place of existing code that uses
 +[NSURLConnection sendAsynchronousRequest:queue:completionHandler:]

 An NSURLSession creates NSURLSessionTask objects which represent the
 action of a resource being loaded.  These are analogous to
 NSURLConnection objects but provide for more control and a unified
 delegate model.
 
 NSURLSessionTask objects are always created in a suspended state and
 must be sent the -resume message before they will execute.

 Subclasses of NSURLSessionTask are used to syntactically
 differentiate between data and file downloads.

 An NSURLSessionDataTask receives the resource as a series of calls to
 the URLSession:dataTask:didReceiveData: delegate method.  This is type of
 task most commonly associated with retrieving objects for immediate parsing
 by the consumer.

 An NSURLSessionUploadTask differs from an NSURLSessionDataTask
 in how its instance is constructed.  Upload tasks are explicitly created
 by referencing a file or data object to upload, or by utilizing the
 -URLSession:task:needNewBodyStream: delegate message to supply an upload
 body.

 An NSURLSessionDownloadTask will directly write the response data to
 a temporary file.  When completed, the delegate is sent
 URLSession:downloadTask:didFinishDownloadingToURL: and given an opportunity 
 to move this file to a permanent location in its sandboxed container, or to
 otherwise read the file. If canceled, an NSURLSessionDownloadTask can
 produce a data blob that can be used to resume a download at a later
 time.

 Beginning with iOS 9 and Mac OS X 10.11, NSURLSessionStream is
 available as a task type.  This allows for direct TCP/IP connection
 to a given host and port with optional secure handshaking and
 navigation of proxies.  Data tasks may also be upgraded to a
 NSURLSessionStream task via the HTTP Upgrade: header and appropriate
 use of the pipelining option of NSURLSessionConfiguration.  See RFC
 2817 and RFC 6455 for information about the Upgrade: header, and
 comments below on turning data tasks into stream tasks.
 */

@class NSURLSession;
@class NSURLSessionDataTask;                /* DataTask objects receive the payload through zero or more delegate messages */
@class NSURLSessionUploadTask;              /* UploadTask objects receive periodic progress updates but do not return a body */
@class NSURLSessionDownloadTask;            /* DownloadTask objects represent an active download to disk.  They can provide resume data when canceled. */
@class NSURLSessionStreamTask;              /* StreamTask objects may be used to create NSInput and NSOutputStreams, or used directly in reading and writing. */
@class NSURLSessionConfiguration;
@protocol NSURLSessionDelegate;

NS_ASSUME_NONNULL_BEGIN

/*

 NSURLSession is not available for i386 targets before Mac OS X 10.10.

 */

#if __OBJC2__
#define NSURLSESSION_AVAILABLE	10_9
#else
#define NSURLSESSION_AVAILABLE	10_10
#endif


FOUNDATION_EXPORT const int64_t NSURLSessionTransferSizeUnknown NS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);    /* -1LL */

NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSession : NSObject

/*
 * The shared session uses the currently set global NSURLCache,
 * NSHTTPCookieStorage and NSURLCredentialStorage objects.
 */
+ (NSURLSession *)sharedSession;

/*
 * Customization of NSURLSession occurs during creation of a new session.
 * If you only need to use the convenience routines with custom
 * configuration options it is not necessary to specify a delegate.
 * If you do specify a delegate, the delegate will be retained until after
 * the delegate has been sent the URLSession:didBecomeInvalidWithError: message.
 */
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration;
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration delegate:(nullable id <NSURLSessionDelegate>)delegate delegateQueue:(nullable NSOperationQueue *)queue;

@property (readonly, retain) NSOperationQueue *delegateQueue;
@property (nullable, readonly, retain) id <NSURLSessionDelegate> delegate;
@property (readonly, copy) NSURLSessionConfiguration *configuration;

/*
 * The sessionDescription property is available for the developer to
 * provide a descriptive label for the session.
 */
@property (nullable, copy) NSString *sessionDescription;

/* -finishTasksAndInvalidate returns immediately and existing tasks will be allowed
 * to run to completion.  New tasks may not be created.  The session
 * will continue to make delegate callbacks until URLSession:didBecomeInvalidWithError:
 * has been issued. 
 *
 * -finishTasksAndInvalidate and -invalidateAndCancel do not
 * have any effect on the shared session singleton.
 *
 * When invalidating a background session, it is not safe to create another background
 * session with the same identifier until URLSession:didBecomeInvalidWithError: has
 * been issued.
 */
- (void)finishTasksAndInvalidate;

/* -invalidateAndCancel acts as -finishTasksAndInvalidate, but issues
 * -cancel to all outstanding tasks for this session.  Note task 
 * cancellation is subject to the state of the task, and some tasks may
 * have already have completed at the time they are sent -cancel. 
 */
- (void)invalidateAndCancel;

- (void)resetWithCompletionHandler:(void (^)(void))completionHandler;    /* empty all cookies, cache and credential stores, removes disk files, issues -flushWithCompletionHandler:. Invokes completionHandler() on the delegate queue if not nil. */
- (void)flushWithCompletionHandler:(void (^)(void))completionHandler;    /* flush storage to disk and clear transient network caches.  Invokes completionHandler() on the delegate queue if not nil. */

- (void)getTasksWithCompletionHandler:(void (^)(NSArray<NSURLSessionDataTask *> *dataTasks, NSArray<NSURLSessionUploadTask *> *uploadTasks, NSArray<NSURLSessionDownloadTask *> *downloadTasks))completionHandler; /* invokes completionHandler with outstanding data, upload and download tasks. */

- (void)getAllTasksWithCompletionHandler:(void (^)(NSArray<__kindof NSURLSessionTask *> *tasks))completionHandler NS_AVAILABLE(10_11, 9_0); /* invokes completionHandler with all outstanding tasks. */

/* 
 * NSURLSessionTask objects are always created in a suspended state and
 * must be sent the -resume message before they will execute.
 */

/* Creates a data task with the given request.  The request may have a body stream. */
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request;

/* Creates a data task to retrieve the contents of the given URL. */
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url;

/* Creates an upload task with the given request.  The body of the request will be created from the file referenced by fileURL */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL;

/* Creates an upload task with the given request.  The body of the request is provided from the bodyData. */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(NSData *)bodyData;

/* Creates an upload task with the given request.  The previously set body stream of the request (if any) is ignored and the URLSession:task:needNewBodyStream: delegate will be called when the body payload is required. */
- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request;

/* Creates a download task with the given request. */
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request;

/* Creates a download task to download the contents of the given URL. */
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url;

/* Creates a download task with the resume data.  If the download cannot be successfully resumed, URLSession:task:didCompleteWithError: will be called. */
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData;

/* Creates a bidirectional stream task to a given host and port.
 */
- (NSURLSessionStreamTask *)streamTaskWithHostName:(NSString *)hostname port:(NSInteger)port NS_AVAILABLE(10_11, 9_0);

/* Creates a bidirectional stream task with an NSNetService to identify the endpoint.
 * The NSNetService will be resolved before any IO completes.
 */
- (NSURLSessionStreamTask *)streamTaskWithNetService:(NSNetService *)service NS_AVAILABLE(10_11, 9_0);

@end

/*
 * NSURLSession convenience routines deliver results to 
 * a completion handler block.  These convenience routines
 * are not available to NSURLSessions that are configured
 * as background sessions.
 *
 * Task objects are always created in a suspended state and 
 * must be sent the -resume message before they will execute.
 */
@interface NSURLSession (NSURLSessionAsynchronousConvenience)
/*
 * data task convenience methods.  These methods create tasks that
 * bypass the normal delegate calls for response and data delivery,
 * and provide a simple cancelable asynchronous interface to receiving
 * data.  Errors will be returned in the NSURLErrorDomain, 
 * see <Foundation/NSURLError.h>.  The delegate, if any, will still be
 * called for authentication challenges.
 */
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSData * __nullable data, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSData * __nullable data, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;

/*
 * upload convenience method.
 */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL completionHandler:(void (^)(NSData * __nullable data, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(nullable NSData *)bodyData completionHandler:(void (^)(NSData * __nullable data, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;

/*
 * download task convenience methods.  When a download successfully
 * completes, the NSURL will point to a file that must be read or
 * copied during the invocation of the completion routine.  The file
 * will be removed automatically.
 */
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSURL * __nullable location, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSURL * __nullable location, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData completionHandler:(void (^)(NSURL * __nullable location, NSURLResponse * __nullable response, NSError * __nullable error))completionHandler;

@end

typedef NS_ENUM(NSInteger, NSURLSessionTaskState) {
    NSURLSessionTaskStateRunning = 0,                     /* The task is currently being serviced by the session */
    NSURLSessionTaskStateSuspended = 1,
    NSURLSessionTaskStateCanceling = 2,                   /* The task has been told to cancel.  The session will receive a URLSession:task:didCompleteWithError: message. */
    NSURLSessionTaskStateCompleted = 3,                   /* The task has completed and the session will receive no more delegate notifications */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * NSURLSessionTask - a cancelable object that refers to the lifetime
 * of processing a given request.
 */
NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSessionTask : NSObject <NSCopying>

@property (readonly)                 NSUInteger    taskIdentifier;    /* an identifier for this task, assigned by and unique to the owning session */
@property (nullable, readonly, copy) NSURLRequest  *originalRequest;  /* may be nil if this is a stream task */
@property (nullable, readonly, copy) NSURLRequest  *currentRequest;   /* may differ from originalRequest due to http server redirection */
@property (nullable, readonly, copy) NSURLResponse *response;         /* may be nil if no response has been received */

/* Byte count properties may be zero if no body is expected, 
 * or NSURLSessionTransferSizeUnknown if it is not possible 
 * to know how many bytes will be transferred.
 */

/* number of body bytes already received */
@property (readonly) int64_t countOfBytesReceived;

/* number of body bytes already sent */
@property (readonly) int64_t countOfBytesSent;

/* number of body bytes we expect to send, derived from the Content-Length of the HTTP request */
@property (readonly) int64_t countOfBytesExpectedToSend;

/* number of byte bytes we expect to receive, usually derived from the Content-Length header of an HTTP response. */
@property (readonly) int64_t countOfBytesExpectedToReceive;

/*
 * The taskDescription property is available for the developer to
 * provide a descriptive label for the task.
 */
@property (nullable, copy) NSString *taskDescription;

/* -cancel returns immediately, but marks a task as being canceled.
 * The task will signal -URLSession:task:didCompleteWithError: with an
 * error value of { NSURLErrorDomain, NSURLErrorCancelled }.  In some 
 * cases, the task may signal other work before it acknowledges the 
 * cancelation.  -cancel may be sent to a task that has been suspended.
 */
- (void)cancel;

/*
 * The current state of the task within the session.
 */
@property (readonly) NSURLSessionTaskState state;

/*
 * The error, if any, delivered via -URLSession:task:didCompleteWithError:
 * This property will be nil in the event that no error occured.
 */
@property (nullable, readonly, copy) NSError *error;

/*
 * Suspending a task will prevent the NSURLSession from continuing to
 * load data.  There may still be delegate calls made on behalf of
 * this task (for instance, to report data received while suspending)
 * but no further transmissions will be made on behalf of the task
 * until -resume is sent.  The timeout timer associated with the task
 * will be disabled while a task is suspended. -suspend and -resume are
 * nestable. 
 */
- (void)suspend;
- (void)resume;

/*
 * Sets a scaling factor for the priority of the task. The scaling factor is a
 * value between 0.0 and 1.0 (inclusive), where 0.0 is considered the lowest
 * priority and 1.0 is considered the highest.
 *
 * The priority is a hint and not a hard requirement of task performance. The
 * priority of a task may be changed using this API at any time, but not all
 * protocols support this; in these cases, the last priority that took effect
 * will be used.
 *
 * If no priority is specified, the task will operate with the default priority
 * as defined by the constant NSURLSessionTaskPriorityDefault. Two additional
 * priority levels are provided: NSURLSessionTaskPriorityLow and
 * NSURLSessionTaskPriorityHigh, but use is not restricted to these.
 */
@property float priority NS_AVAILABLE(10_10, 8_0);

@end

FOUNDATION_EXPORT const float NSURLSessionTaskPriorityDefault NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityLow NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityHigh NS_AVAILABLE(10_10, 8_0);

/*
 * An NSURLSessionDataTask does not provide any additional
 * functionality over an NSURLSessionTask and its presence is merely
 * to provide lexical differentiation from download and upload tasks.
 */
@interface NSURLSessionDataTask : NSURLSessionTask
@end

/*
 * An NSURLSessionUploadTask does not currently provide any additional
 * functionality over an NSURLSessionDataTask.  All delegate messages
 * that may be sent referencing an NSURLSessionDataTask equally apply
 * to NSURLSessionUploadTasks.
 */
@interface NSURLSessionUploadTask : NSURLSessionDataTask
@end

/*
 * NSURLSessionDownloadTask is a task that represents a download to
 * local storage.
 */
@interface NSURLSessionDownloadTask : NSURLSessionTask

/* Cancel the download (and calls the superclass -cancel).  If
 * conditions will allow for resuming the download in the future, the
 * callback will be called with an opaque data blob, which may be used
 * with -downloadTaskWithResumeData: to attempt to resume the download.
 * If resume data cannot be created, the completion handler will be
 * called with nil resumeData.
 */
- (void)cancelByProducingResumeData:(void (^)(NSData * __nullable resumeData))completionHandler;

@end

/*
 * An NSURLSessionStreamTask provides an interface to perform reads
 * and writes to a TCP/IP stream created via NSURLSession.  This task
 * may be explicitly created from an NSURLSession, or created as a
 * result of the appropriate disposition response to a
 * -URLSession:dataTask:didReceiveResponse: delegate message.
 * 
 * NSURLSessionStreamTask can be used to perform asynchronous reads
 * and writes.  Reads and writes are enquened and executed serially,
 * with the completion handler being invoked on the sessions delegate
 * queuee.  If an error occurs, or the task is canceled, all
 * outstanding read and write calls will have their completion
 * handlers invoked with an appropriate error.
 *
 * It is also possible to create NSInputStream and NSOutputStream
 * instances from an NSURLSessionTask by sending
 * -captureStreams to the task.  All outstanding read and writess are
 * completed before the streams are created.  Once the streams are
 * delivered to the session delegate, the task is considered complete
 * and will receive no more messsages.  These streams are
 * disassociated from the underlying session.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSURLSessionStreamTask : NSURLSessionTask

/* Read minBytes, or at most maxBytes bytes and invoke the completion
 * handler on the sessions delegate queue with the data or an error.
 * If an error occurs, any outstanding reads will also fail, and new
 * read requests will error out immediately.
 */
- (void)readDataOfMinLength:(NSUInteger)minBytes maxLength:(NSUInteger)maxBytes timeout:(NSTimeInterval)timeout completionHandler:(void (^) (NSData * __nullable data, BOOL atEOF, NSError * __nullable error))completionHandler;

/* Write the data completely to the underlying socket.  If all the
 * bytes have not been written by the timeout, a timeout error will
 * occur.  Note that invocation of the completion handler does not
 * guarantee that the remote side has received all the bytes, only
 * that they have been written to the kernel. */
- (void)writeData:(NSData *)data timeout:(NSTimeInterval)timeout completionHandler:(void (^) (NSError * __nullable error))completionHandler;

/* -captureStreams completes any already enqueued reads
 * and writes, and then invokes the
 * URLSession:streamTask:didBecomeInputStream:outputStream: delegate
 * message. When that message is received, the task object is
 * considered completed and will not receive any more delegate
 * messages. */
- (void)captureStreams;

/* Enqueue a request to close the write end of the underlying socket.
 * All outstanding IO will complete before the write side of the
 * socket is closed.  The server, however, may continue to write bytes
 * back to the client, so best practice is to continue reading from
 * the server until you receive EOF.
 */
- (void)closeWrite;

/* Enqueue a request to close the read side of the underlying socket.
 * All outstanding IO will complete before the read side is closed.
 * You may continue writing to the server.
 */
- (void)closeRead;

/*
 * Begin encrypted handshake.  The hanshake begins after all pending 
 * IO has completed.  TLS authentication callbacks are sent to the 
 * session's -URLSession:task:didReceiveChallenge:completionHandler:
 */
- (void)startSecureConnection;

/*
 * Cleanly close a secure connection after all pending secure IO has 
 * completed.
 */
- (void)stopSecureConnection;

@end

/*
 * Configuration options for an NSURLSession.  When a session is
 * created, a copy of the configuration object is made - you cannot
 * modify the configuration of a session after it has been created.
 *
 * The shared session uses the global singleton credential, cache
 * and cookie storage objects.
 *
 * An ephemeral session has no persistent disk storage for cookies,
 * cache or credentials.
 *
 * A background session can be used to perform networking operations
 * on behalf of a suspended application, within certain constraints.
 */
NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSessionConfiguration : NSObject <NSCopying>

+ (NSURLSessionConfiguration *)defaultSessionConfiguration;
+ (NSURLSessionConfiguration *)ephemeralSessionConfiguration;
+ (NSURLSessionConfiguration *)backgroundSessionConfigurationWithIdentifier:(NSString *)identifier NS_AVAILABLE(10_10, 8_0);

/* identifier for the background session configuration */
@property (nullable, readonly, copy) NSString *identifier;

/* default cache policy for requests */
@property NSURLRequestCachePolicy requestCachePolicy;

/* default timeout for requests.  This will cause a timeout if no data is transmitted for the given timeout value, and is reset whenever data is transmitted. */
@property NSTimeInterval timeoutIntervalForRequest;

/* default timeout for requests.  This will cause a timeout if a resource is not able to be retrieved within a given timeout. */
@property NSTimeInterval timeoutIntervalForResource;

/* type of service for requests. */
@property NSURLRequestNetworkServiceType networkServiceType;

/* allow request to route over cellular. */
@property BOOL allowsCellularAccess;

/* allows background tasks to be scheduled at the discretion of the system for optimal performance. */
@property (getter=isDiscretionary) BOOL discretionary NS_AVAILABLE(10_10, 7_0);

/* The identifier of the shared data container into which files in background sessions should be downloaded.
 * App extensions wishing to use background sessions *must* set this property to a valid container identifier, or
 * all transfers in that session will fail with NSURLErrorBackgroundSessionRequiresSharedContainer.
 */
@property (nullable, copy) NSString *sharedContainerIdentifier NS_AVAILABLE(10_10, 8_0);

/* 
 * Allows the app to be resumed or launched in the background when tasks in background sessions complete
 * or when auth is required. This only applies to configurations created with +backgroundSessionConfigurationWithIdentifier:
 * and the default value is YES.
 */
@property BOOL sessionSendsLaunchEvents NS_AVAILABLE(NA, 7_0);

/* The proxy dictionary, as described by <CFNetwork/CFHTTPStream.h> */
@property (nullable, copy) NSDictionary *connectionProxyDictionary;

/* The minimum allowable versions of the TLS protocol, from <Security/SecureTransport.h> */
@property SSLProtocol TLSMinimumSupportedProtocol;

/* The maximum allowable versions of the TLS protocol, from <Security/SecureTransport.h> */
@property SSLProtocol TLSMaximumSupportedProtocol;

/* Allow the use of HTTP pipelining */
@property BOOL HTTPShouldUsePipelining;

/* Allow the session to set cookies on requests */
@property BOOL HTTPShouldSetCookies;

/* Policy for accepting cookies.  This overrides the policy otherwise specified by the cookie storage. */
@property NSHTTPCookieAcceptPolicy HTTPCookieAcceptPolicy;

/* Specifies additional headers which will be set on outgoing requests.
   Note that these headers are added to the request only if not already present. */
@property (nullable, copy) NSDictionary *HTTPAdditionalHeaders;

/* The maximum number of simultanous persistent connections per host */
@property NSInteger HTTPMaximumConnectionsPerHost;

/* The cookie storage object to use, or nil to indicate that no cookies should be handled */
@property (nullable, retain) NSHTTPCookieStorage *HTTPCookieStorage;

/* The credential storage object, or nil to indicate that no credential storage is to be used */
@property (nullable, retain) NSURLCredentialStorage *URLCredentialStorage;

/* The URL resource cache, or nil to indicate that no caching is to be performed */
@property (nullable, retain) NSURLCache *URLCache;

/* Enable extended background idle mode for any tcp sockets created.    Enabling this mode asks the system to keep the socket open
 *  and delay reclaiming it when the process moves to the background (see https://developer.apple.com/library/ios/technotes/tn2277/_index.html) 
 */
@property BOOL shouldUseExtendedBackgroundIdleMode NS_AVAILABLE(10_11, 9_0);

/* An optional array of Class objects which subclass NSURLProtocol.
   The Class will be sent +canInitWithRequest: when determining if
   an instance of the class can be used for a given URL scheme.
   You should not use +[NSURLProtocol registerClass:], as that
   method will register your class with the default session rather
   than with an instance of NSURLSession. 
   Custom NSURLProtocol subclasses are not available to background
   sessions.
 */
@property (nullable, copy) NSArray<Class> *protocolClasses;

@end

/*
 * Disposition options for various delegate messages
 */
typedef NS_ENUM(NSInteger, NSURLSessionAuthChallengeDisposition) {
    NSURLSessionAuthChallengeUseCredential = 0,                                       /* Use the specified credential, which may be nil */
    NSURLSessionAuthChallengePerformDefaultHandling = 1,                              /* Default handling for the challenge - as if this delegate were not implemented; the credential parameter is ignored. */
    NSURLSessionAuthChallengeCancelAuthenticationChallenge = 2,                       /* The entire request will be canceled; the credential parameter is ignored. */
    NSURLSessionAuthChallengeRejectProtectionSpace = 3,                               /* This challenge is rejected and the next authentication protection space should be tried; the credential parameter is ignored. */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);


typedef NS_ENUM(NSInteger, NSURLSessionResponseDisposition) {
    NSURLSessionResponseCancel = 0,                                      /* Cancel the load, this is the same as -[task cancel] */
    NSURLSessionResponseAllow = 1,                                       /* Allow the load to continue */
    NSURLSessionResponseBecomeDownload = 2,                              /* Turn this request into a download */
    NSURLSessionResponseBecomeStream NS_ENUM_AVAILABLE(10_11, 9_0) = 3,  /* Turn this task into a stream task */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * NSURLSessionDelegate specifies the methods that a session delegate
 * may respond to.  There are both session specific messages (for
 * example, connection based auth) as well as task based messages.
 */

/*
 * Messages related to the URL session as a whole
 */
@protocol NSURLSessionDelegate <NSObject>
@optional

/* The last message a session receives.  A session will only become
 * invalid because of a systemic error or when it has been
 * explicitly invalidated, in which case the error parameter will be nil.
 */
- (void)URLSession:(NSURLSession *)session didBecomeInvalidWithError:(nullable NSError *)error;

/* If implemented, when a connection level authentication challenge
 * has occurred, this delegate will be given the opportunity to
 * provide authentication credentials to the underlying
 * connection. Some types of authentication will apply to more than
 * one request on a given connection to a server (SSL Server Trust
 * challenges).  If this delegate message is not implemented, the 
 * behavior will be to use the default handling, which may involve user
 * interaction. 
 */
- (void)URLSession:(NSURLSession *)session didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
                                             completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * __nullable credential))completionHandler;

/* If an application has received an
 * -application:handleEventsForBackgroundURLSession:completionHandler:
 * message, the session delegate will receive this message to indicate
 * that all messages previously enqueued for this session have been
 * delivered.  At this time it is safe to invoke the previously stored
 * completion handler, or to begin any internal updates that will
 * result in invoking the completion handler.
 */
- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession *)session NS_AVAILABLE_IOS(7_0);

@end

/*
 * Messages related to the operation of a specific task.
 */
@protocol NSURLSessionTaskDelegate <NSURLSessionDelegate>
@optional

/* An HTTP request is attempting to perform a redirection to a different
 * URL. You must invoke the completion routine to allow the
 * redirection, allow the redirection with a modified request, or
 * pass nil to the completionHandler to cause the body of the redirection 
 * response to be delivered as the payload of this request. The default
 * is to follow redirections. 
 *
 * For tasks in background sessions, redirections will always be followed and this method will not be called.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                     willPerformHTTPRedirection:(NSHTTPURLResponse *)response
                                     newRequest:(NSURLRequest *)request
                              completionHandler:(void (^)(NSURLRequest * __nullable))completionHandler;

/* The task has received a request specific authentication challenge.
 * If this delegate is not implemented, the session specific authentication challenge
 * will *NOT* be called and the behavior will be the same as using the default handling
 * disposition. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                            didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge 
                              completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * __nullable credential))completionHandler;

/* Sent if a task requires a new, unopened body stream.  This may be
 * necessary when authentication has failed for any request that
 * involves a body stream. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                              needNewBodyStream:(void (^)(NSInputStream * __nullable bodyStream))completionHandler;

/* Sent periodically to notify the delegate of upload progress.  This
 * information is also available as properties of the task.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                                didSendBodyData:(int64_t)bytesSent
                                 totalBytesSent:(int64_t)totalBytesSent
                       totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;

/* Sent as the last message related to a specific task.  Error may be
 * nil, which implies that no error occurred and this task is complete. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                           didCompleteWithError:(nullable NSError *)error;

@end

/*
 * Messages related to the operation of a task that delivers data
 * directly to the delegate.
 */
@protocol NSURLSessionDataDelegate <NSURLSessionTaskDelegate>
@optional
/* The task has received a response and no further messages will be
 * received until the completion block is called. The disposition
 * allows you to cancel a request or to turn a data task into a
 * download task. This delegate message is optional - if you do not
 * implement it, you can get the response as a property of the task.
 *
 * This method will not be called for background upload tasks (which cannot be converted to download tasks).
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                 didReceiveResponse:(NSURLResponse *)response
                                  completionHandler:(void (^)(NSURLSessionResponseDisposition disposition))completionHandler;

/* Notification that a data task has become a download task.  No
 * future messages will be sent to the data task.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                              didBecomeDownloadTask:(NSURLSessionDownloadTask *)downloadTask;

/*
 * Notification that a data task has become a bidirectional stream
 * task.  No future messages will be sent to the data task.  The newly
 * created streamTask will carry the original request and response as
 * properties.
 *
 * For requests that were pipelined, the stream object will only allow
 * reading, and the object will immediately issue a
 * -URLSession:writeClosedForStream:.  Pipelining can be disabled for
 * all requests in a session, or by the NSURLRequest
 * HTTPShouldUsePipelining property.
 *
 * The underlying connection is no longer considered part of the HTTP
 * connection cache and won't count against the total number of
 * connections per host.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                didBecomeStreamTask:(NSURLSessionStreamTask *)streamTask;

/* Sent when data is available for the delegate to consume.  It is
 * assumed that the delegate will retain and not copy the data.  As
 * the data may be discontiguous, you should use 
 * [NSData enumerateByteRangesUsingBlock:] to access it.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                     didReceiveData:(NSData *)data;

/* Invoke the completion routine with a valid NSCachedURLResponse to
 * allow the resulting data to be cached, or pass nil to prevent
 * caching. Note that there is no guarantee that caching will be
 * attempted for a given resource, and you should not rely on this
 * message to receive the resource data.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                  willCacheResponse:(NSCachedURLResponse *)proposedResponse 
                                  completionHandler:(void (^)(NSCachedURLResponse * __nullable cachedResponse))completionHandler;

@end

/*
 * Messages related to the operation of a task that writes data to a
 * file and notifies the delegate upon completion.
 */
@protocol NSURLSessionDownloadDelegate <NSURLSessionTaskDelegate>

/* Sent when a download task that has completed a download.  The delegate should 
 * copy or move the file at the given location to a new location as it will be 
 * removed when the delegate message returns. URLSession:task:didCompleteWithError: will
 * still be called.
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                              didFinishDownloadingToURL:(NSURL *)location;

@optional
/* Sent periodically to notify the delegate of download progress. */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                           didWriteData:(int64_t)bytesWritten
                                      totalBytesWritten:(int64_t)totalBytesWritten
                              totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;

/* Sent when a download has been resumed. If a download failed with an
 * error, the -userInfo dictionary of the error will contain an
 * NSURLSessionDownloadTaskResumeData key, whose value is the resume
 * data. 
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                      didResumeAtOffset:(int64_t)fileOffset
                                     expectedTotalBytes:(int64_t)expectedTotalBytes;

@end

@protocol NSURLSessionStreamDelegate <NSURLSessionTaskDelegate>
@optional

/* Indiciates that the read side of a connection has been closed.  Any
 * outstanding reads complete, but future reads will immediately fail.
 * This may be sent even when no reads are in progress. However, when
 * this delegate message is received, there may still be bytes
 * available.  You only know that no more bytes are available when you
 * are able to read until EOF. */
- (void)URLSession:(NSURLSession *)session readClosedForStreamTask:(NSURLSessionStreamTask *)streamTask;

/* Indiciates that the write side of a connection has been closed.
 * Any outstanding writes complete, but future writes will immediately
 * fail.
 */
- (void)URLSession:(NSURLSession *)session writeClosedForStreamTask:(NSURLSessionStreamTask *)streamTask;

/* A notification that the system has determined that a better route
 * to the host has been detected (eg, a wi-fi interface becoming
 * available.)  This is a hint to the delegate that it may be
 * desirable to create a new task for subsequent work.  Note that
 * there is no guarantee that the future task will be able to connect
 * to the host, so callers should should be prepared for failure of
 * reads and writes over any new interface. */
- (void)URLSession:(NSURLSession *)session betterRouteDiscoveredForStreamTask:(NSURLSessionStreamTask *)streamTask;

/* The given task has been completed, and unopened NSInputStream and
 * NSOutputStream objects are created from the underlying network
 * connection.  This will only be invoked after all enqueued IO has
 * completed (including any necessary handshakes.)  The streamTask
 * will not receive any further delegate messages.
 */
- (void)URLSession:(NSURLSession *)session streamTask:(NSURLSessionStreamTask *)streamTask
                                 didBecomeInputStream:(NSInputStream *)inputStream
                                         outputStream:(NSOutputStream *)outputStream;

@end

/* Key in the userInfo dictionary of an NSError received during a failed download. */
FOUNDATION_EXPORT NSString * const NSURLSessionDownloadTaskResumeData NS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

@interface NSURLSessionConfiguration (NSURLSessionDeprecated)
+ (NSURLSessionConfiguration *)backgroundSessionConfiguration:(NSString *)identifier NS_DEPRECATED(NSURLSESSION_AVAILABLE, 10_10, 7_0, 8_0, "Please use backgroundSessionConfigurationWithIdentifier: instead");
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDate.h
/*	NSDate.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSSystemClockDidChangeNotification NS_AVAILABLE(10_6, 4_0);

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

@interface NSDate : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NSTimeInterval timeIntervalSinceReferenceDate;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
@property (readonly) NSTimeInterval timeIntervalSinceNow;
@property (readonly) NSTimeInterval timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (instancetype)dateByAddingTimeInterval:(NSTimeInterval)ti NS_AVAILABLE(10_6, 2_0);

- (NSDate *)earlierDate:(NSDate *)anotherDate;
- (NSDate *)laterDate:(NSDate *)anotherDate;
- (NSComparisonResult)compare:(NSDate *)other;
- (BOOL)isEqualToDate:(NSDate *)otherDate;

@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;

+ (NSTimeInterval)timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSDateCreation)

+ (instancetype)date;
+ (instancetype)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;
+ (instancetype)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti;
+ (instancetype)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
+ (instancetype)dateWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

+ (NSDate *)distantFuture;
+ (NSDate *)distantPast;

- (instancetype)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
- (instancetype)initWithTimeIntervalSince1970:(NSTimeInterval)secs;
- (instancetype)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSOperation.h
/*	NSOperation.h
	Copyright (c) 2006-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <sys/qos.h>
#import <dispatch/dispatch.h>

@class NSArray<ObjectType>, NSSet;

NS_ASSUME_NONNULL_BEGIN

#define NSOperationQualityOfService NSQualityOfService
#define NSOperationQualityOfServiceUserInteractive NSQualityOfServiceUserInteractive
#define NSOperationQualityOfServiceUserInitiated NSQualityOfServiceUserInitiated
#define NSOperationQualityOfServiceUtility NSQualityOfServiceUtility
#define NSOperationQualityOfServiceBackground NSQualityOfServiceBackground


NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSOperation : NSObject {
@private
    id _private;
    int32_t _private1;
#if __LP64__
    int32_t _private1b;
#endif
}

- (void)start;
- (void)main;

@property (readonly, getter=isCancelled) BOOL cancelled;
- (void)cancel;

@property (readonly, getter=isExecuting) BOOL executing;
@property (readonly, getter=isFinished) BOOL finished;
@property (readonly, getter=isConcurrent) BOOL concurrent; // To be deprecated; use and override 'asynchronous' below
@property (readonly, getter=isAsynchronous) BOOL asynchronous NS_AVAILABLE(10_8, 7_0);
@property (readonly, getter=isReady) BOOL ready;

- (void)addDependency:(NSOperation *)op;
- (void)removeDependency:(NSOperation *)op;

@property (readonly, copy) NSArray<NSOperation *> *dependencies;

typedef NS_ENUM(NSInteger, NSOperationQueuePriority) {
	NSOperationQueuePriorityVeryLow = -8L,
	NSOperationQueuePriorityLow = -4L,
	NSOperationQueuePriorityNormal = 0,
	NSOperationQueuePriorityHigh = 4,
	NSOperationQueuePriorityVeryHigh = 8
};

@property NSOperationQueuePriority queuePriority;

@property (nullable, copy) void (^completionBlock)(void) NS_AVAILABLE(10_6, 4_0);

- (void)waitUntilFinished NS_AVAILABLE(10_6, 4_0);

@property double threadPriority NS_DEPRECATED(10_6, 10_10, 4_0, 8_0);

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0);

@property (nullable, copy) NSString *name NS_AVAILABLE(10_10, 8_0);

@end



NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSBlockOperation : NSOperation {
@private
    id _private2;
    void *_reserved2;
}

+ (instancetype)blockOperationWithBlock:(void (^)(void))block;

- (void)addExecutionBlock:(void (^)(void))block;
@property (readonly, copy) NSArray<void (^)(void)> *executionBlocks;

@end


NS_CLASS_AVAILABLE(10_5, 2_0)
NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSInvocationOperation : NSOperation {
@private
    id _inv;
    id _exception;
    void *_reserved2;
}

- (nullable instancetype)initWithTarget:(id)target selector:(SEL)sel object:(nullable id)arg;
- (instancetype)initWithInvocation:(NSInvocation *)inv NS_DESIGNATED_INITIALIZER;

@property (readonly, retain) NSInvocation *invocation;

@property (nullable, readonly, retain) id result;

@end

FOUNDATION_EXPORT NSString * const NSInvocationOperationVoidResultException NS_AVAILABLE(10_5, 2_0);
FOUNDATION_EXPORT NSString * const NSInvocationOperationCancelledException NS_AVAILABLE(10_5, 2_0);

static const NSInteger NSOperationQueueDefaultMaxConcurrentOperationCount = -1;

NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSOperationQueue : NSObject {
@private
    id _private;
    void *_reserved;
}

- (void)addOperation:(NSOperation *)op;
- (void)addOperations:(NSArray<NSOperation *> *)ops waitUntilFinished:(BOOL)wait NS_AVAILABLE(10_6, 4_0);

- (void)addOperationWithBlock:(void (^)(void))block NS_AVAILABLE(10_6, 4_0);

@property (readonly, copy) NSArray<__kindof NSOperation *> *operations;
@property (readonly) NSUInteger operationCount NS_AVAILABLE(10_6, 4_0);

@property NSInteger maxConcurrentOperationCount;

@property (getter=isSuspended) BOOL suspended;

@property (nullable, copy) NSString *name NS_AVAILABLE(10_6, 4_0);

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0);

@property (nullable, assign /* actually retain */) dispatch_queue_t underlyingQueue NS_AVAILABLE(10_10, 8_0);

- (void)cancelAllOperations;

- (void)waitUntilAllOperationsAreFinished;

+ (nullable NSOperationQueue *)currentQueue NS_AVAILABLE(10_6, 4_0);
+ (NSOperationQueue *)mainQueue NS_AVAILABLE(10_6, 4_0);

@end

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSURLProtectionSpace.h
/*	
    NSURLProtectionSpace.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Security/Security.h>

@class NSString;
@class NSArray<ObjectType>;
@class NSData;

NS_ASSUME_NONNULL_BEGIN

/*!
   @const NSURLProtectionSpaceHTTP
   @abstract The protocol for HTTP
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTP NS_AVAILABLE(10_5, 2_0);

/*!
   @const NSURLProtectionSpaceHTTPS
   @abstract The protocol for HTTPS
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPS NS_AVAILABLE(10_5, 2_0);

/*!
   @const NSURLProtectionSpaceFTP
   @abstract The protocol for FTP
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceFTP NS_AVAILABLE(10_5, 2_0);

/*!
    @const NSURLProtectionSpaceHTTPProxy
    @abstract The proxy type for http proxies
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPProxy;

/*!
    @const NSURLProtectionSpaceHTTPSProxy
    @abstract The proxy type for https proxies
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPSProxy;

/*!
    @const NSURLProtectionSpaceFTPProxy
    @abstract The proxy type for ftp proxies
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceFTPProxy;

/*!
    @const NSURLProtectionSpaceSOCKSProxy
    @abstract The proxy type for SOCKS proxies
*/
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceSOCKSProxy;

/*!
    @const NSURLAuthenticationMethodDefault
    @abstract The default authentication method for a protocol
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodDefault;

/*!
    @const NSURLAuthenticationMethodHTTPBasic
    @abstract HTTP basic authentication. Equivalent to
    NSURLAuthenticationMethodDefault for http.
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTTPBasic;

/*!
    @const NSURLAuthenticationMethodHTTPDigest
    @abstract HTTP digest authentication.
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTTPDigest;

/*!
    @const NSURLAuthenticationMethodHTMLForm
    @abstract HTML form authentication. Applies to any protocol.
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTMLForm;

/*!
   @const NSURLAuthenticationMethodNTLM
   @abstract NTLM authentication.
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodNTLM NS_AVAILABLE(10_5, 2_0);

/*!
   @const NSURLAuthenticationMethodNegotiate
   @abstract Negotiate authentication.
*/
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodNegotiate NS_AVAILABLE(10_5, 2_0);

/*!
    @const NSURLAuthenticationMethodClientCertificate
    @abstract SSL Client certificate.  Applies to any protocol.
 */
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodClientCertificate NS_AVAILABLE(10_6, 3_0);

/*!
    @const NSURLAuthenticationMethodServerTrust
    @abstract SecTrustRef validation required.  Applies to any protocol.
 */
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodServerTrust NS_AVAILABLE(10_6, 3_0);

@class NSURLProtectionSpaceInternal;

/*!
    @class NSURLProtectionSpace
    @discussion This class represents a protection space requiring authentication.
*/

@interface NSURLProtectionSpace : NSObject <NSSecureCoding, NSCopying>
{
@private
    NSURLProtectionSpaceInternal *_internal;
}

/*!
    @method initWithHost:port:protocol:realm:authenticationMethod:
    @abstract Initialize a protection space representing an origin server, or a realm on one
    @param host The hostname of the server
    @param port The port for the server
    @param protocol The sprotocol for this server - e.g. "http", "ftp", "https"
    @param realm A string indicating a protocol-specific subdivision
    of a single host. For http and https, this maps to the realm
    string in http authentication challenges. For many other protocols
    it is unused.
    @param authenticationMethod The authentication method to use to access this protection space -
    valid values include nil (default method), @"digest" and @"form".
    @result The initialized object.
*/
- (instancetype)initWithHost:(NSString *)host port:(NSInteger)port protocol:(nullable NSString *)protocol realm:(nullable NSString *)realm authenticationMethod:(nullable NSString *)authenticationMethod;

/*!
    @method initWithProxyHost:port:type:realm:authenticationMethod:
    @abstract Initialize a protection space representing a proxy server, or a realm on one
    @param host The hostname of the proxy server
    @param port The port for the proxy server
    @param type The type of proxy - e.g. "http", "ftp", "SOCKS"
    @param realm A string indicating a protocol-specific subdivision
    of a single host. For http and https, this maps to the realm
    string in http authentication challenges. For many other protocols
    it is unused.
    @param authenticationMethod The authentication method to use to access this protection space -
    valid values include nil (default method) and @"digest"
    @result The initialized object.
*/
- (instancetype)initWithProxyHost:(NSString *)host port:(NSInteger)port type:(nullable NSString *)type realm:(nullable NSString *)realm  authenticationMethod:(nullable NSString *)authenticationMethod;

/*!
    @method realm
    @abstract Get the authentication realm for which the protection space that
    needs authentication
    @discussion This is generally only available for http
    authentication, and may be nil otherwise.
    @result The realm string
*/
@property (nullable, readonly, copy) NSString *realm;

/*!
    @method receivesCredentialSecurely
    @abstract Determine if the password for this protection space can be sent securely
    @result YES if a secure authentication method or protocol will be used, NO otherwise
*/
@property (readonly) BOOL receivesCredentialSecurely;

/*!
    @method isProxy
    @abstract Determine if this authenticating protection space is a proxy server
    @result YES if a proxy, NO otherwise
*/
@property (readonly) BOOL isProxy;

/*!
    @method host
    @abstract Get the proxy host if this is a proxy authentication, or the host from the URL.
    @result The host for this protection space.
*/
@property (readonly, copy) NSString *host;

/*!
    @method port
    @abstract Get the proxy port if this is a proxy authentication, or the port from the URL.
    @result The port for this protection space, or 0 if not set.
*/
@property (readonly) NSInteger port;

/*!
    @method proxyType
    @abstract Get the type of this protection space, if a proxy
    @result The type string, or nil if not a proxy.
 */
@property (nullable, readonly, copy) NSString *proxyType;

/*!
    @method protocol
    @abstract Get the protocol of this protection space, if not a proxy
    @result The type string, or nil if a proxy.
*/
@property (nullable, readonly, copy) NSString *protocol;

/*!
    @method authenticationMethod
    @abstract Get the authentication method to be used for this protection space
    @result The authentication method
*/
@property (readonly, copy) NSString *authenticationMethod;

@end

/*!
    @class NSURLProtectionSpace(NSClientCertificateSpace)
    @discussion This category supplies additional information for use when a client certificate is required by the server in order to complete authentication.
 */
@interface NSURLProtectionSpace(NSClientCertificateSpace)

/*!
    @method distinguishedNames
    @abstract Returns an array of acceptable certificate issuing authorities for client certification authentication. Issuers are identified by their distinguished name and returned as a DER encoded data.
    @result An array of NSData objects.  (Nil if the authenticationMethod is not NSURLAuthenticationMethodClientCertificate)
 */
@property (nullable, readonly, copy) NSArray<NSData *> *distinguishedNames NS_AVAILABLE(10_6, 3_0);

@end

/*!
    @class NSURLProtectionSpace(NSServerTrustValidationSpace)
    @discussion This category supplies additional information for use by the client to evaluate whether to trust a given server during a security handshake.
 */
@interface NSURLProtectionSpace(NSServerTrustValidationSpace)

/*!
    @method serverTrust
    @abstract Returns a SecTrustRef which represents the state of the servers SSL transaction state
    @result A SecTrustRef from Security.framework.  (Nil if the authenticationMethod is not NSURLAuthenticationMethodServerTrust)
 */
@property (nullable, readonly) SecTrustRef serverTrust NS_AVAILABLE(10_6, 3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSNetServices.h
/*	NSNetServices.h
        Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSArray<ObjectType>, NSData, NSDictionary<KeyType, ObjectType>, NSInputStream, NSNumber, NSOutputStream, NSRunLoop, NSString;
@protocol NSNetServiceDelegate, NSNetServiceBrowserDelegate;

NS_ASSUME_NONNULL_BEGIN

#pragma mark Error constants

FOUNDATION_EXPORT NSString * const NSNetServicesErrorCode;
FOUNDATION_EXPORT NSString * const NSNetServicesErrorDomain;

typedef NS_ENUM(NSInteger, NSNetServicesError) {
    
/* An unknown error occured during resolution or publication.
*/
    NSNetServicesUnknownError = -72000L,
    
/* An NSNetService with the same domain, type and name was already present when the publication request was made.
*/
    NSNetServicesCollisionError = -72001L,
    
/* The NSNetService was not found when a resolution request was made.
*/
    NSNetServicesNotFoundError	= -72002L,
    
/* A publication or resolution request was sent to an NSNetService instance which was already published or a search request was made of an NSNetServiceBrowser instance which was already searching.
*/
    NSNetServicesActivityInProgress = -72003L,
    
/* An required argument was not provided when initializing the NSNetService instance.
*/
    NSNetServicesBadArgumentError = -72004L,
    
/* The operation being performed by the NSNetService or NSNetServiceBrowser instance was cancelled.
*/
    NSNetServicesCancelledError = -72005L,
    
/* An invalid argument was provided when initializing the NSNetService instance or starting a search with an NSNetServiceBrowser instance.
*/
    NSNetServicesInvalidError = -72006L,
        
/* Resolution of an NSNetService instance failed because the timeout was reached.
*/
    NSNetServicesTimeoutError = -72007L,
    
};


typedef NS_OPTIONS(NSUInteger, NSNetServiceOptions) {
    /* When passed to -publishWithOptions:, this suppresses the auto-renaming of an
     * NSNetService in the event of a name collision. The collision is reported to the
     * instance's delegate on the -netService:didNotPublish: method.
     */
    NSNetServiceNoAutoRename = 1UL << 0,


    /* When passed to -publishWithOptions:, in addition to publishing the service, a
     * TCP listener is started for both IPv4 and IPv6 on the port specified by the
     * NSNetService. If the listening port can't be opened, an error is reported using
     * -netService:didNotPublish:. Specify a port number of zero to use a random port.
     * When -netServiceDidPublish: is called, -port will return the actual listening
     * port number. Since the listener only supports TCP, the publish will fail with
     * NSNetServicesBadArgumentError if the NSNetService type does not end with "_tcp".
     * New incoming connections will be delivered in the form of NSStreams via the
     * -netService:didAcceptConnectionWithInputStream:outputStream: delegate method.
     */
    NSNetServiceListenForConnections NS_ENUM_AVAILABLE(10_9, 7_0) = 1UL << 1
};



#pragma mark -

@interface NSNetService : NSObject {
@private
    id _netService;
    id _delegate;
    id _reserved;
}

/* This is the initializer for publishing. You should use this initializer if you are going to announce the availability of a service on the network. To publish a service in all available domains, pass the empty string as the domain.
*/
- (instancetype)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name port:(int)port NS_DESIGNATED_INITIALIZER;

/* This is the initializer for resolution. If you know the domain, type and name of the service for which you wish to discover addresses, you should initialize an NSNetService instance using this method and call resolve: on the result. If you wish to connect to this service immediately, you should call getInputStream:getOutputStream: on the result and forego the resolution step entirely.

If publish: is called on an NSNetService instance initialized with this method, an NSNetServicesBadArgumentError will be sent in the error dictionary to the delegate's netService:didNotPublish: method.
*/
- (instancetype)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name;

/* NSNetService instances may be scheduled on NSRunLoops to operate in different modes, or in other threads. It is generally not necessary to schedule NSNetServices in other threads. NSNetServices are scheduled in the current thread's NSRunLoop in the NSDefaultRunLoopMode when they are created.
*/
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

/* Set a delegate to receive publish, resolve, or monitor events.
 */
@property (nullable, assign) id <NSNetServiceDelegate> delegate;

/* Initially set to NO. Set to YES to also publish, resolve, or monitor this service over peer to peer Bluetooth and Wi-Fi (if available). Must be set before operation starts.
*/
@property BOOL includesPeerToPeer NS_AVAILABLE(10_10, 7_0);

/* Returns the name of the discovered or published service.
*/
@property (readonly, copy) NSString *name;

/* Returns the type of the discovered or published service.
*/
@property (readonly, copy) NSString *type;

/* Returns the domain of the discovered or published service.
*/
@property (readonly, copy) NSString *domain;

/* Returns the DNS host name of the computer hosting the discovered or published service. If a successful resolve has not yet occurred, this method will return nil.
*/
@property (nullable, readonly, copy) NSString *hostName;

/* The addresses of the service. This is an NSArray of NSData instances, each of which contains a single struct sockaddr suitable for use with connect(2). In the event that no addresses are resolved for the service or the service has not yet been resolved, an empty NSArray is returned.
*/
@property (nullable, readonly, copy) NSArray<NSData *> *addresses;

/* The port of a resolved service. This returns -1 if the service has not been resolved.
*/
@property (readonly) NSInteger port NS_AVAILABLE(10_5, 2_0);
 
/* Advertises a given service on the network. This method returns immediately. Success or failure is indicated by callbacks to the NSNetService instance's delegate.
 
    If the name of the service is the default name (@""), then the service will be renamed automatically. If the name of the service has been specified, then the service will not be renamed automatically. If more control over renaming is required, then -[NSNetService publishWithOptions:] is available.
*/
- (void)publish;

/* Advertises a given service on the network. This method returns immediately. Success or failure is indicated by callbacks to the NSNetService instance's delegate.
 
    See the notes above for NSNetServiceNoAutoRename for information about controlling the auto-renaming behavior using this method.
*/
- (void)publishWithOptions:(NSNetServiceOptions)options NS_AVAILABLE(10_5, 2_0);


/* Attempts to determine at least one address for the NSNetService instance. For applications linked on or after Mac OS X 10.4 "Tiger", this method calls -resolveWithTimeout: with a value of 5.0. Applications linked prior to Mac OS X 10.4 "Tiger" must call -stop on the instance after an appropriate (short) amount of time to avoid causing unnecessary network traffic.
*/
- (void)resolve NS_DEPRECATED(10_2, 10_4, 2_0, 2_0);

/* Halts a service which is either publishing or resolving.
*/
- (void)stop;

/* Returns an NSDictionary created from the provided NSData. The keys will be UTF8-encoded NSStrings. The values are NSDatas. The caller is responsible for interpreting these as types appropriate to the keys. If the NSData cannot be converted into an appropriate NSDictionary, this method will return nil. For applications linked on or after Mac OS X 10.5, this method will throw an NSInvalidException if it is passed nil as the argument.
*/
+ (NSDictionary<NSString *, NSData *> *)dictionaryFromTXTRecordData:(NSData *)txtData;

/* Returns an NSData created from the provided dictionary. The keys in the provided dictionary must be NSStrings, and the values must be NSDatas. If the dictionary cannot be converted into an NSData suitable for a TXT record, this method will return nil. For applications linked on or after Mac OS X 10.5, this method will throw an NSInvalidArgumentException if it is passed nil as the argument.
*/
+ (NSData *)dataFromTXTRecordDictionary:(NSDictionary<NSString *, NSData *> *)txtDictionary;

/* Starts a resolve for the NSNetService instance of the specified duration. If the delegate's -netServiceDidResolveAddress: method is called before the timeout expires, the resolve is successful. If the timeout is reached, the delegate's -netService:didNotResolve: method will be called. The value of the NSNetServicesErrorCode key in the error dictionary will be NSNetServicesTimeoutError.
*/
- (void)resolveWithTimeout:(NSTimeInterval)timeout;

/* Retrieves streams from the NSNetService instance. The instance's delegate methods are not called. Returns YES if the streams requested are created successfully. Returns NO if or any reason the stream could not be created. If only one stream is desired, pass NULL for the address of the other stream. The streams that are created are not open, and are not scheduled in any run loop for any mode.
*/
- (BOOL)getInputStream:(out __strong NSInputStream * __nullable * __nullable)inputStream outputStream:(out __strong NSOutputStream * __nullable * __nullable)outputStream;

/* Sets the TXT record of the NSNetService instance that has been or will be published. Pass nil to remove the TXT record from the instance.
*/
- (BOOL)setTXTRecordData:(nullable NSData *)recordData;

/* Returns the raw TXT record of the NSNetService instance. If the instance has not been resolved, or the delegate's -netService:didUpdateTXTRecordData: has not been called, this will return nil. It is permitted to have a zero-length TXT record.
*/
- (nullable NSData *)TXTRecordData;

/* Starts monitoring the NSNetService instance for events. In Mac OS X 10.4 Tiger, monitored NSNetService instances inform their delegates of changes to the instance's TXT record by calling the delegate's -netService:didUpdateTXTRecordData: method.
*/
- (void)startMonitoring;

/* Stops monitoring the NSNetService instance for events.
*/
- (void)stopMonitoring;


@end

#pragma mark -

@interface NSNetServiceBrowser : NSObject {
@private
    id _netServiceBrowser;
    id _delegate;
    void * _reserved;
}

- (instancetype)init;

/* Set a delegate to receive discovery events.
*/
@property (nullable, assign) id <NSNetServiceBrowserDelegate> delegate;

/* Initially set to NO. Set to YES to also browse over peer to peer Bluetooth and Wi-Fi (if available). Must be set before starting to search.
*/
@property BOOL includesPeerToPeer NS_AVAILABLE(10_10, 7_0);

/* NSNetServiceBrowser instances may be scheduled on NSRunLoops to operate in different modes, or in other threads. It is generally not necessary to schedule NSNetServiceBrowsers in other threads. NSNetServiceBrowsers are scheduled in the current thread's NSRunLoop in the NSDefaultRunLoopMode when they are created.
*/
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

/* Starts a search for domains that are browsable via Bonjour and the computer's network configuration. Discovered domains are reported to the delegate's -netServiceBrowser:didFindDomain:moreComing: method. There may be more than one browsable domain.
*/
- (void)searchForBrowsableDomains;

/* Starts a search for domains in which the network configuration allows registration (i.e. publishing). Most NSNetServiceBrowser clients do not need to use this API, as it is sufficient to publish an NSNetService instance with the empty string (see -[NSNetService initWithDomain:type:name:port:]). Discovered domains are reported to the delegate's -netServiceBrowser:didFindDomain:moreComing: method. There may be more than one registration domain.
*/
- (void)searchForRegistrationDomains;

/* Starts a search for services of the specified type in the domain indicated by domainString. For each service discovered, a -netServiceBrowser:foundService:moreComing: message is sent to the NSNetServiceBrowser instance's delegate.
*/
- (void)searchForServicesOfType:(NSString *)type inDomain:(NSString *)domainString;

/* Stops the currently running search.
*/
- (void)stop;

@end

#pragma mark -

@protocol NSNetServiceDelegate <NSObject>
@optional

/* Sent to the NSNetService instance's delegate prior to advertising the service on the network. If for some reason the service cannot be published, the delegate will not receive this message, and an error will be delivered to the delegate via the delegate's -netService:didNotPublish: method.
*/
- (void)netServiceWillPublish:(NSNetService *)sender;

/* Sent to the NSNetService instance's delegate when the publication of the instance is complete and successful.
*/
- (void)netServiceDidPublish:(NSNetService *)sender;

/* Sent to the NSNetService instance's delegate when an error in publishing the instance occurs. The error dictionary will contain two key/value pairs representing the error domain and code (see the NSNetServicesError enumeration above for error code constants). It is possible for an error to occur after a successful publication.
*/
- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/* Sent to the NSNetService instance's delegate prior to resolving a service on the network. If for some reason the resolution cannot occur, the delegate will not receive this message, and an error will be delivered to the delegate via the delegate's -netService:didNotResolve: method.
*/
- (void)netServiceWillResolve:(NSNetService *)sender;

/* Sent to the NSNetService instance's delegate when one or more addresses have been resolved for an NSNetService instance. Some NSNetService methods will return different results before and after a successful resolution. An NSNetService instance may get resolved more than once; truly robust clients may wish to resolve again after an error, or to resolve more than once.
*/
- (void)netServiceDidResolveAddress:(NSNetService *)sender;

/* Sent to the NSNetService instance's delegate when an error in resolving the instance occurs. The error dictionary will contain two key/value pairs representing the error domain and code (see the NSNetServicesError enumeration above for error code constants).
*/
- (void)netService:(NSNetService *)sender didNotResolve:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/* Sent to the NSNetService instance's delegate when the instance's previously running publication or resolution request has stopped.
*/
- (void)netServiceDidStop:(NSNetService *)sender;

/* Sent to the NSNetService instance's delegate when the instance is being monitored and the instance's TXT record has been updated. The new record is contained in the data parameter.
*/
- (void)netService:(NSNetService *)sender didUpdateTXTRecordData:(NSData *)data;
    
    
/* Sent to a published NSNetService instance's delegate when a new connection is
 * received. Before you can communicate with the connecting client, you must -open
 * and schedule the streams. To reject a connection, just -open both streams and
 * then immediately -close them.
 
 * To enable TLS on the stream, set the various TLS settings using
 * kCFStreamPropertySSLSettings before calling -open. You must also specify
 * kCFBooleanTrue for kCFStreamSSLIsServer in the settings dictionary along with
 * a valid SecIdentityRef as the first entry of kCFStreamSSLCertificates.
 */
- (void)netService:(NSNetService *)sender didAcceptConnectionWithInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream NS_AVAILABLE(10_9, 7_0);

@end

#pragma mark -

@protocol NSNetServiceBrowserDelegate <NSObject>
@optional

/* Sent to the NSNetServiceBrowser instance's delegate before the instance begins a search. The delegate will not receive this message if the instance is unable to begin a search. Instead, the delegate will receive the -netServiceBrowser:didNotSearch: message.
*/
- (void)netServiceBrowserWillSearch:(NSNetServiceBrowser *)browser;

/* Sent to the NSNetServiceBrowser instance's delegate when the instance's previous running search request has stopped.
*/
- (void)netServiceBrowserDidStopSearch:(NSNetServiceBrowser *)browser;

/* Sent to the NSNetServiceBrowser instance's delegate when an error in searching for domains or services has occurred. The error dictionary will contain two key/value pairs representing the error domain and code (see the NSNetServicesError enumeration above for error code constants). It is possible for an error to occur after a search has been started successfully.
*/
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didNotSearch:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/* Sent to the NSNetServiceBrowser instance's delegate for each domain discovered. If there are more domains, moreComing will be YES. If for some reason handling discovered domains requires significant processing, accumulating domains until moreComing is NO and then doing the processing in bulk fashion may be desirable.
*/
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

/* Sent to the NSNetServiceBrowser instance's delegate for each service discovered. If there are more services, moreComing will be YES. If for some reason handling discovered services requires significant processing, accumulating services until moreComing is NO and then doing the processing in bulk fashion may be desirable.
*/
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing;

/* Sent to the NSNetServiceBrowser instance's delegate when a previously discovered domain is no longer available.
*/
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

/* Sent to the NSNetServiceBrowser instance's delegate when a previously discovered service is no longer published.
*/
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveService:(NSNetService *)service moreComing:(BOOL)moreComing;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLRequest.h
/*	
    NSURLRequest.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSData;
@class NSDictionary<KeyType, ObjectType>;
@class NSInputStream;
@class NSString;
@class NSURL;
@class NSURLRequestInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
    @header NSURLRequest.h

    This header file describes the constructs used to represent URL
    load requests in a manner independent of protocol and URL scheme.
    Immutable and mutable variants of this URL load request concept
    are described, named NSURLRequest and NSMutableURLRequest,
    respectively. A collection of constants is also declared to
    exercise control over URL content caching policy.

    <p>NSURLRequest and NSMutableURLRequest are designed to be
    customized to support protocol-specific requests. Protocol
    implementors who need to extend the capabilities of NSURLRequest
    and NSMutableURLRequest are encouraged to provide categories on
    these classes as appropriate to support protocol-specific data. To
    store and retrieve data, category methods can use the
    <tt>+propertyForKey:inRequest:</tt> and
    <tt>+setProperty:forKey:inRequest:</tt> class methods on
    NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
    NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
    such extensions.

    <p>The main advantage of this design is that a client of the URL
    loading library can implement request policies in a standard way
    without type checking of requests or protocol checks on URLs. Any
    protocol-specific details that have been set on a URL request will
    be used if they apply to the particular URL being loaded, and will
    be ignored if they do not apply.
*/

/*!
    @enum NSURLRequestCachePolicy

    @discussion The NSURLRequestCachePolicy enum defines constants that
    can be used to specify the type of interactions that take place with
    the caching system when the URL loading system processes a request.
    Specifically, these constants cover interactions that have to do
    with whether already-existing cache data is returned to satisfy a
    URL load request.

    @constant NSURLRequestUseProtocolCachePolicy Specifies that the
    caching logic defined in the protocol implementation, if any, is
    used for a particular URL load request. This is the default policy
    for URL load requests.

    @constant NSURLRequestReloadIgnoringLocalCacheData Specifies that the
    data for the URL load should be loaded from the origin source. No
    existing local cache data, regardless of its freshness or validity,
    should be used to satisfy a URL load request.

    @constant NSURLRequestReloadIgnoringLocalAndRemoteCacheData Specifies that
    not only should the local cache data be ignored, but that proxies and
    other intermediates should be instructed to disregard their caches
    so far as the protocol allows.  Unimplemented.

    @constant NSURLRequestReloadIgnoringCacheData Older name for
    NSURLRequestReloadIgnoringLocalCacheData.

    @constant NSURLRequestReturnCacheDataElseLoad Specifies that the
    existing cache data should be used to satisfy a URL load request,
    regardless of its age or expiration date. However, if there is no
    existing data in the cache corresponding to a URL load request,
    the URL is loaded from the origin source.

    @constant NSURLRequestReturnCacheDataDontLoad Specifies that the
    existing cache data should be used to satisfy a URL load request,
    regardless of its age or expiration date. However, if there is no
    existing data in the cache corresponding to a URL load request, no
    attempt is made to load the URL from the origin source, and the
    load is considered to have failed. This constant specifies a
    behavior that is similar to an "offline" mode.

    @constant NSURLRequestReloadRevalidatingCacheData Specifies that
    the existing cache data may be used provided the origin source
    confirms its validity, otherwise the URL is loaded from the
    origin source.  Unimplemented.
*/
typedef NS_ENUM(NSUInteger, NSURLRequestCachePolicy)
{
    NSURLRequestUseProtocolCachePolicy = 0,

    NSURLRequestReloadIgnoringLocalCacheData = 1,
    NSURLRequestReloadIgnoringLocalAndRemoteCacheData = 4, // Unimplemented
    NSURLRequestReloadIgnoringCacheData = NSURLRequestReloadIgnoringLocalCacheData,

    NSURLRequestReturnCacheDataElseLoad = 2,
    NSURLRequestReturnCacheDataDontLoad = 3,

    NSURLRequestReloadRevalidatingCacheData = 5, // Unimplemented
};

/*!
 @enum NSURLRequestNetworkServiceType
 
 @discussion The NSURLRequestNetworkServiceType enum defines constants that
 can be used to specify the service type to associate with this request.  The
 service type is used to provide the networking layers a hint of the purpose 
 of the request.
 
 @constant NSURLNetworkServiceTypeDefault Is the default value for an NSURLRequest
 when created.  This value should be left unchanged for the vast majority of requests.
 
 @constant NSURLNetworkServiceTypeVoIP Specifies that the request is for voice over IP
 control traffic.
 
 @constant NSURLNetworkServiceTypeVideo Specifies that the request is for video
 traffic.

 @constant NSURLNetworkServiceTypeBackground Specifies that the request is for background
 traffic (such as a file download).

 @constant NSURLNetworkServiceTypeVoice Specifies that the request is for voice data.

*/
typedef NS_ENUM(NSUInteger, NSURLRequestNetworkServiceType)
{
    NSURLNetworkServiceTypeDefault = 0,	// Standard internet traffic
    NSURLNetworkServiceTypeVoIP = 1,	// Voice over IP control traffic
    NSURLNetworkServiceTypeVideo = 2,	// Video traffic
    NSURLNetworkServiceTypeBackground = 3, // Background traffic
    NSURLNetworkServiceTypeVoice = 4	   // Voice data
};


/*!
    @class NSURLRequest
    
    @abstract An NSURLRequest object represents a URL load request in a
    manner independent of protocol and URL scheme.
    
    @discussion NSURLRequest encapsulates two basic data elements about
    a URL load request:
    <ul>
    <li>The URL to load.
    <li>The policy to use when consulting the URL content cache made
    available by the implementation.
    </ul>
    In addition, NSURLRequest is designed to be extended to support
    protocol-specific data by adding categories to access a property
    object provided in an interface targeted at protocol implementors.
    <ul>
    <li>Protocol implementors should direct their attention to the
    NSURLRequestExtensibility category on NSURLRequest for more
    information on how to provide extensions on NSURLRequest to
    support protocol-specific request information.
    <li>Clients of this API who wish to create NSURLRequest objects to
    load URL content should consult the protocol-specific NSURLRequest
    categories that are available. The NSHTTPURLRequest category on
    NSURLRequest is an example.
    </ul>
    <p>
    Objects of this class are used to create NSURLConnection instances,
    which can are used to perform the load of a URL, or as input to the
    NSURLConnection class method which performs synchronous loads.
*/
@interface NSURLRequest : NSObject <NSSecureCoding, NSCopying, NSMutableCopying>
{
    @private
    NSURLRequestInternal *_internal;
}

/*! 
    @method requestWithURL:
    @abstract Allocates and initializes an NSURLRequest with the given
    URL.
    @discussion Default values are used for cache policy
    (NSURLRequestUseProtocolCachePolicy) and timeout interval (60
    seconds).
    @param URL The URL for the request.
    @result A newly-created and autoreleased NSURLRequest instance.
*/
+ (instancetype)requestWithURL:(NSURL *)URL;

/*
    @method supportsSecureCoding
    @abstract Indicates that NSURLRequest implements the NSSecureCoding protocol.
    @result A BOOL value set to YES.
*/
+ (BOOL)supportsSecureCoding;

/*!
    @method requestWithURL:cachePolicy:timeoutInterval:
    @abstract Allocates and initializes a NSURLRequest with the given
    URL and cache policy.
    @param URL The URL for the request. 
    @param cachePolicy The cache policy for the request. 
    @param timeoutInterval The timeout interval for the request. See the
    commentary for the <tt>timeoutInterval</tt> for more information on
    timeout intervals.
    @result A newly-created and autoreleased NSURLRequest instance. 
*/
+ (instancetype)requestWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval;

/*! 
    @method initWithURL:
    @abstract Initializes an NSURLRequest with the given URL. 
    @discussion Default values are used for cache policy
    (NSURLRequestUseProtocolCachePolicy) and timeout interval (60
    seconds).
    @param URL The URL for the request. 
    @result An initialized NSURLRequest. 
*/
- (instancetype)initWithURL:(NSURL *)URL;

/*! 
    @method initWithURL:
    @abstract Initializes an NSURLRequest with the given URL and
    cache policy.
    @discussion This is the designated initializer for the 
    NSURLRequest class.
    @param URL The URL for the request. 
    @param cachePolicy The cache policy for the request. 
    @param timeoutInterval The timeout interval for the request. See the
    commentary for the <tt>timeoutInterval</tt> for more information on
    timeout intervals.
    @result An initialized NSURLRequest. 
*/
- (instancetype)initWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval NS_DESIGNATED_INITIALIZER;

/*! 
    @method URL
    @abstract Returns the URL of the receiver. 
    @result The URL of the receiver. 
*/
@property (nullable, readonly, copy) NSURL *URL;

/*! 
    @method cachePolicy
    @abstract Returns the cache policy of the receiver. 
    @result The cache policy of the receiver. 
*/
@property (readonly) NSURLRequestCachePolicy cachePolicy;

/*! 
    @method timeoutInterval
    @abstract Returns the timeout interval of the receiver.
    @discussion The timeout interval specifies the limit on the idle
    interval alloted to a request in the process of loading. The "idle
    interval" is defined as the period of time that has passed since the
    last instance of load activity occurred for a request that is in the
    process of loading. Hence, when an instance of load activity occurs
    (e.g. bytes are received from the network for a request), the idle
    interval for a request is reset to 0. If the idle interval ever
    becomes greater than or equal to the timeout interval, the request
    is considered to have timed out. This timeout interval is measured
    in seconds.
    @result The timeout interval of the receiver. 
*/
@property (readonly) NSTimeInterval timeoutInterval;

/*!
    @method mainDocumentURL
    @abstract The main document URL associated with this load.
    @discussion This URL is used for the cookie "same domain as main
    document" policy. There may also be other future uses.
    See setMainDocumentURL:
    NOTE: In the current implementation, this value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
    @result The main document URL.
*/
@property (nullable, readonly, copy) NSURL *mainDocumentURL;

/*!
 @method networkServiceType
 @abstract Returns the NSURLRequestNetworkServiceType associated with this request.
 @discussion  This will return NSURLNetworkServiceTypeDefault for requests that have
 not explicitly set a networkServiceType (using the setNetworkServiceType method).
 @result The NSURLRequestNetworkServiceType associated with this request.
 */
@property (readonly) NSURLRequestNetworkServiceType networkServiceType NS_AVAILABLE(10_7, 4_0);

/*! 
 @method allowsCellularAccess:
 @abstract returns whether a connection created with this request is allowed to use
 the built in cellular radios (if present).
 @result YES if the receiver is allowed to use the built in cellular radios to
 satify the request, NO otherwise.
 */
@property (readonly) BOOL allowsCellularAccess  NS_AVAILABLE(10_8, 6_0);

@end



/*! 
    @class NSMutableURLRequest
    
    @abstract An NSMutableURLRequest object represents a mutable URL load
    request in a manner independent of protocol and URL scheme.
    
    @discussion This specialization of NSURLRequest is provided to aid
    developers who may find it more convenient to mutate a single request
    object for a series of URL loads instead of creating an immutable
    NSURLRequest for each load. This programming model is supported by
    the following contract stipulation between NSMutableURLRequest and 
    NSURLConnection: NSURLConnection makes a deep copy of each 
    NSMutableURLRequest object passed to one of its initializers.    
    <p>NSMutableURLRequest is designed to be extended to support
    protocol-specific data by adding categories to access a property
    object provided in an interface targeted at protocol implementors.
    <ul>
    <li>Protocol implementors should direct their attention to the
    NSMutableURLRequestExtensibility category on
    NSMutableURLRequest for more information on how to provide
    extensions on NSMutableURLRequest to support protocol-specific
    request information.
    <li>Clients of this API who wish to create NSMutableURLRequest
    objects to load URL content should consult the protocol-specific
    NSMutableURLRequest categories that are available. The
    NSMutableHTTPURLRequest category on NSMutableURLRequest is an
    example.
    </ul>
*/
@interface NSMutableURLRequest : NSURLRequest

/*! 
    @method URL
    @abstract Sets the URL of the receiver. 
    @param URL The new URL for the receiver. 
*/
@property (nullable, copy) NSURL *URL;

/*! 
    @method setCachePolicy:
    @abstract The cache policy of the receiver. 
    @param policy The new NSURLRequestCachePolicy for the receiver. 
*/
@property NSURLRequestCachePolicy cachePolicy;

/*! 
    @method setTimeoutInterval:
    @abstract Sets the timeout interval of the receiver.
    @discussion The timeout interval specifies the limit on the idle
    interval allotted to a request in the process of loading. The "idle
    interval" is defined as the period of time that has passed since the
    last instance of load activity occurred for a request that is in the
    process of loading. Hence, when an instance of load activity occurs
    (e.g. bytes are received from the network for a request), the idle
    interval for a request is reset to 0. If the idle interval ever
    becomes greater than or equal to the timeout interval, the request
    is considered to have timed out. This timeout interval is measured
    in seconds.
    @param seconds The new timeout interval of the receiver. 
*/
@property NSTimeInterval timeoutInterval;

/*!
    @method setMainDocumentURL:
    @abstract Sets the main document URL
    @param URL The main document URL.
    @discussion The caller should pass the URL for an appropriate main
    document, if known. For example, when loading a web page, the URL
    of the main html document for the top-level frame should be
    passed.  This main document will be used to implement the cookie
    "only from same domain as main document" policy, and possibly
    other things in the future.
    NOTE: In the current implementation, the passed-in value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
*/
@property (nullable, copy) NSURL *mainDocumentURL;

/*!
 @method setNetworkServiceType:
 @abstract Sets the NSURLRequestNetworkServiceType to associate with this request
 @param networkServiceType The NSURLRequestNetworkServiceType to associate with the request.
 @discussion This method is used to provide the network layers with a hint as to the purpose
 of the request.  Most clients should not need to use this method.
 */
@property NSURLRequestNetworkServiceType networkServiceType NS_AVAILABLE(10_7, 4_0);

/*! 
 @method setAllowsCellularAccess
 @abstract sets whether a connection created with this request is allowed to use
 the built in cellular radios (if present).
 @param allow NO if the receiver should not be allowed to use the built in
 cellular radios to satisfy the request, YES otherwise.  The default is YES.
 */
@property BOOL allowsCellularAccess NS_AVAILABLE(10_8, 6_0);

@end



/*!
    @category NSURLRequest(NSHTTPURLRequest) 
    The NSHTTPURLRequest on NSURLRequest provides methods for accessing
    information specific to HTTP protocol requests.
*/
@interface NSURLRequest (NSHTTPURLRequest) 

/*! 
    @method HTTPMethod
    @abstract Returns the HTTP request method of the receiver. 
    @result the HTTP request method of the receiver. 
*/
@property (nullable, readonly, copy) NSString *HTTPMethod;

/*! 
    @method allHTTPHeaderFields
    @abstract Returns a dictionary containing all the HTTP header fields
    of the receiver.
    @result a dictionary containing all the HTTP header fields of the
    receiver.
*/
@property (nullable, readonly, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;

/*! 
    @method valueForHTTPHeaderField:
    @abstract Returns the value which corresponds to the given header
    field. Note that, in keeping with the HTTP RFC, HTTP header field
    names are case-insensitive.
    @param field the header field name to use for the lookup
    (case-insensitive).
    @result the value associated with the given header field, or nil if
    there is no value associated with the given header field.
*/
- (nullable NSString *)valueForHTTPHeaderField:(NSString *)field;

/*! 
    @method HTTPBody
    @abstract Returns the request body data of the receiver. 
    @discussion This data is sent as the message body of the request, as
    in done in an HTTP POST request.
    @result The request body data of the receiver. 
*/
@property (nullable, readonly, copy) NSData *HTTPBody;

/*!
    @method HTTPBodyStream
    @abstract Returns the request body stream of the receiver
    if any has been set
    @discussion The stream is returned for examination only; it is
    not safe for the caller to manipulate the stream in any way.  Also
    note that the HTTPBodyStream and HTTPBody are mutually exclusive - only
    one can be set on a given request.  Also note that the body stream is
    preserved across copies, but is LOST when the request is coded via the 
    NSCoding protocol
    @result The request body stream of the receiver.
*/
@property (nullable, readonly, retain) NSInputStream *HTTPBodyStream;

/*! 
    @method HTTPShouldHandleCookies
    @abstract Determine whether default cookie handling will happen for 
    this request.
    @discussion NOTE: This value is not used prior to 10.3
    @result YES if cookies will be sent with and set for this request; 
    otherwise NO.
*/
@property (readonly) BOOL HTTPShouldHandleCookies;

/*!
 @method HTTPShouldUsePipelining
 @abstract Reports whether the receiver is not expected to wait for the
 previous response before transmitting.
 @result YES if the receiver should transmit before the previous response
 is received.  NO if the receiver should wait for the previous response
 before transmitting.
 */
@property (readonly) BOOL HTTPShouldUsePipelining NS_AVAILABLE(10_7, 4_0);

@end



/*!
    @category NSMutableURLRequest(NSMutableHTTPURLRequest) 
    The NSMutableHTTPURLRequest on NSMutableURLRequest provides methods
    for configuring information specific to HTTP protocol requests.
*/
@interface NSMutableURLRequest (NSMutableHTTPURLRequest) 

/*! 
    @method HTTPMethod:
    @abstract Sets the HTTP request method of the receiver. 
    @param method the new HTTP request method for the receiver.
*/
@property (copy) NSString *HTTPMethod;

/*! 
    @method allHTTPHeaderFields:
    @abstract Sets the HTTP header fields of the receiver to the given
    dictionary.
    @discussion This method replaces all header fields that may have
    existed before this method call. 
    <p>Since HTTP header fields must be string values, each object and
    key in the dictionary passed to this method must answer YES when
    sent an <tt>-isKindOfClass:[NSString class]</tt> message. If either
    the key or value for a key-value pair answers NO when sent this
    message, the key-value pair is skipped.
    @param headerFields a dictionary containing HTTP header fields.
*/
@property (nullable, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;

/*! 
    @method setValue:forHTTPHeaderField:
    @abstract Sets the value of the given HTTP header field.
    @discussion If a value was previously set for the given header
    field, that value is replaced with the given value. Note that, in
    keeping with the HTTP RFC, HTTP header field names are
    case-insensitive.
    @param value the header field value. 
    @param field the header field name (case-insensitive). 
*/
- (void)setValue:(nullable NSString *)value forHTTPHeaderField:(NSString *)field;

/*! 
    @method addValue:forHTTPHeaderField:
    @abstract Adds an HTTP header field in the current header
    dictionary.
    @discussion This method provides a way to add values to header
    fields incrementally. If a value was previously set for the given
    header field, the given value is appended to the previously-existing
    value. The appropriate field delimiter, a comma in the case of HTTP,
    is added by the implementation, and should not be added to the given
    value by the caller. Note that, in keeping with the HTTP RFC, HTTP
    header field names are case-insensitive.
    @param value the header field value. 
    @param field the header field name (case-insensitive). 
*/
- (void)addValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

/*! 
    @method HTTPBody:
    @abstract Sets the request body data of the receiver.
    @discussion This data is sent as the message body of the request, as
    in done in an HTTP POST request.
    @param data the new request body data for the receiver.
*/
@property (nullable, copy) NSData *HTTPBody;

/*!
    @method HTTPBodyStream:
    @abstract Sets the request body to be the contents of the given stream. 
    @discussion The provided stream should be unopened; the request will take
    over the stream's delegate.  The entire stream's contents will be 
    transmitted as the HTTP body of the request.  Note that the body stream
    and the body data (set by setHTTPBody:, above) are mutually exclusive 
    - setting one will clear the other. 
    @param inputStream the new input stream for use by the receiver
*/
@property (nullable, retain) NSInputStream *HTTPBodyStream;

/*!
    @method HTTPShouldHandleCookies
    @abstract Decide whether default cookie handling will happen for 
    this request.
    @param YES if cookies should be sent with and set for this request; 
    otherwise NO.
    @discussion The default is YES - in other words, cookies are sent from and 
    stored to the cookie manager by default.
    NOTE: In releases prior to 10.3, this value is ignored
*/
@property BOOL HTTPShouldHandleCookies;

/*!
 @method HTTPShouldUsePipelining
 @abstract Sets whether the request should not wait for the previous response 
 before transmitting.
 @param YES if the receiver should transmit before the previous response is
 received.  NO to wait for the previous response before transmitting.
 @discussion Calling this method with a YES value does not guarantee HTTP 
 pipelining behavior.  This method may have no effect if an HTTP proxy is
 configured, or if the HTTP request uses an unsafe request method (e.g., POST
 requests will not pipeline).  Pipelining behavior also may not begin until
 the second request on a given TCP connection.  There may be other situations
 where pipelining does not occur even though YES was set.
 HTTP 1.1 allows the client to send multiple requests to the server without
 waiting for a response.  Though HTTP 1.1 requires support for pipelining,
 some servers report themselves as being HTTP 1.1 but do not support
 pipelining (disconnecting, sending resources misordered, omitting part of
 a resource, etc.).
 */
@property BOOL HTTPShouldUsePipelining NS_AVAILABLE(10_7, 4_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSExpression.h
/*	NSExpression.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;
@class NSArray<ObjectType>;
@class NSMutableDictionary;
@class NSPredicate;

NS_ASSUME_NONNULL_BEGIN

// Expressions are the core of the predicate implementation. When expressionValueWithObject: is called, the expression is evaluated, and a value returned which can then be handled by an operator. Expressions can be anything from constants to method invocations. Scalars should be wrapped in appropriate NSValue classes.

typedef NS_ENUM(NSUInteger, NSExpressionType) {
    NSConstantValueExpressionType = 0, // Expression that always returns the same value
    NSEvaluatedObjectExpressionType, // Expression that always returns the parameter object itself
    NSVariableExpressionType, // Expression that always returns whatever is stored at 'variable' in the bindings dictionary
    NSKeyPathExpressionType, // Expression that returns something that can be used as a key path
    NSFunctionExpressionType, // Expression that returns the result of evaluating a symbol
    NSUnionSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing a unionSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSIntersectSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing an intersectSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSMinusSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing a minusSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSSubqueryExpressionType NS_ENUM_AVAILABLE(10_5, 3_0) = 13,
    NSAggregateExpressionType NS_ENUM_AVAILABLE(10_5, 3_0) = 14,
    NSAnyKeyExpressionType NS_ENUM_AVAILABLE(10_9, 7_0) = 15,
    NSBlockExpressionType = 19,
    NSConditionalExpressionType NS_ENUM_AVAILABLE(10_11, 9_0) = 20

};

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSExpression : NSObject <NSSecureCoding, NSCopying> {
    @package
    struct _expressionFlags {
        unsigned int _evaluationBlocked:1;
        unsigned int _reservedExpressionFlags:31;
    } _expressionFlags;
#ifdef __LP64__
    uint32_t reserved;
#endif
    NSExpressionType _expressionType;
}

+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat argumentArray:(NSArray *)arguments NS_AVAILABLE(10_6,4_0);
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat, ...  NS_AVAILABLE(10_6,4_0);
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat arguments:(va_list)argList NS_AVAILABLE(10_6,4_0);

+ (NSExpression *)expressionForConstantValue:(nullable id)obj;    // Expression that returns a constant value
+ (NSExpression *)expressionForEvaluatedObject;    // Expression that returns the object being evaluated
+ (NSExpression *)expressionForVariable:(NSString *)string;    // Expression that pulls a value from the variable bindings dictionary
+ (NSExpression *)expressionForKeyPath:(NSString *)keyPath;    // Expression that invokes valueForKeyPath with keyPath
+ (NSExpression *)expressionForFunction:(NSString *)name arguments:(NSArray *)parameters;    // Expression that invokes one of the predefined functions. Will throw immediately if the selector is bad; will throw at runtime if the parameters are incorrect.
    // Predefined functions are:
    // name              parameter array contents				returns
	//-------------------------------------------------------------------------------------------------------------------------------------
    // sum:              NSExpression instances representing numbers		NSNumber 
    // count:            NSExpression instances representing numbers		NSNumber 
    // min:              NSExpression instances representing numbers		NSNumber  
    // max:              NSExpression instances representing numbers		NSNumber
    // average:          NSExpression instances representing numbers		NSNumber
    // median:           NSExpression instances representing numbers		NSNumber
    // mode:             NSExpression instances representing numbers		NSArray	    (returned array will contain all occurrences of the mode)
    // stddev:           NSExpression instances representing numbers		NSNumber
    // add:to:           NSExpression instances representing numbers		NSNumber
    // from:subtract:    two NSExpression instances representing numbers	NSNumber
    // multiply:by:      two NSExpression instances representing numbers	NSNumber
    // divide:by:        two NSExpression instances representing numbers	NSNumber
    // modulus:by:       two NSExpression instances representing numbers	NSNumber
    // sqrt:             one NSExpression instance representing numbers		NSNumber
    // log:              one NSExpression instance representing a number	NSNumber
    // ln:               one NSExpression instance representing a number	NSNumber
    // raise:toPower:    one NSExpression instance representing a number	NSNumber
    // exp:              one NSExpression instance representing a number	NSNumber
    // floor:            one NSExpression instance representing a number	NSNumber
    // ceiling:          one NSExpression instance representing a number	NSNumber
    // abs:              one NSExpression instance representing a number	NSNumber
    // trunc:            one NSExpression instance representing a number	NSNumber
    // uppercase:	 one NSExpression instance representing a string	NSString
    // lowercase:	 one NSExpression instance representing a string	NSString
    // random            none							NSNumber (integer) 
    // randomn:          one NSExpression instance representing a number	NSNumber (integer) such that 0 <= rand < param
    // now               none							[NSDate now]
    // bitwiseAnd:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseOr:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseXor:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // leftshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // rightshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // onesComplement:	 one NSExpression instance representing a numbers	NSNumber    (numbers will be treated as NSInteger)
    // noindex:		 an NSExpression					parameter   (used by CoreData to indicate that an index should be dropped)
    // distanceToLocation:fromLocation:
    //                   two NSExpression instances representing CLLocations    NSNumber
    // length:           an NSExpression instance representing a string         NSNumber

+ (NSExpression *)expressionForAggregate:(NSArray *)subexpressions NS_AVAILABLE(10_5, 3_0); // Expression that returns a collection containing the results of other expressions
+ (NSExpression *)expressionForUnionSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the union of the collections expressed by left and right
+ (NSExpression *)expressionForIntersectSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the intersection of the collections expressed by left and right
+ (NSExpression *)expressionForMinusSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the disjunction of the collections expressed by left and right
+ (NSExpression *)expressionForSubquery:(NSExpression *)expression usingIteratorVariable:(NSString *)variable predicate:(id)predicate NS_AVAILABLE(10_5, 3_0); // Expression that filters a collection by storing elements in the collection in the variable variable and keeping the elements for which qualifer returns true; variable is used as a local variable, and will shadow any instances of variable in the bindings dictionary, the variable is removed or the old value replaced once evaluation completes
+ (NSExpression *)expressionForFunction:(NSExpression *)target selectorName:(NSString *)name arguments:(nullable NSArray *)parameters NS_AVAILABLE(10_5, 3_0);    // Expression that invokes the selector on target with parameters. Will throw at runtime if target does not implement selector or if parameters are wrong.
+ (NSExpression *)expressionForAnyKey NS_AVAILABLE(10_9, 7_0);
+ (NSExpression *)expressionForBlock:(id (^)(id __nullable evaluatedObject, NSArray *expressions, NSMutableDictionary * __nullable context))block arguments:(nullable NSArray<NSExpression *> *)arguments NS_AVAILABLE(10_6, 4_0); // Expression that invokes the block with the parameters; note that block expressions are not encodable or representable as parseable strings.
+ (NSExpression *)expressionForConditional:(NSPredicate *)predicate trueExpression:(NSExpression *)trueExpression falseExpression:(NSExpression *)falseExpression  NS_AVAILABLE(10_11, 9_0); // Expression that will return the result of trueExpression or falseExpression depending on the value of predicate

- (instancetype)initWithExpressionType:(NSExpressionType)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// accessors for individual parameters - raise if not applicable
@property (readonly) NSExpressionType expressionType;
@property (readonly, retain) id constantValue;
@property (readonly, copy) NSString *keyPath;
@property (readonly, copy) NSString *function;
@property (readonly, copy) NSString *variable;
@property (readonly, copy) NSExpression *operand;    // the object on which the selector will be invoked (the result of evaluating a key path or one of the defined functions)
@property (nullable, readonly, copy) NSArray<NSExpression *> *arguments;    // array of expressions which will be passed as parameters during invocation of the selector on the operand of a function expression

@property (readonly, retain) id collection NS_AVAILABLE(10_5, 3_0);
@property (readonly, copy) NSPredicate *predicate NS_AVAILABLE(10_5, 3_0);
@property (readonly, copy) NSExpression *leftExpression NS_AVAILABLE(10_5, 3_0); // expression which represents the left side of a set expression
@property (readonly, copy) NSExpression *rightExpression NS_AVAILABLE(10_5, 3_0); // expression which represents the right side of a set expression


@property (readonly, copy) NSExpression *trueExpression NS_AVAILABLE(10_11, 9_0); // expression which will be evaluated if a conditional expression's predicate evaluates to true
@property (readonly, copy) NSExpression *falseExpression NS_AVAILABLE(10_11, 9_0); // expression which will be evaluated if a conditional expression's predicate evaluates to false

@property (readonly, copy) id (^expressionBlock)(id __nullable, NSArray *, NSMutableDictionary * __nullable) NS_AVAILABLE(10_6, 4_0);

// evaluate the expression using the object and bindings- note that context is mutable here and can be used by expressions to store temporary state for one predicate evaluation
- (id)expressionValueWithObject:(nullable id)object context:(nullable NSMutableDictionary *)context;

- (void)allowEvaluation NS_AVAILABLE(10_9, 7_0); // Force an expression which was securely decoded to allow evaluation

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSNotification.h
/*	NSNotification.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary, NSOperationQueue;

NS_ASSUME_NONNULL_BEGIN

/****************	Notifications	****************/

@interface NSNotification : NSObject <NSCopying, NSCoding>

@property (readonly, copy) NSString *name;
@property (nullable, readonly, retain) id object;
@property (nullable, readonly, copy) NSDictionary *userInfo;

- (instancetype)initWithName:(NSString *)name object:(nullable id)object userInfo:(nullable NSDictionary *)userInfo NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSNotification (NSNotificationCreation)

+ (instancetype)notificationWithName:(NSString *)aName object:(nullable id)anObject;
+ (instancetype)notificationWithName:(NSString *)aName object:(nullable id)anObject userInfo:(nullable NSDictionary *)aUserInfo;

- (instancetype)init /*NS_UNAVAILABLE*/;	/* do not invoke; not a valid initializer for this class */

@end

/****************	Notification Center	****************/

@interface NSNotificationCenter : NSObject {
    @package
    void * __strong _impl;
    void * __strong _callback;
    void *_pad[11];
}

+ (NSNotificationCenter *)defaultCenter;

- (void)addObserver:(id)observer selector:(SEL)aSelector name:(nullable NSString *)aName object:(nullable id)anObject;

- (void)postNotification:(NSNotification *)notification;
- (void)postNotificationName:(NSString *)aName object:(nullable id)anObject;
- (void)postNotificationName:(NSString *)aName object:(nullable id)anObject userInfo:(nullable NSDictionary *)aUserInfo;

- (void)removeObserver:(id)observer;
- (void)removeObserver:(id)observer name:(nullable NSString *)aName object:(nullable id)anObject;

- (id <NSObject>)addObserverForName:(nullable NSString *)name object:(nullable id)obj queue:(nullable NSOperationQueue *)queue usingBlock:(void (^)(NSNotification *note))block NS_AVAILABLE(10_6, 4_0);
    // The return value is retained by the system, and should be held onto by the caller in
    // order to remove the observer with removeObserver: later, to stop observation.

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSCoder.h
/*	NSCoder.h
	Copyright (c) 1993-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData, NSSet<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (nullable NSData *)decodeDataObject;
- (NSInteger)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(nullable id)object;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(nullable id)anObject;
- (void)encodeByrefObject:(nullable id)anObject;
- (void)encodeConditionalObject:(nullable id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(NSUInteger)count at:(const void *)array;
- (void)encodeBytes:(nullable const void *)byteaddr length:(NSUInteger)length;

- (nullable id)decodeObject;
- (nullable id)decodeTopLevelObjectAndReturnError:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeTopLevelObject() throws' instead");
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(NSUInteger)count at:(void *)array;
- (nullable void *)decodeBytesWithReturnedLength:(NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)encodePropertyList:(id)aPropertyList;
- (nullable id)decodePropertyList;
#endif

- (void)setObjectZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (nullable NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

@property (readonly) unsigned int systemVersion;

@property (readonly) BOOL allowsKeyedCoding;

- (void)encodeObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(nullable const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

- (BOOL)containsValueForKey:(NSString *)key;
- (nullable id)decodeObjectForKey:(NSString *)key;
- (nullable id)decodeTopLevelObjectForKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeObjectForKey(_:) throws' instead");
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;   // returned bytes immutable!

- (void)encodeInteger:(NSInteger)intv forKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);
- (NSInteger)decodeIntegerForKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);

// Returns YES if this coder requires secure coding. Secure coders check a list of allowed classes before decoding objects, and all objects must implement NSSecureCoding.
@property (readonly) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

// Specify what the expected class of the allocated object is. If the coder responds YES to -requiresSecureCoding, then an exception will be thrown if the class to be decoded does not implement NSSecureCoding or is not isKindOfClass: of the argument. If the coder responds NO to -requiresSecureCoding, then the class argument is ignored and no check of the class of the decoded object is performed, exactly as if decodeObjectForKey: had been called.
- (nullable id)decodeObjectOfClass:(Class)aClass forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);
- (nullable id)decodeTopLevelObjectOfClass:(Class)aClass forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeTopLevelObjectOfClass(_:,forKey:) throws instead");

// The class of the object may be any class in the provided NSSet, or a subclass of any class in the set. Otherwise, the behavior is the same as -decodeObjectOfClass:forKey:.
- (nullable id)decodeObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key NS_AVAILABLE(10_8, 6_0) NS_REFINED_FOR_SWIFT;
- (nullable id)decodeTopLevelObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'decodeObjectOfClasses(_:,forKey:) throws' instead");

// Calls -decodeObjectOfClasses:forKey: with a set allowing only property list types.
- (nullable id)decodePropertyListForKey:(NSString *)key NS_AVAILABLE(10_8, 6_0);

// Get the current set of allowed classes.
@property (nullable, readonly, copy) NSSet<Class> *allowedClasses NS_AVAILABLE(10_8, 6_0);

// Record that the entire decode has failed, in lieu of raising an exception
- (void)failWithError:(NSError *)error NS_AVAILABLE(10_11, 9_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
FOUNDATION_EXPORT NSObject * __nullable NXReadNSObjectFromCoder(NSCoder *decoder) NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Given an NSCoder, returns an object previously written with
   NXWriteNSObject(). The returned object is autoreleased. */

@interface NSCoder (NSTypedstreamCompatibility)

- (void)encodeNXObject:(id)object NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Writes old-style object onto the coder. No sharing is done across
   separate -encodeNXObject:. Callers must have implemented an
   -encodeWithCoder:, which parallels the -write: methods, on all of
   their classes which may be touched by this operation. Object's
   -replacementObjectForCoder: compatibility method will take care
   of calling -startArchiving:. */
    
- (nullable id)decodeNXObject NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
/* Reads an object previously written with -encodeNXObject:. No
   sharing is done across separate -decodeNXObject. Callers must
   have implemented an -initWithCoder:, which parallels the -read:
   methods, on all of their classes which may be touched by this
   operation. Object's -awakeAfterUsingCoder: compatibility method
   will take care of calling -awake and -finishUnarchiving. The
   returned object is autoreleased. */

@end
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDictionary.h
/*	NSDictionary.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray<ObjectType>, NSSet<ObjectType>, NSString, NSURL;

/****************	Immutable Dictionary	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary<__covariant KeyType, __covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (nullable ObjectType)objectForKey:(KeyType)aKey;
- (NSEnumerator<KeyType> *)keyEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
#if TARGET_OS_WIN32
- (instancetype)initWithObjects:(const ObjectType [])objects forKeys:(const KeyType [])keys count:(NSUInteger)cnt;
#else
- (instancetype)initWithObjects:(const ObjectType [])objects forKeys:(const KeyType <NSCopying> [])keys count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
#endif
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDictionary<KeyType, ObjectType> (NSExtendedDictionary)

@property (readonly, copy) NSArray<KeyType> *allKeys;
- (NSArray<KeyType> *)allKeysForObject:(ObjectType)anObject;
@property (readonly, copy) NSArray<ObjectType> *allValues;
@property (readonly, copy) NSString *description;
@property (readonly, copy) NSString *descriptionInStringsFileFormat;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
- (BOOL)isEqualToDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (NSArray<ObjectType> *)objectsForKeys:(NSArray<KeyType> *)keys notFoundMarker:(ObjectType)marker;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if url of a type that cannot be written atomically.

- (NSArray<KeyType> *)keysSortedByValueUsingSelector:(SEL)comparator;
// count refers to the number of elements in the dictionary
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys count:(NSUInteger)count NS_AVAILABLE(10_7, 5_0);

- (nullable ObjectType)objectForKeyedSubscript:(KeyType)key NS_AVAILABLE(10_8, 6_0);

- (void)enumerateKeysAndObjectsUsingBlock:(void (^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateKeysAndObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSArray<KeyType> *)keysSortedByValueUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (NSArray<KeyType> *)keysSortedByValueWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

- (NSSet<KeyType> *)keysOfEntriesPassingTest:(BOOL (^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet<KeyType> *)keysOfEntriesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSDictionary<KeyType, ObjectType> (NSDeprecated)
/// This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:andKeys:count:
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys;
@end

@interface NSDictionary<KeyType, ObjectType> (NSDictionaryCreation)

+ (instancetype)dictionary;
+ (instancetype)dictionaryWithObject:(ObjectType)object forKey:(KeyType <NSCopying>)key;
#if TARGET_OS_WIN32
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType [])keys count:(NSUInteger)cnt;
#else
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType <NSCopying> [])keys count:(NSUInteger)cnt;
#endif

+ (instancetype)dictionaryWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION NS_SWIFT_UNAVAILABLE("Use dictionary literals instead");

+ (instancetype)dictionaryWithDictionary:(NSDictionary<KeyType, ObjectType> *)dict;
+ (instancetype)dictionaryWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

- (instancetype)initWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary copyItems:(BOOL)flag;
- (instancetype)initWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

/****************	Mutable Dictionary	****************/

@interface NSMutableDictionary<KeyType, ObjectType> : NSDictionary<KeyType, ObjectType>

- (void)removeObjectForKey:(KeyType)aKey;
- (void)setObject:(ObjectType)anObject forKey:(KeyType <NSCopying>)aKey;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSExtendedMutableDictionary)

- (void)addEntriesFromDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (void)removeAllObjects;
- (void)removeObjectsForKeys:(NSArray<KeyType> *)keyArray;
- (void)setDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (void)setObject:(nullable ObjectType)obj forKeyedSubscript:(KeyType <NSCopying>)key NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSMutableDictionaryCreation)

+ (instancetype)dictionaryWithCapacity:(NSUInteger)numItems;

+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Use this method to create a key set to pass to +dictionaryWithSharedKeySet:.
 The keys are copied from the array and must be copyable.
 If the array parameter is nil or not an NSArray, an exception is thrown.
 If the array of keys is empty, an empty key set is returned.
 The array of keys may contain duplicates, which are ignored (it is undefined which object of each duplicate pair is used).
 As for any usage of hashing, is recommended that the keys have a well-distributed implementation of -hash, and the hash codes must satisfy the hash/isEqual: invariant.
 Keys with duplicate hash codes are allowed, but will cause lower performance and increase memory usage.
 */
+ (id)sharedKeySetForKeys:(NSArray<KeyType <NSCopying>> *)keys NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Create a mutable dictionary which is optimized for dealing with a known set of keys.
 Keys that are not in the key set can still be set into the dictionary, but that usage is not optimal.
 As with any dictionary, the keys must be copyable.
 If keyset is nil, an exception is thrown.
 If keyset is not an object returned by +sharedKeySetForKeys:, an exception is thrown.
 */
+ (NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithSharedKeySet:(id)keyset NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSMethodSignature.h
/*	NSMethodSignature.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSMethodSignature : NSObject {
@private
    void *_private;
    void *_reserved[6];
}

+ (nullable NSMethodSignature *)signatureWithObjCTypes:(const char *)types;

@property (readonly) NSUInteger numberOfArguments;
- (const char *)getArgumentTypeAtIndex:(NSUInteger)idx NS_RETURNS_INNER_POINTER;

@property (readonly) NSUInteger frameLength;

- (BOOL)isOneway;

@property (readonly) const char *methodReturnType NS_RETURNS_INNER_POINTER;
@property (readonly) NSUInteger methodReturnLength;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSByteCountFormatter.h
/*	NSByteCountFormatter.h
	Copyright (c) 2012-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSByteCountFormatterUnits) {
    // This causes default units appropriate for the platform to be used. Specifying any units explicitly causes just those units to be used in showing the number.
    NSByteCountFormatterUseDefault      = 0, 
    //  Specifying any of the following causes the specified units to be used in showing the number.
    NSByteCountFormatterUseBytes        = 1UL << 0, 
    NSByteCountFormatterUseKB           = 1UL << 1,
    NSByteCountFormatterUseMB           = 1UL << 2,
    NSByteCountFormatterUseGB           = 1UL << 3, 
    NSByteCountFormatterUseTB           = 1UL << 4, 
    NSByteCountFormatterUsePB           = 1UL << 5, 
    NSByteCountFormatterUseEB           = 1UL << 6, 
    NSByteCountFormatterUseZB           = 1UL << 7, 
    NSByteCountFormatterUseYBOrHigher   = 0x0FFUL << 8, 
    // Can use any unit in showing the number.
    NSByteCountFormatterUseAll          = 0x0FFFFUL 
};

typedef NS_ENUM(NSInteger, NSByteCountFormatterCountStyle) {
    // Specifies display of file or storage byte counts. The actual behavior for this is platform-specific; on OS X 10.8, this uses the decimal style, but that may change over time.
    NSByteCountFormatterCountStyleFile   = 0,        
    // Specifies display of memory byte counts. The actual behavior for this is platform-specific; on OS X 10.8, this uses the binary style, but that may change over time.
    NSByteCountFormatterCountStyleMemory = 1,
    // The following two allow specifying the number of bytes for KB explicitly. It's better to use one of the above values in most cases.
    NSByteCountFormatterCountStyleDecimal = 2,    // 1000 bytes are shown as 1 KB
    NSByteCountFormatterCountStyleBinary  = 3     // 1024 bytes are shown as 1 KB
};


NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSByteCountFormatter : NSFormatter {
    @private
    unsigned int _allowedUnits;
    char _countStyle;
    BOOL _allowsNonnumericFormatting, _includesUnit, _includesCount, _includesActualByteCount, _adaptive, _zeroPadsFractionDigits;
    int _formattingContext;
    int _reserved[5];
}

/* Shortcut for converting a byte count into a string without creating an NSByteCountFormatter and an NSNumber. If you need to specify options other than countStyle, create an instance of NSByteCountFormatter first.
 */
+ (NSString *)stringFromByteCount:(long long)byteCount countStyle:(NSByteCountFormatterCountStyle)countStyle;

/* Convenience method on stringForObjectValue:. Convert a byte count into a string without creating an NSNumber.
 */
- (NSString *)stringFromByteCount:(long long)byteCount;
    
/* Specify the units that can be used in the output. If NSByteCountFormatterUseDefault, uses platform-appropriate settings; otherwise will only use the specified units. This is the default value. Note that ZB and YB cannot be covered by the range of possible values, but you can still choose to use these units to get fractional display ("0.0035 ZB" for instance).
 */
@property NSByteCountFormatterUnits allowedUnits;

/* Specify how the count is displayed by indicating the number of bytes to be used for kilobyte. The default setting is NSByteCountFormatterFileCount, which is the system specific value for file and storage sizes.
 */ 
@property NSByteCountFormatterCountStyle countStyle;

/* Choose whether to allow more natural display of some values, such as zero, where it may be displayed as "Zero KB," ignoring all other flags or options (with the exception of NSByteCountFormatterUseBytes, which would generate "Zero bytes"). The result is appropriate for standalone output. Default value is YES. Special handling of certain values such as zero is especially important in some languages, so it's highly recommended that this property be left in its default state.
 */
@property BOOL allowsNonnumericFormatting;

/* Choose whether to include the number or the units in the resulting formatted string. (For example, instead of 723 KB, returns "723" or "KB".) You can call the API twice to get both parts, separately. But note that putting them together yourself via string concatenation may be wrong for some locales; so use this functionality with care.  Both of these values are YES by default.  Setting both to NO will unsurprisingly result in an empty string.
 */
@property BOOL includesUnit;
@property BOOL includesCount;

/* Choose whether to parenthetically (localized as appropriate) display the actual number of bytes as well, for instance "723 KB (722,842 bytes)".  This will happen only if needed, that is, the first part is already not showing the exact byte count.  If includesUnit or includesCount are NO, then this setting has no effect.  Default value is NO.
*/
@property BOOL includesActualByteCount;

/* Choose the display style. The "adaptive" algorithm is platform specific and uses a different number of fraction digits based on the magnitude (in 10.8: 0 fraction digits for bytes and KB; 1 fraction digits for MB; 2 for GB and above). Otherwise the result always tries to show at least three significant digits, introducing fraction digits as necessary. Default is YES.
 */
@property (getter=isAdaptive) BOOL adaptive;

/* Choose whether to zero pad fraction digits so a consistent number of fraction digits are displayed, causing updating displays to remain more stable. For instance, if the adaptive algorithm is used, this option formats 1.19 and 1.2 GB as "1.19 GB" and "1.20 GB" respectively, while without the option the latter would be displayed as "1.2 GB". Default value is NO.
*/
@property BOOL zeroPadsFractionDigits;

/* Specify the formatting context for the formatted string. Default is NSFormattingContextUnknown.
*/
@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSAutoreleasePool.h
/*	NSAutoreleasePool.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

NS_AUTOMATED_REFCOUNT_UNAVAILABLE
@interface NSAutoreleasePool : NSObject {
@private
    void	*_token;
    void	*_reserved3;
    void	*_reserved2;
    void	*_reserved;
}

+ (void)addObject:(id)anObject;

- (void)addObject:(id)anObject;

- (void)drain;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSLengthFormatter.h
/*      NSLengthFormatter.h
        Copyright (c) 2014-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSLengthFormatterUnit) {
    NSLengthFormatterUnitMillimeter = 8,
    NSLengthFormatterUnitCentimeter = 9,
    NSLengthFormatterUnitMeter = 11,
    NSLengthFormatterUnitKilometer = 14,
    NSLengthFormatterUnitInch = (5 << 8) + 1,
    NSLengthFormatterUnitFoot = (5 << 8) + 2,
    NSLengthFormatterUnitYard = (5 << 8) + 3,
    NSLengthFormatterUnitMile = (5 << 8) + 4,
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSLengthFormatter : NSFormatter {
@private
    void *_formatter;
    BOOL _isForPersonHeight;
    void *_reserved[2];
}
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;    // default is NSNumberFormatter with NSNumberFormatterDecimalStyle
@property NSFormattingUnitStyle unitStyle;              // default is NSFormattingUnitStyleMedium

@property (getter = isForPersonHeightUse) BOOL forPersonHeightUse;  // default is NO; if it is set to YES, the number argument for -stringFromMeters: and -unitStringFromMeters: is considered as a person's height

// Format a combination of a number and an unit to a localized string.
- (NSString *)stringFromValue:(double)value unit:(NSLengthFormatterUnit)unit;

// Format a number in meters to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 4.3m = 14.1ft in the US locale).
- (NSString *)stringFromMeters:(double)numberInMeters;

// Return a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSLengthFormatterUnit)unit;

// Return the locale-appropriate unit, the same unit used by -stringFromMeters:.
- (NSString *)unitStringFromMeters:(double)numberInMeters usedUnit:(nullable NSLengthFormatterUnit *)unitp;

// No parsing is supported. This method will return NO.
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSObjCRuntime.h
/*	NSObjCRuntime.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#include <TargetConditionals.h>
#include <Availability.h>

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#include <objc/NSObjCRuntime.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <AvailabilityMacros.h>
#endif

#if defined(__cplusplus)
#define FOUNDATION_EXTERN extern "C"
#else
#define FOUNDATION_EXTERN extern
#endif

#if TARGET_OS_WIN32

    #if defined(NSBUILDINGFOUNDATION)
        #define FOUNDATION_EXPORT FOUNDATION_EXTERN __declspec(dllexport)
    #else
        #define FOUNDATION_EXPORT FOUNDATION_EXTERN __declspec(dllimport)
    #endif

    #define FOUNDATION_IMPORT FOUNDATION_EXTERN __declspec(dllimport)

#else
    #define FOUNDATION_EXPORT  FOUNDATION_EXTERN
    #define FOUNDATION_IMPORT FOUNDATION_EXTERN
#endif

#if !defined(NS_INLINE)
    #if defined(__GNUC__)
        #define NS_INLINE static __inline__ __attribute__((always_inline))
    #elif defined(__MWERKS__) || defined(__cplusplus)
        #define NS_INLINE static inline
    #elif defined(_MSC_VER)
        #define NS_INLINE static __inline
    #elif TARGET_OS_WIN32
        #define NS_INLINE static __inline__
    #endif
#endif

#if !defined(FOUNDATION_STATIC_INLINE)
#define FOUNDATION_STATIC_INLINE static __inline__
#endif

#if !defined(FOUNDATION_EXTERN_INLINE)
#define FOUNDATION_EXTERN_INLINE extern __inline__
#endif

#if !defined(NS_REQUIRES_NIL_TERMINATION)
    #if TARGET_OS_WIN32
        #define NS_REQUIRES_NIL_TERMINATION
    #else
        #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
            #define NS_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))
        #else
            #define NS_REQUIRES_NIL_TERMINATION __attribute__((sentinel))
        #endif
    #endif
#endif

#if !defined(NS_BLOCKS_AVAILABLE)
    #if __BLOCKS__ && (MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED)
        #define NS_BLOCKS_AVAILABLE 1
    #else
        #define NS_BLOCKS_AVAILABLE 0
    #endif
#endif

// Marks APIs whose iOS versions are nonatomic, that is cannot be set/get from multiple threads safely without additional synchronization
#if !defined(NS_NONATOMIC_IOSONLY)
    #if TARGET_OS_IPHONE
	#define NS_NONATOMIC_IOSONLY nonatomic
    #else
        #if __has_feature(objc_property_explicit_atomic)
            #define NS_NONATOMIC_IOSONLY atomic
        #else
            #define NS_NONATOMIC_IOSONLY
        #endif
    #endif
#endif

// Use NS_NONATOMIC_IOSONLY instead of this older macro
#if !defined(NS_NONATOMIC_IPHONEONLY)
#define NS_NONATOMIC_IPHONEONLY NS_NONATOMIC_IOSONLY
#endif

// Marks APIs which format strings by taking a format string and optional varargs as arguments
#if !defined(NS_FORMAT_FUNCTION)
    #if (__GNUC__*10+__GNUC_MINOR__ >= 42) && (TARGET_OS_MAC || TARGET_OS_EMBEDDED)
	#define NS_FORMAT_FUNCTION(F,A) __attribute__((format(__NSString__, F, A)))
    #else
	#define NS_FORMAT_FUNCTION(F,A)
    #endif
#endif

// Marks APIs which are often used to process (take and return) format strings, so they can be used in place of a constant format string parameter in APIs
#if !defined(NS_FORMAT_ARGUMENT)
    #if defined(__clang__)
	#define NS_FORMAT_ARGUMENT(A) __attribute__ ((format_arg(A)))
    #else
	#define NS_FORMAT_ARGUMENT(A)
    #endif
#endif

// Some compilers provide the capability to test if certain features are available. This macro provides a compatibility path for other compilers.
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#ifndef __has_extension
#define __has_extension(x) 0
#endif

// Some compilers provide the capability to test if certain attributes are available. This macro provides a compatibility path for other compilers.
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

// Marks methods and functions which return an object that needs to be released by the caller but whose names are not consistent with Cocoa naming rules. The recommended fix to this is to rename the methods or functions, but this macro can be used to let the clang static analyzer know of any exceptions that cannot be fixed.
// This macro is ONLY to be used in exceptional circumstances, not to annotate functions which conform to the Cocoa naming rules.
#if __has_feature(attribute_ns_returns_retained)
#define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
#else
#define NS_RETURNS_RETAINED
#endif

// Marks methods and functions which return an object that may need to be retained by the caller but whose names are not consistent with Cocoa naming rules. The recommended fix to this is to rename the methods or functions, but this macro can be used to let the clang static analyzer know of any exceptions that cannot be fixed.
// This macro is ONLY to be used in exceptional circumstances, not to annotate functions which conform to the Cocoa naming rules.
#if __has_feature(attribute_ns_returns_not_retained)
#define NS_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
#else
#define NS_RETURNS_NOT_RETAINED
#endif

#ifndef NS_RETURNS_INNER_POINTER
#if __has_attribute(objc_returns_inner_pointer)
#define NS_RETURNS_INNER_POINTER __attribute__((objc_returns_inner_pointer))
#else
#define NS_RETURNS_INNER_POINTER
#endif
#endif

// Marks methods and functions which cannot be used when compiling in automatic reference counting mode.
#if __has_feature(objc_arc)
#define NS_AUTOMATED_REFCOUNT_UNAVAILABLE __attribute__((unavailable("not available in automatic reference counting mode")))
#else
#define NS_AUTOMATED_REFCOUNT_UNAVAILABLE
#endif

// Marks classes which cannot participate in the ARC weak reference feature.
#if __has_attribute(objc_arc_weak_reference_unavailable)
#define NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE __attribute__((objc_arc_weak_reference_unavailable))
#else
#define NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
#endif

// Marks classes that must specify @dynamic or @synthesize for properties in their @implementation (property getters & setters will not be synthesized unless the @synthesize directive is used)
#if __has_attribute(objc_requires_property_definitions)
#define NS_REQUIRES_PROPERTY_DEFINITIONS __attribute__((objc_requires_property_definitions)) 
#else
#define NS_REQUIRES_PROPERTY_DEFINITIONS
#endif

// Decorates methods in which the receiver may be replaced with the result of the method. 
#if __has_feature(attribute_ns_consumes_self)
#define NS_REPLACES_RECEIVER __attribute__((ns_consumes_self)) NS_RETURNS_RETAINED
#else
#define NS_REPLACES_RECEIVER
#endif

#if __has_feature(attribute_ns_consumed)
#define NS_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
#define NS_RELEASES_ARGUMENT
#endif

// Mark local variables of type 'id' or pointer-to-ObjC-object-type so that values stored into that local variable are not aggressively released by the compiler during optimization, but are held until either the variable is assigned to again, or the end of the scope (such as a compound statement, or method definition) of the local variable.
#ifndef NS_VALID_UNTIL_END_OF_SCOPE
#if __has_attribute(objc_precise_lifetime)
#define NS_VALID_UNTIL_END_OF_SCOPE __attribute__((objc_precise_lifetime))
#else
#define NS_VALID_UNTIL_END_OF_SCOPE
#endif
#endif

// Annotate classes which are root classes as really being root classes
#ifndef NS_ROOT_CLASS
#if __has_attribute(objc_root_class)
#define NS_ROOT_CLASS __attribute__((objc_root_class))
#else
#define NS_ROOT_CLASS
#endif
#endif

#ifndef NS_REQUIRES_SUPER
#if __has_attribute(objc_requires_super)
#define NS_REQUIRES_SUPER __attribute__((objc_requires_super))
#else
#define NS_REQUIRES_SUPER
#endif
#endif

#ifndef NS_DESIGNATED_INITIALIZER
#if __has_attribute(objc_designated_initializer)
#define NS_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
#else
#define NS_DESIGNATED_INITIALIZER
#endif
#endif

#ifndef NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
#if __has_attribute(objc_protocol_requires_explicit_implementation)
#define NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION __attribute__((objc_protocol_requires_explicit_implementation))
#else
#define NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
#endif
#endif

#if !__has_feature(objc_instancetype)
#undef instancetype
#define instancetype id
#endif

#if !defined(NS_UNAVAILABLE)
#define NS_UNAVAILABLE UNAVAILABLE_ATTRIBUTE
#endif

#if !defined(__unsafe_unretained)
#define __unsafe_unretained
#endif

#if TARGET_OS_WIN32
#import <objc/objc.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#endif

#include <CoreFoundation/CFAvailability.h>

#define NS_AVAILABLE(_mac, _ios) CF_AVAILABLE(_mac, _ios)
#define NS_AVAILABLE_MAC(_mac) CF_AVAILABLE_MAC(_mac)
#define NS_AVAILABLE_IOS(_ios) CF_AVAILABLE_IOS(_ios)

#define NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
#define NS_DEPRECATED_MAC(_macIntro, _macDep, ...) CF_DEPRECATED_MAC(_macIntro, _macDep, __VA_ARGS__)
#define NS_DEPRECATED_IOS(_iosIntro, _iosDep, ...) CF_DEPRECATED_IOS(_iosIntro, _iosDep, __VA_ARGS__)

#define NS_ENUM_AVAILABLE(_mac, _ios) CF_ENUM_AVAILABLE(_mac, _ios)
#define NS_ENUM_AVAILABLE_MAC(_mac) CF_ENUM_AVAILABLE_MAC(_mac)
#define NS_ENUM_AVAILABLE_IOS(_ios) CF_ENUM_AVAILABLE_IOS(_ios)

#define NS_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) CF_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
#define NS_ENUM_DEPRECATED_MAC(_macIntro, _macDep, ...) CF_ENUM_DEPRECATED_MAC(_macIntro, _macDep, __VA_ARGS__)
#define NS_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep, ...) CF_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep, __VA_ARGS__)

#define NS_AVAILABLE_IPHONE(_ios) CF_AVAILABLE_IOS(_ios)
#define NS_DEPRECATED_IPHONE(_iosIntro, _iosDep) CF_DEPRECATED_IOS(_iosIntro, _iosDep)

/* NS_ENUM supports the use of one or two arguments. The first argument is always the integer type used for the values of the enum. The second argument is an optional type name for the macro. When specifying a type name, you must precede the macro with 'typedef' like so:
 
typedef NS_ENUM(NSInteger, NSComparisonResult) {
    ...
};
 
If you do not specify a type name, do not use 'typedef'. For example:
 
NS_ENUM(NSInteger) {
    ...
};
*/
#define NS_ENUM(...) CF_ENUM(__VA_ARGS__)
#define NS_OPTIONS(_type, _name) CF_OPTIONS(_type, _name)

// This macro is to be used by system frameworks to support the weak linking of classes. Weak linking is supported on iOS 3.1 and Mac OS X 10.6.8 or later.
#if (__MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_6 || __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_3_1) && \
    ((__has_feature(objc_weak_class) || \
     (defined(__llvm__) && defined(__APPLE_CC__) && (__APPLE_CC__ >= 5658)) || \
     (defined(__APPLE_CC__) && (__APPLE_CC__ >= 5666))))
#define NS_CLASS_AVAILABLE(_mac, _ios) __attribute__((visibility("default"))) NS_AVAILABLE(_mac, _ios)
#define NS_CLASS_DEPRECATED(_mac, _macDep, _ios, _iosDep, ...) __attribute__((visibility("default"))) NS_DEPRECATED(_mac, _macDep, _ios, _iosDep, __VA_ARGS__)
#else
// class weak import is not supported
#define NS_CLASS_AVAILABLE(_mac, _ios)
#define NS_CLASS_DEPRECATED(_mac, _macDep, _ios, _iosDep, ...)
#endif

#define NS_CLASS_AVAILABLE_IOS(_ios) NS_CLASS_AVAILABLE(NA, _ios)
#define NS_CLASS_AVAILABLE_MAC(_mac) NS_CLASS_AVAILABLE(_mac, NA)
#define NS_CLASS_DEPRECATED_MAC(_macIntro, _macDep, ...) NS_CLASS_DEPRECATED(_macIntro, _macDep, NA, NA, __VA_ARGS__)
#define NS_CLASS_DEPRECATED_IOS(_iosIntro, _iosDep, ...) NS_CLASS_DEPRECATED(NA, NA, _iosIntro, _iosDep, __VA_ARGS__)

#define NS_EXTENSION_UNAVAILABLE(_msg)      __OS_EXTENSION_UNAVAILABLE(_msg)
#define NS_EXTENSION_UNAVAILABLE_MAC(_msg)  __OSX_EXTENSION_UNAVAILABLE(_msg)
#define NS_EXTENSION_UNAVAILABLE_IOS(_msg)  __IOS_EXTENSION_UNAVAILABLE(_msg)

#define NS_SWIFT_UNAVAILABLE(_msg) CF_SWIFT_UNAVAILABLE(_msg)

#define NS_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define NS_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")

#define NS_REFINED_FOR_SWIFT CF_REFINED_FOR_SWIFT

#define NS_SWIFT_NAME(_name) CF_SWIFT_NAME(_name)

#if __has_attribute(swift_error)
#define NS_SWIFT_NOTHROW __attribute__((swift_error(none)))
#else
#define NS_SWIFT_NOTHROW
#endif


NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT double NSFoundationVersionNumber;

#if TARGET_OS_MAC
#define NSFoundationVersionNumber10_0	397.40
#define NSFoundationVersionNumber10_1	425.00
#define NSFoundationVersionNumber10_1_1	425.00
#define NSFoundationVersionNumber10_1_2	425.00
#define NSFoundationVersionNumber10_1_3	425.00
#define NSFoundationVersionNumber10_1_4	425.00
#define NSFoundationVersionNumber10_2	462.00
#define NSFoundationVersionNumber10_2_1	462.00
#define NSFoundationVersionNumber10_2_2	462.00
#define NSFoundationVersionNumber10_2_3	462.00
#define NSFoundationVersionNumber10_2_4	462.00
#define NSFoundationVersionNumber10_2_5	462.00
#define NSFoundationVersionNumber10_2_6	462.00
#define NSFoundationVersionNumber10_2_7	462.70
#define NSFoundationVersionNumber10_2_8	462.70
#define NSFoundationVersionNumber10_3	500.00
#define NSFoundationVersionNumber10_3_1	500.00
#define NSFoundationVersionNumber10_3_2	500.30
#define NSFoundationVersionNumber10_3_3	500.54
#define NSFoundationVersionNumber10_3_4	500.56
#define NSFoundationVersionNumber10_3_5	500.56
#define NSFoundationVersionNumber10_3_6	500.56
#define NSFoundationVersionNumber10_3_7	500.56
#define NSFoundationVersionNumber10_3_8	500.56
#define NSFoundationVersionNumber10_3_9	500.58
#define NSFoundationVersionNumber10_4	567.00
#define NSFoundationVersionNumber10_4_1	567.00
#define NSFoundationVersionNumber10_4_2	567.12
#define NSFoundationVersionNumber10_4_3	567.21
#define NSFoundationVersionNumber10_4_4_Intel	567.23
#define NSFoundationVersionNumber10_4_4_PowerPC	567.21
#define NSFoundationVersionNumber10_4_5	567.25
#define NSFoundationVersionNumber10_4_6	567.26
#define NSFoundationVersionNumber10_4_7	567.27
#define NSFoundationVersionNumber10_4_8	567.28
#define NSFoundationVersionNumber10_4_9	567.29
#define NSFoundationVersionNumber10_4_10	567.29
#define NSFoundationVersionNumber10_4_11	567.36
#define NSFoundationVersionNumber10_5	677.00
#define NSFoundationVersionNumber10_5_1	677.10
#define NSFoundationVersionNumber10_5_2 677.15
#define NSFoundationVersionNumber10_5_3 677.19
#define NSFoundationVersionNumber10_5_4 677.19
#define NSFoundationVersionNumber10_5_5 677.21
#define NSFoundationVersionNumber10_5_6 677.22
#define NSFoundationVersionNumber10_5_7 677.24
#define NSFoundationVersionNumber10_5_8 677.26
#define NSFoundationVersionNumber10_6 751.00
#define NSFoundationVersionNumber10_6_1 751.00
#define NSFoundationVersionNumber10_6_2 751.14
#define NSFoundationVersionNumber10_6_3 751.21
#define NSFoundationVersionNumber10_6_4 751.29
#define NSFoundationVersionNumber10_6_5 751.42
#define NSFoundationVersionNumber10_6_6 751.53
#define NSFoundationVersionNumber10_6_7 751.53
#define NSFoundationVersionNumber10_6_8 751.62
#define NSFoundationVersionNumber10_7 833.10
#define NSFoundationVersionNumber10_7_1 833.10
#define NSFoundationVersionNumber10_7_2 833.20
#define NSFoundationVersionNumber10_7_3 833.24
#define NSFoundationVersionNumber10_7_4 833.25
#define NSFoundationVersionNumber10_8 945.00
#define NSFoundationVersionNumber10_8_1 945.00
#define NSFoundationVersionNumber10_8_2 945.11
#define NSFoundationVersionNumber10_8_3 945.16
#define NSFoundationVersionNumber10_8_4 945.18
#define NSFoundationVersionNumber10_9 1056
#define NSFoundationVersionNumber10_9_1 1056
#define NSFoundationVersionNumber10_9_2 1056.13
#define NSFoundationVersionNumber10_10 1151.16
#define NSFoundationVersionNumber10_10_1 1151.16
#define NSFoundationVersionNumber10_10_2 1152.14
#define NSFoundationVersionNumber10_10_3 1153.20
#endif

#if TARGET_OS_IPHONE
#define NSFoundationVersionNumber_iPhoneOS_2_0	678.24
#define NSFoundationVersionNumber_iPhoneOS_2_1  678.26
#define NSFoundationVersionNumber_iPhoneOS_2_2  678.29
#define NSFoundationVersionNumber_iPhoneOS_3_0  678.47
#define NSFoundationVersionNumber_iPhoneOS_3_1  678.51
#define NSFoundationVersionNumber_iPhoneOS_3_2  678.60
#define NSFoundationVersionNumber_iOS_4_0  751.32
#define NSFoundationVersionNumber_iOS_4_1  751.37
#define NSFoundationVersionNumber_iOS_4_2  751.49
#define NSFoundationVersionNumber_iOS_4_3  751.49
#define NSFoundationVersionNumber_iOS_5_0  881.00
#define NSFoundationVersionNumber_iOS_5_1  890.10
#define NSFoundationVersionNumber_iOS_6_0  992.00
#define NSFoundationVersionNumber_iOS_6_1  993.00
#define NSFoundationVersionNumber_iOS_7_0 1047.20
#define NSFoundationVersionNumber_iOS_7_1 1047.25
#define NSFoundationVersionNumber_iOS_8_0 1140.11
#define NSFoundationVersionNumber_iOS_8_1 1141.1
#define NSFoundationVersionNumber_iOS_8_2 1142.14
#define NSFoundationVersionNumber_iOS_8_3 1144.17
#endif

#if TARGET_OS_WIN32
typedef long NSInteger;
typedef unsigned long NSUInteger;

#define NSIntegerMax    LONG_MAX
#define NSIntegerMin    LONG_MIN
#define NSUIntegerMax   ULONG_MAX

#define NSINTEGER_DEFINED 1
#endif

@class NSString, Protocol;

FOUNDATION_EXPORT NSString *NSStringFromSelector(SEL aSelector);
FOUNDATION_EXPORT SEL NSSelectorFromString(NSString *aSelectorName);

FOUNDATION_EXPORT NSString *NSStringFromClass(Class aClass);
FOUNDATION_EXPORT Class __nullable NSClassFromString(NSString *aClassName);

FOUNDATION_EXPORT NSString *NSStringFromProtocol(Protocol *proto) NS_AVAILABLE(10_5, 2_0);
FOUNDATION_EXPORT Protocol * __nullable NSProtocolFromString(NSString *namestr) NS_AVAILABLE(10_5, 2_0);

FOUNDATION_EXPORT const char *NSGetSizeAndAlignment(const char *typePtr, NSUInteger * __nullable sizep, NSUInteger * __nullable alignp);

FOUNDATION_EXPORT void NSLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2);
FOUNDATION_EXPORT void NSLogv(NSString *format, va_list args) NS_FORMAT_FUNCTION(1,0);

typedef NS_ENUM(NSInteger, NSComparisonResult) {NSOrderedAscending = -1L, NSOrderedSame, NSOrderedDescending};

#if NS_BLOCKS_AVAILABLE
typedef NSComparisonResult (^NSComparator)(id obj1, id obj2);
#endif

typedef NS_OPTIONS(NSUInteger, NSEnumerationOptions) {
    NSEnumerationConcurrent = (1UL << 0),
    NSEnumerationReverse = (1UL << 1),
};

typedef NS_OPTIONS(NSUInteger, NSSortOptions) {
    NSSortConcurrent = (1UL << 0),
    NSSortStable = (1UL << 4),
};

/* The following Quality of Service (QoS) classifications are used to indicate to the system the nature and importance of work.  They are used by the system to manage a variety of resources.  Higher QoS classes receive more resources than lower ones during resource contention. */
typedef NS_ENUM(NSInteger, NSQualityOfService) {
    /* UserInteractive QoS is used for work directly involved in providing an interactive UI such as processing events or drawing to the screen. */
    NSQualityOfServiceUserInteractive = 0x21,
    
    /* UserInitiated QoS is used for performing work that has been explicitly requested by the user and for which results must be immediately presented in order to allow for further user interaction.  For example, loading an email after a user has selected it in a message list. */
    NSQualityOfServiceUserInitiated = 0x19,
    
    /* Utility QoS is used for performing work which the user is unlikely to be immediately waiting for the results.  This work may have been requested by the user or initiated automatically, does not prevent the user from further interaction, often operates at user-visible timescales and may have its progress indicated to the user by a non-modal progress indicator.  This work will run in an energy-efficient manner, in deference to higher QoS work when resources are constrained.  For example, periodic content updates or bulk file operations such as media import. */
    NSQualityOfServiceUtility = 0x11,
    
    /* Background QoS is used for work that is not user initiated or visible.  In general, a user is unaware that this work is even happening and it will run in the most efficient manner while giving the most deference to higher QoS work.  For example, pre-fetching content, search indexing, backups, and syncing of data with external systems. */
    NSQualityOfServiceBackground = 0x09,

    /* Default QoS indicates the absence of QoS information.  Whenever possible QoS information will be inferred from other sources.  If such inference is not possible, a QoS between UserInitiated and Utility will be used. */
    NSQualityOfServiceDefault = -1
} NS_ENUM_AVAILABLE(10_10, 8_0);

static const NSInteger NSNotFound = NSIntegerMax;

NS_ASSUME_NONNULL_END

#if !defined(YES)
    #define YES	(BOOL)1
#endif

#if !defined(NO)
    #define NO	(BOOL)0
#endif

#if !defined(NS_SUPPRESS_MIN_MAX_ABS)

#if (defined(__GNUC__) || defined(__clang__)) && !defined(__STRICT_ANSI__)

#if __clang__

#define __NSX_PASTE__(A,B) A##B

#if !defined(MIN)
    #define __NSMIN_IMPL__(A,B,L) ({ __typeof__(A) __NSX_PASTE__(__a,L) = (A); __typeof__(B) __NSX_PASTE__(__b,L) = (B); (__NSX_PASTE__(__a,L) < __NSX_PASTE__(__b,L)) ? __NSX_PASTE__(__a,L) : __NSX_PASTE__(__b,L); })
    #define MIN(A,B) __NSMIN_IMPL__(A,B,__COUNTER__)
#endif

#if !defined(MAX)
    #define __NSMAX_IMPL__(A,B,L) ({ __typeof__(A) __NSX_PASTE__(__a,L) = (A); __typeof__(B) __NSX_PASTE__(__b,L) = (B); (__NSX_PASTE__(__a,L) < __NSX_PASTE__(__b,L)) ? __NSX_PASTE__(__b,L) : __NSX_PASTE__(__a,L); })
    #define MAX(A,B) __NSMAX_IMPL__(A,B,__COUNTER__)
#endif

#if !defined(ABS)
    #define __NSABS_IMPL__(A,L) ({ __typeof__(A) __NSX_PASTE__(__a,L) = (A); (__NSX_PASTE__(__a,L) < 0) ? - __NSX_PASTE__(__a,L) : __NSX_PASTE__(__a,L); })
    #define ABS(A) __NSABS_IMPL__(A,__COUNTER__)
#endif

#else

#if !defined(MIN)
    #define MIN(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif

#if !defined(MAX)
    #define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

#if !defined(ABS)
    #define ABS(A)	({ __typeof__(A) __a = (A); __a < 0 ? -__a : __a; })
#endif

#endif

#else

#if !defined(MIN)
    #define MIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(MAX)
    #define MAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(ABS)
    #define ABS(A)	((A) < 0 ? (-(A)) : (A))
#endif

#endif

#endif

// ==========  Foundation.framework/Headers/NSScanner.h
/*	NSScanner.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

NS_ASSUME_NONNULL_BEGIN

@interface NSScanner : NSObject <NSCopying>

@property (readonly, copy) NSString *string;
@property NSUInteger scanLocation;
@property (nullable, copy) NSCharacterSet *charactersToBeSkipped;
@property BOOL caseSensitive;
@property (nullable, retain) id locale;

- (instancetype)initWithString:(NSString *)string NS_DESIGNATED_INITIALIZER;

@end

@interface NSScanner (NSExtendedScanner)

// On overflow, the below methods will return success and clamp
- (BOOL)scanInt:(nullable int *)result;
- (BOOL)scanInteger:(nullable NSInteger *)result NS_AVAILABLE(10_5, 2_0);
- (BOOL)scanLongLong:(nullable long long *)result;
- (BOOL)scanUnsignedLongLong:(nullable unsigned long long *)result NS_AVAILABLE(10_9, 7_0);
- (BOOL)scanFloat:(nullable float *)result;
- (BOOL)scanDouble:(nullable double *)result;
- (BOOL)scanHexInt:(nullable unsigned *)result;                                          // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexLongLong:(nullable unsigned long long *)result NS_AVAILABLE(10_5, 2_0);   // Optionally prefixed with "0x" or "0X"
- (BOOL)scanHexFloat:(nullable float *)result NS_AVAILABLE(10_5, 2_0);                   // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.
- (BOOL)scanHexDouble:(nullable double *)result NS_AVAILABLE(10_5, 2_0);                 // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.

- (BOOL)scanString:(NSString *)string intoString:(NSString * __nullable * __nullable)result;
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * __nullable * __nullable)result;

- (BOOL)scanUpToString:(NSString *)string intoString:(NSString * __nullable * __nullable)result;
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * __nullable * __nullable)result;

@property (getter=isAtEnd, readonly) BOOL atEnd;

+ (instancetype)scannerWithString:(NSString *)string;
+ (id)localizedScannerWithString:(NSString *)string;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSMapTable.h
/*	NSMapTable.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSMAPTABLE__)
#define __FOUNDATION_NSMAPTABLE__ 1

@class NSArray, NSDictionary<KeyType, ObjectType>, NSMapTable;

NS_ASSUME_NONNULL_BEGIN

/****************	Class	****************/

/* An NSMapTable is modeled after a dictionary, although, because of its options, is not a dictionary because it will behave differently.  The major option is to have keys and/or values held "weakly" in a manner that entries will be removed at some indefinite point after one of the objects is reclaimed.  In addition to being held weakly, keys or values may be copied on input or may use pointer identity for equality and hashing.
   An NSMapTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunction options or configure and use  NSPointerFunctions objects directly for initialization.
*/

static const NSPointerFunctionsOptions NSMapTableStrongMemory NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsStrongMemory;
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
static const NSPointerFunctionsOptions NSMapTableZeroingWeakMemory NS_ENUM_DEPRECATED_MAC(10_5, 10_8) = NSPointerFunctionsZeroingWeakMemory;
#endif
static const NSPointerFunctionsOptions NSMapTableCopyIn NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSMapTableObjectPointerPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSMapTableWeakMemory NS_ENUM_AVAILABLE(10_8, 6_0) = NSPointerFunctionsWeakMemory;

typedef NSUInteger NSMapTableOptions;

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSMapTable<KeyType, ObjectType> : NSObject <NSCopying, NSCoding, NSFastEnumeration>

- (instancetype)initWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithKeyPointerFunctions:(NSPointerFunctions *)keyFunctions valuePointerFunctions:(NSPointerFunctions *)valueFunctions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;

+ (NSMapTable<KeyType, ObjectType> *)mapTableWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
+ (id)mapTableWithStrongToStrongObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithWeakToStrongObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithStrongToWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithWeakToWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);
#endif

+ (NSMapTable<KeyType, ObjectType> *)strongToStrongObjectsMapTable NS_AVAILABLE(10_8, 6_0);
+ (NSMapTable<KeyType, ObjectType> *)weakToStrongObjectsMapTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak key is reclaimed
+ (NSMapTable<KeyType, ObjectType> *)strongToWeakObjectsMapTable NS_AVAILABLE(10_8, 6_0);
+ (NSMapTable<KeyType, ObjectType> *)weakToWeakObjectsMapTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak key or object is reclaimed

/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
@property (readonly, copy) NSPointerFunctions *keyPointerFunctions;
@property (readonly, copy) NSPointerFunctions *valuePointerFunctions;

- (nullable ObjectType)objectForKey:(nullable KeyType)aKey;

- (void)removeObjectForKey:(nullable KeyType)aKey;
- (void)setObject:(nullable ObjectType)anObject forKey:(nullable KeyType)aKey;   // add/replace value (CFDictionarySetValue, NSMapInsert)

@property (readonly) NSUInteger count;

- (NSEnumerator<KeyType> *)keyEnumerator;
- (nullable NSEnumerator<ObjectType> *)objectEnumerator;

- (void)removeAllObjects;

- (NSDictionary<KeyType, ObjectType> *)dictionaryRepresentation;  // create a dictionary of contents
@end

NS_ASSUME_NONNULL_END


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

NS_ASSUME_NONNULL_BEGIN

/****************	void * Map table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void * __nullable _bs;} NSMapEnumerator;



FOUNDATION_EXPORT void NSFreeMapTable(NSMapTable *table);
FOUNDATION_EXPORT void NSResetMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSCompareMapTables(NSMapTable *table1, NSMapTable *table2);
FOUNDATION_EXPORT NSMapTable *NSCopyMapTableWithZone(NSMapTable *table, NSZone * __nullable zone);
FOUNDATION_EXPORT BOOL NSMapMember(NSMapTable *table, const void *key, void * __nullable * __nullable originalKey, void * __nullable * __nullable value);
FOUNDATION_EXPORT void * __nullable NSMapGet(NSMapTable *table, const void * __nullable key);
FOUNDATION_EXPORT void NSMapInsert(NSMapTable *table, const void * __nullable key, const void * __nullable value);
FOUNDATION_EXPORT void NSMapInsertKnownAbsent(NSMapTable *table, const void * __nullable key, const void * __nullable value);
FOUNDATION_EXPORT void * __nullable NSMapInsertIfAbsent(NSMapTable *table, const void * __nullable key, const void * __nullable value);
FOUNDATION_EXPORT void NSMapRemove(NSMapTable *table, const void * __nullable key);
FOUNDATION_EXPORT NSMapEnumerator NSEnumerateMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSNextMapEnumeratorPair(NSMapEnumerator *enumerator, void * __nullable * __nullable key, void * __nullable * __nullable value);
FOUNDATION_EXPORT void NSEndMapTableEnumeration(NSMapEnumerator *enumerator);
FOUNDATION_EXPORT NSUInteger NSCountMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSString *NSStringFromMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableKeys(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableValues(NSMapTable *table);


/****************     Legacy     ***************************************/

typedef struct {
    NSUInteger	(* __nullable hash)(NSMapTable *table, const void *);
    BOOL	(* __nullable isEqual)(NSMapTable *table, const void *, const void *);
    void	(* __nullable retain)(NSMapTable *table, const void *);
    void	(* __nullable release)(NSMapTable *table, void *);
    NSString 	* __nullable (* __nullable describe)(NSMapTable *table, const void *);
    const void	* __nullable notAKeyMarker;
} NSMapTableKeyCallBacks;
    
#define NSNotAnIntMapKey	((const void *)NSIntegerMin)
#define NSNotAnIntegerMapKey	((const void *)NSIntegerMin)
#define NSNotAPointerMapKey	((const void *)UINTPTR_MAX)

typedef struct {
    void	(* __nullable retain)(NSMapTable *table, const void *);
    void	(* __nullable release)(NSMapTable *table, void *);
    NSString 	* __nullable(* __nullable describe)(NSMapTable *table, const void *);
} NSMapTableValueCallBacks;

FOUNDATION_EXPORT NSMapTable *NSCreateMapTableWithZone(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity, NSZone * __nullable zone);
FOUNDATION_EXPORT NSMapTable *NSCreateMapTable(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity);


/****************	Common map table key callbacks	****************/

FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntegerMapKeyCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerOrNullMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonRetainedObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntMapKeyCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

/****************	Common map table value callbacks	****************/

FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntegerMapValueCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonRetainedObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntMapValueCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

NS_ASSUME_NONNULL_END

#else

#if defined(__has_include)
#if __has_include(<Foundation/NSMapTablePriv.h>)
#include <Foundation/NSMapTablePriv.h>
#endif
#endif

#endif

#endif

// ==========  Foundation.framework/Headers/NSComparisonPredicate.h
/*	NSComparisonPredicate.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

NS_ASSUME_NONNULL_BEGIN

// Flags(s) that can be passed to the factory to indicate that a operator operating on strings should do so in a case insensitive fashion.
typedef NS_OPTIONS(NSUInteger, NSComparisonPredicateOptions) {
    NSCaseInsensitivePredicateOption = 0x01,
    NSDiacriticInsensitivePredicateOption = 0x02,
    NSNormalizedPredicateOption NS_ENUM_AVAILABLE(10_6, 4_0) = 0x04, /* Indicate that the strings to be compared have been preprocessed; this supersedes other options and is intended as a performance optimization option */
};

// Describes how the operator is modified: can be direct, ALL, or ANY
typedef NS_ENUM(NSUInteger, NSComparisonPredicateModifier) {
    NSDirectPredicateModifier = 0, // Do a direct comparison
    NSAllPredicateModifier, // ALL toMany.x = y
    NSAnyPredicateModifier // ANY toMany.x = y
};


// Type basic set of operators defined. Most are obvious; NSCustomSelectorPredicateOperatorType allows a developer to create an operator which uses the custom selector specified in the constructor to do the evaluation.
typedef NS_ENUM(NSUInteger, NSPredicateOperatorType) {
    NSLessThanPredicateOperatorType = 0, // compare: returns NSOrderedAscending
    NSLessThanOrEqualToPredicateOperatorType, // compare: returns NSOrderedAscending || NSOrderedSame
    NSGreaterThanPredicateOperatorType, // compare: returns NSOrderedDescending
    NSGreaterThanOrEqualToPredicateOperatorType, // compare: returns NSOrderedDescending || NSOrderedSame
    NSEqualToPredicateOperatorType, // isEqual: returns true
    NSNotEqualToPredicateOperatorType, // isEqual: returns false
    NSMatchesPredicateOperatorType,
    NSLikePredicateOperatorType,
    NSBeginsWithPredicateOperatorType,
    NSEndsWithPredicateOperatorType,
    NSInPredicateOperatorType, // rhs contains lhs returns true
    NSCustomSelectorPredicateOperatorType,
    NSContainsPredicateOperatorType NS_ENUM_AVAILABLE(10_5, 3_0) = 99, // lhs contains rhs returns true
    NSBetweenPredicateOperatorType NS_ENUM_AVAILABLE(10_5, 3_0)
};

@class NSPredicateOperator;
@class NSExpression;

// Comparison predicates are predicates which do some form of comparison between the results of two expressions and return a BOOL. They take an operator, a left expression, and a right expression, and return the result of invoking the operator with the results of evaluating the expressions.

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSComparisonPredicate : NSPredicate {
    @private
    void *_reserved2;
    NSPredicateOperator *_predicateOperator;
    NSExpression *_lhs;
    NSExpression *_rhs;
}

+ (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options;
+ (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector;

- (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (readonly) NSPredicateOperatorType predicateOperatorType;
@property (readonly) NSComparisonPredicateModifier comparisonPredicateModifier;
@property (readonly, retain) NSExpression *leftExpression;
@property (readonly, retain) NSExpression *rightExpression;
@property (nullable, readonly) SEL customSelector;
@property (readonly) NSComparisonPredicateOptions options;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSFileWrapper.h
/*
	NSFileWrapper.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary<KeyType, ObjectType>, NSError, NSString, NSURL;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSFileWrapperReadingOptions) {
    
    /* Whether the contents are read immediately, applied recursively in the case of directory file wrappers. If reading with this option succeeds then subsequent invocations of -fileWrappers, -regularFileContents, -symbolicLinkDestinationURL:, -serializedRepresentation, and, on Mac OS X, -[NSFileWrapper(NSExtensions) icon] sent to the receiver and all its descendant file wrappers won't fail. For performance NSFileWrapper may or may not immediately read the contents of some file packages immediately even when this option is chosen. For example, the contents of bundles (not all file packages are bundles) are immutable to the user so on Mac OS X NSFileWrapper may read the children of such a directory lazily. You can use this option to take a reasonable snapshot of a file or folder for writing later. For example, a Mac OS X application like TextEdit can use this option when creating new file wrappers to represent attachments that the user creates by copying and pasting or dragging and dropping from the Finder to a TextEdit document. You wouldn't use this option when reading a document file package because that would cause unnecessarily bad perfomance. For example, an application wouldn't use this option when creating file wrappers to represent attachments as it's opening a document stored in a file package.
    */
    NSFileWrapperReadingImmediate = 1 << 0,

    /* Whether file mapping for regular file wrappers is disallowed. In Mac OS 10.6 and newer NSFileWrapper only ever memory maps files on internal drives, regardless of whether this option is used. It never memory maps files on external drives or network volumes. You can use this option to keep NSFileWrapper from memory mapping files at all, even ones on internal drives. This is useful if you want to make sure your application doesn't hold files open (mapped files are open files) and therefore prevent the user from ejecting DVDs, unmounting disk partitions, or unmounting disk images.
    */
    NSFileWrapperReadingWithoutMapping = 1 << 1

} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSFileWrapperWritingOptions) {

    /* Whether writing is done atomically. You can use this option to ensure that when overwriting a file package the overwriting either completely succeeds or completely fails, with no possibility of leaving the file package in an inconsistent state. Because this option causes additional I/O you shouldn't use it unnecessarily. For example, on Mac OS X you wouldn't use this option in an override of -[NSDocument writeToURL:ofType:error:] because NSDocument's implementation of safe saving already does atomic writing.
    */
    NSFileWrapperWritingAtomic = 1 << 0,

    /* Whether descendant file wrappers are sent -setFilename: if the writing succeeds. This is necessary when your application passes original contents URLs to -writeToURL:options:originalContentsURL:error:. Without using this and reusing child file wrappers properly subsequent invocations of -writeToURL:options:originalContentsURL:error: wouldn't be able to reliably create hard links in a new file package for performance because the record of names in the old file package would be out of date.
    */
    NSFileWrapperWritingWithNameUpdating = 1 << 1

} NS_ENUM_AVAILABLE(10_6, 4_0);

NS_CLASS_AVAILABLE(10_0, 4_0)
@interface NSFileWrapper : NSObject<NSCoding> {
    @private
    NSDictionary *_fileAttributes;
    NSString *_preferredFileName;
    NSString *_fileName;
    id _contents;
    id _icon;
    id _moreVars;
}

#pragma mark *** Initialization ***

/* A designated initializer for creating an instance whose kind (directory, regular file, or symbolic link) is determined based on what the URL locates. If reading is not successful return nil after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be read.
*/
- (nullable instancetype)initWithURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_6, 4_0);

/* A designated initializer for creating an instance for which -isDirectory returns YES. The passed-in dictionary must contain entries whose values are the file wrappers that are to become children and whose keys are file names. Each file wrapper that does not already have a preferred file name is sent -setPreferredFilename: with the corresponding key as the argument.
*/
- (instancetype)initDirectoryWithFileWrappers:(NSDictionary<NSString *, NSFileWrapper *> *)childrenByPreferredName NS_DESIGNATED_INITIALIZER;

/* A designated initializer for creating an instance for which -isRegularFile returns YES.
*/
- (instancetype)initRegularFileWithContents:(NSData *)contents NS_DESIGNATED_INITIALIZER;

/* A designated initializer for creating an instance for which -isSymbolicLink returns YES. -writeToURL:options:originalContentsURL:error: uses the result of sending -relativePath to this URL when creating a symbolic link. (An NSURL initialized by -initFileURLWithPath: returns that entire path when sent -relativePath though.)
*/
- (instancetype)initSymbolicLinkWithDestinationURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_6, 4_0);

/* A designated initializer. The data must be in the same format as that returned by -serializedRepresentation.
*/
- (nullable instancetype)initWithSerializedRepresentation:(NSData *)serializeRepresentation NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

#pragma mark *** Properties Applicable to Every Kind of File Wrapper ***

/* What kind of file wrapper it is. Invocations of -readFromURL:options:error: may change what subsequent invocations of these methods return.
*/
@property (readonly, getter=isDirectory) BOOL directory;
@property (readonly, getter=isRegularFile) BOOL regularFile;
@property (readonly, getter=isSymbolicLink) BOOL symbolicLink;

/* The file name that is "preferred." When the receiver is added to a parent directory file wrapper the parent will attempt to use this name as the key into its dictionary of children. Usually the preferred file name will actually get used in this situation but it won't be if that key is already in use. The default implementation of this method causes existing parents to remove and re-add the child to accommodate the change. Preferred file names of children are not effectively preserved when you write a file wrapper to disk and then later instantiate another file wrapper by reading. If your application needs to preserve the user-visible names of attachments it has to make its own arrangements for their storage.

Some instances of NSFileWrapper may be created without a preferredFilename (e.g. -initDirectoryWithFileWrappers: or -initRegularFileWithContents:), meaning preferredFilename may be nil. However, setting nil is never allowed and will result in an exception.
*/
@property (nullable, copy) NSString *preferredFilename;

/* The actual file name. Often it will be the same as the preferred file name but might instead be a name derived from the preferred file name. You can use this method to find out the name of a child that's just been read but you should not use it to find out the name of a child that's about to be written, because the name might be about to change. Send -keyForFileWrapper: to the parent instead.
*/
@property (nullable, copy) NSString *filename;

/* The file attributes, in a dictionary of the same sort as those returned by -[NSFileManager attributesOfItemAtPath:error:].
*/
@property (copy) NSDictionary<NSString *, id> *fileAttributes;

/* On Mac OS X methods for setting and getting the icon are in AppKit's NSFileWrapper(NSExtensions), declared in <AppKit/NSFileWrapperExtensions.h>.
*/

#pragma mark *** Reading ***

/* Whether the receiver matches the directory, regular file, or symbolic link that is located by the URL. For a directory, children are compared against the files in the directory, recursively. The contents of files are not compared; matching of regular files is based on file modification dates. Because children of directory file wrappers are not read immediately by -initWithURL:options:error: or -readFromURL:options:error: unless NSFileWrapperReadingImmediate is used, creating a file wrapper and then later sending it this message is not a reliable way to simply check whether anything in a directory has changed. You can use this method to determine whether the receiver's contents in memory are out of date relative to the file system.
*/
- (BOOL)matchesContentsOfURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);

/* Recursively reread the entire contents of the receiver from the specified location, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be reread. When reading a directory children are added and removed as necessary to match the file system.
*/
- (BOOL)readFromURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError NS_AVAILABLE(10_6, 4_0);

#pragma mark *** Writing ***

/* Recursively write the entire contents of the receiver at the specified location, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be written. originalContentsURL may be nil or it may be the location of a previous revision of what is being written. If it is not nil the default implementation of this method attempts to avoid unnecessary I/O by merely writing hard links to regular files instead of actually writing out their contents. The descendant file wrappers must return accurate values when sent -filename for this to work (use NSFileWrapperWritingWithNameUpdating to increase the likelihood of that).
*/
- (BOOL)writeToURL:(NSURL *)url options:(NSFileWrapperWritingOptions)options originalContentsURL:(nullable NSURL *)originalContentsURL error:(NSError **)outError NS_AVAILABLE(10_6, 4_0);

#pragma mark *** Serialization ***

/* Return an NSData suitable for passing to -initWithSerializedRepresentation:. This method may return nil if the receiver is the result of reading from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
@property (nullable, readonly, copy) NSData *serializedRepresentation;

#pragma mark *** Directories ***

/* Each of these methods throw an exception when [receiver isDirectory]==NO. */

/* Add a file wrapper to the receiver's children and return the file name that uniquely identifies it among the receiver's children. The unique file name will be the same as the passed-in file wrapper's preferred file name unless that name is already in use as a key into the receiver's dictionary of children. Beware of the fact that -initDirectoryWithFileWrappers:, -initRegularFileWithContents:, and -initSymbolicLinkWithDestinationURL: do not automatically set the preferred file name.
*/
- (NSString *)addFileWrapper:(NSFileWrapper *)child;

/* A convenience method. The default implementation merely allocates a new file wrapper, initializes it with -initRegularFileWithContents:, sends it -setPreferredFileName:fileName, adds it to the receiver with -addFileWrapper:, and returns what -addFileWrapper: returned.
*/
- (NSString *)addRegularFileWithContents:(NSData *)data preferredFilename:(NSString *)fileName;

/* Remove a file wrapper from the receiver's children.
*/
- (void)removeFileWrapper:(NSFileWrapper *)child;

/* Return a dictionary whose values are the receiver's children and whose keys are the unique file name that has been assigned to each one. This method may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
@property (nullable, readonly, copy) NSDictionary<NSString *, NSFileWrapper *> *fileWrappers;

/* Return the unique file name that has been assigned to a child or nil if it is not a child of the receiver.
*/
- (nullable NSString *)keyForFileWrapper:(NSFileWrapper *)child;

#pragma mark *** Regular Files ***

/* This method throws an exception when [receiver isRegularFile]==NO. */

/* Return the receiver's contents. This may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
@property (nullable, readonly, copy) NSData *regularFileContents;

#pragma mark *** Symbolic Links ***

/* This method throws an exception when [receiver isSymbolicLink]==NO. */

/* Return the destination link of the receiver. This may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
@property (nullable, readonly, copy) NSURL *symbolicLinkDestinationURL NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@interface NSFileWrapper(NSDeprecated)

#pragma mark *** Backward Compatibility ***

/* Methods that were deprecated in OS X 10.6 and never available on iOS. */

- (nullable id)initWithPath:(NSString *)path NS_DEPRECATED_MAC(10_0, 10_10, "Use -initWithURL:options:error: instead.");
- (id)initSymbolicLinkWithDestination:(NSString *)path NS_DEPRECATED_MAC(10_0, 10_10, "Use -initSymbolicLinkWithDestinationURL: and -setPreferredFileName:, if necessary, instead.");
- (BOOL)needsToBeUpdatedFromPath:(NSString *)path NS_DEPRECATED_MAC(10_0, 10_10, "Use -matchesContentsOfURL: instead.");
- (BOOL)updateFromPath:(NSString *)path NS_DEPRECATED_MAC(10_0, 10_10, "Use -readFromURL:options:error: instead.");
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)atomicFlag updateFilenames:(BOOL)updateFilenamesFlag NS_DEPRECATED_MAC(10_0, 10_10, "Use -writeToURL:options:originalContentsURL:error: instead.");
- (NSString *)addFileWithPath:(NSString *)path NS_DEPRECATED_MAC(10_0, 10_10, "Instantiate a new NSFileWrapper with -initWithURL:options:error:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.");
- (NSString *)addSymbolicLinkWithDestination:(NSString *)path preferredFilename:(NSString *)filename NS_DEPRECATED_MAC(10_0, 10_10, "Instantiate a new NSFileWrapper with -initWithSymbolicLinkDestinationURL:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.");
- (NSString *)symbolicLinkDestination NS_DEPRECATED_MAC(10_0, 10_10, "Use -symbolicLinkDestinationURL instead.");

@end

#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDateIntervalFormatter.h
/*	NSDateIntervalFormatter.h
        Copyright (c) 2013-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>
#include <dispatch/dispatch.h>
@class NSLocale, NSCalendar, NSTimeZone, NSDate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSDateIntervalFormatterStyle) {
    NSDateIntervalFormatterNoStyle = 0,
    NSDateIntervalFormatterShortStyle = 1,
    NSDateIntervalFormatterMediumStyle = 2,
    NSDateIntervalFormatterLongStyle = 3,
    NSDateIntervalFormatterFullStyle = 4
} NS_ENUM_AVAILABLE(10_10, 8_0);

// NSDateIntervalFormatter is used to format the range between two NSDates in a locale-sensitive way.
// NSDateIntervalFormatter returns nil and NO for all methods in NSFormatter.

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSDateIntervalFormatter : NSFormatter
{
@private
    NSLocale *_locale;
    NSCalendar *_calendar;
    NSTimeZone *_timeZone;
    NSString *_dateTemplate;
    NSString *_dateTemplateFromStyles;
    void *_formatter;
    NSDateIntervalFormatterStyle _dateStyle;
    NSDateIntervalFormatterStyle _timeStyle;
    BOOL _modified;
    BOOL _useTemplate;
    dispatch_semaphore_t _lock;
    void *_reserved[4];
}

@property (null_resettable, copy) NSLocale   *locale;                // default is [NSLocale currentLocale]
@property (null_resettable, copy) NSCalendar *calendar;              // default is the calendar of the locale
@property (null_resettable, copy) NSTimeZone *timeZone;              // default is [NSTimeZone defaultTimeZone]
@property (null_resettable, copy) NSString   *dateTemplate;          // default is an empty string
@property NSDateIntervalFormatterStyle dateStyle;   // default is NSDateIntervalFormatterNoStyle
@property NSDateIntervalFormatterStyle timeStyle;   // default is NSDateIntervalFormatterNoStyle

/*
     If the range smaller than the resolution specified by the dateTemplate, a single date format will be produced. If the range is larger than the format specified by the dateTemplate, a locale-specific fallback will be used to format the items missing from the pattern.
     
     For example, if the range is 2010-03-04 07:56 - 2010-03-04 19:56 (12 hours)
     - The pattern jm will produce
        for en_US, "7:56 AM - 7:56 PM"
        for en_GB, "7:56 - 19:56"
     - The pattern MMMd will produce
        for en_US, "Mar 4"
        for en_GB, "4 Mar"
     If the range is 2010-03-04 07:56 - 2010-03-08 16:11 (4 days, 8 hours, 15 minutes)
     - The pattern jm will produce
        for en_US, "3/4/2010 7:56 AM - 3/8/2010 4:11 PM"
        for en_GB, "4/3/2010 7:56 - 8/3/2010 16:11"
     - The pattern MMMd will produce
        for en_US, "Mar 4-8"
        for en_GB, "4-8 Mar"
*/
- (NSString *)stringFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSFilePresenter.h
/*
	NSFilePresenter.h
	Copyright (c) 2010-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSError, NSFileVersion, NSOperationQueue, NSURL;

NS_ASSUME_NONNULL_BEGIN

/* A protocol to be implemented by objects that present the contents of files or directories to the user for viewing or editing. The objects can take an active role in operations that access those files or directories, even operations performed by other processes in the system. For an NSFilePresenter to be aware of such file access it must be "coordinated" file access. The NSFileCoordinator class that is used to do coordinated file access is declared in <Foundation/NSFileCoordinator.h>. Starting in version 10.7 many components of Mac OS X use NSFileCoordinator, including AppKit, Finder, and various applications. NSDocument conforms to the NSFilePresenter protocol and has useful implementations of all of its methods. You are unlikely to have to implement NSFilePresenter yourself in an NSDocument-based application.

See the comments for -[NSFileCoordinator initWithFilePresenter:] for information about how an NSFilePresenter can avoid receiving messages about its own reading and writing.

You can consider "item" in method names in this header file to be an abbreviation of "fileOrDirectory." As always, a directory might actually be a file package.
*/
@protocol NSFilePresenter<NSObject>

@required

/* The NSURL that locates the file or directory that the receiver is presenting to the user. Implementations of this method must be prepared to be invoked by Cocoa in any queue, at any time, including from within invocations of NSFileCoordinator methods. A nil value is valid and means that the presented item does not exist yet. An NSFilePresenter with a nil presentedItemURL will be asked for its presentedItemURL again when coordinated file access on behalf of that NSFilePresenter completes, in case the presented item was just created.

For example, NSDocument has a -presentedItemURL method that usually returns [self fileURL]. In a shoebox application that stores the user's data in files somewhere on the user's computer you can implement this method to specify the directory that contains those files.
*/
@property (nullable, readonly, copy) NSURL *presentedItemURL;

/* The operation queue in which all of the other NSFilePresenter messages except -presentedItemURL will be sent to the receiver. Implementations of this method must be prepared to be invoked by Cocoa in any queue, at any time, including from within invocations of NSFileCoordinator methods. A nil value is not valid.

For example, NSDocument has a -presentedItemOperationQueue method that returns a private queue. In very simple cases you can return [NSOperationQueue mainQueue], but doing so is often an invitation to deadlocks.
*/
@property (readonly, retain) NSOperationQueue *presentedItemOperationQueue;

@optional

/* Support for App Sandbox on OS X. Some applications, given a user-selected file, require access to additional files or directories with related names. For example, a movie player might have to automatically load subtitles for a movie that the user opened. By convention, the subtitle file has the same name as the movie, but a different file extension. If the movie player is sandboxed, its use of NSOpenPanel will grant it access to the user-selected movie (the primary item). However, access to the subtitle file (the secondary item) will not be granted by NSOpenPanel. To get access to a secondary item, a process can register an NSFilePresenter for it and unregister the NSFilePresenter once the application is finished accessing it. Each NSFilePresenter of a secondary item must return an NSURL to the primary item on request. You make that happen by providing an implementation of -primaryPresentedItemURL that returns an NSURL for the primary item.
*/
@property (nullable, readonly, copy) NSURL *primaryPresentedItemURL NS_AVAILABLE(10_8, NA);

/* Given that something in the system is waiting to read from the presented file or directory, do whatever it takes to ensure that the application will behave properly while that reading is happening, and then invoke the completion handler. The definition of "properly" depends on what kind of ownership model the application implements. Implementations of this method must always invoke the passed-in reader block because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting. When an implementation of this method invokes the passed-in block it can pass that block yet another block, which will be invoked in the receiver's operation queue when reading is complete.

A common sequence that your NSFilePresenter must handle is the file coordination mechanism sending this message, then sending -savePresentedItemChangesWithCompletionHandler:, and then, after you have invoked that completion handler, invoking your reacquirer.
*/
- (void)relinquishPresentedItemToReader:(void (^)(void (^ __nullable reacquirer)(void)))reader;

/* Given that something in the system is waiting to write to the presented file or directory, do whatever it takes to ensure that the application will behave properly while that writing is happening, and then invoke the completion handler. The definition of "properly" depends on what kind of ownership model the application implements. Implementations of this method must always invoke the passed-in writer block because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting. When an implementation of this method invokes the passed-in block it can pass that block yet another block, which will be invoked in the receiver's operation queue when writing is complete.

A common sequence that your NSFilePresenter must handle is the file coordination mechanism sending this message, then sending -accommodatePresentedItemDeletionWithCompletionHandler: or -savePresentedItemChangesWithCompletionHandler:, and then, after you have invoked that completion handler, invoking your reacquirer. It is also common for your NSFilePresenter to be sent a combination of the -presented... messages listed below in between relinquishing and reacquiring.
*/
- (void)relinquishPresentedItemToWriter:(void (^)(void (^ __nullable reacquirer)(void)))writer;

/* Given that something in the system is waiting to read from the presented file or directory, do whatever it takes to ensure that the contents of the presented file or directory is completely up to date, and then invoke the completion handler. If successful (including when there is simply nothing to do) pass nil to the completion handler, or if not successful pass an NSError that encapsulates the reason why saving failed. Implementations of this method must always invoke the completion handler because other parts of the system will wait until it is invoked or the user loses patience and cancels the waiting. If this method is not implemented then the NSFilePresenter is assumed to be one that never lets the user make changes that need to be saved.

For example, NSDocument has an implementation of this method that autosaves the document if it has been changed since the last time it was saved or autosaved. That way when another process tries to read the document file it always reads the same version of the document that the user is looking at in your application. (WYSIWGCBF - What You See Is What Gets Copied By Finder.) A shoebox application would also implement this method.

The file coordination mechanism does not always send -relinquishPresentedItemToReader: or -relinquishPresentedItemToWriter: to your NSFilePresenter before sending this message. For example, other process' use of -[NSFileCoordinator prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:] can cause this to happen.
*/
- (void)savePresentedItemChangesWithCompletionHandler:(void (^)(NSError * __nullable errorOrNil))completionHandler;

/* Given that something in the system is waiting to delete the presented file or directory, do whatever it takes to ensure that the deleting will succeed and that the receiver's application will behave properly when the deleting has happened, and then invoke the completion handler. If successful (including when there is simply nothing to do) pass nil to the completion handler, or if not successful pass an NSError that encapsulates the reason why preparation failed. Implementations of this method must always invoke the completion handler because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting.

For example, NSDocument has an implementation of this method that closes the document. That way if the document is in the trash and the user empties the trash the document is simply closed before its file is deleted. This means that emptying the trash will not fail with an alert about the file being "in use" just because the document's file is memory mapped by the application. It also means that the document won't be left open with no document file underneath it. A shoebox application would only implement this method to be robust against surprising things like the user deleting its data directory while the application is running.

The file coordination mechanism does not always send -relinquishPresentedItemToReader: or -relinquishPresentedItemToWriter: to your NSFilePresenter before sending this message. For example, other process' use of -[NSFileCoordinator prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:] can cause this to happen.
*/
- (void)accommodatePresentedItemDeletionWithCompletionHandler:(void (^)(NSError * __nullable errorOrNil))completionHandler;

/* Be notified that the file or directory has been moved or renamed, or a directory containing it has been moved or renamed. A typical implementation of this method will cause subsequent invocations of -presentedItemURL to return the new URL.

The new URL may have a different file name extension than the current value of the presentedItemURL property.

For example, NSDocument implements this method to handle document file moving and renaming. A shoebox application would only implement this method to be robust against surprising things like the user moving its data directory while the application is running.

Not all programs use file coordination. Your NSFileProvider may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/
- (void)presentedItemDidMoveToURL:(NSURL *)newURL;

#pragma mark *** Files and File Packages ***

/* These messages are sent by the file coordination machinery only when the presented item is a file or file package.
*/

/* Be notified that the file or file package's contents or attributes have been been written to. Because this method may be be invoked when the attributes have changed but the contents have not, implementations that read the contents must use modification date checking to avoid needless rereading. They should check that the modification date has changed since the receiver most recently read from or wrote to the item. To avoid race conditions, getting the modification date should typically be done within invocations of one of the -[NSFileCoordinator coordinate...] methods.

For example, NSDocument implements this method to react to both contents changes (like the user overwriting the document file with another application) and attribute changes (like the user toggling the "Hide extension" checkbox in a Finder info panel). It uses modification date checking as described above.

Not all programs use file coordination. Your NSFileProvider may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/
- (void)presentedItemDidChange;

/* Be notified that something in the system has added, removed, or resolved a version of the file or file package.

For example, NSDocument has implementations of these methods that help decide whether to present a versions browser when it has reacquired after relinquishing to a writer, and to react to versions being added and removed while it is presenting the versions browser.
*/
- (void)presentedItemDidGainVersion:(NSFileVersion *)version;
- (void)presentedItemDidLoseVersion:(NSFileVersion *)version;
- (void)presentedItemDidResolveConflictVersion:(NSFileVersion *)version;

#pragma mark *** Directories ***

/* These methods are sent by the file coordination machinery only when the presented item is a directory. "Contained by the directory" in these comments means contained by the directory, a directory contained by the directory, and so on.
*/

/* Given that something in the system is waiting to delete a file or directory contained by the directory, do whatever it takes to ensure that the deleting will succeed and that the receiver's application will behave properly when the deleting has happened, and then invoke the completion handler. If successful (including when there is simply nothing to do) pass nil to the completion handler, or if not successful pass an NSError that encapsulates the reason why preparation failed. Implementations of this method must always invoke the completion handler because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting.

The file coordination mechanism does not always send -relinquishPresentedItemToReader: or -relinquishPresentedItemToWriter: to your NSFilePresenter before sending this message. For example, other process' use of -[NSFileCoordinator prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:] can cause this to happen.
*/
- (void)accommodatePresentedSubitemDeletionAtURL:(NSURL *)url completionHandler:(void (^)(NSError * __nullable errorOrNil))completionHandler;

/* Be notified that a file or directory contained by the directory has been added. If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.

Not all programs use file coordination. Your NSFileProvider may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/
- (void)presentedSubitemDidAppearAtURL:(NSURL *)url;

/* Be notified that a file or directory contained by the directory has been moved or renamed. If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.

Not all programs use file coordination. Your NSFileProvider may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/
- (void)presentedSubitemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;

/* Be notified that the contents or attributes of a file or directory contained by the directory have been been written to. Depending on the situation the advice given for -presentedItemDidChange may apply here too. If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.

Not all programs use file coordination. Your NSFileProvider may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/
- (void)presentedSubitemDidChangeAtURL:(NSURL *)url;

/* Be notified that the something in the system has added, removed, or resolved a version of a file or directory contained by the directory.
*/
- (void)presentedSubitemAtURL:(NSURL *)url didGainVersion:(NSFileVersion *)version;
- (void)presentedSubitemAtURL:(NSURL *)url didLoseVersion:(NSFileVersion *)version;
- (void)presentedSubitemAtURL:(NSURL *)url didResolveConflictVersion:(NSFileVersion *)version;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSTimer.h
/*	NSTimer.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSTimer : NSObject

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti invocation:(NSInvocation *)invocation repeats:(BOOL)yesOrNo;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti invocation:(NSInvocation *)invocation repeats:(BOOL)yesOrNo;

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti target:(id)aTarget selector:(SEL)aSelector userInfo:(nullable id)userInfo repeats:(BOOL)yesOrNo;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti target:(id)aTarget selector:(SEL)aSelector userInfo:(nullable id)userInfo repeats:(BOOL)yesOrNo;

- (instancetype)initWithFireDate:(NSDate *)date interval:(NSTimeInterval)ti target:(id)t selector:(SEL)s userInfo:(nullable id)ui repeats:(BOOL)rep NS_DESIGNATED_INITIALIZER;

- (void)fire;

@property (copy) NSDate *fireDate;
@property (readonly) NSTimeInterval timeInterval;

// Setting a tolerance for a timer allows it to fire later than the scheduled fire date, improving the ability of the system to optimize for increased power savings and responsiveness. The timer may fire at any time between its scheduled fire date and the scheduled fire date plus the tolerance. The timer will not fire before the scheduled fire date. For repeating timers, the next fire date is calculated from the original fire date regardless of tolerance applied at individual fire times, to avoid drift. The default value is zero, which means no additional tolerance is applied. The system reserves the right to apply a small amount of tolerance to certain timers regardless of the value of this property.
// As the user of the timer, you will have the best idea of what an appropriate tolerance for a timer may be. A general rule of thumb, though, is to set the tolerance to at least 10% of the interval, for a repeating timer. Even a small amount of tolerance will have a significant positive impact on the power usage of your application. The system may put a maximum value of the tolerance.
@property NSTimeInterval tolerance NS_AVAILABLE(10_9, 7_0);

- (void)invalidate;
@property (readonly, getter=isValid) BOOL valid;

@property (nullable, readonly, retain) id userInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLCache.h
/*	
    NSURLCache.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @enum NSURLCacheStoragePolicy
    
    @discussion The NSURLCacheStoragePolicy enum defines constants that
    can be used to specify the type of storage that is allowable for an
    NSCachedURLResponse object that is to be stored in an NSURLCache.
    
    @constant NSURLCacheStorageAllowed Specifies that storage in an
    NSURLCache is allowed without restriction.

    @constant NSURLCacheStorageAllowedInMemoryOnly Specifies that
    storage in an NSURLCache is allowed; however storage should be
    done in memory only, no disk storage should be done.

    @constant NSURLCacheStorageNotAllowed Specifies that storage in an
    NSURLCache is not allowed in any fashion, either in memory or on
    disk.
*/
typedef NS_ENUM(NSUInteger, NSURLCacheStoragePolicy)
{
    NSURLCacheStorageAllowed,
    NSURLCacheStorageAllowedInMemoryOnly,
    NSURLCacheStorageNotAllowed,
};


@class NSCachedURLResponseInternal;
@class NSData;
@class NSDictionary;
@class NSURLRequest;
@class NSURLResponse;
@class NSDate;
@class NSURLSessionDataTask;

/*!
    @class NSCachedURLResponse
    NSCachedURLResponse is a class whose objects functions as a wrapper for
    objects that are stored in the framework's caching system. 
    It is used to maintain characteristics and attributes of a cached 
    object. 
*/
@interface NSCachedURLResponse : NSObject <NSSecureCoding, NSCopying>
{
    @private
    NSCachedURLResponseInternal *_internal;
}

/*! 
    @method initWithResponse:data
    @abstract Initializes an NSCachedURLResponse with the given
    response and data.
    @discussion A default NSURLCacheStoragePolicy is used for
    NSCachedURLResponse objects initialized with this method:
    NSURLCacheStorageAllowed.
    @param response a NSURLResponse object.
    @param data an NSData object representing the URL content
    corresponding to the given response.
    @result an initialized NSCachedURLResponse.
*/
- (instancetype)initWithResponse:(NSURLResponse *)response data:(NSData *)data;

/*! 
    @method initWithResponse:data:userInfo:storagePolicy:
    @abstract Initializes an NSCachedURLResponse with the given
    response, data, user-info dictionary, and storage policy.
    @param response a NSURLResponse object.
    @param data an NSData object representing the URL content
    corresponding to the given response.
    @param userInfo a dictionary user-specified information to be
    stored with the NSCachedURLResponse.
    @param storagePolicy an NSURLCacheStoragePolicy constant.
    @result an initialized NSCachedURLResponse.
*/
- (instancetype)initWithResponse:(NSURLResponse *)response data:(NSData *)data userInfo:(nullable NSDictionary *)userInfo storagePolicy:(NSURLCacheStoragePolicy)storagePolicy;

/*! 
    @method response
    @abstract Returns the response wrapped by this instance. 
    @result The response wrapped by this instance. 
*/
@property (readonly, copy) NSURLResponse *response;

/*! 
    @method data
    @abstract Returns the data of the receiver. 
    @result The data of the receiver. 
*/
@property (readonly, copy) NSData *data;

/*! 
    @method userInfo
    @abstract Returns the userInfo dictionary of the receiver. 
    @result The userInfo dictionary of the receiver. 
*/
@property (nullable, readonly, copy) NSDictionary *userInfo;

/*! 
    @method storagePolicy
    @abstract Returns the NSURLCacheStoragePolicy constant of the receiver. 
    @result The NSURLCacheStoragePolicy constant of the receiver. 
*/
@property (readonly) NSURLCacheStoragePolicy storagePolicy;

@end


@class NSURLRequest;
@class NSURLCacheInternal;

@interface NSURLCache : NSObject
{
    @private
    NSURLCacheInternal *_internal;
}

/*! 
    @method sharedURLCache
    @abstract Returns the shared NSURLCache instance.
    @discussion Unless set explicitly through a call to
    <tt>+setSharedURLCache:</tt>, this method returns an NSURLCache
    instance created with the following default values:
    <ul>
    <li>Memory capacity: 4 megabytes (4 * 1024 * 1024 bytes)
    <li>Disk capacity: 20 megabytes (20 * 1024 * 1024 bytes)
    <li>Disk path: <nobr>(user home directory)/Library/Caches/(application bundle id)</nobr> 
    </ul>
    <p>Users who do not have special caching requirements or
    constraints should find the default shared cache instance
    acceptable. If this default shared cache instance is not
    acceptable, <tt>+setSharedURLCache:</tt> can be called to set a
    different NSURLCache instance to be returned from this method.
    @result the shared NSURLCache instance.
*/
+ (NSURLCache *)sharedURLCache;

/*! 
    @method setSharedURLCache:
    @abstract Sets the NSURLCache instance shared by all clients of
    the current process. This will be the new object returned when
    calls to the <tt>sharedURLCache</tt> method are made.
    @discussion Callers should take care to ensure that this method is called
    at a time when no other caller has a reference to the previously-set shared
    URL cache. This is to prevent storing cache data from becoming 
    unexpectedly unretrievable.
    @param cache the new shared NSURLCache instance.
*/
+ (void)setSharedURLCache:(NSURLCache *)cache;

/*! 
    @method initWithMemoryCapacity:diskCapacity:diskPath:
    @abstract Initializes an NSURLCache with the given capacity and
    path.
    @discussion The returned NSURLCache is backed by disk, so
    developers can be more liberal with space when choosing the
    capacity for this kind of cache. A disk cache measured in the tens
    of megabytes should be acceptable in most cases.
    @param capacity the capacity, measured in bytes, for the cache.
    @param path the path on disk where the cache data is stored.
    @result an initialized NSURLCache, with the given capacity, backed
    by disk.
*/
- (instancetype)initWithMemoryCapacity:(NSUInteger)memoryCapacity diskCapacity:(NSUInteger)diskCapacity diskPath:(nullable NSString *)path;

/*! 
    @method cachedResponseForRequest:
    @abstract Returns the NSCachedURLResponse stored in the cache with
    the given request.
    @discussion The method returns nil if there is no
    NSCachedURLResponse stored using the given request.
    @param request the NSURLRequest to use as a key for the lookup.
    @result The NSCachedURLResponse stored in the cache with the given
    request, or nil if there is no NSCachedURLResponse stored with the
    given request.
*/
- (nullable NSCachedURLResponse *)cachedResponseForRequest:(NSURLRequest *)request;

/*! 
    @method storeCachedResponse:forRequest:
    @abstract Stores the given NSCachedURLResponse in the cache using
    the given request.
    @param cachedResponse The cached response to store.
    @param request the NSURLRequest to use as a key for the storage.
*/
- (void)storeCachedResponse:(NSCachedURLResponse *)cachedResponse forRequest:(NSURLRequest *)request;

/*! 
    @method removeCachedResponseForRequest:
    @abstract Removes the NSCachedURLResponse from the cache that is
    stored using the given request. 
    @discussion No action is taken if there is no NSCachedURLResponse
    stored with the given request.
    @param request the NSURLRequest to use as a key for the lookup.
*/
- (void)removeCachedResponseForRequest:(NSURLRequest *)request;

/*! 
    @method removeAllCachedResponses
    @abstract Clears the given cache, removing all NSCachedURLResponse
    objects that it stores.
*/
- (void)removeAllCachedResponses;

/*!
 @method removeCachedResponsesSince:
 @abstract Clears the given cache of any cached responses since the provided date.
 */
- (void)removeCachedResponsesSinceDate:(NSDate *)date NS_AVAILABLE(10_10, 8_0);

/*! 
    @method memoryCapacity
    @abstract In-memory capacity of the receiver. 
    @discussion At the time this call is made, the in-memory cache will truncate its contents to the size given, if necessary.
    @result The in-memory capacity, measured in bytes, for the receiver. 
*/
@property NSUInteger memoryCapacity;

/*! 
    @method diskCapacity
    @abstract The on-disk capacity of the receiver. 
    @discussion At the time this call is made, the on-disk cache will truncate its contents to the size given, if necessary.
    @param diskCapacity the new on-disk capacity, measured in bytes, for the receiver.
*/
@property NSUInteger diskCapacity;

/*! 
    @method currentMemoryUsage
    @abstract Returns the current amount of space consumed by the
    in-memory cache of the receiver.
    @discussion This size, measured in bytes, indicates the current
    usage of the in-memory cache. 
    @result the current usage of the in-memory cache of the receiver.
*/
@property (readonly) NSUInteger currentMemoryUsage;

/*! 
    @method currentDiskUsage
    @abstract Returns the current amount of space consumed by the
    on-disk cache of the receiver.
    @discussion This size, measured in bytes, indicates the current
    usage of the on-disk cache. 
    @result the current usage of the on-disk cache of the receiver.
*/
@property (readonly) NSUInteger currentDiskUsage;

@end

@interface NSURLCache (NSURLSessionTaskAdditions)
- (void)storeCachedResponse:(NSCachedURLResponse *)cachedResponse forDataTask:(NSURLSessionDataTask *)dataTask NS_AVAILABLE(10_10, 8_0);
- (void)getCachedResponseForDataTask:(NSURLSessionDataTask *)dataTask completionHandler:(void (^) (NSCachedURLResponse * __nullable cachedResponse))completionHandler NS_AVAILABLE(10_10, 8_0);
- (void)removeCachedResponseForDataTask:(NSURLSessionDataTask *)dataTask NS_AVAILABLE(10_10, 8_0);
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLResponse.h
/*	
    NSURLResponse.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Foundation/NSObject.h>

@class NSDictionary<KeyType, ObjectType>;
@class NSString;
@class NSURL;
@class NSURLRequest;
@class NSURLResponseInternal;

NS_ASSUME_NONNULL_BEGIN

#define NSURLResponseUnknownLength ((long long)-1)

/*!
    @class NSURLResponse

    @abstract An NSURLResponse object represents a URL load response in a
    manner independent of protocol and URL scheme.

    @discussion NSURLResponse encapsulates the metadata associated
    with a URL load. Note that NSURLResponse objects do not contain
    the actual bytes representing the content of a URL. See
    NSURLConnection and NSURLConnectionDelegate for more information
    about receiving the content data for a URL load.
*/
@interface NSURLResponse : NSObject <NSSecureCoding, NSCopying>
{
    @package
    NSURLResponseInternal *_internal;
}

/*!
    @method initWithURL:MIMEType:expectedContentLength:textEncodingName:
    @abstract Initialize an NSURLResponse with the provided values.
    @param URL the URL
    @param MIMETYPE the MIME content type of the response
    @param expectedContentLength the expected content length of the associated data
    @param textEncodingName the name of the text encoding for the associated data, if applicable, else nil
    @result The initialized NSURLResponse.
    @discussion This is the designated initializer for NSURLResponse.
*/
- (instancetype)initWithURL:(NSURL *)URL MIMEType:(nullable NSString *)MIMEType expectedContentLength:(NSInteger)length textEncodingName:(nullable NSString *)name NS_DESIGNATED_INITIALIZER;

/*! 
    @method URL
    @abstract Returns the URL of the receiver. 
    @result The URL of the receiver. 
*/
@property (nullable, readonly, copy) NSURL *URL;

/*! 
    @method MIMEType
    @abstract Returns the MIME type of the receiver. 
    @discussion The MIME type is based on the information provided
    from an origin source. However, that value may be changed or
    corrected by a protocol implementation if it can be determined
    that the origin server or source reported the information
    incorrectly or imprecisely. An attempt to guess the MIME type may
    be made if the origin source did not report any such information.
    @result The MIME type of the receiver.
*/
@property (nullable, readonly, copy) NSString *MIMEType;

/*! 
    @method expectedContentLength
    @abstract Returns the expected content length of the receiver.
    @discussion Some protocol implementations report a content length
    as part of delivering load metadata, but not all protocols
    guarantee the amount of data that will be delivered in actuality.
    Hence, this method returns an expected amount. Clients should use
    this value as an advisory, and should be prepared to deal with
    either more or less data.
    @result The expected content length of the receiver, or -1 if
    there is no expectation that can be arrived at regarding expected
    content length.
*/
@property (readonly) long long expectedContentLength;

/*! 
    @method textEncodingName
    @abstract Returns the name of the text encoding of the receiver.
    @discussion This name will be the actual string reported by the
    origin source during the course of performing a protocol-specific
    URL load. Clients can inspect this string and convert it to an
    NSStringEncoding or CFStringEncoding using the methods and
    functions made available in the appropriate framework.
    @result The name of the text encoding of the receiver, or nil if no
    text encoding was specified. 
*/
@property (nullable, readonly, copy) NSString *textEncodingName;

/*!
    @method suggestedFilename
    @abstract Returns a suggested filename if the resource were saved to disk.
    @discussion The method first checks if the server has specified a filename using the
    content disposition header. If no valid filename is specified using that mechanism,
    this method checks the last path component of the URL. If no valid filename can be
    obtained using the last path component, this method uses the URL's host as the filename.
    If the URL's host can't be converted to a valid filename, the filename "unknown" is used.
    In mose cases, this method appends the proper file extension based on the MIME type.
    This method always returns a valid filename.
    @result A suggested filename to use if saving the resource to disk.
*/
@property (nullable, readonly, copy) NSString *suggestedFilename;

@end



@class NSHTTPURLResponseInternal;

/*!
    @class NSHTTPURLResponse

    @abstract An NSHTTPURLResponse object represents a response to an
    HTTP URL load. It is a specialization of NSURLResponse which
    provides conveniences for accessing information specific to HTTP
    protocol responses.
*/
@interface NSHTTPURLResponse : NSURLResponse 
{
    @package
    NSHTTPURLResponseInternal *_httpInternal;
}

/*!
  @method	initWithURL:statusCode:HTTPVersion:headerFields:
  @abstract initializer for NSHTTPURLResponse objects.
  @param 	url the URL from which the response was generated.
  @param	statusCode an HTTP status code.
  @param	HTTPVersion The version of the HTTP response as represented by the server.  This is typically represented as "HTTP/1.1".
  @param 	headerFields A dictionary representing the header keys and values of the server response.
  @result 	the instance of the object, or NULL if an error occurred during initialization.
  @discussion This API was introduced in Mac OS X 10.7.2 and iOS 5.0 and is not available prior to those releases.
*/
- (nullable instancetype)initWithURL:(NSURL *)url statusCode:(NSInteger)statusCode HTTPVersion:(nullable NSString *)HTTPVersion headerFields:(nullable NSDictionary<NSString *, NSString *> *)headerFields NS_AVAILABLE(10_7, 5_0);

/*! 
    @method statusCode
    @abstract Returns the HTTP status code of the receiver. 
    @result The HTTP status code of the receiver. 
*/
@property (readonly) NSInteger statusCode;

/*! 
    @method allHeaderFields
    @abstract Returns a dictionary containing all the HTTP header fields
    of the receiver.
    @discussion By examining this header dictionary, clients can see
    the "raw" header information which was reported to the protocol
    implementation by the HTTP server. This may be of use to
    sophisticated or special-purpose HTTP clients.
    @result A dictionary containing all the HTTP header fields of the
    receiver.
*/
@property (readonly, copy) NSDictionary *allHeaderFields;

/*! 
    @method localizedStringForStatusCode:
    @abstract Convenience method which returns a localized string
    corresponding to the status code for this response.
    @param the status code to use to produce a localized string.
    @result A localized string corresponding to the given status code.
*/
+ (NSString *)localizedStringForStatusCode:(NSInteger)statusCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDateComponentsFormatter.h
/*	NSDateComponentsFormatter.h
	Copyright (c) 2014-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#import <Foundation/NSCalendar.h>
#import <Foundation/NSNumberFormatter.h>

NS_ASSUME_NONNULL_BEGIN

NS_ENUM_AVAILABLE(10_10, 8_0)
typedef NS_ENUM(NSInteger, NSDateComponentsFormatterUnitsStyle) {
    NSDateComponentsFormatterUnitsStylePositional = 0, // "1:10; may fall back to abbreviated units in some cases, e.g. 3d"
    NSDateComponentsFormatterUnitsStyleAbbreviated, // "1h 10m"
    NSDateComponentsFormatterUnitsStyleShort, // "1hr 10min"
    NSDateComponentsFormatterUnitsStyleFull, // "1 hour, 10 minutes"
    NSDateComponentsFormatterUnitsStyleSpellOut // "One hour, ten minutes"
};

NS_ENUM_AVAILABLE(10_10, 8_0)
typedef NS_OPTIONS(NSUInteger, NSDateComponentsFormatterZeroFormattingBehavior) {
    NSDateComponentsFormatterZeroFormattingBehaviorNone = (0), //drop none, pad none
    NSDateComponentsFormatterZeroFormattingBehaviorDefault = (1 << 0), //Positional units: drop leading zeros, pad other zeros. All others: drop all zeros.

    NSDateComponentsFormatterZeroFormattingBehaviorDropLeading = (1 << 1), // Off: "0h 10m", On: "10m"
    NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle = (1 << 2), // Off: "1h 0m 10s", On: "1h 10s"
    NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing = (1 << 3), // Off: "1h 0m", On: "1h"
    NSDateComponentsFormatterZeroFormattingBehaviorDropAll = (NSDateComponentsFormatterZeroFormattingBehaviorDropLeading | NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle | NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing),

    NSDateComponentsFormatterZeroFormattingBehaviorPad = (1 << 16), // Off: "1:0:10", On: "01:00:10" 
};

/* NSDateComponentsFormatter provides locale-correct and flexible string formatting of quantities of time, such as "1 day" or "1h 10m", as specified by NSDateComponents. For formatting intervals of time (such as "2PM to 5PM"), see NSDateIntervalFormatter. NSDateComponentsFormatter is thread-safe, in that calling methods on it from multiple threads will not cause crashes or incorrect results, but it makes no attempt to prevent confusion when one thread sets something and another thread isn't expecting it to change.
 */
NS_AVAILABLE(10_10, 8_0)
@interface NSDateComponentsFormatter : NSFormatter {
    @private
    pthread_mutex_t _lock;
    void *_fmt;
    void *_unused;
    NSString *_fmtLocaleIdent;
    NSCalendar *_calendar;
    NSDate *_referenceDate;
    NSNumberFormatter *_unitFormatter;
    NSCalendarUnit _allowedUnits;
    NSFormattingContext _formattingContext;
    NSDateComponentsFormatterUnitsStyle _unitsStyle;
    NSDateComponentsFormatterZeroFormattingBehavior _zeroFormattingBehavior;
    NSInteger _maximumUnitCount;
    BOOL _allowsFractionalUnits;
    BOOL _collapsesLargestUnit;
    BOOL _includesApproximationPhrase;
    BOOL _includesTimeRemainingPhrase;
    void *_reserved;
}

/* 'obj' must be an instance of NSDateComponents.
 */
- (nullable NSString *)stringForObjectValue:(id)obj;

- (nullable NSString *)stringFromDateComponents:(NSDateComponents *)components;

/* Normally, NSDateComponentsFormatter will calculate as though counting from the current date and time (e.g. in February, 1 month formatted as a number of days will be 28). -stringFromDate:toDate: calculates from the passed-in startDate instead.
 
   See 'allowedUnits' for how the default set of allowed units differs from -stringFromDateComponents:.
 
   Note that this is still formatting the quantity of time between the dates, not the pair of dates itself. For strings like "Feb 22nd - Feb 28th", use NSDateIntervalFormatter.
 */
- (nullable NSString *)stringFromDate:(NSDate *)startDate toDate:(NSDate *)endDate;

/* Convenience method for formatting a number of seconds. See 'allowedUnits' for how the default set of allowed units differs from -stringFromDateComponents:.
 */
- (nullable NSString *)stringFromTimeInterval:(NSTimeInterval)ti;


+ (nullable NSString *)localizedStringFromDateComponents:(NSDateComponents *)components unitsStyle:(NSDateComponentsFormatterUnitsStyle) unitsStyle;

/* Choose how to indicate units. For example, 1h 10m vs 1:10. Default is NSDateComponentsFormatterUnitsStylePositional.
 */
@property NSDateComponentsFormatterUnitsStyle unitsStyle;

/* Bitmask of units to include. Set to 0 to get the default behavior. Note that, especially if the maximum number of units is low, unit collapsing is on, or zero dropping is on, not all allowed units may actually be used for a given NSDateComponents. Default value is the components of the passed-in NSDateComponents object, or years | months | weeks | days | hours | minutes | seconds if passed an NSTimeInterval or pair of NSDates.
 
   Allowed units are:
 
    NSCalendarUnitYear
    NSCalendarUnitMonth
    NSCalendarUnitWeekOfMonth (used to mean "quantity of weeks")
    NSCalendarUnitDay
    NSCalendarUnitHour
    NSCalendarUnitMinute
    NSCalendarUnitSecond
 
   Specifying any other NSCalendarUnits will result in an exception.
 */
@property NSCalendarUnit allowedUnits;

/* Bitmask specifying how to handle zeros in units. This includes both padding and dropping zeros so that a consistent number digits are displayed, causing updating displays to remain more stable. Default is NSDateComponentsFormatterZeroFormattingBehaviorDefault.
 
   If the combination of zero formatting behavior and style would lead to ambiguous date formats (for example, 1:10 meaning 1 hour, 10 seconds), NSDateComponentsFormatter will throw an exception.
 */
@property NSDateComponentsFormatterZeroFormattingBehavior zeroFormattingBehavior;

/* Specifies the locale and calendar to use for formatting date components that do not themselves have calendars. Defaults to NSAutoupdatingCurrentCalendar. If set to nil, uses the gregorian calendar with the en_US_POSIX locale.
 */
@property (nullable, copy) NSCalendar *calendar;

/* Choose whether non-integer units should be used to handle display of values that can't be exactly represented with the allowed units. For example, if minutes aren't allowed, then "1h 30m" could be formatted as "1.5h". Default is NO.
 */
@property BOOL allowsFractionalUnits;

/* Choose whether or not, and at which point, to round small units in large values to zero.
   Examples:
    1h 10m 30s, maximumUnitCount set to 0: "1h 10m 30s"
    1h 10m 30s, maximumUnitCount set to 2: "1h 10m"
    10m 30s, maximumUnitCount set to 0: "10m 30s"
    10m 30s, maximumUnitCount set to 2: "10m 30s"

   Default is 0, which is interpreted as unlimited.
 */
@property NSInteger maximumUnitCount;

/* Choose whether to express largest units just above the threshold for the next lowest unit as a larger quantity of the lower unit. For example: "1m 3s" vs "63s". Default is NO.
 */
@property BOOL collapsesLargestUnit;

/* Choose whether to indicate that the allowed units/insignificant units choices lead to inexact results. In some languages, simply prepending "about " to the string will produce incorrect results; this handles those cases correctly. Default is NO.
 */
@property BOOL includesApproximationPhrase;

/* Choose whether to produce strings like "35 minutes remaining". Default is NO.
 */
@property BOOL includesTimeRemainingPhrase;

/* 
   Currently unimplemented, will be removed in a future seed.
 */
@property NSFormattingContext formattingContext;

/* NSDateComponentsFormatter currently only implements formatting, not parsing. Until it implements parsing, this will always return NO.
 */
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSCharacterSet.h
/*	NSCharacterSet.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <CoreFoundation/CFCharacterSet.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSString.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

enum {
    NSOpenStepUnicodeReservedBase = 0xF400
};

@interface NSCharacterSet : NSObject <NSCopying, NSMutableCopying, NSCoding>

+ (NSCharacterSet *)controlCharacterSet;
+ (NSCharacterSet *)whitespaceCharacterSet;
+ (NSCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSCharacterSet *)decimalDigitCharacterSet;
+ (NSCharacterSet *)letterCharacterSet;
+ (NSCharacterSet *)lowercaseLetterCharacterSet;
+ (NSCharacterSet *)uppercaseLetterCharacterSet;
+ (NSCharacterSet *)nonBaseCharacterSet;
+ (NSCharacterSet *)alphanumericCharacterSet;
+ (NSCharacterSet *)decomposableCharacterSet;
+ (NSCharacterSet *)illegalCharacterSet;
+ (NSCharacterSet *)punctuationCharacterSet;
+ (NSCharacterSet *)capitalizedLetterCharacterSet;
+ (NSCharacterSet *)symbolCharacterSet;
+ (NSCharacterSet *)newlineCharacterSet NS_AVAILABLE(10_5, 2_0);

+ (NSCharacterSet *)characterSetWithRange:(NSRange)aRange;
+ (NSCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
+ (NSCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;
+ (nullable NSCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

- (instancetype) initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (BOOL)characterIsMember:(unichar)aCharacter;
@property (readonly, copy) NSData *bitmapRepresentation;
@property (readonly, copy) NSCharacterSet *invertedSet;


- (BOOL)longCharacterIsMember:(UTF32Char)theLongChar;

- (BOOL)isSupersetOfSet:(NSCharacterSet *)theOtherSet;
- (BOOL)hasMemberInPlane:(uint8_t)thePlane;
@end

@interface NSMutableCharacterSet : NSCharacterSet <NSCopying, NSMutableCopying>

- (void)addCharactersInRange:(NSRange)aRange;
- (void)removeCharactersInRange:(NSRange)aRange;
- (void)addCharactersInString:(NSString *)aString;
- (void)removeCharactersInString:(NSString *)aString;
- (void)formUnionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)formIntersectionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)invert;

+ (NSMutableCharacterSet *)controlCharacterSet;
+ (NSMutableCharacterSet *)whitespaceCharacterSet;
+ (NSMutableCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSMutableCharacterSet *)decimalDigitCharacterSet;
+ (NSMutableCharacterSet *)letterCharacterSet;
+ (NSMutableCharacterSet *)lowercaseLetterCharacterSet;
+ (NSMutableCharacterSet *)uppercaseLetterCharacterSet;
+ (NSMutableCharacterSet *)nonBaseCharacterSet;
+ (NSMutableCharacterSet *)alphanumericCharacterSet;
+ (NSMutableCharacterSet *)decomposableCharacterSet;
+ (NSMutableCharacterSet *)illegalCharacterSet;
+ (NSMutableCharacterSet *)punctuationCharacterSet;
+ (NSMutableCharacterSet *)capitalizedLetterCharacterSet;
+ (NSMutableCharacterSet *)symbolCharacterSet;
+ (NSMutableCharacterSet *)newlineCharacterSet NS_AVAILABLE(10_5, 2_0);

+ (NSMutableCharacterSet *)characterSetWithRange:(NSRange)aRange;
+ (NSMutableCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
+ (NSMutableCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;
+ (nullable NSMutableCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDateFormatter.h
/*	NSDateFormatter.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray<ObjectType>, NSMutableDictionary, NSString;

NS_ASSUME_NONNULL_BEGIN

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif


@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    __strong CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromDate:(NSDate *)date;
- (nullable NSDate *)dateFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSDateFormatterStyle) {    // date and time format styles
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};

typedef NS_ENUM(NSUInteger, NSDateFormatterBehavior) {
    NSDateFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSDateFormatterBehavior10_0 = 1000,
#endif
    NSDateFormatterBehavior10_4 = 1040,
};


+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle NS_AVAILABLE(10_6, 4_0);

+ (nullable NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(nullable NSLocale *)locale NS_AVAILABLE(10_6, 4_0);
	// no options defined, pass 0 for now

// Attributes of an NSDateFormatter

+ (NSDateFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior;

/*
 A convenient way to generate an appropriate localized date format, and set it, in a single operation.

 Equivalent to, though not necessarily implemented as:
 formatter.dateFormat = [NSDateFormatter dateFormatFromTemplate:dateFormatTemplate options:0 locale:formatter.locale];

 Note that the template string is used only to specify which date format components should be included. Ordering and other text will not be preserved.
 The parameter is also not stored, or updated when the locale or other options change, just as with the ‘dateFormat’ property.
 */
- (void) setLocalizedDateFormatFromTemplate:(NSString *)dateFormatTemplate NS_AVAILABLE(10_10, 8_0);

@property (null_resettable, copy) NSString *dateFormat;
@property NSDateFormatterStyle dateStyle;
@property NSDateFormatterStyle timeStyle;
@property (null_resettable, copy) NSLocale *locale;
@property BOOL generatesCalendarDates;
@property NSDateFormatterBehavior formatterBehavior;
@property (null_resettable, copy) NSTimeZone *timeZone;
@property (null_resettable, copy) NSCalendar *calendar;
@property (getter=isLenient) BOOL lenient;
@property (nullable, copy) NSDate *twoDigitStartDate;
@property (nullable, copy) NSDate *defaultDate;
@property (null_resettable, copy) NSArray<NSString *> *eraSymbols;
@property (null_resettable, copy) NSArray<NSString *> *monthSymbols;
@property (null_resettable, copy) NSArray<NSString *> *shortMonthSymbols;
@property (null_resettable, copy) NSArray<NSString *> *weekdaySymbols;
@property (null_resettable, copy) NSArray<NSString *> *shortWeekdaySymbols;
@property (null_resettable, copy) NSString *AMSymbol;
@property (null_resettable, copy) NSString *PMSymbol;
@property (null_resettable, copy) NSArray<NSString *> *longEraSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *quarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (nullable, copy) NSDate *gregorianStartDate NS_AVAILABLE(10_5, 2_0);
@property BOOL doesRelativeDateFormatting NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");
- (BOOL)allowsNaturalLanguage NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "There is no replacement");

@end
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSTextCheckingResult.h
/*	NSTextCheckingResult.h
	Copyright (c) 2008-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSTimeZone, NSOrthography, NSURL, NSRegularExpression;

NS_ASSUME_NONNULL_BEGIN

/* NSTextCheckingResult is a class used to describe items located by text checking.  Each of these objects represents something that has been found during checking--a misspelled word, a sentence with grammatical issues, a detected URL, a straight quote to be replaced with curly quotes, and so forth. */

typedef NS_OPTIONS(uint64_t, NSTextCheckingType) {    // a single type
    NSTextCheckingTypeOrthography           = 1ULL << 0,            // language identification
    NSTextCheckingTypeSpelling              = 1ULL << 1,            // spell checking
    NSTextCheckingTypeGrammar               = 1ULL << 2,            // grammar checking
    NSTextCheckingTypeDate                  = 1ULL << 3,            // date/time detection
    NSTextCheckingTypeAddress               = 1ULL << 4,            // address detection
    NSTextCheckingTypeLink                  = 1ULL << 5,            // link detection
    NSTextCheckingTypeQuote                 = 1ULL << 6,            // smart quotes
    NSTextCheckingTypeDash                  = 1ULL << 7,            // smart dashes
    NSTextCheckingTypeReplacement           = 1ULL << 8,            // fixed replacements, such as copyright symbol for (c)
    NSTextCheckingTypeCorrection            = 1ULL << 9,            // autocorrection
    NSTextCheckingTypeRegularExpression NS_ENUM_AVAILABLE(10_7, 4_0)  = 1ULL << 10,           // regular expression matches
    NSTextCheckingTypePhoneNumber NS_ENUM_AVAILABLE(10_7, 4_0)        = 1ULL << 11,           // phone number detection
    NSTextCheckingTypeTransitInformation NS_ENUM_AVAILABLE(10_7, 4_0) = 1ULL << 12            // transit (e.g. flight) info detection
};

typedef uint64_t NSTextCheckingTypes;   // a combination of types
NS_ENUM(NSTextCheckingTypes) {
    NSTextCheckingAllSystemTypes    = 0xffffffffULL,        // the first 32 types are reserved
    NSTextCheckingAllCustomTypes    = 0xffffffffULL << 32,  // clients may use the remainder for their own purposes
    NSTextCheckingAllTypes          = (NSTextCheckingAllSystemTypes | NSTextCheckingAllCustomTypes)
};

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSTextCheckingResult : NSObject <NSCopying, NSCoding>

/* Mandatory properties, used with all types of results. */
@property (readonly) NSTextCheckingType resultType;
@property (readonly) NSRange range;

@end

@interface NSTextCheckingResult (NSTextCheckingResultOptional)

/* Optional properties, used with certain types of results. */
@property (nullable, readonly, copy) NSOrthography *orthography;
@property (nullable, readonly, copy) NSArray<NSString *> *grammarDetails;
@property (nullable, readonly, copy) NSDate *date;
@property (nullable, readonly, copy) NSTimeZone *timeZone;
@property (readonly) NSTimeInterval duration;
@property (nullable, readonly, copy) NSDictionary<NSString *, NSString *> *components NS_AVAILABLE(10_7, 4_0);
@property (nullable, readonly, copy) NSURL *URL;
@property (nullable, readonly, copy) NSString *replacementString;
@property (nullable, readonly, copy) NSArray<NSString *> *alternativeStrings NS_AVAILABLE(10_9, 7_0);
@property (nullable, readonly, copy) NSRegularExpression *regularExpression NS_AVAILABLE(10_7, 4_0);
@property (nullable, readonly, copy) NSString *phoneNumber NS_AVAILABLE(10_7, 4_0);

@property (nullable, readonly, copy) NSDictionary<NSString *, NSString *> *addressComponents;

/* A result must have at least one range, but may optionally have more (for example, to represent regular expression capture groups).  The range at index 0 always matches the range property.  Additional ranges, if any, will have indexes from 1 to numberOfRanges-1. */
@property (readonly) NSUInteger numberOfRanges NS_AVAILABLE(10_7, 4_0);
- (NSRange)rangeAtIndex:(NSUInteger)idx NS_AVAILABLE(10_7, 4_0);
- (NSTextCheckingResult *)resultByAdjustingRangesWithOffset:(NSInteger)offset NS_AVAILABLE(10_7, 5_0);

@end



/* Keys for address components. */
FOUNDATION_EXPORT NSString * const NSTextCheckingNameKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingJobTitleKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingOrganizationKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingStreetKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingCityKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingStateKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingZIPKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingCountryKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingPhoneKey NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingAirlineKey NS_AVAILABLE(10_7, 4_0);
FOUNDATION_EXPORT NSString * const NSTextCheckingFlightKey NS_AVAILABLE(10_7, 4_0);


@interface NSTextCheckingResult (NSTextCheckingResultCreation)

/* Methods for creating instances of the various types of results. */
+ (NSTextCheckingResult *)orthographyCheckingResultWithRange:(NSRange)range orthography:(NSOrthography *)orthography;
+ (NSTextCheckingResult *)spellCheckingResultWithRange:(NSRange)range;
+ (NSTextCheckingResult *)grammarCheckingResultWithRange:(NSRange)range details:(NSArray<NSString *> *)details;
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date;
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date timeZone:(NSTimeZone *)timeZone duration:(NSTimeInterval)duration;
+ (NSTextCheckingResult *)addressCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSString *, NSString *> *)components;
+ (NSTextCheckingResult *)linkCheckingResultWithRange:(NSRange)range URL:(NSURL *)url;
+ (NSTextCheckingResult *)quoteCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)dashCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)replacementCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString alternativeStrings:(NSArray<NSString *> *)alternativeStrings     NS_AVAILABLE(10_9, 7_0);
+ (NSTextCheckingResult *)regularExpressionCheckingResultWithRanges:(NSRangePointer)ranges count:(NSUInteger)count regularExpression:(NSRegularExpression *)regularExpression   NS_AVAILABLE(10_7, 4_0);
+ (NSTextCheckingResult *)phoneNumberCheckingResultWithRange:(NSRange)range phoneNumber:(NSString *)phoneNumber             NS_AVAILABLE(10_7, 4_0);
+ (NSTextCheckingResult *)transitInformationCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSString *, NSString *> *)components    NS_AVAILABLE(10_7, 4_0);

@end

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSURLConnection.h
/*    
    NSURLConnection.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSArray;
@class NSURL;
@class NSCachedURLResponse;
@class NSData;
@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLConnectionInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSRunLoop;
@class NSInputStream;
@class NSURLProtectionSpace;
@class NSOperationQueue;

@protocol NSURLConnectionDelegate;

NS_ASSUME_NONNULL_BEGIN

/*** DEPRECATED: The NSURLConnection class should no longer be used.  NSURLSession is the replacement for NSURLConnection ***/

/*!
    @class NSURLConnection
    
    @abstract 
        
        An NSURLConnection object provides support to perform
        asynchronous loads of a URL request, providing data to a
        client supplied delegate.
    
    @discussion

        The interface for NSURLConnection is very sparse, providing
        only the controls to start and cancel asynchronous loads of a
        URL request.<p>

        An NSURLConnection may be used for loading of resource data
        directly to memory, in which case an
        NSURLConnectionDataDelegate should be supplied, or for
        downloading of resource data directly to a file, in which case
        an NSURLConnectionDownloadDelegate is used.  The delegate is
        retained by the NSURLConnection until a terminal condition is
        encountered.  These two delegates are logically subclasses of
        the base protocol, NSURLConnectionDelegate.<p>

        A terminal condition produced by the loader will result in a
        connection:didFailWithError: in the case of an error, or
        connectiondidFinishLoading: or connectionDidFinishDownloading:
        delegate message.<p>

        The -cancel message hints to the loader that a resource load
        should be abandoned but does not guarantee that more delegate
        messages will not be delivered.  If -cancel does cause the
        load to be abandoned, the delegate will be released without
        further messages.  In general, a caller should be prepared for
        -cancel to have no effect, and internally ignore any delegate
        callbacks until the delegate is released.

        Scheduling of an NSURLConnection specifies the context in
        which delegate callbacks will be made, but the actual IO may
        occur on a separate thread and should be considered an
        implementation detail.<p>

        When created, an NSURLConnection performs a deep-copy of the
        NSURLRequest.  This copy is available through the
        -originalRequest method.  As the connection performs the load,
        this request may change as a result of protocol
        canonicalization or due to following redirects.
        -currentRequest can be used to retrieve this value.<p>

        An NSURLConnections created with the
        +connectionWithRequest:delegate: or -initWithRequest:delegate:
        methods are scheduled on the current runloop immediately, and
        it is not necessary to send the -start message to begin the
        resource load.<p>

        NSURLConnections created with
        -initWithRequest:delegate:startImmediately: are not
        automatically scheduled.  Use -scheduleWithRunLoop:forMode: or
        -setDelegateQueue: to specify the context for delegate
        callbacks, and -start to begin the load.  If you do not
        explicitly schedule the connection before -start, it will be
        scheduled on the current runloop and mode automatically.<p>

        The NSURLConnectionSynchronousLoading category adds
        +sendSynchronousRequest:returningResponse:error, which blocks
        the current thread until the resource data is available or an
        error occurs.  It should be noted that using this method on an
        applications main run loop may result in an unacceptably long
        delay in a user interface and its use is strongly
        discourage.<p>

        The NSURLConnectionQueuedLoading category implements
        +sendAsynchronousRequest:queue:completionHandler, providing
        similar simplicity but provides a mechanism where the current
        runloop is not blocked.<p>

        Both of the immediate loading categories do not provide for
        customization of resource load, and do not allow the caller to
        respond to, e.g., authentication challenges.<p>
*/
@interface NSURLConnection : NSObject
{
    @private
    NSURLConnectionInternal *_internal;
}

/* Designated initializer */
- (nullable instancetype)initWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate startImmediately:(BOOL)startImmediately NS_DEPRECATED(10_5, 10_11, 2_0, 9_0, "Use NSURLSession (see NSURLSession.h)");

- (nullable instancetype)initWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate NS_DEPRECATED(10_3, 10_11, 2_0, 9_0, "Use NSURLSession (see NSURLSession.h)");
+ (nullable NSURLConnection*)connectionWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate NS_DEPRECATED(10_3, 10_11, 2_0, 9_0, "Use NSURLSession (see NSURLSession.h)");

@property (readonly, copy) NSURLRequest *originalRequest NS_AVAILABLE(10_8, 5_0);
@property (readonly, copy) NSURLRequest *currentRequest NS_AVAILABLE(10_8, 5_0);

- (void)start NS_AVAILABLE(10_5, 2_0);
- (void)cancel;

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode NS_AVAILABLE(10_5, 2_0);
- (void)unscheduleFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode NS_AVAILABLE(10_5, 2_0);
- (void)setDelegateQueue:(nullable NSOperationQueue*) queue NS_AVAILABLE(10_7, 5_0);


/*! 
    @method         canHandleRequest:

    @abstract
                    Performs a "preflight" operation that performs
                    some speculative checks to see if a connection can
                    be initialized, and the associated I/O that is
                    started in the initializer methods can begin.

    @discussion
                    The result of this method is valid only as long as
                    no protocols are registered or unregistered, and
                    as long as the request is not mutated (if the
                    request is mutable). Hence, clients should be
                    prepared to handle failures even if they have
                    performed request preflighting by calling this
                    method.

    @param 
        request     The request to preflight.

    @result

        YES         if it is likely that the given request can be used to
                    initialize a connection and the associated I/O can be
                    started

        NO            
*/
+ (BOOL)canHandleRequest:(NSURLRequest *)request;

@end

/*!
    @protocol       NSURLConnectionDelegate

    @abstract        
                    Delegate methods that are common to all forms of
                    NSURLConnection.  These are all optional.  This
                    protocol should be considered a base class for the
                    NSURLConnectionDataDelegate and
                    NSURLConnectionDownloadDelegate protocols.

    @discussion
                    connection:didFailWithError: will be called at
                    most once, if an error occurs during a resource
                    load.  No other callbacks will be made after.<p>

                    connectionShouldUseCredentialStorage: will be
                    called at most once, before a resource load begins
                    (which means it may be called during construction
                    of the connection.)  The delegate should return
                    TRUE if the connection should consult the shared
                    NSURLCredentialStorage in response to
                    authentication challenges.  Regardless of the
                    result, the authentication challenge methods may
                    still be called.

                    connection:willSendRequestForAuthenticationChallenge:
                    is the preferred (Mac OS X 10.7 and iOS 5.0 or
                    later) mechanism for responding to authentication
                    challenges.  See
                    <Foundation/NSURLAuthenticationChallenge.h> for
                    more information on dealing with the various types
                    of authentication challenges.

                    connection:canAuthenticateAgainstProtectionSpace:
                    connection:didReciveAuthenticationChallenge:
                    connection:didCancelAuthenticationChallenge: are
                    deprected and new code should adopt
                    connection:willSendRequestForAuthenticationChallenge.
                    The older delegates will still be called for
                    compatability, but incur more latency in dealing
                    with the authentication challenge.
*/
@protocol NSURLConnectionDelegate <NSObject>
@optional
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (BOOL)connectionShouldUseCredentialStorage:(NSURLConnection *)connection;
- (void)connection:(NSURLConnection *)connection willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;
- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace NS_DEPRECATED(10_6, 10_10, 3_0, 8_0, "Use -connection:willSendRequestForAuthenticationChallenge: instead.");
- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge NS_DEPRECATED(10_2, 10_10, 2_0, 8_0, "Use -connection:willSendRequestForAuthenticationChallenge: instead.");
- (void)connection:(NSURLConnection *)connection didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge NS_DEPRECATED(10_2, 10_10, 2_0, 8_0, "Use -connection:willSendRequestForAuthenticationChallenge: instead.");
@end

/*!
    @protocol       NSURLConnectionDataDelegate

    @abstract        
                    Delegate methods used for loading data to memory.
                    These delegate methods are all optional.

    @discussion
                    connection:willSendRequest:redirectResponse: is
                    called whenever an connection determines that it
                    must change URLs in order to continue loading a
                    request.  This gives the delegate an opportunity
                    inspect and if necessary modify a request.  A
                    delegate can cause the request to abort by either
                    calling the connections -cancel method, or by
                    returning nil from this callback.<p>

                    There is one subtle difference which results from
                    this choice. If -cancel is called in the delegate
                    method, all processing for the connection stops,
                    and no further delegate callbacks will be sent. If
                    the delegate returns nil, the connection will
                    continue to process, and this has special
                    relevance in the case where the redirectResponse
                    argument is non-nil. In this case, any data that
                    is loaded for the connection will be sent to the
                    delegate, and the delegate will receive a finished
                    or failure delegate callback as appropriate.<p>

                    connection:didReceiveResponse: is called when
                    enough data has been read to construct an
                    NSURLResponse object. In the event of a protocol
                    which may return multiple responses (such as HTTP
                    multipart/x-mixed-replace) the delegate should be
                    prepared to inspect the new response and make
                    itself ready for data callbacks as appropriate.<p>

                    connection:didReceiveData: is called with a single
                    immutable NSData object to the delegate,
                    representing the next portion of the data loaded
                    from the connection.  This is the only guaranteed
                    for the delegate to receive the data from the
                    resource load.<p>

                    connection:needNewBodyStream: is called when the
                    loader must retransmit a requests payload, due to
                    connection errors or authentication challenges.
                    Delegates should construct a new unopened and
                    autoreleased NSInputStream.  If not implemented,
                    the loader will be required to spool the bytes to
                    be uploaded to disk, a potentially expensive
                    operation.  Returning nil will cancel the
                    connection.

                    connection:didSendBodyData:totalBytesWritten:totalBytesExpectedToWrite:
                    is called during an upload operation to provide
                    progress feedback.  Note that the values may
                    change in unexpected ways if the request needs to
                    be retransmitted.<p>

                    connection:willCacheResponse: gives the delegate
                    an opportunity to inspect and modify the
                    NSCachedURLResponse which will be cached by the
                    loader if caching is enabled for the original
                    NSURLRequest.  Returning nil from this delegate
                    will prevent the resource from being cached.  Note
                    that the -data method of the cached response may
                    return an autoreleased in-memory copy of the true
                    data, and should not be used as an alternative to
                    receiving and accumulating the data through
                    connection:didReceiveData:<p>

                    connectionDidFinishLoading: is called when all
                    connection processing has completed successfully,
                    before the delegate is released by the
                    connection.<p>
*/

@protocol NSURLConnectionDataDelegate <NSURLConnectionDelegate>
@optional
- (nullable NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(nullable NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;

- (nullable NSInputStream *)connection:(NSURLConnection *)connection needNewBodyStream:(NSURLRequest *)request;
- (void)connection:(NSURLConnection *)connection   didSendBodyData:(NSInteger)bytesWritten
                                                 totalBytesWritten:(NSInteger)totalBytesWritten
                                         totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite;

- (nullable NSCachedURLResponse *)connection:(NSURLConnection *)connection willCacheResponse:(NSCachedURLResponse *)cachedResponse;

- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
@end

/*!
    @protocol       NSURLConnectionDownloadDelegate

    @abstract
                    Delegate methods used to perform resource
                    downloads directly to a disk file.  All the
                    methods are optional with the exception of
                    connectionDidFinishDownloading:destinationURL:
                    which must be implemented in order to inform the
                    delegate of the location of the finished download.
                    This delegate and download implementation is
                    currently only available on iOS 5.0 or later.

    @discussion
                    connection:didWriteData:totalBytesWritten:expectedTotalBytes:
                    provides progress information about the state of
                    the download, the number of bytes written since
                    the last delegate callback, the total number of
                    bytes written to disk and the total number of
                    bytes that are expected (or 0 if this is unknown.)

                    connectionDidResumeDownloading:totalBytesWritten:expectedTotalBytes:
                    is called when the connection is able to resume an
                    in progress download.  This may happen due to a
                    connection or network failure.

                    connectionDidFinishDownloading:destinationURL: is
                    a terminal event which indicates the completion of
                    a download and provides the location of the file.
                    The file will be located in the applications cache
                    directory and is guaranteed to exist for the
                    duration of the delegate callback.  The
                    implication is that the delegate should copy or
                    move the download to a more persistent location if
                    desired.
*/

@protocol NSURLConnectionDownloadDelegate <NSURLConnectionDelegate>
@optional
- (void)connection:(NSURLConnection *)connection didWriteData:(long long)bytesWritten totalBytesWritten:(long long)totalBytesWritten expectedTotalBytes:(long long) expectedTotalBytes;
- (void)connectionDidResumeDownloading:(NSURLConnection *)connection totalBytesWritten:(long long)totalBytesWritten expectedTotalBytes:(long long) expectedTotalBytes;

@required
- (void)connectionDidFinishDownloading:(NSURLConnection *)connection destinationURL:(NSURL *) destinationURL;
@end

/*!
    @category    NSURLConnection(NSURLConnectionSynchronousLoading)

    @abstract
                 The NSURLConnectionSynchronousLoading category on
                 NSURLConnection provides the interface to perform
                 synchronous loading of URL requests.
*/
@interface NSURLConnection (NSURLConnectionSynchronousLoading)

/*! 
    @method      sendSynchronousRequest:returningResponse:error:

    @abstract 
                 Performs a synchronous load of the given request,
                 returning an NSURLResponse in the given out
                 parameter.

    @discussion
                 A synchronous load for the given request is built on
                 top of the asynchronous loading code made available
                 by the class.  The calling thread is blocked while
                 the asynchronous loading system performs the URL load
                 on a thread spawned specifically for this load
                 request. No special threading or run loop
                 configuration is necessary in the calling thread in
                 order to perform a synchronous load. For instance,
                 the calling thread need not be running its run loop.

    @param
       request   The request to load. Note that the request is
                 deep-copied as part of the initialization
                 process. Changes made to the request argument after
                 this method returns do not affect the request that is
                 used for the loading process.

    @param
       response  An out parameter which is filled in with the
                 response generated by performing the load.

    @param
       error     Out parameter (may be NULL) used if an error occurs
                 while processing the request. Will not be modified if the 
                 load succeeds.

    @result      The content of the URL resulting from performing the load,
                 or nil if the load failed.
*/
+ (nullable NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse * __nullable * __nullable)response error:(NSError **)error NS_DEPRECATED(10_3, 10_11, 2_0, 9_0, "Use [NSURLSession dataTaskWithRequest:completionHandler:] (see NSURLSession.h");

@end

/*!
    @category NSURLConnection(NSURLConnectionQueuedLoading)

    The NSURLConnectionQueuedLoading category on NSURLConnection
    provides the interface to perform asynchronous loading of URL
    requests where the results of the request are delivered to a
    block via an NSOperationQueue.

    Note that there is no guarantee of load ordering implied by this
    method.
 */
@interface NSURLConnection (NSURLConnectionQueuedLoading)

/*!
    @method       sendAsynchronousRequest:queue:completionHandler:

    @abstract 
                  Performs an asynchronous load of the given
                  request. When the request has completed or failed,
                  the block will be executed from the context of the
                  specified NSOperationQueue.

    @discussion
                  This is a convenience routine that allows for
                  asynchronous loading of an url based resource.  If
                  the resource load is successful, the data parameter
                  to the callback will contain the resource data and
                  the error parameter will be nil.  If the resource
                  load fails, the data parameter will be nil and the
                  error will contain information about the failure.

    @param
         request   The request to load. Note that the request is
                   deep-copied as part of the initialization
                   process. Changes made to the request argument after
                   this method returns do not affect the request that
                   is used for the loading process.

    @param 
         queue     An NSOperationQueue upon which    the handler block will
                   be dispatched.

    @param
         handler   A block which receives the results of the resource load.
 */
+ (void)sendAsynchronousRequest:(NSURLRequest*) request
                          queue:(NSOperationQueue*) queue
              completionHandler:(void (^)(NSURLResponse* __nullable response, NSData* __nullable data, NSError* __nullable connectionError)) handler NS_DEPRECATED(10_7, 10_11, 5_0, 9_0, "Use [NSURLSession dataTaskWithRequest:completionHandler:] (see NSURLSession.h");
           
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSZone.h
/*	NSZone.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#include <CoreFoundation/CFBase.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

typedef struct _NSZone NSZone;

FOUNDATION_EXPORT NSZone *NSDefaultMallocZone(void) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT NSZone *NSCreateZone(NSUInteger startSize, NSUInteger granularity, BOOL canFree) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT void NSRecycleZone(NSZone *zone)NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

FOUNDATION_EXPORT void NSSetZoneName(NSZone * __nullable zone, NSString *name)NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT NSString *NSZoneName(NSZone * __nullable zone) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT NSZone * __nullable NSZoneFromPointer(void *ptr) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

FOUNDATION_EXPORT void *NSZoneMalloc(NSZone * __nullable zone, NSUInteger size) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT void *NSZoneCalloc(NSZone * __nullable zone, NSUInteger numElems, NSUInteger byteSize) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT void *NSZoneRealloc(NSZone * __nullable zone, void * __nullable ptr, NSUInteger size) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
FOUNDATION_EXPORT void NSZoneFree(NSZone * __nullable zone, void *ptr) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* Garbage Collected memory allocation.
   Raw memory may be directly allocated (and "realloc"ed) from the collector. The default unscanned memory returned by this call should not be used to hold live pointers to garbage collected memory.  Use the scanned option.  Further, the pointer type of the stored location must be marked with the __strong attribute in order for the write-barrier assignment primitive to be generated.  
   The NSCollectorDisabledOption provides an allocation for use as an external reference.
*/

NS_ENUM(NSUInteger) {
    NSScannedOption = (1UL << 0),
    NSCollectorDisabledOption = (1UL << 1),
};

FOUNDATION_EXPORT void *__strong NSAllocateCollectable(NSUInteger size, NSUInteger options) NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");
FOUNDATION_EXPORT void *__strong NSReallocateCollectable(void * __nullable ptr, NSUInteger size, NSUInteger options) NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");

#endif

#ifndef CF_CONSUMED
#if __has_feature(attribute_cf_consumed)
#define CF_CONSUMED __attribute__((cf_consumed))
#else
#define CF_CONSUMED
#endif
#endif

/*
 NSMakeCollectable
 CFTypeRef style objects are garbage collected, yet only sometime after the last CFRelease() is performed.  Particulary for fully-bridged CFTypeRef objects such as CFStrings and collections (CFDictionaryRef et alia) it is imperative that either CFMakeCollectable or the more type safe NSMakeCollectable be performed, preferably right upon allocation.  Conceptually, this moves them from a "C" style opaque pointer into an "id" style object.
 This function is unavailable in ARC mode. Use CFBridgingRelease instead.
*/
NS_INLINE NS_RETURNS_RETAINED id __nullable NSMakeCollectable(CFTypeRef __nullable CF_CONSUMED cf) NS_AUTOMATED_REFCOUNT_UNAVAILABLE NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");
NS_INLINE NS_RETURNS_RETAINED id __nullable NSMakeCollectable(CFTypeRef __nullable CF_CONSUMED cf) {
#if __has_feature(objc_arc)
    return nil;
#else
    return (cf ? (id)CFMakeCollectable(cf) : nil);
#endif
}

FOUNDATION_EXPORT NSUInteger NSPageSize(void);
FOUNDATION_EXPORT NSUInteger NSLogPageSize(void);
FOUNDATION_EXPORT NSUInteger NSRoundUpToMultipleOfPageSize(NSUInteger bytes);
FOUNDATION_EXPORT NSUInteger NSRoundDownToMultipleOfPageSize(NSUInteger bytes);
FOUNDATION_EXPORT void *NSAllocateMemoryPages(NSUInteger bytes);
FOUNDATION_EXPORT void NSDeallocateMemoryPages(void *ptr, NSUInteger bytes);
FOUNDATION_EXPORT void NSCopyMemoryPages(const void *source, void *dest, NSUInteger bytes);
FOUNDATION_EXPORT NSUInteger NSRealMemoryAvailable(void) NS_DEPRECATED(10_0, 10_8, 2_0, 6_0); // see NSProcessInfo.h instead

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/Foundation.h
/*	Foundation.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/


#include <CoreFoundation/CoreFoundation.h>

#import <Foundation/NSObjCRuntime.h>

#import <Foundation/NSArray.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSBundle.h>
#import <Foundation/NSByteOrder.h>
#import <Foundation/NSCalendar.h>
#import <Foundation/NSCharacterSet.h>
#import <Foundation/NSCoder.h>
#import <Foundation/NSData.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSDateFormatter.h>
#import <Foundation/NSDateIntervalFormatter.h>
#import <Foundation/NSMassFormatter.h>
#import <Foundation/NSLengthFormatter.h>
#import <Foundation/NSEnergyFormatter.h>
#import <Foundation/NSPersonNameComponents.h>
#import <Foundation/NSPersonNameComponentsFormatter.h>
#import <Foundation/NSDecimal.h>
#import <Foundation/NSDecimalNumber.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSError.h>
#import <Foundation/NSException.h>
#import <Foundation/NSFileHandle.h>
#import <Foundation/NSFileManager.h>
#import <Foundation/NSFormatter.h>
#import <Foundation/NSHashTable.h>
#import <Foundation/NSHTTPCookie.h>
#import <Foundation/NSHTTPCookieStorage.h>
#import <Foundation/NSIndexPath.h>
#import <Foundation/NSIndexSet.h>
#import <Foundation/NSInvocation.h>
#import <Foundation/NSJSONSerialization.h>
#import <Foundation/NSKeyValueCoding.h>
#import <Foundation/NSKeyValueObserving.h>
#import <Foundation/NSKeyedArchiver.h>
#import <Foundation/NSLocale.h>
#import <Foundation/NSLock.h>
#import <Foundation/NSMapTable.h>
#import <Foundation/NSMethodSignature.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSNotificationQueue.h>
#import <Foundation/NSNull.h>
#import <Foundation/NSNumberFormatter.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSOperation.h>
#import <Foundation/NSOrderedSet.h>
#import <Foundation/NSOrthography.h>
#import <Foundation/NSPathUtilities.h>
#import <Foundation/NSPointerArray.h>
#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSPort.h>
#import <Foundation/NSProcessInfo.h>
#import <Foundation/NSPropertyList.h>
#import <Foundation/NSProxy.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSRegularExpression.h>
#import <Foundation/NSRunLoop.h>
#import <Foundation/NSScanner.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSSortDescriptor.h>
#import <Foundation/NSStream.h>
#import <Foundation/NSString.h>
#import <Foundation/NSTextCheckingResult.h>
#import <Foundation/NSThread.h>
#import <Foundation/NSTimeZone.h>
#import <Foundation/NSTimer.h>
#import <Foundation/NSURL.h>
#import <Foundation/NSURLAuthenticationChallenge.h>
#import <Foundation/NSURLCache.h>
#import <Foundation/NSURLConnection.h>
#import <Foundation/NSURLCredential.h>
#import <Foundation/NSURLCredentialStorage.h>
#import <Foundation/NSURLError.h>
#import <Foundation/NSURLProtectionSpace.h>
#import <Foundation/NSURLProtocol.h>
#import <Foundation/NSURLRequest.h>
#import <Foundation/NSURLResponse.h>
#import <Foundation/NSUserDefaults.h>
#import <Foundation/NSValue.h>
#import <Foundation/NSValueTransformer.h>
#import <Foundation/NSXMLParser.h>
#import <Foundation/NSZone.h>

#import <Foundation/FoundationErrors.h>

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

#import <Foundation/NSAttributedString.h>
#import <Foundation/NSByteCountFormatter.h>
#import <Foundation/NSCache.h>
#import <Foundation/NSComparisonPredicate.h>
#import <Foundation/NSCompoundPredicate.h>
#import <Foundation/NSDateComponentsFormatter.h>
#import <Foundation/NSExpression.h>
#import <Foundation/NSExtensionContext.h>
#import <Foundation/NSExtensionItem.h>
#import <Foundation/NSExtensionRequestHandling.h>
#import <Foundation/NSFileCoordinator.h>
#import <Foundation/NSFilePresenter.h>
#import <Foundation/NSFileVersion.h>
#import <Foundation/NSFileWrapper.h>
#import <Foundation/NSItemProvider.h>
#import <Foundation/NSLinguisticTagger.h>
#import <Foundation/NSMetadata.h>
#import <Foundation/NSMetadataAttributes.h>
#import <Foundation/NSNetServices.h>
#import <Foundation/NSPredicate.h>
#import <Foundation/NSProgress.h>
#import <Foundation/NSUbiquitousKeyValueStore.h>
#import <Foundation/NSUndoManager.h>
#import <Foundation/NSURLSession.h>
#import <Foundation/NSUserActivity.h>
#import <Foundation/NSUUID.h>
#endif

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

#import <Foundation/NSArchiver.h>
#import <Foundation/NSBackgroundActivityScheduler.h>
#import <Foundation/NSCalendarDate.h>
#import <Foundation/NSConnection.h>
#import <Foundation/NSDistantObject.h>
#import <Foundation/NSDistributedNotificationCenter.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSPortCoder.h>
#import <Foundation/NSPortMessage.h>
#import <Foundation/NSPortNameServer.h>
#import <Foundation/NSProtocolChecker.h>
#import <Foundation/NSTask.h>
#import <Foundation/NSXMLDTD.h>
#import <Foundation/NSXMLDTDNode.h>
#import <Foundation/NSXMLDocument.h>
#import <Foundation/NSXMLElement.h>
#import <Foundation/NSXMLNode.h>
#import <Foundation/NSXMLNodeOptions.h>
#import <Foundation/NSURLDownload.h>
#import <Foundation/NSURLHandle.h>

#endif

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

#import <Foundation/NSAffineTransform.h>
#import <Foundation/NSAppleEventDescriptor.h>
#import <Foundation/NSAppleEventManager.h>
#import <Foundation/NSAppleScript.h>
#import <Foundation/NSClassDescription.h>
#import <Foundation/NSDistributedLock.h>
#import <Foundation/NSGarbageCollector.h>
#import <Foundation/NSHFSFileTypes.h>
#import <Foundation/NSHost.h>
#import <Foundation/NSObjectScripting.h>
#import <Foundation/NSScriptClassDescription.h>
#import <Foundation/NSScriptCoercionHandler.h>
#import <Foundation/NSScriptCommand.h>
#import <Foundation/NSScriptCommandDescription.h>
#import <Foundation/NSScriptExecutionContext.h>
#import <Foundation/NSScriptKeyValueCoding.h>
#import <Foundation/NSScriptObjectSpecifiers.h>
#import <Foundation/NSScriptStandardSuiteCommands.h>
#import <Foundation/NSScriptSuiteRegistry.h>
#import <Foundation/NSScriptWhoseTests.h>
#import <Foundation/NSSpellServer.h>
#import <Foundation/NSUserNotification.h>
#import <Foundation/NSUserScriptTask.h>
#import <Foundation/NSXPCConnection.h>

#endif
// ==========  Foundation.framework/Headers/NSHTTPCookie.h
/*	
    NSHTTPCookie.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;
@class NSDate;
@class NSDictionary<KeyType, ObjectType>;
@class NSNumber;
@class NSString;
@class NSURL;

NS_ASSUME_NONNULL_BEGIN

/*!
    @const NSHTTPCookieName
    @discussion Key for cookie name
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieName;

/*!
    @const NSHTTPCookieValue
    @discussion Key for cookie value
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieValue;

/*!
    @const NSHTTPCookieOriginURL
    @discussion Key for cookie origin URL
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieOriginURL;

/*!
    @const NSHTTPCookieVersion
    @discussion Key for cookie version
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieVersion;

/*!
    @const NSHTTPCookieDomain
    @discussion Key for cookie domain
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieDomain;

/*!
    @const NSHTTPCookiePath
    @discussion Key for cookie path
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookiePath;

/*!
    @const NSHTTPCookieSecure
    @discussion Key for cookie secure flag
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieSecure;

/*!
    @const NSHTTPCookieExpires
    @discussion Key for cookie expiration date
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieExpires;

/*!
    @const NSHTTPCookieComment
    @discussion Key for cookie comment text
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieComment;

/*!
    @const NSHTTPCookieCommentURL
    @discussion Key for cookie comment URL
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieCommentURL;

/*!
    @const NSHTTPCookieDiscard
    @discussion Key for cookie discard (session-only) flag
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieDiscard;

/*!
    @const NSHTTPCookieMaximumAge
    @discussion Key for cookie maximum age (an alternate way of specifying the expiration)
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieMaximumAge;

/*!
    @const NSHTTPCookiePort
    @discussion Key for cookie ports
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookiePort;


@class NSHTTPCookieInternal;

/*!
    @class NSHTTPCookie
    @abstract NSHTTPCookie represents an http cookie.
    @discussion A NSHTTPCookie instance represents a single http cookie. It is
    an immutable object initialized from a dictionary that contains
    the various cookie attributes. It has accessors to get the various
    attributes of a cookie.
*/

@interface NSHTTPCookie : NSObject
{
@private
    NSHTTPCookieInternal * _cookiePrivate;
}

/*!
    @method initWithProperties:
    @abstract Initialize a NSHTTPCookie object with a dictionary of
    parameters
    @param properties The dictionary of properties to be used to
    initialize this cookie.
    @discussion Supported dictionary keys and value types for the
    given dictionary are as follows.

    All properties can handle an NSString value, but some can also
    handle other types.

    <table border=1 cellspacing=2 cellpadding=4>
    <tr>
        <th>Property key constant</th>
        <th>Type of value</th>
        <th>Required</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>NSHTTPCookieComment</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Comment for the cookie. Only valid for version 1 cookies and
        later. Default is nil.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieCommentURL</td>
        <td>NSURL or NSString</td>
        <td>NO</td>
        <td>Comment URL for the cookie. Only valid for version 1 cookies
        and later. Default is nil.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieDomain</td>
        <td>NSString</td>
        <td>Special, a value for either NSHTTPCookieOriginURL or
        NSHTTPCookieDomain must be specified.</td>
        <td>Domain for the cookie. Inferred from the value for
        NSHTTPCookieOriginURL if not provided.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieDiscard</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string stating whether the cookie should be discarded at
        the end of the session. String value must be either "TRUE" or
        "FALSE". Default is "FALSE", unless this is cookie is version
        1 or greater and a value for NSHTTPCookieMaximumAge is not
        specified, in which case it is assumed "TRUE".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieExpires</td>
        <td>NSDate or NSString</td>
        <td>NO</td>
        <td>Expiration date for the cookie. Used only for version 0
        cookies. Ignored for version 1 or greater.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieMaximumAge</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string containing an integer value stating how long in
        seconds the cookie should be kept, at most. Only valid for
        version 1 cookies and later. Default is "0".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieName</td>
        <td>NSString</td>
        <td>YES</td>
        <td>Name of the cookie</td>
    </tr>
    <tr>
        <td>NSHTTPCookieOriginURL</td>
        <td>NSURL or NSString</td>
        <td>Special, a value for either NSHTTPCookieOriginURL or
        NSHTTPCookieDomain must be specified.</td>
        <td>URL that set this cookie. Used as default for other fields
        as noted.</td>
    </tr>
    <tr>
        <td>NSHTTPCookiePath</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Path for the cookie. Inferred from the value for
        NSHTTPCookieOriginURL if not provided. Default is "/".</td>
    </tr>
    <tr>
        <td>NSHTTPCookiePort</td>
        <td>NSString</td>
        <td>NO</td>
        <td>comma-separated integer values specifying the ports for the
        cookie. Only valid for version 1 cookies and later. Default is
        empty string ("").</td>
    </tr>
    <tr>
        <td>NSHTTPCookieSecure</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string stating whether the cookie should be transmitted
        only over secure channels. String value must be either "TRUE"
        or "FALSE". Default is "FALSE".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieValue</td>
        <td>NSString</td>
        <td>YES</td>
        <td>Value of the cookie</td>
    </tr>
    <tr>
        <td>NSHTTPCookieVersion</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Specifies the version of the cookie. Must be either "0" or
        "1". Default is "0".</td>
    </tr>
    </table>
    <p>
    All other keys are ignored.
    @result An initialized NSHTTPCookie, or nil if the set of
    dictionary keys is invalid, for example because a required key is
    missing, or a recognized key maps to an illegal value.
*/
- (nullable instancetype)initWithProperties:(NSDictionary<NSString *, id> *)properties;

/*!
    @method cookieWithProperties:
    @abstract Allocates and initializes an NSHTTPCookie with the given
    dictionary.
    @discussion See the NSHTTPCookie <tt>-initWithProperties:</tt>
    method for more information on the constraints imposed on the
    dictionary, and for descriptions of the supported keys and values.
    @param properties The dictionary to use to initialize this cookie.
    @result A newly-created and autoreleased NSHTTPCookie instance, or
    nil if the set of dictionary keys is invalid, for example because
    a required key is missing, or a recognized key maps to an illegal
    value.
*/
+ (nullable NSHTTPCookie *)cookieWithProperties:(NSDictionary<NSString *, id> *)properties;

/*!
    @method requestHeaderFieldsWithCookies:
    @abstract Return a dictionary of header fields that can be used to add the
    specified cookies to the request.
    @param cookies The cookies to turn into request headers.
    @result An NSDictionary where the keys are header field names, and the values
    are the corresponding header field values.
*/
+ (NSDictionary<NSString *, NSString *> *)requestHeaderFieldsWithCookies:(NSArray<NSHTTPCookie *> *)cookies;

/*!
    @method cookiesWithResponseHeaderFields:forURL:
    @abstract Return an array of cookies parsed from the specified response header fields and URL.
    @param headerFields The response header fields to check for cookies.
    @param URL The URL that the cookies came from - relevant to how the cookies are interpeted.
    @result An NSArray of NSHTTPCookie objects
    @discussion This method will ignore irrelevant header fields so
    you can pass a dictionary containing data other than cookie data.
*/
+ (NSArray<NSHTTPCookie *> *)cookiesWithResponseHeaderFields:(NSDictionary<NSString *, NSString *> *)headerFields forURL:(NSURL *)URL;

/*!
    @method properties
    @abstract Returns a dictionary representation of the receiver.
    @discussion This method returns a dictionary representation of the
    NSHTTPCookie which can be saved and passed to
    <tt>-initWithProperties:</tt> or <tt>+cookieWithProperties:</tt>
    later to reconstitute an equivalent cookie.
    <p>See the NSHTTPCookie <tt>-initWithProperties:</tt> method for
    more information on the constraints imposed on the dictionary, and
    for descriptions of the supported keys and values.
    @result The dictionary representation of the receiver.
*/
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *properties;

/*!
    @method version
    @abstract Returns the version of the receiver.
    @discussion Version 0 maps to "old-style" Netscape cookies.
    Version 1 maps to RFC2965 cookies. There may be future versions.
    @result the version of the receiver.
*/
@property (readonly) NSUInteger version;

/*!
    @method name
    @abstract Returns the name of the receiver.
    @result the name of the receiver.
*/
@property (readonly, copy) NSString *name;

/*!
    @method value
    @abstract Returns the value of the receiver.
    @result the value of the receiver.
*/
@property (readonly, copy) NSString *value;

/*!
    @method expiresDate
    @abstract Returns the expires date of the receiver.
    @result the expires date of the receiver.
    @discussion The expires date is the date when the cookie should be
    deleted. The result will be nil if there is no specific expires
    date. This will be the case only for "session-only" cookies.
    @result The expires date of the receiver.
*/
@property (nullable, readonly, copy) NSDate *expiresDate;

/*!
    @method isSessionOnly
    @abstract Returns whether the receiver is session-only.
    @result YES if this receiver should be discarded at the end of the
    session (regardless of expiration date), NO if receiver need not
    be discarded at the end of the session.
*/
@property (readonly, getter=isSessionOnly) BOOL sessionOnly;

/*!
    @method domain
    @abstract Returns the domain of the receiver.
    @discussion This value specifies URL domain to which the cookie
    should be sent. A domain with a leading dot means the cookie
    should be sent to subdomains as well, assuming certain other
    restrictions are valid. See RFC 2965 for more detail.
    @result The domain of the receiver.
*/
@property (readonly, copy) NSString *domain;

/*!
    @method path
    @abstract Returns the path of the receiver.
    @discussion This value specifies the URL path under the cookie's
    domain for which this cookie should be sent. The cookie will also
    be sent for children of that path, so "/" is the most general.
    @result The path of the receiver.
*/
@property (readonly, copy) NSString *path;

/*!
    @method isSecure
    @abstract Returns whether the receiver should be sent only over
    secure channels
    @discussion Cookies may be marked secure by a server (or by a javascript).
    Cookies marked as such must only be sent via an encrypted connection to 
    trusted servers (i.e. via SSL or TLS), and should not be delievered to any
    javascript applications to prevent cross-site scripting vulnerabilities.
    @result YES if this cookie should be sent only over secure channels,
    NO otherwise.
*/
@property (readonly, getter=isSecure) BOOL secure;

/*!
    @method isHTTPOnly
    @abstract Returns whether the receiver should only be sent to HTTP servers
    per RFC 2965
    @discussion Cookies may be marked as HTTPOnly by a server (or by a javascript).
    Cookies marked as such must only be sent via HTTP Headers in HTTP Requests
    for URL's that match both the path and domain of the respective Cookies.
    Specifically these cookies should not be delivered to any javascript 
    applications to prevent cross-site scripting vulnerabilities.
    @result YES if this cookie should only be sent via HTTP headers,
    NO otherwise.
*/
@property (readonly, getter=isHTTPOnly) BOOL HTTPOnly;

/*!
    @method comment
    @abstract Returns the comment of the receiver.
    @discussion This value specifies a string which is suitable for
    presentation to the user explaining the contents and purpose of this
    cookie. It may be nil.
    @result The comment of the receiver, or nil if the receiver has no
    comment.
*/
@property (nullable, readonly, copy) NSString *comment;

/*!
    @method commentURL
    @abstract Returns the comment URL of the receiver.
    @discussion This value specifies a URL which is suitable for
    presentation to the user as a link for further information about
    this cookie. It may be nil.
    @result The comment URL of the receiver, or nil if the receiver
    has no comment URL.
*/
@property (nullable, readonly, copy) NSURL *commentURL;

/*!
    @method portList
    @abstract Returns the list ports to which the receiver should be
    sent.
    @discussion This value specifies an NSArray of NSNumbers
    (containing integers) which specify the only ports to which this
    cookie should be sent.
    @result The list ports to which the receiver should be sent. The
    array may be nil, in which case this cookie can be sent to any
    port.
*/
@property (nullable, readonly, copy) NSArray<NSNumber *> *portList;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSStream.h
/*	NSStream.h
        Copyright (c) 2003-2015, Apple Inc. All rights reserved
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary, NSError, NSHost, NSInputStream, NSOutputStream, NSRunLoop, NSString, NSURL;
@protocol NSStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSStreamStatus) {
    NSStreamStatusNotOpen = 0,
    NSStreamStatusOpening = 1,
    NSStreamStatusOpen = 2,
    NSStreamStatusReading = 3,
    NSStreamStatusWriting = 4,
    NSStreamStatusAtEnd = 5,
    NSStreamStatusClosed = 6,
    NSStreamStatusError = 7
};

typedef NS_OPTIONS(NSUInteger, NSStreamEvent) {
    NSStreamEventNone = 0,
    NSStreamEventOpenCompleted = 1UL << 0,
    NSStreamEventHasBytesAvailable = 1UL << 1,
    NSStreamEventHasSpaceAvailable = 1UL << 2,
    NSStreamEventErrorOccurred = 1UL << 3,
    NSStreamEventEndEncountered = 1UL << 4
};

// NSStream is an abstract class encapsulating the common API to NSInputStream and NSOutputStream.
// Subclassers of NSInputStream and NSOutputStream must also implement these methods.
@interface NSStream : NSObject
- (void)open;
- (void)close;

@property (nullable, assign) id <NSStreamDelegate> delegate;
    // By default, a stream is its own delegate, and subclassers of NSInputStream and NSOutputStream must maintain this contract. [someStream setDelegate:nil] must restore this behavior. As usual, delegates are not retained.

- (nullable id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(nullable id)property forKey:(NSString *)key;

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

@property (readonly) NSStreamStatus streamStatus;
@property (nullable, readonly, copy) NSError *streamError;
@end

// NSInputStream is an abstract class representing the base functionality of a read stream.
// Subclassers are required to implement these methods.
@interface NSInputStream : NSStream
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;
    // reads up to length bytes into the supplied buffer, which must be at least of size len. Returns the actual number of bytes read.

- (BOOL)getBuffer:(uint8_t * __nullable * __nonnull)buffer length:(NSUInteger *)len;
    // returns in O(1) a pointer to the buffer in 'buffer' and by reference in 'len' how many bytes are available. This buffer is only valid until the next stream operation. Subclassers may return NO for this if it is not appropriate for the stream type. This may return NO if the buffer is not available.

@property (readonly) BOOL hasBytesAvailable;
    // returns YES if the stream has bytes available or if it impossible to tell without actually doing the read.

- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;

@end

// NSOutputStream is an abstract class representing the base functionality of a write stream.
// Subclassers are required to implement these methods.
@interface NSOutputStream : NSStream
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;
    // writes the bytes from the specified buffer to the stream up to len bytes. Returns the number of bytes actually written.

@property (readonly) BOOL hasSpaceAvailable;
    // returns YES if the stream can be written to or if it is impossible to tell without actually doing the write.

- (instancetype)initToMemory NS_DESIGNATED_INITIALIZER;
- (instancetype)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;

@end


@interface NSStream (NSSocketStreamCreationExtensions)

+ (void)getStreamsToHostWithName:(NSString *)hostname port:(NSInteger)port inputStream:(NSInputStream * __nullable * __nullable)inputStream outputStream:(NSOutputStream * __nullable * __nullable)outputStream NS_AVAILABLE(10_10, 8_0);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
+ (void)getStreamsToHost:(NSHost *)host port:(NSInteger)port inputStream:(NSInputStream * __nullable * __nullable)inputStream outputStream:(NSOutputStream * __nullable * __nullable)outputStream NS_DEPRECATED_MAC(10_3, 10_10, "Please use getStreamsToHostWithName:port:inputStream:outputStream: instead");
#endif

@end

@interface NSStream (NSStreamBoundPairCreationExtensions)
+ (void)getBoundStreamsWithBufferSize:(NSUInteger)bufferSize inputStream:(NSInputStream * __nullable * __nullable)inputStream outputStream:(NSOutputStream * __nullable * __nullable)outputStream NS_AVAILABLE(10_10, 8_0);
@end

// The NSInputStreamExtensions category contains additional initializers and convenience routines for dealing with NSInputStreams.
@interface NSInputStream (NSInputStreamExtensions)
- (nullable instancetype)initWithFileAtPath:(NSString *)path;

+ (nullable instancetype)inputStreamWithData:(NSData *)data;
+ (nullable instancetype)inputStreamWithFileAtPath:(NSString *)path;
+ (nullable instancetype)inputStreamWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
@end

// The NSOutputStreamExtensions category contains additional initializers and convenience routines for dealing with NSOutputStreams.
@interface NSOutputStream (NSOutputStreamExtensions)
- (nullable instancetype)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

+ (instancetype)outputStreamToMemory;
+ (instancetype)outputStreamToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
+ (instancetype)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
+ (nullable instancetype)outputStreamWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0);
@end

@protocol NSStreamDelegate <NSObject>
@optional
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
@end

// NSString constants for the propertyForKey/setProperty:forKey: API
// String constants for the setting of the socket security level.
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelKey		NS_AVAILABLE(10_3, 2_0);	// use this as the key for setting one of the following values for the security level of the target stream.

FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNone		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv2		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv3		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelTLSv1		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNegotiatedSSL	NS_AVAILABLE(10_3, 2_0);

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyConfigurationKey		NS_AVAILABLE(10_3, 2_0);	// Value is an NSDictionary containing the key/value pairs below. The dictionary returned from SystemConfiguration for SOCKS proxies will work without alteration.

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyHostKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPortKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersionKey		NS_AVAILABLE(10_3, 2_0);
    // Value is one of NSStreamSOCKSProxyVersion4 or NSStreamSOCKSProxyVersion5
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyUserKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPasswordKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion4			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion5			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey

FOUNDATION_EXPORT NSString * const NSStreamDataWrittenToMemoryStreamKey	NS_AVAILABLE(10_3, 2_0);
    // Key for obtaining the data written to a memory stream.

FOUNDATION_EXPORT NSString * const NSStreamFileCurrentOffsetKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber representing the current absolute offset of the stream.

// NSString constants for error domains.
FOUNDATION_EXPORT NSString * const NSStreamSocketSSLErrorDomain			NS_AVAILABLE(10_3, 2_0);
    // SSL errors are to be interpreted via <Security/SecureTransport.h>
FOUNDATION_EXPORT NSString * const NSStreamSOCKSErrorDomain			NS_AVAILABLE(10_3, 2_0);

// Property key to specify the type of service for the stream.  This
// allows the system to properly handle the request with respect to
// routing, suspension behavior and other networking related attributes
// appropriate for the given service type.  The service types supported
// are documented below.
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceType		    NS_AVAILABLE(10_7, 4_0);
// Supported network service types:
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVoIP	    NS_AVAILABLE(10_7, 4_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVideo	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeBackground	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVoice	    NS_AVAILABLE(10_7, 5_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSExtensionRequestHandling.h
/*	NSExtensionRequestHandling.h
 Copyright (c) 2013-2014, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#if __OBJC2__
NS_ASSUME_NONNULL_BEGIN

@class NSExtensionContext;

// The basic NSExtensionRequestHandling protocol defines a lifecycle hook into the extension. Non view-controller-based services might keep track of the current request using this method. Implemented by the principal object of the extension.
@protocol NSExtensionRequestHandling <NSObject>

@required

// Tells the extension to prepare its interface for the requesting context, and request related data items. At this point [(NS|UI)ViewController extensionContext] returns a non-nil value. This message is delivered after initialization, but before the conforming object will be asked to "do something" with the context (i.e. before -[(NS|UI)ViewController loadView]). Subclasses of classes conforming to this protocol are expected to call [super beginRequestWithExtensionContext:] if this method is overridden.
- (void)beginRequestWithExtensionContext:(NSExtensionContext *)context;

@end

NS_ASSUME_NONNULL_END
#endif
// ==========  Foundation.framework/Headers/NSProxy.h
/*	NSProxy.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature, NSInvocation;

NS_ASSUME_NONNULL_BEGIN

NS_ROOT_CLASS
@interface NSProxy <NSObject> {
    Class	isa;
}

+ (id)alloc;
+ (id)allocWithZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
+ (Class)class;

- (void)forwardInvocation:(NSInvocation *)invocation;
- (nullable NSMethodSignature *)methodSignatureForSelector:(SEL)sel NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available");
- (void)dealloc;
- (void)finalize;
@property (readonly, copy) NSString *description;
@property (readonly, copy) NSString *debugDescription;
+ (BOOL)respondsToSelector:(SEL)aSelector;

- (BOOL)allowsWeakReference NS_UNAVAILABLE;
- (BOOL)retainWeakReference NS_UNAVAILABLE;

// - (id)forwardingTargetForSelector:(SEL)aSelector;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSArray.h
/*	NSArray.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>

@class NSData, NSIndexSet, NSString, NSURL;

/****************	Immutable Array		****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSArray<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (ObjectType)objectAtIndex:(NSUInteger)index;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSArray<ObjectType> (NSExtendedArray)

- (NSArray<ObjectType> *)arrayByAddingObject:(ObjectType)anObject;
- (NSArray<ObjectType> *)arrayByAddingObjectsFromArray:(NSArray<ObjectType> *)otherArray;
- (NSString *)componentsJoinedByString:(NSString *)separator;
- (BOOL)containsObject:(ObjectType)anObject;
@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
- (nullable ObjectType)firstObjectCommonWithArray:(NSArray<ObjectType> *)otherArray;
- (void)getObjects:(ObjectType __unsafe_unretained [])objects range:(NSRange)range;
- (NSUInteger)indexOfObject:(ObjectType)anObject;
- (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject;
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
- (BOOL)isEqualToArray:(NSArray<ObjectType> *)otherArray;
@property (nullable, nonatomic, readonly) ObjectType firstObject NS_AVAILABLE(10_6, 4_0);
@property (nullable, nonatomic, readonly) ObjectType lastObject;
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;
@property (readonly, copy) NSData *sortedArrayHint;
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (*)(ObjectType, ObjectType, void * __nullable))comparator context:(nullable void *)context;
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (*)(ObjectType, ObjectType, void * __nullable))comparator context:(nullable void *)context hint:(nullable NSData *)hint;
- (NSArray<ObjectType> *)sortedArrayUsingSelector:(SEL)comparator;
- (NSArray<ObjectType> *)subarrayWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;

- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;

- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSUInteger)indexOfObjectPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSBinarySearchingOptions) {
	NSBinarySearchingFirstEqual = (1UL << 8),
	NSBinarySearchingLastEqual = (1UL << 9),
	NSBinarySearchingInsertionIndex = (1UL << 10),
};

- (NSUInteger)indexOfObject:(ObjectType)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp NS_AVAILABLE(10_6, 4_0); // binary search

@end

@interface NSArray<ObjectType> (NSArrayCreation)

+ (instancetype)array;
+ (instancetype)arrayWithObject:(ObjectType)anObject;
+ (instancetype)arrayWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
+ (instancetype)arrayWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)arrayWithArray:(NSArray<ObjectType> *)array;

- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array copyItems:(BOOL)flag;

+ (nullable NSArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
- (nullable NSArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSArray<ObjectType> (NSDeprecated)

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:range: instead.
*/
- (void)getObjects:(ObjectType __unsafe_unretained [])objects;

@end

/****************	Mutable Array		****************/

@interface NSMutableArray<ObjectType> : NSArray<ObjectType>

- (void)addObject:(ObjectType)anObject;
- (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;
- (void)removeLastObject;
- (void)removeObjectAtIndex:(NSUInteger)index;
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)anObject;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableArray<ObjectType> (NSExtendedMutableArray)
    
- (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
- (void)removeAllObjects;
- (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;
- (void)removeObject:(ObjectType)anObject;
- (void)removeObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
- (void)removeObjectIdenticalTo:(ObjectType)anObject;
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (void)removeObjectsInArray:(NSArray<ObjectType> *)otherArray;
- (void)removeObjectsInRange:(NSRange)range;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray range:(NSRange)otherRange;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray;
- (void)setArray:(NSArray<ObjectType> *)otherArray;
- (void)sortUsingFunction:(NSInteger (*)(ObjectType,  ObjectType, void * __nullable))compare context:(nullable void *)context;
- (void)sortUsingSelector:(SEL)comparator;

- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

- (void)sortUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

@end

@interface NSMutableArray<ObjectType> (NSMutableArrayCreation)

+ (instancetype)arrayWithCapacity:(NSUInteger)numItems;

+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSPort.h
/*	NSPort.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

typedef int NSSocketNativeHandle;

@class NSRunLoop, NSMutableArray, NSDate;
@class NSConnection, NSPortMessage;
@class NSData;
@protocol NSPortDelegate, NSMachPortDelegate;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSPortDidBecomeInvalidNotification;

@interface NSPort : NSObject <NSCopying, NSCoding>

// For backwards compatibility on Mach, +allocWithZone: returns
// an instance of the NSMachPort class when sent to the NSPort
// class.  Otherwise, it returns an instance of a concrete
// subclass which can be used for messaging between threads
// or processes on the local machine.

+ (NSPort *)port;

- (void)invalidate;
@property (readonly, getter=isValid) BOOL valid;

- (void)setDelegate:(nullable id <NSPortDelegate>)anObject;
- (nullable id <NSPortDelegate>)delegate;

// These two methods should be implemented by subclasses
// to setup monitoring of the port when added to a run loop,
// and stop monitoring if needed when removed;
// These methods should not be called directly!
- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;

// DO Transport API; subclassers should implement these methods
// default is 0
@property (readonly) NSUInteger reservedSpaceLength;	
- (BOOL)sendBeforeDate:(NSDate *)limitDate components:(nullable NSMutableArray *)components from:(nullable NSPort *) receivePort reserved:(NSUInteger)headerSpaceReserved;
- (BOOL)sendBeforeDate:(NSDate *)limitDate msgid:(NSUInteger)msgID components:(nullable NSMutableArray *)components from:(nullable NSPort *)receivePort reserved:(NSUInteger)headerSpaceReserved;
	// The components array consists of a series of instances
	// of some subclass of NSData, and instances of some
	// subclass of NSPort; since one subclass of NSPort does
	// not necessarily know how to transport an instance of
	// another subclass of NSPort (or could do it even if it
	// knew about the other subclass), all of the instances
	// of NSPort in the components array and the 'receivePort'
	// argument MUST be of the same subclass of NSPort that
	// receives this message.  If multiple DO transports are
	// being used in the same program, this requires some care.

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_WIN32)
- (void)addConnection:(NSConnection *)conn toRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead");
- (void)removeConnection:(NSConnection *)conn fromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead");
	// The default implementation of these two methods is to
	// simply add the receiving port to the run loop in the
	// given mode.  Subclassers need not override these methods,
	// but can if they need to do extra work.
#endif

@end

@protocol NSPortDelegate <NSObject>
@optional

- (void)handlePortMessage:(NSPortMessage *)message;
	// This is the delegate method that subclasses should send
	// to their delegates, unless the subclass has something
	// more specific that it wants to try to send first
@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE 
@interface NSMachPort : NSPort {
    @private
    id _delegate;
    NSUInteger _flags;
    uint32_t _machPort;
    NSUInteger _reserved;
}

+ (NSPort *)portWithMachPort:(uint32_t)machPort;
- (instancetype)initWithMachPort:(uint32_t)machPort NS_DESIGNATED_INITIALIZER;

- (void)setDelegate:(nullable id <NSMachPortDelegate>)anObject;
- (nullable id <NSMachPortDelegate>)delegate;

typedef NS_OPTIONS(NSUInteger, NSMachPortOptions) {
    NSMachPortDeallocateNone = 0,
    NSMachPortDeallocateSendRight = (1UL << 0),
    NSMachPortDeallocateReceiveRight = (1UL << 1)
} NS_ENUM_AVAILABLE(10_5, 2_0);

+ (NSPort *)portWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f NS_AVAILABLE(10_5, 2_0);
- (instancetype)initWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;

@property (readonly) uint32_t machPort;

- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
	// If you subclass NSMachPort, you have to override these 2
	// methods from NSPort; since this is complicated, subclassing
	// NSMachPort is not recommended

@end

@protocol NSMachPortDelegate <NSPortDelegate>
@optional

// Delegates are sent this if they respond, otherwise they
// are sent handlePortMessage:; argument is the raw Mach message
- (void)handleMachMessage:(void *)msg;

@end

#endif

// A subclass of NSPort which can be used for local
// message sending on all platforms.
NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE 
@interface NSMessagePort : NSPort {
    @private
    void * __strong _port;
    id _delegate;
}

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32 || TARGET_IPHONE_SIMULATOR

// A subclass of NSPort which can be used for remote
// message sending on all platforms.

@interface NSSocketPort : NSPort {
    @private
    void * __strong _receiver;
    id _connectors;
    void * __strong _loops;
    void * __strong _data;
    id _signature;
    id _delegate;
    id _lock;
    NSUInteger _maxSize;
    NSUInteger _useCount;
    NSUInteger _reserved;
}

- (instancetype)init;
- (nullable instancetype)initWithTCPPort:(unsigned short)port;
- (nullable instancetype)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol socket:(NSSocketNativeHandle)sock NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initRemoteWithTCPPort:(unsigned short)port host:(nullable NSString *)hostName;
- (instancetype)initRemoteWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address NS_DESIGNATED_INITIALIZER;


@property (readonly) int protocolFamily;
@property (readonly) int socketType;
@property (readonly) int protocol;
@property (readonly, copy) NSData *address;
@property (readonly) NSSocketNativeHandle socket;

@end

#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLProtocol.h
/*	
    NSURLProtocol.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLCache.h>

@class NSCachedURLResponse;
@class NSError;
@class NSMutableURLRequest;
@class NSURLAuthenticationChallenge;
@class NSURLConnection;
@class NSURLProtocol;
@class NSURLProtocolInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSURLSessionTask;

NS_ASSUME_NONNULL_BEGIN

/*!
    @header NSURLProtocol.h

    This header file describes the constructs used to represent URL
    protocols, and describes the extensible system by which specific
    classes can be made to handle the loading of particular URL types or
    schemes.
    
    <p>NSURLProtocol is an abstract class which provides the
    basic structure for performing protocol-specific loading of URL
    data.
    
    <p>The NSURLProtocolClient describes the integration points a
    protocol implemention can use to hook into the URL loading system.
    NSURLProtocolClient describes the methods a protocol implementation
    needs to drive the URL loading system from a NSURLProtocol subclass.
    
    <p>To support customization of protocol-specific requests,
    protocol implementors are encouraged to provide categories on
    NSURLRequest and NSMutableURLRequest. Protocol implementors who
    need to extend the capabilities of NSURLRequest and
    NSMutableURLRequest in this way can store and retrieve
    protocol-specific request data by using the
    <tt>+propertyForKey:inRequest:</tt> and
    <tt>+setProperty:forKey:inRequest:</tt> class methods on
    NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
    NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
    such extensions.
    
    <p>An essential responsibility for a protocol implementor is
    creating a NSURLResponse for each request it processes successfully.
    A protocol implementor may wish to create a custom, mutable 
    NSURLResponse class to aid in this work.
*/

/*!
@protocol NSURLProtocolClient
@discussion NSURLProtocolClient provides the interface to the URL
loading system that is intended for use by NSURLProtocol
implementors.
*/
@protocol NSURLProtocolClient <NSObject>

/*!
@method URLProtocol:wasRedirectedToRequest:
 @abstract Indicates to an NSURLProtocolClient that a redirect has
 occurred.
 @param URLProtocol the NSURLProtocol object sending the message.
 @param request the NSURLRequest to which the protocol implementation
 has redirected.
 */
- (void)URLProtocol:(NSURLProtocol *)protocol wasRedirectedToRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;

    /*!
@method URLProtocol:cachedResponseIsValid:
     @abstract Indicates to an NSURLProtocolClient that the protocol
     implementation has examined a cached response and has
     determined that it is valid.
     @param URLProtocol the NSURLProtocol object sending the message.
     @param cachedResponse the NSCachedURLResponse object that has
     examined and is valid.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol cachedResponseIsValid:(NSCachedURLResponse *)cachedResponse;

    /*!
@method URLProtocol:didReceiveResponse:
     @abstract Indicates to an NSURLProtocolClient that the protocol
     implementation has created an NSURLResponse for the current load.
     @param URLProtocol the NSURLProtocol object sending the message.
     @param response the NSURLResponse object the protocol implementation
     has created.
     @param cacheStoragePolicy The NSURLCacheStoragePolicy the protocol
     has determined should be used for the given response if the
     response is to be stored in a cache.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveResponse:(NSURLResponse *)response cacheStoragePolicy:(NSURLCacheStoragePolicy)policy;

    /*!
@method URLProtocol:didLoadData:
     @abstract Indicates to an NSURLProtocolClient that the protocol
     implementation has loaded URL data.
     @discussion The data object must contain only new data loaded since
     the previous call to this method (if any), not cumulative data for
     the entire load.
     @param URLProtocol the NSURLProtocol object sending the message.
     @param data URL load data being made available.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol didLoadData:(NSData *)data;

    /*!
@method URLProtocolDidFinishLoading:
     @abstract Indicates to an NSURLProtocolClient that the protocol
     implementation has finished loading successfully.
     @param URLProtocol the NSURLProtocol object sending the message.
     */
- (void)URLProtocolDidFinishLoading:(NSURLProtocol *)protocol;

    /*!
                @method URLProtocol:didFailWithError:
     @abstract Indicates to an NSURLProtocolClient that the protocol
     implementation has failed to load successfully.
     @param URLProtocol the NSURLProtocol object sending the message.
     @param error The error that caused the load to fail.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol didFailWithError:(NSError *)error;

    /*!
@method URLProtocol:didReceiveAuthenticationChallenge:
     @abstract Start authentication for the specified request
     @param protocol The protocol object requesting authentication.
     @param challenge The authentication challenge.
     @discussion The protocol client guarantees that it will answer the
     request on the same thread that called this method. It may add a
     default credential to the challenge it issues to the connection delegate,
     if the protocol did not provide one.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

    /*!
@method URLProtocol:didCancelAuthenticationChallenge:
     @abstract Cancel authentication for the specified request
     @param protocol The protocol object cancelling authentication.
     @param challenge The authentication challenge.
     */
- (void)URLProtocol:(NSURLProtocol *)protocol didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@end


/*!
    @class NSURLProtocol
    
    @abstract NSURLProtocol is an abstract class which provides the
    basic structure for performing protocol-specific loading of URL
    data. Concrete subclasses handle the specifics associated with one
    or more protocols or URL schemes.
*/
@interface NSURLProtocol : NSObject
{
    @private
    NSURLProtocolInternal *_internal;
}

/*! 
    @method initWithRequest:cachedResponse:client:
    @abstract Initializes an NSURLProtocol given request, 
    cached response, and client.
    @param request The request to load.
    @param cachedResponse A response that has been retrieved from the
    cache for the given request. The protocol implementation should
    apply protocol-specific validity checks if such tests are
    necessary.
    @param client The NSURLProtocolClient object that serves as the
    interface the protocol implementation can use to report results back
    to the URL loading system.
*/
- (instancetype)initWithRequest:(NSURLRequest *)request cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client NS_DESIGNATED_INITIALIZER;

/*! 
    @method client
    @abstract Returns the NSURLProtocolClient of the receiver. 
    @result The NSURLProtocolClient of the receiver.  
*/
@property (nullable, readonly, retain) id <NSURLProtocolClient> client;

/*! 
    @method request
    @abstract Returns the NSURLRequest of the receiver. 
    @result The NSURLRequest of the receiver. 
*/
@property (readonly, copy) NSURLRequest *request;

/*! 
    @method cachedResponse
    @abstract Returns the NSCachedURLResponse of the receiver.  
    @result The NSCachedURLResponse of the receiver. 
*/
@property (nullable, readonly, copy) NSCachedURLResponse *cachedResponse;

/*======================================================================
  Begin responsibilities for protocol implementors

  The methods between this set of begin-end markers must be
  implemented in order to create a working protocol.
  ======================================================================*/
  
/*! 
    @method canInitWithRequest:
    @abstract This method determines whether this protocol can handle
    the given request.
    @discussion A concrete subclass should inspect the given request and
    determine whether or not the implementation can perform a load with
    that request. This is an abstract method. Sublasses must provide an
    implementation. The implementation in this class calls
    NSRequestConcreteImplementation.
    @param request A request to inspect.
    @result YES if the protocol can handle the given request, NO if not.
*/
+ (BOOL)canInitWithRequest:(NSURLRequest *)request;

/*! 
    @method canonicalRequestForRequest:
    @abstract This method returns a canonical version of the given
    request.
    @discussion It is up to each concrete protocol implementation to
    define what "canonical" means. However, a protocol should
    guarantee that the same input request always yields the same
    canonical form. Special consideration should be given when
    implementing this method since the canonical form of a request is
    used to look up objects in the URL cache, a process which performs
    equality checks between NSURLRequest objects.
    <p>
    This is an abstract method; sublasses must provide an
    implementation. The implementation in this class calls
    NSRequestConcreteImplementation.
    @param request A request to make canonical.
    @result The canonical form of the given request. 
*/
+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;

/*!
    @method requestIsCacheEquivalent:toRequest:
    @abstract Compares two requests for equivalence with regard to caching.
    @discussion Requests are considered euqivalent for cache purposes
    if and only if they would be handled by the same protocol AND that
    protocol declares them equivalent after performing 
    implementation-specific checks.
    @result YES if the two requests are cache-equivalent, NO otherwise.
*/
+ (BOOL)requestIsCacheEquivalent:(NSURLRequest *)a toRequest:(NSURLRequest *)b;

/*! 
    @method startLoading
    @abstract Starts protocol-specific loading of a request. 
    @discussion When this method is called, the protocol implementation
    should start loading a request.
*/
- (void)startLoading;

/*! 
    @method stopLoading
    @abstract Stops protocol-specific loading of a request. 
    @discussion When this method is called, the protocol implementation
    should end the work of loading a request. This could be in response
    to a cancel operation, so protocol implementations must be able to
    handle this call while a load is in progress.
*/
- (void)stopLoading;

/*======================================================================
  End responsibilities for protocol implementors
  ======================================================================*/

/*! 
    @method propertyForKey:inRequest:
    @abstract Returns the property in the given request previously
    stored with the given key.
    @discussion The purpose of this method is to provide an interface
    for protocol implementors to access protocol-specific information
    associated with NSURLRequest objects.
    @param key The string to use for the property lookup.
    @param request The request to use for the property lookup.
    @result The property stored with the given key, or nil if no property
    had previously been stored with the given key in the given request.
*/
+ (nullable id)propertyForKey:(NSString *)key inRequest:(NSURLRequest *)request;

/*! 
    @method setProperty:forKey:inRequest:
    @abstract Stores the given property in the given request using the
    given key.
    @discussion The purpose of this method is to provide an interface
    for protocol implementors to customize protocol-specific
    information associated with NSMutableURLRequest objects.
    @param value The property to store. 
    @param key The string to use for the property storage. 
    @param request The request in which to store the property. 
*/
+ (void)setProperty:(id)value forKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;

/*!
    @method removePropertyForKey:inRequest:
    @abstract Remove any property stored under the given key
    @discussion Like setProperty:forKey:inRequest: above, the purpose of this
        method is to give protocol implementors the ability to store 
        protocol-specific information in an NSURLRequest
    @param key The key whose value should be removed
    @param request The request to be modified
*/
+ (void)removePropertyForKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;


/*! 
    @method registerClass:
    @abstract This method registers a protocol class, making it visible
    to several other NSURLProtocol class methods.
    @discussion When the URL loading system begins to load a request,
    each protocol class that has been registered is consulted in turn to
    see if it can be initialized with a given request. The first
    protocol handler class to provide a YES answer to
    <tt>+canInitWithRequest:</tt> "wins" and that protocol
    implementation is used to perform the URL load. There is no
    guarantee that all registered protocol classes will be consulted.
    Hence, it should be noted that registering a class places it first
    on the list of classes that will be consulted in calls to
    <tt>+canInitWithRequest:</tt>, moving it in front of all classes
    that had been registered previously.
    <p>A similar design governs the process to create the canonical form
    of a request with the <tt>+canonicalRequestForRequest:</tt> class
    method.
    @param protocolClass the class to register.
    @result YES if the protocol was registered successfully, NO if not.
    The only way that failure can occur is if the given class is not a
    subclass of NSURLProtocol.
*/
+ (BOOL)registerClass:(Class)protocolClass;

/*! 
    @method unregisterClass:
    @abstract This method unregisters a protocol. 
    @discussion After unregistration, a protocol class is no longer
    consulted in calls to NSURLProtocol class methods.
    @param protocolClass The class to unregister.
*/
+ (void)unregisterClass:(Class)protocolClass;

@end


@interface NSURLProtocol (NSURLSessionTaskAdditions)
+ (BOOL)canInitWithTask:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
- (instancetype)initWithTask:(NSURLSessionTask *)task cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client NS_AVAILABLE(10_10, 8_0);
@property (nullable, readonly, copy) NSURLSessionTask *task NS_AVAILABLE(10_10, 8_0);
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSSet.h
/*	NSSet.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (nullable ObjectType)member:(ObjectType)object;
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet<ObjectType> (NSExtendedSet)

@property (readonly, copy) NSArray<ObjectType> *allObjects;
- (nullable ObjectType)anyObject;
- (BOOL)containsObject:(ObjectType)anObject;
@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (BOOL)intersectsSet:(NSSet<ObjectType> *)otherSet;
- (BOOL)isEqualToSet:(NSSet<ObjectType> *)otherSet;
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)otherSet;

- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

- (NSSet<ObjectType> *)setByAddingObject:(ObjectType)anObject NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromSet:(NSSet<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromArray:(NSArray<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSSet<ObjectType> *)objectsPassingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet<ObjectType> *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSSet<ObjectType> (NSSetCreation)

+ (instancetype)set;
+ (instancetype)setWithObject:(ObjectType)object;
+ (instancetype)setWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
+ (instancetype)setWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)setWithSet:(NSSet<ObjectType> *)set;
+ (instancetype)setWithArray:(NSArray<ObjectType> *)array;

- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet<ObjectType> : NSSet<ObjectType>

- (void)addObject:(ObjectType)object;
- (void)removeObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableSet<ObjectType> (NSExtendedMutableSet)

- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;
- (void)intersectSet:(NSSet<ObjectType> *)otherSet;
- (void)minusSet:(NSSet<ObjectType> *)otherSet;
- (void)removeAllObjects;
- (void)unionSet:(NSSet<ObjectType> *)otherSet;

- (void)setSet:(NSSet<ObjectType> *)otherSet;

@end

@interface NSMutableSet<ObjectType> (NSMutableSetCreation)

+ (instancetype)setWithCapacity:(NSUInteger)numItems;

@end

/****************	Counted Set	****************/

@interface NSCountedSet<ObjectType> : NSMutableSet<ObjectType> {
    @private
    id _table;
    void *_reserved;
}

- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;

- (NSUInteger)countForObject:(ObjectType)object;

- (NSEnumerator<ObjectType> *)objectEnumerator;
- (void)addObject:(ObjectType)object;
- (void)removeObject:(ObjectType)object;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSFileManager.h
/*	NSFileManager.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSPathUtilities.h>
#import <CoreFoundation/CFBase.h>

@class NSArray<ObjectType>, NSData, NSDate, NSDirectoryEnumerator<ObjectType>, NSError, NSNumber;
@protocol NSFileManagerDelegate;

NS_ASSUME_NONNULL_BEGIN

/* Version number where NSFileManager can copy/move/enumerate resources forks correctly. 
*/
#define NSFoundationVersionWithFileManagerResourceForkSupport 412

typedef NS_OPTIONS(NSUInteger, NSVolumeEnumerationOptions) {
    /* The mounted volume enumeration will skip hidden volumes.
     */
    NSVolumeEnumerationSkipHiddenVolumes = 1UL << 1,
    
    /* The mounted volume enumeration will produce file reference URLs rather than path-based URLs.
     */
    NSVolumeEnumerationProduceFileReferenceURLs = 1UL << 2
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSDirectoryEnumerationOptions) {
    /* NSDirectoryEnumerationSkipsSubdirectoryDescendants causes the NSDirectoryEnumerator to perform a shallow enumeration and not descend into directories it encounters.
     */
    NSDirectoryEnumerationSkipsSubdirectoryDescendants = 1UL << 0,
    
    /* NSDirectoryEnumerationSkipsPackageDescendants will cause the NSDirectoryEnumerator to not descend into packages.
     */
    NSDirectoryEnumerationSkipsPackageDescendants      = 1UL << 1,
    
    /* NSDirectoryEnumerationSkipsHiddenFiles causes the NSDirectoryEnumerator to not enumerate hidden files.
     */
    NSDirectoryEnumerationSkipsHiddenFiles             = 1UL << 2
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSFileManagerItemReplacementOptions) {
    /* NSFileManagerItemReplacementUsingNewMetadataOnly causes -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: to use metadata from the new item only and not to attempt to preserve metadata from the original item.
     */
    NSFileManagerItemReplacementUsingNewMetadataOnly = 1UL << 0,
    
    /* NSFileManagerItemReplacementWithoutDeletingBackupItem causes -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: to leave the backup item in place after a successful replacement. The default behavior is to remove the item.
     */
     NSFileManagerItemReplacementWithoutDeletingBackupItem = 1UL << 1
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_ENUM(NSInteger, NSURLRelationship) {
    NSURLRelationshipContains,
    NSURLRelationshipSame,
    NSURLRelationshipOther
} NS_ENUM_AVAILABLE(10_10, 8_0);

/* NSFileManagerUnmountOptions to pass to unmountVolumeAtURL:options:completionHandler: */
typedef NS_OPTIONS(NSUInteger, NSFileManagerUnmountOptions) {
    /* If the volume is on a partitioned disk, unmount all volumes on that disk. Then, eject the disk (if it is ejectable).
     */
    NSFileManagerUnmountAllPartitionsAndEjectDisk = 1UL << 0,
    
    /* Specifies that no UI should accompany the unmount operation. (Otherwise, the unmount UI, if needed, would delay completion of the completionHandler.)
     */
    NSFileManagerUnmountWithoutUI = 1UL << 1,
} NS_ENUM_AVAILABLE(10_11, NA);

/* If unmountVolumeAtURL:options:completionHandler: fails, the process identifier of the dissenter can be found in the  NSError's userInfo dictionary with this key */
FOUNDATION_EXPORT NSString *const NSFileManagerUnmountDissentingProcessIdentifierErrorKey NS_AVAILABLE(10_11, NA); // value is NSNumber containing the process identifier of the dissenter

/* Notification sent after the current ubiquity identity has changed.
*/
extern NSString * const NSUbiquityIdentityDidChangeNotification NS_AVAILABLE(10_8, 6_0);

@interface NSFileManager : NSObject

/* Returns the default singleton instance.
*/
+ (NSFileManager *)defaultManager;

/* -mountedVolumeURLsIncludingResourceValuesForKeys:options: returns an NSArray of NSURLs locating the mounted volumes available on the computer. The property keys that can be requested are available in <Foundation/NSURL.h>.
 */
- (nullable NSArray<NSURL *> *)mountedVolumeURLsIncludingResourceValuesForKeys:(nullable NSArray<NSString *> *)propertyKeys options:(NSVolumeEnumerationOptions)options NS_AVAILABLE(10_6, 4_0);

/* This method starts the process of unmounting the volume specified by url. If the volume is encrypted, it is re-locked after being unmounted. The completionHandler will be executed when the operation is complete. If the operation was successful, the block’s errorOrNil argument will be nil; otherwise, errorOrNil will be an error object indicating why the unmount operation failed.
 */
- (void)unmountVolumeAtURL:(NSURL *)url options:(NSFileManagerUnmountOptions)mask completionHandler:(void (^)(NSError * __nullable errorOrNil))completionHandler NS_AVAILABLE(10_11, NA);

/* -contentsOfDirectoryAtURL:includingPropertiesForKeys:options:error: returns an NSArray of NSURLs identifying the the directory entries. If this method returns nil, an NSError will be returned by reference in the 'error' parameter. If the directory contains no entries, this method will return the empty array. When an array is specified for the 'keys' parameter, the specified property values will be pre-fetched and cached with each enumerated URL.
 
    This method always does a shallow enumeration of the specified directory (i.e. it always acts as if NSDirectoryEnumerationSkipsSubdirectoryDescendants has been specified). If you need to perform a deep enumeration, use -[NSFileManager enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:].
 
    If you wish to only receive the URLs and no other attributes, then pass '0' for 'options' and an empty NSArray ('[NSArray array]') for 'keys'. If you wish to have the property caches of the vended URLs pre-populated with a default set of attributes, then pass '0' for 'options' and 'nil' for 'keys'.
 */
- (nullable NSArray<NSURL *> *)contentsOfDirectoryAtURL:(NSURL *)url includingPropertiesForKeys:(nullable NSArray<NSString *> *)keys options:(NSDirectoryEnumerationOptions)mask error:(NSError **)error NS_AVAILABLE(10_6, 4_0);


/* -URLsForDirectory:inDomains: is analogous to NSSearchPathForDirectoriesInDomains(), but returns an array of NSURL instances for use with URL-taking APIs. This API is suitable when you need to search for a file or files which may live in one of a variety of locations in the domains specified.
 */
- (NSArray<NSURL *> *)URLsForDirectory:(NSSearchPathDirectory)directory inDomains:(NSSearchPathDomainMask)domainMask NS_AVAILABLE(10_6, 4_0);

/* -URLForDirectory:inDomain:appropriateForURL:create:error: is a URL-based replacement for FSFindFolder(). It allows for the specification and (optional) creation of a specific directory for a particular purpose (e.g. the replacement of a particular item on disk, or a particular Library directory.
 
    You may pass only one of the values from the NSSearchPathDomainMask enumeration, and you may not pass NSAllDomainsMask.
 */
- (nullable NSURL *)URLForDirectory:(NSSearchPathDirectory)directory inDomain:(NSSearchPathDomainMask)domain appropriateForURL:(nullable NSURL *)url create:(BOOL)shouldCreate error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets 'outRelationship' to NSURLRelationshipContains if the directory at 'directoryURL' directly or indirectly contains the item at 'otherURL', meaning 'directoryURL' is found while enumerating parent URLs starting from 'otherURL'. Sets 'outRelationship' to NSURLRelationshipSame if 'directoryURL' and 'otherURL' locate the same item, meaning they have the same NSURLFileResourceIdentifierKey value. If 'directoryURL' is not a directory, or does not contain 'otherURL' and they do not locate the same file, then sets 'outRelationship' to NSURLRelationshipOther. If an error occurs, returns NO and sets 'error'.
 */
- (BOOL)getRelationship:(NSURLRelationship *)outRelationship ofDirectoryAtURL:(NSURL *)directoryURL toItemAtURL:(NSURL *)otherURL error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/* Similar to -[NSFileManager getRelationship:ofDirectoryAtURL:toItemAtURL:error:], except that the directory is instead defined by an NSSearchPathDirectory and NSSearchPathDomainMask. Pass 0 for domainMask to instruct the method to automatically choose the domain appropriate for 'url'. For example, to discover if a file is contained by a Trash directory, call [fileManager getRelationship:&result ofDirectory:NSTrashDirectory inDomain:0 toItemAtURL:url error:&error].
 */
- (BOOL)getRelationship:(NSURLRelationship *)outRelationship ofDirectory:(NSSearchPathDirectory)directory inDomain:(NSSearchPathDomainMask)domainMask toItemAtURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/* createDirectoryAtURL:withIntermediateDirectories:attributes:error: creates a directory at the specified URL. If you pass 'NO' for withIntermediateDirectories, the directory must not exist at the time this call is made. Passing 'YES' for withIntermediateDirectories will create any necessary intermediate directories. This method returns YES if all directories specified in 'url' were created and attributes were set. Directories are created with attributes specified by the dictionary passed to 'attributes'. If no dictionary is supplied, directories are created according to the umask of the process. This method returns NO if a failure occurs at any stage of the operation. If an error parameter was provided, a presentable NSError will be returned by reference.
 */
- (BOOL)createDirectoryAtURL:(NSURL *)url withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSString *, id> *)attributes error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* createSymbolicLinkAtURL:withDestinationURL:error: returns YES if the symbolic link that point at 'destURL' was able to be created at the location specified by 'url'. 'destURL' is always resolved against its base URL, if it has one. If 'destURL' has no base URL and it's 'relativePath' is indeed a relative path, then a relative symlink will be created. If this method returns NO, the link was unable to be created and an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 */
- (BOOL)createSymbolicLinkAtURL:(NSURL *)url withDestinationURL:(NSURL *)destURL error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* Instances of NSFileManager may now have delegates. Each instance has one delegate, and the delegate is not retained. In versions of Mac OS X prior to 10.5, the behavior of calling [[NSFileManager alloc] init] was undefined. In Mac OS X 10.5 "Leopard" and later, calling [[NSFileManager alloc] init] returns a new instance of an NSFileManager.
 */
@property (nullable, assign) id <NSFileManagerDelegate> delegate NS_AVAILABLE(10_5, 2_0);

/* setAttributes:ofItemAtPath:error: returns YES when the attributes specified in the 'attributes' dictionary are set successfully on the item specified by 'path'. If this method returns NO, a presentable NSError will be provided by-reference in the 'error' parameter. If no error is required, you may pass 'nil' for the error.
 
    This method replaces changeFileAttributes:atPath:.
 */
- (BOOL)setAttributes:(NSDictionary<NSString *, id> *)attributes ofItemAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* createDirectoryAtPath:withIntermediateDirectories:attributes:error: creates a directory at the specified path. If you pass 'NO' for createIntermediates, the directory must not exist at the time this call is made. Passing 'YES' for 'createIntermediates' will create any necessary intermediate directories. This method returns YES if all directories specified in 'path' were created and attributes were set. Directories are created with attributes specified by the dictionary passed to 'attributes'. If no dictionary is supplied, directories are created according to the umask of the process. This method returns NO if a failure occurs at any stage of the operation. If an error parameter was provided, a presentable NSError will be returned by reference.
 
    This method replaces createDirectoryAtPath:attributes:
 */
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSString *, id> *)attributes error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* contentsOfDirectoryAtPath:error: returns an NSArray of NSStrings representing the filenames of the items in the directory. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. If the directory contains no items, this method will return the empty array.
 
    This method replaces directoryContentsAtPath:
 */
- (nullable NSArray<NSString *> *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* subpathsOfDirectoryAtPath:error: returns an NSArray of NSStrings representing the filenames of the items in the specified directory and all its subdirectories recursively. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. If the directory contains no items, this method will return the empty array.
 
    This method replaces subpathsAtPath:
 */
- (nullable NSArray<NSString *> *)subpathsOfDirectoryAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* attributesOfItemAtPath:error: returns an NSDictionary of key/value pairs containing the attributes of the item (file, directory, symlink, etc.) at the path in question. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces fileAttributesAtPath:traverseLink:.
 */
- (nullable NSDictionary<NSString *, id> *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* attributesOfFileSystemForPath:error: returns an NSDictionary of key/value pairs containing the attributes of the filesystem containing the provided path. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces fileSystemAttributesAtPath:.
 */
- (nullable NSDictionary<NSString *, id> *)attributesOfFileSystemForPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* createSymbolicLinkAtPath:withDestination:error: returns YES if the symbolic link that point at 'destPath' was able to be created at the location specified by 'path'. If this method returns NO, the link was unable to be created and an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces createSymbolicLinkAtPath:pathContent:
 */
- (BOOL)createSymbolicLinkAtPath:(NSString *)path withDestinationPath:(NSString *)destPath error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* destinationOfSymbolicLinkAtPath:error: returns an NSString containing the path of the item pointed at by the symlink specified by 'path'. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter.
 
    This method replaces pathContentOfSymbolicLinkAtPath:
 */
- (nullable NSString *)destinationOfSymbolicLinkAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* These methods replace their non-error returning counterparts below. See the NSFileManagerDelegate protocol below for methods that are dispatched to the NSFileManager instance's delegate.
 */
- (BOOL)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)linkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* These methods are URL-taking equivalents of the four methods above. Their delegate methods are defined in the NSFileManagerDelegate protocol below.
 */
- (BOOL)copyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
- (BOOL)moveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
- (BOOL)linkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
- (BOOL)removeItemAtURL:(NSURL *)URL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* trashItemAtURL:resultingItemURL:error: returns YES if the item at 'url' was successfully moved to a Trash. Since the operation may require renaming the file to avoid collisions, it also returns by reference the resulting URL that the item was moved to. If this method returns NO, the item was not moved and an NSError will be returned by reference in the 'error' parameter.

    To easily discover if an item is in the Trash, you may use [fileManager getRelationship:&result ofDirectory:NSTrashDirectory inDomain:0 toItemAtURL:url error:&error] && result == NSURLRelationshipContains.
 */
- (BOOL)trashItemAtURL:(NSURL *)url resultingItemURL:(NSURL * __nullable * __nullable)outResultingURL error:(NSError **)error NS_AVAILABLE_MAC(10_8);

/* The following methods are deprecated on Mac OS X 10.5. Their URL-based and/or error-returning replacements are listed above.
 */
- (nullable NSDictionary *)fileAttributesAtPath:(NSString *)path traverseLink:(BOOL)yorn NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)changeFileAttributes:(NSDictionary *)attributes atPath:(NSString *)path NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (nullable NSArray *)directoryContentsAtPath:(NSString *)path NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (nullable NSDictionary *)fileSystemAttributesAtPath:(NSString *)path NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (nullable NSString *)pathContentOfSymbolicLinkAtPath:(NSString *)path NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)createSymbolicLinkAtPath:(NSString *)path pathContent:(NSString *)otherpath NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)createDirectoryAtPath:(NSString *)path attributes:(NSDictionary *)attributes NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
- (BOOL)linkPath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)copyPath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)movePath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (BOOL)removeFileAtPath:(NSString *)path handler:(nullable id)handler NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
#endif

/* Process working directory management. Despite the fact that these are instance methods on NSFileManager, these methods report and change (respectively) the working directory for the entire process. Developers are cautioned that doing so is fraught with peril.
 */
@property (readonly, copy) NSString *currentDirectoryPath;
- (BOOL)changeCurrentDirectoryPath:(NSString *)path;

/* The following methods are of limited utility. Attempting to predicate behavior based on the current state of the filesystem or a particular file on the filesystem is encouraging odd behavior in the face of filesystem race conditions. It's far better to attempt an operation (like loading a file or creating a directory) and handle the error gracefully than it is to try to figure out ahead of time whether the operation will succeed.
 */
- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(nullable BOOL *)isDirectory;
- (BOOL)isReadableFileAtPath:(NSString *)path;
- (BOOL)isWritableFileAtPath:(NSString *)path;
- (BOOL)isExecutableFileAtPath:(NSString *)path;
- (BOOL)isDeletableFileAtPath:(NSString *)path;

/* -contentsEqualAtPath:andPath: does not take into account data stored in the resource fork or filesystem extended attributes.
 */
- (BOOL)contentsEqualAtPath:(NSString *)path1 andPath:(NSString *)path2;

/* displayNameAtPath: returns an NSString suitable for presentation to the user. For directories which have localization information, this will return the appropriate localized string. This string is not suitable for passing to anything that must interact with the filesystem.
 */
- (NSString *)displayNameAtPath:(NSString *)path;

/* componentsToDisplayForPath: returns an NSArray of display names for the path provided. Localization will occur as in displayNameAtPath: above. This array cannot and should not be reassembled into an usable filesystem path for any kind of access.
 */
- (nullable NSArray<NSString *> *)componentsToDisplayForPath:(NSString *)path;

/* enumeratorAtPath: returns an NSDirectoryEnumerator rooted at the provided path. If the enumerator cannot be created, this returns NULL. Because NSDirectoryEnumerator is a subclass of NSEnumerator, the returned object can be used in the for...in construct.
 */
- (nullable NSDirectoryEnumerator<NSString *> *)enumeratorAtPath:(NSString *)path;

/* enumeratorAtURL:includingPropertiesForKeys:options:errorHandler: returns an NSDirectoryEnumerator rooted at the provided directory URL. The NSDirectoryEnumerator returns NSURLs from the -nextObject method. The optional 'includingPropertiesForKeys' parameter indicates which resource properties should be pre-fetched and cached with each enumerated URL. The optional 'errorHandler' block argument is invoked when an error occurs. Parameters to the block are the URL on which an error occurred and the error. When the error handler returns YES, enumeration continues if possible. Enumeration stops immediately when the error handler returns NO.

    If you wish to only receive the URLs and no other attributes, then pass '0' for 'options' and an empty NSArray ('[NSArray array]') for 'keys'. If you wish to have the property caches of the vended URLs pre-populated with a default set of attributes, then pass '0' for 'options' and 'nil' for 'keys'.
 */
- (nullable NSDirectoryEnumerator<NSURL *> *)enumeratorAtURL:(NSURL *)url includingPropertiesForKeys:(nullable NSArray<NSString *> *)keys options:(NSDirectoryEnumerationOptions)mask errorHandler:(nullable BOOL (^)(NSURL *url, NSError *error))handler NS_AVAILABLE(10_6, 4_0);

/* subpathsAtPath: returns an NSArray of all contents and subpaths recursively from the provided path. This may be very expensive to compute for deep filesystem hierarchies, and should probably be avoided.
 */
- (nullable NSArray<NSString *> *)subpathsAtPath:(NSString *)path;

/* These methods are provided here for compatibility. The corresponding methods on NSData which return NSErrors should be regarded as the primary method of creating a file from an NSData or retrieving the contents of a file as an NSData.
 */
- (nullable NSData *)contentsAtPath:(NSString *)path;
- (BOOL)createFileAtPath:(NSString *)path contents:(nullable NSData *)data attributes:(nullable NSDictionary<NSString *, id> *)attr;

/* fileSystemRepresentationWithPath: returns an array of characters suitable for passing to lower-level POSIX style APIs. The string is provided in the representation most appropriate for the filesystem in question.
 */
- (__strong const char *)fileSystemRepresentationWithPath:(NSString *)path NS_RETURNS_INNER_POINTER;

/* stringWithFileSystemRepresentation:length: returns an NSString created from an array of bytes that are in the filesystem representation.
 */
- (NSString *)stringWithFileSystemRepresentation:(const char *)str length:(NSUInteger)len;

/* -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is for developers who wish to perform a safe-save without using the full NSDocument machinery that is available in the AppKit.
 
    The `originalItemURL` is the item being replaced.
    `newItemURL` is the item which will replace the original item. This item should be placed in a temporary directory as provided by the OS, or in a uniquely named directory placed in the same directory as the original item if the temporary directory is not available.
    If `backupItemName` is provided, that name will be used to create a backup of the original item. The backup is placed in the same directory as the original item. If an error occurs during the creation of the backup item, the operation will fail. If there is already an item with the same name as the backup item, that item will be removed. The backup item will be removed in the event of success unless the `NSFileManagerItemReplacementWithoutDeletingBackupItem` option is provided in `options`.
    For `options`, pass `0` to get the default behavior, which uses only the metadata from the new item while adjusting some properties using values from the original item. Pass `NSFileManagerItemReplacementUsingNewMetadataOnly` in order to use all possible metadata from the new item.
 */
- (BOOL)replaceItemAtURL:(NSURL *)originalItemURL withItemAtURL:(NSURL *)newItemURL backupItemName:(nullable NSString *)backupItemName options:(NSFileManagerItemReplacementOptions)options resultingItemURL:(NSURL * __nullable * __nullable)resultingURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);


/* Changes whether the item for the specified URL is ubiquitous and moves the item to the destination URL. When making an item ubiquitous, the destination URL must be prefixed with a URL from -URLForUbiquityContainerIdentifier:. Returns YES if the change is successful, NO otherwise.
 */
- (BOOL)setUbiquitous:(BOOL)flag itemAtURL:(NSURL *)url destinationURL:(NSURL *)destinationURL error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* Returns YES if the item for the specified URL is ubiquitous, NO otherwise.
 */
- (BOOL)isUbiquitousItemAtURL:(NSURL *)url NS_AVAILABLE(10_7, 5_0);

/* Start downloading a local instance of the specified ubiquitous item, if necessary. Returns YES if the download started successfully or wasn't necessary, NO otherwise.
 */
- (BOOL)startDownloadingUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* Removes the local instance of the ubiquitous item at the given URL. Returns YES if removal was successful, NO otherwise.
 */
- (BOOL)evictUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* Returns a file URL for the root of the ubiquity container directory corresponding to the supplied container ID. Returns nil if the mobile container does not exist or could not be determined.
 */
- (nullable NSURL *)URLForUbiquityContainerIdentifier:(nullable NSString *)containerIdentifier NS_AVAILABLE(10_7, 5_0);

/* Returns a URL that can be shared with other users to allow them download a copy of the specified ubiquitous item. Also returns the date after which the item will no longer be accessible at the returned URL. The URL must be prefixed with a URL from -URLForUbiquityContainerIdentifier:.
 */
- (nullable NSURL *)URLForPublishingUbiquitousItemAtURL:(NSURL *)url expirationDate:(NSDate * __nullable * __nullable)outDate error:(NSError **)error NS_AVAILABLE(10_7, 5_0);

/* Returns an opaque token that represents the current ubiquity identity. This object can be copied, encoded, or compared with isEqual:. When ubiquity containers are unavailable because the user has disabled them, or when the user is simply not logged in, this method will return nil. The NSUbiquityIdentityDidChangeNotification notification is posted after this value changes.

    If you don't need the container URL and just want to check if ubiquity containers are available you should use this method instead of checking -URLForUbiquityContainerIdentifier:.
*/
@property (nullable, readonly, copy) id<NSObject,NSCopying,NSCoding> ubiquityIdentityToken NS_AVAILABLE(10_8, 6_0);

/* Returns the container directory associated with the specified security application group ID.
 */
- (nullable NSURL *)containerURLForSecurityApplicationGroupIdentifier:(NSString *)groupIdentifier NS_AVAILABLE(10_8, 7_0); // Available for OS X in 10.8.3.


@end

/* These delegate methods are for the use of the deprecated handler-taking methods on NSFileManager for copying, moving, linking or deleting files.
 */
@interface NSObject (NSCopyLinkMoveHandler)
- (BOOL)fileManager:(NSFileManager *)fm shouldProceedAfterError:(NSDictionary *)errorInfo NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
- (void)fileManager:(NSFileManager *)fm willProcessPath:(NSString *)path NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
@end


@protocol NSFileManagerDelegate <NSObject>
@optional

/* fileManager:shouldCopyItemAtPath:toPath: gives the delegate an opportunity to filter the resulting copy. Returning YES from this method will allow the copy to happen. Returning NO from this method causes the item in question to be skipped. If the item skipped was a directory, no children of that directory will be copied, nor will the delegate be notified of those children.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldProceedAfterError:copyingItemAtPath:toPath: gives the delegate an opportunity to recover from or continue copying after an error. If an error occurs, the error object will contain an NSError indicating the problem. The source path and destination paths are also provided. If this method returns YES, the NSFileManager instance will continue as if the error had not occurred. If this method returns NO, the NSFileManager instance will stop copying, return NO from copyItemAtPath:toPath:error: and the error will be provied there.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldMoveItemAtPath:toPath: gives the delegate an opportunity to not move the item at the specified path. If the source path and the destination path are not on the same device, a copy is performed to the destination path and the original is removed. If the copy does not succeed, an error is returned and the incomplete copy is removed, leaving the original in place.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldProceedAfterError:movingItemAtPath:toPath: functions much like fileManager:shouldProceedAfterError:copyingItemAtPath:toPath: above. The delegate has the opportunity to remedy the error condition and allow the move to continue.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldLinkItemAtPath:toPath: acts as the other "should" methods, but this applies to the file manager creating hard links to the files in question.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldProceedAfterError:linkingItemAtPath:toPath: allows the delegate an opportunity to remedy the error which occurred in linking srcPath to dstPath. If the delegate returns YES from this method, the linking will continue. If the delegate returns NO from this method, the linking operation will stop and the error will be returned via linkItemAtPath:toPath:error:.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldRemoveItemAtPath: allows the delegate the opportunity to not remove the item at path. If the delegate returns YES from this method, the NSFileManager instance will attempt to remove the item. If the delegate returns NO from this method, the remove skips the item. If the item is a directory, no children of that item will be visited.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtPath:(NSString *)path;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtURL:(NSURL *)URL NS_AVAILABLE(10_6, 4_0);

/* fileManager:shouldProceedAfterError:removingItemAtPath: allows the delegate an opportunity to remedy the error which occurred in removing the item at the path provided. If the delegate returns YES from this method, the removal operation will continue. If the delegate returns NO from this method, the removal operation will stop and the error will be returned via linkItemAtPath:toPath:error:.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtPath:(NSString *)path;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtURL:(NSURL *)URL NS_AVAILABLE(10_6, 4_0);

@end


@interface NSDirectoryEnumerator<ObjectType> : NSEnumerator<ObjectType>

/* For NSDirectoryEnumerators created with -enumeratorAtPath:, the -fileAttributes and -directoryAttributes methods return an NSDictionary containing the keys listed below. For NSDirectoryEnumerators created with -enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:, these two methods return nil.
 */
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *fileAttributes;
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *directoryAttributes;

- (void)skipDescendents;

/* This method returns the number of levels deep the current object is in the directory hierarchy being enumerated. The directory passed to -enumeratorAtURL:includingPropertiesForKeys:options:errorHandler: is considered to be level 0.
 */
@property (readonly) NSUInteger level NS_AVAILABLE(10_6, 4_0);

/* This method is spelled correctly.
 */
- (void)skipDescendants NS_AVAILABLE(10_6, 4_0);

@end

FOUNDATION_EXPORT NSString * const NSFileType;
FOUNDATION_EXPORT NSString * const NSFileTypeDirectory;
FOUNDATION_EXPORT NSString * const NSFileTypeRegular;
FOUNDATION_EXPORT NSString * const NSFileTypeSymbolicLink;
FOUNDATION_EXPORT NSString * const NSFileTypeSocket;
FOUNDATION_EXPORT NSString * const NSFileTypeCharacterSpecial;
FOUNDATION_EXPORT NSString * const NSFileTypeBlockSpecial;
FOUNDATION_EXPORT NSString * const NSFileTypeUnknown;
FOUNDATION_EXPORT NSString * const NSFileSize;
FOUNDATION_EXPORT NSString * const NSFileModificationDate;
FOUNDATION_EXPORT NSString * const NSFileReferenceCount;
FOUNDATION_EXPORT NSString * const NSFileDeviceIdentifier;
FOUNDATION_EXPORT NSString * const NSFileOwnerAccountName;
FOUNDATION_EXPORT NSString * const NSFileGroupOwnerAccountName;
FOUNDATION_EXPORT NSString * const NSFilePosixPermissions;
FOUNDATION_EXPORT NSString * const NSFileSystemNumber;
FOUNDATION_EXPORT NSString * const NSFileSystemFileNumber;
FOUNDATION_EXPORT NSString * const NSFileExtensionHidden;
FOUNDATION_EXPORT NSString * const NSFileHFSCreatorCode;
FOUNDATION_EXPORT NSString * const NSFileHFSTypeCode;
FOUNDATION_EXPORT NSString * const NSFileImmutable;
FOUNDATION_EXPORT NSString * const NSFileAppendOnly;
FOUNDATION_EXPORT NSString * const NSFileCreationDate;
FOUNDATION_EXPORT NSString * const NSFileOwnerAccountID;
FOUNDATION_EXPORT NSString * const NSFileGroupOwnerAccountID;
FOUNDATION_EXPORT NSString * const NSFileBusy;
FOUNDATION_EXPORT NSString * const NSFileProtectionKey NS_AVAILABLE_IOS(4_0);
FOUNDATION_EXPORT NSString * const NSFileProtectionNone NS_AVAILABLE_IOS(4_0);
FOUNDATION_EXPORT NSString * const NSFileProtectionComplete NS_AVAILABLE_IOS(4_0);
FOUNDATION_EXPORT NSString * const NSFileProtectionCompleteUnlessOpen NS_AVAILABLE_IOS(5_0);
FOUNDATION_EXPORT NSString * const NSFileProtectionCompleteUntilFirstUserAuthentication NS_AVAILABLE_IOS(5_0);

FOUNDATION_EXPORT NSString * const NSFileSystemSize;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeSize;
FOUNDATION_EXPORT NSString * const NSFileSystemNodes;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeNodes;

@interface NSDictionary<KeyType, ObjectType> (NSFileAttributes)

- (unsigned long long)fileSize;
- (nullable NSDate *)fileModificationDate;
- (nullable NSString *)fileType;
- (NSUInteger)filePosixPermissions;
- (nullable NSString *)fileOwnerAccountName;
- (nullable NSString *)fileGroupOwnerAccountName;
- (NSInteger)fileSystemNumber;
- (NSUInteger)fileSystemFileNumber;
- (BOOL)fileExtensionHidden;
- (OSType)fileHFSCreatorCode;
- (OSType)fileHFSTypeCode;
- (BOOL)fileIsImmutable;
- (BOOL)fileIsAppendOnly;
- (nullable NSDate *)fileCreationDate;
- (nullable NSNumber *)fileOwnerAccountID;
- (nullable NSNumber *)fileGroupOwnerAccountID;
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSPersonNameComponentsFormatter.h
/*	NSPersonNameComponentsFormatter.h
	Copyright (c) 2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSPersonNameComponents.h>
#import <Foundation/NSFormatter.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSPersonNameComponentsFormatterStyle) {
    NSPersonNameComponentsFormatterStyleDefault = 0,

    /* Relies on user preferences and language defaults to display shortened form appropriate
      for display in space-constrained settings, e.g. C Darwin */
    NSPersonNameComponentsFormatterStyleShort,

    /* The minimally necessary features for differentiation in a casual setting , e.g. Charles Darwin */
    NSPersonNameComponentsFormatterStyleMedium,

    /* The fully-qualified name complete with all known components, e.g. Charles Robert Darwin, FRS */
    NSPersonNameComponentsFormatterStyleLong,

    /* The maximally-abbreviated form of a name suitable for monograms, e.g. CRD) */
    NSPersonNameComponentsFormatterStyleAbbreviated
} NS_ENUM_AVAILABLE(10_11, 9_0);

typedef NS_OPTIONS (NSUInteger, NSPersonNameComponentsFormatterOptions) {
    /* Indicates that the formatter should format the component object's phoneticRepresentation components instead of its own components.
     The developer must have populated these manually. e.g.: Developer creates components object with the following properties:
     <family:"Family", given:"Given", phoneticRepresentation:<family:"FamilyPhonetic", given:"GivenPhonetic">>.
     If this option is specified, we perform formatting operations on <family "FamilyPhonetic", given "GivenPhonetic"> instead. */
    NSPersonNameComponentsFormatterPhonetic = (1UL << 1)
} NS_ENUM_AVAILABLE(10_11, 9_0);


NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSPersonNameComponentsFormatter : NSFormatter {
@private
    id _private;
}

/* Specify the formatting style for the formatted string on an instance. ShortStyle will fall back to user preferences and language-specific defaults
 */
@property NSPersonNameComponentsFormatterStyle style;

/* Specify that the formatter should only format the components object's phoneticRepresentation
 */
@property (getter=isPhonetic) BOOL phonetic;

/* Shortcut for converting an NSPersonNameComponents object into a string without explicitly creating an instance.
    Create an instance for greater customizability.
 */
+ (NSString *)localizedStringFromPersonNameComponents:(NSPersonNameComponents *)components
                                                style:(NSPersonNameComponentsFormatterStyle)nameFormatStyle
                                              options:(NSPersonNameComponentsFormatterOptions)nameOptions;

/* Convenience method on stringForObjectValue:. Returns a string containing the formatted value of the provided components object.
 */
- (NSString *)stringFromPersonNameComponents:(NSPersonNameComponents *)components;

/* Returns attributed string with annotations for each component. For each range, attributes can be obtained by querying
    dictionary key NSPersonNameComponentKey , using NSPersonNameComponent constant values.
 */
- (NSAttributedString *)annotatedStringFromPersonNameComponents:(NSPersonNameComponents *)components;

/* NSPersonNameComponentsFormatter currently only implements formatting, not parsing. Until it implements parsing, this will always return NO.
 */
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;

@end

// Attributed String identifier key string
FOUNDATION_EXPORT NSString * const NSPersonNameComponentKey NS_AVAILABLE(10_11, 9_0);

// Constants for attributed strings
FOUNDATION_EXPORT NSString * const NSPersonNameComponentGivenName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentFamilyName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentMiddleName NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentPrefix NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentSuffix NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSPersonNameComponentNickname NS_AVAILABLE(10_11, 9_0);

/* The delimiter is the character or characters used to separate name components.
 For CJK languages there is no delimiter.
 */
FOUNDATION_EXPORT NSString * const NSPersonNameComponentDelimiter NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSBundle.h
/*	NSBundle.h
	Copyright (c) 1994-2015, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSProgress.h>

@class NSString, NSURL, NSError, NSUUID, NSLock, NSNumber;

NS_ASSUME_NONNULL_BEGIN

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    NSUInteger		_flags;
    id		        _cfBundle;
    NSUInteger		_reserved2;
    Class		_principalClass;
    id                  _initialPath;
    id                  _resolvedPath;
    id                  _reserved3;
    id                  _lock;
}

/* Methods for creating or retrieving bundle instances. */
+ (NSBundle *)mainBundle;
+ (nullable instancetype)bundleWithPath:(NSString *)path;
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

+ (nullable instancetype)bundleWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
- (nullable instancetype)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);

+ (NSBundle *)bundleForClass:(Class)aClass;
+ (nullable NSBundle *)bundleWithIdentifier:(NSString *)identifier;

+ (NSArray<NSBundle *> *)allBundles;
+ (NSArray<NSBundle *> *)allFrameworks;

/* Methods for loading and unloading bundles. */
- (BOOL)load;
@property (readonly, getter=isLoaded) BOOL loaded;
- (BOOL)unload;

- (BOOL)preflightAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)loadAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* Methods for locating various components of a bundle. */
@property (readonly, copy) NSURL *bundleURL NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *resourceURL NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *executableURL NS_AVAILABLE(10_6, 4_0);
- (nullable NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName NS_AVAILABLE(10_6, 4_0);

@property (nullable, readonly, copy) NSURL *privateFrameworksURL NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *sharedFrameworksURL NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *sharedSupportURL NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *builtInPlugInsURL NS_AVAILABLE(10_6, 4_0);

@property (nullable, readonly, copy) NSURL *appStoreReceiptURL NS_AVAILABLE(10_7, 7_0);

@property (readonly, copy) NSString *bundlePath;
@property (nullable, readonly, copy) NSString *resourcePath;
@property (nullable, readonly, copy) NSString *executablePath;
- (nullable NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;

@property (nullable, readonly, copy) NSString *privateFrameworksPath;
@property (nullable, readonly, copy) NSString *sharedFrameworksPath;
@property (nullable, readonly, copy) NSString *sharedSupportPath;
@property (nullable, readonly, copy) NSString *builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */

+ (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
+ (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);

- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext NS_AVAILABLE(10_6, 4_0);
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

+ (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;
+ (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;

- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext;
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;
- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

/* Method for retrieving localized strings. */
- (NSString *)localizedStringForKey:(NSString *)key value:(nullable NSString *)value table:(nullable NSString *)tableName NS_FORMAT_ARGUMENT(1);

/* Methods for obtaining various information about a bundle. */
@property (nullable, readonly, copy) NSString *bundleIdentifier;
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *infoDictionary;
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *localizedInfoDictionary;
- (nullable id)objectForInfoDictionaryKey:(NSString *)key;
- (nullable Class)classNamed:(NSString *)className;
@property (nullable, readonly) Class principalClass;

/* Methods for dealing with localizations. */
@property (readonly, copy) NSArray<NSString *> *preferredLocalizations;	// a subset of this bundle's localizations, re-ordered into the preferred order for this process's current execution environment; the main bundle's preferred localizations indicate the language (of text) the user is most likely seeing in the UI

@property (readonly, copy) NSArray<NSString *> *localizations;		// list of language names this bundle appears to be localized to
@property (nullable, readonly, copy) NSString *developmentLocalization;

+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray;
+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray forPreferences:(nullable NSArray<NSString *> *)preferencesArray;

/* Method for determining executable architectures. */
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};

@property (nullable, readonly, copy) NSArray<NSNumber *> *executableArchitectures NS_AVAILABLE(10_5, 2_0);

@end

#define NSLocalizedString(key, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

@interface NSString (NSBundleExtensionMethods)

/* For strings with length variations, such as from a stringsdict file, this method returns the variant at the given width. If there is no variant at the given width, the one for the next smaller width is returned. And if there are none smaller, the smallest available is returned. For strings without variations, this method returns self. The unit that width is expressed in is decided by the application or framework. But it is intended to be some measurement indicative of the context a string would fit best to avoid truncation and wasted space.
*/ 
- (NSString *)variantFittingPresentationWidth:(NSInteger)width NS_AVAILABLE(10_11, 9_0);

@end

FOUNDATION_EXPORT NSString * const NSBundleDidLoadNotification;
FOUNDATION_EXPORT NSString * const NSLoadedClasses;	// notification key


/*
 The NSBundleResourceRequest class is used to interact with the on demand resource loading system.
 
 The purpose of the system is to allow an application to download certain resources on demand, when they are required. This also means that the system can purge a resource from disk when it is no longer required, which will save disk space. This class describes which resources are required, makes the request and reports progress, allows the app to specify how long during its execution that they are required.
 
 Resources are downloaded into the application container, and are made available via the standard NSBundle resource lookup API.
 
 The request object itself is lightweight. You may create as many as you need, for example to request the same set of tags in different components of your application.
*/
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NSBundleResourceRequest : NSObject <NSProgressReporting>

- (instancetype)init NS_UNAVAILABLE;

/*
 A tag and bundle are required arguments to the init methods. The tag argument is required and it must exist in the manifest of the specified bundle. The bundle argument describes an existing bundle which was built with on demand resources support. Any resources downloaded can be found using the standard NSBundle resource lookup API once the request is completed. If no bundle is specified then the main bundle is used.
 */
- (instancetype)initWithTags:(NSSet<NSString *> *)tags;
- (instancetype)initWithTags:(NSSet<NSString *> *)tags bundle:(NSBundle *)bundle NS_DESIGNATED_INITIALIZER;

/*
 Provides a hint to the resource loading system as to the loading priority of this request. Values are limited to between 0 and 1, with 1 being the highest priority. The default priority is 0.5.
 
 The exact meaning of the value is up to your application. The system will prefer to act on requests that have a higher priority (from the same application). You may change the priority at any time, even after a request has started. The system will make a best attempt to take the new priority into account.
 */
@property double loadingPriority;

/*
 The tags this request will load.
 */
@property (readonly, copy) NSSet<NSString *> *tags;

/*
 The bundle object that will hold the requested resources. After the -beginAccessingResourcesWithCompletionHandler: callback is invoked, you may use the standard bundle lookup APIs on this bundle object to find your resources.
 */
@property (readonly, strong) NSBundle *bundle;

/*
 Ask the system to fetch the resources that were part of the tag set in this request. Resources will not be purged while in use by the application (as indicated by the application using this begin API paired with a call to -endAccessingResources). If an application has too many fetched resources and the system is unable to reserve enough space for newly requested tags, the request may return an error.
 
 When you are finished with the resources and they may be purged off the disk, invoke -endAccessingResources. If the request object is deallocated, it will also inform the system that the resources are no longer in use.
 
 The completion block will be invoked on a non-main serial queue when the resources are available or an error has occurred. An example of a possible error that may be reported is the lack of a network connection or a problem connecting to the on-demand servers.
 
 Fetch requests are reference counted across the application. So if you have two requests outstanding with the same set of tags, each may be used independently without having to know about any global state. However, each NSBundleResourceRequest object may only be used once.
 
 If you cancel an outstanding request (via the cancel method on the NSProgress object, or cancelling a parent progress object you have created) the completion handler argument to this method will be called back with an NSUserCancelledError in the NSCocoaErrorDomain.
 
 Be sure to always invoke the -endAccessingResources method to balance a call to the begin method, even in the case of an error in the completion handler.
 
 If you want to access the resources again, create a new NSBundleResourceRequest object.
 */
- (void)beginAccessingResourcesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*
 Inform the system that you wish to begin accessing the resources that are part of this request, but do not attempt to download any content over the network. The completion handler will be invoked with a YES argument if the resources are available.
 
 If the resources were available, then you must invoke the -endAccessingResources method once you are done accessing them. If the resources were not available, then you may invoke the -beginAccessingResourcesWithCompletionHandler: method to initiate a download of the resources.
*/
- (void)conditionallyBeginAccessingResourcesWithCompletionHandler:(void (^)(BOOL resourcesAvailable))completionHandler;

/*
 Informs the system that you are finished with the resources that were part of the tag set in this request. Call this after you no longer need the resources to be available on disk. It is important to invoke this method to make room for newly requested resources. This method may only be invoked if you have received a callback from -beginAccessingResourcesWithCompletionHandler:. To cancel an in-progress request, invoke cancel on the -progress property.
 */
- (void)endAccessingResources;

/*
 Progress for the request. The progress object will be valid at initialization and begin updating after the -beginAccessingResourcesWithCompletionHandler: method is called.
*/
@property (readonly, strong) NSProgress *progress;

@end

@interface NSBundle (NSBundleResourceRequestAdditions)

/* Set a preservation priority for tags that are included in this bundle for the On Demand Resources system. Preservation priorities may be between 0.0 and 1.0, with higher values being the last choice for purging by the system. The exact meaning of this value is up to your application as it only has meaning within the set of tags your application uses.
   
   The default value is 0.0.
 
   This method will throw an exception if the receiver bundle has no on demand resource tag information.
*/
- (void)setPreservationPriority:(double)priority forTags:(NSSet<NSString *> *)tags NS_AVAILABLE(NA, 9_0);
- (double)preservationPriorityForTag:(NSString *)tag NS_AVAILABLE(NA, 9_0);

@end

/*
 This notification is posted to the default notification center when the resource request system detects a low disk space condition.
 
 If the application is in the background, the system needs more space, and the application does not free up enough in response to the notification then the application may be killed. The application can free up space by calling -endAccessingResources on any outstanding requests. This will inform the system that you are done with those resources and it may purge the content to make room for a new request.
 
 Note that this notification may not be the same as low disk space on the system, as applications can have a smaller quota.
 */
FOUNDATION_EXPORT NSString * const NSBundleResourceRequestLowDiskSpaceNotification NS_AVAILABLE(NA, 9_0);

/* Use this value for the loadingPriority property if the user is doing nothing but waiting on the result of this request. The system will dedicate the maximum amount of resources available to finishing this request as soon as possible.
 */
FOUNDATION_EXPORT double const NSBundleResourceRequestLoadingPriorityUrgent NS_AVAILABLE(NA, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSIndexSet.h
/*	NSIndexSet.h
	Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

/* Class for managing set of indexes. The set of valid indexes are 0 .. NSNotFound - 1; trying to use indexes outside this range is an error.  NSIndexSet uses NSNotFound as a return value in cases where the queried index doesn't exist in the set; for instance, when you ask firstIndex and there are no indexes; or when you ask for indexGreaterThanIndex: on the last index, and so on.

The following code snippets can be used to enumerate over the indexes in an NSIndexSet:

    // Forward
    NSUInteger currentIndex = [set firstIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexGreaterThanIndex:currentIndex];
    }
    
    // Backward
    NSUInteger currentIndex = [set lastIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexLessThanIndex:currentIndex];
    }

To enumerate without doing a call per index, you can use the method getIndexes:maxCount:inIndexRange:.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSIndexSet : NSObject <NSCopying, NSMutableCopying, NSSecureCoding> {
    @protected   // all instance variables are private
    struct {
        NSUInteger _isEmpty:1;
        NSUInteger _hasSingleRange:1;
        NSUInteger _cacheValid:1;
        NSUInteger _reservedArrayBinderController:29;
    } _indexSetFlags;
    union {
        struct {
            NSRange _range;
        } _singleRange;
        struct {
            void *  __strong _data;
            void *_reserved;
        } _multipleRanges;
    } _internal;
}

+ (instancetype)indexSet;
+ (instancetype)indexSetWithIndex:(NSUInteger)value;
+ (instancetype)indexSetWithIndexesInRange:(NSRange)range;

- (instancetype)initWithIndexesInRange:(NSRange)range NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithIndexSet:(NSIndexSet *)indexSet NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIndex:(NSUInteger)value;

- (BOOL)isEqualToIndexSet:(NSIndexSet *)indexSet;

@property (readonly) NSUInteger count;

/* The following six methods will return NSNotFound if there is no index in the set satisfying the query. 
*/
@property (readonly) NSUInteger firstIndex;
@property (readonly) NSUInteger lastIndex;
- (NSUInteger)indexGreaterThanIndex:(NSUInteger)value;
- (NSUInteger)indexLessThanIndex:(NSUInteger)value;
- (NSUInteger)indexGreaterThanOrEqualToIndex:(NSUInteger)value;
- (NSUInteger)indexLessThanOrEqualToIndex:(NSUInteger)value;

/* Fills up to bufferSize indexes in the specified range into the buffer and returns the number of indexes actually placed in the buffer; also modifies the optional range passed in by pointer to be "positioned" after the last index filled into the buffer.Example: if the index set contains the indexes 0, 2, 4, ..., 98, 100, for a buffer of size 10 and the range (20, 80) the buffer would contain 20, 22, ..., 38 and the range would be modified to (40, 60).
*/
- (NSUInteger)getIndexes:(NSUInteger *)indexBuffer maxCount:(NSUInteger)bufferSize inIndexRange:(nullable NSRangePointer)range;

- (NSUInteger)countOfIndexesInRange:(NSRange)range NS_AVAILABLE(10_5, 2_0);

- (BOOL)containsIndex:(NSUInteger)value;
- (BOOL)containsIndexesInRange:(NSRange)range;
- (BOOL)containsIndexes:(NSIndexSet *)indexSet;

- (BOOL)intersectsIndexesInRange:(NSRange)range;

- (void)enumerateIndexesUsingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateIndexesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateIndexesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSUInteger)indexPassingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

- (NSIndexSet *)indexesPassingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

/*
 The following three convenience methods allow you to enumerate the indexes in the receiver by ranges of contiguous indexes. The performance of these methods is not guaranteed to be any better than if they were implemented with enumerateIndexesInRange:options:usingBlock:. However, depending on the receiver's implementation, they may perform better than that.
 
 If the specified range for enumeration intersects a range of contiguous indexes in the receiver, then the block will be invoked with the intersection of those two ranges.
*/
- (void)enumerateRangesUsingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
- (void)enumerateRangesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
- (void)enumerateRangesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);

@end

@interface NSMutableIndexSet : NSIndexSet {
    @protected
    void *_reserved;
}

- (void)addIndexes:(NSIndexSet *)indexSet;
- (void)removeIndexes:(NSIndexSet *)indexSet;
- (void)removeAllIndexes;
- (void)addIndex:(NSUInteger)value;
- (void)removeIndex:(NSUInteger)value;
- (void)addIndexesInRange:(NSRange)range;
- (void)removeIndexesInRange:(NSRange)range;

/* For a positive delta, shifts the indexes in [index, INT_MAX] to the right, thereby inserting an "empty space" [index, delta], for a negative delta, shifts the indexes in [index, INT_MAX] to the left, thereby deleting the indexes in the range [index - delta, delta].
*/
- (void)shiftIndexesStartingAtIndex:(NSUInteger)index by:(NSInteger)delta;   

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSUUID.h
/*	NSUUID.h
        Copyright (c) 2011-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <CoreFoundation/CFUUID.h>
#include <uuid/uuid.h>

/* Note: NSUUID is not toll-free bridged with CFUUID. Use UUID strings to convert between CFUUID and NSUUID, if needed. NSUUIDs are not guaranteed to be comparable by pointer value (as CFUUIDRef is); use isEqual: to compare two NSUUIDs. */

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSUUID : NSObject <NSCopying, NSSecureCoding>

/* Create a new autoreleased NSUUID with RFC 4122 version 4 random bytes */
+ (instancetype)UUID;

/* Create a new NSUUID with RFC 4122 version 4 random bytes */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/* Create an NSUUID from a string such as "E621E1F8-C36C-495A-93FC-0C247A3E6E5F". Returns nil for invalid strings. */
- (nullable instancetype)initWithUUIDString:(NSString *)string;

/* Create an NSUUID with the given bytes */
- (instancetype)initWithUUIDBytes:(const uuid_t)bytes;

/* Get the individual bytes of the receiver */
- (void)getUUIDBytes:(uuid_t)uuid;

/* Return a string description of the UUID, such as "E621E1F8-C36C-495A-93FC-0C247A3E6E5F" */
@property (readonly, copy) NSString *UUIDString;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSUbiquitousKeyValueStore.h
/*	NSUbiquitousKeyValueStore.h
	Copyright (c) 2011-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary<KeyType, ObjectType>, NSData, NSString;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSUbiquitousKeyValueStore : NSObject {
@private
    id _private1;
    id _private2;
    id _private3;
    void *_private4;
    void *_reserved[3];
    int _daemonWakeToken;
#if DEPLOYMENT_TARGET_MACOSX
    BOOL _disabledSuddenTermination;
#endif
}

+ (NSUbiquitousKeyValueStore *)defaultStore;

- (nullable id)objectForKey:(NSString *)aKey;
- (void)setObject:(nullable id)anObject forKey:(NSString *)aKey;
- (void)removeObjectForKey:(NSString *)aKey;

- (nullable NSString *)stringForKey:(NSString *)aKey;
- (nullable NSArray *)arrayForKey:(NSString *)aKey;
- (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)aKey;
- (nullable NSData *)dataForKey:(NSString *)aKey;
- (long long)longLongForKey:(NSString *)aKey;
- (double)doubleForKey:(NSString *)aKey;
- (BOOL)boolForKey:(NSString *)aKey;

- (void)setString:(nullable NSString *)aString forKey:(NSString *)aKey;
- (void)setData:(nullable NSData *)aData forKey:(NSString *)aKey;
- (void)setArray:(nullable NSArray *)anArray forKey:(NSString *)aKey;
- (void)setDictionary:(nullable NSDictionary<NSString *, id> *)aDictionary forKey:(NSString *)aKey;
- (void)setLongLong:(long long)value forKey:(NSString *)aKey;
- (void)setDouble:(double)value forKey:(NSString *)aKey;
- (void)setBool:(BOOL)value forKey:(NSString *)aKey;

@property (readonly, copy) NSDictionary<NSString *, id> *dictionaryRepresentation;

- (BOOL)synchronize;

@end

FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreDidChangeExternallyNotification NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangeReasonKey NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangedKeysKey NS_AVAILABLE(10_7, 5_0);

NS_ENUM(NSInteger) {
    NSUbiquitousKeyValueStoreServerChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreInitialSyncChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreQuotaViolationChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreAccountChange NS_ENUM_AVAILABLE(10_8, 6_0)
};

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSNotificationQueue.h
/*	NSNotificationQueue.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSNotification, NSNotificationCenter, NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSPostingStyle) {
    NSPostWhenIdle = 1,
    NSPostASAP = 2,
    NSPostNow = 3
};

typedef NS_OPTIONS(NSUInteger, NSNotificationCoalescing) {
    NSNotificationNoCoalescing = 0,
    NSNotificationCoalescingOnName = 1,
    NSNotificationCoalescingOnSender = 2
};

@interface NSNotificationQueue : NSObject {
@private
    id		_notificationCenter;
    id		_asapQueue;
    id		_asapObs;
    id		_idleQueue;
    id		_idleObs;
}

+ (NSNotificationQueue *)defaultQueue;

- (instancetype)initWithNotificationCenter:(NSNotificationCenter *)notificationCenter NS_DESIGNATED_INITIALIZER;

- (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle;
- (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle coalesceMask:(NSNotificationCoalescing)coalesceMask forModes:(nullable NSArray<NSString *> *)modes;

- (void)dequeueNotificationsMatching:(NSNotification *)notification coalesceMask:(NSUInteger)coalesceMask;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSRunLoop.h
/*	NSRunLoop.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <CoreFoundation/CFRunLoop.h>

@class NSTimer, NSPort, NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSDefaultRunLoopMode;
FOUNDATION_EXPORT NSString * const NSRunLoopCommonModes NS_AVAILABLE(10_5, 2_0);

@interface NSRunLoop : NSObject {
@private
    id          _rl;
    id          _dperf;
    id          _perft;
    id          _info;
    id		_ports;
    void	*_reserved[6];
}

+ (NSRunLoop *)currentRunLoop;
+ (NSRunLoop *)mainRunLoop NS_AVAILABLE(10_5, 2_0);

@property (nullable, readonly, copy) NSString *currentMode;

- (CFRunLoopRef)getCFRunLoop CF_RETURNS_NOT_RETAINED;

- (void)addTimer:(NSTimer *)timer forMode:(NSString *)mode;

- (void)addPort:(NSPort *)aPort forMode:(NSString *)mode;
- (void)removePort:(NSPort *)aPort forMode:(NSString *)mode;

- (nullable NSDate *)limitDateForMode:(NSString *)mode;
- (void)acceptInputForMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

@end

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run; 
- (void)runUntilDate:(NSDate *)limitDate;
- (BOOL)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)configureAsServer NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
#endif

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSString *> *)modes;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;

@end

@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSString *> *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSObject.h
/*	NSObject.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#include <TargetConditionals.h>
#import <objc/NSObject.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

NS_ASSUME_NONNULL_BEGIN

/***************	Basic protocols		***************/

@protocol NSCopying

- (id)copyWithZone:(nullable NSZone *)zone;

@end

@protocol NSMutableCopying

- (id)mutableCopyWithZone:(nullable NSZone *)zone;

@end

@protocol NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder; // NS_DESIGNATED_INITIALIZER

@end

// Objects which are safe to be encoded and decoded across privilege boundaries should adopt NSSecureCoding instead of NSCoding. Secure coders (those that respond YES to requiresSecureCoding) will only encode objects that adopt the NSSecureCoding protocol.
// NOTE: NSSecureCoding guarantees only that an archive contains the classes it claims. It makes no guarantees about the suitability for consumption by the receiver of the decoded content of the archive. Archived objects which  may trigger code evaluation should be validated independently by the consumer of the objects to verify that no malicious code is executed (i.e. by checking key paths, selectors etc. specified in the archive).

@protocol NSSecureCoding <NSCoding>
@required
// This method must be return YES on all classes that allow secure coding. Subclasses of classes that adopt NSSecureCoding and override initWithCoder: must also override this method and return YES.
// The Secure Coding Guide should be consulted when writing methods that decode data.
+ (BOOL)supportsSecureCoding;
@end

/***********	Base class		***********/

@interface NSObject (NSCoderMethods)

+ (NSInteger)version;
+ (void)setVersion:(NSInteger)aVersion;
@property (readonly) Class classForCoder;
- (nullable id)replacementObjectForCoder:(NSCoder *)aCoder;
- (nullable id)awakeAfterUsingCoder:(NSCoder *)aDecoder NS_REPLACES_RECEIVER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass NS_DEPRECATED(10_0, 10_5, 2_0, 2_0)
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


/***********	Discardable Content		***********/

@protocol NSDiscardableContent
@required
- (BOOL)beginContentAccess;
- (void)endContentAccess;
- (void)discardContentIfPossible;
- (BOOL)isContentDiscarded;
@end

@interface NSObject (NSDiscardableContentProxy)
@property (readonly, retain) id autoContentAccessingProxy NS_AVAILABLE(10_6, 4_0);
@end

/***********	Object Allocation / Deallocation		*******/
    
FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone * __nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSDeallocateObject(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone * __nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE NS_DEPRECATED(10_0, 10_8, 2_0, 6_0);

FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone * __nullable requestedZone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

#if __has_feature(objc_arc)

// After using a CFBridgingRetain on an NSObject, the caller must take responsibility for calling CFRelease at an appropriate time.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef __nullable CFBridgingRetain(id __nullable X) {
    return (__bridge_retained CFTypeRef)X;
}

NS_INLINE id __nullable CFBridgingRelease(CFTypeRef CF_CONSUMED __nullable X) {
    return (__bridge_transfer id)X;
}

#else

// This function is intended for use while converting to ARC mode only.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef __nullable CFBridgingRetain(id __nullable X) {
    return X ? CFRetain((CFTypeRef)X) : NULL;
}

// This function is intended for use while converting to ARC mode only.
NS_INLINE id __nullable CFBridgingRelease(CFTypeRef CF_CONSUMED __nullable X) {
    return [(id)CFMakeCollectable(X) autorelease];
}

#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLCredential.h
/*	
    NSURLCredential.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Security/Security.h>

@class NSString;
@class NSArray;

NS_ASSUME_NONNULL_BEGIN

/*!
    @enum NSURLCredentialPersistence
    @abstract Constants defining how long a credential will be kept around
    @constant NSURLCredentialPersistenceNone This credential won't be saved.
    @constant NSURLCredentialPersistenceForSession This credential will only be stored for this session.
    @constant NSURLCredentialPersistencePermanent This credential will be stored permanently. Note: Whereas in Mac OS X any application can access any credential provided the user gives permission, in iPhone OS an application can access only its own credentials.
    @constant NSURLCredentialPersistenceSynchronizable This credential will be stored permanently. Additionally, this credential will be distributed to other devices based on the owning AppleID.
        Note: Whereas in Mac OS X any application can access any credential provided the user gives permission, on iOS an application can 
        access only its own credentials.
*/

typedef NS_ENUM(NSUInteger, NSURLCredentialPersistence) {
    NSURLCredentialPersistenceNone,
    NSURLCredentialPersistenceForSession,
    NSURLCredentialPersistencePermanent,
    NSURLCredentialPersistenceSynchronizable NS_ENUM_AVAILABLE(10_8, 6_0)
};

@class NSURLCredentialInternal;

/*!
    @class NSURLCredential
    @discussion This class is an immutable object representing an authentication credential.  The actual type of the credential is determined by the constructor called in the categories declared below.
*/

@interface NSURLCredential : NSObject <NSSecureCoding, NSCopying>
{
    @private
    __strong NSURLCredentialInternal *_internal;
}

/*!
    @method persistence
    @abstract Determine whether this credential is or should be stored persistently
    @result A value indicating whether this credential is stored permanently, per session or not at all.
 */
@property (readonly) NSURLCredentialPersistence persistence;

@end

/*!
    @class NSURLCredential(NSInternetPassword)
    @discussion This category defines the methods available to an NSURLCredential created to represent an internet password credential.  These are most commonly used for resources that require a username and password combination.
 */
@interface NSURLCredential(NSInternetPassword)

/*!
    @method initWithUser:password:persistence:
    @abstract Initialize a NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The initialized NSURLCredential
*/
- (instancetype)initWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method credentialWithUser:password:persistence:
    @abstract Create a new NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The new autoreleased NSURLCredential
*/
+ (NSURLCredential *)credentialWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method user
    @abstract Get the username
    @result The user string
*/
@property (nullable, readonly, copy) NSString *user;

/*!
    @method password
    @abstract Get the password
    @result The password string
    @discussion This method might actually attempt to retrieve the
    password from an external store, possible resulting in prompting,
    so do not call it unless needed.
*/
@property (nullable, readonly, copy) NSString *password;

/*!
    @method hasPassword
    @abstract Find out if this credential has a password, without trying to get it
    @result YES if this credential has a password, otherwise NO
    @discussion If this credential's password is actually kept in an
    external store, the password method may return nil even if this
    method returns YES, since getting the password may fail, or the
    user may refuse access.
*/
@property (readonly) BOOL hasPassword;

@end

/*!
    @class NSURLCredential(NSClientCertificate)
    @discussion This category defines the methods available to an NSURLCredential created to represent a client certificate credential.  Client certificates are commonly stored on the users computer in the keychain and must be presented to the server during a handshake.
*/
@interface NSURLCredential(NSClientCertificate)

/*!
    @method initWithIdentity:certificates:persistence:
    @abstract Initialize an NSURLCredential with an identity and array of at least 1 client certificates (SecCertificateRef)
    @param identity a SecIdentityRef object
    @param certArray an array containing at least one SecCertificateRef objects
    @param persistence enum that says to store per session, permanently or not at all
    @result the Initialized NSURLCredential
 */
- (instancetype)initWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence NS_AVAILABLE(10_6, 3_0);

/*!
    @method credentialWithIdentity:certificates:persistence:
    @abstract Create a new NSURLCredential with an identity and certificate array
    @param identity a SecIdentityRef object
    @param certArray an array containing at least one SecCertificateRef objects
    @param persistence enum that says to store per session, permanently or not at all
    @result The new autoreleased NSURLCredential
 */
+ (NSURLCredential *)credentialWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence NS_AVAILABLE(10_6, 3_0);

/*!
    @method identity
    @abstract Returns the SecIdentityRef of this credential, if it was created with a certificate and identity
    @result A SecIdentityRef or NULL if this is a username/password credential
 */
@property (nullable, readonly) SecIdentityRef identity;

/*!
    @method certificates
    @abstract Returns an NSArray of SecCertificateRef objects representing the client certificate for this credential, if this credential was created with an identity and certificate.
    @result an NSArray of SecCertificateRef or NULL if this is a username/password credential
 */
@property (readonly, copy) NSArray *certificates NS_AVAILABLE(10_6, 3_0);

@end

@interface NSURLCredential(NSServerTrust)

/*!
    @method initWithTrust:
    @abstract Initialize a new NSURLCredential which specifies that the specified trust has been accepted.
    @result the Initialized NSURLCredential
 */
- (instancetype)initWithTrust:(SecTrustRef)trust NS_AVAILABLE(10_6, 3_0);

/*!
    @method credentialForTrust:
    @abstract Create a new NSURLCredential which specifies that a handshake has been trusted.
    @result The new autoreleased NSURLCredential
 */
+ (NSURLCredential *)credentialForTrust:(SecTrustRef)trust NS_AVAILABLE(10_6, 3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSExtensionContext.h
/*	NSExtensionContext.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

#if __OBJC2__

// Class representing the extension request's context
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSExtensionContext : NSObject

// The list of input NSExtensionItems associated with the context. If the context has no input items, this array will be empty.
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSArray *inputItems;

// Signals the host to complete the app extension request with the supplied result items. The completion handler optionally contains any work which the extension may need to perform after the request has been completed, as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous non-expiration invocation of the completionHandler. Note: calling this method will eventually dismiss the associated view controller.
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler;

// Signals the host to cancel the app extension request, with the supplied error, which should be non-nil. The userInfo of the NSError will contain a key NSExtensionItemsAndErrorsKey which will have as its value a dictionary of NSExtensionItems and associated NSError instances.
- (void)cancelRequestWithError:(NSError *)error;

// Asks the host to open an URL on the extension's behalf
- (void)openURL:(NSURL *)URL completionHandler:(void (^ __nullable)(BOOL success))completionHandler;

@end

// Key in userInfo. Value is a dictionary of NSExtensionItems and associated NSError instances.
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionItemsAndErrorsKey NS_AVAILABLE(10_10, 8_0);

// The host process will enter the foreground
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostWillEnterForegroundNotification NS_AVAILABLE_IOS(8_2);

// The host process did enter the background
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostDidEnterBackgroundNotification NS_AVAILABLE_IOS(8_2);

// The host process will resign active status (stop receiving events), the extension may be suspended
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostWillResignActiveNotification NS_AVAILABLE_IOS(8_2);

// The host process did become active (begin receiving events)
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostDidBecomeActiveNotification NS_AVAILABLE_IOS(8_2);

NS_ASSUME_NONNULL_END

#endif
// ==========  Foundation.framework/Headers/NSFileCoordinator.h
/*
	NSFileCoordinator.h
	Copyright (c) 2010-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSError, NSMutableDictionary, NSOperationQueue, NSURL;

@protocol NSFilePresenter;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSFileCoordinatorReadingOptions) {

    /* Whether reading does _not_ trigger sending of -savePresentedItemChangesWithCompletionHandler: to certain NSFilePresenters in the system and waiting for those NSFilePresenters to respond. The default behavior during coordinated reading is to send -savePresentedItemChangesWithCompletionHandler: to NSFilePresenters.
    */
    NSFileCoordinatorReadingWithoutChanges = 1 << 0,

    /* Whether reading of an item that might be a symbolic link file causes the resolution of the link if it is. This affects the URL passed to the block passed to an invocation of one of the -coordinateReadingItemAtURL:... methods. This is not a valid option to use with -prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:.
    */
    NSFileCoordinatorReadingResolvesSymbolicLink = 1 << 1,

    /* Whether the reading to be done will only attempt to get an item's metadata that is immediately available (name, modification date, tags, and other attributes), and not its contents. For ubiquitous items, specifying this option will cause coordinated reads to be granted immediately (barring other coordinated readers or writers or file presenters on the same system on the same system preventing this) instead of waiting for any downloading of contents or additional metadata like conflicting versions or thumbnails. Attempting to read the item's contents during such a coordinated read may give you unexpected results or fail.
     */
    NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly NS_ENUM_AVAILABLE(10_10, 8_0) = 1 << 2,

    /* Whether reading of an item is being done for the purpose of uploading. When using this option, NSFileCoordinator will create a temporary snapshot of the item being read and will relinquish its claim on the file once that snapshot is made to avoid blocking other coordinated writes during a potentially long upload. If the item at the URL being read is a directory (such as a document package), then the snapshot will be a new file that contains the zipped contents of that directory, and the URL passed to the accessor block will locate that file.
     
    When using this option, you may upload the document outside of the accessor block. However, you should open a file descriptor to the file or relocate the file within the accessor block before you do so, because NSFileCoordinator will unlink the file after the block returns, rendering it inaccessible via the URL.
    */
    NSFileCoordinatorReadingForUploading NS_ENUM_AVAILABLE(10_10, 8_0) = 1 << 3,

};

typedef NS_OPTIONS(NSUInteger, NSFileCoordinatorWritingOptions) {

    /* You can use only one of these writing options at a time. Using none of them indicates that the writing will simply update the item.
    */

    /* Whether the writing to be done is actually the deletion of the item. This affects how the writing waits for previously scheduled coordinated reading and writing, how the writing causes subsequently scheduled reading and writing to wait, and what NSFilePresenter messaging is done. See the comments in the Single File Coordination section below. This option is how you trigger sending of -accommodatePresentedItemDeletionWithCompletionHandler: or -accommodatePresentedSubitemDeletionAtURL:completionHandler: messages to NSFilePresenters.

    For example, Finder uses this when it's emptying the trash to give NSFilePresenters a chance to close documents before their files disappear, or would disappear if the files weren't still open.
    */
    NSFileCoordinatorWritingForDeleting = 1 << 0,

    /* Whether the writing to be done is actually the moving or renaming of the item. This affects how the writing waits for previously scheduled coordinated reading and writing, how the writing causes subsequently scheduled reading and writing to wait, and what NSFilePresenter messaging is done. See the comments in the Single File Coordination section below. This option has no effect when what's being moved is a plain file so you can use it in code that moves file system items without checking whether the items are files or directories. Any such check would invite a race condition anyway.

    For example, Finder uses this when it's moving items that the user has dragged and dropped so as not to yank files contained by moved folders out from underneath applications that are reading or writing those files.
    */
    NSFileCoordinatorWritingForMoving = 1 << 1,

    /* Whether coordinated writing triggers sending of -savePresentedItemChangesWithCompletionHandler: to certain NSFilePresenters in the system and waiting for those NSFilePresenters to respond.
    */
    NSFileCoordinatorWritingForMerging = 1 << 2,

    /* Whether the writing to be done is actually the replacement of the item with a different item. It causes the same behavior as NSFileCoordinatorWritingForDeleting except that when the item being written to is renamed or moved while the writer is being made to wait the item is considered to have been a different item, so the writer is not passed an updated URL to reflect the renaming or moving. Use this when the moving or creation of an item will replace any item that gets in its way. To avoid a race condition use it regardless of whether there is actually an item in the way before the writing begins. Don't use this when simply updating the contents of a file, even if the way you do that is writing the contents to another file and renaming it into place. This is not a valid option to use with -prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:.

    For example, NSDocument uses this for NSSaveAsOperation and NSSaveToOperation to announce that it is possibly overwriting an item with a brand new file or file package. This gives any NSFilePresenter of the overwritten item, including perhaps a different instance of NSDocument, perhaps in the same application, a chance to close itself before the item is overwritten.

    For another example, the most accurate and safe way to coordinate a move is to invoke -coordinateWritingItemAtURL:options:writingItemAtURL:options:error:byAccessor: using the NSFileCoordinatorWritingForMoving option with the source URL and NSFileCoordinatorWritingForReplacing with the destination URL.
    */
    NSFileCoordinatorWritingForReplacing = 1 << 3,

    /* Whether the writing to be done will change the item's metadata only and not its contents. If the item being written to is ubiquitous, then changes to the item's contents during this coordinated write may not be preserved or fail. When using this option, changing metadata that is related to the item's contents is not supported for ubiquitous items and such changes may not be preserved. For example, changing the value of NSURLTagNamesKey is supported, but changing the value of NSURLContentModificationDateKey is not.
     */
    NSFileCoordinatorWritingContentIndependentMetadataOnly NS_ENUM_AVAILABLE(10_10, 8_0) = 1 << 4

};


NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSFileAccessIntent : NSObject {
@private
    NSURL *_url;
    BOOL _isRead;
    NSInteger _options;
}
+ (instancetype)readingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options;
+ (instancetype)writingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options;
@property (readonly, copy) NSURL *URL; // Use this URL within the accessor block. This property may change from its original value in response to actions from other writers.
@end


NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSFileCoordinator : NSObject {
    @private
    id _accessArbiter;
    id _fileReactor;
    id _purposeID;
    NSURL *_recentFilePresenterURL;
    id _accessClaimIDOrIDs;
    BOOL _isCancelled;
    NSMutableDictionary *_movedItems;
}

#pragma mark *** File Presenters ***

/* The process' file presenters. If you invoke +addFilePresenter: you have to do a balancing invocation of +removeFilePresenter: before the file presenter is deallocated, even in a garbage-collected application.

If your application reads an item and then registers a file presenter for it there is a possible race condition in which between those two steps another process does coordinated reading or writing of the item, without any messages sent to your not-quite-registered file presenter. This can leave your file presenter ignorant of the fact that what it knows about the item it just read is already out of date, or under the misconception that just because it hasn't received a -relinquish... method it owns the item. To avoid that race condition you can invoke +addFilePresenter: in the same block that you pass to -coordinateReadingItemAtURL:options:error:byAccessor: to read what the file presenter will present.
*/
+ (void)addFilePresenter:(id<NSFilePresenter>)filePresenter;
+ (void)removeFilePresenter:(id<NSFilePresenter>)filePresenter;
+ (NSArray<id<NSFilePresenter>> *)filePresenters;

/* The designated initializer. If an NSFilePresenter is provided then the receiver is considered to have been created by that NSFilePresenter, or on its behalf.

NSFileCoordinator is meant to be instantiated on a per-file-operation basis, where a file operation is something like the opening or saving of a document, or the copying or moving of a batch of folders and files. There is no benefit to keeping an instance of it alive in your application for much more time than it takes to actually perform the file operation. Doing so can be harmful, or at least wasteful of memory, because NSFileCoordinators may retain NSFilePresenters.

You pass an NSFilePresenter to this initializer when the operation whose file access is to be coordinated is being performed by that NSFilePresenter. Associating an NSFileCoordinator with an NSFilePresenter accomplishes a few important things:
- It prevents the NSFileCoordinator from sending messages to that NSFilePresenter, so the NSFilePresenter does not have to somehow filter out messages about its own file operations. The exception to this rule is that messages about versions of the presented item being added, remove, or resolved during coordinated writing are sent to every relevant NSFilePresenter, even the one passed to -initWithFilePresenter:.
- It allows the file coordination mechanism to determine when coordinated writing is being done in response to an NSFilePresenter receiving a -savePresentedItemChangesWithCompletionHandler: message, and not deadlock. Usually coordinated writing done by one NSFileCoordinator must wait for coordinated reading of the same file or directory done by another NSFileCoordinator. But, for example, when coordinated reading is begun with one NSFileCoordinator, and that causes an NSFilePresenter to do coordinated writing using another NSFileCoordinator, the writing done with the second NSFileCoordinator should not wait for the completion of the first NSFileCoordinator's reading, it should instead happen while the first NSFileCoordinator is waiting to read.
- It allows the file coordination mechanism to handle a race condition that can occur when it has sent an NSFilePresenter a -presentedItemDidMoveToURL: message in the NSFilePresenter's operation queue but before that message is dequeued the NSFilePresenter enqueues, on a different queue, an operation using the old URL. For this to be effective however the NSFileCoordinator must be initialized in the same operation queue in which NSFilePresenter messages are received.
- It allows the file coordination mechanism to gracefully handle your application's registration of an NSFilePresenter that at first returns nil when sent -presentedItemURL but can later return non-nil at the end of doing a coordinated write that creates the presented item in the file system for the very first time. AppKit for example takes advantage of this by registering brand new untitled NSDocuments as NSFilePresenters immediately, instead of waiting until after the first time the user causes the document to be saved to a file, which would be more complicated.

For example, NSDocument creates a single NSFileCoordinator for all of the coordinated reading and writing it does during the saving of a document. It always creates the NSFileCoordinator in the main queue even when it is doing the actual coordinated reading and writing in a background queue to implement asynchronous saving.
*/
- (instancetype)initWithFilePresenter:(nullable id<NSFilePresenter>)filePresenterOrNil NS_DESIGNATED_INITIALIZER;

#pragma mark *** Purpose Identifier ***

/* A string that uniquely identifies the file access that will be done by this NSFileCoordinator. Every NSFileCoordinator has a unique purpose identifier that is created during initialization. Coordinated reads and writes performed by NSFileCoordinators with the same purpose identifier never block each other, even if they exist in different processes. In addition to some of the reasons explained in the comments of -initWithFilePresenter:, you may want to set a custom purpose identifier for the following reasons:
- Your application has an NSFileProviderExtension. Any file coordination done on behalf of the NSFileProviderExtension needs to be done using the same purpose identifier reported by your NSFileProviderExtension.
- To avoid deadlocking when two separate subsystems need to work together to perform one high-level operation, and both subsystems perform their own coordinated reads or writes.
 
If you are coordinating file access on behalf of an NSFilePresenter, you should use -initWithFilePresenter: and should not attempt to set a custom purpose identifier. Every NSFileCoordinator instance initialized with the same NSFilePresenter will have the same purpose identifier.
 
When creating custom purpose identifiers, you can use a reverse DNS style string, such as "com.mycompany.myapplication.mypurpose", or a UUID string. Nil and zero-length strings are not allowed.
 
Purpose identifiers can be set only once. If you attempt to set the purpose identifier of an NSFileCoordinator that you initialized with -initWithFilePresenter: or that you already assigned a purpose identifier, an exception will be thrown.
*/
@property (copy) NSString *purposeIdentifier NS_AVAILABLE(10_7, 5_0);

#pragma mark *** Asynchronous File Coordination ***

/* You can consider "item" in method names and comments in this header file to be an abbreviation of "fileOrDirectory." As always, a directory might actually be a file package.

The term "reader" refers to an invocation of -coordinateAccessWithIntents:queue:byAccessor: with at least one NSFileAccessIntent created with +readingIntentWithURL:options:. Similarly, the term "writer" refers to an invocation of -coordinateAccessWithIntents:queue:byAccessor: with at least one NSFileAccessIntent created with +writingIntentWithURL:optiosn:.
*/

/* Given an array of one or more NSFileAccessIntent objects that specify reading and/or writing items located by the corresponding URLs, wait asynchronously for certain other readers and writers and then invoke the passed-in block on the given queue, which must not be nil. If an error occurs, file access is not granted and a non-nil error will be passed to the accessor block. If file access is successfully granted, then 'error' will be nil and you may perform the intended file access inside the accessor block.
 
You must use the URL property on the NSFileAccessIntent objects when performing file access in the accessor block. Within the block, the NSFileAccessIntent objects' URLs may differ from their original values to account for items that have been moved or renamed while waiting for access to be granted. When access to the intended files is granted, certain other readers and writers are made to wait until the given block returns, which defines the end of that file access. Do not allow file access to continue after the accessor block returns by dispatching work to other threads or queues.
 
You can invoke this method to serialize your process's access of files and directories with other processes' access of the same files and directories so that inconsistencies due to overlapping reading and writing don't occur. It also causes messages to be sent to NSFilePresenters, and wait for NSFilePresenters to react, as described below. The fact that file system items can be moved or renamed while this method is waiting to invoke the block you passed when invoking it is why it's critical to use the URL property on the NSFileAccessIntent objects, not the URLs you used when initializing them.
 
In general a coordinated reader waits for a coordinated writer of the same item, and a coordinated writer waits for coordinated readers and other coordinated writers of the same item. Coordinated readers do not wait for each other. Coordinated reading or writing of items in a file package is treated as coordinated reading or writing of the file package as a whole. A coordinated reader of a directory that is not a file package does not wait for coordinated writers of contained items, or cause such writers to wait. With one exception, a coordinated writer of a directory that is not a file package does not wait for coordinated readers and writers of contained items, or cause such readers and writers to wait. The exception is when you use NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingForReplacing. They make your coordinated writer wait for previously scheduled coordinated readers and writers of contained items, and causes subsequently scheduled coordinated readers and writers of contained items to wait.
 
None of those rules apply to coordinated readers and writers that are using the exact same instance of NSFileCoordinator, including arrays of multiple NSFileAccessIntent objects. Instances of NSFileCoordinator never block themselves. You can take advantage of that in a couple of ways when invoking -coordinateAccessWithIntents:queue:byAccessor: multiple times on the same NSFileCoordinator instance, but take care because doing so raises the possibility of deadlocking with other processes that are doing the same sort of thing. If you can, you should invoke -coordinateAccessWithIntents:queue:byAccessor: a single time with multiple NSFileAccessIntent objects instead of invoking it multiple times with a single NSFileAccssIntent object.
 
In addition to waiting for writers, readers wait for NSFilePresenters that are messaged as part of the coordinated reading.
 
Coordinated reading of an item triggers the sending of messages to NSFilePresenters that implement the corresponding optional methods, even those in other processes, except the one specified when -initWithFilePresenter: was invoked:
- -relinquishPresentedItemToReader: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
- If NSFileCoordinatorReadingWithoutChanges is not used then -savePresentedItemChangesWithCompletionHandler: is also sent to the same NSFilePresenters.

In addition to waiting for readers and other writers, writers wait for NSFilePresenters that are messaged as part of the coordinated writing.
 
Coordinated writing of an item triggers the sending of messages to NSFilePresenters that implement the corresponding optional methods, even those in other processes, except the one specified when -initWithFilePresenter: was invoked:
- -relinquishPresentedItemToWriter: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
- If NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingForReplacing is used and the item is a directory then -relinquishPresentedItemToWriter: is also sent to NSFilePresenters of each item contained by it.
- If NSFileCoordinatorWritingForDeleting or NSFileCoordinatorWritingForReplacing is used then -accommodatePresentedItemDeletionWithCompletionHandler: is sent to NSFilePresenters of the item and, if the item is a directory, NSFilePresenters of each item contained by it. -accommodatePresentedSubitemDeletionAtURL:completionHandler: is sent to NSFilePresenters of each file package that contains the item.
- When NSFileCoordinatorWritingForReplacing is used the the definition of "the item" depends on what happened while waiting for other writers. See the description of it above.
- If NSFileCoordinatorWritingForMerging is used then -savePresentedItemChangesWithCompletionHandler: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
 
For both coordinated reading and writing, if there are multiple NSFilePresenters involved then the order in which they are messaged is undefined. If an NSFilePresenter signals failure then waiting will fail and *outError will be set to an NSError describing the failure.
*/
- (void)coordinateAccessWithIntents:(NSArray<NSFileAccessIntent *> *)intents queue:(NSOperationQueue *)queue byAccessor:(void (^)(NSError * __nullable error))accessor NS_AVAILABLE(10_10, 8_0);

#pragma mark *** Synchronous File Coordination ***

/* The next four methods behave similarly to -coordinateAccessWithIntents:queue:byAccessor: with one or two NSFileAccessIntent objects with the following exceptions:

Each of these methods wait synchronously on the same thread they were invoked on before invoking the passed-in accessor block on the same thread, instead of waiting asynchronously and scheduling invocation of the block on a specific queue.

The accessor block of each of these methods is passed one or more URLs that locate the intended items, perhaps changed from the original URLs to take into account the fact that the item might have been moved or renamed during the waiting.
 
Each of these methods returns an NSError by reference instead of passing it to the accessory block. However, these methods are uncommon among Cocoa framework methods in that they don't also return a result indicating success or failure. The success of the waiting that they do is typically not interesting to invokers. Only the success of file system access done by the passed-in block is interesting. (The failure of either is of course interesting.) When invoking these methods it's cleanest to just declare a __block variable outside of the block and initialize it to a value that signals failure, and then inside the block set it to a value that signals success. If the waiting fails then the invoked method sets the error reference to an NSError that describes what went wrong, your block will not be invoked, your __block variable will not be set to a value that signals success, and all will be as it should be, with failure signaled and an NSError that describes the failure.
*/
- (void)coordinateReadingItemAtURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options error:(NSError **)outError byAccessor:(void (^)(NSURL *newURL))reader;
- (void)coordinateWritingItemAtURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options error:(NSError **)outError byAccessor:(void (^)(NSURL *newURL))writer;
- (void)coordinateReadingItemAtURL:(NSURL *)readingURL options:(NSFileCoordinatorReadingOptions)readingOptions writingItemAtURL:(NSURL *)writingURL options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (^)(NSURL *newReadingURL, NSURL *newWritingURL))readerWriter;
- (void)coordinateWritingItemAtURL:(NSURL *)url1 options:(NSFileCoordinatorWritingOptions)options1 writingItemAtURL:(NSURL *)url2 options:(NSFileCoordinatorWritingOptions)options2 error:(NSError **)outError byAccessor:(void (^)(NSURL *newURL1, NSURL *newURL2))writer;

#pragma mark *** Batched File Coordination ***

/* Prepare to more efficiently do a large number of invocations of -coordinate... methods, first synchronously messaging and waiting for NSFilePresenters in a variation of what individual invocations of the -coordinate... methods would do, and then, if no error occurs, invoke the passed-in block. The passed-in block must invoke the completion handler passed to it when all of the coordinated reading and writing it does is done. The completion handler block can be invoked on any thread (or from any dispatch queue, if that's how you think of it). This method returns errors in the same manner as the -coordinate... methods.

The -coordinate... methods must use interprocess communication to message instances of NSFileCoordinator and NSFilePresenter in other processes in the system. That is an expense best avoided when reading or writing many files in one operation. Using this method can greatly reduce the amount of interprocess communication required by, for example, a large batched copying or moving of files. You use it by moving all of the invocations of the -coordinate... methods your application will do during a batch operation, or the scheduling of them if the operation's work is done in a multithreaded fashion, into a block and passing that block to an invocation of this method, remembering that the completion handler passed to that block must be invoked when the operation is done. You don't simply pass all URLs that will be passed into invocations of the -coordinate... methods when invoking this method. Instead you pass the top-level files and directories involved in the operation. This method triggers messages to not just NSFilePresenters of those items, but also NSFilePresenters of items contained by those items. For example, when Finder uses this method during a copy operation readingURLs is an array of the URLs of the exact files and folders that the user has selected, even though those folders may contain many files and subfolders for which Finder is going to do coordinated reading, and writingURLs is an array that contains just the URL of the destination folder.

In most cases it is redundant to pass the same reading or writing options in an invocation of this method as are passed to individual invocations of the -coordinate... methods invoked by the block passed to an invocation of this method. For example, when Finder invokes this method during a copy operation it does not pass NSFileCoordinatorReadingWithoutChanges because it is appropriate to trigger the saving of document changes right away, but it does pass it when doing the nested invocations of -coordinate... methods because it is not necessary to trigger saving again, even if the user changes the document before the Finder proceeds far enough to actually copy that document's file.
*/
- (void)prepareForReadingItemsAtURLs:(NSArray<NSURL *> *)readingURLs options:(NSFileCoordinatorReadingOptions)readingOptions writingItemsAtURLs:(NSArray<NSURL *> *)writingURLs options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (^)(void (^completionHandler)(void)))batchAccessor;

#pragma mark *** Renaming and Moving Notification ***

/*Announce that the item located by a URL is going to be located by another URL.

Support for App Sandbox on OS X. Some applications can rename files while saving them. For example, when a user adds attachments to a rich text document, TextEdit changes the document's extension from .rtf to .rtfd. A sandboxed application like TextEdit must ordinarily prompt the user for approval before renaming a document. You can invoke this method to make your process declare its intent to rename a document without user approval. After the renaming succeeds you must invoke -itemAtURL:didMoveToURL:, with the same arguments, for the process to keep access to the file with its new name and to give up access to any file that appears with the old name. If the renaming fails you should probably not invoke -itemAtURL:didMoveToURL:.

There is no reason to invoke this method from applications that do not use App Sandbox. Invoking it does nothing on iOS.
*/
- (void)itemAtURL:(NSURL *)oldURL willMoveToURL:(NSURL *)newURL NS_AVAILABLE(10_8, 6_0);

/* Announce that the item located by a URL is now located by another URL.

This triggers the sending of messages to NSFilePresenters that implement the corresponding optional methods, even those in other processes, except the one specified when -initWithFilePresenter: was invoked:
- -presentedItemDidMoveToURL: is sent to NSFilePresenters of the item.
- If the item is a directory then -presentedItemDidMoveToURL: is sent to NSFilePresenters of each item contained by it.
- -presentedSubitemAtURL:didMoveToURL: is sent to NSFilePresenters of each directory that contains the item, unless that method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, in which case -presentedItemDidChange is sent instead.

This also balances invocations of -itemAtURL:willMoveToURL:, as described above.

Useless invocations of this method are harmless, so you don't have to write code that compares NSURLs for equality, which is not straightforward. This method must be invoked from within the block passed to an invocation of -coordinateAccessWithIntents:queue:byAccessory:, -coordinateWritingItemAtURL:options:error:byAccessor:, or -coordinateReadingItemAtURL:options:writingItemAtURL:options:error:byAccessor:.
*/
- (void)itemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;

#pragma mark *** Cancellation ***

/* Cancel all invocations of -coordinate... and -prepare... methods for the receiver. Any current invocation of one of those methods will stop waiting and return immediately, unless it has already invoked the passed-in block, in which case it will return when the passed-in block returns. Subsequent invocations of those methods will not invoke the blocks passed into them at all. When an invocation of -coordinate... or -prepare... returns without invoking the passed-in block because this method was invoked it instead returns an error whose domain is NSCocoaErrorDomain and whose code is NSUserCancelledError. Messages that have already been sent to NSFilePresenters will not be cancelled but the file coordination machinery will stop waiting for the replies.

This method can be invoked from any thread. It always returns immediately, without waiting for anything. Cancellation is racy; you usually cannot assume that no block passed into a -coordinate... or -prepare... method is already being invoked, so the code inside those blocks typically still has to check for cancellation, whatever that means in your application.
*/
- (void)cancel;

@end

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSTimeZone.h
/*	NSTimeZone.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSData, NSLocale;

NS_ASSUME_NONNULL_BEGIN

@interface NSTimeZone : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy) NSString *name;
@property (readonly, copy) NSData *data;

- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
- (nullable NSString *)abbreviationForDate:(NSDate *)aDate;
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);
- (nullable NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSExtendedTimeZone)

+ (NSTimeZone *)systemTimeZone;
+ (void)resetSystemTimeZone;

+ (NSTimeZone *)defaultTimeZone;
+ (void)setDefaultTimeZone:(NSTimeZone *)aTimeZone;

+ (NSTimeZone *)localTimeZone;

+ (NSArray<NSString *> *)knownTimeZoneNames;

+ (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;
+ (void)setAbbreviationDictionary:(NSDictionary<NSString *, NSString *> *)dict NS_AVAILABLE(10_6, 4_0);

+ (NSString *)timeZoneDataVersion NS_AVAILABLE(10_6, 4_0);

@property (readonly) NSInteger secondsFromGMT;
@property (nullable, readonly, copy) NSString *abbreviation;
@property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
@property (readonly) NSTimeInterval daylightSavingTimeOffset NS_AVAILABLE(10_5, 2_0); // for current instant
@property (nullable, readonly, copy) NSDate *nextDaylightSavingTimeTransition NS_AVAILABLE(10_5, 2_0); // after current instant

@property (readonly, copy) NSString *description;

- (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

typedef NS_ENUM(NSInteger, NSTimeZoneNameStyle) {
	NSTimeZoneNameStyleStandard,		// Central Standard Time
	NSTimeZoneNameStyleShortStandard,	// CST
	NSTimeZoneNameStyleDaylightSaving,	// Central Daylight Time
	NSTimeZoneNameStyleShortDaylightSaving,	// CDT
	NSTimeZoneNameStyleGeneric,		// Central Time
	NSTimeZoneNameStyleShortGeneric		// CT
};

- (nullable NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly

+ (nullable instancetype)timeZoneWithName:(NSString *)tzName;
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName data:(nullable NSData *)aData;

- (nullable instancetype)initWithName:(NSString *)tzName;
- (nullable instancetype)initWithName:(NSString *)tzName data:(nullable NSData *)aData;

// Time zones created with this never have daylight savings and the
// offset is constant no matter the date; the name and abbreviation
// do NOT follow the POSIX convention (of minutes-west).
+ (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;

+ (nullable instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

FOUNDATION_EXPORT NSString * const NSSystemTimeZoneDidChangeNotification NS_AVAILABLE(10_5, 2_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSCache.h
/*      NSCache.h
        Copyright (c) 2008-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;
@protocol NSCacheDelegate;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSCache <KeyType, ObjectType> : NSObject {
@private
    id _delegate;
    void *_private[5];
    void *_reserved;
}

@property (copy) NSString *name;

@property (nullable, assign) id<NSCacheDelegate> delegate;

- (nullable ObjectType)objectForKey:(KeyType)key;
- (void)setObject:(ObjectType)obj forKey:(KeyType)key; // 0 cost
- (void)setObject:(ObjectType)obj forKey:(KeyType)key cost:(NSUInteger)g;
- (void)removeObjectForKey:(KeyType)key;

- (void)removeAllObjects;

@property NSUInteger totalCostLimit;	// limits are imprecise/not strict
@property NSUInteger countLimit;	// limits are imprecise/not strict
@property BOOL evictsObjectsWithDiscardedContent;

@end

@protocol NSCacheDelegate <NSObject>
@optional
- (void)cache:(NSCache *)cache willEvictObject:(id)obj;
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSFormatter.h
/*	NSFormatter.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString;
@class NSAttributedString;
@class NSDictionary<KeyType, ObjectType>;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSFormattingContext) {
    
    // The capitalization context to be used is unknown (this is the default value).
    NSFormattingContextUnknown = 0,
    
    // The capitalization context is determined dynamically from the set {NSFormattingContextStandalone, NSFormattingContextBeginningOfSentence, NSFormattingContextMiddleOfSentence}. For example, if a date is placed at the beginning of a sentence, NSFormattingContextBeginningOfSentence is used to format the string automatically. When this context is used, the formatter will return a string proxy that works like a normal string in most cases. After returning from the formatter, the string in the string proxy is formatted by using NSFormattingContextUnknown. When the string proxy is used in stringWithFormat:, we can determine where the %@ is and then set the context accordingly. With the new context, the string in the string proxy will be formatted again and be put into the final string returned from stringWithFormat:.
    NSFormattingContextDynamic = 1,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for stand-alone usage such as an isolated name on a calendar page.
    NSFormattingContextStandalone = 2,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for a list or menu item.
    NSFormattingContextListItem = 3,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the beginning of a sentence.
    NSFormattingContextBeginningOfSentence = 4,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the middle of a sentence.
    NSFormattingContextMiddleOfSentence = 5,
    
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*
 * There are 3 widths: long, medium, and short.
 * For example, for English, when formatting "3 pounds"
 * Long is "3 pounds"; medium is "3 lb"; short is "3#";
 */
typedef NS_ENUM(NSInteger, NSFormattingUnitStyle) {
    NSFormattingUnitStyleShort = 1,
    NSFormattingUnitStyleMedium,
    NSFormattingUnitStyleLong,
} NS_ENUM_AVAILABLE(10_10, 8_0);

@interface NSFormatter : NSObject <NSCopying, NSCoding>

- (nullable NSString *)stringForObjectValue:(id)obj;

- (nullable NSAttributedString *)attributedStringForObjectValue:(id)obj withDefaultAttributes:(nullable NSDictionary<NSString *, id> *)attrs;

- (nullable NSString *)editingStringForObjectValue:(id)obj;

- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString * __nullable * __nullable)newString errorDescription:(NSString * __nullable * __nullable)error;
    // Compatibility method.  If a subclass overrides this and does not override the new method below, this will be called as before (the new method just calls this one by default).  The selection range will always be set to the end of the text with this method if replacement occurs.

- (BOOL)isPartialStringValid:(NSString * __nonnull * __nonnull)partialStringPtr proposedSelectedRange:(nullable NSRangePointer)proposedSelRangePtr originalString:(NSString *)origString originalSelectedRange:(NSRange)origSelRange errorDescription:(NSString * __nullable * __nullable)error;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSUserActivity.h
/*	NSUserActivity.h
	Copyright (c) 2014-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if __OBJC2__

@class NSArray, NSDictionary<KeyType, ObjectType>, NSSet<ObjectType>, NSString, NSURL, NSInputStream, NSOutputStream, NSError;
@protocol NSUserActivityDelegate;

NS_ASSUME_NONNULL_BEGIN

/* NSUserActivity encapsulates the state of a user activity in an application on a particular device, in a way that allows the same activity to be continued on another device in a corresponding application from the same developer. Examples of user user activities include editing a document, viewing a web page, or watching a video.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSUserActivity : NSObject

/* Initializes and returns a newly created NSUserActivity with the given activityType. A user activity may be continued only in an application that (1) has the same developer Team ID as the activity's source application and (2) supports the activity's type. Supported activity types are specified in the application's Info.plist under the NSUserActivityTypes key. When receiving a user activity for continuation, the system locates the appropriate application to launch by finding applications with the target Team ID, then filtering on the incoming activity's type identifier.
*/
- (instancetype)initWithActivityType:(NSString *)activityType;

/* Initializes and returns a newly created NSUserActivity with the first activityType from the NSUserActivityTypes key in the application’s Info.plist.
*/
- (instancetype)init;

/* The activityType the user activity was created with.
*/
@property (readonly, copy) NSString *activityType;

/* An optional, user-visible title for this activity, such as a document name or web page title.
*/
@property (nullable, copy) NSString *title;

/* The userInfo dictionary contains application-specific state needed to continue an activity on another device. Each key and value must be of the following types: NSArray, NSData, NSDate, NSDictionary, NSNull, NSNumber, NSSet, NSString, NSURL, or NSUUID. File scheme URLs which refer to iCloud documents may be translated to valid file URLs on a receiving device.
*/
@property (nullable, copy) NSDictionary *userInfo;

/* Adds to the userInfo dictionary the entries from otherDictionary.  The keys and values must be of the types allowed in the userInfo 
*/
- (void)addUserInfoEntriesFromDictionary:(NSDictionary *)otherDictionary;

/* The keys from the userInfo property which represent the minimal information about this user activity that should be stored for later restoration */
@property (copy) NSSet<NSString *> *requiredUserInfoKeys NS_AVAILABLE(10_11, 9_0);

/* If set to YES, then the delegate for this user activity will receive a userActivityWillSave: callback before being sent for continuation on another device. 
*/
@property (assign) BOOL needsSave;

/* When no suitable application is installed on a resuming device and the webPageURL is set, the user activity will instead be continued in a web browser by loading this resource.
*/
@property (nullable, copy) NSURL *webpageURL;

/* If non-nil, then an absolute date after which this activity is no longer eligible to be indexed or handed off. */
@property (copy) NSDate *expirationDate NS_AVAILABLE(10_11, 9_0);

/* A set of NSString* keywords, representing words or phrases in the current user's language that might help the user to find this activity in the application history. */
@property (copy) NSSet<NSString *> *keywords NS_AVAILABLE(10_11, 9_0);

/* When used for continuation, the user activity can allow the continuing side to connect back for more information using streams. This value is set to NO by default. It can be dynamically set to YES to selectively support continuation streams based on the state of the user activity.
*/
@property BOOL supportsContinuationStreams;

/* The user activity delegate is informed when the activity is being saved or continued (see NSUserActivityDelegate, below)
*/
@property (nullable, weak) id<NSUserActivityDelegate> delegate;

/* Marks the receiver as the activity currently in use by the user, for example, the activity associated with the active window. A newly created activity is eligible for continuation on another device after the first time it becomes current.
*/
- (void)becomeCurrent;

/* If this activity is the current activity, it should stop being so and set the current activity to nothing. */
- (void)resignCurrent NS_AVAILABLE(10_11, 9_0);

/* Invalidate an activity when it's no longer eligible for continuation, for example, when the window associated with an activity is closed. An invalid activity cannot become current.
*/
- (void)invalidate;

/* When an app is launched for a continuation event it can request streams back to the originating side. Streams can only be successfully retrieved from the NSUserActivity in the NS/UIApplication delegate that is called for a continuation event. This functionality is optional and is not expected to be needed in most continuation cases. The streams returned in the completion handler will be in an unopened state. The streams should be opened immediately to start requesting information from the other side.
*/
- (void)getContinuationStreamsWithCompletionHandler:(void (^)(NSInputStream * __nullable inputStream, NSOutputStream * __nullable outputStream, NSError * __nullable error))completionHandler;

/* Set to YES if this user activity should be eligible to be handed off to another device */
@property (getter=isEligibleForHandoff) BOOL eligibleForHandoff NS_AVAILABLE(10_11, 9_0);

/* Set to YES if this user activity should be indexed by App History */
@property (getter=isEligibleForSearch) BOOL eligibleForSearch NS_AVAILABLE(10_11, 9_0);

/* Set to YES if this user activity should be eligible for indexing for any user of this application, on any device, or NO if the activity contains private or sensitive information or which would not be useful to other users if indexed.  The activity must also have requiredUserActivityKeys or a webpageURL */
@property (getter=isEligibleForPublicIndexing) BOOL eligibleForPublicIndexing NS_AVAILABLE(10_11, 9_0);

@end

/* The activity type used when continuing from a web browsing session to either a web browser or a native app. Only activities of this type can be continued from a web browser to a native app.
*/
FOUNDATION_EXPORT NSString * const NSUserActivityTypeBrowsingWeb NS_AVAILABLE(10_10, 8_0);

/* The user activity delegate is responsible for updating the state of an activity and is also notified when an activity has been continued on another device.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@protocol NSUserActivityDelegate <NSObject>
@optional

/* The user activity will be saved (to be continued or persisted). The receiver should update the activity with current activity state.
*/
- (void)userActivityWillSave:(NSUserActivity *)userActivity;

/* The user activity was continued on another device.
*/
- (void)userActivityWasContinued:(NSUserActivity *)userActivity;

/* If supportsContinuationStreams is set to YES the continuing side can request streams back to this user activity. This delegate callback will be received with the incoming streams from the other side. The streams will be in an unopened state. The streams should be opened immediately to start receiving requests from the continuing side.
*/
- (void)userActivity:(nullable NSUserActivity *)userActivity didReceiveInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  Foundation.framework/Headers/NSEnumerator.h
/*	NSEnumerator.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

/*
 * The fast enumeration protocol NSFastEnumeration is adopted and
 * implemented by objects wishing to make use of a fast and safe
 * enumeration style.  The language "foreach" construct then can
 * be used with such objects.
 *
 * The abstract class NSEnumerator itself is taught how to do this
 * for convenience by using -nextObject to return items one at a time.
 */

typedef struct {
    unsigned long state;
    id __unsafe_unretained __nullable * __nullable itemsPtr;
    unsigned long * __nullable mutationsPtr;
    unsigned long extra[5];
} NSFastEnumerationState;

@protocol NSFastEnumeration

- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id __unsafe_unretained [])buffer count:(NSUInteger)len;

@end

@interface NSEnumerator<ObjectType> : NSObject <NSFastEnumeration>

- (nullable ObjectType)nextObject;

@end

@interface NSEnumerator<ObjectType> (NSExtendedEnumerator)

@property (readonly, copy) NSArray<ObjectType> *allObjects;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSMetadataAttributes.h
/*	NSMetadataAttributes.h
        Copyright (c) 2004-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

// The following NSMetadataItem attributes are available on Mac OS and iOS.

FOUNDATION_EXPORT NSString * const NSMetadataItemFSNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDisplayNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemURLKey NS_AVAILABLE(10_7, 5_0); // NSURL
FOUNDATION_EXPORT NSString * const NSMetadataItemPathKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFSSizeKey NS_AVAILABLE(10_7, 5_0); // file size in bytes; unsigned long long NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFSCreationDateKey NS_AVAILABLE(10_7, 5_0); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemFSContentChangeDateKey NS_AVAILABLE(10_7, 5_0); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentTypeKey NS_AVAILABLE(10_9, 8_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemContentTypeTreeKey NS_AVAILABLE(10_9, 8_0); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsUbiquitousKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadedKey NS_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use NSMetadataUbiquitousItemDownloadingStatusKey instead"); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusKey NS_AVAILABLE(10_9, 7_0); // NSString ; download status of this item. The values are the three strings defined below:
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusNotDownloaded  NS_AVAILABLE(10_9, 7_0); // this item has not been downloaded yet. Use startDownloadingUbiquitousItemAtURL:error: to download it.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusDownloaded     NS_AVAILABLE(10_9, 7_0); // there is a local version of this item available. The most current version will get downloaded as soon as possible.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusCurrent        NS_AVAILABLE(10_9, 7_0); // there is a local version of this item and it is the most up-to-date version known to this device.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadedKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentDownloadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentUploadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingErrorKey NS_AVAILABLE(10_9, 7_0); // NSError; the error when downloading the item from iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemUploadingErrorKey NS_AVAILABLE(10_9, 7_0); // NSError; the error when uploading the item to iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadRequestedKey NS_AVAILABLE(10_10, 8_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsExternalDocumentKey NS_AVAILABLE(10_10, 8_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemContainerDisplayNameKey NS_AVAILABLE(10_10, 8_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemURLInLocalContainerKey NS_AVAILABLE(10_10, 8_0); // NSURL

// The following NSMetadataItem attributes are available on Mac OS for non-ubiquitious items only. The constants are equal to the corresponding ones in <Metadata/MDItem.h>.

FOUNDATION_EXPORT NSString * const NSMetadataItemAttributeChangeDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemKeywordsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemTitleKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemEditorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemParticipantsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemProjectsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDownloadedDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemWhereFromsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCommentKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCopyrightKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemLastUsedDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentCreationDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentModificationDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemDateAddedKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemDurationSecondsKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemContactKeywordsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemVersionKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemPixelHeightKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPixelWidthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPixelCountKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemColorSpaceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemBitsPerSampleKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFlashOnOffKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFocalLengthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAcquisitionMakeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAcquisitionModelKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemISOSpeedKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemOrientationKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLayerNamesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemWhiteBalanceKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemApertureKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemProfileNameKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemResolutionWidthDPIKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemResolutionHeightDPIKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureModeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureTimeSecondsKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemEXIFVersionKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemCameraOwnerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFocalLength35mmKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLensModelKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemEXIFGPSVersionKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAltitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLatitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLongitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemSpeedKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTimestampKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSTrackKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemImageDirectionKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemNamedLocationKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemGPSStatusKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSMeasureModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDOPKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSMapDatumKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestLatitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestLongitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestBearingKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestDistanceKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSProcessingMethodKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSAreaInformationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDateStampKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDifferentalKey NS_AVAILABLE_MAC(10_9); // NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataItemCodecsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMediaTypesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemStreamableKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTotalBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemVideoBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemDeliveryTypeKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAlbumKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemHasAlphaChannelKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRedEyeOnOffKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemMeteringModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMaxApertureKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFNumberKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureProgramKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureTimeStringKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemHeadlineKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemInstructionsKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCityKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemStateOrProvinceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCountryKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemTextContentKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAudioSampleRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioChannelCountKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTempoKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemKeySignatureKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemTimeSignatureKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioEncodingApplicationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemComposerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemLyricistKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioTrackNumberKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRecordingDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalGenreKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemIsGeneralMIDISequenceKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRecordingYearKey NS_AVAILABLE_MAC(10_9); // NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataItemOrganizationsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemLanguagesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemRightsKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemPublishersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemContributorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemCoverageKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemSubjectKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemThemeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDescriptionKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemIdentifierKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudiencesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings

FOUNDATION_EXPORT NSString * const NSMetadataItemNumberOfPagesKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPageWidthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPageHeightKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemSecurityMethodKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemCreatorKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemEncodingApplicationsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemDueDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemStarRatingKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPhoneNumbersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemInstantMessageAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemKindKey NS_AVAILABLE_MAC(10_9); // NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemFinderCommentKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFontsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsRootKeyKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsKeyFilterTypeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsLoopModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopDescriptorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalInstrumentCategoryKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalInstrumentNameKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemCFBundleIdentifierKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemInformationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDirectorKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemProducerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGenreKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemPerformersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemOriginalFormatKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemOriginalSourceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsLikelyJunkKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExecutableArchitecturesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemExecutablePlatformKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemApplicationCategoriesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsApplicationManagedKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSThread.h
/*	NSThread.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSArray<ObjectType>, NSMutableDictionary, NSDate, NSNumber, NSString;

NS_ASSUME_NONNULL_BEGIN

@interface NSThread : NSObject  {
@private
    id _private;
    uint8_t _bytes[44];
}

+ (NSThread *)currentThread;

+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

+ (BOOL)isMultiThreaded;

@property (readonly, retain) NSMutableDictionary *threadDictionary;

+ (void)sleepUntilDate:(NSDate *)date;
+ (void)sleepForTimeInterval:(NSTimeInterval)ti;

+ (void)exit;

+ (double)threadPriority;
+ (BOOL)setThreadPriority:(double)p;

@property double threadPriority NS_AVAILABLE(10_6, 4_0); // To be deprecated; use qualityOfService below

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0); // read-only after the thread is started

+ (NSArray<NSNumber *> *)callStackReturnAddresses NS_AVAILABLE(10_5, 2_0);
+ (NSArray<NSString *> *)callStackSymbols NS_AVAILABLE(10_6, 4_0);

@property (nullable, copy) NSString *name NS_AVAILABLE(10_5, 2_0);

@property NSUInteger stackSize NS_AVAILABLE(10_5, 2_0);

@property (readonly) BOOL isMainThread NS_AVAILABLE(10_5, 2_0);
+ (BOOL)isMainThread NS_AVAILABLE(10_5, 2_0); // reports whether current thread is main
+ (NSThread *)mainThread NS_AVAILABLE(10_5, 2_0);

- (instancetype)init NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullable id)argument NS_AVAILABLE(10_5, 2_0);

@property (readonly, getter=isExecuting) BOOL executing NS_AVAILABLE(10_5, 2_0);
@property (readonly, getter=isFinished) BOOL finished NS_AVAILABLE(10_5, 2_0);
@property (readonly, getter=isCancelled) BOOL cancelled NS_AVAILABLE(10_5, 2_0);

- (void)cancel NS_AVAILABLE(10_5, 2_0);

- (void)start NS_AVAILABLE(10_5, 2_0);

- (void)main NS_AVAILABLE(10_5, 2_0);	// thread body method

@end

FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

@interface NSObject (NSThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait;
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array NS_AVAILABLE(10_5, 2_0);
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait NS_AVAILABLE(10_5, 2_0);
	// equivalent to the first method with kCFRunLoopCommonModes
- (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg NS_AVAILABLE(10_5, 2_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSValueTransformer.h
/*	NSValueTransformer.h
        Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSNegateBooleanTransformerName	NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSIsNilTransformerName		NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSIsNotNilTransformerName		NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSUnarchiveFromDataTransformerName	NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSKeyedUnarchiveFromDataTransformerName	NS_AVAILABLE(10_5, 3_0);

NS_CLASS_AVAILABLE(10_3, 3_0)
@interface NSValueTransformer : NSObject {
}

// name-based registry for shared objects (especially used when loading nib files with transformers specified by name in Interface Builder) - also useful for localization (developers can register different kind of transformers or differently configured transformers at application startup and refer to them by name from within nib files or other code)
// if valueTransformerForName: does not find a registered transformer instance, it will fall back to looking up a class with the specified name - if one is found, it will instantiate a transformer with the default -init method and automatically register it
+ (void)setValueTransformer:(nullable NSValueTransformer *)transformer forName:(NSString *)name;
+ (nullable NSValueTransformer *)valueTransformerForName:(NSString *)name;
+ (NSArray<NSString *> *)valueTransformerNames;

// information that can be used to analyze available transformer instances (especially used inside Interface Builder)
+ (Class)transformedValueClass;    // class of the "output" objects, as returned by transformedValue:
+ (BOOL)allowsReverseTransformation;    // flag indicating whether transformation is read-only or not

- (nullable id)transformedValue:(nullable id)value;           // by default returns value
- (nullable id)reverseTransformedValue:(nullable id)value;    // by default raises an exception if +allowsReverseTransformation returns NO and otherwise invokes transformedValue:

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSOrderedSet.h
/*	NSOrderedSet.h
	Copyright (c) 2007-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSArray.h>

@class NSArray, NSIndexSet, NSSet<ObjectType>, NSString;

/****************       Immutable Ordered Set   ****************/

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSOrderedSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (ObjectType)objectAtIndex:(NSUInteger)idx;
- (NSUInteger)indexOfObject:(ObjectType)object;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSOrderedSet<ObjectType> (NSExtendedOrderedSet)

- (void)getObjects:(ObjectType __unsafe_unretained [])objects range:(NSRange)range;
- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;
@property (nullable, nonatomic, readonly) ObjectType firstObject;
@property (nullable, nonatomic, readonly) ObjectType lastObject;

- (BOOL)isEqualToOrderedSet:(NSOrderedSet<ObjectType> *)other;

- (BOOL)containsObject:(ObjectType)object;
- (BOOL)intersectsOrderedSet:(NSOrderedSet<ObjectType> *)other;
- (BOOL)intersectsSet:(NSSet<ObjectType> *)set;

- (BOOL)isSubsetOfOrderedSet:(NSOrderedSet<ObjectType> *)other;
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)set;

- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

- (NSEnumerator<ObjectType> *)objectEnumerator;
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;

@property (readonly, copy) NSOrderedSet<ObjectType> *reversedOrderedSet;

// These two methods return a facade object for the receiving ordered set,
// which acts like an immutable array or set (respectively).  Note that
// while you cannot mutate the ordered set through these facades, mutations
// to the original ordered set will "show through" the facade and it will
// appear to change spontaneously, since a copy of the ordered set is not
// being made.
@property (readonly, strong) NSArray<ObjectType> *array;
@property (readonly, strong) NSSet<ObjectType> *set;

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;

- (NSUInteger)indexOfObjectPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;

- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;

- (NSUInteger)indexOfObject:(ObjectType)object inSortedRange:(NSRange)range options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp; // binary search

- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator)cmptr;
- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr;

@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;

@end

@interface NSOrderedSet<ObjectType> (NSOrderedSetCreation)

+ (instancetype)orderedSet;
+ (instancetype)orderedSetWithObject:(ObjectType)object;
+ (instancetype)orderedSetWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
+ (instancetype)orderedSetWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)orderedSetWithOrderedSet:(NSOrderedSet<ObjectType> *)set;
+ (instancetype)orderedSetWithOrderedSet:(NSOrderedSet<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
+ (instancetype)orderedSetWithArray:(NSArray<ObjectType> *)array;
+ (instancetype)orderedSetWithArray:(NSArray<ObjectType> *)array range:(NSRange)range copyItems:(BOOL)flag;
+ (instancetype)orderedSetWithSet:(NSSet<ObjectType> *)set;
+ (instancetype)orderedSetWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;

- (instancetype)initWithObject:(ObjectType)object;
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set;
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithArray:(NSArray<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;

@end

/****************       Mutable Ordered Set     ****************/

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSMutableOrderedSet<ObjectType> : NSOrderedSet<ObjectType>

- (void)insertObject:(ObjectType)object atIndex:(NSUInteger)idx;
- (void)removeObjectAtIndex:(NSUInteger)idx;
- (void)replaceObjectAtIndex:(NSUInteger)idx withObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableOrderedSet<ObjectType> (NSExtendedMutableOrderedSet)

- (void)addObject:(ObjectType)object;
- (void)addObjects:(const ObjectType [])objects count:(NSUInteger)count;
- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;

- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
- (void)moveObjectsAtIndexes:(NSIndexSet *)indexes toIndex:(NSUInteger)idx;

- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;

- (void)setObject:(ObjectType)obj atIndex:(NSUInteger)idx;
- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

- (void)replaceObjectsInRange:(NSRange)range withObjects:(const ObjectType [])objects count:(NSUInteger)count;
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

- (void)removeObjectsInRange:(NSRange)range;
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
- (void)removeAllObjects;

- (void)removeObject:(ObjectType)object;
- (void)removeObjectsInArray:(NSArray<ObjectType> *)array;

- (void)intersectOrderedSet:(NSOrderedSet<ObjectType> *)other;
- (void)minusOrderedSet:(NSOrderedSet<ObjectType> *)other;
- (void)unionOrderedSet:(NSOrderedSet<ObjectType> *)other;

- (void)intersectSet:(NSSet<ObjectType> *)other;
- (void)minusSet:(NSSet<ObjectType> *)other;
- (void)unionSet:(NSSet<ObjectType> *)other;

#if NS_BLOCKS_AVAILABLE
- (void)sortUsingComparator:(NSComparator)cmptr;
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr;
- (void)sortRange:(NSRange)range options:(NSSortOptions)opts usingComparator:(NSComparator)cmptr;
#endif

@end

@interface NSMutableOrderedSet<ObjectType> (NSMutableOrderedSetCreation)

+ (instancetype)orderedSetWithCapacity:(NSUInteger)numItems;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSProgress.h
/*
	NSProgress.h
	Copyright (c) 2011-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary, NSMutableDictionary, NSMutableSet, NSURL, NSUUID, NSXPCConnection, NSLock;

NS_ASSUME_NONNULL_BEGIN

/*
 NSProgress is used to report the amount of work done, and provides a way to allow the user to cancel that work.
 
 Since work is often split up into several parts, progress objects can form a tree where children represent part of the overall total work. Each parent may have as many children as required, but each child only has one parent. The top level progress object in this tree is typically the one that you would display to a user. The leaf objects are updated as work completes, and the updates propagate up the tree.
 
 The work that an NSProgress does is tracked via a "unit count." There are two unit count values: total and completed. In its leaf form, an NSProgress is created with a total unit count and its completed unit count is updated with -setCompletedUnitCount: until it matches the total unit count. The progress is then considered finished.
 
 When progress objects form nodes in trees, they are still created with a total unit count. Portions of the total are then handed out to children as a "pending unit count." The total amount handed out to children should add up to the parent's totalUnitCount. When those children become finished, the pending unit count assigned to that child is added to the parent's completedUnitCount. Therefore, when all children are finished, the parent's completedUnitCount is equal to its totalUnitCount and it becomes finished itself.
 
 Children NSProgress objects can be added implicitly or by invoking the -addChild:withPendingUnitCount: method on the parent. Implicitly added children are attached to a parent progress between a call to -becomeCurrentWithPendingUnitCount: and a call to -resignCurrent. The implicit child is created with the +progressWithTotalUnitCount: method or by passing the result of +currentProgress to the -initWithParent:userInfo: method. Both kinds of children can be attached to the same parent progress object. If you have an idea in advance that some portions of the work will take more or less time than the others, you can use different values of pending unit count for each child.
 
 If you are designing an interface of an object that reports progress, then the recommended approach is to vend an NSProgress property and adopt the NSProgressReporting protocol. The progress should be created with the -discreteProgressWithTotalUnitCount: method. You can then either update the progress object directly or set it to have children of its own. Users of your object can compose your progress into their tree by using the -addChild:withPendingUnitCount: method.
 
 If you want to provide progress reporting for a single method, then the recommended approach is to implicitly attach to a current NSProgress by creating an NSProgress object at the very beginning of your method using +progressWithTotalUnitCount:. This progress object will consume the pending unit count, and then you can set up the progress object with children of its own.

 The localizedDescription and localizedAdditionalDescription properties are meant to be observed as well as set. So are the cancellable and pausable properties. totalUnitCount and completedUnitCount on the other hand are often not the best properties to observe when presenting progress to the user. For example, you should observe fractionCompleted instead of observing totalUnitCount and completedUnitCount and doing your own calculation. NSProgress' default implementation of fractionCompleted does fairly sophisticated things like taking child NSProgresses into account.
 */

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface NSProgress : NSObject {
@private
    __weak NSProgress *_parent;
    int64_t _reserved4;
    id _values;
    void (^ _resumingHandler)(void);
    void (^ _cancellationHandler)(void);
    void (^ _pausingHandler)(void);
    void (^ _prioritizationHandler)(void);
    uint64_t _flags;
    id _userInfoProxy;
    NSString *_publisherID;
    NSXPCConnection *_connection;
    NSInteger _unpublishingBlockageCount;
    NSInteger _disconnectingBlockageCount;
    NSInteger _remoteObserverCount;
    NSMutableDictionary *_acknowledgementHandlersByBundleID;
    NSMutableDictionary *_lastNotificationTimesByKey;
    NSMutableDictionary *_userInfoLastNotificationTimesByKey;
    NSLock *_lock;
    NSMutableSet *_children;
}

/* The instance of NSProgress associated with the current thread by a previous invocation of -becomeCurrentWithPendingUnitCount:, if any. The purpose of this per-thread value is to allow code that does work to usefully report progress even when it is widely separated from the code that actually presents progress to the user, without requiring layers of intervening code to pass the instance of NSProgress through. Using the result of invoking this directly will often not be the right thing to do, because the invoking code will often not even know what units of work the current progress object deals in. Invoking +progressWithTotalUnitCount: to create a child NSProgress object and then using that to report progress makes more sense in that situation.
*/
+ (nullable NSProgress *)currentProgress;

/* Return an instance of NSProgress that has been initialized with -initWithParent:userInfo:. The initializer is passed the current progress object, if there is one, and the value of the totalUnitCount property is set. In many cases you can simply precede code that does a substantial amount of work with an invocation of this method, with repeated invocations of -setCompletedUnitCount: and -isCancelled in the loop that does the work.

You can invoke this method on one thread and then message the returned NSProgress on another thread. For example, you can let the result of invoking this method get captured by a block passed to dispatch_async(). In that block you can invoke methods like -becomeCurrentWithPendingUnitCount: and -resignCurrent, or -setCompletedUnitCount: and -isCancelled.
*/
+ (NSProgress *)progressWithTotalUnitCount:(int64_t)unitCount;

/* Return an instance of NSProgress that has been initialized with -initWithParent:userInfo:. The initializer is passed nil for the parent, resulting in a progress object that is not part of an existing progress tree. The value of the totalUnitCount property is also set.
 */
+ (NSProgress *)discreteProgressWithTotalUnitCount:(int64_t)unitCount NS_AVAILABLE(10_11, 9_0);

/* Return an instance of NSProgress that has been attached to a parent progress with the given pending unit count.
 */
+ (NSProgress *)progressWithTotalUnitCount:(int64_t)unitCount parent:(NSProgress *)parent pendingUnitCount:(int64_t)portionOfParentTotalUnitCount NS_AVAILABLE(10_11, 9_0);

/* The designated initializer. If a parent NSProgress object is passed then progress reporting and cancellation checking done by the receiver will notify or consult the parent. The only valid arguments to the first argument of this method are nil (indicating no parent) or [NSProgress currentProgress]. Any other value will throw an exception.
*/
- (instancetype)initWithParent:(nullable NSProgress *)parentProgressOrNil userInfo:(nullable NSDictionary *)userInfoOrNil NS_DESIGNATED_INITIALIZER;

/* Make the receiver the current thread's current progress object, returned by +currentProgress. At the same time, record how large a portion of the work represented by the receiver will be represented by the next progress object initialized by invoking -initWithParent:userInfo: in the current thread with the receiver as the parent. This will be used when that child is sent -setCompletedUnitCount: and the receiver is notified of that.
 
   With this mechanism, code that doesn't know anything about its callers can report progress accurately by using +progressWithTotalUnitCount: and -setCompletedUnitCount:. The calling code will account for the fact that the work done is only a portion of the work to be done as part of a larger operation. The unit of work in a call to -becomeCurrentWithPendingUnitCount: has to be the same unit of work as that used for the value of the totalUnitCount property, but the unit of work used by the child can be a completely different one, and often will be. You must always balance invocations of this method with invocations of -resignCurrent.
*/
- (void)becomeCurrentWithPendingUnitCount:(int64_t)unitCount;

/* Balance the most recent previous invocation of -becomeCurrentWithPendingUnitCount: on the same thread by restoring the current progress object to what it was before -becomeCurrentWithPendingUnitCount: was invoked.
*/
- (void)resignCurrent;

/* Directly add a child progress to the receiver, assigning it a portion of the receiver's total unit count.
 */
- (void)addChild:(NSProgress *)child withPendingUnitCount:(int64_t)inUnitCount NS_AVAILABLE(10_11, 9_0);

#pragma mark *** Reporting Progress ***

/* The size of the job whose progress is being reported, and how much of it has been completed so far, respectively. For an NSProgress with a kind of NSProgressKindFile, the unit of these properties is bytes while the NSProgressFileTotalCountKey and NSProgressFileCompletedCountKey keys in the userInfo dictionary are used for the overall count of files. For any other kind of NSProgress, the unit of measurement you use does not matter as long as you are consistent. The values may be reported to the user in the localizedDescription and localizedAdditionalDescription.
 
   If the receiver NSProgress object is a "leaf progress" (no children), then the fractionCompleted is generally completedUnitCount / totalUnitCount. If the receiver NSProgress has children, the fractionCompleted will reflect progress made in child objects in addition to its own completedUnitCount. As children finish, the completedUnitCount of the parent will be updated.
*/
@property int64_t totalUnitCount;
@property int64_t completedUnitCount;

/* A description of what progress is being made, fit to present to the user. NSProgress is by default KVO-compliant for this property, with the notifications always being sent on thread which updates the property. The default implementation of the getter for this property does not always return the most recently set value of the property. If the most recently set value of this property is nil then NSProgress uses the value of the kind property to determine how to use the values of other properties, as well as values in the user info dictionary, to return a computed string. If it fails to do that then it returns an empty string.
  
  For example, depending on the kind of progress, the completed and total unit counts, and other parameters, these kinds of strings may be generated:
    Copying 10 files…
    30% completed
    Copying “TextEdit”…
*/
@property (null_resettable, copy) NSString *localizedDescription;

/* A more specific description of what progress is being made, fit to present to the user. NSProgress is by default KVO-compliant for this property, with the notifications always being sent on thread which updates the property. The default implementation of the getter for this property does not always return the most recently set value of the property. If the most recently set value of this property is nil then NSProgress uses the value of the kind property to determine how to use the values of other properties, as well as values in the user info dictionary, to return a computed string. If it fails to do that then it returns an empty string. The difference between this and localizedDescription is that this text is meant to be more specific about what work is being done at any particular moment.

   For example, depending on the kind of progress, the completed and total unit counts, and other parameters, these kinds of strings may be generated:
    3 of 10 files
    123 KB of 789.1 MB
    3.3 MB of 103.92 GB — 2 minutes remaining
    1.61 GB of 3.22 GB (2 KB/sec) — 2 minutes remaining
    1 minute remaining (1 KB/sec)

*/
@property (null_resettable, copy) NSString *localizedAdditionalDescription;

/* Whether the work being done can be cancelled or paused, respectively. By default NSProgresses are cancellable but not pausable. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property. These properties are for communicating whether controls for cancelling and pausing should appear in a progress reporting user interface. NSProgress itself does not do anything with these properties other than help pass their values from progress reporters to progress observers. It is valid for the values of these properties to change in virtually any way during the lifetime of an NSProgress. Of course, if an NSProgress is cancellable you should actually implement cancellability by setting a cancellation handler or by making your code poll the result of invoking -isCancelled. Likewise for pausability.
*/
@property (getter=isCancellable) BOOL cancellable;
@property (getter=isPausable) BOOL pausable;

/* Whether the work being done has been cancelled or paused, respectively. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property. Instances of NSProgress that have parents are at least as cancelled or paused as their parents.
*/
@property (readonly, getter=isCancelled) BOOL cancelled;
@property (readonly, getter=isPaused) BOOL paused;

/* A block to be invoked when cancel is invoked. The block will be invoked even when the method is invoked on an ancestor of the receiver, or an instance of NSProgress in another process that resulted from publishing the receiver or an ancestor of the receiver. Your block won't be invoked on any particular queue. If it must do work on a specific queue then it should schedule that work on that queue.
*/
@property (nullable, copy) void (^cancellationHandler)(void);

/* A block to be invoked when pause is invoked. The block will be invoked even when the method is invoked on an ancestor of the receiver, or an instance of NSProgress in another process that resulted from publishing the receiver or an ancestor of the receiver. Your block won't be invoked on any particular queue. If it must do work on a specific queue then it should schedule that work on that queue.
 */
@property (nullable, copy) void (^pausingHandler)(void);

/* A block to be invoked when resume is invoked. The block will be invoked even when the method is invoked on an ancestor of the receiver, or an instance of NSProgress in another process that resulted from publishing the receiver or an ancestor of the receiver. Your block won't be invoked on any particular queue. If it must do work on a specific queue then it should schedule that work on that queue.
 */
@property (nullable, copy) void (^resumingHandler)(void) NS_AVAILABLE(10_11, 9_0);

/* Set a value in the dictionary returned by invocations of -userInfo, with appropriate KVO notification for properties whose values can depend on values in the user info dictionary, like localizedDescription. If a nil value is passed then the dictionary entry is removed.
*/
- (void)setUserInfoObject:(nullable id)objectOrNil forKey:(NSString *)key;

#pragma mark *** Observing and Controlling Progress ***

/* Whether the progress being made is indeterminate. -isIndeterminate returns YES when the value of the totalUnitCount or completedUnitCount property is less than zero. Zero values for both of those properties indicates that there turned out to not be any work to do after all; -isIndeterminate returns NO and -fractionCompleted returns 1.0 in that case. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property.
*/
@property (readonly, getter=isIndeterminate) BOOL indeterminate;

/* The fraction of the overall work completed by this progress object, including work done by any children it may have.
*/
@property (readonly) double fractionCompleted;

/* Invoke the block registered with the cancellationHandler property, if there is one, and set the cancelled property to YES. Do this for the receiver, any descendants of the receiver, the instance of NSProgress that was published in another process to make the receiver if that's the case, and any descendants of such a published instance of NSProgress.
*/
- (void)cancel;

/* Invoke the block registered with the pausingHandler property, if there is one, and set the paused property to YES. Do this for the receiver, any descendants of the receiver, the instance of NSProgress that was published in another process to make the receiver if that's the case, and any descendants of such a published instance of NSProgress.
*/
- (void)pause;

/* Invoke the block registered with the resumingHandler property, if there is one, and set the paused property to NO. Do this for the receiver, any descendants of the receiver, the instance of NSProgress that was published in another process to make the receiver if that's the case, and any descendants of such a published instance of NSProgress.
*/
- (void)resume NS_AVAILABLE(10_11, 9_0);

/* Arbitrary values associated with the receiver. Returns a KVO-compliant dictionary that changes as -setUserInfoObject:forKey: is sent to the receiver. The dictionary will send all of its KVO notifications on the thread which updates the property. The result will never be nil, but may be an empty dictionary. Some entries have meanings that are recognized by the NSProgress class itself. See the NSProgress...Key string constants listed below.
*/
@property (readonly, copy) NSDictionary *userInfo;

/* Either a string identifying what kind of progress is being made, like NSProgressKindFile, or nil. If the value of the localizedDescription property has not been set to a non-nil value then the default implementation of -localizedDescription uses the progress kind to determine how to use the values of other properties, as well as values in the user info dictionary, to create a string that is presentable to the user. This is most useful when -localizedDescription is actually being invoked in another process, whose localization language may be different, as a result of using the publish and subscribe mechanism described here.
*/
@property (nullable, copy) NSString *kind;

#pragma mark *** Reporting Progress to Other Processes (OS X Only) ***

/* Make the NSProgress observable by other processes. Whether or not another process can discover the NSProgress to observe it, and how it would do that, depends on entries in the user info dictionary. For example, an NSProgressFileURLKey entry makes an NSProgress discoverable by corresponding invokers of +addSubscriberForFileURL:withPublishingHandler:.

When you make an NSProgress observable by other processes you must ensure that at least -localizedDescription, -isIndeterminate, and -fractionCompleted always work when sent to proxies of your NSProgress in other processes. You make -isIndeterminate and -fractionCompleted always work by accurately setting the total and completed unit counts of the progress. You make -localizedDescription always work by setting the value of the kind property to something valid, like NSProgressKindFile, and then fulfilling the requirements for that specific kind of progress. (You can instead set the value of localizedDescription directly but that is not perfectly reliable because other processes might be using different localization languages than yours.)

You can publish an instance of NSProgress at most once.
*/
- (void)publish NS_AVAILABLE(10_9, NA);

/* Make the NSProgress no longer observable by other processes.
*/
- (void)unpublish NS_AVAILABLE(10_9, NA);

#pragma mark *** Observing and Controlling File Progress by Other Processes (OS X Only) ***

typedef void (^NSProgressUnpublishingHandler)(void);
typedef __nullable NSProgressUnpublishingHandler (^NSProgressPublishingHandler)(NSProgress *progress);

/* Register to hear about file progress. The passed-in block will be invoked when -publish has been sent to an NSProgress whose NSProgressFileURLKey user info dictionary entry is an NSURL locating the same item located by the passed-in NSURL, or an item directly contained by it. The NSProgress passed to your block will be a proxy of the one that was published. The passed-in block may return another block. If it does, then that returned block will be invoked when the corresponding invocation of -unpublish is made, or the publishing process terminates, or +removeSubscriber: is invoked. Your blocks will be invoked on the main thread.
*/
+ (id)addSubscriberForFileURL:(NSURL *)url withPublishingHandler:(NSProgressPublishingHandler)publishingHandler NS_AVAILABLE(10_9, NA);

/* Given the object returned by a previous invocation of -addSubscriberForFileURL:withPublishingHandler:, deregister.
*/
+ (void)removeSubscriber:(id)subscriber NS_AVAILABLE(10_9, NA);

/* Return YES if the receiver represents progress that was published before the invocation of +addSubscriberForFileURL:withPublishingHandler: that resulted in the receiver appearing in this process, NO otherwise. The publish and subscribe mechanism described here is generally "level triggered," in that when you invoke +addSubscriberForFileURL:withPublishingHandler: your block will be invoked for every relevant NSProgress that has already been published and not yet unpublished. Sometimes however you need to implement "edge triggered" behavior, in which you do something either exactly when new progress begins or not at all. In the example described above, the Dock does not animate file icon flying when this method returns YES.

Note that there is no reliable definition of "before" in this case, which involves multiple processes in a preemptively scheduled system. You should not use this method for anything more important than best efforts at animating perfectly in the face of processes coming and going due to unpredictable user actions.
*/
@property (readonly, getter=isOld) BOOL old NS_AVAILABLE(10_9, NA);

@end

/* If your class supports reporting progress, then you can adopt the NSProgressReporting protocol. Objects that adopt this protocol should typically be "one-shot" -- that is, the progress is setup at initialization of the object and is updated when work is done. The value of the property should not be set to another progress object. Instead, the user of the NSProgressReporting class should create a new instance to represent a new set of work.
 */
@protocol NSProgressReporting <NSObject>
@property (readonly) NSProgress *progress;
@end

#pragma mark *** Details of General Progress ***

/* How much time is probably left in the operation, as an NSNumber containing a number of seconds.
*/
FOUNDATION_EXPORT NSString *const NSProgressEstimatedTimeRemainingKey NS_AVAILABLE(10_9, 7_0);

/* How fast data is being processed, as an NSNumber containing bytes per second.
*/
FOUNDATION_EXPORT NSString *const NSProgressThroughputKey NS_AVAILABLE(10_9, 7_0);

#pragma mark *** Details of File Progress ***

/* The value for the kind property that indicates that the work being done is one of the kind of file operations listed below. NSProgress of this kind is assumed to use bytes as the unit of work being done and the default implementation of -localizedDescription takes advantage of that to return more specific text than it could otherwise. The NSProgressFileTotalCountKey and NSProgressFileCompletedCountKey keys in the userInfo dictionary are used for the overall count of files.
*/
FOUNDATION_EXPORT NSString *const NSProgressKindFile NS_AVAILABLE(10_9, 7_0);

/* A user info dictionary key, for an entry that is required when the value for the kind property is NSProgressKindFile. The value must be one of the strings listed in the next section. The default implementations of of -localizedDescription and -localizedItemDescription use this value to determine the text that they return.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindKey NS_AVAILABLE(10_9, 7_0);

/* Possible values for NSProgressFileOperationKindKey entries.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindDownloading NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindDecompressingAfterDownloading NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindReceiving NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindCopying NS_AVAILABLE(10_9, 7_0);

/* A user info dictionary key. The value must be an NSURL identifying the item on which progress is being made. This is required for any NSProgress that is published using -publish to be reported to subscribers registered with +addSubscriberForFileURL:withPublishingHandler:.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileURLKey NS_AVAILABLE(10_9, 7_0);

/* User info dictionary keys. The values must be NSNumbers containing integers. These entries are optional but if they are both present then the default implementation of -localizedAdditionalDescription uses them to determine the text that it returns.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileTotalCountKey NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileCompletedCountKey NS_AVAILABLE(10_9, 7_0);

/* User info dictionary keys. The value for the first entry must be an NSImage, typically an icon. The value for the second entry must be an NSValue containing an NSRect, in screen coordinates, locating the image where it initially appears on the screen.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileAnimationImageKey NS_AVAILABLE(10_9, NA);
FOUNDATION_EXPORT NSString *const NSProgressFileAnimationImageOriginalRectKey NS_AVAILABLE(10_9, NA);

/* A user info dictionary key. The value must be an NSImage containing an icon. This entry is optional but, if it is present, the Finder will use it to show the icon of a file while progress is being made on that file. For example, the App Store uses this to specify an icon for an application being downloaded before the icon can be gotten from the application bundle itself.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileIconKey NS_AVAILABLE(10_9, NA);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSLinguisticTagger.h
/*	NSLinguisticTagger.h
	Copyright (c) 2009-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

@class NSArray<ObjectType>, NSOrthography, NSValue;

NS_ASSUME_NONNULL_BEGIN

/* NSLinguisticTagger is a class used to automatically segment natural-language text and tag the tokens with information such as language, script, lemma, and part of speech.  An instance of this class is assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme.
*/

/* Tag schemes */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeTokenType NS_AVAILABLE(10_7, 5_0);               /* This tag scheme classifies tokens according to their broad general type:  word, punctuation, whitespace, etc. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLexicalClass NS_AVAILABLE(10_7, 5_0);            /* This tag scheme classifies tokens according to class:  part of speech for words, type of punctuation or whitespace, etc. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeNameType NS_AVAILABLE(10_7, 5_0);                /* This tag scheme classifies tokens as to whether they are part of named entities of various types or not. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeNameTypeOrLexicalClass NS_AVAILABLE(10_7, 5_0);  /* This tag scheme follows NSLinguisticTagSchemeNameType for names, NSLinguisticTagSchemeLexicalClass for all other tokens. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLemma NS_AVAILABLE(10_7, 5_0);                   /* This tag scheme supplies a stem form for each word token (if known). */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeLanguage NS_AVAILABLE(10_7, 5_0);                /* This tag scheme tags tokens according to their most likely language (if known). */
FOUNDATION_EXPORT NSString *const NSLinguisticTagSchemeScript NS_AVAILABLE(10_7, 5_0);                  /* This tag scheme tags tokens according to their script. */

/* Tags for NSLinguisticTagSchemeTokenType */
FOUNDATION_EXPORT NSString *const NSLinguisticTagWord NS_AVAILABLE(10_7, 5_0);                          /* Tokens considered to be words or word-like linguistic items. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagPunctuation NS_AVAILABLE(10_7, 5_0);                   /* Tokens made up of punctuation. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagWhitespace NS_AVAILABLE(10_7, 5_0);                    /* Tokens made up of whitespace of all sorts. */
FOUNDATION_EXPORT NSString *const NSLinguisticTagOther NS_AVAILABLE(10_7, 5_0);                         /* Other tokens, including non-linguistic items such as symbols. */

/* Tags for NSLinguisticTagSchemeLexicalClass */
FOUNDATION_EXPORT NSString *const NSLinguisticTagNoun NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagVerb NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagAdjective NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagAdverb NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPronoun NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagDeterminer NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagParticle NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPreposition NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagNumber NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagConjunction NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagInterjection NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagClassifier NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagIdiom NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherWord NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagSentenceTerminator NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOpenQuote NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagCloseQuote NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOpenParenthesis NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagCloseParenthesis NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagWordJoiner NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagDash NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherPunctuation NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagParagraphBreak NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOtherWhitespace NS_AVAILABLE(10_7, 5_0);

/* Tags for NSLinguisticTagSchemeNameType */
FOUNDATION_EXPORT NSString *const NSLinguisticTagPersonalName NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagPlaceName NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString *const NSLinguisticTagOrganizationName NS_AVAILABLE(10_7, 5_0);

/* For NSLinguisticTagSchemeTokenType, NSLinguisticTagSchemeLexicalClass, NSLinguisticTagSchemeNameType, and NSLinguisticTagSchemeNameTypeOrLexicalClass, tags will be taken from the lists above (clients may use == comparison).  Tags for NSLinguisticTagSchemeLemma are lemmas from the language.  Tags for NSLinguisticTagSchemeLanguage are standard language abbreviations.  Tags for NSLinguisticTagSchemeScript are standard script abbreviations.
*/

/* Options arguments of type NSLinguisticTaggerOptions may include the following flags, which allow clients interested only in certain general types of tokens to specify that tokens of other types should be omitted from the returned results. */
typedef NS_OPTIONS(NSUInteger, NSLinguisticTaggerOptions) {   /* Any combination of options from the enumeration. */
    NSLinguisticTaggerOmitWords         = 1 << 0,       /* Omit tokens of type NSLinguisticTagWord. */
    NSLinguisticTaggerOmitPunctuation   = 1 << 1,       /* Omit tokens of type NSLinguisticTagPunctuation. */
    NSLinguisticTaggerOmitWhitespace    = 1 << 2,       /* Omit tokens of type NSLinguisticTagWhitespace. */
    NSLinguisticTaggerOmitOther         = 1 << 3,       /* Omit tokens of type NSLinguisticTagOther. */
    NSLinguisticTaggerJoinNames         = 1 << 4        /* Join tokens of tag scheme NSLinguisticTagSchemeNameType. */
};

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSLinguisticTagger : NSObject {
@private
    NSArray *_schemes;
    NSUInteger _options;
    NSString *_string;
    id _orthographyArray;
    id _tokenArray;
    id _reserved;
}

/* An instance of NSLinguisticTagger is created with an array of tag schemes.  The tagger will be able to supply tags corresponding to any of the schemes in this array.
*/
- (instancetype)initWithTagSchemes:(NSArray<NSString *> *)tagSchemes options:(NSUInteger)opts NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray<NSString *> *tagSchemes NS_AVAILABLE(10_7, 5_0);
@property (nullable, retain) NSString *string NS_AVAILABLE(10_7, 5_0);

/* Clients wishing to know the tag schemes supported in NSLinguisticTagger for a particular language may query them with this method.  The language should be specified using a standard abbreviation as with NSOrthography.
*/
+ (NSArray<NSString *> *)availableTagSchemesForLanguage:(NSString *)language NS_AVAILABLE(10_7, 5_0);

/* If clients know the orthography for a given portion of the string, they may supply it to the tagger.  Otherwise, the tagger will infer the language from the contents of the text.  In each case, the charIndex or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception.
*/
- (void)setOrthography:(nullable NSOrthography *)orthography range:(NSRange)range NS_AVAILABLE(10_7, 5_0);
- (nullable NSOrthography *)orthographyAtIndex:(NSUInteger)charIndex effectiveRange:(nullable NSRangePointer)effectiveRange NS_AVAILABLE(10_7, 5_0);

/* If the string attached to the tagger is mutable, this method must be called to inform the tagger whenever the string changes.  The newRange is the range in the final string which was explicitly edited, and delta is the change in length from the previous version to the current version of the string.  Alternatively, the client may call setString: again to reset all information about the string, but this has the disadvantage of not preserving information about portions of the string that have not changed.
*/
- (void)stringEditedInRange:(NSRange)newRange changeInLength:(NSInteger)delta NS_AVAILABLE(10_7, 5_0);

/* The tagger will segment the string as needed into sentences and tokens, and return those ranges along with a tag for any scheme in its array of tag schemes.  The fundamental tagging method on NSLinguisticTagger is a block iterator, that iterates over all tokens intersecting a given range, supplying tags and ranges.  There are several additional convenience methods, for obtaining a sentence range, information about a single token, or for obtaining information about all tokens intersecting a given range at once, in arrays.  In each case, the charIndex or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception.  Note that a given instance of NSLinguisticTagger should not be used from more than one thread simultaneously.
*/
- (void)enumerateTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts usingBlock:(void (^)(NSString *tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);

- (NSRange)sentenceRangeForRange:(NSRange)range NS_AVAILABLE(10_7, 5_0);
- (nullable NSString *)tagAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange NS_AVAILABLE(10_7, 5_0);
- (NSArray<NSString *> *)tagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts tokenRanges:(NSArray<NSValue *> * __nullable * __nullable)tokenRanges NS_AVAILABLE(10_7, 5_0);
- (nullable NSArray<NSString *> *)possibleTagsAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange scores:(NSArray<NSValue *> * __nullable * __nullable)scores NS_AVAILABLE(10_7, 5_0);

@end

@interface NSString (NSLinguisticAnalysis)

/* Clients wishing to analyze a given string once may use these NSString APIs without having to create an instance of NSLinguisticTagger.  If more than one tagging operation is needed on a given string, it is more efficient to use an explicit NSLinguisticTagger instance.
*/
- (NSArray<NSString *> *)linguisticTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts orthography:(nullable NSOrthography *)orthography tokenRanges:(NSArray<NSValue *> * __nullable * __nullable)tokenRanges NS_AVAILABLE(10_7, 5_0);
- (void)enumerateLinguisticTagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts orthography:(nullable NSOrthography *)orthography usingBlock:(void (^)(NSString *tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSIndexPath.h
/*  NSIndexPath.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSIndexPath : NSObject <NSCopying, NSSecureCoding> {
	@private
	__strong NSUInteger *_indexes;
#if !__OBJC2__
	NSUInteger _hash;
#endif
	NSUInteger _length;
        void *_reserved;
}

+ (instancetype)indexPathWithIndex:(NSUInteger)index;
+ (instancetype)indexPathWithIndexes:(const NSUInteger [])indexes length:(NSUInteger)length;

- (instancetype)initWithIndexes:(const NSUInteger [])indexes length:(NSUInteger)length NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIndex:(NSUInteger)index;


- (NSIndexPath *)indexPathByAddingIndex:(NSUInteger)index;
- (NSIndexPath *)indexPathByRemovingLastIndex;

- (NSUInteger)indexAtPosition:(NSUInteger)position;
@property (readonly) NSUInteger length;

/*!
 @abstract Copies the indexes stored in this index path from the positions specified by positionRange into indexes.
 @param indexes Buffer of at least as many NSUIntegers as specified by the length of positionRange. On return, this memory will hold the index path's indexes.
 @param positionRange A range of valid positions within this index path.  If the location plus the length of positionRange is greater than the length of this index path, this method raises an NSRangeException.
 @discussion
    It is the developer’s responsibility to allocate the memory for the C array.
 */
- (void)getIndexes:(NSUInteger *)indexes range:(NSRange)positionRange NS_AVAILABLE(10_9, 7_0);

	// comparison support
- (NSComparisonResult)compare:(NSIndexPath *)otherObject; // sorting an array of indexPaths using this comparison results in an array representing nodes in depth-first traversal order

@end

@interface NSIndexPath (NSDeprecated)
/// This method is unsafe because it could potentially cause buffer overruns. You should use -getIndexes:range: instead. 
- (void)getIndexes:(NSUInteger *)indexes; // use -getIndexes:range: instead
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSKeyValueCoding.h
/*
	NSKeyValueCoding.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSOrderedSet.h>
#import <Foundation/NSSet.h>

@class NSError, NSString;

NS_ASSUME_NONNULL_BEGIN

/* The exception that is thrown when a key value coding operation fails. The exception's user info dictionary will contain at least two entries:
    - @"NSTargetObjectUserInfoKey": the receiver of the failed KVC message.
    - @"NSUnknownUserInfoKey": the key that was used in the failed KVC message.

The actual value of this constant string is "NSUnknownKeyException," to match the exceptions that are thrown by KVC methods that were deprecated in Mac OS 10.3.
*/
FOUNDATION_EXPORT NSString *const NSUndefinedKeyException;

/* Strings for the names of array operators supported by key-value coding. Only these string declarations are new in Mac OS 10.4. The actual support for array operators appeared in Mac OS 10.3. The values of these do not include "@" prefixes.
*/
FOUNDATION_EXPORT NSString *const NSAverageKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSCountKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfArraysKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfObjectsKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfSetsKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSMaximumKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSMinimumKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSSumKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSUnionOfArraysKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSUnionOfObjectsKeyValueOperator;
FOUNDATION_EXPORT NSString *const NSUnionOfSetsKeyValueOperator;

@interface NSObject(NSKeyValueCoding)

/* Return YES if -valueForKey:, -setValue:forKey:, -mutableArrayValueForKey:, -storedValueForKey:, -takeStoredValue:forKey:, and -takeValue:forKey: may directly manipulate instance variables when sent to instances of the receiving class, NO otherwise. The default implementation of this method returns YES.
*/
+ (BOOL)accessInstanceVariablesDirectly;

/* Given a key that identifies an attribute or to-one relationship, return the attribute value or the related object. Given a key that identifies a to-many relationship, return an immutable array or an immutable set that contains all of the related objects.
    
The default implementation of this method does the following:
    1. Searches the class of the receiver for an accessor method whose name matches the pattern -get<Key>, -<key>, or -is<Key>, in that order. If such a method is found it is invoked. If the type of the method's result is an object pointer type the result is simply returned. If the type of the result is one of the scalar types supported by NSNumber conversion is done and an NSNumber is returned. Otherwise, conversion is done and an NSValue is returned (new in Mac OS 10.5: results of arbitrary type are converted to NSValues, not just NSPoint, NRange, NSRect, and NSSize).
    2 (introduced in Mac OS 10.7). Otherwise (no simple accessor method is found), searches the class of the receiver for methods whose names match the patterns -countOf<Key> and -indexIn<Key>OfObject: and -objectIn<Key>AtIndex: (corresponding to the primitive methods defined by the NSOrderedSet class) and also -<key>AtIndexes: (corresponding to -[NSOrderedSet objectsAtIndexes:]). If a count method and an indexOf method and at least one of the other two possible methods are found, a collection proxy object that responds to all NSOrderedSet methods is returned. Each NSOrderedSet message sent to the collection proxy object will result in some combination of -countOf<Key>, -indexIn<Key>OfObject:, -objectIn<Key>AtIndex:, and -<key>AtIndexes: messages being sent to the original receiver of -valueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -get<Key>:range: that method will be used when appropriate for best performance.
    3. Otherwise (no simple accessor method or set of ordered set access methods is found), searches the class of the receiver for methods whose names match the patterns -countOf<Key> and -objectIn<Key>AtIndex: (corresponding to the primitive methods defined by the NSArray class) and (introduced in Mac OS 10.4) also -<key>AtIndexes: (corresponding to -[NSArray objectsAtIndexes:]). If a count method and at least one of the other two possible methods are found, a collection proxy object that responds to all NSArray methods is returned. Each NSArray message sent to the collection proxy object will result in some combination of -countOf<Key>, -objectIn<Key>AtIndex:, and -<key>AtIndexes: messages being sent to the original receiver of -valueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -get<Key>:range: that method will be used when appropriate for best performance.
    4 (introduced in Mac OS 10.4). Otherwise (no simple accessor method or set of ordered set or array access methods is found), searches the class of the receiver for a threesome of methods whose names match the patterns -countOf<Key>, -enumeratorOf<Key>, and -memberOf<Key>: (corresponding to the primitive methods defined by the NSSet class). If all three such methods are found a collection proxy object that responds to all NSSet methods is returned. Each NSSet message sent to the collection proxy object will result in some combination of -countOf<Key>, -enumeratorOf<Key>, and -memberOf<Key>: messages being sent to the original receiver of -valueForKey:.
    5. Otherwise (no simple accessor method or set of collection access methods is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order. If such an instance variable is found, the value of the instance variable in the receiver is returned, with the same sort of conversion to NSNumber or NSValue as in step 1.
    6. Otherwise (no simple accessor method, set of collection access methods, or instance variable is found), invokes -valueForUndefinedKey: and returns the result. The default implementation of -valueForUndefinedKey: raises an NSUndefinedKeyException, but you can override it in your application.

Compatibility notes:
    - For backward binary compatibility, an accessor method whose name matches the pattern -_get<Key>, or -_<key> is searched for between steps 1 and 3. If such a method is found it is invoked, with the same sort of conversion to NSNumber or NSValue as in step 1. KVC accessor methods whose names start with underscores were deprecated as of Mac OS 10.3 though.
    - The behavior described in step 5 is a change from Mac OS 10.2, in which the instance variable search order was <key>, _<key>.
    - For backward binary compatibility, -handleQueryWithUnboundKey: will be invoked instead of -valueForUndefinedKey: in step 6, if the implementation of -handleQueryWithUnboundKey: in the receiver's class is not NSObject's.
*/
- (nullable id)valueForKey:(NSString *)key;

/* Given a value and a key that identifies an attribute, set the value of the attribute. Given an object and a key that identifies a to-one relationship, relate the object to the receiver, unrelating the previously related object if there was one. Given a collection object and a key that identifies a to-many relationship, relate the objects contained in the collection to the receiver, unrelating previously related objects if there were any.

The default implementation of this method does the following:
    1. Searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found the type of its parameter is checked. If the parameter type is not an object pointer type but the value is nil -setNilValueForKey: is invoked. The default implementation of -setNilValueForKey: raises an NSInvalidArgumentException, but you can override it in your application. Otherwise, if the type of the method's parameter is an object pointer type the method is simply invoked with the value as the argument. If the type of the method's parameter is some other type the inverse of the NSNumber/NSValue conversion done by -valueForKey: is performed before the method is invoked.
    2. Otherwise (no accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order. If such an instance variable is found and its type is an object pointer type the value is retained and the result is set in the instance variable, after the instance variable's old value is first released. If the instance variable's type is some other type its value is set after the same sort of conversion from NSNumber or NSValue as in step 1.
    3. Otherwise (no accessor method or instance variable is found), invokes -setValue:forUndefinedKey:. The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException, but you can override it in your application.

Compatibility notes:
    - For backward binary compatibility with -takeValue:forKey:'s behavior, a method whose name matches the pattern -_set<Key>: is also recognized in step 1. KVC accessor methods whose names start with underscores were deprecated as of Mac OS 10.3 though.
    - For backward binary compatibility, -unableToSetNilForKey: will be invoked instead of -setNilValueForKey: in step 1, if the implementation of -unableToSetNilForKey: in the receiver's class is not NSObject's.
    - The behavior described in step 2 is different from -takeValue:forKey:'s, in which the instance variable search order is <key>, _<key>.
    - For backward binary compatibility with -takeValue:forKey:'s behavior, -handleTakeValue:forUnboundKey: will be invoked instead of -setValue:forUndefinedKey: in step 3, if the implementation of -handleTakeValue:forUnboundKey: in the receiver's class is not NSObject's.
*/
- (void)setValue:(nullable id)value forKey:(NSString *)key;

/* Given a pointer to a value pointer, a key that identifies an attribute or to-one relationship, and a pointer to an NSError pointer, return a value that is suitable for use in subsequent -setValue:forKey: messages sent to the same receiver. If no validation is necessary, return YES without altering *ioValue or *outError. If validation is necessary and possible, return YES after setting *ioValue to an object that is the validated version of the original value, but without altering *outError. If validation is necessary but not possible, return NO after setting *outError to an NSError that encapsulates the reason that validation was not possible, but without altering *ioValue. The sender of the message is never given responsibility for releasing ioValue or outError.

The default implementation of this method searches the class of the receiver for a validator method whose name matches the pattern -validate<Key>:error:. If such a method is found it is invoked and the result is returned. If no such method is found, YES is returned.
*/
- (BOOL)validateValue:(inout id __nullable * __nonnull)ioValue forKey:(NSString *)inKey error:(out NSError **)outError;

/* Given a key that identifies an _ordered_ to-many relationship, return a mutable array that provides read-write access to the related objects. Objects added to the mutable array will become related to the receiver, and objects removed from the mutable array will become unrelated.

The default implementation of this method recognizes the same simple accessor methods and array accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return. It also:
    1. Searches the class of the receiver for methods whose names match the patterns -insertObject:in<Key>AtIndex: and -removeObjectFrom<Key>AtIndex: (corresponding to the two most primitive methods defined by the NSMutableArray class), and (introduced in Mac OS 10.4) also -insert<Key>:atIndexes: and -remove<Key>AtIndexes: (corresponding to -[NSMutableArray insertObjects:atIndexes:] and -[NSMutableArray removeObjectsAtIndexes:). If at least one insertion method and at least one removal method are found each NSMutableArray message sent to the collection proxy object will result in some combination of -insertObject:in<Key>AtIndex:, -removeObjectFrom<Key>AtIndex:, -insert<Key>:atIndexes:, and -remove<Key>AtIndexes: messages being sent to the original receiver of -mutableArrayValueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -replaceObjectIn<Key>AtIndex:withObject: or (introduced in Mac OS 10.4) -replace<Key>AtIndexes:with<Key>: that method will be used when appropriate for best performance.
    2. Otherwise (no set of array mutation methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found each NSMutableArray message sent to the collection proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableArrayValueForKey:.
    3. Otherwise (no set of array mutation methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order. If such an instance variable is found, each NSMutableArray message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableArray or a subclass of NSMutableArray.
    4. Otherwise (no set of array mutation methods, simple accessor method, or instance variable is found), returns a mutable collection proxy object anyway. Each NSMutableArray message sent to the collection proxy object will result in a -setValue:forUndefinedKey: message being sent to the original receiver of -mutableArrayValueForKey:. The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException, but you can override it in your application.

Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem. For better performance implement insertion and removal methods that fulfill the requirements for step 1 in your KVC-compliant class. For best performance implement a replacement method too.
*/
- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key;

/* Given a key that identifies an _ordered_ and uniquing to-many relationship, return a mutable ordered set that provides read-write access to the related objects. Objects added to the mutable ordered set will become related to the receiver, and objects removed from the mutable ordered set will become unrelated.

The default implementation of this method recognizes the same simple accessor methods and ordered set accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return. It also:
    1. Searches the class of the receiver for methods whose names match the patterns -insertObject:in<Key>AtIndex: and -removeObjectFrom<Key>AtIndex: (corresponding to the two most primitive methods defined by the NSMutableOrderedSet class), and also -insert<Key>:atIndexes: and -remove<Key>AtIndexes: (corresponding to -[NSMutableOrderedSet insertObjects:atIndexes:] and -[NSMutableOrderedSet removeObjectsAtIndexes:). If at least one insertion method and at least one removal method are found each NSMutableOrderedSet message sent to the collection proxy object will result in some combination of -insertObject:in<Key>AtIndex:, -removeObjectFrom<Key>AtIndex:, -insert<Key>:atIndexes:, and -remove<Key>AtIndexes: messages being sent to the original receiver of -mutableOrderedSetValueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -replaceObjectIn<Key>AtIndex:withObject: or -replace<Key>AtIndexes:with<Key>: that method will be used when appropriate for best performance.
    2. Otherwise (no set of ordered set mutation methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found each NSMutableOrderedSet message sent to the collection proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableOrderedSetValueForKey:.
    3. Otherwise (no set of ordered set mutation methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order. If such an instance variable is found, each NSMutableOrderedSet message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableOrderedSet or a subclass of NSMutableOrderedSet.
    4. Otherwise (no set of ordered set mutation methods, simple accessor method, or instance variable is found), returns a mutable collection proxy object anyway. Each NSMutableOrderedSet message sent to the collection proxy object will result in a -setValue:forUndefinedKey: message being sent to the original receiver of -mutableOrderedSetValueForKey:. The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException, but you can override it in your application.

Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem. For better performance implement insertion and removal methods that fulfill the requirements for step 1 in your KVC-compliant class. For best performance implement a replacement method too.
*/
- (NSMutableOrderedSet *)mutableOrderedSetValueForKey:(NSString *)key NS_AVAILABLE(10_7, 5_0);

/* Given a key that identifies an _unordered_ and uniquing to-many relationship, return a mutable set that provides read-write access to the related objects. Objects added to the mutable set will become related to the receiver, and objects removed from the mutable set will become unrelated.

The default implementation of this method recognizes the same simple accessor methods and set accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return. It also:
    1. Searches the class of the receiver for methods whose names match the patterns -add<Key>Object: and -remove<Key>Object: (corresponding to the two primitive methods defined by the NSMutableSet class) and also -add<Key>: and -remove<Key>: (corresponding to -[NSMutableSet unionSet:] and -[NSMutableSet minusSet:]). If at least one addition method and at least one removal method are found each NSMutableSet message sent to the collection proxy object will result in some combination of -add<Key>Object:, -remove<Key>Object:, -add<Key>:, and -remove<Key>: messages being sent to the original receiver of -mutableSetValueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -intersect<Key>: or -set<Key>: that method will be used when appropriate for best performance.
    2. Otherwise (no set of set mutation methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found each NSMutableSet message sent to the collection proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableSetValueForKey:.
    3. Otherwise (no set of set mutation methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order. If such an instance variable is found, each NSMutableSet message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableSet or a subclass of NSMutableSet.
    4. Otherwise (no set of set mutation methods, simple accessor method, or instance variable is found), returns a mutable collection proxy object anyway. Each NSMutableSet message sent to the collection proxy object will result in a -setValue:forUndefinedKey: message being sent to the original receiver of -mutableSetValueForKey:. The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException, but you can override it in your application.

Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem. For better performance implement methods that fulfill the requirements for step 1 in your KVC-compliant class.
*/
- (NSMutableSet *)mutableSetValueForKey:(NSString *)key;

/* Key-path-taking variants of like-named methods. The default implementation of each parses the key path enough to determine whether or not it has more than one component (key path components are separated by periods). If so, -valueForKey: is invoked with the first key path component as the argument, and the method being invoked is invoked recursively on the result, with the remainder of the key path passed as an argument. If not, the like-named non-key-path-taking method is invoked.
*/
- (nullable id)valueForKeyPath:(NSString *)keyPath;
- (void)setValue:(nullable id)value forKeyPath:(NSString *)keyPath;
- (BOOL)validateValue:(inout id __nullable * __nonnull)ioValue forKeyPath:(NSString *)inKeyPath error:(out NSError **)outError;
- (NSMutableArray *)mutableArrayValueForKeyPath:(NSString *)keyPath;
- (NSMutableOrderedSet *)mutableOrderedSetValueForKeyPath:(NSString *)keyPath NS_AVAILABLE(10_7, 5_0);
- (NSMutableSet *)mutableSetValueForKeyPath:(NSString *)keyPath;

/* Given that an invocation of -valueForKey: would be unable to get a keyed value using its default access mechanism, return the keyed value using some other mechanism. The default implementation of this method raises an NSUndefinedKeyException. You can override it to handle properties that are dynamically defined at run-time.
*/
- (nullable id)valueForUndefinedKey:(NSString *)key;

/* Given that an invocation of -setValue:forKey: would be unable to set the keyed value using its default mechanism, set the keyed value using some other mechanism. The default implementation of this method raises an NSUndefinedKeyException. You can override it to handle properties that are dynamically defined at run-time.
*/
- (void)setValue:(nullable id)value forUndefinedKey:(NSString *)key;

/* Given that an invocation of -setValue:forKey: would be unable to set the keyed value because the type of the parameter of the corresponding accessor method is an NSNumber scalar type or NSValue structure type but the value is nil, set the keyed value using some other mechanism. The default implementation of this method raises an NSInvalidArgumentException. You can override it to map nil values to something meaningful in the context of your application.
*/
- (void)setNilValueForKey:(NSString *)key;

/* Given an array of keys, return a dictionary containing the keyed attribute values, to-one-related objects, and/or collections of to-many-related objects. Entries for which -valueForKey: returns nil have NSNull as their value in the returned dictionary.
*/
- (NSDictionary<NSString *, id> *)dictionaryWithValuesForKeys:(NSArray<NSString *> *)keys;

/* Given a dictionary containing keyed attribute values, to-one-related objects, and/or collections of to-many-related objects, set the keyed values. Dictionary entries whose values are NSNull result in -setValue:nil forKey:key messages being sent to the receiver.
*/
- (void)setValuesForKeysWithDictionary:(NSDictionary<NSString *, id> *)keyedValues;

@end

@interface NSArray<ObjectType>(NSKeyValueCoding)

/* Return an array containing the results of invoking -valueForKey: on each of the receiver's elements. The returned array will contain NSNull elements for each instance of -valueForKey: returning nil.
*/
- (id)valueForKey:(NSString *)key;

/* Invoke -setValue:forKey: on each of the receiver's elements.
*/
- (void)setValue:(nullable id)value forKey:(NSString *)key;

@end

@interface NSDictionary<KeyType, ObjectType>(NSKeyValueCoding)

/* Return the result of sending -objectForKey: to the receiver.
*/
- (nullable ObjectType)valueForKey:(NSString *)key;

@end

@interface NSMutableDictionary<KeyType, ObjectType>(NSKeyValueCoding)

/* Send -setObject:forKey: to the receiver, unless the value is nil, in which case send -removeObjectForKey:.
*/
- (void)setValue:(nullable ObjectType)value forKey:(NSString *)key;

@end

@interface NSOrderedSet<ObjectType>(NSKeyValueCoding)

/* Return an ordered set containing the results of invoking -valueForKey: on each of the receiver's members. The returned ordered set might not have the same number of members as the receiver. The returned ordered set will not contain any elements corresponding to instances of -valueForKey: returning nil, nor will it contain duplicates.
*/
- (id)valueForKey:(NSString *)key NS_AVAILABLE(10_7, 5_0);

/* Invoke -setValue:forKey: on each of the receiver's members.
*/
- (void)setValue:(nullable id)value forKey:(NSString *)key NS_AVAILABLE(10_7, 5_0);

@end

@interface NSSet<ObjectType>(NSKeyValueCoding)

/* Return a set containing the results of invoking -valueForKey: on each of the receiver's members. The returned set might not have the same number of members as the receiver. The returned set will not contain any elements corresponding to instances of -valueForKey: returning nil (in contrast with -[NSArray(NSKeyValueCoding) valueForKey:], which may put NSNulls in the arrays it returns).
*/
- (id)valueForKey:(NSString *)key;

/* Invoke -setValue:forKey: on each of the receiver's members.
*/
- (void)setValue:(nullable id)value forKey:(NSString *)key;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@interface NSObject(NSDeprecatedKeyValueCoding)

/* Methods that were deprecated in Mac OS 10.4.
*/
+ (BOOL)useStoredAccessor NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)storedValueForKey:(NSString *)key NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)takeStoredValue:(nullable id)value forKey:(NSString *)key NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* Methods that were deprecated in Mac OS 10.3. Use the new, more consistently named, methods declared above instead.
*/
- (void)takeValue:(nullable id)value forKey:(NSString *)key NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (void)takeValue:(nullable id)value forKeyPath:(NSString *)keyPath NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (nullable id)handleQueryWithUnboundKey:(NSString *)key NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (void)handleTakeValue:(nullable id)value forUnboundKey:(NSString *)key NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (void)unableToSetNilForKey:(NSString *)key NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (NSDictionary *)valuesForKeys:(NSArray *)keys NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);
- (void)takeValuesFromDictionary:(NSDictionary *)properties NS_DEPRECATED(10_0, 10_3, 2_0, 2_0);

@end

#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSValue.h
/*	NSValue.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary;

NS_ASSUME_NONNULL_BEGIN

@interface NSValue : NSObject <NSCopying, NSSecureCoding>

- (void)getValue:(void *)value;
@property (readonly) const char *objCType NS_RETURNS_INNER_POINTER;

- (instancetype)initWithBytes:(const void *)value objCType:(const char *)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSValue (NSValueCreation)

+ (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
+ (NSValue *)value:(const void *)value withObjCType:(const char *)type;

@end

@interface NSValue (NSValueExtensionMethods)

+ (NSValue *)valueWithNonretainedObject:(nullable id)anObject;
@property (nullable, readonly) id nonretainedObjectValue;

+ (NSValue *)valueWithPointer:(nullable const void *)pointer;
@property (nullable, readonly) void *pointerValue;

- (BOOL)isEqualToValue:(NSValue *)value;

@end

@interface NSNumber : NSValue

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithChar:(char)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedChar:(unsigned char)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithShort:(short)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedShort:(unsigned short)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithInt:(int)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedInt:(unsigned int)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithLong:(long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedLong:(unsigned long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithLongLong:(long long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedLongLong:(unsigned long long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithFloat:(float)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithDouble:(double)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithBool:(BOOL)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithInteger:(NSInteger)value NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedInteger:(NSUInteger)value NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;

@property (readonly) char charValue;
@property (readonly) unsigned char unsignedCharValue;
@property (readonly) short shortValue;
@property (readonly) unsigned short unsignedShortValue;
@property (readonly) int intValue;
@property (readonly) unsigned int unsignedIntValue;
@property (readonly) long longValue;
@property (readonly) unsigned long unsignedLongValue;
@property (readonly) long long longLongValue;
@property (readonly) unsigned long long unsignedLongLongValue;
@property (readonly) float floatValue;
@property (readonly) double doubleValue;
@property (readonly) BOOL boolValue;
@property (readonly) NSInteger integerValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) NSUInteger unsignedIntegerValue NS_AVAILABLE(10_5, 2_0);

@property (readonly, copy) NSString *stringValue;

- (NSComparisonResult)compare:(NSNumber *)otherNumber;

- (BOOL)isEqualToNumber:(NSNumber *)number;

- (NSString *)descriptionWithLocale:(nullable id)locale;

@end

@interface NSNumber (NSNumberCreation)

+ (NSNumber *)numberWithChar:(char)value;
+ (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
+ (NSNumber *)numberWithShort:(short)value;
+ (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
+ (NSNumber *)numberWithInt:(int)value;
+ (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
+ (NSNumber *)numberWithLong:(long)value;
+ (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
+ (NSNumber *)numberWithLongLong:(long long)value;
+ (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
+ (NSNumber *)numberWithFloat:(float)value;
+ (NSNumber *)numberWithDouble:(double)value;
+ (NSNumber *)numberWithBool:(BOOL)value;
+ (NSNumber *)numberWithInteger:(NSInteger)value NS_AVAILABLE(10_5, 2_0);
+ (NSNumber *)numberWithUnsignedInteger:(NSUInteger)value NS_AVAILABLE(10_5, 2_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSUserDefaults.h
/*	NSUserDefaults.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSData, NSDictionary<KeyValue, ObjectValue>, NSMutableDictionary, NSString, NSURL;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSGlobalDomain;
FOUNDATION_EXPORT NSString * const NSArgumentDomain;
FOUNDATION_EXPORT NSString * const NSRegistrationDomain;

@interface NSUserDefaults : NSObject {
@private
    NSInteger _unused;
    void *_reserved[4];
}

+ (NSUserDefaults *)standardUserDefaults;
+ (void)resetStandardUserDefaults;

- (instancetype)init;
- (nullable instancetype)initWithSuiteName:(nullable NSString *)suitename NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER; //nil suite means use the default search list that +standardUserDefaults uses
- (nullable id)initWithUser:(NSString *)username NS_DEPRECATED(10_0, 10_9, 2_0, 7_0);

- (nullable id)objectForKey:(NSString *)defaultName;
- (void)setObject:(nullable id)value forKey:(NSString *)defaultName;
- (void)removeObjectForKey:(NSString *)defaultName;

- (nullable NSString *)stringForKey:(NSString *)defaultName;
- (nullable NSArray *)arrayForKey:(NSString *)defaultName;
- (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)defaultName;
- (nullable NSData *)dataForKey:(NSString *)defaultName;
- (nullable NSArray<NSString *> *)stringArrayForKey:(NSString *)defaultName;
- (NSInteger)integerForKey:(NSString *)defaultName;
- (float)floatForKey:(NSString *)defaultName;
- (double)doubleForKey:(NSString *)defaultName;
- (BOOL)boolForKey:(NSString *)defaultName;
- (nullable NSURL *)URLForKey:(NSString *)defaultName NS_AVAILABLE(10_6, 4_0);

- (void)setInteger:(NSInteger)value forKey:(NSString *)defaultName;
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
- (void)setDouble:(double)value forKey:(NSString *)defaultName;
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;
- (void)setURL:(nullable NSURL *)url forKey:(NSString *)defaultName NS_AVAILABLE(10_6, 4_0);

- (void)registerDefaults:(NSDictionary<NSString *, id> *)registrationDictionary;

- (void)addSuiteNamed:(NSString *)suiteName;
- (void)removeSuiteNamed:(NSString *)suiteName;

- (NSDictionary<NSString *, id> *)dictionaryRepresentation;

@property (readonly, copy) NSArray<NSString *> *volatileDomainNames;
- (NSDictionary<NSString *, id> *)volatileDomainForName:(NSString *)domainName;
- (void)setVolatileDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;
- (void)removeVolatileDomainForName:(NSString *)domainName;

- (NSArray *)persistentDomainNames NS_DEPRECATED(10_0, 10_9, 2_0, 7_0);
- (nullable NSDictionary<NSString *, id> *)persistentDomainForName:(NSString *)domainName;
- (void)setPersistentDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;
- (void)removePersistentDomainForName:(NSString *)domainName;

- (BOOL)synchronize;

- (BOOL)objectIsForcedForKey:(NSString *)key;
- (BOOL)objectIsForcedForKey:(NSString *)key inDomain:(NSString *)domain;


@end

FOUNDATION_EXPORT NSString * const NSUserDefaultsDidChangeNotification;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
/* The following keys and their values are deprecated in Mac OS X 10.5 "Leopard". Developers should use NSLocale, NSDateFormatter and NSNumberFormatter to retrieve the values formerly returned by these keys.
 */
FOUNDATION_EXPORT NSString * const NSWeekDayNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortWeekDayNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSMonthNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortMonthNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSTimeFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSTimeDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortTimeDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSCurrencySymbol NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDecimalSeparator NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSThousandsSeparator NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDecimalDigits NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSAMPMDesignation NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSHourNameDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSYearMonthWeekDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSEarlierTimeDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSLaterTimeDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSThisDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNextDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNextNextDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSPriorDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDateTimeOrdering NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSInternationalCurrencyString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSPositiveCurrencyFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNegativeCurrencyFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSItemProvider.h
/*	NSItemProvider.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/


#import <Foundation/Foundation.h>

#if __OBJC2__

NS_ASSUME_NONNULL_BEGIN

typedef void (^NSItemProviderCompletionHandler)(__nullable id <NSSecureCoding> item, NSError * __null_unspecified error);
typedef void (^NSItemProviderLoadHandler)(__null_unspecified NSItemProviderCompletionHandler completionHandler, __null_unspecified Class expectedValueClass, NSDictionary * __null_unspecified options);

// An NSItemProvider is a high level abstraction for file-like data objects supporting multiple representations and preview images.
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSItemProvider : NSObject <NSCopying>

// Initialize an NSItemProvider with a single handler for the given item.
- (instancetype)initWithItem:(nullable id <NSSecureCoding>)item typeIdentifier:(nullable NSString *)typeIdentifier NS_DESIGNATED_INITIALIZER;

// Initialize an NSItemProvider with load handlers for the given file URL, and the file content.
- (nullable instancetype)initWithContentsOfURL:(null_unspecified NSURL *)fileURL;

// Sets a load handler block for a specific type identifier. Handlers are invoked on demand through loadItemForTypeIdentifier:options:completionHandler:. To complete loading, the implementation has to call the given completionHandler. Both expectedValueClass and options parameters are derived from the completionHandler block.
- (void)registerItemForTypeIdentifier:(NSString *)typeIdentifier loadHandler:(NSItemProviderLoadHandler)loadHandler;

// Returns the list of registered type identifiers
@property(copy, readonly, NS_NONATOMIC_IOSONLY) NSArray *registeredTypeIdentifiers;

// Returns YES if the item provider has at least one item that conforms to the supplied type identifier.
- (BOOL)hasItemConformingToTypeIdentifier:(NSString *)typeIdentifier;

// Loads the best matching item for a type identifier. The client's expected value class is automatically derived from the blocks item parameter. Returns an error if the returned item class does not match the expected value class. Item providers will perform simple type coercions (eg. NSURL to NSData, NSURL to NSFileWrapper, NSData to UIImage).
- (void)loadItemForTypeIdentifier:(NSString *)typeIdentifier options:(nullable NSDictionary *)options completionHandler:(nullable NSItemProviderCompletionHandler)completionHandler;

@end

// Common keys for the item provider options dictionary.
FOUNDATION_EXTERN NSString * __null_unspecified const NSItemProviderPreferredImageSizeKey NS_AVAILABLE(10_10, 8_0); // NSValue of CGSize or NSSize, specifies image size in pixels.

@interface NSItemProvider(NSPreviewSupport)

// Sets a custom preview image handler block for this item provider. The returned item should preferably be NSData or a file NSURL.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSItemProviderLoadHandler previewImageHandler NS_AVAILABLE(10_10, 8_0);

// Loads the preview image for this item by either calling the supplied preview block or falling back to a QuickLook-based handler. This method, like loadItemForTypeIdentifier:options:completionHandler:, supports implicit type coercion for the item parameter of the completion block. Allowed value classes are: NSData, NSURL, UIImage/NSImage.
- (void)loadPreviewImageWithOptions:(null_unspecified NSDictionary *)options completionHandler:(null_unspecified NSItemProviderCompletionHandler)completionHandler NS_AVAILABLE(10_10, 8_0);

@end


// Keys used in property list items received from or sent to JavaScript code

// If JavaScript code passes an object to its completionFunction, it will be placed into an item of type kUTTypePropertyList, containing an NSDictionary, under this key.
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionJavaScriptPreprocessingResultsKey NS_AVAILABLE(10_10, 8_0);

// Arguments to be passed to a JavaScript finalize method should be placed in an item of type kUTTypePropertyList, containing an NSDictionary, under this key.
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionJavaScriptFinalizeArgumentKey NS_AVAILABLE_IOS(8_0);


// Errors

// Constant used by NSError to distinguish errors belonging to the NSItemProvider domain
FOUNDATION_EXTERN NSString * __null_unspecified const NSItemProviderErrorDomain NS_AVAILABLE(10_10, 8_0);

// NSItemProvider-related error codes
typedef NS_ENUM(NSInteger, NSItemProviderErrorCode) {
    NSItemProviderUnknownError                                      = -1,
    NSItemProviderItemUnavailableError                              = -1000,
    NSItemProviderUnexpectedValueClassError                         = -1100,
    NSItemProviderUnavailableCoercionError NS_AVAILABLE(10_11, 9_0) = -1200
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_ASSUME_NONNULL_END

#endif
// ==========  Foundation.framework/Headers/NSCompoundPredicate.h
/*	NSCompoundPredicate.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

@class NSArray<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

// Compound predicates are predicates which act on the results of evaluating other operators. We provide the basic boolean operators: AND, OR, and NOT.

typedef NS_ENUM(NSUInteger, NSCompoundPredicateType) {
    NSNotPredicateType = 0, 
    NSAndPredicateType,
    NSOrPredicateType,
};

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSCompoundPredicate : NSPredicate {
    @private
    void *_reserved2;
    NSUInteger _type;
    NSArray *_subpredicates;
}

- (instancetype)initWithType:(NSCompoundPredicateType)type subpredicates:(NSArray<NSPredicate *> *)subpredicates NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (readonly) NSCompoundPredicateType compoundPredicateType;
@property (readonly, copy) NSArray *subpredicates;

/*** Convenience Methods ***/
+ (NSCompoundPredicate *)andPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates NS_SWIFT_NAME(init(andPredicateWithSubpredicates:));
+ (NSCompoundPredicate *)orPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates NS_SWIFT_NAME(init(orPredicateWithSubpredicates:));
+ (NSCompoundPredicate *)notPredicateWithSubpredicate:(NSPredicate *)predicate NS_SWIFT_NAME(init(notPredicateWithSubpredicate:));

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSInvocation.h
/*	NSInvocation.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <stdbool.h>

@class NSMethodSignature;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSInvocation : NSObject {
@private
    __strong void *_frame;
    __strong void *_retdata;
    id _signature;
    id _container;
    uint8_t _retainedArgs;
    uint8_t _reserved[15];
}

+ (NSInvocation *)invocationWithMethodSignature:(NSMethodSignature *)sig;

@property (readonly, retain) NSMethodSignature *methodSignature;

- (void)retainArguments;
@property (readonly) BOOL argumentsRetained;

@property (nullable, assign) id target;
@property SEL selector;

- (void)getReturnValue:(void *)retLoc;
- (void)setReturnValue:(void *)retLoc;

- (void)getArgument:(void *)argumentLocation atIndex:(NSInteger)idx;
- (void)setArgument:(void *)argumentLocation atIndex:(NSInteger)idx;

- (void)invoke;
- (void)invokeWithTarget:(id)target;

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5

enum _NSObjCValueType {
    NSObjCNoType = 0,
    NSObjCVoidType = 'v',
    NSObjCCharType = 'c',
    NSObjCShortType = 's',
    NSObjCLongType = 'l',
    NSObjCLonglongType = 'q',
    NSObjCFloatType = 'f',
    NSObjCDoubleType = 'd',
    NSObjCBoolType = 'B',
    NSObjCSelectorType = ':',
    NSObjCObjectType = '@',
    NSObjCStructType = '{',
    NSObjCPointerType = '^',
    NSObjCStringType = '*',
    NSObjCArrayType = '[',
    NSObjCUnionType = '(',
    NSObjCBitfield = 'b'
} NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

typedef struct {
    NSInteger type NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
    union {
    	char charValue;
	short shortValue;
	long longValue;
	long long longlongValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	SEL selectorValue;
	id objectValue;
	void *pointerValue;
	void *structLocation;
	char *cStringLocation;
    } value NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
} NSObjCValue NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

#endif
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSJSONSerialization.h
/*	
    NSJSONSerialization.h
    Copyright (c) 2009-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSError, NSOutputStream, NSInputStream, NSData;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSJSONReadingOptions) {
    NSJSONReadingMutableContainers = (1UL << 0),
    NSJSONReadingMutableLeaves = (1UL << 1),
    NSJSONReadingAllowFragments = (1UL << 2)
} NS_ENUM_AVAILABLE(10_7, 5_0);

typedef NS_OPTIONS(NSUInteger, NSJSONWritingOptions) {
    NSJSONWritingPrettyPrinted = (1UL << 0)
} NS_ENUM_AVAILABLE(10_7, 5_0);

/* A class for converting JSON to Foundation objects and converting Foundation objects to JSON.
   
   An object that may be converted to JSON must have the following properties:
    - Top level object is an NSArray or NSDictionary
    - All objects are NSString, NSNumber, NSArray, NSDictionary, or NSNull
    - All dictionary keys are NSStrings
    - NSNumbers are not NaN or infinity
*/
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSJSONSerialization : NSObject {
@private
    void *reserved[6];
}

/* Returns YES if the given object can be converted to JSON data, NO otherwise. The object must have the following properties:
    - Top level object is an NSArray or NSDictionary
    - All objects are NSString, NSNumber, NSArray, NSDictionary, or NSNull
    - All dictionary keys are NSStrings
    - NSNumbers are not NaN or infinity
 Other rules may apply. Calling this method or attempting a conversion are the definitive ways to tell if a given object can be converted to JSON data.
 */
+ (BOOL)isValidJSONObject:(id)obj;

/* Generate JSON data from a Foundation object. If the object will not produce valid JSON then an exception will be thrown. Setting the NSJSONWritingPrettyPrinted option will generate JSON with whitespace designed to make the output more readable. If that option is not set, the most compact possible JSON will be generated. If an error occurs, the error parameter will be set and the return value will be nil. The resulting data is a encoded in UTF-8.
 */
+ (nullable NSData *)dataWithJSONObject:(id)obj options:(NSJSONWritingOptions)opt error:(NSError **)error;

/* Create a Foundation object from JSON data. Set the NSJSONReadingAllowFragments option if the parser should allow top-level objects that are not an NSArray or NSDictionary. Setting the NSJSONReadingMutableContainers option will make the parser generate mutable NSArrays and NSDictionaries. Setting the NSJSONReadingMutableLeaves option will make the parser generate mutable NSString objects. If an error occurs during the parse, then the error parameter will be set and the result will be nil.
   The data must be in one of the 5 supported encodings listed in the JSON specification: UTF-8, UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE. The data may or may not have a BOM. The most efficient encoding to use for parsing is UTF-8, so if you have a choice in encoding the data passed to this method, use UTF-8.
 */
+ (nullable id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt error:(NSError **)error;

/* Write JSON data into a stream. The stream should be opened and configured. The return value is the number of bytes written to the stream, or 0 on error. All other behavior of this method is the same as the dataWithJSONObject:options:error: method.
 */
+ (NSInteger)writeJSONObject:(id)obj toStream:(NSOutputStream *)stream options:(NSJSONWritingOptions)opt error:(NSError **)error;

/* Create a JSON object from JSON data stream. The stream should be opened and configured. All other behavior of this method is the same as the JSONObjectWithData:options:error: method.
 */
+ (nullable id)JSONObjectWithStream:(NSInputStream *)stream options:(NSJSONReadingOptions)opt error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSEnergyFormatter.h
/*      NSEnergyFormatter.h
        Copyright (c) 2014-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSEnergyFormatterUnit) {
    NSEnergyFormatterUnitJoule = 11,
    NSEnergyFormatterUnitKilojoule = 14,
    NSEnergyFormatterUnitCalorie = (7 << 8) + 1,       // chemistry "calories", abbr "cal"
    NSEnergyFormatterUnitKilocalorie = (7 << 8) + 2,   // kilocalories in general, abbr “kcal”, or “C” in some locales (e.g. US) when usesFoodEnergy is set to YES
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSEnergyFormatter : NSFormatter {
@private
    void *_formatter;
    BOOL _isForFoodEnergyUse;
    void *_reserved[2];
}
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;    // default is NSNumberFormatter with NSNumberFormatterDecimalStyle
@property NSFormattingUnitStyle unitStyle;              // default is NSFormattingUnitStyleMedium
@property (getter = isForFoodEnergyUse) BOOL forFoodEnergyUse; // default is NO; if it is set to YES, NSEnergyFormatterUnitKilocalorie may be “C” instead of “kcal"

// Format a combination of a number and an unit to a localized string.
- (NSString *)stringFromValue:(double)value unit:(NSEnergyFormatterUnit)unit;

// Format a number in joules to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 10.3J = 2.46cal in the US locale).
- (NSString *)stringFromJoules:(double)numberInJoules;

// Return a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSEnergyFormatterUnit)unit;

// Return the locale-appropriate unit, the same unit used by -stringFromJoules:.
- (NSString *)unitStringFromJoules:(double)numberInJoules usedUnit:(nullable NSEnergyFormatterUnit *)unitp;

// No parsing is supported. This method will return NO.
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;
@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSPathUtilities.h
/*	NSPathUtilities.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (NSStringPathExtensions)

+ (NSString *)pathWithComponents:(NSArray<NSString *> *)components;
@property (readonly, copy) NSArray<NSString *> *pathComponents;

@property (getter=isAbsolutePath, readonly) BOOL absolutePath;

@property (readonly, copy) NSString *lastPathComponent;
@property (readonly, copy) NSString *stringByDeletingLastPathComponent;
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

@property (readonly, copy) NSString *pathExtension;
@property (readonly, copy) NSString *stringByDeletingPathExtension;
- (nullable NSString *)stringByAppendingPathExtension:(NSString *)str;

@property (readonly, copy) NSString *stringByAbbreviatingWithTildeInPath;
@property (readonly, copy) NSString *stringByExpandingTildeInPath;

@property (readonly, copy) NSString *stringByStandardizingPath;

@property (readonly, copy) NSString *stringByResolvingSymlinksInPath;

- (NSArray<NSString *> *)stringsByAppendingPaths:(NSArray<NSString *> *)paths;

- (NSUInteger)completePathIntoString:(NSString * __nonnull * __nullable)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray<NSString *> * __nonnull * __nullable)outputArray filterTypes:(nullable NSArray<NSString *> *)filterTypes;

@property (readonly) __strong const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER;
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(NSUInteger)max;

@end

@interface NSArray<ObjectType> (NSArrayPathExtensions)

- (NSArray<NSString *> *)pathsMatchingExtensions:(NSArray<NSString *> *)filterTypes;

@end

FOUNDATION_EXPORT NSString *NSUserName(void);
FOUNDATION_EXPORT NSString *NSFullUserName(void);

FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
FOUNDATION_EXPORT NSString * __nullable NSHomeDirectoryForUser(NSString * __nullable userName);

FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);

FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);

typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
    NSApplicationDirectory = 1,             // supported applications (Applications)
    NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
    NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
    NSAdminApplicationDirectory,            // system and network administration applications (Administration)
    NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
    NSUserDirectory,                        // user home directories (Users)
    NSDocumentationDirectory,               // documentation (Documentation)
    NSDocumentDirectory,                    // documents (Documents)
    NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
    NSAutosavedInformationDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 11,   // location of autosaved documents (Documents/Autosaved)
    NSDesktopDirectory = 12,                // location of user's desktop
    NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
    NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
    NSDownloadsDirectory NS_ENUM_AVAILABLE(10_5, 2_0) = 15,              // location of the user's "Downloads" directory
    NSInputMethodsDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 16,           // input methods (Library/Input Methods)
    NSMoviesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 17,                 // location of user's Movies directory (~/Movies)
    NSMusicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 18,                  // location of user's Music directory (~/Music)
    NSPicturesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 19,               // location of user's Pictures directory (~/Pictures)
    NSPrinterDescriptionDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
    NSSharedPublicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 21,           // location of user's Public sharing directory (~/Public)
    NSPreferencePanesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
    NSApplicationScriptsDirectory NS_ENUM_AVAILABLE(10_8, NA) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
    NSItemReplacementDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
    NSAllApplicationsDirectory = 100,       // all directories where applications can occur
    NSAllLibrariesDirectory = 101,          // all directories where resources can occur
    NSTrashDirectory NS_ENUM_AVAILABLE(10_8, NA) = 102                   // location of Trash directory

};

typedef NS_OPTIONS(NSUInteger, NSSearchPathDomainMask) {
    NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
    NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
    NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};

FOUNDATION_EXPORT NSArray<NSString *> *NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSCalendar.h
/*	NSCalendar.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>
#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSString, NSArray<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

FOUNDATION_EXPORT NSString * const NSCalendarIdentifierGregorian  NS_AVAILABLE(10_6, 4_0); // the common calendar in Europe, the Western Hemisphere, and elsewhere
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierBuddhist            NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierChinese             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierCoptic              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierEthiopicAmeteMihret NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierEthiopicAmeteAlem   NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierHebrew              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierISO8601             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIndian              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamic             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicCivil        NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierJapanese            NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierPersian             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierRepublicOfChina     NS_AVAILABLE(10_6, 4_0);
// A simple tabular Islamic calendar using the astronomical/Thursday epoch of CE 622 July 15
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicTabular      NS_AVAILABLE(10_10, 8_0);
// The Islamic Umm al-Qura calendar used in Saudi Arabia. This is based on astronomical calculation, instead of tabular behavior.
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicUmmAlQura    NS_AVAILABLE(10_10, 8_0);


typedef NS_OPTIONS(NSUInteger, NSCalendarUnit) {
        NSCalendarUnitEra                = kCFCalendarUnitEra,
        NSCalendarUnitYear               = kCFCalendarUnitYear,
        NSCalendarUnitMonth              = kCFCalendarUnitMonth,
        NSCalendarUnitDay                = kCFCalendarUnitDay,
        NSCalendarUnitHour               = kCFCalendarUnitHour,
        NSCalendarUnitMinute             = kCFCalendarUnitMinute,
        NSCalendarUnitSecond             = kCFCalendarUnitSecond,
        NSCalendarUnitWeekday            = kCFCalendarUnitWeekday,
        NSCalendarUnitWeekdayOrdinal     = kCFCalendarUnitWeekdayOrdinal,
        NSCalendarUnitQuarter            NS_ENUM_AVAILABLE(10_6, 4_0) = kCFCalendarUnitQuarter,
        NSCalendarUnitWeekOfMonth        NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfMonth,
        NSCalendarUnitWeekOfYear         NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfYear,
        NSCalendarUnitYearForWeekOfYear  NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitYearForWeekOfYear,
        NSCalendarUnitNanosecond         NS_ENUM_AVAILABLE(10_7, 5_0) = (1 << 15),
        NSCalendarUnitCalendar           NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 20),
        NSCalendarUnitTimeZone           NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 21),

	NSEraCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitEra instead") = NSCalendarUnitEra,
	NSYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitYear instead") = NSCalendarUnitYear,
	NSMonthCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitMonth instead") = NSCalendarUnitMonth,
	NSDayCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitDay instead") = NSCalendarUnitDay,
	NSHourCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitHour instead") = NSCalendarUnitHour,
	NSMinuteCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitMinute instead") = NSCalendarUnitMinute,
	NSSecondCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitSecond instead") = NSCalendarUnitSecond,
	NSWeekCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekOfMonth or NSCalendarUnitWeekOfYear, depending on which you mean") = kCFCalendarUnitWeek,
	NSWeekdayCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekday instead") = NSCalendarUnitWeekday,
	NSWeekdayOrdinalCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekdayOrdinal instead") = NSCalendarUnitWeekdayOrdinal,
	NSQuarterCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarUnitQuarter instead") = NSCalendarUnitQuarter,
	NSWeekOfMonthCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitWeekOfMonth instead") = NSCalendarUnitWeekOfMonth,
	NSWeekOfYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitWeekOfYear instead") = NSCalendarUnitWeekOfYear,
	NSYearForWeekOfYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitYearForWeekOfYear instead") = NSCalendarUnitYearForWeekOfYear,
	NSCalendarCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 4_0, 8_0, "Use NSCalendarUnitCalendar instead") = NSCalendarUnitCalendar,
	NSTimeZoneCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 4_0, 8_0, "Use NSCalendarUnitTimeZone instead") = NSCalendarUnitTimeZone,
};
    
typedef NS_OPTIONS(NSUInteger, NSCalendarOptions) {
	NSCalendarWrapComponents = (1UL << 0), // option for arithmetic operations that do calendar addition

	NSCalendarMatchStrictly    NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 1),
	NSCalendarSearchBackwards  NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 2),
    
	NSCalendarMatchPreviousTimePreservingSmallerUnits NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 8),
	NSCalendarMatchNextTimePreservingSmallerUnits     NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 9),
	NSCalendarMatchNextTime                           NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 10),
    
	NSCalendarMatchFirst  NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 12),
	NSCalendarMatchLast   NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 13)
};

enum {
	NSWrapCalendarComponents NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarWrapComponents instead") = NSCalendarWrapComponents,
};


@interface NSCalendar : NSObject <NSCopying, NSSecureCoding>


+ (NSCalendar *)currentCalendar;					// user's preferred calendar
+ (NSCalendar *)autoupdatingCurrentCalendar NS_AVAILABLE(10_5, 2_0); // tracks changes to user's preferred calendar identifier

/*
	This method returns a new autoreleased calendar object of the given type, specified by a calendar identifier constant.
	The calendar defaults to having the current locale and default time zone, for those properties.
*/
+ (nullable NSCalendar *)calendarWithIdentifier:(NSString *)calendarIdentifierConstant NS_AVAILABLE(10_9, 8_0);

- (instancetype)init NS_UNAVAILABLE;

- (nullable id)initWithCalendarIdentifier:(NSString *)ident NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) NSString *calendarIdentifier;
@property (nullable, copy) NSLocale *locale;
@property (copy) NSTimeZone *timeZone;
@property NSUInteger firstWeekday;
@property NSUInteger minimumDaysInFirstWeek;

// Methods to return component name strings localized to the calendar's locale

@property (readonly, copy) NSArray<NSString *> *eraSymbols      NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *longEraSymbols  NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray<NSString *> *monthSymbols                    NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortMonthSymbols               NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *veryShortMonthSymbols           NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *standaloneMonthSymbols          NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortStandaloneMonthSymbols     NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray<NSString *> *weekdaySymbols                    NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortWeekdaySymbols               NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *veryShortWeekdaySymbols           NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *standaloneWeekdaySymbols          NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols     NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray<NSString *> *quarterSymbols                 NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortQuarterSymbols            NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *standaloneQuarterSymbols       NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols  NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSString *AMSymbol  NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSString *PMSymbol  NS_AVAILABLE(10_7, 5_0);


// Calendrical calculations

- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
- (NSUInteger)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

- (BOOL)rangeOfUnit:(NSCalendarUnit)unit startDate:(NSDate * __nullable * __nullable)datep interval:(nullable NSTimeInterval *)tip forDate:(NSDate *)date NS_AVAILABLE(10_5, 2_0);

- (nullable NSDate *)dateFromComponents:(NSDateComponents *)comps;
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)date;

- (nullable NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(NSCalendarOptions)opts;

- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(NSCalendarOptions)opts;


/*
	This API is a convenience for getting era, year, month, and day of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getEra:(out nullable NSInteger *)eraValuePointer year:(out nullable NSInteger *)yearValuePointer month:(out nullable NSInteger *)monthValuePointer day:(out nullable NSInteger *)dayValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API is a convenience for getting era, year for week-of-year calculations, week of year, and weekday of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getEra:(out nullable NSInteger *)eraValuePointer yearForWeekOfYear:(out nullable NSInteger *)yearValuePointer weekOfYear:(out nullable NSInteger *)weekValuePointer weekday:(out nullable NSInteger *)weekdayValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API is a convenience for getting hour, minute, second, and nanoseconds of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getHour:(out nullable NSInteger *)hourValuePointer minute:(out nullable NSInteger *)minuteValuePointer second:(out nullable NSInteger *)secondValuePointer nanosecond:(out nullable NSInteger *)nanosecondValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Get just one component's value.
*/
- (NSInteger)component:(NSCalendarUnit)unit fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Create a date with given components.
	Current era is assumed.
*/
- (nullable NSDate *)dateWithEra:(NSInteger)eraValue year:(NSInteger)yearValue month:(NSInteger)monthValue day:(NSInteger)dayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue NS_AVAILABLE(10_9, 8_0);


/*
	Create a date with given components.
	Current era is assumed.
*/
- (nullable NSDate *)dateWithEra:(NSInteger)eraValue yearForWeekOfYear:(NSInteger)yearValue weekOfYear:(NSInteger)weekValue weekday:(NSInteger)weekdayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue NS_AVAILABLE(10_9, 8_0);


/*
	This API returns the first moment date of a given date.
	Pass in [NSDate date], for example, if you want the start of "today".
	If there were two midnights, it returns the first.  If there was none, it returns the first moment that did exist.
*/
- (NSDate *)startOfDayForDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API returns all the date components of a date, as if in a given time zone (instead of the receiving calendar's time zone).
	The time zone overrides the time zone of the NSCalendar for the purposes of this calculation.
	Note: if you want "date information in a given time zone" in order to display it, you should use NSDateFormatter to format the date.
*/
- (NSDateComponents *)componentsInTimeZone:(NSTimeZone *)timezone fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units, otherwise either less than or greater than.
*/
- (NSComparisonResult)compareDate:(NSDate *)date1 toDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units.
*/
- (BOOL)isDate:(NSDate *)date1 equalToDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the Days of the given dates, reporting them equal if they are in the same Day.
*/
- (BOOL)isDate:(NSDate *)date1 inSameDayAsDate:(NSDate *)date2 NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "today".
*/
- (BOOL)isDateInToday:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "yesterday".
*/
- (BOOL)isDateInYesterday:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "tomorrow".
*/
- (BOOL)isDateInTomorrow:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within a weekend period, as defined by the calendar and calendar's locale.
*/
- (BOOL)isDateInWeekend:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Find the range of the weekend around the given date, returned via two by-reference parameters.
	Returns NO if the given date is not in a weekend.
	Note that a given entire Day within a calendar is not necessarily all in a weekend or not; weekends can start in the middle of a Day in some calendars and locales.
*/
- (BOOL)rangeOfWeekendStartDate:(out NSDate * __nullable * __nullable)datep interval:(out nullable NSTimeInterval *)tip containingDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Returns the range of the next weekend, via two by-reference parameters, which starts strictly after the given date.
	The NSCalendarSearchBackwards option can be used to find the previous weekend range strictly before the date.
	Returns NO if there are no such things as weekend in the calendar and its locale.
	Note that a given entire Day within a calendar is not necessarily all in a weekend or not; weekends can start in the middle of a Day in some calendars and locales.
*/
- (BOOL)nextWeekendStartDate:(out NSDate * __nullable * __nullable)datep interval:(out nullable NSTimeInterval *)tip options:(NSCalendarOptions)options afterDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/* 
	This API returns the difference between two dates specified as date components.
	For units which are not specified in each NSDateComponents, but required to specify an absolute date, the base value of the unit is assumed.  For example, for an NSDateComponents with just a Year and a Month specified, a Day of 1, and an Hour, Minute, Second, and Nanosecond of 0 are assumed.
	Calendrical calculations with unspecified Year or Year value prior to the start of a calendar are not advised.
	For each date components object, if its time zone property is set, that time zone is used for it; if the calendar property is set, that is used rather than the receiving calendar, and if both the calendar and time zone are set, the time zone property value overrides the time zone of the calendar property.
	No options are currently defined; pass 0.
*/
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDateComponents:(NSDateComponents *)startingDateComp toDateComponents:(NSDateComponents *)resultDateComp options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by adding an amount of a specific component to a given date.
	The NSCalendarWrapComponents option specifies if the component should be incremented and wrap around to zero/one on overflow, and should not cause higher units to be incremented.
*/
- (nullable NSDate *)dateByAddingUnit:(NSCalendarUnit)unit value:(NSInteger)value toDate:(NSDate *)date options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This method computes the dates which match (or most closely match) a given set of components, and calls the block once for each of them, until the enumeration is stopped.
	There will be at least one intervening date which does not match all the components (or the given date itself must not match) between the given date and any result.
	If the NSCalendarSearchBackwards option is used, this method finds the previous match before the given date.  The intent is that the same matches as for a forwards search will be found (that is, if you are enumerating forwards or backwards for each hour with minute "27", the seconds in the date you will get in forwards search would obviously be 00, and the same will be true in a backwards search in order to implement this rule.  Similarly for DST backwards jumps which repeats times, you'll get the first match by default, where "first" is defined from the point of view of searching forwards.  So, when searching backwards looking for a particular hour, with no minute and second specified, you don't get a minute and second of 59:59 for the matching hour (which would be the nominal first match within a given hour, given the other rules here, when searching backwards).
	If the NSCalendarMatchStrictly option is used, the algorithm travels as far forward or backward as necessary looking for a match, but there are ultimately implementation-defined limits in how far distant the search will go.  If the NSCalendarMatchStrictly option is not specified, the algorithm searches up to the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument.  If you want to find the next Feb 29 in the Gregorian calendar, for example, you have to specify the NSCalendarMatchStrictly option to guarantee finding it.
	If an exact match is not possible, and requested with the NSCalendarMatchStrictly option, nil is passed to the block and the enumeration ends.  (Logically, since an exact match searches indefinitely into the future, if no match is found there's no point in continuing the enumeration.)

	If the NSCalendarMatchStrictly option is NOT used, exactly one option from the set {NSCalendarMatchPreviousTimePreservingSmallerUnits, NSCalendarMatchNextTimePreservingSmallerUnits, NSCalendarMatchNextTime} must be specified, or an illegal argument exception will be thrown.
	
        If the NSCalendarMatchPreviousTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the previous existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 1:37am, if that exists).
	
        If the NSCalendarMatchNextTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 3:37am, if that exists).
 
	If the NSCalendarMatchNextTime option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing time which exists (e.g., no 2:37am results in 3:00am, if that exists).
	If the NSCalendarMatchFirst option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the first occurrence.
	If the NSCalendarMatchLast option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the last occurrence.
	If neither the NSCalendarMatchFirst or NSCalendarMatchLast option is specified, the default behavior is to act as if NSCalendarMatchFirst was specified.
	There is no option to return middle occurrences of more than two occurrences of a matching time, if such exist.

	Result dates have an integer number of seconds (as if 0 was specified for the nanoseconds property of the NSDateComponents matching parameter), unless a value was set in the nanoseconds property, in which case the result date will have that number of nanoseconds (or as close as possible with floating point numbers).
	The enumeration is stopped by setting *stop = YES in the block and return.  It is not necessary to set *stop to NO to keep the enumeration going.
*/
- (void)enumerateDatesStartingAfterDate:(NSDate *)start matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)opts usingBlock:(void (^)(NSDate * __nullable date, BOOL exactMatch, BOOL *stop))block NS_AVAILABLE(10_9, 8_0);

/*
	This method computes the next date which matches (or most closely matches) a given set of components.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date found which matches a specific component value.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingUnit:(NSCalendarUnit)unit value:(NSInteger)value options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date found which matches the given hour, minute, and second values.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingHour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by setting a specific component to a given time, and trying to keep lower components the same.  If the unit already has that value, this may result in a date which is the same as the given date.
	Changing a component's value often will require higher or coupled components to change as well.  For example, setting the Weekday to Thursday usually will require the Day component to change its value, and possibly the Month and Year as well.
	If no such time exists, the next available time is returned (which could, for example, be in a different day, week, month, ... than the nominal target date).  Setting a component to something which would be inconsistent forces other units to change; for example, setting the Weekday to Thursday probably shifts the Day and possibly Month and Year.
	The specific behaviors here are as yet unspecified; for example, if I change the weekday to Thursday, does that move forward to the next, backward to the previous, or to the nearest Thursday?  A likely rule is that the algorithm will try to produce a result which is in the next-larger unit to the one given (there's a table of this mapping at the top of this document).  So for the "set to Thursday" example, find the Thursday in the Week in which the given date resides (which could be a forwards or backwards move, and not necessarily the nearest Thursday).  For forwards or backwards behavior, one can use the -nextDateAfterDate:matchingUnit:value:options: method above.
 */
- (nullable NSDate *)dateBySettingUnit:(NSCalendarUnit)unit value:(NSInteger)v ofDate:(NSDate *)date options:(NSCalendarOptions)opts NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by setting hour, minute, and second to a given time.
	If no such time exists, the next available time is returned (which could, for example, be in a different day than the nominal target date).
	The intent is to return a date on the same day as the original date argument.  This may result in a date which is earlier than the given date, of course.
 */
- (nullable NSDate *)dateBySettingHour:(NSInteger)h minute:(NSInteger)m second:(NSInteger)s ofDate:(NSDate *)date options:(NSCalendarOptions)opts NS_AVAILABLE(10_9, 8_0);


/*
    This API returns YES if the date has all the matched components. Otherwise, it returns NO.
    It is useful to test the return value of the -nextDateAfterDate:matchingUnit:value:options:, to find out if the components were obeyed or if the method had to fudge the result value due to missing time.
 */
- (BOOL)date:(NSDate *)date matchesComponents:(NSDateComponents *)components NS_AVAILABLE(10_9, 8_0);

@end


// This notification is posted through [NSNotificationCenter defaultCenter]
// when the system day changes. Register with "nil" as the object of this
// notification. If the computer/device is asleep when the day changed,
// this will be posted on wakeup. You'll get just one of these if the
// machine has been asleep for several days. The definition of "Day" is
// relative to the current calendar ([NSCalendar currentCalendar]) of the
// process and its locale and time zone. There are no guarantees that this
// notification is received by observers in a "timely" manner, same as
// with distributed notifications.

FOUNDATION_EXPORT NSString * const NSCalendarDayChangedNotification NS_AVAILABLE(10_9, 8_0);



// This is a just used as an extensible struct, basically;
// note that there are two uses: one for specifying a date
// via components (some components may be missing, making the
// specific date ambiguous), and the other for specifying a
// set of component quantities (like, 3 months and 5 hours).
// Undefined fields have (or fields can be set to) the value
// NSDateComponentUndefined.

// NSDateComponents is not responsible for answering questions
// about a date beyond the information it has been initialized
// with; for example, if you initialize one with May 6, 2004,
// and then ask for the weekday, you'll get Undefined, not Thurs.
// A NSDateComponents is meaningless in itself, because you need
// to know what calendar it is interpreted against, and you need
// to know whether the values are absolute values of the units,
// or quantities of the units.
// When you create a new one of these, all values begin Undefined.

NS_ENUM(NSInteger) {
	NSDateComponentUndefined = NSIntegerMax,

	NSUndefinedDateComponent NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSDateComponentUndefined instead") = NSDateComponentUndefined
};


@interface NSDateComponents : NSObject <NSCopying, NSSecureCoding>

@property (nullable, copy) NSCalendar *calendar NS_AVAILABLE(10_7, 4_0);
@property (nullable, copy) NSTimeZone *timeZone NS_AVAILABLE(10_7, 4_0);
@property NSInteger era;
@property NSInteger year;
@property NSInteger month;
@property NSInteger day;
@property NSInteger hour;
@property NSInteger minute;
@property NSInteger second;
@property NSInteger nanosecond NS_AVAILABLE(10_7, 5_0);
@property NSInteger weekday;
@property NSInteger weekdayOrdinal;
@property NSInteger quarter NS_AVAILABLE(10_6, 4_0);
@property NSInteger weekOfMonth NS_AVAILABLE(10_7, 5_0);
@property NSInteger weekOfYear NS_AVAILABLE(10_7, 5_0);
@property NSInteger yearForWeekOfYear NS_AVAILABLE(10_7, 5_0);
@property (getter=isLeapMonth) BOOL leapMonth NS_AVAILABLE(10_8, 6_0);
@property (nullable, readonly, copy) NSDate *date NS_AVAILABLE(10_7, 4_0);

- (NSInteger)week NS_CALENDAR_DEPRECATED(10_4, 10_9, 2_0, 7_0, "Use weekOfMonth or weekOfYear, depending on which you mean");
- (void)setWeek:(NSInteger)v NS_CALENDAR_DEPRECATED(10_4, 10_9, 2_0, 7_0, "Use setWeekOfMonth: or setWeekOfYear:, depending on which you mean");

/*
	This API allows one to set a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth properties cannot be set by this method.
*/
- (void)setValue:(NSInteger)value forComponent:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API allows one to get the value of a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth property values cannot be gotten by this method.
*/
- (NSInteger)valueForComponent:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
	The calendar property must be set, or NO is returned.
*/
@property (getter=isValidDate, readonly) BOOL validDate NS_AVAILABLE(10_9, 8_0);


/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
*/
- (BOOL)isValidDateInCalendar:(NSCalendar *)calendar NS_AVAILABLE(10_9, 8_0);


@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSKeyValueObserving.h
/*
	NSKeyValueObserving.h
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSOrderedSet.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSDictionary.h>

@class NSIndexSet, NSString;

NS_ASSUME_NONNULL_BEGIN

/* Options for use with -addObserver:forKeyPath:options:context: and -addObserver:toObjectsAtIndexes:forKeyPath:options:context:.
*/
typedef NS_OPTIONS(NSUInteger, NSKeyValueObservingOptions) {

    /* Whether the change dictionaries sent in notifications should contain NSKeyValueChangeNewKey and NSKeyValueChangeOldKey entries, respectively.
    */
    NSKeyValueObservingOptionNew = 0x01,
    NSKeyValueObservingOptionOld = 0x02,

    /* Whether a notification should be sent to the observer immediately, before the observer registration method even returns. The change dictionary in the notification will always contain an NSKeyValueChangeNewKey entry if NSKeyValueObservingOptionNew is also specified but will never contain an NSKeyValueChangeOldKey entry. (In an initial notification the current value of the observed property may be old, but it's new to the observer.) You can use this option instead of explicitly invoking, at the same time, code that is also invoked by the observer's -observeValueForKeyPath:ofObject:change:context: method. When this option is used with -addObserver:toObjectsAtIndexes:forKeyPath:options:context: a notification will be sent for each indexed object to which the observer is being added.
    */
    NSKeyValueObservingOptionInitial NS_ENUM_AVAILABLE(10_5, 2_0) = 0x04,

    /* Whether separate notifications should be sent to the observer before and after each change, instead of a single notification after the change. The change dictionary in a notification sent before a change always contains an NSKeyValueChangeNotificationIsPriorKey entry whose value is [NSNumber numberWithBool:YES], but never contains an NSKeyValueChangeNewKey entry. You can use this option when the observer's own KVO-compliance requires it to invoke one of the -willChange... methods for one of its own properties, and the value of that property depends on the value of the observed object's property. (In that situation it's too late to easily invoke -willChange... properly in response to receiving an -observeValueForKeyPath:ofObject:change:context: message after the change.)

When this option is specified, the change dictionary in a notification sent after a change contains the same entries that it would contain if this option were not specified, except for ordered unique to-many relationships represented by NSOrderedSets.  For those, for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement changes, the change dictionary for a will-change notification contains an NSKeyValueChangeIndexesKey (and NSKeyValueChangeOldKey in the case of Replacement where the NSKeyValueObservingOptionOld option was specified at registration time) which give the indexes (and objects) which *may* be changed by the operation.  The second notification, after the change, contains entries reporting what did actually change.  For NSKeyValueChangeRemoval changes, removals by index are precise.
    */
    NSKeyValueObservingOptionPrior NS_ENUM_AVAILABLE(10_5, 2_0) = 0x08

};

/* Possible values in the NSKeyValueChangeKindKey entry in change dictionaries. See the comments for -observeValueForKeyPath:ofObject:change:context: for more information.
*/
typedef NS_ENUM(NSUInteger, NSKeyValueChange) {
    NSKeyValueChangeSetting = 1,
    NSKeyValueChangeInsertion = 2,
    NSKeyValueChangeRemoval = 3,
    NSKeyValueChangeReplacement = 4,
};

/* Possible kinds of set mutation for use with -willChangeValueForKey:withSetMutation:usingObjects: and -didChangeValueForKey:withSetMutation:usingObjects:. Their semantics correspond exactly to NSMutableSet's -unionSet:, -minusSet:, -intersectSet:, and -setSet: method, respectively.
*/
typedef NS_ENUM(NSUInteger, NSKeyValueSetMutationKind) {
    NSKeyValueUnionSetMutation = 1,
    NSKeyValueMinusSetMutation = 2,
    NSKeyValueIntersectSetMutation = 3,
    NSKeyValueSetSetMutation = 4
};

/* Keys for entries in change dictionaries. See the comments for -observeValueForKeyPath:ofObject:change:context: for more information.
*/
FOUNDATION_EXPORT NSString *const NSKeyValueChangeKindKey;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeNewKey;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeOldKey;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeIndexesKey;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeNotificationIsPriorKey NS_AVAILABLE(10_5, 2_0);

@interface NSObject(NSKeyValueObserving)

/* Given that the receiver has been registered as an observer of the value at a key path relative to an object, be notified of a change to that value.

The change dictionary always contains an NSKeyValueChangeKindKey entry whose value is an NSNumber wrapping an NSKeyValueChange (use -[NSNumber unsignedIntegerValue]). The meaning of NSKeyValueChange depends on what sort of property is identified by the key path:
    - For any sort of property (attribute, to-one relationship, or ordered or unordered to-many relationship) NSKeyValueChangeSetting indicates that the observed object has received a -setValue:forKey: message, or that the key-value coding-compliant set method for the key has been invoked, or that a -willChangeValueForKey:/-didChangeValueForKey: pair has otherwise been invoked.
    - For an _ordered_ to-many relationship, NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the array returned by a -mutableArrayValueForKey: message sent to the object, or sent to the ordered set returned by a -mutableOrderedSetValueForKey: message sent to the object, or that one of the key-value coding-compliant array or ordered set mutation methods for the key has been invoked, or that a -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: pair has otherwise been invoked.
    - For an _unordered_ to-many relationship (introduced in Mac OS 10.4), NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the set returned by a -mutableSetValueForKey: message sent to the object, or that one of the key-value coding-compliant set mutation methods for the key has been invoked, or that a -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: pair has otherwise been invoked.

For any sort of property, the change dictionary contains an NSKeyValueChangeNewKey entry if NSKeyValueObservingOptionNew was specified at observer registration time, it's the right kind of change, and this isn't a prior notification. The change dictionary contains an NSKeyValueChangeOldKey if NSKeyValueObservingOptionOld was specified and it's the right kind of change. See the comments for the NSKeyValueObserverNotification informal protocol methods for what the values of those entries can be.

For an _ordered_ to-many relationship, the change dictionary always contains an NSKeyValueChangeIndexesKey entry whose value is an NSIndexSet containing the indexes of the inserted, removed, or replaced objects, unless the change is an NSKeyValueChangeSetting.

If NSKeyValueObservingOptionPrior (introduced in Mac OS 10.5) was specified at observer registration time, and this notification is one being sent prior to a change as a result, the change dictionary contains an NSKeyValueChangeNotificationIsPriorKey entry whose value is an NSNumber wrapping YES (use -[NSNumber boolValue]).

context is always the same pointer that was passed in at observer registration time.
*/
- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable id)object change:(nullable NSDictionary<NSString*, id> *)change context:(nullable void *)context;

@end

@interface NSObject(NSKeyValueObserverRegistration)

/* Register or deregister as an observer of the value at a key path relative to the receiver. The options determine what is included in observer notifications and when they're sent, as described above, and the context is passed in observer notifications as described above. You should use -removeObserver:forKeyPath:context: instead of -removeObserver:forKeyPath: whenever possible because it allows you to more precisely specify your intent. When the same observer is registered for the same key path multiple times, but with different context pointers each time, -removeObserver:forKeyPath: has to guess at the context pointer when deciding what exactly to remove, and it can guess wrong.
*/
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSArray<ObjectType>(NSKeyValueObserverRegistration)

/* Register or deregister as an observer of the values at a key path relative to each indexed element of the array. The options determine what is included in observer notifications and when they're sent, as described above, and the context is passed in observer notifications as described above. These are not merely convenience methods; invoking them is potentially much faster than repeatedly invoking NSObject(NSKeyValueObserverRegistration) methods. You should use -removeObserver:fromObjectsAtIndexes:forKeyPath:context: instead of -removeObserver:fromObjectsAtIndexes:forKeyPath: whenever possible for the same reason described in the NSObject(NSKeyValueObserverRegistration) comment.
*/
- (void)addObserver:(NSObject *)observer toObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer fromObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer fromObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath;

/* NSArrays are not observable, so these methods raise exceptions when invoked on NSArrays. Instead of observing an array, observe the ordered to-many relationship for which the array is the collection of related objects.
*/
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSOrderedSet<ObjectType>(NSKeyValueObserverRegistration)

/* NSOrderedSets are not observable, so these methods raise exceptions when invoked on NSOrderedSets. Instead of observing an ordered set, observe the ordered to-many relationship for which the ordered set is the collection of related objects.
*/
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSSet<ObjectType>(NSKeyValueObserverRegistration)

/* NSSets are not observable, so these methods raise exceptions when invoked on NSSets. Instead of observing a set, observe the unordered to-many relationship for which the set is the collection of related objects.
*/
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSObject(NSKeyValueObserverNotification)

/* Given a key that identifies a property (attribute, to-one relationship, or ordered or unordered to-many relationship), send -observeValueForKeyPath:ofObject:change:context: notification messages of kind NSKeyValueChangeSetting to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. Invocations of these methods must always be paired.

The change dictionaries in notifications resulting from use of these methods contain optional entries if requested at observer registration time:
    - The NSKeyValueChangeOldKey entry, if present, contains the value returned by -valueForKey: at the instant that -willChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
    - The NSKeyValueChangeNewKey entry, if present, contains the value returned by -valueForKey: at the instant that -didChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
*/
- (void)willChangeValueForKey:(NSString *)key;
- (void)didChangeValueForKey:(NSString *)key;

/* Given a key that identifies an _ordered_ to-many relationship, send -observeValueForKeyPath:ofObject:change:context: notification messages of the passed-in change kind to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. The passed-in kind must be NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, or NSKeyValueChangeReplacement. The passed-in index set must be the indexes of the objects being inserted, removed, or replaced. Invocations of these methods must always be paired, with identical arguments.

The change dictionaries in notifications resulting from use of these methods contain optional entries if requested at observer registration time:
    - The NSKeyValueChangeOldKey entry, if present (only for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -willChangeValueForKey:valuesAtIndexes:forKey: is invoked.
    - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -didChangeValueForKey:valuesAtIndexes:forKey: is invoked.
*/
- (void)willChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;
- (void)didChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;

/* Given a key that identifies an _unordered_ to-many relationship, send -observeValueForKeyPath:ofObject:change:context: notification messages to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. The passed-in mutation kind corresponds to an NSMutableSet method. The passed-in set must contain the set that would be passed to the corresponding NSMutableSet method. Invocations of these methods must always be paired, with identical arguments.

The value of the NSKeyValueChangeKindKey entry in change dictionaries in notifications resulting from use of these methods depends on the passed-in mutationKind value:
    - NSKeyValueUnionSetMutation -> NSKeyValueChangeInsertion
    - NSKeyValueMinusSetMutation -> NSKeyValueChangeRemoval
    - NSKeyValueIntersectSetMutation -> NSKeyValueChangeRemoval
    - NSKeyValueSetSetMutation -> NSKeyValueChangeReplacement

The change dictionaries may also contain optional entries:
    - The NSKeyValueChangeOldKey entry, if present (only for for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains the set of objects that were removed.
    - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains the set of objects that were added.
*/
- (void)willChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;
- (void)didChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;

@end

@interface NSObject(NSKeyValueObservingCustomization)

/* Return a set of key paths for properties whose values affect the value of the keyed property. When an observer for the key is registered with an instance of the receiving class, KVO itself automatically observes all of the key paths for the same instance, and sends change notifications for the key to the observer when the value for any of those key paths changes. The default implementation of this method searches the receiving class for a method whose name matches the pattern +keyPathsForValuesAffecting<Key>, and returns the result of invoking that method if it is found. So, any such method must return an NSSet too. If no such method is found, an NSSet that is computed from information provided by previous invocations of the now-deprecated +setKeys:triggerChangeNotificationsForDependentKey: method is returned, for backward binary compatibility.

This method and KVO's automatic use of it comprise a dependency mechanism that you can use instead of sending -willChangeValueForKey:/-didChangeValueForKey: messages for dependent, computed, properties.
 
You can override this method when the getter method of one of your properties computes a value to return using the values of other properties, including those that are located by key paths. Your override should typically invoke super and return a set that includes any members in the set that result from doing that (so as not to interfere with overrides of this method in superclasses).

You can't really override this method when you add a computed property to an existing class using a category, because you're not supposed to override methods in categories. In that case, implement a matching +keyPathsForValuesAffecting<Key> to take advantage of this mechanism.
*/
+ (NSSet<NSString *> *)keyPathsForValuesAffectingValueForKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);

/* Return YES if the key-value observing machinery should automatically invoke -willChangeValueForKey:/-didChangeValueForKey:, -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey:, or -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: whenever instances of the class receive key-value coding messages for the key, or mutating key-value coding-compliant methods for the key are invoked. Return NO otherwise. Starting in Mac OS 10.5, the default implementation of this method searches the receiving class for a method whose name matches the pattern +automaticallyNotifiesObserversOf<Key>, and returns the result of invoking that method if it is found. So, any such method must return BOOL too. If no such method is found YES is returned.
*/
+ (BOOL)automaticallyNotifiesObserversForKey:(NSString *)key;

/* Take or return a pointer that identifies information about all of the observers that are registered with the receiver, the options that were used at registration-time, etc. The default implementation of these methods store observation info in a global dictionary keyed by the receivers' pointers. For improved performance, you can override these methods to store the opaque data pointer in an instance variable. Overrides of these methods must not attempt to send Objective-C messages to the passed-in observation info, including -retain and -release.
*/
@property (nullable) void *observationInfo NS_RETURNS_INNER_POINTER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@interface NSObject(NSDeprecatedKeyValueObservingCustomization)

/* A method that was deprecated in Mac OS 10.5, in favor of using +keyPathsForValuesAffectingValueForKey:. Registers the fact that invocations of -willChangeValueForKey:/-didChangeValueForKey:, -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey:, and -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: for any key in the passed-in array should also send notifications for the dependent key.
*/
+ (void)setKeys:(NSArray *)keys triggerChangeNotificationsForDependentKey:(NSString *)dependentKey NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

@end 

#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSMassFormatter.h
/*      NSMassFormatter.h
        Copyright (c) 2014-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>

@class NSNumberFormatter;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSMassFormatterUnit) {
    NSMassFormatterUnitGram = 11,
    NSMassFormatterUnitKilogram = 14,
    NSMassFormatterUnitOunce = (6 << 8) + 1,
    NSMassFormatterUnitPound = (6 << 8) + 2,
    NSMassFormatterUnitStone = (6 << 8) + 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSMassFormatter : NSFormatter {
@private
    void *_formatter;
    BOOL _isForPersonMassUse;
    void *_reserved[2];
}

@property (null_resettable, copy) NSNumberFormatter *numberFormatter;    // default is NSNumberFormatter with NSNumberFormatterDecimalStyle
@property NSFormattingUnitStyle unitStyle;              // default is NSFormattingUnitStyleMedium
@property (getter = isForPersonMassUse) BOOL forPersonMassUse;  // default is NO; if it is set to YES, the number argument for -stringFromKilograms: and -unitStringFromKilograms: is considered as a person’s mass

// Format a combination of a number and an unit to a localized string.
- (NSString *)stringFromValue:(double)value unit:(NSMassFormatterUnit)unit;

// Format a number in kilograms to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 1.2kg = 2.64lb in the US locale).
- (NSString *)stringFromKilograms:(double)numberInKilograms;

// Return a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSMassFormatterUnit)unit;

// Return the locale-appropriate unit, the same unit used by -stringFromKilograms:.
- (NSString *)unitStringFromKilograms:(double)numberInKilograms usedUnit:(nullable NSMassFormatterUnit *)unitp;

// No parsing is supported. This method will return NO.
- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string errorDescription:(out NSString * __nullable * __nullable)error;
@end

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSError.h
/*	NSError.h
	Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary, NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

// Predefined domain for errors from most AppKit and Foundation APIs.
FOUNDATION_EXPORT NSString *const NSCocoaErrorDomain;

// Other predefined domains; value of "code" will correspond to preexisting values in these domains.
FOUNDATION_EXPORT NSString *const NSPOSIXErrorDomain;
FOUNDATION_EXPORT NSString *const NSOSStatusErrorDomain;
FOUNDATION_EXPORT NSString *const NSMachErrorDomain;

// Key in userInfo. A recommended standard way to embed NSErrors from underlying calls. The value of this key should be an NSError.
FOUNDATION_EXPORT NSString *const NSUnderlyingErrorKey;

// Keys in userInfo, for subsystems wishing to provide their error messages up-front. Note that NSError will also consult the userInfoValueProvider for the domain when these values are not present in the userInfo dictionary.
FOUNDATION_EXPORT NSString *const NSLocalizedDescriptionKey;             // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedFailureReasonErrorKey;      // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoverySuggestionErrorKey; // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoveryOptionsErrorKey;    // NSArray of NSStrings
FOUNDATION_EXPORT NSString *const NSRecoveryAttempterErrorKey;           // Instance of a subclass of NSObject that conforms to the NSErrorRecoveryAttempting informal protocol
FOUNDATION_EXPORT NSString *const NSHelpAnchorErrorKey;                  // NSString containing a help anchor

// Other standard keys in userInfo, for various error codes
FOUNDATION_EXPORT NSString *const NSStringEncodingErrorKey ;  // NSNumber containing NSStringEncoding
FOUNDATION_EXPORT NSString *const NSURLErrorKey;              // NSURL
FOUNDATION_EXPORT NSString *const NSFilePathErrorKey;         // NSString



@interface NSError : NSObject <NSCopying, NSSecureCoding> {
    @private
    void *_reserved;
    NSInteger _code;
    NSString *_domain;
    NSDictionary *_userInfo;
}

/* Domain cannot be nil; dict may be nil if no userInfo desired.
*/
- (instancetype)initWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(nullable NSDictionary *)dict NS_DESIGNATED_INITIALIZER;
+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(nullable NSDictionary *)dict;

/* These define the error. Domains are described by names that are arbitrary strings used to differentiate groups of codes; for custom domain using reverse-DNS naming will help avoid conflicts. Codes are domain-specific.
*/
@property (readonly, copy) NSString *domain;
@property (readonly) NSInteger code;

/* Additional info which may be used to describe the error further. Examples of keys that might be included in here are "Line Number", "Failed URL", etc. Embedding other errors in here can also be used as a way to communicate underlying reasons for failures; for instance "File System Error" embedded in the userInfo of an NSError returned from a higher level document object. If the embedded error information is itself NSError, the standard key NSUnderlyingErrorKey can be used.
*/
@property (readonly, copy) NSDictionary *userInfo;

/* The primary user-presentable message for the error, for instance for NSFileReadNoPermissionError: "The file "File Name" couldn't be opened because you don't have permission to view it.". By default this looks for NSLocalizedDescriptionKey in the user info. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, it manufactures a last-resort string from the domain and code. This manufactured result is likely not suitable for presentation to the user, but can be used in logs or debugging.
*/
@property (readonly, copy) NSString *localizedDescription;

/* Return a complete sentence which describes why the operation failed. For instance, for NSFileReadNoPermissionError: "You don't have permission.". In many cases this will be just the "because" part of the error message (but as a complete sentence, which makes localization easier).  Default implementation of this picks up the value of NSLocalizedFailureReasonErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *localizedFailureReason;

/* Return the string that can be displayed as the "informative" (aka "secondary") message on an alert panel. For instance, for NSFileReadNoPermissionError: "To view or change permissions, select the item in the Finder and choose File > Get Info.". Default implementation of this picks up the value of NSLocalizedRecoverySuggestionErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *localizedRecoverySuggestion;

/* Return titles of buttons that are appropriate for displaying in an alert. These should match the string provided as a part of localizedRecoverySuggestion.  The first string would be the title of the right-most and default button, the second one next to it, and so on. If used in an alert the corresponding default return values are NSAlertFirstButtonReturn + n. Default implementation of this picks up the value of NSLocalizedRecoveryOptionsErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil. nil return usually implies no special suggestion, which would imply a single "OK" button.
*/
@property (nullable, readonly, copy) NSArray<NSString *> *localizedRecoveryOptions;

/* Return an object that conforms to the NSErrorRecoveryAttempting informal protocol. The recovery attempter must be an object that can correctly interpret an index into the array returned by localizedRecoveryOptions. The default implementation of this picks up the value of NSRecoveryAttempterErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain. If that returns nil, this also returns nil.
*/
@property (nullable, readonly, strong) id recoveryAttempter;

/* Return the help anchor that can be used to create a help button to accompany the error when it's displayed to the user.  This is done automatically by +[NSAlert alertWithError:], which the presentError: variants in NSApplication go through. The default implementation of this picks up the value of the NSHelpAnchorErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain.  If that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *helpAnchor;


/* Specify a block which will be called from the implementations of localizedDescription, localizedFailureReason, localizedRecoverySuggestion, localizedRecoveryOptions, recoveryAttempter, and helpAnchor, when the underlying value for these is not present in the userInfo dictionary of NSError instances with the specified domain.  The provider will be called with the userInfo key corresponding to the queried property: For instance, NSLocalizedDescriptionKey for localizedDescription.  The provider should return nil for any keys it is not able to provide and, very importantly, any keys it does not recognize (since we may extend the list of keys in future releases).

The specified block will be called synchronously at the time when the above properties are queried. The results are not cached.

This provider is optional. It enables localization and formatting of error messages to be done lazily; rather than populating the userInfo at NSError creation time, these keys will be fetched on-demand when asked for.
 
It is expected that only the “owner” of an NSError domain specifies the provider for the domain, and this is done once. This facility is not meant for consumers of errors to customize the userInfo entries.  This facility should not be used to customize the behaviors of error domains provided by the system.
 
If an appropriate result for the requested key cannot be provided, return nil rather than choosing to manufacture a generic fallback response such as "Operation could not be completed, error 42." NSError will take care of the fallback cases.
*/
+ (void)setUserInfoValueProviderForDomain:(NSString *)errorDomain provider:(id __nullable (^ __nullable)(NSError *err, NSString *userInfoKey))provider NS_AVAILABLE(10_11, 9_0);
+ (id __nullable (^ __nullable)(NSError *err, NSString *userInfoKey))userInfoValueProviderForDomain:(NSString *)errorDomain NS_AVAILABLE(10_11, 9_0);

@end


@interface NSObject(NSErrorRecoveryAttempting)

/* Given that an error alert has been presented document-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and send the selected message to the specified delegate. The option index is an index into the error's array of localized recovery options. The method selected by didRecoverSelector must have the same signature as:

    - (void)didPresentErrorWithRecovery:(BOOL)didRecover contextInfo:(void *)contextInfo;

The value passed for didRecover must be YES if error recovery was completely successful, NO otherwise.
*/
- (void)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex delegate:(nullable id)delegate didRecoverSelector:(nullable SEL)didRecoverSelector contextInfo:(nullable void *)contextInfo;

/* Given that an error alert has been presented applicaton-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and return YES if error recovery was completely successful, NO otherwise. The recovery option index is an index into the error's array of localized recovery options.
*/
- (BOOL)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex;

@end

NS_ASSUME_NONNULL_END

// ==========  Foundation.framework/Headers/NSPointerArray.h
/*
 *  NSPointerArray.h
 *  Copyright (c) 2005-2015, Apple Inc. All rights reserved.
 *
 */
 

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSPointerFunctions.h>

NS_ASSUME_NONNULL_BEGIN

/*
   NSPointerArray.h

   A PointerArray acts like a traditional array that slides elements on insertion or deletion.
   Unlike traditional arrays, it holds NULLs, which can be inserted or extracted (and contribute to count).
   Also unlike traditional arrays, the 'count' of the array may be set directly.
   Using NSPointerFunctionsWeakMemory object references will turn to NULL on last release (or when collected under GC).

   The copying and archiving protocols are applicable only when NSPointerArray is configured for Object uses.
   The fast enumeration protocol (supporting the for..in statement) will yield NULLs if present.  It is defined for all types of pointers although the language syntax doesn't directly support this.
*/

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSPointerArray : NSObject <NSFastEnumeration, NSCopying, NSCoding>
// construction
- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithPointerFunctions:(NSPointerFunctions *)functions NS_DESIGNATED_INITIALIZER;

+ (NSPointerArray *)pointerArrayWithOptions:(NSPointerFunctionsOptions)options;
+ (NSPointerArray *)pointerArrayWithPointerFunctions:(NSPointerFunctions *)functions;

/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
@property (readonly, copy) NSPointerFunctions *pointerFunctions;

- (nullable void *)pointerAtIndex:(NSUInteger)index;

// Array like operations that slide or grow contents, including NULLs
- (void)addPointer:(nullable void *)pointer;  // add pointer at index 'count'
- (void)removePointerAtIndex:(NSUInteger)index;    // everything above index, including holes, slide lower
- (void)insertPointer:(nullable void *)item atIndex:(NSUInteger)index;  // everything at & above index, including holes, slide higher

- (void)replacePointerAtIndex:(NSUInteger)index withPointer:(nullable void *)item;  // O(1); NULL item is okay; index must be < count

- (void)compact;   // eliminate NULLs

// Getter: the number of elements in the array, including NULLs
// Setter: sets desired number of elements, adding NULLs or removing items as necessary.
@property NSUInteger count;

@end


@interface NSPointerArray (NSPointerArrayConveniences)  

// construction
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
+ (id) pointerArrayWithStrongObjects NS_DEPRECATED_MAC(10_5, 10_8); // strong objects
+ (id) pointerArrayWithWeakObjects NS_DEPRECATED_MAC(10_5, 10_8); // weak objects
#endif

+ (NSPointerArray *)strongObjectsPointerArray NS_AVAILABLE(10_8, 6_0);
+ (NSPointerArray *)weakObjectsPointerArray NS_AVAILABLE(10_8, 6_0);

@property (readonly, copy) NSArray *allObjects;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSString.h
/*	NSString.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

typedef unsigned short unichar;

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <stdarg.h>

@class NSData, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSCharacterSet, NSURL, NSError, NSLocale;

NS_ASSUME_NONNULL_BEGIN

/* These options apply to the various search/find and comparison methods (except where noted).
*/
typedef NS_OPTIONS(NSUInteger, NSStringCompareOptions) {
    NSCaseInsensitiveSearch = 1,
    NSLiteralSearch = 2,		/* Exact character-by-character equivalence */
    NSBackwardsSearch = 4,		/* Search from end of source string */
    NSAnchoredSearch = 8,		/* Search is limited to start (or end, if NSBackwardsSearch) of source string */
    NSNumericSearch = 64,		/* Added in 10.2; Numbers within strings are compared using numeric value, that is, Foo2.txt < Foo7.txt < Foo25.txt; only applies to compare methods, not find */
    NSDiacriticInsensitiveSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 128, /* If specified, ignores diacritics (o-umlaut == o) */
    NSWidthInsensitiveSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 256, /* If specified, ignores width differences ('a' == UFF41) */
    NSForcedOrderingSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 512, /* If specified, comparisons are forced to return either NSOrderedAscending or NSOrderedDescending if the strings are equivalent but not strictly equal, for stability when sorting (e.g. "aaa" > "AAA" with NSCaseInsensitiveSearch specified) */
    NSRegularExpressionSearch NS_ENUM_AVAILABLE(10_7, 3_2) = 1024    /* Applies to rangeOfString:..., stringByReplacingOccurrencesOfString:..., and replaceOccurrencesOfString:... methods only; the search string is treated as an ICU-compatible regular expression; if set, no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch */
};

/* Note that in addition to the values explicitly listed below, NSStringEncoding supports encodings provided by CFString.
See CFStringEncodingExt.h for a list of these encodings.
See CFString.h for functions which convert between NSStringEncoding and CFStringEncoding.
*/
typedef NSUInteger NSStringEncoding;
NS_ENUM(NSStringEncoding) {
    NSASCIIStringEncoding = 1,		/* 0..127 only */
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,
    NSShiftJISStringEncoding = 8,          /* kCFStringEncodingDOSJapanese */
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10,
    NSWindowsCP1251StringEncoding = 11,    /* Cyrillic; same as AdobeStandardCyrillic */
    NSWindowsCP1252StringEncoding = 12,    /* WinLatin1 */
    NSWindowsCP1253StringEncoding = 13,    /* Greek */
    NSWindowsCP1254StringEncoding = 14,    /* Turkish */
    NSWindowsCP1250StringEncoding = 15,    /* WinLatin2 */
    NSISO2022JPStringEncoding = 21,        /* ISO 2022 Japanese encoding for e-mail */
    NSMacOSRomanStringEncoding = 30,

    NSUTF16StringEncoding = NSUnicodeStringEncoding,      /* An alias for NSUnicodeStringEncoding */

    NSUTF16BigEndianStringEncoding = 0x90000100,          /* NSUTF16StringEncoding encoding with explicit endianness specified */
    NSUTF16LittleEndianStringEncoding = 0x94000100,       /* NSUTF16StringEncoding encoding with explicit endianness specified */

    NSUTF32StringEncoding = 0x8c000100,                   
    NSUTF32BigEndianStringEncoding = 0x98000100,          /* NSUTF32StringEncoding encoding with explicit endianness specified */
    NSUTF32LittleEndianStringEncoding = 0x9c000100        /* NSUTF32StringEncoding encoding with explicit endianness specified */
};

typedef NS_OPTIONS(NSUInteger, NSStringEncodingConversionOptions) {
    NSStringEncodingConversionAllowLossy = 1,
    NSStringEncodingConversionExternalRepresentation = 2
};


@interface NSString : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

#pragma mark *** String funnel methods ***

/* NSString primitives. A minimal subclass of NSString just needs to implement these two, along with an init method appropriate for that subclass. We also recommend overriding getCharacters:range: for performance.
 */
@property (readonly) NSUInteger length;
- (unichar)characterAtIndex:(NSUInteger)index;

/* The initializers available to subclasses. See further below for additional init methods.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSString (NSStringExtensionMethods)

#pragma mark *** Substrings ***

/* To avoid breaking up character sequences such as Emoji, you can do:
    [str substringFromIndex:[str rangeOfComposedCharacterSequenceAtIndex:index].location]
    [str substringToIndex:NSMaxRange([str rangeOfComposedCharacterSequenceAtIndex:index])]
    [str substringWithRange:[str rangeOfComposedCharacterSequencesForRange:range]
*/
- (NSString *)substringFromIndex:(NSUInteger)from;
- (NSString *)substringToIndex:(NSUInteger)to;
- (NSString *)substringWithRange:(NSRange)range;                // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences

- (void)getCharacters:(unichar *)buffer range:(NSRange)range;   // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences


#pragma mark *** String comparison and equality ***

/* In the compare: methods, the range argument specifies the subrange, rather than the whole, of the receiver to use in the comparison. The range is not applied to the search string.  For example, [@"AB" compare:@"ABC" options:0 range:NSMakeRange(0,1)] compares "A" to "ABC", not "A" to "A", and will return NSOrderedAscending.
*/
- (NSComparisonResult)compare:(NSString *)string;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)compareRange;
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)compareRange locale:(nullable id)locale; // locale arg used to be a dictionary pre-Leopard. We now accept NSLocale. Assumes the current locale if non-nil and non-NSLocale. nil continues to mean canonical compare, which doesn't depend on user's locale choice.
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;
- (NSComparisonResult)localizedCompare:(NSString *)string;
- (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;

/* localizedStandardCompare:, added in 10.6, should be used whenever file names or other strings are presented in lists and tables where Finder-like sorting is appropriate.  The exact behavior of this method may be tweaked in future releases, and will be different under different localizations, so clients should not depend on the exact sorting order of the strings.
*/
- (NSComparisonResult)localizedStandardCompare:(NSString *)string NS_AVAILABLE(10_6, 4_0);

- (BOOL)isEqualToString:(NSString *)aString;


#pragma mark *** String searching ***

/* These perform locale unaware prefix or suffix match. If you need locale awareness, use rangeOfString:options:range:locale:, passing NSAnchoredSearch (or'ed with NSBackwardsSearch for suffix, and NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch if needed) for options, NSMakeRange(0, [receiver length]) for range, and [NSLocale currentLocale] for locale.
*/
- (BOOL)hasPrefix:(NSString *)str;
- (BOOL)hasSuffix:(NSString *)str;

- (NSString *)commonPrefixWithString:(NSString *)str options:(NSStringCompareOptions)mask;

/* Simple convenience methods for string searching. containsString: returns YES if the target string is contained within the receiver. Same as calling rangeOfString:options: with no options, thus doing a case-sensitive, locale-unaware search. localizedCaseInsensitiveContainsString: is the case-insensitive variant which also takes the current locale into effect. Starting in 10.11 and iOS9, the new localizedStandardRangeOfString: or localizedStandardContainsString: APIs are even better convenience methods for user level searching.   More sophisticated needs can be achieved by calling rangeOfString:options:range:locale: directly.
*/
- (BOOL)containsString:(NSString *)str NS_AVAILABLE(10_10, 8_0);
- (BOOL)localizedCaseInsensitiveContainsString:(NSString *)str NS_AVAILABLE(10_10, 8_0);

/* The following two are the most appropriate methods for doing user-level string searches, similar to how searches are done generally in the system.  The search is locale-aware, case and diacritic insensitive. As with other APIs, "standard" in the name implies "system default behavior," so the exact list of search options applied may change over time.  If you need more control over the search options, please use the rangeOfString:options:range:locale: method. You can pass [NSLocale currentLocale] for searches in user's locale.
*/
- (BOOL)localizedStandardContainsString:(NSString *)str NS_AVAILABLE(10_11, 9_0);
- (NSRange)localizedStandardRangeOfString:(NSString *)str NS_AVAILABLE(10_11, 9_0);

/* These methods perform string search, looking for the searchString within the receiver string.  These return length==0 if the target string is not found. So, to check for containment: ([str rangeOfString:@"target"].length > 0).  Note that the length of the range returned by these methods might be different than the length of the target string, due composed characters and such.
 
Note that the first three methods do not take locale arguments, and perform the search in a non-locale aware fashion, which is not appropriate for user-level searching. To do user-level string searching, use the last method, specifying locale:[NSLocale currentLocale], or better yet, use localizedStandardRangeOfString: or localizedStandardContainsString:.
*/
- (NSRange)rangeOfString:(NSString *)searchString;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)searchRange;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)searchRange locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* These return the range of the first character from the set in the string, not the range of a sequence of characters. 
*/
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask range:(NSRange)searchRange;

- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(NSUInteger)index;
- (NSRange)rangeOfComposedCharacterSequencesForRange:(NSRange)range NS_AVAILABLE(10_5, 2_0);

- (NSString *)stringByAppendingString:(NSString *)aString;
- (NSString *)stringByAppendingFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);


#pragma mark *** Extracting numeric values ***

/* The following convenience methods all skip initial space characters (whitespaceSet) and ignore trailing characters. They are not locale-aware. NSScanner or NSNumberFormatter can be used for more powerful and locale-aware parsing of numbers.
*/
@property (readonly) double doubleValue;
@property (readonly) float floatValue;
@property (readonly) int intValue;
@property (readonly) NSInteger integerValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) long long longLongValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) BOOL boolValue NS_AVAILABLE(10_5, 2_0);  // Skips initial space characters (whitespaceSet), or optional -/+ sign followed by zeroes. Returns YES on encountering one of "Y", "y", "T", "t", or a digit 1-9. It ignores any trailing characters.


#pragma mark *** Case changing ***

/* The following three return the canonical (non-localized) mappings. They are suitable for programming operations that require stable results not depending on the user's locale preference.  For locale-aware case mapping for strings presented to users, use the "localized" methods below.
*/
@property (readonly, copy) NSString *uppercaseString;
@property (readonly, copy) NSString *lowercaseString;
@property (readonly, copy) NSString *capitalizedString;

/* The following three return the locale-aware case mappings. They are suitable for strings presented to the user.
*/
@property (readonly, copy) NSString *localizedUppercaseString NS_AVAILABLE(10_11, 9_0);
@property (readonly, copy) NSString *localizedLowercaseString NS_AVAILABLE(10_11, 9_0);
@property (readonly, copy) NSString *localizedCapitalizedString NS_AVAILABLE(10_11, 9_0);

/* The following methods perform localized case mappings based on the locale specified. Passing nil indicates the canonical mapping.  For the user preference locale setting, specify +[NSLocale currentLocale].
*/
- (NSString *)uppercaseStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);
- (NSString *)lowercaseStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);
- (NSString *)capitalizedStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);


#pragma mark *** Finding lines, sentences, words, etc ***

- (void)getLineStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)lineEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)lineRangeForRange:(NSRange)range;

- (void)getParagraphStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)parEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
- (NSRange)paragraphRangeForRange:(NSRange)range;

typedef NS_OPTIONS(NSUInteger, NSStringEnumerationOptions) {
    // Pass in one of the "By" options:
    NSStringEnumerationByLines = 0,                       // Equivalent to lineRangeForRange:
    NSStringEnumerationByParagraphs = 1,                  // Equivalent to paragraphRangeForRange:
    NSStringEnumerationByComposedCharacterSequences = 2,  // Equivalent to rangeOfComposedCharacterSequencesForRange:
    NSStringEnumerationByWords = 3,
    NSStringEnumerationBySentences = 4,
    // ...and combine any of the desired additional options:
    NSStringEnumerationReverse = 1UL << 8,
    NSStringEnumerationSubstringNotRequired = 1UL << 9,
    NSStringEnumerationLocalized = 1UL << 10              // User's default locale
};

/* In the enumerate methods, the blocks will be invoked inside an autorelease pool, so any values assigned inside the block should be retained.
*/
- (void)enumerateSubstringsInRange:(NSRange)range options:(NSStringEnumerationOptions)opts usingBlock:(void (^)(NSString * __nullable substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateLinesUsingBlock:(void (^)(NSString *line, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);


#pragma mark *** Character encoding and converting to/from c-string representations ***

@property (nullable, readonly) __strong const char *UTF8String NS_RETURNS_INNER_POINTER;	// Convenience to return null-terminated UTF8 representation

@property (readonly) NSStringEncoding fastestEncoding;    	// Result in O(1) time; a rough estimate
@property (readonly) NSStringEncoding smallestEncoding;   	// Result in O(n) time; the encoding in which the string is most compact

- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;   // External representation
- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding;                                    // External representation

- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

/* Methods to convert NSString to a NULL-terminated cString using the specified encoding. Note, these are the "new" cString methods, and are not deprecated like the older cString methods which do not take encoding arguments.
*/
- (nullable __strong const char *)cStringUsingEncoding:(NSStringEncoding)encoding NS_RETURNS_INNER_POINTER;	// "Autoreleased"; NULL return if encoding conversion not possible; for performance reasons, lifetime of this should not be considered longer than the lifetime of the receiving string (if the receiver string is freed, this might go invalid then, before the end of the autorelease scope)
- (BOOL)getCString:(char *)buffer maxLength:(NSUInteger)maxBufferCount encoding:(NSStringEncoding)encoding;	// NO return if conversion not possible due to encoding errors or too small of a buffer. The buffer should include room for maxBufferCount bytes; this number should accomodate the expected size of the return value plus the NULL termination character, which this method adds. (So note that the maxLength passed to this method is one more than the one you would have passed to the deprecated getCString:maxLength:.)

/* Use this to convert string section at a time into a fixed-size buffer, without any allocations.  Does not NULL-terminate. 
    buffer is the buffer to write to; if NULL, this method can be used to computed size of needed buffer.
    maxBufferCount is the length of the buffer in bytes. It's a good idea to make sure this is at least enough to hold one character's worth of conversion. 
    usedBufferCount is the length of the buffer used up by the current conversion. Can be NULL.
    encoding is the encoding to convert to.
    options specifies the options to apply.
    range is the range to convert.
    leftOver is the remaining range. Can be NULL.
    YES return indicates some characters were converted. Conversion might usually stop when the buffer fills, 
      but it might also stop when the conversion isn't possible due to the chosen encoding. 
*/
- (BOOL)getBytes:(nullable void *)buffer maxLength:(NSUInteger)maxBufferCount usedLength:(nullable NSUInteger *)usedBufferCount encoding:(NSStringEncoding)encoding options:(NSStringEncodingConversionOptions)options range:(NSRange)range remainingRange:(nullable NSRangePointer)leftover;

/* These return the maximum and exact number of bytes needed to store the receiver in the specified encoding in non-external representation. The first one is O(1), while the second one is O(n). These do not include space for a terminating null.
*/
- (NSUInteger)maximumLengthOfBytesUsingEncoding:(NSStringEncoding)enc;	// Result in O(1) time; the estimate may be way over what's needed. Returns 0 on error (overflow)
- (NSUInteger)lengthOfBytesUsingEncoding:(NSStringEncoding)enc;		// Result in O(n) time; the result is exact. Returns 0 on error (cannot convert to specified encoding, or overflow)

+ (const NSStringEncoding *)availableStringEncodings;
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

/* User-dependent encoding whose value is derived from user's default language and potentially other factors. The use of this encoding might sometimes be needed when interpreting user documents with unknown encodings, in the absence of other hints.  This encoding should be used rarely, if at all. Note that some potential values here might result in unexpected encoding conversions of even fairly straightforward NSString content --- for instance, punctuation characters with a bidirectional encoding.
 */
+ (NSStringEncoding)defaultCStringEncoding;	// Should be rarely used


#pragma mark *** Other ***

@property (readonly, copy) NSString *decomposedStringWithCanonicalMapping;
@property (readonly, copy) NSString *precomposedStringWithCanonicalMapping;
@property (readonly, copy) NSString *decomposedStringWithCompatibilityMapping;
@property (readonly, copy) NSString *precomposedStringWithCompatibilityMapping;

- (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;
- (NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator NS_AVAILABLE(10_5, 2_0);

- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;
- (NSString *)stringByPaddingToLength:(NSUInteger)newLength withString:(NSString *)padString startingAtIndex:(NSUInteger)padIndex;

/* Returns a string with the character folding options applied. theOptions is a mask of compare flags with *InsensitiveSearch suffix.
*/
- (NSString *)stringByFoldingWithOptions:(NSStringCompareOptions)options locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string in the specified range with replacement. Specified compare options are used for matching target. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string with replacement. Invokes the above method with 0 options and range of the whole string.
*/
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

/* Replace characters in range with the specified string, returning new string.
*/
- (NSString *)stringByReplacingCharactersInRange:(NSRange)range withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

/* Perform string transliteration.  The transformation represented by transform is applied to the receiver. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return nil; otherwise the transformed string value is returned (even if no characters are actually transformed). You can pass one of the predefined transforms below (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
*/
- (nullable NSString *)stringByApplyingTransform:(NSString *)transform reverse:(BOOL)reverse NS_AVAILABLE(10_11, 9_0);	// Returns nil if reverse not applicable or transform is invalid

FOUNDATION_EXPORT NSString * const NSStringTransformLatinToKatakana         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToHiragana         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToHangul           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToArabic           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToHebrew           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToThai             NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToCyrillic         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformLatinToGreek            NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformToLatin                 NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformMandarinToLatin         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformHiraganaToKatakana      NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformFullwidthToHalfwidth    NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformToXMLHex                NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformToUnicodeName           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformStripCombiningMarks     NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSString * const NSStringTransformStripDiacritics         NS_AVAILABLE(10_11, 9_0);


/* Write to specified url or path using the specified encoding.  The optional error return is to indicate file system or encoding errors.
 */
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

@property (readonly, copy) NSString *description;

@property (readonly) NSUInteger hash;


#pragma mark *** Initializers ***

/* In general creation methods in NSString do not apply to subclassers, as subclassers are assumed to provide their own init methods which create the string in the way the subclass wishes.  Designated initializers of NSString are thus init and initWithCoder:.
*/
- (instancetype)initWithCharactersNoCopy:(unichar *)characters length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
- (instancetype)initWithCharacters:(const unichar *)characters length:(NSUInteger)length;
- (nullable instancetype)initWithUTF8String:(const char *)nullTerminatedCString;
- (instancetype)initWithString:(NSString *)aString;
- (instancetype)initWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (instancetype)initWithFormat:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale, ... NS_FORMAT_FUNCTION(1,3);
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
- (nullable instancetype)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
- (nullable instancetype)initWithBytes:(const void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding;
- (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */

+ (instancetype)string;
+ (instancetype)stringWithString:(NSString *)string;
+ (instancetype)stringWithCharacters:(const unichar *)characters length:(NSUInteger)length;
+ (nullable instancetype)stringWithUTF8String:(const char *)nullTerminatedCString;
+ (instancetype)stringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
+ (instancetype)localizedStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

- (nullable instancetype)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding;
+ (nullable instancetype)stringWithCString:(const char *)cString encoding:(NSStringEncoding)enc;

/* These use the specified encoding.  If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
- (nullable instancetype)initWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;

/* These try to determine the encoding, and return the encoding which was used.  Note that these methods might get "smarter" in subsequent releases of the system, and use additional techniques for recognizing encodings. If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
- (nullable instancetype)initWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;

@end


@interface NSString (NSStringEncodingDetection)

#pragma mark *** Encoding detection ***

/* This API is used to detect the string encoding of a given raw data. It can also do lossy string conversion. It converts the data to a string in the detected string encoding. The data object contains the raw bytes, and the option dictionary contains the hints and parameters for the analysis. The opts dictionary can be nil. If the string parameter is not NULL, the string created by the detected string encoding is returned. The lossy substitution string is emitted in the output string for characters that could not be converted when lossy conversion is enabled. The usedLossyConversion indicates if there is any lossy conversion in the resulted string. If no encoding can be detected, 0 is returned.
 
The possible items for the dictionary are:
 1) an array of suggested string encodings (without specifying the 3rd option in this list, all string encodings are considered but the ones in the array will have a higher preference; moreover, the order of the encodings in the array is important: the first encoding has a higher preference than the second one in the array)
 2) an array of string encodings not to use (the string encodings in this list will not be considered at all)
 3) a boolean option indicating whether only the suggested string encodings are considered
 4) a boolean option indicating whether lossy is allowed
 5) an option that gives a specific string to substitude for mystery bytes
 6) the current user's language
 7) a boolean option indicating whether the data is generated by Windows
 
If the values in the dictionary have wrong types (for example, the value of NSStringEncodingDetectionSuggestedEncodingsKey is not an array), an exception is thrown.
If the values in the dictionary are unknown (for example, the value in the array of suggested string encodings is not a valid encoding), the values will be ignored.
*/
+ (NSStringEncoding)stringEncodingForData:(NSData *)data
                          encodingOptions:(nullable NSDictionary<NSString *, id> *)opts
                          convertedString:(NSString * __nullable * __nullable)string
                      usedLossyConversion:(nullable BOOL *)usedLossyConversion NS_AVAILABLE(10_10, 8_0);

/* The following keys are for the option dictionary for the string encoding detection API.
*/
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionSuggestedEncodingsKey           NS_AVAILABLE(10_10, 8_0);   // NSArray of NSNumbers which contain NSStringEncoding values; if this key is not present in the dictionary, all encodings are weighted the same
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionDisallowedEncodingsKey          NS_AVAILABLE(10_10, 8_0);   // NSArray of NSNumbers which contain NSStringEncoding values; if this key is not present in the dictionary, all encodings are considered
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionUseOnlySuggestedEncodingsKey    NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is NO
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionAllowLossyKey                   NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is YES
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionFromWindowsKey                  NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is NO
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionLossySubstitutionKey            NS_AVAILABLE(10_10, 8_0);   // NSString value; if this key is not present in the dictionary, the default value is U+FFFD
FOUNDATION_EXPORT NSString * const NSStringEncodingDetectionLikelyLanguageKey               NS_AVAILABLE(10_10, 8_0);   // NSString value; ISO language code; if this key is not present in the dictionary, no such information is considered

@end



@interface NSMutableString : NSString

#pragma mark *** Mutable string ***

/* NSMutableString primitive (funnel) method. See below for the other mutation methods.
*/
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end

@interface NSMutableString (NSMutableStringExtensionMethods)

/* Additional mutation methods.  For subclassers these are all available implemented in terms of the primitive replaceCharactersInRange:range: method.
*/
- (void)insertString:(NSString *)aString atIndex:(NSUInteger)loc;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)appendString:(NSString *)aString;
- (void)appendFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (void)setString:(NSString *)aString;

/* This method replaces all occurrences of the target string with the replacement string, in the specified range of the receiver string, and returns the number of replacements. NSBackwardsSearch means the search is done from the end of the range (the results could be different); NSAnchoredSearch means only anchored (but potentially multiple) instances will be replaced. NSLiteralSearch and NSCaseInsensitiveSearch also apply. NSNumericSearch is ignored. Use NSMakeRange(0, [receiver length]) to process whole string. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/
- (NSUInteger)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange;

/* Perform string transliteration.  The transformation represented by transform is applied to the given range of string in place. Only the specified range will be modified, but the transform may look at portions of the string outside that range for context. If supplied, resultingRange is modified to reflect the new range corresponding to the original range. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return NO; otherwise YES is returned, even if no characters are actually transformed. You can pass one of the predefined transforms listed above (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
*/
- (BOOL)applyTransform:(NSString *)transform reverse:(BOOL)reverse range:(NSRange)range updatedRange:(nullable NSRangePointer)resultingRange NS_AVAILABLE(10_11, 9_0);

/* In addition to these two, NSMutableString responds properly to all NSString creation methods.
 */
- (NSMutableString *)initWithCapacity:(NSUInteger)capacity;
+ (NSMutableString *)stringWithCapacity:(NSUInteger)capacity;

@end



FOUNDATION_EXPORT NSString * const NSCharacterConversionException;
FOUNDATION_EXPORT NSString * const NSParseErrorException; // raised by -propertyList
#define NSMaximumStringLength	(INT_MAX-1)

#pragma mark *** Deprecated/discouraged APIs ***

@interface NSString (NSExtendedStringPropertyListParsing)

/* These methods are no longer recommended since they do not work with property lists and strings files in binary plist format. Please use the APIs in NSPropertyList.h instead.
 */
- (id)propertyList;
- (nullable NSDictionary *)propertyListFromStringsFileFormat;

@end

@interface NSString (NSStringDeprecated)

/* The following methods are deprecated and will be removed from this header file in the near future. These methods use [NSString defaultCStringEncoding] as the encoding to convert to, which means the results depend on the user's language and potentially other settings. This might be appropriate in some cases, but often these methods are misused, resulting in issues when running in languages other then English. UTF8String in general is a much better choice when converting arbitrary NSStrings into 8-bit representations. Additional potential replacement methods are being introduced in NSString as appropriate.
*/
- (nullable const char *)cString NS_RETURNS_INNER_POINTER NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable const char *)lossyCString NS_RETURNS_INNER_POINTER NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (NSUInteger)cStringLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength range:(NSRange)aRange remainingRange:(nullable NSRangePointer)leftoverRange NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable id)initWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getCharacters:range: instead.
*/
- (void)getCharacters:(unichar *)buffer;

@end

NS_ENUM(NSStringEncoding) {
    NSProprietaryStringEncoding = 65536    /* Installation-specific encoding */
};

/* The rest of this file is bookkeeping stuff that has to be here. Don't use this stuff, don't refer to it.
*/
#if !defined(_OBJC_UNICHAR_H_)
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0

@interface NSSimpleCString : NSString {
@package
    char *bytes;
    int numBytes;
#if __LP64__
    int _unused;
#endif
}
@end

@interface NSConstantString : NSSimpleCString
@end

#if __LP64__
#else
extern void *_NSConstantStringClassReference;
#endif


NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSDecimal.h
/*	NSDecimal.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#include <limits.h>
#import <Foundation/NSObjCRuntime.h>

@class NSDictionary;

NS_ASSUME_NONNULL_BEGIN

/***************	Type definitions		***********/

// Rounding policies :
// Original
//    value 1.2  1.21  1.25  1.35  1.27
// Plain    1.2  1.2   1.3   1.4   1.3
// Down     1.2  1.2   1.2   1.3   1.2
// Up       1.2  1.3   1.3   1.4   1.3
// Bankers  1.2  1.2   1.2   1.4   1.3

typedef NS_ENUM(NSUInteger, NSRoundingMode) {
    NSRoundPlain,   // Round up on a tie
    NSRoundDown,    // Always down == truncate
    NSRoundUp,      // Always up
    NSRoundBankers  // on a tie round so last digit is even
};

typedef NS_ENUM(NSUInteger, NSCalculationError) {
    NSCalculationNoError = 0,
    NSCalculationLossOfPrecision, // Result lost precision
    NSCalculationUnderflow,       // Result became 0
    NSCalculationOverflow,        // Result exceeds possible representation
    NSCalculationDivideByZero
};

#define NSDecimalMaxSize (8)
    // Give a precision of at least 38 decimal digits, 128 binary positions.

#define NSDecimalNoScale SHRT_MAX

typedef struct {
    signed   int _exponent:8;
    unsigned int _length:4;     // length == 0 && isNegative -> NaN
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:18;
    unsigned short _mantissa[NSDecimalMaxSize];
} NSDecimal;

NS_INLINE BOOL NSDecimalIsNotANumber(const NSDecimal *dcm)
  { return ((dcm->_length == 0) && dcm->_isNegative); }

/***************	Operations		***********/

FOUNDATION_EXPORT void NSDecimalCopy(NSDecimal *destination, const NSDecimal *source);

FOUNDATION_EXPORT void NSDecimalCompact(NSDecimal *number);

FOUNDATION_EXPORT NSComparisonResult NSDecimalCompare(const NSDecimal *leftOperand, const NSDecimal *rightOperand);
    // NSDecimalCompare:Compares leftOperand and rightOperand.

FOUNDATION_EXPORT void NSDecimalRound(NSDecimal *result, const NSDecimal *number, NSInteger scale, NSRoundingMode roundingMode);
    // Rounds num to the given scale using the given mode.
    // result may be a pointer to same space as num.
    // scale indicates number of significant digits after the decimal point

FOUNDATION_EXPORT NSCalculationError NSDecimalNormalize(NSDecimal *number1, NSDecimal *number2, NSRoundingMode roundingMode);

FOUNDATION_EXPORT NSCalculationError NSDecimalAdd(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

FOUNDATION_EXPORT NSCalculationError NSDecimalSubtract(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

FOUNDATION_EXPORT NSCalculationError NSDecimalMultiply(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

FOUNDATION_EXPORT NSCalculationError NSDecimalDivide(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Division could be silently inexact;
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand
    
FOUNDATION_EXPORT NSCalculationError NSDecimalPower(NSDecimal *result, const NSDecimal *number, NSUInteger power, NSRoundingMode roundingMode);

FOUNDATION_EXPORT NSCalculationError NSDecimalMultiplyByPowerOf10(NSDecimal *result, const NSDecimal *number, short power, NSRoundingMode roundingMode);

FOUNDATION_EXPORT NSString *NSDecimalString(const NSDecimal *dcm, id __nullable locale);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/FoundationErrors.h
/*	FoundationErrors.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

/* NSError codes in NSCocoaErrorDomain. Note that other frameworks (such as AppKit and CoreData) also provide additional NSCocoaErrorDomain error codes.
*/
NS_ENUM(NSInteger) {
    // File system and file I/O related errors, with NSFilePathErrorKey or NSURLErrorKey containing path or URL
    NSFileNoSuchFileError = 4,                                              // Attempt to do a file system operation on a non-existent file
    NSFileLockingError = 255,                                               // Couldn't get a lock on file
    NSFileReadUnknownError = 256,                                           // Read error (reason unknown)
    NSFileReadNoPermissionError = 257,                                      // Read error (permission problem)
    NSFileReadInvalidFileNameError = 258,                                   // Read error (invalid file name)
    NSFileReadCorruptFileError = 259,                                       // Read error (file corrupt, bad format, etc)
    NSFileReadNoSuchFileError = 260,                                        // Read error (no such file)
    NSFileReadInapplicableStringEncodingError = 261,                        // Read error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileReadUnsupportedSchemeError = 262,                                 // Read error (unsupported URL scheme)
    NSFileReadTooLargeError NS_ENUM_AVAILABLE(10_5, 2_0) = 263,             // Read error (file too large)
    NSFileReadUnknownStringEncodingError NS_ENUM_AVAILABLE(10_5, 2_0) = 264, // Read error (string encoding of file contents could not be determined)
    NSFileWriteUnknownError = 512,                                          // Write error (reason unknown)
    NSFileWriteNoPermissionError = 513,                                     // Write error (permission problem)
    NSFileWriteInvalidFileNameError = 514,                                  // Write error (invalid file name)
    NSFileWriteFileExistsError NS_ENUM_AVAILABLE(10_7, 5_0) = 516,          // Write error (file exists)
    NSFileWriteInapplicableStringEncodingError = 517,                       // Write error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileWriteUnsupportedSchemeError = 518,                                // Write error (unsupported URL scheme)
    NSFileWriteOutOfSpaceError = 640,                                       // Write error (out of disk space)
    NSFileWriteVolumeReadOnlyError NS_ENUM_AVAILABLE(10_6, 4_0) = 642,      // Write error (readonly volume)

    // NSFileManager unmount errors
    NSFileManagerUnmountUnknownError NS_ENUM_AVAILABLE(10_11, NA) = 768,    // The volume could not be unmounted (reason unknown)
    NSFileManagerUnmountBusyError NS_ENUM_AVAILABLE(10_11, NA) = 769,       // The volume could not be unmounted because it is in use

    // Other errors
    NSKeyValueValidationError = 1024,                                       // KVC validation error
    NSFormattingError = 2048,                                               // Formatting error
    NSUserCancelledError = 3072,                                            // User cancelled operation (this one often doesn't deserve a panel and might be a good one to special case)
    NSFeatureUnsupportedError NS_ENUM_AVAILABLE(10_8, 6_0) = 3328,          // Feature unsupported error
    
    // Executable loading errors
    NSExecutableNotLoadableError NS_ENUM_AVAILABLE(10_5, 2_0) = 3584,           // Executable is of a type that is not loadable in the current process
    NSExecutableArchitectureMismatchError NS_ENUM_AVAILABLE(10_5, 2_0) = 3585,  // Executable does not provide an architecture compatible with the current process
    NSExecutableRuntimeMismatchError NS_ENUM_AVAILABLE(10_5, 2_0) = 3586,       // Executable has Objective C runtime information incompatible with the current process
    NSExecutableLoadError NS_ENUM_AVAILABLE(10_5, 2_0) = 3587,                  // Executable cannot be loaded for some other reason, such as a problem with a library it depends on
    NSExecutableLinkError NS_ENUM_AVAILABLE(10_5, 2_0) = 3588,                  // Executable fails due to linking issues
    
    // Inclusive error range definitions, for checking future error codes
    NSFileErrorMinimum = 0,
    NSFileErrorMaximum = 1023,
    
    NSValidationErrorMinimum = 1024,
    NSValidationErrorMaximum = 2047,

    NSExecutableErrorMinimum NS_ENUM_AVAILABLE(10_5, 2_0) = 3584,
    NSExecutableErrorMaximum NS_ENUM_AVAILABLE(10_5, 2_0) = 3839,

    NSFormattingErrorMinimum = 2048,
    NSFormattingErrorMaximum = 2559,
    
    NSPropertyListReadCorruptError NS_ENUM_AVAILABLE(10_6, 4_0) = 3840,         // Error parsing a property list
    NSPropertyListReadUnknownVersionError NS_ENUM_AVAILABLE(10_6, 4_0) = 3841,  // The version number in the property list is unknown
    NSPropertyListReadStreamError NS_ENUM_AVAILABLE(10_6, 4_0) = 3842,          // Stream error reading a property list
    NSPropertyListWriteStreamError NS_ENUM_AVAILABLE(10_6, 4_0) = 3851,         // Stream error writing a property list
    NSPropertyListWriteInvalidError NS_ENUM_AVAILABLE(10_10, 8_0) = 3852,       // Invalid property list object or invalid property list type specified when writing

    NSPropertyListErrorMinimum NS_ENUM_AVAILABLE(10_6, 4_0) = 3840,
    NSPropertyListErrorMaximum NS_ENUM_AVAILABLE(10_6, 4_0) = 4095,

    NSXPCConnectionInterrupted NS_ENUM_AVAILABLE(10_8, 6_0) = 4097,
    NSXPCConnectionInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4099,
    NSXPCConnectionReplyInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4101,
    
    NSXPCConnectionErrorMinimum NS_ENUM_AVAILABLE(10_8, 6_0) = 4096,
    NSXPCConnectionErrorMaximum NS_ENUM_AVAILABLE(10_8, 6_0) = 4224,

    NSUbiquitousFileUnavailableError NS_ENUM_AVAILABLE(10_9, 7_0) = 4353, // NSURLUbiquitousItemDownloadingErrorKey contains an error with this code when the item has not been uploaded to iCloud by the other devices yet
    NSUbiquitousFileNotUploadedDueToQuotaError NS_ENUM_AVAILABLE(10_9, 7_0) = 4354, // NSURLUbiquitousItemUploadingErrorKey contains an error with this code when the item has not been uploaded to iCloud because it would make the account go over-quota
    NSUbiquitousFileUbiquityServerNotAvailable NS_ENUM_AVAILABLE(10_9, 7_0) = 4355, // NSURLUbiquitousItemDownloadingErrorKey and NSURLUbiquitousItemUploadingErrorKey contain an error with this code when connecting to the iCloud servers failed

    NSUbiquitousFileErrorMinimum NS_ENUM_AVAILABLE(10_9, 7_0) = 4352,
    NSUbiquitousFileErrorMaximum NS_ENUM_AVAILABLE(10_9, 7_0) = 4607,

    NSUserActivityHandoffFailedError NS_ENUM_AVAILABLE(10_10, 8_0) = 4608,	// The data for the user activity was not available (e.g. if the remote device became unavailable.)
    NSUserActivityConnectionUnavailableError NS_ENUM_AVAILABLE(10_10, 8_0) = 4609,  // The user activity could not be continued because a required connection was not available
    NSUserActivityRemoteApplicationTimedOutError NS_ENUM_AVAILABLE(10_10, 8_0) = 4610, // The remote application failed to send data in time
    NSUserActivityHandoffUserInfoTooLargeError NS_ENUM_AVAILABLE(10_10, 8_0) = 4611, // The NSUserActivity userInfo dictionary was too large to receive

    NSUserActivityErrorMinimum NS_ENUM_AVAILABLE(10_10, 8_0) = 4608,
    NSUserActivityErrorMaximum NS_ENUM_AVAILABLE(10_10, 8_0) = 4863,
    
    NSCoderReadCorruptError NS_ENUM_AVAILABLE(10_11, 9_0) = 4864, // Error parsing data during decode
    NSCoderValueNotFoundError NS_ENUM_AVAILABLE(10_11, 9_0) = 4865, // Data requested was not found
    NSCoderErrorMinimum NS_ENUM_AVAILABLE(10_11, 9_0) = 4864,
    NSCoderErrorMaximum NS_ENUM_AVAILABLE(10_11, 9_0) = 4991,
    
    NSBundleErrorMinimum NS_ENUM_AVAILABLE(10_11, 9_0) = 4992,
    NSBundleErrorMaximum NS_ENUM_AVAILABLE(10_11, 9_0) = 5119,
    
    NSBundleOnDemandResourceOutOfSpaceError NS_ENUM_AVAILABLE(NA, 9_0) = 4992, // There was not enough space available to download the requested On Demand Resources.
    NSBundleOnDemandResourceExceededMaximumSizeError NS_ENUM_AVAILABLE(NA, 9_0) = 4993, // The application exceeded the amount of On Demand Resources content in use at one time
    NSBundleOnDemandResourceInvalidTagError NS_ENUM_AVAILABLE(NA, 9_0) = 4994, // The application specified a tag which the system could not find in the application tag manifest
};

// ==========  Foundation.framework/Headers/NSFileHandle.h
/*	NSFileHandle.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>

@class NSString, NSData, NSError;

NS_ASSUME_NONNULL_BEGIN

@interface NSFileHandle : NSObject <NSSecureCoding>

@property (readonly, copy) NSData *availableData;

- (NSData *)readDataToEndOfFile;
- (NSData *)readDataOfLength:(NSUInteger)length;

- (void)writeData:(NSData *)data;

@property (readonly) unsigned long long offsetInFile;
- (unsigned long long)seekToEndOfFile;
- (void)seekToFileOffset:(unsigned long long)offset;

- (void)truncateFileAtOffset:(unsigned long long)offset;
- (void)synchronizeFile;
- (void)closeFile;

- (instancetype)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSFileHandle (NSFileHandleCreation)

+ (NSFileHandle *)fileHandleWithStandardInput;
+ (NSFileHandle *)fileHandleWithStandardOutput;
+ (NSFileHandle *)fileHandleWithStandardError;
+ (NSFileHandle *)fileHandleWithNullDevice;

+ (nullable instancetype)fileHandleForReadingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForWritingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForUpdatingAtPath:(NSString *)path;

+ (nullable instancetype)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
+ (nullable instancetype)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
+ (nullable instancetype)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

@end

FOUNDATION_EXPORT NSString * const NSFileHandleOperationException;

FOUNDATION_EXPORT NSString * const NSFileHandleReadCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleReadToEndOfFileCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleConnectionAcceptedNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleDataAvailableNotification;

FOUNDATION_EXPORT NSString * const NSFileHandleNotificationDataItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationFileHandleItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationMonitorModes NS_DEPRECATED(10_0, 10_7, 2_0, 5_0);

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

- (void)readInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)readInBackgroundAndNotify;

- (void)readToEndOfFileInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;

- (void)acceptConnectionInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)acceptConnectionInBackgroundAndNotify;

- (void)waitForDataInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)waitForDataInBackgroundAndNotify;

#ifdef __BLOCKS__
@property (nullable, copy) void (^readabilityHandler)(NSFileHandle *)  NS_AVAILABLE(10_7, 5_0);
@property (nullable, copy) void (^writeabilityHandler)(NSFileHandle *) NS_AVAILABLE(10_7, 5_0);
#endif

@end

@interface NSFileHandle (NSFileHandlePlatformSpecific)

- (instancetype)initWithFileDescriptor:(int)fd;

@property (readonly) int fileDescriptor;

@end

@interface NSPipe : NSObject

@property (readonly, retain) NSFileHandle *fileHandleForReading;
@property (readonly, retain) NSFileHandle *fileHandleForWriting;

+ (NSPipe *)pipe;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSSortDescriptor.h
/*
	NSSortDescriptor.h
	Foundation
	Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSOrderedSet.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSSortDescriptor : NSObject <NSSecureCoding, NSCopying> {
@private
    NSUInteger _sortDescriptorFlags;
    NSString *_key;
    SEL _selector;
    id _selectorOrBlock;
}

+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending NS_AVAILABLE(10_6, 4_0);
+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector NS_AVAILABLE(10_6, 4_0);

// keys may be key paths
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending;
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector;
- (nullable instancetype)initWithCoder:(NSCoder *)coder;

@property (nullable, readonly, copy) NSString *key;
@property (readonly) BOOL ascending;
@property (nullable, readonly) SEL selector;

- (void)allowEvaluation NS_AVAILABLE(10_9, 7_0); // Force a sort descriptor which was securely decoded to allow evaluation

+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

@property (readonly) NSComparator comparator NS_AVAILABLE(10_6, 4_0);

- (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;    // primitive - override this method if you want to perform comparisons differently (not key based for example)
@property (readonly, retain) id reversedSortDescriptor;    // primitive - override this method to return a sort descriptor instance with reversed sort order

@end

@interface NSSet<ObjectType> (NSSortDescriptorSorting)

- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_6, 4_0);    // returns a new array by sorting the objects of the receiver

@end

@interface NSArray<ObjectType> (NSSortDescriptorSorting)

- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;    // returns a new array by sorting the objects of the receiver

@end

@interface NSMutableArray<ObjectType> (NSSortDescriptorSorting)

- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;    // sorts the array itself

@end

@interface NSOrderedSet<ObjectType> (NSKeyValueSorting)

// returns a new array by sorting the objects of the receiver
- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_7, 5_0);

@end

@interface NSMutableOrderedSet<ObjectType> (NSKeyValueSorting)

// sorts the ordered set itself
- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_7, 5_0);

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSRange.h
/*	NSRange.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>
#import <Foundation/NSObjCRuntime.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

typedef struct _NSRange {
    NSUInteger location;
    NSUInteger length;
} NSRange;

typedef NSRange *NSRangePointer;

NS_INLINE NSRange NSMakeRange(NSUInteger loc, NSUInteger len) {
    NSRange r;
    r.location = loc;
    r.length = len;
    return r;
}

NS_INLINE NSUInteger NSMaxRange(NSRange range) {
    return (range.location + range.length);
}

NS_INLINE BOOL NSLocationInRange(NSUInteger loc, NSRange range) {
    return (!(loc < range.location) && (loc - range.location) < range.length) ? YES : NO;
}

NS_INLINE BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location && range1.length == range2.length);
}

FOUNDATION_EXPORT NSRange NSUnionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSRange NSIntersectionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSString *NSStringFromRange(NSRange range);
FOUNDATION_EXPORT NSRange NSRangeFromString(NSString *aString);

@interface NSValue (NSValueRangeExtensions)

+ (NSValue *)valueWithRange:(NSRange)range;
@property (readonly) NSRange rangeValue;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSMetadata.h
/*	NSMetadata.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSMetadataAttributes.h>

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSURL, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSPredicate, NSOperationQueue, NSSortDescriptor;
@class NSMetadataItem, NSMetadataQueryAttributeValueTuple, NSMetadataQueryResultGroup;
@protocol NSMetadataQueryDelegate;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQuery : NSObject {
@private
    NSUInteger _flags;
    NSTimeInterval _interval;
    id _private[11];
    __strong void *_reserved;
}

@property (nullable, assign) id<NSMetadataQueryDelegate> delegate;
@property (nullable, copy) NSPredicate *predicate;
@property (copy) NSArray<NSSortDescriptor *> *sortDescriptors;
@property (copy) NSArray<NSString *> *valueListAttributes;
@property (nullable, copy) NSArray<NSString *> *groupingAttributes;
@property NSTimeInterval notificationBatchingInterval;

@property (copy) NSArray *searchScopes;
// scopes is an NSArray of NSURL objects (file URLs only) and/or string
// paths and/or the special string constants below, which specifies the
// locations to which the search is limited; an empty array means no
// limits, which is the default state.

@property (nullable, copy) NSArray *searchItems NS_AVAILABLE(10_9, 7_0);
// items can be a mixture of NSMetadataItem, NSURL objects (file URLs only)
// and/or string paths; the getter returns the same mixture as was set

@property (nullable, retain) NSOperationQueue *operationQueue NS_AVAILABLE(10_9, 7_0);
// optional operation queue for notifications and delegate method calls

- (BOOL)startQuery;
- (void)stopQuery;

@property (readonly, getter=isStarted) BOOL started;
@property (readonly, getter=isGathering) BOOL gathering;
@property (readonly, getter=isStopped) BOOL stopped;

- (void)disableUpdates; // these nest
- (void)enableUpdates;


// Results are NSMetadataItems, or whatever the delegate replaces that with
@property (readonly) NSUInteger resultCount;
- (id)resultAtIndex:(NSUInteger)idx;

- (void)enumerateResultsUsingBlock:(void (^)(id result, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);
- (void)enumerateResultsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id result, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);

@property (readonly, copy) NSArray *results;   // this is for K-V Bindings, and causes side-effects on the query

- (NSUInteger)indexOfResult:(id)result;

@property (readonly, copy) NSDictionary<NSString *, NSArray<NSMetadataQueryAttributeValueTuple *> *> *valueLists; // values are arrays of NSMetadataQueryAttributeValueTuple

@property (readonly, copy) NSArray<NSMetadataQueryResultGroup *> *groupedResults; // array of NSMetadataQueryResultGroups, for first grouping attribute

- (nullable id)valueOfAttribute:(NSString *)attrName forResultAtIndex:(NSUInteger)idx;

@end

@protocol NSMetadataQueryDelegate <NSObject>
@optional

- (id)metadataQuery:(NSMetadataQuery *)query replacementObjectForResultObject:(NSMetadataItem *)result;
- (id)metadataQuery:(NSMetadataQuery *)query replacementValueForAttribute:(NSString *)attrName value:(id)attrValue;

@end

// notifications
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidStartGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryGatheringProgressNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidFinishGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidUpdateNotification NS_AVAILABLE(10_4, 5_0);

// keys for use with notification info dictionary
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateAddedItemsKey NS_AVAILABLE(10_9, 8_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateChangedItemsKey NS_AVAILABLE(10_9, 8_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateRemovedItemsKey NS_AVAILABLE(10_9, 8_0);

FOUNDATION_EXPORT NSString * const NSMetadataQueryResultContentRelevanceAttribute NS_AVAILABLE(10_4, 5_0);

// Scope constants for defined search locations
FOUNDATION_EXPORT NSString * const NSMetadataQueryUserHomeScope NS_AVAILABLE_MAC(10_4); // user home directory
FOUNDATION_EXPORT NSString * const NSMetadataQueryLocalComputerScope NS_AVAILABLE_MAC(10_4); // all local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryNetworkScope NS_AVAILABLE_MAC(10_4); // all user-mounted remote volumes

FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedLocalComputerScope NS_AVAILABLE_MAC(10_9); // all indexed local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedNetworkScope NS_AVAILABLE_MAC(10_9); // all indexed user-mounted remote volumes

// -setSearchScopes: will throw an exception if the given array contains a mix of the scope constants below with constants above.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDocumentsScope NS_AVAILABLE(10_7, 5_0); // "Documents" subdirectory in the application's Ubiquity container
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDataScope NS_AVAILABLE(10_7, 5_0); // application's Ubiquity container, excluding the "Documents" subdirectory
FOUNDATION_EXPORT NSString * const NSMetadataQueryAccessibleUbiquitousExternalDocumentsScope NS_AVAILABLE(10_10, 8_0); // documents from outside the application's container that are accessible without user interaction. NSMetadataItemURLKey attributes of results are security-scoped NSURLs.


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataItem : NSObject {
@private
    id _item;
    __strong void *_reserved;
}

- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_AVAILABLE_MAC(10_9);

- (nullable id)valueForAttribute:(NSString *)key;
- (nullable NSDictionary<NSString *, id> *)valuesForAttributes:(NSArray<NSString *> *)keys;

@property (readonly, copy) NSArray<NSString *> *attributes;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryAttributeValueTuple : NSObject {
@private
    id _attr;
    id _value;
    NSUInteger _count;
    void *_reserved;
}

@property (readonly, copy) NSString *attribute;
@property (nullable, readonly, retain) id value;
@property (readonly) NSUInteger count;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryResultGroup : NSObject {
@private
    id _private[9];
    NSUInteger _private2[1];
    void *_reserved;
}

@property (readonly, copy) NSString *attribute;
@property (readonly, retain) id value;

@property (nullable, readonly, copy) NSArray<NSMetadataQueryResultGroup *> *subgroups; // nil if this is a leaf

@property (readonly) NSUInteger resultCount;
- (id)resultAtIndex:(NSUInteger)idx; // uncertain whether this will do anything useful for non-leaf groups

@property (readonly, copy) NSArray *results;   // this is for K-V Bindings, and causes side-effects on the query

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLAuthenticationChallenge.h
/*	
    NSURLAuthenticationChallenge.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSURLAuthenticationChallenge;
@class NSURLCredential;
@class NSURLProtectionSpace;
@class NSURLResponse;
@class NSError;

NS_ASSUME_NONNULL_BEGIN

/*!  
    @protocol NSURLAuthenticationChallengeSender 
    @discussion This protocol represents the sender of an
    authentication challenge. It has methods to provide a credential,
    to continue without any credential, getting whatever failure
    result would happen in that case, cancel a challenge, perform the default
    action as defined by the system, or reject the currently supplied protection-space
    in the challenge.
*/

@protocol NSURLAuthenticationChallengeSender <NSObject>

/*!
    @method useCredential:forAuthenticationChallenge:
*/
- (void)useCredential:(NSURLCredential *)credential forAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method continueWithoutCredentialForAuthenticationChallenge:
*/
- (void)continueWithoutCredentialForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method cancelAuthenticationChallenge:
*/
- (void)cancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@optional
/*!
 @method performDefaultHandlingForAuthenticationChallenge:
 */
- (void)performDefaultHandlingForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
 @method rejectProtectionSpaceAndContinueWithChallenge:
 */
- (void)rejectProtectionSpaceAndContinueWithChallenge:(NSURLAuthenticationChallenge *)challenge;

@end

@class NSURLAuthenticationChallengeInternal;

/*!
    @class NSURLAuthenticationChallenge
    @discussion This class represents an authentication challenge. It
    provides all the information about the challenge, and has a method
    to indicate when it's done.
*/

@interface NSURLAuthenticationChallenge : NSObject <NSSecureCoding>
{
@private
    NSURLAuthenticationChallengeInternal *_internal;
}

/*!
    @method initWithProtectionSpace:proposedCredential:previousFailureCount:failureResponse:error:
    @abstract Initialize an authentication challenge 
    @param space The NSURLProtectionSpace to use
    @param credential The proposed NSURLCredential for this challenge, or nil
    @param previousFailureCount A count of previous failures attempting access.
    @param response The NSURLResponse for the authentication failure, if applicable, else nil
    @param error The NSError for the authentication failure, if applicable, else nil
    @result An authentication challenge initialized with the specified parameters
*/
- (instancetype)initWithProtectionSpace:(NSURLProtectionSpace *)space proposedCredential:(nullable NSURLCredential *)credential previousFailureCount:(NSInteger)previousFailureCount failureResponse:(nullable NSURLResponse *)response error:(nullable NSError *)error sender:(id<NSURLAuthenticationChallengeSender>)sender;

/*!
    @method initWithAuthenticationChallenge:
    @abstract Initialize an authentication challenge copying all parameters from another one.
    @param challenge
    @result A new challenge initialized with the parameters from the passed in challenge
    @discussion This initializer may be useful to subclassers that want to proxy
    one type of authentication challenge to look like another type.
*/
- (instancetype)initWithAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge sender:(id<NSURLAuthenticationChallengeSender>)sender;

/*!
    @method protectionSpace
    @abstract Get a description of the protection space that requires authentication
    @result The protection space that needs authentication
*/
@property (readonly, copy) NSURLProtectionSpace *protectionSpace;

/*!
    @method proposedCredential
    @abstract Get the proposed credential for this challenge
    @result The proposed credential
    @discussion proposedCredential may be nil, if there is no default
    credential to use for this challenge (either stored or in the
    URL). If the credential is not nil and returns YES for
    hasPassword, this means the NSURLConnection thinks the credential
    is ready to use as-is. If it returns NO for hasPassword, then the
    credential is not ready to use as-is, but provides a default
    username the client could use when prompting.
*/
@property (nullable, readonly, copy) NSURLCredential *proposedCredential;

/*!
    @method previousFailureCount
    @abstract Get count of previous failed authentication attempts
    @result The count of previous failures
*/
@property (readonly) NSInteger previousFailureCount;

/*!
    @method failureResponse
    @abstract Get the response representing authentication failure.
    @result The failure response or nil
    @discussion If there was a previous authentication failure, and
    this protocol uses responses to indicate authentication failure,
    then this method will return the response. Otherwise it will
    return nil.
*/
@property (nullable, readonly, copy) NSURLResponse *failureResponse;

/*!
    @method error
    @abstract Get the error representing authentication failure.
    @discussion If there was a previous authentication failure, and
    this protocol uses errors to indicate authentication failure,
    then this method will return the error. Otherwise it will
    return nil.
*/
@property (nullable, readonly, copy) NSError *error;

/*!
    @method sender
    @abstract Get the sender of this challenge
    @result The sender of the challenge
    @discussion The sender is the object you should reply to when done processing the challenge.
*/
@property (nullable, readonly, retain) id<NSURLAuthenticationChallengeSender> sender;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSUndoManager.h
/*	NSUndoManager.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/


//
// NSUndoManager is a general-purpose undo stack where clients can register
// callbacks to be invoked should an undo be requested.
//

#import <Foundation/NSObject.h>
#include <stdint.h>

@class NSArray<ObjectType>;
@class NSString;

NS_ASSUME_NONNULL_BEGIN

// used with NSRunLoop's performSelector:target:argument:order:modes:
static const NSUInteger NSUndoCloseGroupingRunLoopOrdering = 350000;

NS_CLASS_AVAILABLE(10_0, 3_0)
@interface NSUndoManager : NSObject {
    @private
    id 			_undoStack;
    id 			_redoStack;
    NSArray 		*_runLoopModes;
    uint64_t		_NSUndoManagerPrivate1;
    id 			_target;
    id			_proxy;
    void		*_NSUndoManagerPrivate2;
    void		*_NSUndoManagerPrivate3;
}

        /* Begin/End Grouping */

- (void)beginUndoGrouping;
- (void)endUndoGrouping;
    // These nest.

@property (readonly) NSInteger groupingLevel;
    // Zero means no open group.

        /* Enable/Disable registration */

- (void)disableUndoRegistration;
- (void)enableUndoRegistration;
@property (readonly, getter=isUndoRegistrationEnabled) BOOL undoRegistrationEnabled;

        /* Groups By Event */

@property BOOL groupsByEvent;
    // If groupsByEvent is enabled, the undoManager automatically groups
    // all undos registered during a single NSRunLoop event together in
    // a single top-level group. This featured is enabled by default.

        /* Undo levels */

@property NSUInteger levelsOfUndo;
    // Sets the number of complete groups (not operations) that should
    // be kept my the manager.  When limit is reached, oldest undos are
    // thrown away.  0 means no limit !

        /* Run Loop Modes */

@property (copy) NSArray<NSString *> *runLoopModes;

        /* Undo/Redo */

- (void)undo;
    // Undo until a matching begin. It terminates a top level undo if
    // necesary. Useful for undoing when groupByEvents is on (default is
    // on)
- (void)redo;
    // Will redo last top-level undo.

- (void)undoNestedGroup;
    // Undoes a nested grouping without first trying to close a top level
    // undo group.

@property (readonly) BOOL canUndo;
@property (readonly) BOOL canRedo;
    // returns whether or not the UndoManager has anything to undo or redo

@property (readonly, getter=isUndoing) BOOL undoing;
@property (readonly, getter=isRedoing) BOOL redoing;
    // returns whether or not the undo manager is currently in the process
    // of invoking undo or redo operations.

        /* remove */

- (void)removeAllActions;

- (void)removeAllActionsWithTarget:(id)target;

        /* Object based Undo */

- (void)registerUndoWithTarget:(id)target selector:(SEL)selector object:(nullable id)anObject;

        /* Invocation based undo */

- (id)prepareWithInvocationTarget:(id)target;
   // called as:
   // [[undoManager prepareWithInvocationTarget:self] setFont:oldFont color:oldColor]
   // When undo is called, the specified target will be called with
   // [target setFont:oldFont color:oldColor]

/*! @abstract records single undo operation for the specified target
    @param target non-nil target of the undo operation
    @param undoHandler non-nil block to be executed for the undo operation
    @discussion
      As with other undo operations, this does not strongly retain target. Care should be taken to avoid introducing retain cycles by other references captured by the block.
 */
- (void)registerUndoWithTarget:(id)target handler:(void (^)(id target))undoHandler NS_AVAILABLE(10_11, 9_0) NS_REFINED_FOR_SWIFT;

- (void)setActionIsDiscardable:(BOOL)discardable NS_AVAILABLE(10_7, 5_0);
   // Set the latest undo action to discardable if it may be safely discarded when a document can not be saved for any reason. An example might be an undo action that changes the viewable area of a document. To find out if an undo group contains only discardable actions, look for the NSUndoManagerGroupIsDiscardableKey in the userInfo dictionary of the NSUndoManagerDidCloseUndoGroupNotification.

// This key is set on the user info dictionary of the NSUndoManagerDidCloseUndoGroupNotification, with a NSNumber boolean value of YES, if the undo group as a whole is discardable.
FOUNDATION_EXPORT NSString * const NSUndoManagerGroupIsDiscardableKey NS_AVAILABLE(10_7, 5_0);

@property (readonly) BOOL undoActionIsDiscardable NS_AVAILABLE(10_7, 5_0);
@property (readonly) BOOL redoActionIsDiscardable NS_AVAILABLE(10_7, 5_0);
   // Call to see if the next undo or redo action is discardable.

    	/* Undo/Redo action name */

@property (readonly, copy) NSString *undoActionName;
@property (readonly, copy) NSString *redoActionName;
    // Call undoActionName or redoActionName to get the name of the next action to be undone or redone.
    // Returns @"" if there is nothing to undo/redo or no action names were registered.

- (void)setActionName:(NSString *)actionName;
    // Call setActionName: to set the name of an action.
    // The actionName parameter can not be nil

    	/* Undo/Redo menu item title */

@property (readonly, copy) NSString *undoMenuItemTitle;
@property (readonly, copy) NSString *redoMenuItemTitle;
    // Call undoMenuItemTitle or redoMenuItemTitle to get the string for the undo or redo menu item.
    // In English they will return "Undo <action name>"/"Redo <action name>" or "Undo"/"Redo" if there is
    // nothing to undo/redo or no action names were set.

    	/* localization hooks */

- (NSString *)undoMenuTitleForUndoActionName:(NSString *)actionName;
- (NSString *)redoMenuTitleForUndoActionName:(NSString *)actionName;
    // The localization of the pattern is usually done by localizing the string patterns in
    // undo.strings. But undo/redoMenuTitleForUndoActionName can also be overridden if
    // localizing the pattern happens to not be sufficient.

@end

FOUNDATION_EXPORT NSString * const NSUndoManagerCheckpointNotification NS_AVAILABLE(10_0, 3_0);
    // This is called before an undo group is begun or ended so any
    // clients that need to lazily register undos can do so in the
    // correct group.

FOUNDATION_EXPORT NSString * const NSUndoManagerWillUndoChangeNotification NS_AVAILABLE(10_0, 3_0);
FOUNDATION_EXPORT NSString * const NSUndoManagerWillRedoChangeNotification NS_AVAILABLE(10_0, 3_0);

FOUNDATION_EXPORT NSString * const NSUndoManagerDidUndoChangeNotification NS_AVAILABLE(10_0, 3_0);
FOUNDATION_EXPORT NSString * const NSUndoManagerDidRedoChangeNotification NS_AVAILABLE(10_0, 3_0);

FOUNDATION_EXPORT NSString * const NSUndoManagerDidOpenUndoGroupNotification NS_AVAILABLE(10_0, 3_0);
FOUNDATION_EXPORT NSString * const NSUndoManagerWillCloseUndoGroupNotification NS_AVAILABLE(10_0, 3_0);

// This notification is sent after an undo group closes. It should be safe to undo at this time.
FOUNDATION_EXPORT NSString * const NSUndoManagerDidCloseUndoGroupNotification NS_AVAILABLE(10_7, 5_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSProcessInfo.h
/*	NSProcessInfo.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

enum {	/* Constants returned by -operatingSystem */
    NSWindowsNTOperatingSystem = 1,
    NSWindows95OperatingSystem,
    NSSolarisOperatingSystem,
    NSHPUXOperatingSystem,
    NSMACHOperatingSystem,
    NSSunOSOperatingSystem,
    NSOSF1OperatingSystem
} NS_ENUM_DEPRECATED(10_0, 10_10, 2_0, 8_0);

typedef struct {
    NSInteger majorVersion;
    NSInteger minorVersion;
    NSInteger patchVersion;
} NSOperatingSystemVersion;

@class NSArray<ObjectType>, NSString, NSDictionary<KeyType, ObjectType>;

@interface NSProcessInfo : NSObject {
@private
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;
    NSString		*name;
    NSInteger		automaticTerminationOptOutCounter;
}

+ (NSProcessInfo *)processInfo;

@property (readonly, copy) NSDictionary<NSString *, NSString *> *environment;
@property (readonly, copy) NSArray<NSString *> *arguments;
@property (readonly, copy) NSString *hostName;
@property (copy) NSString *processName;
@property (readonly) int processIdentifier;

@property (readonly, copy) NSString *globallyUniqueString;

- (NSUInteger)operatingSystem NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead");
- (NSString *)operatingSystemName NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead");

	/* Human readable, localized; appropriate for displaying to user or using in bug emails and such; NOT appropriate for parsing */
@property (readonly, copy) NSString *operatingSystemVersionString;

@property (readonly) NSOperatingSystemVersion operatingSystemVersion NS_AVAILABLE(10_10, 8_0);

@property (readonly) NSUInteger processorCount NS_AVAILABLE(10_5, 2_0);
@property (readonly) NSUInteger activeProcessorCount NS_AVAILABLE(10_5, 2_0);
@property (readonly) unsigned long long physicalMemory NS_AVAILABLE(10_5, 2_0);

- (BOOL) isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion)version NS_AVAILABLE(10_10, 8_0);
@property (readonly) NSTimeInterval systemUptime NS_AVAILABLE(10_6, 4_0);

/* Disable or reenable the ability to be quickly killed. The default implementations of these methods increment or decrement, respectively, a counter whose value is 1 when the process is first created. When the counter's value is 0 the application is considered to be safely killable and may be killed by the operating system without any notification or event being sent to the process first. If an application's Info.plist has an NSSupportsSuddenTermination entry whose value is true then NSApplication invokes -enableSuddenTermination automatically during application launch, which typically renders the process killable right away. You can also manually invoke -enableSuddenTermination right away in, for example, agents or daemons that don't depend on AppKit. After that, you can invoke these methods whenever the process has work it must do before it terminates. For example:
 - NSUserDefaults uses these to prevent process killing between the time at which a default has been set and the time at which the preferences file including that default has been written to disk.
 - NSDocument uses these to prevent process killing between the time at which the user has made a change to a document and the time at which the user's change has been written to disk.
 - You can use these whenever your application defers work that must be done before the application terminates. If for example your application ever defers writing something to disk, and it has an NSSupportsSuddenTermination entry in its Info.plist so as not to contribute to user-visible delays at logout or shutdown time, it must invoke -disableSuddenTermination when the writing is first deferred and -enableSuddenTermination after the writing is actually done.
 */
- (void)disableSuddenTermination NS_AVAILABLE(10_6, NA);
- (void)enableSuddenTermination NS_AVAILABLE(10_6, NA);

/*
 * Increment or decrement the counter tracking the number of automatic quit opt-out requests. When this counter is greater than zero, the app will be considered 'active' and ineligible for automatic termination.
 * An example of using this would be disabling autoquitting when the user of an instant messaging application signs on, due to it requiring a background connection to be maintained even if the app is otherwise inactive.
 * Each pair of calls should have a matching "reason" argument, which can be used to easily track why an application is or is not automatically terminable.
 * A given reason can be used more than once at the same time (for example: two files are transferring over the network, each one disables automatic termination with the reason @"file transfer in progress")
 */
- (void)disableAutomaticTermination:(NSString *)reason NS_AVAILABLE(10_7, NA);
- (void)enableAutomaticTermination:(NSString *)reason NS_AVAILABLE(10_7, NA);

/*
 * Marks the calling app as supporting automatic termination. Without calling this or setting the equivalent Info.plist key (NSSupportsAutomaticTermination), the above methods (disableAutomaticTermination:/enableAutomaticTermination:) have no effect,
 * although the counter tracking automatic termination opt-outs is still kept up to date to ensure correctness if this is called later. Currently, passing NO has no effect.
 * This should be called during -applicationDidFinishLaunching or earlier.
 */
@property BOOL automaticTerminationSupportEnabled NS_AVAILABLE(10_7, NA);

@end

/*
 The system has heuristics to improve battery life, performance, and responsiveness of applications for the benefit of the user. This API can be used to give hints to the system that your application has special requirements. In response to creating one of these activities, the system will disable some or all of the heuristics so your application can finish quickly while still providing responsive behavior if the user needs it.
 
 These activities can be used when your application is performing a long-running operation. If the activity can take different amounts of time (for example, calculating the next move in a chess game), it should use this API. This will ensure correct behavior when the amount of data or the capabilities of the user's computer varies. You should put your activity into one of two major categories:
 
 User initiated: These are finite length activities that the user has explicitly started. Examples include exporting or downloading a user specified file.
 
 Background: These are finite length activities that are part of the normal operation of your application but are not explicitly started by the user. Examples include autosaving, indexing, and automatic downloading of files.
 
 In addition, if your application requires high priority IO, you can include the 'NSActivityLatencyCritical' flag (using a bitwise or). This should be reserved for activities like audio or video recording.
 
 If your activity takes place synchronously inside an event callback on the main thread, you do not need to use this API.
 
 Be aware that failing to end these activities for an extended period of time can have significant negative impacts to the performance of your user's computer, so be sure to use only the minimum amount of time required. User preferences may override your application’s request.
 
 This API can also be used to control auto termination or sudden termination. 
 
    id activity = [[NSProcessInfo processInfo] beginActivityWithOptions:NSActivityAutomaticTerminationDisabled reason:@"Good Reason"];
    // work
    [[NSProcessInfo processInfo] endActivity:activity];
 
 is equivalent to:
 
    [[NSProcessInfo processInfo] disableAutomaticTermination:@"Good Reason"];
    // work
    [[NSProcessInfo processInfo] enableAutomaticTermination:@"Good Reason"]
 
 Since this API returns an object, it may be easier to pair begins and ends. If the object is deallocated before the -endActivity: call, the activity will be automatically ended.
 
 This API also provides a mechanism to disable system-wide idle sleep and display idle sleep. These can have a large impact on the user experience, so be sure not to forget to end activities that disable sleep (including NSActivityUserInitiated).
 
 */

typedef NS_OPTIONS(uint64_t, NSActivityOptions) {
    // To include one of these individual flags in one of the sets, use bitwise or:
    //   NSActivityUserInitiated | NSActivityIdleDisplaySleepDisabled
    // (this may be used during a presentation, for example)
    
    // To exclude from one of the sets, use bitwise and with not:
    //   NSActivityUserInitiated & ~NSActivitySuddenTerminationDisabled
    // (this may be used during a user intiated action that may be safely terminated with no application interaction in case of logout)
    
    // Used for activities that require the screen to stay powered on.
    NSActivityIdleDisplaySleepDisabled = (1ULL << 40),
    
    // Used for activities that require the computer to not idle sleep. This is included in NSActivityUserInitiated.
    NSActivityIdleSystemSleepDisabled = (1ULL << 20),
    
    // Prevents sudden termination. This is included in NSActivityUserInitiated.
    NSActivitySuddenTerminationDisabled = (1ULL << 14),
    
    // Prevents automatic termination. This is included in NSActivityUserInitiated.
    NSActivityAutomaticTerminationDisabled = (1ULL << 15),
    
    // ----
    // Sets of options.
    
    // App is performing a user-requested action.
    NSActivityUserInitiated = (0x00FFFFFFULL | NSActivityIdleSystemSleepDisabled),
    NSActivityUserInitiatedAllowingIdleSystemSleep = (NSActivityUserInitiated & ~NSActivityIdleSystemSleepDisabled),
    
    // App has initiated some kind of work, but not as the direct result of user request.
    NSActivityBackground = 0x000000FFULL,
    
    // Used for activities that require the highest amount of timer and I/O precision available. Very few applications should need to use this constant.
    NSActivityLatencyCritical = 0xFF00000000ULL,
} NS_ENUM_AVAILABLE(10_9, 7_0);

@interface NSProcessInfo (NSProcessInfoActivity)
/*
 * Pass in an activity to this API, and a non-NULL, non-empty reason string. Indicate completion of the activity by calling the corresponding endActivity: method with the result of the beginActivityWithOptions:reason: method. The reason string is used for debugging.
 */
- (id <NSObject>)beginActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason NS_AVAILABLE(10_9, 7_0);

/*
 * The argument to this method is the result of beginActivityWithOptions:reason:.
 */
- (void)endActivity:(id <NSObject>)activity NS_AVAILABLE(10_9, 7_0);

/*
 * Synchronously perform an activity. The activity will be automatically ended after your block argument returns. The reason string is used for debugging.
 */
- (void)performActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason usingBlock:(void (^)(void))block NS_AVAILABLE(10_9, 7_0);

/* 
 * Perform an expiring background task, which obtains an expiring task assertion on iOS. The block contains any work which needs to be completed as a background-priority task. The block will be scheduled on a system-provided concurrent queue. After a system-specified time, the block will be called with the `expired` parameter set to YES. The `expired` parameter will also be YES if the system decides to prematurely terminate a previous non-expiration invocation of the block.
 */
- (void)performExpiringActivityWithReason:(NSString *)reason usingBlock:(void(^)(BOOL expired))block NS_AVAILABLE_IOS(8_2);

@end

// Describes the current thermal state of the system.
typedef NS_ENUM(NSInteger, NSProcessInfoThermalState) {
    // No corrective action is needed.
    NSProcessInfoThermalStateNominal,

    // The system has reached a state where fans may become audible.
    NSProcessInfoThermalStateFair,

    // Fans are running at maximum speed, system performance maybe impacted. Recommendation: reduce application's usage of CPU, GPU and I/O, if possible. Switch to lower quality visual effects, reduce frame rates.
    NSProcessInfoThermalStateSerious,
    
    // System performance is significantly impacted and the Mac needs to cool down. Recommendation: reduce application's usage of CPU, GPU, and I/O to the minimum level needed to respond to user actions. Consider stopping use of camera and other peripherals if your application is using them.
    NSProcessInfoThermalStateCritical
} NS_ENUM_AVAILABLE(10_10_3, NA);

@interface NSProcessInfo (NSProcessInfoThermalState)

// Retrieve the current thermal state of the system. On systems where thermal state is unknown or unsupported, the value returned from the thermalState property is always NSProcessInfoThermalStateNominal.
@property (readonly) NSProcessInfoThermalState thermalState NS_AVAILABLE(10_10_3, NA);

@end

@interface NSProcessInfo (NSProcessInfoPowerState)

// Retrieve the current setting of the system for the low power mode setting. On systems where the low power mode is unknown or unsupported, the value returned from the lowPowerModeEnabled property is always NO
@property (readonly, getter=isLowPowerModeEnabled) BOOL lowPowerModeEnabled NS_AVAILABLE(NA, 9_0);

@end

/*
 NSProcessInfoThermalStateDidChangeNotification is posted once the thermal state of the system has changed. Once the notification is posted, use the thermalState property to retrieve the current thermal state of the system.
 
 You can use this opportunity to take corrective action in your application to help cool the system down. Work that could be done in the background or at opportunistic times should be using the Quality of Service levels in NSOperation or the NSBackgroundActivityScheduler API.
 
 This notification is posted on the global dispatch queue. Register for it using the default notification center. The object associated with the notification is +[NSProcessInfo processInfo].
*/
FOUNDATION_EXTERN NSString * const NSProcessInfoThermalStateDidChangeNotification NS_AVAILABLE(10_10_3, NA);

/*
 NSProcessInfoPowerStateDidChangeNotification is posted once any power usage mode of the system has changed. Once the notification is posted, use the isLowPowerModeEnabled property to retrieve the current state of the low power mode setting of the system.
 
 When this notification is posted your application should attempt to reduce power usage by reducing potentially costly computation and other power using activities like network activity or keeping the screen on if the low power mode setting is enabled.
 
 This notification is posted on the global dispatch queue. Register for it using the default notification center. The object associated with the notification is +[NSProcessInfo processInfo].
 */
FOUNDATION_EXTERN NSString * const NSProcessInfoPowerStateDidChangeNotification NS_AVAILABLE(NA, 9_0);

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSRegularExpression.h
/*	NSRegularExpression.h
	Copyright (c) 2009-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSTextCheckingResult.h>

@class NSArray<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

/* NSRegularExpression is a class used to represent and apply regular expressions.  An instance of this class is an immutable representation of a compiled regular expression pattern and various option flags.
*/

typedef NS_OPTIONS(NSUInteger, NSRegularExpressionOptions) {
   NSRegularExpressionCaseInsensitive             = 1 << 0,     /* Match letters in the pattern independent of case. */
   NSRegularExpressionAllowCommentsAndWhitespace  = 1 << 1,     /* Ignore whitespace and #-prefixed comments in the pattern. */
   NSRegularExpressionIgnoreMetacharacters        = 1 << 2,     /* Treat the entire pattern as a literal string. */
   NSRegularExpressionDotMatchesLineSeparators    = 1 << 3,     /* Allow . to match any character, including line separators. */
   NSRegularExpressionAnchorsMatchLines           = 1 << 4,     /* Allow ^ and $ to match the start and end of lines. */
   NSRegularExpressionUseUnixLineSeparators       = 1 << 5,     /* Treat only \n as a line separator (otherwise, all standard line separators are used). */
   NSRegularExpressionUseUnicodeWordBoundaries    = 1 << 6      /* Use Unicode TR#29 to specify word boundaries (otherwise, traditional regular expression word boundaries are used). */
};

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface NSRegularExpression : NSObject <NSCopying, NSCoding> {
    @protected   // all instance variables are private
    NSString *_pattern;
    NSUInteger _options;
    void *_internal;
    id _reserved1;
    int32_t _checkout;
    int32_t _reserved2;
}

/* An instance of NSRegularExpression is created from a regular expression pattern and a set of options.  If the pattern is invalid, nil will be returned and an NSError will be returned by reference.  The pattern syntax currently supported is that specified by ICU.
*/
+ (nullable NSRegularExpression *)regularExpressionWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error;
- (nullable instancetype)initWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) NSString *pattern;
@property (readonly) NSRegularExpressionOptions options;
@property (readonly) NSUInteger numberOfCaptureGroups;

/* This class method will produce a string by adding backslash escapes as necessary to the given string, to escape any characters that would otherwise be treated as pattern metacharacters.
*/
+ (NSString *)escapedPatternForString:(NSString *)string;

@end


typedef NS_OPTIONS(NSUInteger, NSMatchingOptions) {
   NSMatchingReportProgress         = 1 << 0,       /* Call the block periodically during long-running match operations. */
   NSMatchingReportCompletion       = 1 << 1,       /* Call the block once after the completion of any matching. */
   NSMatchingAnchored               = 1 << 2,       /* Limit matches to those at the start of the search range. */
   NSMatchingWithTransparentBounds  = 1 << 3,       /* Allow matching to look beyond the bounds of the search range. */
   NSMatchingWithoutAnchoringBounds = 1 << 4        /* Prevent ^ and $ from automatically matching the beginning and end of the search range. */
};

typedef NS_OPTIONS(NSUInteger, NSMatchingFlags) {
   NSMatchingProgress               = 1 << 0,       /* Set when the block is called to report progress during a long-running match operation. */
   NSMatchingCompleted              = 1 << 1,       /* Set when the block is called after completion of any matching. */
   NSMatchingHitEnd                 = 1 << 2,       /* Set when the current match operation reached the end of the search range. */
   NSMatchingRequiredEnd            = 1 << 3,       /* Set when the current match depended on the location of the end of the search range. */
   NSMatchingInternalError          = 1 << 4        /* Set when matching failed due to an internal error. */
};

@interface NSRegularExpression (NSMatching)

/* The fundamental matching method on NSRegularExpression is a block iterator.  There are several additional convenience methods, for returning all matches at once, the number of matches, the first match, or the range of the first match.  Each match is specified by an instance of NSTextCheckingResult (of type NSTextCheckingTypeRegularExpression) in which the overall match range is given by the range property (equivalent to rangeAtIndex:0) and any capture group ranges are given by rangeAtIndex: for indexes from 1 to numberOfCaptureGroups.  {NSNotFound, 0} is used if a particular capture group does not participate in the match.
*/

- (void)enumerateMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range usingBlock:(void (^)(NSTextCheckingResult * __nullable result, NSMatchingFlags flags, BOOL *stop))block;

- (NSArray<NSTextCheckingResult *> *)matchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
- (NSUInteger)numberOfMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
- (nullable NSTextCheckingResult *)firstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
- (NSRange)rangeOfFirstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;

/* By default, the block iterator method calls the block precisely once for each match, with a non-nil result and appropriate flags.  The client may then stop the operation by setting the contents of stop to YES.  If the NSMatchingReportProgress option is specified, the block will also be called periodically during long-running match operations, with nil result and NSMatchingProgress set in the flags, at which point the client may again stop the operation by setting the contents of stop to YES.  If the NSMatchingReportCompletion option is specified, the block will be called once after matching is complete, with nil result and NSMatchingCompleted set in the flags, plus any additional relevant flags from among NSMatchingHitEnd, NSMatchingRequiredEnd, or NSMatchingInternalError.  NSMatchingReportProgress and NSMatchingReportCompletion have no effect for methods other than the block iterator.

NSMatchingHitEnd is set in the flags passed to the block if the current match operation reached the end of the search range.  NSMatchingRequiredEnd is set in the flags passed to the block if the current match depended on the location of the end of the search range.  NSMatchingInternalError is set in the flags passed to the block if matching failed due to an internal error (such as an expression requiring exponential memory allocations) without examining the entire search range.

NSMatchingAnchored, NSMatchingWithTransparentBounds, and NSMatchingWithoutAnchoringBounds can apply to any match or replace method.  If NSMatchingAnchored is specified, matches are limited to those at the start of the search range.  If NSMatchingWithTransparentBounds is specified, matching may examine parts of the string beyond the bounds of the search range, for purposes such as word boundary detection, lookahead, etc.  If NSMatchingWithoutAnchoringBounds is specified, ^ and $ will not automatically match the beginning and end of the search range (but will still match the beginning and end of the entire string).  NSMatchingWithTransparentBounds and NSMatchingWithoutAnchoringBounds have no effect if the search range covers the entire string.

NSRegularExpression is designed to be immutable and threadsafe, so that a single instance can be used in matching operations on multiple threads at once.  However, the string on which it is operating should not be mutated during the course of a matching operation (whether from another thread or from within the block used in the iteration).
*/

@end


@interface NSRegularExpression (NSReplacement)

/* NSRegularExpression also provides find-and-replace methods for both immutable and mutable strings.  The replacement is treated as a template, with $0 being replaced by the contents of the matched range, $1 by the contents of the first capture group, and so on.  Additional digits beyond the maximum required to represent the number of capture groups will be treated as ordinary characters, as will a $ not followed by digits.  Backslash will escape both $ and itself.
*/
- (NSString *)stringByReplacingMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;
- (NSUInteger)replaceMatchesInString:(NSMutableString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;

/* For clients implementing their own replace functionality, this is a method to perform the template substitution for a single result, given the string from which the result was matched, an offset to be added to the location of the result in the string (for example, in case modifications to the string moved the result since it was matched), and a replacement template.
*/
- (NSString *)replacementStringForResult:(NSTextCheckingResult *)result inString:(NSString *)string offset:(NSInteger)offset template:(NSString *)templ;

/* This class method will produce a string by adding backslash escapes as necessary to the given string, to escape any characters that would otherwise be treated as template metacharacters. 
*/
+ (NSString *)escapedTemplateForString:(NSString *)string;

@end

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface NSDataDetector : NSRegularExpression {
    @protected   // all instance variables are private
    NSTextCheckingTypes _types;
}

/* NSDataDetector is a specialized subclass of NSRegularExpression.  Instead of finding matches to regular expression patterns, it matches items identified by Data Detectors, such as dates, addresses, and URLs.  The checkingTypes argument should contain one or more of the types NSTextCheckingTypeDate, NSTextCheckingTypeAddress, NSTextCheckingTypeLink, NSTextCheckingTypePhoneNumber, and NSTextCheckingTypeTransitInformation.  The NSTextCheckingResult instances returned will be of the appropriate types from that list.
*/
+ (nullable NSDataDetector *)dataDetectorWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error;
- (nullable instancetype)initWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error NS_DESIGNATED_INITIALIZER;

@property (readonly) NSTextCheckingTypes checkingTypes;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSKeyedArchiver.h
/*	NSKeyedArchiver.h
	Copyright (c) 2001-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>
#import <Foundation/NSPropertyList.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <Foundation/NSGeometry.h>
#endif


@class NSArray<ObjectType>, NSMutableData, NSData, NSString;
@protocol NSKeyedArchiverDelegate, NSKeyedUnarchiverDelegate;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const NSInvalidArchiveOperationException;
FOUNDATION_EXPORT NSString * const NSInvalidUnarchiveOperationException;
// Archives created using the class method archivedRootDataWithObject used this key for the root object in the hierarchy of encoded objects. The NSKeyedUnarchiver class method unarchiveObjectWithData: will look for this root key as well. You can also use it as the key for the root object in your own archives.
FOUNDATION_EXPORT NSString * const NSKeyedArchiveRootObjectKey NS_AVAILABLE(10_9, 7_0);

@interface NSKeyedArchiver : NSCoder {
@private
    void *_stream;
    NSUInteger _flags;
    id _delegate;
    id _containers;
    id _objects;
    id _objRefMap;
    id _replacementMap;
    id _classNameMap;
    id _conditionals;
    id _classes;
    NSUInteger _genericKey;
    void *_cache;
    NSUInteger _cacheSize;
    NSUInteger _estimatedCount;
    void *_reserved2;
    id _visited;
    void *  __strong _reserved0;
}

+ (NSData *)archivedDataWithRootObject:(id)rootObject;
+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;

- (instancetype)initForWritingWithMutableData:(NSMutableData *)data;

@property (nullable, assign) id <NSKeyedArchiverDelegate> delegate;

@property NSPropertyListFormat outputFormat;

- (void)finishEncoding;

+ (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;
- (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;
	// During encoding, the coder first checks with the coder's
	// own table, then if there was no mapping there, the class's.

+ (nullable NSString *)classNameForClass:(Class)cls;
- (nullable NSString *)classNameForClass:(Class)cls;

- (void)encodeObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(nullable id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;	// native int
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(nullable const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

// Enables secure coding support on this keyed archiver. You do not need to enable secure coding on the archiver to enable secure coding on the unarchiver. Enabling secure coding on the archiver is a way for you to be sure that all classes that are encoded conform with NSSecureCoding (it will throw an exception if a class which does not NSSecureCoding is archived). Note that the getter is on the superclass, NSCoder. See NSCoder for more information about secure coding.
@property (readwrite) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

@end

@interface NSKeyedUnarchiver : NSCoder {
@private
    id _delegate;
    uint32_t _flags;
    id _objRefMap;
    id _replacementMap;
    id _nameClassMap;
    id _tmpRefObjMap;
    id _refObjMap;
    int32_t _genericKey;
    id _data;
    void *_offsetData;
    id _containers;
    id _objects;
    const uint8_t *_bytes;
    uint64_t _len;
    id _helper;
    void *  __strong _reserved0;
}

+ (nullable id)unarchiveObjectWithData:(NSData *)data;
+ (nullable id)unarchiveTopLevelObjectWithData:(NSData *)data error:(NSError **)error NS_AVAILABLE(10_11, 9_0) NS_SWIFT_UNAVAILABLE("Use 'unarchiveTopLevelObjectWithData(_:) throws' instead");
+ (nullable id)unarchiveObjectWithFile:(NSString *)path;

- (instancetype)initForReadingWithData:(NSData *)data;

@property (nullable, assign) id <NSKeyedUnarchiverDelegate> delegate;

- (void)finishDecoding;

+ (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;
- (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;
	// During decoding, the coder first checks with the coder's
	// own table, then if there was no mapping there, the class's.

+ (nullable Class)classForClassName:(NSString *)codedName;
- (nullable Class)classForClassName:(NSString *)codedName;

- (BOOL)containsValueForKey:(NSString *)key;

- (nullable id)decodeObjectForKey:(NSString *)key;
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;		// may raise a range exception
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;	// returned bytes immutable, and they go away with the unarchiver, not the containing autorelease pool

// Enables secure coding support on this keyed unarchiver. When enabled, anarchiving a disallowed class throws an exception. Once enabled, attempting to set requiresSecureCoding to NO will throw an exception. This is to prevent classes from selectively turning secure coding off. This is designed to be set once at the top level and remain on. Note that the getter is on the superclass, NSCoder. See NSCoder for more information about secure coding.
@property (readwrite) BOOL requiresSecureCoding NS_AVAILABLE(10_8, 6_0);

@end

@protocol NSKeyedArchiverDelegate <NSObject>
@optional

// substitution
- (nullable id)archiver:(NSKeyedArchiver *)archiver willEncodeObject:(id)object;
	// Informs the delegate that the object is about to be encoded.  The delegate
	// either returns this object or can return a different object to be encoded
	// instead.  The delegate can also fiddle with the coder state.  If the delegate
	// returns nil, nil is encoded.  This method is called after the original object
        // may have replaced itself with replacementObjectForKeyedArchiver:.
        // This method is not called for an object once a replacement mapping has been
        // setup for that object (either explicitly, or because the object has previously
        // been encoded).  This is also not called when nil is about to be encoded.
        // This method is called whether or not the object is being encoded conditionally.

- (void)archiver:(NSKeyedArchiver *)archiver didEncodeObject:(nullable id)object;
	// Informs the delegate that the given object has been encoded.  The delegate
	// might restore some state it had fiddled previously, or use this to keep
	// track of the objects which are encoded.  The object may be nil.  Not called
	// for conditional objects until they are really encoded (if ever).

// notification
- (void)archiver:(NSKeyedArchiver *)archiver willReplaceObject:(nullable id)object withObject:(nullable id)newObject;
	// Informs the delegate that the newObject is being substituted for the
	// object. This is also called when the delegate itself is doing/has done
	// the substitution. The delegate may use this method if it is keeping track
	// of the encoded or decoded objects.

- (void)archiverWillFinish:(NSKeyedArchiver *)archiver;
	// Notifies the delegate that encoding is about to finish.

- (void)archiverDidFinish:(NSKeyedArchiver *)archiver;
	// Notifies the delegate that encoding has finished.

@end

@protocol NSKeyedUnarchiverDelegate <NSObject>
@optional

// error handling
- (nullable Class)unarchiver:(NSKeyedUnarchiver *)unarchiver cannotDecodeObjectOfClassName:(NSString *)name originalClasses:(NSArray<NSString *> *)classNames;
	// Informs the delegate that the named class is not available during decoding.
	// The delegate may, for example, load some code to introduce the class to the
	// runtime and return it, or substitute a different class object.  If the
	// delegate returns nil, unarchiving aborts with an exception.  The first class
        // name string in the array is the class of the encoded object, the second is
        // the immediate superclass, and so on.

// substitution
- (nullable id)unarchiver:(NSKeyedUnarchiver *)unarchiver didDecodeObject:(nullable id) NS_RELEASES_ARGUMENT object NS_RETURNS_RETAINED;
	// Informs the delegate that the object has been decoded.  The delegate
	// either returns this object or can return a different object to replace
	// the decoded one.  The object may be nil.  If the delegate returns nil,
        // the decoded value will be unchanged (that is, the original object will be
        // decoded). The delegate may use this to keep track of the decoded objects.

// notification
- (void)unarchiver:(NSKeyedUnarchiver *)unarchiver willReplaceObject:(id)object withObject:(id)newObject;
	// Informs the delegate that the newObject is being substituted for the
	// object. This is also called when the delegate itself is doing/has done
	// the substitution. The delegate may use this method if it is keeping track
	// of the encoded or decoded objects.

- (void)unarchiverWillFinish:(NSKeyedUnarchiver *)unarchiver;
	// Notifies the delegate that decoding is about to finish.

- (void)unarchiverDidFinish:(NSKeyedUnarchiver *)unarchiver;
	// Notifies the delegate that decoding has finished.

@end

@interface NSObject (NSKeyedArchiverObjectSubstitution)

@property (nullable, readonly) Class classForKeyedArchiver;
	// Implemented by classes to substitute a new class for instances during
	// encoding.  The object will be encoded as if it were a member of the
	// returned class.  The results of this method are overridden by the archiver
        // class and instance name<->class encoding tables.  If nil is returned,
        // the result of this method is ignored.  This method returns the result of
	// [self classForArchiver] by default, NOT -classForCoder as might be
	// expected.  This is a concession to source compatibility.

- (nullable id)replacementObjectForKeyedArchiver:(NSKeyedArchiver *)archiver;
	// Implemented by classes to substitute new instances for the receiving
	// instance during encoding.  The returned object will be encoded instead
	// of the receiver (if different).  This method is called only if no
	// replacement mapping for the object has been set up in the archiver yet
        // (for example, due to a previous call of replacementObjectForKeyedArchiver:
        // to that object).  This method returns the result of
	// [self replacementObjectForArchiver:nil] by default, NOT
	// -replacementObjectForCoder: as might be expected.  This is a concession
	// to source compatibility.


+ (NSArray<NSString *> *)classFallbacksForKeyedArchiver;


@end

@interface NSObject (NSKeyedUnarchiverObjectSubstitution)

+ (Class)classForKeyedUnarchiver;
	// Implemented by classes to substitute a new class during decoding.
        // Objects of the class will be decoded as members of the returned
        // class.  This method overrides the results of the unarchiver's class and
        // instance name<->class encoding tables.  Returns self by default.

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSXMLParser.h
/*	NSXMLParser.h
        Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary<KeyType, ObjectType>, NSError, NSString, NSURL, NSInputStream, NSSet<ObjectType>;
@protocol NSXMLParserDelegate;

NS_ASSUME_NONNULL_BEGIN

NS_ENUM_AVAILABLE(10_9, 8_0)
typedef NS_ENUM(NSUInteger, NSXMLParserExternalEntityResolvingPolicy) {
    NSXMLParserResolveExternalEntitiesNever = 0, // default
    NSXMLParserResolveExternalEntitiesNoNetwork,
    NSXMLParserResolveExternalEntitiesSameOriginOnly, //only applies to NSXMLParser instances initialized with -initWithContentsOfURL:
    NSXMLParserResolveExternalEntitiesAlways
};

@interface NSXMLParser : NSObject {
@private
    id _reserved0;
    id _delegate;
    id _reserved1;
    id _reserved2;
    id _reserved3;
}
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;  // initializes the parser with the specified URL.
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER; // create the parser from data
- (instancetype)initWithStream:(NSInputStream *)stream NS_AVAILABLE(10_7, 5_0); //create a parser that incrementally pulls data from the specified stream and parses it.

// delegate management. The delegate is not retained.
@property (nullable, assign) id <NSXMLParserDelegate> delegate;

@property BOOL shouldProcessNamespaces;
@property BOOL shouldReportNamespacePrefixes;
    
// The next two properties are really only available in OS X 10.9.5 or later
@property NSXMLParserExternalEntityResolvingPolicy externalEntityResolvingPolicy NS_AVAILABLE(10_9, 8_0); //defaults to NSXMLNodeLoadExternalEntitiesNever

@property (nullable, copy) NSSet<NSURL *> *allowedExternalEntityURLs NS_AVAILABLE(10_9, 8_0);

- (BOOL)parse;	// called to start the event-driven parse. Returns YES in the event of a successful parse, and NO in case of error.
- (void)abortParsing;	// called by the delegate to stop the parse. The delegate will get an error message sent to it.

@property (nullable, readonly, copy) NSError *parserError;	// can be called after a parse is over to determine parser state.

//Toggles between disabling external entities entirely, and the current setting of the 'externalEntityResolvingPolicy'.
//The 'externalEntityResolvingPolicy' property should be used instead of this, unless targeting 10.9/7.0 or earlier
@property BOOL shouldResolveExternalEntities;

@end

// Once a parse has begun, the delegate may be interested in certain parser state. These methods will only return meaningful information during parsing, or after an error has occurred.
@interface NSXMLParser (NSXMLParserLocatorAdditions)
@property (nullable, readonly, copy) NSString *publicID;
@property (nullable, readonly, copy) NSString *systemID;
@property (readonly) NSInteger lineNumber;
@property (readonly) NSInteger columnNumber;

@end

/*
 
 For the discussion of event methods, assume the following XML:

 <?xml version="1.0" encoding="UTF-8"?>
 <?xml-stylesheet type='text/css' href='cvslog.css'?>
 <!DOCTYPE cvslog SYSTEM "cvslog.dtd">
 <cvslog xmlns="http://xml.apple.com/cvslog">
   <radar:radar xmlns:radar="http://xml.apple.com/radar">
     <radar:bugID>2920186</radar:bugID>
     <radar:title>API/NSXMLParser: there ought to be an NSXMLParser</radar:title>
   </radar:radar>
 </cvslog>
 
 */

// The parser's delegate is informed of events through the methods in the NSXMLParserDelegateEventAdditions category.
@protocol NSXMLParserDelegate <NSObject>
@optional

// Document handling methods
- (void)parserDidStartDocument:(NSXMLParser *)parser;
    // sent when the parser begins parsing of the document.
- (void)parserDidEndDocument:(NSXMLParser *)parser;
    // sent when the parser has completed parsing. If this is encountered, the parse was successful.

// DTD handling methods for various declarations.
- (void)parser:(NSXMLParser *)parser foundNotationDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

- (void)parser:(NSXMLParser *)parser foundUnparsedEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID notationName:(nullable NSString *)notationName;

- (void)parser:(NSXMLParser *)parser foundAttributeDeclarationWithName:(NSString *)attributeName forElement:(NSString *)elementName type:(nullable NSString *)type defaultValue:(nullable NSString *)defaultValue;

- (void)parser:(NSXMLParser *)parser foundElementDeclarationWithName:(NSString *)elementName model:(NSString *)model;

- (void)parser:(NSXMLParser *)parser foundInternalEntityDeclarationWithName:(NSString *)name value:(nullable NSString *)value;

- (void)parser:(NSXMLParser *)parser foundExternalEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName attributes:(NSDictionary<NSString *, NSString *> *)attributeDict;
    // sent when the parser finds an element start tag.
    // In the case of the cvslog tag, the following is what the delegate receives:
    //   elementName == cvslog, namespaceURI == http://xml.apple.com/cvslog, qualifiedName == cvslog
    // In the case of the radar tag, the following is what's passed in:
    //    elementName == radar, namespaceURI == http://xml.apple.com/radar, qualifiedName == radar:radar
    // If namespace processing >isn't< on, the xmlns:radar="http://xml.apple.com/radar" is returned as an attribute pair, the elementName is 'radar:radar' and there is no qualifiedName.

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName;
    // sent when an end tag is encountered. The various parameters are supplied as above.

- (void)parser:(NSXMLParser *)parser didStartMappingPrefix:(NSString *)prefix toURI:(NSString *)namespaceURI;
    // sent when the parser first sees a namespace attribute.
    // In the case of the cvslog tag, before the didStartElement:, you'd get one of these with prefix == @"" and namespaceURI == @"http://xml.apple.com/cvslog" (i.e. the default namespace)
    // In the case of the radar:radar tag, before the didStartElement: you'd get one of these with prefix == @"radar" and namespaceURI == @"http://xml.apple.com/radar"

- (void)parser:(NSXMLParser *)parser didEndMappingPrefix:(NSString *)prefix;
    // sent when the namespace prefix in question goes out of scope.

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;
    // This returns the string of the characters encountered thus far. You may not necessarily get the longest character run. The parser reserves the right to hand these to the delegate as potentially many calls in a row to -parser:foundCharacters:

- (void)parser:(NSXMLParser *)parser foundIgnorableWhitespace:(NSString *)whitespaceString;
    // The parser reports ignorable whitespace in the same way as characters it's found.

- (void)parser:(NSXMLParser *)parser foundProcessingInstructionWithTarget:(NSString *)target data:(nullable NSString *)data;
    // The parser reports a processing instruction to you using this method. In the case above, target == @"xml-stylesheet" and data == @"type='text/css' href='cvslog.css'"

- (void)parser:(NSXMLParser *)parser foundComment:(NSString *)comment;
    // A comment (Text in a <!-- --> block) is reported to the delegate as a single string

- (void)parser:(NSXMLParser *)parser foundCDATA:(NSData *)CDATABlock;
    // this reports a CDATA block to the delegate as an NSData.

- (nullable NSData *)parser:(NSXMLParser *)parser resolveExternalEntityName:(NSString *)name systemID:(nullable NSString *)systemID;
    // this gives the delegate an opportunity to resolve an external entity itself and reply with the resulting data.

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError;
    // ...and this reports a fatal error to the delegate. The parser will stop parsing.

- (void)parser:(NSXMLParser *)parser validationErrorOccurred:(NSError *)validationError;
    // If validation is on, this will report a fatal validation error to the delegate. The parser will stop parsing.
@end

FOUNDATION_EXPORT NSString * const NSXMLParserErrorDomain	NS_AVAILABLE(10_3, 2_0);  // for use with NSError.

// Error reporting
typedef NS_ENUM(NSInteger, NSXMLParserError) {
    NSXMLParserInternalError = 1,
    NSXMLParserOutOfMemoryError = 2,
    NSXMLParserDocumentStartError = 3,
    NSXMLParserEmptyDocumentError = 4,
    NSXMLParserPrematureDocumentEndError = 5,
    NSXMLParserInvalidHexCharacterRefError = 6,
    NSXMLParserInvalidDecimalCharacterRefError = 7,
    NSXMLParserInvalidCharacterRefError = 8,
    NSXMLParserInvalidCharacterError = 9,
    NSXMLParserCharacterRefAtEOFError = 10,
    NSXMLParserCharacterRefInPrologError = 11,
    NSXMLParserCharacterRefInEpilogError = 12,
    NSXMLParserCharacterRefInDTDError = 13,
    NSXMLParserEntityRefAtEOFError = 14,
    NSXMLParserEntityRefInPrologError = 15,
    NSXMLParserEntityRefInEpilogError = 16,
    NSXMLParserEntityRefInDTDError = 17,
    NSXMLParserParsedEntityRefAtEOFError = 18,
    NSXMLParserParsedEntityRefInPrologError = 19,
    NSXMLParserParsedEntityRefInEpilogError = 20,
    NSXMLParserParsedEntityRefInInternalSubsetError = 21,
    NSXMLParserEntityReferenceWithoutNameError = 22,
    NSXMLParserEntityReferenceMissingSemiError = 23,
    NSXMLParserParsedEntityRefNoNameError = 24,
    NSXMLParserParsedEntityRefMissingSemiError = 25,
    NSXMLParserUndeclaredEntityError = 26,
    NSXMLParserUnparsedEntityError = 28,
    NSXMLParserEntityIsExternalError = 29,
    NSXMLParserEntityIsParameterError = 30,
    NSXMLParserUnknownEncodingError = 31,
    NSXMLParserEncodingNotSupportedError = 32,
    NSXMLParserStringNotStartedError = 33,
    NSXMLParserStringNotClosedError = 34,
    NSXMLParserNamespaceDeclarationError = 35,
    NSXMLParserEntityNotStartedError = 36,
    NSXMLParserEntityNotFinishedError = 37,
    NSXMLParserLessThanSymbolInAttributeError = 38,
    NSXMLParserAttributeNotStartedError = 39,
    NSXMLParserAttributeNotFinishedError = 40,
    NSXMLParserAttributeHasNoValueError = 41,
    NSXMLParserAttributeRedefinedError = 42,
    NSXMLParserLiteralNotStartedError = 43,
    NSXMLParserLiteralNotFinishedError = 44,
    NSXMLParserCommentNotFinishedError = 45,
    NSXMLParserProcessingInstructionNotStartedError = 46,
    NSXMLParserProcessingInstructionNotFinishedError = 47,
    NSXMLParserNotationNotStartedError = 48,
    NSXMLParserNotationNotFinishedError = 49,
    NSXMLParserAttributeListNotStartedError = 50,
    NSXMLParserAttributeListNotFinishedError = 51,
    NSXMLParserMixedContentDeclNotStartedError = 52,
    NSXMLParserMixedContentDeclNotFinishedError = 53,
    NSXMLParserElementContentDeclNotStartedError = 54,
    NSXMLParserElementContentDeclNotFinishedError = 55,
    NSXMLParserXMLDeclNotStartedError = 56,
    NSXMLParserXMLDeclNotFinishedError = 57,
    NSXMLParserConditionalSectionNotStartedError = 58,
    NSXMLParserConditionalSectionNotFinishedError = 59,
    NSXMLParserExternalSubsetNotFinishedError = 60,
    NSXMLParserDOCTYPEDeclNotFinishedError = 61,
    NSXMLParserMisplacedCDATAEndStringError = 62,
    NSXMLParserCDATANotFinishedError = 63,
    NSXMLParserMisplacedXMLDeclarationError = 64,
    NSXMLParserSpaceRequiredError = 65,
    NSXMLParserSeparatorRequiredError = 66,
    NSXMLParserNMTOKENRequiredError = 67,
    NSXMLParserNAMERequiredError = 68,
    NSXMLParserPCDATARequiredError = 69,
    NSXMLParserURIRequiredError = 70,
    NSXMLParserPublicIdentifierRequiredError = 71,
    NSXMLParserLTRequiredError = 72,
    NSXMLParserGTRequiredError = 73,
    NSXMLParserLTSlashRequiredError = 74,
    NSXMLParserEqualExpectedError = 75,
    NSXMLParserTagNameMismatchError = 76,
    NSXMLParserUnfinishedTagError = 77,
    NSXMLParserStandaloneValueError = 78,
    NSXMLParserInvalidEncodingNameError = 79,
    NSXMLParserCommentContainsDoubleHyphenError = 80,
    NSXMLParserInvalidEncodingError = 81,
    NSXMLParserExternalStandaloneEntityError = 82,
    NSXMLParserInvalidConditionalSectionError = 83,
    NSXMLParserEntityValueRequiredError = 84,
    NSXMLParserNotWellBalancedError = 85,
    NSXMLParserExtraContentError = 86,
    NSXMLParserInvalidCharacterInEntityError = 87,
    NSXMLParserParsedEntityRefInInternalError = 88,
    NSXMLParserEntityRefLoopError = 89,
    NSXMLParserEntityBoundaryError = 90,
    NSXMLParserInvalidURIError = 91,
    NSXMLParserURIFragmentError = 92,
    NSXMLParserNoDTDError = 94,
    NSXMLParserDelegateAbortedParseError = 512
};

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSURLCredentialStorage.h
/*	
    NSURLCredentialStorage.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLProtectionSpace.h>

@class NSDictionary<KeyType, ObjectType>;
@class NSString;
@class NSURLCredential;
@class NSURLSessionTask;

@class NSURLCredentialStorageInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
    @class NSURLCredentialStorage
    @discussion NSURLCredentialStorage implements a singleton object (shared instance) which manages the shared credentials cache. Note: Whereas in Mac OS X any application can access any credential with a persistence of NSURLCredentialPersistencePermanent provided the user gives permission, in iPhone OS an application can access only its own credentials.
*/

@interface NSURLCredentialStorage : NSObject
{
    @private
    NSURLCredentialStorageInternal *_internal;
}

/*!
    @method sharedCredentialStorage
    @abstract Get the shared singleton authentication storage
    @result the shared authentication storage
*/
+ (NSURLCredentialStorage *)sharedCredentialStorage;

/*!
    @method credentialsForProtectionSpace:
    @abstract Get a dictionary mapping usernames to credentials for the specified protection space.
    @param protectionSpace An NSURLProtectionSpace indicating the protection space for which to get credentials
    @result A dictionary where the keys are usernames and the values are the corresponding NSURLCredentials.
*/
- (nullable NSDictionary<NSString *, NSURLCredential *> *)credentialsForProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method allCredentials
    @abstract Get a dictionary mapping NSURLProtectionSpaces to dictionaries which map usernames to NSURLCredentials
    @result an NSDictionary where the keys are NSURLProtectionSpaces
    and the values are dictionaries, in which the keys are usernames
    and the values are NSURLCredentials
*/
@property (readonly, copy) NSDictionary<NSURLProtectionSpace *, NSDictionary<NSString *, NSURLCredential *> *> *allCredentials;

/*!
    @method setCredential:forProtectionSpace:
    @abstract Add a new credential to the set for the specified protection space or replace an existing one.
    @param credential The credential to set.
    @param space The protection space for which to add it. 
    @discussion Multiple credentials may be set for a given protection space, but each must have
    a distinct user. If a credential with the same user is already set for the protection space,
    the new one will replace it.
*/
- (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method removeCredential:forProtectionSpace:
    @abstract Remove the credential from the set for the specified protection space.
    @param credential The credential to remove.
    @param space The protection space for which a credential should be removed
    @discussion The credential is removed from both persistent and temporary storage. A credential that
    has a persistence policy of NSURLCredentialPersistenceSynchronizable will fail.  
    See removeCredential:forProtectionSpace:options.
*/
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/*!
 @method removeCredential:forProtectionSpace:options
 @abstract Remove the credential from the set for the specified protection space based on options.
 @param credential The credential to remove.
 @param space The protection space for which a credential should be removed
 @param options A dictionary containing options to consider when removing the credential.  This should
 be used when trying to delete a credential that has the NSURLCredentialPersistenceSynchronizable policy.
 Please note that when NSURLCredential objects that have a NSURLCredentialPersistenceSynchronizable policy
 are removed, the credential will be removed on all devices that contain this credential.
 @discussion The credential is removed from both persistent and temporary storage.
 */
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_9, 7_0);

/*!
    @method defaultCredentialForProtectionSpace:
    @abstract Get the default credential for the specified protection space.
    @param space The protection space for which to get the default credential.
*/
- (nullable NSURLCredential *)defaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method setDefaultCredential:forProtectionSpace:
    @abstract Set the default credential for the specified protection space.
    @param credential The credential to set as default.
    @param space The protection space for which the credential should be set as default.
    @discussion If the credential is not yet in the set for the protection space, it will be added to it.
*/
- (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

@end

@interface NSURLCredentialStorage (NSURLSessionTaskAdditions)
- (void)getCredentialsForProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task completionHandler:(void (^) (NSDictionary<NSString *, NSURLCredential *> * __nullable credentials))completionHandler NS_AVAILABLE(10_10, 8_0);
- (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace options:(nullable NSDictionary<NSString *, id> *)options task:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
- (void)getDefaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space task:(NSURLSessionTask *)task completionHandler:(void (^) (NSURLCredential * __nullable credential))completionHandler NS_AVAILABLE(10_10, 8_0);
- (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
@end

/*!
    @const NSURLCredentialStorageChangedNotification
    @abstract This notification is sent on the main thread whenever
    the set of stored credentials changes.
*/
FOUNDATION_EXPORT NSString *const NSURLCredentialStorageChangedNotification;

/*
 *  NSURLCredentialStorageRemoveSynchronizableCredentials - (NSNumber value)
 *		A key that indicates either @YES or @NO that credentials which contain the NSURLCredentialPersistenceSynchronizable
 *		attribute should be removed.  If the key is missing or the value is @NO, then no attempt will be made
 *		to remove such a credential.
 */
FOUNDATION_EXPORT NSString *const NSURLCredentialStorageRemoveSynchronizableCredentials NS_AVAILABLE(10_9, 7_0);


NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSPersonNameComponents.h
/*	NSPersonNameComponents.h
	Copyright (c) 2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSPersonNameComponents : NSObject <NSCopying, NSSecureCoding>{
@private
    id _private;
}

/* The below examples all assume the full name Dr. Johnathan Maple Appleseed Esq., nickname "Johnny" */

/* Pre-nominal letters denoting title, salutation, or honorific, e.g. Dr., Mr. */
@property (copy, nullable) NSString *namePrefix;

/* Name bestowed upon an individual by one's parents, e.g. Johnathan */
@property (copy, nullable) NSString *givenName;

/* Secondary given name chosen to differentiate those with the same first name, e.g. Maple  */
@property (copy, nullable) NSString *middleName;

/* Name passed from one generation to another to indicate lineage, e.g. Appleseed  */
@property (copy, nullable) NSString *familyName;

/* Post-nominal letters denoting degree, accreditation, or other honor, e.g. Esq., Jr., Ph.D. */
@property (copy, nullable) NSString *nameSuffix;

/* Name substituted for the purposes of familiarity, e.g. "Johnny"*/
@property (copy, nullable) NSString *nickname;

/* Each element of the phoneticRepresentation should correspond to an element of the original PersonNameComponents instance.
   The phoneticRepresentation of the phoneticRepresentation object itself will be ignored. nil by default, must be instantiated.
*/
@property (copy, nullable) NSPersonNameComponents *phoneticRepresentation;

@end

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSHashTable.h
/*	NSHashTable.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSHASHTABLE__)
#define __FOUNDATION_NSHASHTABLE__ 1

@class NSArray<ObjectType>, NSSet<ObjectType>, NSHashTable;

NS_ASSUME_NONNULL_BEGIN

/* An NSHashTable is modeled after a set, although, because of its options, is not a set because it can behave differently (for example, if pointer equality is specified two isEqual strings will both be entered).  The major option is to provide for "weak" references that are removed automatically, but at some indefinite point in the future.
   An NSHashTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunctionsOptions or configure or use an NSPointerFunctions object itself for initialization.
*/

static const NSPointerFunctionsOptions NSHashTableStrongMemory NS_AVAILABLE(10_5, 6_0) = NSPointerFunctionsStrongMemory;
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
static const NSPointerFunctionsOptions NSHashTableZeroingWeakMemory NS_DEPRECATED_MAC(10_5, 10_8) = NSPointerFunctionsZeroingWeakMemory;
#endif
static const NSPointerFunctionsOptions NSHashTableCopyIn NS_AVAILABLE(10_5, 6_0) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSHashTableObjectPointerPersonality NS_AVAILABLE(10_5, 6_0) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSHashTableWeakMemory NS_AVAILABLE(10_8, 6_0) = NSPointerFunctionsWeakMemory;

typedef NSUInteger NSHashTableOptions;

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSHashTable<ObjectType> : NSObject <NSCopying, NSCoding, NSFastEnumeration>

- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithPointerFunctions:(NSPointerFunctions *)functions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;

// conveniences

+ (NSHashTable<ObjectType> *)hashTableWithOptions:(NSPointerFunctionsOptions)options;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
+ (id)hashTableWithWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);  // GC zeroing, otherwise unsafe unretained
#endif

+ (NSHashTable<ObjectType> *)weakObjectsHashTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak object is reclaimed


/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
@property (readonly, copy) NSPointerFunctions *pointerFunctions;

@property (readonly) NSUInteger count;
- (nullable ObjectType)member:(nullable ObjectType)object;
- (NSEnumerator<ObjectType> *)objectEnumerator;

- (void)addObject:(nullable ObjectType)object;
- (void)removeObject:(nullable ObjectType)object;

- (void)removeAllObjects;

@property (readonly, copy) NSArray<ObjectType> *allObjects;    // convenience

@property (nullable, nonatomic, readonly) ObjectType anyObject;
- (BOOL)containsObject:(nullable ObjectType)anObject;

- (BOOL)intersectsHashTable:(NSHashTable<ObjectType> *)other;
- (BOOL)isEqualToHashTable:(NSHashTable<ObjectType> *)other;
- (BOOL)isSubsetOfHashTable:(NSHashTable<ObjectType> *)other;

- (void)intersectHashTable:(NSHashTable<ObjectType> *)other;
- (void)unionHashTable:(NSHashTable<ObjectType> *)other;
- (void)minusHashTable:(NSHashTable<ObjectType> *)other;

@property (readonly, copy) NSSet<ObjectType> *setRepresentation;  // create a set of the contents

@end

NS_ASSUME_NONNULL_END


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

NS_ASSUME_NONNULL_BEGIN

/****************	(void *) Hash table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void * __nullable _bs;} NSHashEnumerator;

FOUNDATION_EXPORT void NSFreeHashTable(NSHashTable *table);
FOUNDATION_EXPORT void NSResetHashTable(NSHashTable *table);
FOUNDATION_EXPORT BOOL NSCompareHashTables(NSHashTable *table1, NSHashTable *table2);
FOUNDATION_EXPORT NSHashTable *NSCopyHashTableWithZone(NSHashTable *table, NSZone * __nullable zone);
FOUNDATION_EXPORT void *NSHashGet(NSHashTable *table, const void * __nullable pointer);
FOUNDATION_EXPORT void NSHashInsert(NSHashTable *table, const void * __nullable pointer);
FOUNDATION_EXPORT void NSHashInsertKnownAbsent(NSHashTable *table, const void * __nullable pointer);
FOUNDATION_EXPORT void * __nullable NSHashInsertIfAbsent(NSHashTable *table, const void * __nullable pointer);
FOUNDATION_EXPORT void NSHashRemove(NSHashTable *table, const void * __nullable pointer);
FOUNDATION_EXPORT NSHashEnumerator NSEnumerateHashTable(NSHashTable *table);
FOUNDATION_EXPORT void * __nullable NSNextHashEnumeratorItem(NSHashEnumerator *enumerator);
FOUNDATION_EXPORT void NSEndHashTableEnumeration(NSHashEnumerator *enumerator);
FOUNDATION_EXPORT NSUInteger NSCountHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSString *NSStringFromHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSArray *NSAllHashTableObjects(NSHashTable *table);


/****************	Legacy	****************/

typedef struct {
    NSUInteger	(* __nullable hash)(NSHashTable *table, const void *);
    BOOL	(* __nullable isEqual)(NSHashTable *table, const void *, const void *);
    void	(* __nullable retain)(NSHashTable *table, const void *);
    void	(* __nullable release)(NSHashTable *table, void *);
    NSString 	* __nullable (* __nullable describe)(NSHashTable *table, const void *);
} NSHashTableCallBacks;

FOUNDATION_EXPORT NSHashTable *NSCreateHashTableWithZone(NSHashTableCallBacks callBacks, NSUInteger capacity, NSZone * __nullable zone);
FOUNDATION_EXPORT NSHashTable *NSCreateHashTable(NSHashTableCallBacks callBacks, NSUInteger capacity);


FOUNDATION_EXPORT const NSHashTableCallBacks NSIntegerHashCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonRetainedObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedObjectIdentityHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSPointerToStructHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSIntHashCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

NS_ASSUME_NONNULL_END

#else

#if defined(__has_include)
#if __has_include(<Foundation/NSHashTablePriv.h>)
#include <Foundation/NSHashTablePriv.h>
#endif
#endif

#endif

#endif

// ==========  Foundation.framework/Headers/NSNumberFormatter.h
/*	NSNumberFormatter.h
	Copyright (c) 1996-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>

@class NSLocale, NSError, NSMutableDictionary, NSRecursiveLock, NSString, NSCache;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSNumberFormatterBehavior) {
    NSNumberFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSNumberFormatterBehavior10_0 = 1000,
#endif
    NSNumberFormatterBehavior10_4 = 1040,
};

@interface NSNumberFormatter : NSFormatter {
@private
    NSMutableDictionary	*_attributes;
    __strong CFNumberFormatterRef _formatter;
    NSUInteger _counter;
    NSNumberFormatterBehavior _behavior;
    NSRecursiveLock *_lock;
    unsigned long _stateBitMask; // this is for NSUnitFormatter
    NSInteger _cacheGeneration;
    void *_reserved[8];
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (nullable NSString *)stringFromNumber:(NSNumber *)number;
- (nullable NSNumber *)numberFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSNumberFormatterStyle) {
    NSNumberFormatterNoStyle = kCFNumberFormatterNoStyle,
    NSNumberFormatterDecimalStyle = kCFNumberFormatterDecimalStyle,
    NSNumberFormatterCurrencyStyle = kCFNumberFormatterCurrencyStyle,
    NSNumberFormatterPercentStyle = kCFNumberFormatterPercentStyle,
    NSNumberFormatterScientificStyle = kCFNumberFormatterScientificStyle,
    NSNumberFormatterSpellOutStyle = kCFNumberFormatterSpellOutStyle,
    NSNumberFormatterOrdinalStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterOrdinalStyle,
    NSNumberFormatterCurrencyISOCodeStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyISOCodeStyle,
    NSNumberFormatterCurrencyPluralStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyPluralStyle,
    NSNumberFormatterCurrencyAccountingStyle NS_ENUM_AVAILABLE(10_11, 9_0) = kCFNumberFormatterCurrencyAccountingStyle,
};

+ (NSString *)localizedStringFromNumber:(NSNumber *)num numberStyle:(NSNumberFormatterStyle)nstyle NS_AVAILABLE(10_6, 4_0);

// Attributes of an NSNumberFormatter

+ (NSNumberFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior;

@property NSNumberFormatterStyle numberStyle;
@property (null_resettable, copy) NSLocale *locale;
@property BOOL generatesDecimalNumbers;
@property NSNumberFormatterBehavior formatterBehavior;

@property (null_resettable, copy) NSString *negativeFormat;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeValues;
@property (null_resettable, copy) NSString *positiveFormat;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveValues;
@property BOOL allowsFloats;
@property (null_resettable, copy) NSString *decimalSeparator;
@property BOOL alwaysShowsDecimalSeparator;
@property (null_resettable, copy) NSString *currencyDecimalSeparator;
@property BOOL usesGroupingSeparator;
@property (null_resettable, copy) NSString *groupingSeparator;

@property (nullable, copy) NSString *zeroSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForZero;
@property (copy) NSString *nilSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNil;
@property (null_resettable, copy) NSString *notANumberSymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNotANumber;
@property (copy) NSString *positiveInfinitySymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveInfinity;
@property (copy) NSString *negativeInfinitySymbol;
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeInfinity;

@property (null_resettable, copy) NSString *positivePrefix;
@property (null_resettable, copy) NSString *positiveSuffix;
@property (null_resettable, copy) NSString *negativePrefix;
@property (null_resettable, copy) NSString *negativeSuffix;
@property (null_resettable, copy) NSString *currencyCode;
@property (null_resettable, copy) NSString *currencySymbol;
@property (null_resettable, copy) NSString *internationalCurrencySymbol;
@property (null_resettable, copy) NSString *percentSymbol;
@property (null_resettable, copy) NSString *perMillSymbol;
@property (null_resettable, copy) NSString *minusSign;
@property (null_resettable, copy) NSString *plusSign;
@property (null_resettable, copy) NSString *exponentSymbol;

@property NSUInteger groupingSize;
@property NSUInteger secondaryGroupingSize;
@property (nullable, copy) NSNumber *multiplier;
@property NSUInteger formatWidth;
@property (null_resettable, copy) NSString *paddingCharacter;


typedef NS_ENUM(NSUInteger, NSNumberFormatterPadPosition) {
    NSNumberFormatterPadBeforePrefix = kCFNumberFormatterPadBeforePrefix,
    NSNumberFormatterPadAfterPrefix = kCFNumberFormatterPadAfterPrefix,
    NSNumberFormatterPadBeforeSuffix = kCFNumberFormatterPadBeforeSuffix,
    NSNumberFormatterPadAfterSuffix = kCFNumberFormatterPadAfterSuffix
};

typedef NS_ENUM(NSUInteger, NSNumberFormatterRoundingMode) {
    NSNumberFormatterRoundCeiling = kCFNumberFormatterRoundCeiling,
    NSNumberFormatterRoundFloor = kCFNumberFormatterRoundFloor,
    NSNumberFormatterRoundDown = kCFNumberFormatterRoundDown,
    NSNumberFormatterRoundUp = kCFNumberFormatterRoundUp,
    NSNumberFormatterRoundHalfEven = kCFNumberFormatterRoundHalfEven,
    NSNumberFormatterRoundHalfDown = kCFNumberFormatterRoundHalfDown,
    NSNumberFormatterRoundHalfUp = kCFNumberFormatterRoundHalfUp
};

@property NSNumberFormatterPadPosition paddingPosition;
@property NSNumberFormatterRoundingMode roundingMode;
@property (null_resettable, copy) NSNumber *roundingIncrement;
@property NSUInteger minimumIntegerDigits;
@property NSUInteger maximumIntegerDigits;
@property NSUInteger minimumFractionDigits;
@property NSUInteger maximumFractionDigits;
@property (nullable, copy) NSNumber *minimum;
@property (nullable, copy) NSNumber *maximum;
@property (null_resettable, copy) NSString *currencyGroupingSeparator NS_AVAILABLE(10_5, 2_0);
@property (getter=isLenient) BOOL lenient NS_AVAILABLE(10_5, 2_0);
@property BOOL usesSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property NSUInteger minimumSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property NSUInteger maximumSignificantDigits NS_AVAILABLE(10_5, 2_0);
@property (getter=isPartialStringValidationEnabled) BOOL partialStringValidationEnabled NS_AVAILABLE(10_5, 2_0);

@end

@class NSDecimalNumberHandler;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSNumberFormatter (NSNumberFormatterCompatibility)

@property BOOL hasThousandSeparators;
@property (null_resettable, copy) NSString *thousandSeparator;

@property BOOL localizesFormat;

@property (copy) NSString *format;

@property (copy) NSAttributedString *attributedStringForZero;
@property (copy) NSAttributedString *attributedStringForNil;
@property (copy) NSAttributedString *attributedStringForNotANumber;

@property (copy) NSDecimalNumberHandler *roundingBehavior;

@end
#endif

NS_ASSUME_NONNULL_END
// ==========  Foundation.framework/Headers/NSByteOrder.h
/*	NSByteOrder.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreFoundation/CFByteOrder.h>

enum {
    NS_UnknownByteOrder = CFByteOrderUnknown,
    NS_LittleEndian = CFByteOrderLittleEndian,
    NS_BigEndian = CFByteOrderBigEndian
};

NS_INLINE long NSHostByteOrder(void) {
    return CFByteOrderGetCurrent();
}

NS_INLINE unsigned short NSSwapShort(unsigned short inv) {
    return CFSwapInt16(inv);
}

NS_INLINE unsigned int NSSwapInt(unsigned int inv) {
    return CFSwapInt32(inv);
}

NS_INLINE unsigned long NSSwapLong(unsigned long inv) {
#if __LP64__
    return CFSwapInt64(inv);
#else
    return CFSwapInt32(inv);
#endif
}

NS_INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    return CFSwapInt64(inv);
}

NS_INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return CFSwapInt16BigToHost(x);
}

NS_INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return CFSwapInt32BigToHost(x);
}

NS_INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64BigToHost(x);
#else
    return CFSwapInt32BigToHost(x);
#endif
}

NS_INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return CFSwapInt64BigToHost(x);
}

NS_INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return CFSwapInt16HostToBig(x);
}

NS_INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return CFSwapInt32HostToBig(x);
}

NS_INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToBig(x);
#else
    return CFSwapInt32HostToBig(x);
#endif
}

NS_INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return CFSwapInt64HostToBig(x);
}

NS_INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return CFSwapInt16LittleToHost(x);
}

NS_INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return CFSwapInt32LittleToHost(x);
}

NS_INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64LittleToHost(x);
#else
    return CFSwapInt32LittleToHost(x);
#endif
}

NS_INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return CFSwapInt64LittleToHost(x);
}

NS_INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return CFSwapInt16HostToLittle(x);
}

NS_INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return CFSwapInt32HostToLittle(x);
}

NS_INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToLittle(x);
#else
    return CFSwapInt32HostToLittle(x);
#endif
}

NS_INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return CFSwapInt64HostToLittle(x);
}


typedef struct {unsigned int v;} NSSwappedFloat;
typedef struct {unsigned long long v;} NSSwappedDouble;

NS_INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

NS_INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

NS_INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

NS_INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

NS_INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    x.v = NSSwapInt(x.v);
    return x;
}

NS_INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    x.v = NSSwapLongLong(x.v);
    return x;
}

#if defined(__BIG_ENDIAN__)

NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)

NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error Do not know the endianess of this architecture
#endif

// ==========  Foundation.framework/Headers/NSPropertyList.h
/*	NSPropertyList.h
	Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <CoreFoundation/CFPropertyList.h>

@class NSData, NSString, NSError, NSInputStream, NSOutputStream;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSPropertyListMutabilityOptions) {
    NSPropertyListImmutable = kCFPropertyListImmutable,
    NSPropertyListMutableContainers = kCFPropertyListMutableContainers,
    NSPropertyListMutableContainersAndLeaves = kCFPropertyListMutableContainersAndLeaves
};

typedef NS_ENUM(NSUInteger, NSPropertyListFormat) {
    NSPropertyListOpenStepFormat = kCFPropertyListOpenStepFormat,
    NSPropertyListXMLFormat_v1_0 = kCFPropertyListXMLFormat_v1_0,
    NSPropertyListBinaryFormat_v1_0 = kCFPropertyListBinaryFormat_v1_0
};

typedef NSPropertyListMutabilityOptions NSPropertyListReadOptions;
typedef NSUInteger NSPropertyListWriteOptions;

@interface NSPropertyListSerialization : NSObject {
    void *reserved[6];
}

/* Verify that a specified property list is valid for a given format. Returns YES if the property list is valid.
 */
+ (BOOL)propertyList:(id)plist isValidForFormat:(NSPropertyListFormat)format;

/* Create an NSData from a property list. The format can be either NSPropertyListXMLFormat_v1_0 or NSPropertyListBinaryFormat_v1_0. The options parameter is currently unused and should be set to 0. If an error occurs the return value will be nil and the error parameter (if non-NULL) set to an autoreleased NSError describing the problem.
 */
+ (nullable NSData *)dataWithPropertyList:(id)plist format:(NSPropertyListFormat)format options:(NSPropertyListWriteOptions)opt error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Write a property list to an output stream. The stream should be opened and configured. The format can be either NSPropertyListXMLFormat_v1_0 or NSPropertyListBinaryFormat_v1_0. The options parameter is currently unused and should be set to 0. If an error occurs the return value will be 0 and the error parameter (if non-NULL) set to an autoreleased NSError describing the problem. In a successful case, the return value is the number of bytes written to the stream.
 */
+ (NSInteger)writePropertyList:(id)plist toStream:(NSOutputStream *)stream format:(NSPropertyListFormat)format options:(NSPropertyListWriteOptions)opt error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Create a property list from an NSData. The options can be any of NSPropertyListMutabilityOptions. If the format parameter is non-NULL, it will be filled out with the format that the property list was stored in. If an error occurs the return value will be nil and the error parameter (if non-NULL) set to an autoreleased NSError describing the problem.
 */
+ (nullable id)propertyListWithData:(NSData *)data options:(NSPropertyListReadOptions)opt format:(nullable NSPropertyListFormat *)format error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Create a property list by reading from an NSInputStream. The options can be any of NSPropertyListMutabilityOptions. If the format parameter is non-NULL, it will be filled out with the format that the property list was stored in. If an error occurs the return value will be nil and the error parameter (if non-NULL) set to an autoreleased NSError describing the problem.
 */
+ (nullable id)propertyListWithStream:(NSInputStream *)stream options:(NSPropertyListReadOptions)opt format:(nullable NSPropertyListFormat *)format error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);


/* This method is deprecated. Use dataWithPropertyList:format:options:error: instead.
 */
+ (nullable NSData *)dataFromPropertyList:(id)plist format:(NSPropertyListFormat)format errorDescription:(out __strong NSString * __nullable * __nullable)errorString NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use dataWithPropertyList:format:options:error: instead.");

/* This method is deprecated. Use propertyListWithData:options:format:error: instead.
 */
+ (nullable id)propertyListFromData:(NSData *)data mutabilityOption:(NSPropertyListMutabilityOptions)opt format:(nullable NSPropertyListFormat *)format errorDescription:(out __strong NSString * __nullable * __nullable)errorString NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use propertyListWithData:options:format:error: instead.");

@end

NS_ASSUME_NONNULL_END
