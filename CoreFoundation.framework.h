// ==========  CoreFoundation.framework/Headers/CFUUID.h
/*	CFUUID.h
	Copyright (c) 1999-2015, Apple Inc.  All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFUUID__)
#define __COREFOUNDATION_CFUUID__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef const struct CF_BRIDGED_TYPE(id) __CFUUID * CFUUIDRef;

typedef struct {
    UInt8 byte0;
    UInt8 byte1;
    UInt8 byte2;
    UInt8 byte3;
    UInt8 byte4;
    UInt8 byte5;
    UInt8 byte6;
    UInt8 byte7;
    UInt8 byte8;
    UInt8 byte9;
    UInt8 byte10;
    UInt8 byte11;
    UInt8 byte12;
    UInt8 byte13;
    UInt8 byte14;
    UInt8 byte15;
} CFUUIDBytes;
/* The CFUUIDBytes struct is a 128-bit struct that contains the
raw UUID.  A CFUUIDRef can provide such a struct from the
CFUUIDGetUUIDBytes() function.  This struct is suitable for
passing to APIs that expect a raw UUID.
*/
        
CF_EXPORT
CFTypeID CFUUIDGetTypeID(void);

CF_EXPORT
CFUUIDRef CFUUIDCreate(CFAllocatorRef alloc);
    /* Create and return a brand new unique identifier */

CF_EXPORT
CFUUIDRef CFUUIDCreateWithBytes(CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15);
    /* Create and return an identifier with the given contents.  This may return an existing instance with its ref count bumped because of uniquing. */

CF_EXPORT
CFUUIDRef CFUUIDCreateFromString(CFAllocatorRef alloc, CFStringRef uuidStr);
    /* Converts from a string representation to the UUID.  This may return an existing instance with its ref count bumped because of uniquing. */

CF_EXPORT
CFStringRef CFUUIDCreateString(CFAllocatorRef alloc, CFUUIDRef uuid);
    /* Converts from a UUID to its string representation. */

CF_EXPORT
CFUUIDRef CFUUIDGetConstantUUIDWithBytes(CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15);
    /* This returns an immortal CFUUIDRef that should not be released.  It can be used in headers to declare UUID constants with #define. */

CF_EXPORT
CFUUIDBytes CFUUIDGetUUIDBytes(CFUUIDRef uuid);

CF_EXPORT
CFUUIDRef CFUUIDCreateFromUUIDBytes(CFAllocatorRef alloc, CFUUIDBytes bytes);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFUUID__ */

// ==========  CoreFoundation.framework/Headers/CFBundle.h
/*	CFBundle.h
	Copyright (c) 1999-2015, Apple Inc.  All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBUNDLE__)
#define __COREFOUNDATION_CFBUNDLE__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_TYPE(id) __CFBundle *CFBundleRef;
typedef struct CF_BRIDGED_TYPE(id) __CFBundle *CFPlugInRef;

/* ===================== Standard Info.plist keys ===================== */
CF_EXPORT
const CFStringRef kCFBundleInfoDictionaryVersionKey;
    /* The version of the Info.plist format */
CF_EXPORT
const CFStringRef kCFBundleExecutableKey;
    /* The name of the executable in this bundle, if any */
CF_EXPORT
const CFStringRef kCFBundleIdentifierKey;
    /* The bundle identifier (for CFBundleGetBundleWithIdentifier()) */
CF_EXPORT
const CFStringRef kCFBundleVersionKey;
    /* The version number of the bundle.  For Mac OS 9 style version numbers (for example "2.5.3d5"), */
    /* clients can use CFBundleGetVersionNumber() instead of accessing this key directly since that */
    /* function will properly convert the version string into its compact integer representation. */
CF_EXPORT
const CFStringRef kCFBundleDevelopmentRegionKey;
    /* The name of the development language of the bundle. */
CF_EXPORT
const CFStringRef kCFBundleNameKey;
    /* The human-readable name of the bundle.  This key is often found in the InfoPlist.strings since it is usually localized. */
CF_EXPORT
const CFStringRef kCFBundleLocalizationsKey;
    /* Allows an unbundled application that handles localization itself to specify which localizations it has available. */

/* ===================== Finding Bundles ===================== */

CF_EXPORT
CFBundleRef CFBundleGetMainBundle(void);

CF_EXPORT
CFBundleRef CFBundleGetBundleWithIdentifier(CFStringRef bundleID);
    /* A bundle can name itself by providing a key in the info dictionary. */
    /* This facility is meant to allow bundle-writers to get hold of their */
    /* bundle from their code without having to know where it was on the disk. */
    /* This is meant to be a replacement mechanism for +bundleForClass: users. */
    /* Note that this does not search for bundles on the disk; it will locate */
    /* only bundles already loaded or otherwise known to the current process. */

CF_EXPORT
CFArrayRef CFBundleGetAllBundles(void);
    /* This is potentially expensive, and not thread-safe.  Use with care. */
    /* Best used for debuggging or other diagnostic purposes. */

/* ===================== Creating Bundles ===================== */

CF_EXPORT
CFTypeID CFBundleGetTypeID(void);

CF_EXPORT
CFBundleRef CFBundleCreate(CFAllocatorRef allocator, CFURLRef bundleURL);
    /* Might return an existing instance with the ref-count bumped. */

CF_EXPORT
CFArrayRef CFBundleCreateBundlesFromDirectory(CFAllocatorRef allocator, CFURLRef directoryURL, CFStringRef bundleType);
    /* Create instances for all bundles in the given directory matching the given type */
    /* (or all of them if bundleType is NULL).  Instances are created using CFBundleCreate() and are not released. */

/* ==================== Basic Bundle Info ==================== */

CF_EXPORT
CFURLRef CFBundleCopyBundleURL(CFBundleRef bundle);

CF_EXPORT
CFTypeRef CFBundleGetValueForInfoDictionaryKey(CFBundleRef bundle, CFStringRef key);
    /* Returns a localized value if available, otherwise the global value. */
    /* This is the recommended function for examining the info dictionary. */

CF_EXPORT
CFDictionaryRef CFBundleGetInfoDictionary(CFBundleRef bundle);
    /* This is the global info dictionary.  Note that CFBundle may add */
    /* extra keys to the dictionary for its own use. */

CF_EXPORT
CFDictionaryRef CFBundleGetLocalInfoDictionary(CFBundleRef bundle);
    /* This is the localized info dictionary. */

CF_EXPORT
void CFBundleGetPackageInfo(CFBundleRef bundle, UInt32 *packageType, UInt32 *packageCreator);

CF_EXPORT
CFStringRef CFBundleGetIdentifier(CFBundleRef bundle);

CF_EXPORT
UInt32 CFBundleGetVersionNumber(CFBundleRef bundle);

CF_EXPORT
CFStringRef CFBundleGetDevelopmentRegion(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySupportFilesDirectoryURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyResourcesDirectoryURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyPrivateFrameworksURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySharedFrameworksURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySharedSupportURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyBuiltInPlugInsURL(CFBundleRef bundle);

/* ------------- Basic Bundle Info without a CFBundle instance ------------- */
/* This API is provided to enable developers to retrieve basic information */
/* about a bundle without having to create an instance of CFBundle. */
/* Because of caching behavior when a CFBundle instance exists, it will be faster */
/* to actually create a CFBundle if you need to retrieve multiple pieces of info. */
CF_EXPORT
CFDictionaryRef CFBundleCopyInfoDictionaryInDirectory(CFURLRef bundleURL);

CF_EXPORT
Boolean CFBundleGetPackageInfoInDirectory(CFURLRef url, UInt32 *packageType, UInt32 *packageCreator);

/* ==================== Resource Handling API ==================== */

CF_EXPORT
CFURLRef CFBundleCopyResourceURL(CFBundleRef bundle, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfType(CFBundleRef bundle, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFStringRef CFBundleCopyLocalizedString(CFBundleRef bundle, CFStringRef key, CFStringRef value, CFStringRef tableName) CF_FORMAT_ARGUMENT(2);

#define CFCopyLocalizedString(key, comment) \
            CFBundleCopyLocalizedString(CFBundleGetMainBundle(), (key), (key), NULL)
#define CFCopyLocalizedStringFromTable(key, tbl, comment) \
            CFBundleCopyLocalizedString(CFBundleGetMainBundle(), (key), (key), (tbl))
#define CFCopyLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
            CFBundleCopyLocalizedString((bundle), (key), (key), (tbl))
#define CFCopyLocalizedStringWithDefaultValue(key, tbl, bundle, value, comment) \
            CFBundleCopyLocalizedString((bundle), (key), (value), (tbl))

/* ------------- Resource Handling without a CFBundle instance ------------- */
/* This API is provided to enable developers to use the CFBundle resource */
/* searching policy without having to create an instance of CFBundle. */
/* Because of caching behavior when a CFBundle instance exists, it will be faster */
/* to actually create a CFBundle if you need to access several resources. */

CF_EXPORT
CFURLRef CFBundleCopyResourceURLInDirectory(CFURLRef bundleURL, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfTypeInDirectory(CFURLRef bundleURL, CFStringRef resourceType, CFStringRef subDirName);

/* =========== Localization-specific Resource Handling API =========== */
/* This API allows finer-grained control over specific localizations,  */
/* as distinguished from the above API, which always uses the user's   */
/* preferred localizations for the bundle in the current app context.  */

CF_EXPORT
CFArrayRef CFBundleCopyBundleLocalizations(CFBundleRef bundle);
    /* Lists the localizations that a bundle contains.  */

CF_EXPORT
CFArrayRef CFBundleCopyPreferredLocalizationsFromArray(CFArrayRef locArray);
    /* Given an array of possible localizations, returns the one or more */
    /* of them that CFBundle would use in the current application context. */
    /* To determine the localizations that would be used for a particular */
    /* bundle in the current application context, apply this function to the */
    /* result of CFBundleCopyBundleLocalizations().  */

CF_EXPORT
CFArrayRef CFBundleCopyLocalizationsForPreferences(CFArrayRef locArray, CFArrayRef prefArray);
    /* Given an array of possible localizations, returns the one or more of */
    /* them that CFBundle would use, without reference to the current application */
    /* context, if the user's preferred localizations were given by prefArray. */
    /* If prefArray is NULL, the current user's actual preferred localizations will */
    /* be used. This is not the same as CFBundleCopyPreferredLocalizationsFromArray(), */
    /* because that function takes the current application context into account. */
    /* To determine the localizations that another application would use, apply */
    /* this function to the result of CFBundleCopyBundleLocalizations().  */

CF_EXPORT
CFURLRef CFBundleCopyResourceURLForLocalization(CFBundleRef bundle, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName, CFStringRef localizationName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfTypeForLocalization(CFBundleRef bundle, CFStringRef resourceType, CFStringRef subDirName, CFStringRef localizationName);
    /* The localizationName argument to CFBundleCopyResourceURLForLocalization() or */
    /* CFBundleCopyResourceURLsOfTypeForLocalization() must be identical to one of the */
    /* localizations in the bundle, as returned by CFBundleCopyBundleLocalizations(). */
    /* It is recommended that either CFBundleCopyPreferredLocalizationsFromArray() or */
    /* CFBundleCopyLocalizationsForPreferences() be used to select the localization. */

/* =================== Unbundled application info ===================== */
/* This API is provided to enable developers to retrieve bundle-related */
/* information about an application that may be bundled or unbundled.   */
CF_EXPORT
CFDictionaryRef CFBundleCopyInfoDictionaryForURL(CFURLRef url);
    /* For a directory URL, this is equivalent to CFBundleCopyInfoDictionaryInDirectory(). */
    /* For a plain file URL representing an unbundled executable, this will attempt to read */
    /* an info dictionary from the (__TEXT, __info_plist) section, if it is a Mach-o file, */
    /* or from a 'plst' resource.  */

CF_EXPORT
CFArrayRef CFBundleCopyLocalizationsForURL(CFURLRef url);
    /* For a directory URL, this is equivalent to calling CFBundleCopyBundleLocalizations() */
    /* on the corresponding bundle.  For a plain file URL representing an unbundled executable, */
    /* this will attempt to determine its localizations using the CFBundleLocalizations and */
    /* CFBundleDevelopmentRegion keys in the dictionary returned by CFBundleCopyInfoDictionaryForURL,*/
    /* or from a 'vers' resource if those are not present.  */

CF_EXPORT
CFArrayRef CFBundleCopyExecutableArchitecturesForURL(CFURLRef url) CF_AVAILABLE(10_5, 2_0);
    /* For a directory URL, this is equivalent to calling CFBundleCopyExecutableArchitectures() */
    /* on the corresponding bundle.  For a plain file URL representing an unbundled executable, */
    /* this will return the architectures it provides, if it is a Mach-o file, or NULL otherwise. */

/* ==================== Primitive Code Loading API ==================== */
/* This API abstracts the various different executable formats supported on */
/* various platforms.  It can load DYLD, CFM, or DLL shared libraries (on their */
/* appropriate platforms) and gives a uniform API for looking up functions. */

CF_EXPORT
CFURLRef CFBundleCopyExecutableURL(CFBundleRef bundle);

enum {
    kCFBundleExecutableArchitectureI386     = 0x00000007,
    kCFBundleExecutableArchitecturePPC      = 0x00000012,
    kCFBundleExecutableArchitectureX86_64   = 0x01000007,
    kCFBundleExecutableArchitecturePPC64    = 0x01000012
} CF_ENUM_AVAILABLE(10_5, 2_0);

CF_EXPORT
CFArrayRef CFBundleCopyExecutableArchitectures(CFBundleRef bundle) CF_AVAILABLE(10_5, 2_0);
    /* If the bundle's executable exists and is a Mach-o file, this function will return an array */
    /* of CFNumbers whose values are integers representing the architectures the file provides. */
    /* The values currently in use are those listed in the enum above, but others may be added */
    /* in the future.  If the executable is not a Mach-o file, this function returns NULL. */

CF_EXPORT
Boolean CFBundlePreflightExecutable(CFBundleRef bundle, CFErrorRef *error) CF_AVAILABLE(10_5, 2_0);
    /* This function will return true if the bundle is loaded, or if the bundle appears to be */
    /* loadable upon inspection.  This does not mean that the bundle is definitively loadable, */
    /* since it may fail to load due to link errors or other problems not readily detectable. */
    /* If this function detects problems, it will return false, and return a CFError by reference. */
    /* It is the responsibility of the caller to release the CFError. */

CF_EXPORT
Boolean CFBundleLoadExecutableAndReturnError(CFBundleRef bundle, CFErrorRef *error) CF_AVAILABLE(10_5, 2_0);
    /* If the bundle is already loaded, this function will return true.  Otherwise, it will attempt */
    /* to load the bundle, and it will return true if that attempt succeeds.  If the bundle fails */
    /* to load, this function will return false, and it will return a CFError by reference.  */
    /* It is the responsibility of the caller to release the CFError. */

CF_EXPORT
Boolean CFBundleLoadExecutable(CFBundleRef bundle);

CF_EXPORT
Boolean CFBundleIsExecutableLoaded(CFBundleRef bundle);

CF_EXPORT
void CFBundleUnloadExecutable(CFBundleRef bundle);

CF_EXPORT
void *CFBundleGetFunctionPointerForName(CFBundleRef bundle, CFStringRef functionName);

CF_EXPORT
void CFBundleGetFunctionPointersForNames(CFBundleRef bundle, CFArrayRef functionNames, void *ftbl[]);

CF_EXPORT
void *CFBundleGetDataPointerForName(CFBundleRef bundle, CFStringRef symbolName);

CF_EXPORT
void CFBundleGetDataPointersForNames(CFBundleRef bundle, CFArrayRef symbolNames, void *stbl[]);

CF_EXPORT
CFURLRef CFBundleCopyAuxiliaryExecutableURL(CFBundleRef bundle, CFStringRef executableName);
    /* This function can be used to find executables other than your main */
    /* executable.  This is useful, for instance, for applications that have */
    /* some command line tool that is packaged with and used by the application. */
    /* The tool can be packaged in the various platform executable directories */
    /* in the bundle and can be located with this function.  This allows an */
    /* app to ship versions of the tool for each platform as it does for the */
    /* main app executable. */

/* ==================== Getting a bundle's plugIn ==================== */

CF_EXPORT
CFPlugInRef CFBundleGetPlugIn(CFBundleRef bundle);

/* ==================== Resource Manager-Related API ==================== */

#if __LP64__
typedef int CFBundleRefNum;
#else
typedef SInt16 CFBundleRefNum;
#endif

CF_EXPORT
CFBundleRefNum CFBundleOpenBundleResourceMap(CFBundleRef bundle);
   /* This function opens the non-localized and the localized resource files */
   /* (if any) for the bundle, creates and makes current a single read-only */
   /* resource map combining both, and returns a reference number for it. */
   /* If it is called multiple times, it opens the files multiple times, */
   /* and returns distinct reference numbers.  */

CF_EXPORT
SInt32 CFBundleOpenBundleResourceFiles(CFBundleRef bundle, CFBundleRefNum *refNum, CFBundleRefNum *localizedRefNum);
   /* Similar to CFBundleOpenBundleResourceMap(), except that it creates two */
   /* separate resource maps and returns reference numbers for both. */

CF_EXPORT
void CFBundleCloseBundleResourceMap(CFBundleRef bundle, CFBundleRefNum refNum);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFBUNDLE__ */

// ==========  CoreFoundation.framework/Headers/CFBag.h
/*	CFBag.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBAG__)
#define __COREFOUNDATION_CFBAG__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef const void *	(*CFBagRetainCallBack)(CFAllocatorRef allocator, const void *value);
typedef void		(*CFBagReleaseCallBack)(CFAllocatorRef allocator, const void *value);
typedef CFStringRef	(*CFBagCopyDescriptionCallBack)(const void *value);
typedef Boolean		(*CFBagEqualCallBack)(const void *value1, const void *value2);
typedef CFHashCode	(*CFBagHashCallBack)(const void *value);
typedef struct {
    CFIndex				version;
    CFBagRetainCallBack			retain;
    CFBagReleaseCallBack		release;
    CFBagCopyDescriptionCallBack	copyDescription;
    CFBagEqualCallBack			equal;
    CFBagHashCallBack			hash;
} CFBagCallBacks;

CF_EXPORT
const CFBagCallBacks kCFTypeBagCallBacks;
CF_EXPORT
const CFBagCallBacks kCFCopyStringBagCallBacks;

typedef void (*CFBagApplierFunction)(const void *value, void *context);

typedef const struct CF_BRIDGED_TYPE(id) __CFBag * CFBagRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFBag * CFMutableBagRef;

CF_EXPORT
CFTypeID CFBagGetTypeID(void);

CF_EXPORT
CFBagRef CFBagCreate(CFAllocatorRef allocator, const void **values, CFIndex numValues, const CFBagCallBacks *callBacks);

CF_EXPORT
CFBagRef CFBagCreateCopy(CFAllocatorRef allocator, CFBagRef theBag);

CF_EXPORT
CFMutableBagRef CFBagCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFBagCallBacks *callBacks);

CF_EXPORT
CFMutableBagRef CFBagCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFBagRef theBag);

CF_EXPORT
CFIndex CFBagGetCount(CFBagRef theBag);

CF_EXPORT
CFIndex CFBagGetCountOfValue(CFBagRef theBag, const void *value);

CF_EXPORT
Boolean CFBagContainsValue(CFBagRef theBag, const void *value);

CF_EXPORT
const void *CFBagGetValue(CFBagRef theBag, const void *value);

CF_EXPORT
Boolean CFBagGetValueIfPresent(CFBagRef theBag, const void *candidate, const void **value);

CF_EXPORT
void CFBagGetValues(CFBagRef theBag, const void **values);

CF_EXPORT
void CFBagApplyFunction(CFBagRef theBag, CFBagApplierFunction applier, void *context);

CF_EXPORT
void CFBagAddValue(CFMutableBagRef theBag, const void *value);

CF_EXPORT
void CFBagReplaceValue(CFMutableBagRef theBag, const void *value);

CF_EXPORT
void CFBagSetValue(CFMutableBagRef theBag, const void *value);

CF_EXPORT
void CFBagRemoveValue(CFMutableBagRef theBag, const void *value);

CF_EXPORT
void CFBagRemoveAllValues(CFMutableBagRef theBag);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFBAG__ */

// ==========  CoreFoundation.framework/Headers/CFPreferences.h
/*	CFPreferences.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFPREFERENCES__)
#define __COREFOUNDATION_CFPREFERENCES__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

CF_EXPORT
const CFStringRef kCFPreferencesAnyApplication;
CF_EXPORT
const CFStringRef kCFPreferencesCurrentApplication;
CF_EXPORT
const CFStringRef kCFPreferencesAnyHost;
CF_EXPORT
const CFStringRef kCFPreferencesCurrentHost;
CF_EXPORT
const CFStringRef kCFPreferencesAnyUser;
CF_EXPORT
const CFStringRef kCFPreferencesCurrentUser;

/* NOTE: All CFPropertyListRef values returned from
         CFPreferences API should be assumed to be immutable.
*/

/*	The "App" functions search the various sources of defaults that
	apply to the given application, and should never be called with
	kCFPreferencesAnyApplication - only kCFPreferencesCurrentApplication
	or an application's ID (its bundle identifier).
*/

/* Searches the various sources of application defaults to find the
value for the given key. key must not be NULL.  If a value is found,
it returns it; otherwise returns NULL.  Caller must release the
returned value */
CF_EXPORT
CFPropertyListRef CFPreferencesCopyAppValue(CFStringRef key, CFStringRef applicationID);

/* Convenience to interpret a preferences value as a boolean directly.
Returns false if the key doesn't exist, or has an improper format; under
those conditions, keyExistsAndHasValidFormat (if non-NULL) is set to false */
CF_EXPORT
Boolean CFPreferencesGetAppBooleanValue(CFStringRef key, CFStringRef applicationID, Boolean *keyExistsAndHasValidFormat);

/* Convenience to interpret a preferences value as an integer directly.
Returns 0 if the key doesn't exist, or has an improper format; under
those conditions, keyExistsAndHasValidFormat (if non-NULL) is set to false */
CF_EXPORT
CFIndex CFPreferencesGetAppIntegerValue(CFStringRef key, CFStringRef applicationID, Boolean *keyExistsAndHasValidFormat);

/* Sets the given value for the given key in the "normal" place for
application preferences.  key must not be NULL.  If value is NULL,
key is removed instead. */
CF_EXPORT
void CFPreferencesSetAppValue(CFStringRef key, CFPropertyListRef value, CFStringRef applicationID);

/* Adds the preferences for the given suite to the app preferences for
   the specified application.  To write to the suite domain, use
   CFPreferencesSetValue(), below, using the suiteName in place
   of the appName */
CF_EXPORT
void CFPreferencesAddSuitePreferencesToApp(CFStringRef applicationID, CFStringRef suiteID);

CF_EXPORT
void CFPreferencesRemoveSuitePreferencesFromApp(CFStringRef applicationID, CFStringRef suiteID);

/* Writes all changes in all sources of application defaults.
Returns success or failure. */
CF_EXPORT
Boolean CFPreferencesAppSynchronize(CFStringRef applicationID);

/* The primitive get mechanism; all arguments must be non-NULL
(use the constants above for common values).  Only the exact
location specified by app-user-host is searched.  The returned
CFType must be released by the caller when it is finished with it. */
CF_EXPORT
CFPropertyListRef CFPreferencesCopyValue(CFStringRef key, CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

/* Convenience to fetch multiple keys at once.  Keys in 
keysToFetch that are not present in the returned dictionary
are not present in the domain.  If keysToFetch is NULL, all
keys are fetched. */
CF_EXPORT
CFDictionaryRef CFPreferencesCopyMultiple(CFArrayRef keysToFetch, CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

/* The primitive set function; all arguments except value must be
non-NULL.  If value is NULL, the given key is removed */
CF_EXPORT
void CFPreferencesSetValue(CFStringRef key, CFPropertyListRef value, CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

/* Convenience to set multiple values at once.  Behavior is undefined
if a key is in both keysToSet and keysToRemove */
CF_EXPORT
void CFPreferencesSetMultiple(CFDictionaryRef keysToSet, CFArrayRef keysToRemove, CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

CF_EXPORT
Boolean CFPreferencesSynchronize(CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

/* Constructs and returns the list of the name of all applications
which have preferences in the scope of the given user and host.
The returned value must be released by the caller; neither argument
may be NULL. */
CF_EXPORT
CFArrayRef CFPreferencesCopyApplicationList(CFStringRef userName, CFStringRef hostName) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0);

/* Constructs and returns the list of all keys set in the given
location.  The returned value must be released by the caller;
all arguments must be non-NULL */
CF_EXPORT
CFArrayRef CFPreferencesCopyKeyList(CFStringRef applicationID, CFStringRef userName, CFStringRef hostName);

#ifndef CF_OPEN_SOURCE

/* Function to determine whether or not a given key has been imposed on the
user - In cases where machines and/or users are under some kind of management,
callers should use this function to determine whether or not to disable UI elements
corresponding to those preference keys. */
CF_EXPORT
Boolean CFPreferencesAppValueIsForced(CFStringRef key, CFStringRef applicationID);

#endif

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFPREFERENCES__ */

// ==========  CoreFoundation.framework/Headers/CFAvailability.h
/*	CFAvailability.h
	Copyright (c) 2013-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFAVAILABILITY__)
#define __COREFOUNDATION_CFAVAILABILITY__ 1

#include <TargetConditionals.h>

#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32)
#include <Availability.h>

// Even if unused, these must remain here for compatibility, because projects rely on them being included.
#include <AvailabilityMacros.h>
#endif

#ifndef __has_feature
#define __has_feature(x) 0
#endif
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif
#ifndef __has_extension
#define __has_extension(x) 0
#endif

// The arguments to these availability macros is a version number, e.g. 10_6, 3_0 or 'NA'
// To use a deprecation message with the macro, add a string as the last argument.
#if __has_feature(attribute_availability_with_version_underscores) || (__has_feature(attribute_availability_with_message) && __clang__ && __clang_major__ >= 7)
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
// This section is for compilers targeting OS X which support attribute_availability_with_message

#define CF_AVAILABLE(_mac, _ios) __attribute__((availability(macosx,introduced=_mac)))
#define CF_AVAILABLE_MAC(_mac) __attribute__((availability(macosx,introduced=_mac)))
#define CF_AVAILABLE_IOS(_ios) __attribute__((availability(macosx,unavailable)))
#define CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) __attribute__((availability(macosx,introduced=_macIntro,deprecated=_macDep,message="" __VA_ARGS__)))
#define CF_DEPRECATED_MAC(_macIntro, _macDep, ...) __attribute__((availability(macosx,introduced=_macIntro,deprecated=_macDep,message="" __VA_ARGS__)))
#define CF_DEPRECATED_IOS(_iosIntro, _iosDep, ...) __attribute__((availability(macosx,unavailable)))

#elif (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
// This section is for compilers targeting iOS which support attribute_availability_with_message

#define CF_AVAILABLE(_mac, _ios) __attribute__((availability(ios,introduced=_ios)))
#define CF_AVAILABLE_MAC(_mac) __attribute__((availability(ios,unavailable)))
#define CF_AVAILABLE_IOS(_ios) __attribute__((availability(ios,introduced=_ios)))
#define CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) __attribute__((availability(ios,introduced=_iosIntro,deprecated=_iosDep,message="" __VA_ARGS__)))
#define CF_DEPRECATED_MAC(_macIntro, _macDep, ...) __attribute__((availability(ios,unavailable)))
#define CF_DEPRECATED_IOS(_iosIntro, _iosDep, ...) __attribute__((availability(ios,introduced=_iosIntro,deprecated=_iosDep,message="" __VA_ARGS__)))

#endif

#elif (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
// This section is for OS X or iOS, and compilers without support for attribute_availability_with_message. We fall back to Availability.h.

#ifndef __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_0
#define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_0 __AVAILABILITY_INTERNAL_DEPRECATED
#endif

#define CF_AVAILABLE(_mac, _ios) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_##_ios)
#define CF_AVAILABLE_MAC(_mac) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_NA)
#define CF_AVAILABLE_IOS(_ios) __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_##_ios)
#define CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)
#define CF_DEPRECATED_MAC(_macIntro, _macDep, ...) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_NA, __IPHONE_NA)
#define CF_DEPRECATED_IOS(_iosIntro, _iosDep, ...) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)

#endif // __has_feature(attribute_availability_with_message)

#ifndef CF_AVAILABLE
// This section is for platforms which do not support availability
#define CF_AVAILABLE(_mac, _ios)
#define CF_AVAILABLE_MAC(_mac)
#define CF_AVAILABLE_IOS(_ios)
#define CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...)
#define CF_DEPRECATED_MAC(_macIntro, _macDep, ...)
#define CF_DEPRECATED_IOS(_iosIntro, _iosDep, ...)
#endif

// Older versions of these macros; use iOS versions instead
#define CF_AVAILABLE_IPHONE(_ios) CF_AVAILABLE_IOS(_ios)
#define CF_DEPRECATED_IPHONE(_iosIntro, _iosDep) CF_DEPRECATED_IOS(_iosIntro, _iosDep)

// Enum availability macros
#if __has_feature(enumerator_attributes) && __has_attribute(availability)
#define CF_ENUM_AVAILABLE(_mac, _ios) CF_AVAILABLE(_mac, _ios)
#define CF_ENUM_AVAILABLE_MAC(_mac) CF_AVAILABLE_MAC(_mac)
#define CF_ENUM_AVAILABLE_IOS(_ios) CF_AVAILABLE_IOS(_ios)
#define CF_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
#define CF_ENUM_DEPRECATED_MAC(_macIntro, _macDep, ...) CF_DEPRECATED_MAC(_macIntro, _macDep, __VA_ARGS__)
#define CF_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep, ...) CF_DEPRECATED_IOS(_iosIntro, _iosDep, __VA_ARGS__)
#else
#define CF_ENUM_AVAILABLE(_mac, _ios)
#define CF_ENUM_AVAILABLE_MAC(_mac)
#define CF_ENUM_AVAILABLE_IOS(_ios)
#define CF_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...)
#define CF_ENUM_DEPRECATED_MAC(_macIntro, _macDep, ...)
#define CF_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep, ...)
#endif

// Enums and Options
#define __CF_ENUM_GET_MACRO(_1, _2, NAME, ...) NAME
#if (__cplusplus && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!__cplusplus && __has_feature(objc_fixed_enum))
#define __CF_NAMED_ENUM(_type, _name)     enum _name : _type _name; enum _name : _type
#define __CF_ANON_ENUM(_type)             enum : _type
#if (__cplusplus)
#define CF_OPTIONS(_type, _name) _type _name; enum : _type
#else
#define CF_OPTIONS(_type, _name) enum _name : _type _name; enum _name : _type
#endif
#else
#define __CF_NAMED_ENUM(_type, _name) _type _name; enum
#define __CF_ANON_ENUM(_type) enum
#define CF_OPTIONS(_type, _name) _type _name; enum
#endif

/* CF_ENUM supports the use of one or two arguments. The first argument is always the integer type used for the values of the enum. The second argument is an optional type name for the macro. When specifying a type name, you must precede the macro with 'typedef' like so:

typedef CF_ENUM(CFIndex, CFComparisonResult) {
    ...
};

If you do not specify a type name, do not use 'typdef', like so:

CF_ENUM(CFIndex) {
    ...
};
*/
#define CF_ENUM(...) __CF_ENUM_GET_MACRO(__VA_ARGS__, __CF_NAMED_ENUM, __CF_ANON_ENUM)(__VA_ARGS__)

// Extension availability macros
#define CF_EXTENSION_UNAVAILABLE(_msg)      __OS_EXTENSION_UNAVAILABLE(_msg)
#define CF_EXTENSION_UNAVAILABLE_MAC(_msg)  __OSX_EXTENSION_UNAVAILABLE(_msg)
#define CF_EXTENSION_UNAVAILABLE_IOS(_msg)  __IOS_EXTENSION_UNAVAILABLE(_msg)

// Swift availability macro
#if __has_feature(attribute_availability_swift)
#define CF_SWIFT_UNAVAILABLE(_msg) __attribute__((availability(swift, unavailable, message=_msg)))
#else
#define CF_SWIFT_UNAVAILABLE(_msg)
#endif

#endif // __COREFOUNDATION_CFAVAILABILITY__
// ==========  CoreFoundation.framework/Headers/CFNotificationCenter.h
/*	CFNotificationCenter.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNOTIFICATIONCENTER__)
#define __COREFOUNDATION_CFNOTIFICATIONCENTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFNotificationCenter * CFNotificationCenterRef;

typedef void (*CFNotificationCallback)(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo);

typedef CF_ENUM(CFIndex, CFNotificationSuspensionBehavior) {
    CFNotificationSuspensionBehaviorDrop = 1,
        // The server will not queue any notifications with this name and object while the process/app is in the background.
    CFNotificationSuspensionBehaviorCoalesce = 2,
        // The server will only queue the last notification of the specified name and object; earlier notifications are dropped. 
    CFNotificationSuspensionBehaviorHold = 3,
        // The server will hold all matching notifications until the queue has been filled (queue size determined by the server) at which point the server may flush queued notifications.
    CFNotificationSuspensionBehaviorDeliverImmediately = 4
        // The server will deliver notifications matching this registration whether or not the process is in the background.  When a notification with this suspension behavior is matched, it has the effect of first flushing any queued notifications.
};

CF_EXPORT CFTypeID CFNotificationCenterGetTypeID(void);

CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetLocalCenter(void);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDistributedCenter(void);
#endif

CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDarwinNotifyCenter(void);
// The Darwin Notify Center is based on the <notify.h> API.
// For this center, there are limitations in the API. There are no notification "objects",
// "userInfo" cannot be passed in the notification, and there are no suspension behaviors
// (always "deliver immediately"). Other limitations in the <notify.h> API as described in
// that header will also apply.
// - In the CFNotificationCallback, the 'object' and 'userInfo' parameters must be ignored.
// - CFNotificationCenterAddObserver(): the 'object' and 'suspensionBehavior' arguments are ignored.
// - CFNotificationCenterAddObserver(): the 'name' argument may not be NULL (for this center).
// - CFNotificationCenterRemoveObserver(): the 'object' argument is ignored.
// - CFNotificationCenterPostNotification(): the 'object', 'userInfo', and 'deliverImmediately' arguments are ignored.
// - CFNotificationCenterPostNotificationWithOptions(): the 'object', 'userInfo', and 'options' arguments are ignored.
// The Darwin Notify Center has no notion of per-user sessions, all notifications are system-wide.
// As with distributed notifications, the main thread's run loop must be running in one of the
// common modes (usually kCFRunLoopDefaultMode) for Darwin-style notifications to be delivered.
// NOTE: NULL or 0 should be passed for all ignored arguments to ensure future compatibility.


CF_EXPORT void CFNotificationCenterAddObserver(CFNotificationCenterRef center, const void *observer, CFNotificationCallback callBack, CFStringRef name, const void *object, CFNotificationSuspensionBehavior suspensionBehavior);

CF_EXPORT void CFNotificationCenterRemoveObserver(CFNotificationCenterRef center, const void *observer, CFStringRef name, const void *object);
CF_EXPORT void CFNotificationCenterRemoveEveryObserver(CFNotificationCenterRef center, const void *observer);

CF_EXPORT void CFNotificationCenterPostNotification(CFNotificationCenterRef center, CFStringRef name, const void *object, CFDictionaryRef userInfo, Boolean deliverImmediately);

CF_ENUM(CFOptionFlags) {
    kCFNotificationDeliverImmediately = (1UL << 0),
    kCFNotificationPostToAllSessions = (1UL << 1)
};

CF_EXPORT void CFNotificationCenterPostNotificationWithOptions(CFNotificationCenterRef center, CFStringRef name, const void *object, CFDictionaryRef userInfo, CFOptionFlags options);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFNOTIFICATIONCENTER__ */

// ==========  CoreFoundation.framework/Headers/CFArray.h
/*	CFArray.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

/*!
	@header CFArray
	CFArray implements an ordered, compact container of pointer-sized
	values. Values are accessed via integer keys (indices), from the
	range 0 to N-1, where N is the number of values in the array when
	an operation is performed. The array is said to be "compact" because
	deleted or inserted values do not leave a gap in the key space --
	the values with higher-numbered indices have their indices
	renumbered lower (or higher, in the case of insertion) so that the
	set of valid indices is always in the integer range [0, N-1]. Thus,
	the index to access a particular value in the array may change over
	time as other values are inserted into or deleted from the array.

	Arrays come in two flavors, immutable, which cannot have values
	added to them or removed from them after the array is created, and
	mutable, to which you can add values or from which remove values.
	Mutable arrays can have an unlimited number of values (or rather,
	limited only by constraints external to CFArray, like the amount
	of available memory).

	As with all CoreFoundation collection types, arrays maintain hard
	references on the values you put in them, but the retaining and
	releasing functions are user-defined callbacks that can actually do
	whatever the user wants (for example, nothing).

	Computational Complexity
	The access time for a value in the array is guaranteed to be at
	worst O(lg N) for any implementation, current and future, but will
	often be O(1) (constant time). Linear search operations similarly
	have a worst case complexity of O(N*lg N), though typically the
	bounds will be tighter, and so on. Insertion or deletion operations
	will typically be linear in the number of values in the array, but
	may be O(N*lg N) clearly in the worst case in some implementations.
	There are no favored positions within the array for performance;
	that is, it is not necessarily faster to access values with low
	indices, or to insert or delete values with high indices, or
	whatever.
*/

#if !defined(__COREFOUNDATION_CFARRAY__)
#define __COREFOUNDATION_CFARRAY__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
	@typedef CFArrayCallBacks
	Structure containing the callbacks of a CFArray.
	@field version The version number of the structure type being passed
		in as a parameter to the CFArray creation functions. This
		structure is version 0.
	@field retain The callback used to add a retain for the array on
		values as they are put into the array. This callback returns
		the value to store in the array, which is usually the value
		parameter passed to this callback, but may be a different
		value if a different value should be stored in the array.
		The array's allocator is passed as the first argument.
	@field release The callback used to remove a retain previously added
		for the array from values as they are removed from the
		array. The array's allocator is passed as the first
		argument.
	@field copyDescription The callback used to create a descriptive
		string representation of each value in the array. This is
		used by the CFCopyDescription() function.
	@field equal The callback used to compare values in the array for
		equality for some operations.
*/
typedef const void *	(*CFArrayRetainCallBack)(CFAllocatorRef allocator, const void *value);
typedef void		(*CFArrayReleaseCallBack)(CFAllocatorRef allocator, const void *value);
typedef CFStringRef	(*CFArrayCopyDescriptionCallBack)(const void *value);
typedef Boolean		(*CFArrayEqualCallBack)(const void *value1, const void *value2);
typedef struct {
    CFIndex				version;
    CFArrayRetainCallBack		retain;
    CFArrayReleaseCallBack		release;
    CFArrayCopyDescriptionCallBack	copyDescription;
    CFArrayEqualCallBack		equal;
} CFArrayCallBacks;

/*!
	@constant kCFTypeArrayCallBacks
	Predefined CFArrayCallBacks structure containing a set of callbacks
	appropriate for use when the values in a CFArray are all CFTypes.
*/
CF_EXPORT
const CFArrayCallBacks kCFTypeArrayCallBacks;

/*!
	@typedef CFArrayApplierFunction
	Type of the callback function used by the apply functions of
		CFArrays.
	@param value The current value from the array.
	@param context The user-defined context parameter given to the apply
		function.
*/
typedef void (*CFArrayApplierFunction)(const void *value, void *context);

/*!
	@typedef CFArrayRef
	This is the type of a reference to immutable CFArrays.
*/
typedef const struct CF_BRIDGED_TYPE(NSArray) __CFArray * CFArrayRef;

/*!
	@typedef CFMutableArrayRef
	This is the type of a reference to mutable CFArrays.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableArray) __CFArray * CFMutableArrayRef;

/*!
	@function CFArrayGetTypeID
	Returns the type identifier of all CFArray instances.
*/
CF_EXPORT
CFTypeID CFArrayGetTypeID(void);

/*!
	@function CFArrayCreate
	Creates a new immutable array with the given values.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param values A C array of the pointer-sized values to be in the
		array. The values in the array are ordered in the same order
		in which they appear in this C array. This parameter may be
		NULL if the numValues parameter is 0. This C array is not
		changed or freed by this function. If this parameter is not
		a valid pointer to a C array of at least numValues pointers,
		the behavior is undefined.
	@param numValues The number of values to copy from the values C
		array into the CFArray. This number will be the count of the
		array.
		If this parameter is negative, or greater than the number of
		values actually in the value's C array, the behavior is
		undefined.
	@param callBacks A pointer to a CFArrayCallBacks structure
		initialized with the callbacks for the array to use on each
		value in the array. The retain callback will be used within
		this function, for example, to retain all of the new values
		from the values C array. A copy of the contents of the
		callbacks structure is made, so that a pointer to a
		structure on the stack can be passed in, or can be reused
		for multiple array creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFArray, the behavior is undefined. The retain field may be
		NULL, in which case the CFArray will do nothing to add a
		retain to the contained values for the array. The release
		field may be NULL, in which case the CFArray will do nothing
		to remove the array's retain (if any) on the values when the
		array is destroyed. If the copyDescription field is NULL,
		the array will create a simple description for the value. If
		the equal field is NULL, the array will use pointer equality
		to test for equality of values. This callbacks parameter
		itself may be NULL, which is treated as if a valid structure
		of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a  CFArrayCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		array is not one understood by one of the callback functions
		the behavior when that callback function is used is
		undefined.
	@result A reference to the new immutable CFArray.
*/
CF_EXPORT
CFArrayRef CFArrayCreate(CFAllocatorRef allocator, const void **values, CFIndex numValues, const CFArrayCallBacks *callBacks);

/*!
	@function CFArrayCreateCopy
	Creates a new immutable array with the values from the given array.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theArray The array which is to be copied. The values from the
		array are copied as pointers into the new array (that is,
		the values themselves are copied, not that which the values
		point to, if anything). However, the values are also
		retained by the new array. The count of the new array will
		be the same as the given array. The new array uses the same
		callbacks as the array to be copied. If this parameter is
		not a valid CFArray, the behavior is undefined.
	@result A reference to the new immutable CFArray.
*/
CF_EXPORT
CFArrayRef CFArrayCreateCopy(CFAllocatorRef allocator, CFArrayRef theArray);

/*!
	@function CFArrayCreateMutable
	Creates a new empty mutable array.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param capacity A hint about the number of values that will be held
		by the CFArray. Pass 0 for no hint. The implementation may
		ignore this hint, or may use it to optimize various
		operations. An array's actual capacity is only limited by
		address space and available memory constraints). If this
		parameter is negative, the behavior is undefined.
	@param callBacks A pointer to a CFArrayCallBacks structure
		initialized with the callbacks for the array to use on each
		value in the array. A copy of the contents of the
		callbacks structure is made, so that a pointer to a
		structure on the stack can be passed in, or can be reused
		for multiple array creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFArray, the behavior is undefined. The retain field may be
		NULL, in which case the CFArray will do nothing to add a
		retain to the contained values for the array. The release
		field may be NULL, in which case the CFArray will do nothing
		to remove the array's retain (if any) on the values when the
		array is destroyed. If the copyDescription field is NULL,
		the array will create a simple description for the value. If
		the equal field is NULL, the array will use pointer equality
		to test for equality of values. This callbacks parameter
		itself may be NULL, which is treated as if a valid structure
		of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a  CFArrayCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		array is not one understood by one of the callback functions
		the behavior when that callback function is used is
		undefined.
	@result A reference to the new mutable CFArray.
*/
CF_EXPORT
CFMutableArrayRef CFArrayCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFArrayCallBacks *callBacks);

/*!
	@function CFArrayCreateMutableCopy
	Creates a new mutable array with the values from the given array.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFArray. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. An array's actual capacity is only limited by 
                address space and available memory constraints).
		This parameter must be greater than or equal
		to the count of the array which is to be copied, or the
		behavior is undefined. If this parameter is negative, the
		behavior is undefined.
	@param theArray The array which is to be copied. The values from the
		array are copied as pointers into the new array (that is,
		the values themselves are copied, not that which the values
		point to, if anything). However, the values are also
		retained by the new array. The count of the new array will
		be the same as the given array. The new array uses the same
		callbacks as the array to be copied. If this parameter is
		not a valid CFArray, the behavior is undefined.
	@result A reference to the new mutable CFArray.
*/
CF_EXPORT
CFMutableArrayRef CFArrayCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFArrayRef theArray);

/*!
	@function CFArrayGetCount
	Returns the number of values currently in the array.
	@param theArray The array to be queried. If this parameter is not a valid
		CFArray, the behavior is undefined.
	@result The number of values in the array.
*/
CF_EXPORT
CFIndex CFArrayGetCount(CFArrayRef theArray);

/*!
	@function CFArrayGetCountOfValue
	Counts the number of times the given value occurs in the array.
	@param theArray The array to be searched. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param range The range within the array to search. If the range
		location or end point (defined by the location plus length
		minus 1) is outside the index space of the array (0 to
		N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
	@param value The value for which to find matches in the array. The
		equal() callback provided when the array was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the array, are not understood by the equal() callback,
		the behavior is undefined.
	@result The number of times the given value occurs in the array,
		within the specified range.
*/
CF_EXPORT
CFIndex CFArrayGetCountOfValue(CFArrayRef theArray, CFRange range, const void *value);

/*!
	@function CFArrayContainsValue
	Reports whether or not the value is in the array.
	@param theArray The array to be searched. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param range The range within the array to search. If the range
		location or end point (defined by the location plus length
		minus 1) is outside the index space of the array (0 to
		N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
	@param value The value for which to find matches in the array. The
		equal() callback provided when the array was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the array, are not understood by the equal() callback,
		the behavior is undefined.
	@result true, if the value is in the specified range of the array,
		otherwise false.
*/
CF_EXPORT
Boolean CFArrayContainsValue(CFArrayRef theArray, CFRange range, const void *value);

/*!
	@function CFArrayGetValueAtIndex
	Retrieves the value at the given index.
	@param theArray The array to be queried. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param idx The index of the value to retrieve. If the index is
		outside the index space of the array (0 to N-1 inclusive,
		where N is the count of the array), the behavior is
		undefined.
	@result The value with the given index in the array.
*/
CF_EXPORT
const void *CFArrayGetValueAtIndex(CFArrayRef theArray, CFIndex idx);

/*!
	@function CFArrayGetValues
	Fills the buffer with values from the array.
	@param theArray The array to be queried. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param range The range of values within the array to retrieve. If
		the range location or end point (defined by the location
		plus length minus 1) is outside the index space of the
		array (0 to N-1 inclusive, where N is the count of the
		array), the behavior is undefined. If the range length is
		negative, the behavior is undefined. The range may be empty
		(length 0), in which case no values are put into the buffer.
	@param values A C array of pointer-sized values to be filled with
		values from the array. The values in the C array are ordered
		in the same order in which they appear in the array. If this
		parameter is not a valid pointer to a C array of at least
		range.length pointers, the behavior is undefined.
*/
CF_EXPORT
void CFArrayGetValues(CFArrayRef theArray, CFRange range, const void **values);

/*!
	@function CFArrayApplyFunction
	Calls a function once for each value in the array.
	@param theArray The array to be operated upon. If this parameter is not
		a valid CFArray, the behavior is undefined.
	@param range The range of values within the array to which to apply
		the function. If the range location or end point (defined by
		the location plus length minus 1) is outside the index
		space of the array (0 to N-1 inclusive, where N is the count
		of the array), the behavior is undefined. If the range
		length is negative, the behavior is undefined. The range may
		be empty (length 0).
	@param applier The callback function to call once for each value in
		the given range in the array. If this parameter is not a
		pointer to a function of the correct prototype, the behavior
		is undefined. If there are values in the range which the
		applier function does not expect or cannot properly apply
		to, the behavior is undefined. 
	@param context A pointer-sized user-defined value, which is passed
		as the second parameter to the applier function, but is
		otherwise unused by this function. If the context is not
		what is expected by the applier function, the behavior is
		undefined.
*/
CF_EXPORT
void CFArrayApplyFunction(CFArrayRef theArray, CFRange range, CFArrayApplierFunction applier, void *context);

/*!
	@function CFArrayGetFirstIndexOfValue
	Searches the array for the value.
	@param theArray The array to be searched. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param range The range within the array to search. If the range
		location or end point (defined by the location plus length
		minus 1) is outside the index space of the array (0 to
		N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
		The search progresses from the smallest index defined by
		the range to the largest.
	@param value The value for which to find a match in the array. The
		equal() callback provided when the array was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the array, are not understood by the equal() callback,
		the behavior is undefined.
	@result The lowest index of the matching values in the range, or
		kCFNotFound if no value in the range matched.
*/
CF_EXPORT
CFIndex CFArrayGetFirstIndexOfValue(CFArrayRef theArray, CFRange range, const void *value);

/*!
	@function CFArrayGetLastIndexOfValue
	Searches the array for the value.
	@param theArray The array to be searched. If this parameter is not a
		valid CFArray, the behavior is undefined.
	@param range The range within the array to search. If the range
		location or end point (defined by the location plus length
		minus 1) is outside the index space of the array (0 to
		N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
		The search progresses from the largest index defined by the
		range to the smallest.
	@param value The value for which to find a match in the array. The
		equal() callback provided when the array was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the array, are not understood by the equal() callback,
		the behavior is undefined.
	@result The highest index of the matching values in the range, or
		kCFNotFound if no value in the range matched.
*/
CF_EXPORT
CFIndex CFArrayGetLastIndexOfValue(CFArrayRef theArray, CFRange range, const void *value);

/*!
	@function CFArrayBSearchValues
	Searches the array for the value using a binary search algorithm.
	@param theArray The array to be searched. If this parameter is not a
		valid CFArray, the behavior is undefined. If the array is
		not sorted from least to greatest according to the
		comparator function, the behavior is undefined.
	@param range The range within the array to search. If the range
		location or end point (defined by the location plus length
		minus 1) is outside the index space of the array (0 to
		N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
	@param value The value for which to find a match in the array. If
		value, or any of the values in the array, are not understood
		by the comparator callback, the behavior is undefined.
	@param comparator The function with the comparator function type
		signature which is used in the binary search operation to
		compare values in the array with the given value. If this
		parameter is not a pointer to a function of the correct
		prototype, the behavior is undefined. If there are values
		in the range which the comparator function does not expect
		or cannot properly compare, the behavior is undefined.
	@param context A pointer-sized user-defined value, which is passed
		as the third parameter to the comparator function, but is
		otherwise unused by this function. If the context is not
		what is expected by the comparator function, the behavior is
		undefined.
	@result The return value is either 1) the index of a value that
		matched, if the target value matches one or more in the
		range, 2) greater than or equal to the end point of the
		range, if the value is greater than all the values in the
		range, or 3) the index of the value greater than the target
		value, if the value lies between two of (or less than all
		of) the values in the range.
*/
CF_EXPORT
CFIndex CFArrayBSearchValues(CFArrayRef theArray, CFRange range, const void *value, CFComparatorFunction comparator, void *context);

/*!
	@function CFArrayAppendValue
	Adds the value to the array giving it a new largest index.
	@param theArray The array to which the value is to be added. If this
		parameter is not a valid mutable CFArray, the behavior is
		undefined.
	@param value The value to add to the array. The value is retained by
		the array using the retain callback provided when the array
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The value is
		assigned to the index one larger than the previous largest
		index, and the count of the array is increased by one.
*/
CF_EXPORT
void CFArrayAppendValue(CFMutableArrayRef theArray, const void *value);

/*!
	@function CFArrayInsertValueAtIndex
	Adds the value to the array, giving it the given index.
	@param theArray The array to which the value is to be added. If this
		parameter is not a valid mutable CFArray, the behavior is
		undefined.
	@param idx The index to which to add the new value. If the index is
		outside the index space of the array (0 to N inclusive,
		where N is the count of the array before the operation), the
		behavior is undefined. If the index is the same as N, this
		function has the same effect as CFArrayAppendValue().
	@param value The value to add to the array. The value is retained by
		the array using the retain callback provided when the array
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The value is
		assigned to the given index, and all values with equal and
		larger indices have their indexes increased by one.
*/
CF_EXPORT
void CFArrayInsertValueAtIndex(CFMutableArrayRef theArray, CFIndex idx, const void *value);

/*!
	@function CFArraySetValueAtIndex
	Changes the value with the given index in the array.
	@param theArray The array in which the value is to be changed. If this
		parameter is not a valid mutable CFArray, the behavior is
		undefined.
	@param idx The index to which to set the new value. If the index is
		outside the index space of the array (0 to N inclusive,
		where N is the count of the array before the operation), the
		behavior is undefined. If the index is the same as N, this
		function has the same effect as CFArrayAppendValue().
	@param value The value to set in the array. The value is retained by
		the array using the retain callback provided when the array
		was created, and the previous value with that index is
		released. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The indices of
		other values is not affected.
*/
CF_EXPORT
void CFArraySetValueAtIndex(CFMutableArrayRef theArray, CFIndex idx, const void *value);

/*!
	@function CFArrayRemoveValueAtIndex
	Removes the value with the given index from the array.
	@param theArray The array from which the value is to be removed. If
		this parameter is not a valid mutable CFArray, the behavior
		is undefined.
	@param idx The index from which to remove the value. If the index is
		outside the index space of the array (0 to N-1 inclusive,
		where N is the count of the array before the operation), the
		behavior is undefined.
*/
CF_EXPORT
void CFArrayRemoveValueAtIndex(CFMutableArrayRef theArray, CFIndex idx);

/*!
	@function CFArrayRemoveAllValues
	Removes all the values from the array, making it empty.
	@param theArray The array from which all of the values are to be
		removed. If this parameter is not a valid mutable CFArray,
		the behavior is undefined.
*/
CF_EXPORT
void CFArrayRemoveAllValues(CFMutableArrayRef theArray);

/*!
	@function CFArrayReplaceValues
	Replaces a range of values in the array.
	@param theArray The array from which all of the values are to be
		removed. If this parameter is not a valid mutable CFArray,
		the behavior is undefined.
	@param range The range of values within the array to replace. If the
		range location or end point (defined by the location plus
		length minus 1) is outside the index space of the array (0
		to N inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0),
		in which case the new values are merely inserted at the
		range location.
	@param newValues A C array of the pointer-sized values to be placed
		into the array. The new values in the array are ordered in
		the same order in which they appear in this C array. This
		parameter may be NULL if the newCount parameter is 0. This
		C array is not changed or freed by this function. If this
		parameter is not a valid pointer to a C array of at least
		newCount pointers, the behavior is undefined.
	@param newCount The number of values to copy from the values C
		array into the CFArray. If this parameter is different than
		the range length, the excess newCount values will be
		inserted after the range, or the excess range values will be
		deleted. This parameter may be 0, in which case no new
		values are replaced into the array and the values in the
		range are simply removed. If this parameter is negative, or
		greater than the number of values actually in the newValues
		C array, the behavior is undefined.
*/
CF_EXPORT
void CFArrayReplaceValues(CFMutableArrayRef theArray, CFRange range, const void **newValues, CFIndex newCount);

/*!
	@function CFArrayExchangeValuesAtIndices
	Exchanges the values at two indices of the array.
	@param theArray The array of which the values are to be swapped. If
		this parameter is not a valid mutable CFArray, the behavior
		is undefined.
	@param idx1 The first index whose values should be swapped. If the
		index is outside the index space of the array (0 to N-1
		inclusive, where N is the count of the array before the
		operation), the behavior is undefined.
	@param idx2 The second index whose values should be swapped. If the
		index is outside the index space of the array (0 to N-1
		inclusive, where N is the count of the array before the
		operation), the behavior is undefined.
*/
CF_EXPORT
void CFArrayExchangeValuesAtIndices(CFMutableArrayRef theArray, CFIndex idx1, CFIndex idx2);

/*!
	@function CFArraySortValues
	Sorts the values in the array using the given comparison function.
	@param theArray The array whose values are to be sorted. If this
		parameter is not a valid mutable CFArray, the behavior is
		undefined.
	@param range The range of values within the array to sort. If the
		range location or end point (defined by the location plus
		length minus 1) is outside the index space of the array (0
		to N-1 inclusive, where N is the count of the array), the
		behavior is undefined. If the range length is negative, the
		behavior is undefined. The range may be empty (length 0).
	@param comparator The function with the comparator function type
		signature which is used in the sort operation to compare
		values in the array with the given value. If this parameter
		is not a pointer to a function of the correct prototype, the
		the behavior is undefined. If there are values in the array
		which the comparator function does not expect or cannot
		properly compare, the behavior is undefined. The values in
		the range are sorted from least to greatest according to
		this function.
	@param context A pointer-sized user-defined value, which is passed
		as the third parameter to the comparator function, but is
		otherwise unused by this function. If the context is not
		what is expected by the comparator function, the behavior is
		undefined.
*/
CF_EXPORT
void CFArraySortValues(CFMutableArrayRef theArray, CFRange range, CFComparatorFunction comparator, void *context);

/*!
	@function CFArrayAppendArray
	Adds the values from an array to another array.
	@param theArray The array to which values from the otherArray are to
		be added. If this parameter is not a valid mutable CFArray,
		the behavior is undefined.
	@param otherArray The array providing the values to be added to the
		array. If this parameter is not a valid CFArray, the
		behavior is undefined.
	@param otherRange The range within the otherArray from which to add
		the values to the array. If the range location or end point
		(defined by the location plus length minus 1) is outside
		the index space of the otherArray (0 to N-1 inclusive, where
		N is the count of the otherArray), the behavior is
		undefined. The new values are retained by the array using
		the retain callback provided when the array was created. If
		the values are not of the sort expected by the retain
		callback, the behavior is undefined. The values are assigned
		to the indices one larger than the previous largest index
		in the array, and beyond, and the count of the array is
		increased by range.length. The values are assigned new
		indices in the array from smallest to largest index in the
		order in which they appear in the otherArray.
*/
CF_EXPORT
void CFArrayAppendArray(CFMutableArrayRef theArray, CFArrayRef otherArray, CFRange otherRange);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFARRAY__ */

// ==========  CoreFoundation.framework/Headers/CFStream.h
/*	CFStream.h
	Copyright (c) 2000-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFSTREAM__)
#define __COREFOUNDATION_CFSTREAM__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFSocket.h>
#include <CoreFoundation/CFError.h>
#include <dispatch/dispatch.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef CF_ENUM(CFIndex, CFStreamStatus) {
    kCFStreamStatusNotOpen = 0,
    kCFStreamStatusOpening,  /* open is in-progress */
    kCFStreamStatusOpen,
    kCFStreamStatusReading,
    kCFStreamStatusWriting,
    kCFStreamStatusAtEnd,    /* no further bytes can be read/written */
    kCFStreamStatusClosed,
    kCFStreamStatusError
};

typedef CF_OPTIONS(CFOptionFlags, CFStreamEventType) {
    kCFStreamEventNone = 0,
    kCFStreamEventOpenCompleted = 1,
    kCFStreamEventHasBytesAvailable = 2,
    kCFStreamEventCanAcceptBytes = 4, 
    kCFStreamEventErrorOccurred = 8,
    kCFStreamEventEndEncountered = 16
};

typedef struct {
    CFIndex version;
    void *info;
    void *(*retain)(void *info);
    void (*release)(void *info);
    CFStringRef (*copyDescription)(void *info);
} CFStreamClientContext;

typedef struct CF_BRIDGED_MUTABLE_TYPE(NSInputStream) __CFReadStream * CFReadStreamRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSOutputStream) __CFWriteStream * CFWriteStreamRef;

typedef void (*CFReadStreamClientCallBack)(CFReadStreamRef stream, CFStreamEventType type, void *clientCallBackInfo);
typedef void (*CFWriteStreamClientCallBack)(CFWriteStreamRef stream, CFStreamEventType type, void *clientCallBackInfo);

CF_EXPORT
CFTypeID CFReadStreamGetTypeID(void);
CF_EXPORT
CFTypeID CFWriteStreamGetTypeID(void);

/* Memory streams */

/* Value will be a CFData containing all bytes thusfar written; used to recover the data written to a memory write stream. */
CF_EXPORT
const CFStringRef kCFStreamPropertyDataWritten;

/* Pass kCFAllocatorNull for bytesDeallocator to prevent CFReadStream from deallocating bytes; otherwise, CFReadStream will deallocate bytes when the stream is destroyed */
CF_EXPORT
CFReadStreamRef CFReadStreamCreateWithBytesNoCopy(CFAllocatorRef alloc, const UInt8 *bytes, CFIndex length, CFAllocatorRef bytesDeallocator);

/* The stream writes into the buffer given; when bufferCapacity is exhausted, the stream is exhausted (status becomes kCFStreamStatusAtEnd) */
CF_EXPORT
CFWriteStreamRef CFWriteStreamCreateWithBuffer(CFAllocatorRef alloc, UInt8 *buffer, CFIndex bufferCapacity);

/* New buffers are allocated from bufferAllocator as bytes are written to the stream.  At any point, you can recover the bytes thusfar written by asking for the property kCFStreamPropertyDataWritten, above */
CF_EXPORT
CFWriteStreamRef CFWriteStreamCreateWithAllocatedBuffers(CFAllocatorRef alloc, CFAllocatorRef bufferAllocator);

/* File streams */
CF_EXPORT
CFReadStreamRef CFReadStreamCreateWithFile(CFAllocatorRef alloc, CFURLRef fileURL);
CF_EXPORT
CFWriteStreamRef CFWriteStreamCreateWithFile(CFAllocatorRef alloc, CFURLRef fileURL);
CF_IMPLICIT_BRIDGING_DISABLED
CF_EXPORT
void CFStreamCreateBoundPair(CFAllocatorRef alloc, CFReadStreamRef *readStream, CFWriteStreamRef *writeStream, CFIndex transferBufferSize);
CF_IMPLICIT_BRIDGING_ENABLED

/* Property for file write streams; value should be a CFBoolean.  Set to TRUE to append to a file, rather than to replace its contents */
CF_EXPORT
const CFStringRef kCFStreamPropertyAppendToFile;

CF_EXPORT
const CFStringRef kCFStreamPropertyFileCurrentOffset;   // Value is a CFNumber


/* Socket stream properties */

/* Value will be a CFData containing the native handle */
CF_EXPORT
const CFStringRef kCFStreamPropertySocketNativeHandle;

/* Value will be a CFString, or NULL if unknown */
CF_EXPORT
const CFStringRef kCFStreamPropertySocketRemoteHostName;

/* Value will be a CFNumber, or NULL if unknown */
CF_EXPORT
const CFStringRef kCFStreamPropertySocketRemotePortNumber;

CF_IMPLICIT_BRIDGING_DISABLED
/* Socket streams; the returned streams are paired such that they use the same socket; pass NULL if you want only the read stream or the write stream */
CF_EXPORT
void CFStreamCreatePairWithSocket(CFAllocatorRef alloc, CFSocketNativeHandle sock, CFReadStreamRef *readStream, CFWriteStreamRef *writeStream);
CF_EXPORT
void CFStreamCreatePairWithSocketToHost(CFAllocatorRef alloc, CFStringRef host, UInt32 port, CFReadStreamRef *readStream, CFWriteStreamRef *writeStream);
CF_EXPORT
void CFStreamCreatePairWithPeerSocketSignature(CFAllocatorRef alloc, const CFSocketSignature *signature, CFReadStreamRef *readStream, CFWriteStreamRef *writeStream);
CF_IMPLICIT_BRIDGING_ENABLED


/* Returns the current state of the stream */
CF_EXPORT
CFStreamStatus CFReadStreamGetStatus(CFReadStreamRef stream);
CF_EXPORT
CFStreamStatus CFWriteStreamGetStatus(CFWriteStreamRef stream);

/* Returns NULL if no error has occurred; otherwise returns the error. */
CF_EXPORT
CFErrorRef CFReadStreamCopyError(CFReadStreamRef stream) CF_AVAILABLE(10_5, 2_0);
CF_EXPORT
CFErrorRef CFWriteStreamCopyError(CFWriteStreamRef stream) CF_AVAILABLE(10_5, 2_0);

/* Returns success/failure.  Opening a stream causes it to reserve all the system
   resources it requires.  If the stream can open non-blocking, this will always 
   return TRUE; listen to the run loop source to find out when the open completes
   and whether it was successful, or poll using CFRead/WriteStreamGetStatus(), waiting 
   for a status of kCFStreamStatusOpen or kCFStreamStatusError.  */
CF_EXPORT
Boolean CFReadStreamOpen(CFReadStreamRef stream);
CF_EXPORT
Boolean CFWriteStreamOpen(CFWriteStreamRef stream);

/* Terminates the flow of bytes; releases any system resources required by the 
   stream.  The stream may not fail to close.  You may call CFStreamClose() to 
   effectively abort a stream. */
CF_EXPORT
void CFReadStreamClose(CFReadStreamRef stream);
CF_EXPORT
void CFWriteStreamClose(CFWriteStreamRef stream);

/* Whether there is data currently available for reading; returns TRUE if it's 
   impossible to tell without trying */
CF_EXPORT
Boolean CFReadStreamHasBytesAvailable(CFReadStreamRef stream);

/* Returns the number of bytes read, or -1 if an error occurs preventing any 
   bytes from being read, or 0 if the stream's end was encountered.  
   It is an error to try and read from a stream that hasn't been opened first.  
   This call will block until at least one byte is available; it will NOT block
   until the entire buffer can be filled.  To avoid blocking, either poll using
   CFReadStreamHasBytesAvailable() or use the run loop and listen for the 
   kCFStreamCanRead event for notification of data available. */
CF_EXPORT
CFIndex CFReadStreamRead(CFReadStreamRef stream, UInt8 *buffer, CFIndex bufferLength);

/* Returns a pointer to an internal buffer if possible (setting *numBytesRead
   to the length of the returned buffer), otherwise returns NULL; guaranteed
   to return in O(1).  Bytes returned in the buffer are considered read from
   the stream; if maxBytesToRead is greater than 0, not more than maxBytesToRead
   will be returned.  If maxBytesToRead is less than or equal to zero, as many bytes
   as are readily available will be returned.  The returned buffer is good only
   until the next stream operation called on the stream.  Caller should neither
   change the contents of the returned buffer nor attempt to deallocate the buffer;
   it is still owned by the stream. */
CF_EXPORT
const UInt8 *CFReadStreamGetBuffer(CFReadStreamRef stream, CFIndex maxBytesToRead, CFIndex *numBytesRead);

/* Whether the stream can currently be written to without blocking;
   returns TRUE if it's impossible to tell without trying */
CF_EXPORT
Boolean CFWriteStreamCanAcceptBytes(CFWriteStreamRef stream);

/* Returns the number of bytes successfully written, -1 if an error has
   occurred, or 0 if the stream has been filled to capacity (for fixed-length
   streams).  If the stream is not full, this call will block until at least
   one byte is written.  To avoid blocking, either poll via CFWriteStreamCanAcceptBytes
   or use the run loop and listen for the kCFStreamCanWrite event. */
CF_EXPORT
CFIndex CFWriteStreamWrite(CFWriteStreamRef stream, const UInt8 *buffer, CFIndex bufferLength);

/* Particular streams can name properties and assign meanings to them; you
   access these properties through the following calls.  A property is any interesting
   information about the stream other than the data being transmitted itself.
   Examples include the headers from an HTTP transmission, or the expected 
   number of bytes, or permission information, etc.  Properties that can be set
   configure the behavior of the stream, and may only be settable at particular times
   (like before the stream has been opened).  See the documentation for particular 
   properties to determine their get- and set-ability. */
CF_EXPORT
CFTypeRef CFReadStreamCopyProperty(CFReadStreamRef stream, CFStringRef propertyName);
CF_EXPORT
CFTypeRef CFWriteStreamCopyProperty(CFWriteStreamRef stream, CFStringRef propertyName);

/* Returns TRUE if the stream recognizes and accepts the given property-value pair; 
   FALSE otherwise. */
CF_EXPORT
Boolean CFReadStreamSetProperty(CFReadStreamRef stream, CFStringRef propertyName, CFTypeRef propertyValue);
CF_EXPORT
Boolean CFWriteStreamSetProperty(CFWriteStreamRef stream, CFStringRef propertyName, CFTypeRef propertyValue);

/* Asynchronous processing - If you wish to neither poll nor block, you may register 
   a client to hear about interesting events that occur on a stream.  Only one client
   per stream is allowed; registering a new client replaces the previous one.
 
   Once you have set a client, the stream must be scheduled to provide the context in
   which the client will be called.  Streams may be scheduled on a single dispatch queue
   or on one or more run loops.  If scheduled on a run loop, it is the caller's responsibility
   to ensure that at least one of the scheduled run loops is being run.

   NOTE: Unlike other CoreFoundation APIs, pasing a NULL clientContext here will remove
   the client.  If you do not care about the client context (i.e. your only concern
   is that your callback be called), you should pass in a valid context where every
   entry is 0 or NULL.

*/

CF_EXPORT
Boolean CFReadStreamSetClient(CFReadStreamRef stream, CFOptionFlags streamEvents, CFReadStreamClientCallBack clientCB, CFStreamClientContext *clientContext);
CF_EXPORT
Boolean CFWriteStreamSetClient(CFWriteStreamRef stream, CFOptionFlags streamEvents, CFWriteStreamClientCallBack clientCB, CFStreamClientContext *clientContext);

CF_EXPORT
void CFReadStreamScheduleWithRunLoop(CFReadStreamRef stream, CFRunLoopRef runLoop, CFStringRef runLoopMode);
CF_EXPORT
void CFWriteStreamScheduleWithRunLoop(CFWriteStreamRef stream, CFRunLoopRef runLoop, CFStringRef runLoopMode);

CF_EXPORT
void CFReadStreamUnscheduleFromRunLoop(CFReadStreamRef stream, CFRunLoopRef runLoop, CFStringRef runLoopMode);
CF_EXPORT
void CFWriteStreamUnscheduleFromRunLoop(CFWriteStreamRef stream, CFRunLoopRef runLoop, CFStringRef runLoopMode);

/*
 * Specify the dispatch queue upon which the client callbacks will be invoked.
 * Passing NULL for the queue will prevent future callbacks from being invoked.
 * Specifying a dispatch queue using this API will unschedule the stream from
 * any run loops it had previously been scheduled upon - similarly, scheduling
 * with a runloop will disassociate the stream from any existing dispatch queue.
 */
CF_EXPORT
void CFReadStreamSetDispatchQueue(CFReadStreamRef stream, dispatch_queue_t q) CF_AVAILABLE(10_9, 7_0);

CF_EXPORT
void CFWriteStreamSetDispatchQueue(CFWriteStreamRef stream, dispatch_queue_t q) CF_AVAILABLE(10_9, 7_0);

/*
 * Returns the previously set dispatch queue with an incremented retain count.  
 * Note that the stream's queue may have been set to NULL if the stream was 
 * scheduled on a runloop subsequent to it having had a dispatch queue set.
 */
CF_EXPORT
dispatch_queue_t CFReadStreamCopyDispatchQueue(CFReadStreamRef stream) CF_AVAILABLE(10_9, 7_0);

CF_EXPORT
dispatch_queue_t CFWriteStreamCopyDispatchQueue(CFWriteStreamRef stream) CF_AVAILABLE(10_9, 7_0);

/* The following API is deprecated starting in 10.5; please use CFRead/WriteStreamCopyError(), above, instead */
typedef CF_ENUM(CFIndex, CFStreamErrorDomain) {
    kCFStreamErrorDomainCustom = -1L,      /* custom to the kind of stream in question */
    kCFStreamErrorDomainPOSIX = 1,        /* POSIX errno; interpret using <sys/errno.h> */
    kCFStreamErrorDomainMacOSStatus      /* OSStatus type from Carbon APIs; interpret using <MacTypes.h> */
};

typedef struct {
    CFIndex domain; 
    SInt32 error;
} CFStreamError;
CF_EXPORT
CFStreamError CFReadStreamGetError(CFReadStreamRef stream);
CF_EXPORT
CFStreamError CFWriteStreamGetError(CFWriteStreamRef stream);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFSTREAM__ */
// ==========  CoreFoundation.framework/Headers/CoreFoundation.h
/*	CoreFoundation.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_COREFOUNDATION__)
#define __COREFOUNDATION_COREFOUNDATION__ 1
#define __COREFOUNDATION__ 1

#if !defined(CF_EXCLUDE_CSTD_HEADERS)

#include <sys/types.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__)

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#endif

#endif

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFBag.h>
#include <CoreFoundation/CFBinaryHeap.h>
#include <CoreFoundation/CFBitVector.h>
#include <CoreFoundation/CFByteOrder.h>
#include <CoreFoundation/CFCalendar.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFDateFormatter.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFNumberFormatter.h>
#include <CoreFoundation/CFPreferences.h>
#include <CoreFoundation/CFPropertyList.h>
#include <CoreFoundation/CFSet.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFStringEncodingExt.h>
#include <CoreFoundation/CFTimeZone.h>
#include <CoreFoundation/CFTree.h>
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFURLAccess.h>
#include <CoreFoundation/CFUUID.h>
#include <CoreFoundation/CFUtilities.h>

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || TARGET_OS_WIN32
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFMessagePort.h>
#include <CoreFoundation/CFPlugIn.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFStream.h>
#include <CoreFoundation/CFSocket.h>

#ifndef CF_OPEN_SOURCE
#include <CoreFoundation/CFAttributedString.h>
#include <CoreFoundation/CFNotificationCenter.h>
#include <CoreFoundation/CFURLEnumerator.h>
#endif

#endif

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#ifndef CF_OPEN_SOURCE
#include <CoreFoundation/CFFileSecurity.h>
#include <CoreFoundation/CFMachPort.h>
#include <CoreFoundation/CFStringTokenizer.h>
#include <CoreFoundation/CFFileDescriptor.h>
#endif
#endif

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#include <CoreFoundation/CFUserNotification.h>
#include <CoreFoundation/CFXMLNode.h>
#include <CoreFoundation/CFXMLParser.h>
#endif

#ifndef CF_OPEN_SOURCE
#if TARGET_OS_WIN32
#include <CoreFoundation/CFWindowsNamedPipe.h>
#endif
#endif

#endif /* ! __COREFOUNDATION_COREFOUNDATION__ */

// ==========  CoreFoundation.framework/Headers/CFDictionary.h
/*	CFDictionary.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

/*!
	@header CFDictionary
	CFDictionary implements a container which pairs pointer-sized keys
	with pointer-sized values. Values are accessed via arbitrary
	user-defined keys. A CFDictionary differs from a CFArray in that
	the key used to access a particular value in the dictionary remains
	the same as values are added to or removed from the dictionary,
	unless a value associated with its particular key is replaced or
	removed. In a CFArray, the key (or index) used to retrieve a
	particular value can change over time as values are added to or
	deleted from the array. Also unlike an array, there is no ordering
	among values in a dictionary. To enable later retrieval of a value,
	the key of the key-value pair should be constant (or treated as
	constant); if the key changes after being used to put a value in
	the dictionary, the value may not be retrievable. The keys of a
	dictionary form a set; that is, no two keys which are equal to
	one another are present in the dictionary at any time.

	Dictionaries come in two flavors, immutable, which cannot have
	values added to them or removed from them after the dictionary is
	created, and mutable, to which you can add values or from which
	remove values. Mutable dictionaries can have an unlimited number
	of values (or rather, limited only by constraints external to
	CFDictionary, like the amount of available memory).

	As with all CoreFoundation collection types, dictionaries maintain
	hard references on the values you put in them, but the retaining and
	releasing functions are user-defined callbacks that can actually do
	whatever the user wants (for example, nothing).

	Although a particular implementation of CFDictionary may not use
	hashing and a hash table for storage of the values, the keys have
	a hash-code generating function defined for them, and a function
	to test for equality of two keys. These two functions together
	must maintain the invariant that if equal(X, Y), then hash(X) ==
	hash(Y). Note that the converse will not generally be true (but
	the contrapositive, if hash(X) != hash(Y), then !equal(X, Y),
	will be as required by Boolean logic). If the hash() and equal()
	key callbacks are NULL, the key is used as a pointer-sized integer,
	and pointer equality is used. Care should be taken to provide a
	hash() callback which will compute sufficiently dispersed hash
	codes for the key set for best performance.

	Computational Complexity
	The access time for a value in the dictionary is guaranteed to be at
	worst O(N) for any implementation, current and future, but will
	often be O(1) (constant time). Insertion or deletion operations
	will typically be constant time as well, but are O(N*N) in the
	worst case in some implementations. Access of values through a key
	is faster than accessing values directly (if there are any such
	operations). Dictionaries will tend to use significantly more memory
	than a array with the same number of values.
*/

#if !defined(__COREFOUNDATION_CFDICTIONARY__)
#define __COREFOUNDATION_CFDICTIONARY__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
	@typedef CFDictionaryKeyCallBacks
	Structure containing the callbacks for keys of a CFDictionary.
	@field version The version number of the structure type being passed
		in as a parameter to the CFDictionary creation functions.
		This structure is version 0.
	@field retain The callback used to add a retain for the dictionary
		on keys as they are used to put values into the dictionary.
		This callback returns the value to use as the key in the
		dictionary, which is usually the value parameter passed to
		this callback, but may be a different value if a different
		value should be used as the key. The dictionary's allocator
		is passed as the first argument.
	@field release The callback used to remove a retain previously added
		for the dictionary from keys as their values are removed from
		the dictionary. The dictionary's allocator is passed as the
		first argument.
	@field copyDescription The callback used to create a descriptive
		string representation of each key in the dictionary. This
		is used by the CFCopyDescription() function.
	@field equal The callback used to compare keys in the dictionary for
		equality.
	@field hash The callback used to compute a hash code for keys as they
		are used to access, add, or remove values in the dictionary.
*/
typedef const void *	(*CFDictionaryRetainCallBack)(CFAllocatorRef allocator, const void *value);
typedef void		(*CFDictionaryReleaseCallBack)(CFAllocatorRef allocator, const void *value);
typedef CFStringRef	(*CFDictionaryCopyDescriptionCallBack)(const void *value);
typedef Boolean		(*CFDictionaryEqualCallBack)(const void *value1, const void *value2);
typedef CFHashCode	(*CFDictionaryHashCallBack)(const void *value);
typedef struct {
    CFIndex				version;
    CFDictionaryRetainCallBack		retain;
    CFDictionaryReleaseCallBack		release;
    CFDictionaryCopyDescriptionCallBack	copyDescription;
    CFDictionaryEqualCallBack		equal;
    CFDictionaryHashCallBack		hash;
} CFDictionaryKeyCallBacks;

/*!
	@constant kCFTypeDictionaryKeyCallBacks
	Predefined CFDictionaryKeyCallBacks structure containing a
	set of callbacks appropriate for use when the keys of a
	CFDictionary are all CFTypes.
*/
CF_EXPORT
const CFDictionaryKeyCallBacks kCFTypeDictionaryKeyCallBacks;

/*!
	@constant kCFCopyStringDictionaryKeyCallBacks
	Predefined CFDictionaryKeyCallBacks structure containing a
	set of callbacks appropriate for use when the keys of a
	CFDictionary are all CFStrings, which may be mutable and
	need to be copied in order to serve as constant keys for
	the values in the dictionary.
*/
CF_EXPORT
const CFDictionaryKeyCallBacks kCFCopyStringDictionaryKeyCallBacks;

/*!
	@typedef CFDictionaryValueCallBacks
	Structure containing the callbacks for values of a CFDictionary.
	@field version The version number of the structure type being passed
		in as a parameter to the CFDictionary creation functions.
		This structure is version 0.
	@field retain The callback used to add a retain for the dictionary
		on values as they are put into the dictionary.
		This callback returns the value to use as the value in the
		dictionary, which is usually the value parameter passed to
		this callback, but may be a different value if a different
		value should be added to the dictionary. The dictionary's
		allocator is passed as the first argument.
	@field release The callback used to remove a retain previously added
		for the dictionary from values as they are removed from
		the dictionary. The dictionary's allocator is passed as the
		first argument.
	@field copyDescription The callback used to create a descriptive
		string representation of each value in the dictionary. This
		is used by the CFCopyDescription() function.
	@field equal The callback used to compare values in the dictionary for
		equality in some operations.
*/
typedef struct {
    CFIndex				version;
    CFDictionaryRetainCallBack		retain;
    CFDictionaryReleaseCallBack		release;
    CFDictionaryCopyDescriptionCallBack	copyDescription;
    CFDictionaryEqualCallBack		equal;
} CFDictionaryValueCallBacks;

/*!
	@constant kCFTypeDictionaryValueCallBacks
	Predefined CFDictionaryValueCallBacks structure containing a set
	of callbacks appropriate for use when the values in a CFDictionary
	are all CFTypes.
*/
CF_EXPORT
const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks;

/*!
	@typedef CFDictionaryApplierFunction
	Type of the callback function used by the apply functions of
		CFDictionarys.
	@param key The current key for the value.
	@param value The current value from the dictionary.
	@param context The user-defined context parameter given to the apply
		function.
*/
typedef void (*CFDictionaryApplierFunction)(const void *key, const void *value, void *context);

/*!
	@typedef CFDictionaryRef
	This is the type of a reference to immutable CFDictionarys.
*/
typedef const struct CF_BRIDGED_TYPE(NSDictionary) __CFDictionary * CFDictionaryRef;

/*!
	@typedef CFMutableDictionaryRef
	This is the type of a reference to mutable CFDictionarys.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableDictionary) __CFDictionary * CFMutableDictionaryRef;

/*!
	@function CFDictionaryGetTypeID
	Returns the type identifier of all CFDictionary instances.
*/
CF_EXPORT
CFTypeID CFDictionaryGetTypeID(void);

/*!
	@function CFDictionaryCreate
	Creates a new immutable dictionary with the given values.
	@param allocator The CFAllocator which should be used to allocate
		memory for the dictionary and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param keys A C array of the pointer-sized keys to be used for
		the parallel C array of values to be put into the dictionary.
		This parameter may be NULL if the numValues parameter is 0.
		This C array is not changed or freed by this function. If
		this parameter is not a valid pointer to a C array of at
		least numValues pointers, the behavior is undefined.
	@param values A C array of the pointer-sized values to be in the
		dictionary. This parameter may be NULL if the numValues
		parameter is 0. This C array is not changed or freed by
		this function. If this parameter is not a valid pointer to
		a C array of at least numValues pointers, the behavior is
		undefined.
	@param numValues The number of values to copy from the keys and
		values C arrays into the CFDictionary. This number will be
		the count of the dictionary. If this parameter is
		negative, or greater than the number of values actually
		in the keys or values C arrays, the behavior is undefined.
	@param keyCallBacks A pointer to a CFDictionaryKeyCallBacks structure
		initialized with the callbacks for the dictionary to use on
		each key in the dictionary. The retain callback will be used
		within this function, for example, to retain all of the new
		keys from the keys C array. A copy of the contents of the
		callbacks structure is made, so that a pointer to a structure
		on the stack can be passed in, or can be reused for multiple
		dictionary creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFDictionary, the behavior is undefined. The retain field may
		be NULL, in which case the CFDictionary will do nothing to add
		a retain to the keys of the contained values. The release field
		may be NULL, in which case the CFDictionary will do nothing
		to remove the dictionary's retain (if any) on the keys when the
		dictionary is destroyed or a key-value pair is removed. If the
		copyDescription field is NULL, the dictionary will create a
		simple description for a key. If the equal field is NULL, the
		dictionary will use pointer equality to test for equality of
		keys. If the hash field is NULL, a key will be converted from
		a pointer to an integer to compute the hash code. This callbacks
		parameter itself may be NULL, which is treated as if a valid
		structure of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a CFDictionaryKeyCallBacks callbacks structure,
		the behavior is undefined. If any of the keys put into the
		dictionary is not one understood by one of the callback functions
		the behavior when that callback function is used is undefined.
	@param valueCallBacks A pointer to a CFDictionaryValueCallBacks structure
		initialized with the callbacks for the dictionary to use on
		each value in the dictionary. The retain callback will be used
		within this function, for example, to retain all of the new
		values from the values C array. A copy of the contents of the
		callbacks structure is made, so that a pointer to a structure
		on the stack can be passed in, or can be reused for multiple
		dictionary creations. If the version field of this callbacks
		structure is not one of the defined ones for CFDictionary, the
		behavior is undefined. The retain field may be NULL, in which
		case the CFDictionary will do nothing to add a retain to values
		as they are put into the dictionary. The release field may be
		NULL, in which case the CFDictionary will do nothing to remove
		the dictionary's retain (if any) on the values when the
		dictionary is destroyed or a key-value pair is removed. If the
		copyDescription field is NULL, the dictionary will create a
		simple description for a value. If the equal field is NULL, the
		dictionary will use pointer equality to test for equality of
		values. This callbacks parameter itself may be NULL, which is
		treated as if a valid structure of version 0 with all fields
		NULL had been passed in. Otherwise,
		if any of the fields are not valid pointers to functions
		of the correct type, or this parameter is not a valid
		pointer to a CFDictionaryValueCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		dictionary is not one understood by one of the callback functions
		the behavior when that callback function is used is undefined.
	@result A reference to the new immutable CFDictionary.
*/
CF_EXPORT
CFDictionaryRef CFDictionaryCreate(CFAllocatorRef allocator, const void **keys, const void **values, CFIndex numValues, const CFDictionaryKeyCallBacks *keyCallBacks, const CFDictionaryValueCallBacks *valueCallBacks);

/*!
	@function CFDictionaryCreateCopy
	Creates a new immutable dictionary with the key-value pairs from
		the given dictionary.
	@param allocator The CFAllocator which should be used to allocate
		memory for the dictionary and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theDict The dictionary which is to be copied. The keys and values
		from the dictionary are copied as pointers into the new
		dictionary (that is, the values themselves are copied, not
		that which the values point to, if anything). However, the
		keys and values are also retained by the new dictionary using
		the retain function of the original dictionary.
		The count of the new dictionary will be the same as the
		given dictionary. The new dictionary uses the same callbacks
		as the dictionary to be copied. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@result A reference to the new immutable CFDictionary.
*/
CF_EXPORT
CFDictionaryRef CFDictionaryCreateCopy(CFAllocatorRef allocator, CFDictionaryRef theDict);

/*!
	@function CFDictionaryCreateMutable
	Creates a new mutable dictionary.
	@param allocator The CFAllocator which should be used to allocate
		memory for the dictionary and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFDictionary. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A dictionary's actual capacity is only limited by 
                address space and available memory constraints). If this 
                parameter is negative, the behavior is undefined.
	@param keyCallBacks A pointer to a CFDictionaryKeyCallBacks structure
		initialized with the callbacks for the dictionary to use on
		each key in the dictionary. A copy of the contents of the
		callbacks structure is made, so that a pointer to a structure
		on the stack can be passed in, or can be reused for multiple
		dictionary creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFDictionary, the behavior is undefined. The retain field may
		be NULL, in which case the CFDictionary will do nothing to add
		a retain to the keys of the contained values. The release field
		may be NULL, in which case the CFDictionary will do nothing
		to remove the dictionary's retain (if any) on the keys when the
		dictionary is destroyed or a key-value pair is removed. If the
		copyDescription field is NULL, the dictionary will create a
		simple description for a key. If the equal field is NULL, the
		dictionary will use pointer equality to test for equality of
		keys. If the hash field is NULL, a key will be converted from
		a pointer to an integer to compute the hash code. This callbacks
		parameter itself may be NULL, which is treated as if a valid
		structure of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a CFDictionaryKeyCallBacks callbacks structure,
		the behavior is undefined. If any of the keys put into the
		dictionary is not one understood by one of the callback functions
		the behavior when that callback function is used is undefined.
	@param valueCallBacks A pointer to a CFDictionaryValueCallBacks structure
		initialized with the callbacks for the dictionary to use on
		each value in the dictionary. The retain callback will be used
		within this function, for example, to retain all of the new
		values from the values C array. A copy of the contents of the
		callbacks structure is made, so that a pointer to a structure
		on the stack can be passed in, or can be reused for multiple
		dictionary creations. If the version field of this callbacks
		structure is not one of the defined ones for CFDictionary, the
		behavior is undefined. The retain field may be NULL, in which
		case the CFDictionary will do nothing to add a retain to values
		as they are put into the dictionary. The release field may be
		NULL, in which case the CFDictionary will do nothing to remove
		the dictionary's retain (if any) on the values when the
		dictionary is destroyed or a key-value pair is removed. If the
		copyDescription field is NULL, the dictionary will create a
		simple description for a value. If the equal field is NULL, the
		dictionary will use pointer equality to test for equality of
		values. This callbacks parameter itself may be NULL, which is
		treated as if a valid structure of version 0 with all fields
		NULL had been passed in. Otherwise,
		if any of the fields are not valid pointers to functions
		of the correct type, or this parameter is not a valid
		pointer to a CFDictionaryValueCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		dictionary is not one understood by one of the callback functions
		the behavior when that callback function is used is undefined.
	@result A reference to the new mutable CFDictionary.
*/
CF_EXPORT
CFMutableDictionaryRef CFDictionaryCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFDictionaryKeyCallBacks *keyCallBacks, const CFDictionaryValueCallBacks *valueCallBacks);

/*!
	@function CFDictionaryCreateMutableCopy
	Creates a new mutable dictionary with the key-value pairs from
		the given dictionary.
	@param allocator The CFAllocator which should be used to allocate
		memory for the dictionary and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFDictionary. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A dictionary's actual capacity is only limited by
                address space and available memory constraints). 
                This parameter must be greater than or equal
                to the count of the dictionary which is to be copied, or the
                behavior is undefined. If this parameter is negative, the
                behavior is undefined.
	@param theDict The dictionary which is to be copied. The keys and values
		from the dictionary are copied as pointers into the new
		dictionary (that is, the values themselves are copied, not
		that which the values point to, if anything). However, the
		keys and values are also retained by the new dictionary using
		the retain function of the original dictionary.
		The count of the new dictionary will be the same as the
		given dictionary. The new dictionary uses the same callbacks
		as the dictionary to be copied. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@result A reference to the new mutable CFDictionary.
*/
CF_EXPORT
CFMutableDictionaryRef CFDictionaryCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFDictionaryRef theDict);

/*!
	@function CFDictionaryGetCount
	Returns the number of values currently in the dictionary.
	@param theDict The dictionary to be queried. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@result The number of values in the dictionary.
*/
CF_EXPORT
CFIndex CFDictionaryGetCount(CFDictionaryRef theDict);

/*!
	@function CFDictionaryGetCountOfKey
	Counts the number of times the given key occurs in the dictionary.
	@param theDict The dictionary to be searched. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param key The key for which to find matches in the dictionary. The
		hash() and equal() key callbacks provided when the dictionary
		was created are used to compare. If the hash() key callback
		was NULL, the key is treated as a pointer and converted to
		an integer. If the equal() key callback was NULL, pointer
		equality (in C, ==) is used. If key, or any of the keys in
		the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@result Returns 1 if a matching key is used by the dictionary,
		0 otherwise.
*/
CF_EXPORT
CFIndex CFDictionaryGetCountOfKey(CFDictionaryRef theDict, const void *key);

/*!
	@function CFDictionaryGetCountOfValue
	Counts the number of times the given value occurs in the dictionary.
	@param theDict The dictionary to be searched. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param value The value for which to find matches in the dictionary. The
		equal() callback provided when the dictionary was created is
		used to compare. If the equal() value callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values in
		the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@result The number of times the given value occurs in the dictionary.
*/
CF_EXPORT
CFIndex CFDictionaryGetCountOfValue(CFDictionaryRef theDict, const void *value);

/*!
	@function CFDictionaryContainsKey
	Reports whether or not the key is in the dictionary.
	@param theDict The dictionary to be searched. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param key The key for which to find matches in the dictionary. The
		hash() and equal() key callbacks provided when the dictionary
		was created are used to compare. If the hash() key callback
		was NULL, the key is treated as a pointer and converted to
		an integer. If the equal() key callback was NULL, pointer
		equality (in C, ==) is used. If key, or any of the keys in
		the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@result true, if the key is in the dictionary, otherwise false.
*/
CF_EXPORT
Boolean CFDictionaryContainsKey(CFDictionaryRef theDict, const void *key);

/*!
	@function CFDictionaryContainsValue
	Reports whether or not the value is in the dictionary.
	@param theDict The dictionary to be searched. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param value The value for which to find matches in the dictionary. The
		equal() callback provided when the dictionary was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@result true, if the value is in the dictionary, otherwise false.
*/
CF_EXPORT
Boolean CFDictionaryContainsValue(CFDictionaryRef theDict, const void *value);

/*!
	@function CFDictionaryGetValue
	Retrieves the value associated with the given key.
	@param theDict The dictionary to be queried. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param key The key for which to find a match in the dictionary. The
		hash() and equal() key callbacks provided when the dictionary
		was created are used to compare. If the hash() key callback
		was NULL, the key is treated as a pointer and converted to
		an integer. If the equal() key callback was NULL, pointer
		equality (in C, ==) is used. If key, or any of the keys in
		the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@result The value with the given key in the dictionary, or NULL if
		no key-value pair with a matching key exists. Since NULL
		can be a valid value in some dictionaries, the function
		CFDictionaryGetValueIfPresent() must be used to distinguish
		NULL-no-found from NULL-is-the-value.
*/
CF_EXPORT
const void *CFDictionaryGetValue(CFDictionaryRef theDict, const void *key);

/*!
	@function CFDictionaryGetValueIfPresent
	Retrieves the value associated with the given key.
	@param theDict The dictionary to be queried. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param key The key for which to find a match in the dictionary. The
		hash() and equal() key callbacks provided when the dictionary
		was created are used to compare. If the hash() key callback
		was NULL, the key is treated as a pointer and converted to
		an integer. If the equal() key callback was NULL, pointer
		equality (in C, ==) is used. If key, or any of the keys in
		the dictionary, are not understood by the equal() callback,
		the behavior is undefined.
	@param value A pointer to memory which should be filled with the
		pointer-sized value if a matching key is found. If no key
		match is found, the contents of the storage pointed to by
		this parameter are undefined. This parameter may be NULL,
		in which case the value from the dictionary is not returned
		(but the return value of this function still indicates
		whether or not the key-value pair was present).
	@result true, if a matching key was found, false otherwise.
*/
CF_EXPORT
Boolean CFDictionaryGetValueIfPresent(CFDictionaryRef theDict, const void *key, const void **value);

/*!
	@function CFDictionaryGetKeysAndValues
	Fills the two buffers with the keys and values from the dictionary.
	@param theDict The dictionary to be queried. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param keys A C array of pointer-sized values to be filled with keys
		from the dictionary. The keys and values C arrays are parallel
		to each other (that is, the items at the same indices form a
		key-value pair from the dictionary). This parameter may be NULL
		if the keys are not desired. If this parameter is not a valid
		pointer to a C array of at least CFDictionaryGetCount() pointers,
		or NULL, the behavior is undefined.
	@param values A C array of pointer-sized values to be filled with values
		from the dictionary. The keys and values C arrays are parallel
		to each other (that is, the items at the same indices form a
		key-value pair from the dictionary). This parameter may be NULL
		if the values are not desired. If this parameter is not a valid
		pointer to a C array of at least CFDictionaryGetCount() pointers,
		or NULL, the behavior is undefined.
*/
CF_EXPORT
void CFDictionaryGetKeysAndValues(CFDictionaryRef theDict, const void **keys, const void **values);

/*!
	@function CFDictionaryApplyFunction
	Calls a function once for each value in the dictionary.
	@param theDict The dictionary to be queried. If this parameter is
		not a valid CFDictionary, the behavior is undefined.
	@param applier The callback function to call once for each value in
		the dictionary. If this parameter is not a
		pointer to a function of the correct prototype, the behavior
		is undefined. If there are keys or values which the
		applier function does not expect or cannot properly apply
		to, the behavior is undefined. 
	@param context A pointer-sized user-defined value, which is passed
		as the third parameter to the applier function, but is
		otherwise unused by this function. If the context is not
		what is expected by the applier function, the behavior is
		undefined.
*/
CF_EXPORT
void CFDictionaryApplyFunction(CFDictionaryRef theDict, CFDictionaryApplierFunction applier, void *context);

/*!
	@function CFDictionaryAddValue
	Adds the key-value pair to the dictionary if no such key already exists.
	@param theDict The dictionary to which the value is to be added. If this
		parameter is not a valid mutable CFDictionary, the behavior is
		undefined.
	@param key The key of the value to add to the dictionary. The key is
		retained by the dictionary using the retain callback provided
		when the dictionary was created. If the key is not of the sort
		expected by the retain callback, the behavior is undefined. If
		a key which matches this key is already present in the dictionary,
		this function does nothing ("add if absent").
	@param value The value to add to the dictionary. The value is retained
		by the dictionary using the retain callback provided when the
		dictionary was created. If the value is not of the sort expected
		by the retain callback, the behavior is undefined.
*/
CF_EXPORT
void CFDictionaryAddValue(CFMutableDictionaryRef theDict, const void *key, const void *value);

/*!
	@function CFDictionarySetValue
	Sets the value of the key in the dictionary.
	@param theDict The dictionary to which the value is to be set. If this
		parameter is not a valid mutable CFDictionary, the behavior is
		undefined.
	@param key The key of the value to set into the dictionary. If a key 
		which matches this key is already present in the dictionary, only
		the value is changed ("add if absent, replace if present"). If
		no key matches the given key, the key-value pair is added to the
		dictionary. If added, the key is retained by the dictionary,
		using the retain callback provided
		when the dictionary was created. If the key is not of the sort
		expected by the key retain callback, the behavior is undefined.
	@param value The value to add to or replace into the dictionary. The value
		is retained by the dictionary using the retain callback provided
		when the dictionary was created, and the previous value if any is
		released. If the value is not of the sort expected by the
		retain or release callbacks, the behavior is undefined.
*/
CF_EXPORT
void CFDictionarySetValue(CFMutableDictionaryRef theDict, const void *key, const void *value);

/*!
	@function CFDictionaryReplaceValue
	Replaces the value of the key in the dictionary.
	@param theDict The dictionary to which the value is to be replaced. If this
		parameter is not a valid mutable CFDictionary, the behavior is
		undefined.
	@param key The key of the value to replace in the dictionary. If a key 
		which matches this key is present in the dictionary, the value
		is changed to the given value, otherwise this function does
		nothing ("replace if present").
	@param value The value to replace into the dictionary. The value
		is retained by the dictionary using the retain callback provided
		when the dictionary was created, and the previous value is
		released. If the value is not of the sort expected by the
		retain or release callbacks, the behavior is undefined.
*/
CF_EXPORT
void CFDictionaryReplaceValue(CFMutableDictionaryRef theDict, const void *key, const void *value);

/*!
	@function CFDictionaryRemoveValue
	Removes the value of the key from the dictionary.
	@param theDict The dictionary from which the value is to be removed. If this
		parameter is not a valid mutable CFDictionary, the behavior is
		undefined.
	@param key The key of the value to remove from the dictionary. If a key 
		which matches this key is present in the dictionary, the key-value
		pair is removed from the dictionary, otherwise this function does
		nothing ("remove if present").
*/
CF_EXPORT
void CFDictionaryRemoveValue(CFMutableDictionaryRef theDict, const void *key);

/*!
	@function CFDictionaryRemoveAllValues
	Removes all the values from the dictionary, making it empty.
	@param theDict The dictionary from which all of the values are to be
		removed. If this parameter is not a valid mutable
		CFDictionary, the behavior is undefined.
*/
CF_EXPORT
void CFDictionaryRemoveAllValues(CFMutableDictionaryRef theDict);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFDICTIONARY__ */

// ==========  CoreFoundation.framework/Headers/CFFileSecurity.h
/*
 *  CFFileSecurity.h
 *  NSFileSecurity and CFFileSecurity are toll-free bridged.
 *
 *  Copyright (c) 2010-2015, Apple Inc. All rights reserved.
 */

#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || CF_BUILDING_CF || NSBUILDINGFOUNDATION

#if !defined(__COREFOUNDATION_CFFILESECURITY__)
#define __COREFOUNDATION_CFFILESECURITY__ 1

#include <sys/types.h>
#include <sys/acl.h>
#include <sys/fcntl.h>
#include <CoreFoundation/CFUUID.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*
 *	A CFFileSecurity object encapulates a file system object's security information
 *	in a CF object.
 */
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSFileSecurity) __CFFileSecurity* CFFileSecurityRef;

/*
 *	Returns the type identifier for the CFFileSecurity opaque type.
 *
 *	Return Value
 *		The type identifier for the CFFileSecurity opaque type.
 */
CF_EXPORT
CFTypeID CFFileSecurityGetTypeID(void) CF_AVAILABLE(10_7, 5_0);


/*
 *	Creates an CFFileSecurity object.
 *
 *	Parameters
 *		allocator
 *			The allocator to use to allocate memory for the new object. Pass
 *			NULL or kCFAllocatorDefault to use the current default allocator.
 *	Return Value
 *		A new CFFileSecurity object, or NULL if there was a problem creating the
 *		object. Ownership follows the Create Rule.
 */
CF_EXPORT
CFFileSecurityRef CFFileSecurityCreate(CFAllocatorRef allocator) CF_AVAILABLE(10_7, 5_0);


/*
 *  Creates a copy of a CFFileSecurity object.
 *
 *  Parameters
 *		allocator
 *			The allocator to use to allocate memory for the new object. Pass
 *			NULL or kCFAllocatorDefault to use the current default allocator.
 *		fileSec
 *			The CFFileSecurity object to copy.
 *	Return Value
 *		A copy of fileSec, or NULL if there was a problem creating the object.
 *		Ownership follows the Create Rule.
 */
CF_EXPORT
CFFileSecurityRef CFFileSecurityCreateCopy(CFAllocatorRef allocator, CFFileSecurityRef fileSec) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine copies the owner UUID associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		ownerUUID
 *			A pointer to storage for the owner UUID.
 *	Return Value
 *		true if ownerUUID is successfully returned; false if there is no owner
 *		UUID property associated with an CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityCopyOwnerUUID(CFFileSecurityRef fileSec, CFUUIDRef *ownerUUID) CF_AVAILABLE(10_7, 5_0);

/*
 *	This routine sets the owner UUID associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		ownerUUID
 *			The owner UUID.
 *	Return Value
 *		true if the owner UUID was successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetOwnerUUID(CFFileSecurityRef fileSec, CFUUIDRef ownerUUID) CF_AVAILABLE(10_7, 5_0);

/*
 *	This routine copies the group UUID associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		groupUUID
 *			A pointer to storage for the group UUID.
 *	Return Value
 *		true if groupUUID is successfully returned; false if there is no group
 *		UUID property associated with an CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityCopyGroupUUID(CFFileSecurityRef fileSec, CFUUIDRef *groupUUID) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine sets the group UUID associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		groupUUID
 *			The group UUID.
 *	Return Value
 *		true if the group UUID was successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetGroupUUID(CFFileSecurityRef fileSec, CFUUIDRef groupUUID) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine copies the access control list (acl_t) associated with an
 *	CFFileSecurity object. The acl_t returned by this routine is a copy and must
 *	be released using acl_free(3). The acl_t is meant to be manipulated using
 *	the acl calls defined in <sys/acl.h>.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		accessControlList
 *			A pointer to storage for an acl_t. The acl_t be released using
 *			acl_free(3)
 *	Return Value
 *		true if the access control list is successfully copied; false if there is
 *		no access control list property associated with the CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityCopyAccessControlList(CFFileSecurityRef fileSec, acl_t *accessControlList) CF_AVAILABLE(10_7, 5_0);

#define kCFFileSecurityRemoveACL (acl_t) _FILESEC_REMOVE_ACL

/*
 *	This routine will set the access control list (acl_t) associated with an
 *	CFFileSecurityRef. To request removal of an access control list from a
 *	filesystem object, pass in kCFFileSecurityRemoveACL as the acl_t and set
 *	the fileSec on the target object using CFURLSetResourcePropertyForKey and
 *	the kCFURLFileSecurityKey. Setting the accessControlList to NULL will result
 *	in the property being unset.
 *
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		accessControlList
 *			The acl_t to set, or kCFFileSecurityRemoveACL to remove the access
 *			control list, or NULL to unset the accessControlList.
 *	Return Value
 *		true if the access control list is successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetAccessControlList(CFFileSecurityRef fileSec, acl_t accessControlList) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine gets the owner uid_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			A pointer to where the owner uid_t will be put.
 *	Return Value
 *		true if owner uid_t is successfully obtained; false if there is no owner
 *		property associated with an CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityGetOwner(CFFileSecurityRef fileSec, uid_t *owner) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine sets the owner uid_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			The owner uid_t.
 *	Return Value
 *		true if the owner uid_t was successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetOwner(CFFileSecurityRef fileSec, uid_t owner) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine gets the group gid_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			A pointer to where the group gid_t will be put.
 *	Return Value
 *		true if group gid_t is successfully obtained; false if there is no group
 *		property associated with an CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityGetGroup(CFFileSecurityRef fileSec, gid_t *group) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine sets the group gid_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			The group gid_t.
 *	Return Value
 *		true if the group gid_t was successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetGroup(CFFileSecurityRef fileSec, gid_t group) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine gets the mode_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			A pointer to where the mode_t will be put.
 *	Return Value
 *		true if mode_t is successfully obtained; false if there is no mode
 *		property associated with an CFFileSecurity object.
 */
CF_EXPORT
Boolean CFFileSecurityGetMode(CFFileSecurityRef fileSec, mode_t *mode) CF_AVAILABLE(10_7, 5_0);


/*
 *	This routine sets the mode_t associated with an CFFileSecurity object.
 *  
 *	Parameters
 *		fileSec
 *			The CFFileSecurity object.
 *		owner
 *			The mode_t.
 *	Return Value
 *		true if the mode_t was successfully set; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecuritySetMode(CFFileSecurityRef fileSec, mode_t mode) CF_AVAILABLE(10_7, 5_0);


/* values to pass in the clearPropertyMask to CFFileSecurityClearProperties */
typedef CF_OPTIONS(CFOptionFlags, CFFileSecurityClearOptions) {
    kCFFileSecurityClearOwner               = 1UL << 0,
    kCFFileSecurityClearGroup               = 1UL << 1,
    kCFFileSecurityClearMode                = 1UL << 2,
    kCFFileSecurityClearOwnerUUID           = 1UL << 3,
    kCFFileSecurityClearGroupUUID           = 1UL << 4,
    kCFFileSecurityClearAccessControlList   = 1UL << 5
} CF_ENUM_AVAILABLE(10_8, 6_0);

/*
 *	This routine clears file security properties in the CFFileSecurity object.
 *  
 *	Parameters
 *		clearPropertyMask
 *			The file security properties to clear.
 *	Return Value
 *		true if the file security properties were successfully cleared; otherwise, false.
 */
CF_EXPORT
Boolean CFFileSecurityClearProperties(CFFileSecurityRef fileSec, CFFileSecurityClearOptions clearPropertyMask) CF_AVAILABLE(10_8, 6_0);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFFILESECURITY__ */
#endif

// ==========  CoreFoundation.framework/Headers/CFCharacterSet.h
/*	CFCharacterSet.h
	Copyright (c) 1999-2015, Apple Inc. All rights reserved.
*/

/*!
	@header CFCharacterSet
        CFCharacterSet represents a set, or a bag, of Unicode characters.
        The API consists of 3 groups:
        1) creation/manipulation of CFCharacterSet instances,
        2) query of a single Unicode character membership,
        and 3) bitmap representation related (reading/writing).
        Conceptually, CFCharacterSet is a 136K byte bitmap array of
        which each bit represents a Unicode code point.  It could
        contain the Unicode characters in ISO 10646 Basic Multilingual
        Plane (BMP) and characters in Plane 1 through Plane 16
        accessible via surrogate paris in the Unicode Transformation
        Format, 16-bit encoding form (UTF-16).  In other words, it can
        store values from 0x00000 to 0x10FFFF in the Unicode
        Transformation Format, 32-bit encoding form (UTF-32).  However,
        in general, how CFCharacterSet stores the information is an
        implementation detail.  Note even CFData used for the external
        bitmap representation rarely has 136K byte.  For detailed
        discussion of the external bitmap representation, refer to the
        comments for CFCharacterSetCreateWithBitmapRepresentation below.
        Note that the existance of non-BMP characters in a character set
        does not imply the membership of the corresponding surrogate
        characters.  For example, a character set with U+10000 does not
        match with U+D800.
*/

#if !defined(__COREFOUNDATION_CFCHARACTERSET__)
#define __COREFOUNDATION_CFCHARACTERSET__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
	@typedef CFCharacterSetRef
	This is the type of a reference to immutable CFCharacterSets.
*/
typedef const struct CF_BRIDGED_TYPE(NSCharacterSet) __CFCharacterSet * CFCharacterSetRef;

/*!
	@typedef CFMutableCharacterSetRef
	This is the type of a reference to mutable CFMutableCharacterSets.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableCharacterSet) __CFCharacterSet * CFMutableCharacterSetRef;

/*!
	@typedef CFCharacterSetPredefinedSet
        Type of the predefined CFCharacterSet selector values.
*/
   
typedef CF_ENUM(CFIndex, CFCharacterSetPredefinedSet) {
    kCFCharacterSetControl = 1, /* Control character set (Unicode General Category Cc and Cf) */
    kCFCharacterSetWhitespace, /* Whitespace character set (Unicode General Category Zs and U0009 CHARACTER TABULATION) */
    kCFCharacterSetWhitespaceAndNewline,  /* Whitespace and Newline character set (Unicode General Category Z*, U000A ~ U000D, and U0085) */
    kCFCharacterSetDecimalDigit, /* Decimal digit character set */
    kCFCharacterSetLetter, /* Letter character set (Unicode General Category L* & M*) */
    kCFCharacterSetLowercaseLetter, /* Lowercase character set (Unicode General Category Ll) */
    kCFCharacterSetUppercaseLetter, /* Uppercase character set (Unicode General Category Lu and Lt) */
    kCFCharacterSetNonBase, /* Non-base character set (Unicode General Category M*) */
    kCFCharacterSetDecomposable, /* Canonically decomposable character set */
    kCFCharacterSetAlphaNumeric, /* Alpha Numeric character set (Unicode General Category L*, M*, & N*) */
    kCFCharacterSetPunctuation, /* Punctuation character set (Unicode General Category P*) */
    kCFCharacterSetCapitalizedLetter = 13, /* Titlecase character set (Unicode General Category Lt) */
    kCFCharacterSetSymbol = 14, /* Symbol character set (Unicode General Category S*) */
    kCFCharacterSetNewline CF_ENUM_AVAILABLE(10_5, 2_0) = 15, /* Newline character set (U000A ~ U000D, U0085, U2028, and U2029) */
    kCFCharacterSetIllegal = 12/* Illegal character set */
};

/*!
	@function CFCharacterSetGetTypeID
	Returns the type identifier of all CFCharacterSet instances.
*/
CF_EXPORT
CFTypeID CFCharacterSetGetTypeID(void);

/*!
	@function CFCharacterSetGetPredefined
	Returns a predefined CFCharacterSet instance.
	@param theSetIdentifier The CFCharacterSetPredefinedSet selector
                which specifies the predefined character set.  If the
                value is not in CFCharacterSetPredefinedSet, the behavior
                is undefined.
	@result A reference to the predefined immutable CFCharacterSet.
                This instance is owned by CF.
*/
CF_EXPORT
CFCharacterSetRef CFCharacterSetGetPredefined(CFCharacterSetPredefinedSet theSetIdentifier);

/*!
	@function CFCharacterSetCreateWithCharactersInRange
	Creates a new immutable character set with the values from the given range.
	@param alloc The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theRange The CFRange which should be used to specify the
                Unicode range the character set is filled with.  It
                accepts the range in 32-bit in the UTF-32 format.  The
                valid character point range is from 0x00000 to 0x10FFFF.
                If the range is outside of the valid Unicode character
                point, the behavior is undefined.
	@result A reference to the new immutable CFCharacterSet.
*/
CF_EXPORT
CFCharacterSetRef CFCharacterSetCreateWithCharactersInRange(CFAllocatorRef alloc, CFRange theRange);

/*!
	@function CFCharacterSetCreateWithCharactersInString
	Creates a new immutable character set with the values in the given string.
	@param alloc The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theString The CFString which should be used to specify
                the Unicode characters the character set is filled with.
                If this parameter is not a valid CFString, the behavior
                is undefined.
        @result A reference to the new immutable CFCharacterSet.
*/
CF_EXPORT
CFCharacterSetRef CFCharacterSetCreateWithCharactersInString(CFAllocatorRef alloc, CFStringRef theString);

/*!
	@function CFCharacterSetCreateWithBitmapRepresentation
	Creates a new immutable character set with the bitmap representtion in the given data.
	@param alloc The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theData The CFData which should be used to specify the
                bitmap representation of the Unicode character points
                the character set is filled with.  The bitmap
                representation could contain all the Unicode character
                range starting from BMP to Plane 16.  The first 8192 bytes
                of the data represent the BMP range.  The BMP range 8192
                bytes can be followed by zero to sixteen 8192 byte
                bitmaps, each one with the plane index byte prepended.
                For example, the bitmap representing the BMP and Plane 2
                has the size of 16385 bytes (8192 bytes for BMP, 1 byte
                index + 8192 bytes bitmap for Plane 2).  The plane index
                byte, in this case, contains the integer value two.  If
                this parameter is not a valid CFData or it contains a
                Plane index byte outside of the valid Plane range
                (1 to 16), the behavior is undefined.
        @result A reference to the new immutable CFCharacterSet.
*/
CF_EXPORT
CFCharacterSetRef CFCharacterSetCreateWithBitmapRepresentation(CFAllocatorRef alloc, CFDataRef theData);

/*!
	@function CFCharacterSetCreateInvertedSet
	Creates a new immutable character set that is the invert of the specified character set.
	@param alloc The CFAllocator which should be used to allocate
			memory for the array and its storage for values. This
			parameter may be NULL in which case the current default
			CFAllocator is used. If this reference is not a valid
			CFAllocator, the behavior is undefined.
	@param theSet The CFCharacterSet which is to be inverted.  If this
                		parameter is not a valid CFCharacterSet, the behavior is
              		undefined.
	@result A reference to the new immutable CFCharacterSet.
*/
CF_EXPORT CFCharacterSetRef CFCharacterSetCreateInvertedSet(CFAllocatorRef alloc, CFCharacterSetRef theSet);

/*!
	@function CFCharacterSetIsSupersetOfSet
	Reports whether or not the character set is a superset of the character set specified as the second parameter.
	@param theSet  The character set to be checked for the membership of theOtherSet.
		If this parameter is not a valid CFCharacterSet, the behavior is undefined.
	@param theOtherset  The character set to be checked whether or not it is a subset of theSet.
		If this parameter is not a valid CFCharacterSet, the behavior is undefined.
*/
CF_EXPORT Boolean CFCharacterSetIsSupersetOfSet(CFCharacterSetRef theSet, CFCharacterSetRef theOtherset);

/*!
	@function CFCharacterSetHasMemberInPlane
	Reports whether or not the character set contains at least one member character in the specified plane.
	@param theSet  The character set to be checked for the membership.  If this
		parameter is not a valid CFCharacterSet, the behavior is undefined.
	@param thePlane  The plane number to be checked for the membership.
		The valid value range is from 0 to 16.  If the value is outside of the valid
		plane number range, the behavior is undefined.
*/
CF_EXPORT Boolean CFCharacterSetHasMemberInPlane(CFCharacterSetRef theSet, CFIndex thePlane);

/*!
	@function CFCharacterSetCreateMutable
	Creates a new empty mutable character set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@result A reference to the new mutable CFCharacterSet.
*/
CF_EXPORT
CFMutableCharacterSetRef CFCharacterSetCreateMutable(CFAllocatorRef alloc);

/*!
	@function CFCharacterSetCreateCopy
	Creates a new character set with the values from the given character set.  This function tries to compact the backing store where applicable.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theSet The CFCharacterSet which is to be copied.  If this
                parameter is not a valid CFCharacterSet, the behavior is
                undefined.
	@result A reference to the new CFCharacterSet.
*/
CF_EXPORT
CFCharacterSetRef CFCharacterSetCreateCopy(CFAllocatorRef alloc, CFCharacterSetRef theSet);

/*!
	@function CFCharacterSetCreateMutableCopy
	Creates a new mutable character set with the values from the given character set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theSet The CFCharacterSet which is to be copied.  If this
                parameter is not a valid CFCharacterSet, the behavior is
                undefined.
	@result A reference to the new mutable CFCharacterSet.
*/
CF_EXPORT
CFMutableCharacterSetRef CFCharacterSetCreateMutableCopy(CFAllocatorRef alloc, CFCharacterSetRef theSet);

/*!
	@function CFCharacterSetIsCharacterMember
	Reports whether or not the Unicode character is in the character set.
	@param theSet The character set to be searched. If this parameter
                is not a valid CFCharacterSet, the behavior is undefined.
	@param theChar The Unicode character for which to test against the
                character set.  Note that this function takes 16-bit Unicode
                character value; hence, it does not support access to the
                non-BMP planes.  
        @result true, if the value is in the character set, otherwise false.
*/
CF_EXPORT
Boolean CFCharacterSetIsCharacterMember(CFCharacterSetRef theSet, UniChar theChar);

/*!
	@function CFCharacterSetIsLongCharacterMember
	Reports whether or not the UTF-32 character is in the character set.
	@param theSet The character set to be searched. If this parameter
               		 is not a valid CFCharacterSet, the behavior is undefined.
	@param theChar The UTF-32 character for which to test against the
			character set.
        @result true, if the value is in the character set, otherwise false.
*/
CF_EXPORT Boolean CFCharacterSetIsLongCharacterMember(CFCharacterSetRef theSet, UTF32Char theChar);

/*!
	@function CFCharacterSetCreateBitmapRepresentation
	Creates a new immutable data with the bitmap representation from the given character set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theSet The CFCharacterSet which is to be used create the
                bitmap representation from.  Refer to the comments for
                CFCharacterSetCreateWithBitmapRepresentation for the
                detailed discussion of the bitmap representation format.
                If this parameter is not a valid CFCharacterSet, the
                behavior is undefined.
	@result A reference to the new immutable CFData.
*/
CF_EXPORT
CFDataRef CFCharacterSetCreateBitmapRepresentation(CFAllocatorRef alloc, CFCharacterSetRef theSet);

/*!
	@function CFCharacterSetAddCharactersInRange
	Adds the given range to the charaacter set.
	@param theSet The character set to which the range is to be added.
                If this parameter is not a valid mutable CFCharacterSet,
                the behavior is undefined.
        @param theRange The range to add to the character set.  It accepts
                the range in 32-bit in the UTF-32 format.  The valid
                character point range is from 0x00000 to 0x10FFFF.  If the
                range is outside of the valid Unicode character point,
                the behavior is undefined.
*/
CF_EXPORT
void CFCharacterSetAddCharactersInRange(CFMutableCharacterSetRef theSet, CFRange theRange);

/*!
	@function CFCharacterSetRemoveCharactersInRange
	Removes the given range from the charaacter set.
	@param theSet The character set from which the range is to be
                removed.  If this parameter is not a valid mutable
                CFCharacterSet, the behavior is undefined.
        @param theRange The range to remove from the character set.
                It accepts the range in 32-bit in the UTF-32 format.
                The valid character point range is from 0x00000 to 0x10FFFF.
                If the range is outside of the valid Unicode character point,
                the behavior is undefined.
*/
CF_EXPORT
void CFCharacterSetRemoveCharactersInRange(CFMutableCharacterSetRef theSet, CFRange theRange);

/*!
	@function CFCharacterSetAddCharactersInString
	Adds the characters in the given string to the charaacter set.
	@param theSet The character set to which the characters in the
                string are to be added.  If this parameter is not a
                valid mutable CFCharacterSet, the behavior is undefined.
        @param theString The string to add to the character set.
                If this parameter is not a valid CFString, the behavior
                is undefined.
*/
CF_EXPORT
void CFCharacterSetAddCharactersInString(CFMutableCharacterSetRef theSet,  CFStringRef theString);

/*!
	@function CFCharacterSetRemoveCharactersInString
	Removes the characters in the given string from the charaacter set.
	@param theSet The character set from which the characters in the
                string are to be remove.  If this parameter is not a
                valid mutable CFCharacterSet, the behavior is undefined.
        @param theString The string to remove from the character set.
                If this parameter is not a valid CFString, the behavior
                is undefined.
*/
CF_EXPORT
void CFCharacterSetRemoveCharactersInString(CFMutableCharacterSetRef theSet, CFStringRef theString);

/*!
	@function CFCharacterSetUnion
	Forms the union with the given character set.
	@param theSet The destination character set into which the
                union of the two character sets is stored.  If this
                parameter is not a valid mutable CFCharacterSet, the
                behavior is undefined.
	@param theOtherSet The character set with which the union is
                formed.  If this parameter is not a valid CFCharacterSet,
                the behavior is undefined.
*/
CF_EXPORT
void CFCharacterSetUnion(CFMutableCharacterSetRef theSet, CFCharacterSetRef theOtherSet);

/*!
	@function CFCharacterSetIntersect
	Forms the intersection with the given character set.
	@param theSet The destination character set into which the
                intersection of the two character sets is stored.
                If this parameter is not a valid mutable CFCharacterSet,
                the behavior is undefined.
	@param theOtherSet The character set with which the intersection
                is formed.  If this parameter is not a valid CFCharacterSet,
                the behavior is undefined.
*/
CF_EXPORT
void CFCharacterSetIntersect(CFMutableCharacterSetRef theSet, CFCharacterSetRef theOtherSet);

/*!
	@function CFCharacterSetInvert
	Inverts the content of the given character set.
	@param theSet The character set to be inverted.
                If this parameter is not a valid mutable CFCharacterSet,
                the behavior is undefined.
*/
CF_EXPORT
void CFCharacterSetInvert(CFMutableCharacterSetRef theSet);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFCHARACTERSET__ */

// ==========  CoreFoundation.framework/Headers/CFDateFormatter.h
/*	CFDateFormatter.h
	Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFDATEFORMATTER__)
#define __COREFOUNDATION_CFDATEFORMATTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFLocale.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFDateFormatter *CFDateFormatterRef;

// CFDateFormatters are not thread-safe.  Do not use one from multiple threads!

CF_EXPORT
CFStringRef CFDateFormatterCreateDateFormatFromTemplate(CFAllocatorRef allocator, CFStringRef tmplate, CFOptionFlags options, CFLocaleRef locale) CF_AVAILABLE(10_6, 4_0);
	// no options defined, pass 0 for now

CF_EXPORT
CFTypeID CFDateFormatterGetTypeID(void);

typedef CF_ENUM(CFIndex, CFDateFormatterStyle) {	// date and time format styles
	kCFDateFormatterNoStyle = 0,
	kCFDateFormatterShortStyle = 1,
	kCFDateFormatterMediumStyle = 2,
	kCFDateFormatterLongStyle = 3,
	kCFDateFormatterFullStyle = 4
};

// The exact formatted result for these date and time styles depends on the
// locale, but generally:
//     Short is completely numeric, such as "12/13/52" or "3:30pm"
//     Medium is longer, such as "Jan 12, 1952"
//     Long is longer, such as "January 12, 1952" or "3:30:32pm"
//     Full is pretty complete; e.g. "Tuesday, April 12, 1952 AD" or "3:30:42pm PST"
// The specifications though are left fuzzy, in part simply because a user's
// preference choices may affect the output, and also the results may change
// from one OS release to another.  To produce an exactly formatted date you
// should not rely on styles and localization, but set the format string and
// use nothing but numbers.

CF_EXPORT
CFDateFormatterRef CFDateFormatterCreate(CFAllocatorRef allocator, CFLocaleRef locale, CFDateFormatterStyle dateStyle, CFDateFormatterStyle timeStyle);
	// Returns a CFDateFormatter, localized to the given locale, which
	// will format dates to the given date and time styles.

CF_EXPORT
CFLocaleRef CFDateFormatterGetLocale(CFDateFormatterRef formatter);

CF_EXPORT
CFDateFormatterStyle CFDateFormatterGetDateStyle(CFDateFormatterRef formatter);

CF_EXPORT
CFDateFormatterStyle CFDateFormatterGetTimeStyle(CFDateFormatterRef formatter);
	// Get the properties with which the date formatter was created.

CF_EXPORT
CFStringRef CFDateFormatterGetFormat(CFDateFormatterRef formatter);

CF_EXPORT
void CFDateFormatterSetFormat(CFDateFormatterRef formatter, CFStringRef formatString);
	// Set the format description string of the date formatter.  This
	// overrides the style settings.  The format of the format string
	// is as defined by the ICU library.  The date formatter starts with a
	// default format string defined by the style arguments with
	// which it was created.


CF_EXPORT
CFStringRef CFDateFormatterCreateStringWithDate(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFDateRef date);

CF_EXPORT
CFStringRef CFDateFormatterCreateStringWithAbsoluteTime(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFAbsoluteTime at);
	// Create a string representation of the given date or CFAbsoluteTime
	// using the current state of the date formatter.


CF_EXPORT
CFDateRef CFDateFormatterCreateDateFromString(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFStringRef string, CFRange *rangep);

CF_EXPORT
Boolean CFDateFormatterGetAbsoluteTimeFromString(CFDateFormatterRef formatter, CFStringRef string, CFRange *rangep, CFAbsoluteTime *atp);
	// Parse a string representation of a date using the current state
	// of the date formatter.  The range parameter specifies the range
	// of the string in which the parsing should occur in input, and on
	// output indicates the extent that was used; this parameter can
	// be NULL, in which case the whole string may be used.  The
	// return value indicates whether some date was computed and
	// (if atp is not NULL) stored at the location specified by atp.


CF_EXPORT
void CFDateFormatterSetProperty(CFDateFormatterRef formatter, CFStringRef key, CFTypeRef value);

CF_EXPORT
CFTypeRef CFDateFormatterCopyProperty(CFDateFormatterRef formatter, CFStringRef key);
	// Set and get various properties of the date formatter, the set of
	// which may be expanded in the future.

CF_EXPORT const CFStringRef kCFDateFormatterIsLenient;	// CFBoolean
CF_EXPORT const CFStringRef kCFDateFormatterTimeZone;		// CFTimeZone
CF_EXPORT const CFStringRef kCFDateFormatterCalendarName;	// CFString
CF_EXPORT const CFStringRef kCFDateFormatterDefaultFormat;	// CFString
CF_EXPORT const CFStringRef kCFDateFormatterTwoDigitStartDate; // CFDate
CF_EXPORT const CFStringRef kCFDateFormatterDefaultDate;	// CFDate
CF_EXPORT const CFStringRef kCFDateFormatterCalendar;		// CFCalendar
CF_EXPORT const CFStringRef kCFDateFormatterEraSymbols;	// CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterMonthSymbols;	// CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortMonthSymbols; // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterWeekdaySymbols;	// CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortWeekdaySymbols; // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterAMSymbol;		// CFString
CF_EXPORT const CFStringRef kCFDateFormatterPMSymbol;		// CFString
CF_EXPORT const CFStringRef kCFDateFormatterLongEraSymbols CF_AVAILABLE(10_5, 2_0);   // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterVeryShortMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterVeryShortStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterVeryShortWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterVeryShortStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterQuarterSymbols CF_AVAILABLE(10_5, 2_0); 	// CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterStandaloneQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterShortStandaloneQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFStringRef kCFDateFormatterGregorianStartDate CF_AVAILABLE(10_5, 2_0); // CFDate
CF_EXPORT const CFStringRef kCFDateFormatterDoesRelativeDateFormattingKey CF_AVAILABLE(10_6, 4_0); // CFBoolean

// See CFLocale.h for these calendar constants:
//	const CFStringRef kCFGregorianCalendar;
//	const CFStringRef kCFBuddhistCalendar;
//	const CFStringRef kCFJapaneseCalendar;
//	const CFStringRef kCFIslamicCalendar;
//	const CFStringRef kCFIslamicCivilCalendar;
//	const CFStringRef kCFHebrewCalendar;
//	const CFStringRef kCFChineseCalendar;
//	const CFStringRef kCFRepublicOfChinaCalendar;
//	const CFStringRef kCFPersianCalendar;
//	const CFStringRef kCFIndianCalendar;
//	const CFStringRef kCFISO8601Calendar;

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFDATEFORMATTER__ */

// ==========  CoreFoundation.framework/Headers/CFTree.h
/*	CFTree.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/
/*!
        @header CFTree
        CFTree implements a container which stores references to other CFTrees.
        Each tree may have a parent, and a variable number of children.
*/

#if !defined(__COREFOUNDATION_CFTREE__)
#define __COREFOUNDATION_CFTREE__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
        @typedef CFTreeRetainCallBack
        Type of the callback function used to add a retain to the user-specified
        info parameter.  This callback may returns the value to use whenever the
        info parameter is retained, which is usually the value parameter passed
        to this callback, but may be a different value if a different value
        should be used.
        @param info A user-supplied info parameter provided in a CFTreeContext.
        @result The retained info parameter.
*/
typedef const void *	(*CFTreeRetainCallBack)(const void *info);

/*!
        @typedef CFTreeReleaseCallBack
        Type of the callback function used to remove a retain previously
        added to the user-specified info parameter.
        @param info A user-supplied info parameter provided in a CFTreeContext.
*/
typedef void		(*CFTreeReleaseCallBack)(const void *info);

/*!
        @typedef CFTreeCopyDescriptionCallBack
        Type of the callback function used to provide a description of the
        user-specified info parameter.
        @param info A user-supplied info parameter provided in a CFTreeContext.
        @result A description of the info parameter.
*/
typedef CFStringRef	(*CFTreeCopyDescriptionCallBack)(const void *info);

/*!
        @typedef CFTreeContext
        Structure containing user-specified data and callbacks for a CFTree.
        @field version The version number of the structure type being passed
                in as a parameter to the CFTree creation function.
                This structure is version 0.
        @field info A C pointer to a user-specified block of data.
        @field retain The callback used to add a retain for the info field.
                If this parameter is not a pointer to a function of the correct
                prototype, the behavior is undefined.  The value may be NULL.
        @field release The calllback used to remove a retain previously added
                for the info field.  If this parameter is not a pointer to a 
                function of the correct prototype, the behavior is undefined.
                The value may be NULL.
        @field copyDescription The callback used to provide a description of
                the info field.
*/
typedef struct {
    CFIndex				version;
    void *				info;
    CFTreeRetainCallBack		retain;
    CFTreeReleaseCallBack		release;	
    CFTreeCopyDescriptionCallBack	copyDescription;
} CFTreeContext;

/*!
        @typedef CFTreeApplierFunction
        Type of the callback function used by the apply functions of
                CFTree.
        @param value The current value from the CFTree
        @param context The user-defined context parameter give to the apply
                function.
*/
typedef void (*CFTreeApplierFunction)(const void *value, void *context);

/*!
        @typedef CFTreeRef
        This is the type of a reference to CFTrees.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFTree * CFTreeRef;

/*!
        @function CFTreeGetTypeID
        Returns the type identifier of all CFTree instances.
*/
CF_EXPORT
CFTypeID CFTreeGetTypeID(void);

/*!
        @function CFTreeCreate
        Creates a new mutable tree.
        @param allocator The CFAllocator which should be used to allocate
                memory for the tree and storage for its children.  This
                parameter may be NULL in which case the current default
                CFAllocator is used.  If this reference is not a valid
                CFAllocator, the behavior is undefined.
        @param context A C pointer to a CFTreeContext structure to be copied 
                and used as the context of the new tree.  The info parameter
                will be retained by the tree if a retain function is provided.
                If this value is not a valid C pointer to a CFTreeContext 
                structure-sized block of storage, the result is undefined. 
                If the version number of the storage is not a valid CFTreeContext
                version number, the result is undefined.
        @result A reference to the new CFTree.
*/
CF_EXPORT
CFTreeRef CFTreeCreate(CFAllocatorRef allocator, const CFTreeContext *context);

/*!
        @function CFTreeGetParent
        Returns the parent of the specified tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @result The parent of the tree.
*/
CF_EXPORT
CFTreeRef CFTreeGetParent(CFTreeRef tree);

/*!
        @function CFTreeGetNextSibling
        Returns the sibling after the specified tree in the parent tree's list.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @result The next sibling of the tree.
*/
CF_EXPORT
CFTreeRef CFTreeGetNextSibling(CFTreeRef tree);

/*!
        @function CFTreeGetFirstChild
        Returns the first child of the tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @result The first child of the tree.
*/
CF_EXPORT
CFTreeRef CFTreeGetFirstChild(CFTreeRef tree);

/*!
        @function CFTreeGetContext
        Returns the context of the specified tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @param context A C pointer to a CFTreeContext structure to be filled in with
                the context of the specified tree.  If this value is not a valid C
                pointer to a CFTreeContext structure-sized block of storage, the
                result is undefined.  If the version number of the storage is not
                a valid CFTreeContext version number, the result is undefined.
*/
CF_EXPORT
void CFTreeGetContext(CFTreeRef tree, CFTreeContext *context);

/*!
        @function CFTreeGetChildCount
        Returns the number of children of the specified tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @result The number of children.
*/
CF_EXPORT
CFIndex CFTreeGetChildCount(CFTreeRef tree);

/*!
        @function CFTreeGetChildAtIndex
        Returns the nth child of the specified tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @param idx The index of the child tree to be returned.  If this parameter
                is less than zero or greater than the number of children of the
                tree, the result is undefined.
        @result A reference to the specified child tree.
*/
CF_EXPORT
CFTreeRef CFTreeGetChildAtIndex(CFTreeRef tree, CFIndex idx);

/*!
        @function CFTreeGetChildren
        Fills the buffer with children from the tree.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
	@param children A C array of pointer-sized values to be filled with
		children from the tree.  If this parameter is not a valid pointer to a 
                C array of at least CFTreeGetChildCount() pointers, the behavior is undefined.
        @result A reference to the specified child tree.
*/
CF_EXPORT
void CFTreeGetChildren(CFTreeRef tree, CFTreeRef *children);

/*!
	@function CFTreeApplyFunctionToChildren
	Calls a function once for each child of the tree.  Note that the applier
        only operates one level deep, and does not operate on descendents further
        removed than the immediate children of the tree.
        @param heap The tree to be operated upon.  If this parameter is not a
		valid CFTree, the behavior is undefined.
	@param applier The callback function to call once for each child of
		the given tree.  If this parameter is not a pointer to a 
                function of the correct prototype, the behavior is undefined.
                If there are values in the tree which the applier function does
                not expect or cannot properly apply to, the behavior is undefined.
	@param context A pointer-sized user-defined value, which is passed
		as the second parameter to the applier function, but is
		otherwise unused by this function.  If the context is not
		what is expected by the applier function, the behavior is
		undefined.
*/
CF_EXPORT
void CFTreeApplyFunctionToChildren(CFTreeRef tree, CFTreeApplierFunction applier, void *context);

/*!
        @function CFTreeFindRoot
        Returns the root tree of which the specified tree is a descendent.
        @param tree The tree to be queried.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @result A reference to the root of the tree.
*/
CF_EXPORT
CFTreeRef CFTreeFindRoot(CFTreeRef tree);

/*!
        @function CFTreeSetContext
        Replaces the context of a tree.  The tree releases its retain on the
        info of the previous context, and retains the info of the new context.
        @param tree The tree to be operated on.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @param context A C pointer to a CFTreeContext structure to be copied 
                and used as the context of the new tree.  The info parameter
                will be retained by the tree if a retain function is provided.
                If this value is not a valid C pointer to a CFTreeContext 
                structure-sized block of storage, the result is undefined. 
                If the version number of the storage is not a valid CFTreeContext
                version number, the result is undefined.
*/
CF_EXPORT
void CFTreeSetContext(CFTreeRef tree, const CFTreeContext *context);

/*!
        @function CFTreePrependChild
        Adds the newChild to the specified tree as the first in its list of children.
        @param tree The tree to be operated on.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @param newChild The child to be added.
                If this parameter is not a valid CFTree, the behavior is undefined.
                If this parameter is a tree which is already a child of any tree,
                the behavior is undefined.
*/
CF_EXPORT
void CFTreePrependChild(CFTreeRef tree, CFTreeRef newChild);

/*!
        @function CFTreeAppendChild
        Adds the newChild to the specified tree as the last in its list of children.
        @param tree The tree to be operated on.  If this parameter is not a valid
                CFTree, the behavior is undefined.
        @param newChild The child to be added.
                If this parameter is not a valid CFTree, the behavior is undefined.
                If this parameter is a tree which is already a child of any tree,
                the behavior is undefined.
*/
CF_EXPORT
void CFTreeAppendChild(CFTreeRef tree, CFTreeRef newChild);

/*!
        @function CFTreeInsertSibling
        Inserts newSibling into the the parent tree's linked list of children after
        tree.  The newSibling will have the same parent as tree.
        @param tree The tree to insert newSibling after.  If this parameter is not a valid
                CFTree, the behavior is undefined.  If the tree does not have a
                parent, the behavior is undefined.
        @param newSibling The sibling to be added.
                If this parameter is not a valid CFTree, the behavior is undefined.
                If this parameter is a tree which is already a child of any tree,
                the behavior is undefined.  
*/
CF_EXPORT
void CFTreeInsertSibling(CFTreeRef tree, CFTreeRef newSibling);

/*!
        @function CFTreeRemove
        Removes the tree from its parent.
        @param tree The tree to be removed.  If this parameter is not a valid
                CFTree, the behavior is undefined.
*/
CF_EXPORT
void CFTreeRemove(CFTreeRef tree);

/*!
        @function CFTreeRemoveAllChildren
        Removes all the children of the tree.
        @param tree The tree to remove all children from.  If this parameter is not a valid
                CFTree, the behavior is undefined.
*/
CF_EXPORT
void CFTreeRemoveAllChildren(CFTreeRef tree);

/*!
        @function CFTreeSortChildren
        Sorts the children of the specified tree using the specified comparator function.
        @param tree The tree to be operated on.  If this parameter is not a valid
                CFTree, the behavior is undefined.
	@param comparator The function with the comparator function type
		signature which is used in the sort operation to compare
		children of the tree with the given value. If this parameter
		is not a pointer to a function of the correct prototype, the
		the behavior is undefined. The children of the tree are sorted 
                from least to greatest according to this function.
	@param context A pointer-sized user-defined value, which is passed
		as the third parameter to the comparator function, but is
		otherwise unused by this function. If the context is not
		what is expected by the comparator function, the behavior is
		undefined.
*/
CF_EXPORT
void CFTreeSortChildren(CFTreeRef tree, CFComparatorFunction comparator, void *context);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFTREE__ */

// ==========  CoreFoundation.framework/Headers/CFMessagePort.h
/*	CFMessagePort.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFMESSAGEPORT__)
#define __COREFOUNDATION_CFMESSAGEPORT__ 1

#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFData.h>
#include <dispatch/dispatch.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMessagePort) __CFMessagePort * CFMessagePortRef;

CF_ENUM(SInt32) {
    kCFMessagePortSuccess = 0,
    kCFMessagePortSendTimeout = -1,
    kCFMessagePortReceiveTimeout = -2,
    kCFMessagePortIsInvalid = -3,
    kCFMessagePortTransportError = -4,
    kCFMessagePortBecameInvalidError = -5
};

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFMessagePortContext;

typedef CFDataRef (*CFMessagePortCallBack)(CFMessagePortRef local, SInt32 msgid, CFDataRef data, void *info);
/* If callout wants to keep a hold of the data past the return of the callout, it must COPY the data. This includes the case where the data is given to some routine which _might_ keep a hold of it; System will release returned CFData. */
typedef void (*CFMessagePortInvalidationCallBack)(CFMessagePortRef ms, void *info);

CF_EXPORT CFTypeID	CFMessagePortGetTypeID(void);

CF_EXPORT CFMessagePortRef	CFMessagePortCreateLocal(CFAllocatorRef allocator, CFStringRef name, CFMessagePortCallBack callout, CFMessagePortContext *context, Boolean *shouldFreeInfo);
CF_EXPORT CFMessagePortRef	CFMessagePortCreateRemote(CFAllocatorRef allocator, CFStringRef name);

CF_EXPORT Boolean	CFMessagePortIsRemote(CFMessagePortRef ms);
CF_EXPORT CFStringRef	CFMessagePortGetName(CFMessagePortRef ms);
CF_EXPORT Boolean	CFMessagePortSetName(CFMessagePortRef ms, CFStringRef newName);
CF_EXPORT void		CFMessagePortGetContext(CFMessagePortRef ms, CFMessagePortContext *context);
CF_EXPORT void		CFMessagePortInvalidate(CFMessagePortRef ms);
CF_EXPORT Boolean	CFMessagePortIsValid(CFMessagePortRef ms);
CF_EXPORT CFMessagePortInvalidationCallBack CFMessagePortGetInvalidationCallBack(CFMessagePortRef ms);
CF_EXPORT void CFMessagePortSetInvalidationCallBack(CFMessagePortRef ms, CFMessagePortInvalidationCallBack callout);

/* NULL replyMode argument means no return value expected, dont wait for it */
CF_EXPORT SInt32	CFMessagePortSendRequest(CFMessagePortRef remote, SInt32 msgid, CFDataRef data, CFTimeInterval sendTimeout, CFTimeInterval rcvTimeout, CFStringRef replyMode, CFDataRef *returnData);

CF_EXPORT CFRunLoopSourceRef	CFMessagePortCreateRunLoopSource(CFAllocatorRef allocator, CFMessagePortRef local, CFIndex order);

CF_EXPORT void CFMessagePortSetDispatchQueue(CFMessagePortRef ms, dispatch_queue_t queue) CF_AVAILABLE(10_6, 4_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFMESSAGEPORT__ */

// ==========  CoreFoundation.framework/Headers/CFURLEnumerator.h
/*
    CFURLEnumerator.h
    Copyright (c) 2008-2015, Apple Inc. All rights reserved.
 */

#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || CF_BUILDING_CF || NSBUILDINGFOUNDATION

#if !defined(__COREFOUNDATION_CFURLENUMERATOR__)
#define __COREFOUNDATION_CFURLENUMERATOR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN


typedef const struct CF_BRIDGED_MUTABLE_TYPE(id) __CFURLEnumerator *CFURLEnumeratorRef;

/* CFURLEnumeratorGetTypeID - Returns the CFURLEnumerator CFTypeID. */
CF_EXPORT
CFTypeID CFURLEnumeratorGetTypeID( void ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorOptions - Options for controlling enumerator behavior. */
typedef CF_OPTIONS(CFOptionFlags, CFURLEnumeratorOptions) {
    kCFURLEnumeratorDefaultBehavior                 = 0,        /* Use the default behavior for the enumerator. */
    kCFURLEnumeratorDescendRecursively              = 1UL << 0, /* The directory enumerator will recurse ("depth-first") into each subdirectory enumerated */
    kCFURLEnumeratorSkipInvisibles                  = 1UL << 1, /* The directory or volume enumerator skips "hidden" or "invisible" objects */
    kCFURLEnumeratorGenerateFileReferenceURLs       = 1UL << 2, /* The volume enumerator generates file reference URLs */
    kCFURLEnumeratorSkipPackageContents             = 1UL << 3, /* The directory enumerator skips package directory contents */
    kCFURLEnumeratorIncludeDirectoriesPreOrder      = 1UL << 4, /* With this option set, a recursive directory enumerator will return directory URLs when CFURLEnumeratorGetNextURL() returns kCFURLEnumeratorSuccess before any of the directory's descendants are visited (pre-order). */
    kCFURLEnumeratorIncludeDirectoriesPostOrder     = 1UL << 5, /* With this option set, a recursive directory enumerator will return directory URLs when CFURLEnumeratorGetNextURL() returns kCFURLEnumeratorDirectoryPostOrderSuccess after all of directory's descendants have been visited (post-order). */
    /* Note: if both kCFURLEnumeratorIncludeDirectoriesPreOrder and kCFURLEnumeratorIncludeDirectoriesPostOrder are used, directories will be seen twice (even empty directories and directories whose descendants are skipped) -- once when kCFURLEnumeratorSuccess is returned and once when kCFURLEnumeratorDirectoryPostOrderSuccess is returned. */
};

/* CFURLEnumeratorCreateForDirectoryURL - Creates a directory enumerator, flat or recursive. Client specifies the directory URL to enumerate, a bit array of options, and an optional array of property keys to pre-fetch for the found URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A directory enumerator generates URLs with the same type as the directory URL being enumerated. If the directoryURL input parameter is a file reference URL, then generated URLs will be file reference URLs. If the directoryURL input parameter is a file path URL, then generated URLs will be file path URLs.

The kCFURLEnumeratorGenerateFileReferenceURLs option is ignored by CFURLEnumeratorCreateForDirectoryURL.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForDirectoryURL( CFAllocatorRef alloc, CFURLRef directoryURL, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorCreateForMountedVolumes - Creates an enumerator for mounted filesystem volumes. Client specifies an allocator, a bit array of options, and an optional array of property keys to pre-fetch for the volume URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A volume enumerator generates file path URLs. If you want a volume enumerator to generate file reference URLs, pass the kCFURLEnumeratorGenerateFileReferenceURLs option.

The kCFURLEnumeratorDescendRecursively and kCFURLEnumeratorSkipPackageContents options are ignored by CFURLEnumeratorCreateForMountedVolumes.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForMountedVolumes( CFAllocatorRef alloc, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorResult - Results for CFURLEnumeratorGetNextURL */
typedef CF_ENUM(CFIndex, CFURLEnumeratorResult) {
    kCFURLEnumeratorSuccess = 1,                    /* The enumeration was successful. The url output parameter is valid. */
    kCFURLEnumeratorEnd = 2,                        /* The enumeration is complete. */
    kCFURLEnumeratorError = 3,			    /* An error occured during enumeration. The retained error output parameter describes the error. */
    kCFURLEnumeratorDirectoryPostOrderSuccess = 4,  /* The enumeration was successful. The url output parameter is for a directory after all of directory's descendants have been visited (post-order). This result will only be returned for directories when both the kCFURLEnumeratorDescendRecursively and kCFURLEnumeratorIncludeDirectoriesPostOrder options are passed to CFURLEnumeratorCreateForDirectoryURL. */
};

/* CFURLEnumeratorGetNextURL - Advances the enumerator. If kCFURLEnumeratorSuccess is returned, the url output parameter returns the next URL found. If kCFURLEnumeratorError is returned, an error has occured and the error output parameter describes the error. If kCFURLEnumeratorEnd, the enumeration is finished.

The url output parameter, if returned, is not retained. The error output parameter, if returned, is retained and must be released.
*/
CF_EXPORT
CFURLEnumeratorResult CFURLEnumeratorGetNextURL( CFURLEnumeratorRef enumerator, CFURLRef *url, CFErrorRef *error ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorSkipDescendents - Tells a recursive CFURLEnumerator not to descend into the directory of the last CFURLRef returned by CFURLEnumeratorGetNextURL.

Calls to CFURLEnumeratorSkipDescendents are ignored if:
    * CFURLEnumeratorGetNextURL has never been called with the CFURLEnumerator.
    * The last CFURL returned by CFURLEnumeratorGetNextURL is not a directory.
    * The CFURLEnumerator was not created with CFURLEnumeratorCreateForDirectoryURL using the kCFURLEnumeratorDescendRecursively option.
*/
CF_EXPORT
void CFURLEnumeratorSkipDescendents( CFURLEnumeratorRef enumerator ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorGetDescendentLevel - Returns the number of levels a directory enumerator has descended down into the directory hierarchy from the starting directory. The children of the starting directory are at level 1. Each time a recursive enumerator descends into a subdirectory, it adds one to the descendent level. It then subtracts one from the level when it finishes a subdirectory and continues enumerating the parent directory.
*/
CF_EXPORT
CFIndex CFURLEnumeratorGetDescendentLevel( CFURLEnumeratorRef enumerator ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorGetSourceDidChange is deprecated. If your program is interested in directory hierarchy changes during enumeration (and most programs are not interested), you should use the File System Events API.
 
 CFURLEnumeratorGetSourceDidChange does nothing and always returns false.
 */
CF_EXPORT
Boolean CFURLEnumeratorGetSourceDidChange( CFURLEnumeratorRef enumerator ) CF_DEPRECATED(10_6, 10_7, 4_0, 5_0);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFURLENUMERATOR__ */

#endif

// ==========  CoreFoundation.framework/Headers/CFMachPort.h
/*	CFMachPort.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFMACHPORT__)
#define __COREFOUNDATION_CFMACHPORT__ 1

#include <CoreFoundation/CFRunLoop.h>
#include <mach/port.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMachPort) __CFMachPort * CFMachPortRef;

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFMachPortContext;

typedef void (*CFMachPortCallBack)(CFMachPortRef port, void *msg, CFIndex size, void *info);
typedef void (*CFMachPortInvalidationCallBack)(CFMachPortRef port, void *info);

CF_EXPORT CFTypeID	CFMachPortGetTypeID(void);

CF_EXPORT CFMachPortRef	CFMachPortCreate(CFAllocatorRef allocator, CFMachPortCallBack callout, CFMachPortContext *context, Boolean *shouldFreeInfo);
CF_EXPORT CFMachPortRef	CFMachPortCreateWithPort(CFAllocatorRef allocator, mach_port_t portNum, CFMachPortCallBack callout, CFMachPortContext *context, Boolean *shouldFreeInfo);

CF_EXPORT mach_port_t	CFMachPortGetPort(CFMachPortRef port);
CF_EXPORT void		CFMachPortGetContext(CFMachPortRef port, CFMachPortContext *context);
CF_EXPORT void		CFMachPortInvalidate(CFMachPortRef port);
CF_EXPORT Boolean	CFMachPortIsValid(CFMachPortRef port);
CF_EXPORT CFMachPortInvalidationCallBack CFMachPortGetInvalidationCallBack(CFMachPortRef port);
CF_EXPORT void		CFMachPortSetInvalidationCallBack(CFMachPortRef port, CFMachPortInvalidationCallBack callout);

CF_EXPORT CFRunLoopSourceRef	CFMachPortCreateRunLoopSource(CFAllocatorRef allocator, CFMachPortRef port, CFIndex order);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFMACHPORT__ */

// ==========  CoreFoundation.framework/Headers/CFPlugInCOM.h
/*	CFPlugInCOM.h
	Copyright (c) 1999-2015, Apple Inc.  All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFPLUGINCOM__)
#define __COREFOUNDATION_CFPLUGINCOM__ 1

#include <CoreFoundation/CFPlugIn.h>

CF_EXTERN_C_BEGIN

/* ================= IUnknown definition (C struct) ================= */

/* All interface structs must have an IUnknownStruct at the beginning. */
/* The _reserved field is part of the Microsoft COM binary standard on Macintosh. */
/* You can declare new C struct interfaces by defining a new struct that includes "IUNKNOWN_C_GUTS;" before the first field of the struct. */

typedef SInt32 HRESULT;
typedef UInt32 ULONG;
typedef void *LPVOID;
typedef CFUUIDBytes REFIID;

#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#define FAILED(Status) ((HRESULT)(Status)<0)

/* Macros for more detailed HRESULT analysis */
#define IS_ERROR(Status) ((unsigned long)(Status) >> 31 == SEVERITY_ERROR)
#define HRESULT_CODE(hr) ((hr) & 0xFFFF)
#define HRESULT_FACILITY(hr) (((hr) >> 16) & 0x1fff)
#define HRESULT_SEVERITY(hr) (((hr) >> 31) & 0x1)
#define SEVERITY_SUCCESS 0
#define SEVERITY_ERROR 1

/* Creating an HRESULT from its component pieces */
#define MAKE_HRESULT(sev,fac,code) ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )

/* Pre-defined success HRESULTS */
#define S_OK ((HRESULT)0x00000000L)
#define S_FALSE ((HRESULT)0x00000001L)

/* Common error HRESULTS */
#define E_UNEXPECTED ((HRESULT)0x8000FFFFL)
#define E_NOTIMPL ((HRESULT)0x80000001L)
#define E_OUTOFMEMORY ((HRESULT)0x80000002L)
#define E_INVALIDARG ((HRESULT)0x80000003L)
#define E_NOINTERFACE ((HRESULT)0x80000004L)
#define E_POINTER ((HRESULT)0x80000005L)
#define E_HANDLE ((HRESULT)0x80000006L)
#define E_ABORT ((HRESULT)0x80000007L)
#define E_FAIL ((HRESULT)0x80000008L)
#define E_ACCESSDENIED ((HRESULT)0x80000009L)

/* This macro should be used when defining all interface functions (as it is for the IUnknown functions below). */
#define STDMETHODCALLTYPE

/* The __RPC_FAR macro is for COM source compatibility only. This macro is used a lot in COM interface definitions.  If your CFPlugIn interfaces need to be COM interfaces as well, you can use this macro to get better source compatibility.  It is not used in the IUnknown definition below, because when doing COM, you will be using the Microsoft supplied IUnknown interface anyway. */
#define __RPC_FAR

/* The IUnknown interface */
#define IUnknownUUID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorSystemDefault, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46)

#if __clang__
#define __PRAGMA_PUSH_NO_NULLABILITY_COMPLETENESS_WARNINGS _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wnullability-completeness\"")
#define __PRAGMA_POP_NO_NULLABILITY_COMPLETENESS_WARNINGS _Pragma("clang diagnostic pop")
#else
#define __PRAGMA_PUSH_NO_NULLABILITY_COMPLETENESS_WARNINGS
#define __PRAGMA_POP_NO_NULLABILITY_COMPLETENESS_WARNINGS
#endif

#define IUNKNOWN_C_GUTS \
    __PRAGMA_PUSH_NO_NULLABILITY_COMPLETENESS_WARNINGS \
    void *_reserved; \
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(void *thisPointer, REFIID iid, LPVOID *ppv); \
    ULONG (STDMETHODCALLTYPE *AddRef)(void *thisPointer); \
    ULONG (STDMETHODCALLTYPE *Release)(void *thisPointer) \
    __PRAGMA_POP_NO_NULLABILITY_COMPLETENESS_WARNINGS
    
typedef struct IUnknownVTbl {
    IUNKNOWN_C_GUTS;
} IUnknownVTbl;

CF_EXTERN_C_END


/* C++ specific stuff */
#if defined(__cplusplus)
/* ================= IUnknown definition (C++ class) ================= */

/* This is a definition of IUnknown as a pure abstract virtual C++ class.  This class will work only with compilers that can produce COM-compatible object layouts for C++ classes.  egcs can not do this.  MetroWerks can do this (if you subclass from __comobject) */

class IUnknown
#if defined(__MWERKS__) && TARGET_OS_WIN32
 : __comobject
#endif
{
    public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;
};

#endif /* __cplusplus */

#endif /* ! __COREFOUNDATION_CFPLUGINCOM__ */

// ==========  CoreFoundation.framework/Headers/CFPlugIn.h
/*	CFPlugIn.h
	Copyright (c) 1999-2015, Apple Inc.  All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFPLUGIN__)
#define __COREFOUNDATION_CFPLUGIN__ 1

#if !defined(COREFOUNDATION_CFPLUGINCOM_SEPARATE)
#define COREFOUNDATION_CFPLUGINCOM_SEPARATE 1
#endif

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFUUID.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/* ================ Standard Info.plist keys for plugIns ================ */

CF_EXPORT const CFStringRef kCFPlugInDynamicRegistrationKey;
CF_EXPORT const CFStringRef kCFPlugInDynamicRegisterFunctionKey;
CF_EXPORT const CFStringRef kCFPlugInUnloadFunctionKey;
CF_EXPORT const CFStringRef kCFPlugInFactoriesKey;
CF_EXPORT const CFStringRef kCFPlugInTypesKey;

/* ================= Function prototypes for various callbacks ================= */
/* Function types that plugIn authors can implement for various purposes. */

typedef void (*CFPlugInDynamicRegisterFunction)(CFPlugInRef plugIn);
typedef void (*CFPlugInUnloadFunction)(CFPlugInRef plugIn);
typedef void *(*CFPlugInFactoryFunction)(CFAllocatorRef allocator, CFUUIDRef typeUUID);

/* ================= Creating PlugIns ================= */

CF_EXPORT CFTypeID CFPlugInGetTypeID(void);

CF_EXPORT CFPlugInRef CFPlugInCreate(CFAllocatorRef allocator, CFURLRef plugInURL);
    /* Might return an existing instance with the ref-count bumped. */

CF_EXPORT CFBundleRef CFPlugInGetBundle(CFPlugInRef plugIn);

/* ================= Controlling load on demand ================= */
/* For plugIns. */
/* PlugIns that do static registration are load on demand by default. */
/* PlugIns that do dynamic registration are not load on demand by default. */
/* A dynamic registration function can call CFPlugInSetLoadOnDemand(). */

CF_EXPORT void CFPlugInSetLoadOnDemand(CFPlugInRef plugIn, Boolean flag);

CF_EXPORT Boolean CFPlugInIsLoadOnDemand(CFPlugInRef plugIn);

/* ================= Finding factories and creating instances ================= */
/* For plugIn hosts. */
/* Functions for finding factories to create specific types and actually creating instances of a type. */

/* This function finds all the factories from any plugin for the given type.  Returns an array that the caller must release. */
CF_EXPORT CFArrayRef CFPlugInFindFactoriesForPlugInType(CFUUIDRef typeUUID) CF_RETURNS_RETAINED;


/* This function restricts the result to factories from the given plug-in that can create the given type.  Returns an array that the caller must release. */
CF_EXPORT CFArrayRef CFPlugInFindFactoriesForPlugInTypeInPlugIn(CFUUIDRef typeUUID, CFPlugInRef plugIn) CF_RETURNS_RETAINED;

/* This function returns the IUnknown interface for the new instance. */
CF_EXPORT void *CFPlugInInstanceCreate(CFAllocatorRef allocator, CFUUIDRef factoryUUID, CFUUIDRef typeUUID);

/* ================= Registering factories and types ================= */
/* For plugIn writers who must dynamically register things. */
/* Functions to register factory functions and to associate factories with types. */

CF_EXPORT Boolean CFPlugInRegisterFactoryFunction(CFUUIDRef factoryUUID, CFPlugInFactoryFunction func);

CF_EXPORT Boolean CFPlugInRegisterFactoryFunctionByName(CFUUIDRef factoryUUID, CFPlugInRef plugIn, CFStringRef functionName);

CF_EXPORT Boolean CFPlugInUnregisterFactory(CFUUIDRef factoryUUID);

CF_EXPORT Boolean CFPlugInRegisterPlugInType(CFUUIDRef factoryUUID, CFUUIDRef typeUUID);

CF_EXPORT Boolean CFPlugInUnregisterPlugInType(CFUUIDRef factoryUUID, CFUUIDRef typeUUID);

/* ================= Registering instances ================= */
/* When a new instance of a type is created, the instance is responsible for registering itself with the factory that created it and unregistering when it deallocates. */
/* This means that an instance must keep track of the CFUUIDRef of the factory that created it so it can unregister when it goes away. */

CF_EXPORT void CFPlugInAddInstanceForFactory(CFUUIDRef factoryID);

CF_EXPORT void CFPlugInRemoveInstanceForFactory(CFUUIDRef factoryID);


/* Obsolete API */

typedef struct CF_BRIDGED_TYPE(id) __CFPlugInInstance *CFPlugInInstanceRef;

typedef Boolean (*CFPlugInInstanceGetInterfaceFunction)(CFPlugInInstanceRef instance, CFStringRef interfaceName, void **ftbl);
typedef void (*CFPlugInInstanceDeallocateInstanceDataFunction)(void *instanceData);

CF_EXPORT Boolean CFPlugInInstanceGetInterfaceFunctionTable(CFPlugInInstanceRef instance, CFStringRef interfaceName, void **ftbl);

/* This function returns a retained object on 10.8 or later. */
CF_EXPORT CFStringRef CFPlugInInstanceGetFactoryName(CFPlugInInstanceRef instance) CF_RETURNS_RETAINED;

CF_EXPORT void *CFPlugInInstanceGetInstanceData(CFPlugInInstanceRef instance);

CF_EXPORT CFTypeID CFPlugInInstanceGetTypeID(void);

CF_EXPORT CFPlugInInstanceRef CFPlugInInstanceCreateWithInstanceDataSize(CFAllocatorRef allocator, CFIndex instanceDataSize, CFPlugInInstanceDeallocateInstanceDataFunction deallocateInstanceFunction, CFStringRef factoryName, CFPlugInInstanceGetInterfaceFunction getInterfaceFunction);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#if !COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif /* !COREFOUNDATION_CFPLUGINCOM_SEPARATE */

#endif /* ! __COREFOUNDATION_CFPLUGIN__ */

// ==========  CoreFoundation.framework/Headers/CFDate.h
/*	CFDate.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFDATE__)
#define __COREFOUNDATION_CFDATE__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef double CFTimeInterval;
typedef CFTimeInterval CFAbsoluteTime;
/* absolute time is the time interval since the reference date */
/* the reference date (epoch) is 00:00:00 1 January 2001. */

CF_EXPORT
CFAbsoluteTime CFAbsoluteTimeGetCurrent(void);

CF_EXPORT
const CFTimeInterval kCFAbsoluteTimeIntervalSince1970;
CF_EXPORT
const CFTimeInterval kCFAbsoluteTimeIntervalSince1904;

typedef const struct CF_BRIDGED_TYPE(NSDate) __CFDate * CFDateRef;

CF_EXPORT
CFTypeID CFDateGetTypeID(void);

CF_EXPORT
CFDateRef CFDateCreate(CFAllocatorRef allocator, CFAbsoluteTime at);

CF_EXPORT
CFAbsoluteTime CFDateGetAbsoluteTime(CFDateRef theDate);

CF_EXPORT
CFTimeInterval CFDateGetTimeIntervalSinceDate(CFDateRef theDate, CFDateRef otherDate);

CF_EXPORT
CFComparisonResult CFDateCompare(CFDateRef theDate, CFDateRef otherDate, void *context);

CF_IMPLICIT_BRIDGING_DISABLED

typedef const struct CF_BRIDGED_TYPE(NSTimeZone) __CFTimeZone * CFTimeZoneRef;


#if !defined(CF_CALENDAR_ENUM_DEPRECATED)
#if 1 || NS_ENABLE_CALENDAR_DEPRECATIONS
#define CF_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) CF_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define CF_CALENDAR_DEPRECATED(A, B, C, D, ...) CF_DEPRECATED(A, B, C, D, __VA_ARGS__)
#else
#define CF_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) CF_ENUM_AVAILABLE(A, C)
#define CF_CALENDAR_DEPRECATED(A, B, C, D, ...) CF_AVAILABLE(A, C)
#endif
#endif

typedef struct {
    SInt32 year;
    SInt8 month;
    SInt8 day;
    SInt8 hour;
    SInt8 minute;
    double second;
} CFGregorianDate CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

typedef struct {
    SInt32 years;
    SInt32 months;
    SInt32 days;
    SInt32 hours;
    SInt32 minutes;
    double seconds;
} CFGregorianUnits CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

typedef CF_OPTIONS(CFOptionFlags, CFGregorianUnitFlags) {
    kCFGregorianUnitsYears CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 0),
    kCFGregorianUnitsMonths CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 1),
    kCFGregorianUnitsDays CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 2),
    kCFGregorianUnitsHours CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 3),
    kCFGregorianUnitsMinutes CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 4),
    kCFGregorianUnitsSeconds CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = (1UL << 5),
    kCFGregorianAllUnits CF_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead") = 0x00FFFFFF
};

CF_EXPORT
Boolean CFGregorianDateIsValid(CFGregorianDate gdate, CFOptionFlags unitFlags) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
CFAbsoluteTime CFGregorianDateGetAbsoluteTime(CFGregorianDate gdate, CFTimeZoneRef tz) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
CFGregorianDate CFAbsoluteTimeGetGregorianDate(CFAbsoluteTime at, CFTimeZoneRef tz) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
CFAbsoluteTime CFAbsoluteTimeAddGregorianUnits(CFAbsoluteTime at, CFTimeZoneRef tz, CFGregorianUnits units) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
CFGregorianUnits CFAbsoluteTimeGetDifferenceAsGregorianUnits(CFAbsoluteTime at1, CFAbsoluteTime at2, CFTimeZoneRef tz, CFOptionFlags unitFlags) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
SInt32 CFAbsoluteTimeGetDayOfWeek(CFAbsoluteTime at, CFTimeZoneRef tz) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
SInt32 CFAbsoluteTimeGetDayOfYear(CFAbsoluteTime at, CFTimeZoneRef tz) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXPORT
SInt32 CFAbsoluteTimeGetWeekOfYear(CFAbsoluteTime at, CFTimeZoneRef tz) CF_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use CFCalendar or NSCalendar API instead");

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFDATE__ */

// ==========  CoreFoundation.framework/Headers/CFStringTokenizer.h
/*	CFStringTokenizer.h
	Copyright (c) 2006-2015, Apple Inc. All rights reserved.
*/

/*!
    @header CFStringTokenizer
    @abstract A CFStringTokenizer object provides the means by which you can
		tokenize a string. To find a token that includes the character
		specified by character index and set it as the current token, you call
		CFStringTokenizerGoToTokenAtIndex. To advance to the next token and set
		it as the current token, you call CFStringTokenizerAdvanceToNextToken.
		To get the range of current token, you call
		CFStringTokenizerGetCurrentTokenRange. You can use
		CFStringTokenizerCopyCurrentTokenAttribute to get the attribute of
		current token. If current token is a compound, you can call
		CFStringTokenizerGetCurrentSubTokens to retrieve the subtokens or derived
		subtokens contained in the compound token.
		To guess the language of a string, you call 
		CFStringTokenizerCopyBestStringLanguage.
*/

#if !defined(__COREFOUNDATION_CFSTRINGTOKENIZER__)
#define __COREFOUNDATION_CFSTRINGTOKENIZER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*
===================================================================
	Language Identifier
===================================================================
*/

/*!
	@function CFStringTokenizerCopyBestStringLanguage
	@abstract Guesses the language of a string and returns the BCP 47 string of the
		language.
	@param string The string whose language is to be guessed.
	@param range The range of characters in string whose language to be
		guessed. The specified range must not exceed the bounds of the string.
		If the range is empty (length 0), the first few hundred characters in
		the string are used.
	@result A language represented in BCP 47 string, or NULL if the
		language of the string cannot be guessed. 
	@discussion The result is not guaranteed to be accurate. Typically 200-400
		characters are required to reliably guess the language of a string.
*/
CF_EXPORT
CFStringRef CFStringTokenizerCopyBestStringLanguage(CFStringRef string, CFRange range) CF_AVAILABLE(10_5, 3_0);

/*
===================================================================
	Tokenization
===================================================================
*/

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFStringTokenizer * CFStringTokenizerRef;

/*!
	Tokenization options
*/
CF_ENUM(CFOptionFlags) {
    /*!
      Tokenization Unit
      Use one of tokenization unit options with CFStringTokenizerCreate to
      specify how the string should be tokenized. 
    */
    /* kCFStringTokenizerUnitWord doesn't return space between words as a token. */
    kCFStringTokenizerUnitWord                           = 0,
    kCFStringTokenizerUnitSentence                       = 1,
    kCFStringTokenizerUnitParagraph                      = 2,
    kCFStringTokenizerUnitLineBreak                      = 3,
    /* kCFStringTokenizerUnitWordBoundary can be used in double click detection
    and whole word search. It is locale sensitive. If the locale parameter of
    CFStringTokenizerCreate is NULL, default locale is used.
    kCFStringTokenizerUnitWordBoundary returns space between words as a token. */
    kCFStringTokenizerUnitWordBoundary                   = 4,

    /*!
      Attribute Specifier
      Use attribute specifier to tell tokenizer to prepare the specified attribute
      when it tokenizes the given string. The attribute value can be retrieved by
      calling CFStringTokenizerCopyCurrentTokenAttribute with one of the attribute
      option. 
    */
    /* Latin Transcription. Used with kCFStringTokenizerUnitWord or
       kCFStringTokenizerUnitWordBoundary */
    kCFStringTokenizerAttributeLatinTranscription        = 1UL << 16,
    /* Language in BCP 47 string. Used with kCFStringTokenizerUnitSentence
	   or kCFStringTokenizerUnitParagraph. */
    kCFStringTokenizerAttributeLanguage                  = 1UL << 17,
};

/*!
	Token type
	CFStringTokenizerGoToTokenAtIndex / CFStringTokenizerAdvanceToNextToken returns
	the type of current token.
*/
typedef CF_OPTIONS(CFOptionFlags, CFStringTokenizerTokenType) {
    /* Have no token. */
    kCFStringTokenizerTokenNone                                      = 0,
    
    /* Normal token */
    kCFStringTokenizerTokenNormal                                    = 1UL << 0,
    
    /*!
        Compound token which may contain subtokens but with no derived subtokens.
        Its subtokens can be obtained by calling CFStringTokenizerGetCurrentSubTokens.
    */
    kCFStringTokenizerTokenHasSubTokensMask                          = 1UL << 1,
    
    /*!
        Compound token which may contain derived subtokens.
        Its subtokens and derived subtokens can be obtained by calling
        CFStringTokenizerGetCurrentSubTokens.
    */
    kCFStringTokenizerTokenHasDerivedSubTokensMask                   = 1UL << 2,
    
    kCFStringTokenizerTokenHasHasNumbersMask                         = 1UL << 3,
    kCFStringTokenizerTokenHasNonLettersMask                         = 1UL << 4,
    kCFStringTokenizerTokenIsCJWordMask                              = 1UL << 5
};

/*!
	@function CFStringTokenizerGetTypeID
	@abstract Get the type identifier.
	@result the type identifier of all CFStringTokenizer instances.
*/
CF_EXPORT
CFTypeID CFStringTokenizerGetTypeID(void) CF_AVAILABLE(10_5, 3_0);
																				
/*!
	@function CFStringTokenizerCreate
	@abstract Creates a tokenizer instance.
	@param alloc The CFAllocator which should be used to allocate memory for the
		tokenizer and its storage for values. This parameter may be NULL in which 
		case the current default CFAllocator is used. 	
	@param string The string to tokenize.
	@param range The range of characters within the string to be tokenized. The
		specified range must not exceed the length of the string.
	@param options Use one of the Tokenization Unit options to specify how the 
		string should be tokenized. Optionally specify one or more attribute
		specifiers to tell the tokenizer to prepare specified attributes when it
		tokenizes the string.
	@param locale The locale to specify language or region specific behavior. Pass
               NULL if you want tokenizer to identify the locale automatically.
	@result A reference to the new CFStringTokenizer.
*/
CF_EXPORT
CFStringTokenizerRef CFStringTokenizerCreate(CFAllocatorRef alloc, CFStringRef string, CFRange range, CFOptionFlags options, CFLocaleRef locale) CF_AVAILABLE(10_5, 3_0);

/*!
	@function CFStringTokenizerSetString
	@abstract Set the string to tokenize.
	@param tokenizer The reference to CFStringTokenizer returned by
		CFStringTokenizerCreate.
	@param string The string to tokenize.
	@param range The range of characters within the string to be tokenized. The
		specified range must not exceed the length of the string.
*/
CF_EXPORT
void CFStringTokenizerSetString(CFStringTokenizerRef tokenizer, CFStringRef string, CFRange range) CF_AVAILABLE(10_5, 3_0);
																		
/*!
	@function CFStringTokenizerGoToTokenAtIndex
	@abstract Random access to a token. Find a token that includes the character specified
		by character index, and set it as the current token.
	@param tokenizer The reference to CFStringTokenizer returned by
		CFStringTokenizerCreate.
	@param index The index of the Unicode character in the CFString.
	@result Type of the token if succeeded in finding a token and setting it as
		current token. kCFStringTokenizerTokenNone if failed in finding a token.
	@discussion The range and attribute of the token can be obtained by calling
		CFStringTokenizerGetCurrentTokenRange and CFStringTokenizerCopyCurrentTokenAttribute.
		If the token is a compound (with type kCFStringTokenizerTokenHasSubTokensMask or
		kCFStringTokenizerTokenHasDerivedSubTokensMask), its subtokens and
		(or) derived subtokens can be obtained by calling CFStringTokenizerGetCurrentSubTokens. 
*/
CF_EXPORT
CFStringTokenizerTokenType CFStringTokenizerGoToTokenAtIndex(CFStringTokenizerRef tokenizer, CFIndex index) CF_AVAILABLE(10_5, 3_0);

/*!
	@function CFStringTokenizerAdvanceToNextToken
	@abstract Token enumerator.
	@param tokenizer The reference to CFStringTokenizer returned by
		CFStringTokenizerCreate.
	@result Type of the token if succeeded in finding a token and setting it as
		current token. kCFStringTokenizerTokenNone if failed in finding a token.
	@discussion If there is no preceding call to CFStringTokenizerGoToTokenAtIndex 
		or CFStringTokenizerAdvanceToNextToken, it finds the first token in the range
		specified to CFStringTokenizerCreate. If there is a current token after successful
		call to CFStringTokenizerGoToTokenAtIndex or CFStringTokenizerAdvanceToNextToken,
		it proceeds to the next token. If succeeded in finding a token, set it as current 
		token and return its token type. Otherwise invalidate current token and return
		kCFStringTokenizerTokenNone.
		The range and attribute of the token can be obtained by calling
		CFStringTokenizerGetCurrentTokenRange and 
        CFStringTokenizerCopyCurrentTokenAttribute. If the token is a compound
		(with type kCFStringTokenizerTokenHasSubTokensMask or
		kCFStringTokenizerTokenHasDerivedSubTokensMask), its subtokens and
		(or) derived subtokens can be obtained by calling CFStringTokenizerGetCurrentSubTokens. 
*/
CF_EXPORT
CFStringTokenizerTokenType CFStringTokenizerAdvanceToNextToken(CFStringTokenizerRef tokenizer) CF_AVAILABLE(10_5, 3_0);

/*!
	@function CFStringTokenizerGetCurrentTokenRange
	@abstract Returns the range of current token.
	@param tokenizer The reference to CFStringTokenizer returned by
		CFStringTokenizerCreate.
	@result Range of current token, or {kCFNotFound,0} if there is no current token.
*/
CF_EXPORT 
CFRange CFStringTokenizerGetCurrentTokenRange(CFStringTokenizerRef tokenizer) CF_AVAILABLE(10_5, 3_0);
																				
/*!
	@function CFStringTokenizerCopyCurrentTokenAttribute
	@abstract Copies the specified attribute of current token.
	@param tokenizer The reference to CFStringTokenizer returned by
		CFStringTokenizerCreate.
	@param attribute Specify a token attribute you want to obtain. The value is
		one of kCFStringTokenizerAttributeLatinTranscription or
		kCFStringTokenizerAttributeLanguage.
	@result Token attribute, or NULL if current token does not have the specified
		attribute or if there is no current token.
*/
CF_EXPORT
CFTypeRef CFStringTokenizerCopyCurrentTokenAttribute(CFStringTokenizerRef tokenizer, CFOptionFlags attribute) CF_AVAILABLE(10_5, 3_0);

/*!
	@function CFStringTokenizerGetCurrentSubTokens
	@abstract Retrieves the subtokens or derived subtokens contained in the compound token.
	@param tokenizer The reference to CFStringTokenizer returned by CFStringTokenizerCreate.
	@param ranges An array of CFRange to fill in with the ranges of subtokens. The filled in 
		ranges are relative to the string specified to CFStringTokenizerCreate. This parameter
		can be NULL.
	@param maxRangeLength The maximum number of ranges to return.
	@param derivedSubTokens An array of CFMutableArray to which the derived subtokens are to
		be added. This parameter can be NULL.
	@result number of subtokens.
	@discussion If token type is kCFStringTokenizerTokenNone, the ranges array and 
		derivedSubTokens array are untouched and the return value is 0.
        If token type is kCFStringTokenizerTokenNormal, the ranges array has one item
        filled in with the entire range of the token (if maxRangeLength >= 1) and a string
		taken from the entire token range is added to the derivedSubTokens array and the 
		return value is 1.
		If token type is kCFStringTokenizerTokenHasSubTokensMask or
        kCFStringTokenizerTokenHasDerivedSubTokensMask, the ranges array is filled
        in with as many items as there are subtokens (up to a limit of maxRangeLength).
		The derivedSubTokens array will have sub tokens added even when the sub token is a 
		substring of the token. If token type is kCFStringTokenizerTokenHasSubTokensMask,
		the ordinary non-derived subtokens are added to the derivedSubTokens array. 
*/
CF_EXPORT
CFIndex CFStringTokenizerGetCurrentSubTokens(CFStringTokenizerRef tokenizer, CFRange *ranges, CFIndex maxRangeLength, CFMutableArrayRef derivedSubTokens) CF_AVAILABLE(10_5, 3_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFSTRINGTOKENIZER__ */
// ==========  CoreFoundation.framework/Headers/CFLocale.h
/*	CFLocale.h
	Copyright (c) 2002-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFLOCALE__)
#define __COREFOUNDATION_CFLOCALE__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef const struct CF_BRIDGED_TYPE(NSLocale) __CFLocale *CFLocaleRef;

CF_EXPORT
CFTypeID CFLocaleGetTypeID(void);

CF_EXPORT
CFLocaleRef CFLocaleGetSystem(void);
	// Returns the "root", canonical locale.  Contains fixed "backstop" settings.

CF_EXPORT
CFLocaleRef CFLocaleCopyCurrent(void);
	// Returns the logical "user" locale for the current user.
	// [This is Copy in the sense that you get a retain you have to release,
	// but we may return the same cached object over and over.]  Settings
	// you get from this locale do not change under you as CFPreferences
	// are changed (for safety and correctness).  Generally you would not
	// grab this and hold onto it forever, but use it to do the operations
	// you need to do at the moment, then throw it away.  (The non-changing
	// ensures that all the results of your operations are consistent.)

CF_EXPORT
CFArrayRef CFLocaleCopyAvailableLocaleIdentifiers(void);
	// Returns an array of CFStrings that represents all locales for
	// which locale data is available.

CF_EXPORT
CFArrayRef CFLocaleCopyISOLanguageCodes(void);
	// Returns an array of CFStrings that represents all known legal ISO
	// language codes.  Note: many of these will not have any supporting
	// locale data in Mac OS X.

CF_EXPORT
CFArrayRef CFLocaleCopyISOCountryCodes(void);
	// Returns an array of CFStrings that represents all known legal ISO
	// country codes.  Note: many of these will not have any supporting
	// locale data in Mac OS X.

CF_EXPORT
CFArrayRef CFLocaleCopyISOCurrencyCodes(void);
	// Returns an array of CFStrings that represents all known legal ISO
	// currency codes.  Note: some of these currencies may be obsolete, or
	// represent other financial instruments.

CF_EXPORT
CFArrayRef CFLocaleCopyCommonISOCurrencyCodes(void) CF_AVAILABLE(10_5, 2_0);
	// Returns an array of CFStrings that represents ISO currency codes for
	// currencies in common use.

CF_EXPORT
CFArrayRef CFLocaleCopyPreferredLanguages(void) CF_AVAILABLE(10_5, 2_0);
	// Returns the array of canonicalized CFString locale IDs that the user prefers.

CF_EXPORT
CFStringRef CFLocaleCreateCanonicalLanguageIdentifierFromString(CFAllocatorRef allocator, CFStringRef localeIdentifier);
	// Map an arbitrary language identification string (something close at
	// least) to a canonical language identifier.

CF_EXPORT
CFStringRef CFLocaleCreateCanonicalLocaleIdentifierFromString(CFAllocatorRef allocator, CFStringRef localeIdentifier);
	// Map an arbitrary locale identification string (something close at
	// least) to the canonical identifier.

CF_EXPORT
CFStringRef CFLocaleCreateCanonicalLocaleIdentifierFromScriptManagerCodes(CFAllocatorRef allocator, LangCode lcode, RegionCode rcode);
	// Map a Mac OS LangCode and RegionCode to the canonical locale identifier.

CF_EXPORT
CFStringRef CFLocaleCreateLocaleIdentifierFromWindowsLocaleCode(CFAllocatorRef allocator, uint32_t lcid) CF_AVAILABLE(10_6, 4_0);
	// Map a Windows LCID to the canonical locale identifier.

CF_EXPORT
uint32_t CFLocaleGetWindowsLocaleCodeFromLocaleIdentifier(CFStringRef localeIdentifier) CF_AVAILABLE(10_6, 4_0);
	// Map a locale identifier to a Windows LCID.

typedef CF_ENUM(CFIndex, CFLocaleLanguageDirection) {
    kCFLocaleLanguageDirectionUnknown = 0,
    kCFLocaleLanguageDirectionLeftToRight = 1,
    kCFLocaleLanguageDirectionRightToLeft = 2,
    kCFLocaleLanguageDirectionTopToBottom = 3,
    kCFLocaleLanguageDirectionBottomToTop = 4
};

CF_EXPORT
CFLocaleLanguageDirection CFLocaleGetLanguageCharacterDirection(CFStringRef isoLangCode) CF_AVAILABLE(10_6, 4_0);

CF_EXPORT
CFLocaleLanguageDirection CFLocaleGetLanguageLineDirection(CFStringRef isoLangCode) CF_AVAILABLE(10_6, 4_0);

CF_EXPORT
CFDictionaryRef CFLocaleCreateComponentsFromLocaleIdentifier(CFAllocatorRef allocator, CFStringRef localeID);
	// Parses a locale ID consisting of language, script, country, variant,
	// and keyword/value pairs into a dictionary. The keys are the constant
	// CFStrings corresponding to the locale ID components, and the values
	// will correspond to constants where available.
	// Example: "en_US@calendar=japanese" yields a dictionary with three
	// entries: kCFLocaleLanguageCode=en, kCFLocaleCountryCode=US, and
	// kCFLocaleCalendarIdentifier=kCFJapaneseCalendar.

CF_EXPORT
CFStringRef CFLocaleCreateLocaleIdentifierFromComponents(CFAllocatorRef allocator, CFDictionaryRef dictionary);
	// Reverses the actions of CFLocaleCreateDictionaryFromLocaleIdentifier,
	// creating a single string from the data in the dictionary. The
	// dictionary {kCFLocaleLanguageCode=en, kCFLocaleCountryCode=US,
	// kCFLocaleCalendarIdentifier=kCFJapaneseCalendar} becomes
	// "en_US@calendar=japanese".

CF_EXPORT
CFLocaleRef CFLocaleCreate(CFAllocatorRef allocator, CFStringRef localeIdentifier);
	// Returns a CFLocaleRef for the locale named by the "arbitrary" locale identifier.

CF_EXPORT
CFLocaleRef CFLocaleCreateCopy(CFAllocatorRef allocator, CFLocaleRef locale);
	// Having gotten a CFLocale from somebody, code should make a copy
	// if it is going to use it for several operations
	// or hold onto it.  In the future, there may be mutable locales.

CF_EXPORT
CFStringRef CFLocaleGetIdentifier(CFLocaleRef locale);
	// Returns the locale's identifier.  This may not be the same string
	// that the locale was created with (CFLocale may canonicalize it).

CF_EXPORT
CFTypeRef CFLocaleGetValue(CFLocaleRef locale, CFStringRef key);
	// Returns the value for the given key.  This is how settings and state
	// are accessed via a CFLocale.  Values might be of any CF type.

CF_EXPORT
CFStringRef CFLocaleCopyDisplayNameForPropertyValue(CFLocaleRef displayLocale, CFStringRef key, CFStringRef value);
	// Returns the display name for the given value.  The key tells what
	// the value is, and is one of the usual locale property keys, though
	// not all locale property keys have values with display name values.


CF_EXPORT const CFStringRef kCFLocaleCurrentLocaleDidChangeNotification CF_AVAILABLE(10_5, 2_0);


// Locale Keys
CF_EXPORT const CFStringRef kCFLocaleIdentifier;
CF_EXPORT const CFStringRef kCFLocaleLanguageCode;
CF_EXPORT const CFStringRef kCFLocaleCountryCode;
CF_EXPORT const CFStringRef kCFLocaleScriptCode;
CF_EXPORT const CFStringRef kCFLocaleVariantCode;

CF_EXPORT const CFStringRef kCFLocaleExemplarCharacterSet;
CF_EXPORT const CFStringRef kCFLocaleCalendarIdentifier;
CF_EXPORT const CFStringRef kCFLocaleCalendar;
CF_EXPORT const CFStringRef kCFLocaleCollationIdentifier;
CF_EXPORT const CFStringRef kCFLocaleUsesMetricSystem;
CF_EXPORT const CFStringRef kCFLocaleMeasurementSystem; // "Metric" or "U.S."
CF_EXPORT const CFStringRef kCFLocaleDecimalSeparator;
CF_EXPORT const CFStringRef kCFLocaleGroupingSeparator;
CF_EXPORT const CFStringRef kCFLocaleCurrencySymbol;
CF_EXPORT const CFStringRef kCFLocaleCurrencyCode; // ISO 3-letter currency code
CF_EXPORT const CFStringRef kCFLocaleCollatorIdentifier CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFLocaleQuotationBeginDelimiterKey CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFLocaleQuotationEndDelimiterKey CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFLocaleAlternateQuotationBeginDelimiterKey CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFLocaleAlternateQuotationEndDelimiterKey CF_AVAILABLE(10_6, 4_0);

// Values for kCFLocaleCalendarIdentifier
CF_EXPORT const CFStringRef kCFGregorianCalendar;
CF_EXPORT const CFStringRef kCFBuddhistCalendar;
CF_EXPORT const CFStringRef kCFChineseCalendar;
CF_EXPORT const CFStringRef kCFHebrewCalendar;
CF_EXPORT const CFStringRef kCFIslamicCalendar;
CF_EXPORT const CFStringRef kCFIslamicCivilCalendar;
CF_EXPORT const CFStringRef kCFJapaneseCalendar;
CF_EXPORT const CFStringRef kCFRepublicOfChinaCalendar CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFPersianCalendar CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFIndianCalendar CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFISO8601Calendar CF_AVAILABLE(10_6, 4_0);
CF_EXPORT const CFStringRef kCFIslamicTabularCalendar CF_AVAILABLE(10_10, 8_0);
CF_EXPORT const CFStringRef kCFIslamicUmmAlQuraCalendar CF_AVAILABLE(10_10, 8_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFLOCALE__ */

// ==========  CoreFoundation.framework/Headers/CFData.h
/*	CFData.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFDATA__)
#define __COREFOUNDATION_CFDATA__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
    
typedef const struct CF_BRIDGED_TYPE(NSData) __CFData * CFDataRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableData) __CFData * CFMutableDataRef;

CF_EXPORT
CFTypeID CFDataGetTypeID(void);

CF_EXPORT
CFDataRef CFDataCreate(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex length);

CF_EXPORT
CFDataRef CFDataCreateWithBytesNoCopy(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex length, CFAllocatorRef bytesDeallocator);
    /* Pass kCFAllocatorNull as bytesDeallocator to assure the bytes aren't freed */

CF_EXPORT
CFDataRef CFDataCreateCopy(CFAllocatorRef allocator, CFDataRef theData);

CF_EXPORT
CFMutableDataRef CFDataCreateMutable(CFAllocatorRef allocator, CFIndex capacity);

CF_EXPORT
CFMutableDataRef CFDataCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFDataRef theData);

CF_EXPORT
CFIndex CFDataGetLength(CFDataRef theData);

CF_EXPORT
const UInt8 *CFDataGetBytePtr(CFDataRef theData);

CF_EXPORT
UInt8 *CFDataGetMutableBytePtr(CFMutableDataRef theData);

CF_EXPORT
void CFDataGetBytes(CFDataRef theData, CFRange range, UInt8 *buffer); 

CF_EXPORT
void CFDataSetLength(CFMutableDataRef theData, CFIndex length);

CF_EXPORT
void CFDataIncreaseLength(CFMutableDataRef theData, CFIndex extraLength);

CF_EXPORT
void CFDataAppendBytes(CFMutableDataRef theData, const UInt8 *bytes, CFIndex length);

CF_EXPORT
void CFDataReplaceBytes(CFMutableDataRef theData, CFRange range, const UInt8 *newBytes, CFIndex newLength);

CF_EXPORT
void CFDataDeleteBytes(CFMutableDataRef theData, CFRange range);

typedef CF_OPTIONS(CFOptionFlags, CFDataSearchFlags) {
    kCFDataSearchBackwards = 1UL << 0,
    kCFDataSearchAnchored = 1UL << 1
} CF_ENUM_AVAILABLE(10_6, 4_0);

CF_EXPORT
CFRange CFDataFind(CFDataRef theData, CFDataRef dataToFind, CFRange searchRange, CFDataSearchFlags compareOptions) CF_AVAILABLE(10_6, 4_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFDATA__ */

// ==========  CoreFoundation.framework/Headers/CFNumberFormatter.h
/*	CFNumberFormatter.h
	Copyright (c) 2003-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNUMBERFORMATTER__)
#define __COREFOUNDATION_CFNUMBERFORMATTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFLocale.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFNumberFormatter *CFNumberFormatterRef;

// CFNumberFormatters are not thread-safe.  Do not use one from multiple threads!

CF_EXPORT
CFTypeID CFNumberFormatterGetTypeID(void);

typedef CF_ENUM(CFIndex, CFNumberFormatterStyle) {	// number format styles
	kCFNumberFormatterNoStyle = 0,
	kCFNumberFormatterDecimalStyle = 1,
	kCFNumberFormatterCurrencyStyle = 2,
	kCFNumberFormatterPercentStyle = 3,
	kCFNumberFormatterScientificStyle = 4,
	kCFNumberFormatterSpellOutStyle = 5,
	kCFNumberFormatterOrdinalStyle CF_ENUM_AVAILABLE(10_11, 9_0) = 6,
	kCFNumberFormatterCurrencyISOCodeStyle CF_ENUM_AVAILABLE(10_11, 9_0) = 8,
	kCFNumberFormatterCurrencyPluralStyle CF_ENUM_AVAILABLE(10_11, 9_0) = 9,
	kCFNumberFormatterCurrencyAccountingStyle CF_ENUM_AVAILABLE(10_11, 9_0) = 10,
};


CF_EXPORT
CFNumberFormatterRef CFNumberFormatterCreate(CFAllocatorRef allocator, CFLocaleRef locale, CFNumberFormatterStyle style);
	// Returns a CFNumberFormatter, localized to the given locale, which
	// will format numbers to the given style.

CF_EXPORT
CFLocaleRef CFNumberFormatterGetLocale(CFNumberFormatterRef formatter);

CF_EXPORT
CFNumberFormatterStyle CFNumberFormatterGetStyle(CFNumberFormatterRef formatter);
	// Get the properties with which the number formatter was created.

CF_EXPORT
CFStringRef CFNumberFormatterGetFormat(CFNumberFormatterRef formatter);

CF_EXPORT
void CFNumberFormatterSetFormat(CFNumberFormatterRef formatter, CFStringRef formatString);
	// Set the format description string of the number formatter.  This
	// overrides the style settings.  The format of the format string
	// is as defined by the ICU library, and is similar to that found
	// in Microsoft Excel and NSNumberFormatter.
	// The number formatter starts with a default format string defined
	// by the style argument with which it was created.


CF_EXPORT
CFStringRef CFNumberFormatterCreateStringWithNumber(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFNumberRef number);

CF_EXPORT
CFStringRef CFNumberFormatterCreateStringWithValue(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFNumberType numberType, const void *valuePtr);
	// Create a string representation of the given number or value
	// using the current state of the number formatter.


typedef CF_OPTIONS(CFOptionFlags, CFNumberFormatterOptionFlags) {
    kCFNumberFormatterParseIntegersOnly = 1	/* only parse integers */
};

CF_EXPORT
CFNumberRef CFNumberFormatterCreateNumberFromString(CFAllocatorRef allocator, CFNumberFormatterRef formatter, CFStringRef string, CFRange *rangep, CFOptionFlags options);

CF_EXPORT
Boolean CFNumberFormatterGetValueFromString(CFNumberFormatterRef formatter, CFStringRef string, CFRange *rangep, CFNumberType numberType, void *valuePtr);
	// Parse a string representation of a number using the current state
	// of the number formatter.  The range parameter specifies the range
	// of the string in which the parsing should occur in input, and on
	// output indicates the extent that was used; this parameter can
	// be NULL, in which case the whole string may be used.  The
	// return value indicates whether some number was computed and
	// (if valuePtr is not NULL) stored at the location specified by
	// valuePtr.  The numberType indicates the type of value pointed
	// to by valuePtr.


CF_EXPORT
void CFNumberFormatterSetProperty(CFNumberFormatterRef formatter, CFStringRef key, CFTypeRef value);

CF_EXPORT
CFTypeRef CFNumberFormatterCopyProperty(CFNumberFormatterRef formatter, CFStringRef key);
	// Set and get various properties of the number formatter, the set of
	// which may be expanded in the future.

CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyCode;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterDecimalSeparator;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyDecimalSeparator; // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterAlwaysShowDecimalSeparator; // CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterGroupingSeparator;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterUseGroupingSeparator;	// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterPercentSymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterZeroSymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNaNSymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterInfinitySymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMinusSign;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPlusSign;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencySymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterExponentSymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMinIntegerDigits;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxIntegerDigits;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMinFractionDigits;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxFractionDigits;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterGroupingSize;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterSecondaryGroupingSize;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterRoundingMode;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterRoundingIncrement;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterFormatWidth;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPaddingPosition;	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPaddingCharacter;	// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterDefaultFormat;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterMultiplier;		// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterPositivePrefix;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPositiveSuffix;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNegativePrefix;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterNegativeSuffix;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterPerMillSymbol;		// CFString
CF_EXPORT const CFStringRef kCFNumberFormatterInternationalCurrencySymbol; // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterCurrencyGroupingSeparator CF_AVAILABLE(10_5, 2_0); // CFString
CF_EXPORT const CFStringRef kCFNumberFormatterIsLenient CF_AVAILABLE(10_5, 2_0);		// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterUseSignificantDigits CF_AVAILABLE(10_5, 2_0);	// CFBoolean
CF_EXPORT const CFStringRef kCFNumberFormatterMinSignificantDigits CF_AVAILABLE(10_5, 2_0);	// CFNumber
CF_EXPORT const CFStringRef kCFNumberFormatterMaxSignificantDigits CF_AVAILABLE(10_5, 2_0);	// CFNumber

typedef CF_ENUM(CFIndex, CFNumberFormatterRoundingMode) {
    kCFNumberFormatterRoundCeiling = 0,
    kCFNumberFormatterRoundFloor = 1,
    kCFNumberFormatterRoundDown = 2,
    kCFNumberFormatterRoundUp = 3,
    kCFNumberFormatterRoundHalfEven = 4,
    kCFNumberFormatterRoundHalfDown = 5,
    kCFNumberFormatterRoundHalfUp = 6
};

typedef CF_ENUM(CFIndex, CFNumberFormatterPadPosition) {
    kCFNumberFormatterPadBeforePrefix = 0,
    kCFNumberFormatterPadAfterPrefix = 1,
    kCFNumberFormatterPadBeforeSuffix = 2,
    kCFNumberFormatterPadAfterSuffix = 3
};


CF_EXPORT
Boolean CFNumberFormatterGetDecimalInfoForCurrencyCode(CFStringRef currencyCode, int32_t *defaultFractionDigits, double *roundingIncrement);
	// Returns the number of fraction digits that should be displayed, and
	// the rounding increment (or 0.0 if no rounding is done by the currency)
	// for the given currency.  Returns false if the currency code is unknown
	// or the information is not available.
	// Not localized because these are properties of the currency.

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFNUMBERFORMATTER__ */

// ==========  CoreFoundation.framework/Headers/CFURLAccess.h
/*	CFURLAccess.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.

        CFURLAccess is deprecated as of Mac OS X 10.9 and iOS 7.0. The suggested replacement for URLs with network schemes (http, https, ftp, data) are the NSURLSession or NSURLConnection classes. The suggested replacement for URLs with the file scheme are the foundation classes NSFileManager, NSFileHandle and NSURL, or the CoreFoundation classes CFStream and CFURL.
*/

#if !defined(__COREFOUNDATION_CFURLACCESS__)
#define __COREFOUNDATION_CFURLACCESS__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN



/* Attempts to read the data and properties for the given URL.  If
only interested in one of the resourceData and properties, pass NULL
for the other.  If properties is non-NULL and desiredProperties is
NULL, then all properties are fetched.  Returns success or failure;
note that as much work as possible is done even if false is returned.
So for instance if one property is not available, the others are
fetched anyway. errorCode is set to 0 on success, and some other
value on failure.  If non-NULL, it is the caller 's responsibility
to release resourceData and properties.

    Apple reserves for its use all negative error code values; these
values represent errors common to any scheme.  Scheme-specific error
codes should be positive, non-zero, and should be used only if one of
the predefined Apple error codes does not apply.  Error codes should
be publicized and documented with the scheme-specific properties.

NOTE: When asking for the resource data, this call will allocate the entire
resource in memory. This can be very expensive, depending on the size of the
resource (file). Please use CFStream or other techniques if you are downloading
large files.

*/
/* Deprecated -- see top of this file for suggested replacement classes */
CF_EXPORT
Boolean CFURLCreateDataAndPropertiesFromResource(CFAllocatorRef alloc, CFURLRef url, CFDataRef *resourceData, CFDictionaryRef *properties, CFArrayRef desiredProperties, SInt32 *errorCode) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "For resource data, use the CFReadStream API. For file resource properties, use CFURLCopyResourcePropertiesForKeys.");

/* Attempts to write the given data and properties to the given URL.
If dataToWrite is NULL, only properties are written out (use
CFURLDestroyResource() to delete a resource).  Properties not present
in propertiesToWrite are left unchanged, hence if propertiesToWrite
is NULL or empty, the URL's properties are not changed at all.
Returns success or failure; errorCode is set as for
CFURLCreateDataAndPropertiesFromResource(), above.
*/
/* Deprecated -- see top of this file for suggested replacement classes */
CF_EXPORT
Boolean CFURLWriteDataAndPropertiesToResource(CFURLRef url, CFDataRef dataToWrite, CFDictionaryRef propertiesToWrite, SInt32 *errorCode) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "For resource data, use the CFWriteStream API. For file resource properties, use CFURLSetResourcePropertiesForKeys.");

/* Destroys the resource indicated by url.
Returns success or failure; errorCode set as above.
*/
/* Deprecated -- see top of this file for suggested replacement classes */
CF_EXPORT
Boolean CFURLDestroyResource(CFURLRef url, SInt32 *errorCode) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLGetFileSystemRepresentation and removefile(3) instead.");

/* Convenience method which calls through to CFURLCreateDataAndPropertiesFromResource().
Returns NULL on error and sets errorCode accordingly.
*/
/* Deprecated -- see top of this file for suggested replacement classes */
CF_EXPORT
CFTypeRef CFURLCreatePropertyFromResource(CFAllocatorRef alloc, CFURLRef url, CFStringRef property, SInt32 *errorCode) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "For file resource properties, use CFURLCopyResourcePropertyForKey.");


/* Common error codes (returned only by the older APIs that predate CFError) */
typedef CF_ENUM(CFIndex, CFURLError) {
    kCFURLUnknownError = -10L,
    kCFURLUnknownSchemeError = -11L,
    kCFURLResourceNotFoundError = -12L,
    kCFURLResourceAccessViolationError = -13L,
    kCFURLRemoteHostUnavailableError = -14L,
    kCFURLImproperArgumentsError = -15L,
    kCFURLUnknownPropertyKeyError = -16L,
    kCFURLPropertyKeyUnavailableError = -17L,
    kCFURLTimeoutError = -18L
} CF_ENUM_DEPRECATED(10_0, 10_9, 2_0, 7_0);

/* Older property keys */

CF_EXPORT
const CFStringRef kCFURLFileExists CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLResourceIsReachable instead.");
CF_EXPORT
const CFStringRef kCFURLFileDirectoryContents CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use the CFURLEnumerator API instead.");
CF_EXPORT
const CFStringRef kCFURLFileLength CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLCopyResourcePropertyForKey with kCFURLFileSizeKey instead.");
CF_EXPORT 
const CFStringRef kCFURLFileLastModificationTime CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLCopyResourcePropertyForKey with kCFURLContentModificationDateKey instead.");
CF_EXPORT
const CFStringRef kCFURLFilePOSIXMode CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLCopyResourcePropertyForKey with kCFURLFileSecurityKey and then the CFFileSecurity API instead.");
CF_EXPORT
const CFStringRef kCFURLFileOwnerID CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use CFURLCopyResourcePropertyForKey with kCFURLFileSecurityKey and then the CFFileSecurity API instead.");
CF_EXPORT
const CFStringRef kCFURLHTTPStatusCode CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use NSHTTPURLResponse methods instead.");
CF_EXPORT
const CFStringRef kCFURLHTTPStatusLine CF_DEPRECATED(10_0, 10_9, 2_0, 7_0, "Use NSHTTPURLResponse methods instead.");

/* The value of kCFURLFileExists is a CFBoolean */
/* The value of kCFURLFileDirectoryContents is a CFArray containing CFURLs.  An empty array means the directory exists, but is empty */
/* The value of kCFURLFileLength is a CFNumber giving the file's length in bytes */
/* The value of kCFURLFileLastModificationTime is a CFDate */
/* The value of kCFURLFilePOSIXMode is a CFNumber as given in stat.h */
/* The value of kCFURLFileOwnerID is a CFNumber representing the owner's uid */

/* Properties for the http: scheme.  Except for the common error codes, above, errorCode will be set to the HTTP response status code upon failure.  Any HTTP header name can also be used as a property */
/* The value of kCFURLHTTPStatusCode is a CFNumber */
/* The value of kCFURLHTTPStatusLine is a CFString */

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFURLACCESS__ */

// ==========  CoreFoundation.framework/Headers/CFTimeZone.h
/*	CFTimeZone.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFTIMEZONE__)
#define __COREFOUNDATION_CFTIMEZONE__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

CF_EXPORT
CFTypeID CFTimeZoneGetTypeID(void);

CF_EXPORT
CFTimeZoneRef CFTimeZoneCopySystem(void);

CF_EXPORT
void CFTimeZoneResetSystem(void);

CF_EXPORT
CFTimeZoneRef CFTimeZoneCopyDefault(void);

CF_EXPORT
void CFTimeZoneSetDefault(CFTimeZoneRef tz);

CF_EXPORT
CFArrayRef CFTimeZoneCopyKnownNames(void);

CF_EXPORT
CFDictionaryRef CFTimeZoneCopyAbbreviationDictionary(void);

CF_EXPORT
void CFTimeZoneSetAbbreviationDictionary(CFDictionaryRef dict);

CF_EXPORT
CFTimeZoneRef CFTimeZoneCreate(CFAllocatorRef allocator, CFStringRef name, CFDataRef data);

CF_EXPORT
CFTimeZoneRef CFTimeZoneCreateWithTimeIntervalFromGMT(CFAllocatorRef allocator, CFTimeInterval ti);

CF_EXPORT
CFTimeZoneRef CFTimeZoneCreateWithName(CFAllocatorRef allocator, CFStringRef name, Boolean tryAbbrev);

CF_EXPORT
CFStringRef CFTimeZoneGetName(CFTimeZoneRef tz);

CF_EXPORT
CFDataRef CFTimeZoneGetData(CFTimeZoneRef tz);

CF_EXPORT
CFTimeInterval CFTimeZoneGetSecondsFromGMT(CFTimeZoneRef tz, CFAbsoluteTime at);

CF_EXPORT
CFStringRef CFTimeZoneCopyAbbreviation(CFTimeZoneRef tz, CFAbsoluteTime at);

CF_EXPORT
Boolean CFTimeZoneIsDaylightSavingTime(CFTimeZoneRef tz, CFAbsoluteTime at);

CF_EXPORT
CFTimeInterval CFTimeZoneGetDaylightSavingTimeOffset(CFTimeZoneRef tz, CFAbsoluteTime at) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT
CFAbsoluteTime CFTimeZoneGetNextDaylightSavingTimeTransition(CFTimeZoneRef tz, CFAbsoluteTime at) CF_AVAILABLE(10_5, 2_0);

typedef CF_ENUM(CFIndex, CFTimeZoneNameStyle) {
	kCFTimeZoneNameStyleStandard,
	kCFTimeZoneNameStyleShortStandard,
	kCFTimeZoneNameStyleDaylightSaving,
	kCFTimeZoneNameStyleShortDaylightSaving,
	kCFTimeZoneNameStyleGeneric,
	kCFTimeZoneNameStyleShortGeneric
} CF_ENUM_AVAILABLE(10_5, 2_0);

CF_EXPORT
CFStringRef CFTimeZoneCopyLocalizedName(CFTimeZoneRef tz, CFTimeZoneNameStyle style, CFLocaleRef locale) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT
const CFStringRef kCFTimeZoneSystemTimeZoneDidChangeNotification CF_AVAILABLE(10_5, 2_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFTIMEZONE__ */

// ==========  CoreFoundation.framework/Headers/CFError.h
/*	CFError.h
	Copyright (c) 2006-2015, Apple Inc. All rights reserved.
*/

/*!
	@header CFError
        @discussion
            CFErrors are used to encompass information about errors. At minimum, errors are identified by their domain (a string) and an error code within that domain. In addition a "userInfo" dictionary supplied at creation time enables providing additional info that might be useful for the interpretation and reporting of the error. This dictionary can even contain an "underlying" error, which is wrapped as an error bubbles up through various layers. 
            
            CFErrors have the ability to provide human-readable descriptions for the errors; in fact, they are designed to provide localizable, end-user presentable errors that can appear in the UI. CFError has a number of predefined userInfo keys to enable developers to supply the info.
            
            Usage recommendation for CFErrors is to return them as by-ref parameters in functions. This enables the caller to pass NULL in when they don't actually want information about the error. The presence of an error should be reported by other means, for instance a NULL or false return value from the function call proper:
            
            CFError *error;
            if (!ReadFromFile(fd, &error)) {
                ... process error ...
                CFRelease(error);   // If an error occurs, the returned CFError must be released.
            }
            
            It is the responsibility of anyone returning CFErrors this way to:
            - Not touch the error argument if no error occurs
            - Create and assign the error for return only if the error argument is non-NULL
            
            In addition, it's recommended that CFErrors be used in error situations only (not status), and where there are multiple possible errors to distinguish between. For instance there is no plan to add CFErrors to existing APIs in CF which currently don't return errors; in many cases, there is one possible reason for failure, and a false or NULL return is enough to indicate it.

            CFError is toll-free bridged to NSError in Foundation. NSError in Foundation has some additional guidelines which makes it easy to automatically report errors to users and even try to recover from them.  See http://developer.apple.com/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/chapter_1_section_1.html for more info on NSError programming guidelines.
*/

#if !defined(__COREFOUNDATION_CFERROR__)
#define __COREFOUNDATION_CFERROR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
	@typedef CFErrorRef
	    This is the type of a reference to CFErrors.  CFErrorRef is toll-free bridged with NSError.
*/
typedef struct CF_BRIDGED_TYPE(NSError) __CFError * CFErrorRef;

/*!
	@function CFErrorGetTypeID
	    Returns the type identifier of all CFError instances.
*/
CF_EXPORT
CFTypeID CFErrorGetTypeID(void) CF_AVAILABLE(10_5, 2_0);


// Predefined domains; value of "code" will correspond to preexisting values in these domains.
CF_EXPORT const CFStringRef kCFErrorDomainPOSIX		    CF_AVAILABLE(10_5, 2_0);
CF_EXPORT const CFStringRef kCFErrorDomainOSStatus	    CF_AVAILABLE(10_5, 2_0);
CF_EXPORT const CFStringRef kCFErrorDomainMach		    CF_AVAILABLE(10_5, 2_0);
CF_EXPORT const CFStringRef kCFErrorDomainCocoa		    CF_AVAILABLE(10_5, 2_0);

// Keys in userInfo for localizable, end-user presentable error messages. At minimum provide one of first two; ideally provide all three.
CF_EXPORT const CFStringRef kCFErrorLocalizedDescriptionKey         CF_AVAILABLE(10_5, 2_0);   // Key to identify the end user-presentable description in userInfo.
CF_EXPORT const CFStringRef kCFErrorLocalizedFailureReasonKey       CF_AVAILABLE(10_5, 2_0);   // Key to identify the end user-presentable failure reason in userInfo.
CF_EXPORT const CFStringRef kCFErrorLocalizedRecoverySuggestionKey  CF_AVAILABLE(10_5, 2_0);   // Key to identify the end user-presentable recovery suggestion in userInfo.

// If you do not have localizable error strings, you can provide a value for this key instead.
CF_EXPORT const CFStringRef kCFErrorDescriptionKey                  CF_AVAILABLE(10_5, 2_0);   // Key to identify the description in the userInfo dictionary. Should be a complete sentence if possible. Should not contain domain name or error code.

// Other keys in userInfo.
CF_EXPORT const CFStringRef kCFErrorUnderlyingErrorKey              CF_AVAILABLE(10_5, 2_0);   // Key to identify the underlying error in userInfo.
CF_EXPORT const CFStringRef kCFErrorURLKey                          CF_AVAILABLE(10_7, 5_0);    // Key to identify associated URL in userInfo.  Typically one of this or kCFErrorFilePathKey is provided.
CF_EXPORT const CFStringRef kCFErrorFilePathKey                     CF_AVAILABLE(10_7, 5_0);    // Key to identify associated file path in userInfo.    Typically one of this or kCFErrorURLKey is provided.


/*!
	@function CFErrorCreate
	@abstract Creates a new CFError.
	@param allocator The CFAllocator which should be used to allocate memory for the error. This parameter may be NULL in which case the 
	    current default CFAllocator is used. If this reference is not a valid CFAllocator, the behavior is undefined.
	@param domain A CFString identifying the error domain. If this reference is NULL or is otherwise not a valid CFString, the behavior is undefined.
	@param code A CFIndex identifying the error code. The code is interpreted within the context of the error domain.
	@param userInfo A CFDictionary created with kCFCopyStringDictionaryKeyCallBacks and kCFTypeDictionaryValueCallBacks. It will be copied with CFDictionaryCreateCopy(). 
	    If no userInfo dictionary is desired, NULL may be passed in as a convenience, in which case an empty userInfo dictionary will be assigned.
	@result A reference to the new CFError.
*/
CF_EXPORT
CFErrorRef CFErrorCreate(CFAllocatorRef allocator, CFStringRef domain, CFIndex code, CFDictionaryRef userInfo) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorCreateWithUserInfoKeysAndValues
	@abstract Creates a new CFError without having to create an intermediate userInfo dictionary.
	@param allocator The CFAllocator which should be used to allocate memory for the error. This parameter may be NULL in which case the 
	    current default CFAllocator is used. If this reference is not a valid CFAllocator, the behavior is undefined.
	@param domain A CFString identifying the error domain. If this reference is NULL or is otherwise not a valid CFString, the behavior is undefined.
	@param code A CFIndex identifying the error code. The code is interpreted within the context of the error domain.
	@param userInfoKeys An array of numUserInfoValues CFStrings used as keys in creating the userInfo dictionary. NULL is valid only if numUserInfoValues is 0.
	@param userInfoValues An array of numUserInfoValues CF types used as values in creating the userInfo dictionary.  NULL is valid only if numUserInfoValues is 0.
	@param numUserInfoValues CFIndex representing the number of keys and values in the userInfoKeys and userInfoValues arrays.
	@result A reference to the new CFError. numUserInfoValues CF types are gathered from each of userInfoKeys and userInfoValues to create the userInfo dictionary.
*/
CF_EXPORT
CFErrorRef CFErrorCreateWithUserInfoKeysAndValues(CFAllocatorRef allocator, CFStringRef domain, CFIndex code, const void *const *userInfoKeys, const void *const *userInfoValues, CFIndex numUserInfoValues) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorGetDomain
	@abstract Returns the error domain the CFError was created with.
	@param err The CFError whose error domain is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result The error domain of the CFError. Since this is a "Get" function, the caller shouldn't CFRelease the return value.
*/
CF_EXPORT
CFStringRef CFErrorGetDomain(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorGetCode
	@abstract Returns the error code the CFError was created with.
	@param err The CFError whose error code is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result The error code of the CFError (not an error return for the current call).
*/
CF_EXPORT
CFIndex CFErrorGetCode(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorCopyUserInfo
        @abstract Returns CFError userInfo dictionary.
	@discussion Returns a dictionary containing the same keys and values as in the userInfo dictionary the CFError was created with. Returns an empty dictionary if NULL was supplied to CFErrorCreate().
	@param err The CFError whose error user info is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result The user info of the CFError.
*/
CF_EXPORT
CFDictionaryRef CFErrorCopyUserInfo(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorCopyDescription
	@abstract Returns a human-presentable description for the error. CFError creators should strive to make sure the return value is human-presentable and localized by providing a value for kCFErrorLocalizedDescriptionKey at the time of CFError creation.
        @discussion This is a complete sentence or two which says what failed and why it failed. Rules for computing the return value:
            - Look for kCFErrorLocalizedDescriptionKey in the user info and if not NULL, returns that as-is.  
            - Otherwise, if there is a kCFErrorLocalizedFailureReasonKey in the user info, generate an error from that. Something like: "Operation code not be completed. " + kCFErrorLocalizedFailureReasonKey
            - Otherwise, generate a semi-user presentable string from kCFErrorDescriptionKey, the domain, and code. Something like: "Operation could not be completed. Error domain/code occurred. " or "Operation could not be completed. " + kCFErrorDescriptionKey + " (Error domain/code)"
            Toll-free bridged NSError instances might provide additional behaviors for manufacturing a description string.  Do not count on the exact contents or format of the returned string, it might change.
	@param err The CFError whose description is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result A CFString with human-presentable description of the CFError. Never NULL.
*/
CF_EXPORT
CFStringRef CFErrorCopyDescription(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorCopyFailureReason
        @abstract Returns a human-presentable failure reason for the error.  May return NULL.  CFError creators should strive to make sure the return value is human-presentable and localized by providing a value for kCFErrorLocalizedFailureReasonKey at the time of CFError creation.
        @discussion This is a complete sentence which describes why the operation failed. In many cases this will be just the "because" part of the description (but as a complete sentence, which makes localization easier). By default this looks for kCFErrorLocalizedFailureReasonKey in the user info. Toll-free bridged NSError instances might provide additional behaviors for manufacturing this value. If no user-presentable string is available, returns NULL.
            Example Description: "Could not save file 'Letter' in folder 'Documents' because the volume 'MyDisk' doesn't have enough space."
            Corresponding FailureReason: "The volume 'MyDisk' doesn't have enough space."
	@param err The CFError whose failure reason is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result A CFString with the localized, end-user presentable failure reason of the CFError, or NULL. 
*/
CF_EXPORT
CFStringRef CFErrorCopyFailureReason(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFErrorCopyRecoverySuggestion
        @abstract Returns a human presentable recovery suggestion for the error.  May return NULL.  CFError creators should strive to make sure the return value is human-presentable and localized by providing a value for kCFErrorLocalizedRecoverySuggestionKey at the time of CFError creation.
        @discussion This is the string that can be displayed as the "informative" (aka "secondary") message on an alert panel. By default this looks for kCFErrorLocalizedRecoverySuggestionKey in the user info. Toll-free bridged NSError instances might provide additional behaviors for manufacturing this value. If no user-presentable string is available, returns NULL.
            Example Description: "Could not save file 'Letter' in folder 'Documents' because the volume 'MyDisk' doesn't have enough space."
            Corresponding RecoverySuggestion: "Remove some files from the volume and try again."
	@param err The CFError whose recovery suggestion is to be returned. If this reference is not a valid CFError, the behavior is undefined.
	@result A CFString with the localized, end-user presentable recovery suggestion of the CFError, or NULL. 
*/
CF_EXPORT
CFStringRef CFErrorCopyRecoverySuggestion(CFErrorRef err) CF_AVAILABLE(10_5, 2_0);



CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFERROR__ */

// ==========  CoreFoundation.framework/Headers/CFNumber.h
/*	CFNumber.h
	Copyright (c) 1999-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNUMBER__)
#define __COREFOUNDATION_CFNUMBER__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef const struct CF_BRIDGED_TYPE(NSNumber) __CFBoolean * CFBooleanRef;

CF_EXPORT
const CFBooleanRef kCFBooleanTrue;
CF_EXPORT
const CFBooleanRef kCFBooleanFalse;

CF_EXPORT
CFTypeID CFBooleanGetTypeID(void);

CF_EXPORT
Boolean CFBooleanGetValue(CFBooleanRef boolean);

typedef CF_ENUM(CFIndex, CFNumberType) {
    /* Fixed-width types */
    kCFNumberSInt8Type = 1,
    kCFNumberSInt16Type = 2,
    kCFNumberSInt32Type = 3,
    kCFNumberSInt64Type = 4,
    kCFNumberFloat32Type = 5,
    kCFNumberFloat64Type = 6,	/* 64-bit IEEE 754 */
    /* Basic C types */
    kCFNumberCharType = 7,
    kCFNumberShortType = 8,
    kCFNumberIntType = 9,
    kCFNumberLongType = 10,
    kCFNumberLongLongType = 11,
    kCFNumberFloatType = 12,
    kCFNumberDoubleType = 13,
    /* Other */
    kCFNumberCFIndexType = 14,
    kCFNumberNSIntegerType CF_ENUM_AVAILABLE(10_5, 2_0) = 15,
    kCFNumberCGFloatType CF_ENUM_AVAILABLE(10_5, 2_0) = 16,
    kCFNumberMaxType = 16
};

typedef const struct CF_BRIDGED_TYPE(NSNumber) __CFNumber * CFNumberRef;

CF_EXPORT
const CFNumberRef kCFNumberPositiveInfinity;
CF_EXPORT
const CFNumberRef kCFNumberNegativeInfinity;
CF_EXPORT
const CFNumberRef kCFNumberNaN;

CF_EXPORT
CFTypeID CFNumberGetTypeID(void);

/*
	Creates a CFNumber with the given value. The type of number pointed
	to by the valuePtr is specified by type. If type is a floating point
	type and the value represents one of the infinities or NaN, the
	well-defined CFNumber for that value is returned. If either of
	valuePtr or type is an invalid value, the result is undefined.
*/
CF_EXPORT
CFNumberRef CFNumberCreate(CFAllocatorRef allocator, CFNumberType theType, const void *valuePtr);

/*
	Returns the storage format of the CFNumber's value.  Note that
	this is not necessarily the type provided in CFNumberCreate().
*/
CF_EXPORT
CFNumberType CFNumberGetType(CFNumberRef number);

/*
	Returns the size in bytes of the type of the number.
*/
CF_EXPORT
CFIndex CFNumberGetByteSize(CFNumberRef number);

/*
	Returns true if the type of the CFNumber's value is one of
	the defined floating point types.
*/
CF_EXPORT
Boolean CFNumberIsFloatType(CFNumberRef number);

/*
	Copies the CFNumber's value into the space pointed to by
	valuePtr, as the specified type. If conversion needs to take
	place, the conversion rules follow human expectation and not
	C's promotion and truncation rules. If the conversion is
	lossy, or the value is out of range, false is returned. Best
	attempt at conversion will still be in *valuePtr.
*/
CF_EXPORT
Boolean CFNumberGetValue(CFNumberRef number, CFNumberType theType, void *valuePtr);

/*
	Compares the two CFNumber instances. If conversion of the
	types of the values is needed, the conversion and comparison
	follow human expectations and not C's promotion and comparison
	rules. Negative zero compares less than positive zero.
	Positive infinity compares greater than everything except
	itself, to which it compares equal. Negative infinity compares
	less than everything except itself, to which it compares equal.
	Unlike standard practice, if both numbers are NaN, then they
	compare equal; if only one of the numbers is NaN, then the NaN
	compares greater than the other number if it is negative, and
	smaller than the other number if it is positive. (Note that in
	CFEqual() with two CFNumbers, if either or both of the numbers
	is NaN, true is returned.)
*/
CF_EXPORT
CFComparisonResult CFNumberCompare(CFNumberRef number, CFNumberRef otherNumber, void *context);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFNUMBER__ */

// ==========  CoreFoundation.framework/Headers/CFPropertyList.h
/*	CFPropertyList.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFPROPERTYLIST__)
#define __COREFOUNDATION_CFPROPERTYLIST__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFError.h>
#if TARGET_OS_MAC || TARGET_OS_WIN32 || TARGET_OS_EMBEDDED
#include <CoreFoundation/CFStream.h>
#endif

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef CF_OPTIONS(CFOptionFlags, CFPropertyListMutabilityOptions) {
    kCFPropertyListImmutable = 0,
    kCFPropertyListMutableContainers,
    kCFPropertyListMutableContainersAndLeaves
};

CF_IMPLICIT_BRIDGING_DISABLED

/*
	Creates a property list object from its XML description; xmlData should
	be the raw bytes of that description, possibly the contents of an XML
	file. Returns NULL if the data cannot be parsed; if the parse fails
	and errorString is non-NULL, a human-readable description of the failure
	is returned in errorString. It is the caller's responsibility to release
	either the returned object or the error string, whichever is applicable.
 
        This function is deprecated. See CFPropertyListCreateWithData() for a replacement.
*/
CF_EXPORT
CFPropertyListRef CFPropertyListCreateFromXMLData(CFAllocatorRef allocator, CFDataRef xmlData, CFOptionFlags mutabilityOption, CFStringRef *errorString) CF_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use CFPropertyListCreateWithData instead.");

/*
	Returns the XML description of the given object; propertyList must
	be one of the supported property list types, and (for composite types
	like CFArray and CFDictionary) must not contain any elements that
	are not themselves of a property list type. If a non-property list
	type is encountered, NULL is returned. The returned data is
	appropriate for writing out to an XML file. Note that a data, not a
	string, is returned because the bytes contain in them a description
	of the string encoding used.
 
        This function is deprecated. See CFPropertyListCreateData() for a replacement.
*/
CF_EXPORT
CFDataRef CFPropertyListCreateXMLData(CFAllocatorRef allocator, CFPropertyListRef propertyList) CF_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use CFPropertyListCreateData instead.");

CF_IMPLICIT_BRIDGING_ENABLED

/*
	Recursively creates a copy of the given property list (so nested arrays
	and dictionaries are copied as well as the top-most container). The
	resulting property list has the mutability characteristics determined
	by mutabilityOption.
*/
CF_EXPORT
CFPropertyListRef CFPropertyListCreateDeepCopy(CFAllocatorRef allocator, CFPropertyListRef propertyList, CFOptionFlags mutabilityOption);

typedef CF_ENUM(CFIndex, CFPropertyListFormat) {
    kCFPropertyListOpenStepFormat = 1,
    kCFPropertyListXMLFormat_v1_0 = 100,
    kCFPropertyListBinaryFormat_v1_0 = 200
};

/* Returns true if the object graph rooted at plist is a valid property list
 * graph -- that is, no cycles, containing only plist objects, and dictionary
 * keys are strings. The debugging library version spits out some messages
 * to be helpful. The plist structure which is to be allowed is given by
 * the format parameter. */
CF_EXPORT
Boolean CFPropertyListIsValid(CFPropertyListRef plist, CFPropertyListFormat format);

#if TARGET_OS_MAC || TARGET_OS_WIN32 || TARGET_OS_EMBEDDED
CF_IMPLICIT_BRIDGING_DISABLED

/* Writes the bytes of a plist serialization out to the stream.  The
 * stream must be opened and configured -- the function simply writes
 * a bunch of bytes to the stream. The output plist format can be chosen.
 * Leaves the stream open, but note that reading a plist expects the
 * reading stream to end wherever the writing ended, so that the
 * end of the plist data can be identified. Returns the number of bytes
 * written, or 0 on error. Error messages are not currently localized, but
 * may be in the future, so they are not suitable for comparison. 
 *
 * This function is deprecated. See CFPropertyListWrite() for a replacement. */
CF_EXPORT
CFIndex CFPropertyListWriteToStream(CFPropertyListRef propertyList, CFWriteStreamRef stream, CFPropertyListFormat format, CFStringRef *errorString) CF_DEPRECATED(10_2, 10_10, 2_0, 8_0, "Use CFPropertyListWrite instead.");


/* Same as current function CFPropertyListCreateFromXMLData()
 * but takes a stream instead of data, and works on any plist file format.
 * CFPropertyListCreateFromXMLData() also works on any plist file format.
 * The stream must be open and configured -- the function simply reads a bunch
 * of bytes from it starting at the current location in the stream, to the END
 * of the stream, which is expected to be the end of the plist, or up to the
 * number of bytes given by the length parameter if it is not 0. Error messages
 * are not currently localized, but may be in the future, so they are not
 * suitable for comparison. 
 *
 * This function is deprecated. See CFPropertyListCreateWithStream() for a replacement. */
CF_EXPORT
CFPropertyListRef CFPropertyListCreateFromStream(CFAllocatorRef allocator, CFReadStreamRef stream, CFIndex streamLength, CFOptionFlags mutabilityOption, CFPropertyListFormat *format, CFStringRef *errorString) CF_DEPRECATED(10_2, 10_10, 2_0, 8_0, "Use CFPropertyListCreateWithStream instead.");

CF_IMPLICIT_BRIDGING_ENABLED
#endif

CF_IMPLICIT_BRIDGING_DISABLED

CF_ENUM(CFIndex) {
    kCFPropertyListReadCorruptError = 3840,              // Error parsing a property list
    kCFPropertyListReadUnknownVersionError = 3841,       // The version number in the property list is unknown
    kCFPropertyListReadStreamError = 3842,               // Stream error reading a property list
    kCFPropertyListWriteStreamError = 3851,              // Stream error writing a property list
} CF_ENUM_AVAILABLE(10_6, 4_0);

/* Create a property list with a CFData input. If the format parameter is non-NULL, it will be set to the format of the data after parsing is complete. The options parameter is used to specify CFPropertyListMutabilityOptions. If an error occurs while parsing the data, the return value will be NULL. Additionally, if an error occurs and the error parameter is non-NULL, the error parameter will be set to a CFError describing the problem, which the caller must release. If the parse succeeds, the returned value is a reference to the new property list. It is the responsibility of the caller to release this value.
 */
CF_EXPORT
CFPropertyListRef CFPropertyListCreateWithData(CFAllocatorRef allocator, CFDataRef data, CFOptionFlags options, CFPropertyListFormat *format, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

#if TARGET_OS_MAC || TARGET_OS_WIN32 || TARGET_OS_EMBEDDED

/* Create and return a property list with a CFReadStream input. If the format parameter is non-NULL, it will be set to the format of the data after parsing is complete. The options parameter is used to specify CFPropertyListMutabilityOptions. The streamLength parameter specifies the number of bytes to read from the stream. Set streamLength to 0 to read until the end of the stream is detected. If an error occurs while parsing the data, the return value will be NULL. Additionally, if an error occurs and the error parameter is non-NULL, the error parameter will be set to a CFError describing the problem, which the caller must release. If the parse succeeds, the returned value is a reference to the new property list. It is the responsibility of the caller to release this value.
 */
CF_EXPORT
CFPropertyListRef CFPropertyListCreateWithStream(CFAllocatorRef allocator, CFReadStreamRef stream, CFIndex streamLength, CFOptionFlags options, CFPropertyListFormat *format, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

/* Write the bytes of a serialized property list out to a stream. The stream must be opened and configured. The format of the property list can be chosen with the format parameter. The options parameter is currently unused and should be set to 0. The return value is the number of bytes written or 0 in the case of an error. If an error occurs and the error parameter is non-NULL, the error parameter will be set to a CFError describing the problem, which the caller must release.
 */
CF_EXPORT
CFIndex CFPropertyListWrite(CFPropertyListRef propertyList, CFWriteStreamRef stream, CFPropertyListFormat format, CFOptionFlags options, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

#endif

/* Create a CFData with the bytes of a serialized property list. The format of the property list can be chosen with the format parameter. The options parameter is currently unused and should be set to 0. If an error occurs while parsing the data, the return value will be NULL. Additionally, if an error occurs and the error parameter is non-NULL, the error parameter will be set to a CFError describing the problem, which the caller must release. If the conversion succeeds, the returned value is a reference to the created data. It is the responsibility of the caller to release this value.
 */
CF_EXPORT
CFDataRef CFPropertyListCreateData(CFAllocatorRef allocator, CFPropertyListRef propertyList, CFPropertyListFormat format, CFOptionFlags options, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

CF_IMPLICIT_BRIDGING_ENABLED

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFPROPERTYLIST__ */

// ==========  CoreFoundation.framework/Headers/CFByteOrder.h
/*	CFByteOrder.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBYTEORDER__)
#define __COREFOUNDATION_CFBYTEORDER__ 1

#include <CoreFoundation/CFBase.h>
#if ((TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) && !defined(CF_USE_OSBYTEORDER_H)
#include <libkern/OSByteOrder.h>
#define CF_USE_OSBYTEORDER_H 1
#endif

CF_EXTERN_C_BEGIN

enum __CFByteOrder {
    CFByteOrderUnknown,
    CFByteOrderLittleEndian,
    CFByteOrderBigEndian
};
typedef CFIndex CFByteOrder;

CF_INLINE CFByteOrder CFByteOrderGetCurrent(void) {
#if CF_USE_OSBYTEORDER_H
    int32_t byteOrder = OSHostByteOrder();
    switch (byteOrder) {
    case OSLittleEndian: return CFByteOrderLittleEndian;
    case OSBigEndian: return CFByteOrderBigEndian;
    default: break;
    }
    return CFByteOrderUnknown;
#else
#if __LITTLE_ENDIAN__
    return CFByteOrderLittleEndian;
#elif __BIG_ENDIAN__
    return CFByteOrderBigEndian;
#else
    return CFByteOrderUnknown;
#endif
#endif
}

CF_INLINE uint16_t CFSwapInt16(uint16_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapInt16(arg);
#else
    uint16_t result;
    result = (uint16_t)(((arg << 8) & 0xFF00) | ((arg >> 8) & 0xFF));
    return result;
#endif
}

CF_INLINE uint32_t CFSwapInt32(uint32_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapInt32(arg);
#else
    uint32_t result;
    result = ((arg & 0xFF) << 24) | ((arg & 0xFF00) << 8) | ((arg >> 8) & 0xFF00) | ((arg >> 24) & 0xFF);
    return result;
#endif
}

CF_INLINE uint64_t CFSwapInt64(uint64_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapInt64(arg);
#else
    union CFSwap {
        uint64_t sv;
        uint32_t ul[2];
    } tmp, result;
    tmp.sv = arg;
    result.ul[0] = CFSwapInt32(tmp.ul[1]); 
    result.ul[1] = CFSwapInt32(tmp.ul[0]);
    return result.sv;
#endif
}

CF_INLINE uint16_t CFSwapInt16BigToHost(uint16_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapBigToHostInt16(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32BigToHost(uint32_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapBigToHostInt32(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64BigToHost(uint64_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapBigToHostInt64(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16HostToBig(uint16_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToBigInt16(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32HostToBig(uint32_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToBigInt32(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64HostToBig(uint64_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToBigInt64(arg);
#elif __BIG_ENDIAN__
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16LittleToHost(uint16_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapLittleToHostInt16(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32LittleToHost(uint32_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapLittleToHostInt32(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64LittleToHost(uint64_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapLittleToHostInt64(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16HostToLittle(uint16_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToLittleInt16(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32HostToLittle(uint32_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToLittleInt32(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64HostToLittle(uint64_t arg) {
#if CF_USE_OSBYTEORDER_H
    return OSSwapHostToLittleInt64(arg);
#elif __LITTLE_ENDIAN__
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

typedef struct {uint32_t v;} CFSwappedFloat32;
typedef struct {uint64_t v;} CFSwappedFloat64;

CF_INLINE CFSwappedFloat32 CFConvertFloat32HostToSwapped(Float32 arg) {
    union CFSwap {
	Float32 v;
	CFSwappedFloat32 sv;
    } result;
    result.v = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE Float32 CFConvertFloat32SwappedToHost(CFSwappedFloat32 arg) {
    union CFSwap {
	Float32 v;
	CFSwappedFloat32 sv;
    } result;
    result.sv = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat64 CFConvertFloat64HostToSwapped(Float64 arg) {
    union CFSwap {
	Float64 v;
	CFSwappedFloat64 sv;
    } result;
    result.v = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE Float64 CFConvertFloat64SwappedToHost(CFSwappedFloat64 arg) {
    union CFSwap {
	Float64 v;
	CFSwappedFloat64 sv;
    } result;
    result.sv = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat32 CFConvertFloatHostToSwapped(float arg) {
    union CFSwap {
	float v;
	CFSwappedFloat32 sv;
    } result;
    result.v = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE float CFConvertFloatSwappedToHost(CFSwappedFloat32 arg) {
    union CFSwap {
	float v;
	CFSwappedFloat32 sv;
    } result;
    result.sv = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat64 CFConvertDoubleHostToSwapped(double arg) {
    union CFSwap {
	double v;
	CFSwappedFloat64 sv;
    } result;
    result.v = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE double CFConvertDoubleSwappedToHost(CFSwappedFloat64 arg) {
    union CFSwap {
	double v;
	CFSwappedFloat64 sv;
    } result;
    result.sv = arg;
#if __LITTLE_ENDIAN__
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.v;
}

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFBYTEORDER__ */

// ==========  CoreFoundation.framework/Headers/CFSocket.h
/*	CFSocket.h
	Copyright (c) 1999-2015, Apple Inc.  All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFSOCKET__)
#define __COREFOUNDATION_CFSOCKET__ 1

#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFData.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFSocket * CFSocketRef;

/* A CFSocket contains a native socket within a structure that can 
be used to read from the socket in the background and make the data
thus read available using a runloop source.  The callback used for
this may be of three types, as specified by the callBackTypes
argument when creating the CFSocket.

If kCFSocketReadCallBack is used, then data will not be
automatically read, but the callback will be called when data
is available to be read, or a new child socket is waiting to be
accepted.
    
If kCFSocketAcceptCallBack is used, then new child sockets will be
accepted and passed to the callback, with the data argument being
a pointer to a CFSocketNativeHandle.  This is usable only with
connection rendezvous sockets.

If kCFSocketDataCallBack is used, then data will be read in chunks
in the background and passed to the callback, with the data argument
being a CFDataRef.

These three types are mutually exclusive, but any one of them may
have kCFSocketConnectCallBack added to it, if the socket will be
used to connect in the background.  Connect in the background occurs
if CFSocketConnectToAddress is called with a negative timeout
value, in which case the call returns immediately, and a
kCFSocketConnectCallBack is generated when the connect finishes.
In this case the data argument is either NULL, or a pointer to
an SInt32 error code if the connect failed.  kCFSocketConnectCallBack
will never be sent more than once for a given socket.

The callback types may also have kCFSocketWriteCallBack added to
them, if large amounts of data are to be sent rapidly over the 
socket and notification is desired when there is space in the
kernel buffers so that the socket is writable again.  

With a connection-oriented socket, if the connection is broken from the
other end, then one final kCFSocketReadCallBack or kCFSocketDataCallBack 
will occur.  In the case of kCFSocketReadCallBack, the underlying socket 
will have 0 bytes available to read.  In the case of kCFSocketDataCallBack,
the data argument will be a CFDataRef of length 0.

There are socket flags that may be set to control whether callbacks of 
a given type are automatically reenabled after they are triggered, and 
whether the underlying native socket will be closed when the CFSocket
is invalidated.  By default read, accept, and data callbacks are 
automatically reenabled; write callbacks are not, and connect callbacks
may not be, since they are sent once only.  Be careful about automatically
reenabling read and write callbacks, since this implies that the 
callbacks will be sent repeatedly if the socket remains readable or
writable respectively.  Be sure to set these flags only for callbacks
that your CFSocket actually possesses; the result of setting them for
other callback types is undefined.

Individual callbacks may also be enabled and disabled manually, whether 
they are automatically reenabled or not.  If they are not automatically 
reenabled, then they will need to be manually reenabled when the callback 
is ready to be received again (and not sooner).  Even if they are 
automatically reenabled, there may be occasions when it will be useful
to be able to manually disable them temporarily and then reenable them.
Be sure to enable and disable only callbacks that your CFSocket actually
possesses; the result of enabling and disabling other callback types is
undefined.

By default the underlying native socket will be closed when the CFSocket 
is invalidated, but it will not be if kCFSocketCloseOnInvalidate is 
turned off.  This can be useful in order to destroy a CFSocket but 
continue to use the underlying native socket.  The CFSocket must 
still be invalidated when it will no longer be used.  Do not in 
either case close the underlying native socket without invalidating 
the CFSocket.

Addresses are stored as CFDatas containing a struct sockaddr
appropriate for the protocol family; make sure that all fields are
filled in properly when passing in an address.  

*/

/* Values for CFSocketError */
typedef CF_ENUM(CFIndex, CFSocketError) {
    kCFSocketSuccess = 0,
    kCFSocketError = -1L,
    kCFSocketTimeout = -2L
};

typedef struct {
    SInt32	protocolFamily;
    SInt32	socketType;
    SInt32	protocol;
    CFDataRef	address;
} CFSocketSignature;

/* Values for CFSocketCallBackType */
typedef CF_OPTIONS(CFOptionFlags, CFSocketCallBackType) {
    kCFSocketNoCallBack = 0,
    kCFSocketReadCallBack = 1,
    kCFSocketAcceptCallBack = 2,
    kCFSocketDataCallBack = 3,
    kCFSocketConnectCallBack = 4,
    kCFSocketWriteCallBack = 8
};

/* Socket flags */
CF_ENUM(CFOptionFlags) {
    kCFSocketAutomaticallyReenableReadCallBack = 1,
    kCFSocketAutomaticallyReenableAcceptCallBack = 2,
    kCFSocketAutomaticallyReenableDataCallBack = 3,
    kCFSocketAutomaticallyReenableWriteCallBack = 8,
    kCFSocketLeaveErrors CF_ENUM_AVAILABLE(10_5, 2_0) = 64,
    kCFSocketCloseOnInvalidate = 128
};

typedef void (*CFSocketCallBack)(CFSocketRef s, CFSocketCallBackType type, CFDataRef address, const void *data, void *info);
/* If the callback wishes to keep hold of address or data after the point that it returns, then it must copy them. */

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFSocketContext;

#if TARGET_OS_WIN32
typedef uintptr_t CFSocketNativeHandle;
#else
typedef int CFSocketNativeHandle;
#endif

CF_EXPORT CFTypeID	CFSocketGetTypeID(void);

CF_EXPORT CFSocketRef	CFSocketCreate(CFAllocatorRef allocator, SInt32 protocolFamily, SInt32 socketType, SInt32 protocol, CFOptionFlags callBackTypes, CFSocketCallBack callout, const CFSocketContext *context);
CF_EXPORT CFSocketRef	CFSocketCreateWithNative(CFAllocatorRef allocator, CFSocketNativeHandle sock, CFOptionFlags callBackTypes, CFSocketCallBack callout, const CFSocketContext *context);
CF_EXPORT CFSocketRef	CFSocketCreateWithSocketSignature(CFAllocatorRef allocator, const CFSocketSignature *signature, CFOptionFlags callBackTypes, CFSocketCallBack callout, const CFSocketContext *context);
/* CFSocketCreateWithSocketSignature() creates a socket of the requested type and binds its address (using CFSocketSetAddress()) to the requested address.  If this fails, it returns NULL. */
CF_EXPORT CFSocketRef	CFSocketCreateConnectedToSocketSignature(CFAllocatorRef allocator, const CFSocketSignature *signature, CFOptionFlags callBackTypes, CFSocketCallBack callout, const CFSocketContext *context, CFTimeInterval timeout);
/* CFSocketCreateConnectedToSocketSignature() creates a socket suitable for connecting to the requested type and address, and connects it (using CFSocketConnectToAddress()).  If this fails, it returns NULL. */

CF_EXPORT CFSocketError	CFSocketSetAddress(CFSocketRef s, CFDataRef address);
CF_EXPORT CFSocketError	CFSocketConnectToAddress(CFSocketRef s, CFDataRef address, CFTimeInterval timeout);
CF_EXPORT void		CFSocketInvalidate(CFSocketRef s);

CF_EXPORT Boolean	CFSocketIsValid(CFSocketRef s);
CF_EXPORT CFDataRef	CFSocketCopyAddress(CFSocketRef s);
CF_EXPORT CFDataRef	CFSocketCopyPeerAddress(CFSocketRef s);
CF_EXPORT void		CFSocketGetContext(CFSocketRef s, CFSocketContext *context);
CF_EXPORT CFSocketNativeHandle	CFSocketGetNative(CFSocketRef s);

CF_EXPORT CFRunLoopSourceRef	CFSocketCreateRunLoopSource(CFAllocatorRef allocator, CFSocketRef s, CFIndex order);

CF_EXPORT CFOptionFlags	CFSocketGetSocketFlags(CFSocketRef s);
CF_EXPORT void		CFSocketSetSocketFlags(CFSocketRef s, CFOptionFlags flags);
CF_EXPORT void		CFSocketDisableCallBacks(CFSocketRef s, CFOptionFlags callBackTypes);
CF_EXPORT void		CFSocketEnableCallBacks(CFSocketRef s, CFOptionFlags callBackTypes);


/* For convenience, a function is provided to send data using the socket with a timeout.  The timeout will be used only if the specified value is positive.  The address should be left NULL if the socket is already connected. */
CF_EXPORT CFSocketError	CFSocketSendData(CFSocketRef s, CFDataRef address, CFDataRef data, CFTimeInterval timeout);

/* Generic name registry functionality (CFSocketRegisterValue, 
CFSocketCopyRegisteredValue) allows the registration of any property
list type.  Functions specific to CFSockets (CFSocketRegisterSocketData,
CFSocketCopyRegisteredSocketData) register a CFData containing the
components of a socket signature (protocol family, socket type,
protocol, and address).  In each function the nameServerSignature
may be NULL, or any component of it may be 0, to use default values
(TCP, INADDR_LOOPBACK, port as set).  Name registration servers might
not allow registration with other than TCP and INADDR_LOOPBACK.
The actual address of the server responding to a query may be obtained
by using the nameServerAddress argument.  This address, the address
returned by CFSocketCopyRegisteredSocketSignature, and the value
returned by CFSocketCopyRegisteredValue must (if non-null) be released
by the caller.  CFSocketUnregister removes any registration associated
with the specified name.
*/

CF_EXPORT CFSocketError	CFSocketRegisterValue(const CFSocketSignature *nameServerSignature, CFTimeInterval timeout, CFStringRef name, CFPropertyListRef value);
CF_EXPORT CFSocketError	CFSocketCopyRegisteredValue(const CFSocketSignature *nameServerSignature, CFTimeInterval timeout, CFStringRef name, CFPropertyListRef *value, CFDataRef *nameServerAddress);

CF_EXPORT CFSocketError	CFSocketRegisterSocketSignature(const CFSocketSignature *nameServerSignature, CFTimeInterval timeout, CFStringRef name, const CFSocketSignature *signature);
CF_EXPORT CFSocketError	CFSocketCopyRegisteredSocketSignature(const CFSocketSignature *nameServerSignature, CFTimeInterval timeout, CFStringRef name, CFSocketSignature *signature, CFDataRef *nameServerAddress);

CF_EXPORT CFSocketError	CFSocketUnregister(const CFSocketSignature *nameServerSignature, CFTimeInterval timeout, CFStringRef name);

CF_EXPORT void		CFSocketSetDefaultNameRegistryPortNumber(UInt16 port);
CF_EXPORT UInt16	CFSocketGetDefaultNameRegistryPortNumber(void);

/* Constants used in name registry server communications */
CF_EXPORT const CFStringRef kCFSocketCommandKey;
CF_EXPORT const CFStringRef kCFSocketNameKey;
CF_EXPORT const CFStringRef kCFSocketValueKey;
CF_EXPORT const CFStringRef kCFSocketResultKey;
CF_EXPORT const CFStringRef kCFSocketErrorKey;
CF_EXPORT const CFStringRef kCFSocketRegisterCommand;
CF_EXPORT const CFStringRef kCFSocketRetrieveCommand;

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFSOCKET__ */

// ==========  CoreFoundation.framework/Headers/CFFileDescriptor.h
/*	CFFileDescriptor.h
	Copyright (c) 2006-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFFILEDESCRIPTOR__)
#define __COREFOUNDATION_CFFILEDESCRIPTOR__ 1

#include <CoreFoundation/CFRunLoop.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef int CFFileDescriptorNativeDescriptor;

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFFileDescriptor * CFFileDescriptorRef;

/* Callback Reason Types */
CF_ENUM(CFOptionFlags) {
    kCFFileDescriptorReadCallBack = 1UL << 0,
    kCFFileDescriptorWriteCallBack = 1UL << 1
};

typedef void (*CFFileDescriptorCallBack)(CFFileDescriptorRef f, CFOptionFlags callBackTypes, void *info);

typedef struct {
    CFIndex	version;
    void *	info;
    void *	(*retain)(void *info);
    void	(*release)(void *info);
    CFStringRef	(*copyDescription)(void *info);
} CFFileDescriptorContext;

CF_EXPORT CFTypeID	CFFileDescriptorGetTypeID(void) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT CFFileDescriptorRef	CFFileDescriptorCreate(CFAllocatorRef allocator, CFFileDescriptorNativeDescriptor fd, Boolean closeOnInvalidate, CFFileDescriptorCallBack callout, const CFFileDescriptorContext *context) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT CFFileDescriptorNativeDescriptor	CFFileDescriptorGetNativeDescriptor(CFFileDescriptorRef f) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT void	 CFFileDescriptorGetContext(CFFileDescriptorRef f, CFFileDescriptorContext *context) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT void	 CFFileDescriptorEnableCallBacks(CFFileDescriptorRef f, CFOptionFlags callBackTypes) CF_AVAILABLE(10_5, 2_0);
CF_EXPORT void	 CFFileDescriptorDisableCallBacks(CFFileDescriptorRef f, CFOptionFlags callBackTypes) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT void	 CFFileDescriptorInvalidate(CFFileDescriptorRef f) CF_AVAILABLE(10_5, 2_0);
CF_EXPORT Boolean	CFFileDescriptorIsValid(CFFileDescriptorRef f) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT CFRunLoopSourceRef	CFFileDescriptorCreateRunLoopSource(CFAllocatorRef allocator, CFFileDescriptorRef f, CFIndex order) CF_AVAILABLE(10_5, 2_0);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFFILEDESCRIPTOR__ */

// ==========  CoreFoundation.framework/Headers/CFURL.h
/*	CFURL.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFURL__)
#define __COREFOUNDATION_CFURL__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef CF_ENUM(CFIndex, CFURLPathStyle) {
    kCFURLPOSIXPathStyle = 0,
    kCFURLHFSPathStyle CF_ENUM_DEPRECATED(10_0, 10_9, 2_0, 7_0), /* The use of kCFURLHFSPathStyle is deprecated. The Carbon File Manager, which uses HFS style paths, is deprecated. HFS style paths are unreliable because they can arbitrarily refer to multiple volumes if those volumes have identical volume names. You should instead use kCFURLPOSIXPathStyle wherever possible. */
    kCFURLWindowsPathStyle
};
    
typedef const struct CF_BRIDGED_TYPE(NSURL) __CFURL * CFURLRef;

/* CFURLs are composed of two fundamental pieces - their string, and a */
/* (possibly NULL) base URL.  A relative URL is one in which the string */
/* by itself does not fully specify the URL (for instance "myDir/image.tiff"); */
/* an absolute URL is one in which the string does fully specify the URL */
/* ("file://localhost/myDir/image.tiff").  Absolute URLs always have NULL */
/* base URLs; however, it is possible for a URL to have a NULL base, and still */
/* not be absolute.  Such a URL has only a relative string, and cannot be */
/* resolved.  Two CFURLs are considered equal if and only if their strings */
/* are equal and their bases are equal.  In other words, */
/* "file://localhost/myDir/image.tiff" is NOT equal to the URL with relative */
/* string "myDir/image.tiff" and base URL "file://localhost/".  Clients that */
/* need these less strict form of equality should convert all URLs to their */
/* absolute form via CFURLCopyAbsoluteURL(), then compare the absolute forms. */

CF_EXPORT
CFTypeID CFURLGetTypeID(void);

/* encoding will be used both to interpret the bytes of URLBytes, and to */
/* interpret any percent-escapes within the bytes. */
/* Using a string encoding which isn't a superset of ASCII encoding is not */
/* supported because CFURLGetBytes and CFURLGetByteRangeForComponent require */
/* 7-bit ASCII characters to be stored in a single 8-bit byte. */
/* CFStringEncodings which are a superset of ASCII encoding include MacRoman, */
/* WindowsLatin1, ISOLatin1, NextStepLatin, ASCII, and UTF8. */
CF_EXPORT
CFURLRef CFURLCreateWithBytes(CFAllocatorRef allocator, const UInt8 *URLBytes, CFIndex length, CFStringEncoding encoding, CFURLRef baseURL);

/* Escapes any character that is not 7-bit ASCII with the byte-code */
/* for the given encoding.  If escapeWhitespace is true, whitespace */
/* characters (' ', '\t', '\r', '\n') will be escaped also (desirable */
/* if embedding the URL into a larger text stream like HTML) */
CF_EXPORT
CFDataRef CFURLCreateData(CFAllocatorRef allocator, CFURLRef url, CFStringEncoding encoding, Boolean escapeWhitespace);

/* Any escape sequences in URLString will be interpreted via UTF-8. */
CF_EXPORT
CFURLRef CFURLCreateWithString(CFAllocatorRef allocator, CFStringRef URLString, CFURLRef baseURL);

/* Create an absolute URL directly, without requiring the extra step */
/* of calling CFURLCopyAbsoluteURL().  If useCompatibilityMode is  */
/* true, the rules historically used on the web are used to resolve */
/* relativeString against baseURL - these rules are generally listed */
/* in the RFC as optional or alternate interpretations.  Otherwise, */
/* the strict rules from the RFC are used.  The major differences are */
/* that in compatibility mode, we are lenient of the scheme appearing */
/* in relative portion, leading "../" components are removed from the */
/* final URL's path, and if the relative portion contains only */
/* resource specifier pieces (query, parameters, and fragment), then */
/* the last path component of the base URL will not be deleted.  */
/* Using a string encoding which isn't a superset of ASCII encoding is not */
/* supported because CFURLGetBytes and CFURLGetByteRangeForComponent require */
/* 7-bit ASCII characters to be stored in a single 8-bit byte. */
/* CFStringEncodings which are a superset of ASCII encoding include MacRoman, */
/* WindowsLatin1, ISOLatin1, NextStepLatin, ASCII, and UTF8. */
CF_EXPORT
CFURLRef CFURLCreateAbsoluteURLWithBytes(CFAllocatorRef alloc, const UInt8 *relativeURLBytes, CFIndex length, CFStringEncoding encoding, CFURLRef baseURL, Boolean useCompatibilityMode);

/* filePath should be the URL's path expressed as a path of the type */
/* fsType.  If filePath is not absolute, the resulting URL will be */
/* considered relative to the current working directory (evaluated */
/* at creation time).  isDirectory determines whether filePath is */
/* treated as a directory path when resolving against relative path */
/* components */
CF_EXPORT
CFURLRef CFURLCreateWithFileSystemPath(CFAllocatorRef allocator, CFStringRef filePath, CFURLPathStyle pathStyle, Boolean isDirectory);

CF_EXPORT
CFURLRef CFURLCreateFromFileSystemRepresentation(CFAllocatorRef allocator, const UInt8 *buffer, CFIndex bufLen, Boolean isDirectory);

/* The path style of the baseURL must match the path style of the relative */
/* url or the results are undefined.  If the provided filePath looks like an */
/* absolute path ( starting with '/' if pathStyle is kCFURLPosixPathStyle, */
/* not starting with ':' for kCFURLHFSPathStyle, or starting with what looks */
/* like a drive letter and colon for kCFURLWindowsPathStyle ) then the baseURL */
/* is ignored. */
CF_EXPORT
CFURLRef CFURLCreateWithFileSystemPathRelativeToBase(CFAllocatorRef allocator, CFStringRef filePath, CFURLPathStyle pathStyle, Boolean isDirectory, CFURLRef baseURL); 

CF_EXPORT
CFURLRef CFURLCreateFromFileSystemRepresentationRelativeToBase(CFAllocatorRef allocator, const UInt8 *buffer, CFIndex bufLen, Boolean isDirectory, CFURLRef baseURL);
                                                                         
/* Fills buffer with the file system's native representation of */
/* url's path. No more than maxBufLen bytes are written to buffer. */
/* The buffer should be at least the maximum path length for */
/* the file system in question to avoid failures for insufficiently */
/* large buffers.  If resolveAgainstBase is true, the url's relative */
/* portion is resolved against its base before the path is computed. */
/* Returns success or failure. */
CF_EXPORT
Boolean CFURLGetFileSystemRepresentation(CFURLRef url, Boolean resolveAgainstBase, UInt8 *buffer, CFIndex maxBufLen);

/* Creates a new URL by resolving the relative portion of relativeURL against its base. */
CF_EXPORT
CFURLRef CFURLCopyAbsoluteURL(CFURLRef relativeURL);

/* Returns the URL's string. */
CF_EXPORT
CFStringRef CFURLGetString(CFURLRef anURL);

/* Returns the base URL if it exists */
CF_EXPORT
CFURLRef CFURLGetBaseURL(CFURLRef anURL);

/*
All URLs can be broken into two pieces - the scheme (preceding the
first colon) and the resource specifier (following the first colon).
Most URLs are also "standard" URLs conforming to RFC 1808 (available
from www.w3c.org).  This category includes URLs of the file, http,
https, and ftp schemes, to name a few.  Standard URLs start the
resource specifier with two slashes ("//"), and can be broken into
four distinct pieces - the scheme, the net location, the path, and
further resource specifiers (typically an optional parameter, query,
and/or fragment).  The net location appears immediately following
the two slashes and goes up to the next slash; it's format is
scheme-specific, but is usually composed of some or all of a username,
password, host name, and port.  The path is a series of path components
separated by slashes; if the net location is present, the path always
begins with a slash.  Standard URLs can be relative to another URL,
in which case at least the scheme and possibly other pieces as well
come from the base URL (see RFC 1808 for precise details when resolving
a relative URL against its base).  The full URL is therefore

<scheme> "://" <net location> <path, always starting with slash> <add'l resource specifiers>

If a given CFURL can be decomposed (that is, conforms to RFC 1808), you
can ask for each of the four basic pieces (scheme, net location, path,
and resource specifer) separately, as well as for its base URL.  The
basic pieces are returned with any percent escape sequences still in
place (although note that the scheme may not legally include any
percent escapes); this is to allow the caller to distinguish between
percent sequences that may have syntactic meaning if replaced by the
character being escaped (for instance, a '/' in a path component).
Since only the individual schemes know which characters are
syntactically significant, CFURL cannot safely replace any percent
escape sequences.  However, you can use
CFURLCreateStringByReplacingPercentEscapes() to create a new string with
the percent escapes removed; see below.

If a given CFURL can not be decomposed, you can ask for its scheme and its
resource specifier; asking it for its net location or path will return NULL.

To get more refined information about the components of a decomposable
CFURL, you may ask for more specific pieces of the URL, expressed with
the percent escapes removed.  The available functions are CFURLCopyHostName(),
CFURLGetPortNumber() (returns an Int32), CFURLCopyUserName(),
CFURLCopyPassword(), CFURLCopyQuery(), CFURLCopyParameters(), and
CFURLCopyFragment().  Because the parameters, query, and fragment of an
URL may contain scheme-specific syntaxes, these methods take a second
argument, giving a list of characters which should NOT be replaced if
percent escaped.  For instance, the ftp parameter syntax gives simple
key-value pairs as "<key>=<value>;"  Clearly if a key or value includes
either '=' or ';', it must be escaped to avoid corrupting the meaning of
the parameters, so the caller may request the parameter string as

CFStringRef myParams = CFURLCopyParameters(ftpURL, CFSTR("=;%"));

requesting that all percent escape sequences be replaced by the represented
characters, except for escaped '=', '%' or ';' characters.  Pass the empty
string (CFSTR("")) to request that all percent escapes be replaced, or NULL
to request that none be.
*/

/* Returns true if anURL conforms to RFC 1808 */
CF_EXPORT
Boolean CFURLCanBeDecomposed(CFURLRef anURL); 

/* The next several methods leave any percent escape sequences intact */

CF_EXPORT
CFStringRef CFURLCopyScheme(CFURLRef anURL);

/* NULL if CFURLCanBeDecomposed(anURL) is false */
CF_EXPORT
CFStringRef CFURLCopyNetLocation(CFURLRef anURL); 

/* NULL if CFURLCanBeDecomposed(anURL) is false; also does not resolve the URL */
/* against its base.  See also CFURLCopyAbsoluteURL().  Note that, strictly */
/* speaking, any leading '/' is not considered part of the URL's path, although */
/* its presence or absence determines whether the path is absolute. */
/* CFURLCopyPath()'s return value includes any leading slash (giving the path */
/* the normal POSIX appearance); CFURLCopyStrictPath()'s return value omits any */
/* leading slash, and uses isAbsolute to report whether the URL's path is absolute. */

/* CFURLCopyFileSystemPath() returns the URL's path as a file system path for the */
/* given path style.  All percent escape sequences are replaced.  The URL is not */
/* resolved against its base before computing the path. */
CF_EXPORT
CFStringRef CFURLCopyPath(CFURLRef anURL);

CF_EXPORT
CFStringRef CFURLCopyStrictPath(CFURLRef anURL, Boolean *isAbsolute);

CF_EXPORT
CFStringRef CFURLCopyFileSystemPath(CFURLRef anURL, CFURLPathStyle pathStyle);

/* Returns whether anURL's path represents a directory */
/* (true returned) or a simple file (false returned) */
CF_EXPORT
Boolean CFURLHasDirectoryPath(CFURLRef anURL);

/* Any additional resource specifiers after the path.  For URLs */
/* that cannot be decomposed, this is everything except the scheme itself. */
CF_EXPORT
CFStringRef CFURLCopyResourceSpecifier(CFURLRef anURL); 

CF_EXPORT
CFStringRef CFURLCopyHostName(CFURLRef anURL);

CF_EXPORT
SInt32 CFURLGetPortNumber(CFURLRef anURL); /* Returns -1 if no port number is specified */

CF_EXPORT
CFStringRef CFURLCopyUserName(CFURLRef anURL);

CF_EXPORT
CFStringRef CFURLCopyPassword(CFURLRef anURL);

/* These remove all percent escape sequences except those for */
/* characters in charactersToLeaveEscaped.  If charactersToLeaveEscaped */
/* is empty (""), all percent escape sequences are replaced by their */
/* corresponding characters.  If charactersToLeaveEscaped is NULL, */
/* then no escape sequences are removed at all */
CF_EXPORT
CFStringRef CFURLCopyParameterString(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyQueryString(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyFragment(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyLastPathComponent(CFURLRef url);

CF_EXPORT
CFStringRef CFURLCopyPathExtension(CFURLRef url);

/* These functions all treat the base URL of the supplied url as */
/* invariant.  In other words, the URL returned will always have */
/* the same base as the URL supplied as an argument. */

CF_EXPORT
CFURLRef CFURLCreateCopyAppendingPathComponent(CFAllocatorRef allocator, CFURLRef url, CFStringRef pathComponent, Boolean isDirectory);

CF_EXPORT
CFURLRef CFURLCreateCopyDeletingLastPathComponent(CFAllocatorRef allocator, CFURLRef url);

CF_EXPORT
CFURLRef CFURLCreateCopyAppendingPathExtension(CFAllocatorRef allocator, CFURLRef url, CFStringRef extension);

CF_EXPORT
CFURLRef CFURLCreateCopyDeletingPathExtension(CFAllocatorRef allocator, CFURLRef url);

/* Fills buffer with the bytes for url, returning the number of bytes */
/* filled.  If buffer is of insufficient size, returns -1 and no bytes */
/* are placed in buffer.  If buffer is NULL, the needed length is */
/* computed and returned.  The returned bytes are the original bytes */ 
/* from which the URL was created; if the URL was created from a */
/* string, the bytes will be the bytes of the string encoded via UTF-8  */
CF_EXPORT
CFIndex CFURLGetBytes(CFURLRef url, UInt8 *buffer, CFIndex bufferLength);

typedef CF_ENUM(CFIndex, CFURLComponentType) {
	kCFURLComponentScheme = 1,
	kCFURLComponentNetLocation = 2,
	kCFURLComponentPath = 3,
	kCFURLComponentResourceSpecifier = 4,

	kCFURLComponentUser = 5,
	kCFURLComponentPassword = 6,
	kCFURLComponentUserInfo = 7,
	kCFURLComponentHost = 8,
	kCFURLComponentPort = 9,
	kCFURLComponentParameterString = 10,
	kCFURLComponentQuery = 11,
	kCFURLComponentFragment = 12
};
 
/* 
Gets the  range of the requested component in the bytes of url, as
returned by CFURLGetBytes().  This range is only good for use in the
bytes returned by CFURLGetBytes!

If non-NULL, rangeIncludingSeparators gives the range of component
including the sequences that separate component from the previous and
next components.  If there is no previous or next component, that end of
rangeIncludingSeparators will match the range of the component itself.
If url does not contain the given component type, (kCFNotFound, 0) is
returned, and rangeIncludingSeparators is set to the location where the
component would be inserted.  Some examples -

For the URL http://www.apple.com/hotnews/

Component           returned range      rangeIncludingSeparators
scheme              (0, 4)              (0, 7)
net location        (7, 13)             (4, 16)
path                (20, 9)             (20, 9)    
resource specifier  (kCFNotFound, 0)    (29, 0)
user                (kCFNotFound, 0)    (7, 0)
password            (kCFNotFound, 0)    (7, 0)
user info           (kCFNotFound, 0)    (7, 0)
host                (7, 13)             (4, 16)
port                (kCFNotFound, 0)    (20, 0)
parameter           (kCFNotFound, 0)    (29, 0)
query               (kCFNotFound, 0)    (29, 0)
fragment            (kCFNotFound, 0)    (29, 0)


For the URL ./relPath/file.html#fragment

Component           returned range      rangeIncludingSeparators
scheme              (kCFNotFound, 0)    (0, 0)
net location        (kCFNotFound, 0)    (0, 0)
path                (0, 19)             (0, 20)
resource specifier  (20, 8)             (19, 9)
user                (kCFNotFound, 0)    (0, 0)
password            (kCFNotFound, 0)    (0, 0)
user info           (kCFNotFound, 0)    (0, 0)
host                (kCFNotFound, 0)    (0, 0)
port                (kCFNotFound, 0)    (0, 0)
parameter           (kCFNotFound, 0)    (19, 0)
query               (kCFNotFound, 0)    (19, 0)
fragment            (20, 8)             (19, 9)


For the URL scheme://user:pass@host:1/path/path2/file.html;params?query#fragment

Component           returned range      rangeIncludingSeparators
scheme              (0, 6)              (0, 9)
net location        (9, 16)             (6, 19)
path                (25, 21)            (25, 22) 
resource specifier  (47, 21)            (46, 22)
user                (9, 4)              (6, 8)
password            (14, 4)             (13, 6)
user info           (9, 9)              (6, 13)
host                (19, 4)             (18, 6)
port                (24, 1)             (23, 2)
parameter           (47, 6)             (46, 8)
query               (54, 5)             (53, 7)
fragment            (60, 8)             (59, 9)
*/
CF_EXPORT
CFRange CFURLGetByteRangeForComponent(CFURLRef url, CFURLComponentType component, CFRange *rangeIncludingSeparators);

/* Returns a string with any percent escape sequences that do NOT */
/* correspond to characters in charactersToLeaveEscaped with their */
/* equivalent.  Returns NULL on failure (if an invalid percent sequence */
/* is encountered), or the original string (retained) if no characters */
/* need to be replaced. Pass NULL to request that no percent escapes be */
/* replaced, or the empty string (CFSTR("")) to request that all percent */
/* escapes be replaced.  Uses UTF8 to interpret percent escapes. */
CF_EXPORT
CFStringRef CFURLCreateStringByReplacingPercentEscapes(CFAllocatorRef allocator, CFStringRef originalString, CFStringRef charactersToLeaveEscaped);

/* As above, but allows you to specify the encoding to use when interpreting percent escapes */
CF_EXPORT
CFStringRef CFURLCreateStringByReplacingPercentEscapesUsingEncoding(CFAllocatorRef allocator, CFStringRef origString, CFStringRef charsToLeaveEscaped, CFStringEncoding encoding) CF_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use [NSString stringByRemovingPercentEncoding] or CFURLCreateStringByReplacingPercentEscapes() instead, which always uses the recommended UTF-8 encoding.");

/* Creates a copy or originalString, replacing certain characters with */
/* the equivalent percent escape sequence based on the encoding specified. */
/* If the originalString does not need to be modified (no percent escape */
/* sequences are missing), may retain and return originalString. */
/* If you are uncertain of the correct encoding, you should use UTF-8, */
/* which is the encoding designated by RFC 2396 as the correct encoding */
/* for use in URLs.  The characters so escaped are all characters that */
/* are not legal URL characters (based on RFC 2396), plus any characters */
/* in legalURLCharactersToBeEscaped, less any characters in */
/* charactersToLeaveUnescaped.  To simply correct any non-URL characters */
/* in an otherwise correct URL string, do: */
/*      newString = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, origString, NULL, NULL, kCFStringEncodingUTF8); */
CF_EXPORT
CFStringRef CFURLCreateStringByAddingPercentEscapes(CFAllocatorRef allocator, CFStringRef originalString, CFStringRef charactersToLeaveUnescaped, CFStringRef legalURLCharactersToBeEscaped, CFStringEncoding encoding) CF_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use [NSString stringByAddingPercentEncodingWithAllowedCharacters:] instead, which always uses the recommended UTF-8 encoding, and which encodes for a specific URL component or subcomponent (since each URL component or subcomponent has different rules for what characters are valid).");


#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || CF_BUILDING_CF || NSBUILDINGFOUNDATION
CF_IMPLICIT_BRIDGING_DISABLED

/*
    CFURLIsFileReferenceURL

    Returns whether the URL is a file reference URL.

    Parameters
        url
            The URL specifying the resource.
 */
CF_EXPORT
Boolean CFURLIsFileReferenceURL(CFURLRef url) CF_AVAILABLE(10_9, 7_0);

/*
    CFURLCreateFileReferenceURL
    
    Returns a new file reference URL that refers to the same resource as a specified URL.

    Parameters
        allocator
            The memory allocator for creating the new URL.
        url
            The file URL specifying the resource.
        error
            On output when the result is NULL, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        The new file reference URL, or NULL if an error occurs.

    Discussion
        File reference URLs use a URL path syntax that identifies a file system object by reference, not by path. This form of file URL remains valid when the file system path of the URL’s underlying resource changes. An error will occur if the url parameter is not a file URL. File reference URLs cannot be created to file system objects which do not exist or are not reachable. In some areas of the file system hierarchy, file reference URLs cannot be generated to the leaf node of the URL path. A file reference URL's path should never be persistently stored because is not valid across system restarts, and across remounts of volumes -- if you want to create a persistent reference to a file system object, use a bookmark (see CFURLCreateBookmarkData). If this function returns NULL, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
CFURLRef CFURLCreateFileReferenceURL(CFAllocatorRef allocator, CFURLRef url, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLCreateFilePathURL
    
    Returns a new file path URL that refers to the same resource as a specified URL.

    Parameters
        allocator
            The memory allocator for creating the new URL.
        url
            The file URL specifying the resource.
        error
            On output when the result is NULL, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        The new file path URL, or NULL if an error occurs.

    Discussion
        File path URLs use a file system style path. An error will occur if the url parameter is not a file URL. A file reference URL's resource must exist and be reachable to be converted to a file path URL. If this function returns NULL, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
CFURLRef CFURLCreateFilePathURL(CFAllocatorRef allocator, CFURLRef url, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

CF_IMPLICIT_BRIDGING_ENABLED
#endif

#ifndef CF_OPEN_SOURCE
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

struct FSRef;

// Note: CFURLCreateFromFSRef and CFURLGetFSRef have never been functional on iOS because the Carbon File Manager is not on iOS.

CF_EXPORT
CFURLRef CFURLCreateFromFSRef(CFAllocatorRef allocator, const struct FSRef *fsRef) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0);

CF_EXPORT
Boolean CFURLGetFSRef(CFURLRef url, struct FSRef *fsRef) CF_DEPRECATED(10_0, 10_9, 2_0, 7_0);

#endif
#endif


#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || CF_BUILDING_CF || NSBUILDINGFOUNDATION
CF_IMPLICIT_BRIDGING_DISABLED

/* Resource access

    The behavior of resource value caching is slightly different between the NSURL and CFURL API.

    When the NSURL methods which get, set, or use cached resource values are used from the main thread, resource values cached by the URL (except those added as temporary properties) are invalidated the next time the main thread's run loop runs.

    The CFURL functions do not automatically clear any resource values cached by the URL. The client has complete control over the cache lifetime. If you are using CFURL API, you must use CFURLClearResourcePropertyCacheForKey or CFURLClearResourcePropertyCache to clear cached resource values.
 */


/*
    CFURLCopyResourcePropertyForKey
    
    Returns the resource value identified by a given resource key.

    Parameters
        url
            The URL specifying the resource.
        key
            The resource key that identifies the resource property.
        propertyValueTypeRefPtr
            On output when the result is true, the resource value or NULL.
        error
            On output when the result is false, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        true if propertyValueTypeRefPtr is successfully populated; false if an error occurs.

    Discussion
        CFURLCopyResourcePropertyForKey first checks if the URL object already caches the resource value. If so, it returns the cached resource value to the caller. If not, then CFURLCopyResourcePropertyForKey synchronously obtains the resource value from the backing store, adds the resource value to the URL object's cache, and returns the resource value to the caller. The type of the resource value varies by resource property (see resource key definitions). If this function returns true and propertyValueTypeRefPtr is populated with NULL, it means the resource property is not available for the specified resource and no errors occurred when determining the resource property was not available. If this function returns false, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
Boolean CFURLCopyResourcePropertyForKey(CFURLRef url, CFStringRef key, void *propertyValueTypeRefPtr, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLCopyResourcePropertiesForKeys
    
    Returns the resource values identified by specified array of resource keys.

    Parameters
        url
            The URL specifying the resource.
        keys
            An array of resource keys that identify the resource properties.
        error
            On output when the result is NULL, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        A dictionary of resource values indexed by resource key; NULL if an error occurs.

    Discussion
        CFURLCopyResourcePropertiesForKeys first checks if the URL object already caches the resource values. If so, it returns the cached resource values to the caller. If not, then CFURLCopyResourcePropertyForKey synchronously obtains the resource values from the backing store, adds the resource values to the URL object's cache, and returns the resource values to the caller. The type of the resource values vary by property (see resource key definitions). If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available for the specified resource and no errors occurred when determining those resource properties were not available. If this function returns NULL, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
CFDictionaryRef CFURLCopyResourcePropertiesForKeys(CFURLRef url, CFArrayRef keys, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLSetResourcePropertyForKey
    
    Sets the resource value identified by a given resource key.

    Parameters
        url
            The URL specifying the resource.
        key
            The resource key that identifies the resource property.
        propertyValue
            The resource value.
        error
            On output when the result is false, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        true if the attempt to set the resource value completed with no errors; otherwise, false.

    Discussion
        CFURLSetResourcePropertyForKey writes the new resource value out to the backing store. Attempts to set a read-only resource property or to set a resource property not supported by the resource are ignored and are not considered errors. If this function returns false, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
Boolean CFURLSetResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertyValue, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLSetResourcePropertiesForKeys
    
    Sets any number of resource values of a URL's resource.

    Parameters
        url
            The URL specifying the resource.
        keyedPropertyValues
            A dictionary of resource values indexed by resource keys.
        error
            On output when the result is false, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        true if the attempt to set the resource values completed with no errors; otherwise, false.

    Discussion
        CFURLSetResourcePropertiesForKeys writes the new resource values out to the backing store. Attempts to set read-only resource properties or to set resource properties not supported by the resource are ignored and are not considered errors. If an error occurs after some resource properties have been successfully changed, the userInfo dictionary in the returned error contains an array of resource keys that were not set with the key kCFURLKeysOfUnsetValuesKey. The order in which the resource values are set is not defined. If you need to guarantee the order resource values are set, you should make multiple requests to CFURLSetResourcePropertiesForKeys or CFURLSetResourcePropertyForKey to guarantee the order. If this function returns false, the optional error is populated. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
Boolean CFURLSetResourcePropertiesForKeys(CFURLRef url, CFDictionaryRef keyedPropertyValues, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);


CF_EXPORT
const CFStringRef kCFURLKeysOfUnsetValuesKey CF_AVAILABLE(10_7, 5_0);
    /* Key for the resource properties that have not been set after the CFURLSetResourcePropertiesForKeys function returns an error, returned as an array of of CFString objects. */


/*
    CFURLClearResourcePropertyCacheForKey
    
    Discards a cached resource value of a URL.

    Parameters
        url
            The URL specifying the resource.
        key
            The resource key that identifies the resource property.

    Discussion
        Discarding a cached resource value may discard other cached resource values, because some resource values are cached as a set of values and because some resource values depend on other resource values (temporary properties have no dependencies). This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
void CFURLClearResourcePropertyCacheForKey(CFURLRef url, CFStringRef key) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLClearResourcePropertyCache
    
    Discards all cached resource values of a URL.

    Parameters
        url
            The URL specifying the resource.

    Discussion
        All temporary properties are also cleared from the URL object's cache. This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
void CFURLClearResourcePropertyCache(CFURLRef url) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLSetTemporaryResourcePropertyForKey
    
    Sets a temporary resource value on the URL object.

    Parameters
        url
            The URL object.
        key
            The resource key that identifies the temporary resource property.
        propertyValue
            The resource value.

    Discussion
        Temporary properties are for client use. Temporary properties exist only in memory and are never written to the resource's backing store. Once set, a temporary value can be copied from the URL object with CFURLCopyResourcePropertyForKey and CFURLCopyResourcePropertiesForKeys. To remove a temporary value from the URL object, use CFURLClearResourcePropertyCacheForKey. Temporary values must be valid Core Foundation types, and will be retained by CFURLSetTemporaryResourcePropertyForKey. Care should be taken to ensure the key that identifies a temporary resource property is unique and does not conflict with system defined keys (using reverse domain name notation in your temporary resource property keys is recommended). This function is currently applicable only to URLs for file system resources.
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
void CFURLSetTemporaryResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertyValue) CF_AVAILABLE(10_6, 4_0);


/*
    CFURLResourceIsReachable
    
    Returns whether the URL's resource exists and is reachable.

    Parameters
        url
            The URL object.
        error
            On output when the result is false, the error that occurred. This parameter is optional; if you do not wish the error returned, pass NULL here. The caller is responsible for releasing a valid output error.

    Return Value
        true if the resource is reachable; otherwise, false.

    Discussion
        CFURLResourceIsReachable synchronously checks if the resource's backing store is reachable. Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file or copying resource properties, it is more efficient to simply try the operation and handle failures. This function is currently applicable only to URLs for file system resources. If this function returns false, the optional error is populated. For other URL types, false is returned. 
        Symbol is present in iOS 4, but performs no operation.
 */
CF_EXPORT
Boolean CFURLResourceIsReachable(CFURLRef url, CFErrorRef *error) CF_AVAILABLE(10_6, 4_0);

CF_IMPLICIT_BRIDGING_ENABLED


/* Properties of File System Resources */

CF_EXPORT 
const CFStringRef kCFURLNameKey CF_AVAILABLE(10_6, 4_0);
    /* The resource name provided by the file system (Read-write, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedNameKey CF_AVAILABLE(10_6, 4_0);
    /* Localized or extension-hidden name as displayed to users (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLIsRegularFileKey CF_AVAILABLE(10_6, 4_0);
    /* True for regular files (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsDirectoryKey CF_AVAILABLE(10_6, 4_0);
    /* True for directories (Read-only, CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSymbolicLinkKey CF_AVAILABLE(10_6, 4_0);
    /* True for symlinks (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsVolumeKey CF_AVAILABLE(10_6, 4_0);
    /* True for the root directory of a volume (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsPackageKey CF_AVAILABLE(10_6, 4_0);
    /* True for packaged directories (Read-only 10_6 and 10_7, read-write 10_8, value type CFBoolean). Note: You can only set or clear this property on directories; if you try to set this property on non-directory objects, the property is ignored. If the directory is a package for some other reason (extension type, etc), setting this property to false will have no effect. */

CF_EXPORT
const CFStringRef kCFURLIsApplicationKey CF_AVAILABLE(10_11, 9_0);
    /* True if resource is an application (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLApplicationIsScriptableKey CF_AVAILABLE(10_11, NA);
    /* True if the resource is scriptable. Only applies to applications. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSystemImmutableKey CF_AVAILABLE(10_6, 4_0);
    /* True for system-immutable resources (Read-write, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsUserImmutableKey CF_AVAILABLE(10_6, 4_0);
    /* True for user-immutable resources (Read-write, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsHiddenKey CF_AVAILABLE(10_6, 4_0);
    /* True for resources normally not displayed to users (Read-write, value type CFBoolean). Note: If the resource is a hidden because its name starts with a period, setting this property to false will not change the property. */

CF_EXPORT
const CFStringRef kCFURLHasHiddenExtensionKey CF_AVAILABLE(10_6, 4_0);
    /* True for resources whose filename extension is removed from the localized name property (Read-write, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLCreationDateKey CF_AVAILABLE(10_6, 4_0);
    /* The date the resource was created (Read-write, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLContentAccessDateKey CF_AVAILABLE(10_6, 4_0);
    /* The date the resource was last accessed (Read-only, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLContentModificationDateKey CF_AVAILABLE(10_6, 4_0);
    /* The time the resource content was last modified (Read-write, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLAttributeModificationDateKey CF_AVAILABLE(10_6, 4_0);
    /* The time the resource's attributes were last modified (Read-write, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLLinkCountKey CF_AVAILABLE(10_6, 4_0);
    /* Number of hard links to the resource (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLParentDirectoryURLKey CF_AVAILABLE(10_6, 4_0);
    /* The resource's parent directory, if any (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLVolumeURLKey CF_AVAILABLE(10_6, 4_0);
    /* URL of the volume on which the resource is stored (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLTypeIdentifierKey CF_AVAILABLE(10_6, 4_0);
    /* Uniform type identifier (UTI) for the resource (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedTypeDescriptionKey CF_AVAILABLE(10_6, 4_0);
    /* User-visible type or "kind" description (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLabelNumberKey CF_AVAILABLE(10_6, 4_0);
    /* The label number assigned to the resource (Read-write, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLLabelColorKey CF_AVAILABLE(10_6, 4_0);
    /* The color of the assigned label (Currently not implemented, value type CGColorRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLLocalizedLabelKey CF_AVAILABLE(10_6, 4_0);
    /* The user-visible label text (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLEffectiveIconKey CF_AVAILABLE(10_6, 4_0);
    /* The icon normally displayed for the resource (Read-only, value type CGImageRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLCustomIconKey CF_AVAILABLE(10_6, 4_0);
    /* The custom icon assigned to the resource, if any (Currently not implemented, value type CGImageRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLFileResourceIdentifierKey CF_AVAILABLE(10_7, 5_0);
    /* An identifier which can be used to compare two file system objects for equality using CFEqual (i.e, two object identifiers are equal if they have the same file system path or if the paths are linked to same inode on the same file system). This identifier is not persistent across system restarts. (Read-only, value type CFType) */

CF_EXPORT
const CFStringRef kCFURLVolumeIdentifierKey CF_AVAILABLE(10_7, 5_0);
    /* An identifier that can be used to identify the volume the file system object is on. Other objects on the same volume will have the same volume identifier and can be compared using for equality using CFEqual. This identifier is not persistent across system restarts. (Read-only, value type CFType) */

CF_EXPORT
const CFStringRef kCFURLPreferredIOBlockSizeKey CF_AVAILABLE(10_7, 5_0);
    /* The optimal block size when reading or writing this file's data, or NULL if not available. (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLIsReadableKey CF_AVAILABLE(10_7, 5_0);
    /* true if this process (as determined by EUID) can read the resource. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsWritableKey CF_AVAILABLE(10_7, 5_0);
    /* true if this process (as determined by EUID) can write to the resource. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsExecutableKey CF_AVAILABLE(10_7, 5_0);
    /* true if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLFileSecurityKey CF_AVAILABLE(10_7, 5_0);
    /* The file system object's security information encapsulated in a CFFileSecurity object. (Read-write, value type CFFileSecurity) */

CF_EXPORT
const CFStringRef kCFURLIsExcludedFromBackupKey CF_AVAILABLE(10_8, 5_1);
    /* true if resource should be excluded from backups, false otherwise (Read-write, value type CFBoolean). This property is only useful for excluding cache and other application support files which are not needed in a backup. Some operations commonly made to user documents will cause this property to be reset to false and so this property should not be used on user documents. */

CF_EXPORT
const CFStringRef kCFURLTagNamesKey CF_AVAILABLE(10_9, NA);
    /* The array of Tag names (Read-write, value type CFArray of CFString) */
    
CF_EXPORT
const CFStringRef kCFURLPathKey CF_AVAILABLE(10_8, 6_0);
    /* the URL's path as a file system path (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLIsMountTriggerKey CF_AVAILABLE(10_7, 4_0);
    /* true if this URL is a file system trigger directory. Traversing or opening a file system trigger will cause an attempt to mount a file system on the trigger directory. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLGenerationIdentifierKey CF_AVAILABLE(10_10, 8_0);
    /* An opaque generation identifier which can be compared using CFEqual() to determine if the data in a document has been modified. For URLs which refer to the same file inode, the generation identifier will change when the data in the file's data fork is changed (changes to extended attributes or other file system metadata do not change the generation identifier). For URLs which refer to the same directory inode, the generation identifier will change when direct children of that directory are added, removed or renamed (changes to the data of the direct children of that directory will not change the generation identifier). The generation identifier is persistent across system restarts. The generation identifier is tied to a specific document on a specific volume and is not transferred when the document is copied to another volume. This property is not supported by all volumes. (Read-only, value type CFType) */

CF_EXPORT
const CFStringRef kCFURLDocumentIdentifierKey CF_AVAILABLE(10_10, 8_0);
    /* The document identifier -- a value assigned by the kernel to a document (which can be either a file or directory) and is used to identify the document regardless of where it gets moved on a volume. The document identifier survives "safe save” operations; i.e it is sticky to the path it was assigned to (-replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is the preferred safe-save API). The document identifier is persistent across system restarts. The document identifier is not transferred when the file is copied. Document identifiers are only unique within a single volume. This property is not supported by all volumes. (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLAddedToDirectoryDateKey CF_AVAILABLE(10_10, 8_0);
    /* The date the resource was created, or renamed into or within its parent directory. Note that inconsistent behavior may be observed when this attribute is requested on hard-linked items. This property is not supported by all volumes. (Read-only, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLQuarantinePropertiesKey CF_AVAILABLE(10_10, NA);
    /* The quarantine properties as defined in LSQuarantine.h. To remove quarantine information from a file, pass kCFNull as the value when setting this property. (Read-write, value type CFDictionary) */

CF_EXPORT
const CFStringRef kCFURLFileResourceTypeKey CF_AVAILABLE(10_7, 5_0);
    /* Returns the file system object type. (Read-only, value type CFString) */

/* The file system object type values returned for the kCFURLFileResourceTypeKey */
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeNamedPipe CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeCharacterSpecial CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeDirectory CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeBlockSpecial CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeRegular CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeSymbolicLink CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeSocket CF_AVAILABLE(10_7, 5_0);
CF_EXPORT
const CFStringRef kCFURLFileResourceTypeUnknown CF_AVAILABLE(10_7, 5_0);

/* File Properties */

CF_EXPORT
const CFStringRef kCFURLFileSizeKey CF_AVAILABLE(10_6, 4_0);
    /* Total file size in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLFileAllocatedSizeKey CF_AVAILABLE(10_6, 4_0);
    /* Total size allocated on disk for the file in bytes (number of blocks times block size) (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLTotalFileSizeKey CF_AVAILABLE(10_7, 5_0);
    /* Total displayable size of the file in bytes (this may include space used by metadata), or NULL if not available. (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLTotalFileAllocatedSizeKey CF_AVAILABLE(10_7, 5_0);
    /* Total allocated size of the file in bytes (this may include space used by metadata), or NULL if not available. This can be less than the value returned by kCFURLTotalFileSizeKey if the resource is compressed. (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLIsAliasFileKey CF_AVAILABLE(10_6, 4_0);
    /*  true if the resource is a Finder alias file or a symlink, false otherwise ( Read-only, value type CFBooleanRef) */

CF_EXPORT
const CFStringRef kCFURLFileProtectionKey CF_AVAILABLE_IOS(9_0);
    /* The protection level for this file */

/* The protection level values returned for the kCFURLFileProtectionKey */
CF_EXPORT
const CFStringRef kCFURLFileProtectionNone CF_AVAILABLE_IOS(9_0); // The file has no special protections associated with it. It can be read from or written to at any time.

CF_EXPORT
const CFStringRef kCFURLFileProtectionComplete CF_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be read from or written to while the device is locked or booting.

CF_EXPORT
const CFStringRef kCFURLFileProtectionCompleteUnlessOpen CF_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk. Files can be created while the device is locked, but once closed, cannot be opened again until the device is unlocked. If the file is opened when unlocked, you may continue to access the file normally, even if the user locks the device. There is a small performance penalty when the file is created and opened, though not when being written to or read from. This can be mitigated by changing the file protection to kCFURLFileProtectionComplete when the device is unlocked.

CF_EXPORT
const CFStringRef kCFURLFileProtectionCompleteUntilFirstUserAuthentication CF_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be accessed until after the device has booted. After the user unlocks the device for the first time, your app can access the file and continue to access it even if the user subsequently locks the device.

/* Volume Properties */

/* As a convenience, volume properties can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located. */

CF_EXPORT
const CFStringRef kCFURLVolumeLocalizedFormatDescriptionKey CF_AVAILABLE(10_6, 4_0);
    /* The user-visible volume format (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLVolumeTotalCapacityKey CF_AVAILABLE(10_6, 4_0);
    /* Total volume capacity in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeAvailableCapacityKey CF_AVAILABLE(10_6, 4_0);
    /* Total free space in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeResourceCountKey CF_AVAILABLE(10_6, 4_0);
    /* Total number of resources on the volume (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsPersistentIDsKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format supports persistent object identifiers and can look up file system objects by their IDs (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSymbolicLinksKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format supports symbolic links (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsHardLinksKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format supports hard links (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsJournalingKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format supports a journal used to speed recovery in case of unplanned restart (such as a power outage or crash). This does not necessarily mean the volume is actively using a journal. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsJournalingKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume is currently using a journal for speedy recovery after an unplanned restart. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSparseFilesKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format supports sparse files, that is, files which can have 'holes' that have never been written to, and thus do not consume space on disk. A sparse file may have an allocated size on disk that is less than its logical length. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsZeroRunsKey CF_AVAILABLE(10_6, 4_0);
    /* For security reasons, parts of a file (runs) that have never been written to must appear to contain zeroes. true if the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCaseSensitiveNamesKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format treats upper and lower case characters in file and directory names as different. Otherwise an upper case character is equivalent to a lower case character, and you can't have two names that differ solely in the case of the characters. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCasePreservedNamesKey CF_AVAILABLE(10_6, 4_0);
    /* true if the volume format preserves the case of file and directory names.  Otherwise the volume may change the case of some characters (typically making them all upper or all lower case). (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsRootDirectoryDatesKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume supports reliable storage of times for the root directory. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsVolumeSizesKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume supports returning volume size values (kCFURLVolumeTotalCapacityKey and kCFURLVolumeAvailableCapacityKey). (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsRenamingKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume can be renamed. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsAdvisoryFileLockingKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume implements whole-file flock(2) style advisory locks, and the O_EXLOCK and O_SHLOCK flags of the open(2) call. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsExtendedSecurityKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume implements extended security (ACLs). (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsBrowsableKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume should be visible via the GUI (i.e., appear on the Desktop as a separate volume). (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeMaximumFileSizeKey CF_AVAILABLE(10_7, 5_0);
    /* The largest file size (in bytes) supported by this file system, or NULL if this cannot be determined. (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsEjectableKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume's media is ejectable from the drive mechanism under software control. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsRemovableKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume's media is removable from the drive mechanism. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsInternalKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume's device is connected to an internal bus, false if connected to an external bus, or NULL if not available. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsAutomountedKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume is automounted. Note: do not mistake this with the functionality provided by kCFURLVolumeSupportsBrowsingKey. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsLocalKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume is stored on a local device. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeIsReadOnlyKey CF_AVAILABLE(10_7, 5_0);
    /* true if the volume is read-only. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLVolumeCreationDateKey CF_AVAILABLE(10_7, 5_0);
    /* The volume's creation date, or NULL if this cannot be determined. (Read-only, value type CFDate) */

CF_EXPORT
const CFStringRef kCFURLVolumeURLForRemountingKey CF_AVAILABLE(10_7, 5_0);
    /* The CFURL needed to remount a network volume, or NULL if not available. (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLVolumeUUIDStringKey CF_AVAILABLE(10_7, 5_0);
    /* The volume's persistent UUID as a string, or NULL if a persistent UUID is not available for the volume. (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLVolumeNameKey CF_AVAILABLE(10_7, 5_0);
    /* The name of the volume (Read-write, settable if kCFURLVolumeSupportsRenamingKey is true and permissions allow, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLVolumeLocalizedNameKey CF_AVAILABLE(10_7, 5_0);
    /* The user-presentable name of the volume (Read-only, value type CFString) */

/* UbiquitousItem Properties */

CF_EXPORT
const CFStringRef kCFURLIsUbiquitousItemKey CF_AVAILABLE(10_7, 5_0);
    /* true if this item is synced to the cloud, false if it is only a local file. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemHasUnresolvedConflictsKey CF_AVAILABLE(10_7, 5_0);
    /* true if this item has conflicts outstanding. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemIsDownloadedKey CF_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use kCFURLUbiquitousItemDownloadingStatusKey instead");
    /* Equivalent to NSURLUbiquitousItemDownloadingStatusKey == NSURLUbiquitousItemDownloadingStatusCurrent. Has never behaved as documented in earlier releases, hence deprecated. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemIsDownloadingKey CF_AVAILABLE(10_7, 5_0);
    /* true if data is being downloaded for this item. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemIsUploadedKey CF_AVAILABLE(10_7, 5_0);
    /* true if there is data present in the cloud for this item. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemIsUploadingKey CF_AVAILABLE(10_7, 5_0);
    /* true if data is being uploaded for this item. (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemPercentDownloadedKey CF_DEPRECATED(10_7, 10_8, 5_0, 6_0, "Use NSMetadataQuery and NSMetadataUbiquitousItemPercentDownloadedKey on NSMetadataItem instead");
    /* Use NSMetadataQuery and NSMetadataUbiquitousItemPercentDownloadedKey on NSMetadataItem instead */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemPercentUploadedKey CF_DEPRECATED(10_7, 10_8, 5_0, 6_0, "Use NSMetadataQuery and NSMetadataUbiquitousItemPercentUploadedKey on NSMetadataItem instead");
    /* Use NSMetadataQuery and NSMetadataUbiquitousItemPercentUploadedKey on NSMetadataItem instead */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemDownloadingStatusKey CF_AVAILABLE(10_9, 7_0);
    /* Returns the download status of this item. (Read-only, value type CFString). Possible values below. */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemDownloadingErrorKey CF_AVAILABLE(10_9, 7_0);
    /* returns the error when downloading the item from iCloud failed. See the NSUbiquitousFile section in FoundationErrors.h. (Read-only, value type CFError) */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemUploadingErrorKey CF_AVAILABLE(10_9, 7_0);
    /* returns the error when uploading the item to iCloud failed. See the NSUbiquitousFile section in FoundationErrors.h. (Read-only, value type CFError) */

/* The values returned for kCFURLUbiquitousItemDownloadingStatusKey
 */
CF_EXPORT
const CFStringRef kCFURLUbiquitousItemDownloadingStatusNotDownloaded CF_AVAILABLE(10_9, 7_0);
    /* this item has not been downloaded yet. Use NSFileManager's startDownloadingUbiquitousItemAtURL:error: to download it */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemDownloadingStatusDownloaded CF_AVAILABLE(10_9, 7_0);
    /* there is a local version of this item available. The most current version will get downloaded as soon as possible. */

CF_EXPORT
const CFStringRef kCFURLUbiquitousItemDownloadingStatusCurrent CF_AVAILABLE(10_9, 7_0);
    /* there is a local version of this item and it is the most up-to-date version known to this device. */


typedef CF_OPTIONS(CFOptionFlags, CFURLBookmarkCreationOptions) {
    kCFURLBookmarkCreationMinimalBookmarkMask = ( 1UL << 9 ), // creates bookmark data with "less" information, which may be smaller but still be able to resolve in certain ways
    kCFURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ), // include the properties required by CFURLWriteBookmarkDataToFile() in the bookmark data created
    kCFURLBookmarkCreationWithSecurityScope CF_ENUM_AVAILABLE(10_7, NA) = ( 1UL << 11 ), // Mac OS X 10.7.3 and later, include information in the bookmark data which allows the same sandboxed process to access the resource after being relaunched
    kCFURLBookmarkCreationSecurityScopeAllowOnlyReadAccess CF_ENUM_AVAILABLE(10_7, NA) = ( 1UL << 12 ), // Mac OS X 10.7.3 and later, if used with kCFURLBookmarkCreationWithSecurityScope, at resolution time only read access to the resource will be granted
    
    // deprecated
    kCFURLBookmarkCreationPreferFileIDResolutionMask CF_ENUM_DEPRECATED(10_6, 10_9, 4_0, 7_0, "kCFURLBookmarkCreationPreferFileIDResolutionMask does nothing and has no effect on bookmark resolution" ) = ( 1UL << 8 ),
} CF_ENUM_AVAILABLE(10_6, 4_0);

typedef CF_OPTIONS(CFOptionFlags, CFURLBookmarkResolutionOptions) {
    kCFURLBookmarkResolutionWithoutUIMask = ( 1UL << 8 ), // don't perform any user interaction during bookmark resolution
    kCFURLBookmarkResolutionWithoutMountingMask = ( 1UL << 9 ), // don't mount a volume during bookmark resolution
    kCFURLBookmarkResolutionWithSecurityScope CF_ENUM_AVAILABLE(10_7, NA) = ( 1UL << 10 ), // Mac OS X 10.7.3 and later, use the secure information included at creation time to provide the ability to access the resource in a sandboxed process.
    
    kCFBookmarkResolutionWithoutUIMask = kCFURLBookmarkResolutionWithoutUIMask,
    kCFBookmarkResolutionWithoutMountingMask = kCFURLBookmarkResolutionWithoutMountingMask,
} CF_ENUM_AVAILABLE(10_6, 4_0);

typedef CFOptionFlags CFURLBookmarkFileCreationOptions;

CF_IMPLICIT_BRIDGING_DISABLED

/* Returns bookmark data for the URL, created with specified options and resource properties. If this function returns NULL, the optional error is populated.
 */
CF_EXPORT
CFDataRef CFURLCreateBookmarkData ( CFAllocatorRef allocator, CFURLRef url, CFURLBookmarkCreationOptions options, CFArrayRef resourcePropertiesToInclude, CFURLRef relativeToURL, CFErrorRef* error ) CF_AVAILABLE(10_6, 4_0);

/* Return a URL that refers to a location specified by resolving bookmark data. If this function returns NULL, the optional error is populated.
 */
CF_EXPORT
CFURLRef CFURLCreateByResolvingBookmarkData ( CFAllocatorRef allocator, CFDataRef bookmark, CFURLBookmarkResolutionOptions options, CFURLRef relativeToURL, CFArrayRef resourcePropertiesToInclude, Boolean* isStale, CFErrorRef* error ) CF_AVAILABLE(10_6, 4_0);

/* Returns the resource propertyies identified by a specified array of keys contained in specified bookmark data. If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available in the bookmark data.
 */
CF_EXPORT
CFDictionaryRef CFURLCreateResourcePropertiesForKeysFromBookmarkData ( CFAllocatorRef allocator, CFArrayRef resourcePropertiesToReturn, CFDataRef bookmark ) CF_AVAILABLE(10_6, 4_0);

/*  Returns the resource property identified by a given resource key contained in specified bookmark data. If this function returns NULL, it means the resource property is not available in the bookmark data.
 */
CF_EXPORT
CFTypeRef  CFURLCreateResourcePropertyForKeyFromBookmarkData( CFAllocatorRef allocator, CFStringRef resourcePropertyKey, CFDataRef bookmark ) CF_AVAILABLE(10_6, 4_0);

/* Returns bookmark data derived from an alias file referred to by fileURL. If fileURL refers to an alias file created prior to OS X v10.6 that contains Alias Manager information but no bookmark data, this method synthesizes bookmark data for the file. If this method returns NULL, the optional error is populated.
 */
CF_EXPORT
CFDataRef CFURLCreateBookmarkDataFromFile(CFAllocatorRef allocator, CFURLRef fileURL, CFErrorRef *errorRef ) CF_AVAILABLE(10_6, 5_0);

/* Creates an alias file on disk at a specified location with specified bookmark data. The bookmark data must have been created with the kCFURLBookmarkCreationSuitableForBookmarkFile option. fileURL must either refer to an existing file (which will be overwritten), or to location in an existing directory. If this method returns FALSE, the optional error is populated.
 */
CF_EXPORT
Boolean CFURLWriteBookmarkDataToFile( CFDataRef bookmarkRef, CFURLRef fileURL, CFURLBookmarkFileCreationOptions options, CFErrorRef *errorRef ) CF_AVAILABLE(10_6, 5_0);

/* Returns bookmark data derived from an alias record.
 */
CF_EXPORT
CFDataRef CFURLCreateBookmarkDataFromAliasRecord ( CFAllocatorRef allocatorRef, CFDataRef aliasRecordDataRef ) CF_AVAILABLE_MAC(10_6);

CF_IMPLICIT_BRIDGING_ENABLED

/* Given a CFURLRef created by resolving a bookmark data created with security scope, make the resource referenced by the url accessible to the process. When access to this resource is no longer needed the client must call CFURLStopAccessingSecurityScopedResource(). Each call to CFURLStartAccessingSecurityScopedResource() must be balanced with a call to CFURLStopAccessingSecurityScopedResource() (Note: this is not reference counted).
 */
CF_EXPORT
Boolean CFURLStartAccessingSecurityScopedResource(CFURLRef url) CF_AVAILABLE(10_7, 8_0); // On OSX, available in MacOS X 10.7.3 and later

/* Revokes the access granted to the url by a prior successful call to CFURLStartAccessingSecurityScopedResource().
 */
CF_EXPORT
void CFURLStopAccessingSecurityScopedResource(CFURLRef url) CF_AVAILABLE(10_7, 8_0); // On OSX, available in MacOS X 10.7.3 and later

#endif /* TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE */

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFURL__ */

// ==========  CoreFoundation.framework/Headers/CFBitVector.h
/*	CFBitVector.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBITVECTOR__)
#define __COREFOUNDATION_CFBITVECTOR__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef UInt32 CFBit;

typedef const struct CF_BRIDGED_TYPE(id) __CFBitVector * CFBitVectorRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFBitVector * CFMutableBitVectorRef;

CF_EXPORT CFTypeID	CFBitVectorGetTypeID(void);

CF_EXPORT CFBitVectorRef	CFBitVectorCreate(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex numBits);
CF_EXPORT CFBitVectorRef	CFBitVectorCreateCopy(CFAllocatorRef allocator, CFBitVectorRef bv);
CF_EXPORT CFMutableBitVectorRef	CFBitVectorCreateMutable(CFAllocatorRef allocator, CFIndex capacity);
CF_EXPORT CFMutableBitVectorRef	CFBitVectorCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFBitVectorRef bv);

CF_EXPORT CFIndex	CFBitVectorGetCount(CFBitVectorRef bv);
CF_EXPORT CFIndex	CFBitVectorGetCountOfBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT Boolean	CFBitVectorContainsBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT CFBit		CFBitVectorGetBitAtIndex(CFBitVectorRef bv, CFIndex idx);
CF_EXPORT void		CFBitVectorGetBits(CFBitVectorRef bv, CFRange range, UInt8 *bytes);
CF_EXPORT CFIndex	CFBitVectorGetFirstIndexOfBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT CFIndex	CFBitVectorGetLastIndexOfBit(CFBitVectorRef bv, CFRange range, CFBit value);

CF_EXPORT void		CFBitVectorSetCount(CFMutableBitVectorRef bv, CFIndex count);
CF_EXPORT void		CFBitVectorFlipBitAtIndex(CFMutableBitVectorRef bv, CFIndex idx);
CF_EXPORT void		CFBitVectorFlipBits(CFMutableBitVectorRef bv, CFRange range);
CF_EXPORT void		CFBitVectorSetBitAtIndex(CFMutableBitVectorRef bv, CFIndex idx, CFBit value);
CF_EXPORT void		CFBitVectorSetBits(CFMutableBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT void		CFBitVectorSetAllBits(CFMutableBitVectorRef bv, CFBit value);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFBITVECTOR__ */

// ==========  CoreFoundation.framework/Headers/CFAttributedString.h
/*	CFAttributedString.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

/*! @header CFAttributedString
Instances of CFAttributedString manage character strings and associated sets of attributes (for example, font and kerning) that apply to individual characters or ranges of characters in the string. CFAttributedString as defined in CoreFoundation provides the basic container functionality, while higher levels provide definitions for standard attributes, their values, and additional behaviors involving these. 

CFAttributedString is not a "subclass" of CFString; that is, it does not respond to CFString function calls. CFAttributedString conceptually contains a CFString to which it applies attributes. This protects users of attributed strings from ambiguities caused by the semantic differences between simple and attributed strings.

Attributes are identified by key/value pairs stored in CFDictionaryRefs. Keys must be CFStrings, while the values are arbitrary CFTypeRefs.
*/

#if !defined(__COREFOUNDATION_CFATTRIBUTEDSTRING__)
#define __COREFOUNDATION_CFATTRIBUTEDSTRING__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN


/* CFAttributedString comes in immutable and mutable flavors.
*/
typedef const struct CF_BRIDGED_TYPE(NSAttributedString) __CFAttributedString *CFAttributedStringRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableAttributedString) __CFAttributedString *CFMutableAttributedStringRef;

/*! @function CFAttributedStringGetTypeID
Returns the type identifier of all CFAttributedString instances.
*/
CF_EXPORT CFTypeID CFAttributedStringGetTypeID(void);



/*** CFAttributedString ***/

/*! @function CFAttributedStringCreate
Creates an attributed string with the specified string and attributes (both copied).
*/
CF_EXPORT CFAttributedStringRef CFAttributedStringCreate(CFAllocatorRef alloc, CFStringRef str, CFDictionaryRef attributes);

/*! @function CFAttributedStringCreateWithSubstring
Creates a sub-attributed string from the specified range. It's a programming error for range to specify characters outside the bounds of aStr.
*/
CF_EXPORT CFAttributedStringRef CFAttributedStringCreateWithSubstring(CFAllocatorRef alloc, CFAttributedStringRef aStr, CFRange range);

/*! @function CFAttributedStringCreateCopy
Creates an immutable attributed string copy.
*/
CF_EXPORT CFAttributedStringRef CFAttributedStringCreateCopy(CFAllocatorRef alloc, CFAttributedStringRef aStr);

/*! @function CFAttributedStringGetString
Returns the string for the attributed string. For performance reasons, this will often point at the backing store of the attributed string, and it might change if the attributed string is edited.  However, this is an implementation detail, and definitely not something that should be counted on.
*/
CF_EXPORT CFStringRef CFAttributedStringGetString(CFAttributedStringRef aStr);

/*! @function CFAttributedStringGetLength
Returns the length of the attributed string in characters; same as CFStringGetLength(CFAttributedStringGetString(aStr))
*/
CF_EXPORT CFIndex CFAttributedStringGetLength(CFAttributedStringRef aStr);

/*! @function CFAttributedStringGetAttributes
Returns the attributes at the specified location. If effectiveRange is not NULL, upon return *effectiveRange contains a range over which the exact same set of attributes apply. Note that for performance reasons, the returned effectiveRange is not necessarily the maximal range - for that, use CFAttributedStringGetAttributesAndLongestEffectiveRange().  It's a programming error for loc to specify a location outside the bounds of the attributed string.

Note that the returned attribute dictionary might change in unpredictable ways from under the caller if the attributed string is edited after this call. If you wish to hang on to the dictionary long-term, you should make an actual copy of it rather than just retaining it.  Also, no assumptions should be made about the relationship of the actual CFDictionaryRef returned by this call and the dictionary originally used to set the attributes, other than the fact that the values stored in the dictionary will be identical (that is, ==) to those originally specified.
*/
CF_EXPORT CFDictionaryRef CFAttributedStringGetAttributes(CFAttributedStringRef aStr, CFIndex loc, CFRange *effectiveRange);

/*! @function CFAttributedStringGetAttribute
Returns the value of a single attribute at the specified location. If the specified attribute doesn't exist at the location, returns NULL. If effectiveRange is not NULL, upon return *effectiveRange contains a range over which the exact same attribute value applies. Note that for performance reasons, the returned effectiveRange is not necessarily the maximal range - for that, use CFAttributedStringGetAttributeAndLongestEffectiveRange(). It's a programming error for loc to specify a location outside the bounds of the attributed string.
*/
CF_EXPORT CFTypeRef CFAttributedStringGetAttribute(CFAttributedStringRef aStr, CFIndex loc, CFStringRef attrName, CFRange *effectiveRange);

/*! @function CFAttributedStringGetAttributesAndLongestEffectiveRange
Returns the attributes at the specified location. If longestEffectiveRange is not NULL, upon return *longestEffectiveRange contains the maximal range within inRange over which the exact same set of attributes apply. The returned range is clipped to inRange. It's a programming error for loc or inRange to specify locations outside the bounds of the attributed string.
*/
CF_EXPORT CFDictionaryRef CFAttributedStringGetAttributesAndLongestEffectiveRange(CFAttributedStringRef aStr, CFIndex loc, CFRange inRange, CFRange *longestEffectiveRange);

/*! @function CFAttributedStringGetAttributeAndLongestEffectiveRange
Returns the value of a single attribute at the specified location. If longestEffectiveRange is not NULL, upon return *longestEffectiveRange contains the maximal range within inRange over which the exact same attribute value applies. The returned range is clipped to inRange. It's a programming error for loc or inRange to specify locations outside the bounds of the attributed string.
*/
CF_EXPORT CFTypeRef CFAttributedStringGetAttributeAndLongestEffectiveRange(CFAttributedStringRef aStr, CFIndex loc, CFStringRef attrName, CFRange inRange, CFRange *longestEffectiveRange);



/*** CFMutableAttributedString ***/

/*! @function CFAttributedStringCreateMutableCopy
Creates a mutable attributed string copy. maxLength, if not 0, is a hard bound on the length of the attributed string; exceeding this size limit during any editing operation is a programming error. If 0, there is no limit on the length.
*/
CF_EXPORT CFMutableAttributedStringRef CFAttributedStringCreateMutableCopy(CFAllocatorRef alloc, CFIndex maxLength, CFAttributedStringRef aStr);

/*! @function CFAttributedStringCreateMutable
Creates a mutable empty attributed string. maxLength, if not 0, is a hard bound on the length of the attributed string; exceeding this size limit during any editing operation is a programming error. If 0, there is no limit on the length.
*/
CF_EXPORT CFMutableAttributedStringRef CFAttributedStringCreateMutable(CFAllocatorRef alloc, CFIndex maxLength);

/*! @function CFAttributedStringReplaceString
Modifies the string for the attributed string, much like CFStringReplace().  It's an error for range to specify characters outside the bounds of aStr. 

(Note: This function is a convenience on CFAttributedStringGetMutableString(); however, until CFAttributedStringGetMutableString() is implemented, it remains the only way to edit the string of the attributed string.)
*/
CF_EXPORT void CFAttributedStringReplaceString(CFMutableAttributedStringRef aStr, CFRange range, CFStringRef replacement);

/*! @function CFAttributedStringGetMutableString
Gets the string for the attributed string as a mutable string, allowing editing the character contents of the string as if it were an CFMutableString. Attributes corresponding to the edited range are appropriately modified. If, as a result of the edit, new characters are introduced into the string, they inherit the attributes of the first replaced character from range. If no existing characters are replaced by the edit, the new characters inherit the attributes of the character preceding range if it has any, otherwise of the character following range. If the initial string is empty, the attributes for the new characters are also empty.

(Note: This function is not yet implemented and will return NULL except for toll-free bridged instances.)
*/
CF_EXPORT CFMutableStringRef CFAttributedStringGetMutableString(CFMutableAttributedStringRef aStr);

/*! @function CFAttributedStringSetAttributes
Sets the value of multiple attributes over the specified range, which should be valid. If clearOtherAttributes is false, existing attributes (which aren't being replaced) are left alone; otherwise they are cleared. The dictionary should be setup for "usual" CF type usage --- CFString keys, and arbitrary CFType values. Note that after this call, further mutations to the replacement dictionary argument by the caller will not affect the contents of the attributed string.
*/
CF_EXPORT void CFAttributedStringSetAttributes(CFMutableAttributedStringRef aStr, CFRange range, CFDictionaryRef replacement, Boolean clearOtherAttributes);

/*! @function CFAttributedStringSetAttribute
Sets the value of a single attribute over the specified range, which should be valid. value should not be NULL. 
*/
CF_EXPORT void CFAttributedStringSetAttribute(CFMutableAttributedStringRef aStr, CFRange range, CFStringRef attrName, CFTypeRef value);

/*! @function CFAttributedStringRemoveAttribute
Removes the value of a single attribute over the specified range, which should be valid. It's OK for the attribute not the exist over the specified range.
*/
CF_EXPORT void CFAttributedStringRemoveAttribute(CFMutableAttributedStringRef aStr, CFRange range, CFStringRef attrName);

/*! @function CFAttributedStringReplaceAttributedString
Replaces the attributed substring over the specified range with the attributed string specified in replacement. range should be valid. To delete a range of the attributed string, call CFAttributedStringReplaceString() with empty string and specified range. 
*/
CF_EXPORT void CFAttributedStringReplaceAttributedString(CFMutableAttributedStringRef aStr, CFRange range, CFAttributedStringRef replacement);

/*! @function CFAttributedStringBeginEditing
In cases where attributed string might do a bunch of work to assure self-consistency, CFAttributedStringBeginEditing/CFAttributedStringEndEditing allow disabling that to allow deferring and coalescing any work. It's a good idea to call these around a set of related mutation calls which don't require the string to be in consistent state in between. These calls can be nested. 
*/
CF_EXPORT void CFAttributedStringBeginEditing(CFMutableAttributedStringRef aStr);

/*! @function CFAttributedStringEndEditing
In cases where attributed string might do a bunch of work to assure self-consistency, CFAttributedStringBeginEditing/CFAttributedStringEndEditing allow disabling that to allow deferring and coalescing any work. It's a good idea to call these around a set of related mutation calls which don't require the string to be in consistent state in between. These calls can be nested. 
*/
CF_EXPORT void CFAttributedStringEndEditing(CFMutableAttributedStringRef aStr);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFATTRIBUTEDSTRING__ */

// ==========  CoreFoundation.framework/Headers/CFRunLoop.h
/*	CFRunLoop.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFRUNLOOP__)
#define __COREFOUNDATION_CFRUNLOOP__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFString.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#include <mach/port.h>
#endif

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFRunLoop * CFRunLoopRef;

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFRunLoopSource * CFRunLoopSourceRef;

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFRunLoopObserver * CFRunLoopObserverRef;

typedef struct CF_BRIDGED_MUTABLE_TYPE(NSTimer) __CFRunLoopTimer * CFRunLoopTimerRef;

/* Reasons for CFRunLoopRunInMode() to Return */
typedef CF_ENUM(SInt32, CFRunLoopRunResult) {
    kCFRunLoopRunFinished = 1,
    kCFRunLoopRunStopped = 2,
    kCFRunLoopRunTimedOut = 3,
    kCFRunLoopRunHandledSource = 4
};

/* Run Loop Observer Activities */
typedef CF_OPTIONS(CFOptionFlags, CFRunLoopActivity) {
    kCFRunLoopEntry = (1UL << 0),
    kCFRunLoopBeforeTimers = (1UL << 1),
    kCFRunLoopBeforeSources = (1UL << 2),
    kCFRunLoopBeforeWaiting = (1UL << 5),
    kCFRunLoopAfterWaiting = (1UL << 6),
    kCFRunLoopExit = (1UL << 7),
    kCFRunLoopAllActivities = 0x0FFFFFFFU
};

CF_EXPORT const CFStringRef kCFRunLoopDefaultMode;
CF_EXPORT const CFStringRef kCFRunLoopCommonModes;

CF_EXPORT CFTypeID CFRunLoopGetTypeID(void);

CF_EXPORT CFRunLoopRef CFRunLoopGetCurrent(void);
CF_EXPORT CFRunLoopRef CFRunLoopGetMain(void);

CF_EXPORT CFStringRef CFRunLoopCopyCurrentMode(CFRunLoopRef rl);

CF_EXPORT CFArrayRef CFRunLoopCopyAllModes(CFRunLoopRef rl);

CF_EXPORT void CFRunLoopAddCommonMode(CFRunLoopRef rl, CFStringRef mode);

CF_EXPORT CFAbsoluteTime CFRunLoopGetNextTimerFireDate(CFRunLoopRef rl, CFStringRef mode);

CF_EXPORT void CFRunLoopRun(void);
CF_EXPORT CFRunLoopRunResult CFRunLoopRunInMode(CFStringRef mode, CFTimeInterval seconds, Boolean returnAfterSourceHandled);
CF_EXPORT Boolean CFRunLoopIsWaiting(CFRunLoopRef rl);
CF_EXPORT void CFRunLoopWakeUp(CFRunLoopRef rl);
CF_EXPORT void CFRunLoopStop(CFRunLoopRef rl);

#if __BLOCKS__
CF_EXPORT void CFRunLoopPerformBlock(CFRunLoopRef rl, CFTypeRef mode, void (^block)(void)) CF_AVAILABLE(10_6, 4_0); 
#endif

CF_EXPORT Boolean CFRunLoopContainsSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);
CF_EXPORT void CFRunLoopAddSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);

CF_EXPORT Boolean CFRunLoopContainsObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);
CF_EXPORT void CFRunLoopAddObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);

CF_EXPORT Boolean CFRunLoopContainsTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);
CF_EXPORT void CFRunLoopAddTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
    Boolean	(*equal)(const void *info1, const void *info2);
    CFHashCode	(*hash)(const void *info);
    void	(*schedule)(void *info, CFRunLoopRef rl, CFStringRef mode);
    void	(*cancel)(void *info, CFRunLoopRef rl, CFStringRef mode);
    void	(*perform)(void *info);
} CFRunLoopSourceContext;

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
    Boolean	(*equal)(const void *info1, const void *info2);
    CFHashCode	(*hash)(const void *info);
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
    mach_port_t	(*getPort)(void *info);
    void *	(*perform)(void *msg, CFIndex size, CFAllocatorRef allocator, void *info);
#else
    void *	(*getPort)(void *info);
    void	(*perform)(void *info);
#endif
} CFRunLoopSourceContext1;

CF_EXPORT CFTypeID CFRunLoopSourceGetTypeID(void);

CF_EXPORT CFRunLoopSourceRef CFRunLoopSourceCreate(CFAllocatorRef allocator, CFIndex order, CFRunLoopSourceContext *context);

CF_EXPORT CFIndex CFRunLoopSourceGetOrder(CFRunLoopSourceRef source);
CF_EXPORT void CFRunLoopSourceInvalidate(CFRunLoopSourceRef source);
CF_EXPORT Boolean CFRunLoopSourceIsValid(CFRunLoopSourceRef source);
CF_EXPORT void CFRunLoopSourceGetContext(CFRunLoopSourceRef source, CFRunLoopSourceContext *context);
CF_EXPORT void CFRunLoopSourceSignal(CFRunLoopSourceRef source);

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFRunLoopObserverContext;

typedef void (*CFRunLoopObserverCallBack)(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info);

CF_EXPORT CFTypeID CFRunLoopObserverGetTypeID(void);

CF_EXPORT CFRunLoopObserverRef CFRunLoopObserverCreate(CFAllocatorRef allocator, CFOptionFlags activities, Boolean repeats, CFIndex order, CFRunLoopObserverCallBack callout, CFRunLoopObserverContext *context);
#if __BLOCKS__
CF_EXPORT CFRunLoopObserverRef CFRunLoopObserverCreateWithHandler(CFAllocatorRef allocator, CFOptionFlags activities, Boolean repeats, CFIndex order, void (^block) (CFRunLoopObserverRef observer, CFRunLoopActivity activity)) CF_AVAILABLE(10_7, 5_0);
#endif

CF_EXPORT CFOptionFlags CFRunLoopObserverGetActivities(CFRunLoopObserverRef observer);
CF_EXPORT Boolean CFRunLoopObserverDoesRepeat(CFRunLoopObserverRef observer);
CF_EXPORT CFIndex CFRunLoopObserverGetOrder(CFRunLoopObserverRef observer);
CF_EXPORT void CFRunLoopObserverInvalidate(CFRunLoopObserverRef observer);
CF_EXPORT Boolean CFRunLoopObserverIsValid(CFRunLoopObserverRef observer);
CF_EXPORT void CFRunLoopObserverGetContext(CFRunLoopObserverRef observer, CFRunLoopObserverContext *context);

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFRunLoopTimerContext;

typedef void (*CFRunLoopTimerCallBack)(CFRunLoopTimerRef timer, void *info);

CF_EXPORT CFTypeID CFRunLoopTimerGetTypeID(void);

CF_EXPORT CFRunLoopTimerRef CFRunLoopTimerCreate(CFAllocatorRef allocator, CFAbsoluteTime fireDate, CFTimeInterval interval, CFOptionFlags flags, CFIndex order, CFRunLoopTimerCallBack callout, CFRunLoopTimerContext *context);
#if __BLOCKS__
CF_EXPORT CFRunLoopTimerRef CFRunLoopTimerCreateWithHandler(CFAllocatorRef allocator, CFAbsoluteTime fireDate, CFTimeInterval interval, CFOptionFlags flags, CFIndex order, void (^block) (CFRunLoopTimerRef timer)) CF_AVAILABLE(10_7, 5_0);
#endif

CF_EXPORT CFAbsoluteTime CFRunLoopTimerGetNextFireDate(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerSetNextFireDate(CFRunLoopTimerRef timer, CFAbsoluteTime fireDate);
CF_EXPORT CFTimeInterval CFRunLoopTimerGetInterval(CFRunLoopTimerRef timer);
CF_EXPORT Boolean CFRunLoopTimerDoesRepeat(CFRunLoopTimerRef timer);
CF_EXPORT CFIndex CFRunLoopTimerGetOrder(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerInvalidate(CFRunLoopTimerRef timer);
CF_EXPORT Boolean CFRunLoopTimerIsValid(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerGetContext(CFRunLoopTimerRef timer, CFRunLoopTimerContext *context);

// Setting a tolerance for a timer allows it to fire later than the scheduled fire date, improving the ability of the system to optimize for increased power savings and responsiveness. The timer may fire at any time between its scheduled fire date and the scheduled fire date plus the tolerance. The timer will not fire before the scheduled fire date. For repeating timers, the next fire date is calculated from the original fire date regardless of tolerance applied at individual fire times, to avoid drift. The default value is zero, which means no additional tolerance is applied. The system reserves the right to apply a small amount of tolerance to certain timers regardless of the value of this property.
// As the user of the timer, you will have the best idea of what an appropriate tolerance for a timer may be. A general rule of thumb, though, is to set the tolerance to at least 10% of the interval, for a repeating timer. Even a small amount of tolerance will have a significant positive impact on the power usage of your application. The system may put a maximum value of the tolerance.
CF_EXPORT CFTimeInterval CFRunLoopTimerGetTolerance(CFRunLoopTimerRef timer) CF_AVAILABLE(10_9, 7_0);
CF_EXPORT void CFRunLoopTimerSetTolerance(CFRunLoopTimerRef timer, CFTimeInterval tolerance) CF_AVAILABLE(10_9, 7_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFRUNLOOP__ */

// ==========  CoreFoundation.framework/Headers/CFString.h
/*	CFString.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFSTRING__)
#define __COREFOUNDATION_CFSTRING__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFLocale.h>
#include <stdarg.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*
Please note: CFStrings are conceptually an array of Unicode characters.
However, in general, how a CFString stores this array is an implementation
detail. For instance, CFString might choose to use an array of 8-bit characters
to store its contents, or it might use multiple blocks of memory, or whatever.
This is especially true since CFString is toll-free bridged with NSString, enabling
any NSString instance to be used as a CFString. Furthermore, the implementation
may change depending on the default system encoding, the user's language, 
or even a release or update of the OS.

What this means is that you should use the following advanced functions with care:

  CFStringGetPascalStringPtr()
  CFStringGetCStringPtr()
  CFStringGetCharactersPtr()

These functions are provided for optimization only. They will either return the desired
pointer quickly, in constant time, or they return NULL. They might choose to return NULL
for many reasons; for instance it's possible that for users running in different
languages these sometimes return NULL; or in a future OS release the first two might
switch to always returning NULL. Never observing NULL returns in your usages of these
functions does not mean they won't ever return NULL. (But note the CFStringGetCharactersPtr()
exception mentioned further below.)

In your usages of these functions, if you get a NULL return, use the non-Ptr version
of the functions as shown in this example:

  char buffer[BUFSIZE];
  const char *ptr = CFStringGetCStringPtr(str, encoding);
  if (ptr == NULL) {
      if (CFStringGetCString(str, buffer, BUFSIZE, encoding)) ptr = buffer;
  }

Note that CFStringGetCString() or CFStringGetPascalString() calls might still fail --- but
that will happen in two circumstances only: The conversion from the UniChar contents of CFString
to the specified encoding fails, or the buffer is too small. If they fail, that means
the conversion was not possible.

If you need a copy of the buffer in the above example, you might consider simply calling
CFStringGetCString() in all cases --- CFStringGetCStringPtr() is simply an optimization.

In addition, the following functions, which create immutable CFStrings from developer
supplied buffers without copying the buffers, might have to actually copy
under certain circumstances (If they do copy, the buffer will be dealt with by the
"contentsDeallocator" argument.):

  CFStringCreateWithPascalStringNoCopy()
  CFStringCreateWithCStringNoCopy()
  CFStringCreateWithCharactersNoCopy()

You should of course never depend on the backing store of these CFStrings being
what you provided, and in other no circumstance should you change the contents
of that buffer (given that would break the invariant about the CFString being immutable).

Having said all this, there are actually ways to create a CFString where the backing store
is external, and can be manipulated by the developer or CFString itself:

  CFStringCreateMutableWithExternalCharactersNoCopy()
  CFStringSetExternalCharactersNoCopy()

A "contentsAllocator" is used to realloc or free the backing store by CFString.
kCFAllocatorNull can be provided to assure CFString will never realloc or free the buffer.
Developer can call CFStringSetExternalCharactersNoCopy() to update
CFString's idea of what's going on, if the buffer is changed externally. In these
strings, CFStringGetCharactersPtr() is guaranteed to return the external buffer.

These functions are here to allow wrapping a buffer of UniChar characters in a CFString,
allowing the buffer to passed into CFString functions and also manipulated via CFString
mutation functions. In general, developers should not use this technique for all strings,
as it prevents CFString from using certain optimizations.
*/

/* Identifier for character encoding; the values are the same as Text Encoding Converter TextEncoding.
*/
typedef UInt32 CFStringEncoding;

/* Platform-independent built-in encodings; always available on all platforms.
   Call CFStringGetSystemEncoding() to get the default system encoding.
*/
#define kCFStringEncodingInvalidId (0xffffffffU)
typedef CF_ENUM(CFStringEncoding, CFStringBuiltInEncodings) {
    kCFStringEncodingMacRoman = 0,
    kCFStringEncodingWindowsLatin1 = 0x0500, /* ANSI codepage 1252 */
    kCFStringEncodingISOLatin1 = 0x0201, /* ISO 8859-1 */
    kCFStringEncodingNextStepLatin = 0x0B01, /* NextStep encoding*/
    kCFStringEncodingASCII = 0x0600, /* 0..127 (in creating CFString, values greater than 0x7F are treated as corresponding Unicode value) */
    kCFStringEncodingUnicode = 0x0100, /* kTextEncodingUnicodeDefault  + kTextEncodingDefaultFormat (aka kUnicode16BitFormat) */
    kCFStringEncodingUTF8 = 0x08000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF8Format */
    kCFStringEncodingNonLossyASCII = 0x0BFF, /* 7bit Unicode variants used by Cocoa & Java */

    kCFStringEncodingUTF16 = 0x0100, /* kTextEncodingUnicodeDefault + kUnicodeUTF16Format (alias of kCFStringEncodingUnicode) */
    kCFStringEncodingUTF16BE = 0x10000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF16BEFormat */
    kCFStringEncodingUTF16LE = 0x14000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF16LEFormat */

    kCFStringEncodingUTF32 = 0x0c000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF32Format */
    kCFStringEncodingUTF32BE = 0x18000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF32BEFormat */
    kCFStringEncodingUTF32LE = 0x1c000100 /* kTextEncodingUnicodeDefault + kUnicodeUTF32LEFormat */
};


/* CFString type ID */
CF_EXPORT
CFTypeID CFStringGetTypeID(void);

/* CFSTR() allows creation of compile-time constant CFStringRefs; the argument 
should be a constant C-string.

CFSTR(), not being a "Copy" or "Create" function, does not return a new
reference for you. So, you should not release the return value. This is
much like constant C or Pascal strings --- when you use "hello world"
in a program, you do not free it.

However, strings returned from CFSTR() can be retained and released in a
properly nested fashion, just like any other CF type. That is, if you pass
a CFSTR() return value to a function such as SetMenuItemWithCFString(), the
function can retain it, then later, when it's done with it, it can release it.

Non-7 bit characters (that is, above 127) in CFSTR() are supported, although care must
be taken in dealing with files containing them. If you can trust your editor and tools
to deal with non-ASCII characters in the source code, then you can use them directly 
in CFSTR(); otherwise, you can represent such characters with their escaped octal 
equivalents in the encoding the compiler will use to interpret them (for instance, 
O-umlaut is \303\226 in UTF-8). UTF-8 is the recommended encoding here, 
since it is the default choice with Mac OS X developer tools.
*/
#if TARGET_OS_WIN32 || TARGET_OS_LINUX
#undef __CONSTANT_CFSTRINGS__
#endif

#ifdef __CONSTANT_CFSTRINGS__
#define CFSTR(cStr)  ((CFStringRef) __builtin___CFStringMakeConstantString ("" cStr ""))
#else
#define CFSTR(cStr)  __CFStringMakeConstantString("" cStr "")
#endif

#if defined(__GNUC__) && (__GNUC__*10+__GNUC_MINOR__ >= 42) && defined(__APPLE_CC__) && (__APPLE_CC__ > 1) && !defined(__INTEL_COMPILER) && (TARGET_OS_MAC || TARGET_OS_EMBEDDED)
#define CF_FORMAT_FUNCTION(F,A) __attribute__((format(CFString, F, A)))
#define CF_FORMAT_ARGUMENT(A) __attribute__((format_arg(A)))
#else
#define CF_FORMAT_FUNCTION(F,A)
#define CF_FORMAT_ARGUMENT(A)
#endif

/*** Immutable string creation functions ***/

/* Functions to create basic immutable strings. The provided allocator is used for all memory activity in these functions.
*/

/* The following four functions copy the provided buffer into CFString's internal storage. */
CF_EXPORT
CFStringRef CFStringCreateWithPascalString(CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding);

CF_EXPORT
CFStringRef CFStringCreateWithCString(CFAllocatorRef alloc, const char *cStr, CFStringEncoding encoding);

/* The following takes an explicit length, and allows you to specify whether the data is an external format --- that is, whether to pay attention to the BOM character (if any) and do byte swapping if necessary
*/
CF_EXPORT
CFStringRef CFStringCreateWithBytes(CFAllocatorRef alloc, const UInt8 *bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation);

CF_EXPORT
CFStringRef CFStringCreateWithCharacters(CFAllocatorRef alloc, const UniChar *chars, CFIndex numChars);


/* These functions try not to copy the provided buffer. The buffer will be deallocated 
with the provided contentsDeallocator when it's no longer needed; to not free
the buffer, specify kCFAllocatorNull here. As usual, NULL means default allocator.

NOTE: Do not count on these buffers as being used by the string; 
in some cases the CFString might free the buffer and use something else
(for instance if it decides to always use Unicode encoding internally). 

NOTE: If you are not transferring ownership of the buffer to the CFString
(for instance, you supplied contentsDeallocator = kCFAllocatorNull), it is your
responsibility to assure the buffer does not go away during the lifetime of the string.
If the string is retained or copied, its lifetime might extend in ways you cannot
predict. So, for strings created with buffers whose lifetimes you cannot
guarantee, you need to be extremely careful --- do not hand it out to any
APIs which might retain or copy the strings.
*/
CF_EXPORT
CFStringRef CFStringCreateWithPascalStringNoCopy(CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator);

CF_EXPORT
CFStringRef CFStringCreateWithCStringNoCopy(CFAllocatorRef alloc, const char *cStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator);

/* The following takes an explicit length, and allows you to specify whether the data is an external format --- that is, whether to pay attention to the BOM character (if any) and do byte swapping if necessary
*/
CF_EXPORT
CFStringRef CFStringCreateWithBytesNoCopy(CFAllocatorRef alloc, const UInt8 *bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation, CFAllocatorRef contentsDeallocator);

CF_EXPORT
CFStringRef CFStringCreateWithCharactersNoCopy(CFAllocatorRef alloc, const UniChar *chars, CFIndex numChars, CFAllocatorRef contentsDeallocator);

/* Create copies of part or all of the string.
*/
CF_EXPORT
CFStringRef CFStringCreateWithSubstring(CFAllocatorRef alloc, CFStringRef str, CFRange range);

CF_EXPORT
CFStringRef CFStringCreateCopy(CFAllocatorRef alloc, CFStringRef theString);

/* These functions create a CFString from the provided printf-like format string and arguments.
*/
CF_EXPORT
CFStringRef CFStringCreateWithFormat(CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, ...) CF_FORMAT_FUNCTION(3,4);

CF_EXPORT
CFStringRef CFStringCreateWithFormatAndArguments(CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments) CF_FORMAT_FUNCTION(3,0);

/* Functions to create mutable strings. "maxLength", if not 0, is a hard bound on the length of the string. If 0, there is no limit on the length.
*/
CF_EXPORT
CFMutableStringRef CFStringCreateMutable(CFAllocatorRef alloc, CFIndex maxLength);

CF_EXPORT
CFMutableStringRef CFStringCreateMutableCopy(CFAllocatorRef alloc, CFIndex maxLength, CFStringRef theString);

/* This function creates a mutable string that has a developer supplied and directly editable backing store.
The string will be manipulated within the provided buffer (if any) until it outgrows capacity; then the
externalCharactersAllocator will be consulted for more memory. When the CFString is deallocated, the
buffer will be freed with the externalCharactersAllocator. Provide kCFAllocatorNull here to prevent the buffer
from ever being reallocated or deallocated by CFString. See comments at top of this file for more info.
*/
CF_EXPORT
CFMutableStringRef CFStringCreateMutableWithExternalCharactersNoCopy(CFAllocatorRef alloc, UniChar *chars, CFIndex numChars, CFIndex capacity, CFAllocatorRef externalCharactersAllocator);

/*** Basic accessors for the contents ***/

/* Number of 16-bit Unicode characters in the string.
*/
CF_EXPORT
CFIndex CFStringGetLength(CFStringRef theString);

/* Extracting the contents of the string. For obtaining multiple characters, calling
CFStringGetCharacters() is more efficient than multiple calls to CFStringGetCharacterAtIndex().
If the length of the string is not known (so you can't use a fixed size buffer for CFStringGetCharacters()),
another method is to use is CFStringGetCharacterFromInlineBuffer() (see further below).
*/
CF_EXPORT
UniChar CFStringGetCharacterAtIndex(CFStringRef theString, CFIndex idx);

CF_EXPORT
void CFStringGetCharacters(CFStringRef theString, CFRange range, UniChar *buffer);


/*** Conversion to other encodings ***/

/* These two convert into the provided buffer; they return false if conversion isn't possible
(due to conversion error, or not enough space in the provided buffer). 
These functions do zero-terminate or put the length byte; the provided bufferSize should include
space for this (so pass 256 for Str255). More sophisticated usages can go through CFStringGetBytes().
These functions are equivalent to calling CFStringGetBytes() with 
the range of the string; lossByte = 0; and isExternalRepresentation = false; 
if successful, they then insert the leading length or terminating zero, as desired.
*/
CF_EXPORT
Boolean CFStringGetPascalString(CFStringRef theString, StringPtr buffer, CFIndex bufferSize, CFStringEncoding encoding);

CF_EXPORT
Boolean CFStringGetCString(CFStringRef theString, char *buffer, CFIndex bufferSize, CFStringEncoding encoding);

/* These functions attempt to return in O(1) time the desired format for the string.
Note that although this means a pointer to the internal structure is being returned,
this can't always be counted on. Please see note at the top of the file for more
details.
*/
CF_EXPORT
ConstStringPtr CFStringGetPascalStringPtr(CFStringRef theString, CFStringEncoding encoding);	/* May return NULL at any time; be prepared for NULL */

CF_EXPORT
const char *CFStringGetCStringPtr(CFStringRef theString, CFStringEncoding encoding);		/* May return NULL at any time; be prepared for NULL */

CF_EXPORT
const UniChar *CFStringGetCharactersPtr(CFStringRef theString);					/* May return NULL at any time; be prepared for NULL */

/* The primitive conversion routine; allows you to convert a string piece at a time
       into a fixed size buffer. Returns number of characters converted. 
   Characters that cannot be converted to the specified encoding are represented
       with the byte specified by lossByte; if lossByte is 0, then lossy conversion
       is not allowed and conversion stops, returning partial results.
   Pass buffer==NULL if you don't care about the converted string (but just the convertability,
       or number of bytes required). 
   maxBufLength indicates the maximum number of bytes to generate. It is ignored when buffer==NULL.
   Does not zero-terminate. If you want to create Pascal or C string, allow one extra byte at start or end. 
   Setting isExternalRepresentation causes any extra bytes that would allow 
       the data to be made persistent to be included; for instance, the Unicode BOM. Note that
       CFString prepends UTF encoded data with the Unicode BOM <http://www.unicode.org/faq/utf_bom.html> 
       when generating external representation if the target encoding allows. It's important to note that
       only UTF-8, UTF-16, and UTF-32 define the handling of the byte order mark character, and the "LE"
       and "BE" variants of UTF-16 and UTF-32 don't.
*/
CF_EXPORT
CFIndex CFStringGetBytes(CFStringRef theString, CFRange range, CFStringEncoding encoding, UInt8 lossByte, Boolean isExternalRepresentation, UInt8 *buffer, CFIndex maxBufLen, CFIndex *usedBufLen);

/* Convenience functions String <-> Data. These generate "external" formats, that is, formats that
   can be written out to disk. For instance, if the encoding is Unicode,
   CFStringCreateFromExternalRepresentation() pays attention to the BOM character (if any) 
   and does byte swapping if necessary. Similarly CFStringCreateExternalRepresentation() will  
   include a BOM character if appropriate. See CFStringGetBytes() for more on this and lossByte.
*/
CF_EXPORT
CFStringRef CFStringCreateFromExternalRepresentation(CFAllocatorRef alloc, CFDataRef data, CFStringEncoding encoding);	/* May return NULL on conversion error */

CF_EXPORT
CFDataRef CFStringCreateExternalRepresentation(CFAllocatorRef alloc, CFStringRef theString, CFStringEncoding encoding, UInt8 lossByte);	/* May return NULL on conversion error */	

/* Hints about the contents of a string
*/
CF_EXPORT
CFStringEncoding CFStringGetSmallestEncoding(CFStringRef theString);	/* Result in O(n) time max */

CF_EXPORT
CFStringEncoding CFStringGetFastestEncoding(CFStringRef theString);	/* Result in O(1) time max */

/* General encoding info
*/
CF_EXPORT
CFStringEncoding CFStringGetSystemEncoding(void);		/* The default encoding for the system; untagged 8-bit characters are usually in this encoding */

CF_EXPORT
CFIndex CFStringGetMaximumSizeForEncoding(CFIndex length, CFStringEncoding encoding);	/* Max bytes a string of specified length (in UniChars) will take up if encoded */


/*** FileSystem path conversion functions ***/

/* Extract the contents of the string as a NULL-terminated 8-bit string appropriate for passing to POSIX APIs (for example, normalized for HFS+).  The string is zero-terminated. false will be returned if the conversion results don't fit into the buffer.  Use CFStringGetMaximumSizeOfFileSystemRepresentation() if you want to make sure the buffer is of sufficient length.
*/
CF_EXPORT
Boolean CFStringGetFileSystemRepresentation(CFStringRef string, char *buffer, CFIndex maxBufLen);

/* Get the upper bound on the number of bytes required to hold the file system representation for the string. This result is returned quickly as a very rough approximation, and could be much larger than the actual space required. The result includes space for the zero termination. If you are allocating a buffer for long-term keeping, it's recommended that you reallocate it smaller (to be the right size) after calling CFStringGetFileSystemRepresentation(). 
*/
CF_EXPORT
CFIndex CFStringGetMaximumSizeOfFileSystemRepresentation(CFStringRef string);

/* Create a CFString from the specified zero-terminated POSIX file system representation.  If the conversion fails (possible due to bytes in the buffer not being a valid sequence of bytes for the appropriate character encoding), NULL is returned.
*/
CF_EXPORT
CFStringRef CFStringCreateWithFileSystemRepresentation(CFAllocatorRef alloc, const char *buffer);


/*** Comparison functions. ***/

/* Find and compare flags; these are OR'ed together and provided as CFStringCompareFlags in the various functions. 
*/
typedef CF_OPTIONS(CFOptionFlags, CFStringCompareFlags) {
    kCFCompareCaseInsensitive = 1,	
    kCFCompareBackwards = 4,		/* Starting from the end of the string */
    kCFCompareAnchored = 8,		/* Only at the specified starting point */
    kCFCompareNonliteral = 16,		/* If specified, loose equivalence is performed (o-umlaut == o, umlaut) */
    kCFCompareLocalized = 32,		/* User's default locale is used for the comparisons */
    kCFCompareNumerically = 64,		/* Numeric comparison is used; that is, Foo2.txt < Foo7.txt < Foo25.txt */
    kCFCompareDiacriticInsensitive CF_ENUM_AVAILABLE(10_5, 2_0) = 128, /* If specified, ignores diacritics (o-umlaut == o) */
    kCFCompareWidthInsensitive CF_ENUM_AVAILABLE(10_5, 2_0) = 256, /* If specified, ignores width differences ('a' == UFF41) */
    kCFCompareForcedOrdering CF_ENUM_AVAILABLE(10_5, 2_0) = 512 /* If specified, comparisons are forced to return either kCFCompareLessThan or kCFCompareGreaterThan if the strings are equivalent but not strictly equal, for stability when sorting (e.g. "aaa" > "AAA" with kCFCompareCaseInsensitive specified) */
};

/* The main comparison routine; compares specified range of the first string to (the full range of) the second string.
   locale == NULL indicates canonical locale (the return value from CFLocaleGetSystem()).
   kCFCompareNumerically, added in 10.2, does not work if kCFCompareLocalized is specified on systems before 10.3
   kCFCompareBackwards and kCFCompareAnchored are not applicable.
   rangeToCompare applies to the first string; that is, only the substring of theString1 specified by rangeToCompare is compared against all of theString2.
*/
CF_EXPORT
CFComparisonResult CFStringCompareWithOptionsAndLocale(CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions, CFLocaleRef locale) CF_AVAILABLE(10_5, 2_0);

/* Comparison convenience. Uses the current user locale (the return value from CFLocaleCopyCurrent()) if kCFCompareLocalized. Refer to CFStringCompareWithOptionsAndLocale() for more info.
*/
CF_EXPORT
CFComparisonResult CFStringCompareWithOptions(CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions);

/* Comparison convenience suitable for passing as sorting functions.
   kCFCompareNumerically, added in 10.2, does not work if kCFCompareLocalized is specified on systems before 10.3
   kCFCompareBackwards and kCFCompareAnchored are not applicable.
*/
CF_EXPORT
CFComparisonResult CFStringCompare(CFStringRef theString1, CFStringRef theString2, CFStringCompareFlags compareOptions);

/* CFStringFindWithOptionsAndLocale() returns the found range in the CFRange * argument; you can pass NULL for simple discovery check.
   locale == NULL indicates canonical locale (the return value from CFLocaleGetSystem()).
   If stringToFind is the empty string (zero length), nothing is found.
   Ignores the kCFCompareNumerically option.
   Only the substring of theString specified by rangeToSearch is searched for stringToFind.
*/
CF_EXPORT
Boolean CFStringFindWithOptionsAndLocale(CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFLocaleRef locale, CFRange *result) CF_AVAILABLE(10_5, 2_0);

/* Find convenience. Uses the current user locale (the return value from CFLocaleCopyCurrent()) if kCFCompareLocalized. Refer to CFStringFindWithOptionsAndLocale() for more info.
*/
CF_EXPORT
Boolean CFStringFindWithOptions(CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange *result);

/* CFStringCreateArrayWithFindResults() returns an array of CFRange pointers, or NULL if there are no matches.
   Overlapping instances are not found; so looking for "AA" in "AAA" finds just one range.
   Post 10.1: If kCFCompareBackwards is provided, the scan is done from the end (which can give a different result), and
      the results are stored in the array backwards (last found range in slot 0).
   If stringToFind is the empty string (zero length), nothing is found.
   kCFCompareAnchored causes just the consecutive instances at start (or end, if kCFCompareBackwards) to be reported. So, searching for "AB" in "ABABXAB..." you just get the first two occurrences.
   Ignores the kCFCompareNumerically option.
   Only the substring of theString specified by rangeToSearch is searched for stringToFind.
*/
CF_EXPORT
CFArrayRef CFStringCreateArrayWithFindResults(CFAllocatorRef alloc, CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags compareOptions);

/* Find conveniences; see comments above concerning empty string and options.
*/
CF_EXPORT
CFRange CFStringFind(CFStringRef theString, CFStringRef stringToFind, CFStringCompareFlags compareOptions);

CF_EXPORT
Boolean CFStringHasPrefix(CFStringRef theString, CFStringRef prefix);

CF_EXPORT
Boolean CFStringHasSuffix(CFStringRef theString, CFStringRef suffix);

/*!
	@function CFStringGetRangeOfComposedCharactersAtIndex
	Returns the range of the composed character sequence at the specified index.
	@param theString The CFString which is to be searched.  If this
                		parameter is not a valid CFString, the behavior is
              		undefined.
	@param theIndex The index of the character contained in the
			composed character sequence.  If the index is
			outside the index space of the string (0 to N-1 inclusive,
			where N is the length of the string), the behavior is
			undefined.
	@result The range of the composed character sequence.
*/
CF_EXPORT CFRange CFStringGetRangeOfComposedCharactersAtIndex(CFStringRef theString, CFIndex theIndex);

/*!
	@function CFStringFindCharacterFromSet
	Query the range of the first character contained in the specified character set.
	@param theString The CFString which is to be searched.  If this
                		parameter is not a valid CFString, the behavior is
              		undefined.
	@param theSet The CFCharacterSet against which the membership
			of characters is checked.  If this parameter is not a valid
			CFCharacterSet, the behavior is undefined.
	@param range The range of characters within the string to search. If
			the range location or end point (defined by the location
			plus length minus 1) are outside the index space of the
			string (0 to N-1 inclusive, where N is the length of the
			string), the behavior is undefined. If the range length is
			negative, the behavior is undefined. The range may be empty
			(length 0), in which case no search is performed.
	@param searchOptions The bitwise-or'ed option flags to control
			the search behavior.  The supported options are
			kCFCompareBackwards andkCFCompareAnchored.
			If other option flags are specified, the behavior
                        is undefined.
	@param result The pointer to a CFRange supplied by the caller in
			which the search result is stored.  Note that the length
			of this range can be more than 1, if for instance the 
			result is a composed character. If a pointer to an invalid
			memory is specified, the behavior is undefined.
	@result true, if at least a character which is a member of the character
			set is found and result is filled, otherwise, false.
*/
CF_EXPORT Boolean CFStringFindCharacterFromSet(CFStringRef theString, CFCharacterSetRef theSet, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange *result);

/* Find range of bounds of the line(s) that span the indicated range (startIndex, numChars),
   taking into account various possible line separator sequences (CR, CRLF, LF, and Unicode NextLine, LineSeparator, ParagraphSeparator).
   All return values are "optional" (provide NULL if you don't want them)
     lineBeginIndex: index of first character in line
     lineEndIndex: index of first character of the next line (including terminating line separator characters)
     contentsEndIndex: index of the first line separator character
   Thus, lineEndIndex - lineBeginIndex is the number of chars in the line, including the line separators
         contentsEndIndex - lineBeginIndex is the number of chars in the line w/out the line separators
*/
CF_EXPORT
void CFStringGetLineBounds(CFStringRef theString, CFRange range, CFIndex *lineBeginIndex, CFIndex *lineEndIndex, CFIndex *contentsEndIndex); 

/* Same as CFStringGetLineBounds(), however, will only look for paragraphs. Won't stop at Unicode NextLine or LineSeparator characters.
*/
CF_EXPORT
void CFStringGetParagraphBounds(CFStringRef string, CFRange range, CFIndex *parBeginIndex, CFIndex *parEndIndex, CFIndex *contentsEndIndex) CF_AVAILABLE(10_5, 2_0);

/*!
	@function CFStringGetHyphenationLocationBeforeIndex
	Retrieve the first potential hyphenation location found before the specified location.
	@param string The CFString which is to be hyphenated.  If this
                		parameter is not a valid CFString, the behavior is
              		undefined.
	@param location An index in the string.  If a valid hyphen index is returned, it 
	                will be before this index.
	@param limitRange The range of characters within the string to search. If
			the range location or end point (defined by the location
			plus length minus 1) are outside the index space of the
			string (0 to N-1 inclusive, where N is the length of the
			string), the behavior is undefined. If the range length is
			negative, the behavior is undefined. The range may be empty
			(length 0), in which case no hyphen location is generated.
	@param options Reserved for future use.
	@param locale Specifies which language's hyphenation conventions to use.
			This must be a valid locale.  Hyphenation data is not available
			for all locales.  You can use CFStringIsHyphenationAvailableForLocale
			to test for availability of hyphenation data.
	@param character The suggested hyphen character to insert.  Pass NULL if you
			do not need this information.
	@result an index in the string where it is appropriate to insert a hyphen, if
			one exists; else kCFNotFound
*/
CF_EXPORT
CFIndex CFStringGetHyphenationLocationBeforeIndex(CFStringRef string, CFIndex location, CFRange limitRange, CFOptionFlags options, CFLocaleRef locale, UTF32Char *character) CF_AVAILABLE(10_7, 4_2);

CF_EXPORT
Boolean CFStringIsHyphenationAvailableForLocale(CFLocaleRef locale) CF_AVAILABLE(10_7, 4_3);

/*** Exploding and joining strings with a separator string ***/

CF_EXPORT
CFStringRef CFStringCreateByCombiningStrings(CFAllocatorRef alloc, CFArrayRef theArray, CFStringRef separatorString);	/* Empty array returns empty string; one element array returns the element */

CF_EXPORT
CFArrayRef CFStringCreateArrayBySeparatingStrings(CFAllocatorRef alloc, CFStringRef theString, CFStringRef separatorString);	/* No separators in the string returns array with that string; string == sep returns two empty strings */


/*** Parsing non-localized numbers from strings ***/

CF_EXPORT
SInt32 CFStringGetIntValue(CFStringRef str);		/* Skips whitespace; returns 0 on error, MAX or -MAX on overflow */

CF_EXPORT
double CFStringGetDoubleValue(CFStringRef str);	/* Skips whitespace; returns 0.0 on error */


/*** MutableString functions ***/

/* CFStringAppend("abcdef", "xxxxx") -> "abcdefxxxxx"
   CFStringDelete("abcdef", CFRangeMake(2, 3)) -> "abf"
   CFStringReplace("abcdef", CFRangeMake(2, 3), "xxxxx") -> "abxxxxxf"
   CFStringReplaceAll("abcdef", "xxxxx") -> "xxxxx"
*/
CF_EXPORT
void CFStringAppend(CFMutableStringRef theString, CFStringRef appendedString);

CF_EXPORT
void CFStringAppendCharacters(CFMutableStringRef theString, const UniChar *chars, CFIndex numChars);

CF_EXPORT
void CFStringAppendPascalString(CFMutableStringRef theString, ConstStr255Param pStr, CFStringEncoding encoding);

CF_EXPORT
void CFStringAppendCString(CFMutableStringRef theString, const char *cStr, CFStringEncoding encoding);

CF_EXPORT
void CFStringAppendFormat(CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, ...) CF_FORMAT_FUNCTION(3,4);

CF_EXPORT
void CFStringAppendFormatAndArguments(CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments) CF_FORMAT_FUNCTION(3,0);

CF_EXPORT
void CFStringInsert(CFMutableStringRef str, CFIndex idx, CFStringRef insertedStr);

CF_EXPORT
void CFStringDelete(CFMutableStringRef theString, CFRange range);

CF_EXPORT
void CFStringReplace(CFMutableStringRef theString, CFRange range, CFStringRef replacement);

CF_EXPORT
void CFStringReplaceAll(CFMutableStringRef theString, CFStringRef replacement);	/* Replaces whole string */

/* Replace all occurrences of target in rangeToSearch of theString with replacement.
   Pays attention to kCFCompareCaseInsensitive, kCFCompareBackwards, kCFCompareNonliteral, and kCFCompareAnchored.
   kCFCompareBackwards can be used to do the replacement starting from the end, which could give a different result.
     ex. AAAAA, replace AA with B -> BBA or ABB; latter if kCFCompareBackwards
   kCFCompareAnchored assures only anchored but multiple instances are found (the instances must be consecutive at start or end)
     ex. AAXAA, replace A with B -> BBXBB or BBXAA; latter if kCFCompareAnchored
   Returns number of replacements performed.
*/
CF_EXPORT
CFIndex CFStringFindAndReplace(CFMutableStringRef theString, CFStringRef stringToFind, CFStringRef replacementString, CFRange rangeToSearch, CFStringCompareFlags compareOptions);


/* This function will make the contents of a mutable CFString point directly at the specified UniChar array.
   It works only with CFStrings created with CFStringCreateMutableWithExternalCharactersNoCopy().
   This function does not free the previous buffer.
   The string will be manipulated within the provided buffer (if any) until it outgrows capacity; then the
     externalCharactersAllocator will be consulted for more memory.
   See comments at the top of this file for more info.
*/
CF_EXPORT
void CFStringSetExternalCharactersNoCopy(CFMutableStringRef theString, UniChar *chars, CFIndex length, CFIndex capacity);	/* Works only on specially created mutable strings! */

/* CFStringPad() will pad or cut down a string to the specified size.
   The pad string is used as the fill string; indexIntoPad specifies which character to start with.
     CFStringPad("abc", " ", 9, 0) ->  "abc      "
     CFStringPad("abc", ". ", 9, 1) -> "abc . . ."
     CFStringPad("abcdef", ?, 3, ?) -> "abc"

     CFStringTrim() will trim the specified string from both ends of the string.
     CFStringTrimWhitespace() will do the same with white space characters (tab, newline, etc)
     CFStringTrim("  abc ", " ") -> "abc"
     CFStringTrim("* * * *abc * ", "* ") -> "*abc "
*/
CF_EXPORT
void CFStringPad(CFMutableStringRef theString, CFStringRef padString, CFIndex length, CFIndex indexIntoPad);

CF_EXPORT
void CFStringTrim(CFMutableStringRef theString, CFStringRef trimString);

CF_EXPORT
void CFStringTrimWhitespace(CFMutableStringRef theString);

CF_EXPORT
void CFStringLowercase(CFMutableStringRef theString, CFLocaleRef locale);

CF_EXPORT
void CFStringUppercase(CFMutableStringRef theString, CFLocaleRef locale);

CF_EXPORT
void CFStringCapitalize(CFMutableStringRef theString, CFLocaleRef locale);

/*!
	@typedef CFStringNormalizationForm
	This is the type of Unicode normalization forms as described in
	Unicode Technical Report #15. To normalize for use with file
	system calls, use CFStringGetFileSystemRepresentation().
*/
typedef CF_ENUM(CFIndex, CFStringNormalizationForm) {
	kCFStringNormalizationFormD = 0, // Canonical Decomposition
	kCFStringNormalizationFormKD, // Compatibility Decomposition
	kCFStringNormalizationFormC, // Canonical Decomposition followed by Canonical Composition
	kCFStringNormalizationFormKC // Compatibility Decomposition followed by Canonical Composition
};

/*!
	@function CFStringNormalize
	Normalizes the string into the specified form as described in
	Unicode Technical Report #15.
	@param theString  The string which is to be normalized.  If this
		parameter is not a valid mutable CFString, the behavior is
		undefined.
	@param theForm  The form into which the string is to be normalized.
		If this parameter is not a valid CFStringNormalizationForm value,
		the behavior is undefined.
*/
CF_EXPORT void CFStringNormalize(CFMutableStringRef theString, CFStringNormalizationForm theForm);


/*!
	@function CFStringFold
	Folds the string into the form specified by the flags.
		Character foldings are operations that convert any of a set of characters
		sharing similar semantics into a single representative from that set.
		This function can be used to preprocess strings that are to be compared,
		searched, or indexed.
		Note that folding does not include normalization, so it is necessary
		to use CFStringNormalize in addition to CFStringFold in order to obtain
		the effect of kCFCompareNonliteral.
	@param theString  The string which is to be folded.  If this parameter is not
		a valid mutable CFString, the behavior is undefined.
	@param theFlag  The equivalency flags which describes the character folding form.
		Only those flags containing the word "insensitive" are recognized here; other flags are ignored.		
		Folding with kCFCompareCaseInsensitive removes case distinctions in accordance with the mapping
		specified by ftp://ftp.unicode.org/Public/UNIDATA/CaseFolding.txt.  Folding with
		kCFCompareDiacriticInsensitive removes distinctions of accents and other diacritics.  Folding
		with kCFCompareWidthInsensitive removes character width distinctions by mapping characters in
		the range U+FF00-U+FFEF to their ordinary equivalents.
	@param theLocale The locale tailoring the character folding behavior. If NULL,
		it's considered to be the system locale returned from CFLocaleGetSystem().
		If non-NULL and not a valid CFLocale object, the behavior is undefined.
*/

CF_EXPORT
void CFStringFold(CFMutableStringRef theString, CFStringCompareFlags theFlags, CFLocaleRef theLocale) CF_AVAILABLE(10_5, 2_0);

/* Perform string transliteration.  The transformation represented by transform is applied to the given range of string, modifying it in place. Only the specified range will be modified, but the transform may look at portions of the string outside that range for context. NULL range pointer causes the whole string to be transformed. On return, range is modified to reflect the new range corresponding to the original range. reverse indicates that the inverse transform should be used instead, if it exists. If the transform is successful, true is returned; if unsuccessful, false. Reasons for the transform being unsuccessful include an invalid transform identifier, or attempting to reverse an irreversible transform.

You can pass one of the predefined transforms below, or any valid ICU transform ID as defined in the ICU User Guide. Note that we do not support arbitrary set of ICU transform rules.
*/
CF_EXPORT
Boolean CFStringTransform(CFMutableStringRef string, CFRange *range, CFStringRef transform, Boolean reverse);

/* Transform identifiers for CFStringTransform()
*/
CF_EXPORT const CFStringRef kCFStringTransformStripCombiningMarks;
CF_EXPORT const CFStringRef kCFStringTransformToLatin;
CF_EXPORT const CFStringRef kCFStringTransformFullwidthHalfwidth;
CF_EXPORT const CFStringRef kCFStringTransformLatinKatakana;
CF_EXPORT const CFStringRef kCFStringTransformLatinHiragana;
CF_EXPORT const CFStringRef kCFStringTransformHiraganaKatakana;
CF_EXPORT const CFStringRef kCFStringTransformMandarinLatin;
CF_EXPORT const CFStringRef kCFStringTransformLatinHangul;
CF_EXPORT const CFStringRef kCFStringTransformLatinArabic;
CF_EXPORT const CFStringRef kCFStringTransformLatinHebrew;
CF_EXPORT const CFStringRef kCFStringTransformLatinThai;
CF_EXPORT const CFStringRef kCFStringTransformLatinCyrillic;
CF_EXPORT const CFStringRef kCFStringTransformLatinGreek;
CF_EXPORT const CFStringRef kCFStringTransformToXMLHex;
CF_EXPORT const CFStringRef kCFStringTransformToUnicodeName;
CF_EXPORT const CFStringRef kCFStringTransformStripDiacritics CF_AVAILABLE(10_5, 2_0);


/*** General encoding related functionality ***/

/* This returns availability of the encoding on the system
*/
CF_EXPORT
Boolean CFStringIsEncodingAvailable(CFStringEncoding encoding);

/* This function returns list of available encodings.  The returned list is terminated with kCFStringEncodingInvalidId and owned by the system.
*/
CF_EXPORT
const CFStringEncoding *CFStringGetListOfAvailableEncodings(void);

/* Returns name of the encoding; non-localized.
*/
CF_EXPORT
CFStringRef CFStringGetNameOfEncoding(CFStringEncoding encoding);

/* ID mapping functions from/to Cocoa NSStringEncoding.  Returns kCFStringEncodingInvalidId if no mapping exists.
*/
CF_EXPORT
unsigned long CFStringConvertEncodingToNSStringEncoding(CFStringEncoding encoding);

CF_EXPORT
CFStringEncoding CFStringConvertNSStringEncodingToEncoding(unsigned long encoding);

/* ID mapping functions from/to Microsoft Windows codepage (covers both OEM & ANSI).  Returns kCFStringEncodingInvalidId if no mapping exists.
*/
CF_EXPORT
UInt32 CFStringConvertEncodingToWindowsCodepage(CFStringEncoding encoding);

CF_EXPORT
CFStringEncoding CFStringConvertWindowsCodepageToEncoding(UInt32 codepage);

/* ID mapping functions from/to IANA registery charset names.  Returns kCFStringEncodingInvalidId if no mapping exists.
*/
CF_EXPORT
CFStringEncoding CFStringConvertIANACharSetNameToEncoding(CFStringRef theString);

CF_EXPORT
CFStringRef  CFStringConvertEncodingToIANACharSetName(CFStringEncoding encoding);

/* Returns the most compatible MacOS script value for the input encoding */
/* i.e. kCFStringEncodingMacRoman -> kCFStringEncodingMacRoman */
/*	kCFStringEncodingWindowsLatin1 -> kCFStringEncodingMacRoman */
/*	kCFStringEncodingISO_2022_JP -> kCFStringEncodingMacJapanese */
CF_EXPORT
CFStringEncoding CFStringGetMostCompatibleMacStringEncoding(CFStringEncoding encoding);



/* The next two functions allow fast access to the contents of a string, 
   assuming you are doing sequential or localized accesses. To use, call
   CFStringInitInlineBuffer() with a CFStringInlineBuffer (on the stack, say),
   and a range in the string to look at. Then call CFStringGetCharacterFromInlineBuffer()
   as many times as you want, with a index into that range (relative to the start
   of that range). These are INLINE functions and will end up calling CFString only 
   once in a while, to fill a buffer.  CFStringGetCharacterFromInlineBuffer() returns 0 if
   a location outside the original range is specified.
*/
#define __kCFStringInlineBufferLength 64
typedef struct {
    UniChar buffer[__kCFStringInlineBufferLength];
    CFStringRef theString;
    const UniChar *directUniCharBuffer;
    const char *directCStringBuffer;
    CFRange rangeToBuffer;		/* Range in string to buffer */
    CFIndex bufferedRangeStart;		/* Start of range currently buffered (relative to rangeToBuffer.location) */
    CFIndex bufferedRangeEnd;		/* bufferedRangeStart + number of chars actually buffered */
} CFStringInlineBuffer;

#if defined(CF_INLINE)
CF_INLINE void CFStringInitInlineBuffer(CFStringRef str, CFStringInlineBuffer *buf, CFRange range) {
    buf->theString = str;
    buf->rangeToBuffer = range;
    buf->directCStringBuffer = (buf->directUniCharBuffer = CFStringGetCharactersPtr(str)) ? NULL : CFStringGetCStringPtr(str, kCFStringEncodingASCII);
    buf->bufferedRangeStart = buf->bufferedRangeEnd = 0;
}

CF_INLINE UniChar CFStringGetCharacterFromInlineBuffer(CFStringInlineBuffer *buf, CFIndex idx) {
    if (idx < 0 || idx >= buf->rangeToBuffer.length) return 0;
    if (buf->directUniCharBuffer) return buf->directUniCharBuffer[idx + buf->rangeToBuffer.location];
    if (buf->directCStringBuffer) return (UniChar)(buf->directCStringBuffer[idx + buf->rangeToBuffer.location]);
    if (idx >= buf->bufferedRangeEnd || idx < buf->bufferedRangeStart) {
	if ((buf->bufferedRangeStart = idx - 4) < 0) buf->bufferedRangeStart = 0;
	buf->bufferedRangeEnd = buf->bufferedRangeStart + __kCFStringInlineBufferLength;
	if (buf->bufferedRangeEnd > buf->rangeToBuffer.length) buf->bufferedRangeEnd = buf->rangeToBuffer.length;
	CFStringGetCharacters(buf->theString, CFRangeMake(buf->rangeToBuffer.location + buf->bufferedRangeStart, buf->bufferedRangeEnd - buf->bufferedRangeStart), buf->buffer);
    }
    return buf->buffer[idx - buf->bufferedRangeStart];
}

#else
/* If INLINE functions are not available, we do somewhat less powerful macros that work similarly (except be aware that the buf argument is evaluated multiple times).
*/
#define CFStringInitInlineBuffer(str, buf, range) \
    do {(buf)->theString = str; (buf)->rangeToBuffer = range; (buf)->directCStringBuffer = ((buf)->directUniCharBuffer = CFStringGetCharactersPtr(str)) ? NULL : CFStringGetCStringPtr(str, kCFStringEncodingASCII);} while (0)

#define CFStringGetCharacterFromInlineBuffer(buf, idx) \
    (((idx) < 0 || (idx) >= (buf)->rangeToBuffer.length) ? 0 : ((buf)->directUniCharBuffer ? (buf)->directUniCharBuffer[(idx) + (buf)->rangeToBuffer.location] : ((buf)->directCStringBuffer ? (UniChar)((buf)->directCStringBuffer[(idx) + (buf)->rangeToBuffer.location]) : CFStringGetCharacterAtIndex((buf)->theString, (idx) + (buf)->rangeToBuffer.location))))

#endif /* CF_INLINE */



/* UTF-16 surrogate support
 */
CF_INLINE Boolean CFStringIsSurrogateHighCharacter(UniChar character) {
    return ((character >= 0xD800UL) && (character <= 0xDBFFUL) ? true : false);
}

CF_INLINE Boolean CFStringIsSurrogateLowCharacter(UniChar character) {
    return ((character >= 0xDC00UL) && (character <= 0xDFFFUL) ? true : false);
}

CF_INLINE UTF32Char CFStringGetLongCharacterForSurrogatePair(UniChar surrogateHigh, UniChar surrogateLow) {
    return (UTF32Char)(((surrogateHigh - 0xD800UL) << 10) + (surrogateLow - 0xDC00UL) + 0x0010000UL);
}

// Maps a UTF-32 character to a pair of UTF-16 surrogate characters. The buffer pointed by surrogates has to have space for at least 2 UTF-16 characters. Returns true if mapped to a surrogate pair.
CF_INLINE Boolean CFStringGetSurrogatePairForLongCharacter(UTF32Char character, UniChar *surrogates) {
    if ((character > 0xFFFFUL) && (character < 0x110000UL)) { // Non-BMP character
        character -= 0x10000;
        if (NULL != surrogates) {
            surrogates[0] = (UniChar)((character >> 10) + 0xD800UL);
            surrogates[1] = (UniChar)((character & 0x3FF) + 0xDC00UL);
        }
        return true;
    } else {
        if (NULL != surrogates) *surrogates = (UniChar)character;
        return false;
    }
}

/* Rest of the stuff in this file is private and should not be used directly
*/
/* For debugging only; output goes to stderr
   Use CFShow() to printf the description of any CFType;
   Use CFShowStr() to printf detailed info about a CFString
*/
CF_EXPORT
void CFShow(CFTypeRef obj);

CF_EXPORT
void CFShowStr(CFStringRef str);

/* This function is private and should not be used directly */
CF_EXPORT
CFStringRef  __CFStringMakeConstantString(const char *cStr) CF_FORMAT_ARGUMENT(1);	/* Private; do not use */

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFSTRING__ */
// ==========  CoreFoundation.framework/Headers/CFBinaryHeap.h
/*	CFBinaryHeap.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/
/*!
        @header CFBinaryHeap
        CFBinaryHeap implements a container which stores values sorted using
        a binary search algorithm.  CFBinaryHeaps can be useful as priority
	queues.
*/

#if !defined(__COREFOUNDATION_CFBINARYHEAP__)
#define __COREFOUNDATION_CFBINARYHEAP__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFBinaryHeapCompareContext;

/*!
        @typedef CFBinaryHeapCallBacks
	Structure containing the callbacks for values of a CFBinaryHeap.
        @field version The version number of the structure type being passed
                in as a parameter to the CFBinaryHeap creation functions.
                This structure is version 0.
	@field retain The callback used to add a retain for the binary heap
		on values as they are put into the binary heap.
		This callback returns the value to use as the value in the
		binary heap, which is usually the value parameter passed to
		this callback, but may be a different value if a different
		value should be added to the binary heap. The binary heap's
		allocator is passed as the first argument.
	@field release The callback used to remove a retain previously added
		for the binary heap from values as they are removed from
		the binary heap. The binary heap's allocator is passed as the
		first argument.
	@field copyDescription The callback used to create a descriptive
		string representation of each value in the binary heap. This
		is used by the CFCopyDescription() function.
	@field compare The callback used to compare values in the binary heap for
		equality in some operations.
*/
typedef struct {
    CFIndex	version;
    const void *(*retain)(CFAllocatorRef allocator, const void *ptr);
    void	(*release)(CFAllocatorRef allocator, const void *ptr);
    CFStringRef	(*copyDescription)(const void *ptr);
    CFComparisonResult	(*compare)(const void *ptr1, const void *ptr2, void *context);
} CFBinaryHeapCallBacks;

/*!
	@constant kCFStringBinaryHeapCallBacks
	Predefined CFBinaryHeapCallBacks structure containing a set
	of callbacks appropriate for use when the values in a CFBinaryHeap
	are all CFString types.
*/
CF_EXPORT const CFBinaryHeapCallBacks kCFStringBinaryHeapCallBacks;

/*!
	@typedef CFBinaryHeapApplierFunction
	Type of the callback function used by the apply functions of
		CFBinaryHeap.
	@param value The current value from the binary heap.
	@param context The user-defined context parameter given to the apply
		function.
*/
typedef void (*CFBinaryHeapApplierFunction)(const void *val, void *context);

/*!
	@typedef CFBinaryHeapRef
	This is the type of a reference to CFBinaryHeaps.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFBinaryHeap * CFBinaryHeapRef;

/*!
	@function CFBinaryHeapGetTypeID
	Returns the type identifier of all CFBinaryHeap instances.
*/
CF_EXPORT CFTypeID	CFBinaryHeapGetTypeID(void);

/*!
	@function CFBinaryHeapCreate
	Creates a new mutable binary heap with the given values.
	@param allocator The CFAllocator which should be used to allocate
		memory for the binary heap and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFBinaryHeap. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A heap's actual capacity is only limited by 
                address space and available memory constraints). If this 
                parameter is negative, the behavior is undefined.
	@param callBacks A pointer to a CFBinaryHeapCallBacks structure
		initialized with the callbacks for the binary heap to use on
		each value in the binary heap. A copy of the contents of the
		callbacks structure is made, so that a pointer to a structure
		on the stack can be passed in, or can be reused for multiple
		binary heap creations. If the version field of this callbacks
		structure is not one of the defined ones for CFBinaryHeap, the
		behavior is undefined. The retain field may be NULL, in which
		case the CFBinaryHeap will do nothing to add a retain to values
		as they are put into the binary heap. The release field may be
		NULL, in which case the CFBinaryHeap will do nothing to remove
		the binary heap's retain (if any) on the values when the
		heap is destroyed or a key-value pair is removed. If the
		copyDescription field is NULL, the binary heap will create a
		simple description for a value. If the equal field is NULL, the
		binary heap will use pointer equality to test for equality of
		values. This callbacks parameter itself may be NULL, which is
		treated as if a valid structure of version 0 with all fields
		NULL had been passed in. Otherwise,
		if any of the fields are not valid pointers to functions
		of the correct type, or this parameter is not a valid
		pointer to a CFBinaryHeapCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		binary heap is not one understood by one of the callback functions
		the behavior when that callback function is used is undefined.
        @param compareContext A pointer to a CFBinaryHeapCompareContext structure.
	@result A reference to the new CFBinaryHeap.
*/
CF_EXPORT CFBinaryHeapRef	CFBinaryHeapCreate(CFAllocatorRef allocator, CFIndex capacity, const CFBinaryHeapCallBacks *callBacks, const CFBinaryHeapCompareContext *compareContext);

/*!
	@function CFBinaryHeapCreateCopy
	Creates a new mutable binary heap with the values from the given binary heap.
	@param allocator The CFAllocator which should be used to allocate
		memory for the binary heap and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFBinaryHeap. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A heap's actual capacity is only limited by
                address space and available memory constraints). 
                This parameter must be greater than or equal
                to the count of the heap which is to be copied, or the
                behavior is undefined. If this parameter is negative, the
                behavior is undefined.
	@param heap The binary heap which is to be copied. The values from the
		binary heap are copied as pointers into the new binary heap (that is,
		the values themselves are copied, not that which the values
		point to, if anything). However, the values are also
		retained by the new binary heap. The count of the new binary will
		be the same as the given binary heap. The new binary heap uses the same
		callbacks as the binary heap to be copied. If this parameter is
		not a valid CFBinaryHeap, the behavior is undefined.
	@result A reference to the new mutable binary heap.
*/
CF_EXPORT CFBinaryHeapRef	CFBinaryHeapCreateCopy(CFAllocatorRef allocator, CFIndex capacity, CFBinaryHeapRef heap);

/*!
	@function CFBinaryHeapGetCount
	Returns the number of values currently in the binary heap.
	@param heap The binary heap to be queried. If this parameter is not a valid
		CFBinaryHeap, the behavior is undefined.
	@result The number of values in the binary heap.
*/
CF_EXPORT CFIndex	CFBinaryHeapGetCount(CFBinaryHeapRef heap);

/*!
	@function CFBinaryHeapGetCountOfValue
	Counts the number of times the given value occurs in the binary heap.
	@param heap The binary heap to be searched. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
	@param value The value for which to find matches in the binary heap. The
		compare() callback provided when the binary heap was created is
		used to compare. If the compare() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the binary heap, are not understood by the compare() callback,
		the behavior is undefined.
	@result The number of times the given value occurs in the binary heap.
*/
CF_EXPORT CFIndex	CFBinaryHeapGetCountOfValue(CFBinaryHeapRef heap, const void *value);

/*!
	@function CFBinaryHeapContainsValue
	Reports whether or not the value is in the binary heap.
	@param heap The binary heap to be searched. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
	@param value The value for which to find matches in the binary heap. The
		compare() callback provided when the binary heap was created is
		used to compare. If the compare() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the binary heap, are not understood by the compare() callback,
		the behavior is undefined.
	@result true, if the value is in the specified binary heap, otherwise false.
*/
CF_EXPORT Boolean	CFBinaryHeapContainsValue(CFBinaryHeapRef heap, const void *value);

/*!
	@function CFBinaryHeapGetMinimum
	Returns the minimum value is in the binary heap.  If the heap contains several equal
                minimum values, any one may be returned.
	@param heap The binary heap to be searched. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
	@result A reference to the minimum value in the binary heap, or NULL if the
                binary heap contains no values.
*/
CF_EXPORT const void *	CFBinaryHeapGetMinimum(CFBinaryHeapRef heap);

/*!
	@function CFBinaryHeapGetMinimumIfPresent
	Returns the minimum value is in the binary heap, if present.  If the heap contains several equal
                minimum values, any one may be returned.
	@param heap The binary heap to be searched. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
        @param value A C pointer to pointer-sized storage to be filled with the minimum value in 
                the binary heap.  If this value is not a valid C pointer to a pointer-sized block
                of storage, the result is undefined.  If the result of the function is false, the value
                stored at this address is undefined.
	@result true, if a minimum value was found in the specified binary heap, otherwise false.
*/
CF_EXPORT Boolean	CFBinaryHeapGetMinimumIfPresent(CFBinaryHeapRef heap, const void **value);

/*!
	@function CFBinaryHeapGetValues
	Fills the buffer with values from the binary heap.
	@param heap The binary heap to be queried. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
	@param values A C array of pointer-sized values to be filled with
		values from the binary heap. The values in the C array are ordered
		from least to greatest. If this parameter is not a valid pointer to a 
                C array of at least CFBinaryHeapGetCount() pointers, the behavior is undefined.
*/
CF_EXPORT void		CFBinaryHeapGetValues(CFBinaryHeapRef heap, const void **values);

/*!
	@function CFBinaryHeapApplyFunction
	Calls a function once for each value in the binary heap.
	@param heap The binary heap to be operated upon. If this parameter is not a
		valid CFBinaryHeap, the behavior is undefined.
	@param applier The callback function to call once for each value in
		the given binary heap. If this parameter is not a
		pointer to a function of the correct prototype, the behavior
		is undefined. If there are values in the binary heap which the
		applier function does not expect or cannot properly apply
		to, the behavior is undefined. 
	@param context A pointer-sized user-defined value, which is passed
		as the second parameter to the applier function, but is
		otherwise unused by this function. If the context is not
		what is expected by the applier function, the behavior is
		undefined.
*/
CF_EXPORT void		CFBinaryHeapApplyFunction(CFBinaryHeapRef heap, CFBinaryHeapApplierFunction applier, void *context);

/*!
	@function CFBinaryHeapAddValue
	Adds the value to the binary heap.
	@param heap The binary heap to which the value is to be added. If this parameter is not a
		valid mutable CFBinaryHeap, the behavior is undefined.
	@param value The value to add to the binary heap. The value is retained by
		the binary heap using the retain callback provided when the binary heap
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined.
*/
CF_EXPORT void		CFBinaryHeapAddValue(CFBinaryHeapRef heap, const void *value);

/*!
	@function CFBinaryHeapRemoveMinimumValue
	Removes the minimum value from the binary heap.
	@param heap The binary heap from which the minimum value is to be removed. If this 
                parameter is not a valid mutable CFBinaryHeap, the behavior is undefined.
*/
CF_EXPORT void		CFBinaryHeapRemoveMinimumValue(CFBinaryHeapRef heap);

/*!
	@function CFBinaryHeapRemoveAllValues
	Removes all the values from the binary heap, making it empty.
	@param heap The binary heap from which all of the values are to be
		removed. If this parameter is not a valid mutable CFBinaryHeap,
		the behavior is undefined.
*/
CF_EXPORT void		CFBinaryHeapRemoveAllValues(CFBinaryHeapRef heap);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFBINARYHEAP__ */

// ==========  CoreFoundation.framework/Headers/CFBase.h
/*	CFBase.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBASE__)
#define __COREFOUNDATION_CFBASE__ 1

#include <TargetConditionals.h>
#include <CoreFoundation/CFAvailability.h>

#if (defined(__CYGWIN32__) || defined(_WIN32)) && !defined(__WIN32__)
#define __WIN32__ 1
#endif

#if defined(_WIN64) && !defined(__WIN64__)
#define __WIN64__ 1
#endif

#if defined(__WIN64__) && !defined(__LLP64__)
#define __LLP64__ 1
#endif

#if defined(_MSC_VER) && defined(_M_IX86)
#define __i386__ 1
#endif

#if (defined(__i386__) || defined(__x86_64__)) && !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__ 1
#endif

#if !defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)
#error Do not know the endianess of this architecture
#endif

#if !__BIG_ENDIAN__ && !__LITTLE_ENDIAN__
#error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be false
#endif

#if __BIG_ENDIAN__ && __LITTLE_ENDIAN__
#error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be true
#endif

// Some compilers provide the capability to test if certain features are available. This macro provides a compatibility path for other compilers.
#ifndef __has_feature
#define __has_feature(x) 0
#endif

// Some compilers provide the capability to test if certain attributes are available. This macro provides a compatibility path for other compilers.
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#ifndef __has_extension
#define __has_extension(x) 0
#endif

#if defined(__GNUC__) || TARGET_OS_WIN32
#include <stdint.h>
#include <stdbool.h>
#endif

#if __BLOCKS__
#include <Block.h>
#endif

#ifndef CF_OPEN_SOURCE
  #if defined(__CF_USE_FRAMEWORK_INCLUDES__) || ((TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    #include <MacTypes.h>
  #endif
#else
  #if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
    #include <libkern/OSTypes.h>
  #endif
#endif

#if !defined(__MACTYPES__)
#if !defined(_OS_OSTYPES_H)
    typedef unsigned char           Boolean;
    typedef unsigned char           UInt8;
    typedef signed char             SInt8;
    typedef unsigned short          UInt16;
    typedef signed short            SInt16;
    typedef unsigned int            UInt32;
    typedef signed int              SInt32;
    typedef uint64_t		    UInt64;
    typedef int64_t		    SInt64;
    typedef SInt32                  OSStatus;
#endif
    typedef float                   Float32;
    typedef double                  Float64;
    typedef unsigned short          UniChar;
    typedef unsigned long           UniCharCount;
    typedef unsigned char *         StringPtr;
    typedef const unsigned char *   ConstStringPtr;
    typedef unsigned char           Str255[256];
    typedef const unsigned char *   ConstStr255Param;
    typedef SInt16                  OSErr;
    typedef SInt16                  RegionCode;
    typedef SInt16                  LangCode;
    typedef SInt16                  ScriptCode;
    typedef UInt32                  FourCharCode;
    typedef FourCharCode            OSType;
    typedef UInt8                   Byte;
    typedef SInt8                   SignedByte;
#endif
#if !defined(__MACTYPES__) || (defined(UNIVERSAL_INTERFACES_VERSION) && UNIVERSAL_INTERFACES_VERSION < 0x0340)
    typedef UInt32                  UTF32Char;
    typedef UInt16                  UTF16Char;
    typedef UInt8                   UTF8Char;
#endif

#if !defined(CF_EXTERN_C_BEGIN)
#if defined(__cplusplus)
#define CF_EXTERN_C_BEGIN extern "C" {
#define CF_EXTERN_C_END   }
#else
#define CF_EXTERN_C_BEGIN
#define CF_EXTERN_C_END
#endif
#endif

#if TARGET_OS_WIN32

#if !defined(CF_EXPORT)
#if defined(CF_BUILDING_CF) && defined(__cplusplus)
#define CF_EXPORT extern "C" __declspec(dllexport) 
#elif defined(CF_BUILDING_CF) && !defined(__cplusplus)
#define CF_EXPORT extern __declspec(dllexport) 
#elif defined(__cplusplus)
#define CF_EXPORT extern "C" __declspec(dllimport) 
#else
#define CF_EXPORT extern __declspec(dllimport) 
#endif
#endif

#else
#define CF_EXPORT extern
#endif

CF_EXTERN_C_BEGIN

#if !defined(NULL)
#if defined(__GNUG__)
    #define NULL __null
#elif defined(__cplusplus)
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif
#endif

#if !defined(TRUE)
    #define TRUE	1
#endif

#if !defined(FALSE)
    #define FALSE	0
#endif

#if !defined(CF_INLINE)
    #if defined(__GNUC__) && (__GNUC__ == 4) && !defined(DEBUG)
        #define CF_INLINE static __inline__ __attribute__((always_inline))
    #elif defined(__GNUC__)
        #define CF_INLINE static __inline__
    #elif defined(__cplusplus)
	#define CF_INLINE static inline
    #elif defined(_MSC_VER)
        #define CF_INLINE static __inline
    #elif TARGET_OS_WIN32
	#define CF_INLINE static __inline__
    #endif
#endif

// Marks functions which return a CF type that needs to be released by the caller but whose names are not consistent with CoreFoundation naming rules. The recommended fix to this is to rename the functions, but this macro can be used to let the clang static analyzer know of any exceptions that cannot be fixed.
// This macro is ONLY to be used in exceptional circumstances, not to annotate functions which conform to the CoreFoundation naming rules.
#ifndef CF_RETURNS_RETAINED
#if __has_feature(attribute_cf_returns_retained)
#define CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
#else
#define CF_RETURNS_RETAINED
#endif
#endif

// Marks functions which return a CF type that may need to be retained by the caller but whose names are not consistent with CoreFoundation naming rules. The recommended fix to this is to rename the functions, but this macro can be used to let the clang static analyzer know of any exceptions that cannot be fixed. 
// This macro is ONLY to be used in exceptional circumstances, not to annotate functions which conform to the CoreFoundation naming rules.
#ifndef CF_RETURNS_NOT_RETAINED
#if __has_feature(attribute_cf_returns_not_retained)
#define CF_RETURNS_NOT_RETAINED __attribute__((cf_returns_not_retained))
#else
#define CF_RETURNS_NOT_RETAINED
#endif
#endif

// Marks function arguments which are released by the callee.
#ifndef CF_RELEASES_ARGUMENT
#if __has_feature(attribute_cf_consumed)
#define CF_RELEASES_ARGUMENT __attribute__((cf_consumed))
#else
#define CF_RELEASES_ARGUMENT
#endif
#endif

// Compatibility
#ifndef CF_CONSUMED
#if __has_feature(attribute_cf_consumed)
#define CF_CONSUMED __attribute__((cf_consumed))
#else
#define CF_CONSUMED
#endif
#endif

// Marks functions which cannot be used when compiling in automatic reference counting mode.
#if __has_feature(objc_arc)
#define CF_AUTOMATED_REFCOUNT_UNAVAILABLE __attribute__((unavailable("not available in automatic reference counting mode")))
#else
#define CF_AUTOMATED_REFCOUNT_UNAVAILABLE
#endif

#ifndef CF_IMPLICIT_BRIDGING_ENABLED
#if __has_feature(arc_cf_code_audited)
#define CF_IMPLICIT_BRIDGING_ENABLED _Pragma("clang arc_cf_code_audited begin")
#else
#define CF_IMPLICIT_BRIDGING_ENABLED
#endif
#endif

#ifndef CF_IMPLICIT_BRIDGING_DISABLED
#if __has_feature(arc_cf_code_audited)
#define CF_IMPLICIT_BRIDGING_DISABLED _Pragma("clang arc_cf_code_audited end")
#else
#define CF_IMPLICIT_BRIDGING_DISABLED
#endif
#endif

#if __has_attribute(objc_bridge) && __has_feature(objc_bridge_id) && __has_feature(objc_bridge_id_on_typedefs)

#ifdef __OBJC__
@class NSArray;
@class NSAttributedString;
@class NSString;
@class NSNull;
@class NSCharacterSet;
@class NSData;
@class NSDate;
@class NSTimeZone;
@class NSDictionary;
@class NSError;
@class NSLocale;
@class NSNumber;
@class NSSet;
@class NSURL;
#endif

#define CF_BRIDGED_TYPE(T)		__attribute__((objc_bridge(T)))
#define CF_BRIDGED_MUTABLE_TYPE(T)	__attribute__((objc_bridge_mutable(T)))
#define CF_RELATED_TYPE(T,C,I)		__attribute__((objc_bridge_related(T,C,I)))
#else
#define CF_BRIDGED_TYPE(T)
#define CF_BRIDGED_MUTABLE_TYPE(T)
#define CF_RELATED_TYPE(T,C,I)
#endif


#if __has_feature(assume_nonnull)
#define CF_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define CF_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else
#define CF_ASSUME_NONNULL_BEGIN
#define CF_ASSUME_NONNULL_END
#endif


#if !__has_feature(nullability)
#ifndef __nullable
#define __nullable
#endif
#ifndef __nonnull
#define __nonnull
#endif
#ifndef __null_unspecified
#define __null_unspecified
#endif
#endif


#if __has_attribute(swift_private)
# define CF_REFINED_FOR_SWIFT __attribute__((swift_private))
#else
# define CF_REFINED_FOR_SWIFT
#endif


#if __has_attribute(swift_name)
# define CF_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
# define CF_SWIFT_NAME(_name)
#endif


#if !__has_feature(objc_generics_variance)
#ifndef __covariant
#define __covariant
#endif
#ifndef __contravariant
#define __contravariant
#endif
#endif


CF_EXPORT double kCFCoreFoundationVersionNumber;

#if TARGET_OS_MAC
#define kCFCoreFoundationVersionNumber10_0	196.40
#define kCFCoreFoundationVersionNumber10_0_3	196.50
#define kCFCoreFoundationVersionNumber10_1	226.00
#define kCFCoreFoundationVersionNumber10_1_1	226.00
/* Note the next three do not follow the usual numbering policy from the base release */
#define kCFCoreFoundationVersionNumber10_1_2	227.20
#define kCFCoreFoundationVersionNumber10_1_3	227.20
#define kCFCoreFoundationVersionNumber10_1_4	227.30
#define kCFCoreFoundationVersionNumber10_2	263.00
#define kCFCoreFoundationVersionNumber10_2_1	263.10
#define kCFCoreFoundationVersionNumber10_2_2	263.10
#define kCFCoreFoundationVersionNumber10_2_3	263.30
#define kCFCoreFoundationVersionNumber10_2_4	263.30
#define kCFCoreFoundationVersionNumber10_2_5	263.50
#define kCFCoreFoundationVersionNumber10_2_6	263.50
#define kCFCoreFoundationVersionNumber10_2_7	263.50
#define kCFCoreFoundationVersionNumber10_2_8	263.50
#define kCFCoreFoundationVersionNumber10_3	299.00
#define kCFCoreFoundationVersionNumber10_3_1	299.00
#define kCFCoreFoundationVersionNumber10_3_2	299.00
#define kCFCoreFoundationVersionNumber10_3_3	299.30
#define kCFCoreFoundationVersionNumber10_3_4	299.31
#define kCFCoreFoundationVersionNumber10_3_5	299.31
#define kCFCoreFoundationVersionNumber10_3_6	299.32
#define kCFCoreFoundationVersionNumber10_3_7	299.33
#define kCFCoreFoundationVersionNumber10_3_8	299.33
#define kCFCoreFoundationVersionNumber10_3_9	299.35
#define kCFCoreFoundationVersionNumber10_4	368.00
#define kCFCoreFoundationVersionNumber10_4_1	368.10
#define kCFCoreFoundationVersionNumber10_4_2	368.11
#define kCFCoreFoundationVersionNumber10_4_3	368.18
#define kCFCoreFoundationVersionNumber10_4_4_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_4_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_5_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_5_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_6_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_6_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_7	368.27
#define kCFCoreFoundationVersionNumber10_4_8	368.27
#define kCFCoreFoundationVersionNumber10_4_9	368.28
#define kCFCoreFoundationVersionNumber10_4_10	368.28
#define kCFCoreFoundationVersionNumber10_4_11	368.31
#define kCFCoreFoundationVersionNumber10_5	476.00
#define kCFCoreFoundationVersionNumber10_5_1	476.00
#define kCFCoreFoundationVersionNumber10_5_2	476.10
#define kCFCoreFoundationVersionNumber10_5_3	476.13
#define kCFCoreFoundationVersionNumber10_5_4	476.14
#define kCFCoreFoundationVersionNumber10_5_5	476.15
#define kCFCoreFoundationVersionNumber10_5_6	476.17
#define kCFCoreFoundationVersionNumber10_5_7	476.18
#define kCFCoreFoundationVersionNumber10_5_8	476.19
#define kCFCoreFoundationVersionNumber10_6	550.00
#define kCFCoreFoundationVersionNumber10_6_1	550.00
#define kCFCoreFoundationVersionNumber10_6_2	550.13
#define kCFCoreFoundationVersionNumber10_6_3	550.19
#define kCFCoreFoundationVersionNumber10_6_4	550.29
#define kCFCoreFoundationVersionNumber10_6_5	550.42
#define kCFCoreFoundationVersionNumber10_6_6	550.42
#define kCFCoreFoundationVersionNumber10_6_7	550.42
#define kCFCoreFoundationVersionNumber10_6_8	550.43
#define kCFCoreFoundationVersionNumber10_7      635.00
#define kCFCoreFoundationVersionNumber10_7_1    635.00
#define kCFCoreFoundationVersionNumber10_7_2    635.15
#define kCFCoreFoundationVersionNumber10_7_3    635.19
#define kCFCoreFoundationVersionNumber10_7_4    635.21
#define kCFCoreFoundationVersionNumber10_7_5    635.21
#define kCFCoreFoundationVersionNumber10_8      744.00
#define kCFCoreFoundationVersionNumber10_8_1    744.00
#define kCFCoreFoundationVersionNumber10_8_2    744.12
#define kCFCoreFoundationVersionNumber10_8_3    744.18
#define kCFCoreFoundationVersionNumber10_8_4    744.19
#define kCFCoreFoundationVersionNumber10_9      855.11
#define kCFCoreFoundationVersionNumber10_9_1    855.11
#define kCFCoreFoundationVersionNumber10_9_2    855.14
#define kCFCoreFoundationVersionNumber10_10     1151.16
#define kCFCoreFoundationVersionNumber10_10_1   1151.16
#define kCFCoreFoundationVersionNumber10_10_2   1152
#define kCFCoreFoundationVersionNumber10_10_3   1153.18
#endif

#if TARGET_OS_IPHONE
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_0 478.23
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_1 478.26
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_2 478.29
#define kCFCoreFoundationVersionNumber_iPhoneOS_3_0 478.47
#define kCFCoreFoundationVersionNumber_iPhoneOS_3_1 478.52
#define kCFCoreFoundationVersionNumber_iPhoneOS_3_2 478.61
#define kCFCoreFoundationVersionNumber_iOS_4_0 550.32
#define kCFCoreFoundationVersionNumber_iOS_4_1 550.38
#define kCFCoreFoundationVersionNumber_iOS_4_2 550.52
#define kCFCoreFoundationVersionNumber_iOS_4_3 550.52
#define kCFCoreFoundationVersionNumber_iOS_5_0 675.00
#define kCFCoreFoundationVersionNumber_iOS_5_1 690.10
#define kCFCoreFoundationVersionNumber_iOS_6_0 793.00
#define kCFCoreFoundationVersionNumber_iOS_6_1 793.00
#define kCFCoreFoundationVersionNumber_iOS_7_0 847.20
#define kCFCoreFoundationVersionNumber_iOS_7_1 847.24
#define kCFCoreFoundationVersionNumber_iOS_8_0 1140.1
#define kCFCoreFoundationVersionNumber_iOS_8_1 1141.14
#define kCFCoreFoundationVersionNumber_iOS_8_2 1142.16
#endif

#if __LLP64__
typedef unsigned long long CFTypeID;
typedef unsigned long long CFOptionFlags;
typedef unsigned long long CFHashCode;
typedef signed long long CFIndex;
#else
typedef unsigned long CFTypeID;
typedef unsigned long CFOptionFlags;
typedef unsigned long CFHashCode;
typedef signed long CFIndex;
#endif

/* Base "type" of all "CF objects", and polymorphic functions on them */
typedef const CF_BRIDGED_TYPE(id) void * CFTypeRef;

typedef const struct CF_BRIDGED_TYPE(NSString) __CFString * CFStringRef;
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableString) __CFString * CFMutableStringRef;

/*
        Type to mean any instance of a property list type;
        currently, CFString, CFData, CFNumber, CFBoolean, CFDate,
        CFArray, and CFDictionary.
*/
typedef CF_BRIDGED_TYPE(id) CFTypeRef CFPropertyListRef;

/* Values returned from comparison functions */
typedef CF_ENUM(CFIndex, CFComparisonResult) {
    kCFCompareLessThan = -1L,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1
};

/* A standard comparison function */
typedef CFComparisonResult (*CFComparatorFunction)(const void *val1, const void *val2, void *context);

/* Constant used by some functions to indicate failed searches. */
static const CFIndex kCFNotFound = -1;


/* Range type */
typedef struct {
    CFIndex location;
    CFIndex length;
} CFRange;

#if defined(CF_INLINE)
CF_INLINE CFRange CFRangeMake(CFIndex loc, CFIndex len) {
    CFRange range;
    range.location = loc;
    range.length = len;
    return range;
}
#else
#define CFRangeMake(LOC, LEN) __CFRangeMake(LOC, LEN)
#endif

/* Private; do not use */
CF_EXPORT
CFRange __CFRangeMake(CFIndex loc, CFIndex len);


/* Null representant */

typedef const struct CF_BRIDGED_TYPE(NSNull) __CFNull * CFNullRef;

CF_EXPORT
CFTypeID CFNullGetTypeID(void);

CF_EXPORT
const CFNullRef kCFNull;	// the singleton null instance


/* Allocator API

   Most of the time when specifying an allocator to Create functions, the NULL
   argument indicates "use the default"; this is the same as using kCFAllocatorDefault
   or the return value from CFAllocatorGetDefault().  This assures that you will use
   the allocator in effect at that time.
*/
typedef const struct CF_BRIDGED_TYPE(id) __CFAllocator * CFAllocatorRef;

/* This is a synonym for NULL, if you'd rather use a named constant. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorDefault;

/* Default system allocator; you rarely need to use this. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorSystemDefault;

/* This allocator uses malloc(), realloc(), and free(). This should not be
   generally used; stick to kCFAllocatorDefault whenever possible. This
   allocator is useful as the "bytesDeallocator" in CFData or
   "contentsDeallocator" in CFString where the memory was obtained as a
   result of malloc() type functions.
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorMalloc;

/* This allocator explicitly uses the default malloc zone, returned by
   malloc_default_zone(). It should only be used when an object is
   safe to be allocated in non-scanned memory.
 */
CF_EXPORT
const CFAllocatorRef kCFAllocatorMallocZone;

/* Null allocator which does nothing and allocates no memory. This allocator
   is useful as the "bytesDeallocator" in CFData or "contentsDeallocator"
   in CFString where the memory should not be freed. 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorNull;

/* Special allocator argument to CFAllocatorCreate() which means
   "use the functions given in the context to allocate the allocator
   itself as well". 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorUseContext;

typedef const void *	(*CFAllocatorRetainCallBack)(const void *info);
typedef void		(*CFAllocatorReleaseCallBack)(const void *info);
typedef CFStringRef	(*CFAllocatorCopyDescriptionCallBack)(const void *info);
typedef void *		(*CFAllocatorAllocateCallBack)(CFIndex allocSize, CFOptionFlags hint, void *info);
typedef void *		(*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize, CFOptionFlags hint, void *info);
typedef void		(*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef CFIndex		(*CFAllocatorPreferredSizeCallBack)(CFIndex size, CFOptionFlags hint, void *info);
typedef struct {
    CFIndex				version;
    void *				info;
    CFAllocatorRetainCallBack		retain;
    CFAllocatorReleaseCallBack		release;        
    CFAllocatorCopyDescriptionCallBack	copyDescription;
    CFAllocatorAllocateCallBack		allocate;
    CFAllocatorReallocateCallBack	reallocate;
    CFAllocatorDeallocateCallBack	deallocate;
    CFAllocatorPreferredSizeCallBack	preferredSize;
} CFAllocatorContext;

CF_EXPORT
CFTypeID	CFAllocatorGetTypeID(void);

/*
	CFAllocatorSetDefault() sets the allocator that is used in the current
	thread whenever NULL is specified as an allocator argument. This means
	that most, if not all allocations will go through this allocator. It
	also means that any allocator set as the default needs to be ready to
	deal with arbitrary memory allocation requests; in addition, the size
	and number of requests will change between releases.

	An allocator set as the default will never be released, even if later
	another allocator replaces it as the default. Not only is it impractical
	for it to be released (as there might be caches created under the covers
	that refer to the allocator), in general it's also safer and more
	efficient to keep it around.

	If you wish to use a custom allocator in a context, it's best to provide
	it as the argument to the various creation functions rather than setting
	it as the default. Setting the default allocator is not encouraged.

	If you do set an allocator as the default, either do it for all time in
	your app, or do it in a nested fashion (by restoring the previous allocator
	when you exit your context). The latter might be appropriate for plug-ins
	or libraries that wish to set the default allocator.
*/
CF_EXPORT
void CFAllocatorSetDefault(CFAllocatorRef allocator);

CF_EXPORT
CFAllocatorRef CFAllocatorGetDefault(void);

CF_EXPORT
CFAllocatorRef CFAllocatorCreate(CFAllocatorRef allocator, CFAllocatorContext *context);

CF_EXPORT
void *CFAllocatorAllocate(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void *CFAllocatorReallocate(CFAllocatorRef allocator, void *ptr, CFIndex newsize, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorDeallocate(CFAllocatorRef allocator, void *ptr);

CF_EXPORT
CFIndex CFAllocatorGetPreferredSizeForSize(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorGetContext(CFAllocatorRef allocator, CFAllocatorContext *context);


/* Polymorphic CF functions */

CF_IMPLICIT_BRIDGING_ENABLED

CF_EXPORT
CFTypeID CFGetTypeID(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyTypeIDDescription(CFTypeID type_id);

CF_EXPORT
CFTypeRef CFRetain(CFTypeRef cf);

CF_EXPORT
void CFRelease(CFTypeRef cf);

CF_EXPORT
CFTypeRef CFAutorelease(CFTypeRef CF_RELEASES_ARGUMENT arg) CF_AVAILABLE(10_9, 7_0);

CF_EXPORT
CFIndex CFGetRetainCount(CFTypeRef cf);

CF_EXPORT
Boolean CFEqual(CFTypeRef cf1, CFTypeRef cf2);

CF_EXPORT
CFHashCode CFHash(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyDescription(CFTypeRef cf);

CF_EXPORT
CFAllocatorRef CFGetAllocator(CFTypeRef cf);

CF_IMPLICIT_BRIDGING_DISABLED

// This function is unavailable in ARC mode.
CF_EXPORT
CFTypeRef CFMakeCollectable(CFTypeRef cf) CF_AUTOMATED_REFCOUNT_UNAVAILABLE;

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFBASE__ */

// ==========  CoreFoundation.framework/Headers/CFSet.h
/*	CFSet.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/
/*!
        @header CFSet
        CFSet implements a container which stores unique values.
*/

#if !defined(__COREFOUNDATION_CFSET__)
#define __COREFOUNDATION_CFSET__ 1

#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

/*!
	@typedef CFSetRetainCallBack
	Type of the callback function used by CFSets for retaining values.
        @param allocator The allocator of the CFSet.
	@param value The value to retain.
        @result The value to store in the set, which is usually the value
		parameter passed to this callback, but may be a different
		value if a different value should be stored in the set.
*/
typedef const void *	(*CFSetRetainCallBack)(CFAllocatorRef allocator, const void *value);

/*!
	@typedef CFSetReleaseCallBack
	Type of the callback function used by CFSets for releasing a retain on values.
        @param allocator The allocator of the CFSet.
	@param value The value to release.
*/
typedef void		(*CFSetReleaseCallBack)(CFAllocatorRef allocator, const void *value);

/*!
	@typedef CFSetCopyDescriptionCallBack
	Type of the callback function used by CFSets for describing values.
	@param value The value to describe.
        @result A description of the specified value.
*/
typedef CFStringRef	(*CFSetCopyDescriptionCallBack)(const void *value);

/*!
	@typedef CFSetEqualCallBack
	Type of the callback function used by CFSets for comparing values.
	@param value1 The first value to compare.
	@param value2 The second value to compare.
        @result True if the values are equal, otherwise false.
*/
typedef Boolean		(*CFSetEqualCallBack)(const void *value1, const void *value2);

/*!
	@typedef CFSetHashCallBack
	Type of the callback function used by CFSets for hashing values.
	@param value The value to hash.
        @result The hash of the value.
*/
typedef CFHashCode	(*CFSetHashCallBack)(const void *value);

/*!
	@typedef CFSetCallBacks
	Structure containing the callbacks of a CFSet.
	@field version The version number of the structure type being passed
		in as a parameter to the CFSet creation functions. This
		structure is version 0.
	@field retain The callback used to add a retain for the set on
		values as they are put into the set. This callback returns
		the value to store in the set, which is usually the value
		parameter passed to this callback, but may be a different
		value if a different value should be stored in the set.
		The set's allocator is passed as the first argument.
	@field release The callback used to remove a retain previously added
		for the set from values as they are removed from the
		set. The set's allocator is passed as the first
		argument.
	@field copyDescription The callback used to create a descriptive
		string representation of each value in the set. This is
		used by the CFCopyDescription() function.
	@field equal The callback used to compare values in the set for
		equality for some operations.
	@field hash The callback used to compare values in the set for
		uniqueness for some operations.
*/
typedef struct {
    CFIndex				version;
    CFSetRetainCallBack			retain;
    CFSetReleaseCallBack		release;
    CFSetCopyDescriptionCallBack	copyDescription;
    CFSetEqualCallBack			equal;
    CFSetHashCallBack			hash;
} CFSetCallBacks;

/*!
	@constant kCFTypeSetCallBacks
	Predefined CFSetCallBacks structure containing a set of callbacks
	appropriate for use when the values in a CFSet are all CFTypes.
*/
CF_EXPORT
const CFSetCallBacks kCFTypeSetCallBacks;

/*!
	@constant kCFCopyStringSetCallBacks
	Predefined CFSetCallBacks structure containing a set of callbacks
	appropriate for use when the values in a CFSet should be copies
        of a CFString.
*/
CF_EXPORT
const CFSetCallBacks kCFCopyStringSetCallBacks;

/*!
	@typedef CFSetApplierFunction
	Type of the callback function used by the apply functions of
		CFSets.
	@param value The current value from the set.
	@param context The user-defined context parameter given to the apply
		function.
*/
typedef void (*CFSetApplierFunction)(const void *value, void *context);

/*!
        @typedef CFSetRef
	This is the type of a reference to immutable CFSets.
*/
typedef const struct CF_BRIDGED_TYPE(NSSet) __CFSet * CFSetRef;

/*!
        @typedef CFMutableSetRef
	This is the type of a reference to mutable CFSets.
*/
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableSet) __CFSet * CFMutableSetRef;

/*!
        @function CFSetGetTypeID
        Returns the type identifier of all CFSet instances.
*/
CF_EXPORT
CFTypeID CFSetGetTypeID(void);

/*!
        @function CFSetCreate
        Creates a new immutable set with the given values.
	@param allocator The CFAllocator which should be used to allocate
		memory for the set and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param values A C array of the pointer-sized values to be in the
		set.  This C array is not changed or freed by this function. 
                If this parameter is not a valid pointer to a C array of at
                least numValues pointers, the behavior is undefined.
	@param numValues The number of values to copy from the values C
		array into the CFSet. This number will be the count of the
		set.  If this parameter is zero, negative, or greater than 
                the number of values actually in the values C array, the 
                behavior is undefined.
	@param callBacks A C pointer to a CFSetCallBacks structure
		initialized with the callbacks for the set to use on each
		value in the set. A copy of the contents of the
		callbacks structure is made, so that a pointer to a
		structure on the stack can be passed in, or can be reused
		for multiple set creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFSet, the behavior is undefined. The retain field may be
		NULL, in which case the CFSet will do nothing to add a
		retain to the contained values for the set. The release
		field may be NULL, in which case the CFSet will do nothing
		to remove the set's retain (if any) on the values when the
		set is destroyed. If the copyDescription field is NULL,
		the set will create a simple description for the value. If
		the equal field is NULL, the set will use pointer equality
		to test for equality of values. The hash field may be NULL,
                in which case the CFSet will determine uniqueness by pointer
                equality. This callbacks parameter
		itself may be NULL, which is treated as if a valid structure
		of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a  CFSetCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		set is not one understood by one of the callback functions
		the behavior when that callback function is used is
		undefined.
	@result A reference to the new immutable CFSet.
*/
CF_EXPORT
CFSetRef CFSetCreate(CFAllocatorRef allocator, const void **values, CFIndex numValues, const CFSetCallBacks *callBacks);

/*!
	@function CFSetCreateCopy
	Creates a new immutable set with the values from the given set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the set and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
	@param theSet The set which is to be copied. The values from the
		set are copied as pointers into the new set (that is,
		the values themselves are copied, not that which the values
		point to, if anything). However, the values are also
		retained by the new set. The count of the new set will
		be the same as the copied set. The new set uses the same
		callbacks as the set to be copied. If this parameter is
		not a valid CFSet, the behavior is undefined.
	@result A reference to the new immutable CFSet.
*/
CF_EXPORT
CFSetRef CFSetCreateCopy(CFAllocatorRef allocator, CFSetRef theSet);

/*!
	@function CFSetCreateMutable
	Creates a new empty mutable set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the set and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFSet. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A set's actual capacity is only limited by 
                address space and available memory constraints). If this 
                parameter is negative, the behavior is undefined.
	@param callBacks A C pointer to a CFSetCallBacks structure
		initialized with the callbacks for the set to use on each
		value in the set. A copy of the contents of the
		callbacks structure is made, so that a pointer to a
		structure on the stack can be passed in, or can be reused
		for multiple set creations. If the version field of this
		callbacks structure is not one of the defined ones for
		CFSet, the behavior is undefined. The retain field may be
		NULL, in which case the CFSet will do nothing to add a
		retain to the contained values for the set. The release
		field may be NULL, in which case the CFSet will do nothing
		to remove the set's retain (if any) on the values when the
		set is destroyed. If the copyDescription field is NULL,
		the set will create a simple description for the value. If
		the equal field is NULL, the set will use pointer equality
		to test for equality of values. The hash field may be NULL,
                in which case the CFSet will determine uniqueness by pointer
                equality. This callbacks parameter
		itself may be NULL, which is treated as if a valid structure
		of version 0 with all fields NULL had been passed in.
		Otherwise, if any of the fields are not valid pointers to
		functions of the correct type, or this parameter is not a
		valid pointer to a  CFSetCallBacks callbacks structure,
		the behavior is undefined. If any of the values put into the
		set is not one understood by one of the callback functions
		the behavior when that callback function is used is
		undefined.
	@result A reference to the new mutable CFSet.
*/
CF_EXPORT
CFMutableSetRef CFSetCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFSetCallBacks *callBacks);

/*!
	@function CFSetCreateMutableCopy
	Creates a new immutable set with the values from the given set.
	@param allocator The CFAllocator which should be used to allocate
		memory for the set and its storage for values. This
		parameter may be NULL in which case the current default
		CFAllocator is used. If this reference is not a valid
		CFAllocator, the behavior is undefined.
        @param capacity A hint about the number of values that will be held
                by the CFSet. Pass 0 for no hint. The implementation may
                ignore this hint, or may use it to optimize various
                operations. A set's actual capacity is only limited by
                address space and available memory constraints). 
                This parameter must be greater than or equal
                to the count of the set which is to be copied, or the
                behavior is undefined. If this parameter is negative, the
                behavior is undefined.
	@param theSet The set which is to be copied. The values from the
		set are copied as pointers into the new set (that is,
		the values themselves are copied, not that which the values
		point to, if anything). However, the values are also
		retained by the new set. The count of the new set will
		be the same as the copied set. The new set uses the same
		callbacks as the set to be copied. If this parameter is
		not a valid CFSet, the behavior is undefined.
	@result A reference to the new mutable CFSet.
*/
CF_EXPORT
CFMutableSetRef CFSetCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFSetRef theSet);

/*!
	@function CFSetGetCount
	Returns the number of values currently in the set.
	@param theSet The set to be queried. If this parameter is not a valid
		CFSet, the behavior is undefined.
	@result The number of values in the set.
*/
CF_EXPORT
CFIndex CFSetGetCount(CFSetRef theSet);

/*!
	@function CFSetGetCountOfValue
	Counts the number of times the given value occurs in the set. Since 
        sets by definition contain only one instance of a value, this function
        is synonymous to CFSetContainsValue.
	@param theSet The set to be searched. If this parameter is not a
		valid CFSet, the behavior is undefined.
	@param value The value for which to find matches in the set. The
		equal() callback provided when the set was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the set, are not understood by the equal() callback,
		the behavior is undefined.
	@result The number of times the given value occurs in the set.
*/
CF_EXPORT
CFIndex CFSetGetCountOfValue(CFSetRef theSet, const void *value);

/*!
	@function CFSetContainsValue
	Reports whether or not the value is in the set.
	@param theSet The set to be searched. If this parameter is not a
		valid CFSet, the behavior is undefined.
	@param value The value for which to find matches in the set. The
		equal() callback provided when the set was created is
		used to compare. If the equal() callback was NULL, pointer
		equality (in C, ==) is used. If value, or any of the values
		in the set, are not understood by the equal() callback,
		the behavior is undefined.
	@result true, if the value is in the set, otherwise false.
*/
CF_EXPORT
Boolean CFSetContainsValue(CFSetRef theSet, const void *value);

/*!
	@function CFSetGetValue
	Retrieves a value in the set which hashes the same as the specified value.
	@param theSet The set to be queried. If this parameter is not a
		valid CFSet, the behavior is undefined.
	@param value The value to retrieve. The equal() callback provided when
                the set was created is used to compare. If the equal() callback
                was NULL, pointer equality (in C, ==) is used. If a value, or
                any of the values in the set, are not understood by the equal()
                callback, the behavior is undefined.
        @result The value in the set with the given hash.
*/
CF_EXPORT
const void *CFSetGetValue(CFSetRef theSet, const void *value);

/*!
	@function CFSetGetValueIfPresent
	Retrieves a value in the set which hashes the same as the specified value,
        if present.
	@param theSet The set to be queried. If this parameter is not a
		valid CFSet, the behavior is undefined.
	@param candidate This value is hashed and compared with values in the
                set to determine which value to retrieve. The equal() callback provided when
                the set was created is used to compare. If the equal() callback
                was NULL, pointer equality (in C, ==) is used. If a value, or
                any of the values in the set, are not understood by the equal()
                callback, the behavior is undefined.
	@param value A pointer to memory which should be filled with the
		pointer-sized value if a matching value is found. If no
		match is found, the contents of the storage pointed to by
		this parameter are undefined. This parameter may be NULL,
		in which case the value from the dictionary is not returned
		(but the return value of this function still indicates
		whether or not the value was present).
        @result True if the value was present in the set, otherwise false.
*/
CF_EXPORT
Boolean CFSetGetValueIfPresent(CFSetRef theSet, const void *candidate, const void **value);

/*!
	@function CFSetGetValues
	Fills the buffer with values from the set.
	@param theSet The set to be queried. If this parameter is not a
		valid CFSet, the behavior is undefined.
	@param values A C array of pointer-sized values to be filled with
		values from the set. The values in the C array are ordered
		in the same order in which they appear in the set. If this
		parameter is not a valid pointer to a C array of at least
		CFSetGetCount() pointers, the behavior is undefined.
*/
CF_EXPORT
void CFSetGetValues(CFSetRef theSet, const void **values);

/*!
	@function CFSetApplyFunction
	Calls a function once for each value in the set.
	@param theSet The set to be operated upon. If this parameter is not
		a valid CFSet, the behavior is undefined.
	@param applier The callback function to call once for each value in
		the given set. If this parameter is not a
		pointer to a function of the correct prototype, the behavior
		is undefined. If there are values in the set which the
		applier function does not expect or cannot properly apply
		to, the behavior is undefined. 
	@param context A pointer-sized user-defined value, which is passed
		as the second parameter to the applier function, but is
		otherwise unused by this function. If the context is not
		what is expected by the applier function, the behavior is
		undefined.
*/
CF_EXPORT
void CFSetApplyFunction(CFSetRef theSet, CFSetApplierFunction applier, void *context);

/*!
	@function CFSetAddValue
	Adds the value to the set if it is not already present.
	@param theSet The set to which the value is to be added. If this
		parameter is not a valid mutable CFSet, the behavior is
		undefined.
	@param value The value to add to the set. The value is retained by
		the set using the retain callback provided when the set
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The count of the 
                set is increased by one.
*/
CF_EXPORT
void CFSetAddValue(CFMutableSetRef theSet, const void *value);

/*!
	@function CFSetReplaceValue
	Replaces the value in the set if it is present.
	@param theSet The set to which the value is to be replaced. If this
		parameter is not a valid mutable CFSet, the behavior is
		undefined.
        @param value The value to replace in the set. The equal() callback provided when
                the set was created is used to compare. If the equal() callback
                was NULL, pointer equality (in C, ==) is used. If a value, or
                any of the values in the set, are not understood by the equal()
                callback, the behavior is undefined. The value is retained by
		the set using the retain callback provided when the set
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The count of the 
                set is increased by one.
*/
CF_EXPORT
void CFSetReplaceValue(CFMutableSetRef theSet, const void *value);

/*!
	@function CFSetSetValue
	Replaces the value in the set if it is present, or adds the value to 
        the set if it is absent.
	@param theSet The set to which the value is to be replaced. If this
		parameter is not a valid mutable CFSet, the behavior is
		undefined.
        @param value The value to set in the CFSet. The equal() callback provided when
                the set was created is used to compare. If the equal() callback
                was NULL, pointer equality (in C, ==) is used. If a value, or
                any of the values in the set, are not understood by the equal()
                callback, the behavior is undefined. The value is retained by
		the set using the retain callback provided when the set
		was created. If the value is not of the sort expected by the
		retain callback, the behavior is undefined. The count of the 
                set is increased by one.
*/
CF_EXPORT
void CFSetSetValue(CFMutableSetRef theSet, const void *value);

/*!
	@function CFSetRemoveValue
	Removes the specified value from the set.
	@param theSet The set from which the value is to be removed.
                If this parameter is not a valid mutable CFSet,
		the behavior is undefined.
        @param value The value to remove. The equal() callback provided when
                the set was created is used to compare. If the equal() callback
                was NULL, pointer equality (in C, ==) is used. If a value, or
                any of the values in the set, are not understood by the equal()
                callback, the behavior is undefined.
*/
CF_EXPORT
void CFSetRemoveValue(CFMutableSetRef theSet, const void *value);

/*!
	@function CFSetRemoveAllValues
	Removes all the values from the set, making it empty.
	@param theSet The set from which all of the values are to be
		removed. If this parameter is not a valid mutable CFSet,
		the behavior is undefined.
*/
CF_EXPORT
void CFSetRemoveAllValues(CFMutableSetRef theSet);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFSET__ */

// ==========  CoreFoundation.framework/Headers/CFUtilities.h
/*	CFUtilities.h
	Copyright (c) 2005-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFUTILITIES__)
#define __COREFOUNDATION_CFUTILITIES__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

CF_EXPORT
CFURLRef CFCopyHomeDirectoryURL(void) CF_AVAILABLE_IOS(5_0);

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFUTILITIES__ */

// ==========  CoreFoundation.framework/Headers/CFCalendar.h
/*	CFCalendar.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFCALENDAR__)
#define __COREFOUNDATION_CFCALENDAR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFTimeZone.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef struct CF_BRIDGED_MUTABLE_TYPE(NSCalendar) __CFCalendar * CFCalendarRef;

CF_EXPORT
CFTypeID CFCalendarGetTypeID(void);

CF_EXPORT
CFCalendarRef CFCalendarCopyCurrent(void);

CF_EXPORT
CFCalendarRef CFCalendarCreateWithIdentifier(CFAllocatorRef allocator, CFStringRef identifier);
	// Create a calendar.  The identifiers are the kCF*Calendar
	// constants in CFLocale.h.

CF_EXPORT
CFStringRef CFCalendarGetIdentifier(CFCalendarRef calendar);
	// Returns the calendar's identifier.

CF_EXPORT
CFLocaleRef CFCalendarCopyLocale(CFCalendarRef calendar);

CF_EXPORT
void CFCalendarSetLocale(CFCalendarRef calendar, CFLocaleRef locale);

CF_EXPORT
CFTimeZoneRef CFCalendarCopyTimeZone(CFCalendarRef calendar);

CF_EXPORT
void CFCalendarSetTimeZone(CFCalendarRef calendar, CFTimeZoneRef tz);

CF_EXPORT
CFIndex CFCalendarGetFirstWeekday(CFCalendarRef calendar);

CF_EXPORT
void CFCalendarSetFirstWeekday(CFCalendarRef calendar, CFIndex wkdy);

CF_EXPORT
CFIndex CFCalendarGetMinimumDaysInFirstWeek(CFCalendarRef calendar);

CF_EXPORT
void CFCalendarSetMinimumDaysInFirstWeek(CFCalendarRef calendar, CFIndex mwd);


typedef CF_OPTIONS(CFOptionFlags, CFCalendarUnit) {
	kCFCalendarUnitEra = (1UL << 1),
	kCFCalendarUnitYear = (1UL << 2),
	kCFCalendarUnitMonth = (1UL << 3),
	kCFCalendarUnitDay = (1UL << 4),
	kCFCalendarUnitHour = (1UL << 5),
	kCFCalendarUnitMinute = (1UL << 6),
	kCFCalendarUnitSecond = (1UL << 7),
	kCFCalendarUnitWeek CF_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0) = (1UL << 8),
	kCFCalendarUnitWeekday = (1UL << 9),
	kCFCalendarUnitWeekdayOrdinal = (1UL << 10),
	kCFCalendarUnitQuarter CF_ENUM_AVAILABLE(10_6, 4_0) = (1UL << 11),
	kCFCalendarUnitWeekOfMonth CF_ENUM_AVAILABLE(10_7, 5_0) = (1UL << 12),
	kCFCalendarUnitWeekOfYear CF_ENUM_AVAILABLE(10_7, 5_0) = (1UL << 13),
	kCFCalendarUnitYearForWeekOfYear CF_ENUM_AVAILABLE(10_7, 5_0) = (1UL << 14),
};

CF_EXPORT
CFRange CFCalendarGetMinimumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit);

CF_EXPORT
CFRange CFCalendarGetMaximumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit);

CF_EXPORT
CFRange CFCalendarGetRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at);

CF_EXPORT
CFIndex CFCalendarGetOrdinalityOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at);

CF_EXPORT
Boolean CFCalendarGetTimeRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit, CFAbsoluteTime at, CFAbsoluteTime *startp, CFTimeInterval *tip) CF_AVAILABLE(10_5, 2_0);

CF_EXPORT
Boolean CFCalendarComposeAbsoluteTime(CFCalendarRef calendar, /* out */ CFAbsoluteTime *at, const char *componentDesc, ...);

CF_EXPORT
Boolean CFCalendarDecomposeAbsoluteTime(CFCalendarRef calendar, CFAbsoluteTime at, const char *componentDesc, ...);


CF_ENUM(CFOptionFlags) {
    kCFCalendarComponentsWrap = (1UL << 0)  // option for adding
};

CF_EXPORT
Boolean CFCalendarAddComponents(CFCalendarRef calendar, /* inout */ CFAbsoluteTime *at, CFOptionFlags options, const char *componentDesc, ...);

CF_EXPORT
Boolean CFCalendarGetComponentDifference(CFCalendarRef calendar, CFAbsoluteTime startingAT, CFAbsoluteTime resultAT, CFOptionFlags options, const char *componentDesc, ...);


CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFCALENDAR__ */

// ==========  CoreFoundation.framework/Headers/CFStringEncodingExt.h
/*	CFStringEncodingExt.h
	Copyright (c) 1998-2015, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFSTRINGENCODINGEXT__)
#define __COREFOUNDATION_CFSTRINGENCODINGEXT__ 1

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

typedef CF_ENUM(CFIndex, CFStringEncodings) {
/*  kCFStringEncodingMacRoman = 0L, defined in CoreFoundation/CFString.h */
    kCFStringEncodingMacJapanese = 1,
    kCFStringEncodingMacChineseTrad = 2,
    kCFStringEncodingMacKorean = 3,
    kCFStringEncodingMacArabic = 4,
    kCFStringEncodingMacHebrew = 5,
    kCFStringEncodingMacGreek = 6,
    kCFStringEncodingMacCyrillic = 7,
    kCFStringEncodingMacDevanagari = 9,
    kCFStringEncodingMacGurmukhi = 10,
    kCFStringEncodingMacGujarati = 11,
    kCFStringEncodingMacOriya = 12,
    kCFStringEncodingMacBengali = 13,
    kCFStringEncodingMacTamil = 14,
    kCFStringEncodingMacTelugu = 15,
    kCFStringEncodingMacKannada = 16,
    kCFStringEncodingMacMalayalam = 17,
    kCFStringEncodingMacSinhalese = 18,
    kCFStringEncodingMacBurmese = 19,
    kCFStringEncodingMacKhmer = 20,
    kCFStringEncodingMacThai = 21,
    kCFStringEncodingMacLaotian = 22,
    kCFStringEncodingMacGeorgian = 23,
    kCFStringEncodingMacArmenian = 24,
    kCFStringEncodingMacChineseSimp = 25,
    kCFStringEncodingMacTibetan = 26,
    kCFStringEncodingMacMongolian = 27,
    kCFStringEncodingMacEthiopic = 28,
    kCFStringEncodingMacCentralEurRoman = 29,
    kCFStringEncodingMacVietnamese = 30,
    kCFStringEncodingMacExtArabic = 31,
    /* The following use script code 0, smRoman */
    kCFStringEncodingMacSymbol = 33,
    kCFStringEncodingMacDingbats = 34,
    kCFStringEncodingMacTurkish = 35,
    kCFStringEncodingMacCroatian = 36,
    kCFStringEncodingMacIcelandic = 37,
    kCFStringEncodingMacRomanian = 38,
    kCFStringEncodingMacCeltic = 39,
    kCFStringEncodingMacGaelic = 40,
    /* The following use script code 4, smArabic */
    kCFStringEncodingMacFarsi = 0x8C,	/* Like MacArabic but uses Farsi digits */
    /* The following use script code 7, smCyrillic */
    kCFStringEncodingMacUkrainian = 0x98,
    /* The following use script code 32, smUnimplemented */
    kCFStringEncodingMacInuit = 0xEC,
    kCFStringEncodingMacVT100 = 0xFC,	/* VT100/102 font from Comm Toolbox: Latin-1 repertoire + box drawing etc */
    /* Special Mac OS encodings*/
    kCFStringEncodingMacHFS = 0xFF,	/* Meta-value, should never appear in a table */

    /* Unicode & ISO UCS encodings begin at 0x100 */
    /* We don't use Unicode variations defined in TextEncoding; use the ones in CFString.h, instead. */

    /* ISO 8-bit and 7-bit encodings begin at 0x200 */
/*  kCFStringEncodingISOLatin1 = 0x0201, defined in CoreFoundation/CFString.h */
    kCFStringEncodingISOLatin2 = 0x0202,	/* ISO 8859-2 */
    kCFStringEncodingISOLatin3 = 0x0203,	/* ISO 8859-3 */
    kCFStringEncodingISOLatin4 = 0x0204,	/* ISO 8859-4 */
    kCFStringEncodingISOLatinCyrillic = 0x0205,	/* ISO 8859-5 */
    kCFStringEncodingISOLatinArabic = 0x0206,	/* ISO 8859-6, =ASMO 708, =DOS CP 708 */
    kCFStringEncodingISOLatinGreek = 0x0207,	/* ISO 8859-7 */
    kCFStringEncodingISOLatinHebrew = 0x0208,	/* ISO 8859-8 */
    kCFStringEncodingISOLatin5 = 0x0209,	/* ISO 8859-9 */
    kCFStringEncodingISOLatin6 = 0x020A,	/* ISO 8859-10 */
    kCFStringEncodingISOLatinThai = 0x020B,	/* ISO 8859-11 */
    kCFStringEncodingISOLatin7 = 0x020D,	/* ISO 8859-13 */
    kCFStringEncodingISOLatin8 = 0x020E,	/* ISO 8859-14 */
    kCFStringEncodingISOLatin9 = 0x020F,	/* ISO 8859-15 */
    kCFStringEncodingISOLatin10 = 0x0210,	/* ISO 8859-16 */

    /* MS-DOS & Windows encodings begin at 0x400 */
    kCFStringEncodingDOSLatinUS = 0x0400,	/* code page 437 */
    kCFStringEncodingDOSGreek = 0x0405,		/* code page 737 (formerly code page 437G) */
    kCFStringEncodingDOSBalticRim = 0x0406,	/* code page 775 */
    kCFStringEncodingDOSLatin1 = 0x0410,	/* code page 850, "Multilingual" */
    kCFStringEncodingDOSGreek1 = 0x0411,	/* code page 851 */
    kCFStringEncodingDOSLatin2 = 0x0412,	/* code page 852, Slavic */
    kCFStringEncodingDOSCyrillic = 0x0413,	/* code page 855, IBM Cyrillic */
    kCFStringEncodingDOSTurkish = 0x0414,	/* code page 857, IBM Turkish */
    kCFStringEncodingDOSPortuguese = 0x0415,	/* code page 860 */
    kCFStringEncodingDOSIcelandic = 0x0416,	/* code page 861 */
    kCFStringEncodingDOSHebrew = 0x0417,	/* code page 862 */
    kCFStringEncodingDOSCanadianFrench = 0x0418, /* code page 863 */
    kCFStringEncodingDOSArabic = 0x0419,	/* code page 864 */
    kCFStringEncodingDOSNordic = 0x041A,	/* code page 865 */
    kCFStringEncodingDOSRussian = 0x041B,	/* code page 866 */
    kCFStringEncodingDOSGreek2 = 0x041C,	/* code page 869, IBM Modern Greek */
    kCFStringEncodingDOSThai = 0x041D,		/* code page 874, also for Windows */
    kCFStringEncodingDOSJapanese = 0x0420,	/* code page 932, also for Windows */
    kCFStringEncodingDOSChineseSimplif = 0x0421, /* code page 936, also for Windows */
    kCFStringEncodingDOSKorean = 0x0422,	/* code page 949, also for Windows; Unified Hangul Code */
    kCFStringEncodingDOSChineseTrad = 0x0423,	/* code page 950, also for Windows */
/*  kCFStringEncodingWindowsLatin1 = 0x0500, defined in CoreFoundation/CFString.h */
    kCFStringEncodingWindowsLatin2 = 0x0501,	/* code page 1250, Central Europe */
    kCFStringEncodingWindowsCyrillic = 0x0502,	/* code page 1251, Slavic Cyrillic */
    kCFStringEncodingWindowsGreek = 0x0503,	/* code page 1253 */
    kCFStringEncodingWindowsLatin5 = 0x0504,	/* code page 1254, Turkish */
    kCFStringEncodingWindowsHebrew = 0x0505,	/* code page 1255 */
    kCFStringEncodingWindowsArabic = 0x0506,	/* code page 1256 */
    kCFStringEncodingWindowsBalticRim = 0x0507,	/* code page 1257 */
    kCFStringEncodingWindowsVietnamese = 0x0508, /* code page 1258 */
    kCFStringEncodingWindowsKoreanJohab = 0x0510, /* code page 1361, for Windows NT */

    /* Various national standards begin at 0x600 */
/*  kCFStringEncodingASCII = 0x0600, defined in CoreFoundation/CFString.h */
    kCFStringEncodingANSEL = 0x0601,	/* ANSEL (ANSI Z39.47) */
    kCFStringEncodingJIS_X0201_76 = 0x0620,
    kCFStringEncodingJIS_X0208_83 = 0x0621,
    kCFStringEncodingJIS_X0208_90 = 0x0622,
    kCFStringEncodingJIS_X0212_90 = 0x0623,
    kCFStringEncodingJIS_C6226_78 = 0x0624,
    kCFStringEncodingShiftJIS_X0213 CF_ENUM_AVAILABLE(10_5, 2_0) = 0x0628, /* Shift-JIS format encoding of JIS X0213 planes 1 and 2*/
    kCFStringEncodingShiftJIS_X0213_MenKuTen = 0x0629,	/* JIS X0213 in plane-row-column notation */
    kCFStringEncodingGB_2312_80 = 0x0630,
    kCFStringEncodingGBK_95 = 0x0631,		/* annex to GB 13000-93; for Windows 95 */
    kCFStringEncodingGB_18030_2000 = 0x0632,
    kCFStringEncodingKSC_5601_87 = 0x0640,	/* same as KSC 5601-92 without Johab annex */
    kCFStringEncodingKSC_5601_92_Johab = 0x0641, /* KSC 5601-92 Johab annex */
    kCFStringEncodingCNS_11643_92_P1 = 0x0651,	/* CNS 11643-1992 plane 1 */
    kCFStringEncodingCNS_11643_92_P2 = 0x0652,	/* CNS 11643-1992 plane 2 */
    kCFStringEncodingCNS_11643_92_P3 = 0x0653,	/* CNS 11643-1992 plane 3 (was plane 14 in 1986 version) */

    /* ISO 2022 collections begin at 0x800 */
    kCFStringEncodingISO_2022_JP = 0x0820,
    kCFStringEncodingISO_2022_JP_2 = 0x0821,
    kCFStringEncodingISO_2022_JP_1 = 0x0822, /* RFC 2237*/
    kCFStringEncodingISO_2022_JP_3 = 0x0823, /* JIS X0213*/
    kCFStringEncodingISO_2022_CN = 0x0830,
    kCFStringEncodingISO_2022_CN_EXT = 0x0831,
    kCFStringEncodingISO_2022_KR = 0x0840,

    /* EUC collections begin at 0x900 */
    kCFStringEncodingEUC_JP = 0x0920,		/* ISO 646, 1-byte katakana, JIS 208, JIS 212 */
    kCFStringEncodingEUC_CN = 0x0930,		/* ISO 646, GB 2312-80 */
    kCFStringEncodingEUC_TW = 0x0931,		/* ISO 646, CNS 11643-1992 Planes 1-16 */
    kCFStringEncodingEUC_KR = 0x0940,		/* ISO 646, KS C 5601-1987 */

    /* Misc standards begin at 0xA00 */
    kCFStringEncodingShiftJIS = 0x0A01,		/* plain Shift-JIS */
    kCFStringEncodingKOI8_R = 0x0A02,		/* Russian internet standard */
    kCFStringEncodingBig5 = 0x0A03,		/* Big-5 (has variants) */
    kCFStringEncodingMacRomanLatin1 = 0x0A04,	/* Mac OS Roman permuted to align with ISO Latin-1 */
    kCFStringEncodingHZ_GB_2312 = 0x0A05,	/* HZ (RFC 1842, for Chinese mail & news) */
    kCFStringEncodingBig5_HKSCS_1999 = 0x0A06, /* Big-5 with Hong Kong special char set supplement*/
    kCFStringEncodingVISCII = 0x0A07,	/* RFC 1456, Vietnamese */
    kCFStringEncodingKOI8_U = 0x0A08,	/* RFC 2319, Ukrainian */
    kCFStringEncodingBig5_E = 0x0A09,	/* Taiwan Big-5E standard */

    /* Other platform encodings*/
/*  kCFStringEncodingNextStepLatin = 0x0B01, defined in CoreFoundation/CFString.h */
    kCFStringEncodingNextStepJapanese = 0x0B02,	/* NextStep Japanese encoding */

    /* EBCDIC & IBM host encodings begin at 0xC00 */
    kCFStringEncodingEBCDIC_US = 0x0C01,	/* basic EBCDIC-US */
    kCFStringEncodingEBCDIC_CP037 = 0x0C02,	/* code page 037, extended EBCDIC (Latin-1 set) for US,Canada... */

    kCFStringEncodingUTF7 CF_ENUM_AVAILABLE(10_6, 4_0) = 0x04000100, /* kTextEncodingUnicodeDefault + kUnicodeUTF7Format RFC2152 */
    kCFStringEncodingUTF7_IMAP CF_ENUM_AVAILABLE(10_6, 4_0) = 0x0A10, /* UTF-7 (IMAP folder variant) RFC3501 */

    /* Deprecated constants */
    kCFStringEncodingShiftJIS_X0213_00 = 0x0628 /* Shift-JIS format encoding of JIS X0213 planes 1 and 2 (DEPRECATED) */
};

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFSTRINGENCODINGEXT__ */

