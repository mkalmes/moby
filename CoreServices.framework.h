// ==========  CoreServices.framework/Headers/UTType.h
/*
     File:       UTType.h
 
     Contains:   Public interfaces for uniform type identifiers
 
     Copyright:  (c) 2003-2012 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __UTTYPE__
#define __UTTYPE__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif


#include <Availability.h>


#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif



CF_ASSUME_NONNULL_BEGIN



/* ======================================================================================================== */
/* Uniform Type Identification API                                                                          */
/* ======================================================================================================== */
/*
    Uniform Type Identification Primer

    Uniform Type Identifiers (or UTIs) are strings which uniquely identify
    abstract types. They can be used to describe a file format or an
    in-memory data type, but can also be used to describe the type of
    other sorts of entities, such as directories, volumes, or packages.

    The syntax of a uniform type identifier looks like a bundle identifier.
    It has the form of a reversed DNS name, although some special top-level 
    UTI domains are reserved by Apple and are outside the current IANA 
    top-level Internet domain name space.

    Examples:

        public.jpeg
        public.utf16-plain-text
        com.apple.xml-property-list

    Types which are standard or not controlled by any one organization 
    are declared in the "public" domain. Currently, public types may  
    be declared only by Apple.

    Types specific to Mac OS are declared with identifiers in the 
    com.apple.macos domain.

    Third parties should declare their own uniform type identifiers
    in their respective registered Internet domain spaces.

    Type declarations appear in bundle property lists and tell
    the system several things about a type, including the following:

    Conformance

    A type may "conform" to one or more other types. For example, the
    type com.apple.xml-property-list conforms to both the
    com.apple.property-list and public.xml types. The public.xml 
    type in turn conforms to type public.text. Finally, type public.text  
    conforms to public.data, which is the base type for all types 
    describing bytes stream formats. Conformance relationships between 
    types are established in type declarations.

    Conformance relationships establish a multiple inheritanace hierarchy
    between types. Type property values may be inherited at runtime
    according to the conformance relationships for each type. When a type's 
    declaration does not include a value for particular type property, 
    then the type's supertypes are searched for a value. Supertypes are 
    searched depth-first, in the order given in the type declaration. 
    This is the only way in which the declared order of the conforms-to 
    supertypes is significant.

    Tags

    A "tag" is a string which indicates a type in some other type 
    identification space, such as a filename extension, MIME Type,
    or NSPboardType. Each type declaration may include a 
    "tag specification", which is a dictionary listing all of the 
    tags associated with the type.

    A tag's "class" is the namespace of a tag: filename extension, 
    MIME type, OSType, etc. Tag classes are themselves identified by 
    uniform type identifiers so that the set of valid tag classes is 
    easily extendend in the future.

    Other Type Properties

    Type declarations may include several other properties: a localizable
    user description of the type, the name of an icon resource in
    the declaring bundle, a reference URL identifying technical 
    documentation about the type itself, and finally a version number, 
    which can be incremented as a type evolves. All of these properties
    are optional.

    Exported vs. Imported Type Declarations

    Type declarations are either exported or imported. An exported
    type declaration means that the type itself is defined or owned 
    by the organization making the declaration. For example, a propietary
    document type declaration should only be exported by the application
    which controls the document format.

    An imported declaration is for applications which depend on the
    existence of someone else's type declaration. If application A can
    open application B's document format, then application A makes
    an imported declaration of application B's document type so that
    even if application B is not present on the system, there is an
    acessible declaration of its document type.

    An exported declaration of a particular type identifier is always
    preferred over an imported declaration.

    Example XML Type Declaration

    Appearing below is an XML excerpt from a bundle Info.plist file which 
    declares the public type "public.jpeg":
    
        <key>UTExportedTypeDeclarations</key>
        <array>
            <dict>
                <key>UTTypeIdentifier</key>
                <string>public.jpeg</string>
                <key>UTTypeDescription</key>
                <string>JPEG image</string>
                <key>UTTypeIconFile</key>
                <string>public.jpeg.icns</string>
                <key>UTTypeConformsTo</key>
                <array>
                    <string>public.image</string>
                </array>
                <key>UTTypeTagSpecification</key>
                <dict>
                    <key>com.apple.ostype</key>
                    <string>JPEG</string>
                    <key>public.filename-extension</key>
                    <array>
                        <string>jpeg</string>
                        <string>jpg</string>
                    </array>
                    <key>public.mime-type</key>
                    <string>image/jpeg</string>
                </dict>
            </dict>
        </array>


    Dynamic Type Identifiers

    Uniform Type Identifiation uses dynamic type identifiers to
    represent types for which no identifier has been declared. A
    dynamic type identifier is syntactially a regular uniform
    type identifier in the "dyn" domain. However, after the
    initial domain label, a dynamic type identifier is an 
    opaque encoding of a tag specification. Dynamic type 
    identifiers cannot be declared. They are generated on-demand
    with whatever type information is available at the time, often 
    a single (otherwise unknown) type tag.

    A dynamic identifier therefore carries within it a minimal
    amount of type information, but enough to work well with the
    Uniform Type Identification API. For example, a client can
    extract from a dynamic type identifier the original tag
    specification with which it was created. A client can also
    test a dynamic type identifier for equality to another
    uniform type identifier. If the dynamic identifier's
    tag specification is a subset of the other identifier's
    tags, the two are considered equal.

    Dynamic type identifiers do not express the full richness
    of type information associated with a declared type 
    identifier, but dynamic type identifiers allow the behavior
    to degrade gracefully in the presence of incomplete 
    declared type information.

    A dynamic type identifier may be transmitted across processes
    on a given system, but it should never be stored persistently
    or transmitted over the wire to another system. In particular,
    dynamic identifiers should not appear in bundle info property
    lists, and they will generally be ignored when they do. Apple 
    reserves the right to change the opaque format of dynamic
    identifiers in future versions of Mac OS X.
*/

