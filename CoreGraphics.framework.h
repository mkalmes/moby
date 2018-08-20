// ==========  CoreGraphics.framework/Headers/CGGeometry.h
/* CoreGraphics - CGGeometry.h
   Copyright (c) 1998-2011 Apple Inc.
   All rights reserved. */

#ifndef CGGEOMETRY_H_
#define CGGEOMETRY_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Points. */

struct CGPoint {
    CGFloat x;
    CGFloat y;
};
typedef struct CGPoint CGPoint;

/* Sizes. */

struct CGSize {
    CGFloat width;
    CGFloat height;
};
typedef struct CGSize CGSize;

/* Vectors. */

#define CGVECTOR_DEFINED 1

struct CGVector {
    CGFloat dx;
    CGFloat dy;
};
typedef struct CGVector CGVector;

/* Rectangles. */

struct CGRect {
    CGPoint origin;
    CGSize size;
};
typedef struct CGRect CGRect;

/* Rectangle edges. */

typedef CF_ENUM(uint32_t, CGRectEdge) {
    CGRectMinXEdge, CGRectMinYEdge, CGRectMaxXEdge, CGRectMaxYEdge
};

/* The "zero" point -- equivalent to CGPointMake(0, 0). */ 

CG_EXTERN const CGPoint CGPointZero
      CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "zero" size -- equivalent to CGSizeMake(0, 0). */ 

CG_EXTERN const CGSize CGSizeZero
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "zero" rectangle -- equivalent to CGRectMake(0, 0, 0, 0). */ 

CG_EXTERN const CGRect CGRectZero
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "empty" rect. This is the rectangle returned when, for example, we
   intersect two disjoint rectangles. Note that the null rect is not the
   same as the zero rect. */

CG_EXTERN const CGRect CGRectNull
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The infinite rectangle. */

CG_EXTERN const CGRect CGRectInfinite
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Make a point from `(x, y)'. */

CG_INLINE CGPoint CGPointMake(CGFloat x, CGFloat y);

/* Make a size from `(width, height)'. */

CG_INLINE CGSize CGSizeMake(CGFloat width, CGFloat height);

/* Make a vector from `(dx, dy)'. */

CG_INLINE CGVector CGVectorMake(CGFloat dx, CGFloat dy);

/* Make a rect from `(x, y; width, height)'. */

CG_INLINE CGRect CGRectMake(CGFloat x, CGFloat y, CGFloat width,
  CGFloat height);

/* Return the leftmost x-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMinX(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the midpoint x-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMidX(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the rightmost x-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMaxX(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the bottommost y-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMinY(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the midpoint y-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMidY(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the topmost y-value of `rect'. */

