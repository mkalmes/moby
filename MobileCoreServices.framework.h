// ==========  MobileCoreServices.framework/Headers/MobileCoreServices.h
/*
	File:      MobileCoreServices/MobileCoreServices.h
 
	Contains:  Master include for MobileCoreServices
 
	Copyright: (c) 1999-2018 Apple Inc. All rights reserved. 
 */

#import <CoreServices/CoreServices.h>
// ==========  MobileCoreServices.framework/Headers/UTType.h
/*
 File:       UTType.h
 
 Contains:   Public interfaces for uniform type identifiers
 
 Copyright:  (c) 2003-2012 by Apple Inc. All rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 */

#if TARGET_OS_IPHONE && (TARGET_OS_EMBEDDED || TARGET_OS_SIMULATOR || !TARGET_OS_UIKITFORMAC)
#import <CoreServices/UTType.h>
#else
#import <CoreServices/CoreServices.h>
#endif
// ==========  MobileCoreServices.framework/Headers/UTCoreTypes.h
/*
 File:       UTCoreTypes.h
 
 Contains:   String constants for core uniform type identifiers
 
 Copyright:  (c) 2004-2012 by Apple Inc. All rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 */

#if TARGET_OS_IPHONE && (TARGET_OS_EMBEDDED || TARGET_OS_SIMULATOR || !TARGET_OS_UIKITFORMAC)
#import <CoreServices/UTCoreTypes.h>
#else
#import <CoreServices/CoreServices.h>
#endif

