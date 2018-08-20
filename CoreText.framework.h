// ==========  CoreText.framework/Headers/CTRunDelegate.h
/*
 *	CTRunDelegate.h
 *	CoreText
 *
 *	Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTRUNDELEGATE__
#define __CTRUNDELEGATE__

#include <CoreText/CTDefines.h>
#include <CoreText/CTRun.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Run Delegate Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTRunDelegate * CTRunDelegateRef;

/*!
	@function	CTRunDelegateGetTypeID
	@abstract	Returns the CFType of CTRunDelegate objects.
*/

CFTypeID CTRunDelegateGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Run Delegate Callbacks */
/* --------------------------------------------------------------------------- */

/*!
	@typedef	CTRunDelegateDeallocateCallback
	@abstract	The callback invoked when a CTRunDelegate is deallocated.
	
	@param		refCon
				The value supplied to CTRunDelegateCreate.
*/

typedef void (*CTRunDelegateDeallocateCallback) (
	void * refCon );

/*!
	@typedef	CTRunDelegateGetAscentCallback
	@abstract	The callback used to determine typographic ascent.
	
	@param		refCon
				The value supplied to CTRunDelegateCreate.
				
	@result		A CGFloat value indicating the typographic ascent of glyphs to
				which a run delegate pertains.
*/

typedef CGFloat (*CTRunDelegateGetAscentCallback) (
	void * refCon );

/*!
	@typedef	CTRunDelegateGetDescentCallback
	@abstract	The callback used to determine typographic descent.
	
	@param		refCon
				The value supplied to CTRunDelegateCreate.
				
	@result		A CGFloat value indicating the typographic descent of glyphs to
				which a run delegate pertains.
*/

typedef CGFloat (*CTRunDelegateGetDescentCallback) (
	void * refCon );

/*!
	@typedef	CTRunDelegateGetWidthCallback
	@abstract	The callback used to determine width.
	
	@param		refCon
				The value supplied to CTRunDelegateCreate.
				
	@result		A CGFloat value indicating the width of glyphs to which a run
				delegate pertains. A value of 0.0 indicates that the glyphs
				should not be drawn.
*/

typedef CGFloat (*CTRunDelegateGetWidthCallback) (
	void * refCon );

/*!
	@typedef	CTRunDelegateCallbacks
	@abstract	Structure containing the callbacks of a CTRunDelegate.
	
	@discussion These callbacks are provided by the owner of a run delegate and
				are used to modify glyph metrics during layout. The values
				returned by a delegate are applied to each glyph in the run(s)
				corresponding to the attribute containing that delegate.
				
	@field		version
				The version number of the callbacks being passed in as a
				parameter to CTRunDelegateCreate. This field should always 
				be set to kCTRunDelegateCurrentVersion.
				
	@field		dealloc
				The callback used when a CTRunDelegate's retain count reaches
				0 and the CTRunDelegate is deallocated. This callback may be
				NULL.
				
	@field		getAscent
				The callback used to indicate the ascent of the
				CTRunDelegate. This callback may be NULL, which is equivalent
				to a getAscent callback that always returns 0.
				
	@field		getDescent
				The callback used to indicate the descent of the
				CTRunDelegate. This callback may be NULL, which is equivalent
				to a getDescent callback that always returns 0.
				
	@field		getWidth
				The callback used to indicate the width of the
				CTRunDelegate. This callback may be NULL, which is equivalent
				to a getWidth callback that always returns 0.
*/

typedef struct
{
	CFIndex							version;
	CTRunDelegateDeallocateCallback	dealloc;
	CTRunDelegateGetAscentCallback	getAscent;
	CTRunDelegateGetDescentCallback	getDescent;
	CTRunDelegateGetWidthCallback	getWidth;
} CTRunDelegateCallbacks;

/* --------------------------------------------------------------------------- */
/* Run Delegate Versions */
/* --------------------------------------------------------------------------- */

/*!
	@enum		Run Delegate Versions
	@discussion Set version field of CTRunDelegateCallbacks to kCTRunDelegateCurrentVersion
				when calling CTRunDelegateCreate.
 */
enum {
	kCTRunDelegateVersion1 = 1,
	kCTRunDelegateCurrentVersion = kCTRunDelegateVersion1
};

/* --------------------------------------------------------------------------- */
/* Run Delegate Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTRunDelegateCreate
	@abstract	Creates an immutable instance of a run delegate.

	@discussion This function creates an immutable instance of a run delegate
				that can be used for reserving space in a line or for eliding the
				glyphs for a range of text altogether. 
				
	@param		callbacks
				The callbacks for this run delegate.
				
	@result		If run delegate creation was successful, this function will
				return a valid reference to an immutable CTRunDelegate
				object. Otherwise, this function will return NULL.
*/

