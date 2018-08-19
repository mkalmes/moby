// ==========  ImageIO.framework/Headers/ImageIOBase.h
/*
 * ImageIO - ImageIOBase.h
 * Copyright (c) 2009-2010 Apple Inc. 
 * All rights reserved.
 *
 */

#ifndef __IMAGEIOBASE__
#define __IMAGEIOBASE__

#include <CoreFoundation/CoreFoundation.h>

#if defined(IMAGEIO_BUILDING_IMAGEIO)

#   define IMAGEIO_AVAILABLE_STARTING(_mac,_iphone)
#   define IMAGEIO_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)

#else /* !defined(IMAGEIO_BUILDING_IMAGEIO) */

#   include <Availability.h>
#   define IMAGEIO_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
#   define IMAGEIO_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED

#endif /* !defined(IMAGEIO_BUILDING_IMAGEIO) */


#if !defined(IMAGEIO_EXTERN)
#   if defined(__WIN32__)
#       if defined(IMAGEIO_BUILDING_IMAGEIO)
#           if defined(__cplusplus)
#               define IMAGEIO_EXTERN extern "C" __declspec(dllexport)
#           else /* !defined(__cplusplus) */
#               define IMAGEIO_EXTERN extern __declspec(dllexport)
#           endif /* !defined(__cplusplus) */
#       else /* !defined(IMAGEIO_BUILDING_IMAGEIO) */
#           if defined(__cplusplus)
#               define IMAGEIO_EXTERN extern "C" __declspec(dllimport) 
#           else /* !defined(__cplusplus) */
#               define IMAGEIO_EXTERN extern __declspec(dllimport)
#           endif /* !defined(__cplusplus) */
#       endif /* !defined(IMAGEIO_BUILDING_IMAGEIO) */
#   else /* !defined(__WIN32__) */
#       if defined(__cplusplus)
#           define IMAGEIO_EXTERN extern "C"
#       else /* !defined(__cplusplus) */
#           define IMAGEIO_EXTERN extern
#       endif /* !defined(__cplusplus) */
#   endif /* !defined(__WIN32__) */
#endif /* !defined(IMAGEIO_EXTERN) */


#if !defined(IMAGEIO_EXTERN_C_BEGIN)
#   ifdef __cplusplus
#       define IMAGEIO_EXTERN_C_BEGIN extern "C" {
#       define IMAGEIO_EXTERN_C_END   }
#   else
#       define IMAGEIO_EXTERN_C_BEGIN
#       define IMAGEIO_EXTERN_C_END
#   endif
#endif

#if (TARGET_OS_MAC && !TARGET_IPHONE_SIMULATOR) || TARGET_OS_EMBEDDED
#    define IIO_HAS_IOSURFACE 1
#else
#    define IIO_HAS_IOSURFACE 0
#endif

#if defined(__has_feature) && __has_feature(objc_bridge_id)
#define IIO_BRIDGED_TYPE(type)       CF_BRIDGED_TYPE(type)
#else
#define IIO_BRIDGED_TYPE(type)
#endif


#endif  /* __IMAGEIOBASE__ */
// ==========  ImageIO.framework/Headers/ImageIO.h
/*
 * ImageIO - ImageIO.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

#ifndef __IMAGEIO__
#define __IMAGEIO__

#include <ImageIO/ImageIOBase.h>

#include <ImageIO/CGImageSource.h>

#include <ImageIO/CGImageDestination.h>

#include <ImageIO/CGImageProperties.h>

#include <ImageIO/CGImageMetadata.h>


#endif  /* __IMAGEIO__ */
// ==========  ImageIO.framework/Headers/CGImageMetadata.h
// *****************************************************************************
// CGImageMetadata.h
// *****************************************************************************

#ifndef CGIMAGEMETADATA_H_
#define CGIMAGEMETADATA_H_

#include <ImageIO/ImageIOBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

/*!
 * @header CGImageMetadata.h
 * @abstract Implements access to image metadata
 * @description CGImageMetadata APIs allow clients to view and modify metadata
 * for popular image formats. ImageIO supports the EXIF, IPTC, and XMP
 * metadata specifications. Please refer to CGImageSource.h for functions to 
 * read metadata from a CGImageSource, and CGImageDestination.h for functions to
 * write metadata to a CGImageDestination. CGImageDestinationCopyImageSource can
 * be used to modify metadata without recompressing the image.
 *
 * Developers can enable additional debugging information by setting the
 * environment variable IIO_DEBUG_METADATA=1.
 * @related CGImageSource.h
 * @related CGImageDestination.h
 * @ignorefuncmacro IMAGEIO_AVAILABLE_STARTING
 * @ignore IMAGEIO_EXTERN
 * @unsorted
 */

/*!
 * @typedef CGImageMetadataRef 
 * @abstract an immutable container for CGImageMetadataTags
 */
typedef const struct IIO_BRIDGED_TYPE(id) CGImageMetadata *CGImageMetadataRef;

///*! @functiongroup Creating and identifying CGImageMetadata containers */
/*!
 * @function CGImageMetadataGetTypeID
 * @abstract Gets the type identifier for the CGImageMetadata opaque type
 * @return the type identifier for the CGImageMetadata opaque type
 */
IMAGEIO_EXTERN CFTypeID CGImageMetadataGetTypeID(void);

/*!
 * @typedef CGMutableImageMetadataRef
 * @abstract a mutable container for CGImageMetadataTags
 * @discussion A CGMutableImageMetadataRef can be used in any function that
 * accepts a CGImageMetadataRef.
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageMetadata *CGMutableImageMetadataRef;

/*!
 * @function CGImageMetadataCreateMutable
 * @abstract Creates an empty CGMutableImageMetadataRef
 */
IMAGEIO_EXTERN CGMutableImageMetadataRef __nonnull CGImageMetadataCreateMutable(void) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCreateMutableCopy
 * @abstract Creates a deep mutable copy of another CGImageMetadataRef
 * @discussion Before modifying an immutable CGImageMetadataRef (such as metadata
 * from CGImageSourceCopyMetadataAtIndex) you must first make a copy.
 * This function makes a deep copy of all CGImageMetadataTags and their values.
 */
IMAGEIO_EXTERN CGMutableImageMetadataRef __nullable CGImageMetadataCreateMutableCopy(CGImageMetadataRef __nonnull metadata) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// ****************************************************************************
// CGImageMetadataTag - an individual metadata tag, encapsulating an EXIF tag, 
// IPTC tag, or XMP property.
// ****************************************************************************

/*!
 * @typedef CGImageMetadataTagRef
 * @abstract an individual metadata tag
 * @discussion A CGImageMetadataTag encapsulates an EXIF, IPTC, or XMP property.
 * All tags contain a namespace, prefix, name, type, and value. Please see
 * @link CGImageMetadataTagCreate @/link for more details.
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageMetadataTag *CGImageMetadataTagRef;

///*! @functiongroup Creating and identifying CGImageMetadataTags */
/*!
 * @function CGImageMetadataTagGetTypeID
 * @abstract Gets the type identifier for the CGImageMetadataTag opaque type
 * @return the type identifier for the CGImageMetadataTagGetTypeID opaque type
 */
IMAGEIO_EXTERN CFTypeID CGImageMetadataTagGetTypeID(void) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Constants for use in a CGImageMetadataTag
// ****************************************************************************

CF_ASSUME_NONNULL_BEGIN

// All metadata tags must contain a namespace. Clients may use one of the 
// public namespaces defined below or create their own namespace. If a caller
// defines their own namespace, it should comply with the guidelines set forth
// by Adobe in their XMP specification at:
// http://www.adobe.com/devnet/xmp.html.
// For example: "http://ns.adobe.com/exif/1.0/". 
// The caller must also register a custom namespace using 
// CGImageMetadataRegisterNamespaceForPrefix.

// Public, common namespaces.
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExif IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifAux IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifEX IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceDublinCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceIPTCCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespacePhotoshop IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceTIFF IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPBasic IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPRights IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// All metadata tags must contain a prefix. For the public namespaces defined
// above, no prefix is required - ImageIO will use appropriate defaults.  For 
// other namespaces a prefix is required. For example, while the exif namespace 
// is rather long ("http://ns.adobe.com/exif/1.0/"), when exported the shorter 
// string "exif" will be used to prefix all properties in the exif namespace 
// (example - "exif:Flash").