/*
    Type Declaration Dictionary Keys

    The following keys are used in type declarations
*/
/*
 *  kUTExportedTypeDeclarationsKey
 */
extern const CFStringRef kUTExportedTypeDeclarationsKey              API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTImportedTypeDeclarationsKey
 */
extern const CFStringRef kUTImportedTypeDeclarationsKey              API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeIdentifierKey
 */
extern const CFStringRef kUTTypeIdentifierKey                        API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeTagSpecificationKey
 */
extern const CFStringRef kUTTypeTagSpecificationKey                  API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeConformsToKey
 */
extern const CFStringRef kUTTypeConformsToKey                        API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeDescriptionKey
 */
extern const CFStringRef kUTTypeDescriptionKey                       API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeIconFileKey
 */
extern const CFStringRef kUTTypeIconFileKey                          API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeReferenceURLKey
 */
extern const CFStringRef kUTTypeReferenceURLKey                      API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTypeVersionKey
 */
extern const CFStringRef kUTTypeVersionKey                           API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );


/*
    Type Tag Classes

    The following constant strings identify tag classes for use 
    when converting uniform type identifiers to and from
    equivalent tags.
*/
/*
 *  kUTTagClassFilenameExtension
 */
extern const CFStringRef kUTTagClassFilenameExtension                API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTagClassMIMEType
 */
extern const CFStringRef kUTTagClassMIMEType                         API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );
/*
 *  kUTTagClassNSPboardType
 */
extern const CFStringRef kUTTagClassNSPboardType                     API_AVAILABLE( macos(10.3) ) API_UNAVAILABLE( ios, tvos, watchos );
/*
 *  kUTTagClassOSType
 */
extern const CFStringRef kUTTagClassOSType                           API_AVAILABLE( macos(10.3) ) API_UNAVAILABLE( ios, tvos, watchos );

/*
 *  UTTypeCreatePreferredIdentifierForTag()
 *  
 *  Discussion:
 *    Creates a uniform type identifier for the type indicated by the
 *    specified tag. This is the primary function to use for going from
 *    tag (extension/MIMEType/OSType) to uniform type identifier.
 *    Optionally, the returned type identifiers must conform to the
 *    identified "conforming-to" type argument. This is a hint to the
 *    implementation to constrain the search to a particular tree of
 *    types. For example, the client may want to know the type
 *    indicated by a particular extension tag. If the client knows that
 *    the extension is associated with a directory (rather than a
 *    file), the client may specify "public.directory" for the
 *    conforming-to argument. This will allow the implementation to
 *    ignore all types associated with byte data formats (public.data
 *    base type). If more than one type is indicated, preference is
 *    given to a public type over a non-public type on the theory that
 *    instances of public types are more common, and therefore more
 *    likely to be correct. When there a choice must be made between
 *    multiple public types or multiple non-public types, the selection
 *    rules are undefined. Clients needing finer control should use
 *    UTTypeCreateAllIdentifiersForTag. If no declared type is
 *    indicated, a dynamic type identifier is generated which satisfies
 *    the parameters.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inTagClass:
 *      the class identifier of the tag argument
 *    
 *    inTag:
 *      the tag string
 *    
 *    inConformingToUTI:
 *      the identifier of a type to which the result must conform
 *  
 *  Result:
 *    a new CFStringRef containing the type identifier, or NULL if
 *    inTagClass is not a known tag class
 */
extern __nullable CFStringRef
UTTypeCreatePreferredIdentifierForTag(
  CFStringRef              inTagClass,
  CFStringRef              inTag,
  __nullable CFStringRef   inConformingToUTI)                        API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCreateAllIdentifiersForTag()
 *  
 *  Discussion:
 *    Creates an array of all uniform type identifiers indicated by the
 *    specified tag. An overloaded tag (e.g., an extension used by
 *    several applications for different file formats) may indicate
 *    multiple types. If no declared type identifiers have the
 *    specified tag, then a single dynamic type identifier will be
 *    created for the tag. Optionally, the returned type identifiers
 *    must conform to the identified "conforming-to" type argument.
 *    This is a hint to the implementation to constrain the search to a
 *    particular tree of types. For example, the client may want to
 *    know the type indicated by a particular extension tag. If the
 *    client knows that the extension is associated with a directory
 *    (rather than a file), the client may specify "public.directory"
 *    for the conforming-to argument. This will allow the
 *    implementation to ignore all types associated with byte data
 *    formats (public.data base type).
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inTagClass:
 *      the class identifier of the tag argument
 *    
 *    inTag:
 *      the tag string
 *    
 *    inConformingToUTI:
 *      the identifier of a type to which the results must conform
 *  
 *  Result:
 *    An array of uniform type identifiers, or NULL if inTagClass is
 *    not a known tag class
 */