CG_EXTERN CGFloat CGRectGetMaxY(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the width of `rect'. */

CG_EXTERN CGFloat CGRectGetWidth(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the height of `rect'. */

CG_EXTERN CGFloat CGRectGetHeight(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `point1' and `point2' are the same, false otherwise. */

CG_EXTERN bool CGPointEqualToPoint(CGPoint point1, CGPoint point2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `size1' and `size2' are the same, false otherwise. */

CG_EXTERN bool CGSizeEqualToSize(CGSize size1, CGSize size2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect1' and `rect2' are the same, false otherwise. */

CG_EXTERN bool CGRectEqualToRect(CGRect rect1, CGRect rect2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Standardize `rect' -- i.e., convert it to an equivalent rect which has
   positive width and height. */

CG_EXTERN CGRect CGRectStandardize(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is empty (that is, if it has zero width or height),
   false otherwise. A null rect is defined to be empty. */

CG_EXTERN bool CGRectIsEmpty(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is the null rectangle, false otherwise. */

CG_EXTERN bool CGRectIsNull(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is the infinite rectangle, false otherwise. */

CG_EXTERN bool CGRectIsInfinite(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Inset `rect' by `(dx, dy)' -- i.e., offset its origin by `(dx, dy)', and
   decrease its size by `(2*dx, 2*dy)'. */

CG_EXTERN CGRect CGRectInset(CGRect rect, CGFloat dx, CGFloat dy)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Expand `rect' to the smallest rect containing it with integral origin and
   size. */

CG_EXTERN CGRect CGRectIntegral(CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the union of `r1' and `r2'. */

CG_EXTERN CGRect CGRectUnion(CGRect r1, CGRect r2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the intersection of `r1' and `r2'. This may return a null rect. */

CG_EXTERN CGRect CGRectIntersection(CGRect r1, CGRect r2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Offset `rect' by `(dx, dy)'. */

CG_EXTERN CGRect CGRectOffset(CGRect rect, CGFloat dx, CGFloat dy)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Make two new rectangles, `slice' and `remainder', by dividing `rect' with
   a line that's parallel to one of its sides, specified by `edge' -- either
   `CGRectMinXEdge', `CGRectMinYEdge', `CGRectMaxXEdge', or
   `CGRectMaxYEdge'. The size of `slice' is determined by `amount', which
   measures the distance from the specified edge. */

CG_EXTERN void CGRectDivide(CGRect rect, CGRect *  slice,
    CGRect *  remainder, CGFloat amount, CGRectEdge edge)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `point' is contained in `rect', false otherwise. */

CG_EXTERN bool CGRectContainsPoint(CGRect rect, CGPoint point)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect2' is contained in `rect1', false otherwise. `rect2'
   is contained in `rect1' if the union of `rect1' and `rect2' is equal to
   `rect1'. */

CG_EXTERN bool CGRectContainsRect(CGRect rect1, CGRect rect2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect1' intersects `rect2', false otherwise. `rect1'
   intersects `rect2' if the intersection of `rect1' and `rect2' is not the
   null rect. */

CG_EXTERN bool CGRectIntersectsRect(CGRect rect1, CGRect rect2)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/*** Persistent representations. ***/

/* Return a dictionary representation of `point'. */

CG_EXTERN CFDictionaryRef  CGPointCreateDictionaryRepresentation(
    CGPoint point)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGPoint from the contents of `dict' (presumably returned earlier
   from `CGPointCreateDictionaryRepresentation') and store the value in
   `point'. Returns true on success; false otherwise. */

CG_EXTERN bool CGPointMakeWithDictionaryRepresentation(
    CFDictionaryRef __nullable dict, CGPoint * __nullable point)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a dictionary representation of `size'. */

CG_EXTERN CFDictionaryRef  CGSizeCreateDictionaryRepresentation(CGSize size)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGSize from the contents of `dict' (presumably returned earlier
   from `CGSizeCreateDictionaryRepresentation') and store the value in
   `size'. Returns true on success; false otherwise. */

CG_EXTERN bool CGSizeMakeWithDictionaryRepresentation(
    CFDictionaryRef __nullable dict, CGSize * __nullable size)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a dictionary representation of `rect'. */

CG_EXTERN CFDictionaryRef  CGRectCreateDictionaryRepresentation(CGRect)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGRect from the contents of `dict' (presumably returned earlier
   from `CGRectCreateDictionaryRepresentation') and store the value in
   `rect'. Returns true on success; false otherwise. */

CG_EXTERN bool CGRectMakeWithDictionaryRepresentation(
    CFDictionaryRef __nullable dict, CGRect * __nullable rect)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/*** Definitions of inline functions. ***/

CG_INLINE CGPoint
CGPointMake(CGFloat x, CGFloat y)
{
  CGPoint p; p.x = x; p.y = y; return p;
}

CG_INLINE CGSize
CGSizeMake(CGFloat width, CGFloat height)
{
  CGSize size; size.width = width; size.height = height; return size;
}

CG_INLINE CGVector
CGVectorMake(CGFloat dx, CGFloat dy)
{
  CGVector vector; vector.dx = dx; vector.dy = dy; return vector;
}

CG_INLINE CGRect
CGRectMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height)
{
  CGRect rect;
  rect.origin.x = x; rect.origin.y = y;
  rect.size.width = width; rect.size.height = height;
  return rect;
}

CG_INLINE bool
__CGPointEqualToPoint(CGPoint point1, CGPoint point2)
{
  return point1.x == point2.x && point1.y == point2.y;
}
#define CGPointEqualToPoint __CGPointEqualToPoint

CG_INLINE bool
__CGSizeEqualToSize(CGSize size1, CGSize size2)
{
  return size1.width == size2.width && size1.height == size2.height;
}

#define CGSizeEqualToSize __CGSizeEqualToSize

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGGEOMETRY_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFOperatorTable.h
/* CoreGraphics - CGPDFOperatorTable.h
 * Copyright (c) 2004-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFOPERATORTABLE_H_
#define CGPDFOPERATORTABLE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFOperatorTable *CGPDFOperatorTableRef;

#include <CoreGraphics/CGPDFScanner.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

typedef void (*CGPDFOperatorCallback)(CGPDFScannerRef  scanner,
                                      void * __nullable info);

/* Return an empty operator table. */

CG_EXTERN CGPDFOperatorTableRef __nullable CGPDFOperatorTableCreate(void)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Increment the retain count of `table'. */

CG_EXTERN CGPDFOperatorTableRef __nullable CGPDFOperatorTableRetain(
    CGPDFOperatorTableRef __nullable table)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Decrement the retain count of `table'. */

CG_EXTERN void CGPDFOperatorTableRelease(
    CGPDFOperatorTableRef __nullable table)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Set the callback for the operator named `name' to `callback' */

CG_EXTERN void CGPDFOperatorTableSetCallback(
    CGPDFOperatorTableRef __nullable table,
    const char * __nullable name, CGPDFOperatorCallback __nullable callback)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* CGPDFOPERATORTABLE_H_ */
// ==========  CoreGraphics.framework/Headers/CGError.h
/* CoreGraphics - CGError.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGERROR_H_
#define CGERROR_H_

#include <CoreGraphics/CGBase.h>
#include <stdint.h>

#include <CoreFoundation/CFAvailability.h>


/* Types used for errors and error handlers. */

typedef CF_ENUM (int32_t, CGError) {
  kCGErrorSuccess = 0,
  kCGErrorFailure = 1000,
  kCGErrorIllegalArgument = 1001,
  kCGErrorInvalidConnection = 1002,
  kCGErrorInvalidContext = 1003,
  kCGErrorCannotComplete = 1004,
  kCGErrorNotImplemented = 1006,
  kCGErrorRangeCheck = 1007,
  kCGErrorTypeCheck = 1008,
  kCGErrorInvalidOperation = 1010,
  kCGErrorNoneAvailable = 1011,
};

#endif /* CGERROR_H_ */
// ==========  CoreGraphics.framework/Headers/CGFunction.h
/* CoreGraphics - CGFunction.h
   Copyright (c) 1999-2011 Apple Inc.
   All rights reserved. */

#ifndef CGFUNCTION_H_
#define CGFUNCTION_H_

/* A CGFunction is a general floating-point function evaluator which uses a
   user-specified callback to map an arbitrary number of inputs to an
   arbitrary number of outputs. */

typedef struct CGFunction *CGFunctionRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* This callback evaluates a function, using `in' as inputs, and places the
   result in `out'. `info' is the info parameter passed to the CGFunction
   creation functions. */

typedef void (*CGFunctionEvaluateCallback)(void * __nullable info,
  const CGFloat *  in, CGFloat *  out);

/* When a function is deallocated, this callback releases `info', the info
   parameter passed to the CGFunction creation functions. */

typedef void (*CGFunctionReleaseInfoCallback)(void * __nullable info);

/* Callbacks for a CGFunction.
     `version' is the version number of this structure. This structure is
       version 0.
     `evaluate' is the callback used to evaluate the function.
     `releaseInfo', if non-NULL, is the callback used to release the info
       parameter passed to the CGFunction creation functions when the
       function is deallocated. */

struct CGFunctionCallbacks {
    unsigned int version;
    CGFunctionEvaluateCallback __nullable evaluate;
    CGFunctionReleaseInfoCallback __nullable releaseInfo;
};
typedef struct CGFunctionCallbacks CGFunctionCallbacks;

/* Return the CFTypeID for CGFunctionRefs. */

CG_EXTERN CFTypeID CGFunctionGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a CGFunction using `callbacks' to evaluate the function. `info' is
   passed to each of the callback functions. `domainDimension' is the number
   of input values to the function; `rangeDimension' is the number of output
   values from the function.

   `domain' is an array of 2M values, where M is the number of input values.
   For each k from 0 to M-1, domain[2*k] must be less than or equal to
   domain[2*k+1]. The k'th input value (in[k]) will be clipped to lie in
   this interval, so that domain[2*k] <= in[k] <= domain[2*k+1]. If `domain'
   is NULL, then the input values will not be clipped. However, it's
   strongly recommended that `domain' be specified; each domain interval
   should specify reasonable values for the minimum and maximum in that
   dimension.

   `range' is an array of 2N values, where N is the number of output values.
   For each k from 0 to N-1, range[2*k] must be less than or equal to
   range[2*k+1]. The k'th output value (out[k]) will be clipped to lie in
   this interval, so that range[2*k] <= out[k] <= range[2*k+1]. If `range'
   is NULL, then the output values will not be clipped. However, it's
   strongly recommended that `range' be specified; each range interval
   should specify reasonable values for the minimum and maximum in that
   dimension.

   The contents of the callbacks structure is copied, so, for example, a
   pointer to a structure on the stack can be passed to this function. */

CG_EXTERN CGFunctionRef __nullable CGFunctionCreate(void * __nullable info,
    size_t domainDimension, const CGFloat *__nullable domain,
    size_t rangeDimension, const CGFloat * __nullable range,
    const CGFunctionCallbacks * __nullable callbacks)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRetain(function)', except it doesn't crash (as CFRetain
   does) if `function' is NULL. */

CG_EXTERN CGFunctionRef __nullable CGFunctionRetain(
    CGFunctionRef __nullable function)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRelease(function)', except it doesn't crash (as
   CFRelease does) if `function' is NULL. */

CG_EXTERN void CGFunctionRelease(CGFunctionRef __nullable function)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGFUNCTION_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFStream.h
/* CoreGraphics - CGPDFStream.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFSTREAM_H_
#define CGPDFSTREAM_H_

typedef struct CGPDFStream *CGPDFStreamRef;

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef CF_ENUM (int32_t, CGPDFDataFormat) {
    CGPDFDataFormatRaw, CGPDFDataFormatJPEGEncoded, CGPDFDataFormatJPEG2000
};

#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreFoundation/CFData.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Return the dictionary of `stream'. */

CG_EXTERN CGPDFDictionaryRef __nullable CGPDFStreamGetDictionary(
    CGPDFStreamRef __nullable stream)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the data of `stream'. */

CG_EXTERN CFDataRef __nullable CGPDFStreamCopyData(
    CGPDFStreamRef __nullable stream,
    CGPDFDataFormat * __nullable format)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFSTREAM_H_ */
// ==========  CoreGraphics.framework/Headers/CGDataProvider.h
/* CoreGraphics - CGDataProvider.h
   Copyright (c) 1999-2011 Apple Inc.
   All rights reserved. */

#ifndef CGDATAPROVIDER_H_
#define CGDATAPROVIDER_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGDataProvider *CGDataProviderRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <sys/types.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* This callback is called to copy `count' bytes from the sequential data
   stream to `buffer'. */

typedef size_t (*CGDataProviderGetBytesCallback)(void * __nullable info,
    void *  buffer, size_t count);

/* This callback is called to skip `count' bytes forward in the sequential
   data stream. It should return the number of bytes that were actually
   skipped. */

typedef off_t (*CGDataProviderSkipForwardCallback)(void * __nullable info,
    off_t count);

/* This callback is called to rewind to the beginning of sequential data
   stream. */

typedef void (*CGDataProviderRewindCallback)(void * __nullable info);

/* This callback is called to release the `info' pointer when the data
   provider is freed. */

typedef void (*CGDataProviderReleaseInfoCallback)(void * __nullable info);

/* Callbacks for sequentially accessing data.
   `version' is the version of this structure. It should be set to 0.
   `getBytes' is called to copy `count' bytes from the sequential data
     stream to `buffer'. It should return the number of bytes copied, or 0
     if there's no more data.
   `skipForward' is called to skip ahead in the sequential data stream by
     `count' bytes.
   `rewind' is called to rewind the sequential data stream to the beginning
     of the data.
   `releaseInfo', if non-NULL, is called to release the `info' pointer when
     the provider is freed. */

struct CGDataProviderSequentialCallbacks {
    unsigned int version;
    CGDataProviderGetBytesCallback __nullable getBytes;
    CGDataProviderSkipForwardCallback __nullable skipForward;
    CGDataProviderRewindCallback __nullable rewind;
    CGDataProviderReleaseInfoCallback __nullable releaseInfo;
};
typedef struct CGDataProviderSequentialCallbacks
    CGDataProviderSequentialCallbacks;

/*  This callback is called to get a pointer to the entire block of data. */

typedef const void * __nullable(*CGDataProviderGetBytePointerCallback)(
    void * __nullable info);

/* This callback is called to release the pointer to entire block of
   data. */

typedef void (*CGDataProviderReleaseBytePointerCallback)(
    void * __nullable info, const void *  pointer);

/* This callback is called to copy `count' bytes at byte offset `position'
   into `buffer'. */

typedef size_t (*CGDataProviderGetBytesAtPositionCallback)(
    void * __nullable info, void *  buffer, off_t pos, size_t cnt);

/* Callbacks for directly accessing data.
   `version' is the version of this structure. It should be set to 0.
   `getBytePointer', if non-NULL, is called to return a pointer to the
     provider's entire block of data.
   `releaseBytePointer', if non-NULL, is called to release a pointer to the
     provider's entire block of data.
   `getBytesAtPosition', if non-NULL, is called to copy `count' bytes at
     offset `position' from the provider's data to `buffer'. It should
     return the number of bytes copied, or 0 if there's no more data.
   `releaseInfo', if non-NULL, is called to release the `info' pointer when
     the provider is freed.

   At least one of `getBytePointer' or `getBytesAtPosition' must be
   non-NULL. */

struct CGDataProviderDirectCallbacks {
    unsigned int version;
    CGDataProviderGetBytePointerCallback __nullable getBytePointer;
    CGDataProviderReleaseBytePointerCallback __nullable releaseBytePointer;
    CGDataProviderGetBytesAtPositionCallback __nullable getBytesAtPosition;
    CGDataProviderReleaseInfoCallback __nullable releaseInfo;
};
typedef struct CGDataProviderDirectCallbacks CGDataProviderDirectCallbacks;

/* Return the CFTypeID for CGDataProviderRefs. */

CG_EXTERN CFTypeID CGDataProviderGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a sequential-access data provider using `callbacks' to provide the
   data. `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateSequential(
    void * __nullable info,
    const CGDataProviderSequentialCallbacks * __nullable callbacks)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Create a direct-access data provider using `callbacks' to supply `size'
   bytes of data. `info' is passed to each of the callback functions.
   The underlying data must not change for the life of the data provider. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateDirect(
    void * __nullable info, off_t size,
    const CGDataProviderDirectCallbacks * __nullable callbacks)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The callback used by `CGDataProviderCreateWithData'. */

typedef void (*CGDataProviderReleaseDataCallback)(void * __nullable info,
    const void *  data, size_t size);

/* Create a direct-access data provider using `data', an array of `size'
   bytes. `releaseData' is called when the data provider is freed, and is
   passed `info' as its first argument. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateWithData(
    void * __nullable info, const void * __nullable data, size_t size,
    CGDataProviderReleaseDataCallback __nullable releaseData)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a direct-access data provider which reads from `data'. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateWithCFData(
    CFDataRef __nullable data)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a data provider reading from `url'. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateWithURL(
    CFURLRef __nullable url)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a data provider reading from `filename'. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderCreateWithFilename(
    const char * __nullable filename)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRetain(provider)', but doesn't crash (as CFRetain does)
   if `provider' is NULL. */

CG_EXTERN CGDataProviderRef __nullable CGDataProviderRetain(
    CGDataProviderRef __nullable provider)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(provider)', but doesn't crash (as CFRelease
   does) if `provider' is NULL. */

CG_EXTERN void CGDataProviderRelease(CGDataProviderRef __nullable provider)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a copy of the data specified by provider. Returns NULL if a
   complete copy of the data can't be obtained (for example, if the
   underlying data is too large to fit in memory). */

CG_EXTERN CFDataRef __nullable CGDataProviderCopyData(
    CGDataProviderRef __nullable provider)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGDATAPROVIDER_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFArray.h
/* CoreGraphics - CGPDFArray.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFARRAY_H_
#define CGPDFARRAY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFArray *CGPDFArrayRef;

#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#/* Return the number of items in `array'. */

CG_EXTERN size_t CGPDFArrayGetCount(CGPDFArrayRef __nullable array)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and return the result in
   `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetObject(CGPDFArrayRef __nullable array, size_t index,
    CGPDFObjectRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a null, return
   true; otherwise, return false. */

CG_EXTERN bool CGPDFArrayGetNull(CGPDFArrayRef __nullable array, size_t index)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a boolean, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetBoolean(CGPDFArrayRef __nullable array,
    size_t index, CGPDFBoolean * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an integer, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetInteger(CGPDFArrayRef __nullable array,
    size_t index, CGPDFInteger * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a number (real or
   integer), return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFArrayGetNumber(CGPDFArrayRef __nullable array,
    size_t index, CGPDFReal * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a name, return the
   result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetName(CGPDFArrayRef __nullable array,
    size_t index, const char * __nullable *  __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a string, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetString(CGPDFArrayRef __nullable array,
    size_t index, CGPDFStringRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an array, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetArray(CGPDFArrayRef __nullable array,
    size_t index, CGPDFArrayRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a dictionary,
   return it in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetDictionary(CGPDFArrayRef __nullable array,
    size_t index, CGPDFDictionaryRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a stream, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetStream(CGPDFArrayRef __nullable array,
    size_t index, CGPDFStreamRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFARRAY_H_ */
// ==========  CoreGraphics.framework/Headers/CGLayer.h
/* CoreGraphics - CGLayer.h
 * Copyright (c) 2004-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGLAYER_H_
#define CGLAYER_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGLayer *CGLayerRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Create a layer of size `size' relative to the context `context'. The
   value of `size' is specified in default user space (base space) units.
   The parameter `auxiliaryInfo' should be NULL; it is reserved for future
   expansion. */

CG_EXTERN CGLayerRef __nullable CGLayerCreateWithContext(
    CGContextRef __nullable context,
    CGSize size, CFDictionaryRef __nullable auxiliaryInfo)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Equivalent to `CFRetain(layer)', except it doesn't crash (as CFRetain
   does) if `layer' is NULL. */

CG_EXTERN CGLayerRef __nullable CGLayerRetain(CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Equivalent to `CFRelease(layer)', except it doesn't crash (as CFRelease
   does) if `layer' is NULL. */

CG_EXTERN void CGLayerRelease(CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the size of the layer `layer'. CGSizeZero if invalid `layer'. */

CG_EXTERN CGSize CGLayerGetSize(CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the context of `layer'. */

CG_EXTERN CGContextRef __nullable CGLayerGetContext(CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Draw the contents of `layer' into `rect' of `context'. The contents are
   scaled, if necessary, to fit into `rect'; the rectangle `rect' is in user
   space. */

CG_EXTERN void CGContextDrawLayerInRect(CGContextRef __nullable context,
    CGRect rect, CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Draw the contents of `layer' at `point' in `context'. This is equivalent
   to calling "CGContextDrawLayerInRect" with a rectangle having origin at
   `point' and size equal to the size of `layer'. */

CG_EXTERN void CGContextDrawLayerAtPoint(CGContextRef __nullable context,
    CGPoint point, CGLayerRef __nullable layer)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the CFTypeID for CGLayerRefs. */

CG_EXTERN CFTypeID CGLayerGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* CGLAYER_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFScanner.h
/* CoreGraphics - CGPDFScanner.h
   Copyright (c) 2004-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFSCANNER_H_
#define CGPDFSCANNER_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFScanner *CGPDFScannerRef;

#include <CoreGraphics/CGPDFContentStream.h>
#include <CoreGraphics/CGPDFOperatorTable.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Create a scanner. */

CG_EXTERN CGPDFScannerRef  CGPDFScannerCreate(
    CGPDFContentStreamRef  cs,
    CGPDFOperatorTableRef __nullable table, void * __nullable info)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Retain `scanner'. */

CG_EXTERN CGPDFScannerRef __nullable CGPDFScannerRetain(
    CGPDFScannerRef __nullable scanner)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Release `scanner'. */

CG_EXTERN void CGPDFScannerRelease(CGPDFScannerRef __nullable scanner)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Scan the content stream of `scanner'. Returns true if the entire stream
   was scanned successfully; false if scanning failed for some reason (for
   example, if the stream's data is corrupted). */

CG_EXTERN bool CGPDFScannerScan(CGPDFScannerRef __nullable scanner)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the content stream associated with `scanner'. */

CG_EXTERN CGPDFContentStreamRef  CGPDFScannerGetContentStream(
    CGPDFScannerRef  scanner)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and return it in `value'. */

CG_EXTERN bool CGPDFScannerPopObject(CGPDFScannerRef  scanner,
    CGPDFObjectRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a boolean, return
   it in `value'. Return false if the top of the stack isn't a boolean. */

CG_EXTERN bool CGPDFScannerPopBoolean(CGPDFScannerRef  scanner,
    CGPDFBoolean * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's an integer, return
   it in `value'. Return false if the top of the stack isn't an integer. */

CG_EXTERN bool CGPDFScannerPopInteger(CGPDFScannerRef  scanner,
    CGPDFInteger * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a number, return
   it in `value'. Return false if the top of the stack isn't a number. */

CG_EXTERN bool CGPDFScannerPopNumber(CGPDFScannerRef  scanner,
    CGPDFReal * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a name, return it
   in `value'. Return false if the top of the stack isn't a name. */

CG_EXTERN bool CGPDFScannerPopName(CGPDFScannerRef  scanner,
    const char * __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a string, return
   it in `value'. Return false if the top of the stack isn't a string. */

CG_EXTERN bool CGPDFScannerPopString(CGPDFScannerRef  scanner,
    CGPDFStringRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's an array, return
   it in `value'. Return false if the top of the stack isn't an array. */

CG_EXTERN bool CGPDFScannerPopArray(CGPDFScannerRef  scanner,
    CGPDFArrayRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a dictionary,
   return it in `value'. Return false if the top of the stack isn't a
   dictionary. */

CG_EXTERN bool CGPDFScannerPopDictionary(CGPDFScannerRef  scanner,
    CGPDFDictionaryRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Pop an object from the stack of `scanner' and, if it's a stream, return
   it in `value'. Return false if the top of the stack isn't a stream. */

CG_EXTERN bool CGPDFScannerPopStream(CGPDFScannerRef  scanner,
    CGPDFStreamRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFSCANNER_H_ */
// ==========  CoreGraphics.framework/Headers/CoreGraphics.h
/* CoreGraphics - CoreGraphics.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef COREGRAPHICS_H_
#define COREGRAPHICS_H_

#include <CoreGraphics/CGBase.h>

#include <CoreGraphics/CGAffineTransform.h>
#include <CoreGraphics/CGBitmapContext.h>
#include <CoreGraphics/CGColor.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGDataConsumer.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGError.h>
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGFunction.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreGraphics/CGGradient.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGLayer.h>
#include <CoreGraphics/CGPDFArray.h>
#include <CoreGraphics/CGPDFContentStream.h>
#include <CoreGraphics/CGPDFContext.h>
#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFDocument.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFOperatorTable.h>
#include <CoreGraphics/CGPDFPage.h>
#include <CoreGraphics/CGPDFScanner.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGPattern.h>
#include <CoreGraphics/CGShading.h>


#endif	/* COREGRAPHICS_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFPage.h
/* CoreGraphics - CGPDFPage.h
   Copyright (c) 2001-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFPAGE_H_
#define CGPDFPAGE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFPage *CGPDFPageRef;

#include <CoreGraphics/CGAffineTransform.h> 
#include <CoreGraphics/CGPDFDictionary.h> 
#include <CoreGraphics/CGPDFDocument.h> 

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

typedef CF_ENUM (int32_t, CGPDFBox) {
  kCGPDFMediaBox = 0,
  kCGPDFCropBox = 1,
  kCGPDFBleedBox = 2,
  kCGPDFTrimBox = 3,
  kCGPDFArtBox = 4
};

/* Equivalent to `CFRetain(page)', except it doesn't crash (as CFRetain
   does) if `page' is NULL. */

CG_EXTERN CGPDFPageRef __nullable CGPDFPageRetain(CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRelease(page)', except it doesn't crash (as CFRelease
   does) if `page' is NULL. */

CG_EXTERN void CGPDFPageRelease(CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the document of `page'. */

CG_EXTERN CGPDFDocumentRef __nullable CGPDFPageGetDocument(
    CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the page number of `page'. */

CG_EXTERN size_t CGPDFPageGetPageNumber(CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the rectangle associated with `box' in `page'. This is the value
   of the corresponding entry (such as /MediaBox, /ArtBox, and so on) in the
   page's dictionary. Return CGRectNull if `page' is not a valid CGPDFPageRef
   or `box' is not a valid CGPDFBox. */

CG_EXTERN CGRect CGPDFPageGetBoxRect(CGPDFPageRef __nullable page, CGPDFBox box)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the rotation angle (in degrees) of `page'. This is the value of
   the /Rotate entry in the page's dictionary. Return 0 if `page' is not a valid
   CGPDFPageRef. */

CG_EXTERN int CGPDFPageGetRotationAngle(CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a transform mapping the box specified by `box' to `rect' as
   follows:
     - Compute the effective rect by intersecting the rect associated with
       `box' and the /MediaBox entry of the page.
     - Rotate the effective rect according to the page's /Rotate entry.
     - Center the resulting rect on `rect'. If `rotation' is non-zero, then
       the rect will rotated clockwise by `rotation' degrees. `rotation'
       must be a multiple of 90.
     - Scale the rect down, if necessary, so that it coincides with the
       edges of `rect'. If `preserveAspectRatio' is true, then the final
       rect will coincide with the edges of `rect' only in the more
       restrictive dimension. */

CG_EXTERN CGAffineTransform CGPDFPageGetDrawingTransform(
    CGPDFPageRef __nullable page, CGPDFBox box, CGRect rect, int rotate,
    bool preserveAspectRatio)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the dictionary of `page'. */

CG_EXTERN CGPDFDictionaryRef __nullable CGPDFPageGetDictionary(
    CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the CFTypeID for CGPDFPageRefs. */

CG_EXTERN CFTypeID CGPDFPageGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFPAGE_H_ */
// ==========  CoreGraphics.framework/Headers/CGPath.h
/* CoreGraphics - CGPath.h
   Copyright (c) 2001-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPATH_H_
#define CGPATH_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPath *CGMutablePathRef;
typedef const struct CGPath *CGPathRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Line join styles. */

typedef CF_ENUM(int32_t, CGLineJoin) {
    kCGLineJoinMiter,
    kCGLineJoinRound,
    kCGLineJoinBevel
};

/* Line cap styles. */

typedef CF_ENUM(int32_t, CGLineCap) {
    kCGLineCapButt,
    kCGLineCapRound,
    kCGLineCapSquare
};

/* Return the CFTypeID for CGPathRefs. */

CG_EXTERN CFTypeID CGPathGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a mutable path. */

CG_EXTERN CGMutablePathRef  CGPathCreateMutable(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a copy of `path'. */

CG_EXTERN CGPathRef __nullable CGPathCreateCopy(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a copy of `path' transformed by `transform'. */

CG_EXTERN CGPathRef __nullable CGPathCreateCopyByTransformingPath(
    CGPathRef __nullable path, const CGAffineTransform * __nullable transform)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Create a mutable copy of `path'. */

CG_EXTERN CGMutablePathRef __nullable CGPathCreateMutableCopy(
    CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a mutable copy of `path' transformed by `transform'. */

CG_EXTERN CGMutablePathRef __nullable CGPathCreateMutableCopyByTransformingPath(
    CGPathRef __nullable path, const CGAffineTransform * __nullable transform)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Return a path representing a rectangle bounded by `rect'. The rectangle
   forms a complete subpath of the path --- that is, it begins with a "move
   to" and ends with a "close subpath" --- oriented in the clockwise
   direction. If `transform' is non-NULL, then the lines representing the
   rectangle will be transformed by `transform' before they are added to the
   path. */

CG_EXTERN CGPathRef  CGPathCreateWithRect(CGRect rect,
    const CGAffineTransform * __nullable transform)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_4_0);

/* Return a path representing an ellipse bounded by `rect'. The ellipse is
   approximated by a sequence of Bézier curves. The center of the ellipse is
   the midpoint of `rect'. If `rect' is square, then the ellipse will be
   circular with radius equal to one-half the width (equivalently, one-half
   the height) of `rect'. If `rect' is rectangular, then the major- and
   minor-axes will be the `width' and `height' of rect. The ellipse forms a
   complete subpath of the path --- that is, it begins with a "move to" and
   ends with a "close subpath" --- oriented in the clockwise direction. If
   `transform' is non-NULL, then the constructed Bézier curves representing
   the ellipse will be transformed by `transform' before they are added to
   the path. */

CG_EXTERN CGPathRef  CGPathCreateWithEllipseInRect(CGRect rect,
    const CGAffineTransform * __nullable transform)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Return a path representing a rounded rectangle. The rounded rectangle
   coincides with the edges of `rect'. Each corner is consists of
   one-quarter of an ellipse with axes equal to `cornerWidth' and
   `cornerHeight'. The rounded rectangle forms a complete subpath of the
   path --- that is, it begins with a "move to" and ends with a "close
   subpath" --- oriented in the clockwise direction. If `transform' is
   non-NULL, then the path elements representing the rounded rectangle will
   be transformed by `transform' before they are added to the path. */

CG_EXTERN CGPathRef  CGPathCreateWithRoundedRect(CGRect rect,
    CGFloat cornerWidth, CGFloat cornerHeight,
    const CGAffineTransform * __nullable transform)
    CG_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/* Add a rounded rectangle to `path'. The rounded rectangle coincides with
   the edges of `rect'. Each corner is consists of one-quarter of an ellipse
   with axes equal to `cornerWidth' and `cornerHeight'. The rounded
   rectangle forms a complete subpath of the path --- that is, it begins
   with a "move to" and ends with a "close subpath" --- oriented in the
   clockwise direction. If `transform' is non-NULL, then the path elements
   representing the rounded rectangle will be transformed by `transform'
   before they are added to the path. */

CG_EXTERN void CGPathAddRoundedRect(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable transform, CGRect rect,
    CGFloat cornerWidth, CGFloat cornerHeight)
    CG_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/* Create a dashed path from `path'. The parameters `phase', `lengths', and
   `count' have the same meaning as the corresponding parameters for
   `CGContextSetLineDash'. If `transform' is non-NULL, then the elements of
   the constructed path will be transformed by `transform' before they are
   added to the path. */

CG_EXTERN CGPathRef __nullable CGPathCreateCopyByDashingPath(
    CGPathRef __nullable path, const CGAffineTransform * __nullable transform,
    CGFloat phase, const CGFloat * __nullable lengths, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Create a stroked path from `path'. The parameters `lineWidth', `lineCap',
   `lineJoin', and `miterLimit' have the same meaning as the corresponding
   CGContext parameters. If `transform' is non-NULL, then the elements of
   the constructed path will be transformed by `transform' before they are
   added to the path. */

CG_EXTERN CGPathRef __nullable CGPathCreateCopyByStrokingPath(
    CGPathRef __nullable path, const CGAffineTransform * __nullable transform,
    CGFloat lineWidth, CGLineCap lineCap,
    CGLineJoin lineJoin, CGFloat miterLimit)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Equivalent to `CFRetain(path)', except it doesn't crash (as CFRetain
   does) if `path' is NULL. */

CG_EXTERN CGPathRef __nullable CGPathRetain(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRelease(path)', except it doesn't crash (as CFRelease
   does) if `path' is NULL. */

CG_EXTERN void CGPathRelease(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `path1' is equal to `path2'; false otherwise. */

CG_EXTERN bool CGPathEqualToPath(CGPathRef __nullable path1,
    CGPathRef __nullable path2)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/*** Path construction functions. ***/

/* Move the current point to `(x, y)' in `path' and begin a new subpath. If
   `m' is non-NULL, then transform `(x, y)' by `m' first. */

CG_EXTERN void CGPathMoveToPoint(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Append a straight line segment from the current point to `(x, y)' in
   `path' and move the current point to `(x, y)'. If `m' is non-NULL, then
   transform `(x, y)' by `m' first. */

CG_EXTERN void CGPathAddLineToPoint(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Append a quadratic curve from the current point to `(x, y)' with control
   point `(cpx, cpy)' in `path' and move the current point to `(x, y)'. If
   `m' is non-NULL, then transform all points by `m' first. */

CG_EXTERN void CGPathAddQuadCurveToPoint(CGMutablePathRef __nullable path,
    const CGAffineTransform *__nullable m, CGFloat cpx, CGFloat cpy,
    CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Append a cubic Bézier curve from the current point to `(x,y)' with
   control points `(cp1x, cp1y)' and `(cp2x, cp2y)' in `path' and move the
   current point to `(x, y)'. If `m' is non-NULL, then transform all points
   by `m' first. */

CG_EXTERN void CGPathAddCurveToPoint(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGFloat cp1x, CGFloat cp1y,
    CGFloat cp2x, CGFloat cp2y, CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Append a line from the current point to the starting point of the current
   subpath of `path' and end the subpath. */

CG_EXTERN void CGPathCloseSubpath(CGMutablePathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/*** Path construction convenience functions. ***/

/* Add `rect' to `path'. If `m' is non-NULL, then first transform `rect' by
   `m' before adding it to `path'. */

CG_EXTERN void CGPathAddRect(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Add each rectangle specified by `rects', an array of `count' CGRects, to
   `path'. If `m' is non-NULL, then first transform each rectangle by `m'
   before adding it to `path'. */

CG_EXTERN void CGPathAddRects(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, const CGRect * __nullable rects,
    size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Move to the first element of `points', an array of `count' CGPoints, and
   append a line from each point to the next point in `points'. If `m' is
   non-NULL, then first transform each point by `m'. */

CG_EXTERN void CGPathAddLines(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, const CGPoint * __nullable points,
    size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Add an ellipse (an oval) inside `rect' to `path'. The ellipse is
   approximated by a sequence of Bézier curves. The center of the ellipse is
   the midpoint of `rect'. If `rect' is square, then the ellipse will be
   circular with radius equal to one-half the width (equivalently, one-half
   the height) of `rect'. If `rect' is rectangular, then the major- and
   minor-axes will be the `width' and `height' of rect. The ellipse forms a
   complete subpath of `path' --- that is, it begins with a "move to" and
   ends with a "close subpath" --- oriented in the clockwise direction. If
   `m' is non-NULL, then the constructed Bézier curves representing the
   ellipse will be transformed by `m' before they are added to `path'. */

CG_EXTERN void CGPathAddEllipseInRect(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Add an arc of a circle to `path', possibly preceded by a straight line
   segment. The arc is approximated by a sequence of Bézier curves. The
   center of the arc is `(x,y)'; `radius' is its radius. `startAngle' is the
   angle to the first endpoint of the arc, measured counter-clockwise from
   the positive x-axis. `startAngle + delta' is the angle to the second
   endpoint of the arc. If `delta' is positive, then the arc is drawn
   counter-clockwise; if negative, clockwise. `startAngle' and `delta' are
   measured in radians. If `matrix' is non-NULL, then the constructed Bézier
   curves representing the arc will be transformed by `matrix' before they
   are added to the path. */

CG_EXTERN void CGPathAddRelativeArc(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable matrix, CGFloat x, CGFloat y,
    CGFloat radius, CGFloat startAngle, CGFloat delta)
    CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* Add an arc of a circle to `path', possibly preceded by a straight line
   segment. The arc is approximated by a sequence of Bézier curves. `(x, y)'
   is the center of the arc; `radius' is its radius; `startAngle' is the
   angle to the first endpoint of the arc; `endAngle' is the angle to the
   second endpoint of the arc; and `clockwise' is true if the arc is to be
   drawn clockwise, false otherwise. `startAngle' and `endAngle' are
   measured in radians. If `m' is non-NULL, then the constructed Bézier
   curves representing the arc will be transformed by `m' before they are
   added to `path'.

   Note that using values very near 2π can be problematic. For example,
   setting `startAngle' to 0, `endAngle' to 2π, and `clockwise' to true will
   draw nothing. (It's easy to see this by considering, instead of 0 and 2π,
   the values ε and 2π - ε, where ε is very small.) Due to round-off error,
   however, it's possible that passing the value `2 * M_PI' to approximate
   2π will numerically equal to 2π + δ, for some small δ; this will cause a
   full circle to be drawn.

   If you want a full circle to be drawn clockwise, you should set
   `startAngle' to 2π, `endAngle' to 0, and `clockwise' to true. This avoids
   the instability problems discussed above. */

CG_EXTERN void CGPathAddArc(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m,
    CGFloat x, CGFloat y, CGFloat radius, CGFloat startAngle, CGFloat endAngle,
    bool clockwise)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Add an arc of a circle to `path', possibly preceded by a straight line
   segment. The arc is approximated by a sequence of Bézier curves. `radius'
   is the radius of the arc. The resulting arc is tangent to the line from
   the current point of `path' to `(x1, y1)', and the line from `(x1, y1)'
   to `(x2, y2)'. If `m' is non-NULL, then the constructed Bézier curves
   representing the arc will be transformed by `m' before they are added to
   `path'. */

CG_EXTERN void CGPathAddArcToPoint(CGMutablePathRef __nullable path,
    const CGAffineTransform * __nullable m, CGFloat x1, CGFloat y1,
    CGFloat x2, CGFloat y2, CGFloat radius)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Add `path2' to `path1'. If `m' is non-NULL, then the points in `path2'
   will be transformed by `m' before they are added to `path1'. */

CG_EXTERN void CGPathAddPath(CGMutablePathRef __nullable path1,
    const CGAffineTransform * __nullable m, CGPathRef __nullable path2)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/*** Path information functions. ***/

/* Return true if `path' contains no elements, false otherwise. */

CG_EXTERN bool CGPathIsEmpty(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `path' represents a rectangle, false otherwise. */

CG_EXTERN bool CGPathIsRect(CGPathRef __nullable path, CGRect * __nullable rect)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the current point of the current subpath of `path'. If there is no
   current point, then return CGPointZero. */

CG_EXTERN CGPoint CGPathGetCurrentPoint(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bounding box of `path'. The bounding box is the smallest
   rectangle completely enclosing all points in the path, including control
   points for Bézier cubic and quadratic curves. If the path is empty, then
   return `CGRectNull'. */

CG_EXTERN CGRect CGPathGetBoundingBox(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the path bounding box of `path'. The path bounding box is the
   smallest rectangle completely enclosing all points in the path, *not*
   including control points for Bézier cubic and quadratic curves. If the
   path is empty, then return `CGRectNull'. */

CG_EXTERN CGRect CGPathGetPathBoundingBox(CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);

/* Return true if `point' is contained in `path'; false otherwise. A point
   is contained in a path if it is inside the painted region when the path
   is filled; if `eoFill' is true, then the even-odd fill rule is used to
   evaluate the painted region of the path, otherwise, the winding-number
   fill rule is used. If `m' is non-NULL, then the point is transformed by
   `m' before determining whether the path contains it. */

CG_EXTERN bool CGPathContainsPoint(CGPathRef __nullable path,
    const CGAffineTransform * __nullable m, CGPoint point, bool eoFill)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The types of path elements returned by `CGPathApply'. */

typedef CF_ENUM(int32_t, CGPathElementType) {
  kCGPathElementMoveToPoint,
  kCGPathElementAddLineToPoint,
  kCGPathElementAddQuadCurveToPoint,
  kCGPathElementAddCurveToPoint,
  kCGPathElementCloseSubpath
};

/* An element of a path returned by `CGPathApply'. */

struct CGPathElement {
  CGPathElementType type;
  CGPoint *  points;
};
typedef struct CGPathElement CGPathElement;

/* The prototype for the function called by `CGPathApplyFunction'. */

typedef void (*CGPathApplierFunction)(void * __nullable info,
  const CGPathElement *  element);

/* For element of `path', call `function', passing it the path element and
   `info'. */

CG_EXTERN void CGPathApply(CGPathRef __nullable path, void * __nullable info,
    CGPathApplierFunction __nullable function)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPATH_H_ */
// ==========  CoreGraphics.framework/Headers/CGColor.h
/* CoreGraphics - CGColor.h
 * Copyright (c) 2003-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGCOLOR_H_
#define CGCOLOR_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGColor *CGColorRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGPattern.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Create a color in the color space `space' with color components
   (including alpha) specified by `components'. `space' may be any color
   space except a pattern color space. */

CG_EXTERN CGColorRef __nullable CGColorCreate(CGColorSpaceRef __nullable space,
  const CGFloat * __nullable components)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a color in the "Generic" gray color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericGray(CGFloat gray, CGFloat alpha)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in the "Generic" RGB color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericRGB(CGFloat red, CGFloat green,
  CGFloat blue, CGFloat alpha) CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in the "Generic" CMYK color space. */

CG_EXTERN CGColorRef  CGColorCreateGenericCMYK(CGFloat cyan, CGFloat magenta,
  CGFloat yellow, CGFloat black, CGFloat alpha)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Return a constant color. As `CGColorGetConstantColor' is not a "Copy" or
   "Create" function, it does not necessarily return a new reference each
   time it's called. As a consequence, you should not release the returned
   value. However, colors returned from `CGColorGetConstantColor' can be
   retained and released in a properly nested fashion, just like any other
   CF type. */

CG_EXTERN CGColorRef __nullable CGColorGetConstantColor(CFStringRef __nullable colorName)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Create a color in color space `space' with pattern `pattern' and
   components `components'. `space' must be a pattern color space. */

CG_EXTERN CGColorRef __nullable CGColorCreateWithPattern(CGColorSpaceRef __nullable space,
  CGPatternRef __nullable pattern, const CGFloat * __nullable components)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a copy of `color'. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopy(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a copy of `color' with alpha set to `alpha'. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopyWithAlpha(CGColorRef __nullable color,
  CGFloat alpha) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Create a copy of `color' by matching existing color to destination color space. */

CG_EXTERN CGColorRef __nullable CGColorCreateCopyByMatchingToColorSpace(__nullable CGColorSpaceRef,
  CGColorRenderingIntent intent, CGColorRef __nullable color, __nullable CFDictionaryRef options)
  CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/* Equivalent to `CFRetain(color)', except it doesn't crash (as CFRetain
   does) if `color' is NULL. */

CG_EXTERN CGColorRef __nullable CGColorRetain(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRelease(color)', except it doesn't crash (as CFRelease
   does) if `color' is NULL. */

CG_EXTERN void CGColorRelease(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return true if `color1' is equal to `color2'; false otherwise. */

CG_EXTERN bool CGColorEqualToColor(CGColorRef __nullable color1, CGColorRef __nullable color2)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the number of color components (including alpha) associated with
   `color'. */

CG_EXTERN size_t CGColorGetNumberOfComponents(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the color components (including alpha) associated with `color'. */

CG_EXTERN const CGFloat * __nullable CGColorGetComponents(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the alpha component associated with `color'. */

CG_EXTERN CGFloat CGColorGetAlpha(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the color space associated with `color'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorGetColorSpace(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the pattern associated with `color', if it's a color in a pattern
   color space; NULL otherwise. */

CG_EXTERN CGPatternRef __nullable CGColorGetPattern(CGColorRef __nullable color)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the CFTypeID for CGColors. */

CG_EXTERN CFTypeID CGColorGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*** Names of colors for use with `CGColorGetConstantColor'. ***/

/* Colors in the "Generic" gray color space. */

CG_EXTERN const CFStringRef  kCGColorWhite
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

CG_EXTERN const CFStringRef  kCGColorBlack
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

CG_EXTERN const CFStringRef  kCGColorClear
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLOR_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFContext.h
/* CoreGraphics - CGPDFContext.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFCONTEXT_H_
#define CGPDFCONTEXT_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGDataConsumer.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN


/* Create a PDF context, using `consumer' for output. `mediaBox' is the
   default page media bounding box; if NULL, then a default page size is
   used. `auxiliaryInfo' specifies additional information used by the PDF
   context when generating the PDF file. The keys and values in
   `auxiliaryInfo' are described below. If `mediaBox' is non-NULL, then its
   value overrides the value of `kCGPDFContextMediaBox' if specified in the
   `auxiliaryInfo' dictionary. */

CG_EXTERN CGContextRef __nullable CGPDFContextCreate(CGDataConsumerRef __nullable consumer,
  const CGRect *__nullable mediaBox, CFDictionaryRef __nullable auxiliaryInfo)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a PDF context for writing to `url'. This function behaves in the
   same manner as the above function, except that the output data will be
   written to `url'. */

CG_EXTERN CGContextRef __nullable CGPDFContextCreateWithURL(CFURLRef __nullable url,
  const CGRect * __nullable mediaBox, CFDictionaryRef __nullable auxiliaryInfo)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Close a PDF context. After closing the context, all pending data is
   written to the context's destination, and the PDF file is completed. No
   additional data will be written to the context's destionation after
   closing. */

CG_EXTERN void CGPDFContextClose(CGContextRef __nullable context)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Begin a new page in the PDF context `context'. */

CG_EXTERN void CGPDFContextBeginPage(CGContextRef __nullable context,
  CFDictionaryRef __nullable pageInfo)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* End the current page in the PDF context `context'. */

CG_EXTERN void CGPDFContextEndPage(CGContextRef __nullable context)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Add the metadata stream specified by `metadata' to the document catalog
   of `context', as described in Table 3.25, "Entries in the catalog
   dictionary", of the PDF 1.7 specification. The contents of metadata must
   be XML formatted according to the Extensible Metadata Platform, as
   described in section 10.2.2, "Metadata Streams", of the PDF 1.7
   specification. */

CG_EXTERN void CGPDFContextAddDocumentMetadata(CGContextRef __nullable context,
  CFDataRef __nullable metadata) CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);

/* Set the URL associated with `rect' to `url' in the PDF context
   `context'. */

CG_EXTERN void CGPDFContextSetURLForRect(CGContextRef __nullable context, CFURLRef  url,
  CGRect rect) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a PDF destination named `name' at `point' in the current page of
   the PDF context `context'. */

CG_EXTERN void CGPDFContextAddDestinationAtPoint(CGContextRef __nullable context,
  CFStringRef  name, CGPoint point)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Specify a destination named `name' to jump to when clicking in `rect' of
   the current page of the PDF context `context'. */

CG_EXTERN void CGPDFContextSetDestinationForRect(CGContextRef __nullable context,
  CFStringRef  name, CGRect rect)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Keys for the auxiliary info dictionary or the page info dictionary. ***/ 

/* The media box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef  kCGPDFContextMediaBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The crop box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef  kCGPDFContextCropBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The bleed box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef  kCGPDFContextBleedBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The trim box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef  kCGPDFContextTrimBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The art box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef  kCGPDFContextArtBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Keys for auxiliary info dictionary. ***/

/* The document's title. Optional; if present, the value of this key must be
   a CFString. */

CG_EXTERN const CFStringRef  kCGPDFContextTitle
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The name of the person who created this document. Optional; if present,
   the value of this key must be a CFString. */

CG_EXTERN const CFStringRef  kCGPDFContextAuthor
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The subject of a document. Optional; if present, the value of this key
   must be a CFString. */

CG_EXTERN const CFStringRef  kCGPDFContextSubject
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The keywords for this document. This key is optional. If the value of
   this key is a CFString, the /Keywords entry will be the specified string.
   If the value of this key is a CFArray, then it must be an array of
   CFStrings. The /Keywords entry will in this case be the concatenation of
   the specified strings separated by commas (","). In addition, an entry
   with the key "/AAPL:Keywords" will be stored in the document information
   dictionary; its value is an array consisting of each of the specified
   strings. The value of this key must be in one of the above forms;
   otherwise, this key is ignored. */

CG_EXTERN const CFStringRef  kCGPDFContextKeywords
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The name of the application that created the original data used to create
   this document. Optional; if present, the value of this key must be a
   CFString. */

CG_EXTERN const CFStringRef  kCGPDFContextCreator
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The "owner password" of the PDF document. If this key is specified, the
   document will be encrypted using the value as the owner password;
   otherwise, the document will not be encrypted. The value of this key must
   be a CFStringRef which can be represented in ASCII encoding; only the
   first 32 bytes will be used for the password. There is no default value
   for this key.

   If the value of this key cannot be represented in ASCII, the document
   will not be created and the creation function will return NULL. */

CG_EXTERN const CFStringRef  kCGPDFContextOwnerPassword
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The "user password" of the PDF document. If the document is encrypted,
   then the value of this key will be the user password for the document; if
   unspecified, the user password will be the empty string. The value of
   this key must be a CFStringRef which can be represented in ASCII
   encoding; only the first 32 bytes will be used for the password.

   If the value of this key cannot be represented in ASCII, the document
   will not be created and the creation function will return NULL. */

CG_EXTERN const CFStringRef  kCGPDFContextUserPassword
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Specifies the encryption key length in bits; see Table 3.18 "Entries
   common to all encryption dictionaries", PDF Reference: Adobe PDF version
   1.5 (4th ed.) for more info. Optional; if present, the value of this key
   must be a CFNumber with value which is a multiple of 8 between 40 and
   128, inclusive. If this key is absent or invalid, the encryption key
   length defaults to 40 bits. */

CG_EXTERN const CFStringRef  kCGPDFContextEncryptionKeyLength
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Used to specify whether the document allows printing when unlocked with
   the user password. The value of this key must be a CFBooleanRef. The
   default value of this key is "kCFBooleanTrue". */

CG_EXTERN const CFStringRef  kCGPDFContextAllowsPrinting
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Used to specify whether the document allows copying when unlocked with
   the user password. The value of this key must be a CFBooleanRef. The
   default value of this key is "kCFBooleanTrue". */

CG_EXTERN const CFStringRef  kCGPDFContextAllowsCopying
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The document's PDF/X output intent. Optional; if present, the value of
   this key must be a CFDictionaryRef. The dictionary is added to the
   /OutputIntents entry in the PDF file's document catalog. The keys and
   values contained in the dictionary must match those specified in section
   9.10.4 of the PDF 1.4 specification, ISO/DIS 15930-3 document published
   by ISO/TC 130, and Adobe Technical Note #5413. */

CG_EXTERN const CFStringRef  kCGPDFContextOutputIntent
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The following keys are supported in the output intent dictionary:

   kCGPDFXOutputIntentSubtype ("S"): The output intent subtype. This key is
   required; the value of this key must be a CFString equal to "GTS_PDFX";
   otherwise, the dictionary is ignored. */

CG_EXTERN const CFStringRef  kCGPDFXOutputIntentSubtype
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXOutputConditionIdentifier ("OutputConditionIdentifier"): A string
   identifying the intended output device or production condition in a
   human- or machine-readable form. This key is required; the value of this
   key must be a CFString. For best results, the string should be
   representable losslessly in ASCII encoding. */

CG_EXTERN const CFStringRef  kCGPDFXOutputConditionIdentifier
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXOutputCondition ("OutputCondition"): A text string identifying the
   intended output device or production condition in a human-readable form.
   This key is optional; if present, the value of this key must be a
   CFString. */

CG_EXTERN const CFStringRef  kCGPDFXOutputCondition
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXRegistryName ("RegistryName"): A string identifying the registry
   in which the condition designated by `kCGPDFXOutputConditionIdentifier'
   is defined. This key is optional; if present, the value of this key must
   be a CFString. For best results, the string should be representable
   losslessly in ASCII encoding. */

CG_EXTERN const CFStringRef  kCGPDFXRegistryName
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXInfo ("Info"): A human-readable text string containing additional
   information about the intended target device or production condition.
   This key is required if the value of `kCGPDFXOutputConditionIdentifier'
   does not specify a standard production condition; it is optional
   otherwise. If present, the value of this key must be a CFString. */

CG_EXTERN const CFStringRef  kCGPDFXInfo
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXDestinationOutputProfile ("DestOutputProfile"): An ICC profile
   stream defining the transformation from the PDF document's source colors
   to output device colorants. This key is required if the value of
   `kCGPDFXOutputConditionIdentifier' does not specify a standard production
   condition; it is optional otherwise. If present, the value of this key
   must be a ICC-based CGColorSpaceRef. */

CG_EXTERN const CFStringRef  kCGPDFXDestinationOutputProfile
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The document's output intents. Optional; if present, the value must be a
   CFArrayRef containing one or more CFDictionaryRefs. The array is added to
   the PDF document in the /OutputIntents entry in the PDF file's document
   catalog. Each dictionary in the array must be of form specified above for
   the `kCGPDFContextOutputIntent' key, except that only the first
   dictionary in the array may contain the `kCGPDFXOutputIntentSubtype'
   ("S") key with a value of "GTS_PDFX". If both `kCGPDFContextOutputIntent'
   and `kCGPDFContextOutputIntents' keys are specified, the former is
   ignored. */

CG_EXTERN const CFStringRef  kCGPDFContextOutputIntents
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFCONTEXT_H_ */
// ==========  CoreGraphics.framework/Headers/CGBase.h
/* CoreGraphics - CGBase.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGBASE_H_
#define CGBASE_H_

#include <stdbool.h>
#include <stddef.h>
#include <float.h>

/* Definition of `__CG_HAS_COMPILER_ATTRIBUTE'. */

#if !defined(__CG_HAS_COMPILER_ATTRIBUTE)
# if defined(__has_attribute)
#  define __CG_HAS_COMPILER_ATTRIBUTE(attribute) __has_attribute(attribute)
# elif defined(__GNUC__) && __GNUC__ >= 4
#  define __CG_HAS_COMPILER_ATTRIBUTE(attribute) (1)
# else
#  define __CG_HAS_COMPILER_ATTRIBUTE(attribute) (0)
# endif
#endif

/* Definition of `__CG_HAS_COMPILER_EXTENSION'. */

#if !defined(__CG_HAS_COMPILER_EXTENSION)
# if defined(__has_extension)
#  define __CG_HAS_COMPILER_EXTENSION(extension) __has_extension(extension)
# elif defined(__has_feature)
#  define __CG_HAS_COMPILER_EXTENSION(extension) __has_feature(extension)
# else
#  define __CG_HAS_COMPILER_EXTENSION(extension) (0)
# endif
#endif

/* Define `__WIN32__' where appropriate if it's not already defined. */

# if defined(_WIN32) || defined(__CYGWIN32__)
#  define __WIN32__ 1
# endif

/* Definition of `CG_EXTERN'. */

#if !defined(CG_EXTERN)
#  if defined(__cplusplus)
#   define CG_EXTERN extern "C"
#  else
#   define CG_EXTERN extern
#  endif
#endif /* !defined(CG_EXTERN) */

/* Definition of `CG_LOCAL'. */

#if !defined(CG_LOCAL)
# if __CG_HAS_COMPILER_ATTRIBUTE(visibility)
#  if defined(__cplusplus)
#   define CG_LOCAL extern "C" __attribute__((visibility("hidden")))
#  else
#   define CG_LOCAL extern __attribute__((visibility("hidden")))
#  endif
# else
#  define CG_LOCAL CG_EXTERN
# endif
#endif /* !defined(CG_LOCAL) */

/* Definition of `CG_EXTERN_64` */

#if !defined(CG_EXTERN_64)
# if defined(__LP64__)
#  define CG_EXTERN_64 CG_EXTERN
# else /* !defined(__LP64__) */
#  define CG_EXTERN_64 CG_LOCAL
# endif /* defined(__LP64__) */
#endif /* !defined(CG_EXTERN_64) */

/* Definition of `CG_EXTERN_32` */

#if !defined(CG_EXTERN_32)
# if defined(__LP64__)
#  define CG_EXTERN_32 CG_LOCAL __attribute__((unused))
# else /* !defined(__LP64__) */
#  define CG_EXTERN_32 CG_EXTERN
# endif /* defined(__LP64__) */
#endif /* !defined(CG_EXTERN_32) */

/* Definition of `CG_LOCAL_64` */

#if !defined(CG_LOCAL_64)
# if defined(__LP64__)
#  define CG_LOCAL_64 CG_LOCAL
# else /* !defined(__LP64__) */
#  define CG_LOCAL_64 CG_LOCAL __attribute__((unused))
# endif /* defined(__LP64__) */
#endif /* !defined(CG_LOCAL_64) */

/* Definition of `CG_LOCAL_32` */

#if !defined(CG_LOCAL_32)
# if defined(__LP64__)
#  define CG_LOCAL_32 CG_LOCAL __attribute__((unused))
# else /* !defined(__LP64__) */
#  define CG_LOCAL_32 CG_LOCAL
# endif /* defined(__LP64__) */
#endif /* !defined(CG_LOCAL_32) */

/* Definition of `__CG_DEPRECATED'. */

#if !defined(__CG_DEPRECATED)
# if __CG_HAS_COMPILER_ATTRIBUTE(deprecated) && !defined(CG_BUILDING_CG)
#  define __CG_DEPRECATED __attribute__((deprecated))
# else
#  define __CG_DEPRECATED
# endif
#endif

/* Definition of `__CG_DEPRECATED_WITH_MSG'. */

#if !defined(__CG_DEPRECATED_WITH_MSG)
# if __CG_HAS_COMPILER_ATTRIBUTE(deprecated)				      \
    && __CG_HAS_COMPILER_EXTENSION(attribute_deprecated_with_message)	      \
    && !defined(CG_BUILDING_CG)
#  define __CG_DEPRECATED_WITH_MSG(msg) __attribute__((deprecated(msg)))
# else
#  define __CG_DEPRECATED_WITH_MSG(msg) __CG_DEPRECATED
# endif
#endif

/* Definition of `__CG_DEPRECATED_ENUMERATOR'. */

#if !defined(__CG_DEPRECATED_ENUMERATOR)
# if __CG_HAS_COMPILER_ATTRIBUTE(deprecated)				      \
   && __CG_HAS_COMPILER_EXTENSION(enumerator_attributes)		      \
   && !defined(CG_BUILDING_CG)
#  define __CG_DEPRECATED_ENUMERATOR __attribute__((deprecated))
# else
#  define __CG_DEPRECATED_ENUMERATOR
# endif
#endif

/* Definition of `__CG_DEPRECATED_ENUMERATOR_WITH_MSG'. */

#if !defined(__CG_DEPRECATED_ENUMERATOR_WITH_MSG)
# if __CG_HAS_COMPILER_ATTRIBUTE(deprecated)				      \
&& __CG_HAS_COMPILER_EXTENSION(attribute_deprecated_with_message) \
&& __CG_HAS_COMPILER_EXTENSION(enumerator_attributes)		      \
&& !defined(CG_BUILDING_CG)
#  define __CG_DEPRECATED_ENUMERATOR_WITH_MSG(msg) __attribute__((deprecated(msg)))
# else
#  define __CG_DEPRECATED_ENUMERATOR_WITH_MSG(msg) __CG_DEPRECATED_ENUMERATOR
# endif
#endif

/* Define `CG_AVAILABLE_STARTING' and `CG_AVAILABLE_BUT_DEPRECATED'. */

#if defined(CG_BUILDING_CG)
# define CG_AVAILABLE_STARTING(_mac, _iphone)
# define CG_AVAILABLE_BUT_DEPRECATED(_mac, _macDep, _iphone, _iphoneDep)
#else
# include <Availability.h>
# define CG_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
# define CG_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#endif

/* Definition of `__CG_STATIC_ASSERT'. */

#if !defined(__CG_STATIC_ASSERT)
# if defined(__cplusplus) && __CG_HAS_COMPILER_EXTENSION(cxx_static_assert)
#  define __CG_STATIC_ASSERT(constant_expression)			      \
     static_assert(constant_expression, #constant_expression)
# elif !defined(__cplusplus) && __CG_HAS_COMPILER_EXTENSION(c_static_assert)
#  define __CG_STATIC_ASSERT(constant_expression)			      \
     _Static_assert(constant_expression, #constant_expression)
# else
#  define __CG_STATIC_ASSERT(constant_expression)
# endif
#endif

/* Definition of `CG_INLINE'. */

#if !defined(CG_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define CG_INLINE static inline
# elif defined(__cplusplus)
#  define CG_INLINE static inline
# elif defined(__GNUC__)
#  define CG_INLINE static __inline__
# else
#  define CG_INLINE static    
# endif
#endif

/* Definition of `__CG_NO_INLINE'. */

#if !defined(__CG_NO_INLINE)
# if __CG_HAS_COMPILER_ATTRIBUTE(noinline)
#  define __CG_NO_INLINE static __attribute__((noinline))
# else
#  define __CG_NO_INLINE static
# endif
#endif

/* Definition of `__CG_FORMAT_PRINTF'. */

#if !defined(__CG_FORMAT_PRINTF)
# if __CG_HAS_COMPILER_ATTRIBUTE(format)
#  define __CG_FORMAT_PRINTF(FORMAT_STRING, STARTING_ARG)		      \
     __attribute__((format(printf, FORMAT_STRING, STARTING_ARG)))	      \
     __attribute__((nonnull(FORMAT_STRING)))
# else
#  define __CG_FORMAT_PRINTF(FORMAT_STRING, STARTING_ARG)
# endif
#endif

/* Definition of `__CG_FORMAT_VPRINTF'. */

#if !defined(__CG_FORMAT_VPRINTF)
# if __CG_HAS_COMPILER_ATTRIBUTE(format)
#  define __CG_FORMAT_VPRINTF(FORMAT_STRING)				      \
     __attribute__((format(printf, FORMAT_STRING, 0)))
# else
#  define __CG_FORMAT_VPRINTF(FORMAT_STRING)
# endif
#endif

/* Definition of `CGFLOAT_TYPE', `CGFLOAT_IS_DOUBLE', `CGFLOAT_MIN', and
   `CGFLOAT_MAX'. */

#if defined(__LP64__) && __LP64__
# define CGFLOAT_TYPE double
# define CGFLOAT_IS_DOUBLE 1
# define CGFLOAT_MIN DBL_MIN
# define CGFLOAT_MAX DBL_MAX
#else
# define CGFLOAT_TYPE float
# define CGFLOAT_IS_DOUBLE 0
# define CGFLOAT_MIN FLT_MIN
# define CGFLOAT_MAX FLT_MAX
#endif

/* Definition of the `CGFloat' type and `CGFLOAT_DEFINED'. */

typedef CGFLOAT_TYPE CGFloat;
#define CGFLOAT_DEFINED 1

/* Definition of `CG_OBSOLETE'. Deprecated; to be removed. */

#if !defined(CG_OBSOLETE)
# define CG_OBSOLETE __CG_DEPRECATED
#endif

/* Definition of `CG_PRIVATE_EXTERN'. Deprecated; to be removed. */

#if !defined(CG_PRIVATE_EXTERN) && !defined(CG_BUILDING_CG)
# define CG_PRIVATE_EXTERN CG_LOCAL
#endif

#endif /* CGBASE_H_ */
// ==========  CoreGraphics.framework/Headers/CGBitmapContext.h
/* CoreGraphics - CGBitmapContext.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGBITMAPCONTEXT_H_
#define CGBITMAPCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* The callback for releasing the data supplied to
   `CGBitmapContextCreateWithData'. */

typedef void (*CGBitmapContextReleaseDataCallback)(void * __nullable releaseInfo,
    void * __nullable data);

/* Create a bitmap context. The context draws into a bitmap which is `width'
   pixels wide and `height' pixels high. The number of components for each
   pixel is specified by `space', which may also specify a destination color
   profile. The number of bits for each component of a pixel is specified by
   `bitsPerComponent'. The number of bytes per pixel is equal to
   `(bitsPerComponent * number of components + 7)/8'. Each row of the bitmap
   consists of `bytesPerRow' bytes, which must be at least `width * bytes
   per pixel' bytes; in addition, `bytesPerRow' must be an integer multiple
   of the number of bytes per pixel. `data', if non-NULL, points to a block
   of memory at least `bytesPerRow * height' bytes. If `data' is NULL, the
   context will allocate the data itself; this data will be freed when the
   context is deallocated. `bitmapInfo' specifies whether the bitmap should
   contain an alpha channel and how it's to be generated, along with whether
   the components are floating-point or integer. If `releaseCallback' is
   non-NULL, it is called when the context is freed with `releaseInfo' and
   `data' as arguments. */

CG_EXTERN CGContextRef __nullable CGBitmapContextCreateWithData(
    void * __nullable data, size_t width, size_t height, size_t bitsPerComponent,
    size_t bytesPerRow, CGColorSpaceRef __nullable space, uint32_t bitmapInfo,
    CGBitmapContextReleaseDataCallback __nullable releaseCallback,
    void * __nullable releaseInfo)
    CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);

/* Create a bitmap context. The context draws into a bitmap which is `width'
   pixels wide and `height' pixels high. The number of components for each
   pixel is specified by `space', which may also specify a destination color
   profile. The number of bits for each component of a pixel is specified by
   `bitsPerComponent'. The number of bytes per pixel is equal to
   `(bitsPerComponent * number of components + 7)/8'. Each row of the bitmap
   consists of `bytesPerRow' bytes, which must be at least `width * bytes
   per pixel' bytes; in addition, `bytesPerRow' must be an integer multiple
   of the number of bytes per pixel. `data', if non-NULL, points to a block
   of memory at least `bytesPerRow * height' bytes. If `data' is NULL, the
   data for context is allocated automatically and freed when the context is
   deallocated. `bitmapInfo' specifies whether the bitmap should contain an
   alpha channel and how it's to be generated, along with whether the
   components are floating-point or integer. */

CG_EXTERN CGContextRef __nullable CGBitmapContextCreate(void * __nullable data,
    size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow,
    CGColorSpaceRef __nullable space, uint32_t bitmapInfo)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the data associated with the bitmap context `context', or NULL if
   `context' is not a bitmap context. */

CG_EXTERN void * __nullable CGBitmapContextGetData(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the width of the bitmap context `context', or 0 if `context' is
   not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetWidth(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the height of the bitmap context `context', or 0 if `context' is
   not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetHeight(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bits per component of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerComponent(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bits per pixel of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerPixel(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bytes per row of the bitmap context `context', or 0 if
   `context' is not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBytesPerRow(CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the color space of the bitmap context `context', or NULL if
   `context' is not a bitmap context. */

CG_EXTERN CGColorSpaceRef __nullable CGBitmapContextGetColorSpace(
    CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the alpha info of the bitmap context `context', or
   "kCGImageAlphaNone" if `context' is not a bitmap context. */

CG_EXTERN CGImageAlphaInfo CGBitmapContextGetAlphaInfo(
    CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bitmap info of the bitmap context `context', or 0 if `context'
   is not a bitmap context. */

CG_EXTERN CGBitmapInfo CGBitmapContextGetBitmapInfo(
    CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return an image containing a snapshot of the bitmap context `context'. If
   context is not a bitmap context, or if the image cannot be created for
   any reason, this function returns NULL. This is a "copy" operation ---
   subsequent changes to context will not affect the contents of the
   returned image.

   Note that in some cases the copy will actually follow "copy-on-write"
   semantics, so that the actual physical copy of the bits will only occur
   if the underlying data in the bitmap context is modified. As a
   consequence, you may wish to use the resulting image and release it
   before performing more drawing into the bitmap context; in this way, the
   actual physical copy of the data may be avoided. */

CG_EXTERN CGImageRef __nullable CGBitmapContextCreateImage(
    CGContextRef __nullable context)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGBITMAPCONTEXT_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFDocument.h
/* CoreGraphics - CGPDFDocument.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFDOCUMENT_H_
#define CGPDFDOCUMENT_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFDocument *CGPDFDocumentRef;

#include <CoreGraphics/CGDataProvider.h> 
#include <CoreGraphics/CGGeometry.h> 
#include <CoreGraphics/CGPDFPage.h> 
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Create a PDF document, using `provider' to obtain the document's data. */

CG_EXTERN CGPDFDocumentRef __nullable CGPDFDocumentCreateWithProvider(
    CGDataProviderRef __nullable provider)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a PDF document from `url'. */

CG_EXTERN CGPDFDocumentRef __nullable CGPDFDocumentCreateWithURL(
    CFURLRef __nullable url)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRetain(document)', except it doesn't crash (as CFRetain
   does) if `document' is NULL. */

CG_EXTERN CGPDFDocumentRef __nullable CGPDFDocumentRetain(
    CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(document)', except it doesn't crash (as
   CFRelease does) if `document' is NULL. */

CG_EXTERN void CGPDFDocumentRelease(CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the major and minor version numbers of `document'. */

CG_EXTERN void CGPDFDocumentGetVersion(CGPDFDocumentRef __nullable document,
  int *  majorVersion, int *  minorVersion)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return true if the PDF file associated with `document' is encrypted;
   false otherwise. If the PDF file is encrypted, then a password must be
   supplied before certain operations are enabled; different passwords may
   enable different operations. */

CG_EXTERN bool CGPDFDocumentIsEncrypted(CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Use `password' to decrypt `document' and grant permission for certain
   operations. Returns true if `password' is a valid password; false
   otherwise. */

CG_EXTERN bool CGPDFDocumentUnlockWithPassword(
    CGPDFDocumentRef __nullable document, const char *  password)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `document' is unlocked; false otherwise. A document is
   unlocked if it isn't encrypted, or if it is encrypted and a valid
   password was specified with `CGPDFDocumentUnlockWithPassword'. */

CG_EXTERN bool CGPDFDocumentIsUnlocked(CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `document' allows printing; false otherwise. Typically,
   this function returns false only if the document is encrypted and the
   document's current password doesn't grant permission to perform
   printing. */

CG_EXTERN bool CGPDFDocumentAllowsPrinting(CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `document' allows copying; false otherwise. Typically,
   this function returns false only if the document is encrypted and the
   document's current password doesn't grant permission to perform
   copying. */

CG_EXTERN bool CGPDFDocumentAllowsCopying(CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the number of pages in `document'. */

CG_EXTERN size_t CGPDFDocumentGetNumberOfPages(
    CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the page corresponding to `pageNumber', or NULL if no such page
   exists in the document. Pages are numbered starting at 1. */

CG_EXTERN CGPDFPageRef __nullable CGPDFDocumentGetPage(
    CGPDFDocumentRef __nullable document, size_t pageNumber)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the document catalog of `document'. */

CG_EXTERN CGPDFDictionaryRef __nullable CGPDFDocumentGetCatalog(
    CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the info dictionary of `document'. */

CG_EXTERN CGPDFDictionaryRef __nullable CGPDFDocumentGetInfo(
    CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the "file identifier" array of `document'. */

CG_EXTERN CGPDFArrayRef __nullable CGPDFDocumentGetID(
    CGPDFDocumentRef __nullable document)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the CFTypeID for CGPDFDocumentRefs. */

CG_EXTERN CFTypeID CGPDFDocumentGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* The following functions are deprecated in favor of the CGPDFPage API. */

/* DEPRECATED; return the media box of page number `page' in `document'.
   CGRectNull is returned if cannot find `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetMediaBox(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

/* DEPRECATED; return the crop box of page number `page' in `document'.
   CGRectNull is returned if cannot find `page' in `document'. */


CG_EXTERN CGRect CGPDFDocumentGetCropBox(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

/* DEPRECATED; return the bleed box of page number `page' in `document'.
   CGRectNull is returned if cannot find `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetBleedBox(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

/* DEPRECATED; return the trim box of page number `page' in `document'.
   CGRectNull is returned if cannot find `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetTrimBox(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

/* DEPRECATED; return the art box of page number `page' in `document'.
  CGRectNull is returned if cannot find `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetArtBox(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

/* DEPRECATED; return the rotation angle (in degrees) of page number `page'
   in `document'. 0 if if cannot find `page' in `document'.*/

CG_EXTERN int CGPDFDocumentGetRotationAngle(CGPDFDocumentRef __nullable document,
    int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFDOCUMENT_H_ */
// ==========  CoreGraphics.framework/Headers/CGFont.h
/* CoreGraphics - CGFont.h
   Copyright (c) 1999-2012 Apple Inc.
   All rights reserved. */

#ifndef CGFONT_H_
#define CGFONT_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

/* The type used to represent a CoreGraphics font. */

typedef struct CGFont *CGFontRef;

/* A type to represent indexes in a CGFontRef. */

typedef unsigned short CGFontIndex;

/* A type to represent glyph identifiers in a CGFontRef. */

typedef CGFontIndex CGGlyph;

/* The format of a PostScript font subset. Type1 is documented in "Adobe
   Type 1 Font Format"; Type3 in "PostScript Language Reference, 3rd ed."
   and Type42 in "Adobe Technical Note 5012, The Type 42 Font Format
   Specification". */

typedef CF_ENUM(int32_t, CGFontPostScriptFormat) {
    kCGFontPostScriptFormatType1 = 1,
    kCGFontPostScriptFormatType3 = 3,
    kCGFontPostScriptFormatType42 = 42
};

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* The maximum allowed value of a CGFontIndex. Always <= USHRT_MAX - 1. */
static const CGFontIndex kCGFontIndexMax = ((1 << 16) - 2);

/* A value representing an invalid CGFontIndex. Always <= USHRT_MAX. */
static const CGFontIndex kCGFontIndexInvalid = ((1 << 16) - 1);

  /* The maximum allowed value of a CGGlyph. */
static const CGFontIndex kCGGlyphMax = kCGFontIndexMax;

/* Return the CFTypeID for CGFontRefs. */

CG_EXTERN CFTypeID CGFontGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a CGFontRef using `platformFontReference', a pointer to a
   platform-specific font reference. For MacOS X, `platformFontReference'
   should be a pointer to an ATSFontRef. */

CG_EXTERN CGFontRef __nullable CGFontCreateWithPlatformFont(
    void * __nullable platformFontReference)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_6,
                                __IPHONE_NA, __IPHONE_NA);

/* Return the font defined by the data provided by `provider', or NULL if
   the font can't be created. */

CG_EXTERN CGFontRef __nullable CGFontCreateWithDataProvider(
    CGDataProviderRef __nullable provider)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the font identified by `name', corresponding to the font's
   PostScript name or its full name, or NULL if the font can't be
   created. */

CG_EXTERN CGFontRef __nullable CGFontCreateWithFontName(
    CFStringRef __nullable name)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a font based on `font' with the variation specification dictionary
   `variations' applied to `font'. A variation specification dictionary
   contains keys corresponding the variation axis names of the font. Each
   key is a variation axis name; the value for each key is the value
   specified for that particular variation axis represented as a
   CFNumberRef. If a variation axis name is not specified in `variations',
   then the current value from `font' is used. */

CG_EXTERN CGFontRef __nullable CGFontCreateCopyWithVariations(
    CGFontRef __nullable font, CFDictionaryRef __nullable variations)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Equivalent to `CFRetain(font)', except it doesn't crash (as CFRetain
   does) if `font' is NULL. */

CG_EXTERN CGFontRef __nullable CGFontRetain(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(font)', except it doesn't crash (as CFRelease
   does) if `font' is NULL. */

CG_EXTERN void CGFontRelease(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of glyphs in `font'. */

CG_EXTERN size_t CGFontGetNumberOfGlyphs(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the glyph space units/em for `font'. */

CG_EXTERN int CGFontGetUnitsPerEm(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the PostScript name of `font'. */

CG_EXTERN CFStringRef __nullable CGFontCopyPostScriptName(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the "full name" of `font'. */

CG_EXTERN CFStringRef __nullable CGFontCopyFullName(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the ascent of `font'. The ascent is the maximum distance above the
   baseline of glyphs in a font. The value is specified in glyph space
   units. */

CG_EXTERN int CGFontGetAscent(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the descent of `font'. The descent is the maximum distance below
   the baseline of glyphs in a font. The value is specified in glyph space
   units. */

CG_EXTERN int CGFontGetDescent(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the leading of `font'. The leading is the spacing between
   consecutive lines of text in a font. The value is specified in glyph
   space units. */

CG_EXTERN int CGFontGetLeading(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the cap height of `font'. The cap height is the distance above the
   baseline of the top of flat capital letters of glyphs in a font. The
   value is specified in glyph space units. */

CG_EXTERN int CGFontGetCapHeight(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the x-height of `font'. The x-height is the distance above the
   baseline of the top of flat, non-ascending lowercase letters (such as
   "x") of glyphs in a font. The value is specified in glyph space units. */

CG_EXTERN int CGFontGetXHeight(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the font bounding box of `font'. The font bounding box is the
   union of all of the bounding boxes for all the glyphs in a font. The
   value is specified in glyph space units. */

CG_EXTERN CGRect CGFontGetFontBBox(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the italic angle of `font', measured in degrees counter-clockwise
   from the vertical. */

CG_EXTERN CGFloat CGFontGetItalicAngle(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the thickness of the dominant vertical stems of glyphs in `font'.
   The value is specified in glyph space units. */

CG_EXTERN CGFloat CGFontGetStemV(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return an array of the variation axis dictionaries for `font'. Each
   variation axis dictionary contains values for the variation axis keys
   listed below. This function returns NULL if `font' doesn't support
   variations. */

CG_EXTERN CFArrayRef __nullable CGFontCopyVariationAxes(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the variation specification dictionary from `font'. This
   dictionary contains keys corresponding the variation axis names of the
   font. Each key is a variation axis name; the value for each key is the
   value specified for that particular variation axis represented as a
   CFNumberRef. This function returns NULL if `font' doesn't support
   variations. */

CG_EXTERN CFDictionaryRef __nullable CGFontCopyVariations(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Get the advance of each glyph in `glyphs', an array of `count' glyphs,
   and return it in the corresponding entry of `advances', an array of
   `count' integers. The advances are specified in glyph space. Returns
   false if advances can't be retrieved for any reason; true otherwise. */

CG_EXTERN bool CGFontGetGlyphAdvances(CGFontRef __nullable font,
    const CGGlyph *  glyphs, size_t count, int *  advances)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Get the bounding box of each glyph in `glyphs', an array of `count'
   glyphs, and return it in the corresponding entry of `bboxes', an array of
   `count' rectangles. The bounding boxes are specified in glyph space.
   Returns false if bounding boxes can't be retrieved for any reason; true
   otherwise. */

CG_EXTERN bool CGFontGetGlyphBBoxes(CGFontRef __nullable font,
    const CGGlyph *  glyphs, size_t count, CGRect *  bboxes)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the glyph associated with `name' in `font'. If `name' isn't found
   in the font, return 0. */

CG_EXTERN CGGlyph CGFontGetGlyphWithGlyphName(
    CGFontRef __nullable font, CFStringRef __nullable name)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the glyph name of `glyph' in `font', or NULL if `glyph' does not
   appear in `font'. */

CG_EXTERN CFStringRef __nullable CGFontCopyGlyphNameForGlyph(
    CGFontRef __nullable font, CGGlyph glyph)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return true if a subset in the PostScript format `format' can be created
   for `font'; false otherwise. */

CG_EXTERN bool CGFontCanCreatePostScriptSubset(CGFontRef __nullable font,
    CGFontPostScriptFormat format)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a subset of `font' named `subsetName' in the PostScript format
   `format'. The subset will contain the glyphs specified by `glyphs', an
   array of `count' CGGlyphs. If non-NULL, `encoding' specifies the default
   encoding for the subset. */

CG_EXTERN CFDataRef __nullable CGFontCreatePostScriptSubset(
    CGFontRef __nullable font, CFStringRef __nullable subsetName,
    CGFontPostScriptFormat format, const CGGlyph * __nullable glyphs,
    size_t count, const CGGlyph encoding[256])
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return a PostScript encoding of `font' containing glyphs in
   `encoding'. */

CG_EXTERN CFDataRef __nullable CGFontCreatePostScriptEncoding(
    CGFontRef __nullable font, const CGGlyph encoding[256])
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return an array of font table tags in `font'. Each entry in the array is
   a four-byte value representing a single TrueType or OpenType font table
   tag. */

CG_EXTERN CFArrayRef __nullable CGFontCopyTableTags(CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the table in `font' corresponding to `tag', or NULL if no such
   table exists. */

CG_EXTERN CFDataRef __nullable CGFontCopyTableForTag(
    CGFontRef __nullable font, uint32_t tag)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/*** Keys for the font variation axis dictionary. ***/

/* The key used to obtain the variation axis name from a variation axis
   dictionary. The value obtained with this key is a CFStringRef specifying
   the name of the variation axis. */

CG_EXTERN const CFStringRef  kCGFontVariationAxisName
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The key used to obtain the minimum variation axis value from a variation
   axis dictionary. The value obtained with this key is a CFNumberRef
   specifying the minimum value of the variation axis. */

CG_EXTERN const CFStringRef  kCGFontVariationAxisMinValue
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The key used to obtain the maximum variation axis value from a variation
   axis dictionary. The value obtained with this key is a CFNumberRef
   specifying the maximum value of the variation axis. */

CG_EXTERN const CFStringRef  kCGFontVariationAxisMaxValue
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The key used to obtain the default variation axis value from a variation
   axis dictionary. The value obtained with this key is a CFNumberRef
   specifying the default value of the variation axis. */

CG_EXTERN const CFStringRef  kCGFontVariationAxisDefaultValue
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Obsolete; don't use these. */

typedef CF_ENUM (int32_t, CGGlypDeprecatedEnum) {
  CGGlyphMin __CG_DEPRECATED_ENUMERATOR,
  CGGlyphMax __CG_DEPRECATED_ENUMERATOR
};

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGFONT_H_ */
// ==========  CoreGraphics.framework/Headers/CGShading.h
/* CoreGraphics - CGShading.h
   Copyright (c) 2001-2011 Apple Inc.
   All rights reserved. */

#ifndef CGSHADING_H_
#define CGSHADING_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGShading *CGShadingRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFunction.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Return the CFTypeID for CGShadingRefs. */

CG_EXTERN CFTypeID CGShadingGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a shading defining a color blend which varies along a linear axis
   between two endpoints and extends indefinitely perpendicular to that
   axis. The shading may optionally extend beyond either endpoint by
   continuing the boundary colors indefinitely. The color values are
   specified in the color space `space'. The starting point of the axis is
   `start' and the ending point of the axis is `end', both specified in the
   shading's target coordinate space. The shading function, specified by
   `function', is a 1-in, N-out function, where N is one more (for alpha)
   than the number of color components in the shading's color space. The
   input value 0 corresponds to the color at the starting point of the
   shading; the input value 1 corresponds to the color at the ending point
   of the shading. If `extendStart' is true, then the shading will extend
   beyond the starting point of the axis. If `extendEnd' is true, then the
   shading will extend beyond the ending point of the axis. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateAxial(
    CGColorSpaceRef __nullable space, CGPoint start, CGPoint end,
    CGFunctionRef __nullable function, bool extendStart, bool extendEnd)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a shading defining a color blend which varies between two circles.
   The shading may optionally extend beyond either circle by continuing the
   boundary colors. The color values are specified in the color space
   `space'. The starting circle has radius `startRadius' and is centered at
   `start', specified in the shading's target coordinate space. The ending
   circle has radius `endRadius' and is centered at `end', specified in the
   shading's target coordinate space. The shading function, specified by
   `function', is a 1-in, N-out function, where N is one more (for alpha)
   than the number of color components in the shading's color space. The
   input value 0 corresponds to the color of the starting circle; the input
   value 1 corresponds to the color of the ending circle. If `extendStart'
   is true, then the shading will extend beyond the starting circle. If
   `extendEnd' is true, then the shading will extend beyond the ending
   circle. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateRadial(
    CGColorSpaceRef __nullable space,
    CGPoint start, CGFloat startRadius, CGPoint end, CGFloat endRadius,
    CGFunctionRef __nullable function, bool extendStart, bool extendEnd)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRetain(shading)', except it doesn't crash (as CFRetain
   does) if `shading' is NULL. */

CG_EXTERN CGShadingRef __nullable CGShadingRetain(CGShadingRef __nullable shading)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRelease(shading)', except it doesn't crash (as CFRelease
   does) if `shading' is NULL. */

CG_EXTERN void CGShadingRelease(CGShadingRef __nullable shading)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGSHADING_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFContentStream.h
/* CoreGraphics - CGPDFContentStream.h
   Copyright (c) 2004-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFCONTENTSTREAM_H_
#define CGPDFCONTENTSTREAM_H_

typedef struct CGPDFContentStream *CGPDFContentStreamRef;

#include <CoreGraphics/CGPDFPage.h>

CF_IMPLICIT_BRIDGING_ENABLED

/* Create a content stream from `page'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithPage(
  CGPDFPageRef page) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a content stream from `stream'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithStream(
  CGPDFStreamRef stream, CGPDFDictionaryRef streamResources,
  CGPDFContentStreamRef parent)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Increment the retain count of `cs'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamRetain(
  CGPDFContentStreamRef cs) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Decrement the retain count of `cs'. */

CG_EXTERN void CGPDFContentStreamRelease(CGPDFContentStreamRef cs)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the array of CGPDFStreamRefs comprising the entire content stream
   of `cs'. */

CG_EXTERN CFArrayRef CGPDFContentStreamGetStreams(CGPDFContentStreamRef cs)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the resource named `name' in category `category' of the resource
   dictionaries of `cs'. */

CG_EXTERN CGPDFObjectRef CGPDFContentStreamGetResource(
  CGPDFContentStreamRef cs, const char *category, const char *name)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFCONTENTSTREAM_H_ */
// ==========  CoreGraphics.framework/Headers/CGAffineTransform.h
/* CoreGraphics - CGAffineTransform.h
   Copyright (c) 1998-2011 Apple Inc.
   All rights reserved. */

#ifndef CGAFFINETRANSFORM_H_
#define CGAFFINETRANSFORM_H_

typedef struct CGAffineTransform CGAffineTransform;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>

CF_IMPLICIT_BRIDGING_ENABLED

struct CGAffineTransform {
  CGFloat a, b, c, d;
  CGFloat tx, ty;
};

/* The identity transform: [ 1 0 0 1 0 0 ]. */

CG_EXTERN const CGAffineTransform CGAffineTransformIdentity
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the transform [ a b c d tx ty ]. */

CG_EXTERN CGAffineTransform CGAffineTransformMake(CGFloat a, CGFloat b,
  CGFloat c, CGFloat d, CGFloat tx, CGFloat ty)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which translates by `(tx, ty)':
     t' = [ 1 0 0 1 tx ty ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeTranslation(CGFloat tx,
  CGFloat ty) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which scales by `(sx, sy)':
     t' = [ sx 0 0 sy 0 0 ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeScale(CGFloat sx, CGFloat sy)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which rotates by `angle' radians:
     t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] */

CG_EXTERN CGAffineTransform CGAffineTransformMakeRotation(CGFloat angle)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `t' is the identity transform, false otherwise. */

CG_EXTERN bool CGAffineTransformIsIdentity(CGAffineTransform t)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Translate `t' by `(tx, ty)' and return the result:
     t' = [ 1 0 0 1 tx ty ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformTranslate(CGAffineTransform t,
  CGFloat tx, CGFloat ty) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Scale `t' by `(sx, sy)' and return the result:
     t' = [ sx 0 0 sy 0 0 ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformScale(CGAffineTransform t,
  CGFloat sx, CGFloat sy) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Rotate `t' by `angle' radians and return the result:
     t' =  [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] * t */

CG_EXTERN CGAffineTransform CGAffineTransformRotate(CGAffineTransform t,
  CGFloat angle) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Invert `t' and return the result. If `t' has zero determinant, then `t'
   is returned unchanged. */

CG_EXTERN CGAffineTransform CGAffineTransformInvert(CGAffineTransform t)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Concatenate `t2' to `t1' and return the result:
     t' = t1 * t2 */

CG_EXTERN CGAffineTransform CGAffineTransformConcat(CGAffineTransform t1,
  CGAffineTransform t2) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `t1' and `t2' are equal, false otherwise. */

CG_EXTERN bool CGAffineTransformEqualToTransform(CGAffineTransform t1,
  CGAffineTransform t2) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' by `t' and return the result:
     p' = p * t
   where p = [ x y 1 ]. */

CG_EXTERN CGPoint CGPointApplyAffineTransform(CGPoint point,
  CGAffineTransform t) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Transform `size' by `t' and return the result:
     s' = s * t
   where s = [ width height 0 ]. */

CG_EXTERN CGSize CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Transform `rect' by `t' and return the result. Since affine transforms do
   not preserve rectangles in general, this function returns the smallest
   rectangle which contains the transformed corner points of `rect'. If `t'
   consists solely of scales, flips and translations, then the returned
   rectangle coincides with the rectangle constructed from the four
   transformed corners. */

CG_EXTERN CGRect CGRectApplyAffineTransform(CGRect rect, CGAffineTransform t)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Definitions of inline functions. ***/

CG_INLINE CGAffineTransform
__CGAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d,
  CGFloat tx, CGFloat ty)
{
  CGAffineTransform t;
  t.a = a; t.b = b; t.c = c; t.d = d; t.tx = tx; t.ty = ty;
  return t;
}
#define CGAffineTransformMake __CGAffineTransformMake

CG_INLINE CGPoint
__CGPointApplyAffineTransform(CGPoint point, CGAffineTransform t)
{
  CGPoint p;
  p.x = (CGFloat)((double)t.a * point.x + (double)t.c * point.y + t.tx);
  p.y = (CGFloat)((double)t.b * point.x + (double)t.d * point.y + t.ty);
  return p;
}
#define CGPointApplyAffineTransform __CGPointApplyAffineTransform

CG_INLINE CGSize
__CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
{
  CGSize s;
  s.width = (CGFloat)((double)t.a * size.width + (double)t.c * size.height);
  s.height = (CGFloat)((double)t.b * size.width + (double)t.d * size.height);
  return s;
}
#define CGSizeApplyAffineTransform __CGSizeApplyAffineTransform

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGAFFINETRANSFORM_H_ */
// ==========  CoreGraphics.framework/Headers/CGColorSpace.h
/* CoreGraphics - CGColorSpace.h
   Copyright (c) 1999-2013 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORSPACE_H_
#define CGCOLORSPACE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGColorSpace *CGColorSpaceRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h>

CF_IMPLICIT_BRIDGING_ENABLED

/* Color rendering intents. */

typedef CF_ENUM (int32_t, CGColorRenderingIntent) {
    kCGRenderingIntentDefault,
    kCGRenderingIntentAbsoluteColorimetric,
    kCGRenderingIntentRelativeColorimetric,
    kCGRenderingIntentPerceptual,
    kCGRenderingIntentSaturation
};

/* The model of a color space. */

typedef CF_ENUM (int32_t,  CGColorSpaceModel) {
    kCGColorSpaceModelUnknown = -1,
    kCGColorSpaceModelMonochrome,
    kCGColorSpaceModelRGB,
    kCGColorSpaceModelCMYK,
    kCGColorSpaceModelLab,
    kCGColorSpaceModelDeviceN,
    kCGColorSpaceModelIndexed,
    kCGColorSpaceModelPattern
};

CF_ASSUME_NONNULL_BEGIN

/* The name of the "Generic" Gray color space. It is a legacy
   color space so use it only if you definitely know that you
   need it. If you need just a reasonable monochrome color space,
   please use Generic Gray Gamma 2.2, i.e. use
   kCGColorSpaceGenericGrayGamma2_2 name instead of
   kCGColorSpaceGenericGray. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGray
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_9_0);

/* The name of the "Generic" RGB color space. It is a legacy
   color space so use it only if you definitely know that you
   need it. If you need just a reasonable RGB color space,
   please use sRGB, i.e. use kCGColorSpaceSRGB name
   instead of kCGColorSpaceGenericRGB. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGB
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_9_0);

/* The name of the "Generic" CMYK color space. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericCMYK
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_8_0);
  

/* The name of the "Generic" linear RGB color space. This is the same as
   `kCGColorSpaceGenericRGB' but with a 1.0 gamma. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericRGBLinear
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_9_0);

/* The name of the Adobe RGB (1998) color space. For more information, see
  "Adobe RGB (1998) Color Image Encoding", Version 2005-05, Adobe Systems
  Inc. (http://www.adobe.com). */

CG_EXTERN const CFStringRef kCGColorSpaceAdobeRGB1998
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_8_0);

/* The name of the sRGB color space. The capitalization in the name, while
   strictly inaccurate, avoids interpretational ambiguity. For more
   information, see IEC 61966-2-1 (1999-10): "Multimedia systems and
   equipment - Colour measurement and management - Part 2-1: Colour
   management - Default RGB colour space - sRGB". */

CG_EXTERN const CFStringRef kCGColorSpaceSRGB
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_8_0);

/* The "Generic" gray color space with γ = 2.2. */

CG_EXTERN const CFStringRef kCGColorSpaceGenericGrayGamma2_2
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_8_0);

CG_EXTERN const CFStringRef kCGColorSpaceGenericXYZ
  CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceACESCGLinear
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceITUR_709
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceITUR_2020
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CG_EXTERN const CFStringRef kCGColorSpaceROMMRGB
CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);


/* Create a DeviceGray color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateDeviceGray(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceRGB color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateDeviceRGB(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a DeviceCMYK color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateDeviceCMYK(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a calibrated gray color space. `whitePoint' is an array of 3
   numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
   the diffuse white point. `blackPoint' is an array of 3 numbers specifying
   the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `gamma' defines the gamma for the gray component. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateCalibratedGray(const CGFloat
  whitePoint[3], const CGFloat blackPoint[3], CGFloat gamma)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a calibrated RGB color space. `whitePoint' is an array of 3
   numbers specifying the tristimulus value, in the CIE 1931 XYZ-space, of
   the diffuse white point. `blackPoint' is an array of 3 numbers specifying
   the tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `gamma' is an array of 3 numbers specifying the gamma for the red, green,
   and blue components of the color space. `matrix' is an array of 9 numbers
   specifying the linear interpretation of the gamma-modified RGB values of
   the color space with respect to the final XYZ representation. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateCalibratedRGB(const CGFloat
  whitePoint[3], const CGFloat blackPoint[3], const CGFloat gamma[3],
  const CGFloat matrix[9]) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
    
/* Create an L*a*b* color space. `whitePoint' is an array of 3 numbers
   specifying the tristimulus value, in the CIE 1931 XYZ-space, of the
   diffuse white point. `blackPoint' is an array of 3 numbers specifying the
   tristimulus value, in CIE 1931 XYZ-space, of the diffuse black point.
   `range' is an array of four numbers specifying the range of valid values
   for the a* and b* components of the color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateLab(const CGFloat whitePoint[3],
  const CGFloat blackPoint[3], const CGFloat range[4])
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an ICC-based color space using the ICC profile specified by
   `data'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateWithICCProfile(CFDataRef __nullable data)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Create an ICC-based color space. `nComponents' specifies the number of
   color components in the color space defined by the ICC profile data. This
   must match the number of components actually in the ICC profile, and must
   be 1, 3, or 4. `range' is an array of 2*nComponents numbers specifying
   the minimum and maximum valid values of the corresponding color
   components, so that for color component k, range[2*k] <= c[k] <=
   range[2*k+1], where c[k] is the k'th color component. `profile' is a data
   provider specifying the ICC profile. `alternate' specifies an alternate
   color space to be used in case the ICC profile is not supported. It must
   have `nComponents' color components. If `alternate' is NULL, then the
   color space used will be DeviceGray, DeviceRGB, or DeviceCMYK, depending
   on whether `nComponents' is 1, 3, or 4, respectively. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateICCBased(size_t nComponents,
  const CGFloat * __nullable range, CGDataProviderRef __nullable profile,
  CGColorSpaceRef __nullable alternate)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an indexed color space. A sample value in an indexed color space
   is treated as an index into the color table of the color space. `base'
   specifies the base color space in which the values in the color table are
   to be interpreted. `lastIndex' is an integer which specifies the maximum
   valid index value; it must be less than or equal to 255. `colorTable' is
   an array of m * (lastIndex + 1) bytes, where m is the number of color
   components in the base color space. Each byte is an unsigned integer in
   the range 0 to 255 that is scaled to the range of the corresponding color
   component in the base color space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateIndexed(CGColorSpaceRef __nullable baseSpace,
  size_t lastIndex, const unsigned char * __nullable colorTable)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a pattern color space. `baseSpace' is the underlying color space
   of the pattern color space. For colored patterns, `baseSpace' should be
   NULL; for uncolored patterns, `baseSpace' specifies the color space of
   colors which will be painted through the pattern. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreatePattern(CGColorSpaceRef __nullable baseSpace)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a color space using `ref', a platform-specific color space
   reference. For MacOS X, `ref' should be a ColorSyncProfileRef. */

CG_EXTERN CGColorSpaceRef __nullable
  CGColorSpaceCreateWithPlatformColorSpace(const void * __nullable ref)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_9_0);

/* Create a color space using `name' as the identifier for the color
   space. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceCreateWithName(CFStringRef __nullable name)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Equivalent to `CFRetain(space)', except it doesn't crash (as CFRetain
   does) if `space' is NULL. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceRetain(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(space)', except it doesn't crash (as CFRelease
   does) if `space' is NULL. */

CG_EXTERN void CGColorSpaceRelease(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the name used to create the color space `space', or NULL if the
   color space was not created using `CGColorSpaceCreateWithName'. */

CG_EXTERN CFStringRef __nullable CGColorSpaceCopyName(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Return the CFTypeID for CGColorSpaces. */

CG_EXTERN CFTypeID CGColorSpaceGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the number of color components in the color space `space'. */

CG_EXTERN size_t CGColorSpaceGetNumberOfComponents(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the color space model of `space'. */

CG_EXTERN CGColorSpaceModel CGColorSpaceGetModel(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the base color space of `space' if `space' is a pattern or indexed
   color space; otherwise, return NULL. To determine whether a color space
   is an indexed or pattern color space, use `CGColorSpaceGetModel'. */

CG_EXTERN CGColorSpaceRef __nullable CGColorSpaceGetBaseColorSpace(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the number of entries in the color table of `space' if `space' is
   an indexed color space; otherwise, return 0. To determine whether a color
   space is an indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN size_t CGColorSpaceGetColorTableCount(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Copy the entries in the color table of `space' to `table' if `space' is
   an indexed color space; otherwise, do nothing. The array pointed to by
   `table' should be at least as large as the number of entries in the color
   table; the returned data is in the same format as that passed to
   `CGColorSpaceCreateIndexed'. To determine whether a color space is an
   indexed color space, use `CGColorSpaceGetModel'. */

CG_EXTERN void CGColorSpaceGetColorTable(CGColorSpaceRef __nullable space,
  uint8_t * __nullable table) CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a copy of the ICC profile of `space', or NULL if the color space
   doesn't have an ICC profile. */

CG_EXTERN CFDataRef __nullable CGColorSpaceCopyICCProfile(CGColorSpaceRef __nullable space)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORSPACE_H_ */
// ==========  CoreGraphics.framework/Headers/CGGradient.h
/* CoreGraphics - CGGradient.h
   Copyright (c) 2006-2011 Apple Inc.
   All rights reserved. */

#ifndef CGGRADIENT_H_
#define CGGRADIENT_H_

typedef struct CGGradient *CGGradientRef;


#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef CF_OPTIONS (uint32_t, CGGradientDrawingOptions) {
  kCGGradientDrawsBeforeStartLocation = (1 << 0),
  kCGGradientDrawsAfterEndLocation = (1 << 1)
};

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGContext.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* A CGGradient defines a transition between colors. The transition is
   defined over a range from 0 to 1 inclusive. A gradient specifies a color
   at location 0, one at location 1, and possibly additional colors assigned
   to locations between 0 and 1.

   A CGGradient has a color space. When a gradient is created, all colors
   specified are converted to that color space, and interpolation of colors
   occurs using the components of that color space. See the documentation of
   each creation function for more details. */

/* Return the CFTypeID for CGGradients. */

CG_EXTERN CFTypeID CGGradientGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Creates a gradient by pairing the color components provided in
   `components' with locations provided in `locations'. If `locations' is
   NULL, the first color in `colors' will be at location 0, the last color
   in `colors' will be at location 1, and intervening colors will be at
   equal intervals in between. Otherwise, each location in `locations'
   should be a CGFloat between 0 and 1. Each set of color components should
   specify a color in the color space `space' (which may not be a pattern or
   indexed color space). The number of locations is specified by `count';
   the number of color components is the product of `count' and the number
   of color components of `space'. If no color is provided for 0 or 1, the
   gradient will use the color provided at the locations closest to 0 and 1
   for those values. */

CG_EXTERN CGGradientRef __nullable CGGradientCreateWithColorComponents(
    CGColorSpaceRef __nullable space, const CGFloat * __nullable components,
    const CGFloat * __nullable locations, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Creates a gradient by pairing the colors provided in `colors' with the
   locations provided in `locations'. `colors' should be a non-empty array
   of CGColor objects. The colors may be in any color space other than a
   pattern or indexed color space. If `space' is non-NULL, each color will
   be converted to that color space and the gradient will drawn in that
   space; otherwise, each color will be converted to and drawn in the
   "Generic" RGB color space. If `space' is specified, it may not be a
   pattern or indexed color space. If `locations' is NULL, the first color
   in `colors' will be at location 0, the last color in `colors' will be at
   location 1, and intervening colors will be at equal intervals in between.
   Otherwise, each location in `locations' should be a CGFloat between 0 and
   1; the array of locations should should contain the same number of items
   as `colors'. If no color is provided for 0 or 1, the gradient will use
   the color provided at the locations closest to 0 and 1 for those
   values. */

CG_EXTERN CGGradientRef __nullable CGGradientCreateWithColors(
    CGColorSpaceRef __nullable space, CFArrayRef __nullable colors,
    const CGFloat * __nullable locations)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Equivalent to `CFRetain' except that it doesn't crash (as `CFRetain'
   does) if `gradient' is NULL. */

CG_EXTERN CGGradientRef __nullable CGGradientRetain(
    CGGradientRef __nullable gradient)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Equivalent to `CFRelease' except that it doesn't crash (as `CFRelease'
   does) if `gradient' is NULL. */

CG_EXTERN void CGGradientRelease(CGGradientRef __nullable gradient)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGGRADIENT_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFString.h
/* CoreGraphics - CGPDFString.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFSTRING_H_
#define CGPDFSTRING_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFString *CGPDFStringRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Return the length of `string'. */

CG_EXTERN size_t CGPDFStringGetLength(CGPDFStringRef __nullable string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a pointer to the bytes of `string'. */

CG_EXTERN const unsigned char * __nullable CGPDFStringGetBytePtr(
    CGPDFStringRef __nullable string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a CFString representing `string' as a "text string". See Section
   3.8.1 "Text Strings", PDF Reference: Adobe PDF version 1.6 (5th ed.) for
   more information. */

CG_EXTERN CFStringRef __nullable CGPDFStringCopyTextString(
    CGPDFStringRef __nullable string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Convert `string' to a CFDate. See Section 3.8.3 "Dates", PDF Reference:
   Adobe PDF version 1.6 (5th ed.) for more information. */

CG_EXTERN CFDateRef __nullable CGPDFStringCopyDate(
    CGPDFStringRef __nullable string)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFSTRING_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFDictionary.h
/* CoreGraphics - CGPDFDictionary.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFDICTIONARY_H_
#define CGPDFDICTIONARY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFDictionary *CGPDFDictionaryRef;

#include <CoreGraphics/CGPDFArray.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Return the number of entries in `dictionary'. */

CG_EXTERN size_t CGPDFDictionaryGetCount(CGPDFDictionaryRef __nullable dict)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and return the result
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetObject(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFObjectRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a
   boolean, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetBoolean(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFBoolean * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's an
   integer, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetInteger(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFInteger * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a number
   (real or integer), return the result in `value'. Return true on success;
   false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetNumber(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFReal * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a name,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetName(CGPDFDictionaryRef __nullable dict,
    const char *  key, const char * __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a string,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetString(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFStringRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's an array,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetArray(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFArrayRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a
   dictionary, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetDictionary(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFDictionaryRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a stream,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetStream(CGPDFDictionaryRef __nullable dict,
    const char *  key, CGPDFStreamRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* The callback for `CGPDFDictionaryApplyFunction'. `key' is the current
   key, `value' is the value for `key', and `info' is the parameter passed
   to `CGPDFDictionaryApplyFunction'. */

typedef void (*CGPDFDictionaryApplierFunction)(const char *  key,
    CGPDFObjectRef  value, void * __nullable info);

/* Enumerate all of the keys in `dict', calling `function' once for each
   key/value pair. Passes the current key, the associated value, and `info'
   to `function'. */

CG_EXTERN void CGPDFDictionaryApplyFunction(CGPDFDictionaryRef __nullable dict,
    CGPDFDictionaryApplierFunction __nullable function, void * __nullable info)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFDICTIONARY_H_ */
// ==========  CoreGraphics.framework/Headers/CGContext.h
/* CoreGraphics - CGContext.h
   Copyright (c) 2000-2012 Apple Inc.
   All rights reserved. */

#ifndef CGCONTEXT_H_
#define CGCONTEXT_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGContext *CGContextRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreGraphics/CGColor.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGGradient.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGPattern.h>
#include <CoreGraphics/CGPDFDocument.h>
#include <CoreGraphics/CGShading.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Drawing modes for paths. */

typedef CF_ENUM (int32_t, CGPathDrawingMode) {
  kCGPathFill,
  kCGPathEOFill,
  kCGPathStroke,
  kCGPathFillStroke,
  kCGPathEOFillStroke
};

/* Drawing modes for text. */

typedef CF_ENUM (int32_t, CGTextDrawingMode) {
  kCGTextFill,
  kCGTextStroke,
  kCGTextFillStroke,
  kCGTextInvisible,
  kCGTextFillClip,
  kCGTextStrokeClip,
  kCGTextFillStrokeClip,
  kCGTextClip
};

/* Text encodings. */

typedef CF_ENUM (int32_t, CGTextEncoding) {
  kCGEncodingFontSpecific,
  kCGEncodingMacRoman
} CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_2_0, __IPHONE_7_0);

/* Interpolation quality. */

typedef CF_ENUM (int32_t, CGInterpolationQuality) {
  kCGInterpolationDefault = 0,  /* Let the context decide. */
  kCGInterpolationNone = 1,     /* Never interpolate. */
  kCGInterpolationLow = 2,      /* Low quality, fast interpolation. */
  kCGInterpolationMedium = 4,   /* Medium quality, slower than kCGInterpolationLow. */
  kCGInterpolationHigh = 3      /* Highest quality, slower than kCGInterpolationMedium. */
};

/* Blend modes.

   The blend modes from kCGBlendModeNormal to kCGBlendModeLuminosity are
   supported in Mac OS X 10.4 and later. The Porter-Duff blend modes (from
   kCGBlendModeClear to kCGBlendModePlusLighter) are supported in Mac OS X
   10.5 and later. The names of the Porter-Duff blend modes are historical.

   Note that the Porter-Duff blend modes are not necessarily supported in
   every context. In particular, they are only guaranteed to work in
   bitmap-based contexts, such as those created by CGBitmapContextCreate. It
   is your responsibility to make sure that they do what you want when you
   use them in a CGContext. */

typedef CF_ENUM (int32_t, CGBlendMode) {
    /* Available in Mac OS X 10.4 & later. */
    kCGBlendModeNormal,
    kCGBlendModeMultiply,
    kCGBlendModeScreen,
    kCGBlendModeOverlay,
    kCGBlendModeDarken,
    kCGBlendModeLighten,
    kCGBlendModeColorDodge,
    kCGBlendModeColorBurn,
    kCGBlendModeSoftLight,
    kCGBlendModeHardLight,
    kCGBlendModeDifference,
    kCGBlendModeExclusion,
    kCGBlendModeHue,
    kCGBlendModeSaturation,
    kCGBlendModeColor,
    kCGBlendModeLuminosity,

    /* Available in Mac OS X 10.5 & later. R, S, and D are, respectively,
       premultiplied result, source, and destination colors with alpha; Ra,
       Sa, and Da are the alpha components of these colors.

       The Porter-Duff "source over" mode is called `kCGBlendModeNormal':
         R = S + D*(1 - Sa)

       Note that the Porter-Duff "XOR" mode is only titularly related to the
       classical bitmap XOR operation (which is unsupported by
       CoreGraphics). */

    kCGBlendModeClear,                  /* R = 0 */
    kCGBlendModeCopy,                   /* R = S */
    kCGBlendModeSourceIn,               /* R = S*Da */
    kCGBlendModeSourceOut,              /* R = S*(1 - Da) */
    kCGBlendModeSourceAtop,             /* R = S*Da + D*(1 - Sa) */
    kCGBlendModeDestinationOver,        /* R = S*(1 - Da) + D */
    kCGBlendModeDestinationIn,          /* R = D*Sa */
    kCGBlendModeDestinationOut,         /* R = D*(1 - Sa) */
    kCGBlendModeDestinationAtop,        /* R = S*(1 - Da) + D*Sa */
    kCGBlendModeXOR,                    /* R = S*(1 - Da) + D*(1 - Sa) */
    kCGBlendModePlusDarker,             /* R = MAX(0, (1 - D) + (1 - S)) */
    kCGBlendModePlusLighter             /* R = MIN(1, S + D) */
};

/* Return the CFTypeID for CGContextRefs. */

CG_EXTERN CFTypeID CGContextGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/** Graphics state functions. **/

/* Push a copy of the current graphics state onto the graphics state stack.
   Note that the path is not considered part of the graphics state, and is
   not saved. */

CG_EXTERN void CGContextSaveGState(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Restore the current graphics state from the one on the top of the
   graphics state stack, popping the graphics state stack in the process. */

CG_EXTERN void CGContextRestoreGState(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Coordinate space transformations. **/

/* Scale the current graphics state's transformation matrix (the CTM) by
   `(sx, sy)'. */

CG_EXTERN void CGContextScaleCTM(CGContextRef __nullable c,
    CGFloat sx, CGFloat sy)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Translate the current graphics state's transformation matrix (the CTM) by
   `(tx, ty)'. */

CG_EXTERN void CGContextTranslateCTM(CGContextRef __nullable c,
    CGFloat tx, CGFloat ty)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Rotate the current graphics state's transformation matrix (the CTM) by
   `angle' radians. */

CG_EXTERN void CGContextRotateCTM(CGContextRef __nullable c, CGFloat angle)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Concatenate the current graphics state's transformation matrix (the CTM)
   with the affine transform `transform'. */

CG_EXTERN void CGContextConcatCTM(CGContextRef __nullable c,
    CGAffineTransform transform)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the current graphics state's transformation matrix. Returns 
   CGAffineTransformIdentity in case of inavlid context. */

CG_EXTERN CGAffineTransform CGContextGetCTM(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Drawing attribute functions. **/

/* Set the line width in the current graphics state to `width'. */

CG_EXTERN void CGContextSetLineWidth(CGContextRef __nullable c, CGFloat width)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the line cap in the current graphics state to `cap'. */

CG_EXTERN void CGContextSetLineCap(CGContextRef __nullable c, CGLineCap cap)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the line join in the current graphics state to `join'. */

CG_EXTERN void CGContextSetLineJoin(CGContextRef __nullable c, CGLineJoin join)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the miter limit in the current graphics state to `limit'. */

CG_EXTERN void CGContextSetMiterLimit(CGContextRef __nullable c, CGFloat limit)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the line dash patttern in the current graphics state of `c'. */

CG_EXTERN void CGContextSetLineDash(CGContextRef __nullable c, CGFloat phase,
    const CGFloat * __nullable lengths, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the path flatness parameter in the current graphics state of `c' to
   `flatness'. */

CG_EXTERN void CGContextSetFlatness(CGContextRef __nullable c, CGFloat flatness)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the alpha value in the current graphics state of `c' to `alpha'. */

CG_EXTERN void CGContextSetAlpha(CGContextRef __nullable c, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the blend mode of `context' to `mode'. */

CG_EXTERN void CGContextSetBlendMode(CGContextRef __nullable c, CGBlendMode mode)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Path construction functions. **/

/* Note that a context has a single path in use at any time: a path is not
   part of the graphics state. */

/* Begin a new path. The old path is discarded. */

CG_EXTERN void CGContextBeginPath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Start a new subpath at point `(x, y)' in the context's path. */

CG_EXTERN void CGContextMoveToPoint(CGContextRef __nullable c,
    CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Append a straight line segment from the current point to `(x, y)'. */

CG_EXTERN void CGContextAddLineToPoint(CGContextRef __nullable c,
    CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Append a cubic Bezier curve from the current point to `(x,y)', with
   control points `(cp1x, cp1y)' and `(cp2x, cp2y)'. */

CG_EXTERN void CGContextAddCurveToPoint(CGContextRef __nullable c, CGFloat cp1x,
    CGFloat cp1y, CGFloat cp2x, CGFloat cp2y, CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Append a quadratic curve from the current point to `(x, y)', with control
   point `(cpx, cpy)'. */

CG_EXTERN void CGContextAddQuadCurveToPoint(CGContextRef __nullable c,
    CGFloat cpx, CGFloat cpy, CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Close the current subpath of the context's path. */

CG_EXTERN void CGContextClosePath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Path construction convenience functions. **/

/* Add a single rect to the context's path. */

CG_EXTERN void CGContextAddRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add a set of rects to the context's path. */

CG_EXTERN void CGContextAddRects(CGContextRef __nullable c,
    const CGRect * __nullable rects, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add a set of lines to the context's path. */

CG_EXTERN void CGContextAddLines(CGContextRef __nullable c,
    const CGPoint * __nullable points, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add an ellipse inside `rect' to the current path of `context'. See the
   function `CGPathAddEllipseInRect' for more information on how the path
   for the ellipse is constructed. */

CG_EXTERN void CGContextAddEllipseInRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Add an arc of a circle to the context's path, possibly preceded by a
   straight line segment. `(x, y)' is the center of the arc; `radius' is its
   radius; `startAngle' is the angle to the first endpoint of the arc;
   `endAngle' is the angle to the second endpoint of the arc; and
   `clockwise' is 1 if the arc is to be drawn clockwise, 0 otherwise.
   `startAngle' and `endAngle' are measured in radians. */

CG_EXTERN void CGContextAddArc(CGContextRef __nullable c, CGFloat x, CGFloat y,
    CGFloat radius, CGFloat startAngle, CGFloat endAngle, int clockwise)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add an arc of a circle to the context's path, possibly preceded by a
   straight line segment. `radius' is the radius of the arc. The arc is
   tangent to the line from the current point to `(x1, y1)', and the line
   from `(x1, y1)' to `(x2, y2)'. */

CG_EXTERN void CGContextAddArcToPoint(CGContextRef __nullable c,
    CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2, CGFloat radius)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add `path' to the path of context. The points in `path' are transformed
   by the CTM of context before they are added. */

CG_EXTERN void CGContextAddPath(CGContextRef __nullable c,
    CGPathRef __nullable path)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/** Path stroking. **/

/* Replace the path in `context' with the stroked version of the path, using
   the parameters of `context' to calculate the stroked path. The resulting
   path is created such that filling it with the appropriate color will
   produce the same results as stroking the original path. You can use this
   path in the same way you can use the path of any context; for example,
   you can clip to the stroked version of a path by calling this function
   followed by a call to "CGContextClip". */

CG_EXTERN void CGContextReplacePathWithStrokedPath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Path information functions. **/

/* Return true if the path of `context' contains no elements, false
   otherwise. */

CG_EXTERN bool CGContextIsPathEmpty(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the current point of the current subpath of the path of
   `context'. */

CG_EXTERN CGPoint CGContextGetPathCurrentPoint(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the bounding box of the path of `context'. The bounding box is the
   smallest rectangle completely enclosing all points in the path, including
   control points for Bezier and quadratic curves. */

CG_EXTERN CGRect CGContextGetPathBoundingBox(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a copy of the path of `context'. The returned path is specified in
   the current user space of `context'. */

CG_EXTERN CGPathRef __nullable CGContextCopyPath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return true if `point' is contained in the current path of `context'. A
   point is contained within a context's path if it is inside the painted
   region when the path is stroked or filled with opaque colors using the
   path drawing mode `mode'. `point' is specified is user space. */

CG_EXTERN bool CGContextPathContainsPoint(CGContextRef __nullable c,
    CGPoint point, CGPathDrawingMode mode)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Path drawing functions. **/

/* Draw the context's path using drawing mode `mode'. */

CG_EXTERN void CGContextDrawPath(CGContextRef __nullable c,
    CGPathDrawingMode mode)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Path drawing convenience functions. **/

/* Fill the context's path using the winding-number fill rule. Any open
   subpath of the path is implicitly closed. */

CG_EXTERN void CGContextFillPath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill the context's path using the even-odd fill rule. Any open subpath of
   the path is implicitly closed. */

CG_EXTERN void CGContextEOFillPath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke the context's path. */

CG_EXTERN void CGContextStrokePath(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill `rect' with the current fill color. */

CG_EXTERN void CGContextFillRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill `rects', an array of `count' CGRects, with the current fill
   color. */

CG_EXTERN void CGContextFillRects(CGContextRef __nullable c,
    const CGRect * __nullable rects, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke `rect' with the current stroke color and the current linewidth. */

CG_EXTERN void CGContextStrokeRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke `rect' with the current stroke color, using `width' as the the
   line width. */

CG_EXTERN void CGContextStrokeRectWithWidth(CGContextRef __nullable c,
    CGRect rect, CGFloat width)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Clear `rect' (that is, set the region within the rect to transparent). */

CG_EXTERN void CGContextClearRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextFillEllipseInRect(CGContextRef __nullable c,
    CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Stroke an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextStrokeEllipseInRect(CGContextRef __nullable c,
    CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Stroke a sequence of line segments one after another in `context'. The
   line segments are specified by `points', an array of `count' CGPoints.
   This function is equivalent to

     CGContextBeginPath(context);
     for (k = 0; k < count; k += 2) {
       CGContextMoveToPoint(context, s[k].x, s[k].y);
       CGContextAddLineToPoint(context, s[k+1].x, s[k+1].y);
     }
     CGContextStrokePath(context); */

CG_EXTERN void CGContextStrokeLineSegments(CGContextRef __nullable c,
    const CGPoint * __nullable points, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Clipping functions. **/

/* Intersect the context's path with the current clip path and use the
   resulting path as the clip path for subsequent rendering operations. Use
   the winding-number fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextClip(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Intersect the context's path with the current clip path and use the
   resulting path as the clip path for subsequent rendering operations. Use
   the even-odd fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextEOClip(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add `mask' transformed to `rect' to the clipping area of `context'. The
   mask, which may be either an image mask or an image, is mapped into the
   specified rectangle and intersected with the current clipping area of the
   context.

   If `mask' is an image mask, then it clips in a manner identical to the
   behavior if it were used with "CGContextDrawImage": it indicates an area
   to be masked out (left unchanged) when drawing. The source samples of the
   image mask determine which points of the clipping area are changed,
   acting as an "inverse alpha": if the value of a source sample in the
   image mask is S, then the corresponding point in the current clipping
   area will be multiplied by an alpha of (1-S). (For example, if S is 1,
   then the point in the clipping area becomes clear, while if S is 0, the
   point in the clipping area is unchanged.

   If `mask' is an image, then it serves as alpha mask and is blended with
   the current clipping area. The source samples of mask determine which
   points of the clipping area are changed: if the value of the source
   sample in mask is S, then the corresponding point in the current clipping
   area will be multiplied by an alpha of S. (For example, if S is 0, then
   the point in the clipping area becomes clear, while if S is 1, the point
   in the clipping area is unchanged.

   If `mask' is an image, then it must be in the DeviceGray color space, may
   not have alpha, and may not be masked by an image mask or masking
   color. */

CG_EXTERN void CGContextClipToMask(CGContextRef __nullable c, CGRect rect,
    CGImageRef __nullable mask)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the bounding box of the clip path of `c' in user space. The
   bounding box is the smallest rectangle completely enclosing all points in
   the clip. */

CG_EXTERN CGRect CGContextGetClipBoundingBox(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Clipping convenience functions. **/

/* Intersect the current clipping path with `rect'. Note that this function
   resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRect(CGContextRef __nullable c, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Intersect the current clipping path with the clipping region formed by
   creating a path consisting of all rects in `rects'. Note that this
   function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRects(CGContextRef __nullable c,
    const CGRect *  rects, size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Primitive color functions. **/

/* Set the current fill color in the context `c' to `color'. */

CG_EXTERN void CGContextSetFillColorWithColor(CGContextRef __nullable c,
    CGColorRef __nullable color)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Set the current stroke color in the context `c' to `color'. */

CG_EXTERN void CGContextSetStrokeColorWithColor(CGContextRef __nullable c,
    CGColorRef __nullable color)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Color space functions. **/

/* Set the current fill color space in `context' to `space'. As a
   side-effect, set the fill color to a default value appropriate for the
   color space. */

CG_EXTERN void CGContextSetFillColorSpace(CGContextRef __nullable c,
    CGColorSpaceRef __nullable space)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `space'. As a
   side-effect, set the stroke color to a default value appropriate for the
   color space. */

CG_EXTERN void CGContextSetStrokeColorSpace(CGContextRef __nullable c,
    CGColorSpaceRef __nullable space)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Color functions. **/

/* Set the components of the current fill color in `context' to the values
   specifed by `components'. The number of elements in `components' must be
   one greater than the number of components in the current fill color space
   (N color components + 1 alpha component). The current fill color space
   must not be a pattern color space. */

CG_EXTERN void CGContextSetFillColor(CGContextRef __nullable c,
    const CGFloat * __nullable components)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the components of the current stroke color in `context' to the values
   specifed by `components'. The number of elements in `components' must be
   one greater than the number of components in the current stroke color
   space (N color components + 1 alpha component). The current stroke color
   space must not be a pattern color space. */

CG_EXTERN void CGContextSetStrokeColor(CGContextRef __nullable c,
    const CGFloat * __nullable components)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Pattern functions. **/

/* Set the components of the current fill color in `context' to the values
   specifed by `components', and set the current fill pattern to `pattern'.
   The number of elements in `components' must be one greater than the
   number of components in the current fill color space (N color components
   + 1 alpha component). The current fill color space must be a pattern
   color space. */

CG_EXTERN void CGContextSetFillPattern(CGContextRef __nullable c,
    CGPatternRef __nullable pattern, const CGFloat * __nullable components)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the components of the current stroke color in `context' to the values
   specifed by `components', and set the current stroke pattern to
   `pattern'. The number of elements in `components' must be one greater
   than the number of components in the current stroke color space (N color
   components + 1 alpha component). The current stroke color space must be a
   pattern color space. */

CG_EXTERN void CGContextSetStrokePattern(CGContextRef __nullable c,
    CGPatternRef __nullable pattern, const CGFloat * __nullable components)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the pattern phase in the current graphics state of `context' to
   `phase'. */

CG_EXTERN void CGContextSetPatternPhase(CGContextRef __nullable c, CGSize phase)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Color convenience functions. **/

/* Set the current fill color space in `context' to `DeviceGray' and set the
   components of the current fill color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayFillColor(CGContextRef __nullable c,
    CGFloat gray, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceGray' and set
   the components of the current stroke color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayStrokeColor(CGContextRef __nullable c,
    CGFloat gray, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current fill color space in `context' to `DeviceRGB' and set the
   components of the current fill color to `(red, green, blue, alpha)'. */

CG_EXTERN void CGContextSetRGBFillColor(CGContextRef __nullable c, CGFloat red,
    CGFloat green, CGFloat blue, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceRGB' and set
   the components of the current stroke color to `(red, green, blue,
   alpha)'. */

CG_EXTERN void CGContextSetRGBStrokeColor(CGContextRef __nullable c,
    CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current fill color space in `context' to `DeviceCMYK' and set the
   components of the current fill color to `(cyan, magenta, yellow, black,
   alpha)'. */

CG_EXTERN void CGContextSetCMYKFillColor(CGContextRef __nullable c,
    CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceCMYK' and set
   the components of the current stroke color to `(cyan, magenta, yellow,
   black, alpha)'. */

CG_EXTERN void CGContextSetCMYKStrokeColor(CGContextRef __nullable c,
    CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Rendering intent. **/

/* Set the rendering intent in the current graphics state of `context' to
   `intent'. */

CG_EXTERN void CGContextSetRenderingIntent(CGContextRef __nullable c,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Image functions. **/

/* Draw `image' in the rectangular area specified by `rect' in the context
   `c'. The image is scaled, if necessary, to fit into `rect'. */

CG_EXTERN void CGContextDrawImage(CGContextRef __nullable c, CGRect rect,
    CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Draw `image' tiled in the context `c'. The image is scaled to the size
   specified by `rect' in user space, positioned at the origin of `rect' in
   user space, then replicated, stepping the width of `rect' horizontally
   and the height of `rect' vertically, to fill the current clip region.
   Unlike patterns, the image is tiled in user space, so transformations
   applied to the CTM affect the final result. */

CG_EXTERN void CGContextDrawTiledImage(CGContextRef __nullable c, CGRect rect,
    CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the interpolation quality for image rendering of `context'. The
   interpolation quality is a gstate parameter which controls the level of
   interpolation performed when an image is interpolated (for example, when
   scaling the image). Note that it is merely a hint to the context: not all
   contexts support all interpolation quality levels. */

CG_EXTERN CGInterpolationQuality
    CGContextGetInterpolationQuality(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the interpolation quality of `context' to `quality'. */

CG_EXTERN void CGContextSetInterpolationQuality(CGContextRef __nullable c,
    CGInterpolationQuality quality)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Shadow support. **/

/* Set the shadow parameters in `context'. `offset' specifies a translation
   in base-space; `blur' is a non-negative number specifying the amount of
   blur; `color' specifies the color of the shadow, which may contain a
   non-opaque alpha value. If `color' is NULL, it's equivalent to specifying
   a fully transparent color. The shadow is a gstate parameter. After a
   shadow is specified, all objects drawn subsequently will be shadowed. To
   turn off shadowing, set the shadow color to a fully transparent color (or
   pass NULL as the color), or use the standard gsave/grestore mechanism. */

CG_EXTERN void CGContextSetShadowWithColor(CGContextRef __nullable c,
    CGSize offset, CGFloat blur, CGColorRef __nullable color)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to calling
     CGContextSetShadowWithColor(context, offset, blur, color)
   where color is black with 1/3 alpha (i.e., RGBA = {0, 0, 0, 1.0/3.0}) in
   the DeviceRGB color space. */

CG_EXTERN void CGContextSetShadow(CGContextRef __nullable c, CGSize offset,
    CGFloat blur)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Gradient and shading functions. **/

/* Fill the current clipping region of `context' with a linear gradient from
   `startPoint' to `endPoint'. The location 0 of `gradient' corresponds to
   `startPoint'; the location 1 of `gradient' corresponds to `endPoint';
   colors are linearly interpolated between these two points based on the
   values of the gradient's locations. The option flags control whether the
   gradient is drawn before the start point or after the end point. */

CG_EXTERN void CGContextDrawLinearGradient(CGContextRef __nullable c,
    CGGradientRef __nullable gradient, CGPoint startPoint, CGPoint endPoint,
    CGGradientDrawingOptions options)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Fill the current clipping region of `context' with a radial gradient
   between two circles defined by the center point and radius of each
   circle. The location 0 of `gradient' corresponds to a circle centered at
   `startCenter' with radius `startRadius'; the location 1 of `gradient'
   corresponds to a circle centered at `endCenter' with radius `endRadius';
   colors are linearly interpolated between these two circles based on the
   values of the gradient's locations. The option flags control whether the
   gradient is drawn before the start circle or after the end circle. */

CG_EXTERN void CGContextDrawRadialGradient(CGContextRef __nullable c,
    CGGradientRef __nullable gradient, CGPoint startCenter, CGFloat startRadius,
    CGPoint endCenter, CGFloat endRadius, CGGradientDrawingOptions options)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Fill the current clipping region of `context' with `shading'. */

CG_EXTERN void CGContextDrawShading(CGContextRef __nullable c,
    __nullable CGShadingRef shading)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/** Text functions. **/

/* Set the current character spacing in `context' to `spacing'. The
   character spacing is added to the displacement between the origin of one
   character and the origin of the next. */

CG_EXTERN void CGContextSetCharacterSpacing(CGContextRef __nullable c,
    CGFloat spacing)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the user-space point at which text will be drawn in the context `c'
   to `(x, y)'. */

CG_EXTERN void CGContextSetTextPosition(CGContextRef __nullable c,
    CGFloat x, CGFloat y)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the user-space point at which text will be drawn in `context'. */

CG_EXTERN CGPoint CGContextGetTextPosition(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the text matrix in the context `c' to `t'. */

CG_EXTERN void CGContextSetTextMatrix(CGContextRef __nullable c,
    CGAffineTransform t)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the text matrix in the context `c'. Returns CGAffineTransformIdentity
   if `c' is not a valid context. */

CG_EXTERN CGAffineTransform CGContextGetTextMatrix(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the text drawing mode in the current graphics state of the context
   `c' to `mode'. */

CG_EXTERN void CGContextSetTextDrawingMode(CGContextRef __nullable c,
    CGTextDrawingMode mode)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the font in the current graphics state of the context `c' to
   `font'. */

CG_EXTERN void CGContextSetFont(CGContextRef __nullable c,
    CGFontRef __nullable font)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the font size in the current graphics state of the context `c' to
   `size'. */

CG_EXTERN void CGContextSetFontSize(CGContextRef __nullable c, CGFloat size)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Draw `glyphs', an array of `count' CGGlyphs, at the points specified by
   `positions'. Each element of `positions' specifies the position from the
   associated glyph; the positions are specified in user space. */

CG_EXTERN void CGContextShowGlyphsAtPositions(CGContextRef __nullable c,
    const CGGlyph * __nullable glyphs, const CGPoint * __nullable Lpositions,
    size_t count)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/** PDF functions. **/

/* Draw `page' in the current user space of the context `c'. */

CG_EXTERN void CGContextDrawPDFPage(CGContextRef __nullable c,
    CGPDFPageRef __nullable page)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Output page functions. **/

/* Begin a new page. */

CG_EXTERN void CGContextBeginPage(CGContextRef __nullable c,
    const CGRect * __nullable mediaBox)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* End the current page. */

CG_EXTERN void CGContextEndPage(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Context functions. **/

/* Equivalent to `CFRetain(c)'. */

CG_EXTERN CGContextRef __nullable CGContextRetain(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(c)'. */

CG_EXTERN void CGContextRelease(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Flush all drawing to the destination. */

CG_EXTERN void CGContextFlush(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Synchronized drawing. */

CG_EXTERN void CGContextSynchronize(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Antialiasing functions. **/

/* Turn on antialiasing if `shouldAntialias' is true; turn it off otherwise.
   This parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldAntialias(CGContextRef __nullable c,
    bool shouldAntialias)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Allow antialiasing in `context' if `allowsAntialiasing' is true; don't
   allow it otherwise. This parameter is not part of the graphics state. A
   context will perform antialiasing if both `allowsAntialiasing' and the
   graphics state parameter `shouldAntialias' are true. */

CG_EXTERN void CGContextSetAllowsAntialiasing(CGContextRef __nullable c,
    bool allowsAntialiasing)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Font display functions. **/

/* Turn on font smoothing if `shouldSmoothFonts' is true; turn it off
   otherwise. This parameter is part of the graphics state. Note that this
   doesn't guarantee that font smoothing will occur: not all destination
   contexts support font smoothing. */

CG_EXTERN void CGContextSetShouldSmoothFonts(CGContextRef __nullable c,
    bool shouldSmoothFonts)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* If `allowsFontSmoothing' is true, then allow font smoothing when
   displaying text in `context'; otherwise, don't allow font smoothing. This
   parameter is not part of the graphics state. Fonts will be smoothed if
   they are antialiased when drawn and if both `allowsFontSmoothing' and the
   graphics state parameter `shouldSmoothFonts' are true. */
 
CG_EXTERN void CGContextSetAllowsFontSmoothing(CGContextRef __nullable c,
    bool allowsFontSmoothing)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* If `shouldSubpixelPositionFonts' is true, then glyphs may be placed at
   subpixel positions (if allowed) when displaying text in `context';
   otherwise, glyphs will be forced to integer pixel boundaries. This
   parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldSubpixelPositionFonts(
    CGContextRef __nullable c, bool shouldSubpixelPositionFonts)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `allowsFontSubpixelPositioning' is true, then allow font subpixel
   positioning when displaying text in `context'; otherwise, don't allow
   subpixel positioning. This parameter is not part of the graphics state. A
   context will place glyphs at subpixel positions if fonts will be
   antialiased when drawn and if both `allowsFontSubpixelPositioning' and
   the graphics state parameter `shouldSubpixelPositionFonts' are true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelPositioning(
    CGContextRef __nullable c, bool allowsFontSubpixelPositioning)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `shouldSubpixelQuantizeFonts' is true, then quantize the subpixel
   positions of glyphs when displaying text in `context'; otherwise, don't
   quantize the subpixel positions. This parameter is part of the graphics
   state. */

CG_EXTERN void CGContextSetShouldSubpixelQuantizeFonts(
    CGContextRef __nullable c, bool shouldSubpixelQuantizeFonts)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `allowsFontSubpixelQuantization' is true, then allow font subpixel
   quantization when displaying text in `context'; otherwise, don't allow
   subpixel quantization. This parameter is not part of the graphics state.
   A context quantizes subpixel positions if glyphs will be drawn at
   subpixel positions and `allowsFontSubpixelQuantization' and the graphics
   state parameter `shouldSubpixelQuantizeFonts' are both true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelQuantization(
    CGContextRef __nullable c, bool allowsFontSubpixelQuantization)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/** Transparency layer support. **/

/* Begin a transparency layer in `context'. All subsequent drawing
   operations until a corresponding `CGContextEndTransparencyLayer' are
   composited into a fully transparent backdrop (which is treated as a
   separate destination buffer from the context). After the transparency
   layer is ended, the result is composited into the context using the
   global alpha and shadow state of the context. This operation respects the
   clipping region of the context. After a call to this function, all of the
   parameters in the graphics state remain unchanged with the exception of
   the following:
     - The global alpha is set to 1.
     - The shadow is turned off.
     - The blend mode is set to `kCGBlendModeNormal'.
   Ending the transparency layer restores these parameters to the values
   they had before `CGContextBeginTransparencyLayer' was called.
   Transparency layers may be nested. */

CG_EXTERN void CGContextBeginTransparencyLayer(CGContextRef __nullable c,
    CFDictionaryRef __nullable auxiliaryInfo)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Begin a transparency layer in `context'. This function is identical to
  `CGContextBeginTransparencyLayer' except that the content of the
  transparency layer will be bounded by `rect' (specified in user space). */

CG_EXTERN void CGContextBeginTransparencyLayerWithRect(
    CGContextRef __nullable c, CGRect rect, CFDictionaryRef __nullable auxInfo)
    CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* End a tranparency layer. */

CG_EXTERN void CGContextEndTransparencyLayer(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** User space to device space tranformations. **/

/* Return the affine transform mapping the user space (abstract coordinates)
   of `context' to device space (pixels). */

CG_EXTERN CGAffineTransform
    CGContextGetUserSpaceToDeviceSpaceTransform(CGContextRef __nullable c)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' from the user space of `context' to device space. */

CG_EXTERN CGPoint CGContextConvertPointToDeviceSpace(CGContextRef __nullable c,
    CGPoint point)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' from device space to the user space of `context'. */

CG_EXTERN CGPoint CGContextConvertPointToUserSpace(CGContextRef __nullable c,
    CGPoint point)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `size' from the user space of `context' to device space. */

CG_EXTERN CGSize CGContextConvertSizeToDeviceSpace(CGContextRef __nullable c,
    CGSize size)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `size' from device space to the user space of `context'. */

CG_EXTERN CGSize CGContextConvertSizeToUserSpace(CGContextRef __nullable c,
    CGSize size)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `rect' from the user space of `context' to device space. Since
   affine transforms do not preserve rectangles in general, this function
   returns the smallest rectangle which contains the transformed corner
   points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToDeviceSpace(CGContextRef __nullable c,
    CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `rect' from device space to the user space of `context'. Since
   affine transforms do not preserve rectangles in general, this function
   returns the smallest rectangle which contains the transformed corner
   points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToUserSpace(CGContextRef __nullable c,
    CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Deprecated functions. **/

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextSelectFont(CGContextRef __nullable c,
    const char * __nullable name, CGFloat size, CGTextEncoding textEncoding)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowText(CGContextRef __nullable c,
    const char * __nullable string, size_t length)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowTextAtPoint(CGContextRef __nullable c,
    CGFloat x, CGFloat y, const char * __nullable string, size_t length)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphs(CGContextRef __nullable c,
    const CGGlyph * __nullable g, size_t count)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphsAtPoint(CGContextRef __nullable c, CGFloat x,
    CGFloat y, const CGGlyph * __nullable glyphs, size_t count)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphsWithAdvances(CGContextRef __nullable c,
    const CGGlyph * __nullable glyphs, const CGSize * __nullable advances,
    size_t count)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_9,
                                __IPHONE_2_0, __IPHONE_7_0);

/* DEPRECATED; use the CGPDFPage API instead. */

CG_EXTERN void CGContextDrawPDFDocument(CGContextRef __nullable c, CGRect rect,
    CGPDFDocumentRef __nullable document, int page)
    CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
                                __IPHONE_NA, __IPHONE_NA);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCONTEXT_H_ */
// ==========  CoreGraphics.framework/Headers/CGDataConsumer.h
/* CoreGraphics - CGDataConsumer.h
 * Copyright (c) 1999-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGDATACONSUMER_H_
#define CGDATACONSUMER_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGDataConsumer *CGDataConsumerRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* This callback is called to copy `count' bytes from `buffer' to the data
   consumer. */

typedef size_t (*CGDataConsumerPutBytesCallback)(void * __nullable info,
    const void *  buffer, size_t count);

/* This callback is called to release the `info' pointer when the data
   provider is freed. */

typedef void (*CGDataConsumerReleaseInfoCallback)(void * __nullable info);

/* Callbacks for writing data.
   `putBytes' copies `count' bytes from `buffer' to the consumer, and
     returns the number of bytes copied. It should return 0 if no more data
     can be written to the consumer.
   `releaseConsumer', if non-NULL, is called when the consumer is freed. */

struct CGDataConsumerCallbacks {
    CGDataConsumerPutBytesCallback __nullable putBytes;
    CGDataConsumerReleaseInfoCallback __nullable releaseConsumer;
};
typedef struct CGDataConsumerCallbacks CGDataConsumerCallbacks;

/* Return the CFTypeID for CGDataConsumerRefs. */

CG_EXTERN CFTypeID CGDataConsumerGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a data consumer using `callbacks' to handle the data. `info' is
   passed to each of the callback functions. */

CG_EXTERN CGDataConsumerRef __nullable CGDataConsumerCreate(
    void * __nullable info, const CGDataConsumerCallbacks * __nullable cbks)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a data consumer which writes data to `url'. */

CG_EXTERN CGDataConsumerRef __nullable CGDataConsumerCreateWithURL(
    CFURLRef __nullable url)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a data consumer which writes to `data'. */

CG_EXTERN CGDataConsumerRef __nullable CGDataConsumerCreateWithCFData(
    CFMutableDataRef __nullable data)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Equivalent to `CFRetain(consumer)'. */

CG_EXTERN CGDataConsumerRef __nullable CGDataConsumerRetain(
    CGDataConsumerRef __nullable consumer)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(consumer)'. */

CG_EXTERN void CGDataConsumerRelease(__nullable CGDataConsumerRef consumer)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* CGDATACONSUMER_H_ */
// ==========  CoreGraphics.framework/Headers/CGPattern.h
/* CoreGraphics - CGPattern.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPATTERN_H_
#define CGPATTERN_H_

typedef struct CGPattern *CGPatternRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* kCGPatternTilingNoDistortion: The pattern cell is not distorted when
   painted, however the spacing between pattern cells may vary by as much as
   1 device pixel.

   kCGPatternTilingConstantSpacingMinimalDistortion: Pattern cells are
   spaced consistently, however the pattern cell may be distorted by as much
   as 1 device pixel when the pattern is painted.

   kCGPatternTilingConstantSpacing: Pattern cells are spaced consistently as
   with kCGPatternTilingConstantSpacingMinimalDistortion, however the
   pattern cell may be distorted additionally to permit a more efficient
   implementation. */

typedef CF_ENUM (int32_t, CGPatternTiling) {
    kCGPatternTilingNoDistortion,
    kCGPatternTilingConstantSpacingMinimalDistortion,
    kCGPatternTilingConstantSpacing
};

/* The drawing of the pattern is delegated to the callbacks. The callbacks
   may be called one or many times to draw the pattern.
    `version' is the version number of the structure passed in as a
      parameter to the CGPattern creation functions. The structure defined
      below is version 0.
    `drawPattern' should draw the pattern in the context `c'. `info' is the
      parameter originally passed to the CGPattern creation functions.
    `releaseInfo' is called when the pattern is deallocated. */

typedef void (*CGPatternDrawPatternCallback)(void * __nullable info,
                                             CGContextRef __nullable context);
typedef void (*CGPatternReleaseInfoCallback)(void * __nullable info);

struct CGPatternCallbacks {
    unsigned int version;
    CGPatternDrawPatternCallback __nullable drawPattern;
    CGPatternReleaseInfoCallback __nullable releaseInfo;
};
typedef struct CGPatternCallbacks CGPatternCallbacks;

/* Return the CFTypeID for CGPatternRefs. */

CG_EXTERN CFTypeID CGPatternGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a pattern. */

CG_EXTERN CGPatternRef __nullable CGPatternCreate(void * __nullable info,
    CGRect bounds, CGAffineTransform matrix, CGFloat xStep, CGFloat yStep,
    CGPatternTiling tiling, bool isColored,
    const CGPatternCallbacks * __nullable callbacks)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRetain(pattern)', except it doesn't crash (as CF does)
   if `pattern' is NULL. */

CG_EXTERN CGPatternRef __nullable CGPatternRetain(CGPatternRef __nullable pattern)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(pattern)', except it doesn't crash (as CF does)
   if `pattern' is NULL. */

CG_EXTERN void CGPatternRelease(CGPatternRef __nullable pattern)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPATTERN_H_ */
// ==========  CoreGraphics.framework/Headers/CGImage.h
/* CoreGraphics - CGImage.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGIMAGE_H_
#define CGIMAGE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGImage *CGImageRef;

#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGGeometry.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

typedef CF_ENUM(uint32_t, CGImageAlphaInfo) {
  kCGImageAlphaNone,               /* For example, RGB. */
  kCGImageAlphaPremultipliedLast,  /* For example, premultiplied RGBA */
  kCGImageAlphaPremultipliedFirst, /* For example, premultiplied ARGB */
  kCGImageAlphaLast,               /* For example, non-premultiplied RGBA */
  kCGImageAlphaFirst,              /* For example, non-premultiplied ARGB */
  kCGImageAlphaNoneSkipLast,       /* For example, RBGX. */
  kCGImageAlphaNoneSkipFirst,      /* For example, XRGB. */
  kCGImageAlphaOnly                /* No color data, alpha data only */
};

typedef CF_OPTIONS(uint32_t, CGBitmapInfo) {
  kCGBitmapAlphaInfoMask = 0x1F,
  kCGBitmapFloatComponents = (1 << 8),
    
  kCGBitmapByteOrderMask = 0x7000,
  kCGBitmapByteOrderDefault = (0 << 12),
  kCGBitmapByteOrder16Little = (1 << 12),
  kCGBitmapByteOrder32Little = (2 << 12),
  kCGBitmapByteOrder16Big = (3 << 12),
  kCGBitmapByteOrder32Big = (4 << 12)
} CF_ENUM_AVAILABLE(10_4, 2_0);

#ifdef __BIG_ENDIAN__
# define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Big
# define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Big
#else    /* Little endian. */
# define kCGBitmapByteOrder16Host kCGBitmapByteOrder16Little
# define kCGBitmapByteOrder32Host kCGBitmapByteOrder32Little
#endif

/* Return the CFTypeID for CGImageRefs. */

CG_EXTERN CFTypeID CGImageGetTypeID(void)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create an image. */

CG_EXTERN CGImageRef __nullable CGImageCreate(size_t width, size_t height,
    size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow,
    CGColorSpaceRef __nullable space, CGBitmapInfo bitmapInfo,
    CGDataProviderRef __nullable provider,
    const CGFloat * __nullable decode, bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create an image mask. */

CG_EXTERN CGImageRef __nullable CGImageMaskCreate(size_t width, size_t height,
    size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow,
    CGDataProviderRef __nullable provider, const CGFloat * __nullable decode,
    bool shouldInterpolate)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a copy of `image'. Only the image structure itself is copied; the
   underlying data is not. */

CG_EXTERN CGImageRef __nullable CGImageCreateCopy(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create an image from `source', a data provider of JPEG-encoded data. */

CG_EXTERN CGImageRef __nullable CGImageCreateWithJPEGDataProvider(
    CGDataProviderRef __nullable source, const CGFloat * __nullable decode,
    bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_2_0);

/* Create an image using `source', a data provider for PNG-encoded data. */

CG_EXTERN CGImageRef __nullable CGImageCreateWithPNGDataProvider(
    CGDataProviderRef __nullable source, const CGFloat * __nullable decode,
    bool shouldInterpolate,
    CGColorRenderingIntent intent)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create an image using the data contained within the subrectangle `rect'
   of `image'.

   The new image is created by
     1) adjusting `rect' to integral bounds by calling "CGRectIntegral";
     2) intersecting the result with a rectangle with origin (0, 0) and size
        equal to the size of `image';
     3) referencing the pixels within the resulting rectangle, treating the
        first pixel of the image data as the origin of the image.
   If the resulting rectangle is the null rectangle, this function returns
   NULL.

   If W and H are the width and height of image, respectively, then the
   point (0,0) corresponds to the first pixel of the image data; the point
   (W-1, 0) is the last pixel of the first row of the image data; (0, H-1)
   is the first pixel of the last row of the image data; and (W-1, H-1) is
   the last pixel of the last row of the image data.

   The resulting image retains a reference to the original image, so you may
   release the original image after calling this function. */

CG_EXTERN CGImageRef __nullable CGImageCreateWithImageInRect(
    CGImageRef __nullable image, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a new image from `image' masked by `mask', which may be an image
   mask or an image.

   If `mask' is an image mask, then it indicates which parts of the context
   are to be painted with the image when drawn in a context, and which are
   to be masked out (left unchanged). The source samples of the image mask
   determine which areas are painted, acting as an "inverse alpha": if the
   value of a source sample in the image mask is S, then the corresponding
   region in `image' is blended with the destination using an alpha of
   (1-S). (For example, if S is 1, then the region is not painted, while if
   S is 0, the region is fully painted.)

   If `mask' is an image, then it serves as alpha mask for blending the
   image onto the destination. The source samples of `mask' determine which
   areas are painted: if the value of the source sample in mask is S, then
   the corresponding region in image is blended with the destination with an
   alpha of S. (For example, if S is 0, then the region is not painted,
   while if S is 1, the region is fully painted.)

   The parameter `image' may not be an image mask and may not have an image
   mask or masking color associated with it.
  
   If `mask' is an image, then it must be in a monochrome color space
   (e.g. DeviceGray, GenericGray, etc...), may not have alpha, and may not
   itself be masked by an image mask or a masking color. */

CG_EXTERN CGImageRef __nullable CGImageCreateWithMask(
    CGImageRef __nullable image, CGImageRef __nullable mask)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a new image from `image' masked by `components', an array of 2N
   values { min[1], max[1], ... min[N], max[N] } where N is the number of
   components in color space of `image'. Any image sample with color value
   {c[1], ... c[N]} where min[i] <= c[i] <= max[i] for 1 <= i <= N is masked
   out (that is, not painted).

   Each value in `components' must be a valid image sample value: if `image'
   has integral pixel components, then each value of must be in the range
   [0..2**bitsPerComponent - 1] (where `bitsPerComponent' is the number of
   bits/component of `image'); if `image' has floating-point pixel
   components, then each value may be any floating-point number which is a
   valid color component.

   The parameter `image' may not be an image mask, and may not already have
   an image mask or masking color associated with it. */

CG_EXTERN CGImageRef __nullable CGImageCreateWithMaskingColors(
    CGImageRef __nullable image, const CGFloat * __nullable components)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a copy of `image', replacing the image's color space with `space'.
   Returns NULL if `image' is an image mask, or if the number of components
   of `space' isn't the same as the number of components of the color space
   of `image'. */

CG_EXTERN CGImageRef __nullable CGImageCreateCopyWithColorSpace(
    CGImageRef __nullable image, CGColorSpaceRef __nullable space)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRetain(image)'. */

CG_EXTERN CGImageRef __nullable CGImageRetain(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(image)'. */

CG_EXTERN void CGImageRelease(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `image' is an image mask, false otherwise. */

CG_EXTERN bool CGImageIsMask(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the width of `image'. */

CG_EXTERN size_t CGImageGetWidth(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the height of `image'. */

CG_EXTERN size_t CGImageGetHeight(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bits/component of `image'. */

CG_EXTERN size_t CGImageGetBitsPerComponent(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bits/pixel of `image'. */

CG_EXTERN size_t CGImageGetBitsPerPixel(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the number of bytes/row of `image'. */

CG_EXTERN size_t CGImageGetBytesPerRow(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the color space of `image', or NULL if `image' is an image
   mask. */

CG_EXTERN CGColorSpaceRef __nullable CGImageGetColorSpace(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the alpha info of `image'. */

CG_EXTERN CGImageAlphaInfo CGImageGetAlphaInfo(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the data provider of `image'. */

CG_EXTERN CGDataProviderRef __nullable CGImageGetDataProvider(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the decode array of `image'. */

CG_EXTERN const CGFloat * __nullable CGImageGetDecode(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the interpolation parameter of `image'. */

CG_EXTERN bool CGImageGetShouldInterpolate(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the rendering intent of `image'. */

CG_EXTERN CGColorRenderingIntent CGImageGetRenderingIntent(__nullable CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the bitmap info of `image'. */

CG_EXTERN CGBitmapInfo CGImageGetBitmapInfo(CGImageRef __nullable image)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the UTType of `image'. */

CG_EXTERN CFStringRef  __nullable CGImageGetUTType(__nullable CGImageRef image)
    CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* CGIMAGE_H_ */
// ==========  CoreGraphics.framework/Headers/CGPDFObject.h
/* CoreGraphics - CGPDFObject.h
   Copyright (c) 2002-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFOBJECT_H_
#define CGPDFOBJECT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* A type for boolean values. */

typedef unsigned char CGPDFBoolean;

/* A type for integer values. */

typedef long int CGPDFInteger;

/* A type for real values. */

typedef CGFloat CGPDFReal;

/* A type to hold any object. */

typedef union CGPDFObject *CGPDFObjectRef;

/* An identifier to describe an object's type. */

typedef CF_ENUM (int32_t, CGPDFObjectType) {
  kCGPDFObjectTypeNull = 1,
  kCGPDFObjectTypeBoolean,
  kCGPDFObjectTypeInteger,
  kCGPDFObjectTypeReal,
  kCGPDFObjectTypeName,
  kCGPDFObjectTypeString,
  kCGPDFObjectTypeArray,
  kCGPDFObjectTypeDictionary,
  kCGPDFObjectTypeStream
};

/* Return the type of `object'. */

CG_EXTERN CGPDFObjectType CGPDFObjectGetType(CGPDFObjectRef __nullable object)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Get the value of `object'. If the type of `object' is equal to `type',
   then copy the value of `object' to `value' (if it's non-NULL) and return
   true. Otherwise, if the type of `object' is `kCGPDFObjectTypeInteger' and
   `type' is equal to `kCGPDFObjectTypeReal', then convert the value of
   `object' to floating point and copy the result to `value' (if it's
   non-NULL) and return true. Otherwise, return false. */

CG_EXTERN bool CGPDFObjectGetValue(CGPDFObjectRef __nullable object,
    CGPDFObjectType type, void * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFOBJECT_H_ */