// Public, common prefixes.
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExif IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifAux IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifEX IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixDublinCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixIPTCCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixPhotoshop IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixTIFF IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPBasic IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPRights IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

CF_ASSUME_NONNULL_END

// Metadata value type constants.
/*!
 * @typedef CGImageMetadataType
 * @abstract The XMP type for a CGImageMetadataTag
 * @discussion CGImageMetadataType defines a list of constants used to indicate
 * the type for a CGImageMetadataTag. If you are reading metadata, use the type 
 * to determine how to interpret the CGImageMetadataTag's value. If you are 
 * creating a CGImageMetadataTag, use the type to specify how the tag 
 * should be serialized in XMP. String types have CFStringRef values, array 
 * types have CFArray values, and structure types have CFDictionary values.
 * @const kCGImageMetadataTypeDefault The type will be interpretted based on the
 * CFType of the tag's value. This is only used when creating a new 
 * CGImageMetadataTag - no existing tags should have this value. CFString 
 * defaults to kCGImageMetadataTypeString, CFArray defaults to 
 * kCGImageMetadataTypeArrayOrdered, and CFDictionary defaults to
 * kCGImageMetadataTypeStructure.
 * @const kCGImageMetadataTypeString A string value. CFNumber and CFBoolean 
 * values will be converted to a string.
 * @const kCGImageMetadataTypeArrayUnordered An array where order does not matter.
 * Serialized in XMP as <rdf:Bag>.
 * @const kCGImageMetadataTypeArrayOrdered An array where order is preserved.
 * Serialized in XMP as <rdf:Seq>.
 * @const kCGImageMetadataTypeAlternateArray An ordered array where all elements
 * are alternates for the same value. Serialized in XMP as <rdf:Alt>.
 * @const kCGImageMetadataTypeAlternateText A special case of an alternate array
 * where all elements are different localized strings for the same value. 
 * Serialized in XMP as an alternate array of strings with xml:lang qualifiers.
 * @const kCGImageMetadataTypeStructure A collection of keys and values. Unlike
 * array elements, fields of a structure may belong to different namespaces.
 */
typedef CF_ENUM(int32_t, CGImageMetadataType) {
    kCGImageMetadataTypeInvalid = -1,
    kCGImageMetadataTypeDefault = 0,
    kCGImageMetadataTypeString = 1,
    kCGImageMetadataTypeArrayUnordered = 2,
    kCGImageMetadataTypeArrayOrdered = 3,
    kCGImageMetadataTypeAlternateArray = 4,
    kCGImageMetadataTypeAlternateText = 5,
    kCGImageMetadataTypeStructure = 6
};

// ****************************************************************************
// Creating a CGImageMetadataTag
// ****************************************************************************
/*!
 * @function CGImageMetadataTagCreate
 * @abstract Creates a new CGImageMetadataTag
 * @param xmlns The namespace for the tag. The value can be a common XMP namespace
 * defined above, such as kCGImageMetadataNamespaceExif, or a CFString with a
 * custom namespace URI. Custom namespaces must be a valid XML namespace. By
 * convention, namespaces should end with either '/' or '#'. For example, exif
 * uses the namespace "http://ns.adobe.com/exif/1.0/".
 * @param prefix An abbreviation for the XML namespace. The value can be NULL if
 * the namespace is defined as a constant. Custom prefixes must be a valid XML
 * name. For example, the prefix used for "http://ns.adobe.com/exif/1.0/" is "exif".
 * The XMP serialization of the tag will use the prefix. Prefixes are also
 * important for path-based CGImageMetadata functions, such as 
 * @link CGImageMetadataCopyStringValueWithPath @/link or 
 * @link CGImageMetadataSetValueWithPath @/link.
 * @param name The name of the tag. It must be a valid XMP name.
 * @param type The type of the tag's value. Must be a constant from @link 
 * CGImageMetadataType @/link.
 * @param value The value of the tag. Allowable CFTypes include CFStringRef,
 * CFNumberRef, CFBooleanRef, CFArrayRef, and CFDictionaryRef. The CFType of 'value'
 * must correspond to the 'type'. The elements of a CFArray must be either a 
 * CFStringRef or CGImageMetadataTagRef. The keys of a CFDictionary must be 
 * CFStringRefs with valid XMP names. The values of a CFDictionary must be either
 * CFStringRefs or CGImageMetadataTagRefs. A shallow copy of the value is stored
 * in the tag. Therefore, modifying a mutable value after the tag is created 
 * will not affect the tag's value.
 * @result Returns a pointer to a new CGImageMetadataTag. Returns NULL if a tag
 * could not be created with the specified parameters.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef __nullable CGImageMetadataTagCreate (CFStringRef __nonnull xmlns, CFStringRef __nullable prefix, CFStringRef __nonnull name, CGImageMetadataType type, CFTypeRef __nonnull value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// ****************************************************************************
// Getting attributes of a CGImageMetadataTag
// ****************************************************************************
///*! @functiongroup Getting attributes of a CGImageMetadataTag */
/*!
 * @function CGImageMetadataTagCopyNamespace 
 * @abstract Returns a copy of the tag's namespace
 */