extern __nullable CFArrayRef
UTTypeCreateAllIdentifiersForTag(
  CFStringRef              inTagClass,
  CFStringRef              inTag,
  __nullable CFStringRef   inConformingToUTI)                        API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCopyPreferredTagWithClass()
 *  
 *  Discussion:
 *    Returns the identified type's preferred tag with the specified
 *    tag class as a CFString. This is the primary function to use for
 *    going from uniform type identifier to tag. If the type
 *    declaration included more than one tag with the specified class,
 *    the first tag in the declared tag array is the preferred tag.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *    
 *    inTagClass:
 *      the class of tags to return
 *  
 *  Result:
 *    the tag string, or NULL if there is no tag of the specified class.
 */
extern __nullable CFStringRef
UTTypeCopyPreferredTagWithClass(
  CFStringRef   inUTI,
  CFStringRef   inTagClass)                                          API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCopyAllTagsWithClass()
 *  
 *  Discussion:
 *    Returns each of the identified type's tags with the specified
 *    tag class as a CFArray of CFStrings.
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *    
 *    inTagClass:
 *      the class of tags to return
 *  
 *  Result:
 *    an array of tag strings, or NULL if there is no tag of the specified class.
 */
extern __nullable CFArrayRef
UTTypeCopyAllTagsWithClass(
  CFStringRef   inUTI,
  CFStringRef   inTagClass)                                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeEqual()
 *  
 *  Discussion:
 *    Compares two identified types for equality. Types are equal if
 *    their identifier strings are equal using a case-insensitive
 *    comparison.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI1:
 *      a uniform type identifier
 *    
 *    inUTI2:
 *      another uniform type identifier
 */
extern Boolean 
UTTypeEqual(
  CFStringRef   inUTI1,
  CFStringRef   inUTI2)                                              API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeConformsTo()
 *  
 *  Discussion:
 *    Tests for a conformance relationship between the two identified
 *    types. Returns true if the types are equal, or if the first type
 *    conforms, directly or indirectly, to the second type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier to test
 *    
 *    inConformsToUTI:
 *      the uniform type identifier against which to test conformance.
 */
extern Boolean 
UTTypeConformsTo(
  CFStringRef   inUTI,
  CFStringRef   inConformsToUTI)                                     API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCopyDescription()
 *  
 *  Discussion:
 *    Returns the localized, user-readable type description string
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a localized string, or NULL of no type description is available
 */
extern __nullable CFStringRef
UTTypeCopyDescription(CFStringRef inUTI)                             API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeIsDeclared()
 *  
 *  Discussion:
 *    Returns whether or not the specified UTI has a declaration
 *    registered on the current system. Dynamic UTIs are never
 *    registered.
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    Whether or not the UTI is registered.
 */
extern Boolean
UTTypeIsDeclared(CFStringRef inUTI)                                  API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeIsDynamic()
 *  
 *  Discussion:
 *    Returns whether or not the specified UTI is a dynamic UTI.
 *
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    Whether or not the UTI is dynamic.
 */
extern Boolean
UTTypeIsDynamic(CFStringRef inUTI)                                   API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCopyDeclaration()
 *  
 *  Discussion:
 *    Returns the identified type's declaration dictionary, as it
 *    appears in the declaring bundle's info property list. This the
 *    access path to other type properties for which direct access is
 *    rarely needed.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a tag declaration dictionary, or NULL if the type is not declared
 */
extern __nullable CFDictionaryRef
UTTypeCopyDeclaration(CFStringRef inUTI)                             API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTTypeCopyDeclaringBundleURL()
 *  
 *  Discussion:
 *    Returns the URL of the bundle containing the type declaration of
 *    the identified type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a URL, or NULL if the bundle cannot be located.
 */
extern __nullable CFURLRef
UTTypeCopyDeclaringBundleURL(CFStringRef inUTI)                      API_AVAILABLE( ios(3.0), macos(10.3), tvos(9.0), watchos(1.0) );



/*
 *  UTCreateStringForOSType()
 *  
 *  Discussion:
 *    A helper function to canonically encode an OSType as a CFString
 *    suitable for use as a tag argument.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inOSType:
 *      the OSType value to encode
 *  
 *  Result:
 *    a new CFString representing the OSType
 */
extern CFStringRef
UTCreateStringForOSType(OSType inOSType)                             API_AVAILABLE( macos(10.3) ) API_UNAVAILABLE( ios, tvos, watchos );



/*
 *  UTGetOSTypeFromString()
 *  
 *  Discussion:
 *    A helper function to canonically decode a string-encoded OSType
 *    back to the original OSType value.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inString:
 *      the string to decode
 *  
 *  Result:
 *    the OSType value encoded in the string, or 0 if the string is not
 *    a valid encoding of an OSType
 */