CTRunDelegateRef __nullable CTRunDelegateCreate(
	const CTRunDelegateCallbacks* callbacks,
	void * __nullable refCon ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Run Delegate Access */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTRunDelegateGetRefCon
	@abstract	Returns a run delegate's refCon value.

	@discussion This function returns the refCon value that a run delegate was
				created with.
				
	@param		runDelegate
				The run delegate to be queried.
				
	@result		The refCon value of the supplied run delegate.
*/

void * CTRunDelegateGetRefCon(
	CTRunDelegateRef runDelegate ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTTextTab.h
/*
 *	CTTextTab.h
 *	CoreText
 *
 *	Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTTEXTTAB__
#define __CTTEXTTAB__

#include <CoreText/CTDefines.h>
#include <CoreText/CTParagraphStyle.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Text Tab Types */
/* --------------------------------------------------------------------------- */

/* A CTTextTab represents a tab in an CTParagraphStyle object, storing an
	alignment type and location.

	CoreText supports four alignment types: left, center, right, and decimal.
	These alignment types are absolute, not based on the line sweep direction
	of text. For example, tabbed text is always positioned to the left of a
	right-aligned tab, whether the line sweep direction is left to right or right
	to left. A tab's location, on the other hand, is relative to the back margin.
	A tab set at 1.5", for example, is at 1.5" from the right in right to left
	text.
*/

typedef const struct CF_RELATED_TYPE(NSTextTab,,) __CTTextTab * CTTextTabRef;


/*!
	@function	CTTypesetterGetTypeID
	@abstract	Returns the CFType of the text tab object
*/

CFTypeID CTTextTabGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Constants */
/* --------------------------------------------------------------------------- */

/*!
	@const		kCTTabColumnTerminatorsAttributeName
	@abstract	Used to specify the terminating character for a tab column

	@discussion The value associated with this attribute is a CFCharacterSet. The
				character set is used to determine the terminating character for
				a tab column. The tab and newline characters are implied even if
				they don't exist in the character set. This attribute can be used
				to implement decimal tabs, for instance. This attribute is
				optional.
*/

extern const CFStringRef kCTTabColumnTerminatorsAttributeName CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTextTabCreate
	@abstract	Creates and initializes a new text tab.

	@param		alignment
				The tab's alignment. This is used to determine the position of
				text inside the tab column. This parameter must be set to a valid
				CTTextAlignment value or this function will return NULL.

	@param		location
				The tab's ruler location, relative to the back margin.

	@param		options
				Options to pass in when the tab is created. Currently, the only
				option available is kCTTabColumnTerminatorsAttributeName. This
				parameter is optional and can be set to NULL if not needed.

	@result		The new CTTextTab.
*/

CTTextTabRef CTTextTabCreate(
	CTTextAlignment alignment,
	double location,
	CFDictionaryRef __nullable options ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Access */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTextTabGetAlignment
	@abstract	Returns the text alignment of the tab.

	@param		tab
				The tab whose text alignment you wish to access.

	@result		The tab's text alignment value.
*/

CTTextAlignment CTTextTabGetAlignment(
	CTTextTabRef tab ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTTextTabGetLocation
	@abstract	Returns the tab's ruler location.

	@param		tab
				The tab whose location you wish to access.

	@result		The tab's ruler location relative to the back margin.
*/

double CTTextTabGetLocation(
	CTTextTabRef tab ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTTextTabGetOptions
	@abstract	Returns the dictionary of attributes associated with the tab. 

	@param		tab
				The tab whose attributes you wish to access.

	@result		The dictionary of attributes associated with the tab or NULL if
				no dictionary is present.
*/

CFDictionaryRef __nullable CTTextTabGetOptions(
	CTTextTabRef tab ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTFontDescriptor.h
/*
 *  CTFontDescriptor.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTDESCRIPTOR__
#define __CTFONTDESCRIPTOR__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontTraits.h>

#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFSet.h>
#include <CoreGraphics/CGAffineTransform.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*! --------------------------------------------------------------------------
    @group Descriptor Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontDescriptorRef
    @abstract   The Core Text Font Descriptor reference.
    @discussion This is a opaque reference to a font descriptor.
*/
#if TARGET_OS_IPHONE
typedef const struct CF_BRIDGED_TYPE(UIFontDescriptor) __CTFontDescriptor * CTFontDescriptorRef;
#else
typedef const struct CF_BRIDGED_TYPE(NSFontDescriptor) __CTFontDescriptor * CTFontDescriptorRef;
#endif

/*!
    @function   CTFontDescriptorGetTypeID
    @abstract   Returns the type identifier for Core Text font descriptor
                references.
    @result     The identifier for the opaque type CTFontDescriptorRef.
*/
CFTypeID CTFontDescriptorGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Descriptor Constants
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontURLAttribute
    @abstract   The font URL.
    @discussion This is the key for accessing the font URL from the font descriptor. The value associated with this key is a CFURLRef.
*/
extern const CFStringRef kCTFontURLAttribute CT_AVAILABLE(10_6, 3_2);
/*!
    @defined    kCTFontNameAttribute
    @abstract   The PostScript name.
    @discussion This is the key for retrieving the PostScript name from the font descriptor. When matching, this is treated more generically: the system first tries to find fonts with this PostScript name. If none is found, the system tries to find fonts with this family name, and, finally, if still nothing, tries to find fonts with this display name. The value associated with this key is a CFStringRef. If unspecified, defaults to "Helvetica", if unavailable falls back to global font cascade list.
*/
extern const CFStringRef kCTFontNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontDisplayNameAttribute
    @abstract   The display name.
    @discussion This is the key for accessing the name used to display the font. Most commonly this is the full name. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontDisplayNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFamilyNameAttribute
    @abstract   The family name.
    @discussion This is the key for accessing the family name from the font descriptor. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontFamilyNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontStyleNameAttribute
    @abstract   The style name.
    @discussion This is the key for accessing the style name of the font. This name represents the designer's description of the font's style. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontStyleNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontTraitsAttribute
    @abstract   The font traits dictionary.
    @discussion This is the key for accessing the dictionary of font traits for stylistic information. See CTFontTraits.h for the list of font traits. The value associated with this key is a CFDictionaryRef.
*/
extern const CFStringRef kCTFontTraitsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAttribute
    @abstract   The font variation dictionary.
    @discussion This key is used to obtain the font variation instance as a CFDictionaryRef. If specified in a font descriptor, fonts with the specified axes will be primary match candidates, if no such fonts exist, this attribute will be ignored.
*/
extern const CFStringRef kCTFontVariationAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontSizeAttribute
    @abstract   The font point size.
    @discussion This key is used to obtain or specify the font point size. Creating a font with this unspecified will default to a point size of 12.0. The value for this key is represented as a CFNumberRef.
*/
extern const CFStringRef kCTFontSizeAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontMatrixAttribute
    @abstract   The font transformation matrix.
    @discussion This key is used to specify the font transformation matrix when creating a font. The default value is CGAffineTransformIdentity. The value for this key is a CFDataRef containing a CGAffineTransform, of which only the a, b, c, and d fields are used.
*/
extern const CFStringRef kCTFontMatrixAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontCascadeListAttribute
    @abstract   The font cascade list.
    @discussion This key is used to specify or obtain the cascade list used for a font reference. The cascade list is a CFArrayRef containing CTFontDescriptorRefs. If unspecified, the global cascade list is used. This list is not consulted for private-use characters on OS X 10.10, iOS 8, or earlier.
*/
extern const CFStringRef kCTFontCascadeListAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontCharacterSetAttribute
    @abstract   The font unicode character coverage set.
    @discussion This key is used to specify or obtain the character set for a font reference. This value for this key is a CFCharacterSetRef. If specified this can be used to restrict the font to a subset of its actual character set. If unspecified this attribute is ignored and the actual character set is used.
*/
extern const CFStringRef kCTFontCharacterSetAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontLanguagesAttribute
    @abstract   The list of supported languages.
    @discussion This key is used to specify or obtain a list of covered languages for a font reference. The value for this key is a CFArrayRef of CFStringRefs. If specified this restricts the search to matching fonts that support the specified languages. The language identifier string should conform to UTS #35. If unspecified this attribute is ignored.
*/
extern const CFStringRef kCTFontLanguagesAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontBaselineAdjustAttribute
    @abstract   The baseline adjustment to apply to font metrics.
    @discussion This key is used to specify or obtain the baseline adjustment for a font reference. This is primary used when defining font descriptors for a cascade list to keep the baseline of all fonts even. The value associated with this is a float represented as a CFNumberRef.
*/
extern const CFStringRef kCTFontBaselineAdjustAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontMacintoshEncodingsAttribute
    @abstract   The macintosh encodings attribute.
    @discussion This key is used to specify or obtain the macintosh encodings for a font reference. The value associated with this key is a CFNumberRef containing a bitfield of the Macintosh encodings. This attribute is provided for legacy compatibility.
*/
extern const CFStringRef kCTFontMacintoshEncodingsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeaturesAttribute
    @abstract   The array of font features.
    @discussion This key is used to specify or obtain the font features for a font reference. The value associated with this key is a CFArrayRef of font feature dictionaries. This features list contains the feature information from the 'feat' table of the font. See the CTFontCopyFeatures() API in   CTFont.h.
*/
extern const CFStringRef kCTFontFeaturesAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSettingsAttribute
    @abstract   The array of typographic feature settings.
    @discussion This key is used to specify an array of zero or more feature settings. In the case of duplicate or conflicting settings the last setting in the list will take precedence. In the case of AAT settings, it is the caller's responsibility to handle exclusive and non-exclusive settings as necessary.
                An AAT setting dictionary contains a tuple of a kCTFontFeatureTypeIdentifierKey key-value pair and a kCTFontFeatureSelectorIdentifierKey key-value pair.
                An OpenType setting dictionary contains a tuple of a kCTFontOpenTypeFeatureTag key-value pair and a kCTFontOpenTypeFeatureValue key-value pair. Each setting dictionary indicates which setting should be applied. In the case of duplicate or conflicting settings the last setting in the list will take precedence.

                Starting with OS X 10.10 and iOS 8.0, settings are also accepted (but not returned) in the following simplified forms:
                An OpenType setting can be either an array pair of tag string and value number, or a tag string on its own. For example: @[ @"c2sc", @1 ] or simply @"c2sc". An unspecified value enables the feature and a value of zero disables it.
                An AAT setting can be specified as an array pair of type and selector numbers. For example: @[ @(kUpperCaseType), @(kUpperCaseSmallCapsSelector) ].
*/
extern const CFStringRef kCTFontFeatureSettingsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFixedAdvanceAttribute
    @abstract   Specifies advance width.
    @discussion This key is used to specify a constant advance width, which affects the glyph metrics of any font instance created with this key; it overrides font values and the font transformation matrix, if any. The value associated with this key must be a CFNumberRef.
*/
extern const CFStringRef kCTFontFixedAdvanceAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontOrientationAttribute
    @abstract   The orientation attribute.
    @discussion This key is used to specify a particular orientation for the glyphs of the font. The value associated with this key is a int as a CFNumberRef. If you want to receive vertical metrics from a font for vertical rendering, specify kCTFontVerticalOrientation. If unspecified, the font will use its native orientation.
*/
extern const CFStringRef kCTFontOrientationAttribute CT_AVAILABLE(10_5, 3_2);

/*!
    @enum       CTFontOrientation
    @abstract   Specifies the intended rendering orientation of the font for obtaining glyph metrics.
*/
typedef CF_ENUM(uint32_t, CTFontOrientation) {
    kCTFontOrientationDefault    CT_ENUM_AVAILABLE(10_8, 6_0) = 0,
    kCTFontOrientationHorizontal CT_ENUM_AVAILABLE(10_8, 6_0) = 1,
    kCTFontOrientationVertical   CT_ENUM_AVAILABLE(10_8, 6_0) = 2,

    kCTFontDefaultOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationDefault,
    kCTFontHorizontalOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationHorizontal,
    kCTFontVerticalOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationVertical
};

/*!
    @defined    kCTFontFormatAttribute
    @abstract   Specifies the recognized format of the font.
    @discussion The attribute is used to specify or obtain the format of the font. The returned value is a CFNumber containing one of the constants defined below.
*/
extern const CFStringRef kCTFontFormatAttribute CT_AVAILABLE(10_6, 3_2);

/*!
    @constant   kCTFontFormatUnrecognized
                The font is not a recognized format
    @constant   kCTFontFormatOpenTypePostScript
                The font is an OpenType format containing PostScript data
    @constant   kCTFontFormatOpenTypeTrueType
                The font is an OpenType format containing TrueType data
    @constant   kCTFontFormatTrueType
                The font is a recognized TrueType format
    @constant   kCTFontFormatPostScript
                The font is a recognized PostScript format
    @constant   kCTFontFormatBitmap
                The font is a bitmap only format
*/
typedef CF_ENUM(uint32_t, CTFontFormat) {
    kCTFontFormatUnrecognized       = 0,
    kCTFontFormatOpenTypePostScript = 1,
    kCTFontFormatOpenTypeTrueType   = 2,
    kCTFontFormatTrueType           = 3,
    kCTFontFormatPostScript         = 4,
    kCTFontFormatBitmap             = 5
};

/*!
    @defined    kCTFontRegistrationScopeAttribute
    @abstract   Specifies the font descriptor's registration scope.
    @discussion The attribute is used to specify or obtain the font registration scope. The value returned is a CFNumberRef containing one of the CTFontManagerScope enumerated values. A value of NULL can be returned for font descriptors that are not registered.
*/
extern const CFStringRef kCTFontRegistrationScopeAttribute CT_AVAILABLE(10_6, 3_2);
/*!
    @defined    kCTFontPriorityAttribute
    @abstract   The font descriptors priority when resolving duplicates and sorting match results.
    @discussion This key is used to obtain or specify the font priority. The value returned is a CFNumberRef containing an integer value as defined below. The higher the value, the higher the priority of the font. Only registered fonts will have a priority. Unregistered font descriptors will return NULL.
*/
extern const CFStringRef kCTFontPriorityAttribute CT_AVAILABLE(10_6, 3_2);

/*!
    @constant   kCTFontPrioritySystem
                Priority of system fonts (located in /System/Library/Fonts).
    @constant   kCTFontPriorityNetwork
                Priority of network fonts (located in /Network/Library/Fonts).
    @constant   kCTFontPriorityComputer
                Priority of computer local fonts (located in /Library/Fonts).
    @constant   kCTFontPriorityUser
                Priority of local fonts (located in user's Library/Fonts).
    @constant   kCTFontPriorityDynamic
                Priority of fonts registered dynamically, not located in a standard location (either kCTFontManagerScopeUser, or kCTFontManagerScopeSession).
    @constant   kCTFontPriorityProcess
                Priority of fonts registered for the process (kCTFontManagerScopeProcess).
*/
enum {
    kCTFontPrioritySystem       =  10000,
    kCTFontPriorityNetwork      =  20000,
    kCTFontPriorityComputer     =  30000,
    kCTFontPriorityUser         =  40000,
    kCTFontPriorityDynamic      =  50000,
    kCTFontPriorityProcess      =  60000
};
typedef uint32_t CTFontPriority;

/*!
    @defined    kCTFontEnabledAttribute
    @abstract   The font enabled state.
    @discussion This key is used to obtain the font state. The returned value is a CFNumberRef representing a boolean value. Unregistered font descriptors will return NULL, which is equivalent to false.
*/
extern const CFStringRef kCTFontEnabledAttribute CT_AVAILABLE(10_6, 3_2);

/*!
	@defined    kCTFontDownloadableAttribute
	@abstract   The font downloadable state.
	@discussion The value associated with this key is a CFBoolean.  If it is kCFBooleanTrue, CoreText attempts to download a font if necessary when matching a descriptor.
*/
extern const CFStringRef kCTFontDownloadableAttribute CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTFontDownloadedAttribute
    @abstract   The download state.
    @discussion The value associated with this key is a CFBoolean.  If it is kCFBooleanTrue, corresponding FontAsset has been downloaded. (but still it may be necessary to call appropriate API in order to use the font in the FontAsset.)
*/
extern const CFStringRef kCTFontDownloadedAttribute CT_AVAILABLE_IOS(7_0);

/*! --------------------------------------------------------------------------
    @group Descriptor Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCreateWithNameAndSize
    @abstract   Creates a new font descriptor with the provided PostScript name and size.

    @param      name
                The PostScript name to be used for the font descriptor as a CFStringRef.

    @param      size
                The point size. If 0.0, the kCTFontSizeAttribute will be omitted from the font descriptor.

    @result     This function creates a new font descriptor reference with the given PostScript name and point size.
*/
CTFontDescriptorRef CTFontDescriptorCreateWithNameAndSize(
    CFStringRef         name,
    CGFloat             size ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateWithAttributes
    @abstract   Creates a new font descriptor reference from a dictionary of attributes.

    @param      attributes
                A CFDictionaryRef of arbitrary attributes.

    @result     This function creates a new font descriptor with the attributes specified. This dictionary can contain arbitrary attributes that will be preserved, however unrecognized attributes will be ignored on font creation and and may not be preserved over the round trip (descriptor -> font -> descriptor).
*/
CTFontDescriptorRef CTFontDescriptorCreateWithAttributes(
    CFDictionaryRef     attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateCopyWithAttributes
    @abstract   Creates a copy of the original font descriptor with new attributes.

    @param      original
                The original font descriptor reference.

    @param      attributes
                A CFDictionaryRef of arbitrary attributes.

    @result     This function creates a new copy of the original font descriptor with attributes augmented by those specified. If there are conflicts between attributes, the new attributes will replace existing ones, except for kCTFontVariationAttribute and kCTFontFeatureSettingsAttribute which will be merged.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithAttributes(
    CTFontDescriptorRef     original,
    CFDictionaryRef         attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateCopyWithFamily
    @abstract   Returns a new font descriptor in the specified family based on the traits of the original descriptor.

    @param      original
                The original font descriptor reference.

    @param		family
                The name of the desired family.

    @result     Returns a new font reference with the original traits in the given family, or NULL if none found in the system.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateCopyWithFamily(
    CTFontDescriptorRef     original,
    CFStringRef             family ) CT_AVAILABLE(10_9, 7_0);

/*!
    @function   CTFontDescriptorCreateCopyWithSymbolicTraits
    @abstract   Returns a new font descriptor based on the original descriptor having the specified symbolic traits.

    @param      original
                The original font descriptor reference.

    @param		symTraitValue
                The value of the symbolic traits. This bitfield is used to indicate the desired value for the traits specified by the symTraitMask parameter. Used in conjunction, they can allow for trait removal as well as addition.

    @param		symTraitMask
                The mask bits of the symbolic traits. This bitfield is used to indicate the traits that should be changed.

    @result     Returns a new font descriptor reference in the same family with the given symbolic traits, or NULL if none found in the system.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateCopyWithSymbolicTraits(
    CTFontDescriptorRef     original,
    CTFontSymbolicTraits    symTraitValue,
    CTFontSymbolicTraits    symTraitMask ) CT_AVAILABLE(10_9, 7_0);

/*!
    @function   CTFontDescriptorCreateCopyWithVariation
    @abstract   Creates a copy of the original font descriptor with a new variation instance.

    @param      original
                The original font descriptor reference.

    @param      variationIdentifier
                The variation axis identifier. This is the four character code of the variation axis as a CFNumberRef.

    @param      variationValue
                The value corresponding with the variation instance.

    @result     This function returns a copy of the original font descriptor with a new variation instance. This is a convenience method for easily creating new variation font instances.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithVariation(
    CTFontDescriptorRef     original,
    CFNumberRef             variationIdentifier,
    CGFloat                 variationValue ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateCopyWithFeature
    @abstract   Copies a font descriptor with new feature setting.

    @discussion This is a convenience method to more easily toggle the state of individual features.

    @param      original
                The original font descriptor reference.

    @param      featureTypeIdentifier
                The feature type identifier.

    @param      featureSelectorIdentifier
                The feature selector identifier.

    @result     A copy of the original font descriptor modified with the given feature settings.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithFeature(
    CTFontDescriptorRef     original,
    CFNumberRef             featureTypeIdentifier,
    CFNumberRef             featureSelectorIdentifier ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptors
    @abstract   Returns an array of font normalized font descriptors matching the provided descriptor.

    @param      descriptor
                The font descriptor reference.

    @param      mandatoryAttributes
                A set of attribute keys which are required to be identically matched in any returned font descriptors. Optional.

    @result     This function returns a retained array of normalized font descriptors matching the attributes present in descriptor. If descriptor itself is normalized then the array will contain only one item, the original descriptor.
*/
CFArrayRef __nullable CTFontDescriptorCreateMatchingFontDescriptors(
    CTFontDescriptorRef     descriptor,
    CFSetRef __nullable     mandatoryAttributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptor
    @abstract   Returns an the single preferred matching font descriptor based on the original descriptor and system precedence.

    @param      descriptor
                The font descriptor reference.

    @param      mandatoryAttributes
                A set of attribute keys which are required to be identically matched in any returned font descriptors. Optional.

    @result     This function returns a retained normalized font descriptor matching the attributes present in descriptor. The original descriptor may be returned in normalized form.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateMatchingFontDescriptor(
    CTFontDescriptorRef     descriptor,
    CFSetRef __nullable     mandatoryAttributes ) CT_AVAILABLE(10_5, 3_2);

    
/*!
    Progress state
 */

typedef CF_ENUM(uint32_t, CTFontDescriptorMatchingState) {
    kCTFontDescriptorMatchingDidBegin,              // called once at the beginning.
    kCTFontDescriptorMatchingDidFinish,             // called once at the end.
    
    kCTFontDescriptorMatchingWillBeginQuerying,     // called once before talking to the server.  Skipped if not necessary.
    kCTFontDescriptorMatchingStalled,               // called when stalled. (e.g. while waiting for server response.)
    
    // Downloading and activating are repeated for each descriptor.
    kCTFontDescriptorMatchingWillBeginDownloading,  // Downloading part may be skipped if all the assets are already downloaded
    kCTFontDescriptorMatchingDownloading,
    kCTFontDescriptorMatchingDidFinishDownloading,
    kCTFontDescriptorMatchingDidMatch,              // called when font descriptor is matched.
    
    kCTFontDescriptorMatchingDidFailWithError       // called when an error occurred.  (may be called multiple times.)
};

/*!
    keys for progressParameter dictionary.
 */

/* CTFontDescriptorRef; The current font descriptor.   Valid when state is kCTFontDescriptorMatchingDidMatch. */
extern const CFStringRef kCTFontDescriptorMatchingSourceDescriptor CT_AVAILABLE(10_8, 6_0);

/* CFArray; Array of descriptors to be queried.   Valid while downloading or when state is kCTFontDescriptorMatchingWillBeginQuerying. */
extern const CFStringRef kCTFontDescriptorMatchingDescriptors CT_AVAILABLE(10_8, 6_0);

/* CFArray; Array of matched font descriptors.   Valid when state is kCTFontDescriptorMatchingDidMatch or CTFontDescriptorMatchingEnd. */
extern const CFStringRef kCTFontDescriptorMatchingResult CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Download progress in 0 - 100.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingPercentage CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Byte size to download for the current descriptor.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingCurrentAssetSize CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Total downloaded byte size.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingTotalDownloadedSize CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Total byte size to download.   Always valid, but may be Zero when information is not available. */
extern const CFStringRef kCTFontDescriptorMatchingTotalAssetSize CT_AVAILABLE(10_8, 6_0);

/* CFError; Valid when state kCTFontDescriptorMatchingDidFailWithError. */
extern const CFStringRef kCTFontDescriptorMatchingError CT_AVAILABLE(10_8, 6_0);

#if defined(__BLOCKS__)

/* Progress callback type */
typedef bool (^CTFontDescriptorProgressHandler)(CTFontDescriptorMatchingState state, CFDictionaryRef progressParameter);

/*
    @function   CTFontDescriptorMatchFontDescriptorsWithProgressHandler
                This function returns immediately, but can potentially take long time to process.  The progress is notified via progressBlock.
     
    @param      descriptors
                An array of descriptors to process.
     
    @param      mandatoryAttributes
     
    @param      progressBlock
                Callback block to indicate the progress.
                Return true to continue, and return false to cancel the process.
     
    @result     false if it couldn't start the work.
*/
    
bool CTFontDescriptorMatchFontDescriptorsWithProgressHandler(
    CFArrayRef                          descriptors,
    CFSetRef __nullable                 mandatoryAttributes,
    CTFontDescriptorProgressHandler     progressBlock) CT_AVAILABLE(10_9, 6_0);

#endif // defined(__BLOCKS__)

/*! --------------------------------------------------------------------------
    @group Descriptor Accessors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCopyAttributes
    @abstract   Returns the attributes dictionary of the font descriptor.

    @param      descriptor
                The font descriptor reference.

    @result     A retained reference to the font descriptor attributes dictionary. This dictionary will contain the minimum number of attributes to fully specify this particular font descriptor.
*/
CFDictionaryRef CTFontDescriptorCopyAttributes(
    CTFontDescriptorRef     descriptor ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCopyAttribute
    @abstract   Returns the value associated with an arbitrary attribute.

    @param      descriptor
                The font descriptor.

    @param      attribute
                The requested attribute.

    @result     A retained reference to the requested attribute, or NULL if the requested attribute is not present. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef __nullable CTFontDescriptorCopyAttribute(
    CTFontDescriptorRef     descriptor,
    CFStringRef             attribute ) CT_AVAILABLE(10_5, 3_2);

/*!
    function    CTFontDescriptorCopyLocalizedAttribute
    @abstract   Returns a localized value for the requested attribute if available.

    @discussion This function returns a localized attribute based on the global language list. If localization is not possible for the attribute the behavior matches CTFontDescriptorCopyAttribute(). Generally, localization of attributes is only applicable to name attributes of a normalized font descriptor.

    @param      descriptor
                The font descriptor reference.

    @param      attribute
                The requested font attribute.

    @param      language
                If non-NULL, this will be receive a retained reference to the matched language. The language identifier will conform to UTS #35.
                If CoreText can supply its own localized string where the font cannot, this value will be NULL.

    @result     A retained reference to the requested attribute, or NULL if the requested attribute is not present. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef __nullable CTFontDescriptorCopyLocalizedAttribute(
    CTFontDescriptorRef     descriptor,
    CFStringRef             attribute,
    CFStringRef __nullable * __nullable language ) CT_AVAILABLE(10_5, 3_2);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/SFNTTypes.h
/*
 *  SFNTTypes.h
 *  CoreText
 *
 *  Copyright 1994-2013 Apple Inc. All rights reserved.
 *
 */

#ifndef __SFNTTYPES__
#define __SFNTTYPES__

#include <MacTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

struct sfntDirectoryEntry {
  FourCharCode        tableTag;
  UInt32              checkSum;
  UInt32              offset;
  UInt32              length;
};
typedef struct sfntDirectoryEntry       sfntDirectoryEntry;
/* The search fields limits numOffsets to 4096. */
struct sfntDirectory {
  FourCharCode        format;
  UInt16              numOffsets;             /* number of tables */
  UInt16              searchRange;            /* (max2 <= numOffsets)*16 */
  UInt16              entrySelector;          /* log2(max2 <= numOffsets) */
  UInt16              rangeShift;             /* numOffsets*16-searchRange*/
  sfntDirectoryEntry  table[1];               /* table[numOffsets] */
};
typedef struct sfntDirectory            sfntDirectory;
enum {
  sizeof_sfntDirectory          = 12
};

/* Cmap - character id to glyph id mapping */
enum {
  cmapFontTableTag              = 'cmap'
};

enum {
  kFontUnicodePlatform          = 0,
  kFontMacintoshPlatform        = 1,
  kFontReservedPlatform         = 2,
  kFontMicrosoftPlatform        = 3,
  kFontCustomPlatform           = 4
};

enum {
  kFontUnicodeDefaultSemantics  = 0,
  kFontUnicodeV1_1Semantics     = 1,
  kFontISO10646_1993Semantics   = 2,
  kFontUnicodeV2_0BMPOnlySemantics = 3,
  kFontUnicodeV2_0FullCoverageSemantics = 4,
  kFontUnicodeV4_0VariationSequenceSemantics = 5,
  kFontUnicode_FullRepertoire = 6
};

enum {
  kFontRomanScript              = 0,
  kFontJapaneseScript           = 1,
  kFontTraditionalChineseScript = 2,
  kFontChineseScript            = kFontTraditionalChineseScript,
  kFontKoreanScript             = 3,
  kFontArabicScript             = 4,
  kFontHebrewScript             = 5,
  kFontGreekScript              = 6,
  kFontCyrillicScript           = 7,
  kFontRussian                  = kFontCyrillicScript,
  kFontRSymbolScript            = 8,
  kFontDevanagariScript         = 9,
  kFontGurmukhiScript           = 10,
  kFontGujaratiScript           = 11,
  kFontOriyaScript              = 12,
  kFontBengaliScript            = 13,
  kFontTamilScript              = 14,
  kFontTeluguScript             = 15,
  kFontKannadaScript            = 16,
  kFontMalayalamScript          = 17,
  kFontSinhaleseScript          = 18,
  kFontBurmeseScript            = 19,
  kFontKhmerScript              = 20,
  kFontThaiScript               = 21,
  kFontLaotianScript            = 22,
  kFontGeorgianScript           = 23,
  kFontArmenianScript           = 24,
  kFontSimpleChineseScript      = 25,
  kFontTibetanScript            = 26,
  kFontMongolianScript          = 27,
  kFontGeezScript               = 28,
  kFontEthiopicScript           = kFontGeezScript,
  kFontAmharicScript            = kFontGeezScript,
  kFontSlavicScript             = 29,
  kFontEastEuropeanRomanScript  = kFontSlavicScript,
  kFontVietnameseScript         = 30,
  kFontExtendedArabicScript     = 31,
  kFontSindhiScript             = kFontExtendedArabicScript,
  kFontUninterpretedScript      = 32
};

enum {
  kFontMicrosoftSymbolScript    = 0,
  kFontMicrosoftStandardScript  = 1,
  kFontMicrosoftUCS4Script      = 10
};


enum {
  kFontCustom8BitScript         = 0,
  kFontCustom816BitScript       = 1,
  kFontCustom16BitScript        = 2
};

/* Language codes are zero based everywhere but within a 'cmap' table */
enum {
  kFontEnglishLanguage          = 0,
  kFontFrenchLanguage           = 1,
  kFontGermanLanguage           = 2,
  kFontItalianLanguage          = 3,
  kFontDutchLanguage            = 4,
  kFontSwedishLanguage          = 5,
  kFontSpanishLanguage          = 6,
  kFontDanishLanguage           = 7,
  kFontPortugueseLanguage       = 8,
  kFontNorwegianLanguage        = 9,
  kFontHebrewLanguage           = 10,
  kFontJapaneseLanguage         = 11,
  kFontArabicLanguage           = 12,
  kFontFinnishLanguage          = 13,
  kFontGreekLanguage            = 14,
  kFontIcelandicLanguage        = 15,
  kFontMalteseLanguage          = 16,
  kFontTurkishLanguage          = 17,
  kFontCroatianLanguage         = 18,
  kFontTradChineseLanguage      = 19,
  kFontUrduLanguage             = 20,
  kFontHindiLanguage            = 21,
  kFontThaiLanguage             = 22,
  kFontKoreanLanguage           = 23,
  kFontLithuanianLanguage       = 24,
  kFontPolishLanguage           = 25,
  kFontHungarianLanguage        = 26,
  kFontEstonianLanguage         = 27,
  kFontLettishLanguage          = 28,
  kFontLatvianLanguage          = kFontLettishLanguage,
  kFontSaamiskLanguage          = 29,
  kFontLappishLanguage          = kFontSaamiskLanguage,
  kFontFaeroeseLanguage         = 30,
  kFontFarsiLanguage            = 31,
  kFontPersianLanguage          = kFontFarsiLanguage,
  kFontRussianLanguage          = 32,
  kFontSimpChineseLanguage      = 33,
  kFontFlemishLanguage          = 34,
  kFontIrishLanguage            = 35,
  kFontAlbanianLanguage         = 36,
  kFontRomanianLanguage         = 37,
  kFontCzechLanguage            = 38,
  kFontSlovakLanguage           = 39,
  kFontSlovenianLanguage        = 40,
  kFontYiddishLanguage          = 41,
  kFontSerbianLanguage          = 42,
  kFontMacedonianLanguage       = 43,
  kFontBulgarianLanguage        = 44,
  kFontUkrainianLanguage        = 45,
  kFontByelorussianLanguage     = 46,
  kFontUzbekLanguage            = 47,
  kFontKazakhLanguage           = 48,
  kFontAzerbaijaniLanguage      = 49,
  kFontAzerbaijanArLanguage     = 50,
  kFontArmenianLanguage         = 51,
  kFontGeorgianLanguage         = 52,
  kFontMoldavianLanguage        = 53,
  kFontKirghizLanguage          = 54,
  kFontTajikiLanguage           = 55,
  kFontTurkmenLanguage          = 56,
  kFontMongolianLanguage        = 57,
  kFontMongolianCyrLanguage     = 58,
  kFontPashtoLanguage           = 59,
  kFontKurdishLanguage          = 60,
  kFontKashmiriLanguage         = 61,
  kFontSindhiLanguage           = 62,
  kFontTibetanLanguage          = 63,
  kFontNepaliLanguage           = 64,
  kFontSanskritLanguage         = 65,
  kFontMarathiLanguage          = 66,
  kFontBengaliLanguage          = 67,
  kFontAssameseLanguage         = 68,
  kFontGujaratiLanguage         = 69,
  kFontPunjabiLanguage          = 70,
  kFontOriyaLanguage            = 71,
  kFontMalayalamLanguage        = 72,
  kFontKannadaLanguage          = 73,
  kFontTamilLanguage            = 74,
  kFontTeluguLanguage           = 75,
  kFontSinhaleseLanguage        = 76,
  kFontBurmeseLanguage          = 77,
  kFontKhmerLanguage            = 78,
  kFontLaoLanguage              = 79,
  kFontVietnameseLanguage       = 80,
  kFontIndonesianLanguage       = 81,
  kFontTagalogLanguage          = 82,
  kFontMalayRomanLanguage       = 83,
  kFontMalayArabicLanguage      = 84,
  kFontAmharicLanguage          = 85,
  kFontTigrinyaLanguage         = 86,
  kFontGallaLanguage            = 87,
  kFontOromoLanguage            = kFontGallaLanguage,
  kFontSomaliLanguage           = 88,
  kFontSwahiliLanguage          = 89,
  kFontRuandaLanguage           = 90,
  kFontRundiLanguage            = 91,
  kFontChewaLanguage            = 92,
  kFontMalagasyLanguage         = 93,
  kFontEsperantoLanguage        = 94,
  kFontWelshLanguage            = 128,
  kFontBasqueLanguage           = 129,
  kFontCatalanLanguage          = 130,
  kFontLatinLanguage            = 131,
  kFontQuechuaLanguage          = 132,
  kFontGuaraniLanguage          = 133,
  kFontAymaraLanguage           = 134,
  kFontTatarLanguage            = 135,
  kFontUighurLanguage           = 136,
  kFontDzongkhaLanguage         = 137,
  kFontJavaneseRomLanguage      = 138,
  kFontSundaneseRomLanguage     = 139
};

/* The following are special "don't care" values to be used in interfaces */

enum {
    kFontNoPlatformCode                 = (unsigned int)(~0),
  kFontNoScriptCode                   = (unsigned int)(~0),
  kFontNoLanguageCode                 = (unsigned int)(~0)
};

struct sfntCMapSubHeader {
  UInt16              format;
  UInt16              length;
  UInt16              languageID;             /* base-1 */
};
typedef struct sfntCMapSubHeader        sfntCMapSubHeader;
enum {
  sizeof_sfntCMapSubHeader      = 6
};

struct sfntCMapExtendedSubHeader {
  UInt16              format;
  UInt16              reserved;
  UInt32              length;
  UInt32              language;
};
typedef struct sfntCMapExtendedSubHeader sfntCMapExtendedSubHeader;
enum {
  sizeof_sfntCMapExtendedSubHeader = 12
};

struct sfntCMapEncoding {
  UInt16              platformID;             /* base-0 */
  UInt16              scriptID;               /* base-0 */
  UInt32              offset;
};
typedef struct sfntCMapEncoding         sfntCMapEncoding;
enum {
  sizeof_sfntCMapEncoding       = 8
};

struct sfntCMapHeader {
  UInt16              version;
  UInt16              numTables;
  sfntCMapEncoding    encoding[1];
};
typedef struct sfntCMapHeader           sfntCMapHeader;
enum {
  sizeof_sfntCMapHeader         = 4
};

/* Name table */
enum {
  nameFontTableTag              = 'name'
};

enum {
  kFontCopyrightName            = 0,
  kFontFamilyName               = 1,
  kFontStyleName                = 2,
  kFontUniqueName               = 3,
  kFontFullName                 = 4,
  kFontVersionName              = 5,
  kFontPostscriptName           = 6,
  kFontTrademarkName            = 7,
  kFontManufacturerName         = 8,
  kFontDesignerName             = 9,
  kFontDescriptionName          = 10,
  kFontVendorURLName            = 11,
  kFontDesignerURLName          = 12,
  kFontLicenseDescriptionName   = 13,
  kFontLicenseInfoURLName       = 14,
  kFontPreferredFamilyName      = 16,
  kFontPreferredSubfamilyName   = 17,
  kFontMacCompatibleFullName    = 18,
  kFontSampleTextName           = 19,
  kFontPostScriptCIDName        = 20,
  kFontLastReservedName         = 255
};

/* The following is a special "don't care" value to be used in interfaces */

enum {
    kFontNoNameCode                 = (unsigned int)(~0)
};

struct sfntNameRecord {
  UInt16              platformID;             /* base-0 */
  UInt16              scriptID;               /* base-0 */
  UInt16              languageID;             /* base-0 */
  UInt16              nameID;                 /* base-0 */
  UInt16              length;
  UInt16              offset;
};
typedef struct sfntNameRecord           sfntNameRecord;
enum {
  sizeof_sfntNameRecord         = 12
};

struct sfntNameHeader {
  UInt16              format;
  UInt16              count;
  UInt16              stringOffset;
  sfntNameRecord      rec[1];
};
typedef struct sfntNameHeader           sfntNameHeader;
enum {
  sizeof_sfntNameHeader         = 6
};

/* Fvar table - font variations */
enum {
  variationFontTableTag         = 'fvar'
};

/* These define each font variation */
struct sfntVariationAxis {
  FourCharCode        axisTag;
  Fixed               minValue;
  Fixed               defaultValue;
  Fixed               maxValue;
  SInt16              flags;
  SInt16              nameID;
};
typedef struct sfntVariationAxis        sfntVariationAxis;
enum {
  sizeof_sfntVariationAxis      = 20
};

/* These are named locations in style-space for the user */
struct sfntInstance {
  SInt16              nameID;
  SInt16              flags;
  Fixed               coord[1];               /* [axisCount] */
                                              /* room to grow since the header carries a tupleSize field */
};
typedef struct sfntInstance             sfntInstance;
enum {
  sizeof_sfntInstance           = 4
};

struct sfntVariationHeader {
  Fixed               version;                /* 1.0 Fixed */
  UInt16              offsetToData;           /* to first axis = 16*/
  UInt16              countSizePairs;         /* axis+inst = 2 */
  UInt16              axisCount;
  UInt16              axisSize;
  UInt16              instanceCount;
  UInt16              instanceSize;
                                              /* …other <count,size> pairs */
  sfntVariationAxis   axis[1];                /* [axisCount] */
  sfntInstance        instance[1];            /* [instanceCount]  …other arrays of data */
};
typedef struct sfntVariationHeader      sfntVariationHeader;
enum {
  sizeof_sfntVariationHeader    = 16
};

/* Fdsc table - font descriptor */
enum {
  descriptorFontTableTag        = 'fdsc'
};

struct sfntFontDescriptor {
  FourCharCode        name;
  Fixed               value;
};
typedef struct sfntFontDescriptor       sfntFontDescriptor;
struct sfntDescriptorHeader {
  Fixed               version;                /* 1.0 in Fixed */
  SInt32              descriptorCount;
  sfntFontDescriptor  descriptor[1];
};
typedef struct sfntDescriptorHeader     sfntDescriptorHeader;
enum {
  sizeof_sfntDescriptorHeader   = 8
};

/* Feat Table - layout feature table */
enum {
  featureFontTableTag           = 'feat'
};

struct sfntFeatureName {
  UInt16              featureType;
  UInt16              settingCount;
  SInt32              offsetToSettings;
  UInt16              featureFlags;
  SInt16              nameID;
};
typedef struct sfntFeatureName          sfntFeatureName;
struct sfntFontFeatureSetting {
  UInt16              setting;
  SInt16              nameID;
};
typedef struct sfntFontFeatureSetting   sfntFontFeatureSetting;
struct sfntFontRunFeature {
  UInt16              featureType;
  UInt16              setting;
};
typedef struct sfntFontRunFeature       sfntFontRunFeature;
struct sfntFeatureHeader {
  SInt32              version;                /* 1.0 */
  UInt16              featureNameCount;
  UInt16              featureSetCount;
  SInt32              reserved;               /* set to 0 */
  sfntFeatureName     names[1];
  sfntFontFeatureSetting  settings[1];
  sfntFontRunFeature  runs[1];
};
typedef struct sfntFeatureHeader        sfntFeatureHeader;
/* OS/2 Table */
enum {
  os2FontTableTag               = 'OS/2'
};

/*  Special invalid glyph ID value, useful as a sentinel value, for example */
enum {
  nonGlyphID                    = 65535
};

/*  Data type used to access names from font name table */

typedef UInt32                          FontNameCode;
/* Data types for encoding components as used in interfaces */
typedef UInt32                          FontPlatformCode;
typedef UInt32                          FontScriptCode;
typedef UInt32                          FontLanguageCode;
/*
**  FontVariation is used to specify a coordinate along a variation axis. The name
**  identifies the axes to be applied, and value is the setting to be used.
*/
struct FontVariation {
  FourCharCode        name;
  Fixed               value;
};
typedef struct FontVariation            FontVariation;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // __SFNTTYPES__
// ==========  CoreText.framework/Headers/CTFont.h
/*
 *  CTFont.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONT__
#define __CTFONT__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontDescriptor.h>

#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*! --------------------------------------------------------------------------
    @group Font Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontRef
    @abstract   The Core Text Font reference.
    @discussion This is a opaque reference to a core font object.
*/
#if TARGET_OS_IPHONE
typedef const struct CF_BRIDGED_TYPE(UIFont) __CTFont * CTFontRef;
#else
typedef const struct CF_BRIDGED_TYPE(NSFont) __CTFont * CTFontRef;
#endif

/*!
    @function   CTFontGetTypeID
    @abstract   Returns the type identifier for Core Text font references.
    @result     The identifier for the opaque type CTFontRef.
*/
CFTypeID CTFontGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Constants
*///--------------------------------------------------------------------------

// Name specifier constants
/*!
    @defined    kCTFontCopyrightNameKey
    @abstract   The name specifier for the copyright name.
*/
extern const CFStringRef kCTFontCopyrightNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFamilyNameKey
    @abstract   The name specifier for the family name.
*/
extern const CFStringRef kCTFontFamilyNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontSubFamilyNameKey
    @abstract   The name specifier for the subfamily name.
*/
extern const CFStringRef kCTFontSubFamilyNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontStyleNameKey
    @abstract   The name specifier for the style name.
*/
extern const CFStringRef kCTFontStyleNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontUniqueNameKey
    @abstract   The name specifier for the unique name.
    @discussion Note that this name is often not unique and should not be
                assumed to be truly unique.
*/
extern const CFStringRef kCTFontUniqueNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFullNameKey
    @abstract   The name specifier for the full name.
*/
extern const CFStringRef kCTFontFullNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVersionNameKey
    @abstract   The name specifier for the version name.
*/
extern const CFStringRef kCTFontVersionNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontPostScriptNameKey
    @abstract   The name specifier for the Postscript name.
*/
extern const CFStringRef kCTFontPostScriptNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontTrademarkNameKey
    @abstract   The name specifier for the trademark name.
*/
extern const CFStringRef kCTFontTrademarkNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontManufacturerNameKey
    @abstract   The name specifier for the manufacturer name.
*/
extern const CFStringRef kCTFontManufacturerNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontDesignerNameKey
    @abstract   The name specifier for the designer name.
*/
extern const CFStringRef kCTFontDesignerNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontDescriptionNameKey
    @abstract   The name specifier for the description name.
*/
extern const CFStringRef kCTFontDescriptionNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVendorURLNameKey
    @abstract   The name specifier for the vendor url name.
*/
extern const CFStringRef kCTFontVendorURLNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontDesignerURLNameKey
    @abstract   The name specifier for the designer url name.
*/
extern const CFStringRef kCTFontDesignerURLNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontLicenseNameKey
    @abstract   The name specifier for the license name.
*/
extern const CFStringRef kCTFontLicenseNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontLicenseURLNameKey
    @abstract   The name specifier for the license url name.
*/
extern const CFStringRef kCTFontLicenseURLNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontSampleTextNameKey
    @abstract   The name specifier for the sample text name string.
*/
extern const CFStringRef kCTFontSampleTextNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontPostScriptCIDNameKey
    @abstract   The name specifier for the Postscript CID name.
*/
extern const CFStringRef kCTFontPostScriptCIDNameKey CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCreateWithName
    @abstract   Returns a new font reference for the given name.

    @param      name
                The font name for which you wish to create a new font reference. A valid PostScript name is preferred, although other font name types will be matched in a fallback manner.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @result     This function will return a CTFontRef that best matches the name provided with size and matrix attributes. The name parameter is the only required parameters, and default values will be used for unspecified parameters. A best match will be found if all parameters cannot be matched identically.
*/
CTFontRef CTFontCreateWithName(
    CFStringRef __nullable      name,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateWithFontDescriptor
    @abstract   Returns a new font reference that best matches the font descriptor.

    @param      descriptor
                A font descriptor containing attributes that specify the requested font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @result     This function will return a CTFontRef that best matches the attributes provided with the font descriptor. The size and matrix parameters will override any specified in the font descriptor, unless they are unspecified. A best match font will always be returned, and default values will be used for any unspecified.
*/
CTFontRef CTFontCreateWithFontDescriptor(
    CTFontDescriptorRef     descriptor,
    CGFloat                 size,
    const CGAffineTransform * __nullable matrix ) CT_AVAILABLE(10_5, 3_2);

/*!
    @enum       CTFontOptions
    @abstract   Options for descriptor match and font creation.
    @constant   kCTFontOptionsPreventAutoActivation
                Prevents automatic font activation from taking place.
    @constant   kCTFontOptionsPreferSystemFont
                Font matching will prefer to match Apple system fonts.
*/
typedef CF_OPTIONS(CFOptionFlags, CTFontOptions) {
    kCTFontOptionsDefault               = 0,
    kCTFontOptionsPreventAutoActivation = 1 << 0,
    kCTFontOptionsPreferSystemFont      = 1 << 2
};


/*!
    @function   CTFontCreateWithNameAndOptions
    @abstract   Returns a new font reference for the given name.

    @param      name
                The font name for which you wish to create a new font reference. A valid PostScript name is preferred, although other font name types will be matched in a fallback manner.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.
                
    @param      options
                Options flags.

    @result     This function will return a CTFontRef that best matches the name provided with size and matrix attributes. The name parameter is the only required parameters, and default values will be used for unspecified parameters. A best match will be found if all parameters cannot be matched identically.
*/
CTFontRef CTFontCreateWithNameAndOptions(
    CFStringRef                 name,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CTFontOptions               options ) CT_AVAILABLE(10_6, 3_2);

/*!
    @function   CTFontCreateWithFontDescriptorAndOptions
    @abstract   Returns a new font reference that best matches the font descriptor.

    @param      descriptor
                A font descriptor containing attributes that specify the requested font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      options
                Options flags.

    @result     This function will return a CTFontRef that best matches the attributes provided with the font descriptor. The size and matrix parameters will override any specified in the font descriptor, unless they are unspecified. A best match font will always be returned, and default values will be used for any unspecified.
*/
CTFontRef CTFontCreateWithFontDescriptorAndOptions(
    CTFontDescriptorRef     descriptor,
    CGFloat                 size,
    const CGAffineTransform * __nullable matrix,
    CTFontOptions           options ) CT_AVAILABLE(10_6, 3_2);

/*!
    @enum       UI Type constants
    @abstract   These constants represent the specific user interface purpose to specify for font creation.
    @discussion Use these constants with CTFontCreateUIFontForLanguage to indicate the intended user interface usage of the font reference to be created.
*/
typedef CF_ENUM(uint32_t, CTFontUIFontType) {
    kCTFontUIFontNone                   CT_ENUM_AVAILABLE(10_8, 6_0) = (uint32_t)-1,
    kCTFontUIFontUser                   CT_ENUM_AVAILABLE(10_8, 6_0) =  0,
    kCTFontUIFontUserFixedPitch         CT_ENUM_AVAILABLE(10_8, 6_0) =  1,
    kCTFontUIFontSystem                 CT_ENUM_AVAILABLE(10_8, 6_0) =  2,
    kCTFontUIFontEmphasizedSystem       CT_ENUM_AVAILABLE(10_8, 6_0) =  3,
    kCTFontUIFontSmallSystem            CT_ENUM_AVAILABLE(10_8, 6_0) =  4,
    kCTFontUIFontSmallEmphasizedSystem  CT_ENUM_AVAILABLE(10_8, 6_0) =  5,
    kCTFontUIFontMiniSystem             CT_ENUM_AVAILABLE(10_8, 6_0) =  6,
    kCTFontUIFontMiniEmphasizedSystem   CT_ENUM_AVAILABLE(10_8, 6_0) =  7,
    kCTFontUIFontViews                  CT_ENUM_AVAILABLE(10_8, 6_0) =  8,
    kCTFontUIFontApplication            CT_ENUM_AVAILABLE(10_8, 6_0) =  9,
    kCTFontUIFontLabel                  CT_ENUM_AVAILABLE(10_8, 6_0) = 10,
    kCTFontUIFontMenuTitle              CT_ENUM_AVAILABLE(10_8, 6_0) = 11,
    kCTFontUIFontMenuItem               CT_ENUM_AVAILABLE(10_8, 6_0) = 12,
    kCTFontUIFontMenuItemMark           CT_ENUM_AVAILABLE(10_8, 6_0) = 13,
    kCTFontUIFontMenuItemCmdKey         CT_ENUM_AVAILABLE(10_8, 6_0) = 14,
    kCTFontUIFontWindowTitle            CT_ENUM_AVAILABLE(10_8, 6_0) = 15,
    kCTFontUIFontPushButton             CT_ENUM_AVAILABLE(10_8, 6_0) = 16,
    kCTFontUIFontUtilityWindowTitle     CT_ENUM_AVAILABLE(10_8, 6_0) = 17,
    kCTFontUIFontAlertHeader            CT_ENUM_AVAILABLE(10_8, 6_0) = 18,
    kCTFontUIFontSystemDetail           CT_ENUM_AVAILABLE(10_8, 6_0) = 19,
    kCTFontUIFontEmphasizedSystemDetail CT_ENUM_AVAILABLE(10_8, 6_0) = 20,
    kCTFontUIFontToolbar                CT_ENUM_AVAILABLE(10_8, 6_0) = 21,
    kCTFontUIFontSmallToolbar           CT_ENUM_AVAILABLE(10_8, 6_0) = 22,
    kCTFontUIFontMessage                CT_ENUM_AVAILABLE(10_8, 6_0) = 23,
    kCTFontUIFontPalette                CT_ENUM_AVAILABLE(10_8, 6_0) = 24,
    kCTFontUIFontToolTip                CT_ENUM_AVAILABLE(10_8, 6_0) = 25,
    kCTFontUIFontControlContent         CT_ENUM_AVAILABLE(10_8, 6_0) = 26,

    kCTFontNoFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontNone,
    kCTFontUserFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontUser,
    kCTFontUserFixedPitchFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontUserFixedPitch,
    kCTFontSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontSystem,
    kCTFontEmphasizedSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontEmphasizedSystem,
    kCTFontSmallSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontSmallSystem,
    kCTFontSmallEmphasizedSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontSmallEmphasizedSystem,
    kCTFontMiniSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMiniSystem,
    kCTFontMiniEmphasizedSystemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMiniEmphasizedSystem,
    kCTFontViewsFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontViews,
    kCTFontApplicationFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontApplication,
    kCTFontLabelFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontLabel,
    kCTFontMenuTitleFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMenuTitle,
    kCTFontMenuItemFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMenuItem,
    kCTFontMenuItemMarkFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMenuItemMark,
    kCTFontMenuItemCmdKeyFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMenuItemCmdKey,
    kCTFontWindowTitleFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontWindowTitle,
    kCTFontPushButtonFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontPushButton,
    kCTFontUtilityWindowTitleFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontUtilityWindowTitle,
    kCTFontAlertHeaderFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontAlertHeader,
    kCTFontSystemDetailFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontSystemDetail,
    kCTFontEmphasizedSystemDetailFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontEmphasizedSystemDetail,
    kCTFontToolbarFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontToolbar,
    kCTFontSmallToolbarFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontSmallToolbar,
    kCTFontMessageFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontMessage,
    kCTFontPaletteFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontPalette,
    kCTFontToolTipFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontToolTip,
    kCTFontControlContentFontType CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontUIFontControlContent
};

/*!
    @function   CTFontCreateUIFontForLanguage
    @abstract   Returns the special UI font for the given language and UI type.

    @param      uiType
                A uiType constant specifying the intended UI use for the requested font reference.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default size for the requested uiType is used.

    @param      language
                Language identifier to select a font for a particular localization. If unspecified, the current system language is used. The format of the language identifier should conform to UTS #35.

    @result     This function returns the correct font for various UI uses. The only required parameter is the uiType selector, unspecified optional parameters will use default values.
*/
CTFontRef __nullable CTFontCreateUIFontForLanguage(
    CTFontUIFontType    uiType,
    CGFloat             size,
    CFStringRef __nullable language ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateCopyWithAttributes
    @abstract   Returns a new font with additional attributes based on the original font.

    @discussion This function provides a mechanism to quickly change attributes on a given font reference in response to user actions. For instance, the size can be changed in response to a user manipulating a size slider.

    @param      font
                Original font reference to base new font on.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      attributes
                A font descriptor containing additional attributes that the new font should contain.

    @result     Returns a new font reference converted from the original with the specified attributes.
*/
CTFontRef CTFontCreateCopyWithAttributes(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CTFontDescriptorRef __nullable attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateCopyWithSymbolicTraits
    @abstract   Returns a new font based on the original font with the specified symbolic traits.

    @param      font
                Original font reference on which to base the new font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      symTraitValue
                The value of the symbolic traits. This bitfield is used to indicate the desired value for the traits specified by the symTraitMask parameter. Used in conjunction, they can allow for trait removal as well as addition.

    @param      symTraitMask
                The mask bits of the symbolic traits. This bitfield is used to indicate the traits that should be changed.

    @result     Returns a new font reference in the same family with the given symbolic traits, or NULL if none found in the system.
*/
CTFontRef __nullable CTFontCreateCopyWithSymbolicTraits(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CTFontSymbolicTraits        symTraitValue,
    CTFontSymbolicTraits        symTraitMask ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateCopyWithFamily
    @abstract   Returns a new font in the specified family based on the traits of the original font.

    @param      font
                Original font reference to base new font on.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      family
                The name of the desired family.

    @result     Returns a new font reference with the original traits in the given family. NULL if non found in the system.
*/
CTFontRef __nullable CTFontCreateCopyWithFamily(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CFStringRef                 family ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Cascading
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCreateForString
    @abstract   Returns a new font reference that can best map the given string range based on the current font.

    @discussion This function is to be used when the current font does not cover the given range of the string. The current font itself will not be returned, but preference is given to fonts in its cascade list.

    @param      currentFont
                The current font that contains a valid cascade list.

    @param      string
                A unicode string containing characters that cannot be encoded by the current font.

    @param      range
                A CFRange specifying the range of the string that needs to be mapped.

    @result     This function returns the best substitute font that can encode the specified string range.

    @seealso    CTFontCopyCharacterSet
    @seealso    CTFontGetGlyphsForCharacters
    @seealso    kCTFontCascadeListAttribute
*/
CTFontRef CTFontCreateForString(
    CTFontRef       currentFont,
    CFStringRef     string,
    CFRange         range ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Accessors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyFontDescriptor
    @abstract   Returns the normalized font descriptors for the given font reference.

    @param      font
                The font reference.

    @result     This function returns a normalized font descriptor for a font. The font descriptor contains enough information to recreate this font at a later time.
*/
CTFontDescriptorRef CTFontCopyFontDescriptor(
    CTFontRef       font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyAttribute
    @abstract   Returns the value associated with an arbitrary attribute.

    @param      font
                The font reference.

    @param      attribute
                The requested attribute.

    @result     This function returns a retained reference to an arbitrary attribute. If the requested attribute is not present, NULL is returned. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef __nullable CTFontCopyAttribute(
    CTFontRef       font,
    CFStringRef     attribute ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetSize
    @abstract   Returns the point size of the font reference.

    @param      font
                The font reference.

    @result     This function returns the point size of the given font reference. This is the point size provided when the font was created.
*/
CGFloat CTFontGetSize( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetMatrix
    @abstract   Returns the transformation matrix of the font.

    @param      font
                The font reference.

    @result     This function returns the transformation matrix for this given font reference. This is the matrix that was provided when the font was created.
*/
CGAffineTransform CTFontGetMatrix( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetSymbolicTraits
    @abstract   Returns the symbolic font traits.

    @param      font
                The font reference.

    @result     This function returns the symbolic traits of the font. This is equivalent to the kCTFontSymbolicTrait of traits dictionary. See CTFontTraits.h for a definition of the font traits.
*/
CTFontSymbolicTraits CTFontGetSymbolicTraits( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyTraits
    @abstract   Returns the font traits dictionary.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the font traits dictionary. Individual traits can be accessed with the trait key constants. See CTFontTraits.h for a definition of the font traits.
*/
CFDictionaryRef CTFontCopyTraits( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Names
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyPostScriptName
    @abstract   Returns the PostScript name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the PostScript name of the font.
*/
CFStringRef CTFontCopyPostScriptName( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyFamilyName
    @abstract   Returns the family name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the family name of the font.
*/
CFStringRef CTFontCopyFamilyName( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyFullName
    @abstract   Returns the display name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the full name of the font.
*/
CFStringRef CTFontCopyFullName( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyDisplayName
    @abstract   Returns the display name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the localized display name of the font.
*/
CFStringRef CTFontCopyDisplayName( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyName
    @abstract   Returns a reference to the requested name.

    @param      font
                The font reference.

    @param      nameKey
                The name specifier. See name specifier constants.

    @result     This function creates the requested name for the font, or NULL if the font does not have an entry for the requested name. The Unicode version of the name will be preferred, otherwise the first available will be used.
*/
CFStringRef __nullable CTFontCopyName(
    CTFontRef       font,
    CFStringRef     nameKey ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyLocalizedName
    @abstract   Returns a reference to a localized font name.

    @param      font
                The font reference.

    @param      nameKey
                The name specifier. See name specifier constants.

    @param      actualLanguage
                Pointer to a CFStringRef to receive the language identifier of the returned name string. The format of the language identifier will conform to UTS #35.
                If CoreText can supply its own localized string where the font cannot, this value will be NULL.

    @result     This function returns a specific localized name from the font reference. The name is localized based on the user's global language precedence. If the font does not have an entry for the requested name, NULL will be returned. The matched language will be returned in the caller's buffer.
*/
CFStringRef __nullable CTFontCopyLocalizedName(
    CTFontRef       font,
    CFStringRef     nameKey,
    CFStringRef __nullable * __nullable actualLanguage ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Encoding
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyCharacterSet
    @abstract   Returns the Unicode character set of the font.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the font's character set. This character set covers the nominal referenced by the font's Unicode cmap table (or equivalent).
*/
CFCharacterSetRef CTFontCopyCharacterSet( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetStringEncoding
    @abstract   Returns the best string encoding for legacy format support.

    @param      font
                The font reference.

    @result     This function returns the best string encoding for the font.
*/
CFStringEncoding CTFontGetStringEncoding( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopySupportedLanguages
    @abstract   Returns an array of languages supported by the font.

    @param      font
                The font reference.

    @result     This function returns a retained reference to an array of languages supported by the font. The array contains language identifier strings as CFStringRefs. The format of the language identifier will conform to UTS #35.
*/
CFArrayRef CTFontCopySupportedLanguages( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetGlyphsForCharacters
    @abstract   Performs basic character-to-glyph mapping.

    @discussion This function only provides the nominal mapping as specified by the font's Unicode cmap (or equivalent); such mapping does not constitute proper Unicode layout: it is the caller's responsibility to handle the Unicode properties of the characters.

    @param      font
                The font reference.

    @param      characters
                An array of characters (UTF-16 code units). Non-BMP characters must be encoded as surrogate pairs.

    @param      glyphs
                A pointer to a buffer to receive the glyphs. Glyphs for non-BMP characters are sparse: the first glyph corresponds to the full character and the second glyph will be 0.

    @param      count
                The capacity of both the characters and glyphs arrays.

    @result     The return value indicates whether all provided characters were successfully mapped. A return value of true indicates that the font mapped all characters. A return value of false indicates that some or all of the characters were not mapped; glyphs for unmapped characters will be 0 (with the exception of those corresponding non-BMP characters as described above).

    @seealso    CTFontCopyCharacterSet
*/
bool CTFontGetGlyphsForCharacters(
    CTFontRef       font,
    const UniChar   characters[],
    CGGlyph         glyphs[],
    CFIndex         count ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Metrics
*///--------------------------------------------------------------------------

/*!
    @function   CTFontGetAscent
    @abstract   Returns the scaled font ascent metric.

    @param      font
                The font reference.

    @result     This function returns the font ascent metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetAscent( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetDescent
    @abstract   Returns the scaled font descent metric.

    @param      font
                The font reference.

    @result     This function returns the font descent metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetDescent( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetLeading
    @abstract   Returns the scaled font leading metric.

    @param      font
                The font reference.

    @result     This function returns the font leading metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetLeading( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetUnitsPerEm
    @abstract   Returns the units per em metric.

    @param      font
                The font reference.

    @result     This function returns the units per em of the font.
*/
unsigned CTFontGetUnitsPerEm( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetGlyphCount
    @abstract   Returns the number of glyphs.

    @param      font
                The font reference.

    @result     This function returns the number of glyphs in the font.
*/
CFIndex CTFontGetGlyphCount( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetBoundingBox
    @abstract   Returns the scaled bounding box.

    @param      font
                The font reference.

    @result     This will return the design bounding box of the font, which is the rectangle defined by xMin, yMin, xMax, and yMax values for the font.
*/
CGRect CTFontGetBoundingBox( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetUnderlinePosition
    @abstract   Returns the scaled underline position.

    @param      font
                The font reference.

    @result     This function returns the font underline position metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetUnderlinePosition( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetUnderlineThickness
    @abstract   Returns the scaled underline thickness metric.

    @param      font
                The font reference.

    @result     This function returns the font underline thickness metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetUnderlineThickness( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetSlantAngle
    @abstract   Returns the slant angle of the font.

    @param      font
                The font reference.

    @result     This function returns the transformed slant angle of the font. This is equivalent to the italic or caret angle with any skew from the transformation matrix applied.
*/
CGFloat CTFontGetSlantAngle( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetCapHeight
    @abstract   Returns the cap height metric.

    @param      font
                The font reference.

    @result     This function returns the font cap height metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetCapHeight( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetXHeight
    @abstract   Returns the X height metric.

    @param      font
                The font reference.

    @result     This function returns the font X height metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetXHeight( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Glyphs
*///--------------------------------------------------------------------------

/*!
    @function   CTFontGetGlyphWithName
    @abstract   Returns the CGGlyph for the specified glyph name.

    @param      font
                The font reference.

    @param      glyphName
                The glyph name as a CFString.

    @result     The glyph with the specified name or 0 if the name is not recognized; this glyph can be used with other Core Text glyph data accessors or with Quartz.
*/
CGGlyph CTFontGetGlyphWithName(
    CTFontRef           font,
    CFStringRef         glyphName ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetBoundingRectsForGlyphs
    @abstract   Calculates the bounding rects for an array of glyphs and returns the overall bounding rect for the run.

    @param      font
                The font reference.

    @param      orientation
                The intended drawing orientation of the glyphs. Used to determined which glyph metrics to return.

    @param      glyphs
                An array of count number of glyphs.

    @param      boundingRects
                An array of count number of CGRects to receive the computed glyph rects. Can be NULL, in which case only the overall bounding rect is calculated.

    @param      count
                The capacity of the glyphs and boundingRects buffers.

    @result     This function returns the overall bounding rectangle for an array or run of glyphs. The bounding rects of the individual glyphs are returned through the boundingRects parameter. These are the design metrics from the font transformed in font space.
*/
CGRect CTFontGetBoundingRectsForGlyphs(
    CTFontRef           font,
    CTFontOrientation   orientation,
    const CGGlyph       glyphs[],
    CGRect * __nullable boundingRects,
    CFIndex             count ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetOpticalBoundsForGlyphs
    @abstract   Calculates the optical bounding rects for an array of glyphs and returns the overall optical bounding rect for the run.

    @discussion Fonts may specify the optical edges of glyphs that can be used to make the edges of lines of text line up in a more visually pleasing way. This function returns bounding rects corresponding to this information if present in a font, otherwise it returns typographic bounding rects (composed of the font's ascent and descent and a glyph's advance width).

    @param      font
                The font reference.

    @param      glyphs
                An array of count number of glyphs.

    @param      boundingRects
                An array of count number of CGRects to receive the computed glyph rects. Can be NULL, in which case only the overall bounding rect is calculated.

    @param      count
                The capacity of the glyphs and boundingRects buffers.

    @param      options
                Reserved, set to zero.

    @result     This function returns the overall bounding rectangle for an array or run of glyphs. The bounding rects of the individual glyphs are returned through the boundingRects parameter. These are the design metrics from the font transformed in font space.
*/
CGRect CTFontGetOpticalBoundsForGlyphs(
    CTFontRef           font,
    const CGGlyph       glyphs[],
    CGRect * __nullable boundingRects,
    CFIndex             count,
    CFOptionFlags       options ) CT_AVAILABLE(10_8, 6_0);

/*!
    @function   CTFontGetAdvancesForGlyphs
    @abstract   Calculates the advances for an array of glyphs and returns the summed advance.

    @param      font
                The font reference.

    @param      orientation
                The intended drawing orientation of the glyphs. Used to determined which glyph metrics to return.

    @param      glyphs
                An array of count number of glyphs.

    @param      advances
                An array of count number of CGSize to receive the computed glyph advances. Can be NULL, in which case only the overall advance is calculated.

    @param      count
                The capacity of the glyphs and advances buffers.

    @result     This function returns the summed glyph advance of an array of glyphs. Individual glyph advances are passed back via the advances parameter. These are the ideal metrics for each glyph scaled and transformed in font space.
*/
double CTFontGetAdvancesForGlyphs(
    CTFontRef           font,
    CTFontOrientation   orientation,
    const CGGlyph       glyphs[],
    CGSize * __nullable advances,
    CFIndex             count ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontGetVerticalTranslationsForGlyphs
    @abstract   Calculates the offset from the default (horizontal) origin to the vertical origin for an array of glyphs.

    @param      font
                The font reference.

    @param      glyphs
                An array of count number of glyphs.

    @param      translations
                An array of count number of CGSize to receive the computed origin offsets.

    @param      count
                The capacity of the glyphs and translations buffers.
*/
void CTFontGetVerticalTranslationsForGlyphs(
    CTFontRef       font,
    const CGGlyph   glyphs[],
    CGSize          translations[],
    CFIndex         count ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreatePathForGlyph
    @abstract   Creates a path for the specified glyph.

    @discussion Creates a path from the outlines of the glyph for the specified font. The path will reflect the font point size, matrix, and transform parameter, in that order. The transform parameter will most commonly be used to provide a translation to the desired glyph origin.

    @param      font
                The font reference.

    @param      glyph
                The glyph.

    @param      transform
                An affine transform applied to the path. Can be NULL, in which case CGAffineTransformIdentity will be used.

    @result     A retained CGPath reference containing the glyph outlines or NULL if there is no such glyph or it has no outline.
*/
CGPathRef __nullable CTFontCreatePathForGlyph(
    CTFontRef                   font,
    CGGlyph                     glyph,
    const CGAffineTransform * __nullable matrix ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Variations        (this functionality is not supported on iOS)
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontVariationAxisIdentifierKey
    @abstract   Key to get the variation axis identifier.
    @discussion This key is used with a variation axis dictionary to get the axis identifier value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisIdentifierKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAxisMinimumValueKey
    @abstract   Key to get the variation axis minimum value.
    @discussion This key is used with a variation axis dictionary to get the minimum axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisMinimumValueKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAxisMaximumValueKey
    @abstract   Key to get the variation axis maximum value.
    @discussion This key is used with a variation axis dictionary to get the maximum axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisMaximumValueKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAxisDefaultValueKey
    @abstract   Key to get the variation axis default value.
    @discussion This key is used with a variation axis dictionary to get the default axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisDefaultValueKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAxisNameKey
    @abstract   Key to get the variation axis name string.
    @discussion This key is used with a variation axis dictionary to get the localized variation axis name.
*/
extern const CFStringRef kCTFontVariationAxisNameKey CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyVariationAxes
    @abstract   Returns an array of variation axes.

    @param      font
                The font reference.

    @result     This function returns an array of variation axis dictionaries. Each variation axis dictionary contains the five variation axis keys above.
*/
CFArrayRef __nullable CTFontCopyVariationAxes( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyVariation
    @abstract   Returns a variation dictionary from the font reference.

    @param      font
                The font reference.

    @result     This function returns the current variation instance as a dictionary. The keys for each variation correspond to the variation identifier obtained via kCTFontVariationAxisIdentifierKey which represents the axis' four character code as a CFNumber.
*/
CFDictionaryRef __nullable CTFontCopyVariation( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Features
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontOpenTypeFeatureTag
    @abstract   Key to get the OpenType feature tag.
    @discussion This key can be used with a font feature dictionary to get the tag as a CFStringRef.
*/
extern const CFStringRef kCTFontOpenTypeFeatureTag CT_AVAILABLE(10_10, 8_0);
/*!
    @defined    kCTFontOpenTypeFeatureValue
    @abstract   Key to get the OpenType feature value.
    @discussion This key can be used with a font feature dictionary to get the value as a CFNumberRef.
*/
extern const CFStringRef kCTFontOpenTypeFeatureValue CT_AVAILABLE(10_10, 8_0);
/*!
    @defined    kCTFontFeatureTypeIdentifierKey
    @abstract   Key to get the font feature type value.
    @discussion This key can be used with a font feature dictionary to get the type identifier as a CFNumberRef.
*/
extern const CFStringRef kCTFontFeatureTypeIdentifierKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureTypeNameKey
    @abstract   Key to get the font feature name.
    @discussion This key can be used with a font feature dictionary to get the localized type name string as a CFString.
*/
extern const CFStringRef kCTFontFeatureTypeNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureTypeExclusiveKey
    @abstract   Key to get the font feature exclusive setting.
    @discussion This key can be used with a font feature dictionary to get the the exclusive setting of the feature as a CFBoolean. The value associated with this key indicates whether the feature selectors associated with this type should be mutually exclusive.
*/
extern const CFStringRef kCTFontFeatureTypeExclusiveKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureTypeSelectorsKey
    @abstract   Key to get the font feature selectors.
    @discussion This key can be used with a font feature dictionary to get the array of font feature selectors as a CFArrayRef. This is an array of selector dictionaries that contain the values for the following selector keys.
*/
extern const CFStringRef kCTFontFeatureTypeSelectorsKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSelectorIdentifierKey
    @abstract   Key to get the font feature selector identifier.
    @discussion This key can be used with a selector dictionary corresponding to a feature type to obtain the selector identifier value as a CFNumberRef.
*/
extern const CFStringRef kCTFontFeatureSelectorIdentifierKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSelectorNameKey
    @abstract   Key to get the font feature selector name.
    @discussion This key is used with a selector dictionary to get the localized name string for the selector as a CFStringRef.
*/
extern const CFStringRef kCTFontFeatureSelectorNameKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSelectorDefaultKey
    @abstract   Key to get the font feature selector default setting value.
    @discussion This key is used with a selector dictionary to get the default indicator for the selector. This value is a CFBooleanRef which if present and true indicates that this selector is the default setting for the current feature type.
*/
extern const CFStringRef kCTFontFeatureSelectorDefaultKey CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSelectorSettingKey
    @abstract   Key to get or specify the current feature setting.
    @discussion This key is used with a selector dictionary to get or specify the current setting for the selector. This value is a CFBooleanRef to indicate whether this selector is on or off. If this key is not present, the default setting is used.
*/
extern const CFStringRef kCTFontFeatureSelectorSettingKey CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyFeatures
    @abstract   Returns an array of font features

    @param      font
                The font reference.

    @result     This function returns an array of font feature dictionaries for the font reference.
*/
CFArrayRef __nullable CTFontCopyFeatures( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyFeatureSettings
    @abstract   Returns an array of font feature setting tuples

    @discussion A setting tuple is a dictionary of a kCTFontFeatureTypeIdentifierKey key-value pair and a kCTFontFeatureSelectorIdentifierKey key-value pair. Each tuple corresponds to an enabled non-default setting. It is the caller's responsibility to handle exclusive and non-exclusive settings as necessary.

    @param      font
                The font reference.

    @result     This function returns a normalized array of font feature setting dictionaries. The array will only contain the non-default settings that should be applied to the font, or NULL if the default settings should be used.
*/
CFArrayRef __nullable CTFontCopyFeatureSettings( CTFontRef font ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Font Conversion
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyGraphicsFont
    @abstract   Returns a CGFontRef and attributes.

    @param      font
                The font reference.

    @param      attributes
                A pointer to a CTFontDescriptorRef to receive a font descriptor containing additional attributes. Can be NULL. Must be released by caller.

    @result     This function returns a CGFontRef for the given font reference. Additional attributes from the font will be passed back as a font descriptor via the attributes parameter. The result must be released by the caller.
*/
CGFontRef CTFontCopyGraphicsFont(
    CTFontRef           font,
    CTFontDescriptorRef __nullable * __nullable attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateWithGraphicsFont
    @abstract   Creates a new font reference from a CGFontRef.

    @param      graphicsFont
                A valid CGFontRef.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      attributes
                A CTFontDescriptorRef containing additional attributes that should be matched. Optional.

    @result     This function returns a new font reference for an existing CGFontRef with the specified size, matrix, and additional attributes.
*/
CTFontRef CTFontCreateWithGraphicsFont(
    CGFontRef                   graphicsFont,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CTFontDescriptorRef __nullable attributes ) CT_AVAILABLE(10_5, 3_2);

#ifndef ATSFONTREF_DEFINED
typedef UInt32 ATSFontRef;
#define ATSFONTREF_DEFINED 1
#endif

/*!
    @function   CTFontGetPlatformFont
    @abstract   Returns the ATSFontRef and attributes.

    @param      font
                The font reference.

    @param      attributes
                A pointer to a CTFontDescriptorRef to receive a font descriptor containing additional attributes. Can be NULL. Must be released by caller.

    @result     This function returns a an ATSFontRef for the given font reference. Additional attributes from the font will be passed back as a font descriptor via the attributes parameter.
*/

ATSFontRef CTFontGetPlatformFont(
    CTFontRef               font,
    CTFontDescriptorRef __nullable * __nullable attributes ) CT_AVAILABLE_MAC(10_5);

/*!
    @function   CTFontCreateWithPlatformFont
    @abstract   Creates a new font reference from an ATSFontRef.

    @param      platformFont
                A valid ATSFontRef.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      attributes
                A CTFontDescriptorRef containing additional attributes that should be matched. Optional.

    @result     This function returns a new font reference for an ATSFontRef with the specified size, matrix, and additional attributes.
*/
CTFontRef __nullable CTFontCreateWithPlatformFont(
    ATSFontRef                  platformFont,
    CGFloat                     size,
    const CGAffineTransform * __nullable matrix,
    CTFontDescriptorRef __nullable attributes ) CT_AVAILABLE_MAC(10_5);

/*!
    @function   CTFontCreateWithQuickdrawInstance
    @abstract   Returns a font reference for the given Quickdraw instance.

    @discussion This function is provided for compatibility support between Core Text and clients needing to support Quickdraw font references.

    @param      name
                The Quickdraw font name. If NULL or zero length, an identifier must be specified instead.

    @param      identifier
                The Quickdraw font identifier. If 0, a name must be specified instead.

    @param      style
                The Quickdraw font style.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default size of 12.0 is used.

    @result     This function returns the best font instance matching the Quickdraw instance information.
*/
CTFontRef CTFontCreateWithQuickdrawInstance(
    ConstStr255Param __nullable name,
    int16_t             identifier,
    uint8_t             style,
    CGFloat             size ) CT_AVAILABLE_MAC(10_5);

/*! --------------------------------------------------------------------------
    @group Font Tables
*///--------------------------------------------------------------------------

enum {
    kCTFontTableBASE    = 'BASE',   // Baseline
    kCTFontTableCFF     = 'CFF ',   // PostScript font program
    kCTFontTableDSIG    = 'DSIG',   // Digital signature
    kCTFontTableEBDT    = 'EBDT',   // Embedded bitmap
    kCTFontTableEBLC    = 'EBLC',   // Embedded bitmap location
    kCTFontTableEBSC    = 'EBSC',   // Embedded bitmap scaling
    kCTFontTableGDEF    = 'GDEF',   // Glyph definition
    kCTFontTableGPOS    = 'GPOS',   // Glyph positioning
    kCTFontTableGSUB    = 'GSUB',   // Glyph substitution
    kCTFontTableJSTF    = 'JSTF',   // Justification
    kCTFontTableLTSH    = 'LTSH',   // Linear threshold
    kCTFontTableMATH    = 'MATH',   // Math
    kCTFontTableOS2     = 'OS/2',   // OS/2 and Windows specific metrics
    kCTFontTablePCLT    = 'PCLT',   // PCL 5 data
    kCTFontTableVDMX    = 'VDMX',   // Vertical device metrics
    kCTFontTableVORG    = 'VORG',   // Vertical origin
    kCTFontTableZapf    = 'Zapf',   // Glyph reference
    kCTFontTableAcnt    = 'acnt',   // Accent attachment
    kCTFontTableAnkr    = 'ankr',   // Anchor points
    kCTFontTableAvar    = 'avar',   // Axis variation
    kCTFontTableBdat    = 'bdat',   // Bitmap data
    kCTFontTableBhed    = 'bhed',   // Bitmap font header
    kCTFontTableBloc    = 'bloc',   // Bitmap location
    kCTFontTableBsln    = 'bsln',   // Baseline
    kCTFontTableCmap    = 'cmap',   // Character to glyph mapping
    kCTFontTableCvar    = 'cvar',   // CVT variation
    kCTFontTableCvt     = 'cvt ',   // Control value table
    kCTFontTableFdsc    = 'fdsc',   // Font descriptor
    kCTFontTableFeat    = 'feat',   // Layout feature
    kCTFontTableFmtx    = 'fmtx',   // Font metrics
    kCTFontTableFpgm    = 'fpgm',   // Font program
    kCTFontTableFvar    = 'fvar',   // Font variation
    kCTFontTableGasp    = 'gasp',   // Grid-fitting/Scan-conversion
    kCTFontTableGlyf    = 'glyf',   // Glyph data
    kCTFontTableGvar    = 'gvar',   // Glyph variation
    kCTFontTableHdmx    = 'hdmx',   // Horizontal device metrics
    kCTFontTableHead    = 'head',   // Font header
    kCTFontTableHhea    = 'hhea',   // Horizontal header
    kCTFontTableHmtx    = 'hmtx',   // Horizontal metrics
    kCTFontTableHsty    = 'hsty',   // Horizontal style
    kCTFontTableJust    = 'just',   // Justification
    kCTFontTableKern    = 'kern',   // Kerning
    kCTFontTableKerx    = 'kerx',   // Extended kerning
    kCTFontTableLcar    = 'lcar',   // Ligature caret
    kCTFontTableLtag    = 'ltag',   // Language tags
    kCTFontTableLoca    = 'loca',   // Index to location
    kCTFontTableMaxp    = 'maxp',   // Maximum profile
    kCTFontTableMort    = 'mort',   // Morph
    kCTFontTableMorx    = 'morx',   // Extended morph
    kCTFontTableName    = 'name',   // Naming table
    kCTFontTableOpbd    = 'opbd',   // Optical bounds
    kCTFontTablePost    = 'post',   // PostScript information
    kCTFontTablePrep    = 'prep',   // CVT program
    kCTFontTableProp    = 'prop',   // Properties
    kCTFontTableSbit    = 'sbit',   // Bitmap data
    kCTFontTableSbix    = 'sbix',   // Extended bitmap data
    kCTFontTableTrak    = 'trak',   // Tracking
    kCTFontTableVhea    = 'vhea',   // Vertical header
    kCTFontTableVmtx    = 'vmtx'    // Vertical metrics
};
typedef FourCharCode CTFontTableTag;

typedef CF_OPTIONS(uint32_t, CTFontTableOptions) {
    kCTFontTableOptionNoOptions CT_ENUM_AVAILABLE(10_5, 3_2) = 0,
    kCTFontTableOptionExcludeSynthetic CT_ENUM_DEPRECATED(10_5, 10_8, 3_2, 6_0) = (1 << 0)
};

/*!
    @function   CTFontCopyAvailableTables
    @abstract   Returns an array of font table tags.

    @param      font
                The font reference.

    @param      options

    @result     This function returns an array of CTFontTableTag values for the given font and the supplied options. The returned set will contain unboxed values, which may be extracted like so:
                <code>CTFontTableTag tag = (CTFontTableTag)(uintptr_t)CFArrayGetValueAtIndex(tags, index);</code>
*/
CFArrayRef __nullable CTFontCopyAvailableTables(
    CTFontRef           font,
    CTFontTableOptions  options ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCopyTable
    @abstract   Returns a reference to the font table data.

    @param      font
                The font reference.

    @param      table
                The font table identifier as a CTFontTableTag.

    @param      options

    @result     This function returns a retained reference to the font table data as CFDataRef or NULL if the table is not present.
*/
CFDataRef __nullable CTFontCopyTable(
    CTFontRef           font,
    CTFontTableTag      table,
    CTFontTableOptions  options ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTFontDrawGlyphs
    @abstract   Renders the given glyphs from the CTFont at the given positions in the CGContext.
    @discussion This function will modify the CGContext's font, text size, and text matrix if specified in the CTFont. These attributes will not be restored.
        The given glyphs should be the result of proper Unicode text layout operations (such as CTLine). Results from CTFontGetGlyphsForCharacters (or similar APIs) do not perform any Unicode text layout.

    @param      font
                The font to render glyphs from. If the font has a size or matrix attribute, the CGContext will be set with these values.

    @param      glyphs
                The glyphs to be rendered. See above discussion of how the glyphs should be derived.

    @param      positions
                The positions (origins) for each glyph. The positions are in user space. The number of positions passed in must be equivalent to the number of glyphs.

    @param      count
                The number of glyphs to be rendered from the glyphs array.

    @param      context
                CGContext used to render the glyphs.

    @result     void
*/
void CTFontDrawGlyphs(
    CTFontRef       font, 
    const CGGlyph   glyphs[], 
    const CGPoint   positions[], 
    size_t          count, 
    CGContextRef    context ) CT_AVAILABLE(10_7, 4_2);


/*!
    @function   CTFontGetLigatureCaretPositions
    @abstract   Returns caret positions within a glyph.
    @discussion This function is used to obtain caret positions for a specific glyph.
                The return value is the max number of positions possible, and the function
                will populate the caller's positions buffer with available positions if possible.
                This function may not be able to produce positions if the font does not
                have the appropriate data, in which case it will return 0.
 
    @param      font
                The font reference.
    
    @param      glyph
                The glyph.
 
    @param      positions
                A buffer of at least maxPositions to receive the ligature caret positions for
                the glyph.
 
    @param      maxPositions
                The maximum number of positions to return.
 
    @result     Returns the number of caret positions for the specified glyph.
*/
CFIndex CTFontGetLigatureCaretPositions(
    CTFontRef       font,
    CGGlyph         glyph,
    CGFloat * __nullable positions,
    CFIndex         maxPositions ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Baseline Alignment
 *///--------------------------------------------------------------------------

/*!
    @defined    kCTBaselineClassRoman

    @abstract   Key to reference the Roman baseline class.
 
    @discussion This key can be used with a baseline info dictionary to offset to the Roman baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassRoman CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTBaselineClassIdeographicCentered
 
    @abstract   Key to reference the Ideographic Centered baseline class.
 
    @discussion This key can be used with a baseline info dictionary to offset to the Ideographic Centered baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassIdeographicCentered CT_AVAILABLE(10_8, 6_0);
    
/*!
    @defined    kCTBaselineClassIdeographicLow
 
    @abstract   Key to reference the Ideographic Low baseline class.
 
    @discussion This key can be used with a baseline info dictionary to offset to the Ideographic Low baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassIdeographicLow CT_AVAILABLE(10_8, 6_0);
    
/*!
    @defined    kCTBaselineClassIdeographicHigh

    @abstract   Key to reference the Ideographic High baseline class.

    @discussion This key can be used with a baseline info dictionary to offset to the Ideographic High baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassIdeographicHigh CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTBaselineClassHanging
 
    @abstract   Key to reference the Hanging baseline class.
 
    @discussion This key can be used with a baseline info dictionary to offset to the Hanging baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassHanging CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTBaselineClassMathKey

    @abstract   Key to reference the Math baseline class.

    @discussion This key can be used with a baseline info dictionary to offset to the Math baseline as a CFNumberRef float. It can also be used as the value for kCTBaselineClassAttributeName.
*/
extern const CFStringRef kCTBaselineClassMath CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTBaselineReferenceFont
 
    @abstract   Key to reference a font for the reference baseline.
 
    @discussion This key can be used to specify a font for the reference baseline. The value is a CTFontRef or the kCTBaselineOriginalFont constant.
*/
extern const CFStringRef kCTBaselineReferenceFont CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTBaselineOriginalFont
    
    @abstract   Use the original font for setting the reference baseline.
 
    @discussion This constant can be used as the value for kCTBaselineReferenceFont to specify that the original font should be used for the reference baseline.
*/
extern const CFStringRef kCTBaselineOriginalFont CT_AVAILABLE(10_8, 6_0);


/*!
    @function   CTFontCopyDefaultCascadeListForLanguages
    @abstract   Return an ordered list of CTFontDescriptorRef's for font fallback derived from the system default fallback region according to the given language preferences. The style of the given is also matched as well as the weight and width of the font is not one of the system UI font, otherwise the UI font fallback is applied.

    @param      font
                The font reference.
 
    @param      languagePrefList
                The language preference list - ordered array of CFStringRef's of ISO language codes.

    @result     The ordered list of fallback fonts - ordered array of CTFontDescriptors.
*/
CFArrayRef __nullable CTFontCopyDefaultCascadeListForLanguages( CTFontRef font, CFArrayRef __nullable languagePrefList ) CT_AVAILABLE(10_8, 6_0);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTLine.h
/*
 *  CTLine.h
 *  CoreText
 *
 *  Copyright (c) 2003-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTLINE__
#define __CTLINE__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFAttributedString.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Line Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTLine * CTLineRef;


/*!
    @enum       CTLineBoundsOptions
    @abstract   Options for CTLineGetBoundsWithOptions.

    @discussion Passing 0 (no options) returns the typographic bounds,
                including typographic leading and shifts.

    @constant   kCTLineBoundsExcludeTypographicLeading
                Pass this option to exclude typographic leading.

    @constant   kCTLineBoundsExcludeTypographicShifts
                Pass this option to ignore cross-stream shifts due to
                positioning (such as kerning or baseline alignment).

    @constant   kCTLineBoundsUseHangingPunctuation
                Normally line bounds include all glyphs; pass this option to
                treat standard punctuation hanging off either end of the line
                as fully hanging.

    @constant   kCTLineBoundsUseGlyphPathBounds
                Pass this option to use glyph path bounds rather than the
                default typographic bounds.

    @constant   kCTLineBoundsUseOpticalBounds
                Pass this option to use optical bounds. This option overrides
                kCTLineBoundsUseGlyphPathBounds.
                
    @constant   kCTLineBoundsIncludeLanguageExtents
                Pass this option to include additional space based on common
                glyph sequences for various languages. The result is intended
                to be used when drawing to avoid clipping that may be caused
                by the typographic bounds. This option does not have any effect
                when used with kCTLineBoundsUseGlyphPathBounds.
*/

typedef CF_OPTIONS(CFOptionFlags, CTLineBoundsOptions) {
    kCTLineBoundsExcludeTypographicLeading  = 1 << 0,
    kCTLineBoundsExcludeTypographicShifts   = 1 << 1,
    kCTLineBoundsUseHangingPunctuation      = 1 << 2,
    kCTLineBoundsUseGlyphPathBounds         = 1 << 3,
    kCTLineBoundsUseOpticalBounds           = 1 << 4,
    kCTLineBoundsIncludeLanguageExtents CT_ENUM_AVAILABLE(10_11, 8_0) = 1 << 5,
};


/*!
    @enum       CTLineTruncationType
    @abstract   Truncation types required by CTLineCreateTruncatedLine. These
                will tell truncation engine which type of truncation is being
                requested.

    @constant   kCTLineTruncationStart
                Truncate at the beginning of the line, leaving the end portion
                visible.

    @constant   kCTLineTruncationEnd
                Truncate at the end of the line, leaving the start portion
                visible.

    @constant   kCTLineTruncationMiddle
                Truncate in the middle of the line, leaving both the start
                and the end portions visible.
*/

typedef CF_ENUM(uint32_t, CTLineTruncationType) {
    kCTLineTruncationStart  = 0,
    kCTLineTruncationEnd    = 1,
    kCTLineTruncationMiddle = 2
};


/*!
    @function   CTLineGetTypeID
    @abstract   Returns the CFType of the line object
*/

CFTypeID CTLineGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Line Creation */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTLineCreateWithAttributedString
    @abstract   Creates a single immutable line object directly from an
                attributed string.

    @discussion This will allow clients who need very simple line generation to
                create a line without needing to create a typesetter object. The
                typesetting will be done under the hood. Without a typesetter
                object, the line cannot be properly broken. However, for simple
                things like text labels and other things, this is not an issue.

    @param      attrString
                The attributed string which the line will be created for.

    @result     This function will return a reference to a CTLine object.
*/

CTLineRef CTLineCreateWithAttributedString(
    CFAttributedStringRef attrString ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineCreateTruncatedLine
    @abstract   Creates a truncated line from an existing line.

    @param      line
                The line that you want to create a truncated line for.

    @param      width
                The width at which truncation will begin. The line will be
                truncated if its width is greater than the width passed in this.

    @param      truncationType
                The type of truncation to perform if needed.

    @param      truncationToken
                This token will be added to the point where truncation took place
                to indicate that the line was truncated. Usually, the truncation
                token is the ellipsis character (U+2026). If this parameter is
                set to NULL, then no truncation token is used, and the line is
                simply cut off. The line specified in truncationToken should have
                a width less than the width specified by the width parameter. If
                the width of the line specified in truncationToken is greater,
                this function will return NULL if truncation is needed.

    @result     This function will return a reference to a truncated CTLine
                object if the call was successful. Otherwise, it will return
                NULL.
*/

CTLineRef __nullable CTLineCreateTruncatedLine(
    CTLineRef line,
    double width,
    CTLineTruncationType truncationType,
    CTLineRef __nullable truncationToken ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineCreateJustifiedLine
    @abstract   Creates a justified line from an existing line.

    @param      line
                The line that you want to create a justified line for.

    @param      justificationFactor
                Allows for full or partial justification. When set to 1.0 or
                greater indicates, full justification will be performed. If less
                than 1.0, varying degrees of partial justification will be
                performed. If set to 0 or less, then no justification will be
                performed.

    @param      justificationWidth
                The width to which the resultant line will be justified. If
                justificationWidth is less than the actual width of the line,
                then negative justification will be performed ("text squishing").

    @result     This function will return a reference to a justified CTLine
                object if the call was successful. Otherwise, it will return
                NULL.
*/

CTLineRef __nullable CTLineCreateJustifiedLine(
    CTLineRef line,
    CGFloat justificationFactor,
    double justificationWidth ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Line Access */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTLineGetGlyphCount
    @abstract   Returns the total glyph count for the line object.

    @discussion The total glyph count is equal to the sum of all of the glyphs in
                the glyph runs forming the line.

    @param      line
                The line that you want to obtain the glyph count for.

    @result     The total glyph count for the line passed in.
*/

CFIndex CTLineGetGlyphCount(
    CTLineRef line ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetGlyphRuns
    @abstract   Returns the array of glyph runs that make up the line object.

    @param      line
                The line that you want to obtain the glyph run array for.

    @result     A CFArrayRef containing the CTRun objects that make up the line.
*/

CFArrayRef CTLineGetGlyphRuns(
    CTLineRef line ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetStringRange
    @abstract   Gets the range of characters that originally spawned the glyphs
                in the line.

    @param      line
                The line that you want to obtain the string range from.

    @result     A CFRange that contains the range over the backing store string
                that spawned the glyphs. If the function fails for any reason, an
                empty range will be returned.
*/

CFRange CTLineGetStringRange(
    CTLineRef line ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetPenOffsetForFlush
    @abstract   Gets the pen offset required to draw flush text.

    @param      line
                The line that you want to obtain a flush position from.

    @param      flushFactor
                Specifies what kind of flushness you want. A flushFactor of 0 or
                less indicates left flush. A flushFactor of 1.0 or more indicates
                right flush. Flush factors between 0 and 1.0 indicate varying
                degrees of center flush, with a value of 0.5 being totally center
                flush.

    @param      flushWidth
                Specifies the width that the flushness operation should apply to.

    @result     A value which can be used to offset the current pen position for
                the flush operation.
*/

double CTLineGetPenOffsetForFlush(
    CTLineRef line,
    CGFloat flushFactor,
    double flushWidth ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineDraw
    @abstract   Draws a line.

    @discussion This is a convenience call, since the line could be drawn
                run-by-run by getting the glyph runs and accessing the glyphs out
                of them. Note that this call may leave the graphics context in
                any state and does not flush the context after the draw
                operation.

    @param      line
                The line that you want to draw.

    @param      context
                The context to which the line will be drawn.
*/

void CTLineDraw(
    CTLineRef line,
    CGContextRef context ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Line Measurement */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTLineGetTypographicBounds
    @abstract   Calculates the typographic bounds for a line.

    @discussion A line's typographic width is the distance to the rightmost
                glyph advance width edge. Note that this distance includes
                trailing whitespace glyphs.

    @param      line
                The line that you want to calculate the typographic bounds for.

    @param      ascent
                Upon return, this parameter will contain the ascent of the line.
                This may be set to NULL if not needed.

    @param      descent
                Upon return, this parameter will contain the descent of the line.
                This may be set to NULL if not needed.

    @param      leading
                Upon return, this parameter will contain the leading of the line.
                This may be set to NULL if not needed.

    @result     The typographic width of the line. If line is invalid, this
                function will always return zero.

    @seealso    CTLineGetTrailingWhitespaceWidth
*/

double CTLineGetTypographicBounds(
    CTLineRef line,
    CGFloat * __nullable ascent,
    CGFloat * __nullable descent,
    CGFloat * __nullable leading ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetBoundsWithOptions
    @abstract   Calculates the bounds for a line.

    @param      line
                The line that you want to calculate the bounds for.

    @param      options
                Desired options or 0 if none.

    @result     The bounds of the line as specified by the type and options,
                such that the coordinate origin is coincident with the line
                origin and the rect origin is at the bottom left. If the line
                is invalid this function will return CGRectNull.
*/

CGRect CTLineGetBoundsWithOptions(
    CTLineRef line,
    CTLineBoundsOptions options ) CT_AVAILABLE(10_8, 6_0);


/*!
    @function   CTLineGetTrailingWhitespaceWidth
    @abstract   Calculates the trailing whitespace width for a line.

    @param      line
                The line that you want to calculate the trailing whitespace width
                for. Creating a line for a width can result in a line that is
                actually longer than the desired width due to trailing
                whitespace. Normally this is not an issue due to whitespace being
                invisible, but this function may be used to determine what amount
                of a line's width is due to trailing whitespace.

    @result     The width of the line's trailing whitespace. If line is invalid,
                this function will always return zero.
*/

double CTLineGetTrailingWhitespaceWidth(
    CTLineRef line ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetImageBounds
    @abstract   Calculates the image bounds for a line.

    @discussion The image bounds for a line is the union of all non-empty glyph
                bounding rects, each positioned as it would be if drawn using
                CTLineDraw using the current context. Note that the result is
                ideal and does not account for raster coverage due to rendering.
                This function is purely a convenience for using glyphs as an
                image and should not be used for typographic purposes.

    @param      line
                The line that you want to calculate the image bounds for.

    @param      context
                The context which the image bounds will be calculated for or NULL,
                in which case the bounds are relative to CGPointZero.

    @result     A rectangle that tightly encloses the paths of the line's glyphs,
                which will be translated by the supplied context's text position.
                If the line is invalid, CGRectNull will be returned.

    @seealso    CTLineGetTypographicBounds
    @seealso    CTLineGetBoundsWithOptions
    @seealso    CTLineGetPenOffsetForFlush
*/

CGRect CTLineGetImageBounds(
    CTLineRef line,
    CGContextRef __nullable context ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Line Caret Positioning and Highlighting */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTLineGetStringIndexForPosition
    @abstract   Performs hit testing.

    @discussion This function can be used to determine the string index for a
                mouse click or other event. This string index corresponds to the
                character before which the next character should be inserted.
                This determination is made by analyzing the string from which a
                typesetter was created and the corresponding glyphs as embodied
                by a particular line.

    @param      line
                The line being examined.

    @param      position
                The location of the mouse click relative to the line's origin.

    @result     The string index for the position. Relative to the line's string
                range, this value will be no less than the first string index and
                no greater than one plus the last string index. In the event of
                failure, this function will return kCFNotFound.
*/

CFIndex CTLineGetStringIndexForPosition(
    CTLineRef line,
    CGPoint position ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTLineGetOffsetForStringIndex
    @abstract   Determines the graphical offset(s) for a string index.

    @discussion This function returns the graphical offset(s) corresponding to
                a string index, suitable for movement between adjacent lines or
                for drawing a custom caret. For the former, the primary offset
                may be adjusted for any relative indentation of the two lines;
                a CGPoint constructed with the adjusted offset for its x value
                and 0.0 for its y value is suitable for passing to
                CTLineGetStringIndexForPosition. In either case, the primary
                offset corresponds to the portion of the caret that represents
                the visual insertion location for a character whose direction
                matches the line's writing direction.

    @param      line
                The line from which the offset is requested.

    @param      charIndex
                The string index corresponding to the desired position.

    @param      secondaryOffset
                An output parameter that will be set to the secondary offset
                along the baseline for charIndex. When a single caret is
                sufficient for a string index, this value will be the same as
                the primary offset, which is the return value of this function.
                This parameter may be NULL.

    @result     The primary offset along the baseline for charIndex, or 0.0 in
                the event of failure.
*/

CGFloat CTLineGetOffsetForStringIndex(
    CTLineRef line,
    CFIndex charIndex,
    CGFloat * __nullable secondaryOffset ) CT_AVAILABLE(10_5, 3_2);


#if defined(__BLOCKS__)

/*!
    @function   CTLineEnumerateCaretOffsets
    @abstract   Enumerates caret offsets for characters in a line.

    @discussion The provided block is invoked once for each logical caret edge in the line, in left-to-right visual order.

    @param      block
                The offset parameter is relative to the line origin. The leadingEdge parameter of this block refers to logical order.
*/

void CTLineEnumerateCaretOffsets(
    CTLineRef line,
    void (^block)(double offset, CFIndex charIndex, bool leadingEdge, bool* stop) ) CT_AVAILABLE(10_11, 9_0);

#endif // defined(__BLOCKS__)


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTFramesetter.h
/*
 *	CTFramesetter.h
 *	CoreText
 *
 *	Copyright (c) 2003-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFRAMESETTER__
#define __CTFRAMESETTER__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFrame.h>
#include <CoreText/CTTypesetter.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Framesetter Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTFramesetter * CTFramesetterRef;


/*!
	@function	CTFramesetterGetTypeID
	@abstract	Returns the CFType of the framesetter object
*/

CFTypeID CTFramesetterGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Framesetter Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateWithAttributedString
	@abstract	Creates an immutable framesetter object from an attributed
				string.

	@discussion The resultant framesetter object can be used to create and
				fill text frames with the CTFramesetterCreateFrame call.

	@param		string
				The run with which you want to construct the framesetter
				object with.

	@result		This function will return a reference to a CTFramesetter if
				the call was successful. Otherwise, it will return NULL.
*/

CTFramesetterRef CTFramesetterCreateWithAttributedString(
	CFAttributedStringRef string ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Frame Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateFrame
	@abstract	Creates an immutable frame from a framesetter.

	@discussion This call will create a frame full of glyphs in the shape of
				the path provided by the "path" parameter. The framesetter
				will continue to fill the frame until it either runs out of
				text or it finds that text no longer fits.

	@param		framesetter
				The framesetter that will be used to create the frame.

	@param		stringRange
				The string range which the new frame will be based on. The
				string range is a range over the string that was used to
				create the framesetter. If the length portion of the range
				is set to 0, then the framesetter will continue to add lines
				until it runs out of text or space.

	@param		path
				A CGPath object that specifies the shape which the frame will
				take on.

	@param		frameAttributes
				Additional attributes that control the frame filling process
				can be specified here, or NULL if there are no such attributes.
				See CTFrame.h for available attributes.

	@result		This function will return a reference to a new CTFrame object.
*/

CTFrameRef CTFramesetterCreateFrame(
	CTFramesetterRef framesetter,
	CFRange stringRange,
	CGPathRef path,
	CFDictionaryRef __nullable frameAttributes ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFramesetterGetTypesetter
	@abstract	Returns the typesetter object being used by the framesetter.

	@discussion Each framesetter uses a typesetter internally to perform
				line breaking and other contextual analysis based on the
				characters in a string; this function returns the typesetter
				being used by a particular framesetter if the caller would
				like to perform other operations on that typesetter.

	@param		framesetter
				The framesetter from which a typesetter is being requested.

	@result		This function will return a reference to a CTTypesetter
				object, which should not be released by the caller.
*/

CTTypesetterRef CTFramesetterGetTypesetter(
	CTFramesetterRef framesetter ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Frame Sizing */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterSuggestFrameSizeWithConstraints
	@abstract	Determines the frame size needed for a string range.

	@discussion	This function may be used to determine how much space is needed
				to display a string, optionally by constraining the space along
				either dimension.

	@param		framesetter
				The framesetter that will be used for measuring the frame size.

	@param		stringRange
				The string range to which the frame size will apply. The
				string range is a range over the string that was used to
				create the framesetter. If the length portion of the range
				is set to 0, then the framesetter will continue to add lines
				until it runs out of text or space.

	@param		frameAttributes
				Additional attributes that control the frame filling process
				can be specified here, or NULL if there are no such attributes.

	@param		constraints
				The width and height to which the frame size will be constrained,
				A value of CGFLOAT_MAX for either dimension indicates that it
				should be treated as unconstrained.

	@param		fitRange
				The range of the string that actually fit in the constrained size.

	@result		The actual dimensions for the given string range and constraints.
*/

CGSize CTFramesetterSuggestFrameSizeWithConstraints(
	CTFramesetterRef framesetter,
	CFRange stringRange,
	CFDictionaryRef __nullable frameAttributes,
	CGSize constraints,
	CFRange * __nullable fitRange ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTRubyAnnotation.h
/*
 *  CTRubyAnnotation.h
 *  CoreText
 *
 *  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
 *
 */

/*!
 @header
 
 Thread Safety Information
 
 All functions in this header are thread safe unless otherwise specified.
 */

#ifndef __CTRUBYANNOTATION__
#define __CTRUBYANNOTATION__

#include <CoreText/CTDefines.h>
#include <CoreGraphics/CGBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* RubyAnnotation Types                                                        */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTRubyAnnotation * CTRubyAnnotationRef;


/*!
    @function	CTRubyAnnotationGetTypeID
    @abstract	Returns the CFType of the ruby annotation object
*/

CFTypeID CTRubyAnnotationGetTypeID( void ) CT_AVAILABLE(10_10, 8_0);


/* --------------------------------------------------------------------------- */
/* Ruby alignment Values                                                       */
/* --------------------------------------------------------------------------- */

/*!
    @enum       CTRubyAlignment
    @abstract   These constants specify how to align the ruby annotation and the base text relative to each other when they don't have the same length.

    @constant   kCTRubyAlignmentAuto
                CoreText will determine the alignment.

    @constant   kCTRubyAlignmentStart
                The ruby text is aligned with the start edge of the base text.

    @constant   kCTRubyAlignmentCenter
                The ruby text is centered within the width of the base text. If the ruby text is wider than the base text the base text is centered in the width of the ruby text.

    @constant   kCTRubyAlignmentEnd
                The ruby text is aligned with the end edge of the base text.

    @constant   kCTRubyAlignmentDistributeLetter
                If the width of the ruby text is less than the width of the base text, the ruby text is evenly distributed over the width of the base text, with the first letter of the ruby text aligning with the first letter of the base text and the last letter of the ruby text aligning with the last letter of the base text. If the width of the base text is less than the width of the ruby text, the base text is evenly distributed over the width of the ruby text.

    @constant   kCTRubyAlignmentDistributeSpace
                If the width of the ruby text is less than the width of the base text, the ruby text is evenly distributed over the width of the base text, with a certain amount of space, usually half the inter-character width of the ruby text, before the first and after the last character. If the width of the base text is less than the width of the ruby text, the base text is similarly aligned to the width of the ruby text.

    @constant   kCTRubyAlignmentLineEdge
                If the ruby text is not adjacent to a line edge it is aligned as with kCTRubyAlignmentAuto. If it is adjacent to a line edge the end of ruby text adjacent to the line edge is aligned to the line edge. This is only relevant if the width of the ruby text is greater than the width of the base text; otherwise alignment is as with kCTRubyAlignmentAuto.
*/

typedef CF_ENUM(uint8_t, CTRubyAlignment) {
    kCTRubyAlignmentInvalid = (uint8_t)-1,
    kCTRubyAlignmentAuto = 0,
    kCTRubyAlignmentStart = 1,
    kCTRubyAlignmentCenter = 2,
    kCTRubyAlignmentEnd = 3,
    kCTRubyAlignmentDistributeLetter = 4,
    kCTRubyAlignmentDistributeSpace = 5,
    kCTRubyAlignmentLineEdge = 6
} CT_AVAILABLE(10_10, 8_0);


/* --------------------------------------------------------------------------- */
/* Ruby overhang Values                                                        */
/* --------------------------------------------------------------------------- */

/*!
    @enum       CTRubyOverhang
    @abstract   These constants specify whether, and on which side, ruby text is allowed to overhang adjacent text if it is wider than the base text.

    @constant   kCTRubyOverhangAuto
                The ruby text can overhang adjacent text on both sides.

    @constant   kCTRubyOverhangStart
                The ruby text can overhang the text that proceeds it.

    @constant   kCTRubyOverhangEnd
                The ruby text can overhang the text that follows it.

    @constant   kCTRubyOverhangNone
                The ruby text cannot overhang the proceeding or following text.
*/

typedef CF_ENUM(uint8_t, CTRubyOverhang) {
    kCTRubyOverhangInvalid = (uint8_t)-1,
    kCTRubyOverhangAuto = 0,
    kCTRubyOverhangStart = 1,
    kCTRubyOverhangEnd = 2,
    kCTRubyOverhangNone = 3
} CT_AVAILABLE(10_10, 8_0);


/* --------------------------------------------------------------------------- */
/* Ruby position Values                                                        */
/* --------------------------------------------------------------------------- */

/*!
    @enum       CTRubyPosition
    @abstract   These constants specify the position of the ruby text with respect to the base text.

    @constant   kCTRubyPositionBefore
                The ruby text is positioned before the base text; i.e. above horizontal text and to the right of vertical text.

    @constant   kCTRubyPositionAfter
                The ruby text is positioned after the base text; i.e. below horizontal text and to the left of vertical text.

    @constant   kCTRubyPositionInterCharacter
                The ruby text is positioned to the right of the base text whether it is horizontal or vertical. This is the way that Bopomofo annotations are attached to Chinese text in Taiwan.

    @constant   kCTRubyPositionInline
                The ruby text follows the base text with no special styling.
*/

typedef CF_ENUM(uint8_t, CTRubyPosition) {
    kCTRubyPositionBefore = 0,
    kCTRubyPositionAfter = 1,
    kCTRubyPositionInterCharacter = 2,
    kCTRubyPositionInline = 3,
    kCTRubyPositionCount
} CT_AVAILABLE(10_10, 8_0);


/* --------------------------------------------------------------------------- */
/* Ruby Annotation Creation */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTRubyAnnotationCreate
    @abstract   Creates an immutable ruby annotation object.

    @discussion Using this function is the easiest and most efficient way to
                create a ruby annotation object.

    @param      alignment
                Specifies how the ruby text and the base text should be aligned relative to each other.

    @param      overhang
                Specifies how the ruby text can overhang adjacent characters.

    @param		sizeFactor
                Specifies the size of the annotation text as a percent of the size of the base text.

    @param      text
                An array of CFStringRef, indexed by CTRubyPosition. Supply NULL for any unused positions.

    @result     This function will return a reference to a CTRubyAlignment object.
*/

CTRubyAnnotationRef CTRubyAnnotationCreate(
    CTRubyAlignment alignment,
    CTRubyOverhang overhang,
    CGFloat sizeFactor,
    CFStringRef text[kCTRubyPositionCount] ) CT_AVAILABLE(10_10, 8_0);

/*!
    @function   CTRubyAnnotationCreateCopy
    @abstract   Creates an immutable copy of a ruby annotation object.

    @param      rubyAnnotation
                The ruby annotation that you wish to copy.

    @result     If the "rubyAnnotation" reference is valid, then this
                function will return valid reference to an immutable
                CTRubyAnnotation object that is a copy of the one passed into
                "rubyAnnotation".
*/

CTRubyAnnotationRef CTRubyAnnotationCreateCopy(
    CTRubyAnnotationRef rubyAnnotation ) CT_AVAILABLE(10_10, 8_0);


/*!
    @function   CTRubyAnnotationGetAlignment
    @abstract   Get the alignment value of a ruby annotation object.

    @param      rubyAnnotation
                The ruby annotation object.

    @result     If the "rubyAnnotation" reference is valid, then this
                function will return its alignment. Otherwise it will return kCTRubyAlignmentInvalid.
*/

CTRubyAlignment CTRubyAnnotationGetAlignment(
    CTRubyAnnotationRef rubyAnnotation ) CT_AVAILABLE(10_10, 8_0);


/*!
    @function   CTRubyAnnotationGetOverhang
    @abstract   Get the overhang value of a ruby annotation object.

    @param      rubyAnnotation
                The ruby annotation object.

    @result     If the "rubyAnnotation" reference is valid, then this
                function will return its overhang value. Otherwise it will return kCTRubyOverhangInvalid.
*/

CTRubyOverhang CTRubyAnnotationGetOverhang(
    CTRubyAnnotationRef rubyAnnotation ) CT_AVAILABLE(10_10, 8_0);

/*!
    @function   CTRubyAnnotationGetSizeFactor
    @abstract   Get the size factor of a ruby annotation object.

    @param      rubyAnnotation
                The ruby annotation object.

    @result     If the "rubyAnnotation" reference is valid, then this
                function will return its sizeFactor. Otherwise it will return 0.
*/

CGFloat CTRubyAnnotationGetSizeFactor(
    CTRubyAnnotationRef rubyAnnotation ) CT_AVAILABLE(10_10, 8_0);


/*!
    @function   CTRubyAnnotationGetTextForPosition
    @abstract   Get the ruby text for a particular position in a ruby annotation.

    @param      rubyAnnotation
                The ruby annotation object.

    @param      postion
                The position for which you want to get the ruby text.

    @result     If the "rubyAnnotation" reference and the position are valid, then this
                function will return a CFStringRef for the text. Otherwise it will return NULL.
*/

CFStringRef __nullable CTRubyAnnotationGetTextForPosition(
    CTRubyAnnotationRef rubyAnnotation,
    CTRubyPosition position ) CT_AVAILABLE(10_10, 8_0);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTFontManagerErrors.h
/*
 *  CTFontManagerErrors.h
 *  CoreText
 *
 *  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTFONTMANAGERERRORS__
#define __CTFONTMANAGERERRORS__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
    @const      kCTFontManagerErrorDomain
    @abstract   CFError domain for CTFontManager errors
    @discussion CFErrors with this domain will have error codes corresponding to one of the CTFontManagerErrors above.
*/
extern const CFStringRef kCTFontManagerErrorDomain CT_AVAILABLE(10_6, 3_2);

/*!
    @constant   kCTFontManagerErrorFontURLsKey
    @abstract   User info key to be used with CFError references returned from registration functions.
    @discussion The value associated with this key in the user info dictionary of a CFError is a CFArray of font URLs that failed with given error.
*/
extern const CFStringRef kCTFontManagerErrorFontURLsKey CT_AVAILABLE(10_6, 3_2);

/*!
    @enum
    @abstract   Font registration errors
    @discussion Errors that would prevent registration of fonts for a specified font file URL.
    @constant   kCTFontManagerErrorFileNotFound
                The file does not exist at the specified URL.
    @constant   kCTFontManagerErrorInsufficientPermissions
                Cannot access the file due to insufficient permissions.
    @constant   kCTFontManagerErrorUnrecognizedFormat
                The file is not a recognized or supported font file format.
    @constant   kCTFontManagerErrorInvalidFontData
                The file contains invalid font data that could cause system problems.
    @constant   kCTFontManagerErrorAlreadyRegistered
                The file has already been registered in the specified scope.
*/
/*!
    @enum
    @abstract   Font un-registration errors
    @discussion Errors that would prevent un-registration of fonts for a specified font file URL.
    @constant   kCTFontManagerErrorNotRegistered
                The file is not registered in the specified scope.
    @constant   kCTFontManagerErrorInUse
                The font file is actively in use and cannot be unregistered.
    @constant   kCTFontManagerErrorSystemRequired
                The file is required by the system and cannot be unregistered.
*/
typedef CF_ENUM(CFIndex, CTFontManagerError) {
    kCTFontManagerErrorFileNotFound             = 101,
    kCTFontManagerErrorInsufficientPermissions  = 102,
    kCTFontManagerErrorUnrecognizedFormat       = 103,
    kCTFontManagerErrorInvalidFontData          = 104,
    kCTFontManagerErrorAlreadyRegistered        = 105,
    kCTFontManagerErrorNotRegistered            = 201,
    kCTFontManagerErrorInUse                    = 202,
    kCTFontManagerErrorSystemRequired           = 203,
};

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif
// ==========  CoreText.framework/Headers/CTFontManager.h
/*
 *  CTFontManager.h
 *  CoreText
 *
 *  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTMANAGER__
#define __CTFONTMANAGER__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontDescriptor.h>
#include <CoreText/CTFontManagerErrors.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFURL.h>
#include <CoreGraphics/CGFont.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
    @constant   CTRegisterBundleFonts
    @discussion If this key is defined in the application bundle info dictionary with a boolean value of true, CTFontManager will register all fonts in the Fonts subdirectory of the bundle's Resources directory in the process scope.  
*/

/*!
    @function   CTFontManagerCopyAvailablePostScriptNames
    @abstract   Returns an array of unique PostScript font names.
 
    @result     An array of CFStrings.
*/
CFArrayRef CTFontManagerCopyAvailablePostScriptNames( void ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerCopyAvailableFontFamilyNames
    @abstract   Returns an array of visible font family names sorted for UI display.

    @result     An array of CFStrings.
*/
CFArrayRef CTFontManagerCopyAvailableFontFamilyNames( void ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerCopyAvailableFontURLs
    @abstract   Returns an array of font URLs.

    @result     An array of CFURLs.
*/
CFArrayRef CTFontManagerCopyAvailableFontURLs( void ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerCompareFontFamilyNames
    @abstract   A CFComparatorFunction to compare font family names and sort them according to Apple guidelines.
    @discussion This function compares font family names and sorts them in the preferred order for display in user interfaces.
    @param      family1
                The first localized font family name, as CFStringRef.
    @param      family2
                The second localized font family name, as CFStringRef.
    @param      context
                Unused. Can be NULL.
    @result     A CFComparisonResult value indicating the sort order for the two family names. kCFComparisonResultGreaterThan if family1 is greater than family2, kCFComparisonResultLessThan if family1 is less than family2, and kCFComparisonResultEqualTo if they are equal.
*/
CFComparisonResult CTFontManagerCompareFontFamilyNames(
    const void *        family1,
    const void *        family2,
    void * __nullable   context ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerCreateFontDescriptorsFromURL
    @abstract   Returns an array of font descriptors representing each of the fonts in the specified URL.
                Note: these font descriptors are not available through font descriptor matching.

    @param      fileURL
                A file system URL referencing a valid font file.

    @result     An array of CTFontDescriptors or NULL if there are no valid fonts.
*/
CFArrayRef __nullable CTFontManagerCreateFontDescriptorsFromURL(
    CFURLRef            fileURL ) CT_AVAILABLE(10_6, 7_0);

/*!
    @function   CTFontManagerCreateFontDescriptorFromData
    @abstract   Returns a font descriptor representing the font in the supplied data.
                Note: the font descriptor is not available through font descriptor matching.

    @param      data
                A CFData containing font data.

    @result     A font descriptor created from the data or NULL if it is not a valid font.
*/
CTFontDescriptorRef __nullable CTFontManagerCreateFontDescriptorFromData(
    CFDataRef               data ) CT_AVAILABLE(10_7, 7_0);

/*!
    @enum       CTFontManagerScope
    @abstract   Scope for font registration.
    @constant   kCTFontManagerScopeProcess
                The font is available to the current process for the duration of the process unless directly unregistered.
    @constant   kCTFontManagerScopeUser
                The font is available to all processes for the current user session and will be available in subsequent sessions unless unregistered.
                User scope is unsupported in iOS.
    @constant   kCTFontManagerScopeSession
                The font is available to the current user session, and will not be available in subsequent sessions.
                User scope is unsupported in iOS.
*/
typedef CF_ENUM(uint32_t, CTFontManagerScope) {
    kCTFontManagerScopeNone         = 0,
    kCTFontManagerScopeProcess      = 1,
    kCTFontManagerScopeUser         = 2,    /* not supported in iOS */
    kCTFontManagerScopeSession      = 3     /* not supported in iOS */
};

/*!
    @function   CTFontManagerRegisterFontsForURL
    @abstract   Registers fonts from the specified font URL with the font manager. Registered fonts are discoverable through font descriptor matching.

    @param      fontURL
                Font URL.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. See scope constants for more details.

    @param      error
                Pointer to receive CFError in the case of failed registration.

    @result     Returns true if registration of the fonts was successful.
*/
bool CTFontManagerRegisterFontsForURL(
    CFURLRef                fontURL,
    CTFontManagerScope      scope,
    CFErrorRef *            error ) CT_AVAILABLE(10_6, 4_1);

/*!
    @function   CTFontManagerUnregisterFontsForURL
    @abstract   Unregisters fonts from the specified font URL with the font manager. Unregistered fonts are no longer discoverable through font descriptor matching.
                iOS note: only fonts registered with CTFontManagerRegisterFontsForURL or CTFontManagerRegisterFontsForURLs can be unregistered with this API.

    @param      fontURL
                Font URL.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. Should match the scope the fonts are registered in. See scope constants for more details.

    @param      error
                Pointer to receive CFError in the case of failed unregistration.

    @result     Returns true if unregistration of the fonts was successful.

*/
bool CTFontManagerUnregisterFontsForURL(
    CFURLRef                fontURL,
    CTFontManagerScope      scope,
    CFErrorRef *            error ) CT_AVAILABLE(10_6, 4_1);

/*!
    @function   CTFontManagerRegisterGraphicsFont
    @abstract   Registers the specified graphics font with the font manager. Registered fonts are discoverable through font descriptor matching.
                Attempts to register a font that is either already registered or contains the same Postscript of an already registered font will fail.
                This functionality is useful for fonts that may be embedded in documents or present/constructed in memory. A graphics font is obtained
                by calling CGFontCreateWithDataProvider. Fonts that are backed by files should be registered using CTFontManagerRegisterFontsForURL.
 
    @param      font
                Graphics font to be registered.
 
    @param      error
                Pointer to receive CFError in the case of failed registration.
 
    @result     Returns true if registration of the fonts was successful.
*/
bool CTFontManagerRegisterGraphicsFont(
    CGFontRef               font,
    CFErrorRef *            error ) CT_AVAILABLE(10_8, 4_1);
    
/*!
    @function   CTFontManagerUnregisterGraphicsFont
    @abstract   Unregisters the specified graphics font with the font manager. Unregistered fonts are no longer discoverable through font descriptor matching.
 
    @param      font
                Graphics font to be unregistered.
 
    @param      error
                Pointer to receive CFError in the case of failed unregistration.
 
    @result     Returns true if unregistration of the font was successful.
*/
bool CTFontManagerUnregisterGraphicsFont(
    CGFontRef               font,
    CFErrorRef *            error ) CT_AVAILABLE(10_8, 4_1);

/*!
    @function   CTFontManagerRegisterFontsForURLs
    @abstract   Registers fonts from the specified font URLs with the font manager. Registered fonts are discoverable through font descriptor matching.

    @param      fontURLs
                Array of font URLs.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. See scope constants for more details.

    @param      errors
                Pointer to CFArrayRef to receive array of CFError references. Each error will contain a CFArray of font URLs corresponding to kCTFontManagerErrorFontURLsKey. These URLs represent the font files that caused the error, and were not successfully registered. Must be released by caller. Can be NULL.

    @result     Returns true if registration of all font URLs was successful. Otherwise false.
*/
bool CTFontManagerRegisterFontsForURLs(
    CFArrayRef              fontURLs,
    CTFontManagerScope      scope,
    CFArrayRef __nullable * __nullable errors ) CT_AVAILABLE(10_6, 4_1);

/*!
    @function   CTFontManagerUnregisterFontsForURLs
    @abstract   Unregisters fonts from the specified font URLs with the font manager. Unregistered fonts are no longer discoverable through font descriptor matching.
                iOS note: only fonts registered with CTFontManagerRegisterFontsForURL or CTFontManagerRegisterFontsForURLs can be unregistered with this API.

    @param      fontURLs
                Array of font URLs.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. Should match the scope the fonts are registered in. See scope constants for more details.

    @param      errors
                Pointer to CFArrayRef to receive array of CFError references. Each error will contain a CFArray of font URLs corresponding to kCTFontManagerErrorFontURLsKey. These URLs represent the font files that caused the error, and were not successfully unregistered. Must be released by caller. Can be NULL.

    @result     Returns true if unregistration of all font URLs was successful. Otherwise false.
*/
bool CTFontManagerUnregisterFontsForURLs(
    CFArrayRef              fontURLs,
    CTFontManagerScope      scope,
    CFArrayRef __nullable * __nullable errors ) CT_AVAILABLE(10_6, 4_1);

/*!
    @function   CTFontManagerEnableFontDescriptors
    @abstract   Enables or disables the matching font descriptors for font descriptor matching.

    @param      descriptors
                Array of font descriptors.

    @param      enable
                Boolean value indicating whether the fonts matching descriptors should be enabled for font descriptor matching.
*/
void CTFontManagerEnableFontDescriptors(
    CFArrayRef              descriptors,
    bool                    enable ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerGetScopeForURL
    @abstract   Returns the registration scope of the specified URL.

    @param      fontURL
                Font URL.

    @result     Returns the registration scope of the specified URL, will return kCTFontManagerScopeNone if not currently registered.
*/
CTFontManagerScope CTFontManagerGetScopeForURL(
    CFURLRef                fontURL ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerIsSupportedFontFile
    @abstract   Determines whether the referenced font data (usually by file URL) is supported on the current platform.

    @param      fontURL
                A URL to font data.

    @result     This function returns true if the URL represents a valid font that can be used on the current platform.
*/
bool CTFontManagerIsSupportedFont(
    CFURLRef                fontURL ) CT_AVAILABLE_MAC(10_6);

/*! --------------------------------------------------------------------------
    @group Manager Auto-Activation
*///--------------------------------------------------------------------------

#if defined(__BLOCKS__)
/*!
    @function   CTFontManagerCreateFontRequestRunLoopSource
    @abstract   Creates a CFRunLoopSourceRef that will be used to convey font requests from CTFontManager.
    @param      sourceOrder
                The order of the created run loop source.
    @param      createMatchesCallback
                A block to handle the font request.
    @result     A CFRunLoopSourceRef that should be added to the run loop. To stop receiving requests, invalidate this run loop source. Will return NULL on error, in the case of a duplicate requestPortName or invalid context structure.
*/
CFRunLoopSourceRef __nullable CTFontManagerCreateFontRequestRunLoopSource(
    CFIndex         sourceOrder,
    CFArrayRef    (^createMatchesCallback)(CFDictionaryRef requestAttributes, pid_t requestingProcess)) CT_AVAILABLE_MAC(10_6);
#endif // defined(__BLOCKS__)

/*!
    @const      kCTFontManagerBundleIdentifier
    @abstract   CTFontManage bundle identifier
    @discussion The CTFontManager bundle identifier to be used with get or set global auto-activation settings.
*/
extern const CFStringRef kCTFontManagerBundleIdentifier CT_AVAILABLE_MAC(10_6);

/*!
    @enum
    @abstract   Auto-activation settings.
    @constant   kCTFontManagerAutoActivationDefault
                Default auto-activation setting. When specified, the application will use the global setting.
    @constant   kCTFontManagerAutoActivationDisabled
                Disables auto-activation.
    @constant   kCTFontManagerAutoActivationEnabled
                Enables auto-activation.
    @constant   kCTFontManagerAutoActivationPromptUser
                Requires user input for auto-activation. A dialog will be presented to the user to confirm auto
                activation of the font.
*/
typedef CF_ENUM(uint32_t, CTFontManagerAutoActivationSetting) {
    kCTFontManagerAutoActivationDefault     = 0,
    kCTFontManagerAutoActivationDisabled    = 1,
    kCTFontManagerAutoActivationEnabled     = 2,
    kCTFontManagerAutoActivationPromptUser  = 3
};

/*!
    @function   CTFontManagerSetAutoActivationSetting
    @abstract   Sets the auto-activation for the specified bundle identifier.
    @param      bundleIdentifier
                The bundle identifier. Used to specify a particular application bundle. If NULL,
                the current application bundle will be used. If kCTFontManagerBundleIdentifier is specified,
                will set the global auto-activation settings.
    @param      setting
                The new setting.
    @result     Function will apply the setting to the appropriate preferences location.
*/
void CTFontManagerSetAutoActivationSetting(
    CFStringRef __nullable              bundleIdentifier,
    CTFontManagerAutoActivationSetting  setting ) CT_AVAILABLE_MAC(10_6);

/*!
    @function   CTFontManagerGetAutoActivationSetting
    @abstract   Accessor for the auto-activation setting.
    @param      bundleIdentifier
                The bundle identifier. Used to specify a particular application bundle. If NULL,
                the current application bundle will be used. If kCTFontManagerBundleIdentifier is specified,
                will set the global auto-activation settings.
    @result     Will return the auto-activation setting for specified bundle identifier.
*/
CTFontManagerAutoActivationSetting CTFontManagerGetAutoActivationSetting(
    CFStringRef __nullable bundleIdentifier ) CT_AVAILABLE_MAC(10_6);

/*! --------------------------------------------------------------------------
    @group Manager Notifications
*///--------------------------------------------------------------------------

/*!
    @constant   kCTFontManagerRegisteredFontsChangedNotification
    @abstract   Notification name for font registry changes.
    @discussion This is the string to use as the notification name when subscribing
                to CTFontManager notifications.  This notification will be posted when fonts are added or removed.
                OS X clients should register as an observer of the notification with the distributed notification center
                for changes in session or user scopes and with the local notification center for changes in process scope.
                iOS clients should register as an observer of the notification with the local notification center for all changes.
*/
extern const CFStringRef kCTFontManagerRegisteredFontsChangedNotification CT_AVAILABLE(10_6, 7_0);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/SFNTLayoutTypes.h
/*
 *  SFNTLayoutTypes.h
 *  CoreText
 *
 *  Copyright 1994-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __SFNTLAYOUTTYPES__
#define __SFNTLAYOUTTYPES__

#include <MacTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* ----------------------------------------------------------------------------------------- */
/* CONSTANTS */
/*
    The following values can be used to set run feature values. Note that unless the
    feature is defaulted differently in different fonts, the zero value for the
    selectors represents the default value. Consult the following URL for further info:
    <http://developer.apple.com/fonts/registry/>
*/


/*
 *  Summary:
 *    Feature types
 */
enum {
  kAllTypographicFeaturesType   = 0,
  kLigaturesType                = 1,
  kCursiveConnectionType        = 2,
  kLetterCaseType               = 3,    /* deprecated - use kLowerCaseType or kUpperCaseType instead */
  kVerticalSubstitutionType     = 4,
  kLinguisticRearrangementType  = 5,
  kNumberSpacingType            = 6,
  kSmartSwashType               = 8,
  kDiacriticsType               = 9,
  kVerticalPositionType         = 10,
  kFractionsType                = 11,
  kOverlappingCharactersType    = 13,
  kTypographicExtrasType        = 14,
  kMathematicalExtrasType       = 15,
  kOrnamentSetsType             = 16,
  kCharacterAlternativesType    = 17,
  kDesignComplexityType         = 18,
  kStyleOptionsType             = 19,
  kCharacterShapeType           = 20,
  kNumberCaseType               = 21,
  kTextSpacingType              = 22,
  kTransliterationType          = 23,
  kAnnotationType               = 24,
  kKanaSpacingType              = 25,
  kIdeographicSpacingType       = 26,
  kUnicodeDecompositionType     = 27,
  kRubyKanaType                 = 28,
  kCJKSymbolAlternativesType    = 29,
  kIdeographicAlternativesType  = 30,
  kCJKVerticalRomanPlacementType = 31,
  kItalicCJKRomanType           = 32,
  kCaseSensitiveLayoutType      = 33,
  kAlternateKanaType            = 34,
  kStylisticAlternativesType    = 35,
  kContextualAlternatesType     = 36,
  kLowerCaseType                = 37,
  kUpperCaseType                = 38,
  kLanguageTagType              = 39,
  kCJKRomanSpacingType          = 103,
  kLastFeatureType              = -1
};


/*
 *  Summary:
 *    Selectors for feature type kAllTypographicFeaturesType
 */
enum {
  kAllTypeFeaturesOnSelector    = 0,
  kAllTypeFeaturesOffSelector   = 1
};



/*
 *  Summary:
 *    Selectors for feature type kLigaturesType
 */
enum {
  kRequiredLigaturesOnSelector  = 0,
  kRequiredLigaturesOffSelector = 1,
  kCommonLigaturesOnSelector    = 2,
  kCommonLigaturesOffSelector   = 3,
  kRareLigaturesOnSelector      = 4,
  kRareLigaturesOffSelector     = 5,
  kLogosOnSelector              = 6,
  kLogosOffSelector             = 7,
  kRebusPicturesOnSelector      = 8,
  kRebusPicturesOffSelector     = 9,
  kDiphthongLigaturesOnSelector = 10,
  kDiphthongLigaturesOffSelector = 11,
  kSquaredLigaturesOnSelector   = 12,
  kSquaredLigaturesOffSelector  = 13,
  kAbbrevSquaredLigaturesOnSelector = 14,
  kAbbrevSquaredLigaturesOffSelector = 15,
  kSymbolLigaturesOnSelector    = 16,
  kSymbolLigaturesOffSelector   = 17,
  kContextualLigaturesOnSelector = 18,
  kContextualLigaturesOffSelector = 19,
  kHistoricalLigaturesOnSelector = 20,
  kHistoricalLigaturesOffSelector = 21
};


/*
 *  Summary:
 *    Selectors for feature type kCursiveConnectionType
 */
enum {
  kUnconnectedSelector          = 0,
  kPartiallyConnectedSelector   = 1,
  kCursiveSelector              = 2
};


/*
 *  Summary:
 *    Selectors for feature type kLetterCaseType
 */
enum {
  kUpperAndLowerCaseSelector    = 0,    /* deprecated */
  kAllCapsSelector              = 1,    /* deprecated */
  kAllLowerCaseSelector         = 2,    /* deprecated */
  kSmallCapsSelector            = 3,    /* deprecated */
  kInitialCapsSelector          = 4,    /* deprecated */
  kInitialCapsAndSmallCapsSelector = 5  /* deprecated */
};


/*
 *  Summary:
 *    Selectors for feature type kVerticalSubstitutionType
 */
enum {
  kSubstituteVerticalFormsOnSelector = 0,
  kSubstituteVerticalFormsOffSelector = 1
};


/*
 *  Summary:
 *    Selectors for feature type kLinguisticRearrangementType
 */
enum {
  kLinguisticRearrangementOnSelector = 0,
  kLinguisticRearrangementOffSelector = 1
};


/*
 *  Summary:
 *    Selectors for feature type kNumberSpacingType
 */
enum {
  kMonospacedNumbersSelector    = 0,
  kProportionalNumbersSelector  = 1,
  kThirdWidthNumbersSelector    = 2,
  kQuarterWidthNumbersSelector  = 3
};


/*
 *  Summary:
 *    Selectors for feature type kSmartSwashType
 */
enum {
  kWordInitialSwashesOnSelector = 0,
  kWordInitialSwashesOffSelector = 1,
  kWordFinalSwashesOnSelector   = 2,
  kWordFinalSwashesOffSelector  = 3,
  kLineInitialSwashesOnSelector = 4,
  kLineInitialSwashesOffSelector = 5,
  kLineFinalSwashesOnSelector   = 6,
  kLineFinalSwashesOffSelector  = 7,
  kNonFinalSwashesOnSelector    = 8,
  kNonFinalSwashesOffSelector   = 9
};


/*
 *  Summary:
 *    Selectors for feature type kDiacriticsType
 */
enum {
  kShowDiacriticsSelector       = 0,
  kHideDiacriticsSelector       = 1,
  kDecomposeDiacriticsSelector  = 2
};


/*
 *  Summary:
 *    Selectors for feature type kVerticalPositionType
 */
enum {
  kNormalPositionSelector       = 0,
  kSuperiorsSelector            = 1,
  kInferiorsSelector            = 2,
  kOrdinalsSelector             = 3,
  kScientificInferiorsSelector  = 4
};


/*
 *  Summary:
 *    Selectors for feature type kFractionsType
 */
enum {
  kNoFractionsSelector          = 0,
  kVerticalFractionsSelector    = 1,
  kDiagonalFractionsSelector    = 2
};


/*
 *  Summary:
 *    Selectors for feature type kOverlappingCharactersType
 */
enum {
  kPreventOverlapOnSelector     = 0,
  kPreventOverlapOffSelector    = 1
};


/*
 *  Summary:
 *    Selectors for feature type kTypographicExtrasType
 */
enum {
  kHyphensToEmDashOnSelector    = 0,
  kHyphensToEmDashOffSelector   = 1,
  kHyphenToEnDashOnSelector     = 2,
  kHyphenToEnDashOffSelector    = 3,
  kSlashedZeroOnSelector        = 4,
  kSlashedZeroOffSelector       = 5,
  kFormInterrobangOnSelector    = 6,
  kFormInterrobangOffSelector   = 7,
  kSmartQuotesOnSelector        = 8,
  kSmartQuotesOffSelector       = 9,
  kPeriodsToEllipsisOnSelector  = 10,
  kPeriodsToEllipsisOffSelector = 11
};


/*
 *  Summary:
 *    Selectors for feature type kMathematicalExtrasType
 */
enum {
  kHyphenToMinusOnSelector      = 0,
  kHyphenToMinusOffSelector     = 1,
  kAsteriskToMultiplyOnSelector = 2,
  kAsteriskToMultiplyOffSelector = 3,
  kSlashToDivideOnSelector      = 4,
  kSlashToDivideOffSelector     = 5,
  kInequalityLigaturesOnSelector = 6,
  kInequalityLigaturesOffSelector = 7,
  kExponentsOnSelector          = 8,
  kExponentsOffSelector         = 9,
  kMathematicalGreekOnSelector  = 10,
  kMathematicalGreekOffSelector = 11
};


/*
 *  Summary:
 *    Selectors for feature type kOrnamentSetsType
 */
enum {
  kNoOrnamentsSelector          = 0,
  kDingbatsSelector             = 1,
  kPiCharactersSelector         = 2,
  kFleuronsSelector             = 3,
  kDecorativeBordersSelector    = 4,
  kInternationalSymbolsSelector = 5,
  kMathSymbolsSelector          = 6
};


/*
 *  Summary:
 *    Selectors for feature type kCharacterAlternativesType
 */
enum {
  kNoAlternatesSelector         = 0
};


/*
 *  Summary:
 *    Selectors for feature type kDesignComplexityType
 */
enum {
  kDesignLevel1Selector         = 0,
  kDesignLevel2Selector         = 1,
  kDesignLevel3Selector         = 2,
  kDesignLevel4Selector         = 3,
  kDesignLevel5Selector         = 4
};


/*
 *  Summary:
 *    Selectors for feature type kStyleOptionsType
 */
enum {
  kNoStyleOptionsSelector       = 0,
  kDisplayTextSelector          = 1,
  kEngravedTextSelector         = 2,
  kIlluminatedCapsSelector      = 3,
  kTitlingCapsSelector          = 4,
  kTallCapsSelector             = 5
};


/*
 *  Summary:
 *    Selectors for feature type kCharacterShapeType
 */
enum {
  kTraditionalCharactersSelector = 0,
  kSimplifiedCharactersSelector = 1,
  kJIS1978CharactersSelector    = 2,
  kJIS1983CharactersSelector    = 3,
  kJIS1990CharactersSelector    = 4,
  kTraditionalAltOneSelector    = 5,
  kTraditionalAltTwoSelector    = 6,
  kTraditionalAltThreeSelector  = 7,
  kTraditionalAltFourSelector   = 8,
  kTraditionalAltFiveSelector   = 9,
  kExpertCharactersSelector     = 10,
  kJIS2004CharactersSelector    = 11,
  kHojoCharactersSelector       = 12,
  kNLCCharactersSelector        = 13,
  kTraditionalNamesCharactersSelector = 14
};


/*
 *  Summary:
 *    Selectors for feature type kNumberCaseType
 */
enum {
  kLowerCaseNumbersSelector     = 0,
  kUpperCaseNumbersSelector     = 1
};


/*
 *  Summary:
 *    Selectors for feature type kTextSpacingType
 */
enum {
  kProportionalTextSelector     = 0,
  kMonospacedTextSelector       = 1,
  kHalfWidthTextSelector        = 2,
  kThirdWidthTextSelector       = 3,
  kQuarterWidthTextSelector     = 4,
  kAltProportionalTextSelector  = 5,
  kAltHalfWidthTextSelector     = 6
};


/*
 *  Summary:
 *    Selectors for feature type kTransliterationType
 */
enum {
  kNoTransliterationSelector    = 0,
  kHanjaToHangulSelector        = 1,
  kHiraganaToKatakanaSelector   = 2,
  kKatakanaToHiraganaSelector   = 3,
  kKanaToRomanizationSelector   = 4,
  kRomanizationToHiraganaSelector = 5,
  kRomanizationToKatakanaSelector = 6,
  kHanjaToHangulAltOneSelector  = 7,
  kHanjaToHangulAltTwoSelector  = 8,
  kHanjaToHangulAltThreeSelector = 9
};


/*
 *  Summary:
 *    Selectors for feature type kAnnotationType
 */
enum {
  kNoAnnotationSelector         = 0,
  kBoxAnnotationSelector        = 1,
  kRoundedBoxAnnotationSelector = 2,
  kCircleAnnotationSelector     = 3,
  kInvertedCircleAnnotationSelector = 4,
  kParenthesisAnnotationSelector = 5,
  kPeriodAnnotationSelector     = 6,
  kRomanNumeralAnnotationSelector = 7,
  kDiamondAnnotationSelector    = 8,
  kInvertedBoxAnnotationSelector = 9,
  kInvertedRoundedBoxAnnotationSelector = 10
};


/*
 *  Summary:
 *    Selectors for feature type kKanaSpacingType
 */
enum {
  kFullWidthKanaSelector        = 0,
  kProportionalKanaSelector     = 1
};


/*
 *  Summary:
 *    Selectors for feature type kIdeographicSpacingType
 */
enum {
  kFullWidthIdeographsSelector  = 0,
  kProportionalIdeographsSelector = 1,
  kHalfWidthIdeographsSelector  = 2
};


/*
 *  Summary:
 *    Selectors for feature type kUnicodeDecompositionType
 */
enum {
  kCanonicalCompositionOnSelector = 0,
  kCanonicalCompositionOffSelector = 1,
  kCompatibilityCompositionOnSelector = 2,
  kCompatibilityCompositionOffSelector = 3,
  kTranscodingCompositionOnSelector = 4,
  kTranscodingCompositionOffSelector = 5
};


/*
 *  Summary:
 *    Selectors for feature type kRubyKanaType
 */
enum {
  kNoRubyKanaSelector           = 0,    /* deprecated - use kRubyKanaOffSelector instead */
  kRubyKanaSelector             = 1,    /* deprecated - use kRubyKanaOnSelector instead */
  kRubyKanaOnSelector           = 2,
  kRubyKanaOffSelector          = 3
};


/*
 *  Summary:
 *    Selectors for feature type kCJKSymbolAlternativesType
 */
enum {
  kNoCJKSymbolAlternativesSelector = 0,
  kCJKSymbolAltOneSelector      = 1,
  kCJKSymbolAltTwoSelector      = 2,
  kCJKSymbolAltThreeSelector    = 3,
  kCJKSymbolAltFourSelector     = 4,
  kCJKSymbolAltFiveSelector     = 5
};


/*
 *  Summary:
 *    Selectors for feature type kIdeographicAlternativesType
 */
enum {
  kNoIdeographicAlternativesSelector = 0,
  kIdeographicAltOneSelector    = 1,
  kIdeographicAltTwoSelector    = 2,
  kIdeographicAltThreeSelector  = 3,
  kIdeographicAltFourSelector   = 4,
  kIdeographicAltFiveSelector   = 5
};


/*
 *  Summary:
 *    Selectors for feature type kCJKVerticalRomanPlacementType
 */
enum {
  kCJKVerticalRomanCenteredSelector = 0,
  kCJKVerticalRomanHBaselineSelector = 1
};


/*
 *  Summary:
 *    Selectors for feature type kItalicCJKRomanType
 */
enum {
  kNoCJKItalicRomanSelector     = 0,    /* deprecated - use kCJKItalicRomanOffSelector instead */
  kCJKItalicRomanSelector       = 1,    /* deprecated - use kCJKItalicRomanOnSelector instead */
  kCJKItalicRomanOnSelector     = 2,
  kCJKItalicRomanOffSelector    = 3
};


/*
 *  Summary:
 *    Selectors for feature type kCaseSensitiveLayoutType
 */
enum {
  kCaseSensitiveLayoutOnSelector = 0,
  kCaseSensitiveLayoutOffSelector = 1,
  kCaseSensitiveSpacingOnSelector = 2,
  kCaseSensitiveSpacingOffSelector = 3
};


/*
 *  Summary:
 *    Selectors for feature type kAlternateKanaType
 */
enum {
  kAlternateHorizKanaOnSelector = 0,
  kAlternateHorizKanaOffSelector = 1,
  kAlternateVertKanaOnSelector  = 2,
  kAlternateVertKanaOffSelector = 3
};


/*
 *  Summary:
 *    Selectors for feature type kStylisticAlternativesType
 */
enum {
  kNoStylisticAlternatesSelector = 0,
  kStylisticAltOneOnSelector    = 2,
  kStylisticAltOneOffSelector   = 3,
  kStylisticAltTwoOnSelector    = 4,
  kStylisticAltTwoOffSelector   = 5,
  kStylisticAltThreeOnSelector  = 6,
  kStylisticAltThreeOffSelector = 7,
  kStylisticAltFourOnSelector   = 8,
  kStylisticAltFourOffSelector  = 9,
  kStylisticAltFiveOnSelector   = 10,
  kStylisticAltFiveOffSelector  = 11,
  kStylisticAltSixOnSelector    = 12,
  kStylisticAltSixOffSelector   = 13,
  kStylisticAltSevenOnSelector  = 14,
  kStylisticAltSevenOffSelector = 15,
  kStylisticAltEightOnSelector  = 16,
  kStylisticAltEightOffSelector = 17,
  kStylisticAltNineOnSelector   = 18,
  kStylisticAltNineOffSelector  = 19,
  kStylisticAltTenOnSelector    = 20,
  kStylisticAltTenOffSelector   = 21,
  kStylisticAltElevenOnSelector = 22,
  kStylisticAltElevenOffSelector = 23,
  kStylisticAltTwelveOnSelector = 24,
  kStylisticAltTwelveOffSelector = 25,
  kStylisticAltThirteenOnSelector = 26,
  kStylisticAltThirteenOffSelector = 27,
  kStylisticAltFourteenOnSelector = 28,
  kStylisticAltFourteenOffSelector = 29,
  kStylisticAltFifteenOnSelector = 30,
  kStylisticAltFifteenOffSelector = 31,
  kStylisticAltSixteenOnSelector = 32,
  kStylisticAltSixteenOffSelector = 33,
  kStylisticAltSeventeenOnSelector = 34,
  kStylisticAltSeventeenOffSelector = 35,
  kStylisticAltEighteenOnSelector = 36,
  kStylisticAltEighteenOffSelector = 37,
  kStylisticAltNineteenOnSelector = 38,
  kStylisticAltNineteenOffSelector = 39,
  kStylisticAltTwentyOnSelector = 40,
  kStylisticAltTwentyOffSelector = 41
};


/*
 *  Summary:
 *    Selectors for feature type kContextualAlternatesType
 */
enum {
  kContextualAlternatesOnSelector = 0,
  kContextualAlternatesOffSelector = 1,
  kSwashAlternatesOnSelector    = 2,
  kSwashAlternatesOffSelector   = 3,
  kContextualSwashAlternatesOnSelector = 4,
  kContextualSwashAlternatesOffSelector = 5
};


/*
 *  Summary:
 *    Selectors for feature type kLowerCaseType
 */
enum {
  kDefaultLowerCaseSelector     = 0,
  kLowerCaseSmallCapsSelector   = 1,
  kLowerCasePetiteCapsSelector  = 2
};


/*
 *  Summary:
 *    Selectors for feature type kUpperCaseType
 */
enum {
  kDefaultUpperCaseSelector     = 0,
  kUpperCaseSmallCapsSelector   = 1,
  kUpperCasePetiteCapsSelector  = 2
};


/*
 *  Summary:
 *    Selectors for feature type kCJKRomanSpacingType
 */
enum {
  kHalfWidthCJKRomanSelector    = 0,
  kProportionalCJKRomanSelector = 1,
  kDefaultCJKRomanSelector      = 2,
  kFullWidthCJKRomanSelector    = 3
};

/* --------------------------------------------------------------------------- */
/* ---------------- Table Specific Typedefs and Constants -------------------- */
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: lookup tables - used within various other tables */
enum {
  kSFNTLookupSimpleArray        = 0,    /* a simple array indexed by glyph code */
  kSFNTLookupSegmentSingle      = 2,    /* segment mapping to single value */
  kSFNTLookupSegmentArray       = 4,    /* segment mapping to lookup array */
  kSFNTLookupSingleTable        = 6,    /* sorted list of glyph, value pairs */
  kSFNTLookupTrimmedArray       = 8     /* a simple trimmed array indexed by glyph code */
};

typedef UInt16                          SFNTLookupTableFormat;
typedef UInt16                          SFNTLookupValue;
typedef UInt16                          SFNTLookupOffset;
typedef UInt32                          SFNTLookupKind;
/*
    A BinarySearchHeader defines the five standard fields needed to perform quick
    lookups in a lookup table (note that using UInt16s, and not ItemCounts or
    similar types, is important here, since these tables are in fonts, and the
    documented font formats specify 16-bit quantities).
*/
struct SFNTLookupBinarySearchHeader {
  UInt16              unitSize;               /* size of a unit in bytes */
  UInt16              nUnits;                 /* number of units in table */
  UInt16              searchRange;            /* (largest power of two <= nUnits) * unitSize */
  UInt16              entrySelector;          /* log2 (largest power of two <= nUnits) */
  UInt16              rangeShift;             /* (nUnits - largest power of two <= nUnits) * unitSize */
};
typedef struct SFNTLookupBinarySearchHeader SFNTLookupBinarySearchHeader;
/* A format 0 lookup table maps all glyphs in the font to lookup values */
struct SFNTLookupArrayHeader {
  SFNTLookupValue     lookupValues[1];
};
typedef struct SFNTLookupArrayHeader    SFNTLookupArrayHeader;
/* A format 8 lookup table maps some range of glyphs in the font to lookup values */
struct SFNTLookupTrimmedArrayHeader {
  UInt16              firstGlyph;
  UInt16              count;
  SFNTLookupValue     valueArray[1];
};
typedef struct SFNTLookupTrimmedArrayHeader SFNTLookupTrimmedArrayHeader;
/*
    Format 2 and format 4 lookup tables map ranges of glyphs to either single lookup
    values (format 2), or per-glyph lookup values (format 4). Since both formats
    use the same kind of data, only one unified set of segment-related structures
    is defined.
*/
struct SFNTLookupSegment {
  UInt16              lastGlyph;
  UInt16              firstGlyph;
  UInt16              value[1];
};
typedef struct SFNTLookupSegment        SFNTLookupSegment;
struct SFNTLookupSegmentHeader {
  SFNTLookupBinarySearchHeader  binSearch;
  SFNTLookupSegment   segments[1];
};
typedef struct SFNTLookupSegmentHeader  SFNTLookupSegmentHeader;
/* A format 6 lookup table maps single glyphs to lookup values. */
struct SFNTLookupSingle {
  UInt16              glyph;
  UInt16              value[1];
};
typedef struct SFNTLookupSingle         SFNTLookupSingle;
struct SFNTLookupSingleHeader {
  SFNTLookupBinarySearchHeader  binSearch;
  SFNTLookupSingle    entries[1];
};
typedef struct SFNTLookupSingleHeader   SFNTLookupSingleHeader;
/* The format-specific part of the subtable header */
union SFNTLookupFormatSpecificHeader {
  SFNTLookupArrayHeader  theArray;
  SFNTLookupSegmentHeader  segment;
  SFNTLookupSingleHeader  single;
  SFNTLookupTrimmedArrayHeader  trimmedArray;
};
typedef union SFNTLookupFormatSpecificHeader SFNTLookupFormatSpecificHeader;
/* The overall subtable header */
struct SFNTLookupTable {
  SFNTLookupTableFormat  format;              /* table format */
  SFNTLookupFormatSpecificHeader  fsHeader;   /* format specific header */
};
typedef struct SFNTLookupTable          SFNTLookupTable;
typedef SFNTLookupTable *               SFNTLookupTablePtr;
typedef SFNTLookupTablePtr *            SFNTLookupTableHandle;
/* --------------------------------------------------------------------------- */
/* GENERAL FORMATS FOR STATE TABLES -- prefix "ST" */
enum {
  kSTClassEndOfText             = 0,
  kSTClassOutOfBounds           = 1,
  kSTClassDeletedGlyph          = 2,
  kSTClassEndOfLine             = 3,
  kSTSetMark                    = 0x8000,
  kSTNoAdvance                  = 0x4000,
  kSTMarkEnd                    = 0x2000,
  kSTLigActionMask              = 0x3FFF,
  kSTRearrVerbMask              = 0x000F
};

typedef UInt8                           STClass;
typedef UInt8                           STEntryIndex;
struct STHeader {
  UInt8               filler;
  STClass             nClasses;
  UInt16              classTableOffset;
  UInt16              stateArrayOffset;
  UInt16              entryTableOffset;
};
typedef struct STHeader                 STHeader;
struct STClassTable {
  UInt16              firstGlyph;
  UInt16              nGlyphs;
  STClass             classes[1];
};
typedef struct STClassTable             STClassTable;
struct STEntryZero {
  UInt16              newState;
  UInt16              flags;
};
typedef struct STEntryZero              STEntryZero;
struct STEntryOne {
  UInt16              newState;
  UInt16              flags;
  UInt16              offset1;
};
typedef struct STEntryOne               STEntryOne;
struct STEntryTwo {
  UInt16              newState;
  UInt16              flags;
  UInt16              offset1;
  UInt16              offset2;
};
typedef struct STEntryTwo               STEntryTwo;
/* --------------------------------------------------------------------------- */
/* GENERAL FORMATS FOR STATE TABLES to be used with 'morx' tables -- prefix "STX" */
enum {
  kSTXHasLigAction              = 0x2000
};


typedef UInt16                          STXClass;
typedef UInt16                          STXStateIndex;
typedef UInt16                          STXEntryIndex;
struct STXHeader {
  UInt32              nClasses;
  UInt32              classTableOffset;
  UInt32              stateArrayOffset;
  UInt32              entryTableOffset;
};
typedef struct STXHeader                STXHeader;

typedef SFNTLookupTable                 STXClassTable;
struct STXEntryZero {
  STXStateIndex       newState;
  UInt16              flags;
};
typedef struct STXEntryZero             STXEntryZero;
struct STXEntryOne {
  STXStateIndex       newState;
  UInt16              flags;
  UInt16              index1;
};
typedef struct STXEntryOne              STXEntryOne;
struct STXEntryTwo {
  STXStateIndex       newState;
  UInt16              flags;
  UInt16              index1;
  UInt16              index2;
};
typedef struct STXEntryTwo              STXEntryTwo;
/* --------------------------------------------------------------------------- */
/* GENERAL FORMATS FOR STATE TABLES to be used with 'kerx' tables -- prefix "STK" */
enum {
  kSTKCrossStreamReset          = 0x2000
};
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'lcar' */
/* CONSTANTS */
enum {
  kLCARTag                      = 0x6C636172, /* 'lcar' */
  kLCARCurrentVersion           = 0x00010000, /* current version number for 'lcar' table */
  kLCARLinearFormat             = 0,
  kLCARCtlPointFormat           = 1
};

/* TYPES */
struct LcarCaretClassEntry {
  UInt16              count;
  UInt16              partials[1];            /* these are either FUnits or control-point numbers */
};
typedef struct LcarCaretClassEntry      LcarCaretClassEntry;
struct LcarCaretTable {
  Fixed               version;
  UInt16              format;
  SFNTLookupTable     lookup;
};
typedef struct LcarCaretTable           LcarCaretTable;
typedef LcarCaretTable *                LcarCaretTablePtr;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'just' */
/* CONSTANTS */
enum {
  kJUSTTag                      = 0x6A757374, /* 'just' */
  kJUSTCurrentVersion           = 0x00010000,
  kJUSTStandardFormat           = 0,
  kJUSTnoGlyphcode              = 0xFFFF, /* used in a pcConditionalAddAction */
  kJUSTpcDecompositionAction    = 0,
  kJUSTpcUnconditionalAddAction = 1,
  kJUSTpcConditionalAddAction   = 2,
  kJUSTpcGlyphStretchAction     = 3,
  kJUSTpcDuctilityAction        = 4,
  kJUSTpcGlyphRepeatAddAction   = 5
};

/* Justification priority levels */
enum {
  kJUSTKashidaPriority          = 0,
  kJUSTSpacePriority            = 1,
  kJUSTLetterPriority           = 2,
  kJUSTNullPriority             = 3,
  kJUSTPriorityCount            = 4
};

/* Justification flags */
enum {
  kJUSTOverridePriority         = 0x8000,
  kJUSTOverrideLimits           = 0x4000,
  kJUSTOverrideUnlimited        = 0x2000,
  kJUSTUnlimited                = 0x1000,
  kJUSTPriorityMask             = 0x0003
};

/* TYPES */
typedef UInt16                          JustPCActionType;
typedef UInt16                          JustificationFlags;
/* A JustPCDecompositionAction defines a ligature decomposition action. */
struct JustPCDecompositionAction {
  Fixed               lowerLimit;
  Fixed               upperLimit;
  UInt16              order;
  UInt16              count;
  UInt16              glyphs[1];
};
typedef struct JustPCDecompositionAction JustPCDecompositionAction;
/* A JUSTPCUnconditionalAddAction defines an unconditional glyph add action. */

typedef UInt16                          JustPCUnconditionalAddAction;
/*
    A JUSTPCConditionalAddAction defines a glyph substitution and add action. If the addGlyph
    is equal to kJUSTnoGlyphcode, then no glyph will be added, and the justification for
    the line will be redone.
*/
struct JustPCConditionalAddAction {
  Fixed               substThreshold;        /* threshold of growth factor at which subst occurs */
  UInt16              addGlyph;
  UInt16              substGlyph;
};
typedef struct JustPCConditionalAddAction JustPCConditionalAddAction;
/* A PCDuctilityAction defines a ductile axis along which the glyph will be varied. */
struct JustPCDuctilityAction {
  UInt32              ductilityAxis;
  Fixed               minimumLimit;
  Fixed               noStretchValue;
  Fixed               maximumLimit;
};
typedef struct JustPCDuctilityAction    JustPCDuctilityAction;
/*
    A PCGlyphRepetitionAction defines a glyph which will not be stretched or otherwise
    transformed, but rather which will be emplaced however many times are needed to fill
    the needed gap.
*/
struct JustPCGlyphRepeatAddAction {
  UInt16              flags;
  UInt16              glyph;
};
typedef struct JustPCGlyphRepeatAddAction JustPCGlyphRepeatAddAction;
/* PCActionSubrecords contain the actual postcompensation actions. */
struct JustPCActionSubrecord {
  UInt16              theClass;               /* justification class value associated with this rec */
  JustPCActionType    theType;
  UInt32              length;
  UInt32              data;                   /* not really a UInt32; cast as ptr to appropriate action */
};
typedef struct JustPCActionSubrecord    JustPCActionSubrecord;
/* The set of postcompensation records is defined in a PCAction struct. */
struct JustPCAction {
  UInt32              actionCount;            /* long for alignment purposes */
  JustPCActionSubrecord  actions[1];
};
typedef struct JustPCAction             JustPCAction;
/*
    JustWidthDeltaEntry is the justification table entry structure.  The justClass value (which is
    actually limited to 7 bits by the state table structure) is defined as a long for PPC alignment reasons.
*/
struct JustWidthDeltaEntry {
  UInt32              justClass;
  Fixed               beforeGrowLimit;        /* ems AW can grow by at most on LT */
  Fixed               beforeShrinkLimit;      /* ems AW can shrink by at most on LT */
  Fixed               afterGrowLimit;         /* ems AW can grow by at most on RB */
  Fixed               afterShrinkLimit;       /* ems AW can shrink by at most on RB */
  JustificationFlags  growFlags;              /* flags controlling grow case */
  JustificationFlags  shrinkFlags;            /* flags controlling shrink case */
};
typedef struct JustWidthDeltaEntry      JustWidthDeltaEntry;
struct JustWidthDeltaGroup {
  UInt32              count;
  JustWidthDeltaEntry  entries[1];
};
typedef struct JustWidthDeltaGroup      JustWidthDeltaGroup;
/* Overall structure of a postcompensation table is defined in PostcompTable. */
struct JustPostcompTable {
  SFNTLookupTable     lookupTable;
                                              /* action records here */
};
typedef struct JustPostcompTable        JustPostcompTable;
struct JustDirectionTable {
  UInt16              justClass;              /* offset to state table (0=none) */
  UInt16              widthDeltaClusters;     /* offset to clusters */
  UInt16              postcomp;               /* offset to postcomp table (0=none) */
  SFNTLookupTable     lookup;
};
typedef struct JustDirectionTable       JustDirectionTable;
struct JustTable {
  Fixed               version;
  UInt16              format;
  UInt16              horizHeaderOffset;
  UInt16              vertHeaderOffset;
};
typedef struct JustTable                JustTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'opbd' */
/* CONSTANTS */
enum {
  kOPBDTag                      = 0x6F706264, /* 'opbd' */
  kOPBDCurrentVersion           = 0x00010000,
  kOPBDDistanceFormat           = 0,
  kOPBDControlPointFormat       = 1
};

/* TYPES */

typedef UInt16                          OpbdTableFormat;
/*
    The OpbdSideValues struct is the lookup result from the FindSingle call for the
    optical tables. It contains the 4 FUnit values that are relevant to the specified
    glyph, or the 4 control gxPoint values.
*/
struct OpbdSideValues {
  SInt16              leftSideShift;
  SInt16              topSideShift;
  SInt16              rightSideShift;
  SInt16              bottomSideShift;
};
typedef struct OpbdSideValues           OpbdSideValues;
struct OpbdTable {
  Fixed               version;
  OpbdTableFormat     format;
  SFNTLookupTable     lookupTable;
};
typedef struct OpbdTable                OpbdTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'mort' */
/* CONSTANTS */
enum {
  kMORTTag                      = 0x6D6F7274, /* 'mort' */
  kMORTCurrentVersion           = 0x00010000, /* current version number for 'mort' table */
                                        /* Coverage masks */
  kMORTCoverVertical            = 0x8000,
  kMORTCoverDescending          = 0x4000,
  kMORTCoverIgnoreVertical      = 0x2000,
  kMORTCoverTypeMask            = 0x000F, /* Subtable types */
  kMORTRearrangementType        = 0,
  kMORTContextualType           = 1,
  kMORTLigatureType             = 2,
  kMORTSwashType                = 4,
  kMORTInsertionType            = 5,    /* Ligature subtable constants */
  kMORTLigLastAction            = (int)0x80000000,
  kMORTLigStoreLigature         = 0x40000000,
  kMORTLigFormOffsetMask        = 0x3FFFFFFF,
  kMORTLigFormOffsetShift       = 2,    /* Rearrangement subtable actions */
  kMORTraNoAction               = 0,    /*      no action      */
  kMORTraxA                     = 1,    /*      Ax => xA   */
  kMORTraDx                     = 2,    /*      xD => Dx   */
  kMORTraDxA                    = 3,    /*     AxD => DxA      */
  kMORTraxAB                    = 4,    /*     ABx => xAB      */
  kMORTraxBA                    = 5,    /*     ABx => xBA      */
  kMORTraCDx                    = 6,    /*     xCD => CDx      */
  kMORTraDCx                    = 7,    /*     xCD => DCx      */
  kMORTraCDxA                   = 8,    /*    AxCD => CDxA  */
  kMORTraDCxA                   = 9,    /*    AxCD => DCxA  */
  kMORTraDxAB                   = 10,   /*    ABxD => DxAB  */
  kMORTraDxBA                   = 11,   /*    ABxD => DxBA  */
  kMORTraCDxAB                  = 12,   /* ABxCD => CDxAB */
  kMORTraCDxBA                  = 13,   /* ABxCD => CDxBA */
  kMORTraDCxAB                  = 14,   /* ABxCD => DCxAB */
  kMORTraDCxBA                  = 15,   /* ABxCD => DCxBA */
                                        /* Insertion subtable constants */
  kMORTDoInsertionsBefore       = 0x80,
  kMORTIsSplitVowelPiece        = 0x40,
  kMORTInsertionsCountMask      = 0x3F,
  kMORTCurrInsertKashidaLike    = 0x2000,
  kMORTMarkInsertKashidaLike    = 0x1000,
  kMORTCurrInsertBefore         = 0x0800,
  kMORTMarkInsertBefore         = 0x0400,
  kMORTMarkJustTableCountMask   = 0x3F80,
  kMORTMarkJustTableCountShift  = 7,    /* JustTableIndex for marked character */
  kMORTCurrJustTableCountMask   = 0x007F,
  kMORTCurrJustTableCountShift  = 0,    /* JustTableIndex for current character */
  kMORTCurrInsertCountMask      = 0x03E0,
  kMORTCurrInsertCountShift     = 5,    /* count to insert after current glyphRec */
  kMORTMarkInsertCountMask      = 0x001F,
  kMORTMarkInsertCountShift     = 0     /* count to insert after marked glyphRec */
};

/* TYPES */

typedef UInt32                          MortSubtableMaskFlags;
typedef UInt32                          MortLigatureActionEntry;
struct MortRearrangementSubtable {
  STHeader            header;
};
typedef struct MortRearrangementSubtable MortRearrangementSubtable;
struct MortContextualSubtable {
  STHeader            header;
  UInt16              substitutionTableOffset;
};
typedef struct MortContextualSubtable   MortContextualSubtable;
struct MortLigatureSubtable {
  STHeader            header;
  UInt16              ligatureActionTableOffset;
  UInt16              componentTableOffset;
  UInt16              ligatureTableOffset;
};
typedef struct MortLigatureSubtable     MortLigatureSubtable;
struct MortSwashSubtable {
  SFNTLookupTable     lookup;
};
typedef struct MortSwashSubtable        MortSwashSubtable;
struct MortInsertionSubtable {
  STHeader            header;
};
typedef struct MortInsertionSubtable    MortInsertionSubtable;
union MortSpecificSubtable {
  MortRearrangementSubtable  rearrangement;
  MortContextualSubtable  contextual;
  MortLigatureSubtable  ligature;
  MortSwashSubtable   swash;
  MortInsertionSubtable  insertion;
};
typedef union MortSpecificSubtable      MortSpecificSubtable;
struct MortSubtable {
  UInt16              length;
  UInt16              coverage;
  MortSubtableMaskFlags  flags;
  MortSpecificSubtable  u;
};
typedef struct MortSubtable             MortSubtable;
struct MortFeatureEntry {
  UInt16              featureType;
  UInt16              featureSelector;
  MortSubtableMaskFlags  enableFlags;
  MortSubtableMaskFlags  disableFlags;
};
typedef struct MortFeatureEntry         MortFeatureEntry;
struct MortChain {
  MortSubtableMaskFlags  defaultFlags;        /* default flags for this chain */
  UInt32              length;                 /* byte length of this chain */
  UInt16              nFeatures;              /* number of feature entries */
  UInt16              nSubtables;             /* number of subtables */
  MortFeatureEntry    featureEntries[1];
                                              /* the subtables follow */
};
typedef struct MortChain                MortChain;
struct MortTable {
  Fixed               version;
  UInt32              nChains;
  MortChain           chains[1];
};
typedef struct MortTable                MortTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'morx' (version 2 and beyond metamorphosis tables) */
/* CONSTANTS */
enum {
  kMORXTag                      = 0x6D6F7278, /* 'morx' */
  kMORXCurrentVersion           = 0x00020000, /* version number for current 'morx' table */
                                        /* Coverage masks */
  kMORXCoverVertical            = (int)0x80000000,
  kMORXCoverDescending          = 0x40000000,
  kMORXCoverIgnoreVertical      = 0x20000000,
  kMORXCoverLogicalOrder        = 0x10000000,
  kMORXCoverTypeMask            = 0x000000FF
};

/* TYPES */
struct MorxRearrangementSubtable {
  STXHeader           header;
};
typedef struct MorxRearrangementSubtable MorxRearrangementSubtable;
struct MorxContextualSubtable {
  STXHeader           header;
  UInt32              substitutionTableOffset;
};
typedef struct MorxContextualSubtable   MorxContextualSubtable;
struct MorxLigatureSubtable {
  STXHeader           header;
  UInt32              ligatureActionTableOffset;
  UInt32              componentTableOffset;
  UInt32              ligatureTableOffset;
};
typedef struct MorxLigatureSubtable     MorxLigatureSubtable;
struct MorxInsertionSubtable {
  STXHeader           header;
  UInt32              insertionGlyphTableOffset;
};
typedef struct MorxInsertionSubtable    MorxInsertionSubtable;
union MorxSpecificSubtable {
  MorxRearrangementSubtable  rearrangement;
  MorxContextualSubtable  contextual;
  MorxLigatureSubtable  ligature;
  MortSwashSubtable   swash;
  MorxInsertionSubtable  insertion;
};
typedef union MorxSpecificSubtable      MorxSpecificSubtable;
struct MorxSubtable {
  UInt32              length;
  UInt32              coverage;
  MortSubtableMaskFlags  flags;
  MorxSpecificSubtable  u;
};
typedef struct MorxSubtable             MorxSubtable;
struct MorxChain {
  MortSubtableMaskFlags  defaultFlags;        /* default flags for this chain */
  UInt32              length;                 /* byte length of this chain */
  UInt32              nFeatures;              /* number of feature entries */
  UInt32              nSubtables;             /* number of subtables */
  MortFeatureEntry    featureEntries[1];
                                              /* the subtables follow */
};
typedef struct MorxChain                MorxChain;
struct MorxTable {
  Fixed               version;
  UInt32              nChains;
  MorxChain           chains[1];
};
typedef struct MorxTable                MorxTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'prop' */
/* CONSTANTS */
enum {
  kPROPTag                      = 0x70726F70, /* 'prop' */
  kPROPCurrentVersion           = 0x00030000, /* current version number for 'prop' table */
  kPROPPairOffsetShift          = 8,
  kPROPPairOffsetSign           = 7,
  kPROPIsFloaterMask            = 0x8000, /* glyph is floater */
  kPROPCanHangLTMask            = 0x4000, /* glyph can hang left/top */
  kPROPCanHangRBMask            = 0x2000, /* glyph can hang right/bottom */
  kPROPUseRLPairMask            = 0x1000, /* if glyph lands in RL streak, use paired glyph */
  kPROPPairOffsetMask           = 0x0F00, /* 4-bit signed offset to other pair member */
  kPROPRightConnectMask         = 0x0080, /* glyph connects to glyph on right */
  kPROPZeroReserved             = 0x0060, /* must be zero */
  kPROPDirectionMask            = 0x001F /* direction bits */
};

/* These are the Unicode direction classes (plus the Special European Number class). */
enum {
  kPROPLDirectionClass          = 0,    /* Left-to-Right */
  kPROPRDirectionClass          = 1,    /* Right-to-Left */
  kPROPALDirectionClass         = 2,    /* Right-to-Left Arabic Letter */
  kPROPENDirectionClass         = 3,    /* European Number */
  kPROPESDirectionClass         = 4,    /* European Number Separator */
  kPROPETDirectionClass         = 5,    /* European Number Terminator */
  kPROPANDirectionClass         = 6,    /* Arabic Number */
  kPROPCSDirectionClass         = 7,    /* Common Number Separator */
  kPROPPSDirectionClass         = 8,    /* Paragraph Separator (also referred to as Block Separator) */
  kPROPSDirectionClass          = 9,    /* Segment Separator */
  kPROPWSDirectionClass         = 10,   /* Whitespace */
  kPROPONDirectionClass         = 11,   /* Other Neutral */
  kPROPSENDirectionClass        = 12,   /* Special European Number (not a Unicode class) */
  kPROPLREDirectionClass        = 13,   /* Left-to-Right Embedding */
  kPROPLRODirectionClass        = 14,   /* Left-to-Right Override */
  kPROPRLEDirectionClass        = 15,   /* Right-to-Left Embedding */
  kPROPRLODirectionClass        = 16,   /* Right-to-Left Override */
  kPROPPDFDirectionClass        = 17,   /* Pop Directional Format */
  kPROPNSMDirectionClass        = 18,   /* Non-Spacing Mark */
  kPROPBNDirectionClass         = 19,   /* Boundary Neutral */
  kPROPNumDirectionClasses      = 20    /* Number of Unicode directional types + Special European Number */
};

/* TYPES */

typedef UInt16                          PropCharProperties;
struct PropTable {
  Fixed               version;
  UInt16              format;
  PropCharProperties  defaultProps;
  SFNTLookupTable     lookup;
};
typedef struct PropTable                PropTable;
struct PropLookupSegment {
  UInt16              lastGlyph;
  UInt16              firstGlyph;
  UInt16              value;
};
typedef struct PropLookupSegment        PropLookupSegment;
struct PropLookupSingle {
  UInt16              glyph;
  PropCharProperties  props;
};
typedef struct PropLookupSingle         PropLookupSingle;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'trak' */
/* CONSTANTS */
enum {
  kTRAKTag                      = 0x7472616B, /* 'trak' */
  kTRAKCurrentVersion           = 0x00010000, /* current version number for 'trak' table */
  kTRAKUniformFormat            = 0     /*    kTRAKPerGlyphFormat         = 2*/
};

/* TYPES */

typedef SInt16                          TrakValue;
struct TrakTableEntry {
  Fixed               track;
  UInt16              nameTableIndex;
  UInt16              sizesOffset;            /* offset to array of TrackingValues */
};
typedef struct TrakTableEntry           TrakTableEntry;
struct TrakTableData {
  UInt16              nTracks;
  UInt16              nSizes;
  UInt32              sizeTableOffset;
  TrakTableEntry      trakTable[1];
};
typedef struct TrakTableData            TrakTableData;
struct TrakTable {
  Fixed               version;
  UInt16              format;
  UInt16              horizOffset;
  UInt16              vertOffset;
};
typedef struct TrakTable                TrakTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'kern' */
/* CONSTANTS */
enum {
  kKERNTag                      = 0x6B65726E, /* 'kern' */
  kKERNCurrentVersion           = 0x00010000,
  kKERNVertical                 = 0x8000, /* set if this table has vertical kerning information */
  kKERNResetCrossStream         = 0x8000, /* this value in a cross-stream table means reset to zero */
  kKERNCrossStream              = 0x4000, /* set if this table contains cross-stream kerning values */
  kKERNVariation                = 0x2000, /* set if this table contains variation kerning values */
  kKERNUnusedBits               = 0x1F00, /* UNUSED, MUST BE ZERO */
  kKERNFormatMask               = 0x00FF /* format of this subtable */
};

enum {
  kKERNOrderedList              = 0,    /* ordered list of kerning pairs */
  kKERNStateTable               = 1,    /* state table for n-way contextual kerning */
  kKERNSimpleArray              = 2,    /* simple n X m array of kerning values */
  kKERNIndexArray               = 3     /* modified version of SimpleArray */
};

/* Message Type Flags */
enum {
  kKERNLineStart                = 0x00000001, /* Array of glyphs starts a line */
  kKERNLineEndKerning           = 0x00000002, /* Array of glyphs ends a line */
  kKERNNoCrossKerning           = 0x00000004, /* Prohibit cross kerning */
  kKERNNotesRequested           = 0x00000008, /* Caller wants kerning notes */
  kKERNNoStakeNote              = 1,    /* Indicates a glyph was involved in a kerning pair/group */
  kKERNCrossStreamResetNote     = 2,    /* Indicates a return-to-baseline in cross-stream kerning */
  kKERNNotApplied               = 0x00000001 /* All kerning values were zero, kerning call had no effect */
};

/* TYPES */

typedef UInt8                           KernTableFormat;
typedef UInt16                          KernSubtableInfo;
typedef SInt16                          KernKerningValue;
typedef UInt16                          KernArrayOffset;
/* header for version 0 kerning table */
struct KernVersion0Header {
  UInt16              version;                /* font version number (will be 0!) */
  UInt16              nTables;                /* number of subtables present */
  UInt16              firstSubtable[1];       /* first subtable starts here */
};
typedef struct KernVersion0Header       KernVersion0Header;
/* Header for a kerning table */
struct KernTableHeader {
  Fixed               version;                /* font version number (currently 1.0) */
  SInt32              nTables;                /* number of subtables present */
  UInt16              firstSubtable[1];       /* first subtable starts here */
};
typedef struct KernTableHeader          KernTableHeader;
typedef KernTableHeader *               KernTableHeaderPtr;
typedef KernTableHeaderPtr *            KernTableHeaderHandle;
/*
    F O R M A T   S P E C I F I C   D E F I N I T I O N S

    kernOrderedList:
    
    The table is a sorted list of [left glyph, right glyph, value] triples.
    There's enough information in the header so that the list can be
    efficiently binary searched. 
*/
/* defines a single kerning pair of Glyphcodes  */
struct KernKerningPair {
  UInt16              left;
  UInt16              right;
};
typedef struct KernKerningPair          KernKerningPair;
/* a single list entry */
struct KernOrderedListEntry {
  KernKerningPair     pair;                   /* the kerning pair */
  KernKerningValue    value;                  /* the kerning value for the above pair */
};
typedef struct KernOrderedListEntry     KernOrderedListEntry;
typedef KernOrderedListEntry *          KernOrderedListEntryPtr;
/* the header information for binary searching the list */
struct KernOrderedListHeader {
  UInt16              nPairs;                 /* number of kerning pairs in table */
  UInt16              searchRange;            /* (largest power of two <= nPairs) * entry size */
  UInt16              entrySelector;          /* log2 (largest power of two <= nPairs) */
  UInt16              rangeShift;             /* (nPairs - largest power of two <= nPairs) * entry size */
  UInt16              table[1];               /* entries are first glyph, second glyph, and value */
};
typedef struct KernOrderedListHeader    KernOrderedListHeader;
/* KernStateTable: like the the generic state tables */
struct KernStateHeader {
  STHeader            header;                 /* state table header */
  UInt16              valueTable;             /* offset to kerning value table */
  UInt8               firstTable[1];          /* first table starts here */
};
typedef struct KernStateHeader          KernStateHeader;
struct KernStateEntry {
  UInt16              newState;
  UInt16              flags;                  /* flags per above enum */
};
typedef struct KernStateEntry           KernStateEntry;
/*
    Kern offset table header.
    The offset table is a trimmed array from firstGlyph to limitGlyph.
    Glyphs outside of this range should get zero for right-hand glyphs
    and the offset of the beginning of the kerning array for left-hand glyphs.
*/
struct KernOffsetTable {
  UInt16              firstGlyph;             /* first glyph in class range */
  UInt16              nGlyphs;                /* number of glyphs in class range */
  KernArrayOffset     offsetTable[1];         /* offset table starts here */
};
typedef struct KernOffsetTable          KernOffsetTable;
typedef KernOffsetTable *               KernOffsetTablePtr;
/* Header information for accessing offset tables and kerning array */
/*
    KernSimpleArray:
    
    The array is an nXm array of kerning values. Each row in the array
    represents one left-hand glyph, and each column one right-hand glyph.
    The zeroth row and column always represent glyphs that are out of bounds
    and will always contain zero.
    
    A pair is looked up by indexing the left-hand glyph through the left
    offset table, the right-hand glyph through the right offset table,
    adding both offsets to the starting address of the kerning array,
    and fetching the kerning value pointed to.
*/
/* Kern offset table header. */
/* The offset table is a trimmed array from firstGlyph to limitGlyph. */
/* Glyphs outside of this range should get zero for right-hand glyphs */
/* and the offset of the beginning of the kerning array for left- */
/* hand glyphs. */
struct KernSimpleArrayHeader {
  UInt16              rowWidth;               /* width, in bytes, of a row in the table */
  UInt16              leftOffsetTable;        /* offset to left-hand offset table */
  UInt16              rightOffsetTable;       /* offset to right-hand offset table */
  KernArrayOffset     theArray;               /* offset to start of kerning array */
  UInt16              firstTable[1];          /* first offset table starts here... */
};
typedef struct KernSimpleArrayHeader    KernSimpleArrayHeader;
/* Index Array */
struct KernIndexArrayHeader {
  UInt16              glyphCount;
  UInt8               kernValueCount;
  UInt8               leftClassCount;
  UInt8               rightClassCount;
  UInt8               flags;                  /* set to 0 for now */
  SInt16              kernValue[1];           /* actual kerning values reference by index in kernIndex */
  UInt8               leftClass[1];           /* maps left glyph to offset into kern index */
  UInt8               rightClass[1];          /* maps right glyph to offset into kern index */
  UInt8               kernIndex[1];           /* contains indicies into kernValue */
};
typedef struct KernIndexArrayHeader     KernIndexArrayHeader;
/* format specific part of subtable header */
union KernFormatSpecificHeader {
  KernOrderedListHeader  orderedList;
  KernStateHeader     stateTable;
  KernSimpleArrayHeader  simpleArray;
  KernIndexArrayHeader  indexArray;
};
typedef union KernFormatSpecificHeader  KernFormatSpecificHeader;
/* version 0 subtable header */
struct KernVersion0SubtableHeader {
  UInt16              version;                /* kerning table version number */
  UInt16              length;                 /* length in bytes (including this header) */
  KernSubtableInfo    stInfo;                 /* sub-table info */
  KernFormatSpecificHeader  fsHeader;         /* format specific sub-header */
};
typedef struct KernVersion0SubtableHeader KernVersion0SubtableHeader;
/* Overall Subtable header format */
struct KernSubtableHeader {
  SInt32              length;                 /* length in bytes (including this header) */
  KernSubtableInfo    stInfo;                 /* subtable info */
  SInt16              tupleIndex;             /* tuple index for variation subtables */
  KernFormatSpecificHeader  fsHeader;         /* format specific sub-header */
};
typedef struct KernSubtableHeader       KernSubtableHeader;
typedef KernSubtableHeader *            KernSubtableHeaderPtr;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'kerx' */
/* CONSTANTS */
enum {
  kKERXTag                      = 0x6B657278, /* 'kerx' */
  kKERXCurrentVersion           = 0x00020000,
  kKERXVertical                 = (int)0x80000000, /* set if this table has vertical kerning information */
  kKERXResetCrossStream         = 0x8000, /* this value in a cross-stream table means reset to zero */
  kKERXCrossStream              = 0x40000000, /* set if this table contains cross-stream kerning values */
  kKERXVariation                = 0x20000000, /* set if this table contains variation kerning values */
  kKERXDescending               = 0x10000000,
  kKERXUnusedBits               = 0x0FFFFF00, /* UNUSED, MUST BE ZERO */
  kKERXFormatMask               = 0x000000FF /* format of this subtable */
};

enum {
  kKERXOrderedList              = 0,    /* ordered list of kerning pairs */
  kKERXStateTable               = 1,    /* state table for n-way contextual kerning */
  kKERXSimpleArray              = 2,    /* simple n X m array of kerning values */
  kKERXIndexArray               = 3,    /* modified version of SimpleArray */
  kKERXControlPoint             = 4     /* state table for control point positioning */
};

/* Message Type Flags */
enum {
  kKERXLineStart                = 0x00000001, /* Array of glyphs starts a line */
  kKERXLineEndKerning           = 0x00000002, /* Array of glyphs ends a line */
  kKERXNoCrossKerning           = 0x00000004, /* Prohibit cross kerning */
  kKERXNotesRequested           = 0x00000008, /* Caller wants kerning notes */
  kKERXNoStakeNote              = 1,    /* Indicates a glyph was involved in a kerning pair/group */
  kKERXCrossStreamResetNote     = 2,    /* Indicates a return-to-baseline in cross-stream kerning */
  kKERXNotApplied               = 0x00000001 /* All kerning values were zero, kerning call had no effect */
};

/* Flags in KerxControlPointHeader */
enum {
  kKERXActionTypeMask           = (3U << 30), /* Mask to extract action type */
  kKERXActionTypeControlPoints  = (0U << 30), /* Actions have control point numbers */
  kKERXActionTypeAnchorPoints   = (1U << 30), /* Actions have anchor point numbers */
  kKERXActionTypeCoordinates    = (2U << 30), /* Actions have control point coordinates */
  kKERXUnusedFlags              = 0x3F000000, /* Unused, must be zero */
  kKERXActionOffsetMask         = 0x00FFFFFF, /* Mask to extract offset to action table */
};

/* TYPES */
typedef UInt32                          KerxSubtableCoverage;
typedef UInt32                          KerxArrayOffset;
/* Header for an extended kerning table */
struct KerxTableHeader {
  Fixed               version;                /* font version number (currently 1.0) */
  UInt32              nTables;                /* number of subtables present */
  UInt32              firstSubtable[1];       /* first subtable starts here */
};
typedef struct KerxTableHeader          KerxTableHeader;
typedef KerxTableHeader *               KerxTableHeaderPtr;
typedef KerxTableHeaderPtr *            KerxTableHeaderHandle;
/*
 F O R M A T   S P E C I F I C   D E F I N I T I O N S
 
 kerxOrderedList:
 
 The table is a sorted list of [left glyph, right glyph, value] triples.
 There's enough information in the header so that the list can be
 efficiently binary searched. 
 */
/* defines a single kerning pair of Glyphcodes  */
struct KerxKerningPair {
  UInt16              left;
  UInt16              right;
};
typedef struct KerxKerningPair          KerxKerningPair;
/* a single list entry */
struct KerxOrderedListEntry {
  KerxKerningPair     pair;                   /* the kerning pair */
  KernKerningValue    value;                  /* the kerning value for the above pair */
};
typedef struct KerxOrderedListEntry     KerxOrderedListEntry;
typedef KerxOrderedListEntry *          KerxOrderedListEntryPtr;
/* the header information for binary searching the list */
struct KerxOrderedListHeader {
  UInt32              nPairs;                 /* number of kerning pairs in table */
  UInt32              searchRange;            /* (largest power of two <= nPairs) * entry size */
  UInt32              entrySelector;          /* log2 (largest power of two <= nPairs) */
  UInt32              rangeShift;             /* (nPairs - largest power of two <= nPairs) * entry size */
  UInt32              table[1];               /* entries are first glyph, second glyph, and value */
};
typedef struct KerxOrderedListHeader    KerxOrderedListHeader;
/* KernStateTable: like the the generic state tables */
struct KerxStateHeader {
  STXHeader           header;                 /* state table header */
  UInt32              valueTable;             /* offset to kerning value table */
  UInt8               firstTable[1];          /* first table starts here */
};
typedef struct KerxStateHeader          KerxStateHeader;
struct KerxStateEntry {
  UInt16              newState;
  UInt16              flags;                  /* flags per above enum */
  UInt16              valueIndex;
};
typedef struct KerxStateEntry           KerxStateEntry;
/* KerxControlPointTable: like the the generic state tables */
struct KerxControlPointHeader {
  STXHeader           header;                 /* state table header */
  UInt32              flags;                  /* flags */
  UInt8               firstTable[1];          /* first table starts here */
};
typedef struct KerxControlPointHeader   KerxControlPointHeader;
struct KerxControlPointEntry {
  UInt16              newState;
  UInt16              flags;                  /* flags per above enum */
  UInt16              actionIndex;
};
typedef struct KerxControlPointEntry    KerxControlPointEntry;
struct KerxControlPointAction {
  UInt16              markControlPoint;
  UInt16              currControlPoint;
};
typedef struct KerxControlPointAction   KerxControlPointAction;
struct KerxAnchorPointAction {
  UInt16              markAnchorPoint;
  UInt16              currAnchorPoint;
};
typedef struct KerxAnchorPointAction   KerxAnchorPointAction;
struct KerxCoordinateAction {
  UInt16              markX;
  UInt16              markY;
  UInt16              currX;
  UInt16              currY;
};
typedef struct KerxCoordinateAction     KerxCoordinateAction;
/*
 KerxSimpleArray:
 
 The array is an nXm array of kerning values. Each row in the array
 represents one left-hand glyph, and each column one right-hand glyph.
 The zeroth row and column always represent glyphs that are out of bounds
 and will always contain zero.
 
 A pair is looked up by indexing the left-hand glyph through the left
 offset table, the right-hand glyph through the right offset table,
 adding both offsets to the starting address of the kerning array,
 and fetching the kerning value pointed to.
 */
struct KerxSimpleArrayHeader {
  UInt32              rowWidth;               /* width, in bytes, of a row in the table */
  UInt32              leftOffsetTable;        /* offset to left-hand offset table */
  UInt32              rightOffsetTable;       /* offset to right-hand offset table */
  KerxArrayOffset     theArray;               /* offset to start of kerning array */
  UInt32              firstTable[1];          /* first offset table starts here... */
};
typedef struct KerxSimpleArrayHeader    KerxSimpleArrayHeader;
/* Index Array */
struct KerxIndexArrayHeader {
  UInt16              glyphCount;
  UInt16              kernValueCount;
  UInt16              leftClassCount;
  UInt16              rightClassCount;
  UInt16              flags;                  /* set to 0 for now */
  SInt16              kernValue[1];           /* actual kerning values reference by index in kernIndex */
  UInt16              leftClass[1];           /* maps left glyph to offset into kern index */
  UInt16              rightClass[1];          /* maps right glyph to offset into kern index */
  UInt16              kernIndex[1];           /* contains indicies into kernValue */
};
typedef struct KerxIndexArrayHeader     KerxIndexArrayHeader;
/* format specific part of subtable header */
union KerxFormatSpecificHeader {
  KerxOrderedListHeader  orderedList;
  KerxStateHeader     stateTable;
  KerxSimpleArrayHeader  simpleArray;
  KerxIndexArrayHeader  indexArray;
  KerxControlPointHeader  controlPoint;

};
typedef union KerxFormatSpecificHeader  KerxFormatSpecificHeader;
/* Overall Subtable header format */
struct KerxSubtableHeader {
  UInt32              length;                 /* length in bytes (including this header) */
  KerxSubtableCoverage  stInfo;               /* subtable coverage */
  UInt32              tupleIndex;             /* tuple index for variation subtables */
  KerxFormatSpecificHeader  fsHeader;         /* format specific sub-header */
};
typedef struct KerxSubtableHeader       KerxSubtableHeader;
typedef KerxSubtableHeader *            KerxSubtableHeaderPtr;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'bsln' */
/* CONSTANTS */
enum {
  kBSLNTag                      = 0x62736C6E, /* 'bsln' */
  kBSLNCurrentVersion           = 0x00010000, /* current version number for 'bsln' table */
  kBSLNDistanceFormatNoMap      = 0,
  kBSLNDistanceFormatWithMap    = 1,
  kBSLNControlPointFormatNoMap  = 2,
  kBSLNControlPointFormatWithMap = 3
};

/* Baseline classes and constants */
enum {
  kBSLNRomanBaseline            = 0,
  kBSLNIdeographicCenterBaseline = 1,
  kBSLNIdeographicLowBaseline   = 2,
  kBSLNHangingBaseline          = 3,
  kBSLNMathBaseline             = 4,
  kBSLNIdeographicHighBaseline  = 5,
  kBSLNLastBaseline             = 31,
  kBSLNNumBaselineClasses       = kBSLNLastBaseline + 1,
  kBSLNNoBaseline               = 255,
  kBSLNNoBaselineOverride       = 255
};

/* TYPES */
typedef UInt32                          BslnBaselineClass;
/* The BslnBaselineRecord array defines the baseline deltas for the line. */
typedef Fixed                           BslnBaselineRecord[32];
/*
    BslnFormat0Part is the format-specific data for a distance table with no mapping (i.e.
    all the glyphs belong to the defaultBaseline).
*/
struct BslnFormat0Part {
  SInt16              deltas[32];
};
typedef struct BslnFormat0Part          BslnFormat0Part;
/* BslnFormat1Part is the format-specific data for a distance table with a gxMapping. */
struct BslnFormat1Part {
  SInt16              deltas[32];
  SFNTLookupTable     mappingData;
};
typedef struct BslnFormat1Part          BslnFormat1Part;
/*
    BslnFormat2Part is the format-specific data for a control-point table with no
    mapping (i.e. all the glyphs belong to the defaultBaseline). It specifies a single
    glyph to use and the set of control points in that glyph that designate each of
    the baselines.
*/
struct BslnFormat2Part {
  UInt16              stdGlyph;
  SInt16              ctlPoints[32];
};
typedef struct BslnFormat2Part          BslnFormat2Part;
/*
    BslnFormat3Part is the format-specific data for a distance table with a mapping. Like
    format 2, it contains a single glyph and its set of control-point values for each
    of the baselines.
*/
struct BslnFormat3Part {
  UInt16              stdGlyph;
  SInt16              ctlPoints[32];
  SFNTLookupTable     mappingData;
};
typedef struct BslnFormat3Part          BslnFormat3Part;
/* The BslnFormatUnion is a union containing the format-specific parts of the baseline table. */
union BslnFormatUnion {
  BslnFormat0Part     fmt0Part;
  BslnFormat1Part     fmt1Part;
  BslnFormat2Part     fmt2Part;
  BslnFormat3Part     fmt3Part;
};
typedef union BslnFormatUnion           BslnFormatUnion;
/* The table format used in BaselineTable */

typedef UInt16                          BslnTableFormat;
/* BaselineTable defines the top-level format of the baseline table in the font. */
struct BslnTable {
  Fixed               version;
  BslnTableFormat     format;
  UInt16              defaultBaseline;
  BslnFormatUnion     parts;
};
typedef struct BslnTable                BslnTable;
typedef BslnTable *                     BslnTablePtr;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'ALMX' */
/* TYPES */
struct ALMXHeader {
  Fixed               Version;                /* 16.16 format 1.0 by default */
  UInt16              Flags;
  UInt16              NMasters;
  UInt16              FirstGlyph;
  UInt16              LastGlyph;

  SFNTLookupTable     lookup;                 /* lookup table */
};
typedef struct ALMXHeader               ALMXHeader;
struct ALMXGlyphEntry {                       /* lookup data for ALMX table */
  SInt16              GlyphIndexOffset;
  SInt16              HorizontalAdvance;
  SInt16              XOffsetToHOrigin;
  SInt16              VerticalAdvance;
  SInt16              YOffsetToVOrigin;
};
typedef struct ALMXGlyphEntry           ALMXGlyphEntry;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE: 'ROTA' */
/* TYPES */
struct ROTAHeader {
  Fixed               Version;                /* 16.16 format 1.0 by default */
  UInt16              Flags;
  UInt16              NMasters;
  UInt16              FirstGlyph;
  UInt16              LastGlyph;

  SFNTLookupTable     lookup;                 /* lookup table */
};
typedef struct ROTAHeader               ROTAHeader;
struct ROTAGlyphEntry {                       /* lookup data for ROTA table */
  SInt16              GlyphIndexOffset;
  SInt16              HBaselineOffset;        /* y offset to the rotated horizontal baseline */
  SInt16              VBaselineOffset;        /* x offset to the rotated vertical baseline */
};
typedef struct ROTAGlyphEntry           ROTAGlyphEntry;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE 'ankr' */
/* CONSTANTS */
enum {
  kANKRCurrentVersion = 0
};

/* TYPES */
struct AnchorPoint {
  SInt16               x;                     /* x coordinate of anchor point */
  SInt16               y;                     /* y coordinate of anchor point */
};
typedef struct AnchorPoint              AnchorPoint;

struct AnchorPointTable {
  UInt32              nPoints;                /* number of anchor points defined for this glyph */
  AnchorPoint         points[1];              /* first anchor point starts here */
};
typedef struct AnchorPointTable         AnchorPointTable;

struct AnkrTable {
  UInt16              version;                /* 0 */
  UInt16              flags;                  /* never leave home without them (see 'Zapf') */
  UInt32              lookupTableOffset;      /* Byte offset to lookup table mapping glyphs to offset into anchor point table */
  UInt32              anchorPointTableOffset; /* Byte offset to start of anchor point table */
};
typedef struct AnkrTable                AnkrTable;
/* --------------------------------------------------------------------------- */
/* FORMATS FOR TABLE 'ltag' */
/* CONSTANTS */
enum {
  kLTAGCurrentVersion = 1
};

/* TYPES */
struct LtagStringRange {
  UInt16               offset;                /* offset to the beginning of the string */
  UInt16               length;                /* string length in bytes */
};
typedef struct LtagStringRange          LtagStringRange;

struct LtagTable {
  UInt32              version;                /* 1 */
  UInt32              flags;                  /* none currently defined */
  UInt32              numTags;                /* number of language tags which follow */
  LtagStringRange     tagRange[1];            /* first string range starts here */
};
typedef struct LtagTable                LtagTable;
/* --------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // __SFNTLAYOUTTYPES__
// ==========  CoreText.framework/Headers/CTFontTraits.h
/*
 *  CTFontTraits.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTFONTTRAITS__
#define __CTFONTTRAITS__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
    @defined    kCTFontSymbolicTrait
    @abstract   Dictionary key to access the symbolic traits value.
    @discussion Use this key to access the symbolic traits value from the font traits dictionary. The value is returned as a CFNumberRef.
*/
extern const CFStringRef kCTFontSymbolicTrait CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontWeightTrait
    @abstract   Dictionary key to access the weight trait value.
    @discussion Use this key to access the normalized weight trait from the font traits dictionary. The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized weight. The value of 0.0 corresponds to the regular or medium font weight.
*/
extern const CFStringRef kCTFontWeightTrait CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontWidthTrait
    @abstract   Dictionary key to access the width (condense/expand) trait value.
    @discussion Use this key to access the normalized proportion trait from the font traits dictionary. This value corresponds to the relative inter-glyph spacing for a given font. The value returned is a CFNumberRef representing a float between -1.0 and 1.0. The value of 0.0 corresponds to regular glyph spacing while negative values represent condensed glyph spacing.
*/
extern const CFStringRef kCTFontWidthTrait CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontSlantTrait
    @abstract   Dictionary key to access the slant trait value.
    @discussion Use this key to access the normalized slant angle from the font traits dictionary. The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized slant angle. The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
*/
extern const CFStringRef kCTFontSlantTrait CT_AVAILABLE(10_5, 3_2);

/*!
    @const      kCTFontClassMaskShift
    @abstract   The font class shift.
    @discussion This is used to shift the font class to the upper most 4 bits of the symbolic traits.
*/
enum {
    kCTFontClassMaskShift = 28
};

/*!
    @enum       CTFontSymbolicTraits
    @abstract   Symbolic representation of stylistic font attributes.
    @discussion CTFontSymbolicTraits symbolically describes stylistic aspects of a font. The top 4 bits is used to describe appearance of the font while the lower 28 bits for typeface. The font appearance information represented by the upper 4 bits can be used for stylistic font matching.
*/
typedef CF_OPTIONS(uint32_t, CTFontSymbolicTraits) {
    kCTFontTraitItalic              = (1 << 0),     // Additional detail available via kCTFontSlantTrait
    kCTFontTraitBold                = (1 << 1),     // Additional detail available via kCTFontWeightTrait
    kCTFontTraitExpanded            = (1 << 5),     // Expanded and condensed traits are mutually exclusive
    kCTFontTraitCondensed           = (1 << 6),     // Additional detail available via kCTFontWidthTrait
    kCTFontTraitMonoSpace           = (1 << 10),    // Use fixed-pitch glyphs if available. May have multiple glyph advances (most CJK glyphs may contain two spaces)
    kCTFontTraitVertical            = (1 << 11),    // Use vertical glyph variants and metrics
    kCTFontTraitUIOptimized         = (1 << 12),    // Synthesize appropriate attributes for UI rendering such as control titles if necessary
    kCTFontTraitColorGlyphs         = (1 << 13),    // Color bitmap glyphs are available. 
    kCTFontTraitComposite           = (1 << 14),    // The font is a CFR (Composite font reference), a cascade list is expected per font. 

    kCTFontTraitClassMask           = (15U << kCTFontClassMaskShift),
                                                    // Mask for the font class

    kCTFontItalicTrait = kCTFontTraitItalic,
    kCTFontBoldTrait = kCTFontTraitBold,
    kCTFontExpandedTrait = kCTFontTraitExpanded,
    kCTFontCondensedTrait = kCTFontTraitCondensed,
    kCTFontMonoSpaceTrait = kCTFontTraitMonoSpace,
    kCTFontVerticalTrait = kCTFontTraitVertical,
    kCTFontUIOptimizedTrait = kCTFontTraitUIOptimized,
    kCTFontColorGlyphsTrait = kCTFontTraitColorGlyphs,
    kCTFontCompositeTrait = kCTFontTraitComposite,
    kCTFontClassMaskTrait = kCTFontTraitClassMask
};

/*!
    @enum       CTFontStylisticClass
    @abstract   Stylistic class values.
    @discussion CTFontStylisticClass classifies certain stylistic qualities of the font. These values correspond closely to the font class values in the OpenType 'OS/2' table. The class values are bundled in the upper four bits of the CTFontSymbolicTraits and can be obtained via the kCTFontClassMaskTrait.
*/
typedef CF_OPTIONS(uint32_t, CTFontStylisticClass) {
    kCTFontClassUnknown             = (0 << kCTFontClassMaskShift),
    kCTFontClassOldStyleSerifs      = (1 << kCTFontClassMaskShift),
    kCTFontClassTransitionalSerifs  = (2 << kCTFontClassMaskShift),
    kCTFontClassModernSerifs        = (3 << kCTFontClassMaskShift),
    kCTFontClassClarendonSerifs     = (4 << kCTFontClassMaskShift),
    kCTFontClassSlabSerifs          = (5 << kCTFontClassMaskShift),
    kCTFontClassFreeformSerifs      = (7 << kCTFontClassMaskShift),
    kCTFontClassSansSerif           = (8U << kCTFontClassMaskShift),
    kCTFontClassOrnamentals         = (9U << kCTFontClassMaskShift),
    kCTFontClassScripts             = (10U << kCTFontClassMaskShift),
    kCTFontClassSymbolic            = (12U << kCTFontClassMaskShift),

    kCTFontUnknownClass = kCTFontClassUnknown,
    kCTFontOldStyleSerifsClass = kCTFontClassOldStyleSerifs,
    kCTFontTransitionalSerifsClass = kCTFontClassTransitionalSerifs,
    kCTFontModernSerifsClass = kCTFontClassModernSerifs,
    kCTFontClarendonSerifsClass = kCTFontClassClarendonSerifs,
    kCTFontSlabSerifsClass = kCTFontClassSlabSerifs,
    kCTFontFreeformSerifsClass = kCTFontClassFreeformSerifs,
    kCTFontSansSerifClass = kCTFontClassSansSerif,
    kCTFontOrnamentalsClass = kCTFontClassOrnamentals,
    kCTFontScriptsClass = kCTFontClassScripts,
    kCTFontSymbolicClass = kCTFontClassSymbolic
};

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif
// ==========  CoreText.framework/Headers/CTTypesetter.h
/*
 *	CTTypesetter.h
 *	CoreText
 *
 *	Copyright (c) 2003-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTTYPESETTER__
#define __CTTYPESETTER__

#include <CoreText/CTDefines.h>
#include <CoreText/CTLine.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Typesetter Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTTypesetter * CTTypesetterRef;


/*!
	@function	CTTypesetterGetTypeID
	@abstract	Returns the CFType of the typesetter object
*/

CFTypeID CTTypesetterGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Typesetter Values */
/* --------------------------------------------------------------------------- */

/*!
	@const		kCTTypesetterOptionDisableBidiProcessing
	@abstract	Disables bidi processing.
	@discussion	Value must be a CFBooleanRef. Default is false.
				Normally, typesetting applies the Unicode Bidirectional
				Algorithm as described in UAX #9. If a typesetter is created
				with this option set to true, no directional reordering is
				performed and any directional control characters are ignored.
*/

extern const CFStringRef kCTTypesetterOptionDisableBidiProcessing CT_DEPRECATED(10_5, 10_8, 3_2, 6_0);

/*!
	@const		kCTTypesetterOptionForcedEmbeddingLevel
	@abstract	Specifies the embedding level.
	@discussion	Value must be a CFNumberRef. Default is unset. Normally,
				typesetting applies the Unicode Bidirectional Algorithm as
				described in UAX #9. If present, this specifies the embedding
				level and any directional control characters are ignored.
*/

extern const CFStringRef kCTTypesetterOptionForcedEmbeddingLevel CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Typesetter Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTypesetterCreateWithAttributedString
	@abstract	Creates an immutable typesetter object using an attributed
				string.

	@discussion The resultant typesetter can be used to create lines, perform
				line breaking, and do other contextual analysis based on the
				characters in the string.

	@param		string
				The CFAttributedStringRef that you want to typeset. This
				parameter must be filled in with a valid CFAttributedString.

	@result		This function will return a reference to a CTTypesetter.
*/

CTTypesetterRef CTTypesetterCreateWithAttributedString(
	CFAttributedStringRef string ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTTypesetterCreateWithAttributedStringAndOptions
	@abstract	Creates an immutable typesetter object using an attributed
				string and a dictionary of options.

	@discussion The resultant typesetter can be used to create lines, perform
				line breaking, and do other contextual analysis based on the
				characters in the string.

	@param		string
				The CFAttributedStringRef that you want to typeset. This
				parameter must be filled in with a valid CFAttributedString.

	@param		options
				A CFDictionary of typesetter options, or NULL if there are none.

	@result		This function will return a reference to a CTTypesetter.
*/

CTTypesetterRef CTTypesetterCreateWithAttributedStringAndOptions(
	CFAttributedStringRef string,
	CFDictionaryRef __nullable options ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Typeset Line Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTypesetterCreateLineWithOffset
	@abstract	Creates an immutable line from the typesetter.

	@discussion The resultant line will consist of glyphs in the correct visual
				order, ready to draw.

	@param		typesetter
				The typesetter which the line will come from.

	@param		stringRange
				The string range which the line will be based on. If the length
				portion of range is set to 0, then the typesetter will continue
				to add glyphs to the line until it runs out of characters in the
				string. The location and length of the range must be within the
				bounds of the string, otherwise the call will fail.

	@param		offset
				The line position offset.

	@result		This function will return a reference to a CTLine.
*/

CTLineRef CTTypesetterCreateLineWithOffset(
	CTTypesetterRef typesetter,
	CFRange stringRange,
	double offset ) CT_AVAILABLE(10_6, 3_2);

/*!
	@function	CTTypesetterCreateLine
	@abstract	Equivalent to CTTypesetterCreateLineWithOffset with offset = 0.0.
*/

CTLineRef CTTypesetterCreateLine(
	CTTypesetterRef typesetter,
	CFRange stringRange ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Typeset Line Breaking */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTypesetterSuggestLineBreakWithOffset
	@abstract	Suggests a contextual line break point based on the width
				provided.

	@discussion The line break can be triggered either by a hard break character
				in the stream or by filling the specified width with characters.

	@param		typesetter
				The typesetter which the line will come from.

	@param		startIndex
				The starting point for the line break calculations. The break
				calculations will include the character starting at startIndex.

	@param		width
				The requested line break width.

	@param		offset
				The line position offset.

	@result		The value returned is a count of the characters from startIndex
				that would cause the line break. This value returned can be used
				to construct a character range for CTTypesetterCreateLine.
*/

CFIndex CTTypesetterSuggestLineBreakWithOffset(
	CTTypesetterRef typesetter,
	CFIndex startIndex,
	double width,
	double offset ) CT_AVAILABLE(10_6, 3_2);

/*!
	@function	CTTypesetterSuggestLineBreak
	@abstract	Equivalent to CTTypesetterSuggestLineBreakWithOffset with offset = 0.0.
*/

CFIndex CTTypesetterSuggestLineBreak(
	CTTypesetterRef typesetter,
	CFIndex startIndex,
	double width ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTTypesetterSuggestClusterBreakWithOffset
	@abstract	Suggests a cluster line break point based on the width provided.

	@discussion Suggests a typographic cluster line break point based on the width
				provided. This cluster break is similar to a character break,
				except that it will not break apart linguistic clusters. No other
				contextual analysis will be done. This can be used by the caller
				to implement a different line breaking scheme, such as
				hyphenation. Note that a typographic cluster break can also be
				triggered by a hard break character in the stream.

	@param		typesetter
				The typesetter which the line will come from.

	@param		startIndex
				The starting point for the typographic cluster break
				calculations. The break calculations will include the character
				starting at startIndex.

	@param		width
				The requested typographic cluster break width.

	@param		offset
				The line position offset.

	@result		The value returned is a count of the characters from startIndex
				that would cause the cluster break. This value returned can be
				used to construct a character range for CTTypesetterCreateLine.
*/

CFIndex CTTypesetterSuggestClusterBreakWithOffset(
	CTTypesetterRef typesetter,
	CFIndex startIndex,
	double width,
	double offset ) CT_AVAILABLE(10_6, 3_2);


/*!
	@function	CTTypesetterSuggestClusterBreak
	@abstract	Equivalent to CTTypesetterSuggestClusterBreakWithOffset with offset = 0.0.
*/

CFIndex CTTypesetterSuggestClusterBreak(
	CTTypesetterRef typesetter,
	CFIndex startIndex,
	double width ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTFrame.h
/*
 *	CTFrame.h
 *	CoreText
 *
 *	Copyright (c) 2003-2015 Apple Inc. All rights reserved.
 *
 */
 
/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFRAME__
#define __CTFRAME__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Frame Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTFrame * CTFrameRef;


/*!
	@function	CTFrameGetTypeID
	@abstract	Returns the CFType of the frame object
*/

CFTypeID CTFrameGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Frame Values */
/* --------------------------------------------------------------------------- */

/*!
    @enum		CTFrameProgression
    @abstract	These constants specify frame progression types.

    @discussion The lines of text within a frame may be stacked for either
                horizontal or vertical text. Values are enumerated for each
                stacking type supported by CTFrame. Frames created with a
                progression type specifying vertical text will rotate lines
                90 degrees counterclockwise when drawing.

    @constant	kCTFrameProgressionTopToBottom
                Lines are stacked top to bottom for horizontal text.

    @constant	kCTFrameProgressionRightToLeft
                Lines are stacked right to left for vertical text.

    @constant	kCTFrameProgressionLeftToRight
                Lines are stacked left to right for vertical text.
*/

typedef CF_ENUM(uint32_t, CTFrameProgression) {
    kCTFrameProgressionTopToBottom  = 0,
    kCTFrameProgressionRightToLeft  = 1,
    kCTFrameProgressionLeftToRight  = 2
};


/*!
	@const		kCTFrameProgressionAttributeName
	@abstract	Specifies progression for a frame.
	
	@discussion Value must be a CFNumberRef containing a CTFrameProgression.
				Default is kCTFrameProgressionTopToBottom. This value determines
				the line stacking behavior for a frame and does not affect the
				appearance of the glyphs within that frame.

	@seealso	CTFramesetterCreateFrame
*/

extern const CFStringRef kCTFrameProgressionAttributeName CT_AVAILABLE(10_5, 3_2);

/*!
	@enum		CTFramePathFillRule
	@abstract	These constants specify fill rule used by the frame.
 
	@discussion When a path intersects with itself, the client should specify which rule to use for deciding the 
				area of the path.
 
	@constant	kCTFramePathFillEvenOdd
				Text is filled in the area that would be painted if the path were given to CGContextEOFillPath.

	@constant	kCTFramePathFillWindingNumber
				Text is fill in the area that would be painted if the path were given to CGContextFillPath.
 
 
 */

typedef CF_ENUM(uint32_t, CTFramePathFillRule) {
	kCTFramePathFillEvenOdd         = 0,
	kCTFramePathFillWindingNumber   = 1
};


/*!
	@const		kCTFramePathFillRuleAttributeName
	@abstract	Specifies fill rule for a frame if this attribute is used at top level of frameAttributes dictionary, or specify
				fill rule for a clipping path if used in a dictionary contained in an array specified by kCTFrameClippingPathsAttributeName.
				
	@discussion Value must be a CFNumberRef containing kCTFramePathFillEvenOdd or kCTFramePathFillWindingNumber.
				Default is kCTFramePathFillEvenOdd.

	@seealso	CTFramesetterCreateFrame
 */

extern const CFStringRef kCTFramePathFillRuleAttributeName CT_AVAILABLE(10_7, 4_2);

/*!
	@const		kCTFramePathWidthAttributeName
	@abstract	Specifies frame width if this attribute is used at top level of frameAttributes dictionary, or specify
				clipping path width if used in a dictionary contained in an array specified by kCTFrameClippingPathsAttributeName.

	@discussion Value must be a CFNumberRef specifying frame width.
				Default is zero.

	@seealso	CTFramesetterCreateFrame
 */

extern const CFStringRef kCTFramePathWidthAttributeName CT_AVAILABLE(10_7, 4_2);

	
/*!
	@const		kCTFrameClippingPathsAttributeName
	@abstract	Specifies array of paths to clip frame.
	
	@discussion Value must be a CFArrayRef containing CFDictionaryRefs or CGPathRef.  (CGPathRef is allowed on 10.8 or later.)
				Each dictionary should have a kCTFramePathClippingPathAttributeName key-value pair, and can have a kCTFramePathFillRuleAttributeName key-value pair 
				and kCTFramePathFillRuleAttributeName key-value pair as optional parameters.  In case of CGPathRef, default fill rule (kCTFramePathFillEvenOdd) and width (0.0) are used.

	@seealso	CTFramesetterCreateFrame
*/

extern const CFStringRef kCTFrameClippingPathsAttributeName CT_AVAILABLE(10_7, 4_3);

/*!
	@const		kCTFramePathClippingPathAttributeName
	@abstract	Specifies clipping path.  This attribute is valid in a dictionary contained in an array specified by kCTFrameClippingPathsAttributeName.
				On 10.8 or later, This attribute is also valid in frameAttributes dictionary passed to CTFramesetterCreateFrame.

	@discussion Value must be a CGPathRef specifying a clipping path.

	@seealso	kCTFrameClippingPathsAttributeName
 */

extern const CFStringRef kCTFramePathClippingPathAttributeName CT_AVAILABLE(10_7, 4_3);

/* --------------------------------------------------------------------------- */
/* Frame Accessors */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFrameGetStringRange
	@abstract	Returns the range of characters that were originally requested
				to fill the frame.

	@param		frame
				The frame that you want to get the character range from.

	@result		This function will return a CFRange containing the backing
				store range of characters that were originally requested
				to fill the frame. If the function call is not successful,
				then an empty range will be returned.
*/

CFRange CTFrameGetStringRange(
	CTFrameRef frame ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameGetVisibleStringRange
	@abstract	Returns the range of characters that actually fit in the
				frame.

	@discussion This can be used to chain frames, as it returns the range of
				characters that can be seen in the frame. The next frame would
				start where this frame ends.

	@param		frame
				The frame that you want to get the visible character range
				from.

	@result		This function will return a CFRange containing the backing
				store range of characters that fit into the frame. If the
				function call is not successful, or if no characters fit
				in the frame, then an empty range will be returned.
*/

CFRange CTFrameGetVisibleStringRange(
	CTFrameRef frame ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameGetPath
	@abstract	Returns the path used to create the frame.

	@param		frame
				The frame that you want to obtain the path from.
*/

CGPathRef CTFrameGetPath(
	CTFrameRef frame ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameGetFrameAttributes
	@abstract	Returns the frame attributes used to create the frame.

	@discussion It is possible to create a frame with an attributes dictionary
				in order to control various aspects of the framing process.
				These attributes are different from the ones that are used to
				create an attributed string.

	@param		frame
				The frame that you want to obtain the frame attributes from.

	@result		This function will return a CFDictionary containing the
				frame attributes that were used to create the frame. If the
				frame was created without any frame attributes, this function
				will return NULL.
*/

CFDictionaryRef __nullable CTFrameGetFrameAttributes(
	CTFrameRef frame ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameGetLines
	@abstract	Returns an array of lines that make up the frame.

	@discussion This function will return an array of CTLine objects that are
				stored in the frame. These line objects can be accessed and
				manipulated in any way that normal line objects can be. It is
				possible that an empty frame exists. That is, a frame in which
				no lines exist. In this case, the returned array will have 0
				entries.

	@param		frame
				The frame that you want to obtain the line array from.

	@result		This function will return a CFArray object containing the
				CTLine objects that make up the frame.
*/

CFArrayRef CTFrameGetLines(
	CTFrameRef frame ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameGetLineOrigins
	@abstract	Copies a range of line origins for a frame.

	@discussion	This function will copy a range of CGPoint structures. Each
				CGPoint is the origin of the corresponding line in the array of
				lines returned by CTFrameGetLines, relative to the origin of the
				frame's path. The maximum number of line origins returned by
				this function is the count of the array of lines.

	@param		frame
				The frame that you want to obtain the line origin array from.

	@param		range
				The range of line origins you wish to copy. If the length of the
				range is set to 0, then the copy operation will continue from
				the range's start index to the last line origin.

	@param		origins
				The buffer to which the origins will be copied. The buffer must
				have at least as many elements as specified by range's length.
				When using the origins to calculate measurements for a frame's
				contents, remember that line origins do not always correspond to
				line metrics; paragraph style settings can affect line origins,
				for one. The overall typographic bounds of a frame may generally
				be calculated as the difference between the top of the frame and
				the descent of the last line. This will obviously exclude any
				spacing following the last line, but such spacing has no effect
				on framesetting in the first place.
*/

void CTFrameGetLineOrigins(
	CTFrameRef frame,
	CFRange range,
	CGPoint origins[] ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFrameDraw
	@abstract	Draws an entire frame to a context.

	@discussion This function will draw an entire frame to the context. Note
				that this call may leave the context in any state and does not
				flush it after the draw operation.

	@param		frame
				The frame that you want to draw.

	@param		context
				The context to draw the frame to.

	@result		If both the frame and the context are valid, the frame will be
				drawn in the context.
*/

void CTFrameDraw(
	CTFrameRef frame,
	CGContextRef context ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTRun.h
/*
 *  CTRun.h
 *  CoreText
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTRUN__
#define __CTRUN__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Glyph Run Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTRun * CTRunRef;


/*!
    @enum       CTRunStatus
    @abstract   A bitfield passed back by CTRunGetStatus that is used to
                indicate the disposition of the run.

    @constant   kCTRunStatusNoStatus
                The run has no special attributes.

    @constant   kCTRunStatusRightToLeft
                When set, the run is right to left.

    @constant   kCTRunStatusNonMonotonic
                When set, the run has been reordered in some way such that
                the string indices associated with the glyphs are no longer
                strictly increasing (for left to right runs) or decreasing
                (for right to left runs).

    @constant   kCTRunStatusHasNonIdentityMatrix
                When set, the run requires a specific text matrix to be set
                in the current CG context for proper drawing.
*/

typedef CF_OPTIONS(uint32_t, CTRunStatus)
{
    kCTRunStatusNoStatus = 0,
    kCTRunStatusRightToLeft = (1 << 0),
    kCTRunStatusNonMonotonic = (1 << 1),
    kCTRunStatusHasNonIdentityMatrix = (1 << 2)
};

 
/*!
    @function   CTRunGetTypeID
    @abstract   Returns the CFType of the run object
*/

CFTypeID CTRunGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Run Access */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTRunGetGlyphCount
    @abstract   Gets the glyph count for the run.

    @param      run
                The run whose glyph count you wish to access.

    @result     The number of glyphs that the run contains. It is totally
                possible that this function could return a value of zero,
                indicating that there are no glyphs in this run.
*/

CFIndex CTRunGetGlyphCount(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetAttributes
    @abstract   Returns the attribute dictionary that was used to create the
                glyph run.

    @discussion This dictionary returned is either the same exact one that was
                set as an attribute dictionary on the original attributed string
                or a dictionary that has been manufactured by the layout engine.
                Attribute dictionaries can be manufactured in the case of font
                substitution or if they are missing critical attributes.

    @param      run
                The run whose attributes you wish to access.

    @result     The attribute dictionary.
*/

CFDictionaryRef CTRunGetAttributes(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetStatus
    @abstract   Returns the run's status.

    @discussion In addition to attributes, runs also have status that can be
                used to expedite certain operations. Knowing the direction and
                ordering of a run's glyphs can aid in string index analysis,
                whereas knowing whether the positions reference the identity
                text matrix can avoid expensive comparisons. Note that this
                status is provided as a convenience, since this information is
                not strictly necessary but can certainly be helpful.

    @param      run
                The run whose status you wish to access.

    @result     The run's status.
*/

CTRunStatus CTRunGetStatus(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetGlyphsPtr
    @abstract   Returns a direct pointer for the glyph array stored in the run.

    @discussion The glyph array will have a length equal to the value returned by
                CTRunGetGlyphCount. The caller should be prepared for this
                function to return NULL even if there are glyphs in the stream.
                Should this function return NULL, the caller will need to
                allocate their own buffer and call CTRunGetGlyphs to fetch the
                glyphs.

    @param      run
                The run whose glyphs you wish to access.

    @result     A valid pointer to an array of CGGlyph structures or NULL.
*/

const CGGlyph * __nullable CTRunGetGlyphsPtr(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetGlyphs
    @abstract   Copies a range of glyphs into user-provided buffer.

    @param      run
                The run whose glyphs you wish to copy.

    @param      range
                The range of glyphs to be copied, with the entire range having a
                location of 0 and a length of CTRunGetGlyphCount. If the length
                of the range is set to 0, then the operation will continue from
                the range's start index to the end of the run.

    @param      buffer
                The buffer where the glyphs will be copied to. The buffer must be
                allocated to at least the value specified by the range's length.
*/

void CTRunGetGlyphs(
    CTRunRef run,
    CFRange range,
    CGGlyph buffer[] ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetPositionsPtr
    @abstract   Returns a direct pointer for the glyph position array stored in
                the run.

    @discussion The glyph positions in a run are relative to the origin of the
                line containing the run. The position array will have a length
                equal to the value returned by CTRunGetGlyphCount. The caller
                should be prepared for this function to return NULL even if there
                are glyphs in the stream. Should this function return NULL, the
                caller will need to allocate their own buffer and call
                CTRunGetPositions to fetch the positions.

    @param      run
                The run whose positions you wish to access.

    @result     A valid pointer to an array of CGPoint structures or NULL.
*/

const CGPoint * __nullable CTRunGetPositionsPtr(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetPositions
    @abstract   Copies a range of glyph positions into a user-provided buffer.

    @discussion The glyph positions in a run are relative to the origin of the
                line containing the run.

    @param      run
                The run whose positions you wish to copy.

    @param      range
                The range of glyph positions to be copied, with the entire range
                having a location of 0 and a length of CTRunGetGlyphCount. If the
                length of the range is set to 0, then the operation will continue
                from the range's start index to the end of the run.

    @param      buffer
                The buffer where the glyph positions will be copied to. The buffer
                must be allocated to at least the value specified by the range's
                length.
*/

void CTRunGetPositions(
    CTRunRef run,
    CFRange range,
    CGPoint buffer[] ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetAdvancesPtr
    @abstract   Returns a direct pointer for the glyph advance array stored in
                the run.

    @discussion The advance array will have a length equal to the value returned
                by CTRunGetGlyphCount. The caller should be prepared for this
                function to return NULL even if there are glyphs in the stream.
                Should this function return NULL, the caller will need to
                allocate their own buffer and call CTRunGetAdvances to fetch the
                advances. Note that advances alone are not sufficient for correctly
                positioning glyphs in a line, as a run may have a non-identity
                matrix or the initial glyph in a line may have a non-zero origin;
                callers should consider using positions instead.

    @param      run
                The run whose advances you wish to access.

    @result     A valid pointer to an array of CGSize structures or NULL.
*/

const CGSize * __nullable CTRunGetAdvancesPtr(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetAdvances
    @abstract   Copies a range of glyph advances into a user-provided buffer.

    @param      run
                The run whose advances you wish to copy.

    @param      range
                The range of glyph advances to be copied, with the entire range
                having a location of 0 and a length of CTRunGetGlyphCount. If the
                length of the range is set to 0, then the operation will continue
                from the range's start index to the end of the run.

    @param      buffer
                The buffer where the glyph advances will be copied to. The buffer
                must be allocated to at least the value specified by the range's
                length.
*/

void CTRunGetAdvances(
    CTRunRef run,
    CFRange range,
    CGSize buffer[] ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetStringIndicesPtr
    @abstract   Returns a direct pointer for the string indices stored in the run.

    @discussion The indices are the character indices that originally spawned the
                glyphs that make up the run. They can be used to map the glyphs in
                the run back to the characters in the backing store. The string
                indices array will have a length equal to the value returned by
                CTRunGetGlyphCount. The caller should be prepared for this
                function to return NULL even if there are glyphs in the stream.
                Should this function return NULL, the caller will need to allocate
                their own buffer and call CTRunGetStringIndices to fetch the
                indices.

    @param      run
                The run whose string indices you wish to access.

    @result     A valid pointer to an array of CFIndex structures or NULL.
*/

const CFIndex * __nullable CTRunGetStringIndicesPtr(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetStringIndices
    @abstract   Copies a range of string indices int o a user-provided buffer.

    @discussion The indices are the character indices that originally spawned the
                glyphs that make up the run. They can be used to map the glyphs
                in the run back to the characters in the backing store.

    @param      run
                The run whose string indices you wish to copy.

    @param      range
                The range of string indices to be copied, with the entire range
                having a location of 0 and a length of CTRunGetGlyphCount. If the
                length of the range is set to 0, then the operation will continue
                from the range's start index to the end of the run.

    @param      buffer
                The buffer where the string indices will be copied to. The buffer
                must be allocated to at least the value specified by the range's
                length.
*/

void CTRunGetStringIndices(
    CTRunRef run,
    CFRange range,
    CFIndex buffer[] ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetStringRange
    @abstract   Gets the range of characters that originally spawned the glyphs
                in the run.

    @param      run
                The run whose string range you wish to access.

    @result     Returns the range of characters that originally spawned the
                glyphs. If run is invalid, this will return an empty range.
*/

CFRange CTRunGetStringRange(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetTypographicBounds
    @abstract   Gets the typographic bounds of the run.

    @param      run
                The run that you want to calculate the typographic bounds for.

    @param      range
                The range of glyphs to be measured, with the entire range having
                a location of 0 and a length of CTRunGetGlyphCount. If the length
                of the range is set to 0, then the operation will continue from
                the range's start index to the end of the run.

    @param      ascent
                Upon return, this parameter will contain the ascent of the run.
                This may be set to NULL if not needed.

    @param      descent
                Upon return, this parameter will contain the descent of the run.
                This may be set to NULL if not needed.

    @param      leading
                Upon return, this parameter will contain the leading of the run.
                This may be set to NULL if not needed.

    @result     The typographic width of the run. If run or range is
                invalid, then this function will always return zero.
*/

double CTRunGetTypographicBounds(
    CTRunRef run,
    CFRange range,
    CGFloat * __nullable ascent,
    CGFloat * __nullable descent,
    CGFloat * __nullable leading ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetImageBounds
    @abstract   Calculates the image bounds for a glyph range.

    @discussion The image bounds for a run is the union of all non-empty glyph
                bounding rects, each positioned as it would be if drawn using
                CTRunDraw using the current context. Note that the result is
                ideal and does not account for raster coverage due to rendering.
                This function is purely a convenience for using glyphs as an
                image and should not be used for typographic purposes.

    @param      run
                The run that you want to calculate the image bounds for.

    @param      context
                The context which the image bounds will be calculated for or NULL,
                in which case the bounds are relative to CGPointZero.

    @param      range
                The range of glyphs to be measured, with the entire range having
                a location of 0 and a length of CTRunGetGlyphCount. If the length
                of the range is set to 0, then the operation will continue from
                the range's start index to the end of the run.

    @result     A rect that tightly encloses the paths of the run's glyphs. The
                rect origin will match the drawn position of the requested range;
                that is, it will be translated by the supplied context's text
                position and the positions of the individual glyphs. If the run
                or range is invalid, CGRectNull will be returned.

    @seealso    CTRunGetTypographicBounds
*/

CGRect CTRunGetImageBounds(
    CTRunRef run,
    CGContextRef __nullable context,
    CFRange range ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunGetTextMatrix
    @abstract   Returns the text matrix needed to draw this run.

    @discussion To properly draw the glyphs in a run, the fields 'tx' and 'ty' of
                the CGAffineTransform returned by this function should be set to
                the current text position.

    @param      run
                The run object from which to get the text matrix.

    @result     A CGAffineTransform.
*/

CGAffineTransform CTRunGetTextMatrix(
    CTRunRef run ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTRunDraw
    @abstract   Draws a complete run or part of one.

    @discussion This is a convenience call, since the run could also be drawn by
                accessing its glyphs, positions, and text matrix. Unlike when
                drawing the entire line containing the run with CTLineDraw, the
                run's underline (if any) will not be drawn, since the underline's
                appearance may depend on other runs in the line. Note that this
                call may leave the graphics context in any state and does not
                flush the context after the draw operation.

    @param      run
                The run that you want to draw.

    @param      context
                The context to draw the run to.

    @param      range
                The range of glyphs to be drawn, with the entire range having a
                location of 0 and a length of CTRunGetGlyphCount. If the length
                of the range is set to 0, then the operation will continue from
                the range's start index to the end of the run.
*/

void CTRunDraw(
    CTRunRef run,
    CGContextRef context,
    CFRange range ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTParagraphStyle.h
/*
 *  CTParagraphStyle.h
 *  CoreText
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTPARAGRAPHSTYLE__
#define __CTPARAGRAPHSTYLE__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFArray.h>
#include <CoreGraphics/CGBase.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Paragraph Style Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_RELATED_TYPE(NSParagraphStyle,,) __CTParagraphStyle * CTParagraphStyleRef;


/*!
    @function   CTParagraphStyleGetTypeID
    @abstract   Returns the CFType of the paragraph style object
*/

CFTypeID CTParagraphStyleGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Paragraph Style Values */
/* --------------------------------------------------------------------------- */

/*!
    @enum       CTTextAlignment
    @abstract   These constants specify text alignment.

    @constant   kCTTextAlignmentLeft
                Text is visually left-aligned.

    @constant   kCTTextAlignmentRight
                Text is visually right-aligned.

    @constant   kCTTextAlignmentCenter
                Text is visually center-aligned.

    @constant   kCTTextAlignmentJustified
                Text is fully justified. The last line in a paragraph is
                naturally aligned.

    @constant   kCTTextAlignmentNatural
                Use the natural alignment of the text's script.
*/

typedef CF_ENUM(uint8_t, CTTextAlignment) {
    kCTTextAlignmentLeft      CT_ENUM_AVAILABLE(10_8, 6_0) = 0,
    kCTTextAlignmentRight     CT_ENUM_AVAILABLE(10_8, 6_0) = 1,
    kCTTextAlignmentCenter    CT_ENUM_AVAILABLE(10_8, 6_0) = 2,
    kCTTextAlignmentJustified CT_ENUM_AVAILABLE(10_8, 6_0) = 3,
    kCTTextAlignmentNatural   CT_ENUM_AVAILABLE(10_8, 6_0) = 4,

    kCTLeftTextAlignment CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTTextAlignmentLeft,
    kCTRightTextAlignment CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTTextAlignmentRight,
    kCTCenterTextAlignment CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTTextAlignmentCenter,
    kCTJustifiedTextAlignment CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTTextAlignmentJustified,
    kCTNaturalTextAlignment CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTTextAlignmentNatural
};


/*!
    @enum       CTLineBreakMode
    @abstract   These constants specify what happens when a line is too long for
                its frame.

    @constant   kCTLineBreakByWordWrapping
                Wrapping occurs at word boundaries, unless the word itself doesn't
                fit on a single line.

    @constant   kCTLineBreakByCharWrapping
                Wrapping occurs before the first character that doesn't fit.

    @constant   kCTLineBreakByClipping
                Lines are simply not drawn past the edge of the frame.

    @constant   kCTLineBreakByTruncatingHead
                Each line is displayed so that the end fits in the frame and the
                missing text is indicated by some kind of ellipsis glyph.

    @constant   kCTLineBreakByTruncatingTail
                Each line is displayed so that the beginning fits in the
                container and the missing text is indicated by some kind of
                ellipsis glyph.

    @constant   kCTLineBreakByTruncatingMiddle
                Each line is displayed so that the beginning and end fit in the
                container and the missing text is indicated by some kind of
                ellipsis glyph in the middle.
*/

typedef CF_ENUM(uint8_t, CTLineBreakMode) {
    kCTLineBreakByWordWrapping = 0,
    kCTLineBreakByCharWrapping = 1,
    kCTLineBreakByClipping = 2,
    kCTLineBreakByTruncatingHead = 3,
    kCTLineBreakByTruncatingTail = 4,
    kCTLineBreakByTruncatingMiddle = 5
};


/*!
    @enum       CTWritingDirection
    @abstract   These constants specify the writing direction

    @constant   kCTWritingDirectionNatural
                The writing direction is algorithmically determined
                using the Unicode Bidirectional Algorithm rules P2 and P3.

    @constant   kCTWritingDirectionLeftToRight
                The writing direction is left to right.

    @constant   kCTWritingDirectionRightToLeft
                The writing direction is right to left.
*/

typedef CF_ENUM(int8_t, CTWritingDirection) {
    kCTWritingDirectionNatural = -1,
    kCTWritingDirectionLeftToRight = 0,
    kCTWritingDirectionRightToLeft = 1
};


/*!
    @enum       CTParagraphStyleSpecifier
    @abstract   These constants are used to query and modify the CTParagraphStyle
                object.

    @discussion Each specifier has a type and a default value associated with it.
                The type must always be observed when setting or fetching the
                value from the CTParagraphStyle object. In addition, some
                specifiers affect the behavior of both the framesetter and
                the typesetter, and others only affect the behavior of the
                framesetter; this is also noted below.

    @constant   kCTParagraphStyleSpecifierAlignment
                The text alignment. Natural text alignment is realized as
                left or right alignment, depending on the line sweep direction
                of the first script contained in the paragraph.

                Type: CTTextAlignment
                Default: kCTNaturalTextAlignment
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierFirstLineHeadIndent
                The distance in points from the leading margin of a frame to
                the beginning of the paragraph's first line. This value is always
                nonnegative.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierHeadIndent
                The distance in points from the leading margin of a text
                container to the beginning of lines other than the first.
                This value is always nonnegative.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierTailIndent
                The distance in points from the margin of a frame to the end of
                lines. If positive, this value is the distance from the leading
                margin (for example, the left margin in left-to-right text).
                If 0 or negative, it's the distance from the trailing margin.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierTabStops
                The CTTextTab objects, sorted by location, that define the tab
                stops for the paragraph style.

                Type: CFArray of CTTextTabRef
                Default: 12 left-aligned tabs, spaced by 28.0 points
                Application: CTFramesetter, CTTypesetter


    @constant   kCTParagraphStyleSpecifierDefaultTabInterval
                The document-wide default tab interval. Tabs after the last
                specified by kCTParagraphStyleSpecifierTabStops are placed at
                integer multiples of this distance (if positive).

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter, CTTypesetter


    @constant   kCTParagraphStyleSpecifierLineBreakMode
                The mode that should be used to break lines when laying out
                the paragraph's text.

                Type: CTLineBreakMode
                Default: kCTLineBreakByWordWrapping
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierLineHeightMultiple
                The line height multiple. The natural line height of the
                receiver is multiplied by this factor (if positive) before
                being constrained by minimum and maximum line height.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierMaximumLineHeight
                The maximum height that any line in the frame will occupy,
                regardless of the font size or size of any attached graphic.
                Glyphs and graphics exceeding this height will overlap
                neighboring lines. A maximum height of 0 implies
                no line height limit. This value is always nonnegative.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierMinimumLineHeight
                The minimum height that any line in the frame will occupy,
                regardless of the font size or size of any attached graphic.
                This value is always nonnegative.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierLineSpacing
                Deprecated.
                Use kCTParagraphStyleSpecifierMaximumLineSpacing, kCTParagraphStyleSpecifierMinimumLineSpacing,
                and kCTParagraphStyleSpecifierLineSpacingAdjustment to control
                space between lines.


    @constant   kCTParagraphStyleSpecifierParagraphSpacing
                The space added at the end of the paragraph to separate it from
                the following paragraph. This value is always nonnegative and is
                determined by adding the previous paragraph's
                kCTParagraphStyleSpecifierParagraphSpacing setting and the
                current paragraph's kCTParagraphStyleSpecifierParagraphSpacingBefore
                setting.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierParagraphSpacingBefore
                The distance between the paragraph's top and the beginning of
                its text content.

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierBaseWritingDirection
                The base writing direction of the lines.

                Type: CTWritingDirection
                Default: kCTWritingDirectionNatural
                Application: CTFramesetter, CTTypesetter


    @constant   kCTParagraphStyleSpecifierMaximumLineSpacing
                The maximum space in points between lines within the paragraph
                (commonly known as leading).

                Type: CGFloat
                Default: some large number.
                Application: CTFramesetter
 
 
    @constant   kCTParagraphStyleSpecifierMinimumLineSpacing
                The minimum space in points between lines within the paragraph
                (commonly known as leading).

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter
 
 
    @constant   kCTParagraphStyleSpecifierLineSpacingAdjustment
                The space in points added between lines within the paragraph
                (commonly known as leading). 

                Type: CGFloat
                Default: 0.0
                Application: CTFramesetter


    @constant   kCTParagraphStyleSpecifierLineBoundsOptions
                The options controlling the alignment of the line edges with
                the leading and trailing margins.

                Type: CTLineBoundsOptions
                Default: 0 (no options)
                Application: CTTypesetter
*/

typedef CF_ENUM(uint32_t, CTParagraphStyleSpecifier) {
    kCTParagraphStyleSpecifierAlignment = 0,
    kCTParagraphStyleSpecifierFirstLineHeadIndent = 1,
    kCTParagraphStyleSpecifierHeadIndent = 2,
    kCTParagraphStyleSpecifierTailIndent = 3,
    kCTParagraphStyleSpecifierTabStops = 4,
    kCTParagraphStyleSpecifierDefaultTabInterval = 5,
    kCTParagraphStyleSpecifierLineBreakMode = 6,
    kCTParagraphStyleSpecifierLineHeightMultiple = 7,
    kCTParagraphStyleSpecifierMaximumLineHeight = 8,
    kCTParagraphStyleSpecifierMinimumLineHeight = 9,
    kCTParagraphStyleSpecifierLineSpacing = 10,			/* deprecated */
    kCTParagraphStyleSpecifierParagraphSpacing = 11,
    kCTParagraphStyleSpecifierParagraphSpacingBefore = 12,
    kCTParagraphStyleSpecifierBaseWritingDirection = 13,
    kCTParagraphStyleSpecifierMaximumLineSpacing = 14,
    kCTParagraphStyleSpecifierMinimumLineSpacing = 15,
    kCTParagraphStyleSpecifierLineSpacingAdjustment = 16,
    kCTParagraphStyleSpecifierLineBoundsOptions = 17,

    kCTParagraphStyleSpecifierCount
};


/*!
    @struct     CTParagraphStyleSetting
    @abstract   This structure is used to alter the paragraph style.

    @field      spec
                The specifier of the setting.

    @field      valueSize
                The size of the value pointed to by the "value" field. This
                must match the size of the value required by the
                CTParagraphStyleSpecifier set in the "spec" field.

    @field      value
                A reference to the value of the setting specified by the
                "spec" field. The value must be in the proper range for the
                spec value. The value must also be at least valueSize.
*/
typedef struct CTParagraphStyleSetting
{
    CTParagraphStyleSpecifier spec;
    size_t valueSize;
    const void * value;

} CTParagraphStyleSetting;


/* --------------------------------------------------------------------------- */
/* Paragraph Style Creation */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTParagraphStyleCreate
    @abstract   Creates an immutable paragraph style.

    @discussion Using this function is the easiest and most efficient way to
                create a paragraph style. Paragraph styles should be kept
                immutable for totally lock-free operation.

                If an invalid paragraph style setting specifier is passed into
                the "settings" parameter, nothing bad will happen but just don't
                expect to be able to query for this value. This is to allow
                backwards compatibility with style setting specifiers that may
                be introduced in future versions.

    @param      settings
                The settings that you wish to pre-load the paragraph style
                with. If you wish to specify the default set of settings,
                then this parameter may be set to NULL.

    @param      settingCount
                The number of settings that you have specified in the
                "settings" parameter. This must be greater than or equal
                to zero.

    @result     If the paragraph style creation was successful, this function
                will return a valid reference to an immutable CTParagraphStyle
                object. Otherwise, this function will return NULL.
*/

CTParagraphStyleRef CTParagraphStyleCreate(
    const CTParagraphStyleSetting * __nullable settings,
    size_t settingCount ) CT_AVAILABLE(10_5, 3_2);


/*!
    @function   CTParagraphStyleCreateCopy
    @abstract   Creates an immutable copy of a paragraph style.

    @param      paragraphStyle
                The style that you wish to copy.

    @result     If the "paragraphStyle" reference is valid, then this
                function will return valid reference to an immutable
                CTParagraphStyle object that is a copy of the one passed into
                "paragraphStyle".
*/

CTParagraphStyleRef CTParagraphStyleCreateCopy(
    CTParagraphStyleRef paragraphStyle ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Paragraph Style Access */
/* --------------------------------------------------------------------------- */

/*!
    @function   CTParagraphStyleGetValueForSpecifier
    @abstract   Obtains the current value for a single setting specifier.

    @discussion This function will return the current value of the specifier
                whether or not the user had actually set it. If the user has
                not set it, this function will return the default value.

                If an invalid paragraph style setting specifier is passed into
                the "spec" parameter, nothing bad will happen and the buffer
                value will simply be zeroed out. This is to allow backwards
                compatibility with style setting specifier that may be introduced
                in future versions.

    @param      paragraphStyle
                The paragraph style that you wish to get the value from.

    @param      spec
                The setting specifier that you want to get the value for.

    @param      valueBufferSize
                The size of the buffer pointed to by the "valueBuffer" parameter.
                This value must be at least as large as the size the required by
                the CTParagraphSpecifier value set in the "spec" parameter.

    @param      valueBuffer
                The buffer where the requested setting value will be written
                upon successful completion. The buffer's size needs to be at least
                as large as the value passed into "valueBufferSize".

    @result     This function will return "true" if the valueBuffer had been
                successfully filled. Otherwise, this function will return false,
                indicating that one or more of the parameters is not valid.
*/

bool CTParagraphStyleGetValueForSpecifier(
    CTParagraphStyleRef paragraphStyle,
    CTParagraphStyleSpecifier spec,
    size_t valueBufferSize,
    void * valueBuffer ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTStringAttributes.h
/*
 *  CTStringAttributes.h
 *  CoreText
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTSTRINGATTRIBUTES__
#define __CTSTRINGATTRIBUTES__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>
#include <CoreGraphics/CGColor.h>

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* The purpose of this file is to define all the attributes to which
    CoreText will respond when placed in a CFAttributedString. These
    are left out of other header file on purpose in order to avoid
    layering problems. This file is allowed to include any other header
    file it wants to. */

/* --------------------------------------------------------------------------- */
/* CFAttributedStringRef Attribute Prototypes */
/* --------------------------------------------------------------------------- */

/*!
    @const      kCTFontAttributeName
    @abstract   The font.

    @discussion Value must be a CTFontRef. Default is Helvetica 12.
*/

extern const CFStringRef kCTFontAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTForegroundColorFromContextAttributeName
    @abstract   Never set a foreground color in the CGContext; use what is set as
                the context's fill color.

    @discussion Value must be a CFBooleanRef. Default is false. The reason
                why this exists is because an NSAttributedString defaults to a
                black color if no color attribute is set. This forces CoreText to
                set the color in the context. This will allow developers to
                sidestep this, making CoreText set nothing but font information
                in the CGContext. If set, this attribute also determines the
                color used by kCTUnderlineStyleAttributeName, in which case it
                overrides the foreground color.
*/

extern const CFStringRef kCTForegroundColorFromContextAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTKernAttributeName
    @abstract   A kerning adjustment.

    @discussion Value must be a CFNumberRef float. Default is standard kerning.
                The kerning attribute indicate how many points the following
                character should be shifted from its default offset as defined
                by the current character's font in points; a positive kern
                indicates a shift farther along and a negative kern indicates a
                shift closer to the current character. If this attribute is not
                present, standard kerning will be used. If this attribute is
                set to 0.0, no kerning will be done at all.
*/

extern const CFStringRef kCTKernAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTLigatureAttributeName
    @abstract   Controls ligature formation.

    @discussion Value must be a CFNumberRef. Default is int value 1. The ligature
                attribute determines what kinds of ligatures should be used when
                displaying the string. A value of 0 indicates that only ligatures
                essential for proper rendering of text should be used, 1
                indicates that standard ligatures should be used, and 2 indicates
                that all available ligatures should be used. Which ligatures are
                standard depends on the script and possibly the font. Arabic
                text, for example, requires ligatures for many character
                sequences, but has a rich set of additional ligatures that
                combine characters. English text has no essential ligatures, and
                typically has only two standard ligatures, those for "fi" and
                "fl" -- all others being considered more advanced or fancy.

                On iOS releases prior to 6.0 essential ligatures are applied
                if the font contains glyphs for any of U+FB00 through U+FB04 and
                the font lacks AAT or OpenType shaping tables, but as of 6.0
                shaping tables (or the lack thereof) are treated as definitive.
*/

extern const CFStringRef kCTLigatureAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTForegroundColorAttributeName
    @abstract   The foreground color.

    @discussion Value must be a CGColorRef. Default value is black.
*/

extern const CFStringRef kCTForegroundColorAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTParagraphStyleAttributeName
    @abstract   A CTParagraphStyle object which is used to specify things like
                line alignment, tab rulers, writing direction, etc.

    @discussion Value must be a CTParagraphStyleRef. Default is an empty
                CTParagraphStyle object. See CTParagraphStyle.h for more
                information.
*/

extern const CFStringRef kCTParagraphStyleAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTStrokeWidthAttributeName
    @abstract   The stroke width.

    @discussion Value must be a CFNumberRef. Default value is 0.0, or no stroke.
                This attribute, interpreted as a percentage of font point size,
                controls the text drawing mode: positive values effect drawing
                with stroke only; negative values are for stroke and fill. A
                typical value for outlined text is 3.0.
*/

extern const CFStringRef kCTStrokeWidthAttributeName CT_AVAILABLE(10_6, 3_2);


/*!
    @const      kCTStrokeColorAttributeName
    @abstract   The stroke color.

    @discussion Value must be a CGColorRef. Default is the foreground color.
*/

extern const CFStringRef kCTStrokeColorAttributeName CT_AVAILABLE(10_6, 3_2);


/*!
    @const      kCTUnderlineStyleAttributeName
    @abstract   Allows the setting of an underline to be applied at render
                time.

    @discussion Value must be a CFNumberRef. Default is kCTUnderlineStyleNone.
                Set a value of something other than kCTUnderlineStyleNone to draw
                an underline. In addition, the CTUnderlineStyleModifiers can be
                used to modify the look of the underline. The underline color
                will be determined by the text's foreground color.
*/

extern const CFStringRef kCTUnderlineStyleAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTSuperscriptAttributeName
    @abstract   Controls vertical text positioning.

    @discussion Value must be a CFNumberRef. Default is int value 0. If supported
                by the specified font, a value of 1 enables superscripting and a
                value of -1 enables subscripting.
*/

extern const CFStringRef kCTSuperscriptAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTUnderlineColorAttributeName
    @abstract   The underline color.

    @discussion Value must be a CGColorRef. Default is the foreground color.
*/

extern const CFStringRef kCTUnderlineColorAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTVerticalFormsAttributeName
    @abstract   Controls glyph orientation.

    @discussion Value must be a CFBooleanRef. Default is false. A value of false
                indicates that horizontal glyph forms are to be used, true
                indicates that vertical glyph forms are to be used.
*/

extern const CFStringRef kCTVerticalFormsAttributeName CT_AVAILABLE(10_5, 4_3);


/*!
    @const      kCTGlyphInfoAttributeName
    @abstract   Allows the use of unencoded glyphs.

    @discussion Value must be a CTGlyphInfoRef. The glyph specified by this
                CTGlyphInfo object is assigned to the entire attribute range,
                provided that its contents match the specified base string and
                that the specified glyph is available in the font specified by
                kCTFontAttributeName. See CTGlyphInfo.h for more information.
*/

extern const CFStringRef kCTGlyphInfoAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @const      kCTCharacterShapeAttributeName
    @abstract   Controls glyph selection.

    @discussion Value must be a CFNumberRef. Default is value is 0 (disabled).
                A non-zero value is interpreted as an SFNT kCharacterShapeType
                selector + 1; see SFNTLayoutTypes.h for selectors. For example,
                an attribute value of 1 corresponds to kTraditionalCharactersSelector.
*/

extern const CFStringRef kCTCharacterShapeAttributeName CT_DEPRECATED(10_5, 10_11, 3_2, 9_0);


/*!
    @const      kCTLanguageAttributeName
    @abstract   Specifies text language.

    @discussion Value must be a CFStringRef containing a locale identifier. Default
                is unset. When this attribute is set to a valid identifier, it will
                be used to select localized glyphs (if supported by the font) and
                locale-specific line breaking rules.
*/

extern const CFStringRef kCTLanguageAttributeName CT_AVAILABLE(10_9, 7_0);


/*!
    @const      kCTRunDelegateAttributeName
    @abstract   Allows customization of certain aspects of a range of text's
                appearance.

    @discussion Value must be a CTRunDelegateRef. The values returned by the
                embedded object for an attribute range apply to each glyph
                resulting from the text in that range. Because an embedded object
                is only a display-time modification, care should be taken to
                avoid applying this attribute to a range of text with complex
                behavior, such as a change of writing direction, combining marks,
                etc. Consequently, it is recommended that this attribute be
                applied to a range containing the single character U+FFFC. See
                CTRunDelegate.h for more information.
*/

extern const CFStringRef kCTRunDelegateAttributeName CT_AVAILABLE(10_5, 3_2);


/*!
    @enum       CTUnderlineStyle
    @abstract   Underline style specifiers.

    @discussion These underline type specifiers can be applied to the value set
                with the kCTUnderlineStyleAttributeName attribute to tell
                CoreText that you want a different underline style.
*/

typedef CF_OPTIONS(int32_t, CTUnderlineStyle) {
    kCTUnderlineStyleNone           = 0x00,
    kCTUnderlineStyleSingle         = 0x01,
    kCTUnderlineStyleThick          = 0x02,
    kCTUnderlineStyleDouble         = 0x09
};


/*!
    @enum       CTUnderlineStyleModifiers
    @abstract   Underline style modifiers.

    @discussion Set these bits with the CTUnderlineStyle that you set with the
                kCTUnderlineStyleAttributeName attribute to modify how the
                underline will be drawn.
*/

typedef CF_OPTIONS(int32_t, CTUnderlineStyleModifiers) {
    kCTUnderlinePatternSolid        = 0x0000,
    kCTUnderlinePatternDot          = 0x0100,
    kCTUnderlinePatternDash         = 0x0200,
    kCTUnderlinePatternDashDot      = 0x0300,
    kCTUnderlinePatternDashDotDot   = 0x0400
};


/*!
    @const      kCTBaselineClassAttributeName
    @abstract   Key to reference a baseline class override.

    @discussion Value must be one of the kCTBaselineClass constants. Normally,
                glyphs on the line will be assigned baseline classes according to
                the 'bsln' or 'BASE' table in the font. This attribute may be
                used to change this assignment.

    @seealso    kCTBaselineClassRoman
    @seealso    kCTBaselineClassIdeographicCentered
    @seealso    kCTBaselineClassIdeographicLow
    @seealso    kCTBaselineClassIdeographicHigh
    @seealso    kCTBaselineClassHanging
    @seealso    kCTBaselineClassMath
*/

extern const CFStringRef kCTBaselineClassAttributeName CT_AVAILABLE(10_8, 6_0);


/*!
    @const      kCTBaselineInfoAttributeName
    @abstract   Key to reference a baseline info dictionary.

    @discussion Value must be a CFDictionaryRef. Normally, baseline offsets will
                be assigned based on the 'bsln' or 'BASE' table in the font. This
                attribute may be used to assign different offsets. Each key in
                the dictionary is one of the kCTBaselineClass constants and the
                value is a CFNumberRef of the baseline offset in points. You only
                need to specify the offsets you wish to change.

    @seealso    kCTBaselineClassRoman
    @seealso    kCTBaselineClassIdeographicCentered
    @seealso    kCTBaselineClassIdeographicLow
    @seealso    kCTBaselineClassIdeographicHigh
    @seealso    kCTBaselineClassHanging
    @seealso    kCTBaselineClassMath
*/

extern const CFStringRef kCTBaselineInfoAttributeName CT_AVAILABLE(10_8, 6_0);


/*!
    @const      kCTBaselineReferenceInfoAttributeName
    @abstract   Key to reference a baseline info dictionary for the reference baseline.

    @discussion Value must be a CFDictionaryRef. All glyphs in a run are assigned
                a baseline class and then aligned to the offset for that class in
                the reference baseline baseline info. See the discussion of
                kCTBaselineInfoAttributeName for information about the contents
                of the dictionary. You can also use the kCTBaselineReferenceFont
                key to specify that the baseline offsets of a particular
                CTFontRef should be used as the reference offsets.

    @seealso    kCTBaselineClassRoman
    @seealso    kCTBaselineClassIdeographicCentered
    @seealso    kCTBaselineClassIdeographicLow
    @seealso    kCTBaselineClassIdeographicHigh
    @seealso    kCTBaselineClassHanging
    @seealso    kCTBaselineClassMath
    @seealso    kCTBaselineReferenceFont
*/

extern const CFStringRef kCTBaselineReferenceInfoAttributeName CT_AVAILABLE(10_8, 6_0);


/*!
    @const      kCTWritingDirectionAttributeName
    @abstract   Specifies a bidirectional override or embedding.

    @discussion Value must be a CFArray of CFNumberRefs, each of which should
                have a value of either kCTWritingDirectionLeftToRight or
                kCTWritingDirectionRightToLeft, plus one of
                kCTWritingDirectionEmbedding or kCTWritingDirectionOverride.
                This array represents a sequence of nested bidirectional
                embeddings or overrides, in order from outermost to innermost,
                with (kCTWritingDirectionLeftToRight | kCTWritingDirectionEmbedding)
                corresponding to a LRE/PDF pair in plain text or
                <span dir="ltr"></span> in HTML, (kCTWritingDirectionRightToLeft
                | kCTWritingDirectionEmbedding) corresponding to a RLE/PDF
                pair in plain text or a <span dir="rtl"></span> in HTML,
                (kCTWritingDirectionLeftToRight | kCTWritingDirectionOverride)
                corresponding to a LRO/PDF pair in plain text or
                <bdo dir="ltr"></span> in HTML, and (kCTWritingDirectionRightToLeft
                | kCTWritingDirectionOverride) corresponding to a RLO/PDF
                pair in plain text or <bdo dir="rtl"></span> in HTML.

    @seealso    kCTWritingDirectionLeftToRight
    @seealso    kCTWritingDirectionRightToLeft
    @seealso    kCTWritingDirectionEmbedding
    @seealso    kCTWritingDirectionOverride
*/

extern const CFStringRef kCTWritingDirectionAttributeName CT_AVAILABLE(10_8, 6_0);


/*!
    @abstract   Additional values for use with kCTWritingDirectionAttributeName
                in combination with kCTWritingDirectionLeftToRight or
                kCTWritingDirectionRightToLeft.

    @seealso    kCTWritingDirectionAttributeName
    @seealso    kCTWritingDirectionLeftToRight
    @seealso    kCTWritingDirectionRightToLeft
*/

enum {
    kCTWritingDirectionEmbedding = (0 << 1),
    kCTWritingDirectionOverride = (1 << 1)
};


/*!
    @const      kCTRubyAnnotationAttributeName
    @abstract   Key to reference a CTRubyAnnotation.

    @discussion Value must be a CTRubyAnnotationRef. See CTRubyAnnotation.h for
                more information.
 */

extern const CFStringRef kCTRubyAnnotationAttributeName CT_AVAILABLE(10_10, 8_0);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif
// ==========  CoreText.framework/Headers/CTDefines.h
/*
 *  CTDefines.h
 *  CoreText
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTDEFINES__
#define __CTDEFINES__

#include <Availability.h>

#ifndef __has_feature
# define __has_feature(x) 0
#endif

#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

#if defined(CT_BUILDING_CoreText)
# define CT_AVAILABLE(_mac, _ios)
# define CT_AVAILABLE_MAC(_mac)
# define CT_AVAILABLE_IOS(_ios)
# define CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_DEPRECATED_IOS(_iosIntro, _iosDep)
#else /* defined(CT_BUILDING_CoreText) */
# define CT_AVAILABLE(_mac, _ios) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_##_ios)
# define CT_AVAILABLE_MAC(_mac) __OSX_AVAILABLE_STARTING(__MAC_##_mac, __IPHONE_NA)
# define CT_AVAILABLE_IOS(_ios) __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_##_ios)
# define CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)
# define CT_DEPRECATED_MAC(_macIntro, _macDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##_macIntro, __MAC_##_macDep, __IPHONE_NA, __IPHONE_NA)
# define CT_DEPRECATED_IOS(_iosIntro, _iosDep) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_##_iosIntro, __IPHONE_##_iosDep)
#endif /* defined(CT_BUILDING_CoreText) */

#if __has_feature(enumerator_attributes) && __has_attribute(availability)
# define CT_ENUM_AVAILABLE(_mac, _ios) CT_AVAILABLE(_mac, _ios)
# define CT_ENUM_AVAILABLE_MAC(_mac) CT_AVAILABLE_MAC(_mac)
# define CT_ENUM_AVAILABLE_IOS(_ios) CT_AVAILABLE_IOS(_ios)
# define CT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) CT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_ENUM_DEPRECATED_MAC(_macIntro, _macDep) CT_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep) CT_DEPRECATED_IOS(_iosIntro, _iosDep)
#else
# define CT_ENUM_AVAILABLE(_mac, _ios)
# define CT_ENUM_AVAILABLE_MAC(_mac)
# define CT_ENUM_AVAILABLE_IOS(_ios)
# define CT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)
# define CT_ENUM_DEPRECATED_MAC(_macIntro, _macDep)
# define CT_ENUM_DEPRECATED_IOS(_iosIntro, _iosDep)
#endif /* __has_feature(enumerator_attributes) && __has_attribute(availability) */

#if __has_attribute(objc_bridge)
# if defined(__OBJC__)
#  if TARGET_OS_IPHONE
@class UIFont;
@class UIFontDescriptor;
#  else
@class NSFont;
@class NSFontCollection;
@class NSFontDescriptor;
@class NSGlyphInfo;
@class NSMutableFontCollection;
#  endif /* TARGET_OS_IPHONE */
@class NSParagraphStyle;
@class NSTextTab;
# endif /* defined(__OBJC__) */
#endif /*  __has_attribute(objc_bridge) */

#endif
// ==========  CoreText.framework/Headers/CTFontCollection.h
/*
 *  CTFontCollection.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTCOLLECTION__
#define __CTFONTCOLLECTION__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontDescriptor.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*! --------------------------------------------------------------------------
    @group Collection Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontCollectionRef
    @abstract   The Core Text font collection reference.
    @discussion An opaque reference to an immutable font collection.
*/
#if TARGET_OS_IPHONE
typedef const struct CF_BRIDGED_TYPE(id) __CTFontCollection * CTFontCollectionRef;
#else
typedef const struct CF_BRIDGED_TYPE(NSFontCollection) __CTFontCollection * CTFontCollectionRef;
#endif

/*!
    @typedef    CTMutableFontCollectionRef
    @abstract   The Core Text mutable font collection reference.
    @discussion An opaque reference to a mutable font collection.
*/
#if TARGET_OS_IPHONE
typedef struct CF_BRIDGED_TYPE(id) __CTFontCollection * CTMutableFontCollectionRef;
#else
typedef struct CF_BRIDGED_MUTABLE_TYPE(NSMutableFontCollection) __CTFontCollection * CTMutableFontCollectionRef;
#endif

/*!
    @function   CTFontCollectionGetTypeID
    @abstract   Returns the type identifier for Core Text font collection references.
    @result     The identifier for the opaque types CTFontCollectionRef or CTMutableFontCollectionRef.
*/
CFTypeID CTFontCollectionGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);

/*!
    @typedef    CTFontCollectionSortDescriptorsCallback
    @abstract   Collection sorting callback.
    @discussion This callback can be specified to obtain the matching font descriptors of a collection in sorted order. Return the appropriate comparison result of first descriptor to second descriptor.
*/
typedef CFComparisonResult (*CTFontCollectionSortDescriptorsCallback)(
    CTFontDescriptorRef first,
    CTFontDescriptorRef second,
    void *refCon );

/*! --------------------------------------------------------------------------
    @group Collection Matching Options
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontCollectionRemoveDuplicatesOption
    @abstract   Option key to specify filtering of duplicates.
    @discussion Specify this option key in the options dictionary with a non- zero value to enable automatic filtering of duplicate font descriptors.
*/
extern const CFStringRef kCTFontCollectionRemoveDuplicatesOption CT_AVAILABLE(10_5, 3_2);

/*!
    @defined    kCTFontCollectionIncludeDisabledFontsOption
    @abstract   Option key to include disabled fonts in the matching results.
    @discussion Specify this option key in the options dictionary with a non-zero value to enable matching of disabled fonts. You can pass font descriptors specifying disabled fonts to CTFontManagerEnableFontDescriptors, but you cannot use such a font descriptor to query font attributes from the system database or create a CTFontRef.
*/
extern const CFStringRef kCTFontCollectionIncludeDisabledFontsOption CT_AVAILABLE_MAC(10_7);

/*!
    @defined    kCTFontCollectionDisallowAutoActivationOption
    @abstract   Option key to avoid auto-activating fonts.
    @discussion Specify this option key in the options dictionary with a non-zero value to disallow searches for missing fonts (font descriptors returning no results).
*/
extern const CFStringRef kCTFontCollectionDisallowAutoActivationOption CT_AVAILABLE_MAC(10_7);

/*! --------------------------------------------------------------------------
    @group Collection Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateFromAvailableFonts
    @abstract   Returns a new font collection matching all available fonts.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection containing all fonts available to the current application.
*/
CTFontCollectionRef CTFontCollectionCreateFromAvailableFonts(
    CFDictionaryRef __nullable options ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCollectionCreateWithFontDescriptors
    @abstract   Returns a new collection based on the array of font descriptors.

    @param      queryDescriptors
                An array of font descriptors to use for matching. May be NULL, in which case the matching descriptors will be NULL.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection based on the provided font descriptors. The contents of this collection is defined by matching the provided descriptors against all available font descriptors.
*/
CTFontCollectionRef CTFontCollectionCreateWithFontDescriptors(
    CFArrayRef __nullable queryDescriptors,
    CFDictionaryRef __nullable options ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCollectionCreateCopyWithFontDescriptors
    @abstract   Returns a copy of the original collection augmented with the new font descriptors.

    @param      original
                The original font collection reference.

    @param      queryDescriptors
                An array of font descriptors to augment those of the original collection.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a copy of the original font collection augmented by the new font descriptors and options. The new font descriptors are merged with the existing descriptors to create a single set.
*/
CTFontCollectionRef CTFontCollectionCreateCopyWithFontDescriptors(
    CTFontCollectionRef original,
    CFArrayRef __nullable queryDescriptors,
    CFDictionaryRef __nullable options ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCollectionCreateMutableCopy
    @abstract   Returns a mutable copy of the original collection.

    @param      original
                The original font collection reference.

    @result     This function creates a mutable copy of the original font collection.
*/
CTMutableFontCollectionRef CTFontCollectionCreateMutableCopy(
    CTFontCollectionRef original ) CT_AVAILABLE_MAC(10_7);

/*! --------------------------------------------------------------------------
    @group Editing the query descriptors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCopyQueryDescriptors
    @abstract   Returns the array of descriptors to match.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to the array of descriptors to be used to query (match) the system font database. The return value is undefined if CTFontCollectionCreateFromAvailableFonts was used to create the collection.
*/
CFArrayRef __nullable CTFontCollectionCopyQueryDescriptors(
    CTFontCollectionRef collection ) CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionSetQueryDescriptors
    @abstract   Replaces the array of descriptors to match.

    @param      collection
                The font collection reference.

    @param      descriptors
                An array of CTFontDescriptorRef. May be NULL to represent an empty collection, in which case the matching descriptors will also be NULL.
*/
void CTFontCollectionSetQueryDescriptors(
    CTMutableFontCollectionRef  collection,
    CFArrayRef __nullable       descriptors ) CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionCopyExclusionDescriptors
    @abstract   Returns the array of descriptors to exclude from the match.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to the array of descriptors to be used to query (match) the system font database.
*/
CFArrayRef __nullable CTFontCollectionCopyExclusionDescriptors( CTFontCollectionRef collection ) CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionSetExclusionDescriptors
    @abstract   Replaces the array of descriptors to exclude from the match.

    @param      collection
                The font collection reference.

    @param      descriptors
                An array of CTFontDescriptorRef. May be NULL.
*/
void CTFontCollectionSetExclusionDescriptors(
    CTMutableFontCollectionRef  collection,
    CFArrayRef __nullable       descriptors ) CT_AVAILABLE_MAC(10_7);

/*! --------------------------------------------------------------------------
    @group Retrieving Matching Descriptors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptors
    @abstract   Returns an array of font descriptors matching the collection.

    @param      collection
                The font collection reference.

    @result     An array of CTFontDescriptors matching the collection definition or NULL if there are none.
*/
CFArrayRef __nullable CTFontCollectionCreateMatchingFontDescriptors(
    CTFontCollectionRef collection ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsSortedWithCallback
    @abstract   Returns the array of matching font descriptors sorted with the callback function.

    @param      collection
                The collection reference.

    @param      sortCallback
                The sorting callback function that defines the sort order.

    @param      refCon
                Pointer to client data define context for the callback.

    @result     An array of CTFontDescriptors matching the criteria of the collection, sorted by the results of the sorting callback function, or NULL if there are none.
*/
CFArrayRef __nullable CTFontCollectionCreateMatchingFontDescriptorsSortedWithCallback(
    CTFontCollectionRef                     collection,
    CTFontCollectionSortDescriptorsCallback __nullable sortCallback,
    void * __nullable                       refCon ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsWithOptions
    @abstract   Returns an array of font descriptors matching the collection.

    @param      collection
                The font collection reference.

    @param      options
                The options dictionary. See constant option keys. May be NULL, in which case this call returns the same results as CTFontCollectionCreateMatchingFontDescriptors, using the options passed in when the collection was created.

    @result     An array of CTFontDescriptors matching the collection definition or NULL if there are none.
*/
CFArrayRef __nullable CTFontCollectionCreateMatchingFontDescriptorsWithOptions(
    CTFontCollectionRef collection,
    CFDictionaryRef __nullable options ) CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsForFamily
    @abstract   Returns an array of font descriptors matching the specified family, one descriptor for each style in the collection.

    @param      collection
                The font collection reference.

    @param      familyName
                The font family name

    @result     An array of CTFontDescriptors matching the specified family in the collection or NULL if there are none.
*/
CFArrayRef __nullable CTFontCollectionCreateMatchingFontDescriptorsForFamily(
    CTFontCollectionRef collection,
    CFStringRef         familyName,
    CFDictionaryRef __nullable options ) CT_AVAILABLE_MAC(10_7);

/*! --------------------------------------------------------------------------
    @group Bulk attribute access
*///--------------------------------------------------------------------------
/*!
    @enum       CTFontCollectionCopyOptions
    @abstract   Option bits for use with CTFontCollectionCopyFontAttribute(s).

    @constant   kCTFontCollectionCopyStandardSort
                Passing this option indicates that the return values should be sorted in standard UI order, suitable for display to the user. This is the same sorting behavior used by NSFontPanel and Font Book.

    @constant   kCTFontCollectionCopyUnique
                Passing this option indicates that duplicate values should be removed from the results.
 */
typedef CF_OPTIONS(uint32_t, CTFontCollectionCopyOptions) {
    kCTFontCollectionCopyDefaultOptions = 0,
    kCTFontCollectionCopyUnique = (1 << 0),
    kCTFontCollectionCopyStandardSort = (1 << 1)
} CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionCopyFontAttribute
    @abstract   Returns an array of font descriptor attribute values.

    @param      collection
                The font collection reference.

    @param      attributeName
                The attribute to retrieve for each descriptor in the collection.

    @param      options
                Options to alter the return value.

    @result     An array containing one value for each descriptor. With kCTFontCollectionCopyDefaultOptions, the values will be in the same order as the results from CTFontCollectionCreateMatchingFontDescriptors and NULL values will be transformed to kCFNull. When the kCTFontCollectionCopyUnique is set, duplicate values will be removed. When kCTFontCollectionCopyStandardSort is set, the values will be sorted in standard UI order.
 */
CFArrayRef CTFontCollectionCopyFontAttribute(
    CTFontCollectionRef         collection,
    CFStringRef                 attributeName,
    CTFontCollectionCopyOptions options ) CT_AVAILABLE_MAC(10_7);

/*!
    @function   CTFontCollectionCopyFontAttributes
    @abstract   Returns an array of dictionaries containing font descriptor attribute values.
 
    @param      collection
                The font collection reference.

    @param      attributeNames
                The attributes to retrieve for each descriptor in the collection.

    @param      options
                Options to alter the return value.

    @result     An array containing one CFDictionary value for each descriptor mapping the requested attribute names. With kCTFontCollectionCopyDefaultOptions, the values will be in the same order as the results from CTFontCollectionCreateMatchingFontDescriptors. When the kCTFontCollectionCopyUnique is set, duplicate values will be removed. When kCTFontCollectionCopyStandardSort is set, the values will be sorted in standard UI order.
 */
CFArrayRef CTFontCollectionCopyFontAttributes(
    CTFontCollectionRef         collection,
    CFSetRef                    attributeNames,
    CTFontCollectionCopyOptions options ) CT_AVAILABLE_MAC(10_7);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CTGlyphInfo.h
/*
 *	CTGlyphInfo.h
 *	CoreText
 *
 *	Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTGLYPHINFO__
#define __CTGLYPHINFO__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFont.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Glyph Info Types */
/* --------------------------------------------------------------------------- */

#if TARGET_OS_IPHONE
typedef const struct CF_BRIDGED_TYPE(id) __CTGlyphInfo * CTGlyphInfoRef;
#else
typedef const struct CF_BRIDGED_TYPE(NSGlyphInfo) __CTGlyphInfo * CTGlyphInfoRef;
#endif

/*!
	@function	CTGlyphInfoGetTypeID
	@abstract	Returns the CFType of the glyph info object
*/

CFTypeID CTGlyphInfoGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Info Values */
/* --------------------------------------------------------------------------- */

/*!
	@enum		CTCharacterCollection
	@abstract	These constants specify character collections.

	@constant	kCTCharacterCollectionIdentityMapping
				Indicates that the character identifier is equal to the CGGlyph
				glyph index.

	@constant	kCTCharacterCollectionAdobeCNS1
				Indicates the Adobe-CNS1 mapping.

	@constant	kCTCharacterCollectionAdobeGB1
				Indicates the Adobe-GB1 mapping.

	@constant	kCTCharacterCollectionAdobeJapan1
				Indicates the Adobe-Japan1 mapping.

	@constant	kCTCharacterCollectionAdobeJapan2
				Indicates the Adobe-Japan2 mapping.

	@constant	kCTCharacterCollectionAdobeKorea1
				Indicates the Adobe-Korea1 mapping.
*/

typedef CF_ENUM(uint16_t, CTCharacterCollection) {
	kCTCharacterCollectionIdentityMapping CT_ENUM_AVAILABLE(10_8, 6_0) = 0,
	kCTCharacterCollectionAdobeCNS1       CT_ENUM_AVAILABLE(10_8, 6_0) = 1,
	kCTCharacterCollectionAdobeGB1        CT_ENUM_AVAILABLE(10_8, 6_0) = 2,
	kCTCharacterCollectionAdobeJapan1     CT_ENUM_AVAILABLE(10_8, 6_0) = 3,
	kCTCharacterCollectionAdobeJapan2     CT_ENUM_AVAILABLE(10_8, 6_0) = 4,
	kCTCharacterCollectionAdobeKorea1     CT_ENUM_AVAILABLE(10_8, 6_0) = 5,

	kCTIdentityMappingCharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionIdentityMapping,
	kCTAdobeCNS1CharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionAdobeCNS1,
	kCTAdobeGB1CharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionAdobeGB1,
	kCTAdobeJapan1CharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionAdobeJapan1,
	kCTAdobeJapan2CharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionAdobeJapan2,
	kCTAdobeKorea1CharacterCollection CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTCharacterCollectionAdobeKorea1
};


/* --------------------------------------------------------------------------- */
/* Glyph Info Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTGlyphInfoCreateWithGlyphName
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a glyph
				name such as "copyright" and a specified font.

	@param		glyphName
				The name of the glyph.

	@param		font
				The font to be associated with the returned CTGlyphInfo object.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		This function will return a reference to a CTGlyphInfo object.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithGlyphName(
	CFStringRef glyphName,
	CTFontRef font,
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTGlyphInfoCreateWithGlyph
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a glyph
				index and a specified font.

	@param		glyph
				The glyph identifier.

	@param		font
				The font to be associated with the returned CTGlyphInfo object.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		This function will return a reference to a CTGlyphInfo object.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithGlyph(
	CGGlyph glyph,
	CTFontRef font,
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTGlyphInfoCreateWithCharacterIdentifier
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a
				character identifier and a character collection.

	@param		cid
				A character identifier.

	@param		collection
				A character collection identifier.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		This function will return a reference to a CTGlyphInfo object.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithCharacterIdentifier(
	CGFontIndex cid,
	CTCharacterCollection collection,
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Info Access */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTGlyphInfoGetGlyphName
	@abstract	Gets the glyph name for a glyph info, if applicable.

	@discussion This function will return the glyph name.

	@param		glyphInfo
				The glyph info for which you would like the glyph name.

	@result		If the glyph info object was created with a glyph name, it will
				be returned. Otherwise, this function will return NULL.
*/

CFStringRef __nullable CTGlyphInfoGetGlyphName(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTGlyphInfoGetCharacterIdentifier
	@abstract	Gets the character identifier for a glyph info.

	@discussion This function will return the character identifier.

	@param		glyphInfo
				The glyph info for which you would like the character identifier.

	@result		If the glyph info object was created with a character identifier,
				it will be returned. Otherwise, this function will return 0.
*/

CGFontIndex CTGlyphInfoGetCharacterIdentifier(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTGlyphInfoGetCharacterCollection
	@abstract	Gets the character collection for a glyph info.

	@discussion This function will return the character collection. If the glyph
				info object was created with a glyph name or a glyph index, its
				character collection will be
				kCTIdentityMappingCharacterCollection.

	@param		glyphInfo
				The glyph info for which you would like the character collection.

	@result		This function will return the character collection of the given
				glyph info.
*/

CTCharacterCollection CTGlyphInfoGetCharacterCollection(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
// ==========  CoreText.framework/Headers/CoreText.h
/*
 *  CoreText.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CORETEXT__
#define __CORETEXT__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFont.h>
#include <CoreText/CTFontCollection.h>
#include <CoreText/CTFontDescriptor.h>
#include <CoreText/CTFontManager.h>
#include <CoreText/CTFontTraits.h>
#include <CoreText/CTFrame.h>
#include <CoreText/CTFramesetter.h>
#include <CoreText/CTGlyphInfo.h>
#include <CoreText/CTLine.h>
#include <CoreText/CTParagraphStyle.h>
#include <CoreText/CTRubyAnnotation.h>
#include <CoreText/CTRun.h>
#include <CoreText/CTRunDelegate.h>
#include <CoreText/CTStringAttributes.h>
#include <CoreText/CTTextTab.h>
#include <CoreText/CTTypesetter.h>
#include <CoreText/SFNTLayoutTypes.h>
#include <CoreText/SFNTTypes.h>

CF_EXTERN_C_BEGIN

/*!
    @function   CTGetCoreTextVersion
    @abstract   Returns the version of the CoreText framework.

    @discussion This function returns a number indicating the version of the
                CoreText framework. Note that framework version is not always
                an accurate indicator of feature availability. The recommended
                way to use this function is first to check that the function
                pointer is non-NULL, followed by calling it and comparing its
                result to a defined constant (or constants). For example, to
                determine whether the CoreText API is available:
                    if (&CTGetCoreTextVersion != NULL && CTGetCoreTextVersion() >= kCTVersionNumber10_5) {
                        // CoreText API is available
                    }

    @result     The version number. This value is for comparison with the
                constants beginning with kCTVersionNumber.
*/

uint32_t CTGetCoreTextVersion( void ) CT_AVAILABLE(10_5, 3_2);

#define kCTVersionNumber10_5 0x00020000
#define kCTVersionNumber10_5_2 0x00020001
#define kCTVersionNumber10_5_3 0x00020002
#define kCTVersionNumber10_5_5 0x00020003
#define kCTVersionNumber10_6 0x00030000
#define kCTVersionNumber10_7 0x00040000
#define kCTVersionNumber10_8 0x00050000
#define kCTVersionNumber10_9 0x00060000
#define kCTVersionNumber10_10 0x00070000
#define kCTVersionNumber10_11 0x00080000

CF_EXTERN_C_END

#endif // __CORETEXT__