IMAGEIO_EXTERN CFStringRef __nullable CGImageMetadataTagCopyNamespace(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagCopyPrefix 
 * @abstract Returns a copy of the tag's prefix
 */
IMAGEIO_EXTERN CFStringRef __nullable CGImageMetadataTagCopyPrefix(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagCopyName 
 * @abstract Returns a copy of the tag's name
 */
IMAGEIO_EXTERN CFStringRef __nullable CGImageMetadataTagCopyName(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagCopyValue 
 * @abstract Returns a shallow copy of the tag's value
 * @discussion This function should only be used to read the tag's value. 
 * CGImageMetadataCopyTagWithPath returns a copy of the tag (including a copy of
 * the tag's value). Therefore mutating a tag's value returned from this function
 * may not actually mutate the value in the CGImageMetadata. It is recommended 
 * to create a new tag followed by CGImageMetadataSetTagWithPath, or use 
 * CGImageMetadataSetValueWithPath to mutate a metadata value. 
 */
IMAGEIO_EXTERN CFTypeRef __nullable CGImageMetadataTagCopyValue(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagGetType
 * @abstract Get the type of the CGImageMetadataTag
 * @return Returns a CGImageMetadataType constant for the CGImageMetadataTag.
 * This is primarily used to determine how to interpret the tag's value.
 */
IMAGEIO_EXTERN CGImageMetadataType CGImageMetadataTagGetType(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagCopyQualifiers
 * @abstract Return a copy of the tag's qualifiers
 * @discussion XMP allows properties to contain supplemental properties called
 * qualifiers. Qualifiers are themselves CGImageMetadataTags with their own 
 * namespace, prefix, name, and value. A common use is the xml:lang qualifier
 * for elements of an alternate-text array.
 * @return Returns a copy of the array of qualifiers. Elements of the array are 
 * CGImageMetadataTags. Returns NULL if the tag does not have any qualifiers. 
 * The copy is shallow, the qualifiers are not deep copied.
 */
IMAGEIO_EXTERN CFArrayRef __nullable CGImageMetadataTagCopyQualifiers(CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Functions for copying CGImageMetadataTagRefs from a CGImageMetadataRef. 
// These functions make it easier for the caller to traverse complex nested 
// structures of metadata, similar to KVC-compliant Objective-C classes.
// ****************************************************************************
///*! @functiongroup Retrieving CGImageMetadataTagRefs from a CGImageMetadataRef */
/*!
 * @function CGImageMetadataCopyTags
 * @abstract Obtain an array of tags from a CGImageMetadataRef
 * @return Returns an array with a shallow copy of all top-level 
 * CGImageMetadataTagRefs in a CGImageMetadataRef.
 */
IMAGEIO_EXTERN CFArrayRef __nullable CGImageMetadataCopyTags(CGImageMetadataRef __nonnull metadata) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCopyTagWithPath
 * @abstract Searches for a specific CGImageMetadataTag in a CGImageMetadataRef
 * @discussion This is the primary function for clients to obtain specific 
 * metadata properties from an image. The 'path' mechanism provides a way to 
 * access both simple top-level properties, such as Date & Time, or complex 
 * deeply-nested properties with ease.
 * @param metadata A collection of metadata tags.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property). If the parent
 * is provided, the effective path will be the concatenation of the parent's path
 * and the 'path' parameter. This is useful for accessing array elements or 
 * structure fields inside nested tags.
 * @param path A string representing a path to the desired tag. Paths consist of
 * a tag prefix (i.e. "exif") joined with a tag name (i.e. "Flash") by a colon 
 * (":"), such as CFSTR("exif:Flash"). 
 * Elements of ordered and unordered arrays are accessed via 0-based indices inside square [] brackets.
 * Elements of alternate-text arrays are accessed by an RFC 3066 language code inside square [] brackets.
 * Fields of a structure are delimited by a period, '.'.
 * Qualifiers are delimited by the '?' character. Only tags with string values (kCGImageMetadataTypeString)
 * are allowed to have qualifiers - arrays and structures may not contain qualifiers.
 *
 * If parent is NULL, a prefix must be specified for the first tag. Prefixes for
 * all subsequent tags are optional. If unspecified, the prefix is 
 * inherented from the nearest parent tag with a prefix. Custom prefixes must be
 * registered using @link CGImageMetadataRegisterNamespaceForPrefix @/link prior to use 
 * in any path-based functions.
 *
 * Examples:
 *  <ul>
 *    <li>'path' = CFSTR("xmp:CreateDate")</li>       
 *    <li>'path' = CFSTR("exif:Flash.Fired")</li>
 *    <li>'parent' = tag at path CFSTR("exif:Flash"), path = CFSTR("exif:Fired") (equivilent to previous)</li>
 *    <li>'path' = CFSTR("exif:Flash.RedEyeMode")</li>
 *    <li>'path' = CFSTR("dc:title")</li>
 *    <li>'path' = CFSTR("dc:subject")</li>
 *    <li>'path' = CFSTR("dc:subject[2]") </li>
 *    <li>'parent' = tag at path CFSTR("dc:subject"), path = CFSTR("[2]") (equivilent to previous)</li>
 *    <li>'path' = CFSTR("dc:description[x-default])"</li>
 *    <li>'path' = CFSTR("dc.description[de])"</li>
 *    <li>'path' = CFSTR("dc.description[fr])"</li>
 *    <li>'path' = CFSTR("foo:product)"</li>
 *    <li>'path' = CFSTR("foo:product?bar:manufacturer)"</li>
 *  </ul>
 * @return Returns a copy of CGImageMetadataTag matching 'path', or NULL if no 
 * match is found. The copy of the tag's value is shallow. Tags
 * copied from an immutable CGImageMetadataRef are also immutable. Because this
 * function returns a copy of the tag's value, any modification of the tag's 
 * value must be followed by a CGImageMetadataSetTagWithPath to commit the 
 * change to the metadata container.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef __nullable CGImageMetadataCopyTagWithPath(CGImageMetadataRef __nonnull metadata, CGImageMetadataTagRef __nullable parent, CFStringRef __nonnull path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCopyStringValueWithPath
 * @abstract Searches for a specific tag in a CGImageMetadataRef and returns its
 * string value.
 * @discussion This is a convenience method for searching for a tag at path and
 * extracting the string value.
 * @param metadata A collection of metadata tags.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @return Returns a string from a CGImageMetadataTag located at 'path'. The 
 * tag must be of type kCGImageMetadataTypeString or kCGImageMetadataTypeAlternateText.
 * For AlternateText tags, the element with the "x-default" language qualifier 
 * will be returned. For other types, NULL will be returned.
 */
IMAGEIO_EXTERN CFStringRef __nullable CGImageMetadataCopyStringValueWithPath(CGImageMetadataRef __nonnull metadata, CGImageMetadataTagRef __nullable parent, CFStringRef __nonnull path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// ****************************************************************************
// Functions for modifying a CGMutableImageMetadataRef
// ****************************************************************************
///*! @functiongroup Modifying a CGMutableImageMetadataRef */
/*!
 * @function CGImageMetadataRegisterNamespaceForPrefix
 * @abstract Associates an XMP namespace URI with a prefix string.
 * @discussion This allows ImageIO to create custom metadata when it encounters 
 * an unrecognized prefix in a path (see CGImageMetadataCopyTagWithPath for more
 * information about path syntax). A namespace must be registered before it can 
 * be used to add custom metadata. All namespaces found in the image's metadata,
 * or defined as a constant above, will be pre-registered. Namespaces and 
 * prefixes must be unique.
 * @return Returns true if successful. Returns false and sets 'err' if an error 
 * or conflict occurs.
 */
IMAGEIO_EXTERN bool CGImageMetadataRegisterNamespaceForPrefix(CGMutableImageMetadataRef __nonnull metadata, CFStringRef __nonnull xmlns, CFStringRef __nonnull prefix, __nullable CFErrorRef * __nullable err) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetTagWithPath
 * @abstract Sets the tag at a specific path in a CGMutableImageMetadata container or a parent tag
 * @discussion This is the primary function for adding new metadata tags to a 
 * metadata container, or updating existing tags. All tags required to reach 
 * the final tag (at the end of the path) will be created, if needed. Tags will
 * created with default types (ordered arrays). Creating tags will fail if a 
 * prefix is encountered that has not been registered. Use
 * @link CGImageMetadataRegisterNamespaceForPrefix @/link to associate a prefix
 * with a namespace prior to using a path-based CGImageMetadata function.
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param metadata A mutable collection of metadata tags. 
 * Use @link CGImageMetadataCreateMutableCopy @/link or 
 * @link CGImageMetadataCreateMutable @/link to obtain a mutable metadata container.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property). 
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @param tag The CGImageMetadataTag to be added to the metadata. The tag
 * will be retained.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetTagWithPath(CGMutableImageMetadataRef __nonnull metadata, CGImageMetadataTagRef __nullable parent, CFStringRef __nonnull path, CGImageMetadataTagRef __nonnull tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetValueWithPath
 * @abstract Sets the value of the tag at a specific path in a CGMutableImageMetadataRef container or a parent tag
 * @discussion This function is used to add new metadata values to a 
 * metadata container, or update existing tag values. All tags required to reach 
 * the final tag (at the end of the path) are created, if needed. Tags are
 * created with default types (i.e. arrays will be ordered). Creating tags will 
 * fail if a prefix is encountered that has not been registered. Use
 * @link CGImageMetadataRegisterNamespaceForPrefix @/link to associate a prefix
 * with a namespace prior to using a path-based CGImageMetadata function.
 *
 * Examples
 * <ul>
 *     <li>'path' = CFSTR("xmp:CreateDate"), 'value' = CFSTR("2011-09-20T14:54:47-08:00")</li>
 *     <li>'path' = CFSTR("dc:subject[0]"), 'value' = CFSTR("San Francisco")</li>
 *     <li>'path' = CFSTR("dc:subject[1]"), 'value' = CFSTR("Golden Gate Bridge")</li>
 *     <li>'path' = CFSTR("dc:description[en]") 'value' = CFSTR("my image description")</li>
 *     <li>'path' = CFSTR("dc:description[de]") 'value' = CFSTR("meine bildbeschreibung")</li>
 * </ul>
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param metadata A mutable collection of metadata tags. 
 * Use @link CGImageMetadataCreateMutableCopy @/link or 
 * @link CGImageMetadataCreateMutable @/link to obtain a mutable metadata container.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @param value The value to be added to the CGImageMetadataTag matching the path.
 * The tag will be retained. The restrictions for the value are the same as in @link
 * CGImageMetadataTagCreate @/link.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueWithPath(CGMutableImageMetadataRef __nonnull metadata, CGImageMetadataTagRef __nullable parent, CFStringRef __nonnull path, CFTypeRef __nonnull value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataRemoveTagWithPath
 * @abstract Removes the tag at a specific path from a CGMutableImageMetadata container or from the parent tag
 * @discussion Use this function to delete a metadata tag matching a specific 
 * path from a mutable metadata container. Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 */
IMAGEIO_EXTERN bool CGImageMetadataRemoveTagWithPath(CGMutableImageMetadataRef __nonnull metadata,  CGImageMetadataTagRef __nullable parent, CFStringRef __nonnull path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


#ifdef __BLOCKS__
///*! @functiongroup Iterating through tags of CGImageMetadataRef */
/*!
 * @typedef CGImageMetadataTagBlock
 * @abstract The block type used by CGImageMetadataEnumerateTagsUsingBlock
 * @param path The full path to the tag in the metadata container.
 * @param tag The CGImageMetadataTagRef corresponding to the path in metadata.
 * @return Return true to continue iterating through the tags, or return false to stop.
 */
typedef bool(^CGImageMetadataTagBlock)(CFStringRef __nonnull path, CGImageMetadataTagRef __nonnull tag);

// Enumerates the children of the tag located at 'path'.
// If 'rootPath' is nil, all top-level tags in 'metadata' will be enumerated.
// Executes a CGImageMetadataTagBlock, 'block', for each CGImageMetadataTag.
// The block should return true to continue enumeration, or false to stop.
// Behavior is undefined if 'metadata' is modified during enumeration.

/*!
 * @function CGImageMetadataEnumerateTagsUsingBlock
 * @abstract Executes a given block using each tag in the metadata
 * @discussion This function iterates over all of the tags in a
 * CGImageMetadataRef, executing the block for each tag. The default behavior 
 * iterates over all top-level tags in the metadata. The path of the tag and 
 * the tag itself is passed to the block. The metadata cannot be modified inside
 * the block - consider adding the tags of interest into another collection.
 * @param metadata A collection of metadata tags.
 * @param rootPath Iteration will occur for all children of the tag matching
 * the root path. Please refer to CGImageMetadataCopyTagWithPath for information
 * about path syntax. If NULL or an empty string, the block will be executed 
 * for all top-level tags in the metadata container.
 * @param options A dictionary of options for iterating through the tags.
 * Currently the only supported option is kCGImageMetadataEnumerateRecursively,
 * which should be set to a CFBoolean.
 * @param block The block that is executed for each tag in metadata.
 */
IMAGEIO_EXTERN void CGImageMetadataEnumerateTagsUsingBlock(CGImageMetadataRef __nonnull metadata, CFStringRef __nullable rootPath, CFDictionaryRef __nullable options, CGImageMetadataTagBlock __nonnull block) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
#endif

// A key for the 'options' of CGImageMetadataEnumerateTagsUsingBlock. If present,
// the value should be a CFBoolean. If true, tags will be enumerated recursively,
// if false, only the direct children of 'rootPath' will be enumerated. 
// The default is non-recursive.
IMAGEIO_EXTERN const CFStringRef __nonnull kCGImageMetadataEnumerateRecursively IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Functions for working with constants defined in CGImageProperties.h
// Provides a bridge for values from CGImageCopyPropertiesAtIndex().
// Simplifies metadata access for properties defined EXIF and IPTC standards, 
// which have no notion of namespaces, prefixes, or XMP property types.
// Metadata Working Group guidance is factored into the mapping of 
// CGImageProperties to XMP. For example, setting Exif DateTimeOriginal will
// set the value of the corresponding XMP tag, which is photoshop:DateCreated
// ****************************************************************************

///*! @functiongroup Working with CGImageProperties */
/*!
 * @function CGImageMetadataCopyTagMatchingImageProperty
 * @abstract Searches for a specific CGImageMetadataTag matching a kCGImageProperty constant
 * @discussion Provides a bridge for values from CGImageCopyPropertiesAtIndex, simplifying 
 * access for properties defined in EXIF and IPTC standards, which have no notion of 
 * namespaces, prefixes, or XMP property types.
 * Metadata Working Group guidance is factored into the mapping of CGImageProperties to 
 * XMP compatible CGImageMetadataTags.
 * For example, kCGImagePropertyExifDateTimeOriginal will get the value of the 
 * corresponding XMP tag, which is photoshop:DateCreated. Note that property values will 
 * still be in their XMP forms, such as "YYYY-MM-DDThh:mm:ss" for DateTime, rather than
 * the EXIF or IPTC DateTime formats.
 * @param metadata A collection of metadata tags
 * @param dictionaryName the metadata subdictionary to which the image property belongs,
 * such as kCGImagePropertyExifDictionary or kCGImagePropertyIPTCDictionary. Not all
 * dictionaries and properties are supported at this time.
 * @param propertyName the name of the property. This must be a defined property constant
 * corresponding to the 'dictionaryName'. For example, kCGImagePropertyTIFFOrientation,
 * kCGImagePropertyExifDateTimeOriginal, or kCGImagePropertyIPTCKeywords. A warning
 * will be logged if the CGImageProperty is unsupported by CGImageMetadata.
 * @return Returns a CGImageMetadataTagRef with the appropriate namespace, prefix, 
 * tag name, and XMP value for the corresponding CGImageProperty. Returns NULL if the 
 * property could not be found.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef __nullable CGImageMetadataCopyTagMatchingImageProperty(CGImageMetadataRef __nonnull metadata, CFStringRef __nonnull dictionaryName, CFStringRef __nonnull propertyName) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetValueMatchingImageProperty
 * @abstract Sets the value of the CGImageMetadataTag matching a kCGImageProperty constant
 * @discussion Provides a bridge for values from CGImageCopyPropertiesAtIndex, simplifying 
 * changing property values defined in EXIF and IPTC standards, which have no notion of 
 * namespaces, prefixes, or XMP property types.
 * Metadata Working Group guidance is factored into the mapping of CGImageProperties to 
 * XMP compatible CGImageMetadataTags.
 * For example, setting kCGImagePropertyExifDateTimeOriginal will set the value of the 
 * corresponding XMP tag, which is photoshop:DateCreated. Note that property values should 
 * still be in their XMP forms, such as "YYYY-MM-DDThh:mm:ss" for DateTime, rather than
 * the EXIF or IPTC DateTime formats. Although this function will allow the caller to set
 * custom values for these properties, you should consult the appropriate specifications 
 * for details about property value formats for EXIF and IPTC tags in XMP.
 * @param metadata A mutable collection of metadata tags
 * @param dictionaryName the metadata subdictionary to which the image property belongs,
 * such as kCGImagePropertyExifDictionary or kCGImagePropertyIPTCDictionary. Not all
 * dictionaries and properties are supported at this time.
 * @param propertyName the name of the property. This must be a defined property constant
 * corresponding to the 'dictionaryName'. For example, kCGImagePropertyTIFFOrientation,
 * kCGImagePropertyExifDateTimeOriginal, or kCGImagePropertyIPTCKeywords. A warning
 * will be logged if the CGImageProperty is unsupported by CGImageMetadata.
 * @param value A CFTypeRef with the value for the tag. The same value restrictions apply
 * as in @link CGImageMetadataTagCreate @/link.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueMatchingImageProperty(CGMutableImageMetadataRef __nonnull metadata, CFStringRef __nonnull dictionaryName, CFStringRef __nonnull propertyName, CFTypeRef __nonnull value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Functions for converting metadata to and from XMP packets
// ****************************************************************************
///*! @functiongroup Reading and Writing XMP */

/*!
 * @function CGImageMetadataCreateXMPData
 * @abstract Serializes the CGImageMetadataRef to XMP data
 * @discussion This converts all of the metadata tags to a block of XMP data. Common uses
 * include creating sidecar files that contain metadata for image formats that do not 
 * support embedded XMP, or cannot be edited due to other format restrictions (such as
 * proprietary RAW camera formats).
 * @param metadata A collection of metadata tags.
 * @param options should be NULL. Options are currently not used, but may be used in 
 * future release.
 * @return Returns a CFData containing an XMP representation of the metadata. Returns
 * NULL if an error occurred. 
 */
IMAGEIO_EXTERN CFDataRef __nullable CGImageMetadataCreateXMPData (CGImageMetadataRef __nonnull metadata, CFDictionaryRef __nullable options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCreateFromXMPData
 * @abstract Creates a collection of CGImageMetadataTags from a block of XMP data
 * @discussion Converts XMP data into a collection of metadata tags.
 * The data must be a complete XMP tree. XMP packet  headers (<?xpacket .. ?>) are 
 * supported.
 * @param data The XMP data.
 * @return Returns a collection of CGImageMetadata tags. Returns NULL if an error occurred. 
 */
IMAGEIO_EXTERN CGImageMetadataRef __nullable CGImageMetadataCreateFromXMPData (CFDataRef __nonnull data) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 *  @constant kCFErrorDomainCGImageMetadata
 *  @discussion Error domain for all errors originating in ImageIO for CGImageMetadata APIs.
 *      Error codes may be interpreted using the list below.
 */
IMAGEIO_EXTERN const CFStringRef __nonnull kCFErrorDomainCGImageMetadata;

/*!
 *  @enum CGImageMetadataErrors
 *  @discussion the list of all error codes returned under the error domain kCFErrorDomainCGImageMetadata
 */
typedef CF_ENUM(int32_t, CGImageMetadataErrors) {
    kCGImageMetadataErrorUnknown = 0,
    kCGImageMetadataErrorUnsupportedFormat = 1,
    kCGImageMetadataErrorBadArgument = 2,
    kCGImageMetadataErrorConflictingArguments = 3,
    kCGImageMetadataErrorPrefixConflict = 4,
};

CF_IMPLICIT_BRIDGING_DISABLED

#endif // CGIMAGEMETADATA_H_
// ==========  ImageIO.framework/Headers/CGImageProperties.h
/*
 * ImageIO - CGImageProperties.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

#ifndef __CGIMAGEPROPERTIES__
#define __CGIMAGEPROPERTIES__

#include <CoreGraphics/CGBase.h>
#include <ImageIO/ImageIOBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Properties that, if returned by CGImageSourceCopyProperties or 
 * CGImageSourceCopyPropertiesAtIndex, contain a dictionary of file-format 
 * or metadata-format specific key-values. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyRawDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyCIFFDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerCanonDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerNikonDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerMinoltaDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerFujiDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerOlympusDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerPentaxDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImageProperty8BIMDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyOpenEXRDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerAppleDictionary  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyFileContentsDictionary IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);


/** Properties which may be returned by "CGImageSourceCopyProperties".  The
 ** values apply to the container in general but not necessarily to any
 ** individual image that it contains. **/

/* The size of the image file in bytes, if known. If present, the value of
 * this key is a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyFileSize  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/** Properties which may be returned by "CGImageSourceCopyPropertiesAtIndex".
 ** The values apply to a single image of an image source file. **/

/* The number of pixels in the x- and y-dimensions. The value of these keys 
 * is a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelHeight  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelWidth  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The DPI in the x- and y-dimensions, if known. If present, the value of
 * these keys is a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDPIHeight  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDPIWidth  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The number of bits in each color sample of each pixel. The value of this 
 * key is a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDepth  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The intended display orientation of the image. If present, the value 
 * of this key is a CFNumberRef with the same value as defined by the 
 * TIFF and Exif specifications.  That is:
 *   1  =  0th row is at the top, and 0th column is on the left.  
 *   2  =  0th row is at the top, and 0th column is on the right.  
 *   3  =  0th row is at the bottom, and 0th column is on the right.  
 *   4  =  0th row is at the bottom, and 0th column is on the left.  
 *   5  =  0th row is on the left, and 0th column is the top.  
 *   6  =  0th row is on the right, and 0th column is the top.  
 *   7  =  0th row is on the right, and 0th column is the bottom.  
 *   8  =  0th row is on the left, and 0th column is the bottom.  
 * If not present, a value of 1 is assumed. */ 
 
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyOrientation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The value of this key is kCFBooleanTrue if the image contains floating- 
 * point pixel samples */ 
 
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIsFloat  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The value of this key is kCFBooleanTrue if the image contains indexed 
 * (a.k.a. paletted) pixel samples */ 
 
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIsIndexed  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The value of this key is kCFBooleanTrue if the image contains an alpha 
 * (a.k.a. coverage) channel */ 
 
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHasAlpha  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The color model of the image such as "RGB", "CMYK", "Gray", or "Lab".
 * The value of this key is CFStringRef. */ 

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* The name of the optional ICC profile embedded in the image, if known.  
 * If present, the value of this key is a CFStringRef. */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyProfileName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Possible values for kCGImagePropertyColorModel property */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelRGB  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelGray  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelCMYK  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelLab  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Possible keys for kCGImagePropertyTIFFDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFCompression  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFPhotometricInterpretation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDocumentName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFImageDescription  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFMake  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFOrientation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFXResolution  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFYResolution  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFResolutionUnit  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFSoftware  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTransferFunction  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDateTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFArtist  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFHostComputer  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFCopyright  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFWhitePoint  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFPrimaryChromaticities  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTileWidth  IMAGEIO_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTileLength  IMAGEIO_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/* Possible keys for kCGImagePropertyJFIFDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFXDensity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFYDensity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFDensityUnit  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFIsProgressive  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Possible keys for kCGImagePropertyExifDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureProgram  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSpectralSensitivity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedRatings  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifOECF  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSensitivityType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifStandardOutputSensitivity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifRecommendedExposureIndex  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeed  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedLatitudeyyy  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedLatitudezzz  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDateTimeOriginal  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDateTimeDigitized  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifComponentsConfiguration  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCompressedBitsPerPixel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifShutterSpeedValue  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifApertureValue  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifBrightnessValue  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureBiasValue  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMaxApertureValue  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistance  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMeteringMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLightSource  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlash  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalLength  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectArea  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMakerNote  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifUserComment  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOriginal  IMAGEIO_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_10_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeDigitized  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlashPixVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifColorSpace  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifPixelXDimension  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifPixelYDimension  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifRelatedSoundFile  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlashEnergy  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSpatialFrequencyResponse  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneXResolution  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneYResolution  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneResolutionUnit  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectLocation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureIndex  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSensingMethod  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFileSource  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSceneType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCFAPattern  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCustomRendered  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifWhiteBalance  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDigitalZoomRatio  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalLenIn35mmFilm  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSceneCaptureType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifGainControl  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifContrast  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSaturation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSharpness  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDeviceSettingDescription  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistRange  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifImageUniqueID  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCameraOwnerName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifBodySerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensSpecification  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensMake  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifGamma  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* deprecated */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOrginal IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Possible keys for kCGImagePropertyExifAuxDictionary */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensInfo    IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxSerialNumber    IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensID  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensSerialNumber    IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxImageNumber IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxFlashCompensation   IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxOwnerName   IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxFirmware    IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);

/* Possible keys for kCGImagePropertyGIFDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFLoopCount  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFDelayTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFImageColorMap  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFHasGlobalColorMap  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);

/* Possible keys for kCGImagePropertyPNGDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGGamma  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGInterlaceType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGXPixelsPerMeter  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGYPixelsPerMeter  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGsRGBIntent  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGChromaticities  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGAuthor  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCopyright  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCreationTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGDescription  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGModificationTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGSoftware  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGTitle  IMAGEIO_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGLoopCount  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGDelayTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Possible keys for kCGImagePropertyGPSDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLatitudeRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLatitude  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLongitudeRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLongitude  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAltitudeRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAltitude  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTimeStamp  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSatellites  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSStatus  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSMeasureMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDOP  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSpeedRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSpeed  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTrackRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTrack  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSImgDirectionRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSImgDirection  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSMapDatum  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitudeRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitude  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitudeRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitude  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestBearingRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestBearing  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestDistanceRef  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestDistance  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSProcessingMethod  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAreaInformation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDateStamp  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDifferental  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSHPositioningError  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Possible keys for kCGImagePropertyIPTCDictionary */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectTypeReference  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectAttributeReference  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCEditStatus  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCEditorialUpdate  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCUrgency  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSubjectReference  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCategory  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSupplementalCategory  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCFixtureIdentifier  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCKeywords  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationCode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseDate  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationDate  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSpecialInstructions  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCActionAdvised  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceService  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceDate  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDateCreated  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCTimeCreated  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationDate  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCOriginatingProgram  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCProgramVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectCycle  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCByline  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCBylineTitle  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSubLocation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCProvinceState  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationCode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCOriginalTransmissionReference  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCHeadline  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCredit  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSource  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCopyrightNotice  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContact  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCaptionAbstract  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCWriterEditor  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCImageType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCImageOrientation  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCLanguageIdentifier  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCStarRating  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCreatorContactInfo  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);  // IPTC Core
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCRightsUsageTerms  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);    // IPTC Core
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCScene  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);               // IPTC Core

/* Possible keys for kCGImagePropertyIPTCCreatorContactInfo dictionary (part of IPTC Core - above) */

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCity  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCountry  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoAddress  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPostalCode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoStateProvince  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoEmails  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPhones  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoWebURLs  IMAGEIO_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);

/* Possible keys for kCGImageProperty8BIMDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImageProperty8BIMLayerNames  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageProperty8BIMVersion     IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Possible keys for kCGImagePropertyDNGDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBackwardVersion  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGUniqueCameraModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGLocalizedCameraModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGLensInfo  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);


/* Possible keys for kCGImagePropertyCIFFDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFDescription  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFirmware  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFOwnerName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageFileName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseMethod  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseTiming  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFRecordID  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFSelfTimingTime  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFContinuousDrive  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFocusMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFMeteringMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFShootingMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMaxMM  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMinMM  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFWhiteBalanceIndex  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFMeasuredEV  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);


/* Possible keys for kCGImagePropertyMakerNikonDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSetting  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonColorMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonQuality  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonWhiteBalanceMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonSharpenMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashSetting  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSelection  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonImageAdjustment  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensAdapter  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensType  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensInfo  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusDistance  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonDigitalZoom  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShootingMode  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShutterCount  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);

/* Possible keys for kCGImagePropertyMakerCanonDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonOwnerName  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonImageSerialNumber  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonContinuousDrive  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonLensModel  IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFirmware    IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonAspectRatioInfo IMAGEIO_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);

/* Possible keys for kCGImagePropertyOpenEXRDictionary */

IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyOpenEXRAspectRatio  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);


/* Possible int values for kCGImagePropertyTIFFOrientation */
typedef CF_ENUM(uint32_t, CGImagePropertyOrientation) {
    kCGImagePropertyOrientationUp = 1,        // 0th row at top,    0th column on left   - default orientation
    kCGImagePropertyOrientationUpMirrored,    // 0th row at top,    0th column on right  - horizontal flip
    kCGImagePropertyOrientationDown,          // 0th row at bottom, 0th column on right  - 180 deg rotation
    kCGImagePropertyOrientationDownMirrored,  // 0th row at bottom, 0th column on left   - vertical flip
    kCGImagePropertyOrientationLeftMirrored,  // 0th row on left,   0th column at top
    kCGImagePropertyOrientationRight,         // 0th row on right,  0th column at top    - 90 deg CW
    kCGImagePropertyOrientationRightMirrored, // 0th row on right,  0th column on bottom
    kCGImagePropertyOrientationLeft           // 0th row on left,   0th column at bottom - 90 deg CCW
};


/*
 * Allows client to choose the filters applied before PNG compression
 * http://www.libpng.org/pub/png/book/chapter09.html#png.ch09.div.1
 * The value should be a CFNumber, of type long, containing a bitwise OR of the desired filters
 * The filters are defined below, IMAGEIO_PNG_NO_FILTERS, IMAGEIO_PNG_FILTER_NONE, etc
 * This value has no effect when compressing to any format other than PNG
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCompressionFilter IMAGEIO_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

#define IMAGEIO_PNG_NO_FILTERS     0x00
#define IMAGEIO_PNG_FILTER_NONE    0x08
#define IMAGEIO_PNG_FILTER_SUB     0x10
#define IMAGEIO_PNG_FILTER_UP      0x20
#define IMAGEIO_PNG_FILTER_AVG     0x40
#define IMAGEIO_PNG_FILTER_PAETH   0x80
#define IMAGEIO_PNG_ALL_FILTERS (IMAGEIO_PNG_FILTER_NONE | IMAGEIO_PNG_FILTER_SUB | IMAGEIO_PNG_FILTER_UP | IMAGEIO_PNG_FILTER_AVG | IMAGEIO_PNG_FILTER_PAETH)



/* For use with CGImageSourceCopyAuxiliaryDataInfoAtIndex and CGImageDestinationAddAuxiliaryDataInfo:
 * These strings specify the 'auxiliaryImageDataType':
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeDepth IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeDisparity IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);


/* Depth/Disparity data support for JPEG, HEIF, and DNG images:
 * CGImageSourceCopyAuxiliaryDataInfoAtIndex and CGImageDestinationAddAuxiliaryDataInfo will use these keys in the dictionary:
 * kCGImageAuxiliaryDataInfoData - the depth data (CFDataRef)
 * kCGImageAuxiliaryDataInfoDataDescription - the depth data description (CFDictionary)
 * kCGImageAuxiliaryDataInfoMetadata - metadata (CGImageMetadataRef)
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoData IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoDataDescription IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoMetadata IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);


IMAGEIO_EXTERN const CFStringRef kCGImagePropertyImageCount IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWidth IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHeight IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyBytesPerRow IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyNamedColorSpace IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelFormat IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyImages IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyThumbnailImages IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAuxiliaryData IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAuxiliaryDataType IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);


CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif  /* __CGIMAGEPROPERTIES__ */
// ==========  ImageIO.framework/Headers/CGImageSource.h
/*
 * ImageIO - CGImageSource.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGESOURCE_H_
#define CGIMAGESOURCE_H_

#include <ImageIO/ImageIOBase.h>

typedef struct IIO_BRIDGED_TYPE(id) CGImageSource * CGImageSourceRef;

#include <CoreGraphics/CoreGraphics.h>
#include "CGImageMetadata.h"

CF_IMPLICIT_BRIDGING_ENABLED

typedef CF_ENUM(int32_t, CGImageSourceStatus) {
    kCGImageStatusUnexpectedEOF = -5,
    kCGImageStatusInvalidData = -4,
    kCGImageStatusUnknownType = -3,
    kCGImageStatusReadingHeader = -2,
    kCGImageStatusIncomplete = -1,
    kCGImageStatusComplete = 0
};

CF_ASSUME_NONNULL_BEGIN

/** Keys for the options dictionary when creating a CGImageSourceRef. **/

/* Specifies the "best guess" of the type identifier for the format of the
 * image source file. If specified, the value of this key must be a
 * CFStringRef. For more information about type identifiers, see "UTType.h"
 * in the Application Services framework. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceTypeIdentifierHint  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/** Keys for the options dictionary of "CGImageSourceCopyPropertiesAtIndex"
 ** and "CGImageSourceCreateImageAtIndex". **/

/* Specifies whether the image should be cached in a decoded form. The
 * value of this key must be a CFBooleanRef.
 * kCFBooleanFalse indicates no caching, kCFBooleanTrue indicates caching.
 * For 64-bit architectures, the default is kCFBooleanTrue, for 32-bit the default is kCFBooleanFalse.
 */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCache  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specifies whether image decoding and caching should happen at image creation time.
 * The value of this key must be a CFBooleanRef. The default value is kCFBooleanFalse (image decoding will
 * happen at rendering time).
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCacheImmediately  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/* Specifies whether the image should be returned as a floating
 * point CGImageRef if supported by the file format. Extended
 * range floating point CGImageRef may require additional
 * processing  to render pleasingly.  The value of this key must
 * be a CFBooleanRef; the default value is kCFBooleanFalse. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldAllowFloat  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/** Keys for the options dictionary of
 ** "CGImageSourceCreateThumbnailAtIndex". **/

/* Specifies whether a thumbnail should be automatically created for an
 * image if a thumbnail isn't present in the image source file.  The
 * thumbnail will be created from the full image, subject to the limit
 * specified by kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel
 * size isn't specified, then the thumbnail will be the size of the full
 * image, which probably isn't what you want. The value of this key must be
 * a CFBooleanRef; the default value of this key is kCFBooleanFalse. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageIfAbsent  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specifies whether a thumbnail should be created from the full image even
 * if a thumbnail is present in the image source file. The thumbnail will
 * be created from the full image, subject to the limit specified by
 * kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel size isn't
 * specified, then the thumbnail will be the size of the full image, which
 * probably isn't what you want. The value of this key must be a
 * CFBooleanRef; the default value of this key is kCFBooleanFalse. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageAlways  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specifies the maximum width and height in pixels of a thumbnail.  If
 * this this key is not specified, the width and height of a thumbnail is
 * not limited and thumbnails may be as big as the image itself.  If
 * present, this value of this key must be a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceThumbnailMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specifies whether the thumbnail should be rotated and scaled according
 * to the orientation and pixel aspect ratio of the full image. The value
 * of this key must be a CFBooleanRef; the default value of this key is 
 * kCFBooleanFalse. */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailWithTransform  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specifies that, if possible, an image should be returned as scaled down (in height and width) by a specified factor.
 * The resulting image will be smaller and have reduced spacial quality but will otherwise have the same characteristics
 * as the full size normal image.
 * If the specified scaling factor is not supported, a larger or full size normal image will be returned.
 * Supported file formats are JPEG, HEIF, TIFF, and PNG.
 * The value of this key must be an integer CFNumberRef (allowed values: 2, 4, and 8).
 */

IMAGEIO_EXTERN const CFStringRef kCGImageSourceSubsampleFactor  IMAGEIO_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CF_ASSUME_NONNULL_END


/* Return the CFTypeID for CGImageSources. */

IMAGEIO_EXTERN CFTypeID CGImageSourceGetTypeID (void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return an array of supported type identifiers. */

IMAGEIO_EXTERN CFArrayRef __nonnull CGImageSourceCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image source reading from the data provider `provider'. The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

IMAGEIO_EXTERN CGImageSourceRef __nullable CGImageSourceCreateWithDataProvider(CGDataProviderRef __nonnull provider, CFDictionaryRef __nullable options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image source reading from `data'.  The `options' dictionary
 * may be used to request additional creation options; see the list of keys
 * above for more information. */

IMAGEIO_EXTERN CGImageSourceRef __nullable CGImageSourceCreateWithData(CFDataRef __nonnull data, CFDictionaryRef __nullable options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image source reading from `url'. The `options' dictionary may
 * be used to request additional creation options; see the list of keys
 * above for more information. */

IMAGEIO_EXTERN CGImageSourceRef __nullable CGImageSourceCreateWithURL(CFURLRef __nonnull url, CFDictionaryRef __nullable options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the type identifier of the image source `isrc'.  This type is the
 * type of the source "container", which is not necessarily the type of the
 * image(s) in the container.  For example, the .icns format supports
 * embedded JPEG2000 but the source type will be "com.apple.icns". */

IMAGEIO_EXTERN CFStringRef __nullable CGImageSourceGetType(CGImageSourceRef __nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the number of images (not including thumbnails) in the image
 * source `isrc'. */

IMAGEIO_EXTERN size_t CGImageSourceGetCount(CGImageSourceRef __nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the properties of the image source `isrc'.  These properties
 * apply to the container in general but not necessarily to any individual
 * image that it contains. */

IMAGEIO_EXTERN CFDictionaryRef __nullable CGImageSourceCopyProperties(CGImageSourceRef __nonnull isrc, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the properties of the image at `index' in the image source
 * `isrc'.  The index is zero-based. The `options' dictionary may be used
 * to request additional options; see the list of keys above for more
 * information. */

IMAGEIO_EXTERN CFDictionaryRef __nullable CGImageSourceCopyPropertiesAtIndex(CGImageSourceRef __nonnull isrc, size_t index, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the metadata of the image at `index' in the image source
 * `isrc'. The index is zero-based. The `options' dictionary may be used
 * to request additional options; see the list of keys above for more
 * information. Please refer to CGImageMetadata.h for usage of metadata. */
IMAGEIO_EXTERN CGImageMetadataRef __nullable CGImageSourceCopyMetadataAtIndex (CGImageSourceRef __nonnull isrc, size_t index, CFDictionaryRef __nullable options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);

/* Return the image at `index' in the image source `isrc'.  The index is
 * zero-based. The `options' dictionary may be used to request additional
 * creation options; see the list of keys above for more information. */

IMAGEIO_EXTERN CGImageRef __nullable CGImageSourceCreateImageAtIndex(CGImageSourceRef __nonnull isrc, size_t index, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Remove the cached decoded image data for the image at `index' in the image source `isrc'.
 * The index is zero-based.
 */
IMAGEIO_EXTERN void CGImageSourceRemoveCacheAtIndex(CGImageSourceRef __nonnull isrc, size_t index) IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/* Return the thumbnail of the image at `index' in the image source `isrc'.
 * The index is zero-based. The `options' dictionary may be used to request
 * additional thumbnail creation options; see the list of keys above for
 * more information. */

IMAGEIO_EXTERN CGImageRef __nullable CGImageSourceCreateThumbnailAtIndex(CGImageSourceRef __nonnull isrc, size_t index, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an incremental image source. No data is provided at creation
 * time; it is assumed that data will eventually be provided using
 * "CGImageSourceUpdateDataProvider" or "CGImageSourceUpdateData".  The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

IMAGEIO_EXTERN CGImageSourceRef __nonnull CGImageSourceCreateIncremental(CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Update the incremental image source `isrc' with new data.  The new data
 * must include all the previous data plus any additional new data. The
 * `final' parameter should be true when the final set of data is provided;
 * false otherwise. */

IMAGEIO_EXTERN void CGImageSourceUpdateData(CGImageSourceRef __nonnull isrc, CFDataRef __nonnull data, bool final)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Update the incremental image source `isrc' with a new data provider.
 * The new data provider must provide all the previous data plus any
 * additional new data. The `final' parameter should be true when the final
 * set of data is provided; false otherwise. */

IMAGEIO_EXTERN void CGImageSourceUpdateDataProvider(CGImageSourceRef __nonnull isrc, CGDataProviderRef __nonnull provider, bool final)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the overall status of the image source `isrc'.  The status is
 * particularly informative for incremental image sources, but may be used
 * by clients providing non-incremental data as well. */

IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatus(CGImageSourceRef __nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return the current status of the image at `index' in the image source
 * `isrc'. The index is zero-based. The returned status is particularly
 * informative for incremental image sources but may used by clients
 * providing non-incremental data as well. */

IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatusAtIndex(CGImageSourceRef __nonnull isrc, size_t index)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Depth data support for JPEG, HEIF, and DNG images.
 * The returned CFDictionary contains:
 *   - the depth data (CFDataRef) - (kCGImageAuxiliaryDataInfoData),
 *   - the depth data description (CFDictionary) - (kCGImageAuxiliaryDataInfoDataDescription)
 *   - metadata (CGImageMetadataRef) - (kCGImageAuxiliaryDataInfoMetadata)
 * CGImageSourceCopyAuxiliaryDataInfoAtIndex returns nil if the image did not contain ‘auxiliaryImageDataType’ data.
 */
IMAGEIO_EXTERN CFDictionaryRef __nullable CGImageSourceCopyAuxiliaryDataInfoAtIndex(CGImageSourceRef __nonnull isrc, size_t index, CFStringRef __nonnull auxiliaryImageDataType ) IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);

CF_IMPLICIT_BRIDGING_DISABLED


#endif  /* CGIMAGESOURCE_H_ */
// ==========  ImageIO.framework/Headers/CGImageDestination.h
/*
 * ImageIO - CGImageDestination.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGEDESTINATION_H_
#define CGIMAGEDESTINATION_H_

#include <ImageIO/ImageIOBase.h>

typedef struct IIO_BRIDGED_TYPE(id) CGImageDestination * CGImageDestinationRef;

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/CGImageSource.h>
#include <ImageIO/CGImageMetadata.h>

CF_IMPLICIT_BRIDGING_ENABLED

/** Properties which may be passed to "CGImageDestinationAddImage"
 ** or "CGImageDestinationAddImageFromSource" to effect the output.
 ** The values apply to a single image of an image destination. **/

CF_ASSUME_NONNULL_BEGIN

/* The desired compression quality to use when writing to an image 
 * destination. If present, the value of this key is a CFNumberRef 
 * in the range 0.0 to 1.0. A value of 1.0 implies lossless
 * compression is desired if destination format supports it. 
 * A value of 0.0 implies that that maximum compression is 
 * desired. */

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationLossyCompressionQuality  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* The desired background color to composite against when writing 
 * an image with alpha to a destination format that does not support 
 * alpha. If present, the value of this key is a CGColorRef without
 * any alpha component of its own.  If not present a white color
 * will be used if needed. */

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationBackgroundColor  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Rescale the image to the maximum width and height in pixels.
 * If present, this value of this key must be a CFNumberRef. */

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationImageMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Enable or disable thumbnail embedding for JPEG and HEIF.
 * The value should be kCFBooleanTrue or kCFBooleanFalse. Defaults to kCFBooleanFalse */

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEmbedThumbnail  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

CF_ASSUME_NONNULL_END


/* Return the CFTypeID for CGImageDestinations. */

IMAGEIO_EXTERN CFTypeID CGImageDestinationGetTypeID(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Return an array of supported type identifiers. */

IMAGEIO_EXTERN CFArrayRef __nonnull CGImageDestinationCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image destination writing to the data consumer `consumer'.
 * The parameter `type' specifies the type identifier of the resulting
 * image file.  The parameter `count' specifies number of images (not
 * including thumbnails) that the image file will contain. The `options'
 * dictionary is reserved for future use; currently, you should pass NULL
 * for this parameter. */

IMAGEIO_EXTERN CGImageDestinationRef __nullable CGImageDestinationCreateWithDataConsumer(CGDataConsumerRef __nonnull consumer, CFStringRef __nonnull type, size_t count, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image destination writing to `data'. The parameter `type'
 * specifies the type identifier of the resulting image file.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter. */

IMAGEIO_EXTERN CGImageDestinationRef __nullable CGImageDestinationCreateWithData(CFMutableDataRef __nonnull data, CFStringRef __nonnull type, size_t count, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Create an image destination writing to `url'. The parameter `type'
 * specifies the type identifier of the resulting image file.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter.
 * Note that if `url' already exists, it will be overwritten. */

IMAGEIO_EXTERN CGImageDestinationRef __nullable CGImageDestinationCreateWithURL(CFURLRef __nonnull url, CFStringRef __nonnull type, size_t count, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Specify the dictionary `properties' of properties which apply to all
 * images in the image destination `idst'. */

IMAGEIO_EXTERN void CGImageDestinationSetProperties(CGImageDestinationRef __nonnull idst, CFDictionaryRef __nullable properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Set the next image in the image destination `idst' to be `image' with
 * optional properties specified in `properties'.  An error is logged if
 * more images are added than specified in the original count of the image
 * destination. */

IMAGEIO_EXTERN void CGImageDestinationAddImage(CGImageDestinationRef __nonnull idst, CGImageRef __nonnull image, CFDictionaryRef __nullable properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Set the next image in the image destination `idst' to be the image at
 * `index' in the image source `isrc'.  The index is zero-based. The
 * properties of the source image can be added to or overriden by supplying
 * additional keys/values in `properties'.  If a key in `properties' has
 * the value kCFNull, the corresponding property in the destination will be
 * removed. */

IMAGEIO_EXTERN void CGImageDestinationAddImageFromSource(CGImageDestinationRef __nonnull idst, CGImageSourceRef __nonnull isrc, size_t index, CFDictionaryRef __nullable properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/* Write everything to the destination data, url or consumer of the image
 * destination `idst'.  You must call this function or the image
 * destination will not be valid.  After this function is called, no
 * additional data will be written to the image destination.  Return true
 * if the image was successfully written; false otherwise. */

IMAGEIO_EXTERN bool CGImageDestinationFinalize(CGImageDestinationRef __nonnull idst)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Set the next image in the image destination `idst' to be `image' with
 * metadata properties specified in `metadata'. An error is logged if more
 * images are added than specified in the original count of the image
 * destination. */
IMAGEIO_EXTERN void CGImageDestinationAddImageAndMetadata(CGImageDestinationRef __nonnull idst, CGImageRef __nonnull image, CGImageMetadataRef __nullable metadata, CFDictionaryRef __nullable options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/**
 ** Keys which may be used in the 'options' dictionary of
 ** "CGImageDestinationCopyImageSource" to effect the output.
 **/

CF_ASSUME_NONNULL_BEGIN

/* Set the metadata tags for the image destination. If present, the value of
 * this key is a CGImageMetadataRef. By default, all EXIF, IPTC, and XMP tags
 * will be replaced. Use kCGImageDestinationMergeMetadata to merge the tags
 * with the existing tags in the image source.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMetadata IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/* If true, The metadata will be copied from the source and merged with the tags
 * specified in kCGImageDestinationMetadata. If a tag does not exist in the 
 * source, it will be added. If the tag exists in the source, it will be 
 * updated. A metadata tag can be removed by setting the tag's value to 
 * kCFNull. If present, the value of this key is a CFBoooleanRef. The default
 * is kCFBooleanFalse.
 */ 
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMergeMetadata IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/* XMP data will not be written to the destination. If used in conjunction with 
 * kCGImageDestinationMetadata, EXIF and/or IPTC tags will be preserved, but 
 * an XMP packet will not be written to the file. If present, the value for 
 * this key is a CFBooleanRef. The default is kCFBooleanFalse.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeXMP IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/* If true, GPS metadata will not be written to EXIF data or the corresponding
 * EXIF tags in XMP. This flag cannot filter any proprietary location data that
 * could be stored in a manufacturer's EXIF MakerNote or custom XMP properties.
 * If present, the value for this key is a CFBooleanRef. The default is 
 * kCFBooleanFalse.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeGPS IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Updates the DateTime parameters of the image metadata. Only values
 * present in the original image will updated. If present, the value should
 * be a CFStringRef or a CFDateRef. If CFString, the value must be in 
 * Exif DateTime or ISO 8601 DateTime format. This option is mutually
 * exclusive with kCGImageDestinationMetadata.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationDateTime IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/* Updates the orientation in the image metadata. The image data itself will
 * not be rotated. If present, the value should be a CFNumberRef from 1 to 8. 
 * This option is mutually exclusive with kCGImageDestinationMetadata.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationOrientation IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

CF_ASSUME_NONNULL_END

/* Losslessly copies the contents of the image source, 'isrc', to the 
 * destination, 'idst'. The image data will not be modified. The image's 
 * metadata can be modified by adding the keys and values defined above to 
 * 'options'. No other images should be added to the image destination. 
 * CGImageDestinationFinalize() should not be called afterward -
 * the result is saved to the destination when this function returns. 
 * The image type of the destination must match the image source. Returns true
 * if the operation was successful. If an error occurs, false will be returned 
 * and 'err' will be set to a CFErrorRef. Not all image formats are supported 
 * for this operation. */
IMAGEIO_EXTERN bool CGImageDestinationCopyImageSource(CGImageDestinationRef __nonnull idst, CGImageSourceRef __nonnull isrc, CFDictionaryRef __nullable options, __nullable CFErrorRef * __nullable err) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/* Depth data support for JPEG, HEIF, and DNG images.
 * The auxiliaryDataInfoDictionary should contain:
 *   - the depth data (CFDataRef) - (kCGImageAuxiliaryDataInfoData),
 *   - the depth data description (CFDictionary) - (kCGImageAuxiliaryDataInfoDataDescription)
 *   - metadata (CGImageMetadataRef) - (kCGImageAuxiliaryDataInfoMetadata)
 * To add depth data to an image, call CGImageDestinationAddAuxiliaryDataInfo() after adding the CGImage to the CGImageDestinationRef.
 */
IMAGEIO_EXTERN void CGImageDestinationAddAuxiliaryDataInfo(CGImageDestinationRef __nonnull idst, CFStringRef __nonnull auxiliaryImageDataType, CFDictionaryRef __nonnull auxiliaryDataInfoDictionary ) IMAGEIO_AVAILABLE_STARTING(__MAC_10_13, __IPHONE_11_0);


CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGIMAGEDESTINATION_H_ */