extern OSType 
UTGetOSTypeFromString(CFStringRef inString)                          API_AVAILABLE( macos(10.3) ) API_UNAVAILABLE( ios, tvos, watchos );



CF_ASSUME_NONNULL_END



#ifdef __cplusplus
}
#endif

#endif /* __UTTYPE__ */

// ==========  CoreServices.framework/Headers/CoreServices.h
/*	
	CoreServices.h
	Copyright (c) 2009, Apple Inc. All rights reserved.
*/

#ifndef __CORESERVICES__
#define __CORESERVICES__

#include <CoreServices/UTCoreTypes.h>
#include <CoreServices/UTType.h>

#endif /* __CORESERVICES__ */
// ==========  CoreServices.framework/Headers/UTCoreTypes.h
/*
     File:       UTCoreTypes.h
 
     Contains:   String constants for core uniform type identifiers
 
     Copyright:  (c) 2004-2012 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __UTCORETYPES__
#define __UTCORETYPES__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif


#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif



#ifdef __cplusplus
extern "C" {
#endif



CF_ASSUME_NONNULL_BEGIN



#pragma mark - Abstract base types
/*
 *  kUTTypeItem
 *
 *    generic base type for most things
 *    (files, directories)
 *
 *    UTI: public.item
 *
 *
 *  kUTTypeContent
 *
 *    base type for anything containing user-viewable document content
 *    (documents, pasteboard data, and document packages.) Types describing
 *    files or packages must also conform to kUTTypeData or kUTTypePackage
 *    in order for the system to bind documents to them.
 *
 *    UTI: public.content
 *
 *
 *  kUTTypeCompositeContent
 *
 *    base type for content formats supporting mixed embedded content
 *    (i.e., compound documents)
 *
 *    UTI: public.composite-content
 *    conforms to: public.content
 *
 *
 *  kUTTypeMessage
 *
 *    base type for messages (email, IM, etc.)
 *
 *    UTI: public.message
 *
 *
 *  kUTTypeContact
 *
 *    contact information, e.g. for a person, group, organization
 *
 *    UTI: public.contact
 *
 *
 *  kUTTypeArchive
 *
 *    an archive of files and directories
 *
 *    UTI: public.archive
 *
 *
 *  kUTTypeDiskImage
 *
 *    a data item mountable as a volume
 *
 *    UTI: public.disk-image
 *
 */
extern const CFStringRef kUTTypeItem                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeContent                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCompositeContent                     API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMessage                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeContact                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeArchive                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeDiskImage                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );

#pragma mark - Concrete base types
/*
 *  kUTTypeData
 *
 *    base type for any sort of simple byte stream,
 *    including files and in-memory data
 *
 *    UTI: public.data
 *    conforms to: public.item
 *
 *
 *  kUTTypeDirectory
 *
 *    file system directory 
 *    (includes packages AND folders)
 *
 *    UTI: public.directory
 *    conforms to: public.item
 *
 *
 *  kUTTypeResolvable
 *
 *    symlink and alias file types conform to this UTI
 *
 *    UTI: com.apple.resolvable
 *
 *
 *  kUTTypeSymLink
 *
 *    a symbolic link
 *
 *    UTI: public.symlink
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeExecutable
 *
 *    an executable item
 *    UTI: public.executable
 *    conforms to: public.item
 *
 *
 *  kUTTypeMountPoint
 *
 *    a volume mount point (resolvable, resolves to the root dir of a volume)
 *
 *    UTI: com.apple.mount-point
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeAliasFile
 *
 *    a fully-formed alias file
 *
 *    UTI: com.apple.alias-file
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeAliasRecord
 *
 *    raw alias data
 *
 *    UTI: com.apple.alias-record
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeURLBookmarkData
 *
 *    URL bookmark
 *
 *    UTI: com.apple.bookmark
 *    conforms to: public.data, com.apple.resolvable
 *
 */
extern const CFStringRef kUTTypeData                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeDirectory                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeResolvable                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeSymLink                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeExecutable                           API_AVAILABLE( ios(8.0), macos(10.5), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMountPoint                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAliasFile                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAliasRecord                          API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeURLBookmarkData                      API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - URL types
/*
 *  kUTTypeURL
 *
 *    The bytes of a URL
 *    (OSType 'url ')
 *
 *    UTI: public.url
 *    conforms to: public.data
 *
 *
 *  kUTTypeFileURL
 *
 *    The text of a "file:" URL 
 *    (OSType 'furl')
 *
 *    UTI: public.file-url
 *    conforms to: public.url
 *
 */
extern const CFStringRef kUTTypeURL                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeFileURL                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );

#pragma mark - Text types
/*
 *  kUTTypeText
 *
 *    base type for all text-encoded data, 
 *    including text with markup (HTML, RTF, etc.)
 *
 *    UTI: public.text
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypePlainText
 *
 *    text with no markup, unspecified encoding
 *
 *    UTI: public.plain-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeUTF8PlainText
 *
 *    plain text, UTF-8 encoding
 *    (OSType 'utf8', NSPasteboardType "NSStringPBoardType")
 *
 *    UTI: public.utf8-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeUTF16ExternalPlainText
 *
 *    plain text, UTF-16 encoding, with BOM, or if BOM 
 *    is not present, has "external representation" 
 *    byte order (big-endian).
 *    (OSType 'ut16')
 *
 *    UTI: public.utf16-external-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeUTF16PlainText
 *
 *    plain text, UTF-16 encoding, native byte order, optional BOM
 *    (OSType 'utxt')
 *
 *    UTI: public.utf16-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeDelimitedText
 *
 *    text containing delimited values
 *
 *    UTI: public.delimited-values-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeCommaSeparatedText
 *
 *    text containing comma-separated values (.csv)
 *
 *    UTI: public.comma-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeTabSeparatedText
 *
 *    text containing tab-separated values
 *
 *    UTI: public.tab-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeUTF8TabSeparatedText
 *
 *    UTF-8 encoded text containing tab-separated values
 *
 *    UTI: public.utf8-tab-separated-values-text
 *    conforms to: public.tab-separated-values-text, public.utf8-plain-text
 *
 *
 *  kUTTypeRTF
 *
 *    Rich Text Format
 *
 *    UTI: public.rtf
 *    conforms to: public.text
 *
 */
extern const CFStringRef kUTTypeText                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePlainText                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeUTF8PlainText                        API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeUTF16ExternalPlainText               API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeUTF16PlainText                       API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeDelimitedText                        API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCommaSeparatedText                   API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeTabSeparatedText                     API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeUTF8TabSeparatedText                 API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeRTF                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );

#pragma mark - Markup languages
/*
 *  kUTTypeHTML
 *
 *    HTML, any version
 *
 *    UTI: public.html
 *    conforms to: public.text
 *
 *
 *  kUTTypeXML
 *
 *    generic XML
 *
 *    UTI: public.xml
 *    conforms to: public.text
 *
 */
extern const CFStringRef kUTTypeHTML                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeXML                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );

#pragma mark - Programming languages
/*
 *  kUTTypeSourceCode
 *
 *    abstract type for source code (any language)
 *
 *    UTI: public.source-code
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeAssemblyLanguageSource
 *
 *    assembly language source (.s)
 *
 *    UTI: public.assembly-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCSource
 *
 *    C source code (.c)
 *
 *    UTI: public.c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCSource
 *
 *    Objective-C source code (.m)
 *
 *    UTI: public.objective-c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeSwiftSource
 *
 *    Swift source code (.swift)
 *
 *    UTI: public.swift-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusSource
 *
 *    C++ source code (.cp, etc.)
 *
 *    UTI: public.c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCPlusPlusSource
 *
 *    Objective-C++ source code
 *
 *    UTI: public.objective-c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCHeader
 *
 *    C header
 *
 *    UTI: public.c-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusHeader
 *
 *    C++ header
 *
 *    UTI: public.c-plus-plus-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeJavaSource
 *
 *    Java source code
 *
 *    UTI: com.sun.java-source
 *    conforms to: public.source-code
 *
 */
extern const CFStringRef kUTTypeSourceCode                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAssemblyLanguageSource               API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCSource                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeObjectiveCSource                     API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeSwiftSource                          API_AVAILABLE( ios(9.0), macos(10.11), tvos(9.0), watchos(2.0) );
extern const CFStringRef kUTTypeCPlusPlusSource                      API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeObjectiveCPlusPlusSource             API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCHeader                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCPlusPlusHeader                      API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJavaSource                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );

#pragma mark - Scripting languages
/*
 *  kUTTypeScript
 *
 *    scripting language source
 *
 *    UTI: public.script
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeAppleScript
 *
 *    AppleScript text format (.applescript)
 *
 *    UTI: com.apple.applescript.text
 *    conforms to: public.script
 *
 *
 *  kUTTypeOSAScript
 *
 *    Open Scripting Architecture script binary format (.scpt)
 *
 *    UTI: com.apple.applescript.script
 *    conforms to: public.data, public.script
 *
 *
 *  kUTTypeOSAScriptBundle
 *
 *    Open Scripting Architecture script bundle format (.scptd)
 *
 *    UTI: com.apple.applescript.script-bundle
 *    conforms to: com.apple.bundle, com.apple.package, public.script
 *
 *
 *  kUTTypeJavaScript
 *
 *    JavaScript source code
 *
 *    UTI: com.netscape.javascript-source
 *    conforms to: public.source-code, public.executable
 *
 *
 *  kUTTypeShellScript
 *
 *    base type for shell scripts
 *
 *    UTI: public.shell-script
 *    conforms to: public.script
 *
 *
 *  kUTTypePerlScript
 *
 *    Perl script
 *
 *    UTI: public.perl-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePythonScript
 *
 *    Python script
 *
 *    UTI: public.python-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypeRubyScript
 *
 *    Ruby script
 *
 *    UTI: public.ruby-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePHPScript
 *
 *    PHP script
 *
 *    UTI: public.php-script
 *    conforms to: public.shell-script
 *
 */
extern const CFStringRef kUTTypeScript                               API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAppleScript                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeOSAScript                            API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeOSAScriptBundle                      API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJavaScript                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeShellScript                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePerlScript                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePythonScript                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeRubyScript                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePHPScript                            API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - Serialized data types
/*
 *  kUTTypeJSON
 *
 *    JavaScript object notation (JSON) data
 *    NOTE: JSON almost but doesn't quite conform to
 *    com.netscape.javascript-source
 *
 *    UTI: public.json
 *    conforms to: public.text
 *
 *
 *  kUTTypePropertyList
 *
 *    base type for property lists
 *
 *    UTI: com.apple.property-list
 *    conforms to: public.data
 *
 *
 *  kUTTypeXMLPropertyList
 *
 *    XML property list
 *
 *    UTI: com.apple.xml-property-list
 *    conforms to: public.xml, com.apple.property-list
 *
 *
 *  kUTTypeBinaryPropertyList
 *
 *    XML property list
 *
 *    UTI: com.apple.binary-property-list
 *    conforms to: com.apple.property-list
 *
 */
extern const CFStringRef kUTTypeJSON                                 API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePropertyList                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeXMLPropertyList                      API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeBinaryPropertyList                   API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - Composite content types
/*
 *  kUTTypePDF
 *
 *    Adobe PDF
 *
 *    UTI: com.adobe.pdf
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeRTFD
 *
 *    Rich Text Format Directory 
 *    (RTF with content embedding, on-disk format)
 *
 *    UTI: com.apple.rtfd
 *    conforms to: com.apple.package, public.composite-content
 *
 *
 *  kUTTypeFlatRTFD
 *
 *    Flattened RTFD (pasteboard format)
 *
 *    UTI: com.apple.flat-rtfd
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeTXNTextAndMultimediaData
 *
 *    MLTE (Textension) format for mixed text & multimedia data
 *    (OSType 'txtn')
 *
 *    UTI: com.apple.txn.text-multimedia-data
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeWebArchive
 *
 *    The WebKit webarchive format
 *
 *    UTI: com.apple.webarchive
 *    conforms to: public.data, public.composite-content
 */
extern const CFStringRef kUTTypePDF                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeRTFD                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeFlatRTFD                             API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeTXNTextAndMultimediaData             API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeWebArchive                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );


#pragma mark - Image content types
/*
 *  kUTTypeImage
 *
 *    abstract image data
 *
 *    UTI: public.image
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeJPEG
 *
 *    JPEG image
 *
 *    UTI: public.jpeg
 *    conforms to: public.image
 *
 *
 *  kUTTypeJPEG2000
 *
 *    JPEG-2000 image
 *
 *    UTI: public.jpeg-2000
 *    conforms to: public.image
 *
 *
 *  kUTTypeTIFF
 *
 *    TIFF image
 *
 *    UTI: public.tiff
 *    conforms to: public.image
 *
 *
 *  kUTTypePICT
 *
 *    Quickdraw PICT format
 *
 *    UTI: com.apple.pict
 *    conforms to: public.image
 *
 *
 *  kUTTypeGIF
 *
 *    GIF image
 *
 *    UTI: com.compuserve.gif
 *    conforms to: public.image
 *
 *
 *  kUTTypePNG
 *
 *    PNG image
 *
 *    UTI: public.png
 *    conforms to: public.image
 *
 *
 *  kUTTypeQuickTimeImage
 *
 *    QuickTime image format (OSType 'qtif')
 *
 *    UTI: com.apple.quicktime-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeAppleICNS
 *
 *    Apple icon data
 *
 *    UTI: com.apple.icns
 *    conforms to: public.image
 *
 *
 *  kUTTypeBMP
 *
 *    Windows bitmap
 *
 *    UTI: com.microsoft.bmp
 *    conforms to: public.image
 *
 *
 *  kUTTypeICO
 *
 *    Windows icon data
 *
 *    UTI: com.microsoft.ico
 *    conforms to: public.image
 *
 *
 *  kUTTypeRawImage
 *
 *    base type for raw image data (.raw)
 *
 *    UTI: public.camera-raw-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeScalableVectorGraphics
 *
 *    SVG image
 *
 *    UTI: public.svg-image
 *    conforms to: public.image
 *
 *  kUTTypeLivePhoto
 *
 *    Live Photo
 *
 *    UTI: com.apple.live-photo
 *
 *
 */
extern const CFStringRef kUTTypeImage                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJPEG                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJPEG2000                             API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeTIFF                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePICT                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeGIF                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePNG                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeQuickTimeImage                       API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAppleICNS                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeBMP                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeICO                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeRawImage                             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeScalableVectorGraphics               API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeLivePhoto                            API_AVAILABLE( ios(9.1), macos(10.12), tvos(9.0), watchos(2.1) );

#pragma mark - Audiovisual content types
/*
 *  kUTTypeAudiovisualContent
 *
 *    audio and/or video content
 *
 *    UTI: public.audiovisual-content
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeMovie
 *
 *    A media format which may contain both video and audio
 *    Corresponds to what users would label a "movie"
 *
 *    UTI: public.movie
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeVideo
 *
 *    pure video (no audio)
 *
 *    UTI: public.video
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudio
 *
 *    pure audio (no video)
 *
 *    UTI: public.audio
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeQuickTimeMovie
 *
 *    QuickTime movie
 *
 *    UTI: com.apple.quicktime-movie
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG
 *
 *    MPEG-1 or MPEG-2 movie
 *
 *    UTI: public.mpeg
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG2Video
 *
 *    MPEG-2 video
 *
 *    UTI: public.mpeg-2-video
 *    conforms to: public.video
 *
 *
 *  kUTTypeMPEG2TransportStream
 *
 *    MPEG-2 Transport Stream movie format
 *
 *    UTI: public.mpeg-2-transport-stream
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMP3
 *
 *    MP3 audio
 *
 *    UTI: public.mp3
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMPEG4
 *
 *    MPEG-4 movie
 *
 *    UTI: public.mpeg-4
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG4Audio
 *
 *    MPEG-4 audio layer
 *
 *    UTI: public.mpeg-4-audio
 *    conforms to: public.mpeg-4, public.audio
 *
 *
 *  kUTTypeAppleProtectedMPEG4Audio
 *
 *    Apple protected MPEG4 format
 *    (.m4p, iTunes music store format)
 *
 *    UTI: com.apple.protected-mpeg-4-audio
 *    conforms to: public.audio
 *
 *
 *  kUTTypeAppleProtectedMPEG4Video
 *
 *    Apple protected MPEG-4 movie
 *
 *    UTI: com.apple.protected-mpeg-4-video
 *    conforms to: com.apple.m4v-video
 *
 *
 *  kUTTypeAVIMovie
 *
 *    Audio Video Interleaved (AVI) movie format
 *
 *    UTI: public.avi
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudioInterchangeFileFormat
 *
 *    AIFF audio format
 *
 *    UTI: public.aiff-audio
 *    conforms to: public.aifc-audio
 *
 *
 *  kUTTypeWaveformAudio
 *
 *    Waveform audio format (.wav)
 *
 *    UTI: com.microsoft.waveform-audio
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMIDIAudio
 *
 *    MIDI audio format
 *
 *    UTI: public.midi-audio
 *    conforms to: public.audio
 *
 *
 */
extern const CFStringRef kUTTypeAudiovisualContent                   API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMovie                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeVideo                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAudio                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeQuickTimeMovie                       API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMPEG                                 API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMPEG2Video                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMPEG2TransportStream                 API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMP3                                  API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMPEG4                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMPEG4Audio                           API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAppleProtectedMPEG4Audio             API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAppleProtectedMPEG4Video             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAVIMovie                             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeAudioInterchangeFileFormat           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeWaveformAudio                        API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeMIDIAudio                            API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

/*
 *  kUTTypePlaylist
 *
 *    base type for playlists
 *
 *    UTI: public.playlist
 *
 *
 *  kUTTypeM3UPlaylist
 *
 *    M3U or M3U8 playlist
 *
 *    UTI: public.m3u-playlist
 *    conforms to: public.text, public.playlist
 *
 */
extern const CFStringRef kUTTypePlaylist                             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeM3UPlaylist                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - Directory types
/*
 *  kUTTypeFolder
 *
 *    a user-browsable directory (i.e., not a package)
 *
 *    UTI: public.folder
 *    conforms to: public.directory
 *
 *
 *  kUTTypeVolume
 *
 *    the root folder of a volume/mount point
 *
 *    UTI: public.volume
 *    conforms to: public.folder
 *
 *
 *  kUTTypePackage
 *
 *    a packaged directory
 *
 *    UTI: com.apple.package
 *    conforms to: public.directory
 *
 *
 *  kUTTypeBundle
 *
 *    a directory conforming to one of the CFBundle layouts
 *
 *    UTI: com.apple.bundle
 *    conforms to: public.directory
 *
 *
 *  kUTTypePluginBundle
 *
 *    base type for bundle-based plugins
 *
 *    UTI: com.apple.plugin
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeSpotlightImporter
 *
 *    a Spotlight metadata importer
 *
 *    UTI: com.apple.metadata-importer
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeQuickLookGenerator
 *
 *    a QuickLook preview generator
 *
 *    UTI: com.apple.quicklook-generator
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeXPCService
 *
 *    an XPC service
 *
 *    UTI: com.apple.xpc-service
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeFramework
 *
 *    a Mac OS X framework
 *
 *    UTI: com.apple.framework
 *    conforms to: com.apple.bundle
 *
 */
extern const CFStringRef kUTTypeFolder                               API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeVolume                               API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePackage                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeBundle                               API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePluginBundle                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeSpotlightImporter                    API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeQuickLookGenerator                   API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeXPCService                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeFramework                            API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );


#pragma mark - Application and executable types
/*
 *  kUTTypeApplication
 *
 *    base type for OS X applications, launchable items
 *
 *    UTI: com.apple.application
 *    conforms to: public.executable
 *
 *
 *  kUTTypeApplicationBundle
 *
 *    a bundled application
 *
 *    UTI: com.apple.application-bundle
 *    conforms to: com.apple.application, com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeApplicationFile
 *
 *    a single-file Carbon/Classic application 
 *
 *    UTI: com.apple.application-file
 *    conforms to: com.apple.application, public.data
 *
 *
 *  kUTTypeUnixExecutable
 *
 *    a UNIX executable (flat file)
 *
 *    UTI: public.unix-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeWindowsExecutable
 *
 *    a Windows executable (.exe files)
 *
 *    UTI: com.microsoft.windows-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaClass
 *
 *    a Java class
 *
 *    UTI: com.sun.java-class
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaArchive
 *
 *    a Java archive (.jar)
 *
 *    UTI: com.sun.java-archive
 *    conforms to: public.zip-archive, public.executable
 *
 *
 *  kUTTypeSystemPreferencesPane
 *
 *    a System Preferences pane
 *
 *    UTI: com.apple.systempreference.prefpane
 *    conforms to: com.apple.package, com.apple.bundle
 *
 */
// Abstract executable types
extern const CFStringRef kUTTypeApplication                          API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeApplicationBundle                    API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeApplicationFile                      API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeUnixExecutable                       API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

// Other platform binaries
extern const CFStringRef kUTTypeWindowsExecutable                    API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJavaClass                            API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeJavaArchive                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

// Misc. binaries
extern const CFStringRef kUTTypeSystemPreferencesPane                API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - Archival and compression types
/*
 *  kUTTypeGNUZipArchive
 *
 *    a GNU zip archive (gzip)
 *
 *    UTI: org.gnu.gnu-zip-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeBzip2Archive
 *
 *    a bzip2 archive (.bz2)
 *
 *    UTI: public.bzip2-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeZipArchive
 *
 *    a zip archive
 *
 *    UTI: public.zip-archive
 *    conforms to: com.pkware.zip-archive
 *
 */
extern const CFStringRef kUTTypeGNUZipArchive                        API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeBzip2Archive                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeZipArchive                           API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );


#pragma mark - Document types
/*
 *  kUTTypeSpreadsheet
 *
 *    base spreadsheet document type
 *
 *    UTI: public.spreadsheet
 *    conforms to: public.content
 *
 *
 *  kUTTypePresentation
 *
 *    base presentation document type
 *
 *    UTI: public.presentation
 *    conforms to: public.composite-content
 *
 *
 *  kUTTypeDatabase
 *
 *    a database store
 *
 *    UTI: public.database
 *
 */
extern const CFStringRef kUTTypeSpreadsheet                          API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePresentation                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeDatabase                             API_AVAILABLE( ios(8.0), macos(10.4), tvos(9.0), watchos(1.0) );


#pragma mark - Messages, contacts, and calendar types
/*
 *  kUTTypeVCard
 *
 *    VCard format
 *
 *    UTI: public.vcard
 *    conforms to: public.text, public.contact
 *
 *
 *  kUTTypeToDoItem
 *
 *    to-do item
 *
 *    UTI: public.to-do-item
 *
 *
 *  kUTTypeCalendarEvent
 *
 *    calendar event
 *
 *    UTI: public.calendar-event
 *
 *
 *  kUTTypeEmailMessage
 *
 *    e-mail message
 *
 *    UTI: public.email-message
 *    conforms to: public.message
 *
 */
extern const CFStringRef kUTTypeVCard                                API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeToDoItem                             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeCalendarEvent                        API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeEmailMessage                         API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );

#pragma mark - Internet locations
/*
 *  kUTTypeInternetLocation
 *
 *    base type for Apple Internet locations
 *
 *    UTI: com.apple.internet-location
 *    conforms to: public.data
 *
 */
extern const CFStringRef kUTTypeInternetLocation                     API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );


#pragma mark - Miscellaneous types
/*
 *  kUTTypeInkText
 *
 *    Opaque InkText data
 *
 *    UTI: com.apple.ink.inktext
 *    conforms to: public.data
 *
 *
 *  kUTTypeFont
 *
 *    base type for fonts
 *
 *    UTI: public.font
 *
 *
 *  kUTTypeBookmark
 *
 *    bookmark
 *
 *    UTI: public.bookmark
 *
 *
 *  kUTType3DContent
 *
 *    base type for 3D content
 *
 *    UTI: public.3d-content
 *    conforms to: public.content
 *
 *
 *  kUTTypePKCS12
 *
 *    PKCS#12 format
 *
 *    UTI: com.rsa.pkcs-12
 *    conforms to: public.data
 *
 *
 *  kUTTypeX509Certificate
 *
 *    X.509 certificate format
 *
 *    UTI: public.x509-certificate
 *    conforms to: public.data
 *
 *
 *  kUTTypeElectronicPublication
 *
 *    ePub format
 *
 *    UTI: org.idpf.epub-container
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeLog
 *
 *    console log
 *
 *    UTI: public.log
 *
 */
extern const CFStringRef kUTTypeInkText                              API_AVAILABLE( ios(3.0), macos(10.4), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeFont                                 API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeBookmark                             API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTType3DContent                            API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypePKCS12                               API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeX509Certificate                      API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeElectronicPublication                API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );
extern const CFStringRef kUTTypeLog                                  API_AVAILABLE( ios(8.0), macos(10.10), tvos(9.0), watchos(1.0) );



CF_ASSUME_NONNULL_END



#ifdef __cplusplus
}
#endif



#endif /* __UTCORETYPES__ */
